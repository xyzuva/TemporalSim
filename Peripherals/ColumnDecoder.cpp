#include "ColumnDecoder.h"
#include <iostream>
using namespace std;

void ColumnDecoder::Initialize(int numRows, int numCols){
    this->input = new Inputs();
    this->numRows = numRows;
    this->numCols = numCols;
    this->featureSize = this->input->featureSize;
    this->CMOS_GAP = this->input->CMOS_GAP;

}

double ColumnDecoder::CalculateArea(){
    this->area = this->numCols*2*((2*this->featureSize+this->CMOS_GAP)*(featureSize+this->CMOS_GAP))+(4*this->featureSize+this->CMOS_GAP)*(this->featureSize+this->CMOS_GAP);
    return this->area;
}

double ColumnDecoder::CalculateEnergy(){
    double C_column = (((4*this->input->lambda_col)*(this->input->lambda_col)*0.36*0.057+(2*(7*this->input->lambda_col*0.6)*0.043)))*10e-15;
    double energy = C_column*this->numCols*this->numRows*this->numRows*this->input->VDD*this->input->VDD;
    this->energy = energy;
    return this->energy;
}