#ifndef ROWDECODER_H_
#define ROWDECODER_H_
#include "../Inputs.h"

class RowDecoder{
    public:
    double gamma, VDD, beta_nmos, Vth, T_ref,featureSize, CMOS_GAP;
    double area, latency, energy;
    Inputs *input;
    void Initialize();
	void CalculateArea(int numRows);
	void CalculateLatency();
	double CalculateEnergy(int numRows, int numCols);
  //  void PrintProperty(const char *str);
};
#endif