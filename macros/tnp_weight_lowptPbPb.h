#ifndef tnp_weight_lowptPbPb_h
#define tnp_weigt_lowptPbPb_h
#include "TMath.h"

// IN THIS FILE YOU WILL FIND:
// +++++++++++++++++++++++++++++++++++++++
// - Trigger: (tnp_weight_trg_pbpb)
//   * filterId = 0: Jpsi L2 filter
//   * filterId = 1: Jpsi L3 filter
//   * filterId = 2: Upsi L2 filter
//   * filterId = 3: Upsi L3 filter
//   * idx = 0:  nominal
//   * idx = -1: syst variation, +1 sigma
//   * idx = -2: syst variation, -1 sigma
// - MuID: (tnp_weight_muid_pbpb)
//   * idx = 0:  nominal
//   * idx = -1: syst variation, +1 sigma
//   * idx = -2: syst variation, -1 sigma
// - Inner tracking: (tnp_weight_trk_pbpb)
//   * idx = 0:  nominal
//   * idx = -1: syst variation, +1 sigma
//   * idx = -2: syst variation, -1 sigma
// +++++++++++++++++++++++++++++++++++++++

double tnp_weight_muid_pbpb(double pt, double eta, int idx=0);
double tnp_weight_trk_pbpb(double eta, int idx=0);
double tnp_weight_trg_pbpb(double pt, double eta, int filterId=0,int idx=0);

///////////////////////////////////////////////////
//             M u I D    P b P b                //
///////////////////////////////////////////////////

double tnp_weight_muid_pbpb(double pt, double eta, int idx) {
  double x = pt;
  double num=1,den=1;
  if (idx == 0 || idx<0 ) { //nominal or syst up/down
    // SF for 0 < |eta| < 1.2
    if (fabs(eta) >= 0 && fabs(eta) < 1.2) {
      if (x >= 3.5 && x <4) {num = 0.946125; den = 0.95062;}
      else if (x >= 4 && x <4.5) {num = 0.973366; den = 0.975256;}
      else if (x >= 4.5 && x <5) {num = 0.984622; den = 0.983749;}
      else if (x >= 5 && x <5.5) {num = 0.985061; den = 0.98948;}
      else if (x >= 5.5 && x <6.5) {num = 0.988937; den = 0.99051;}
      else if (x >= 6.5 && x <8) {num = 0.991257; den = 0.992598;}
      else if (x >= 8 && x <10.5) {num = 0.986505; den = 0.9885;}
      else if (x >= 10.5 && x <14) {num = 0.975903; den = 0.967524;}
      else if (x >= 14 && x <18) {num = 0.979888; den = 0.978318;}
      else {num = 0.983224; den = 0.984461;}
    }
    // SF for 1.2 < |eta| < 1.8
    if (fabs(eta) >= 1.2 && fabs(eta) < 1.8) {
      if (x >= 2.37 && x <3) {num = 0.983353; den = 0.981734;}
      else if (x >= 3 && x <3.5) {num = 0.985622; den = 0.984888;}
      else if (x >= 3.5 && x <4) {num = 0.980436; den = 0.989513;}
      else if (x >= 4 && x <4.5) {num = 0.986109; den = 0.991777;}
      else if (x >= 4.5 && x <5) {num = 0.992053; den = 0.993039;}
      else if (x >= 5 && x <6) {num = 0.989106; den = 0.994324;}
      else if (x >= 6 && x <7.5) {num = 0.995133; den = 0.997452;}
      else if (x >= 7.5 && x <10) {num = 0.998692; den = 0.996495;}
      else if (x >= 10 && x <15) {num = 0.979734; den = 0.971008;}
      else {num = 0.996433; den = 0.987155;}
    }
    // SF for 1.8 < |eta| < 2.1
    if (fabs(eta) >= 1.8 && fabs(eta) < 2.1) {
      if (x >= 1.8 && x <2.5) {num = 0.970771; den = 0.955555;}
      else if (x >= 2.5 && x <3) {num = 0.984571; den = 0.983608;}
      else if (x >= 3 && x <3.5) {num = 0.991532; den = 0.99085;}
      else if (x >= 3.5 && x <4) {num = 0.982929; den = 0.995395;}
      else if (x >= 4 && x <4.5) {num = 0.997191; den = 0.998022;}
      else if (x >= 4.5 && x <5.5) {num = 0.996918; den = 0.997783;}
      else if (x >= 5.5 && x <7) {num = 1; den = 0.999082;}
      else if (x >= 7 && x <9) {num = 0.996645; den = 0.999904;}
      else if (x >= 9 && x <12) {num = 0.997479; den = 0.997288;}
      else {num = 0.989358; den = 0.997918;}
    }
    // SF for 2.1 < |eta| < 2.4
    if (fabs(eta) >= 2.1 && fabs(eta) < 2.4) {
      if (x >= 1.8 && x <2.2) {num = 0.89788; den = 0.929933;}
      else if (x >= 2.2 && x <2.7) {num = 0.940431; den = 0.968575;}
      else if (x >= 2.7 && x <3.2) {num = 0.972522; den = 0.980868;}
      else if (x >= 3.2 && x <3.7) {num = 0.977761; den = 0.988464;}
      else if (x >= 3.7 && x <4.7) {num = 0.997206; den = 0.994088;}
      else if (x >= 4.7 && x <8) {num = 0.996334; den = 0.99794;}
      else if (x >= 8 && x <11) {num = 1; den = 0.999768;}
      else if (x >= 11 && x <14) {num = 0.978986; den = 0.998297;}
      else {num = 1; den = 0.996328;}
    }

    if (fabs(eta) >= 0 && fabs(eta) < 1.2) {
      // syst uncertainties
      if (x >= 3.5 && x < 4) syst = 0.000855038;
      if (x >= 4 && x < 4.5) syst = 0.000240768;
      if (x >= 4.5 && x < 5) syst = 0.000899317;
      if (x >= 5 && x < 5.5) syst = 0.00109601;
      if (x >= 5.5 && x < 6.5) syst = 0.000311285;
      if (x >= 6.5 && x < 8) syst = 0.000476892;
      if (x >= 8 && x < 10.5) syst = 0.00122726;
      if (x >= 10.5 && x < 14) syst = 0.00274564;
      if (x >= 14 && x < 18) syst = 0.00133458;
      if (x >= 18 && x < 30) syst = 0.00365302;
    }
    if (fabs(eta) >= 1.2 && fabs(eta) < 1.8) {
      // syst uncertainties
      if (x >= 2.37 && x < 3) syst = 0.00121011;
      if (x >= 3 && x < 3.5) syst = 0.00177203;
      if (x >= 3.5 && x < 4) syst = 0.00181968;
      if (x >= 4 && x < 4.5) syst = 0.00154391;
      if (x >= 4.5 && x < 5) syst = 0.00183399;
      if (x >= 5 && x < 6) syst = 0.000750531;
      if (x >= 6 && x < 7.5) syst = 0.00111009;
      if (x >= 7.5 && x < 10) syst = 0.00123526;
      if (x >= 10 && x < 15) syst = 0.00156111;
      if (x >= 15 && x < 30) syst = 0.00311647;
    }
    if (fabs(eta) >= 1.8 && fabs(eta) < 2.1) {
      // syst uncertainties
      if (x >= 1.8 && x < 2.5) syst = 0.00425782;
      if (x >= 2.5 && x < 3) syst = 0.00100318;
      if (x >= 3 && x < 3.5) syst = 0.00476823;
      if (x >= 3.5 && x < 4) syst = 0.00107436;
      if (x >= 4 && x < 4.5) syst = 0.00280821;
      if (x >= 4.5 && x < 5.5) syst = 0.000743448;
      if (x >= 5.5 && x < 7) syst = 9.14067e-07;
      if (x >= 7 && x < 9) syst = 0.00197499;
      if (x >= 9 && x < 12) syst = 0.000842135;
      if (x >= 12 && x < 20) syst = 0.000789339;
    }
    if (fabs(eta) >= 2.1 && fabs(eta) < 2.4) {
      // syst uncertainties
      if (x >= 1.8 && x < 2.2) syst = 0.0234659;
      if (x >= 2.2 && x < 2.7) syst = 0.00575045;
      if (x >= 2.7 && x < 3.2) syst = 0.00231199;
      if (x >= 3.2 && x < 3.7) syst = 0.00333113;
      if (x >= 3.7 && x < 4.7) syst = 0.00183657;
      if (x >= 4.7 && x < 8) syst = 0.00226061;
      if (x >= 8 && x < 11) syst = 2.45089e-07;
      if (x >= 11 && x < 14) syst = 0.00132322;
      if (x >= 14 && x < 20) syst = 1.46346e-07;
    }
    double syst_factor = 0;
    if (idx == -1) syst_factor = syst;
    if (idx == -2) syst_factor = -1*syst;
    return ((num+systfactor)/den);
  }
}

