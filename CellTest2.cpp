#include "Cell.h"
using namespace std;
#include <iostream>
int main(){
    ATMTrack *testCell = new ATMTrack();
    testCell->Initialize(3, 6);
    int i;
    double in;
    while(true){
        double output;
        cout << "(1) Read, (2) Write, (3) Recover, (4) Erase" << endl;
        cin >> i;
        switch(i){
            case 1 :
                output = testCell->Read();
                testCell->PrintProperty("ATM Cell");
                break;
            case 2 : 
                cout << "Enter input current" << endl;
                cin >> in;
                testCell->Write(in);
                testCell->PrintProperty("ATM Cell");
                break;
            case 3 :
                testCell->Recover();
                testCell->PrintProperty("ATM Cell");
                break;
            case 4 :  
                testCell->Erase(); 
                testCell->PrintProperty("ATM Cell");
        }
    }
}