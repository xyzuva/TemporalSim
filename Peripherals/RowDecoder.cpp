#include "RowDecoder.h"
#include <iostream>
#include <math.h>
using namespace std;
void RowDecoder::Initialize(){
    this->input = new Inputs();
    this->gamma = this->input->gamma;
    this->VDD = this->input->VDD;
    this->beta_nmos = this->input->BETA_NMOS;
    this->Vth = this->input->Vth;
    this->T_ref = this->input->T_ref;
    this->featureSize = this->input->featureSize;
    this->CMOS_GAP = this->input->CMOS_GAP;
}

void RowDecoder::CalculateArea(int numRows){
    double INV_AREA = numRows*((2*this->featureSize+this->CMOS_GAP)*(featureSize+this->CMOS_GAP))+(4*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP);
    double NAND_AREA = (4*floor(numRows/2))*(2*(4*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP)+2*(4*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP));
    double NOR_AREA = 0.25*numRows*((2*(2*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP))+2*(8*this->featureSize+CMOS_GAP)*(this->featureSize+this->CMOS_GAP));

    this->area = INV_AREA+NAND_AREA+NOR_AREA;
    
}

double RowDecoder::CalculateEnergy(int numRows, int numCols){
    double C_column = 4*((this->input->lambda_row)*(this->input->lambda_row)*0.36*0.057+(2*(7*this->input->lambda_row*0.6)*0.043))*10e-15;
    this->energy = numRows*numCols*C_column*this->input->VDD*this->input->VDD;
    return this->energy;

// void RowDecoder::PrintProperty(const char *str){
//     cout << str <<endl;
//     cout << "Area : " << this->area << endl;
//     cout << "Energy : " << this->energy << endl;

}