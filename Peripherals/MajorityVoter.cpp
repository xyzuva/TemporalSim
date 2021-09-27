#include "MajorityVoter.h"
//#include "Cell.h"
#include <iostream>
using namespace std;
void MajorityVoter::Initialize(int numTrees){
    this->input = new Inputs();
    this->numTrees = numTrees;
    this->Wcurrent_minor = this->input->W_current_mirror;
    this->Lcurrent_minor = this->input->L_current_mirror;
    this->Wpass = this->input->Wpass;
    this->Lpass = this->input->Lpass;
    this->CL = this->input->CL;
    this->Alpha = numTrees;
    this->I_base = this->input->I_base;
    this->Wswitch = this->input->W_switch;
    this->Lswitch = this->input->L_switch;
    this->VDD = this->input->VDD;
}

void MajorityVoter::CalculateArea(){
    double Area_current_minor = 10*this->numTrees*((this->Wcurrent_minor*this->Lcurrent_minor)+(this->Wswitch*this->Lswitch));
    double Area_pass_transistor = 10*this->numTrees*(this->Wpass*this->Lpass);
    this->Area = Area_current_minor + Area_pass_transistor; 
}

void MajorityVoter::CalculateEnergy(){
    double energyPassTransistor = this->Alpha*this->CL*this->VDD*this->VDD;
    double energyCurrentMinor = this->Alpha*this->I_base*this->VDD*this->input->T_ref;
    this->Energy = energyPassTransistor + energyCurrentMinor;
}
