using namespace std;
#include <iostream>

double MapDutyCycle(int numStates, double I, double I_min, double I_max);
int main(){
    for(int i = 10; i <= 105; i++){
        double current = i*1e-6;
        double dutyCycle = MapDutyCycle(16, current, 10e-6, 105e-6);
        cout << current << " - " << dutyCycle << endl;
    }
}
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