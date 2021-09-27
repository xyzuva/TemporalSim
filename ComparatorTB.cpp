#include "Array.h"
#include "Comparator.h"
#include <iostream>
using namespace std;
int main(){
    ATMTrackArray *ATMArray = new ATMTrackArray();
    ATMArray->Initialize(4, 4, 0, 15);
    double weight = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            ATMArray->WriteCell(i, j, 11);
            weight++;
        }
    }

    ATCTrack *atc = new ATCTrack();
    atc->Initialize(1, 2);
    atc->Write(55e-6);
    Comparator *cpm = new Comparator();
    cpm->Output(atc, ATMArray->cell[1], 4);
    cout << cpm->VCPM << endl;
}