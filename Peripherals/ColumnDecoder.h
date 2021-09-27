#ifndef COLUMNDECODER_H_
#define COLUMNDECODER_H_
#include "../Inputs.h"
class ColumnDecoder{
    public:
    Inputs *input;
    double gamma, VDD, beta_nmos, Vth, T_ref,featureSize, CMOS_GAP;
    double area, latency, energy;
    int numRows, numCols;
    void Initialize(int numRows, int numCols);
	double CalculateArea();
	double CalculateEnergy();
    void PrintProperty(const char *str);
};
#endif