#ifndef ARRAY_H_
#define ARRAY_H_
#include "Cell.h"

class ATMTrackArray {
    public:
    int collums, rows;
    double maxWeight, minWeight, readEnergy, writeEnergy, recoverEnergy, eraseEnergy;
    ATMTrack ***cell;
    void Initialize(int collums, int rows,double maxWeight, double minWeight);
    double ReadCell(int collum, int row);
    void WriteCell(int collum, int row, double current);
    double RecoverCell(int collum, int row);
    void EraseCell(int collum, int row);
    void LoadArrayValues();
    void PrintProperty(const char *str);
    void PrintDutyCycles();
};

class ATCTrackArray {
    public:
    int collums, rows;
    double maxWeight, minWeight;
    ATCTrack ***cell;
    void Initialize(int collums, int rows);
    double ReadCell(int collum, int row);
    void WriteCell(int collum, int row, double current);
    void EraseCell(int collum, int row);
    void LoadArrayValues();
    void PrintProperty(const char *str);
};

#endif