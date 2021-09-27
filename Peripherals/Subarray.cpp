#include <math>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "SubArray.h"

using namespace std;

SubArray::SubArray(InputParameter& _inputParameter, Tehcnology& _techm Memcell& _cell):
    inputParamneter(_inputParameter), tech(_tech), cell(_cell),
    colDecoder(_inputParameter, _tech, _cell),
    mux(_inputParameter, _tech, _cell),
    wlDecoderDriver(_inputParameter, _tech, _cell)
    colDecoderDriver(_inputParameter, _tech, _cell){
        readDynamicEnergy = writeDynamicEnergy = 0;
    }
void SubArray::Initialize(int _numRow, int _numCol, double _unitWireRes){
    numRow = _numRow;
    numCol = _numCol;
    unitWireRes = _unitWireRes;
    double MIN_CELL_HEIGHT = MAX_TRANSISTOR_HEIGHT; //ADJUST LATER FOR TEMPORALSIM
    double MIN_CELL_WIDTH = (MIN_GAP_BET_GATE_POLY + POLY_WIDTH) * 2; //ADJUST LATER FOR TEMPORALSIM
    double cellHeight = cell.trackWidth; //ADJUST LATER FOR TEMPORALSIM
    double cellWidth = cell.trackLength; //ADJUST LATER FOR TEMPORALSIM
    lengthRow = double(numRow) * MAX(cellWidth, MIN_CELL_WIDTH*2) * tech.featureSize; //ADJUST LATER FOR TEMPORALSIM
    lengthCol = double(numCol) * MAX(cellHeight,MIN_CELL_HEIGHT) * tech.featureSize;

    capRow1 = lengthRow * 0.2e-15/1e-6; //ADJUST LATER FOR TEMPORALSIM
    capRow2 = lengthRow * 0.2e-15/1e-6; //ADJUST LATER FOR TEMPORALSIM
    capCol = lengthCol * 0.2e-15/1e-6; //ADJUST LATER FOR TEMPORALSIM
    resRow = lengthRow * unitWireRes; //ADJUST LATER FOR TEMPORALSIM
    resCol = lengthCol * unitWireRes; //ADJUST LATER FOR TEMPORALSIM

    int numInput = 2; //ADJUST FOR TEMPORALSIM, MUX INPUTS
    double resTg = 4; //ADJUST FOR TEMPORALSIM, resCellAccess + ressitanceOn
    mux.Initialize(numInput, (int)ceil(log2(numInput)), true);
    wlDecoder.Initialize(REGULAR_ROW, (int)ceil(log2(numRow)), false);
    colDecoder.Initialize(REGULAR_COL, (int)ceil(log2(numCol)), false);
    colDecoderDriver.Initialize(REGULAR_COL, (int)ceil(log2(numWriteColMuxed)), false);
    V2I.Initialize();

    /**
    INITIALIZE THE COMPAARATOR, READ UNIT, MAJORITY VOTER, AND VOLTAGE TO CURRENT CONVERTER HERE
    */

}

void subArray::CalculateArea(){
    heightArray = lengthCol;
    widthArray = lengthRow;
    areaArray = heightArray * widthArray;

    wlDecoder.CalculateArea(heightArray, NULL, NONE);
    mux.CalculateArea(NULL, widthArray, NONE);
    colDecoder.CalculateArea(widthArray, NULL, none);
    V2I.CalculateArea(numRow);
    
    height = colDecoder.height + colDecoderDriver.height + heightArray + mux.Height + wlDecoder.height;
    width = wlDecoder.width + mux.width + widthArray + colDecoder.width;

    area = height * width;

    usedArea = areaArray + wlDecoder.area + colDecoder.area + colDecoderDriver.area + mux.area;
    emptyArea = area - usedArea;
}
void SubArray::CalculateLatency(){
    //Calculation parameters based on the 1T1R array
    int numReadOperationPerRow = (int)ceil((double)numCol); //PLACEHOLDER
    int numWriteOperationPerRow = (int)ceil((double)(numCol*activityColWrite)); //PLACEHOLDER
    wlDecoder.CalculateLatency(1e20, capRow2, NULL, numRow*activityRowRead*numReadPulse*numColMuxed, numRow*activityRowWrite);
    double colDecoderLoad = (colDecoderDriver.capInvInput + colDecoderDriver.capTgGateN*2 + colDecoderDriver.capTgGateP)*numWriteCellPerOperationNeuro;
    colDecoder.CalculateLatency(1e20, colDecoderLoad, NULL, 1, numRow*activityRowWrite*numWriteColMuxed);
    colDelay = horowitz(tau, 0, 1e20, &colRamp);
    colDelay = tau*0.2*numColMuxed*numReadPulse;
    mux.CalculateLatency(colRamp, 0, 1);
    readLatency += wlDecoder.readLatency;
    readLatency += colDecoder.readLatency;
    readLatency += mux.readLatency;

    writeLatency += wlDecoder.writeLatency;
    writeLatency += colDecoder.writeLatency;
    writeLatency += mux.writeLatency;


}

void SubArray::CalculatePower(){
    double numReadCells = (int)ceil((double)numCol/numColMuxed);
    int numWriteCells = (int)ceil((double)numCol/numWriteColMuxed);
    wlDecoder.CalculatePower(numCol, numRow*activityRowWrite);
    colDecoder.CalculatePower(numCol, numRow*activityRowWrite*numWriteColMuxed);
    colDecoderDriver.CaclulatePower(numReadCells, numWriteCells, 1, numRow*activityRowWrite*numWriteColMuxed*2);
    mux.CalculatePower(numRow*activityRowRead*numColMuxed*numReadPulse);
    double capBL = lengthCol * 0.2e-15/1e-6; //PLACEHOLDER

    readDynamicEnergy += wlDecoder.readDynamicEnergy;
    readDynamicEnergy += mux.readDynamicEnergy;
    readDynamicEnergy += colDecoder.readDynamicEnergy;

    writeDynamicEnergy += wlDecoder.writeDynamicEnergy;
    writeDynamicEnergy += colDecoder.writeDynamicEnergy;
    writeDynamicEnergy += mux.writeDynamicEnergy;

    leakage += wlDecoder.leakage;
    leakage += colDecoder.leakage;
    leakage += rowDecoder.leakage;

    readPower = readDynamicEnergy/readLatency + leakage;
    writePower = writeDynamicEnergy/writeLatency + leakage;
    recoverPower = readPower;
    erasePower = readPower;
}
