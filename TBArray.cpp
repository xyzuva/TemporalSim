#include "Array.h"
#include "Parser.h"
#include "Comparator.h"
#include <iostream>
using namespace std;
int main(){
    ATMTrackArray *ATMArray = new ATMTrackArray();
    ATMArray->Initialize(4, 4, 0, 15);
    loadArray(ATMArray, "4by4.csv", ATMArray->minWeight, ATMArray->maxWeight, ATMArray->collums, ATMArray->rows, ATMArray->cell[0][0]->Imin_ref, ATMArray->cell[0][0]->Imax_ref);
    //ATMArray->PrintDutyCycles();
    ATCTrackArray *ATCArray = new ATCTrackArray();
    ATCArray->Initialize(1, 4);
    ATCArray->WriteCell(0, 0, 34e-6);
    ATCArray->WriteCell(0, 1, 40e-6);
    ATCArray->WriteCell(0, 2, 88e-6);
    ATCArray->WriteCell(0, 3, 22e-6);
    cout << "----------" << endl;
    for(int i = 0; i < 4; i++){
        cout << ATCArray->cell[0][i]->dutyCycle << endl;

    }
    cout << "-----------" << endl;
    Comparator** cpm = new Comparator*[ATMArray->collums];
    ATMArray->PrintDutyCycles();
    for(int i = 0; i < ATMArray->collums; i++){
        cpm[i] = new Comparator();
        cpm[i]->Initialize();
        cpm[i]->Output(ATCArray, ATMArray, i, ATMArray->rows);
        cpm[i]->PrintProperty("Comparator ");
    }
    int* VCPMFinal = new int[ATMArray->collums/2];
    
    for(int i = 0; i < 4; i+=2){
       VCPMFinal[i] = cpm[i]->VCPM & cpm[i+1]->VCPM;
       cout << VCPMFinal[i] << endl;
    }
    
    //atc->PrintProperty("atc");
}