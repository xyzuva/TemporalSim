#include "Mux.h"
#include "RowDecoder.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include <iostream>
using namespace std;

void testMux(Mux mux);
void testRowDecoder(RowDecoder rowDecoder);
void testColDecoder(RowDecoder colDecoder);
//FILES TO COMPILE: TB.cpp, Mux.cpp, RowDecoder.cpp, Technology.cpp, formula.cpp functionunit.cpp param.cpp

int main(){
    
    /**
    Input parameter for devices to choose process node, device road map, and also the temperature
    */
    InputParameter inputParam;
    inputParam.processNode = 130; //In nm
    inputParam.deviceRoadmap = LSTP; //LSTP or HP 
    inputParam.temperature = 300; //Temp in Kelvin

    /**
    Technology type intitialization for the peripheral circuits
    */
    Technology tech;
    tech.Initialize(inputParam.processNode, inputParam.deviceRoadmap);

    /**
    Memcell here for placeholder, does not affect calculations
    */
    MemCell memCell;

    Mux mux(inputParam, tech, memCell);
    RowDecoder rowDecoder(inputParam, tech, memCell);
    RowDecoder colDecoder(inputParam, tech, memCell);
    testMux(mux);
    testRowDecoder(rowDecoder);
    testColDecoder(colDecoder);

    return 0;
}

void testMux(Mux mux){
    mux.Initialize(2, 1, 1, true); //PARAMETERS: number of inputs, number of selects, restg, digital (bool)
    mux.CalculateArea(3, 3, NONE); //PARAMETERS: height, width, area modify option 
    mux.CalculateLatency(1, 1, 2); //PARAMETERS: rampInput (doesn't matter in a mux), capacitance load, number of reads
    mux.CalculatePower(2); //PRAMETERS: number of reads
    mux.PrintProperty("Mux");
}

void testRowDecoder(RowDecoder rowDecoder){
    rowDecoder.Initialize(REGULAR_ROW, 4, false); //PARAMETERS: row/col mode, number of addresses, mux
    rowDecoder.CalculateArea(NULL, 1, NONE); //PARAMETERS: height, width, area modify
    rowDecoder.CalculateLatency(1, 1, 1, 4, 1); //PARAMETERS: rampinput, load capacitance, numreads, numwrites
    rowDecoder.CalculatePower(4, 1); //PARAMETERS: numRead, numWrite
    rowDecoder.PrintProperty("Row Decoder");
}

void testColDecoder(RowDecoder colDecoder){
    colDecoder.Initialize(REGULAR_COL, 4, false); //PRAMETERS: row/col mode, number of addresses, mux
    colDecoder.CalculateArea(1, NULL, NONE); //PARAMETERS: height, width, area modify
    colDecoder.CalculateLatency(1, 1, 1, 4, 1); //PRAMETERS: rampinput, load capacitance, numREads, numWrites
    colDecoder.CalculatePower(4, 1); //PARAMETERS: numRead, numWrite
    colDecoder.PrintProperty("Col Decoder");

}