#ifndef INPUTS_H_
#define INPUTS_H_
class Inputs{
    public:
    int numStates = 16;
    double Imax_ref = 100e-6;
    double Imin_ref = 10e-6;
    // double trackLength = 640e-9;
    // double trackWidth = 100e-9;
    double LCPM = 0.3;
    double WCPM = 0.1;
    double T_ref = 1e-9;
    double CPM_ref = 0.5e-9;
  //  double RHM - 500;
    double RN = 1.83e3; //NEED TO CHECK!!!!!!!!!!!!!!!!!!!!!!
    double RH = 20e3;
    double RL = 6.67e3;
    double R0 = 12e3; // NEED TO CHECK
    double Rf = 20e3;
    double Vb = 0.7; //NEED TO CHECK
    double VDD = 0.7;
    double RHM = 500;
    double CBUFF = 100e-15; //NEED TO CHECK
    double VMH = 0.4;
    double VML = 0.2;
    double CMOS_GAP = 0.0024;
    double RTM_GAP = 0.01;
    double featureSize = .016;
    double BETA_NMOS = 320e-6;
    double Vth = 0.43;
    double gamma = 3.45;
    double W_current_mirror = .128;
    double L_current_mirror = .016;
    double I_base = 10e-6;
    double Wpass = .032;
    double Lpass = .016;
    double Alpha = 10;
    double CL = 4.89e-18;
    double Rs = 24e-6;
    double L_switch = .016;
    double W_switch = 2*L_switch;
    double COX = 23.56e-18;
    double WRTM = .1;
    double LRTM = .64;
    double lambda_row = 1;
    double lambda_col = 2;
};
#endif