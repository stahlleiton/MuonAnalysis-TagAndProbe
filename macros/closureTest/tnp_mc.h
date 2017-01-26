#ifndef tnp_mc_h
#define tnp_mc_h

#include "TMath.h"

double tnp_mc_trg_pbpb(double x, double eta);
double tnp_mc_trg_pp(double x, double eta);
double tnp_mc_muid_pbpb(double x, double eta);
double tnp_mc_muid_pp(double x, double eta);
double tnp_mc_sta_pp(double x, double eta);
double tnp_mc_trk_pbpb();
double tnp_mc_trk_pp();

///////////////////////////////////////////////////
//               T R G    P b P b                //
///////////////////////////////////////////////////
double tnp_mc_trg_pbpb(double x, double eta)
{
   // denominator (from MC)
   double den=1;
   if (fabs(eta)<1.2) den = (1.64178*TMath::Erf((x-1.99932)/1.43867))-0.66469;
   else if (fabs(eta)<1.8) den = (0.88035*TMath::Erf((x-2.35547)/1.15969))+0.06624;
   else if (fabs(eta)<2.1) den = (0.76354*TMath::Erf((x-1.06381)/2.19873))+0.13397;
   else den = (0.75001*TMath::Erf((x-0.82761)/1.91299))+0.12193;
   return den;
}

///////////////////////////////////////////////////
//               T R G    P P                    //
///////////////////////////////////////////////////
double tnp_mc_trg_pp(double x, double eta)
{
   // denominator (from MC)
   double den=1;
   if (fabs(eta)<1.2) den = (0.51387*(TMath::Erf((x-2.95780)/1.01717)*TMath::Exp(-0.00001*x)))+0.46186;
   else if (fabs(eta)<1.8) den = (0.87963*(TMath::Erf((x-2.33663)/1.22198)*TMath::Exp(-0.00013*x)))+0.06241;
   else if (fabs(eta)<2.1) den = (0.53171*(TMath::Erf((x-1.80661)/1.67849)*TMath::Exp(-0.00000*x)))+0.36279;
   else den = (0.38994*(TMath::Erf((x-1.55863)/1.70815)*TMath::Exp(-0.00003*x)))+0.48718;
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
   if (fabs(eta)<1.2) den = (0.89729*TMath::Erf((x-1.13249)/1.92952))+0.08717;
   else if (fabs(eta)<1.8) den = (0.89052*TMath::Erf((x+2.22470)/3.36829))+0.09852;
   else if (fabs(eta)<2.1) den = (0.49857*TMath::Erf((x+1.05275)/3.92352))+0.49590;
   else den = (0.42980*TMath::Erf((x+0.56912)/3.60743))+0.55171;
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
   if (fabs(eta)<1.2) den = (0.98383*TMath::Erf((x+0.47673)/2.94587))+0.00653;
   else if (fabs(eta)<1.8) den = (0.02768*TMath::Erf((x+8.66696)/28.28792))+0.97612;
   else if (fabs(eta)<2.1) den = (0.74373*TMath::Erf((x-0.30826)/1.07049))+0.25156;
   else den = (0.82009*TMath::Erf((x-1.22789)/0.48924))+0.17143;
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
   if (fabs(eta)<1.2) den = (0.58746*TMath::Erf((x-3.17585)/0.96599))+0.39714;
   else if (fabs(eta)<1.8) den = (0.51632*TMath::Erf((x-0.56984)/1.78604))+0.45932;
   else if (fabs(eta)<2.1) den = (0.51122*TMath::Erf((x-0.01449)/1.43367))+0.47344;
   else den = (0.43706*TMath::Erf((x-0.50936)/1.62531))+0.54785;
   return den;
}

///////////////////////////////////////////////////
//                 T R K    P b P b              //
///////////////////////////////////////////////////

double tnp_mc_trk_pbpb() {
   // denominator (from MC)
   return 0.9938;
}

///////////////////////////////////////////////////
//                   T R K    P P                //
///////////////////////////////////////////////////

double tnp_mc_trk_pp() {
   // denominator (from MC)
   return 0.9973;
}

#endif //#ifndef tnp_mc_h
