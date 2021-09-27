#ifndef VOLTAGETOCURRENTCONVERTOR_H_
#define VOLTAGETOCURRENTCONVERTOR_H_

#include "../Inputs.h"

class VoltageToCurrentConverter{
    public:
    Inputs* input;
    double gamma, VDD, beta_nmos, Vth, T_ref,featureSize, CMOS_GAP;
    double area, latency, energy;
    void Initialize();
	void CalculateArea(int numCols);
	double CalculateEnergy(double Vin, double I_in);
    void PrintProperty(const char *str);
};
#endif