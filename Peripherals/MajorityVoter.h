#ifndef MAJORITYVOTER_H_
#define MAJORITYVOTER_H_
#include "../Inputs.h"

class MajorityVoter{
	public:
	Inputs *input;
	void Initialize(int numTrees);
	void CalculateArea();
	void CalculateEnergy();
	int numTrees, Alpha;
	double Wcurrent_minor, Lcurrent_minor, Wpass, Lpass, CL, I_base, Wswitch, Lswitch, VDD;
	double Energy, Area;

};
#endif