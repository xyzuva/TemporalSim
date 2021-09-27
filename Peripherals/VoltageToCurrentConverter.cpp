#include "VoltageToCurrentConverter.h"
#include <iostream>
#include <math.h>
using namespace std;
void VoltageToCurrentConverter::Initialize(){
    this->input = new Inputs();
    this->gamma = this->input->gamma;
    this->VDD = this->input->VDD;
    this->beta_nmos = this->input->BETA_NMOS;
    this->Vth = this->input->Vth;
    this->T_ref = this->input->T_ref;
    this->featureSize = this->input->featureSize;
    this->CMOS_GAP = this->input->CMOS_GAP;
    this->energy = 0;
}

void VoltageToCurrentConverter::CalculateArea(int numCols){
    this->area = numCols*(2*((this->gamma*7.5*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP))+2*((this->gamma*15*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP))+(17*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP));
    
}

double VoltageToCurrentConverter::CalculateEnergy(double Vin, double I_in){
    double energy = this->gamma*0.5*this->VDD*(2*this->beta_nmos*(Vin-this->Vth)*(Vin-this->Vth)*this->T_ref)+this->VDD*I_in*this->T_ref;
    //cout << energy << endl;
    return energy;
}

// void PrintProperty(const char *str){
//     cout << str <<endl;
//     cout << "Area : " << this->area << endl;
//     cout << "Energy : " << this->energy << endl;

// }