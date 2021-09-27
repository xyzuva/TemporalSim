#include "Parser.h"
#include "Inputs.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void loadArray(ATMTrackArray *arr, ATCTrack **inputs, const char *filename, double minWeight, double maxWeight, int numCols, int numRows, double I_max, double I_min, VoltageToCurrentConverter *V2I){
    double **weights = new double*[numCols];
    for(int i = 0; i < numCols; i++){
        weights[i] = new double[numRows];
    }
    for(int i = 0; i < numCols; i++){
        for(int j = 0; j < numRows; j++){
            weights[i][j] = 0.0;
        }
    }
    ifstream file(filename);
    Inputs *param = new Inputs();
    for(int row = 0; row < numRows; row++){
       // cout << "bleh";
        string line;
        getline(file, line);
        stringstream iss(line);
        for(int column = 0; column < numCols; column++){
            string val;
            getline(iss, val, ',');
            stringstream convertor(val);
            convertor >> weights[column][row];
        }
    }

    //double currents[numCols][numRows];
    double weightToCurrent;
    for(int i = 0; i < numCols; i++){
        for(int j = 0; j < numRows; j++){
            if(i == 0){
                
                weightToCurrent = ((weights[i][j]-minWeight)/(maxWeight-minWeight))*(I_max-I_min)+I_min;
                V2I->energy += V2I->CalculateEnergy(param->VDD, weightToCurrent)*(numCols-1);
                inputs[j]->Write(weightToCurrent);

            }
            else{
            weightToCurrent = ((weights[i][j]-minWeight)/(maxWeight-minWeight))*(I_max-I_min)+I_min;
            V2I->energy += V2I->CalculateEnergy(param->VDD, weightToCurrent);
            arr->WriteCell(i-1, j, weightToCurrent);
            arr->writeEnergy += arr->cell[i-1][j]->CalculateWriteEnergy();
            }
        }
    }
}