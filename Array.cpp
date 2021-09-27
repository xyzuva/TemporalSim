#include "Array.h"
using namespace std;
#include <iostream>
#include <fstream>
void ATMTrackArray::Initialize(int collums, int rows, double maxWeight, double minWeight){
    this->collums = collums;
    this->writeEnergy = 0;
    this->rows = rows;
    this->cell = new ATMTrack**[collums];
    this->maxWeight = maxWeight;
    this->minWeight = minWeight;
    for(int i = 0; i < collums; i++){
        this->cell[i] = new ATMTrack*[rows];
        for(int j = 0; j < rows; j++){
            this->cell[i][j] = new ATMTrack();
            this->cell[i][j]->Initialize(i, j);
        }
    }
}

double ATMTrackArray::ReadCell(int collum, int row){
    return this->cell[collum][row]->Read();
}

void ATMTrackArray::WriteCell(int collum, int row, double current){
    this->cell[collum][row]->Write(current);
}

double ATMTrackArray::RecoverCell(int collum, int row){
    return this->cell[collum][row]->Recover();
}

void ATMTrackArray::EraseCell(int collum, int row){
   this->cell[collum][row]->Erase();
}

void ATMTrackArray::PrintProperty(const char *str){
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->collums; j++){

            this->cell[j][i]->PrintProperty("Cell" );
            cout << "Position: [" << this->cell[j][i]->x << "]" << "[" << this->cell[j][i]->y << "]" << endl;
        }
    } 
}

void ATMTrackArray::PrintDutyCycles(){
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->collums; j++){
            cout << this->cell[j][i]->dutyCycle << ",";
        }
        cout << endl;
    } 
}
void ATCTrackArray::Initialize(int collums, int rows){
    this->collums = collums;
    this->rows = rows;
    this->cell = new ATCTrack**[collums];
    for(int i = 0; i < collums; i++){
        this->cell[i] = new ATCTrack*[rows];
        for(int j = 0; j < rows; j++){
            this->cell[i][j] = new ATCTrack();
            this->cell[i][j]->Initialize(i, j);
        }
    }
}



double ATCTrackArray::ReadCell(int collum, int row){
    return this->cell[collum][row]->Read();
}

void ATCTrackArray::WriteCell(int collum, int row, double current){
    //double current = (weight-minWeight)/(maxWeight-minWeight)*(this->cell[collum][row]->Imax_ref-this->cell[collum][row]->Imin_ref)+cell[collum][row]->Imin_ref;
    this->cell[collum][row]->Write(current);
}

void ATCTrackArray::EraseCell(int collum, int row){
    this->cell[collum][row]->Erase();
}

