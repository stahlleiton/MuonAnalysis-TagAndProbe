#ifndef tnp_mc_h
#define tnp_mc_h

#include "TMath.h"

double tnp_mc_trg_pbpb(double x, double eta);
double tnp_mc_trg_pp(double x, double eta);
double tnp_mc_muid_pbpb(double x, double eta);
double tnp_mc_muid_pp(double x, double eta);
double tnp_mc_sta_pp(double x, double eta);

///////////////////////////////////////////////////
//               T R G    P b P b                //
///////////////////////////////////////////////////
double tnp_mc_trg_pbpb(double x, double eta)
{
   // denominator (from MC)
   double den=1;
   if (fabs(eta)<1.2) den = 0.97701*TMath::Erf((x-2.38691)/1.31574);
   else if (fabs(eta)<1.8) den = 0.94675*TMath::Erf((x-2.29271)/1.19047);
   else if (fabs(eta)<2.1) den = 0.89781*TMath::Erf((x-0.80641)/2.31842);
   else den = 0.87208*TMath::Erf((x-0.63360)/1.99416);
   return den;
}

///////////////////////////////////////////////////
//               T R G    P P                    //
///////////////////////////////////////////////////
double tnp_mc_trg_pp(double x, double eta)
{
   // denominator (from MC)
   double den=1;
   if (fabs(eta)<1.2) den = (34.38245*(TMath::Erf((x-5.78815)/2.97251)*TMath::Exp(-1.37492*x)))+0.97770;
   else if (fabs(eta)<1.8) den = (52.18025*(TMath::Erf((x-6.06559)/6.11135)*TMath::Exp(-1.42980*x)))+0.94384;
   else if (fabs(eta)<2.1) den = (7.30528*(TMath::Erf((x-5.21429)/11.40230)*TMath::Exp(-0.76187*x)))+0.89352;
   else den = (17.36511*(TMath::Erf((x-5.04177)/41.72924)*TMath::Exp(-0.79676*x)))+0.87670;
   return den;
}

///////////////////////////////////////////////////
//             M U I D    P b P b                //
///////////////////////////////////////////////////

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!  ONLY FOR SYSTEMATICS! DO NOT APPLY FOR THE NOMINAL CORRECTION!!! !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

double tnp_mc_muid_pbpb(double x, double eta) {
   // denominator (from MC)
   double den=1;
   if (fabs(eta)<1.2) den = 0.99*TMath::Erf((x+1.16)/3.49);
   else if (fabs(eta)<1.8) den = 0.99*TMath::Erf((x+3.63)/4.27);
   else if (fabs(eta)<2.1) den = 1.00*TMath::Erf((x+4.64)/6.08);
   else den = 0.99*TMath::Erf((x+3.17)/4.98);
   return den;
}

///////////////////////////////////////////////////
//                 M U I D    P P                //
///////////////////////////////////////////////////

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!  ONLY FOR SYSTEMATICS! DO NOT APPLY FOR THE NOMINAL CORRECTION!!! !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

double tnp_mc_muid_pp(double x, double eta) {
   // denominator (from MC)
   double den=1;
   if (fabs(eta)<1.2) den = (0.17208*TMath::Erf((x-1.91314)/2.21047))+0.81832;
   else if (fabs(eta)<1.8) den = (0.02468*TMath::Erf((x+5.04947)/15.26842))+0.97444;
   else if (fabs(eta)<2.1) den = (0.01153*TMath::Erf((x-1.49227)/2.99647))+0.98563;
   else den = (0.02998*TMath::Erf((x+9.82571)/17.70087))+0.96778;
   return den;
}

///////////////////////////////////////////////////
//                   S T A    P P                //
///////////////////////////////////////////////////

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!  ONLY FOR SYSTEMATICS! DO NOT APPLY FOR THE NOMINAL CORRECTION!!! !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

double tnp_mc_sta_pp(double x, double eta) {
   // denominator (from MC)
   double den=1;
   if (fabs(eta)<1.2) den = (1.16795*TMath::Erf((x-2.70934)/1.14920))-0.18306;
   else if (fabs(eta)<1.8) den = (0.06821*TMath::Erf((x-2.40814)/1.06603))+0.90716;
   else if (fabs(eta)<2.1) den = (0.02081*TMath::Erf((x-2.07575)/0.86473))+0.96405;
   else den = (0.03392*TMath::Erf((x-2.61705)/0.01196))+0.94859;
   return den;
}

#endif //#ifndef tnp_mc_h
