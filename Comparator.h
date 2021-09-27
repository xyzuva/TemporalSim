#ifndef COMPARATOR_H_
#define COMPARATOR_H_
#include "Cell.h"
#include "Array.h"
#include "Inputs.h"
#include "Peripherals/VoltageToCurrentConverter.h"
class Comparator{
    public:
    Inputs *input;
    void Initialize();
    int Output(ATCTrack **atc, ATMTrackArray *arr, int colNum, int numRows, VoltageToCurrentConverter *V2I);
    double CalculateComparisonEnergy(ATCTrack* atc, ATMTrack* atm, int colNum);
    double CalculateResetEnergy(ATCTrack* atc, ATMTrack* atm);
    double CalculateEMTJ(ATCTrack* atc, ATMTrack* atm, int colNum);
    double CalculateEAT(ATCTrack* atc, ATMTrack* atm, int colNum);
    double CalculateERF(ATCTrack* atc, ATMTrack* atm, int colNum);
    double CalculateEBUFF(ATCTrack* atc, ATMTrack* atm);
    double CalculateArea(int colNum);
    void PrintProperty(const char *str);
    double RHM, RN, RH, RL, R0, Rf, VDD, VMH, VML, Vb, CBUFF, featureSize, CMOS_GAP, WRTM, RTM_GAP, RS, comparisonEnergy, NAND_AREA, NOR_AREA;
    int VCPM;
    double area, energy;
    double buffer_area;

};
double pow(double i, int j);
#endif