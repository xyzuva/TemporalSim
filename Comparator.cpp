#include "Comparator.h"
#include <iostream>
using namespace std;
void Comparator::Initialize(){
    this->input = new Inputs();
    this->RHM = this->input->RHM;
    this->RN = this->input->RN;
    this->RL = this->input->RL;
    this->R0 = this->input->R0;
    this->RN = this->input->RN;
    this->Rf = this->input->Rf;
    this->RH = this->input->RH;
    this->VDD = this->input->VDD;
    this->VCPM = 1;
    this->VML = this->input->VML;
    this->VMH = this->input->VMH;
    this->Vb = this->input->Vb; 
    this->CBUFF = this->input->CBUFF;
    this->CMOS_GAP = this->input->CMOS_GAP;
    this->WRTM = this->input->WRTM;
    this->RTM_GAP = this->input->RTM_GAP;
    this->RS = this->input->Rs;
    this->featureSize = this->input->featureSize;
}

int Comparator::Output(ATCTrack **atc, ATMTrackArray *arr, int  colNum, int numRows, VoltageToCurrentConverter *V2I){
    this->comparisonEnergy = 0;
    if(colNum%2 == 0){
        
        double T_OFF_AND = max(arr->cell[colNum][0]->dutyCycle, atc[0]->dutyCycle);
       // cout << "ATC : " << atc[0]->dutyCycle << " ";
        //cout << "ATM : " << arr->cell[colNum][0]->dutyCycle << endl;
        this->comparisonEnergy += this->CalculateComparisonEnergy(atc[0], arr->cell[colNum][0], colNum);
       // arr->readEnergy += arr->cell[colNum][0]->CalculateReadEnergy();
        atc[0]->readEnergy += atc[0]->CalculateReadEnergy();
     //   V2I->energy += V2I->CalculateEnergy(this->input->VDD, (arr->cell[colNum][0]->dutyCycle)*((arr->cell[colNum][0]->Imax_ref-arr->cell[colNum][0]->Imin_ref)));
       // V2I->energy += V2I->CalculateEnergy(this->input->VDD, (atc[0]->dutyCycle)*((atc[0]->Imax_ref-atc[0]->Imin_ref)));
        if(T_OFF_AND == atc[0]->dutyCycle){
            this->VCPM = 1;
        }
        else{
            this->VCPM = 0;
        }
        for(int i = 1; i < numRows; i++){
         //           cout << "ATC : " << atc[i]->dutyCycle << " ";
       // cout << "ATM : " << arr->cell[colNum][i]->dutyCycle << endl;
            T_OFF_AND = max(arr->cell[colNum][i]->dutyCycle, atc[i]->dutyCycle);
            this->comparisonEnergy += this->CalculateComparisonEnergy(atc[i], arr->cell[colNum][i], colNum);
         //   arr->readEnergy += arr->cell[colNum][i]->CalculateReadEnergy();
            atc[i]->readEnergy += atc[i]->CalculateReadEnergy();
         //   V2I->energy += V2I->CalculateEnergy(this->input->VDD, (arr->cell[colNum][0]->dutyCycle)*((arr->cell[colNum][0]->Imax_ref-arr->cell[colNum][0]->Imin_ref)));
           // V2I->energy += V2I->CalculateEnergy(this->input->VDD, (atc[0]->dutyCycle)*((atc[0]->Imax_ref-atc[0]->Imin_ref)));
            if(T_OFF_AND != atc[i]->dutyCycle){
                this->VCPM = 0;
            }
        }
        return this->VCPM;
    }
    else{
        double T_OFF_OR = min(arr->cell[colNum][0]->dutyCycle, atc[0]->dutyCycle);
        this->comparisonEnergy += this->CalculateComparisonEnergy(atc[0], arr->cell[colNum][0], colNum);
      //  arr->readEnergy += arr->cell[colNum][0]->CalculateReadEnergy();
        atc[0]->readEnergy += atc[0]->CalculateReadEnergy();
      //  V2I->energy += V2I->CalculateEnergy(this->input->VDD, (arr->cell[colNum][0]->dutyCycle)*((arr->cell[colNum][0]->Imax_ref-arr->cell[colNum][0]->Imin_ref)));
      //  V2I->energy += V2I->CalculateEnergy(this->input->VDD, (atc[0]->dutyCycle)*((atc[0]->Imax_ref-atc[0]->Imin_ref)));
        if(T_OFF_OR == atc[0]->dutyCycle){
            this->VCPM = 1;
        }
        else{
            this->VCPM = 0;
        }
        for(int i = 1; i < numRows; i++){
            T_OFF_OR = min(arr->cell[colNum][i]->dutyCycle, atc[i]->dutyCycle);
            this->comparisonEnergy += this->CalculateComparisonEnergy(atc[i], arr->cell[colNum][i], colNum);
           // arr->readEnergy += arr->cell[colNum][i]->CalculateReadEnergy();
            atc[i]->readEnergy += atc[i]->CalculateReadEnergy();
        //    V2I->energy += V2I->CalculateEnergy(this->input->VDD, (arr->cell[colNum][0]->dutyCycle)*((arr->cell[colNum][0]->Imax_ref-arr->cell[colNum][0]->Imin_ref)));
         //   V2I->energy += V2I->CalculateEnergy(this->input->VDD, (atc[0]->dutyCycle)*((atc[0]->Imax_ref-atc[0]->Imin_ref)));
            if(T_OFF_OR != atc[i]->dutyCycle){
                //cout << atc[i]->dutyCycle << " : " << arr->cell[colNum][i]->dutyCycle << endl;
                this->VCPM = 0;
            }
        }  
        return this->VCPM;
    }
    
}


