#ifndef COMPARATOR_H_
#define COMPARATOR_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"

class Comparator: public FunctionUnit{
    void Initialize(int _numInput, int _numSelection, double _resTg, bool _digital);
	void CalculateArea(double _newHeight, double _newWidth, AreaModify _option);
	void CalculateLatency(double _rampInput, double _capLoad, double numRead);
	void CalculatePower(double numRead);
}
#endif