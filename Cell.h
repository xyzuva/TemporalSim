#ifndef CELL_H_
#define CELL_H_
#include "Inputs.h"
class Cell{
    public:
        double CalculateEMTJ();
        double CalculateEAT();
        double CalculateERF();
        double CalculateEBUFF();
        double CalculateWriteEnergy();
        double CalculateEraseEnergy();
        double RHM, RN, RH, RL, R0, Rf, Vb, VDD, CBUFF, VMH, VML, dutyCycle, Imax_ref, Imin_ref, T_ref;
        double risingPulseTime, featureSize, WRTM, LRTM, CMOS_GAP, RTM_GAP;
        double readEnergy, writeEnergy;
        Inputs *input;
};
class ATMTrack: public Cell{
    public:
        //Variables needed of initialization of cell
        int x, y; //Position of cell in the array
        int numStates; 
        double trackLength;
        double trackWidth;

        //Variables for the recovery track
        double recoveryPosition; 
        double recoveryDutyCycle;
        double recoveryRisingPulseTime;
        
        //Variables for the main track
        double position;
        void PrintProperty(const char* str);
        double CalculateReadEnergy();

        //Cell functions
        void Initialize(int x, int y);
        double Read();
        double Recover();
        void Write(double I);
        void Erase();
        double CalculateArea();
        double CalculateRecoveryEnergy();
};

class ATCTrack: public Cell{
    public:
        //Initialization variables
        int x, y;
        int numStates;
        double trackLength;
        double trackWidth;

        //Track variables
        double position;
        void PrintProperty(const char* str);

        //Cell functions
        void Initialize(int x, int y);
        double Read();
        void Write(double I);
        void Erase();
        double CalculateArea();
        double CalculateReadEnergy();
};

double pow(double i, int j);
#endif
