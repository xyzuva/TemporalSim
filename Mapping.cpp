#include "Mapping.h"
using namespace std;
double MapDutyCycle(int numStates, double I, double I_min, double I_max){
    double treshold = 0;
    double dutyCycle = 0;
    for(int i = 1; i <= numStates; i++){
        treshold = ((I_max-I_min)/numStates)*i+I_min;
        if(I <= treshold){   
            dutyCycle = (100/numStates)*i;
            break;
        }
    }
    return dutyCycle;
}
