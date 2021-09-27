#include <iostream>
using namespace std;
double WeightToCurrent(double weight, double minWeight, double maxWeight, double Imax_ref, double Imin_ref){
    double current = (weight-minWeight)/(maxWeight-minWeight)*(Imax_ref - Imin_ref)+Imin_ref;
    return current;
}
double MapDutyCycle(int numStates, double I, double I_min, double I_max){
    double treshold = 0;
    double dutyCycle = 0;
    for(int i = 1; i <= numStates; i++){
        treshold = ((I_max-I_min)/(numStates))*i+I_min;
        if(I <= treshold){   
            dutyCycle = (100/(numStates))*i;
            break;
        }
    }
    return dutyCycle;
}

int main(){
    for(int i = 0; i < 16; i++){
        cout << MapDutyCycle(16, WeightToCurrent(i, 0, 15, 10, 100), 10, 100) << endl;
    }
}
