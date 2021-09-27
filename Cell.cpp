#include "Cell.h"
#include "Mapping.h"
#include <math.h>
#include <iostream>
using namespace std;

double Cell::CalculateWriteEnergy(){
    //rewrite mapper to store the current value in the cell for the write energy
    
   double I_in = this->dutyCycle*0.01*(this->Imax_ref-this->Imin_ref)+this->Imin_ref;

   //cout << pow(I, 2)*(this->T_ref) << endl;
    return I_in*I_in*(this->T_ref)*(2*this->RN+this->RHM);
}

double ATMTrack::CalculateReadEnergy(){
    //double I = this->dutyCycle*(this->Imax_ref-this->Imin_ref)+this->Imin_ref;
    double I = this->input->Imax_ref;  
    double other = I*I*this->T_ref*(4*this->RN+2*this->RHM);
    //cout << "I^2 T term : " << other << endl;
    //cout << "Other term: " << other << endl;
    return I*I*(this->T_ref-this->risingPulseTime)*(4*this->RN+2*this->RHM)+this->CalculateEAT()+this->CalculateEMTJ()+this->CalculateERF()+this->CalculateEBUFF();
}

double ATCTrack::CalculateReadEnergy(){
    //double I = this->dutyCycle*(this->Imax_ref-this->Imin_ref)+this->Imin_ref;
    double I = this->input->Imax_ref;  
    double other = I*I*this->T_ref*(4*this->RN+2*this->RHM);
    //cout << "I^2 T term : " << other << endl;
    //cout << "Other term: " << other << endl;
    return I*I*(this->T_ref-this->risingPulseTime)*(2*this->RN+this->RHM)+this->CalculateEAT()+this->CalculateEMTJ()+this->CalculateERF()+this->CalculateEBUFF();
}

double Cell::CalculateEraseEnergy(){
    double I = this->dutyCycle*this->Imax_ref+this->Imin_ref;
    return (pow(I, 2)*this->T_ref)*(2*this->RN+this->RHM)+this->CalculateEMTJ()+this->CalculateEAT()+this->CalculateERF()+this->CalculateEBUFF();
}

double Cell::CalculateEMTJ(){
    double EMTJ = (((this->VMH*this->VMH))/this->RH)*(this->T_ref-this->risingPulseTime)+(((this->VML*this->VML)))/this->RL*this->risingPulseTime;
   // cout << "EMTJ " << EMTJ << endl;
    return EMTJ;
}

double Cell::CalculateEAT(){
    double EAT = ((this->VMH*this->VMH)/this->R0)*(this->T_ref-this->risingPulseTime)+(((this->VML*this->VML)))/this->R0*this->risingPulseTime;
    //cout << "EAT " << EAT << endl;
    return EAT;
}

double Cell::CalculateERF(){
    double ERF = (((this->Vb*this->Vb)-this->VMH)/this->Rf)*(this->T_ref-this->risingPulseTime)+(((this->Vb*this->Vb)-this->VML)/this->Rf)*this->risingPulseTime;
 // cout <<"ERF "<< ERF << endl;
    return ERF;
}

double Cell::CalculateEBUFF(){
    double CBUFF = this->CBUFF*this->VDD*this->VDD;
   //  cout <<"CBUFF "<< CBUFF << endl;
    return CBUFF;
}

void ATMTrack::Initialize(int x, int y){
    this->input = new Inputs();
    this->x=x;
    this->y=y;
    this->numStates = this->input->numStates;
    Imax_ref = this->input->Imax_ref;
    Imin_ref = this->input->Imin_ref;
    this->position = 0.0;
    this->trackLength = this->input->LRTM;
    dutyCycle = 0;
    this->risingPulseTime = 0;
    this->recoveryPosition = 0.0;
    this->recoveryRisingPulseTime = 0;
    this->recoveryDutyCycle = 0;
    T_ref = this->input->T_ref;
    RHM = this->input->RHM;
    RN = this->input->RN;
    RH = this->input->RH;
    RL = this->input->RL;
    R0 = this->input->R0;
    Rf = this->input->Rf;
    Vb = this->input->Vb;
    VDD = this->input->VDD;
    RHM = this->input->RHM;
    CBUFF = this->input->CBUFF;
    VMH = this->input->VMH;
    VML = this->input->VML;
    WRTM = this->input->WRTM;
    LRTM = this->input->LRTM;
    CMOS_GAP = this->input->CMOS_GAP;
    RTM_GAP = this->input->RTM_GAP;
    readEnergy = 0;
    writeEnergy = 0;


}
double ATMTrack::CalculateRecoveryEnergy(){
    return this->CalculateReadEnergy();
}
double ATMTrack::Read(){
    this->recoveryPosition = this->position;
    this->recoveryDutyCycle = this->dutyCycle;
    this->recoveryRisingPulseTime = this->risingPulseTime;
    this->position = this->trackLength;
    dutyCycle = 100;
    double time = this->risingPulseTime;
    risingPulseTime = this->T_ref;
    return time;
}

void ATMTrack::Write(double I){
    double dutyCycleNew = MapDutyCycle(this->numStates, I, this->Imin_ref, this->Imax_ref);
    dutyCycle = dutyCycleNew;
    this->position = this->trackLength*dutyCycleNew/100;
    risingPulseTime = dutyCycleNew/100 * this->T_ref;
}

