#include "Array.h"
#include "Cell.h"
#include <iostream>
using namespace std;
int main(){
    ATMTrackArray *arr = new ATMTrackArray();
    arr->Initialize(1024, 1024, 15, 0);
    double area = 1024*1024*arr->cell[0][0]->CalculateArea();
    cout << area << endl;
}