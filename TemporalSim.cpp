#include "Array.h"
#include "Parser.h"
#include "Comparator.h"
#include "Cell.h"
#include "Peripherals/RowDecoder.h"
#include "Peripherals/ColumnDecoder.h"
#include "Peripherals/MajorityVoter.h"
#include "Peripherals/VoltageToCurrentConverter.h"
#include "Inputs.h"
#include <iostream>
using namespace std;
int INPUT_ROWS  = 256;
int INPUT_COLUMNS  = 131073;
#define MIN_WEIGHT 0
#define MAX_WEIGHT 15
double I_MAX = 100e-6;
double I_MIN = 10e-6;
#define NUM_TREES 20
//ALL CURENTS IN MICRO, ALL VOLTAGES AS VOLTS, ALL AREA IN NANOMETER
void InitializeInputTracks(ATCTrack ** inputs);
void InitializeComparators(Comparator** cpm);
void GenerateComparatorOutputs(Comparator** cpm, ATMTrackArray* arr, ATCTrack **inputs, int* CPM_Outputs, VoltageToCurrentConverter *V2I);
double CalculateTotalEnergy(Comparator** cpm, ATMTrackArray* arr, ATCTrack** inputs, RowDecoder *rowDecoder, ColumnDecoder *colDecoder, VoltageToCurrentConverter *V2I, MajorityVoter *majorityVoter);
double CalculateTotalArea(Comparator** cpm, ATMTrackArray* arr, ATCTrack** inputs, RowDecoder *rowDecoder, ColumnDecoder *colDecoder, VoltageToCurrentConverter *V2I, MajorityVoter *majorityVoter);
int main(){
    ATMTrackArray *ATMArray = new ATMTrackArray();
    ATMArray->Initialize(INPUT_COLUMNS-1, INPUT_ROWS, 0, MAX_WEIGHT);
    ATCTrack **inputs = new ATCTrack*[INPUT_ROWS];
    Comparator **cpm = new Comparator*[(INPUT_COLUMNS-1)];
    int* CPM_Outputs = new int[(INPUT_COLUMNS-1)/2];
    RowDecoder *rowDecoder = new RowDecoder();
    ColumnDecoder *colDecoder = new ColumnDecoder();
    MajorityVoter *majorityVoter = new MajorityVoter();
    VoltageToCurrentConverter *V2I = new VoltageToCurrentConverter();


    majorityVoter->Initialize(NUM_TREES);
    rowDecoder->Initialize();
    colDecoder->Initialize(INPUT_ROWS, INPUT_COLUMNS-1);
    // majorityVoter->Initialize(20);
    V2I->Initialize();
    InitializeComparators(cpm);
    InitializeInputTracks(inputs);
    loadArray(ATMArray, inputs, "NewInputs/32T2048L.csv", MIN_WEIGHT, MAX_WEIGHT, INPUT_COLUMNS, INPUT_ROWS, I_MAX, I_MIN, V2I);
    GenerateComparatorOutputs(cpm, ATMArray, inputs, CPM_Outputs, V2I);
    CalculateTotalEnergy(cpm, ATMArray, inputs, rowDecoder, colDecoder, V2I, majorityVoter);
   CalculateTotalArea(cpm, ATMArray, inputs, rowDecoder, colDecoder, V2I, majorityVoter);
    cout << ATMArray->cell[0][0]->CalculateArea() << endl;
    // cout << "--- Comparator Output ---" << endl;
    // for(int i = 0; i < INPUT_COLUMNS-1; i++){
    //     cout << cpm[i]->VCPM << " ";
    // }
//     for(int i = 0; i < INPUT_COLUMNS-1; i++){
//         for(int j = 0; j < INPUT_ROWS; j++){
//    //         cout << ATMArray->cell[i][j]->dutyCycle  << "  ";
//         }
//         cout << endl;
//     }
    cout << endl;
    // cout << " CPM Individual Outputs: " << endl;
    // for(int i = 0; i < INPUT_COLUMNS-1; i++){
    //    cout << cpm[i]->VCPM << "   ";
    // }
    // cout << endl;
    // cout << " CPM Anded Outputs: " << endl;
    //  for(int j = 0; j < (INPUT_COLUMNS-1)/2; j++){
    //     cout << CPM_Outputs[j] << "    ";
    //  }
    //  cout << endl;


    return 0;
}

void InitializeInputTracks(ATCTrack** inputs){
    for(int i = 0; i < INPUT_ROWS; i++){
        inputs[i] = new ATCTrack();
        inputs[i]->Initialize(0, 1);
    }
}

void InitializeComparators(Comparator** cpm){
    for(int i = 0; i < (INPUT_COLUMNS-1); i++){
        cpm[i] = new Comparator();
        cpm[i]->Initialize();
    }
}

void GenerateComparatorOutputs(Comparator** cpm, ATMTrackArray* arr, ATCTrack **inputs, int* CPM_Outputs, VoltageToCurrentConverter *V2I){
    for(int i = 0; i < INPUT_COLUMNS-1; i++){
        cpm[i]->Output(inputs, arr, i, INPUT_ROWS, V2I);
    }
    for(int j = 0; j < (INPUT_COLUMNS-1); j += 2){
        CPM_Outputs[j/2] = cpm[j]->VCPM & cpm[j+1]->VCPM;
    }
}

