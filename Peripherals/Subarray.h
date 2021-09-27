#ifndef SUBARRAY_H_
#define SUBARRAY_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "forumla.h"
#include "RowDecoder.h"
#include "Mux.h"
#include "MajorityVoter.h"
#include "VoltageToCurrentConverter.h"
#include "FunctionUnit.h"
#include "ReadUnit.h"
class SubArray: public FunctionUnit {
public:
	SubArray(InputParameter& _inputParameter, Technology& _tech, MemCell& _cell);
	virtual ~SubArray() {}
	InputParameter& inputParameter;
	Technology& tech;
	MemCell& cell;

	/* Functions */
	void PrintProperty();
	void Initialize(int _numRow, int _numCol, double _unitWireRes);
	void CalculateArea();
	void CalculateLatency();
	void CalculatePower();

	/* Properties */
	bool initialized;	// Initialization flag
	int numRow;			// Number of rows
	int numCol;			// Number of columns
	int numColMuxed;	// How many columns share 1 read circuit (for neuro mode with analog RRAM) or 1 S/A (for memory mode or neuro mode with digital RRAM)
	int numWriteColMuxed;	// // How many columns share 1 write column decoder driver (for memory or neuro mode with digital RRAM)
	double heightArray;
	double widthArray;
	double areaArray;
	double readDynamicEnergyArray, writeDynamicEnergyArray;

	double lengthRow;	// Length of rows, Unit: m
	double lengthCol;	// Length of columns, Unit: m
	double unitWireRes;	// Unit wire resistance, Unit ohm/m
	double capRow1;		// Capacitance of row1 (BL for 1T1R, WL for Cross-point), Unit: F
	double capRow2;		// Capacitance of row2 (WL for 1T1R), Unit: F
	double capCol;		// Capacitance of column, Unit: F
	double resRow;		// Row resistance, Unit: ohm
	double resCol;		// Column resistance, Unit: ohm
	double resCellAccess;	// Resistance of access device, Unit: ohm
	double capCellAccess;	// Capacitance of access device, Unit: ohm
	double colDelay;	// Column delay, Unit: s
    double widthAccessTransistor; // for the 3T1C cell only

	double activityRowWrite;	// Activity for # of rows in the write
	double activityColWrite;	// Activity for # of columns in the write
	double activityRowRead;		// Activity for # of rows in the read
	int numReadPulse;		// # of read pulses for the input vector
	double numWritePulse;	// Average number of write pulse
	int maxNumWritePulse;	// Max # of write pulses for the device
	int maxNumIntBit;		// Max # bits for the integrate-and-fire neuron
	bool digitalModeNeuro;	// Digital RRAM in neuro mode
	ReadCircuitMode readCircuitMode;
	int numWriteCellPerOperationNeuro;  // For multifunctional mode or neuro only mode
	double clkFreq;			// Clock frequency (Hz)


	/* Circuit modules */
	RowDecoder  wlDecoder;
	Mux mux;
	RowDecoder  colDecoder;
    DecoderDriver wlDecoderDriver;
    DecoderDriver colDecoderDriver;
	VoltageToCurrentConverter VtoI;
};