///////////////////////////////////////////////////
//              T R G     P b P b                //
///////////////////////////////////////////////////

double tnp_weight_trg_pbpb(double pt, double eta, int filterId,int idx) {
  double x = pt;
  double num=1,den=1;
  if (idx == 0 || idx<0 ) { //nominal or syst up/down
    if (filterId==0) { //L2 Jpsi
      // SF for 0 < |eta| < 1.2
      if (fabs(eta) >= 0 && fabs(eta) < 1.2) {
	if (x >= 3.5 && x <4) {num = 0.663241; den = 0.612464;}
	else if (x >= 4 && x <4.5) {num = 0.85917; den = 0.842014;}
	else if (x >= 4.5 && x <5) {num = 0.916521; den = 0.900241;}
	else if (x >= 5 && x <5.5) {num = 0.934641; den = 0.919918;}
	else if (x >= 5.5 && x <6.5) {num = 0.947297; den = 0.940729;}
	else if (x >= 6.5 && x <8) {num = 0.949896; den = 0.95601;}
	else if (x >= 8 && x <10.5) {num = 0.950506; den = 0.96243;}
	else if (x >= 10.5 && x <14) {num = 0.947321; den = 0.964831;}
	else if (x >= 14 && x <18) {num = 0.940314; den = 0.966093;}
	else {num = 0.943817; den = 0.957341;}
      }
      // SF for 1.2 < |eta| < 1.8
      if (fabs(eta) >= 1.2 && fabs(eta) < 1.8) {
	if (x >= 2.37 && x <3) {num = 0.698036; den = 0.656794;}
	else if (x >= 3 && x <3.5) {num = 0.829209; den = 0.793366;}
	else if (x >= 3.5 && x <4) {num = 0.900878; den = 0.867213;}
	else if (x >= 4 && x <4.5) {num = 0.917489; den = 0.917832;}
	else if (x >= 4.5 && x <5) {num = 0.935786; den = 0.936854;}
	else if (x >= 5 && x <6) {num = 0.940635; den = 0.950382;}
	else if (x >= 6 && x <7.5) {num = 0.942288; den = 0.955739;}
	else if (x >= 7.5 && x <10) {num = 0.953266; den = 0.959009;}
	else if (x >= 10 && x <15) {num = 0.948259; den = 0.959592;}
	else {num = 0.913688; den = 0.954037;}
      }
      // SF for 1.8 < |eta| < 2.1
      if (fabs(eta) >= 1.8 && fabs(eta) < 2.1) {
	if (x >= 1.8 && x <2) {num = 0.641279; den = 0.556324;}
	else if (x >= 2 && x <2.5) {num = 0.746463; den = 0.740273;}
	else if (x >= 2.5 && x <3) {num = 0.882257; den = 0.893319;}
	else if (x >= 3 && x <3.5) {num = 0.908732; den = 0.927004;}
	else if (x >= 3.5 && x <4) {num = 0.918071; den = 0.943802;}
	else if (x >= 4 && x <4.5) {num = 0.907847; den = 0.946961;}
	else if (x >= 4.5 && x <5.5) {num = 0.930721; den = 0.954231;}
	else if (x >= 5.5 && x <6.5) {num = 0.892041; den = 0.952605;}
	else if (x >= 6.5 && x <8) {num = 0.917612; den = 0.946287;}
	else if (x >= 8 && x <9.5) {num = 0.914016; den = 0.940696;}
	else if (x >= 9.5 && x <13) {num = 0.915476; den = 0.936928;}
	else {num = 0.905898; den = 0.924578;}
      }
      // SF for 2.1 < |eta| < 2.4
      if (fabs(eta) >= 2.1 && fabs(eta) < 2.4) {
	if (x >= 1.8 && x <2.2) {num = 0.789011; den = 0.794511;}
	else if (x >= 2.2 && x <2.7) {num = 0.854198; den = 0.867878;}
	else if (x >= 2.7 && x <3.2) {num = 0.878207; den = 0.893527;}
	else if (x >= 3.2 && x <3.7) {num = 0.877411; den = 0.911546;}
	else if (x >= 3.7 && x <4.7) {num = 0.885503; den = 0.912297;}
	else if (x >= 4.7 && x <6.5) {num = 0.912669; den = 0.928676;}
	else if (x >= 6.5 && x <8.5) {num = 0.900634; den = 0.922926;}
	else if (x >= 8.5 && x <11) {num = 0.869202; den = 0.916807;}
	else {num = 0.891181; den = 0.915654;}
      }

      if (fabs(eta) >= 0 && fabs(eta) < 1.2) {
	// syst uncertainties
	if (x >= 3.5 && x < 4) syst = 0.00136539;
	if (x >= 4 && x < 4.5) syst = 0.00105145;
	if (x >= 4.5 && x < 5) syst = 0.00132265;
	if (x >= 5 && x < 5.5) syst = 0.000788367;
	if (x >= 5.5 && x < 6.5) syst = 0.000562329;
	if (x >= 6.5 && x < 8) syst = 0.000155103;
	if (x >= 8 && x < 10.5) syst = 0.000158629;
	if (x >= 10.5 && x < 14) syst = 0.000280705;
	if (x >= 14 && x < 18) syst = 0.00108834;
	if (x >= 18 && x < 30) syst = 0.00305146;
      }
      if (fabs(eta) >= 1.2 && fabs(eta) < 1.8) {
	// syst uncertainties
	if (x >= 2.37 && x < 3) syst = 0.00329732;
	if (x >= 3 && x < 3.5) syst = 0.00520027;
	if (x >= 3.5 && x < 4) syst = 0.00240912;
	if (x >= 4 && x < 4.5) syst = 0.00222157;
	if (x >= 4.5 && x < 5) syst = 0.0017746;
	if (x >= 5 && x < 6) syst = 0.00167846;
	if (x >= 6 && x < 7.5) syst = 0.000384188;
	if (x >= 7.5 && x < 10) syst = 0.00184184;
	if (x >= 10 && x < 15) syst = 0.000586472;
	if (x >= 15 && x < 30) syst = 0.00495382;
      }
      if (fabs(eta) >= 1.8 && fabs(eta) < 2.1) {
	// syst uncertainties
	if (x >= 1.8 && x < 2) syst = 0.0133628;
	if (x >= 2 && x < 2.5) syst = 0.0347588;
	if (x >= 2.5 && x < 3) syst = 0.00227196;
	if (x >= 3 && x < 3.5) syst = 0.00511758;
	if (x >= 3.5 && x < 4) syst = 0.00466125;
	if (x >= 4 && x < 4.5) syst = 0.0105296;
	if (x >= 4.5 && x < 5.5) syst = 0.00242737;
	if (x >= 5.5 && x < 6.5) syst = 0.00472684;
	if (x >= 6.5 && x < 8) syst = 0.00762573;
	if (x >= 8 && x < 9.5) syst = 0.00627021;
	if (x >= 9.5 && x < 13) syst = 0.00231563;
	if (x >= 13 && x < 20) syst = 0.019257;
      }
      if (fabs(eta) >= 2.1 && fabs(eta) < 2.4) {
	// syst uncertainties
	if (x >= 1.8 && x < 2.2) syst = 0.0690381;
	if (x >= 2.2 && x < 2.7) syst = 0.0073301;
	if (x >= 2.7 && x < 3.2) syst = 0.00969524;
	if (x >= 3.2 && x < 3.7) syst = 0.00401152;
	if (x >= 3.7 && x < 4.7) syst = 0.0131915;
	if (x >= 4.7 && x < 6.5) syst = 0.00669816;
	if (x >= 6.5 && x < 8.5) syst = 0.00311553;
	if (x >= 8.5 && x < 11) syst = 0.00999295;
	if (x >= 11 && x < 20) syst = 0.0151298;
      }
    }
    if (filterId==1) { //L3 Jpsi
      // SF for 0 < |eta| < 1.2
      if (fabs(eta) >= 0 && fabs(eta) < 1.2) {
	if (x >= 3.5 && x <4) {num = 0.0981413; den = 0.071216;}
	else if (x >= 4 && x <4.5) {num = 0.309366; den = 0.234954;}
	else if (x >= 4.5 && x <5) {num = 0.49696; den = 0.427459;}
	else if (x >= 5 && x <5.5) {num = 0.646567; den = 0.569803;}
	else if (x >= 5.5 && x <6.5) {num = 0.717727; den = 0.665688;}
	else if (x >= 6.5 && x <8) {num = 0.770814; den = 0.736851;}
	else if (x >= 8 && x <10.5) {num = 0.791509; den = 0.777511;}
	else if (x >= 10.5 && x <14) {num = 0.826768; den = 0.814073;}
	else if (x >= 14 && x <18) {num = 0.799276; den = 0.820805;}
	else {num = 0.844468; den = 0.83657;}
      }
      // SF for 1.2 < |eta| < 1.8
      if (fabs(eta) >= 1.2 && fabs(eta) < 1.8) {
	if (x >= 2.37 && x <3) {num = 0.331992; den = 0.302908;}
	else if (x >= 3 && x <3.5) {num = 0.429327; den = 0.424718;}
	else if (x >= 3.5 && x <4) {num = 0.543359; den = 0.527324;}
	else if (x >= 4 && x <4.5) {num = 0.590264; den = 0.603494;}
	else if (x >= 4.5 && x <5) {num = 0.638602; den = 0.645253;}
	else if (x >= 5 && x <6) {num = 0.671782; den = 0.678571;}
	else if (x >= 6 && x <7.5) {num = 0.683073; den = 0.719277;}
	else if (x >= 7.5 && x <10) {num = 0.746848; den = 0.753451;}
	else if (x >= 10 && x <15) {num = 0.772519; den = 0.800301;}
	else {num = 0.768513; den = 0.831634;}
      }
      // SF for 1.8 < |eta| < 2.1
      if (fabs(eta) >= 1.8 && fabs(eta) < 2.1) {
	if (x >= 1.8 && x <2) {num = 0.0302057; den = 0.0291672;}
	else if (x >= 2 && x <2.5) {num = 0.173305; den = 0.159501;}
	else if (x >= 2.5 && x <3) {num = 0.470274; den = 0.464604;}
	else if (x >= 3 && x <3.5) {num = 0.661007; den = 0.654318;}
	else if (x >= 3.5 && x <4) {num = 0.707769; den = 0.711729;}
	else if (x >= 4 && x <4.5) {num = 0.726282; den = 0.741631;}
	else if (x >= 4.5 && x <5.5) {num = 0.763392; den = 0.796057;}
	else if (x >= 5.5 && x <6.5) {num = 0.767094; den = 0.82346;}
	else if (x >= 6.5 && x <8) {num = 0.810425; den = 0.833902;}
	else if (x >= 8 && x <9.5) {num = 0.819571; den = 0.840655;}
	else if (x >= 9.5 && x <13) {num = 0.829677; den = 0.856559;}
	else {num = 0.862606; den = 0.873057;}
      }
      // SF for 2.1 < |eta| < 2.4
      if (fabs(eta) >= 2.1 && fabs(eta) < 2.4) {
	if (x >= 1.8 && x <2.2) {num = 0.0980329; den = 0.092124;}
	else if (x >= 2.2 && x <2.7) {num = 0.264092; den = 0.248237;}
	else if (x >= 2.7 && x <3.2) {num = 0.417324; den = 0.407684;}
	else if (x >= 3.2 && x <3.7) {num = 0.486753; den = 0.49461;}
	else if (x >= 3.7 && x <4.7) {num = 0.569753; den = 0.574351;}
	else if (x >= 4.7 && x <6.5) {num = 0.674727; den = 0.651274;}
	else if (x >= 6.5 && x <8.5) {num = 0.720956; den = 0.710909;}
	else if (x >= 8.5 && x <11) {num = 0.714358; den = 0.74928;}
	else {num = 0.748962; den = 0.778156;}
      }

      if (fabs(eta) >= 0 && fabs(eta) < 1.2) {
	// syst uncertainties
	if (x >= 3.5 && x < 4) syst = 0.000650706;
	if (x >= 4 && x < 4.5) syst = 0.00108325;
	if (x >= 4.5 && x < 5) syst = 0.00298052;
	if (x >= 5 && x < 5.5) syst = 0.00341277;
	if (x >= 5.5 && x < 6.5) syst = 0.000613358;
	if (x >= 6.5 && x < 8) syst = 0.000661917;
	if (x >= 8 && x < 10.5) syst = 0.000756817;
	if (x >= 10.5 && x < 14) syst = 0.000783331;
	if (x >= 14 && x < 18) syst = 0.00218267;
	if (x >= 18 && x < 30) syst = 0.00267133;
      }
      if (fabs(eta) >= 1.2 && fabs(eta) < 1.8) {
	// syst uncertainties
	if (x >= 2.37 && x < 3) syst = 0.00235318;
	if (x >= 3 && x < 3.5) syst = 0.0041557;
	if (x >= 3.5 && x < 4) syst = 0.00434833;
	if (x >= 4 && x < 4.5) syst = 0.00151395;
	if (x >= 4.5 && x < 5) syst = 0.00325726;
	if (x >= 5 && x < 6) syst = 0.00151752;
	if (x >= 6 && x < 7.5) syst = 0.0019946;
	if (x >= 7.5 && x < 10) syst = 0.00321667;
	if (x >= 10 && x < 15) syst = 0.00350192;
	if (x >= 15 && x < 30) syst = 0.00441023;
      }
      if (fabs(eta) >= 1.8 && fabs(eta) < 2.1) {
	// syst uncertainties
	if (x >= 1.8 && x < 2) syst = 0.0108482;
	if (x >= 2 && x < 2.5) syst = 0.00318395;
	if (x >= 2.5 && x < 3) syst = 0.00449944;
	if (x >= 3 && x < 3.5) syst = 0.00272957;
	if (x >= 3.5 && x < 4) syst = 0.00779276;
	if (x >= 4 && x < 4.5) syst = 0.00622458;
	if (x >= 4.5 && x < 5.5) syst = 0.00114197;
	if (x >= 5.5 && x < 6.5) syst = 0.0077565;
	if (x >= 6.5 && x < 8) syst = 0.00157525;
	if (x >= 8 && x < 9.5) syst = 0.00373986;
	if (x >= 9.5 && x < 13) syst = 0.00445251;
	if (x >= 13 && x < 20) syst = 0.0284466;
      }
      if (fabs(eta) >= 2.1 && fabs(eta) < 2.4) {
	// syst uncertainties
	if (x >= 1.8 && x < 2.2) syst = 0.0294959;
	if (x >= 2.2 && x < 2.7) syst = 0.00108294;
	if (x >= 2.7 && x < 3.2) syst = 0.0152933;
	if (x >= 3.2 && x < 3.7) syst = 0.00300734;
	if (x >= 3.7 && x < 4.7) syst = 0.00349077;
	if (x >= 4.7 && x < 6.5) syst = 0.0159082;
	if (x >= 6.5 && x < 8.5) syst = 0.00321438;
	if (x >= 8.5 && x < 11) syst = 0.00306389;
	if (x >= 11 && x < 20) syst = 0.0125999;
      }
    }
    if (filterId==2) { //L2 Upsi
      // SF for 0 < |eta| < 1.2
      if (fabs(eta) >= 0 && fabs(eta) < 1.2) {
	if (x >= 3.5 && x <4) {num = 0.687436; den = 0.628026;}
	else if (x >= 4 && x <4.5) {num = 0.879668; den = 0.855425;}
	else if (x >= 4.5 && x <5) {num = 0.936813; den = 0.91093;}
	else if (x >= 5 && x <5.5) {num = 0.948744; den = 0.930006;}
	else if (x >= 5.5 && x <6.5) {num = 0.964058; den = 0.95091;}
	else if (x >= 6.5 && x <8) {num = 0.967607; den = 0.967695;}
	else if (x >= 8 && x <10.5) {num = 0.977261; den = 0.975624;}
	else if (x >= 10.5 && x <14) {num = 0.975199; den = 0.979933;}
	else if (x >= 14 && x <18) {num = 0.978416; den = 0.983164;}
	else {num = 0.986566; den = 0.984365;}
      }
      // SF for 1.2 < |eta| < 1.8
      if (fabs(eta) >= 1.2 && fabs(eta) < 1.8) {
	if (x >= 2.37 && x <3) {num = 0.707798; den = 0.663284;}
	else if (x >= 3 && x <3.5) {num = 0.841787; den = 0.79966;}
	else if (x >= 3.5 && x <4) {num = 0.915148; den = 0.874984;}
	else if (x >= 4 && x <4.5) {num = 0.932092; den = 0.925267;}
	else if (x >= 4.5 && x <5) {num = 0.95135; den = 0.943497;}
	else if (x >= 5 && x <6) {num = 0.968164; den = 0.958147;}
	else if (x >= 6 && x <7.5) {num = 0.962352; den = 0.96425;}
	else if (x >= 7.5 && x <10) {num = 0.979864; den = 0.969778;}
	else if (x >= 10 && x <15) {num = 0.983282; den = 0.973169;}
	else {num = 0.985422; den = 0.979848;}
      }
      // SF for 1.8 < |eta| < 2.1
      if (fabs(eta) >= 1.8 && fabs(eta) < 2.1) {
	if (x >= 1.8 && x <2) {num = 0.651185; den = 0.562127;}
	else if (x >= 2 && x <2.5) {num = 0.75568; den = 0.744834;}
	else if (x >= 2.5 && x <3) {num = 0.895072; den = 0.898086;}
	else if (x >= 3 && x <3.5) {num = 0.911965; den = 0.932775;}
	else if (x >= 3.5 && x <4) {num = 0.933577; den = 0.949087;}
	else if (x >= 4 && x <4.5) {num = 0.92098; den = 0.952348;}
	else if (x >= 4.5 && x <5.5) {num = 0.945015; den = 0.959924;}
	else if (x >= 5.5 && x <6.5) {num = 0.915225; den = 0.961517;}
	else if (x >= 6.5 && x <8) {num = 0.942614; den = 0.958878;}
	else if (x >= 8 && x <9.5) {num = 0.943992; den = 0.95865;}
	else if (x >= 9.5 && x <13) {num = 0.953176; den = 0.956512;}
	else {num = 0.9711; den = 0.959808;}
      }
      // SF for 2.1 < |eta| < 2.4
      if (fabs(eta) >= 2.1 && fabs(eta) < 2.4) {
	if (x >= 1.8 && x <2.2) {num = 0.80688; den = 0.804533;}
	else if (x >= 2.2 && x <2.7) {num = 0.864384; den = 0.87583;}
	else if (x >= 2.7 && x <3.2) {num = 0.892179; den = 0.904052;}
	else if (x >= 3.2 && x <3.7) {num = 0.896585; den = 0.926574;}
	else if (x >= 3.7 && x <4.7) {num = 0.910998; den = 0.928332;}
	else if (x >= 4.7 && x <6.5) {num = 0.938687; den = 0.949857;}
	else if (x >= 6.5 && x <8.5) {num = 0.941825; den = 0.954442;}
	else if (x >= 8.5 && x <11) {num = 0.931535; den = 0.959109;}
	else {num = 0.969056; den = 0.967084;}
      }

      if (fabs(eta) >= 0 && fabs(eta) < 1.2) {
	// syst uncertainties
	if (x >= 3.5 && x < 4) syst = 0.00119995;
	if (x >= 4 && x < 4.5) syst = 0.000801484;
	if (x >= 4.5 && x < 5) syst = 0.00142786;
	if (x >= 5 && x < 5.5) syst = 0.000859141;
	if (x >= 5.5 && x < 6.5) syst = 0.000855793;
	if (x >= 6.5 && x < 8) syst = 0.000338442;
	if (x >= 8 && x < 10.5) syst = 0.000905661;
	if (x >= 10.5 && x < 14) syst = 0.000193737;
	if (x >= 14 && x < 18) syst = 0.000621028;
	if (x >= 18 && x < 30) syst = 0.0029276;
      }
      if (fabs(eta) >= 1.2 && fabs(eta) < 1.8) {
	// syst uncertainties
	if (x >= 2.37 && x < 3) syst = 0.00301699;
	if (x >= 3 && x < 3.5) syst = 0.0051637;
	if (x >= 3.5 && x < 4) syst = 0.00271564;
	if (x >= 4 && x < 4.5) syst = 0.00128082;
	if (x >= 4.5 && x < 5) syst = 0.00105614;
	if (x >= 5 && x < 6) syst = 0.00120191;
	if (x >= 6 && x < 7.5) syst = 0.000729975;
	if (x >= 7.5 && x < 10) syst = 0.00139352;
	if (x >= 10 && x < 15) syst = 0.00151879;
	if (x >= 15 && x < 30) syst = 0.00138277;
      }
      if (fabs(eta) >= 1.8 && fabs(eta) < 2.1) {
	// syst uncertainties
	if (x >= 1.8 && x < 2) syst = 0.0234362;
	if (x >= 2 && x < 2.5) syst = 0.00781699;
	if (x >= 2.5 && x < 3) syst = 0.0020642;
	if (x >= 3 && x < 3.5) syst = 0.00494294;
	if (x >= 3.5 && x < 4) syst = 0.00372959;
	if (x >= 4 && x < 4.5) syst = 0.0101533;
	if (x >= 4.5 && x < 5.5) syst = 0.00248577;
	if (x >= 5.5 && x < 6.5) syst = 0.00480156;
	if (x >= 6.5 && x < 8) syst = 0.00535204;
	if (x >= 8 && x < 9.5) syst = 0.00407749;
	if (x >= 9.5 && x < 13) syst = 0.000734987;
	if (x >= 13 && x < 20) syst = 0.0152108;
      }
      if (fabs(eta) >= 2.1 && fabs(eta) < 2.4) {
	// syst uncertainties
	if (x >= 1.8 && x < 2.2) syst = 0.0547508;
	if (x >= 2.2 && x < 2.7) syst = 0.0439035;
	if (x >= 2.7 && x < 3.2) syst = 0.0100721;
	if (x >= 3.2 && x < 3.7) syst = 0.00486924;
	if (x >= 3.7 && x < 4.7) syst = 0.0164241;
	if (x >= 4.7 && x < 6.5) syst = 0.0045128;
	if (x >= 6.5 && x < 8.5) syst = 0.00615735;
	if (x >= 8.5 && x < 11) syst = 0.00521994;
	if (x >= 11 && x < 20) syst = 0.00496602;
      }
    }
    if (filterId==3) { //L3 Upsi
      // SF for 0 < |eta| < 1.2
      if (fabs(eta) >= 0 && fabs(eta) < 1.2) {
	if (x >= 3.5 && x <4) {num = 0.0981413; den = 0.0714076;}
	else if (x >= 4 && x <4.5) {num = 0.309591; den = 0.234967;}
	else if (x >= 4.5 && x <5) {num = 0.49696; den = 0.427491;}
	else if (x >= 5 && x <5.5) {num = 0.646567; den = 0.569805;}
	else if (x >= 5.5 && x <6.5) {num = 0.717727; den = 0.665698;}
	else if (x >= 6.5 && x <8) {num = 0.771046; den = 0.736859;}
	else if (x >= 8 && x <10.5) {num = 0.792067; den = 0.777534;}
	else if (x >= 10.5 && x <14) {num = 0.826589; den = 0.814236;}
	else if (x >= 14 && x <18) {num = 0.800339; den = 0.820918;}
	else {num = 0.846856; den = 0.837225;}
      }
      // SF for 1.2 < |eta| < 1.8
      if (fabs(eta) >= 1.2 && fabs(eta) < 1.8) {
	if (x >= 2.37 && x <3) {num = 0.307823; den = 0.284114;}
	else if (x >= 3 && x <3.5) {num = 0.429139; den = 0.424849;}
	else if (x >= 3.5 && x <4) {num = 0.54449; den = 0.527662;}
	else if (x >= 4 && x <4.5) {num = 0.591156; den = 0.604174;}
	else if (x >= 4.5 && x <5) {num = 0.639967; den = 0.645913;}
	else if (x >= 5 && x <6) {num = 0.673449; den = 0.679156;}
	else if (x >= 6 && x <7.5) {num = 0.685635; den = 0.720417;}
	else if (x >= 7.5 && x <10) {num = 0.749011; den = 0.754465;}
	else if (x >= 10 && x <15) {num = 0.773253; den = 0.801728;}
	else {num = 0.773038; den = 0.833024;}
      }
      // SF for 1.8 < |eta| < 2.1
      if (fabs(eta) >= 1.8 && fabs(eta) < 2.1) {
	if (x >= 1.8 && x <2) {num = 0.00155461; den = 0.000463755;}
	else if (x >= 2 && x <2.5) {num = 0.00555387; den = 0.00858885;}
	else if (x >= 2.5 && x <3) {num = 0.451703; den = 0.447277;}
	else if (x >= 3 && x <3.5) {num = 0.655861; den = 0.650893;}
	else if (x >= 3.5 && x <4) {num = 0.706533; den = 0.710335;}
	else if (x >= 4 && x <4.5) {num = 0.726282; den = 0.741482;}
	else if (x >= 4.5 && x <5.5) {num = 0.764391; den = 0.796199;}
	else if (x >= 5.5 && x <6.5) {num = 0.769821; den = 0.824468;}
	else if (x >= 6.5 && x <8) {num = 0.811763; den = 0.834174;}
	else if (x >= 8 && x <9.5) {num = 0.819571; den = 0.841319;}
	else if (x >= 9.5 && x <13) {num = 0.829677; den = 0.857122;}
	else {num = 0.874981; den = 0.874474;}
      }
      // SF for 2.1 < |eta| < 2.4
      if (fabs(eta) >= 2.1 && fabs(eta) < 2.4) {
	if (x >= 1.8 && x <2.2) {num = 0.00366548; den = 0.000413051;}
	else if (x >= 2.2 && x <2.7) {num = 0.116176; den = 0.109916;}
	else if (x >= 2.7 && x <3.2) {num = 0.413123; den = 0.401827;}
	else if (x >= 3.2 && x <3.7) {num = 0.482035; den = 0.491334;}
	else if (x >= 3.7 && x <4.7) {num = 0.568894; den = 0.573223;}
	else if (x >= 4.7 && x <6.5) {num = 0.675048; den = 0.651616;}
	else if (x >= 6.5 && x <8.5) {num = 0.722882; den = 0.711847;}
	else if (x >= 8.5 && x <11) {num = 0.714358; den = 0.750096;}
	else {num = 0.753355; den = 0.779864;}
      }

      if (fabs(eta) >= 0 && fabs(eta) < 1.2) {
	// syst uncertainties
	if (x >= 3.5 && x < 4) syst = 0.000650706;
	if (x >= 4 && x < 4.5) syst = 0.0010869;
	if (x >= 4.5 && x < 5) syst = 0.00298052;
	if (x >= 5 && x < 5.5) syst = 0.00341277;
	if (x >= 5.5 && x < 6.5) syst = 0.000613358;
	if (x >= 6.5 && x < 8) syst = 0.000658119;
	if (x >= 8 && x < 10.5) syst = 0.000756756;
	if (x >= 10.5 && x < 14) syst = 0.000662617;
	if (x >= 14 && x < 18) syst = 0.00220571;
	if (x >= 18 && x < 30) syst = 0.00215326;
      }
      if (fabs(eta) >= 1.2 && fabs(eta) < 1.8) {
	// syst uncertainties
	if (x >= 2.37 && x < 3) syst = 0.00406324;
	if (x >= 3 && x < 3.5) syst = 0.00422745;
	if (x >= 3.5 && x < 4) syst = 0.00493964;
	if (x >= 4 && x < 4.5) syst = 0.0015019;
	if (x >= 4.5 && x < 5) syst = 0.00349953;
	if (x >= 5 && x < 6) syst = 0.00165421;
	if (x >= 6 && x < 7.5) syst = 0.00195686;
	if (x >= 7.5 && x < 10) syst = 0.00305233;
	if (x >= 10 && x < 15) syst = 0.00341103;
	if (x >= 15 && x < 30) syst = 0.00425449;
      }
      if (fabs(eta) >= 1.8 && fabs(eta) < 2.1) {
	// syst uncertainties
	if (x >= 1.8 && x < 2) syst = 0.00154707;
	if (x >= 2 && x < 2.5) syst = 0.00239348;
	if (x >= 2.5 && x < 3) syst = 0.00578521;
	if (x >= 3 && x < 3.5) syst = 0.0019864;
	if (x >= 3.5 && x < 4) syst = 0.00826595;
	if (x >= 4 && x < 4.5) syst = 0.00622458;
	if (x >= 4.5 && x < 5.5) syst = 0.00155048;
	if (x >= 5.5 && x < 6.5) syst = 0.00738518;
	if (x >= 6.5 && x < 8) syst = 0.00155169;
	if (x >= 8 && x < 9.5) syst = 0.00373986;
	if (x >= 9.5 && x < 13) syst = 0.00445251;
	if (x >= 13 && x < 20) syst = 0.028681;
      }
      if (fabs(eta) >= 2.1 && fabs(eta) < 2.4) {
	// syst uncertainties
	if (x >= 1.8 && x < 2.2) syst = 0.000519911;
	if (x >= 2.2 && x < 2.7) syst = 0.0288676;
	if (x >= 2.7 && x < 3.2) syst = 0.013137;
	if (x >= 3.2 && x < 3.7) syst = 0.00153582;
	if (x >= 3.7 && x < 4.7) syst = 0.00361851;
	if (x >= 4.7 && x < 6.5) syst = 0.0155374;
	if (x >= 6.5 && x < 8.5) syst = 0.00321391;
	if (x >= 8.5 && x < 11) syst = 0.00306389;
	if (x >= 11 && x < 20) syst = 0.0199929;
      }
    }
    double syst_factor = 0;
    if (idx == -1) syst_factor = syst;
    if (idx == -2) syst_factor = -1*syst;
    return ((num+systfactor)/den);
  }
}