double Comparator::CalculateComparisonEnergy(ATCTrack* atc, ATMTrack* atm, int colNum){ 
    double comparisonEnergy = (pow(this->VDD,2)/(2*this->R0*this->RHM))*(max(atc->risingPulseTime, atm->risingPulseTime))+this->CalculateEMTJ(atc, atm, colNum)+this->CalculateEAT(atc, atm, colNum)+
            this->CalculateERF(atc, atm, colNum)+this->CalculateEBUFF(atc, atm);
    this->energy = comparisonEnergy;
    return comparisonEnergy;
}

double Comparator::CalculateResetEnergy(ATCTrack* atc, ATMTrack* atm){      
}

double Comparator::CalculateEAT(ATCTrack* atc, ATMTrack* atm, int colNum){
if(colNum%2 == 1){
    return (pow(this->VMH, 2)/this->R0)*(atc->T_ref-(max(atc->risingPulseTime, atm->risingPulseTime)))+(pow(this->VML, 2)/this->R0)*(max(atc->risingPulseTime, atm->risingPulseTime));
}
else{
    return (pow(this->VMH, 2)/this->R0)*(atc->T_ref-(min(atc->risingPulseTime, atm->risingPulseTime)))+(pow(this->VML, 2)/this->R0)*(min(atc->risingPulseTime, atm->risingPulseTime));

}
}

double Comparator::CalculateEMTJ(ATCTrack* atc, ATMTrack* atm, int colNum){
if(colNum%2 == 1){
    return (pow(this->VMH, 2)/this->RH)*(atc->T_ref-(max(atc->risingPulseTime, atm->risingPulseTime)))+(pow(VML, 2)/this->RL)*(max(atc->risingPulseTime, atm->risingPulseTime));
}
else{
    return (pow(this->VMH, 2)/this->RH)*(atc->T_ref-(min(atc->risingPulseTime, atm->risingPulseTime)))+(pow(VML, 2)/this->RL)*(min(atc->risingPulseTime, atm->risingPulseTime));
}
}


double Comparator::CalculateERF(ATCTrack* atc, ATMTrack* atm, int colNum){
if(colNum%2 == 1){
    return (pow(this->Vb-this->VMH, 2)/this->Rf)*(atc->T_ref-(max(atc->risingPulseTime, atm->risingPulseTime)))+(pow(this->Vb-this->VML, 2)/this->Rf)*(max(atc->risingPulseTime, atm->risingPulseTime));
}
else{
    return (pow(this->Vb-this->VMH, 2)/this->Rf)*(atc->T_ref-(min(atc->risingPulseTime, atm->risingPulseTime)))+(pow(this->Vb-this->VML, 2)/this->Rf)*(max(atc->risingPulseTime, atm->risingPulseTime));
}
}

double Comparator::CalculateEBUFF(ATCTrack* atc, ATMTrack* atm){
    return this->CBUFF*pow(this->VDD, 2);
}

double Comparator::CalculateArea(int colNum){
    double WR0 = this->RS*this->featureSize/15000;
    double AR0 = (WR0+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP);
    double CMOS_AREA = (4*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP)+(8*this->featureSize+this->CMOS_GAP)*(this->featureSize+CMOS_GAP);
    double BUFFER1_AREA = CMOS_AREA + AR0;
    this->buffer_area = BUFFER1_AREA;
    double CMOS1_AREA = (4*(4*this->featureSize + this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP))+2*((10*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP));
    double RTM_AREA = (this->input->WCPM + this->RTM_GAP)*(this->input->LCPM+this->RTM_GAP);
    //cout << "RTM AREA : " << RTM_AREA << endl;
    this->area = max(RTM_AREA, CMOS1_AREA+BUFFER1_AREA);
    double INV_AREA = (2*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP)+(4*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP);
    if(colNum%2 == 0){
        double NAND_AREA = 2*(4*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP)+2*((4*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP));
        this->NAND_AREA = NAND_AREA;
        this->area += NAND_AREA + INV_AREA;
        return this->area;
    }
    else{
        double NOR_AREA = 2*(4*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP)+2*(8*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP);
        this->NOR_AREA = NOR_AREA;
        this->area += NOR_AREA + INV_AREA;
        return this->area;
    }
}

void Comparator::PrintProperty(const char *str){
    cout << "---------" << endl;
    cout << str << endl;
    //cout << "Area: " << this->CalculateArea() << endl;
    cout << "Comparison Energy: " << this->comparisonEnergy << endl;
    cout << "Output: " << this->VCPM <<endl;
}

