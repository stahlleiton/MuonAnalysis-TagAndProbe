#ifndef tnp_weight_h
#define tnp_weight_h

#include "TMath.h"

// IN THIS FILE YOU WILL FIND:
// ++++++++++++++
//
// - MuID: (tnp_weight_muid_pbpb)   Preliminary
//   * idx = 0: nominal
//   * idx = -1: syst variation,  +1 sigma
//   * idx = -2: syst variation,  -1 sigma
//   * idx = +1: stat variation,  +1 sigma
//   * idx = +2: stat variation,  -1 sigma
//
// - Trigger: (tnp_weight_trg_pbpb)   NOT UPDATED
//   * idx = 0:  nominal
//   * idx = 1..100: toy variations, stat. only
//   * idx = -1: syst variation, "new_MAX", +1 sigma
//   * idx = -2: syst variation, "new_MAX", -1 sigma
//   * idx = -10: binned

// For all:
//   * idx = +200: tnp efficiency for data
//   * idx = +300: tnp efficiency for MC

// THE INDIVIDUAL SFs
// ++++++++++++++++++
double tnp_weight_muid_pbpb(double eta, int idx=0);
double tnp_weight_trg_pbpb(double pt, double eta, int idx=0);  // NOT UPDATED



///////////////////////////////////////////////////
//                 M u I D    P b P b                //
///////////////////////////////////////////////////
double tnp_weight_muid_pbpb(double eta, int idx)
{
   double x = eta;
   double syst = 0.6e-2;  //preliminary

   double num=1,den=1;
   

   // MC
   if (x > -2.4&&x <= -2.1) den = 0.994717;
   if (x > -2.1&&x <= -1.6) den = 0.993653;
   if (x > -1.6&&x <= -1.2) den = 0.982687;
   if (x > -1.2&&x <= -0.9) den = 0.962992;
   if (x > -0.9&&x <= -0.6) den = 0.970103;
   if (x > -0.6&&x <= -0.3) den = 0.982073;
   if (x > -0.3&&x <= 0) den = 0.968219;
   if (x > 0 && x <= 0.3) den = 0.961703;
   if (x > 0.3&&x <= 0.6) den = 0.978947;
   if (x > 0.6&&x <= 0.9) den = 0.970324;
   if (x > 0.9&&x <= 1.2) den = 0.956433;
   if (x > 1.2&&x <= 1.6) den = 0.982577;
   if (x > 1.6&&x <= 2.1) den = 0.995146;
   if (x > 2.1&&x <= 2.4) den = 0.994106;


   // data
   if (idx <= 0 || idx > 10) { // nominal
	   if (x > -2.4&&x <= -2.1) num = 0.983734;
	   if (x > -2.1&&x <= -1.6) num = 0.993892;
	   if (x > -1.6&&x <= -1.2) num = 0.979222;
	   if (x > -1.2&&x <= -0.9) num = 0.955529;
	   if (x > -0.9&&x <= -0.6) num = 0.966578;
	   if (x > -0.6&&x <= -0.3) num = 0.983958;
	   if (x > -0.3&&x <= 0) num = 0.959491;
	   if (x > 0 && x <= 0.3) num = 0.959744;
	   if (x > 0.3&&x <= 0.6) num = 0.976402;
	   if (x > 0.6&&x <= 0.9) num = 0.96839;
	   if (x > 0.9&&x <= 1.2) num = 0.961177;
	   if (x > 1.2&&x <= 1.6) num = 0.98078;
	   if (x > 1.6&&x <= 2.1) num = 0.991852;
	   if (x > 2.1&&x <= 2.4) num = 0.993082;
   }
   else if (idx == 1) { // stat up
	   if (x > -2.4&&x <= -2.1) num = 0.98710825;
	   if (x > -2.1&&x <= -1.6) num = 0.99575701;
	   if (x > -1.6&&x <= -1.2) num = 0.98250043;
	   if (x > -1.2&&x <= -0.9) num = 0.96029298;
	   if (x > -0.9&&x <= -0.6) num = 0.97057735;
	   if (x > -0.6&&x <= -0.3) num = 0.98705592;
	   if (x > -0.3&&x <= 0) num = 0.96370511;
	   if (x > 0 && x <= 0.3) num = 0.96396652;
	   if (x > 0.3&&x <= 0.6) num = 0.97980996;
	   if (x > 0.6&&x <= 0.9) num = 0.97234624;
	   if (x > 0.9&&x <= 1.2) num = 0.9659164;
	   if (x > 1.2&&x <= 1.6) num = 0.98388187;
	   if (x > 1.6&&x <= 2.1) num = 0.99371692;
	   if (x > 2.1&&x <= 2.4) num = 0.9961665;
   }
   else if (idx == 2) { // stat down
	   if (x > -2.4&&x <= -2.1) num = 0.98075691;
	   if (x > -2.1&&x <= -1.6) num = 0.99224693;
	   if (x > -1.6&&x <= -1.2) num = 0.97618383;
	   if (x > -1.2&&x <= -0.9) num = 0.95101985;
	   if (x > -0.9&&x <= -0.6) num = 0.96279449;
	   if (x > -0.6&&x <= -0.3) num = 0.98108946;
	   if (x > -0.3&&x <= 0) num = 0.95550071;
	   if (x > 0 && x <= 0.3) num = 0.95575316;
	   if (x > 0.3&&x <= 0.6) num = 0.97322907;
	   if (x > 0.6&&x <= 0.9) num = 0.96468663;
	   if (x > 0.9&&x <= 1.2) num = 0.9567025;
	   if (x > 1.2&&x <= 1.6) num = 0.9779218;
	   if (x > 1.6&&x <= 2.1) num = 0.99018962;
	   if (x > 2.1&&x <= 2.4) num = 0.9905424;
   }

   if (idx == 200) den = 1.;
   if (idx == 300) num = den * den;


   double syst_factor = 1.;
   if (idx == -1) syst_factor = 1 + syst;
   if (idx == -2) syst_factor = 1 - syst;
   return (num / den)*syst_factor;
}