///////////////////////////////////////////////////
//              T R K     P b P b                //
///////////////////////////////////////////////////

double tnp_weight_trk_pbpb(double eta, int idx) {
  double x = eta;
  double num=1,den=1;
  if (idx == 0 || idx<0 ) { //nominal or syst up/down
    //SF in eta bins
    if (x >= -2.4 && x < -1.6) {num = 0.994498; den = 0.998413;}
    if (x >= -1.6 && x < -1.2) {num = 0.973539; den = 0.967322;}
    if (x >= -1.2 && x < -0.9) {num = 0.964465; den = 0.970816;}
    if (x >= -0.9 && x < -0.6) {num = 0.96081; den = 0.974407;}
    if (x >= -0.6 && x < -0.3) {num = 0.964464; den = 0.97802;}
    if (x >= -0.3 && x < 0.3) {num = 0.963862; den = 0.966583;}
    if (x >= 0.3 && x < 0.6) {num = 0.956897; den = 0.967248;}
    if (x >= 0.6 && x < 0.9) {num = 0.964172; den = 0.966882;}
    if (x >= 0.9 && x < 1.2) {num = 0.961874; den = 0.955987;}
    if (x >= 1.2 && x < 1.6) {num = 0.964754; den = 0.964653;}
    if (x >= 1.6 && x < 2.4) {num = 0.999937; den = 0.998771;}

    // syst uncertainties
    if (x >= -2.4 && x < -1.6) syst = 0.00129036;
    if (x >= -1.6 && x < -1.2) syst = 0.00376932;
    if (x >= -1.2 && x < -0.9) syst = 0.00125496;
    if (x >= -0.9 && x < -0.6) syst = 0.00240006;
    if (x >= -0.6 && x < -0.3) syst = 0.00228604;
    if (x >= -0.3 && x < 0.3) syst = 0.00494002;
    if (x >= 0.3 && x < 0.6) syst = 0.00529974;
    if (x >= 0.6 && x < 0.9) syst = 0.0023114;
    if (x >= 0.9 && x < 1.2) syst = 0.012059;
    if (x >= 1.2 && x < 1.6) syst = 0.00278996;
    if (x >= 1.6 && x < 2.4) syst = 0.00104774;

    double syst_factor = 0;
    if (idx == -1) syst_factor = syst;
    if (idx == -2) syst_factor = -1*syst;
    return ((num+systfactor)/den);
  }
}

#endif
