#include <fstream>
#include <iostream>
using namespace std;
#include "Cell.h"

int main() {
    ATMTrack *testCell = new ATMTrack();
    testCell->Initialize(0, 0);
    ifstream in;
    ofstream results;
    in.open("values.txt");
    results.open("results.txt");
    double nextInput;
    while(in >> nextInput){
        testCell->Write(nextInput);
        testCell->Read();
        testCell->Recover();
        results << testCell->Read() << endl;
        testCell->Erase();
    }
    in.close();
    results.close();
}