///////////////////////////////////////////////////
//               T R G      P b P b              //
///////////////////////////////////////////////////
double tnp_weight_trig_pbpb(double pt, double eta, int idx)
{
  double num=1.0, den=1.0;

  // MC
  if (fabs(eta) > 0 && fabs(eta) <= 1.2) { 
    if (pt > 15 && pt <= 20) den = 0.929682;
    else if (pt > 20 && pt <= 30) den = 0.955507;
    else if (pt > 30 && pt <= 50) den = 0.964566;
    else if (pt > 50 && pt <= 80) den = 0.967298;
    else if (pt > 80 && pt <= 9999) den = 0.958746;
  }
  else if (fabs(eta) > 1.2 && fabs(eta) <= 2.1) { 
    if (pt > 15 && pt <= 20) den = 0.918536;
    else if (pt > 20 && pt <= 30) den = 0.943554;
    else if (pt > 30 && pt <= 50) den = 0.95398;
    else if (pt > 50 && pt <= 80) den = 0.959336;
    else if (pt > 80 && pt <= 9999) den = 0.958833;
  }
  else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
    if (pt > 15 && pt <= 20) den = 0.892248;
    else if (pt > 20 && pt <= 30) den = 0.911687;
    else if (pt > 30 && pt <= 50) den = 0.936458;
    else if (pt > 50 && pt <= 80) den = 0.941882;
    else if (pt > 80 && pt <= 9999) den = 0.928107;
  }

  // data
  if (idx <= 0 || idx > 10) { // nominal
    if (fabs(eta) > 0 && fabs(eta) <= 1.2) { 
      if (pt > 15 && pt <= 20) num = 0.875758;
      else if (pt > 20 && pt <= 30) num = 0.933211;
      else if (pt > 30 && pt <= 50) num = 0.948737;
      else if (pt > 50 && pt <= 80) num = 0.949324;
      else if (pt > 80 && pt <= 9999) num = 0.940581;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 2.1) { 
      if (pt > 15 && pt <= 20) num = 0.893972;
      else if (pt > 20 && pt <= 30) num = 0.906514;
      else if (pt > 30 && pt <= 50) num = 0.925745;
      else if (pt > 50 && pt <= 80) num = 0.934989;
      else if (pt > 80 && pt <= 9999) num = 0.925771;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 15 && pt <= 20) num = 0.828838;
      else if (pt > 20 && pt <= 30) num = 0.87173;
      else if (pt > 30 && pt <= 50) num = 0.898914;
      else if (pt > 50 && pt <= 80) num = 0.914083;
      else if (pt > 80 && pt <= 9999) num = 0.88936;
    }
  }
  else if (idx == 1) { // stat up
    if (fabs(eta) > 0 && fabs(eta) <= 1.2) { 
      if (pt > 15 && pt <= 20) num = 0.890679;
      else if (pt > 20 && pt <= 30) num = 0.93825;
      else if (pt > 30 && pt <= 50) num = 0.950599;
      else if (pt > 50 && pt <= 80) num = 0.954049;
      else if (pt > 80 && pt <= 9999) num = 0.953723;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 2.1) { 
      if (pt > 15 && pt <= 20) num = 0.908596;
      else if (pt > 20 && pt <= 30) num = 0.913665;
      else if (pt > 30 && pt <= 50) num = 0.928577;
      else if (pt > 50 && pt <= 80) num = 0.941448;
      else if (pt > 80 && pt <= 9999) num = 0.945669;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 15 && pt <= 20) num = 0.85611;
      else if (pt > 20 && pt <= 30) num = 0.886324;
      else if (pt > 30 && pt <= 50) num = 0.905769;
      else if (pt > 50 && pt <= 80) num = 0.929944;
      else if (pt > 80 && pt <= 9999) num = 0.940082;
    }
  }
  else if (idx == 2) { // stat down
    if (fabs(eta) > 0 && fabs(eta) <= 1.2) { 
      if (pt > 15 && pt <= 20) num = 0.860029;
      else if (pt > 20 && pt <= 30) num = 0.927955;
      else if (pt > 30 && pt <= 50) num = 0.946871;
      else if (pt > 50 && pt <= 80) num = 0.94431;
      else if (pt > 80 && pt <= 9999) num = 0.925323;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 2.1) { 
      if (pt > 15 && pt <= 20) num = 0.878284;
      else if (pt > 20 && pt <= 30) num = 0.899086;
      else if (pt > 30 && pt <= 50) num = 0.922844;
      else if (pt > 50 && pt <= 80) num = 0.928099;
      else if (pt > 80 && pt <= 9999) num = 0.901912;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 15 && pt <= 20) num = 0.798669;
      else if (pt > 20 && pt <= 30) num = 0.856249;
      else if (pt > 30 && pt <= 50) num = 0.891752;
      else if (pt > 50 && pt <= 80) num = 0.896096;
      else if (pt > 80 && pt <= 9999) num = 0.819909;
    }
  }
  else if (idx == -1) { // syst up
    if (fabs(eta) > 0 && fabs(eta) <= 1.2) { 
      if (pt > 15 && pt <= 20) num = 0.930309;
      else if (pt > 20 && pt <= 30) num = 0.933686;
      else if (pt > 30 && pt <= 50) num = 0.949212;
      else if (pt > 50 && pt <= 80) num = 0.949755;
      else if (pt > 80 && pt <= 9999) num = 0.940849;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 2.1) { 
      if (pt > 15 && pt <= 20) num = 0.899185;
      else if (pt > 20 && pt <= 30) num = 0.907991;
      else if (pt > 30 && pt <= 50) num = 0.92848;
      else if (pt > 50 && pt <= 80) num = 0.940241;
      else if (pt > 80 && pt <= 9999) num = 0.93228;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 15 && pt <= 20) num = 0.847212;
      else if (pt > 20 && pt <= 30) num = 0.873167;
      else if (pt > 30 && pt <= 50) num = 0.902384;
      else if (pt > 50 && pt <= 80) num = 0.921622;
      else if (pt > 80 && pt <= 9999) num = 0.898933;
    }
  }
  else if (idx == -2) { // syst down
    if (fabs(eta) > 0 && fabs(eta) <= 1.2) { 
      if (pt > 15 && pt <= 20) num = 0.821206;
      else if (pt > 20 && pt <= 30) num = 0.932736;
      else if (pt > 30 && pt <= 50) num = 0.948261;
      else if (pt > 50 && pt <= 80) num = 0.948893;
      else if (pt > 80 && pt <= 9999) num = 0.940313;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 2.1) { 
      if (pt > 15 && pt <= 20) num = 0.888759;
      else if (pt > 20 && pt <= 30) num = 0.905038;
      else if (pt > 30 && pt <= 50) num = 0.923011;
      else if (pt > 50 && pt <= 80) num = 0.929738;
      else if (pt > 80 && pt <= 9999) num = 0.919261;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 15 && pt <= 20) num = 0.810465;
      else if (pt > 20 && pt <= 30) num = 0.870294;
      else if (pt > 30 && pt <= 50) num = 0.895443;
      else if (pt > 50 && pt <= 80) num = 0.906544;
      else if (pt > 80 && pt <= 9999) num = 0.879788;
    }
  }

  if (idx == 200) den = 1.0;
  if (idx == 300) num = den * den;

  return (num/den);
}

#endif //#ifndef tnp_weight_h