double ATMTrack::Recover(){
    dutyCycle = this->recoveryDutyCycle;
    this->position = this->recoveryPosition;
    risingPulseTime = this->recoveryRisingPulseTime;
    this->recoveryDutyCycle = 0;
    this->recoveryRisingPulseTime = 0;
    this->recoveryPosition = 0;
    return this->position;
}

void ATMTrack::Erase(){
    dutyCycle = 0;
    this->position = 0;
    risingPulseTime = 0;
    this->recoveryDutyCycle = 0;
    this->recoveryRisingPulseTime = 0;
    this->recoveryPosition = 0;
}

double ATMTrack::CalculateArea(){
    double CMOS_AREA = 4*(((3*featureSize+CMOS_GAP)*(featureSize+CMOS_GAP))+3*(10*featureSize+CMOS_GAP)*(featureSize+CMOS_GAP));
    double RTM_AREA = (2*WRTM+2*RTM_GAP)*(LRTM+2*RTM_GAP);
    return max(CMOS_AREA, RTM_AREA);
}

void ATMTrack::PrintProperty(const char *str){
    cout << "-----------" << endl;
    cout << str << endl;
    cout << "Area : " << this->CalculateArea() << endl;
    cout << "Positions" << endl;
    cout << " - Main track position : " << this->position << endl;
    cout << " - Main track duty cycle : " << this->dutyCycle << endl;
    cout << " - Main track rising pulse time : " << this->risingPulseTime << endl;
    cout << " - Recovery track position : " << this->recoveryPosition << endl;
    cout << " - Recovery track duty cycle : " << this->recoveryDutyCycle << endl;
    cout << " - Recovery track rising pulse time : " << this->recoveryRisingPulseTime << endl;
    cout << "Energy" << endl;
    cout << " - Write Energy : " << this->CalculateWriteEnergy() << endl;
    cout << " - Read/Recover Energy : " << this->CalculateReadEnergy() << endl;
    cout << " - Erase Energy : " << this->CalculateEraseEnergy() << endl;  
    cout << "------------------" << endl;
}

void ATCTrack::Initialize(int x, int y){
    this->input = new Inputs();
    this->x=x;
    this->y=y;
    this->numStates = this->input->numStates;
    Imax_ref = this->input->Imax_ref;
    Imin_ref = this->input->Imin_ref;
    this->position = 0.0;
    this->trackLength = this->input->LRTM;
    dutyCycle = 0;
    this->risingPulseTime = 0;
    T_ref = this->input->T_ref;
    RHM = this->input->RHM;
    RN = this->input->RN;
    RH = this->input->RH;
    RL = this->input->RL;
    R0 = this->input->R0;
    Rf = this->input->Rf;
    Vb = this->input->Vb;
    VDD = this->input->VDD;
    RHM = this->input->RHM;
    CBUFF = this->input->CBUFF;
    VMH = this->input->VMH;
    VML = this->input->VML;
    WRTM = this->input->WRTM;
    LRTM = this->input->LRTM;
    CMOS_GAP = this->input->CMOS_GAP;
    RTM_GAP = this->input->RTM_GAP;
    readEnergy = 0;
    writeEnergy = 0;

}

double ATCTrack::Read(){
    this->position = this->trackLength;
    dutyCycle = 100;
    double time = this->risingPulseTime;
    risingPulseTime = this->T_ref;
    return time;
}

void ATCTrack::Write(double I){
    double dutyCycleNew = MapDutyCycle(this->numStates, I, this->Imin_ref, this->Imax_ref);
    dutyCycle = dutyCycleNew;
    this->position = this->trackLength*dutyCycleNew/100;
    risingPulseTime = dutyCycleNew/100 * this->T_ref;
}

void ATCTrack::Erase(){
    dutyCycle = 0;
    this->position = 0;
    risingPulseTime = 0;
}

double ATCTrack::CalculateArea(){
    double CMOS_AREA = 2*(3*featureSize+CMOS_GAP)*(featureSize+CMOS_GAP)+2*(10*featureSize+CMOS_GAP)*(featureSize+CMOS_GAP);
    //cout << CMOS_AREA << endl;
    double RTM_AREA = (WRTM + RTM_GAP)*(LRTM+RTM_GAP);
    //cout << RTM_AREA << endl;
    return max(CMOS_AREA, RTM_AREA);
}

void ATCTrack::PrintProperty(const char *str){
    cout << "-----------" << endl;
    cout << str << endl;
    cout << "Area : " << this->CalculateArea() << endl;
    cout << "Positions" << endl;
    cout << " - Main track position : " << this->position << endl;
    cout << " - Main track duty cycle : " << this->dutyCycle << endl;
    cout << " - Main track rising pulse time : " << this->risingPulseTime << endl;
    cout << "Energy" << endl;
    cout << " - Write Energy : " << this->CalculateWriteEnergy() << endl;
    cout << " - Read/Recover Energy : " << this->CalculateReadEnergy() << endl;
    cout << " - Erase Energy : " << this->CalculateEraseEnergy() << endl;  
    cout << " --------------- " << endl;
}

double pow(double i, int j){
    double result = i;
    for(int n = 0; n < j; n++){
        result *= i;
    }
    return result;
}