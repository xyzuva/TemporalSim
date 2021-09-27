#include "Peripherals/VoltageToCurrentConverter.h"
#include "Peripherals/RowDecoder.h"
#include "Peripherals/MajorityVoter.h"
#include <iostream>
using namespace std;
int main(){
    VoltageToCurrentConverter V2I = new VoltageToCurrentConverter();
    V2I->Initialize();
}