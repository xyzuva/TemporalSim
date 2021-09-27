#ifndef PARSER_H_
#define PARSER_H_
#include "Array.h"
#include "Cell.h"
#include "Peripherals/VoltageToCurrentConverter.h"
#include "Inputs.h"

void loadArray(ATMTrackArray *arr, ATCTrack **inputs, const char *filename, double minWeight, double maxWeight, int numCols, int numRows, double I_max, double I_min, VoltageToCurrentConverter *V2I);
#endif