double CalculateTotalEnergy(Comparator** cpm, ATMTrackArray* arr, ATCTrack** inputs, RowDecoder *rowDecoder, ColumnDecoder *colDecoder, VoltageToCurrentConverter *V2I, MajorityVoter *majorityVoter){
    //V2I: Every time something is read (multiply by 2 for reading) or written to ATC or ATM
    //Row and column decoder: Row decoder - multiply energy by # of rows, column decoder - m*n
    //Majority voter: Keep energy of majority voter separate for now
    Inputs *param = new Inputs();
    double totalEnergy = 0;
    double comparatorEnergy = 0;
    for(int i = 0; i < INPUT_COLUMNS-1; i++){
        totalEnergy += cpm[i]->comparisonEnergy;
        comparatorEnergy += cpm[i]->comparisonEnergy;
    }
   // totalEnergy += arr->writeEnergy;
    totalEnergy += arr->readEnergy;
    for(int i = 0; i < INPUT_ROWS; i++){
        totalEnergy += inputs[i]->CalculateWriteEnergy();
    }
    for(int i = 0; i < INPUT_ROWS; i++){
        totalEnergy += inputs[i]->readEnergy;
    }
    rowDecoder->CalculateEnergy(INPUT_COLUMNS-1, INPUT_ROWS);
    colDecoder->CalculateEnergy();
    majorityVoter->CalculateEnergy();
    double AND_ENERGY = INPUT_ROWS*(INPUT_COLUMNS-1)*0.5*(4*param->featureSize*param->featureSize*2.56e-11);
    double TANDTOR_ENERGY = INPUT_ROWS*(INPUT_COLUMNS-1)*(0.1+0.035*(param->WCPM/param->LCPM))*10e-15*param->VDD*param->VDD;
    comparatorEnergy += AND_ENERGY;
    comparatorEnergy += TANDTOR_ENERGY;
    totalEnergy += rowDecoder->energy;
    totalEnergy += colDecoder->energy;
    totalEnergy += V2I->energy;
    totalEnergy += majorityVoter->Energy;

    cout << "---- ENERGY ----" << endl;
    cout << "Total Energy : " << totalEnergy << endl;
    double arrayEnergy = 0;
    for(int i = 0; i < INPUT_COLUMNS-1; i++){
        for(int j = 0; j < INPUT_ROWS; j++){
            arrayEnergy +=arr->cell[i][j]->CalculateReadEnergy();
           // cout << arr->cell[i][j]->CalculateReadEnergy() << endl;
        }
    }
  //  arr->cell[0][0]->PrintProperty("ATM");
    //inputs[0]->PrintProperty("ATC");
    totalEnergy += arrayEnergy; 
    cout << " - Array Energy : " << arrayEnergy << endl;
    cout << " - Comparator Energy : " << comparatorEnergy << endl;
    cout << " - Row Decoder Energy : " << rowDecoder->energy << endl;
    cout << " - Column Decoder Energy : " << colDecoder->energy << endl;
    cout << " - V2I Energy  : "  << V2I->energy << endl;
    cout << " - Majority Voter Energy : " << majorityVoter->Energy << endl;

     return totalEnergy;
}

double CalculateTotalArea(Comparator** cpm, ATMTrackArray* arr, ATCTrack** inputs, RowDecoder *rowDecoder, ColumnDecoder *colDecoder, VoltageToCurrentConverter *V2I, MajorityVoter *majorityVoter){
   Inputs* param = new Inputs();
   double INV_AREA = (2*param->featureSize+param->CMOS_GAP)*(param->featureSize+param->CMOS_GAP)+(4*param->featureSize+param->CMOS_GAP)*(param->featureSize+param->CMOS_GAP);
   double NAND_AREA = 2*(4*param->featureSize+param->CMOS_GAP)*(param->featureSize+param->CMOS_GAP)+2*((4*param->featureSize+param->CMOS_GAP)*(param->featureSize+param->CMOS_GAP));
   double totalAndArea = (INPUT_COLUMNS-1)*0.5*(INV_AREA + NAND_AREA);
   cout << "---- AREA (micro meter) ----" << endl;
   double totalArea = 0;
   double comparatorArea = 0;
   for(int i = 0; i < INPUT_COLUMNS-1; i++){
       cpm[i]->CalculateArea(i);
       totalArea += cpm[i]->area;
       comparatorArea += cpm[i]-> area;
   }
   comparatorArea += totalAndArea;
   double arrayArea = (INPUT_COLUMNS-1)*(INPUT_ROWS)*arr->cell[0][0]->CalculateArea();
   totalArea += arrayArea;
   double ATCArea = INPUT_ROWS*inputs[0]->CalculateArea();
   totalArea += ATCArea;
   rowDecoder->CalculateArea(INPUT_ROWS);
   colDecoder->CalculateArea();
   V2I->CalculateArea(INPUT_COLUMNS);
   majorityVoter->CalculateArea();
   majorityVoter->Area += inputs[0]->CalculateArea()*10 + cpm[0]->buffer_area;
   totalArea += rowDecoder->area;
   totalArea += colDecoder->area;
   totalArea += V2I->area;
   totalArea += majorityVoter->Area;
   cout << "Total Area : " << totalArea << endl;
   cout << " - Array Area : " << arrayArea << endl;
   cout << " - Comparator Area : " << comparatorArea << endl;
   cout << " - Row Decoder Area : " << rowDecoder->area << endl;
   cout << " - Column Decoder Area : " << colDecoder->area << endl;
   cout << " - V2I Area : " << V2I->area << endl;
   cout << " - Majority Voter Area : " << majorityVoter->Area << endl;
   return totalArea;
}