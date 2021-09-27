#ifndef VOLTAGETOCURRENTCONVERTER_H_
#define VOLTAGETOCURRENTCONVERTER_H_
#include "../Inputs.h"

class VoltageToCurrentConverter{
	public:
	Inputs *input;
	double gamma, VDD, featureSize, beta_nmos, Vth, T_ref, CMOS_GAP;
    void Initialize();
	void CalculateArea(int numRows);
	void CalculateEnergy(double Vin, double I_in);
};
#endif