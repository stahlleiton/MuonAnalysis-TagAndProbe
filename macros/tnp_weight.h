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
// - Trigger: (tnp_weight_trg_pbpb)  Preliminary
//   * idx = 0:  nominal
//   * idx = -1: TnP syst variation,  +1 sigma
//   * idx = -2: TnP syst variation,  -1 sigma
//   * idx = +1: stat variation,  +1 sigma
//   * idx = +2: stat variation,  -1 sigma

// For all:
//   * idx = +200: tnp efficiency for data
//   * idx = +300: tnp efficiency for MC

// THE INDIVIDUAL SFs
// ++++++++++++++++++
double tnp_weight_muid_pbpb(double eta, int idx=0);
double tnp_weight_trig_pbpb(double pt, double eta, int idx=0);



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
    if (pt > 15 && pt <= 20) den = 0.940279;
    else if (pt > 20 && pt <= 30) den = 0.952896;
    else if (pt > 30 && pt <= 50) den = 0.96442;
    else if (pt > 50 && pt <= 80) den = 0.966926;
    else if (pt > 80 && pt <= 9999) den = 0.959055;
  }
  else if (fabs(eta) > 1.2 && fabs(eta) <= 2.1) { 
    if (pt > 15 && pt <= 20) den = 0.928228;
    else if (pt > 20 && pt <= 30) den = 0.940141;
    else if (pt > 30 && pt <= 50) den = 0.953928;
    else if (pt > 50 && pt <= 80) den = 0.958638;
    else if (pt > 80 && pt <= 9999) den = 0.961176;
  }
  else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
    if (pt > 15 && pt <= 20) den = 0.892999;
    else if (pt > 20 && pt <= 30) den = 0.91481;
    else if (pt > 30 && pt <= 50) den = 0.933872;
    else if (pt > 50 && pt <= 80) den = 0.943662;
    else if (pt > 80 && pt <= 9999) den = 0.947917;
  }

  // data
  if (idx <= 0 || idx > 10) { // nominal
    if (fabs(eta) > 0 && fabs(eta) <= 1.2) { 
      if (pt > 15 && pt <= 20) num = 0.877324;
      else if (pt > 20 && pt <= 30) num = 0.932243;
      else if (pt > 30 && pt <= 50) num = 0.94894;
      else if (pt > 50 && pt <= 80) num = 0.949885;
      else if (pt > 80 && pt <= 9999) num = 0.940513;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 2.1) { 
      if (pt > 15 && pt <= 20) num = 0.88725;
      else if (pt > 20 && pt <= 30) num = 0.905588;
      else if (pt > 30 && pt <= 50) num = 0.927011;
      else if (pt > 50 && pt <= 80) num = 0.939565;
      else if (pt > 80 && pt <= 9999) num = 0.928469;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 15 && pt <= 20) num = 0.828835;
      else if (pt > 20 && pt <= 30) num = 0.853867;
      else if (pt > 30 && pt <= 50) num = 0.89868;
      else if (pt > 50 && pt <= 80) num = 0.913391;
      else if (pt > 80 && pt <= 9999) num = 0.889446;
    }
  }
  else if (idx == 1) { // stat up
    if (fabs(eta) > 0 && fabs(eta) <= 1.2) { 
      if (pt > 15 && pt <= 20) num = 0.892207;
      else if (pt > 20 && pt <= 30) num = 0.937328;
      else if (pt > 30 && pt <= 50) num = 0.952432;
      else if (pt > 50 && pt <= 80) num = 0.954593;
      else if (pt > 80 && pt <= 9999) num = 0.953668;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 2.1) { 
      if (pt > 15 && pt <= 20) num = 0.900786;
      else if (pt > 20 && pt <= 30) num = 0.912801;
      else if (pt > 30 && pt <= 50) num = 0.929974;
      else if (pt > 50 && pt <= 80) num = 0.946251;
      else if (pt > 80 && pt <= 9999) num = 0.9486;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 15 && pt <= 20) num = 0.85611;
      else if (pt > 20 && pt <= 30) num = 0.868009;
      else if (pt > 30 && pt <= 50) num = 0.905552;
      else if (pt > 50 && pt <= 80) num = 0.929288;
      else if (pt > 80 && pt <= 9999) num = 0.940054;
    }
  }
  else if (idx == 2) { // stat down
    if (fabs(eta) > 0 && fabs(eta) <= 1.2) { 
      if (pt > 15 && pt <= 20) num = 0.861214;
      else if (pt > 20 && pt <= 30) num = 0.926936;
      else if (pt > 30 && pt <= 50) num = 0.945448;
      else if (pt > 50 && pt <= 80) num = 0.944865;
      else if (pt > 80 && pt <= 9999) num = 0.925242;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 2.1) { 
      if (pt > 15 && pt <= 20) num = 0.872408;
      else if (pt > 20 && pt <= 30) num = 0.898092;
      else if (pt > 30 && pt <= 50) num = 0.923997;
      else if (pt > 50 && pt <= 80) num = 0.93245;
      else if (pt > 80 && pt <= 9999) num = 0.904228;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 15 && pt <= 20) num = 0.798669;
      else if (pt > 20 && pt <= 30) num = 0.838871;
      else if (pt > 30 && pt <= 50) num = 0.891469;
      else if (pt > 50 && pt <= 80) num = 0.895112;
      else if (pt > 80 && pt <= 9999) num = 0.819963;
    }
  }
  else if (idx == -1) { // syst up
    if (fabs(eta) > 0 && fabs(eta) <= 1.2) { 
      if (pt > 15 && pt <= 20) num = 0.884273;
      else if (pt > 20 && pt <= 30) num = 0.932815;
      else if (pt > 30 && pt <= 50) num = 0.949512;
      else if (pt > 50 && pt <= 80) num = 0.950423;
      else if (pt > 80 && pt <= 9999) num = 0.940912;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 2.1) { 
      if (pt > 15 && pt <= 20) num = 0.893591;
      else if (pt > 20 && pt <= 30) num = 0.906448;
      else if (pt > 30 && pt <= 50) num = 0.928115;
      else if (pt > 50 && pt <= 80) num = 0.941159;
      else if (pt > 80 && pt <= 9999) num = 0.930308;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 15 && pt <= 20) num = 0.835232;
      else if (pt > 20 && pt <= 30) num = 0.855873;
      else if (pt > 30 && pt <= 50) num = 0.900685;
      else if (pt > 50 && pt <= 80) num = 0.915397;
      else if (pt > 80 && pt <= 9999) num = 0.891452;
    }
  }
  else if (idx == -2) { // syst down
    if (fabs(eta) > 0 && fabs(eta) <= 1.2) { 
      if (pt > 15 && pt <= 20) num = 0.870375;
      else if (pt > 20 && pt <= 30) num = 0.93167;
      else if (pt > 30 && pt <= 50) num = 0.948368;
      else if (pt > 50 && pt <= 80) num = 0.949348;
      else if (pt > 80 && pt <= 9999) num = 0.940115;
    }
    else if (fabs(eta) > 1.2 && fabs(eta) <= 2.1) { 
      if (pt > 15 && pt <= 20) num = 0.880909;
      else if (pt > 20 && pt <= 30) num = 0.904728;
      else if (pt > 30 && pt <= 50) num = 0.925906;
      else if (pt > 50 && pt <= 80) num = 0.937972;
      else if (pt > 80 && pt <= 9999) num = 0.926631;
    }
    else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) { 
      if (pt > 15 && pt <= 20) num = 0.822438;
      else if (pt > 20 && pt <= 30) num = 0.851862;
      else if (pt > 30 && pt <= 50) num = 0.896674;
      else if (pt > 50 && pt <= 80) num = 0.911386;
      else if (pt > 80 && pt <= 9999) num = 0.887441;
    }
  }

  if (idx == 200) den = 1.0;
  if (idx == 300) num = den * den;

  return (num/den);
}

#endif //#ifndef tnp_weight_h
