#ifndef tnp_weight_h
#define tnp_weight_h

#include "TMath.h"

// IN THIS FILE YOU WILL FIND:
// ++++++++++++++
//
// - ALL: (tnp_weight_pp, tnp_weight_pbpb)
//   * idx = 0:  nominal
//   * idx = 1..100: toy variations, stat. only
//   * idx = -1: syst variation, +1 sigma
//   * idx = -2: syst variation, -1 sigma
//
// But also all the details entering in the computation (NOT FOR THE END USER)
// - Trigger: (tnp_weight_trg_*)
//   * idx = 0:  nominal
//   * idx = 1..100: toy variations, stat. only
//   * idx = -1: syst variation, "new_MAX", +1 sigma
//   * idx = -2: syst variation, "new_MAX", -1 sigma
//   * idx = -10: binned
// - MuID, STA: (tnp_weight_muid_*, tnp_weight_sta_pp)
//   * same organisation. BUT these SF are for systematics only.

// M A I N   F U N C T I O N S
// +++++++++++++++++++++++++++
double tnp_weight_pbpb(double x, double eta, int idx);
double tnp_weight_pp(double x, double eta, int idx);

// THE INDIVIDUAL SFs
// ++++++++++++++++++
double tnp_weight_trg_pbpb(double x, double eta, int idx);
double tnp_weight_trg_pp(double x, double eta, int idx);
double tnp_weight_muid_pbpb(double x, double eta, int idx=0);
double tnp_weight_muid_pp(double x, double eta, int idx=0);
double tnp_weight_sta_pp(double x, double eta, int idx=0);


///////////////////////////////////////////////////
//      A L L - I N - O N E    P b P b           //
///////////////////////////////////////////////////
double tnp_weight_pbpb(double x, double eta, int idx) {
   if (idx==0 || idx==-10) { // nominal
      return tnp_weight_trg_pbpb(x,eta,idx);
   } else if (idx==-1) { // +1 sigma syst
      double sf0 = tnp_weight_trg_pbpb(x,eta,0);
      double sf1 = tnp_weight_trg_pbpb(x,eta,-1);
      double sfb = max(sf0,tnp_weight_trg_pbpb(x,eta,-10));
      double sfid1 = tnp_weight_muid_pbpb(x,eta,-1);
      double sfidb = max(sfid1,tnp_weight_muid_pbpb(x,eta,-10));
      double sfsta1 = tnp_weight_sta_pp(x,eta,-1);
      double sfstab = max(sfsta1,tnp_weight_sta_pp(x,eta,-10));
      return sf0*(1+sqrt(pow(sf1-sf0,2)+pow(sfb-sf0,2)
            // +pow(sfid1-1,2)
            +pow(sfidb-1,2)
            // +pow(sfsta1-1,2)
            +pow(sfstab-1,2)
            ));
   } else if (idx==-2) { // -1 sigma syst
      double sf0 = tnp_weight_trg_pbpb(x,eta,0);
      double sf1 = tnp_weight_trg_pbpb(x,eta,-2);
      double sfb = min(sf0,tnp_weight_trg_pbpb(x,eta,-10));
      double sfid1 = tnp_weight_muid_pbpb(x,eta,-2);
      double sfidb = min(sfid1,tnp_weight_muid_pbpb(x,eta,-10));
      double sfsta1 = tnp_weight_sta_pp(x,eta,-2);
      double sfstab = min(sfsta1,tnp_weight_sta_pp(x,eta,-10));
      return sf0*(1-sqrt(pow(sf1-sf0,2)+pow(sfb-sf0,2)
            // +pow(sfid1-1,2)
            +pow(sfidb-1,2)
            // +pow(sfsta1-1,2)
            +pow(sfstab-1,2)
            ));
   } else if (idx<=25) {
      return tnp_weight_trg_pbpb(x,eta,idx);
   } else if (idx<=50) {
      return tnp_weight_trg_pbpb(x,eta,idx)*tnp_weight_muid_pbpb(x,eta,idx);
   } else if (idx<=75) {
      return tnp_weight_trg_pbpb(x,eta,idx)*tnp_weight_sta_pp(x,eta,idx);
   } else {
      return tnp_weight_trg_pbpb(x,eta,idx)*tnp_weight_muid_pbpb(x,eta,idx)*tnp_weight_sta_pp(x,eta,idx);
   }
}

///////////////////////////////////////////////
//      A L L - I N - O N E    P P           //
///////////////////////////////////////////////
double tnp_weight_pp(double x, double eta, int idx) {
   if (idx==0 || idx==-10) { // nominal
      return tnp_weight_trg_pp(x,eta,idx);
   } else if (idx==-1) { // +1 sigma syst
      double sf0 = tnp_weight_trg_pp(x,eta,0);
      double sf1 = tnp_weight_trg_pp(x,eta,-1);
      double sfb = max(sf0,tnp_weight_trg_pp(x,eta,-10));
      double sfid1 = tnp_weight_muid_pp(x,eta,-1);
      double sfidb = max(sfid1,tnp_weight_muid_pp(x,eta,-10));
      double sfsta1 = tnp_weight_sta_pp(x,eta,-1);
      double sfstab = max(sfsta1,tnp_weight_sta_pp(x,eta,-10));
      return sf0*(1+sqrt(pow(sf1-sf0,2)+pow(sfb-sf0,2)
            +pow(sfid1-1,2)+pow(sfidb-1,2)
            +pow(sfsta1-1,2)+pow(sfstab-1,2)));
   } else if (idx==-2) { // -1 sigma syst
      double sf0 = tnp_weight_trg_pp(x,eta,0);
      double sf1 = tnp_weight_trg_pp(x,eta,-2);
      double sfb = min(sf0,tnp_weight_trg_pp(x,eta,-10));
      double sfid1 = tnp_weight_muid_pp(x,eta,-2);
      double sfidb = min(sfid1,tnp_weight_muid_pp(x,eta,-10));
      double sfsta1 = tnp_weight_sta_pp(x,eta,-2);
      double sfstab = min(sfsta1,tnp_weight_sta_pp(x,eta,-10));
      return sf0*(1-sqrt(pow(sf1-sf0,2)+pow(sfb-sf0,2)
            +pow(sfid1-1,2)+pow(sfidb-1,2)
            +pow(sfsta1-1,2)+pow(sfstab-1,2)));
   } else if (idx<=25) {
      return tnp_weight_trg_pp(x,eta,idx);
   } else if (idx<=50) {
      return tnp_weight_trg_pp(x,eta,idx)*tnp_weight_muid_pp(x,eta,idx);
   } else if (idx<=75) {
      return tnp_weight_trg_pp(x,eta,idx)*tnp_weight_sta_pp(x,eta,idx);
   } else {
      return tnp_weight_trg_pp(x,eta,idx)*tnp_weight_muid_pp(x,eta,idx)*tnp_weight_sta_pp(x,eta,idx);
   }
}

///////////////////////////////////////////////////
//               T R G    P b P b                //
///////////////////////////////////////////////////
double tnp_weight_trg_pbpb(double x, double eta, int idx)
{
   // binned
   if (idx == -10) {
      if (fabs(eta) < 1.2) {
         // 0 < |eta| < 1.2
         if (x<4) return 1.05083;
         else if (x<4.5) return 1.00482;
         else if (x<5) return 0.991942;
         else if (x<5.5) return 0.999019;
         else if (x<6.5) return 0.998047;
         else if (x<8) return 0.982955;
         else if (x<10.5) return 0.994642;
         else if (x<14) return 0.982937;
         else if (x<18) return 0.980605;
         else return 1.00328;
      } else if (fabs(eta) < 1.8) {
         // 1.2 < |eta| < 1.8
         if (x<3) return 1.141;
         else if (x<3.5) return 1.08315;
         else if (x<4) return 1.03487;
         else if (x<4.5) return 1.01835;
         else if (x<5) return 0.997828;
         else if (x<6) return 0.987733;
         else if (x<7.5) return 1.00724;
         else if (x<10) return 0.994324;
         else if (x<15) return 1.01714;
         else return 1.01007;
      } else if (fabs(eta) < 2.1) {
         // 1.8 < |eta| < 2.1
         if (x<2) return 1.45635;
         else if (x<2.5) return 1.23666;
         else if (x<3) return 1.09206;
         else if (x<3.5) return 1.06978;
         else if (x<4) return 1.02001;
         else if (x<4.5) return 1.03328;
         else if (x<5.5) return 1.02344;
         else if (x<6.5) return 1.03221;
         else if (x<8) return 0.979755;
         else if (x<9.5) return 0.9832;
         else if (x<13) return 1.0359;
         else return 0.97688;
      } else {
         // 2.1 < |eta| < 2.4
         if (x<2.2) return 1.27031;
         else if (x<2.7) return 1.15418;
         else if (x<3.2) return 1.06914;
         else if (x<3.7) return 1.04694;
         else if (x<4.7) return 1.06675;
         else if (x<6.5) return 1.04215;
         else if (x<8.5) return 1.02019;
         else if (x<11) return 1.03374;
         else return 1.07708;
      }
   }

   // denominator (from MC)
   double den=1;
   if (fabs(eta)<1.2) den = 0.97701*TMath::Erf((x-2.38691)/1.31574);
   else if (fabs(eta)<1.8) den = 0.94675*TMath::Erf((x-2.29271)/1.19047);
   else if (fabs(eta)<2.1) den = 0.89781*TMath::Erf((x-0.80641)/2.31842);
   else den = 0.87208*TMath::Erf((x-0.63360)/1.99416);

   // numerator (from data)
   double num=1;

   if (fabs(eta)<1.2)
   {
      if (idx==0) num = 0.96859*TMath::Erf((x-1.86137)/1.57333);
      else if (idx == -1   ) num = 0.96934*TMath::Erf((x-1.86313)/1.55954);
      else if (idx == -2   ) num = 0.96786*TMath::Erf((x-1.86663)/1.57798);
      else if (idx == 1   ) num = 0.97220*TMath::Erf((x-0.68242)/2.39776);
      else if (idx == 2   ) num = 0.96885*TMath::Erf((x-2.06374)/1.46946);
      else if (idx == 3   ) num = 0.96628*TMath::Erf((x-1.99454)/1.48976);
      else if (idx == 4   ) num = 0.96903*TMath::Erf((x-2.05862)/1.44175);
      else if (idx == 5   ) num = 0.96828*TMath::Erf((x-1.69241)/1.68223);
      else if (idx == 6   ) num = 0.96664*TMath::Erf((x-1.84564)/1.56131);
      else if (idx == 7   ) num = 0.97196*TMath::Erf((x-1.89639)/1.59681);
      else if (idx == 8   ) num = 0.96775*TMath::Erf((x-1.90964)/1.56506);
      else if (idx == 9   ) num = 0.96701*TMath::Erf((x-2.07249)/1.42218);
      else if (idx == 10  ) num = 0.96758*TMath::Erf((x-2.24322)/1.24312);
      else if (idx == 11  ) num = 0.96434*TMath::Erf((x-1.76470)/1.66288);
      else if (idx == 12  ) num = 0.97217*TMath::Erf((x-1.50141)/1.86413);
      else if (idx == 13  ) num = 0.96988*TMath::Erf((x-2.05018)/1.45612);
      else if (idx == 14  ) num = 0.96816*TMath::Erf((x-1.55670)/1.82452);
      else if (idx == 15  ) num = 0.96473*TMath::Erf((x-2.15182)/1.34965);
      else if (idx == 16  ) num = 0.97441*TMath::Erf((x-0.87068)/2.42192);
      else if (idx == 17  ) num = 0.96730*TMath::Erf((x-1.86952)/1.58975);
      else if (idx == 18  ) num = 0.96938*TMath::Erf((x-2.33178)/1.24227);
      else if (idx == 19  ) num = 0.97152*TMath::Erf((x-1.01588)/2.19496);
      else if (idx == 20  ) num = 0.96818*TMath::Erf((x-2.03238)/1.47533);
      else if (idx == 21  ) num = 0.97003*TMath::Erf((x-1.31970)/2.00786);
      else if (idx == 22  ) num = 0.96844*TMath::Erf((x-2.14262)/1.36264);
      else if (idx == 23  ) num = 0.97174*TMath::Erf((x-1.66324)/1.76821);
      else if (idx == 24  ) num = 0.96475*TMath::Erf((x-2.61641)/0.96294);
      else if (idx == 25  ) num = 0.96945*TMath::Erf((x-1.96163)/1.51640);
      else if (idx == 26  ) num = 0.96596*TMath::Erf((x-2.51843)/1.01968);
      else if (idx == 27  ) num = 0.97182*TMath::Erf((x-1.34291)/2.04292);
      else if (idx == 28  ) num = 0.96863*TMath::Erf((x-1.80088)/1.59445);
      else if (idx == 29  ) num = 0.96562*TMath::Erf((x-1.85628)/1.57174);
      else if (idx == 30  ) num = 0.97149*TMath::Erf((x-1.25275)/2.02267);
      else if (idx == 31  ) num = 0.96800*TMath::Erf((x-1.16419)/2.03537);
      else if (idx == 32  ) num = 0.96567*TMath::Erf((x-1.92222)/1.50817);
      else if (idx == 33  ) num = 0.96846*TMath::Erf((x-2.05640)/1.42841);
      else if (idx == 34  ) num = 0.96960*TMath::Erf((x-1.02677)/2.21714);
      else if (idx == 35  ) num = 0.96744*TMath::Erf((x-1.84682)/1.56258);
      else if (idx == 36  ) num = 0.96905*TMath::Erf((x-1.27446)/2.03285);
      else if (idx == 37  ) num = 0.96981*TMath::Erf((x-1.21539)/2.10635);
      else if (idx == 38  ) num = 0.97227*TMath::Erf((x-1.43724)/1.90706);
      else if (idx == 39  ) num = 0.96527*TMath::Erf((x-2.26238)/1.26417);
      else if (idx == 40  ) num = 0.96588*TMath::Erf((x-1.74047)/1.62838);
      else if (idx == 41  ) num = 0.97303*TMath::Erf((x-2.05165)/1.44574);
      else if (idx == 42  ) num = 0.96872*TMath::Erf((x-1.49195)/1.83047);
      else if (idx == 43  ) num = 0.97314*TMath::Erf((x-1.08069)/2.21919);
      else if (idx == 44  ) num = 0.96384*TMath::Erf((x-2.00338)/1.40617);
      else if (idx == 45  ) num = 0.96519*TMath::Erf((x-2.52126)/1.00854);
      else if (idx == 46  ) num = 0.97054*TMath::Erf((x-1.66028)/1.74479);
      else if (idx == 47  ) num = 0.97420*TMath::Erf((x-1.02555)/2.20491);
      else if (idx == 48  ) num = 0.96606*TMath::Erf((x-1.61424)/1.78328);
      else if (idx == 49  ) num = 0.96764*TMath::Erf((x-1.51521)/1.82161);
      else if (idx == 50  ) num = 0.97195*TMath::Erf((x-1.06257)/2.21002);
      else if (idx == 51  ) num = 0.97055*TMath::Erf((x-1.61494)/1.78469);
      else if (idx == 52  ) num = 0.96670*TMath::Erf((x-2.36340)/1.19428);
      else if (idx == 53  ) num = 0.96992*TMath::Erf((x-1.54537)/1.77335);
      else if (idx == 54  ) num = 0.96967*TMath::Erf((x-1.88416)/1.58906);
      else if (idx == 55  ) num = 0.96974*TMath::Erf((x-2.11529)/1.40003);
      else if (idx == 56  ) num = 0.96406*TMath::Erf((x-2.62453)/0.92872);
      else if (idx == 57  ) num = 0.96689*TMath::Erf((x-1.53479)/1.80108);
      else if (idx == 58  ) num = 0.96813*TMath::Erf((x-2.21323)/1.35774);
      else if (idx == 59  ) num = 0.97106*TMath::Erf((x-1.54930)/1.76601);
      else if (idx == 60  ) num = 0.96423*TMath::Erf((x-1.95907)/1.50410);
      else if (idx == 61  ) num = 0.96930*TMath::Erf((x-1.33853)/1.92124);
      else if (idx == 62  ) num = 0.96498*TMath::Erf((x-1.42071)/1.91352);
      else if (idx == 63  ) num = 0.96474*TMath::Erf((x-2.08557)/1.40885);
      else if (idx == 64  ) num = 0.96872*TMath::Erf((x-1.15552)/2.00911);
      else if (idx == 65  ) num = 0.96577*TMath::Erf((x-2.27128)/1.25865);
      else if (idx == 66  ) num = 0.97023*TMath::Erf((x-2.13485)/1.40311);
      else if (idx == 67  ) num = 0.96968*TMath::Erf((x-1.89762)/1.59839);
      else if (idx == 68  ) num = 0.97091*TMath::Erf((x-1.35985)/2.00688);
      else if (idx == 69  ) num = 0.96638*TMath::Erf((x-1.49899)/1.84060);
      else if (idx == 70  ) num = 0.96831*TMath::Erf((x-2.16703)/1.31999);
      else if (idx == 71  ) num = 0.96879*TMath::Erf((x-2.19541)/1.35264);
      else if (idx == 72  ) num = 0.96393*TMath::Erf((x-1.81291)/1.53774);
      else if (idx == 73  ) num = 0.96796*TMath::Erf((x-1.84917)/1.56368);
      else if (idx == 74  ) num = 0.96939*TMath::Erf((x-1.68146)/1.68299);
      else if (idx == 75  ) num = 0.96803*TMath::Erf((x-1.72499)/1.65927);
      else if (idx == 76  ) num = 0.96870*TMath::Erf((x-1.85842)/1.57117);
      else if (idx == 77  ) num = 0.96828*TMath::Erf((x-1.74760)/1.67636);
      else if (idx == 78  ) num = 0.97064*TMath::Erf((x-1.11443)/2.17887);
      else if (idx == 79  ) num = 0.96288*TMath::Erf((x-2.04989)/1.39129);
      else if (idx == 80  ) num = 0.96998*TMath::Erf((x-1.70891)/1.68305);
      else if (idx == 81  ) num = 0.97054*TMath::Erf((x-2.21671)/1.34494);
      else if (idx == 82  ) num = 0.96795*TMath::Erf((x-2.52571)/1.07716);
      else if (idx == 83  ) num = 0.97430*TMath::Erf((x-1.08618)/2.16423);
      else if (idx == 84  ) num = 0.97414*TMath::Erf((x-1.08249)/2.20265);
      else if (idx == 85  ) num = 0.96836*TMath::Erf((x-1.82504)/1.54366);
      else if (idx == 86  ) num = 0.96901*TMath::Erf((x-1.86514)/1.57647);
      else if (idx == 87  ) num = 0.96142*TMath::Erf((x-2.13986)/1.34664);
      else if (idx == 88  ) num = 0.96499*TMath::Erf((x-2.23478)/1.26678);
      else if (idx == 89  ) num = 0.96774*TMath::Erf((x-1.83814)/1.55635);
      else if (idx == 90  ) num = 0.96772*TMath::Erf((x-2.16838)/1.34425);
      else if (idx == 91  ) num = 0.97023*TMath::Erf((x-1.88892)/1.59164);
      else if (idx == 92  ) num = 0.96593*TMath::Erf((x-1.83388)/1.55283);
      else if (idx == 93  ) num = 0.96747*TMath::Erf((x-1.66498)/1.70099);
      else if (idx == 94  ) num = 0.96667*TMath::Erf((x-1.85033)/1.56688);
      else if (idx == 95  ) num = 0.97162*TMath::Erf((x-1.94503)/1.52424);
      else if (idx == 96  ) num = 0.96896*TMath::Erf((x-1.97393)/1.49615);
      else if (idx == 97  ) num = 0.96648*TMath::Erf((x-2.08178)/1.36789);
      else if (idx == 98  ) num = 0.96547*TMath::Erf((x-1.82265)/1.54430);
      else if (idx == 99  ) num = 0.96643*TMath::Erf((x-2.04637)/1.41923);
      else if (idx == 100 ) num = 0.97157*TMath::Erf((x-1.52176)/1.82833);
   }
   else if (fabs(eta)<1.8)
   {
      if (idx==0) num = 0.94753*TMath::Erf((x-2.29787)/1.01635);
      else if (idx == -1   ) num = 0.94854*TMath::Erf((x-2.28198)/1.02715);
      else if (idx == -2   ) num = 0.94645*TMath::Erf((x-2.31364)/1.00454);
      else if (idx == 1   ) num = 0.93891*TMath::Erf((x-2.23717)/1.06326);
      else if (idx == 2   ) num = 0.95035*TMath::Erf((x-2.26085)/1.03494);
      else if (idx == 3   ) num = 0.94591*TMath::Erf((x-2.27134)/1.03744);
      else if (idx == 4   ) num = 0.94767*TMath::Erf((x-2.31942)/1.01378);
      else if (idx == 5   ) num = 0.94674*TMath::Erf((x-2.36126)/0.91640);
      else if (idx == 6   ) num = 0.94910*TMath::Erf((x-2.33385)/0.94013);
      else if (idx == 7   ) num = 0.94639*TMath::Erf((x-2.36999)/0.88805);
      else if (idx == 8   ) num = 0.95082*TMath::Erf((x-2.23857)/1.07721);
      else if (idx == 9   ) num = 0.94217*TMath::Erf((x-2.14948)/1.16471);
      else if (idx == 10  ) num = 0.94969*TMath::Erf((x-2.12712)/1.24420);
      else if (idx == 11  ) num = 0.95102*TMath::Erf((x-2.20301)/1.21113);
      else if (idx == 12  ) num = 0.94243*TMath::Erf((x-2.31937)/0.97791);
      else if (idx == 13  ) num = 0.94950*TMath::Erf((x-2.29777)/1.01542);
      else if (idx == 14  ) num = 0.94172*TMath::Erf((x-2.33558)/0.95436);
      else if (idx == 15  ) num = 0.94669*TMath::Erf((x-2.31585)/0.98138);
      else if (idx == 16  ) num = 0.94140*TMath::Erf((x-2.34193)/0.95721);
      else if (idx == 17  ) num = 0.94066*TMath::Erf((x-2.27864)/0.98999);
      else if (idx == 18  ) num = 0.94452*TMath::Erf((x-2.42255)/0.85359);
      else if (idx == 19  ) num = 0.94454*TMath::Erf((x-2.29662)/0.97185);
      else if (idx == 20  ) num = 0.95021*TMath::Erf((x-2.31958)/0.98094);
      else if (idx == 21  ) num = 0.93799*TMath::Erf((x-2.35816)/0.96618);
      else if (idx == 22  ) num = 0.94021*TMath::Erf((x-2.38063)/0.86438);
      else if (idx == 23  ) num = 0.94562*TMath::Erf((x-2.30220)/1.02183);
      else if (idx == 24  ) num = 0.94959*TMath::Erf((x-2.18641)/1.18186);
      else if (idx == 25  ) num = 0.94133*TMath::Erf((x-2.34208)/0.91977);
      else if (idx == 26  ) num = 0.94345*TMath::Erf((x-2.33624)/0.95720);
      else if (idx == 27  ) num = 0.94955*TMath::Erf((x-2.32529)/1.01382);
      else if (idx == 28  ) num = 0.94769*TMath::Erf((x-2.40304)/0.94482);
      else if (idx == 29  ) num = 0.94500*TMath::Erf((x-2.23991)/1.09392);
      else if (idx == 30  ) num = 0.94590*TMath::Erf((x-2.24537)/1.07922);
      else if (idx == 31  ) num = 0.94729*TMath::Erf((x-2.34982)/0.92482);
      else if (idx == 32  ) num = 0.94876*TMath::Erf((x-2.32311)/1.08668);
      else if (idx == 33  ) num = 0.94686*TMath::Erf((x-2.35707)/0.93423);
      else if (idx == 34  ) num = 0.95105*TMath::Erf((x-2.27679)/1.07726);
      else if (idx == 35  ) num = 0.94809*TMath::Erf((x-2.30707)/1.03075);
      else if (idx == 36  ) num = 0.94118*TMath::Erf((x-2.40481)/0.83860);
      else if (idx == 37  ) num = 0.94852*TMath::Erf((x-2.22760)/1.14815);
      else if (idx == 38  ) num = 0.94586*TMath::Erf((x-2.17168)/1.15843);
      else if (idx == 39  ) num = 0.94267*TMath::Erf((x-2.24319)/1.06628);
      else if (idx == 40  ) num = 0.94839*TMath::Erf((x-2.14492)/1.18519);
      else if (idx == 41  ) num = 0.94786*TMath::Erf((x-2.28279)/1.02619);
      else if (idx == 42  ) num = 0.95361*TMath::Erf((x-2.21456)/1.12783);
      else if (idx == 43  ) num = 0.95182*TMath::Erf((x-2.41061)/0.88103);
      else if (idx == 44  ) num = 0.94294*TMath::Erf((x-2.38684)/0.87276);
      else if (idx == 45  ) num = 0.94664*TMath::Erf((x-2.35609)/0.94301);
      else if (idx == 46  ) num = 0.95070*TMath::Erf((x-2.34107)/0.94133);
      else if (idx == 47  ) num = 0.94784*TMath::Erf((x-2.25026)/1.08360);
      else if (idx == 48  ) num = 0.94703*TMath::Erf((x-2.17728)/1.20770);
      else if (idx == 49  ) num = 0.94515*TMath::Erf((x-2.41059)/0.88878);
      else if (idx == 50  ) num = 0.94555*TMath::Erf((x-2.29110)/1.00743);
      else if (idx == 51  ) num = 0.95038*TMath::Erf((x-2.28148)/1.05756);
      else if (idx == 52  ) num = 0.94894*TMath::Erf((x-2.28407)/1.06279);
      else if (idx == 53  ) num = 0.94710*TMath::Erf((x-2.28041)/0.98982);
      else if (idx == 54  ) num = 0.95541*TMath::Erf((x-2.21251)/1.08614);
      else if (idx == 55  ) num = 0.94509*TMath::Erf((x-2.40371)/0.93810);
      else if (idx == 56  ) num = 0.94875*TMath::Erf((x-2.29816)/1.01736);
      else if (idx == 57  ) num = 0.94759*TMath::Erf((x-2.22405)/1.12716);
      else if (idx == 58  ) num = 0.93943*TMath::Erf((x-2.28038)/0.99497);
      else if (idx == 59  ) num = 0.94327*TMath::Erf((x-2.32332)/0.94012);
      else if (idx == 60  ) num = 0.95543*TMath::Erf((x-2.23935)/1.16646);
      else if (idx == 61  ) num = 0.94589*TMath::Erf((x-2.34510)/0.93029);
      else if (idx == 62  ) num = 0.94766*TMath::Erf((x-2.25065)/1.06147);
      else if (idx == 63  ) num = 0.94184*TMath::Erf((x-2.28080)/0.99395);
      else if (idx == 64  ) num = 0.94917*TMath::Erf((x-2.26009)/1.08544);
      else if (idx == 65  ) num = 0.94972*TMath::Erf((x-2.41995)/0.85267);
      else if (idx == 66  ) num = 0.94466*TMath::Erf((x-2.48403)/0.71985);
      else if (idx == 67  ) num = 0.94739*TMath::Erf((x-2.32931)/0.94870);
      else if (idx == 68  ) num = 0.94794*TMath::Erf((x-2.32716)/0.95947);
      else if (idx == 69  ) num = 0.94985*TMath::Erf((x-2.39698)/0.89027);
      else if (idx == 70  ) num = 0.94932*TMath::Erf((x-2.43105)/0.84032);
      else if (idx == 71  ) num = 0.94999*TMath::Erf((x-2.35592)/0.93848);
      else if (idx == 72  ) num = 0.94787*TMath::Erf((x-2.31019)/0.99908);
      else if (idx == 73  ) num = 0.94926*TMath::Erf((x-2.27031)/1.03409);
      else if (idx == 74  ) num = 0.94586*TMath::Erf((x-2.29391)/1.01078);
      else if (idx == 75  ) num = 0.94758*TMath::Erf((x-2.24904)/1.08838);
      else if (idx == 76  ) num = 0.94769*TMath::Erf((x-2.33403)/0.94723);
      else if (idx == 77  ) num = 0.94380*TMath::Erf((x-2.27129)/0.97183);
      else if (idx == 78  ) num = 0.95347*TMath::Erf((x-2.30362)/1.02225);
      else if (idx == 79  ) num = 0.94351*TMath::Erf((x-2.32622)/0.95336);
      else if (idx == 80  ) num = 0.94761*TMath::Erf((x-2.31138)/1.03476);
      else if (idx == 81  ) num = 0.95175*TMath::Erf((x-2.15296)/1.16244);
      else if (idx == 82  ) num = 0.94968*TMath::Erf((x-2.22026)/1.12878);
      else if (idx == 83  ) num = 0.94696*TMath::Erf((x-2.15635)/1.15505);
      else if (idx == 84  ) num = 0.94943*TMath::Erf((x-2.31939)/1.00900);
      else if (idx == 85  ) num = 0.95889*TMath::Erf((x-2.18729)/1.15953);
      else if (idx == 86  ) num = 0.95373*TMath::Erf((x-2.16682)/1.17205);
      else if (idx == 87  ) num = 0.94640*TMath::Erf((x-2.25505)/1.09624);
      else if (idx == 88  ) num = 0.94846*TMath::Erf((x-2.28179)/1.07669);
      else if (idx == 89  ) num = 0.94782*TMath::Erf((x-2.33945)/0.97821);
      else if (idx == 90  ) num = 0.95920*TMath::Erf((x-2.14912)/1.25437);
      else if (idx == 91  ) num = 0.94757*TMath::Erf((x-2.26889)/1.09399);
      else if (idx == 92  ) num = 0.95188*TMath::Erf((x-2.19279)/1.17627);
      else if (idx == 93  ) num = 0.94202*TMath::Erf((x-2.29387)/1.01334);
      else if (idx == 94  ) num = 0.94066*TMath::Erf((x-2.34927)/0.85274);
      else if (idx == 95  ) num = 0.94680*TMath::Erf((x-2.42209)/0.83081);
      else if (idx == 96  ) num = 0.94319*TMath::Erf((x-2.32340)/0.92327);
      else if (idx == 97  ) num = 0.94924*TMath::Erf((x-2.17215)/1.18594);
      else if (idx == 98  ) num = 0.95353*TMath::Erf((x-2.25046)/1.09236);
      else if (idx == 99  ) num = 0.94240*TMath::Erf((x-2.37859)/0.88922);
      else if (idx == 100 ) num = 0.94808*TMath::Erf((x-2.20120)/1.15939);
   }
   else if (fabs(eta)<2.1)
   {
      if (idx==0) num = 0.90308*TMath::Erf((x+0.38340)/3.01756);
      else if (idx == -1   ) num = 0.91411*TMath::Erf((x+0.88702)/3.47188);
      else if (idx == -2   ) num = 0.89193*TMath::Erf((x-0.03453)/2.62900);
      else if (idx == 1   ) num = 0.90133*TMath::Erf((x+2.51524)/4.71657);
      else if (idx == 2   ) num = 0.89938*TMath::Erf((x-0.06893)/2.63399);
      else if (idx == 3   ) num = 0.90375*TMath::Erf((x+0.70347)/3.45947);
      else if (idx == 4   ) num = 0.90401*TMath::Erf((x-0.39313)/2.41467);
      else if (idx == 5   ) num = 0.88480*TMath::Erf((x+2.29709)/4.56739);
      else if (idx == 6   ) num = 0.89109*TMath::Erf((x+1.06979)/3.42303);
      else if (idx == 7   ) num = 0.89845*TMath::Erf((x+0.46623)/3.22404);
      else if (idx == 8   ) num = 0.92622*TMath::Erf((x+1.27287)/3.96030);
      else if (idx == 9   ) num = 0.90232*TMath::Erf((x+0.89344)/3.45003);
      else if (idx == 10  ) num = 0.90578*TMath::Erf((x-0.09903)/2.53014);
      else if (idx == 11  ) num = 0.89629*TMath::Erf((x+1.99642)/4.39586);
      else if (idx == 12  ) num = 0.87757*TMath::Erf((x+0.22838)/2.55574);
      else if (idx == 13  ) num = 0.90430*TMath::Erf((x-0.21894)/2.59751);
      else if (idx == 14  ) num = 0.92484*TMath::Erf((x-0.38317)/2.49856);
      else if (idx == 15  ) num = 0.90022*TMath::Erf((x-0.62171)/2.13680);
      else if (idx == 16  ) num = 0.90568*TMath::Erf((x-0.31125)/2.43715);
      else if (idx == 17  ) num = 0.90842*TMath::Erf((x+0.46539)/3.03519);
      else if (idx == 18  ) num = 0.91753*TMath::Erf((x+0.32573)/3.14621);
      else if (idx == 19  ) num = 0.89349*TMath::Erf((x-0.46061)/2.26023);
      else if (idx == 20  ) num = 0.91794*TMath::Erf((x+5.49976)/7.03158);
      else if (idx == 21  ) num = 0.88517*TMath::Erf((x+0.84423)/3.21242);
      else if (idx == 22  ) num = 0.90298*TMath::Erf((x+0.68959)/3.38150);
      else if (idx == 23  ) num = 0.92797*TMath::Erf((x+0.08437)/3.08065);
      else if (idx == 24  ) num = 0.89026*TMath::Erf((x-0.16617)/2.65288);
      else if (idx == 25  ) num = 0.92337*TMath::Erf((x+4.44746)/6.85401);
      else if (idx == 26  ) num = 0.88888*TMath::Erf((x+0.35533)/2.85771);
      else if (idx == 27  ) num = 0.90306*TMath::Erf((x+0.05722)/2.83532);
      else if (idx == 28  ) num = 0.90449*TMath::Erf((x+0.43834)/3.08061);
      else if (idx == 29  ) num = 0.92440*TMath::Erf((x+1.49333)/4.26229);
      else if (idx == 30  ) num = 0.90958*TMath::Erf((x+1.55308)/4.19987);
      else if (idx == 31  ) num = 0.87435*TMath::Erf((x-1.21415)/1.28728);
      else if (idx == 32  ) num = 0.90720*TMath::Erf((x+0.86987)/3.25010);
      else if (idx == 33  ) num = 0.89337*TMath::Erf((x+0.20992)/2.73142);
      else if (idx == 34  ) num = 0.89829*TMath::Erf((x+3.37266)/5.40874);
      else if (idx == 35  ) num = 0.89568*TMath::Erf((x+2.42446)/4.55309);
      else if (idx == 36  ) num = 0.89148*TMath::Erf((x-0.55512)/1.96536);
      else if (idx == 37  ) num = 0.90946*TMath::Erf((x+0.67907)/3.28619);
      else if (idx == 38  ) num = 0.89490*TMath::Erf((x+1.06397)/3.65065);
      else if (idx == 39  ) num = 0.90462*TMath::Erf((x-0.38578)/2.37546);
      else if (idx == 40  ) num = 0.87301*TMath::Erf((x-0.47416)/1.91654);
      else if (idx == 41  ) num = 0.87731*TMath::Erf((x-0.20504)/2.27713);
      else if (idx == 42  ) num = 0.88756*TMath::Erf((x-0.78447)/1.81204);
      else if (idx == 43  ) num = 0.91966*TMath::Erf((x-0.14912)/2.79753);
      else if (idx == 44  ) num = 0.90146*TMath::Erf((x-0.65164)/2.00435);
      else if (idx == 45  ) num = 0.91837*TMath::Erf((x+0.04792)/2.94349);
      else if (idx == 46  ) num = 0.89783*TMath::Erf((x+0.52600)/3.31095);
      else if (idx == 47  ) num = 0.89940*TMath::Erf((x+0.34263)/3.16886);
      else if (idx == 48  ) num = 0.88998*TMath::Erf((x-0.10339)/2.62082);
      else if (idx == 49  ) num = 0.91888*TMath::Erf((x-0.28315)/2.59053);
      else if (idx == 50  ) num = 0.91343*TMath::Erf((x+0.11011)/2.78660);
      else if (idx == 51  ) num = 0.88749*TMath::Erf((x+0.82065)/3.24149);
      else if (idx == 52  ) num = 0.89758*TMath::Erf((x-0.71825)/1.98357);
      else if (idx == 53  ) num = 0.90252*TMath::Erf((x-0.16748)/2.49708);
      else if (idx == 54  ) num = 0.91812*TMath::Erf((x+1.31527)/3.98975);
      else if (idx == 55  ) num = 0.91096*TMath::Erf((x-0.39460)/2.42503);
      else if (idx == 56  ) num = 0.91327*TMath::Erf((x+1.76644)/4.49519);
      else if (idx == 57  ) num = 0.93348*TMath::Erf((x-0.72815)/2.09701);
      else if (idx == 58  ) num = 0.89835*TMath::Erf((x+0.73167)/3.06207);
      else if (idx == 59  ) num = 0.89840*TMath::Erf((x+0.00238)/2.51083);
      else if (idx == 60  ) num = 0.89302*TMath::Erf((x+0.80239)/3.24793);
      else if (idx == 61  ) num = 0.87143*TMath::Erf((x+1.12502)/3.22869);
      else if (idx == 62  ) num = 0.92543*TMath::Erf((x+0.35322)/3.14925);
      else if (idx == 63  ) num = 0.89613*TMath::Erf((x+0.54113)/2.89346);
      else if (idx == 64  ) num = 0.88552*TMath::Erf((x+0.86215)/3.20295);
      else if (idx == 65  ) num = 0.89764*TMath::Erf((x-0.18359)/2.28236);
      else if (idx == 66  ) num = 0.91130*TMath::Erf((x+0.79615)/3.39557);
      else if (idx == 67  ) num = 0.90162*TMath::Erf((x-0.16368)/2.57634);
      else if (idx == 68  ) num = 0.89933*TMath::Erf((x-0.50153)/2.17003);
      else if (idx == 69  ) num = 0.91062*TMath::Erf((x+1.48648)/4.17404);
      else if (idx == 70  ) num = 0.90863*TMath::Erf((x+0.14089)/2.77845);
      else if (idx == 71  ) num = 0.90796*TMath::Erf((x+0.25725)/2.95999);
      else if (idx == 72  ) num = 0.88684*TMath::Erf((x-0.30889)/2.24101);
      else if (idx == 73  ) num = 0.89895*TMath::Erf((x-0.35268)/2.35784);
      else if (idx == 74  ) num = 0.90060*TMath::Erf((x+1.31374)/3.69622);
      else if (idx == 75  ) num = 0.90401*TMath::Erf((x+0.67193)/3.19159);
      else if (idx == 76  ) num = 0.89913*TMath::Erf((x+4.89065)/5.91700);
      else if (idx == 77  ) num = 0.88745*TMath::Erf((x+0.00411)/2.68113);
      else if (idx == 78  ) num = 0.90692*TMath::Erf((x+0.57875)/3.35768);
      else if (idx == 79  ) num = 0.86222*TMath::Erf((x+0.36570)/2.68251);
      else if (idx == 80  ) num = 0.89631*TMath::Erf((x-0.20282)/2.45861);
      else if (idx == 81  ) num = 0.89445*TMath::Erf((x-0.68104)/2.16591);
      else if (idx == 82  ) num = 0.91009*TMath::Erf((x+1.65957)/4.13236);
      else if (idx == 83  ) num = 0.89310*TMath::Erf((x+0.63138)/2.93873);
      else if (idx == 84  ) num = 0.90464*TMath::Erf((x+2.03629)/4.12120);
      else if (idx == 85  ) num = 0.90484*TMath::Erf((x+1.94694)/4.34561);
      else if (idx == 86  ) num = 0.91820*TMath::Erf((x+1.99734)/4.55747);
      else if (idx == 87  ) num = 0.89881*TMath::Erf((x+1.13199)/3.60696);
      else if (idx == 88  ) num = 0.89174*TMath::Erf((x+0.10509)/2.66778);
      else if (idx == 89  ) num = 0.90317*TMath::Erf((x+0.75288)/3.46098);
      else if (idx == 90  ) num = 0.90123*TMath::Erf((x+4.28682)/6.39578);
      else if (idx == 91  ) num = 0.88905*TMath::Erf((x+0.27105)/2.65697);
      else if (idx == 92  ) num = 0.92952*TMath::Erf((x+0.04262)/2.75286);
      else if (idx == 93  ) num = 0.92110*TMath::Erf((x+2.64333)/5.14776);
      else if (idx == 94  ) num = 0.91314*TMath::Erf((x+1.93417)/4.45411);
      else if (idx == 95  ) num = 0.91004*TMath::Erf((x+0.02527)/2.80648);
      else if (idx == 96  ) num = 0.90279*TMath::Erf((x+0.25425)/3.03008);
      else if (idx == 97  ) num = 0.91834*TMath::Erf((x+2.26470)/5.01178);
      else if (idx == 98  ) num = 0.88781*TMath::Erf((x+0.64929)/3.11468);
      else if (idx == 99  ) num = 0.89985*TMath::Erf((x+2.55673)/4.90839);
      else if (idx == 100 ) num = 0.90635*TMath::Erf((x+0.29160)/2.98695);
   }
   else
   {
      if (idx==0) num = 0.91174*TMath::Erf((x+0.42843)/2.61737);
      else if (idx == -1   ) num = 0.91165*TMath::Erf((x+0.74551)/2.77943);
      else if (idx == -2   ) num = 0.91169*TMath::Erf((x+0.17925)/2.49352);
      else if (idx == 1   ) num = 0.88556*TMath::Erf((x-0.05093)/2.19732);
      else if (idx == 2   ) num = 0.93512*TMath::Erf((x+1.62238)/3.79510);
      else if (idx == 3   ) num = 0.92535*TMath::Erf((x+0.36939)/2.65491);
      else if (idx == 4   ) num = 0.92326*TMath::Erf((x+1.45818)/3.71173);
      else if (idx == 5   ) num = 0.88710*TMath::Erf((x-0.08378)/1.92964);
      else if (idx == 6   ) num = 0.90841*TMath::Erf((x+1.14399)/3.10913);
      else if (idx == 7   ) num = 0.92312*TMath::Erf((x+1.51513)/3.62567);
      else if (idx == 8   ) num = 0.89696*TMath::Erf((x+0.28327)/2.33805);
      else if (idx == 9   ) num = 0.91713*TMath::Erf((x+2.61254)/4.38020);
      else if (idx == 10  ) num = 0.87039*TMath::Erf((x+0.27459)/2.17674);
      else if (idx == 11  ) num = 0.94197*TMath::Erf((x+0.41717)/3.08282);
      else if (idx == 12  ) num = 0.91011*TMath::Erf((x+1.26963)/3.21006);
      else if (idx == 13  ) num = 0.89205*TMath::Erf((x+0.32470)/2.42502);
      else if (idx == 14  ) num = 0.88254*TMath::Erf((x-0.16029)/1.99310);
      else if (idx == 15  ) num = 0.91733*TMath::Erf((x+0.56530)/2.66756);
      else if (idx == 16  ) num = 0.92879*TMath::Erf((x+0.56715)/3.02109);
      else if (idx == 17  ) num = 0.90091*TMath::Erf((x+0.32390)/2.44721);
      else if (idx == 18  ) num = 0.90047*TMath::Erf((x-0.24963)/1.96296);
      else if (idx == 19  ) num = 0.95174*TMath::Erf((x+0.32860)/2.67137);
      else if (idx == 20  ) num = 0.92468*TMath::Erf((x-0.07924)/2.29450);
      else if (idx == 21  ) num = 0.89604*TMath::Erf((x-0.05031)/2.02791);
      else if (idx == 22  ) num = 0.90072*TMath::Erf((x-0.13398)/2.05239);
      else if (idx == 23  ) num = 0.90001*TMath::Erf((x-0.37983)/1.58726);
      else if (idx == 24  ) num = 0.94335*TMath::Erf((x+0.48368)/3.01309);
      else if (idx == 25  ) num = 0.87845*TMath::Erf((x-1.15032)/0.86968);
      else if (idx == 26  ) num = 0.87663*TMath::Erf((x-0.20549)/1.89327);
      else if (idx == 27  ) num = 0.89593*TMath::Erf((x+0.07299)/2.21400);
      else if (idx == 28  ) num = 0.89823*TMath::Erf((x+0.75857)/2.80539);
      else if (idx == 29  ) num = 0.90028*TMath::Erf((x+0.03872)/1.94030);
      else if (idx == 30  ) num = 0.94501*TMath::Erf((x+0.32269)/2.77848);
      else if (idx == 31  ) num = 0.88987*TMath::Erf((x+0.15127)/2.15727);
      else if (idx == 32  ) num = 0.89597*TMath::Erf((x+0.65894)/2.77349);
      else if (idx == 33  ) num = 0.88357*TMath::Erf((x+0.32272)/2.31358);
      else if (idx == 34  ) num = 0.91055*TMath::Erf((x+0.53697)/2.51001);
      else if (idx == 35  ) num = 0.89333*TMath::Erf((x-0.67775)/1.46018);
      else if (idx == 36  ) num = 0.90734*TMath::Erf((x-0.22058)/1.98696);
      else if (idx == 37  ) num = 0.91007*TMath::Erf((x+0.10334)/2.44059);
      else if (idx == 38  ) num = 0.89061*TMath::Erf((x-0.09604)/2.15249);
      else if (idx == 39  ) num = 0.90725*TMath::Erf((x+0.35874)/2.79728);
      else if (idx == 40  ) num = 0.87054*TMath::Erf((x-1.71684)/0.25814);
      else if (idx == 41  ) num = 0.91293*TMath::Erf((x+0.13197)/2.36298);
      else if (idx == 42  ) num = 0.87263*TMath::Erf((x-0.38698)/1.77750);
      else if (idx == 43  ) num = 0.91071*TMath::Erf((x+1.67319)/3.63544);
      else if (idx == 44  ) num = 0.89188*TMath::Erf((x-0.56284)/1.59353);
      else if (idx == 45  ) num = 0.91615*TMath::Erf((x+0.82864)/3.20319);
      else if (idx == 46  ) num = 0.91038*TMath::Erf((x-0.45720)/1.82855);
      else if (idx == 47  ) num = 0.92414*TMath::Erf((x-0.22087)/2.21285);
      else if (idx == 48  ) num = 0.88432*TMath::Erf((x+0.57883)/2.49281);
      else if (idx == 49  ) num = 0.90028*TMath::Erf((x-0.04745)/2.08324);
      else if (idx == 50  ) num = 0.87886*TMath::Erf((x+0.61502)/2.46084);
      else if (idx == 51  ) num = 0.87955*TMath::Erf((x+0.22107)/2.23334);
      else if (idx == 52  ) num = 0.89412*TMath::Erf((x+0.15168)/2.22112);
      else if (idx == 53  ) num = 0.91646*TMath::Erf((x+0.29646)/2.71776);
      else if (idx == 54  ) num = 0.88986*TMath::Erf((x+0.65144)/2.60518);
      else if (idx == 55  ) num = 0.88582*TMath::Erf((x+0.80599)/2.59040);
      else if (idx == 56  ) num = 0.89141*TMath::Erf((x+1.27088)/3.05764);
      else if (idx == 57  ) num = 0.86332*TMath::Erf((x+0.96815)/2.67610);
      else if (idx == 58  ) num = 0.91871*TMath::Erf((x+0.62789)/2.78795);
      else if (idx == 59  ) num = 0.92253*TMath::Erf((x+0.90289)/3.19798);
      else if (idx == 60  ) num = 0.93460*TMath::Erf((x+0.64892)/3.02476);
      else if (idx == 61  ) num = 0.90345*TMath::Erf((x+0.48103)/2.34694);
      else if (idx == 62  ) num = 0.94197*TMath::Erf((x+0.85863)/3.44957);
      else if (idx == 63  ) num = 0.90177*TMath::Erf((x-0.45037)/1.82742);
      else if (idx == 64  ) num = 0.91758*TMath::Erf((x+0.30191)/2.48286);
      else if (idx == 65  ) num = 0.91413*TMath::Erf((x-0.39183)/1.87413);
      else if (idx == 66  ) num = 0.91855*TMath::Erf((x-0.08918)/2.29942);
      else if (idx == 67  ) num = 0.91094*TMath::Erf((x+0.08127)/2.41802);
      else if (idx == 68  ) num = 0.90990*TMath::Erf((x+0.31698)/2.51846);
      else if (idx == 69  ) num = 0.87164*TMath::Erf((x+0.21257)/2.11652);
      else if (idx == 70  ) num = 0.91246*TMath::Erf((x+1.74237)/3.77912);
      else if (idx == 71  ) num = 0.87421*TMath::Erf((x-0.79314)/1.23412);
      else if (idx == 72  ) num = 0.87039*TMath::Erf((x-0.30021)/1.70053);
      else if (idx == 73  ) num = 0.85786*TMath::Erf((x-0.83068)/1.09659);
      else if (idx == 74  ) num = 0.89392*TMath::Erf((x-0.22577)/1.95690);
      else if (idx == 75  ) num = 0.89327*TMath::Erf((x-0.24873)/1.84525);
      else if (idx == 76  ) num = 0.90773*TMath::Erf((x+0.10269)/2.45636);
      else if (idx == 77  ) num = 0.92194*TMath::Erf((x-0.01758)/2.18684);
      else if (idx == 78  ) num = 0.91402*TMath::Erf((x+0.92906)/3.25360);
      else if (idx == 79  ) num = 0.89912*TMath::Erf((x+0.70545)/2.70498);
      else if (idx == 80  ) num = 0.89525*TMath::Erf((x+0.25565)/2.26352);
      else if (idx == 81  ) num = 0.91832*TMath::Erf((x+1.39577)/3.90724);
      else if (idx == 82  ) num = 0.91601*TMath::Erf((x-0.07235)/2.15516);
      else if (idx == 83  ) num = 0.89444*TMath::Erf((x-0.37968)/1.96507);
      else if (idx == 84  ) num = 0.89884*TMath::Erf((x+0.98593)/2.95295);
      else if (idx == 85  ) num = 0.90200*TMath::Erf((x+0.97603)/2.80845);
      else if (idx == 86  ) num = 0.90262*TMath::Erf((x-0.86479)/1.39761);
      else if (idx == 87  ) num = 0.87359*TMath::Erf((x+1.73489)/3.19910);
      else if (idx == 88  ) num = 0.88471*TMath::Erf((x+0.14941)/2.29428);
      else if (idx == 89  ) num = 0.91374*TMath::Erf((x+0.26769)/2.35604);
      else if (idx == 90  ) num = 0.90205*TMath::Erf((x+0.39789)/2.53676);
      else if (idx == 91  ) num = 0.91755*TMath::Erf((x+0.58025)/2.91726);
      else if (idx == 92  ) num = 0.91852*TMath::Erf((x+2.12959)/4.28679);
      else if (idx == 93  ) num = 0.90339*TMath::Erf((x-0.52417)/1.74583);
      else if (idx == 94  ) num = 0.90871*TMath::Erf((x+0.62459)/2.74819);
      else if (idx == 95  ) num = 0.89396*TMath::Erf((x+0.93206)/2.77567);
      else if (idx == 96  ) num = 0.88428*TMath::Erf((x+0.34629)/2.25652);
      else if (idx == 97  ) num = 0.93935*TMath::Erf((x+0.90253)/3.21417);
      else if (idx == 98  ) num = 0.92371*TMath::Erf((x-0.34233)/1.98688);
      else if (idx == 99  ) num = 0.90600*TMath::Erf((x+0.06380)/2.15114);
      else if (idx == 100 ) num = 0.94401*TMath::Erf((x+3.42680)/5.66206);
   }

   // return
   return num/den;
}

///////////////////////////////////////////////////
//               T R G    P P                    //
///////////////////////////////////////////////////
double tnp_weight_trg_pp(double x, double eta, int idx)
{
   // binned
   if (idx == -10) {
      if (fabs(eta) < 1.2) {
         // 0 < |eta| < 1.2
         if (x<4) return 1.05133;
         else if (x<4.5) return 1.01493;
         else if (x<5) return 1.00637;
         else if (x<5.5) return 1.00866;
         else if (x<6) return 1.00403;
         else if (x<7) return 0.999526;
         else if (x<8) return 0.993882;
         else if (x<10.5) return 0.999195;
         else if (x<14) return 0.994448;
         else if (x<18) return 0.997814;
         else return 0.99535;
      } else if (fabs(eta)<1.8) {
         // 1.2 < |eta| < 1.8
         if (x<3) return 1.20399;
         else if (x<3.5) return 1.08496;
         else if (x<4) return 1.0579;
         else if (x<4.5) return 1.02943;
         else if (x<5) return 1.02136;
         else if (x<6) return 1.01855;
         else if (x<7) return 1.01709;
         else if (x<9) return 1.00907;
         else if (x<14) return 1.00748;
         else if (x<18) return 1.02484;
         else return 1.02539;
      } else if (fabs(eta)<2.1) {
         // 1.8 < |eta| < 2.1
         if (x<2.5) return 1.23506;
         else if (x<3) return 1.07046;
         else if (x<3.5) return 1.05211;
         else if (x<4) return 1.04089;
         else if (x<4.5) return 1.04115;
         else if (x<5) return 1.03067;
         else if (x<6) return 1.02442;
         else if (x<7) return 1.025;
         else if (x<9) return 1.02442;
         else if (x<13) return 0.997836;
         else return 0.944194;
      } else {
         // 2.1 < |eta| < 2.4
         if (x<2.5) return 1.21185;
         else if (x<3) return 1.10746;
         else if (x<3.5) return 1.07255;
         else if (x<4) return 1.03562;
         else if (x<4.5) return 1.03939;
         else if (x<5) return 1.02434;
         else if (x<6.5) return 1.02967;
         else if (x<8.5) return 1.02523;
         else if (x<12) return 1.03297;
         else return 0.990749;
      }
   }

   // denominator (from MC)
   double den=1;
   if (fabs(eta)<1.2) den = (0.51387*(TMath::Erf((x-2.95780)/1.01717)*TMath::Exp(-0.00001*x)))+0.46186;
   else if (fabs(eta)<1.8) den = (0.87963*(TMath::Erf((x-2.33663)/1.22198)*TMath::Exp(-0.00013*x)))+0.06241;
   else if (fabs(eta)<2.1) den = (0.53171*(TMath::Erf((x-1.80661)/1.67849)*TMath::Exp(-0.00000*x)))+0.36279;
   else den = (0.38994*(TMath::Erf((x-1.55863)/1.70815)*TMath::Exp(-0.00003*x)))+0.48718;

   // numerator (from data)
   double num=1;
   if (fabs(eta)<1.2)
   {
      if (idx==0) num = (0.52580*(TMath::Erf((x-2.68070)/1.16799)*TMath::Exp(-0.00234*x)))+0.46172;
      else if (idx == -1   ) num = (0.52587*(TMath::Erf((x-2.68165)/1.16925)*TMath::Exp(-0.00229*x)))+0.46179;
      else if (idx == -2   ) num = (0.52570*(TMath::Erf((x-2.67968)/1.16728)*TMath::Exp(-0.00239*x)))+0.46163;
      else if (idx == 1   ) num = (0.52452*(TMath::Erf((x-2.35489)/1.45504)*TMath::Exp(-0.00197*x)))+0.46344;
      else if (idx == 2   ) num = (0.52934*(TMath::Erf((x-2.77208)/1.09665)*TMath::Exp(-0.00408*x)))+0.46478;
      else if (idx == 3   ) num = (0.52466*(TMath::Erf((x-2.68561)/1.17908)*TMath::Exp(-0.00204*x)))+0.46070;
      else if (idx == 4   ) num = (0.52281*(TMath::Erf((x-2.75691)/1.07074)*TMath::Exp(-0.00159*x)))+0.46007;
      else if (idx == 5   ) num = (0.52514*(TMath::Erf((x-2.67519)/1.16231)*TMath::Exp(-0.00247*x)))+0.46113;
      else if (idx == 6   ) num = (0.52817*(TMath::Erf((x-2.59227)/1.29525)*TMath::Exp(-0.00295*x)))+0.46265;
      else if (idx == 7   ) num = (0.52828*(TMath::Erf((x-2.69555)/1.17103)*TMath::Exp(-0.00370*x)))+0.46376;
      else if (idx == 8   ) num = (0.52621*(TMath::Erf((x-2.68257)/1.16886)*TMath::Exp(-0.00226*x)))+0.46210;
      else if (idx == 9   ) num = (0.52731*(TMath::Erf((x-2.59959)/1.28505)*TMath::Exp(-0.00239*x)))+0.46214;
      else if (idx == 10  ) num = (0.52414*(TMath::Erf((x-2.67112)/1.16549)*TMath::Exp(-0.00216*x)))+0.46028;
      else if (idx == 11  ) num = (0.52552*(TMath::Erf((x-2.60357)/1.24309)*TMath::Exp(-0.00193*x)))+0.46096;
      else if (idx == 12  ) num = (0.52633*(TMath::Erf((x-2.52728)/1.31946)*TMath::Exp(-0.00227*x)))+0.46254;
      else if (idx == 13  ) num = (0.52310*(TMath::Erf((x-2.66254)/1.16432)*TMath::Exp(-0.00128*x)))+0.45950;
      else if (idx == 14  ) num = (0.52642*(TMath::Erf((x-2.68076)/1.16826)*TMath::Exp(-0.00263*x)))+0.46224;
      else if (idx == 15  ) num = (0.52526*(TMath::Erf((x-2.75226)/1.09164)*TMath::Exp(-0.00233*x)))+0.46198;
      else if (idx == 16  ) num = (0.52919*(TMath::Erf((x-2.76695)/1.09741)*TMath::Exp(-0.00407*x)))+0.46459;
      else if (idx == 17  ) num = (0.52728*(TMath::Erf((x-2.68522)/1.16877)*TMath::Exp(-0.00304*x)))+0.46296;
      else if (idx == 18  ) num = (0.52206*(TMath::Erf((x-2.81136)/1.04090)*TMath::Exp(-0.00110*x)))+0.45924;
      else if (idx == 19  ) num = (0.52457*(TMath::Erf((x-2.66344)/1.16210)*TMath::Exp(-0.00193*x)))+0.46075;
      else if (idx == 20  ) num = (0.52589*(TMath::Erf((x-2.67629)/1.16444)*TMath::Exp(-0.00235*x)))+0.46182;
      else if (idx == 21  ) num = (0.52703*(TMath::Erf((x-2.58564)/1.28918)*TMath::Exp(-0.00224*x)))+0.46212;
      else if (idx == 22  ) num = (0.52829*(TMath::Erf((x-2.61746)/1.23702)*TMath::Exp(-0.00361*x)))+0.46300;
      else if (idx == 23  ) num = (0.52490*(TMath::Erf((x-2.67810)/1.16528)*TMath::Exp(-0.00194*x)))+0.46095;
      else if (idx == 24  ) num = (0.52293*(TMath::Erf((x-2.66434)/1.18072)*TMath::Exp(-0.00111*x)))+0.45940;
      else if (idx == 25  ) num = (0.52724*(TMath::Erf((x-2.84878)/1.00287)*TMath::Exp(-0.00332*x)))+0.46312;
      else if (idx == 26  ) num = (0.52744*(TMath::Erf((x-2.70500)/1.17644)*TMath::Exp(-0.00298*x)))+0.46300;
      else if (idx == 27  ) num = (0.52612*(TMath::Erf((x-2.68385)/1.17128)*TMath::Exp(-0.00226*x)))+0.46201;
      else if (idx == 28  ) num = (0.52708*(TMath::Erf((x-2.44817)/1.41574)*TMath::Exp(-0.00302*x)))+0.46477;
      else if (idx == 29  ) num = (0.52813*(TMath::Erf((x-2.60511)/1.25966)*TMath::Exp(-0.00328*x)))+0.46273;
      else if (idx == 30  ) num = (0.52656*(TMath::Erf((x-2.45324)/1.41476)*TMath::Exp(-0.00260*x)))+0.46426;
      else if (idx == 31  ) num = (0.52394*(TMath::Erf((x-2.54061)/1.29309)*TMath::Exp(-0.00132*x)))+0.45918;
      else if (idx == 32  ) num = (0.52373*(TMath::Erf((x-2.67145)/1.17424)*TMath::Exp(-0.00145*x)))+0.46001;
      else if (idx == 33  ) num = (0.52636*(TMath::Erf((x-2.76497)/1.08028)*TMath::Exp(-0.00272*x)))+0.46277;
      else if (idx == 34  ) num = (0.52462*(TMath::Erf((x-2.67079)/1.16798)*TMath::Exp(-0.00160*x)))+0.46079;
      else if (idx == 35  ) num = (0.52286*(TMath::Erf((x-2.81377)/1.00901)*TMath::Exp(-0.00171*x)))+0.46024;
      else if (idx == 36  ) num = (0.52523*(TMath::Erf((x-2.66794)/1.16193)*TMath::Exp(-0.00199*x)))+0.46131;
      else if (idx == 37  ) num = (0.52312*(TMath::Erf((x-2.74102)/1.09489)*TMath::Exp(-0.00139*x)))+0.46015;
      else if (idx == 38  ) num = (0.52600*(TMath::Erf((x-2.68107)/1.16878)*TMath::Exp(-0.00232*x)))+0.46190;
      else if (idx == 39  ) num = (0.52232*(TMath::Erf((x-2.65428)/1.15834)*TMath::Exp(-0.00099*x)))+0.45888;
      else if (idx == 40  ) num = (0.52700*(TMath::Erf((x-2.68694)/1.17244)*TMath::Exp(-0.00310*x)))+0.46271;
      else if (idx == 41  ) num = (0.52538*(TMath::Erf((x-2.82397)/1.00989)*TMath::Exp(-0.00267*x)))+0.46217;
      else if (idx == 42  ) num = (0.52622*(TMath::Erf((x-2.69059)/1.17828)*TMath::Exp(-0.00223*x)))+0.46208;
      else if (idx == 43  ) num = (0.52754*(TMath::Erf((x-2.77303)/1.08091)*TMath::Exp(-0.00316*x)))+0.46369;
      else if (idx == 44  ) num = (0.52447*(TMath::Erf((x-2.68015)/1.18223)*TMath::Exp(-0.00190*x)))+0.46059;
      else if (idx == 45  ) num = (0.52586*(TMath::Erf((x-2.67962)/1.16711)*TMath::Exp(-0.00233*x)))+0.46178;
      else if (idx == 46  ) num = (0.52551*(TMath::Erf((x-2.67197)/1.15913)*TMath::Exp(-0.00248*x)))+0.46147;
      else if (idx == 47  ) num = (0.52278*(TMath::Erf((x-2.83594)/0.99002)*TMath::Exp(-0.00115*x)))+0.45945;
      else if (idx == 48  ) num = (0.52288*(TMath::Erf((x-2.73721)/1.10714)*TMath::Exp(-0.00090*x)))+0.45985;
      else if (idx == 49  ) num = (0.52140*(TMath::Erf((x-2.64424)/1.16427)*TMath::Exp(-0.00055*x)))+0.45820;
      else if (idx == 50  ) num = (0.52635*(TMath::Erf((x-2.75543)/1.10865)*TMath::Exp(-0.00262*x)))+0.46234;
      else if (idx == 51  ) num = (0.52330*(TMath::Erf((x-2.86218)/0.95880)*TMath::Exp(-0.00166*x)))+0.45946;
      else if (idx == 52  ) num = (0.52373*(TMath::Erf((x-2.86971)/0.97688)*TMath::Exp(-0.00127*x)))+0.45826;
      else if (idx == 53  ) num = (0.52422*(TMath::Erf((x-2.74165)/1.09627)*TMath::Exp(-0.00186*x)))+0.46085;
      else if (idx == 54  ) num = (0.52561*(TMath::Erf((x-2.68303)/1.17037)*TMath::Exp(-0.00238*x)))+0.46153;
      else if (idx == 55  ) num = (0.52823*(TMath::Erf((x-2.57200)/1.30657)*TMath::Exp(-0.00304*x)))+0.46310;
      else if (idx == 56  ) num = (0.52560*(TMath::Erf((x-2.47978)/1.36119)*TMath::Exp(-0.00226*x)))+0.46240;
      else if (idx == 57  ) num = (0.52256*(TMath::Erf((x-2.65770)/1.16469)*TMath::Exp(-0.00145*x)))+0.45901;
      else if (idx == 58  ) num = (0.52987*(TMath::Erf((x-2.57489)/1.30466)*TMath::Exp(-0.00352*x)))+0.46417;
      else if (idx == 59  ) num = (0.52598*(TMath::Erf((x-2.69172)/1.17819)*TMath::Exp(-0.00227*x)))+0.46184;
      else if (idx == 60  ) num = (0.52207*(TMath::Erf((x-2.79244)/1.01993)*TMath::Exp(-0.00114*x)))+0.45945;
      else if (idx == 61  ) num = (0.52589*(TMath::Erf((x-2.69265)/1.17934)*TMath::Exp(-0.00230*x)))+0.46176;
      else if (idx == 62  ) num = (0.52564*(TMath::Erf((x-2.69262)/1.17797)*TMath::Exp(-0.00198*x)))+0.46156;
      else if (idx == 63  ) num = (0.52588*(TMath::Erf((x-2.49548)/1.35761)*TMath::Exp(-0.00200*x)))+0.46150;
      else if (idx == 64  ) num = (0.52445*(TMath::Erf((x-2.67730)/1.16713)*TMath::Exp(-0.00197*x)))+0.46054;
      else if (idx == 65  ) num = (0.52580*(TMath::Erf((x-2.44552)/1.40849)*TMath::Exp(-0.00258*x)))+0.46364;
      else if (idx == 66  ) num = (0.52354*(TMath::Erf((x-2.87352)/0.94759)*TMath::Exp(-0.00132*x)))+0.45788;
      else if (idx == 67  ) num = (0.52817*(TMath::Erf((x-2.69552)/1.17103)*TMath::Exp(-0.00320*x)))+0.46370;
      else if (idx == 68  ) num = (0.52298*(TMath::Erf((x-2.78556)/1.07754)*TMath::Exp(-0.00140*x)))+0.46030;
      else if (idx == 69  ) num = (0.52216*(TMath::Erf((x-2.83751)/0.98565)*TMath::Exp(-0.00126*x)))+0.45871;
      else if (idx == 70  ) num = (0.52433*(TMath::Erf((x-2.67610)/1.17537)*TMath::Exp(-0.00189*x)))+0.46048;
      else if (idx == 71  ) num = (0.52754*(TMath::Erf((x-2.41440)/1.46757)*TMath::Exp(-0.00329*x)))+0.46541;
      else if (idx == 72  ) num = (0.52696*(TMath::Erf((x-2.59618)/1.26238)*TMath::Exp(-0.00291*x)))+0.46181;
      else if (idx == 73  ) num = (0.52646*(TMath::Erf((x-2.48416)/1.35982)*TMath::Exp(-0.00286*x)))+0.46385;
      else if (idx == 74  ) num = (0.52460*(TMath::Erf((x-2.67009)/1.15880)*TMath::Exp(-0.00206*x)))+0.46070;
      else if (idx == 75  ) num = (0.52595*(TMath::Erf((x-2.58353)/1.26549)*TMath::Exp(-0.00224*x)))+0.46110;
      else if (idx == 76  ) num = (0.52562*(TMath::Erf((x-2.50314)/1.34485)*TMath::Exp(-0.00173*x)))+0.46138;
      else if (idx == 77  ) num = (0.52198*(TMath::Erf((x-2.86934)/0.94978)*TMath::Exp(-0.00118*x)))+0.45928;
      else if (idx == 78  ) num = (0.52220*(TMath::Erf((x-2.65921)/1.17117)*TMath::Exp(-0.00077*x)))+0.45880;
      else if (idx == 79  ) num = (0.52313*(TMath::Erf((x-2.65808)/1.15260)*TMath::Exp(-0.00159*x)))+0.45949;
      else if (idx == 80  ) num = (0.52668*(TMath::Erf((x-2.59023)/1.26609)*TMath::Exp(-0.00244*x)))+0.46165;
      else if (idx == 81  ) num = (0.52635*(TMath::Erf((x-2.67755)/1.16111)*TMath::Exp(-0.00264*x)))+0.46218;
      else if (idx == 82  ) num = (0.52602*(TMath::Erf((x-2.68928)/1.17250)*TMath::Exp(-0.00255*x)))+0.46185;
      else if (idx == 83  ) num = (0.52582*(TMath::Erf((x-2.68361)/1.17183)*TMath::Exp(-0.00230*x)))+0.46173;
      else if (idx == 84  ) num = (0.52293*(TMath::Erf((x-2.66843)/1.16907)*TMath::Exp(-0.00140*x)))+0.45930;
      else if (idx == 85  ) num = (0.52434*(TMath::Erf((x-2.67209)/1.17375)*TMath::Exp(-0.00194*x)))+0.46050;
      else if (idx == 86  ) num = (0.52803*(TMath::Erf((x-2.59703)/1.28077)*TMath::Exp(-0.00253*x)))+0.46249;
      else if (idx == 87  ) num = (0.52411*(TMath::Erf((x-2.77073)/1.06247)*TMath::Exp(-0.00173*x)))+0.46099;
      else if (idx == 88  ) num = (0.52422*(TMath::Erf((x-2.51623)/1.31767)*TMath::Exp(-0.00088*x)))+0.46003;
      else if (idx == 89  ) num = (0.53135*(TMath::Erf((x-2.36660)/1.53977)*TMath::Exp(-0.00494*x)))+0.46920;
      else if (idx == 90  ) num = (0.52736*(TMath::Erf((x-2.59354)/1.24906)*TMath::Exp(-0.00274*x)))+0.46224;
      else if (idx == 91  ) num = (0.52696*(TMath::Erf((x-2.60887)/1.23753)*TMath::Exp(-0.00236*x)))+0.46194;
      else if (idx == 92  ) num = (0.52292*(TMath::Erf((x-2.82867)/1.00100)*TMath::Exp(-0.00210*x)))+0.46016;
      else if (idx == 93  ) num = (0.52697*(TMath::Erf((x-2.54916)/1.29555)*TMath::Exp(-0.00282*x)))+0.46144;
      else if (idx == 94  ) num = (0.52955*(TMath::Erf((x-2.52152)/1.33797)*TMath::Exp(-0.00342*x)))+0.46417;
      else if (idx == 95  ) num = (0.52509*(TMath::Erf((x-2.77296)/1.07610)*TMath::Exp(-0.00201*x)))+0.46190;
      else if (idx == 96  ) num = (0.52587*(TMath::Erf((x-2.54922)/1.28166)*TMath::Exp(-0.00232*x)))+0.46101;
      else if (idx == 97  ) num = (0.52282*(TMath::Erf((x-2.66902)/1.16301)*TMath::Exp(-0.00108*x)))+0.45924;
      else if (idx == 98  ) num = (0.52473*(TMath::Erf((x-2.67440)/1.17207)*TMath::Exp(-0.00173*x)))+0.46087;
      else if (idx == 99  ) num = (0.52958*(TMath::Erf((x-2.55928)/1.29032)*TMath::Exp(-0.00399*x)))+0.46380;
      else if (idx == 100 ) num = (0.52348*(TMath::Erf((x-2.89211)/0.94363)*TMath::Exp(-0.00106*x)))+0.45791;
   }
   else if (fabs(eta)<1.8)
   {
      if (idx==0) num = (0.91504*(TMath::Erf((x-2.23999)/1.16962)*TMath::Exp(-0.00000*x)))+0.04202;
      else if (idx == -1   ) num = (0.91559*(TMath::Erf((x-2.24020)/1.16984)*TMath::Exp(-0.00000*x)))+0.04248;
      else if (idx == -2   ) num = (0.91450*(TMath::Erf((x-2.23958)/1.16980)*TMath::Exp(-0.00000*x)))+0.04156;
      else if (idx == 1   ) num = (0.91624*(TMath::Erf((x-2.21327)/1.23381)*TMath::Exp(-0.00069*x)))+0.04514;
      else if (idx == 2   ) num = (0.91450*(TMath::Erf((x-2.23961)/1.16855)*TMath::Exp(-0.00000*x)))+0.04154;
      else if (idx == 3   ) num = (0.91504*(TMath::Erf((x-2.22873)/1.18396)*TMath::Exp(-0.00000*x)))+0.04261;
      else if (idx == 4   ) num = (0.91564*(TMath::Erf((x-2.24467)/1.17760)*TMath::Exp(-0.00000*x)))+0.04234;
      else if (idx == 5   ) num = (0.91569*(TMath::Erf((x-2.23605)/1.16241)*TMath::Exp(-0.00055*x)))+0.04270;
      else if (idx == 6   ) num = (0.91614*(TMath::Erf((x-2.26412)/1.13703)*TMath::Exp(-0.00000*x)))+0.04080;
      else if (idx == 7   ) num = (0.91508*(TMath::Erf((x-2.24315)/1.17493)*TMath::Exp(-0.00000*x)))+0.04191;
      else if (idx == 8   ) num = (0.91477*(TMath::Erf((x-2.25059)/1.15967)*TMath::Exp(-0.00000*x)))+0.04084;
      else if (idx == 9   ) num = (0.91606*(TMath::Erf((x-2.24308)/1.17389)*TMath::Exp(-0.00000*x)))+0.04278;
      else if (idx == 10  ) num = (0.91281*(TMath::Erf((x-2.22255)/1.17429)*TMath::Exp(-0.00008*x)))+0.04093;
      else if (idx == 11  ) num = (0.91419*(TMath::Erf((x-2.26934)/1.10729)*TMath::Exp(-0.00001*x)))+0.03862;
      else if (idx == 12  ) num = (0.91426*(TMath::Erf((x-2.22107)/1.19868)*TMath::Exp(-0.00000*x)))+0.04264;
      else if (idx == 13  ) num = (0.91481*(TMath::Erf((x-2.22626)/1.18360)*TMath::Exp(-0.00000*x)))+0.04253;
      else if (idx == 14  ) num = (0.91491*(TMath::Erf((x-2.23372)/1.19243)*TMath::Exp(-0.00000*x)))+0.04222;
      else if (idx == 15  ) num = (0.91538*(TMath::Erf((x-2.24101)/1.17106)*TMath::Exp(-0.00000*x)))+0.04227;
      else if (idx == 16  ) num = (0.91761*(TMath::Erf((x-2.24399)/1.16619)*TMath::Exp(-0.00115*x)))+0.04394;
      else if (idx == 17  ) num = (0.91343*(TMath::Erf((x-2.22052)/1.19040)*TMath::Exp(-0.00000*x)))+0.04144;
      else if (idx == 18  ) num = (0.91516*(TMath::Erf((x-2.24204)/1.17186)*TMath::Exp(-0.00019*x)))+0.04202;
      else if (idx == 19  ) num = (0.94768*(TMath::Erf((x-2.18250)/1.22848)*TMath::Exp(-0.00000*x)))+0.01365;
      else if (idx == 20  ) num = (0.91407*(TMath::Erf((x-2.24078)/1.16954)*TMath::Exp(-0.00017*x)))+0.04099;
      else if (idx == 21  ) num = (0.91554*(TMath::Erf((x-2.25665)/1.14497)*TMath::Exp(-0.00000*x)))+0.04086;
      else if (idx == 22  ) num = (0.91499*(TMath::Erf((x-2.22687)/1.18002)*TMath::Exp(-0.00000*x)))+0.04254;
      else if (idx == 23  ) num = (0.91553*(TMath::Erf((x-2.26896)/1.11767)*TMath::Exp(-0.00028*x)))+0.03978;
      else if (idx == 24  ) num = (0.91773*(TMath::Erf((x-2.26930)/1.13960)*TMath::Exp(-0.00000*x)))+0.04181;
      else if (idx == 25  ) num = (0.91575*(TMath::Erf((x-2.22574)/1.20824)*TMath::Exp(-0.00000*x)))+0.04364;
      else if (idx == 26  ) num = (0.91746*(TMath::Erf((x-2.24844)/1.17975)*TMath::Exp(-0.00000*x)))+0.04385;
      else if (idx == 27  ) num = (0.91822*(TMath::Erf((x-2.25975)/1.17822)*TMath::Exp(-0.00061*x)))+0.04363;
      else if (idx == 28  ) num = (0.91996*(TMath::Erf((x-2.23135)/1.20719)*TMath::Exp(-0.00148*x)))+0.04720;
      else if (idx == 29  ) num = (0.91598*(TMath::Erf((x-2.27156)/1.12497)*TMath::Exp(-0.00003*x)))+0.04016;
      else if (idx == 30  ) num = (0.91693*(TMath::Erf((x-2.20717)/1.21986)*TMath::Exp(-0.00000*x)))+0.04609;
      else if (idx == 31  ) num = (0.91593*(TMath::Erf((x-2.26413)/1.13096)*TMath::Exp(-0.00000*x)))+0.04060;
      else if (idx == 32  ) num = (0.91661*(TMath::Erf((x-2.22189)/1.20778)*TMath::Exp(-0.00000*x)))+0.04468;
      else if (idx == 33  ) num = (0.91499*(TMath::Erf((x-2.23510)/1.16195)*TMath::Exp(-0.00020*x)))+0.04217;
      else if (idx == 34  ) num = (0.91585*(TMath::Erf((x-2.26657)/1.13471)*TMath::Exp(-0.00000*x)))+0.04051;
      else if (idx == 35  ) num = (0.91645*(TMath::Erf((x-2.23531)/1.20068)*TMath::Exp(-0.00000*x)))+0.04363;
      else if (idx == 36  ) num = (0.91473*(TMath::Erf((x-2.24554)/1.15959)*TMath::Exp(-0.00000*x)))+0.04112;
      else if (idx == 37  ) num = (0.93865*(TMath::Erf((x-2.23319)/1.16246)*TMath::Exp(-0.00042*x)))+0.02170;
      else if (idx == 38  ) num = (0.91606*(TMath::Erf((x-2.24886)/1.14822)*TMath::Exp(-0.00000*x)))+0.04169;
      else if (idx == 39  ) num = (0.91572*(TMath::Erf((x-2.24370)/1.17367)*TMath::Exp(-0.00000*x)))+0.04243;
      else if (idx == 40  ) num = (0.91710*(TMath::Erf((x-2.25494)/1.15265)*TMath::Exp(-0.00016*x)))+0.04255;
      else if (idx == 41  ) num = (0.91560*(TMath::Erf((x-2.27996)/1.13411)*TMath::Exp(-0.00007*x)))+0.03964;
      else if (idx == 42  ) num = (0.91635*(TMath::Erf((x-2.24468)/1.17510)*TMath::Exp(-0.00000*x)))+0.04298;
      else if (idx == 43  ) num = (0.91613*(TMath::Erf((x-2.24046)/1.17170)*TMath::Exp(-0.00029*x)))+0.04286;
      else if (idx == 44  ) num = (0.91553*(TMath::Erf((x-2.21496)/1.23001)*TMath::Exp(-0.00000*x)))+0.04429;
      else if (idx == 45  ) num = (0.91385*(TMath::Erf((x-2.20187)/1.22045)*TMath::Exp(-0.00000*x)))+0.04343;
      else if (idx == 46  ) num = (0.91595*(TMath::Erf((x-2.25898)/1.13996)*TMath::Exp(-0.00000*x)))+0.04117;
      else if (idx == 47  ) num = (0.91479*(TMath::Erf((x-2.20434)/1.23089)*TMath::Exp(-0.00000*x)))+0.04429;
      else if (idx == 48  ) num = (0.93296*(TMath::Erf((x-2.20352)/1.19159)*TMath::Exp(-0.00000*x)))+0.02307;
      else if (idx == 49  ) num = (0.91515*(TMath::Erf((x-2.23952)/1.16767)*TMath::Exp(-0.00000*x)))+0.04210;
      else if (idx == 50  ) num = (0.91576*(TMath::Erf((x-2.23112)/1.19488)*TMath::Exp(-0.00000*x)))+0.04320;
      else if (idx == 51  ) num = (0.91760*(TMath::Erf((x-2.30165)/1.07416)*TMath::Exp(-0.00000*x)))+0.03914;
      else if (idx == 52  ) num = (0.91412*(TMath::Erf((x-2.23643)/1.16489)*TMath::Exp(-0.00000*x)))+0.04133;
      else if (idx == 53  ) num = (0.91592*(TMath::Erf((x-2.23210)/1.19744)*TMath::Exp(-0.00000*x)))+0.04334;
      else if (idx == 54  ) num = (0.91455*(TMath::Erf((x-2.22019)/1.19593)*TMath::Exp(-0.00000*x)))+0.04291;
      else if (idx == 55  ) num = (0.91551*(TMath::Erf((x-2.22002)/1.18231)*TMath::Exp(-0.00000*x)))+0.04358;
      else if (idx == 56  ) num = (0.91670*(TMath::Erf((x-2.24853)/1.17987)*TMath::Exp(-0.00000*x)))+0.04311;
      else if (idx == 57  ) num = (0.91605*(TMath::Erf((x-2.25072)/1.16032)*TMath::Exp(-0.00000*x)))+0.04195;
      else if (idx == 58  ) num = (0.91527*(TMath::Erf((x-2.23331)/1.19945)*TMath::Exp(-0.00000*x)))+0.04261;
      else if (idx == 59  ) num = (0.91595*(TMath::Erf((x-2.28381)/1.10885)*TMath::Exp(-0.00017*x)))+0.03923;
      else if (idx == 60  ) num = (0.91509*(TMath::Erf((x-2.23106)/1.18060)*TMath::Exp(-0.00000*x)))+0.04250;
      else if (idx == 61  ) num = (0.91412*(TMath::Erf((x-2.22950)/1.15380)*TMath::Exp(-0.00020*x)))+0.04158;
      else if (idx == 62  ) num = (0.91689*(TMath::Erf((x-2.23513)/1.18675)*TMath::Exp(-0.00000*x)))+0.04401;
      else if (idx == 63  ) num = (0.91306*(TMath::Erf((x-2.19505)/1.23155)*TMath::Exp(-0.00000*x)))+0.04328;
      else if (idx == 64  ) num = (0.91614*(TMath::Erf((x-2.25895)/1.13011)*TMath::Exp(-0.00000*x)))+0.04094;
      else if (idx == 65  ) num = (0.91615*(TMath::Erf((x-2.24869)/1.14070)*TMath::Exp(-0.00000*x)))+0.04183;
      else if (idx == 66  ) num = (0.91686*(TMath::Erf((x-2.21650)/1.22437)*TMath::Exp(-0.00000*x)))+0.04562;
      else if (idx == 67  ) num = (0.91474*(TMath::Erf((x-2.24662)/1.15118)*TMath::Exp(-0.00000*x)))+0.04093;
      else if (idx == 68  ) num = (0.91697*(TMath::Erf((x-2.24931)/1.18305)*TMath::Exp(-0.00000*x)))+0.04335;
      else if (idx == 69  ) num = (0.91395*(TMath::Erf((x-2.19152)/1.23844)*TMath::Exp(-0.00000*x)))+0.04445;
      else if (idx == 70  ) num = (0.91637*(TMath::Erf((x-2.24735)/1.17976)*TMath::Exp(-0.00000*x)))+0.04287;
      else if (idx == 71  ) num = (0.91499*(TMath::Erf((x-2.24305)/1.17595)*TMath::Exp(-0.00000*x)))+0.04186;
      else if (idx == 72  ) num = (0.91715*(TMath::Erf((x-2.23241)/1.20396)*TMath::Exp(-0.00000*x)))+0.04455;
      else if (idx == 73  ) num = (0.91610*(TMath::Erf((x-2.22280)/1.18545)*TMath::Exp(-0.00036*x)))+0.04403;
      else if (idx == 74  ) num = (0.91522*(TMath::Erf((x-2.24363)/1.17444)*TMath::Exp(-0.00000*x)))+0.04200;
      else if (idx == 75  ) num = (0.91583*(TMath::Erf((x-2.24799)/1.16094)*TMath::Exp(-0.00007*x)))+0.04200;
      else if (idx == 76  ) num = (0.91508*(TMath::Erf((x-2.24902)/1.15314)*TMath::Exp(-0.00000*x)))+0.04101;
      else if (idx == 77  ) num = (0.91531*(TMath::Erf((x-2.21356)/1.21929)*TMath::Exp(-0.00000*x)))+0.04423;
      else if (idx == 78  ) num = (0.91829*(TMath::Erf((x-2.26671)/1.13958)*TMath::Exp(-0.00064*x)))+0.04262;
      else if (idx == 79  ) num = (0.91452*(TMath::Erf((x-2.23449)/1.16208)*TMath::Exp(-0.00000*x)))+0.04178;
      else if (idx == 80  ) num = (0.91883*(TMath::Erf((x-2.26213)/1.14875)*TMath::Exp(-0.00000*x)))+0.04345;
      else if (idx == 81  ) num = (0.91560*(TMath::Erf((x-2.25953)/1.13956)*TMath::Exp(-0.00000*x)))+0.04061;
      else if (idx == 82  ) num = (0.91408*(TMath::Erf((x-2.23898)/1.16638)*TMath::Exp(-0.00003*x)))+0.04108;
      else if (idx == 83  ) num = (0.91687*(TMath::Erf((x-2.24909)/1.18231)*TMath::Exp(-0.00000*x)))+0.04327;
      else if (idx == 84  ) num = (0.91638*(TMath::Erf((x-2.26237)/1.13921)*TMath::Exp(-0.00000*x)))+0.04122;
      else if (idx == 85  ) num = (0.91490*(TMath::Erf((x-2.23999)/1.17185)*TMath::Exp(-0.00000*x)))+0.04189;
      else if (idx == 86  ) num = (0.91427*(TMath::Erf((x-2.22135)/1.19577)*TMath::Exp(-0.00000*x)))+0.04235;
      else if (idx == 87  ) num = (0.91765*(TMath::Erf((x-2.20885)/1.22987)*TMath::Exp(-0.00135*x)))+0.04667;
      else if (idx == 88  ) num = (0.91493*(TMath::Erf((x-2.23762)/1.16496)*TMath::Exp(-0.00000*x)))+0.04199;
      else if (idx == 89  ) num = (0.91354*(TMath::Erf((x-2.24043)/1.16732)*TMath::Exp(-0.00000*x)))+0.04061;
      else if (idx == 90  ) num = (0.91669*(TMath::Erf((x-2.24022)/1.17043)*TMath::Exp(-0.00000*x)))+0.04354;
      else if (idx == 91  ) num = (0.91815*(TMath::Erf((x-2.24499)/1.17417)*TMath::Exp(-0.00119*x)))+0.04451;
      else if (idx == 92  ) num = (0.91556*(TMath::Erf((x-2.22880)/1.19251)*TMath::Exp(-0.00000*x)))+0.04313;
      else if (idx == 93  ) num = (0.91590*(TMath::Erf((x-2.25187)/1.15998)*TMath::Exp(-0.00000*x)))+0.04179;
      else if (idx == 94  ) num = (0.91475*(TMath::Erf((x-2.22202)/1.19631)*TMath::Exp(-0.00000*x)))+0.04285;
      else if (idx == 95  ) num = (0.91545*(TMath::Erf((x-2.23933)/1.16607)*TMath::Exp(-0.00000*x)))+0.04236;
      else if (idx == 96  ) num = (0.91638*(TMath::Erf((x-2.27566)/1.12569)*TMath::Exp(-0.00000*x)))+0.04032;
      else if (idx == 97  ) num = (0.91827*(TMath::Erf((x-2.25203)/1.18323)*TMath::Exp(-0.00000*x)))+0.04448;
      else if (idx == 98  ) num = (0.91873*(TMath::Erf((x-2.22044)/1.21240)*TMath::Exp(-0.00159*x)))+0.04667;
      else if (idx == 99  ) num = (0.91738*(TMath::Erf((x-2.26136)/1.14473)*TMath::Exp(-0.00000*x)))+0.04214;
      else if (idx == 100 ) num = (0.91590*(TMath::Erf((x-2.24495)/1.17456)*TMath::Exp(-0.00000*x)))+0.04252;
   }
   else if (fabs(eta)<2.1)
   {
      if (idx==0) num = (0.34844*(TMath::Erf((x-2.42840)/1.83954)*TMath::Exp(-0.04675*x)))+0.66739;
      else if (idx == -1   ) num = (0.41766*(TMath::Erf((x-2.10696)/2.12556)*TMath::Exp(-0.03957*x)))+0.60680;
      else if (idx == -2   ) num = (0.31867*(TMath::Erf((x-2.56424)/1.67845)*TMath::Exp(-0.04915*x)))+0.68905;
      else if (idx == 1   ) num = (0.98606*(TMath::Erf((x-0.34625)/3.52546)*TMath::Exp(-0.02754*x)))+0.12205;
      else if (idx == 2   ) num = (0.92956*(TMath::Erf((x-0.39451)/3.29197)*TMath::Exp(-0.02271*x)))+0.13735;
      else if (idx == 3   ) num = (0.55061*(TMath::Erf((x-1.59642)/2.42317)*TMath::Exp(-0.03070*x)))+0.47850;
      else if (idx == 4   ) num = (0.66956*(TMath::Erf((x-1.16638)/2.75609)*TMath::Exp(-0.02383*x)))+0.36856;
      else if (idx == 5   ) num = (0.19726*(TMath::Erf((x-3.12221)/0.95883)*TMath::Exp(-0.05524*x)))+0.77702;
      else if (idx == 6   ) num = (0.17669*(TMath::Erf((x-3.04011)/0.92640)*TMath::Exp(-0.02881*x)))+0.76831;
      else if (idx == 7   ) num = (0.36331*(TMath::Erf((x-2.42567)/2.00163)*TMath::Exp(-0.05129*x)))+0.67213;
      else if (idx == 8   ) num = (0.20325*(TMath::Erf((x-2.90687)/1.11376)*TMath::Exp(-0.02529*x)))+0.74331;
      else if (idx == 9   ) num = (0.35753*(TMath::Erf((x-2.40106)/2.01298)*TMath::Exp(-0.05180*x)))+0.67100;
      else if (idx == 10  ) num = (0.22486*(TMath::Erf((x-2.98020)/1.19159)*TMath::Exp(-0.05309*x)))+0.75860;
      else if (idx == 11  ) num = (0.19997*(TMath::Erf((x-3.05150)/1.06847)*TMath::Exp(-0.05300*x)))+0.77138;
      else if (idx == 12  ) num = (0.17315*(TMath::Erf((x-3.08381)/0.93228)*TMath::Exp(-0.03695*x)))+0.77731;
      else if (idx == 13  ) num = (0.82763*(TMath::Erf((x-0.75201)/2.84778)*TMath::Exp(-0.01819*x)))+0.19915;
      else if (idx == 14  ) num = (0.56221*(TMath::Erf((x-1.53363)/2.32000)*TMath::Exp(-0.02122*x)))+0.44494;
      else if (idx == 15  ) num = (0.51934*(TMath::Erf((x-1.63827)/2.54485)*TMath::Exp(-0.03045*x)))+0.51000;
      else if (idx == 16  ) num = (0.56042*(TMath::Erf((x-1.77027)/2.44976)*TMath::Exp(-0.04624*x)))+0.51466;
      else if (idx == 17  ) num = (0.34032*(TMath::Erf((x-2.43542)/1.68754)*TMath::Exp(-0.04503*x)))+0.66524;
      else if (idx == 18  ) num = (0.92468*(TMath::Erf((x-0.52108)/3.09878)*TMath::Exp(-0.02195*x)))+0.13162;
      else if (idx == 19  ) num = (0.97589*(TMath::Erf((x-0.42845)/3.29236)*TMath::Exp(-0.02397*x)))+0.10661;
      else if (idx == 20  ) num = (0.52171*(TMath::Erf((x-1.66719)/2.20460)*TMath::Exp(-0.02439*x)))+0.47960;
      else if (idx == 21  ) num = (0.95714*(TMath::Erf((x-0.50765)/2.93934)*TMath::Exp(-0.01645*x)))+0.07665;
      else if (idx == 22  ) num = (0.52812*(TMath::Erf((x-1.71999)/2.29539)*TMath::Exp(-0.03288*x)))+0.50165;
      else if (idx == 23  ) num = (0.21806*(TMath::Erf((x-3.05126)/1.07145)*TMath::Exp(-0.06760*x)))+0.77147;
      else if (idx == 24  ) num = (0.20033*(TMath::Erf((x-3.11978)/0.99375)*TMath::Exp(-0.06188*x)))+0.77702;
      else if (idx == 25  ) num = (0.22251*(TMath::Erf((x-3.05029)/1.13496)*TMath::Exp(-0.05607*x)))+0.76696;
      else if (idx == 26  ) num = (0.35061*(TMath::Erf((x-2.43754)/1.77577)*TMath::Exp(-0.04655*x)))+0.66730;
      else if (idx == 27  ) num = (0.99507*(TMath::Erf((x-0.36481)/3.67458)*TMath::Exp(-0.03004*x)))+0.13955;
      else if (idx == 28  ) num = (0.78858*(TMath::Erf((x-0.88956)/2.84612)*TMath::Exp(-0.02149*x)))+0.25020;
      else if (idx == 29  ) num = (0.45086*(TMath::Erf((x-1.96659)/2.11859)*TMath::Exp(-0.03585*x)))+0.56900;
      else if (idx == 30  ) num = (0.97895*(TMath::Erf((x-0.43611)/3.36280)*TMath::Exp(-0.02556*x)))+0.11776;
      else if (idx == 31  ) num = (0.22547*(TMath::Erf((x-2.91153)/1.28905)*TMath::Exp(-0.03692*x)))+0.74581;
      else if (idx == 32  ) num = (0.91683*(TMath::Erf((x-0.56920)/2.96710)*TMath::Exp(-0.01798*x)))+0.11662;
      else if (idx == 33  ) num = (0.28717*(TMath::Erf((x-2.89872)/1.54706)*TMath::Exp(-0.07190*x)))+0.74097;
      else if (idx == 34  ) num = (0.21731*(TMath::Erf((x-2.90506)/1.30542)*TMath::Exp(-0.03655*x)))+0.74660;
      else if (idx == 35  ) num = (0.22306*(TMath::Erf((x-2.89206)/1.21125)*TMath::Exp(-0.04111*x)))+0.74501;
      else if (idx == 36  ) num = (0.35652*(TMath::Erf((x-2.36220)/1.83709)*TMath::Exp(-0.04330*x)))+0.65707;
      else if (idx == 37  ) num = (0.30338*(TMath::Erf((x-2.62022)/1.60007)*TMath::Exp(-0.04676*x)))+0.69976;
      else if (idx == 38  ) num = (0.80758*(TMath::Erf((x-0.88769)/3.15926)*TMath::Exp(-0.03204*x)))+0.29159;
      else if (idx == 39  ) num = (0.93133*(TMath::Erf((x-0.45163)/3.08495)*TMath::Exp(-0.01711*x)))+0.10271;
      else if (idx == 40  ) num = (0.28332*(TMath::Erf((x-2.57355)/1.59773)*TMath::Exp(-0.03197*x)))+0.69258;
      else if (idx == 41  ) num = (0.23537*(TMath::Erf((x-2.93664)/1.25978)*TMath::Exp(-0.05776*x)))+0.75510;
      else if (idx == 42  ) num = (0.33319*(TMath::Erf((x-2.40753)/1.82646)*TMath::Exp(-0.03711*x)))+0.66759;
      else if (idx == 43  ) num = (0.18912*(TMath::Erf((x-3.08258)/1.07116)*TMath::Exp(-0.03446*x)))+0.76874;
      else if (idx == 44  ) num = (0.93223*(TMath::Erf((x-0.41033)/3.10451)*TMath::Exp(-0.01441*x)))+0.09671;
      else if (idx == 45  ) num = (0.50117*(TMath::Erf((x-1.67507)/2.22412)*TMath::Exp(-0.02517*x)))+0.50153;
      else if (idx == 46  ) num = (0.38227*(TMath::Erf((x-2.46335)/1.90357)*TMath::Exp(-0.06190*x)))+0.67122;
      else if (idx == 47  ) num = (0.22082*(TMath::Erf((x-3.03582)/1.17328)*TMath::Exp(-0.05979*x)))+0.76753;
      else if (idx == 48  ) num = (0.88416*(TMath::Erf((x-0.60615)/3.08067)*TMath::Exp(-0.02096*x)))+0.16958;
      else if (idx == 49  ) num = (0.23618*(TMath::Erf((x-2.85780)/1.29683)*TMath::Exp(-0.04258*x)))+0.74345;
      else if (idx == 50  ) num = (0.29170*(TMath::Erf((x-2.63632)/1.57637)*TMath::Exp(-0.04471*x)))+0.70373;
      else if (idx == 51  ) num = (0.35723*(TMath::Erf((x-2.41712)/1.84671)*TMath::Exp(-0.05244*x)))+0.66849;
      else if (idx == 52  ) num = (0.85447*(TMath::Erf((x-0.74043)/2.88116)*TMath::Exp(-0.02185*x)))+0.18992;
      else if (idx == 53  ) num = (0.31080*(TMath::Erf((x-2.73857)/1.63979)*TMath::Exp(-0.05951*x)))+0.71785;
      else if (idx == 54  ) num = (0.19118*(TMath::Erf((x-3.05885)/0.97559)*TMath::Exp(-0.04578*x)))+0.77077;
      else if (idx == 55  ) num = (0.23273*(TMath::Erf((x-3.03149)/1.15138)*TMath::Exp(-0.07406*x)))+0.76988;
      else if (idx == 56  ) num = (0.32840*(TMath::Erf((x-2.39547)/1.89654)*TMath::Exp(-0.03672*x)))+0.66717;
      else if (idx == 57  ) num = (0.94312*(TMath::Erf((x-0.37747)/3.25109)*TMath::Exp(-0.01917*x)))+0.10701;
      else if (idx == 58  ) num = (0.98626*(TMath::Erf((x-0.39342)/3.35103)*TMath::Exp(-0.02390*x)))+0.10410;
      else if (idx == 59  ) num = (0.28311*(TMath::Erf((x-2.82334)/1.50227)*TMath::Exp(-0.06294*x)))+0.73293;
      else if (idx == 60  ) num = (0.48544*(TMath::Erf((x-1.84079)/2.22102)*TMath::Exp(-0.03223*x)))+0.53660;
      else if (idx == 61  ) num = (0.35954*(TMath::Erf((x-2.45024)/1.89194)*TMath::Exp(-0.05225*x)))+0.66844;
      else if (idx == 62  ) num = (0.20433*(TMath::Erf((x-3.05319)/1.12290)*TMath::Exp(-0.04776*x)))+0.77020;
      else if (idx == 63  ) num = (0.33934*(TMath::Erf((x-2.44293)/1.78934)*TMath::Exp(-0.04174*x)))+0.66498;
      else if (idx == 64  ) num = (0.73553*(TMath::Erf((x-0.94356)/2.86190)*TMath::Exp(-0.02107*x)))+0.29593;
      else if (idx == 65  ) num = (0.19263*(TMath::Erf((x-3.04487)/1.02329)*TMath::Exp(-0.04121*x)))+0.76970;
      else if (idx == 66  ) num = (0.31499*(TMath::Erf((x-2.51611)/1.78366)*TMath::Exp(-0.04105*x)))+0.68159;
      else if (idx == 67  ) num = (0.97314*(TMath::Erf((x-0.29400)/3.40047)*TMath::Exp(-0.02084*x)))+0.09566;
      else if (idx == 68  ) num = (0.54872*(TMath::Erf((x-1.63796)/2.41435)*TMath::Exp(-0.03636*x)))+0.48874;
      else if (idx == 69  ) num = (0.84812*(TMath::Erf((x-0.72677)/2.97132)*TMath::Exp(-0.02049*x)))+0.19740;
      else if (idx == 70  ) num = (0.97740*(TMath::Erf((x-0.24212)/3.33105)*TMath::Exp(-0.01759*x)))+0.06617;
      else if (idx == 71  ) num = (0.44042*(TMath::Erf((x-2.16681)/2.16466)*TMath::Exp(-0.04903*x)))+0.61069;
      else if (idx == 72  ) num = (0.29106*(TMath::Erf((x-2.59438)/1.59128)*TMath::Exp(-0.03653*x)))+0.69700;
      else if (idx == 73  ) num = (0.21354*(TMath::Erf((x-2.98755)/1.21430)*TMath::Exp(-0.04496*x)))+0.75912;
      else if (idx == 74  ) num = (0.19416*(TMath::Erf((x-3.10478)/0.93802)*TMath::Exp(-0.05252*x)))+0.77691;
      else if (idx == 75  ) num = (0.98515*(TMath::Erf((x-0.32343)/3.14781)*TMath::Exp(-0.01562*x)))+0.05130;
      else if (idx == 76  ) num = (0.19066*(TMath::Erf((x-2.98663)/1.04503)*TMath::Exp(-0.03299*x)))+0.76024;
      else if (idx == 77  ) num = (0.60121*(TMath::Erf((x-1.44503)/2.48964)*TMath::Exp(-0.02813*x)))+0.43059;
      else if (idx == 78  ) num = (0.95018*(TMath::Erf((x-0.24431)/3.28054)*TMath::Exp(-0.01554*x)))+0.08055;
      else if (idx == 79  ) num = (0.29152*(TMath::Erf((x-2.71664)/1.58926)*TMath::Exp(-0.04936*x)))+0.71420;
      else if (idx == 80  ) num = (0.83645*(TMath::Erf((x-0.61438)/3.10626)*TMath::Exp(-0.01951*x)))+0.19894;
      else if (idx == 81  ) num = (0.21382*(TMath::Erf((x-2.93329)/1.10851)*TMath::Exp(-0.04674*x)))+0.75659;
      else if (idx == 82  ) num = (0.91802*(TMath::Erf((x-0.38594)/3.38512)*TMath::Exp(-0.01954*x)))+0.14618;
      else if (idx == 83  ) num = (0.64480*(TMath::Erf((x-1.35441)/2.80624)*TMath::Exp(-0.03460*x)))+0.42445;
      else if (idx == 84  ) num = (0.29208*(TMath::Erf((x-2.77496)/1.45841)*TMath::Exp(-0.06376*x)))+0.72629;
      else if (idx == 85  ) num = (0.50329*(TMath::Erf((x-1.71188)/2.23493)*TMath::Exp(-0.02810*x)))+0.50209;
      else if (idx == 86  ) num = (0.36565*(TMath::Erf((x-2.45407)/1.81635)*TMath::Exp(-0.05470*x)))+0.66867;
      else if (idx == 87  ) num = (0.60620*(TMath::Erf((x-1.34506)/2.63652)*TMath::Exp(-0.02745*x)))+0.42722;
      else if (idx == 88  ) num = (0.39672*(TMath::Erf((x-2.10028)/2.00563)*TMath::Exp(-0.03004*x)))+0.60122;
      else if (idx == 89  ) num = (0.32743*(TMath::Erf((x-2.40928)/1.80779)*TMath::Exp(-0.03853*x)))+0.66401;
      else if (idx == 90  ) num = (0.34622*(TMath::Erf((x-2.42513)/1.78578)*TMath::Exp(-0.04874*x)))+0.66571;
      else if (idx == 91  ) num = (0.18033*(TMath::Erf((x-3.06503)/0.91306)*TMath::Exp(-0.03577*x)))+0.77136;
      else if (idx == 92  ) num = (0.58441*(TMath::Erf((x-1.39171)/2.45221)*TMath::Exp(-0.02100*x)))+0.41650;
      else if (idx == 93  ) num = (0.49394*(TMath::Erf((x-1.76932)/2.24226)*TMath::Exp(-0.02970*x)))+0.52318;
      else if (idx == 94  ) num = (0.95013*(TMath::Erf((x-0.50591)/3.08801)*TMath::Exp(-0.02079*x)))+0.10818;
      else if (idx == 95  ) num = (0.95441*(TMath::Erf((x-0.38257)/3.18652)*TMath::Exp(-0.01665*x)))+0.08774;
      else if (idx == 96  ) num = (0.46372*(TMath::Erf((x-1.91637)/2.29474)*TMath::Exp(-0.03974*x)))+0.56942;
      else if (idx == 97  ) num = (0.21306*(TMath::Erf((x-3.04485)/1.08285)*TMath::Exp(-0.05445*x)))+0.76924;
      else if (idx == 98  ) num = (0.15324*(TMath::Erf((x-3.01940)/0.74429)*TMath::Exp(-0.01371*x)))+0.76954;
      else if (idx == 99  ) num = (0.21822*(TMath::Erf((x-3.05144)/1.01727)*TMath::Exp(-0.06135*x)))+0.76794;
      else if (idx == 100 ) num = (0.21049*(TMath::Erf((x-2.91620)/1.24286)*TMath::Exp(-0.02410*x)))+0.74188;
   }
   else
   {
      if (idx==0) num = (0.46966*(TMath::Erf((x-0.49035)/2.40643)*TMath::Exp(-0.00715*x)))+0.45423;
      else if (idx == -1   ) num = (0.46984*(TMath::Erf((x-0.48605)/2.39891)*TMath::Exp(-0.00716*x)))+0.45439;
      else if (idx == -2   ) num = (0.46958*(TMath::Erf((x-0.49357)/2.41355)*TMath::Exp(-0.00710*x)))+0.45415;
      else if (idx == 1   ) num = (0.46600*(TMath::Erf((x-0.67911)/2.09606)*TMath::Exp(-0.00517*x)))+0.44736;
      else if (idx == 2   ) num = (0.47692*(TMath::Erf((x-0.11926)/3.11360)*TMath::Exp(-0.00875*x)))+0.46590;
      else if (idx == 3   ) num = (0.47115*(TMath::Erf((x-0.18845)/2.81839)*TMath::Exp(-0.00399*x)))+0.44898;
      else if (idx == 4   ) num = (0.45346*(TMath::Erf((x-0.65391)/1.94557)*TMath::Exp(-0.00006*x)))+0.43924;
      else if (idx == 5   ) num = (0.46830*(TMath::Erf((x-0.45314)/2.39493)*TMath::Exp(-0.00645*x)))+0.45352;
      else if (idx == 6   ) num = (0.48089*(TMath::Erf((x-0.46824)/2.19316)*TMath::Exp(-0.00001*x)))+0.41390;
      else if (idx == 7   ) num = (0.46104*(TMath::Erf((x-0.39623)/2.40150)*TMath::Exp(-0.00000*x)))+0.44890;
      else if (idx == 8   ) num = (0.47551*(TMath::Erf((x-0.28373)/2.80729)*TMath::Exp(-0.00847*x)))+0.46073;
      else if (idx == 9   ) num = (0.63735*(TMath::Erf((x-0.02429)/2.67383)*TMath::Exp(-0.01024*x)))+0.30407;
      else if (idx == 10  ) num = (0.46123*(TMath::Erf((x-0.80634)/1.84176)*TMath::Exp(-0.00184*x)))+0.44265;
      else if (idx == 11  ) num = (0.45932*(TMath::Erf((x-0.54875)/2.19503)*TMath::Exp(-0.00000*x)))+0.44414;
      else if (idx == 12  ) num = (0.60191*(TMath::Erf((x-0.01151)/2.76483)*TMath::Exp(-0.01259*x)))+0.34727;
      else if (idx == 13  ) num = (0.47341*(TMath::Erf((x-0.32608)/2.62191)*TMath::Exp(-0.00668*x)))+0.45387;
      else if (idx == 14  ) num = (0.46790*(TMath::Erf((x-0.57957)/2.28587)*TMath::Exp(-0.00826*x)))+0.45173;
      else if (idx == 15  ) num = (0.52837*(TMath::Erf((x-0.00926)/3.39781)*TMath::Exp(-0.02144*x)))+0.45092;
      else if (idx == 16  ) num = (0.46895*(TMath::Erf((x-0.42796)/2.46395)*TMath::Exp(-0.00477*x)))+0.45491;
      else if (idx == 17  ) num = (0.46201*(TMath::Erf((x-0.55432)/2.33964)*TMath::Exp(-0.00001*x)))+0.44784;
      else if (idx == 18  ) num = (0.49652*(TMath::Erf((x-0.19666)/3.16119)*TMath::Exp(-0.02232*x)))+0.47798;
      else if (idx == 19  ) num = (0.46152*(TMath::Erf((x-0.40297)/2.45333)*TMath::Exp(-0.00000*x)))+0.44650;
      else if (idx == 20  ) num = (0.48696*(TMath::Erf((x-0.20566)/3.10981)*TMath::Exp(-0.01637*x)))+0.47157;
      else if (idx == 21  ) num = (0.49084*(TMath::Erf((x-0.17707)/3.10697)*TMath::Exp(-0.02098*x)))+0.47431;
      else if (idx == 22  ) num = (0.64005*(TMath::Erf((x-0.00424)/6.34049)*TMath::Exp(-0.06996*x)))+0.58062;
      else if (idx == 23  ) num = (0.47072*(TMath::Erf((x-0.60809)/2.20996)*TMath::Exp(-0.00861*x)))+0.44910;
      else if (idx == 24  ) num = (0.46043*(TMath::Erf((x-0.77055)/1.90434)*TMath::Exp(-0.00190*x)))+0.44335;
      else if (idx == 25  ) num = (0.45431*(TMath::Erf((x-0.84448)/1.76636)*TMath::Exp(-0.00007*x)))+0.43736;
      else if (idx == 26  ) num = (0.50013*(TMath::Erf((x-0.61451)/2.53455)*TMath::Exp(-0.02409*x)))+0.47504;
      else if (idx == 27  ) num = (0.47302*(TMath::Erf((x-0.52479)/2.42150)*TMath::Exp(-0.00736*x)))+0.45643;
      else if (idx == 28  ) num = (0.46546*(TMath::Erf((x-0.50500)/2.30282)*TMath::Exp(-0.00467*x)))+0.44461;
      else if (idx == 29  ) num = (0.47186*(TMath::Erf((x-0.51065)/2.37613)*TMath::Exp(-0.00882*x)))+0.45530;
      else if (idx == 30  ) num = (0.47089*(TMath::Erf((x-0.35575)/2.58180)*TMath::Exp(-0.00833*x)))+0.45550;
      else if (idx == 31  ) num = (0.48483*(TMath::Erf((x-0.45881)/2.48702)*TMath::Exp(-0.01341*x)))+0.45923;
      else if (idx == 32  ) num = (0.50439*(TMath::Erf((x-0.26054)/3.20335)*TMath::Exp(-0.02606*x)))+0.48375;
      else if (idx == 33  ) num = (0.47287*(TMath::Erf((x-0.00347)/3.67745)*TMath::Exp(-0.02178*x)))+0.50667;
      else if (idx == 34  ) num = (0.47189*(TMath::Erf((x-0.05281)/3.05598)*TMath::Exp(-0.01064*x)))+0.46401;
      else if (idx == 35  ) num = (0.48844*(TMath::Erf((x-0.17639)/3.15514)*TMath::Exp(-0.01550*x)))+0.47146;
      else if (idx == 36  ) num = (0.48026*(TMath::Erf((x-0.32777)/2.66725)*TMath::Exp(-0.01229*x)))+0.45485;
      else if (idx == 37  ) num = (0.46781*(TMath::Erf((x-0.00017)/3.51845)*TMath::Exp(-0.02025*x)))+0.50037;
      else if (idx == 38  ) num = (0.46386*(TMath::Erf((x-0.81109)/1.90202)*TMath::Exp(-0.00446*x)))+0.44498;
      else if (idx == 39  ) num = (0.48310*(TMath::Erf((x-0.04417)/3.28801)*TMath::Exp(-0.01630*x)))+0.47334;
      else if (idx == 40  ) num = (0.46622*(TMath::Erf((x-0.52946)/2.27725)*TMath::Exp(-0.00193*x)))+0.44539;
      else if (idx == 41  ) num = (0.48692*(TMath::Erf((x-0.01393)/3.14005)*TMath::Exp(-0.00909*x)))+0.45273;
      else if (idx == 42  ) num = (0.45904*(TMath::Erf((x-0.68323)/2.07581)*TMath::Exp(-0.00000*x)))+0.44290;
      else if (idx == 43  ) num = (0.45722*(TMath::Erf((x-0.52994)/2.21623)*TMath::Exp(-0.00000*x)))+0.44433;
      else if (idx == 44  ) num = (0.46025*(TMath::Erf((x-0.49986)/2.24493)*TMath::Exp(-0.00000*x)))+0.44574;
      else if (idx == 45  ) num = (0.47353*(TMath::Erf((x-0.50368)/2.35622)*TMath::Exp(-0.00958*x)))+0.45658;
      else if (idx == 46  ) num = (0.51162*(TMath::Erf((x-0.29791)/3.29705)*TMath::Exp(-0.02664*x)))+0.48929;
      else if (idx == 47  ) num = (0.46059*(TMath::Erf((x-0.45416)/2.32819)*TMath::Exp(-0.00177*x)))+0.44501;
      else if (idx == 48  ) num = (0.46328*(TMath::Erf((x-0.61101)/2.15933)*TMath::Exp(-0.00000*x)))+0.44737;
      else if (idx == 49  ) num = (0.47179*(TMath::Erf((x-0.13700)/2.83970)*TMath::Exp(-0.01033*x)))+0.45983;
      else if (idx == 50  ) num = (0.46290*(TMath::Erf((x-0.00564)/3.90898)*TMath::Exp(-0.03018*x)))+0.53395;
      else if (idx == 51  ) num = (0.47020*(TMath::Erf((x-0.35082)/2.60623)*TMath::Exp(-0.00634*x)))+0.45336;
      else if (idx == 52  ) num = (0.48449*(TMath::Erf((x-0.08916)/3.15882)*TMath::Exp(-0.01672*x)))+0.47330;
      else if (idx == 53  ) num = (0.45951*(TMath::Erf((x-0.74966)/1.89145)*TMath::Exp(-0.00024*x)))+0.44015;
      else if (idx == 54  ) num = (0.46645*(TMath::Erf((x-0.83215)/1.86917)*TMath::Exp(-0.00564*x)))+0.44633;
      else if (idx == 55  ) num = (0.46416*(TMath::Erf((x-0.42221)/2.41527)*TMath::Exp(-0.00597*x)))+0.45067;
      else if (idx == 56  ) num = (0.45854*(TMath::Erf((x-0.45275)/2.23926)*TMath::Exp(-0.00087*x)))+0.43791;
      else if (idx == 57  ) num = (0.50448*(TMath::Erf((x-0.38715)/2.28237)*TMath::Exp(-0.00017*x)))+0.39662;
      else if (idx == 58  ) num = (0.46983*(TMath::Erf((x-0.69735)/2.07846)*TMath::Exp(-0.00744*x)))+0.45068;
      else if (idx == 59  ) num = (0.45840*(TMath::Erf((x-0.65511)/2.01268)*TMath::Exp(-0.00261*x)))+0.44209;
      else if (idx == 60  ) num = (0.49470*(TMath::Erf((x-0.16296)/3.18671)*TMath::Exp(-0.02064*x)))+0.47676;
      else if (idx == 61  ) num = (0.45982*(TMath::Erf((x-0.85657)/1.78932)*TMath::Exp(-0.00049*x)))+0.43992;
      else if (idx == 62  ) num = (0.50030*(TMath::Erf((x-0.11141)/3.42504)*TMath::Exp(-0.02278*x)))+0.48362;
      else if (idx == 63  ) num = (0.47046*(TMath::Erf((x-0.06463)/3.15032)*TMath::Exp(-0.00769*x)))+0.46261;
      else if (idx == 64  ) num = (0.47209*(TMath::Erf((x-0.52422)/2.37018)*TMath::Exp(-0.00902*x)))+0.45529;
      else if (idx == 65  ) num = (0.46755*(TMath::Erf((x-0.28964)/2.69359)*TMath::Exp(-0.00414*x)))+0.45495;
      else if (idx == 66  ) num = (0.45490*(TMath::Erf((x-0.72072)/1.93714)*TMath::Exp(-0.00003*x)))+0.44058;
      else if (idx == 67  ) num = (0.50886*(TMath::Erf((x-0.26254)/2.37796)*TMath::Exp(-0.00023*x)))+0.38832;
      else if (idx == 68  ) num = (0.46238*(TMath::Erf((x-0.32866)/2.50795)*TMath::Exp(-0.00000*x)))+0.44648;
      else if (idx == 69  ) num = (0.46478*(TMath::Erf((x-0.85936)/1.84542)*TMath::Exp(-0.00507*x)))+0.44428;
      else if (idx == 70  ) num = (0.46208*(TMath::Erf((x-0.61722)/2.17406)*TMath::Exp(-0.00000*x)))+0.44608;
      else if (idx == 71  ) num = (0.48371*(TMath::Erf((x-0.29986)/2.85392)*TMath::Exp(-0.01443*x)))+0.46607;
      else if (idx == 72  ) num = (0.47121*(TMath::Erf((x-0.37454)/2.59811)*TMath::Exp(-0.00615*x)))+0.45302;
      else if (idx == 73  ) num = (0.47199*(TMath::Erf((x-0.38083)/2.66019)*TMath::Exp(-0.00722*x)))+0.45770;
      else if (idx == 74  ) num = (0.91844*(TMath::Erf((x-0.00227)/9.87151)*TMath::Exp(-0.09257*x)))+0.60562;
      else if (idx == 75  ) num = (0.47380*(TMath::Erf((x-0.54123)/2.38738)*TMath::Exp(-0.00891*x)))+0.45655;
      else if (idx == 76  ) num = (0.45930*(TMath::Erf((x-0.22934)/2.72916)*TMath::Exp(-0.00000*x)))+0.45137;
      else if (idx == 77  ) num = (0.46061*(TMath::Erf((x-0.82184)/1.87764)*TMath::Exp(-0.00013*x)))+0.44277;
      else if (idx == 78  ) num = (0.45559*(TMath::Erf((x-0.37117)/2.43872)*TMath::Exp(-0.00000*x)))+0.44788;
      else if (idx == 79  ) num = (0.50413*(TMath::Erf((x-0.00011)/4.68558)*TMath::Exp(-0.03772*x)))+0.55203;
      else if (idx == 80  ) num = (0.45922*(TMath::Erf((x-0.79219)/1.84311)*TMath::Exp(-0.00072*x)))+0.44096;
      else if (idx == 81  ) num = (0.45807*(TMath::Erf((x-0.24367)/2.57270)*TMath::Exp(-0.00019*x)))+0.45012;
      else if (idx == 82  ) num = (0.45663*(TMath::Erf((x-0.66609)/2.00535)*TMath::Exp(-0.00001*x)))+0.44188;
      else if (idx == 83  ) num = (0.47970*(TMath::Erf((x-0.38146)/2.59412)*TMath::Exp(-0.00778*x)))+0.45202;
      else if (idx == 84  ) num = (0.47141*(TMath::Erf((x-0.87187)/1.85984)*TMath::Exp(-0.00889*x)))+0.45001;
      else if (idx == 85  ) num = (0.46090*(TMath::Erf((x-0.80677)/1.93369)*TMath::Exp(-0.00259*x)))+0.44323;
      else if (idx == 86  ) num = (0.45641*(TMath::Erf((x-0.80082)/1.75842)*TMath::Exp(-0.00013*x)))+0.43797;
      else if (idx == 87  ) num = (0.45564*(TMath::Erf((x-1.02489)/1.52097)*TMath::Exp(-0.00000*x)))+0.43741;
      else if (idx == 88  ) num = (0.47429*(TMath::Erf((x-0.43210)/2.52407)*TMath::Exp(-0.00802*x)))+0.45352;
      else if (idx == 89  ) num = (0.46163*(TMath::Erf((x-0.63181)/2.03682)*TMath::Exp(-0.00243*x)))+0.44447;
      else if (idx == 90  ) num = (0.47158*(TMath::Erf((x-0.15015)/2.92293)*TMath::Exp(-0.00796*x)))+0.46129;
      else if (idx == 91  ) num = (0.46155*(TMath::Erf((x-0.53068)/2.24367)*TMath::Exp(-0.00000*x)))+0.44687;
      else if (idx == 92  ) num = (0.50277*(TMath::Erf((x-0.12519)/3.44181)*TMath::Exp(-0.02250*x)))+0.48563;
      else if (idx == 93  ) num = (0.46909*(TMath::Erf((x-0.56454)/2.26183)*TMath::Exp(-0.00379*x)))+0.44491;
      else if (idx == 94  ) num = (0.49849*(TMath::Erf((x-0.00730)/3.66396)*TMath::Exp(-0.02361*x)))+0.49015;
      else if (idx == 95  ) num = (0.45773*(TMath::Erf((x-0.67700)/2.01777)*TMath::Exp(-0.00013*x)))+0.44259;
      else if (idx == 96  ) num = (0.46384*(TMath::Erf((x-0.42174)/2.42757)*TMath::Exp(-0.00590*x)))+0.45047;
      else if (idx == 97  ) num = (0.47086*(TMath::Erf((x-0.61911)/2.15541)*TMath::Exp(-0.00351*x)))+0.44176;
      else if (idx == 98  ) num = (0.46237*(TMath::Erf((x-0.20028)/2.79741)*TMath::Exp(-0.00000*x)))+0.45492;
      else if (idx == 99  ) num = (0.46102*(TMath::Erf((x-0.70485)/2.01826)*TMath::Exp(-0.00002*x)))+0.44133;
      else if (idx == 100 ) num = (0.52455*(TMath::Erf((x-0.00249)/3.35289)*TMath::Exp(-0.02111*x)))+0.45048;
   }

   // return
   return num/den;
}

///////////////////////////////////////////////////
//             M U I D    P b P b                //
///////////////////////////////////////////////////

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!  ONLY FOR SYSTEMATICS! DO NOT APPLY FOR THE NOMINAL CORRECTION!!! !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

double tnp_weight_muid_pbpb(double x, double eta, int idx) {
   // denominator (from MC)
   double den=1;
   if (fabs(eta)<1.2) den = 0.99*TMath::Erf((x+1.16)/3.49);
   else if (fabs(eta)<1.8) den = 0.99*TMath::Erf((x+3.63)/4.27);
   else if (fabs(eta)<2.1) den = 1.00*TMath::Erf((x+4.64)/6.08);
   else den = 0.99*TMath::Erf((x+3.17)/4.98);

   // numerator (from data)
   double num=1;
   if (fabs(eta)<1.2) num = 0.98*TMath::Erf((x+0.39)/2.94);
   else if (fabs(eta)<1.8) num = 0.99*TMath::Erf((x+4.38)/5.03);
   else if (fabs(eta)<2.1) num = 1.00*TMath::Erf((x+5.26)/6.31);
   else num = 1.00*TMath::Erf((x+3.34)/5.38);

   return num/den;
}

///////////////////////////////////////////////////
//                 M U I D    P P                //
///////////////////////////////////////////////////

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!  ONLY FOR SYSTEMATICS! DO NOT APPLY FOR THE NOMINAL CORRECTION!!! !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

double tnp_weight_muid_pp(double x, double eta, int idx) {
   // binned
   if (idx == -10) {
      if (fabs(eta) < 1.2) {
         // 0 < |eta| < 1.2
         if (x<4) return 0.999016;
         else if (x<4.5) return 1.0032;
         else if (x<5) return 1.00129;
         else if (x<5.5) return 0.995773;
         else if (x<6) return 0.996447;
         else if (x<7) return 0.999116;
         else if (x<8) return 0.997846;
         else if (x<10.5) return 0.996956;
         else if (x<14) return 0.998218;
         else if (x<18) return 1.0025;
         else return 1.0019;
      } else if (fabs(eta)<1.8) {
         // 1.2 < |eta| < 1.8
         if (x<3) return 1.00141;
         else if (x<3.5) return 0.998122;
         else if (x<4) return 1.00036;
         else if (x<4.5) return 0.999239;
         else if (x<5) return 0.995965;
         else if (x<6) return 0.999212;
         else if (x<7) return 0.998085;
         else if (x<9) return 1.0001;
         else if (x<14) return 1.0001;
         else if (x<18) return 0.985798;
         else return 0.98404;
      } else if (fabs(eta)<2.1) {
         // 1.8 < |eta| < 2.1
         if (x<2.5) return 1.00627;
         else if (x<3) return 1.0015;
         else if (x<3.5) return 1.00118;
         else if (x<4) return 0.999083;
         else if (x<4.5) return 1.00139;
         else if (x<5) return 0.998681;
         else if (x<6) return 1.00311;
         else if (x<7) return 0.998239;
         else if (x<9) return 0.997688;
         else if (x<12) return 1.00159;
         else if (x<16) return 0.981826;
         else return 1.00123;
      } else {
         // 2.1 < |eta| < 2.4
         if (x<2.5) return 1.00186;
         else if (x<3) return 0.999581;
         else if (x<3.5) return 1.00009;
         else if (x<4) return 0.998081;
         else if (x<4.5) return 1.00169;
         else if (x<5) return 0.998405;
         else if (x<6.5) return 1.0008;
         else if (x<8.5) return 0.996034;
         else if (x<11) return 0.999455;
         else if (x<14) return 0.9939;
         else return 0.999963;
      }
   }

   // denominator (from MC)
   double den=1;
   if (fabs(eta)<1.2) den = (0.98383*TMath::Erf((x+0.47673)/2.94587))+0.00653;
   else if (fabs(eta)<1.8) den = (0.02768*TMath::Erf((x+8.66696)/28.28792))+0.97612;
   else if (fabs(eta)<2.1) den = (0.74373*TMath::Erf((x-0.30826)/1.07049))+0.25156;
   else den = (0.82009*TMath::Erf((x-1.22789)/0.48924))+0.17143;

   // numerator (from data)
   double num=1;
   if (fabs(eta)<1.2)
   {
      if (idx==0) num = (0.97976*TMath::Erf((x+0.74721)/3.10382))+0.00985;
      else if (idx == -1   ) num = (0.65054*TMath::Erf((x+0.52317)/3.22754))+0.33988;
      else if (idx == -2   ) num = (0.65043*TMath::Erf((x+1.05790)/3.61151))+0.33977;
      else if (idx == 1   ) num = (0.22226*TMath::Erf((x-0.32760)/3.47264))+0.77011;
      else if (idx == 2   ) num = (0.22308*TMath::Erf((x-2.27135)/1.55735))+0.76382;
      else if (idx == 3   ) num = (0.22181*TMath::Erf((x-1.36213)/2.56241))+0.76722;
      else if (idx == 4   ) num = (0.22279*TMath::Erf((x-1.28096)/2.54439))+0.76641;
      else if (idx == 5   ) num = (0.22341*TMath::Erf((x-1.69618)/2.09962))+0.76408;
      else if (idx == 6   ) num = (0.22345*TMath::Erf((x-1.07986)/2.84487))+0.76688;
      else if (idx == 7   ) num = (0.22347*TMath::Erf((x-1.58025)/2.26085))+0.76480;
      else if (idx == 8   ) num = (0.22476*TMath::Erf((x-1.81958)/2.03622))+0.76483;
      else if (idx == 9   ) num = (0.22417*TMath::Erf((x-1.44742)/2.52192))+0.76653;
      else if (idx == 10  ) num = (0.21207*TMath::Erf((x-0.82048)/3.03397))+0.77652;
      else if (idx == 11  ) num = (0.22312*TMath::Erf((x-0.62664)/3.27070))+0.76862;
      else if (idx == 12  ) num = (0.22358*TMath::Erf((x-1.15854)/2.65989))+0.76702;
      else if (idx == 13  ) num = (0.22141*TMath::Erf((x-1.23766)/2.60870))+0.76839;
      else if (idx == 14  ) num = (0.22312*TMath::Erf((x-0.90689)/2.94542))+0.76719;
      else if (idx == 15  ) num = (0.22439*TMath::Erf((x-1.75181)/2.09217))+0.76463;
      else if (idx == 16  ) num = (0.22330*TMath::Erf((x-2.06320)/1.74978))+0.76384;
      else if (idx == 17  ) num = (0.22061*TMath::Erf((x-1.13759)/2.70406))+0.76872;
      else if (idx == 18  ) num = (0.22368*TMath::Erf((x-1.42929)/2.50582))+0.76623;
      else if (idx == 19  ) num = (0.22226*TMath::Erf((x-1.26373)/2.53671))+0.76738;
      else if (idx == 20  ) num = (0.22218*TMath::Erf((x-1.29168)/2.55065))+0.76752;
      else if (idx == 21  ) num = (0.22252*TMath::Erf((x-1.51003)/2.41437))+0.76817;
      else if (idx == 22  ) num = (0.22298*TMath::Erf((x-1.57374)/2.20721))+0.76427;
      else if (idx == 23  ) num = (0.22414*TMath::Erf((x-1.61999)/2.22867))+0.76539;
      else if (idx == 24  ) num = (0.22316*TMath::Erf((x-0.83810)/3.10118))+0.76774;
      else if (idx == 25  ) num = (0.22341*TMath::Erf((x-2.06532)/1.75290))+0.76394;
      else if (idx == 26  ) num = (0.22444*TMath::Erf((x-1.81516)/2.09015))+0.76446;
      else if (idx == 27  ) num = (0.22378*TMath::Erf((x-1.46050)/2.40881))+0.76664;
      else if (idx == 28  ) num = (0.22331*TMath::Erf((x-0.88668)/2.96649))+0.76776;
      else if (idx == 29  ) num = (0.22198*TMath::Erf((x-1.31919)/2.51800))+0.76637;
      else if (idx == 30  ) num = (0.22355*TMath::Erf((x-0.94698)/2.96407))+0.76777;
      else if (idx == 31  ) num = (0.22202*TMath::Erf((x-0.21878)/3.69325))+0.76999;
      else if (idx == 32  ) num = (0.22375*TMath::Erf((x-1.07978)/2.84738))+0.76723;
      else if (idx == 33  ) num = (0.22423*TMath::Erf((x-1.74384)/2.08179))+0.76455;
      else if (idx == 34  ) num = (0.22400*TMath::Erf((x-1.21905)/2.65036))+0.76705;
      else if (idx == 35  ) num = (0.22363*TMath::Erf((x-1.52644)/2.26757))+0.76496;
      else if (idx == 36  ) num = (0.22096*TMath::Erf((x-1.16457)/2.64009))+0.76905;
      else if (idx == 37  ) num = (0.22446*TMath::Erf((x-1.69405)/2.15682))+0.76515;
      else if (idx == 38  ) num = (0.22427*TMath::Erf((x-1.70810)/2.13150))+0.76499;
      else if (idx == 39  ) num = (0.22091*TMath::Erf((x-0.08550)/3.79812))+0.77101;
      else if (idx == 40  ) num = (0.22374*TMath::Erf((x-1.83272)/2.00067))+0.76391;
      else if (idx == 41  ) num = (0.22333*TMath::Erf((x-2.04743)/1.73945))+0.76390;
      else if (idx == 42  ) num = (0.22425*TMath::Erf((x-1.41671)/2.51656))+0.76658;
      else if (idx == 43  ) num = (0.22406*TMath::Erf((x-2.06987)/1.75752))+0.76455;
      else if (idx == 44  ) num = (0.22343*TMath::Erf((x-1.34001)/2.59368))+0.76605;
      else if (idx == 45  ) num = (0.22421*TMath::Erf((x-1.93528)/1.89326))+0.76447;
      else if (idx == 46  ) num = (0.22331*TMath::Erf((x-1.51424)/2.27210))+0.76501;
      else if (idx == 47  ) num = (0.22361*TMath::Erf((x-0.75411)/3.14467))+0.76818;
      else if (idx == 48  ) num = (0.22391*TMath::Erf((x-1.45136)/2.47338))+0.76777;
      else if (idx == 49  ) num = (0.22102*TMath::Erf((x-0.07034)/3.78901))+0.77121;
      else if (idx == 50  ) num = (0.22432*TMath::Erf((x-1.73221)/2.14686))+0.76478;
      else if (idx == 51  ) num = (0.21772*TMath::Erf((x-0.89904)/2.93879))+0.77159;
      else if (idx == 52  ) num = (0.22457*TMath::Erf((x-1.82033)/2.08633))+0.76455;
      else if (idx == 53  ) num = (0.22389*TMath::Erf((x-1.61081)/2.22264))+0.76529;
      else if (idx == 54  ) num = (0.22394*TMath::Erf((x-1.91426)/1.93619))+0.76422;
      else if (idx == 55  ) num = (0.22385*TMath::Erf((x-1.66396)/2.22636))+0.76554;
      else if (idx == 56  ) num = (0.22236*TMath::Erf((x-0.60005)/3.18714))+0.76824;
      else if (idx == 57  ) num = (0.22202*TMath::Erf((x-0.66949)/3.15748))+0.76715;
      else if (idx == 58  ) num = (0.22411*TMath::Erf((x-1.60716)/2.23292))+0.76540;
      else if (idx == 59  ) num = (0.22458*TMath::Erf((x-1.76111)/2.13975))+0.76495;
      else if (idx == 60  ) num = (0.22057*TMath::Erf((x-1.12210)/2.70477))+0.76931;
      else if (idx == 61  ) num = (0.22383*TMath::Erf((x-1.11981)/2.83503))+0.76697;
      else if (idx == 62  ) num = (0.22179*TMath::Erf((x-1.33847)/2.61976))+0.76927;
      else if (idx == 63  ) num = (0.22282*TMath::Erf((x-0.52027)/3.42886))+0.76922;
      else if (idx == 64  ) num = (0.22176*TMath::Erf((x-1.29186)/2.57155))+0.76750;
      else if (idx == 65  ) num = (0.22245*TMath::Erf((x-0.60792)/3.25106))+0.76811;
      else if (idx == 66  ) num = (0.20985*TMath::Erf((x-0.63656)/3.31467))+0.78108;
      else if (idx == 67  ) num = (0.22460*TMath::Erf((x-1.75937)/2.10559))+0.76477;
      else if (idx == 68  ) num = (0.22455*TMath::Erf((x-1.71551)/2.19899))+0.76495;
      else if (idx == 69  ) num = (0.22260*TMath::Erf((x-1.41910)/2.43058))+0.76622;
      else if (idx == 70  ) num = (0.22026*TMath::Erf((x-1.24158)/2.65989))+0.76914;
      else if (idx == 71  ) num = (0.22270*TMath::Erf((x-0.77323)/3.11942))+0.76755;
      else if (idx == 72  ) num = (0.21991*TMath::Erf((x-1.21134)/2.63441))+0.76849;
      else if (idx == 73  ) num = (0.22121*TMath::Erf((x-0.27654)/3.46020))+0.76926;
      else if (idx == 74  ) num = (0.22073*TMath::Erf((x-1.10837)/2.69327))+0.76806;
      else if (idx == 75  ) num = (0.22325*TMath::Erf((x-1.31159)/2.52405))+0.76599;
      else if (idx == 76  ) num = (0.22386*TMath::Erf((x-1.07513)/2.82952))+0.76760;
      else if (idx == 77  ) num = (0.20997*TMath::Erf((x-0.61271)/3.32730))+0.78147;
      else if (idx == 78  ) num = (0.22344*TMath::Erf((x-0.95688)/2.92933))+0.76742;
      else if (idx == 79  ) num = (0.22147*TMath::Erf((x-0.38420)/3.36176))+0.76832;
      else if (idx == 80  ) num = (0.22221*TMath::Erf((x-1.34497)/2.52481))+0.76750;
      else if (idx == 81  ) num = (0.21713*TMath::Erf((x-0.94669)/2.87905))+0.77232;
      else if (idx == 82  ) num = (0.22417*TMath::Erf((x-1.79638)/2.07757))+0.76422;
      else if (idx == 83  ) num = (0.22343*TMath::Erf((x-1.45515)/2.41192))+0.76602;
      else if (idx == 84  ) num = (0.22009*TMath::Erf((x-1.18605)/2.69329))+0.76927;
      else if (idx == 85  ) num = (0.21461*TMath::Erf((x-0.99160)/2.91544))+0.77520;
      else if (idx == 86  ) num = (0.22174*TMath::Erf((x-1.34730)/2.60557))+0.76978;
      else if (idx == 87  ) num = (0.22145*TMath::Erf((x-1.15048)/2.72003))+0.76938;
      else if (idx == 88  ) num = (0.22332*TMath::Erf((x-0.59403)/3.25373))+0.76954;
      else if (idx == 89  ) num = (0.22321*TMath::Erf((x-1.36045)/2.46958))+0.76582;
      else if (idx == 90  ) num = (0.22074*TMath::Erf((x-1.17682)/2.61198))+0.76839;
      else if (idx == 91  ) num = (0.22098*TMath::Erf((x-1.21138)/2.63359))+0.76914;
      else if (idx == 92  ) num = (0.22308*TMath::Erf((x-1.58555)/2.21717))+0.76421;
      else if (idx == 93  ) num = (0.21968*TMath::Erf((x-1.14231)/2.65202))+0.76852;
      else if (idx == 94  ) num = (0.21605*TMath::Erf((x-0.95720)/2.87345))+0.77418;
      else if (idx == 95  ) num = (0.22391*TMath::Erf((x-1.50657)/2.36730))+0.76666;
      else if (idx == 96  ) num = (0.21867*TMath::Erf((x-1.02845)/2.70694))+0.77007;
      else if (idx == 97  ) num = (0.22367*TMath::Erf((x-1.40186)/2.47322))+0.76660;
      else if (idx == 98  ) num = (0.22373*TMath::Erf((x-1.45812)/2.41291))+0.76661;
      else if (idx == 99  ) num = (0.22188*TMath::Erf((x-1.31948)/2.38177))+0.76520;
      else if (idx == 100 ) num = (0.22426*TMath::Erf((x-2.09322)/1.77929))+0.76471;
   }
   else if (fabs(eta)<1.8)
   {
      if (idx==0) num = (0.65913*TMath::Erf((x+7.42715)/3.84453))+0.32953;
      else if (idx == -1   ) num = (0.00151*TMath::Erf((x-5.09442)/0.00003))+0.98928;
      else if (idx == -2   ) num = (0.00057*TMath::Erf((x-5.28933)/0.00171))+0.98778;
      else if (idx == 1   ) num = (0.52530*TMath::Erf((x-0.06952)/0.70490))+0.46160;
      else if (idx == 2   ) num = (0.52592*TMath::Erf((x-0.02702)/0.92731))+0.46224;
      else if (idx == 3   ) num = (0.52621*TMath::Erf((x-0.01039)/0.89925))+0.46253;
      else if (idx == 4   ) num = (0.52608*TMath::Erf((x-0.02522)/0.92311))+0.46240;
      else if (idx == 5   ) num = (0.52556*TMath::Erf((x-0.02738)/0.92864))+0.46188;
      else if (idx == 6   ) num = (0.52613*TMath::Erf((x-0.02101)/0.92029))+0.46245;
      else if (idx == 7   ) num = (0.52601*TMath::Erf((x-0.02672)/0.92616))+0.46233;
      else if (idx == 8   ) num = (0.52576*TMath::Erf((x-0.02725)/0.92633))+0.46208;
      else if (idx == 9   ) num = (0.52657*TMath::Erf((x-0.02744)/0.92756))+0.46289;
      else if (idx == 10  ) num = (0.52543*TMath::Erf((x-0.10134)/0.88556))+0.46175;
      else if (idx == 11  ) num = (0.52524*TMath::Erf((x-0.02753)/0.92900))+0.46157;
      else if (idx == 12  ) num = (0.52599*TMath::Erf((x-0.02621)/0.92584))+0.46231;
      else if (idx == 13  ) num = (0.52625*TMath::Erf((x-0.02254)/0.92145))+0.46257;
      else if (idx == 14  ) num = (0.52563*TMath::Erf((x-0.02725)/0.92625))+0.46195;
      else if (idx == 15  ) num = (0.52637*TMath::Erf((x-0.02714)/0.92745))+0.46269;
      else if (idx == 16  ) num = (0.52506*TMath::Erf((x-0.07525)/0.70441))+0.46138;
      else if (idx == 17  ) num = (0.52553*TMath::Erf((x-0.02740)/0.92860))+0.46185;
      else if (idx == 18  ) num = (0.52554*TMath::Erf((x-0.02726)/0.92650))+0.46186;
      else if (idx == 19  ) num = (0.52714*TMath::Erf((x-0.02757)/0.92893))+0.46346;
      else if (idx == 20  ) num = (0.52542*TMath::Erf((x-0.02752)/0.92883))+0.46174;
      else if (idx == 21  ) num = (0.52612*TMath::Erf((x-0.02215)/0.92145))+0.46244;
      else if (idx == 22  ) num = (0.52626*TMath::Erf((x-0.02345)/0.92316))+0.46258;
      else if (idx == 23  ) num = (0.52536*TMath::Erf((x-0.02761)/0.92950))+0.46168;
      else if (idx == 24  ) num = (0.52695*TMath::Erf((x-0.70272)/1.06322))+0.46327;
      else if (idx == 25  ) num = (0.52639*TMath::Erf((x-0.02721)/0.92685))+0.46271;
      else if (idx == 26  ) num = (0.00127*TMath::Erf((x-8.90581)/9.46294))+0.99070;
      else if (idx == 27  ) num = (0.51934*TMath::Erf((x-0.64332)/1.07688))+0.46832;
      else if (idx == 28  ) num = (0.52534*TMath::Erf((x-0.02733)/0.92720))+0.46166;
      else if (idx == 29  ) num = (0.52606*TMath::Erf((x-0.02740)/0.92856))+0.46237;
      else if (idx == 30  ) num = (0.52753*TMath::Erf((x-0.02760)/0.92908))+0.46385;
      else if (idx == 31  ) num = (0.52623*TMath::Erf((x-0.02506)/0.92602))+0.46255;
      else if (idx == 32  ) num = (0.52690*TMath::Erf((x-0.02755)/0.92864))+0.46322;
      else if (idx == 33  ) num = (0.52593*TMath::Erf((x-0.02679)/0.92761))+0.46225;
      else if (idx == 34  ) num = (0.52601*TMath::Erf((x-0.02723)/0.92778))+0.46233;
      else if (idx == 35  ) num = (0.52650*TMath::Erf((x-0.02739)/0.92644))+0.46282;
      else if (idx == 36  ) num = (0.52572*TMath::Erf((x-0.02737)/0.92809))+0.46204;
      else if (idx == 37  ) num = (0.52641*TMath::Erf((x-0.02736)/0.92831))+0.46273;
      else if (idx == 38  ) num = (0.52668*TMath::Erf((x-0.02762)/0.92942))+0.46300;
      else if (idx == 39  ) num = (0.52631*TMath::Erf((x-0.02711)/0.92766))+0.46263;
      else if (idx == 40  ) num = (0.52656*TMath::Erf((x-0.02752)/0.92825))+0.46288;
      else if (idx == 41  ) num = (0.52528*TMath::Erf((x-0.77956)/0.98885))+0.46161;
      else if (idx == 42  ) num = (0.52660*TMath::Erf((x-0.02745)/0.92731))+0.46292;
      else if (idx == 43  ) num = (0.52622*TMath::Erf((x-0.02029)/0.91814))+0.46254;
      else if (idx == 44  ) num = (0.52636*TMath::Erf((x-0.02700)/0.92617))+0.46268;
      else if (idx == 45  ) num = (0.52604*TMath::Erf((x-0.02488)/0.92478))+0.46235;
      else if (idx == 46  ) num = (0.52636*TMath::Erf((x-0.02730)/0.92805))+0.46267;
      else if (idx == 47  ) num = (0.52636*TMath::Erf((x-0.02670)/0.92688))+0.46268;
      else if (idx == 48  ) num = (0.52591*TMath::Erf((x-0.02681)/0.92763))+0.46223;
      else if (idx == 49  ) num = (0.52635*TMath::Erf((x-0.02705)/0.92801))+0.46267;
      else if (idx == 50  ) num = (0.52637*TMath::Erf((x-0.02717)/0.92750))+0.46268;
      else if (idx == 51  ) num = (0.52662*TMath::Erf((x-0.88724)/0.97854))+0.46294;
      else if (idx == 52  ) num = (0.52598*TMath::Erf((x-0.02672)/0.92796))+0.46230;
      else if (idx == 53  ) num = (0.52635*TMath::Erf((x-0.02707)/0.92677))+0.46266;
      else if (idx == 54  ) num = (0.52611*TMath::Erf((x-0.01762)/0.91263))+0.46243;
      else if (idx == 55  ) num = (0.52708*TMath::Erf((x-0.02755)/0.92897))+0.46340;
      else if (idx == 56  ) num = (0.00097*TMath::Erf((x-9.00570)/6.73104))+0.98978;
      else if (idx == 57  ) num = (0.52647*TMath::Erf((x-0.02746)/0.92781))+0.46279;
      else if (idx == 58  ) num = (0.52590*TMath::Erf((x-0.02707)/0.92539))+0.46222;
      else if (idx == 59  ) num = (0.52560*TMath::Erf((x-0.78970)/0.93316))+0.46192;
      else if (idx == 60  ) num = (0.52625*TMath::Erf((x-0.02364)/0.92283))+0.46257;
      else if (idx == 61  ) num = (0.52572*TMath::Erf((x-0.10007)/0.88601))+0.46204;
      else if (idx == 62  ) num = (0.52723*TMath::Erf((x-0.02756)/0.92846))+0.46355;
      else if (idx == 63  ) num = (0.52565*TMath::Erf((x-0.10423)/0.88277))+0.46197;
      else if (idx == 64  ) num = (0.52639*TMath::Erf((x-0.02744)/0.92930))+0.46271;
      else if (idx == 65  ) num = (0.52668*TMath::Erf((x-0.02756)/0.92920))+0.46300;
      else if (idx == 66  ) num = (0.52694*TMath::Erf((x-0.02744)/0.92753))+0.46326;
      else if (idx == 67  ) num = (0.52576*TMath::Erf((x-0.02732)/0.92833))+0.46208;
      else if (idx == 68  ) num = (0.00131*TMath::Erf((x-8.90078)/7.81811))+0.98981;
      else if (idx == 69  ) num = (0.52625*TMath::Erf((x-0.02139)/0.91927))+0.46257;
      else if (idx == 70  ) num = (0.52643*TMath::Erf((x-0.02736)/0.92564))+0.46275;
      else if (idx == 71  ) num = (0.52577*TMath::Erf((x-0.02715)/0.92589))+0.46209;
      else if (idx == 72  ) num = (0.52696*TMath::Erf((x-0.02749)/0.92745))+0.46328;
      else if (idx == 73  ) num = (0.52647*TMath::Erf((x-0.02718)/0.92813))+0.46279;
      else if (idx == 74  ) num = (0.52606*TMath::Erf((x-0.02586)/0.92384))+0.46238;
      else if (idx == 75  ) num = (0.52619*TMath::Erf((x-0.00245)/0.87420))+0.46251;
      else if (idx == 76  ) num = (0.52599*TMath::Erf((x-0.02693)/0.92812))+0.46231;
      else if (idx == 77  ) num = (0.52652*TMath::Erf((x-0.02728)/0.92738))+0.46284;
      else if (idx == 78  ) num = (0.52592*TMath::Erf((x-0.02730)/0.92782))+0.46224;
      else if (idx == 79  ) num = (0.52639*TMath::Erf((x-0.02702)/0.92820))+0.46271;
      else if (idx == 80  ) num = (0.00330*TMath::Erf((x-5.94379)/1.46639))+0.99166;
      else if (idx == 81  ) num = (0.52625*TMath::Erf((x-0.02638)/0.92796))+0.46257;
      else if (idx == 82  ) num = (0.52574*TMath::Erf((x-0.02734)/0.92827))+0.46206;
      else if (idx == 83  ) num = (0.00140*TMath::Erf((x-8.89991)/7.95241))+0.98982;
      else if (idx == 84  ) num = (0.52643*TMath::Erf((x-0.02762)/0.92914))+0.46275;
      else if (idx == 85  ) num = (0.52598*TMath::Erf((x-0.02678)/0.92725))+0.46230;
      else if (idx == 86  ) num = (0.52600*TMath::Erf((x-0.02628)/0.92684))+0.46232;
      else if (idx == 87  ) num = (0.52483*TMath::Erf((x-0.56798)/0.51018))+0.46116;
      else if (idx == 88  ) num = (0.52623*TMath::Erf((x-0.01966)/0.91686))+0.46255;
      else if (idx == 89  ) num = (0.52526*TMath::Erf((x-0.02741)/0.92780))+0.46158;
      else if (idx == 90  ) num = (0.52712*TMath::Erf((x-0.02762)/0.92920))+0.46344;
      else if (idx == 91  ) num = (0.52488*TMath::Erf((x-0.07128)/0.70222))+0.46119;
      else if (idx == 92  ) num = (0.52640*TMath::Erf((x-0.02720)/0.92769))+0.46272;
      else if (idx == 93  ) num = (0.52638*TMath::Erf((x-0.02731)/0.92700))+0.46270;
      else if (idx == 94  ) num = (0.52626*TMath::Erf((x-0.02425)/0.92361))+0.46258;
      else if (idx == 95  ) num = (0.52655*TMath::Erf((x-0.02749)/0.92873))+0.46287;
      else if (idx == 96  ) num = (0.52625*TMath::Erf((x-0.83507)/0.95462))+0.46256;
      else if (idx == 97  ) num = (0.17566*TMath::Erf((x-0.00017)/1.86823))+0.81563;
      else if (idx == 98  ) num = (0.52481*TMath::Erf((x-0.62649)/0.47942))+0.46114;
      else if (idx == 99  ) num = (0.52668*TMath::Erf((x-0.02774)/0.92971))+0.46300;
      else if (idx == 100 ) num = (0.52632*TMath::Erf((x-0.02729)/0.92811))+0.46263;
   }
   else if (fabs(eta)<2.1)
   {
      if (idx==0) num = (0.99392*TMath::Erf((x-0.14813)/0.77299))+0.00001;
      else if (idx == -1   ) num = (0.00046*TMath::Erf((x-3.74800)/0.00020))+0.99443;
      else if (idx == -2   ) num = (0.00001*TMath::Erf((x+8.89205)/49.99955))+0.99366;
      else if (idx == 1   ) num = (0.52663*TMath::Erf((x-0.03036)/0.67421))+0.46340;
      else if (idx == 2   ) num = (0.52769*TMath::Erf((x-0.03037)/0.67424))+0.46445;
      else if (idx == 3   ) num = (0.52819*TMath::Erf((x-0.03037)/0.67415))+0.46495;
      else if (idx == 4   ) num = (0.52897*TMath::Erf((x-0.03045)/0.67441))+0.46573;
      else if (idx == 5   ) num = (0.52849*TMath::Erf((x-0.02920)/0.67309))+0.46525;
      else if (idx == 6   ) num = (0.52898*TMath::Erf((x-0.03042)/0.67429))+0.46574;
      else if (idx == 7   ) num = (0.52884*TMath::Erf((x-0.03037)/0.67422))+0.46560;
      else if (idx == 8   ) num = (0.52884*TMath::Erf((x-0.89584)/0.71325))+0.46560;
      else if (idx == 9   ) num = (0.52800*TMath::Erf((x-0.03037)/0.67427))+0.46476;
      else if (idx == 10  ) num = (0.52873*TMath::Erf((x-0.03039)/0.67421))+0.46549;
      else if (idx == 11  ) num = (0.52865*TMath::Erf((x-0.03013)/0.67403))+0.46542;
      else if (idx == 12  ) num = (0.52900*TMath::Erf((x-0.03040)/0.67426))+0.46576;
      else if (idx == 13  ) num = (0.52846*TMath::Erf((x-0.61261)/0.69273))+0.46523;
      else if (idx == 14  ) num = (0.52954*TMath::Erf((x-0.92181)/0.72451))+0.46630;
      else if (idx == 15  ) num = (0.52873*TMath::Erf((x-0.03034)/0.67424))+0.46550;
      else if (idx == 16  ) num = (0.52696*TMath::Erf((x-0.55732)/0.60221))+0.46373;
      else if (idx == 17  ) num = (0.52826*TMath::Erf((x-0.79124)/0.66189))+0.46503;
      else if (idx == 18  ) num = (0.52712*TMath::Erf((x-0.03041)/0.67427))+0.46388;
      else if (idx == 19  ) num = (0.52708*TMath::Erf((x-0.31980)/0.44356))+0.46385;
      else if (idx == 20  ) num = (0.52848*TMath::Erf((x-0.88385)/0.70520))+0.46524;
      else if (idx == 21  ) num = (0.52863*TMath::Erf((x-0.83126)/0.68427))+0.46539;
      else if (idx == 22  ) num = (0.52806*TMath::Erf((x-0.78340)/0.65739))+0.46482;
      else if (idx == 23  ) num = (0.52820*TMath::Erf((x-0.03034)/0.67419))+0.46496;
      else if (idx == 24  ) num = (0.52812*TMath::Erf((x-0.03035)/0.67420))+0.46489;
      else if (idx == 25  ) num = (0.52887*TMath::Erf((x-0.76272)/0.71090))+0.46563;
      else if (idx == 26  ) num = (0.52880*TMath::Erf((x-0.03038)/0.67420))+0.46556;
      else if (idx == 27  ) num = (0.52705*TMath::Erf((x-0.03035)/0.67417))+0.46382;
      else if (idx == 28  ) num = (0.52781*TMath::Erf((x-0.60672)/0.63253))+0.46458;
      else if (idx == 29  ) num = (0.52841*TMath::Erf((x-0.03024)/0.67407))+0.46517;
      else if (idx == 30  ) num = (0.52713*TMath::Erf((x-0.03034)/0.67191))+0.46389;
      else if (idx == 31  ) num = (0.52895*TMath::Erf((x-0.03042)/0.67417))+0.46572;
      else if (idx == 32  ) num = (0.52732*TMath::Erf((x-0.76079)/0.65377))+0.46409;
      else if (idx == 33  ) num = (0.52788*TMath::Erf((x-0.03037)/0.67415))+0.46464;
      else if (idx == 34  ) num = (0.52864*TMath::Erf((x-0.03014)/0.67405))+0.46540;
      else if (idx == 35  ) num = (0.52844*TMath::Erf((x-0.03030)/0.67398))+0.46520;
      else if (idx == 36  ) num = (0.52893*TMath::Erf((x-0.03042)/0.67431))+0.46570;
      else if (idx == 37  ) num = (0.52860*TMath::Erf((x-0.03046)/0.67380))+0.46536;
      else if (idx == 38  ) num = (0.52779*TMath::Erf((x-0.03037)/0.67425))+0.46455;
      else if (idx == 39  ) num = (0.52780*TMath::Erf((x-0.53367)/0.63672))+0.46456;
      else if (idx == 40  ) num = (0.52876*TMath::Erf((x-0.03044)/0.67415))+0.46552;
      else if (idx == 41  ) num = (0.52870*TMath::Erf((x-0.03033)/0.67422))+0.46546;
      else if (idx == 42  ) num = (0.52938*TMath::Erf((x-0.03043)/0.67429))+0.46614;
      else if (idx == 43  ) num = (0.52899*TMath::Erf((x-0.03040)/0.67424))+0.46575;
      else if (idx == 44  ) num = (0.52910*TMath::Erf((x-0.03047)/0.67445))+0.46587;
      else if (idx == 45  ) num = (0.52894*TMath::Erf((x-0.03042)/0.67434))+0.46570;
      else if (idx == 46  ) num = (0.52808*TMath::Erf((x-0.03039)/0.67412))+0.46485;
      else if (idx == 47  ) num = (0.52861*TMath::Erf((x-0.02978)/0.67370))+0.46537;
      else if (idx == 48  ) num = (0.52811*TMath::Erf((x-0.03037)/0.67421))+0.46487;
      else if (idx == 49  ) num = (0.52927*TMath::Erf((x-0.03060)/0.67482))+0.46603;
      else if (idx == 50  ) num = (0.52846*TMath::Erf((x-0.61925)/0.69523))+0.46522;
      else if (idx == 51  ) num = (0.52813*TMath::Erf((x-0.03038)/0.67430))+0.46489;
      else if (idx == 52  ) num = (0.52757*TMath::Erf((x-0.03038)/0.67387))+0.46434;
      else if (idx == 53  ) num = (0.52875*TMath::Erf((x-0.58778)/0.80005))+0.46552;
      else if (idx == 54  ) num = (0.52856*TMath::Erf((x-0.02727)/0.67132))+0.46532;
      else if (idx == 55  ) num = (0.52842*TMath::Erf((x-0.03002)/0.67390))+0.46518;
      else if (idx == 56  ) num = (0.52874*TMath::Erf((x-0.03033)/0.67422))+0.46550;
      else if (idx == 57  ) num = (0.52792*TMath::Erf((x-0.03036)/0.67421))+0.46468;
      else if (idx == 58  ) num = (0.52763*TMath::Erf((x-0.44158)/0.60619))+0.46439;
      else if (idx == 59  ) num = (0.52821*TMath::Erf((x-0.03037)/0.67416))+0.46497;
      else if (idx == 60  ) num = (0.52856*TMath::Erf((x-0.03053)/0.67394))+0.46532;
      else if (idx == 61  ) num = (0.52794*TMath::Erf((x-0.03037)/0.67415))+0.46470;
      else if (idx == 62  ) num = (0.52907*TMath::Erf((x-0.03041)/0.67426))+0.46583;
      else if (idx == 63  ) num = (0.52832*TMath::Erf((x-0.83123)/0.68561))+0.46508;
      else if (idx == 64  ) num = (0.52823*TMath::Erf((x-0.03038)/0.67428))+0.46499;
      else if (idx == 65  ) num = (0.52902*TMath::Erf((x-0.03041)/0.67427))+0.46578;
      else if (idx == 66  ) num = (0.52802*TMath::Erf((x-0.03037)/0.67419))+0.46478;
      else if (idx == 67  ) num = (0.52776*TMath::Erf((x-0.03038)/0.67426))+0.46453;
      else if (idx == 68  ) num = (0.52680*TMath::Erf((x-0.44578)/0.67480))+0.46357;
      else if (idx == 69  ) num = (0.52800*TMath::Erf((x-0.48907)/0.63418))+0.46477;
      else if (idx == 70  ) num = (0.52757*TMath::Erf((x-0.03038)/0.67427))+0.46433;
      else if (idx == 71  ) num = (0.52809*TMath::Erf((x-0.03037)/0.67413))+0.46485;
      else if (idx == 72  ) num = (0.52923*TMath::Erf((x-0.50147)/0.85754))+0.46600;
      else if (idx == 73  ) num = (0.52887*TMath::Erf((x-0.03039)/0.67424))+0.46563;
      else if (idx == 74  ) num = (0.52875*TMath::Erf((x-0.03036)/0.67419))+0.46551;
      else if (idx == 75  ) num = (0.52865*TMath::Erf((x-0.03021)/0.67408))+0.46541;
      else if (idx == 76  ) num = (0.52871*TMath::Erf((x-0.03037)/0.67425))+0.46547;
      else if (idx == 77  ) num = (0.52827*TMath::Erf((x-0.03052)/0.67376))+0.46503;
      else if (idx == 78  ) num = (0.52822*TMath::Erf((x-0.03032)/0.67418))+0.46498;
      else if (idx == 79  ) num = (0.52857*TMath::Erf((x-0.60648)/0.69078))+0.46533;
      else if (idx == 80  ) num = (0.52764*TMath::Erf((x-0.03037)/0.67420))+0.46441;
      else if (idx == 81  ) num = (0.52901*TMath::Erf((x-0.03042)/0.67429))+0.46577;
      else if (idx == 82  ) num = (0.52906*TMath::Erf((x-0.03040)/0.67426))+0.46582;
      else if (idx == 83  ) num = (0.52772*TMath::Erf((x-0.03037)/0.67421))+0.46449;
      else if (idx == 84  ) num = (0.52812*TMath::Erf((x-0.79417)/0.66444))+0.46488;
      else if (idx == 85  ) num = (0.52745*TMath::Erf((x-0.71711)/0.62148))+0.46421;
      else if (idx == 86  ) num = (0.52823*TMath::Erf((x-0.69450)/0.67582))+0.46500;
      else if (idx == 87  ) num = (0.52850*TMath::Erf((x-0.02181)/0.66582))+0.46527;
      else if (idx == 88  ) num = (0.52895*TMath::Erf((x-0.61019)/0.69094))+0.46573;
      else if (idx == 89  ) num = (0.52803*TMath::Erf((x-0.03042)/0.67431))+0.46479;
      else if (idx == 90  ) num = (0.52793*TMath::Erf((x-0.03037)/0.67418))+0.46470;
      else if (idx == 91  ) num = (0.52910*TMath::Erf((x-0.03041)/0.67424))+0.46587;
      else if (idx == 92  ) num = (0.52784*TMath::Erf((x-0.24572)/0.60020))+0.46460;
      else if (idx == 93  ) num = (0.52889*TMath::Erf((x-0.03043)/0.67433))+0.46566;
      else if (idx == 94  ) num = (0.52771*TMath::Erf((x-0.59528)/0.62771))+0.46448;
      else if (idx == 95  ) num = (0.52870*TMath::Erf((x-0.03032)/0.67416))+0.46546;
      else if (idx == 96  ) num = (0.52814*TMath::Erf((x-0.03037)/0.67428))+0.46490;
      else if (idx == 97  ) num = (0.52889*TMath::Erf((x-0.03041)/0.67424))+0.46566;
      else if (idx == 98  ) num = (0.52903*TMath::Erf((x-0.03041)/0.67427))+0.46580;
      else if (idx == 99  ) num = (0.52824*TMath::Erf((x-0.84779)/0.69516))+0.46500;
      else if (idx == 100 ) num = (0.52899*TMath::Erf((x-0.86047)/0.70195))+0.46575;
   }
   else
   {
      if (idx==0) num = (0.99005*TMath::Erf((x-0.34628)/0.89806))+0.00000;
      else if (idx == -1   ) num = (0.11224*TMath::Erf((x+2.97856)/3.62169))+0.87928;
      else if (idx == -2   ) num = (0.11202*TMath::Erf((x+2.90917)/3.67630))+0.87907;
      else if (idx == 1   ) num = (0.52674*TMath::Erf((x-0.46892)/0.95827))+0.46314;
      else if (idx == 2   ) num = (0.52734*TMath::Erf((x-0.42983)/0.96047))+0.46374;
      else if (idx == 3   ) num = (0.52667*TMath::Erf((x-0.41689)/0.95820))+0.46306;
      else if (idx == 4   ) num = (0.52607*TMath::Erf((x-0.02604)/0.71480))+0.46247;
      else if (idx == 5   ) num = (0.52696*TMath::Erf((x-0.05576)/0.93938))+0.46336;
      else if (idx == 6   ) num = (0.52597*TMath::Erf((x-0.50509)/0.89739))+0.46238;
      else if (idx == 7   ) num = (0.52804*TMath::Erf((x-0.13675)/1.01588))+0.46444;
      else if (idx == 8   ) num = (0.52715*TMath::Erf((x-0.42343)/0.95765))+0.46354;
      else if (idx == 9   ) num = (0.52588*TMath::Erf((x-0.16590)/0.89583))+0.46228;
      else if (idx == 10  ) num = (0.52705*TMath::Erf((x-0.29363)/0.95717))+0.46344;
      else if (idx == 11  ) num = (0.52722*TMath::Erf((x-0.41270)/0.95287))+0.46361;
      else if (idx == 12  ) num = (0.52629*TMath::Erf((x-0.16486)/0.64283))+0.46269;
      else if (idx == 13  ) num = (0.52725*TMath::Erf((x-0.28658)/0.95881))+0.46365;
      else if (idx == 14  ) num = (0.52555*TMath::Erf((x-0.39657)/0.94176))+0.46195;
      else if (idx == 15  ) num = (0.52534*TMath::Erf((x-0.40725)/0.90683))+0.46174;
      else if (idx == 16  ) num = (0.52783*TMath::Erf((x-0.11342)/1.00765))+0.46423;
      else if (idx == 17  ) num = (0.52580*TMath::Erf((x-0.00357)/1.32723))+0.46627;
      else if (idx == 18  ) num = (0.52555*TMath::Erf((x-0.06516)/0.86430))+0.46196;
      else if (idx == 19  ) num = (0.52736*TMath::Erf((x-0.41743)/0.95818))+0.46376;
      else if (idx == 20  ) num = (0.52579*TMath::Erf((x-0.36008)/0.92661))+0.46219;
      else if (idx == 21  ) num = (0.52517*TMath::Erf((x-0.12092)/0.86797))+0.46157;
      else if (idx == 22  ) num = (0.52587*TMath::Erf((x-0.24321)/0.91501))+0.46227;
      else if (idx == 23  ) num = (0.52572*TMath::Erf((x-0.35303)/0.92175))+0.46212;
      else if (idx == 24  ) num = (0.52705*TMath::Erf((x-0.41009)/0.95087))+0.46345;
      else if (idx == 25  ) num = (0.52600*TMath::Erf((x-0.43499)/0.95067))+0.46240;
      else if (idx == 26  ) num = (0.52598*TMath::Erf((x-0.30107)/0.92558))+0.46238;
      else if (idx == 27  ) num = (0.52741*TMath::Erf((x-0.42356)/0.95956))+0.46380;
      else if (idx == 28  ) num = (0.52585*TMath::Erf((x-0.42986)/0.94607))+0.46225;
      else if (idx == 29  ) num = (0.52654*TMath::Erf((x-0.34002)/0.93746))+0.46294;
      else if (idx == 30  ) num = (0.52622*TMath::Erf((x-0.01016)/0.91377))+0.46262;
      else if (idx == 31  ) num = (0.52688*TMath::Erf((x-0.03381)/0.91699))+0.46327;
      else if (idx == 32  ) num = (0.52553*TMath::Erf((x-0.29657)/0.90119))+0.46194;
      else if (idx == 33  ) num = (0.52585*TMath::Erf((x-0.00124)/0.82856))+0.46225;
      else if (idx == 34  ) num = (0.52618*TMath::Erf((x-0.02704)/0.72804))+0.46257;
      else if (idx == 35  ) num = (0.52624*TMath::Erf((x-0.42375)/0.94170))+0.46264;
      else if (idx == 36  ) num = (0.52536*TMath::Erf((x-0.24687)/0.88647))+0.46176;
      else if (idx == 37  ) num = (0.52552*TMath::Erf((x-0.00570)/0.80452))+0.46192;
      else if (idx == 38  ) num = (0.52667*TMath::Erf((x-0.53961)/0.92269))+0.46307;
      else if (idx == 39  ) num = (0.52546*TMath::Erf((x-0.10771)/0.86726))+0.46186;
      else if (idx == 40  ) num = (0.52750*TMath::Erf((x-0.41042)/0.95525))+0.46390;
      else if (idx == 41  ) num = (0.52672*TMath::Erf((x-0.20750)/0.94093))+0.46312;
      else if (idx == 42  ) num = (0.52706*TMath::Erf((x-0.54330)/0.95376))+0.46345;
      else if (idx == 43  ) num = (0.52696*TMath::Erf((x-0.15886)/0.97159))+0.46336;
      else if (idx == 44  ) num = (0.52769*TMath::Erf((x-0.26642)/0.97709))+0.46409;
      else if (idx == 45  ) num = (0.52683*TMath::Erf((x-0.03346)/0.91599))+0.46323;
      else if (idx == 46  ) num = (0.52656*TMath::Erf((x-0.37749)/0.93401))+0.46296;
      else if (idx == 47  ) num = (0.52653*TMath::Erf((x-0.28718)/0.94141))+0.46293;
      else if (idx == 48  ) num = (0.52851*TMath::Erf((x-0.41583)/0.95953))+0.46491;
      else if (idx == 49  ) num = (0.52590*TMath::Erf((x-0.04174)/0.68106))+0.46230;
      else if (idx == 50  ) num = (0.52495*TMath::Erf((x-0.17659)/0.59579))+0.46136;
      else if (idx == 51  ) num = (0.52666*TMath::Erf((x-0.11321)/0.93732))+0.46305;
      else if (idx == 52  ) num = (0.52591*TMath::Erf((x-0.02866)/0.69490))+0.46231;
      else if (idx == 53  ) num = (0.52720*TMath::Erf((x-0.35900)/0.95706))+0.46359;
      else if (idx == 54  ) num = (0.52667*TMath::Erf((x-0.40752)/0.94879))+0.46307;
      else if (idx == 55  ) num = (0.52592*TMath::Erf((x-0.14047)/0.89564))+0.46232;
      else if (idx == 56  ) num = (0.52578*TMath::Erf((x-0.21897)/0.90090))+0.46218;
      else if (idx == 57  ) num = (0.52672*TMath::Erf((x-0.43569)/0.95472))+0.46311;
      else if (idx == 58  ) num = (0.52673*TMath::Erf((x-0.25858)/0.94723))+0.46312;
      else if (idx == 59  ) num = (0.52592*TMath::Erf((x-0.19663)/0.92201))+0.46232;
      else if (idx == 60  ) num = (0.52574*TMath::Erf((x-0.13716)/0.88392))+0.46214;
      else if (idx == 61  ) num = (0.52723*TMath::Erf((x-0.54101)/0.92300))+0.46362;
      else if (idx == 62  ) num = (0.52590*TMath::Erf((x-0.12687)/0.89072))+0.46229;
      else if (idx == 63  ) num = (0.52628*TMath::Erf((x-0.43147)/0.92612))+0.46268;
      else if (idx == 64  ) num = (0.52668*TMath::Erf((x-0.42227)/0.94400))+0.46307;
      else if (idx == 65  ) num = (0.52728*TMath::Erf((x-0.10354)/0.98314))+0.46368;
      else if (idx == 66  ) num = (0.52632*TMath::Erf((x-0.34380)/0.93282))+0.46271;
      else if (idx == 67  ) num = (0.52588*TMath::Erf((x-0.32359)/0.89847))+0.46228;
      else if (idx == 68  ) num = (0.52750*TMath::Erf((x-0.27423)/0.98079))+0.46389;
      else if (idx == 69  ) num = (0.52627*TMath::Erf((x-0.50687)/0.94136))+0.46266;
      else if (idx == 70  ) num = (0.52800*TMath::Erf((x-0.50215)/0.97707))+0.46440;
      else if (idx == 71  ) num = (0.52624*TMath::Erf((x-0.37698)/0.93321))+0.46264;
      else if (idx == 72  ) num = (0.52677*TMath::Erf((x-0.39171)/0.94184))+0.46317;
      else if (idx == 73  ) num = (0.52681*TMath::Erf((x-0.40979)/0.95903))+0.46321;
      else if (idx == 74  ) num = (0.52647*TMath::Erf((x-0.00922)/0.88120))+0.46287;
      else if (idx == 75  ) num = (0.52683*TMath::Erf((x-0.39755)/0.94445))+0.46322;
      else if (idx == 76  ) num = (0.52735*TMath::Erf((x-0.54294)/0.92446))+0.46374;
      else if (idx == 77  ) num = (0.52776*TMath::Erf((x-0.56744)/0.94230))+0.46416;
      else if (idx == 78  ) num = (0.52686*TMath::Erf((x-0.25049)/0.95406))+0.46326;
      else if (idx == 79  ) num = (0.52656*TMath::Erf((x-0.28422)/0.94191))+0.46296;
      else if (idx == 80  ) num = (0.52687*TMath::Erf((x-0.29630)/0.95055))+0.46326;
      else if (idx == 81  ) num = (0.00167*TMath::Erf((x-8.70662)/8.05423))+0.99179;
      else if (idx == 82  ) num = (0.52685*TMath::Erf((x-0.26565)/0.95285))+0.46325;
      else if (idx == 83  ) num = (0.52722*TMath::Erf((x-0.41462)/0.95378))+0.46362;
      else if (idx == 84  ) num = (0.52643*TMath::Erf((x-0.38844)/0.93971))+0.46283;
      else if (idx == 85  ) num = (0.52641*TMath::Erf((x-0.55288)/0.93284))+0.46281;
      else if (idx == 86  ) num = (0.52675*TMath::Erf((x-0.04340)/0.93098))+0.46314;
      else if (idx == 87  ) num = (0.52671*TMath::Erf((x-0.52855)/0.91397))+0.46311;
      else if (idx == 88  ) num = (0.52662*TMath::Erf((x-0.38737)/0.93940))+0.46301;
      else if (idx == 89  ) num = (0.52679*TMath::Erf((x-0.03106)/0.91183))+0.46319;
      else if (idx == 90  ) num = (0.52685*TMath::Erf((x-0.03985)/0.92715))+0.46324;
      else if (idx == 91  ) num = (0.52809*TMath::Erf((x-0.33618)/0.98517))+0.46449;
      else if (idx == 92  ) num = (0.52664*TMath::Erf((x-0.30492)/0.94746))+0.46304;
      else if (idx == 93  ) num = (0.52701*TMath::Erf((x-0.48046)/0.96470))+0.46341;
      else if (idx == 94  ) num = (0.52558*TMath::Erf((x-0.07809)/0.85659))+0.46198;
      else if (idx == 95  ) num = (0.52704*TMath::Erf((x-0.38925)/0.94125))+0.46344;
      else if (idx == 96  ) num = (0.52570*TMath::Erf((x-0.20215)/0.89418))+0.46210;
      else if (idx == 97  ) num = (0.52722*TMath::Erf((x-0.45034)/0.96516))+0.46362;
      else if (idx == 98  ) num = (0.53496*TMath::Erf((x-0.22252)/1.04741))+0.45763;
      else if (idx == 99  ) num = (0.52726*TMath::Erf((x-0.45439)/0.96390))+0.46365;
      else if (idx == 100 ) num = (0.52498*TMath::Erf((x-0.28886)/0.87824))+0.46138;
   }

   // return
   return num/den;
}

///////////////////////////////////////////////////
//                   S T A    P P                //
///////////////////////////////////////////////////

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!  ONLY FOR SYSTEMATICS! DO NOT APPLY FOR THE NOMINAL CORRECTION!!! !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

double tnp_weight_sta_pp(double x, double eta, int idx) {
   // binned
   if (idx == -10) {
      if (fabs(eta) < 1.2) {
         // 0 < |eta| < 1.2
         if (x<4) return 1.03808;
         else if (x<4.5) return 1.00984;
         else if (x<5) return 1.01512;
         else if (x<5.5) return 1.00469;
         else if (x<6) return 1.00776;
         else if (x<7) return 0.997825;
         else if (x<8) return 0.996708;
         else if (x<9) return 1.00285;
         else if (x<14) return 0.998507;
         else return 1.00917;
      } else if (fabs(eta)<1.8) {
         // 1.2 < |eta| < 1.8
         if (x<3) return 1.04355;
         else if (x<3.5) return 1.02278;
         else if (x<4) return 1.01099;
         else if (x<4.5) return 0.999804;
         else if (x<5) return 1.00963;
         else if (x<6) return 1.01372;
         else if (x<7) return 1.00494;
         else if (x<8) return 1.02321;
         else if (x<9) return 1.00911;
         else if (x<14) return 1.01161;
         else return 1.03605;
      } else if (fabs(eta)<2.1) {
         // 1.8 < |eta| < 2.1
         if (x<2.5) return 1.03342;
         else if (x<3) return 1.00154;
         else if (x<3.5) return 1.00246;
         else if (x<4) return 1.01347;
         else if (x<4.5) return 0.997808;
         else if (x<5) return 1.01391;
         else if (x<6) return 1.01296;
         else if (x<7) return 1.01524;
         else if (x<10) return 0.992407;
         else return 1.0035;
      } else {
         // 2.1 < |eta| < 2.4
         if (x<2.5) return 1.02921;
         else if (x<3) return 1.00856;
         else if (x<3.5) return 0.989795;
         else if (x<4) return 0.96595;
         else if (x<4.5) return 0.974834;
         else if (x<5) return 0.975238;
         else if (x<6) return 1.01298;
         else if (x<7) return 1.01219;
         else if (x<10) return 1.00975;
         else return 1.00634;
      }
   }

   // denominator (from MC)
   double den=1;
   if (fabs(eta)<1.2) den = (0.58746*TMath::Erf((x-3.17585)/0.96599))+0.39714;
   else if (fabs(eta)<1.8) den = (0.51632*TMath::Erf((x-0.56984)/1.78604))+0.45932;
   else if (fabs(eta)<2.1) den = (0.51122*TMath::Erf((x-0.01449)/1.43367))+0.47344;
   else den = (0.43706*TMath::Erf((x-0.50936)/1.62531))+0.54785;

   // numerator (from data)
   double num=1;
   if (fabs(eta)<1.2)
   {
      if (idx==0) num = (0.52806*TMath::Erf((x-3.14214)/1.01709))+0.45965;
      else if (idx == -1   ) num = (0.53145*TMath::Erf((x-3.13538)/1.00320))+0.46288;
      else if (idx == -2   ) num = (0.52425*TMath::Erf((x-3.14802)/1.03003))+0.45617;
      else if (idx == 1   ) num = (0.52732*TMath::Erf((x-3.00821)/1.18646))+0.46382;
      else if (idx == 2   ) num = (0.52542*TMath::Erf((x-3.10948)/1.07637))+0.45856;
      else if (idx == 3   ) num = (0.52817*TMath::Erf((x-3.18153)/0.96716))+0.45842;
      else if (idx == 4   ) num = (0.52530*TMath::Erf((x-3.15326)/0.97512))+0.45642;
      else if (idx == 5   ) num = (0.52946*TMath::Erf((x-3.15344)/1.02933))+0.46068;
      else if (idx == 6   ) num = (0.52722*TMath::Erf((x-3.08052)/1.09655))+0.46092;
      else if (idx == 7   ) num = (0.52754*TMath::Erf((x-3.20101)/0.89540))+0.45682;
      else if (idx == 8   ) num = (0.52511*TMath::Erf((x-3.08851)/1.07923))+0.45888;
      else if (idx == 9   ) num = (0.52922*TMath::Erf((x-3.17724)/0.98635))+0.45965;
      else if (idx == 10  ) num = (0.52734*TMath::Erf((x-3.09522)/1.10036))+0.46086;
      else if (idx == 11  ) num = (0.52746*TMath::Erf((x-3.00920)/1.25762))+0.46420;
      else if (idx == 12  ) num = (0.52841*TMath::Erf((x-3.24713)/0.83499))+0.45586;
      else if (idx == 13  ) num = (0.52637*TMath::Erf((x-3.05892)/1.11269))+0.46097;
      else if (idx == 14  ) num = (0.52859*TMath::Erf((x-3.20595)/0.93288))+0.45771;
      else if (idx == 15  ) num = (0.52808*TMath::Erf((x-3.19212)/0.94549))+0.45802;
      else if (idx == 16  ) num = (0.52798*TMath::Erf((x-3.13891)/1.01023))+0.45964;
      else if (idx == 17  ) num = (0.52796*TMath::Erf((x-3.16654)/0.98850))+0.45883;
      else if (idx == 18  ) num = (0.52837*TMath::Erf((x-3.14532)/1.02015))+0.45986;
      else if (idx == 19  ) num = (0.52768*TMath::Erf((x-3.13564)/1.00829))+0.45944;
      else if (idx == 20  ) num = (0.52767*TMath::Erf((x-3.10299)/1.05943))+0.46069;
      else if (idx == 21  ) num = (0.52563*TMath::Erf((x-3.05365)/1.10282))+0.46033;
      else if (idx == 22  ) num = (0.52688*TMath::Erf((x-3.17277)/0.95607))+0.45747;
      else if (idx == 23  ) num = (0.52522*TMath::Erf((x-3.04635)/1.14833))+0.46042;
      else if (idx == 24  ) num = (0.52730*TMath::Erf((x-3.13277)/1.00565))+0.45917;
      else if (idx == 25  ) num = (0.52607*TMath::Erf((x-3.05410)/1.16424))+0.46121;
      else if (idx == 26  ) num = (0.52596*TMath::Erf((x-3.13463)/1.00934))+0.45793;
      else if (idx == 27  ) num = (0.52539*TMath::Erf((x-3.13123)/1.00658))+0.45751;
      else if (idx == 28  ) num = (0.52789*TMath::Erf((x-3.13850)/1.01511))+0.45960;
      else if (idx == 29  ) num = (0.52795*TMath::Erf((x-3.03997)/1.19275))+0.46352;
      else if (idx == 30  ) num = (0.52651*TMath::Erf((x-3.12471)/0.99341))+0.45862;
      else if (idx == 31  ) num = (0.52820*TMath::Erf((x-3.14198)/1.01983))+0.45980;
      else if (idx == 32  ) num = (0.52668*TMath::Erf((x-3.24001)/0.85045))+0.45463;
      else if (idx == 33  ) num = (0.52550*TMath::Erf((x-3.09583)/1.07317))+0.45911;
      else if (idx == 34  ) num = (0.52525*TMath::Erf((x-3.14903)/0.97112))+0.45815;
      else if (idx == 35  ) num = (0.52760*TMath::Erf((x-3.22200)/0.90168))+0.45642;
      else if (idx == 36  ) num = (0.52516*TMath::Erf((x-3.16276)/0.98789))+0.45819;
      else if (idx == 37  ) num = (0.52894*TMath::Erf((x-3.19286)/0.95460))+0.45869;
      else if (idx == 38  ) num = (0.52388*TMath::Erf((x-3.04652)/1.13780))+0.45902;
      else if (idx == 39  ) num = (0.52798*TMath::Erf((x-3.20118)/0.96850))+0.45780;
      else if (idx == 40  ) num = (0.52629*TMath::Erf((x-3.20059)/0.94776))+0.45624;
      else if (idx == 41  ) num = (0.52615*TMath::Erf((x-3.09321)/1.05043))+0.45945;
      else if (idx == 42  ) num = (0.52609*TMath::Erf((x-3.22029)/0.90937))+0.45522;
      else if (idx == 43  ) num = (0.52577*TMath::Erf((x-3.07245)/1.06466))+0.45993;
      else if (idx == 44  ) num = (0.53007*TMath::Erf((x-3.16965)/0.98177))+0.46062;
      else if (idx == 45  ) num = (0.52822*TMath::Erf((x-3.17170)/0.99844))+0.45890;
      else if (idx == 46  ) num = (0.52831*TMath::Erf((x-3.13452)/1.00817))+0.46004;
      else if (idx == 47  ) num = (0.52871*TMath::Erf((x-3.18797)/0.93995))+0.45864;
      else if (idx == 48  ) num = (0.52668*TMath::Erf((x-3.14675)/1.02375))+0.45834;
      else if (idx == 49  ) num = (0.52721*TMath::Erf((x-3.13721)/1.00894))+0.45898;
      else if (idx == 50  ) num = (0.52590*TMath::Erf((x-3.17402)/0.97309))+0.45674;
      else if (idx == 51  ) num = (0.52704*TMath::Erf((x-3.13816)/1.01042))+0.45880;
      else if (idx == 52  ) num = (0.52669*TMath::Erf((x-3.20236)/0.90052))+0.45611;
      else if (idx == 53  ) num = (0.52376*TMath::Erf((x-3.16352)/0.95051))+0.45498;
      else if (idx == 54  ) num = (0.52664*TMath::Erf((x-3.26836)/0.81717))+0.45377;
      else if (idx == 55  ) num = (0.52925*TMath::Erf((x-3.24998)/0.87026))+0.45681;
      else if (idx == 56  ) num = (0.52776*TMath::Erf((x-3.05991)/1.14238))+0.46248;
      else if (idx == 57  ) num = (0.52692*TMath::Erf((x-3.14825)/0.97047))+0.45978;
      else if (idx == 58  ) num = (0.52726*TMath::Erf((x-3.18855)/0.93893))+0.45722;
      else if (idx == 59  ) num = (0.52595*TMath::Erf((x-3.19613)/0.91852))+0.45584;
      else if (idx == 60  ) num = (0.52909*TMath::Erf((x-3.23347)/0.85368))+0.45705;
      else if (idx == 61  ) num = (0.52868*TMath::Erf((x-3.15242)/1.03012))+0.46002;
      else if (idx == 62  ) num = (0.52593*TMath::Erf((x-3.13785)/1.01431))+0.45784;
      else if (idx == 63  ) num = (0.52665*TMath::Erf((x-3.13810)/1.01365))+0.45847;
      else if (idx == 64  ) num = (0.52870*TMath::Erf((x-3.16098)/0.98932))+0.46115;
      else if (idx == 65  ) num = (0.52733*TMath::Erf((x-3.17061)/0.95244))+0.45792;
      else if (idx == 66  ) num = (0.52801*TMath::Erf((x-3.08834)/1.07034))+0.46150;
      else if (idx == 67  ) num = (0.52831*TMath::Erf((x-3.11586)/1.04241))+0.46074;
      else if (idx == 68  ) num = (0.52886*TMath::Erf((x-3.22580)/0.91974))+0.45742;
      else if (idx == 69  ) num = (0.52688*TMath::Erf((x-3.13549)/1.00923))+0.45873;
      else if (idx == 70  ) num = (0.52812*TMath::Erf((x-3.17774)/0.95976))+0.45849;
      else if (idx == 71  ) num = (0.52871*TMath::Erf((x-3.19362)/0.92308))+0.45833;
      else if (idx == 72  ) num = (0.52795*TMath::Erf((x-3.09509)/1.04845))+0.46120;
      else if (idx == 73  ) num = (0.52290*TMath::Erf((x-3.08736)/1.03130))+0.45672;
      else if (idx == 74  ) num = (0.52663*TMath::Erf((x-3.13495)/1.00769))+0.45852;
      else if (idx == 75  ) num = (0.52552*TMath::Erf((x-3.16908)/0.95582))+0.45637;
      else if (idx == 76  ) num = (0.52698*TMath::Erf((x-3.14258)/1.01763))+0.45867;
      else if (idx == 77  ) num = (0.52785*TMath::Erf((x-3.15813)/0.98634))+0.45904;
      else if (idx == 78  ) num = (0.52667*TMath::Erf((x-3.21879)/0.89072))+0.45550;
      else if (idx == 79  ) num = (0.52815*TMath::Erf((x-3.23146)/0.89567))+0.45654;
      else if (idx == 80  ) num = (0.52943*TMath::Erf((x-3.19792)/0.94807))+0.45896;
      else if (idx == 81  ) num = (0.52302*TMath::Erf((x-3.16785)/0.97467))+0.45429;
      else if (idx == 82  ) num = (0.52715*TMath::Erf((x-3.14094)/1.01698))+0.45886;
      else if (idx == 83  ) num = (0.52619*TMath::Erf((x-3.06379)/1.12714))+0.46080;
      else if (idx == 84  ) num = (0.52914*TMath::Erf((x-3.19483)/0.95476))+0.45893;
      else if (idx == 85  ) num = (0.52834*TMath::Erf((x-3.14959)/1.02914))+0.45977;
      else if (idx == 86  ) num = (0.52556*TMath::Erf((x-3.16307)/0.94253))+0.45654;
      else if (idx == 87  ) num = (0.52595*TMath::Erf((x-3.13316)/1.00810))+0.45796;
      else if (idx == 88  ) num = (0.52899*TMath::Erf((x-3.13670)/1.00812))+0.46060;
      else if (idx == 89  ) num = (0.52841*TMath::Erf((x-3.18265)/0.95994))+0.45845;
      else if (idx == 90  ) num = (0.52808*TMath::Erf((x-3.15169)/1.03009))+0.45950;
      else if (idx == 91  ) num = (0.52716*TMath::Erf((x-3.23915)/0.85238))+0.45525;
      else if (idx == 92  ) num = (0.52749*TMath::Erf((x-3.18529)/0.96399))+0.45773;
      else if (idx == 93  ) num = (0.52412*TMath::Erf((x-3.12691)/0.99839))+0.45644;
      else if (idx == 94  ) num = (0.52580*TMath::Erf((x-3.04481)/1.16104))+0.46127;
      else if (idx == 95  ) num = (0.52865*TMath::Erf((x-3.09725)/1.08272))+0.46189;
      else if (idx == 96  ) num = (0.52657*TMath::Erf((x-3.12943)/0.99887))+0.45857;
      else if (idx == 97  ) num = (0.52813*TMath::Erf((x-3.18301)/0.96180))+0.45830;
      else if (idx == 98  ) num = (0.52524*TMath::Erf((x-3.22204)/0.85851))+0.45403;
      else if (idx == 99  ) num = (0.52420*TMath::Erf((x-3.05893)/1.12943))+0.45923;
      else if (idx == 100 ) num = (0.52633*TMath::Erf((x-3.16584)/0.97034))+0.45726;
   }
   else if (fabs(eta)<1.8)
   {
      if (idx==0) num = (0.01753*TMath::Erf((x-5.24739)/9.24400))+0.98259;
      else if (idx == -1   ) num = (0.00345*TMath::Erf((x-8.43141)/9.74621))+0.99431;
      else if (idx == -2   ) num = (0.20268*TMath::Erf((x-0.06569)/3.15975))+0.78340;
      else if (idx == 1   ) num = (0.02123*TMath::Erf((x-2.21280)/5.60816))+0.96816;
      else if (idx == 2   ) num = (0.07298*TMath::Erf((x-0.74511)/3.86904))+0.91953;
      else if (idx == 3   ) num = (0.00008*TMath::Erf((x-0.23320)/3.20845))+0.98116;
      else if (idx == 4   ) num = (0.01284*TMath::Erf((x-2.85194)/2.91393))+0.97533;
      else if (idx == 5   ) num = (0.01024*TMath::Erf((x-4.74096)/1.95632))+0.98025;
      else if (idx == 6   ) num = (0.07849*TMath::Erf((x-1.43892)/1.68762))+0.90076;
      else if (idx == 7   ) num = (0.00536*TMath::Erf((x-6.47107)/0.00603))+0.98578;
      else if (idx == 8   ) num = (0.01119*TMath::Erf((x-9.56506)/9.99459))+0.98739;
      else if (idx == 9   ) num = (0.00297*TMath::Erf((x-9.99732)/9.97056))+0.98424;
      else if (idx == 10  ) num = (0.00092*TMath::Erf((x-3.40668)/3.90063))+0.97684;
      else if (idx == 11  ) num = (0.17787*TMath::Erf((x-2.42570)/0.39688))+0.80253;
      else if (idx == 12  ) num = (0.00000*TMath::Erf((x-5.50635)/9.91138))+0.98182;
      else if (idx == 13  ) num = (0.00006*TMath::Erf((x-2.16945)/8.90821))+0.98502;
      else if (idx == 14  ) num = (0.01142*TMath::Erf((x-4.09115)/1.38966))+0.97578;
      else if (idx == 15  ) num = (0.00631*TMath::Erf((x-5.04864)/0.60484))+0.97723;
      else if (idx == 16  ) num = (0.03447*TMath::Erf((x-1.94682)/2.89737))+0.95615;
      else if (idx == 17  ) num = (0.00072*TMath::Erf((x-8.44164)/9.99718))+0.97435;
      else if (idx == 18  ) num = (0.00216*TMath::Erf((x-6.34180)/9.99970))+0.98002;
      else if (idx == 19  ) num = (0.01930*TMath::Erf((x-2.68888)/2.22092))+0.96763;
      else if (idx == 20  ) num = (0.07824*TMath::Erf((x-2.35046)/0.90841))+0.90876;
      else if (idx == 21  ) num = (0.07431*TMath::Erf((x-0.04659)/4.09791))+0.91602;
      else if (idx == 22  ) num = (0.00470*TMath::Erf((x-9.77349)/0.67485))+0.98877;
      else if (idx == 23  ) num = (0.01892*TMath::Erf((x-0.19310)/1.23145))+0.95943;
      else if (idx == 24  ) num = (0.04034*TMath::Erf((x-1.16846)/5.20853))+0.95131;
      else if (idx == 25  ) num = (0.00057*TMath::Erf((x-0.45482)/0.32997))+0.97534;
      else if (idx == 26  ) num = (0.00685*TMath::Erf((x-2.93533)/9.99594))+0.98459;
      else if (idx == 27  ) num = (0.00000*TMath::Erf((x-8.45186)/5.09233))+0.98098;
      else if (idx == 28  ) num = (0.01979*TMath::Erf((x-6.97256)/9.64327))+0.97954;
      else if (idx == 29  ) num = (0.03926*TMath::Erf((x-2.71520)/0.23755))+0.94710;
      else if (idx == 30  ) num = (0.02550*TMath::Erf((x-2.72328)/1.51738))+0.95471;
      else if (idx == 31  ) num = (0.01655*TMath::Erf((x-9.99304)/9.96405))+0.98043;
      else if (idx == 32  ) num = (0.00700*TMath::Erf((x-9.88581)/9.99487))+0.98603;
      else if (idx == 33  ) num = (0.00957*TMath::Erf((x-6.08627)/9.98522))+0.98657;
      else if (idx == 34  ) num = (0.00460*TMath::Erf((x-7.19233)/9.99964))+0.97524;
      else if (idx == 35  ) num = (0.00000*TMath::Erf((x-6.85833)/9.96900))+0.97882;
      else if (idx == 36  ) num = (0.01833*TMath::Erf((x-0.27358)/8.75652))+0.97590;
      else if (idx == 37  ) num = (0.01063*TMath::Erf((x-5.87262)/9.95885))+0.98109;
      else if (idx == 38  ) num = (0.92605*TMath::Erf((x-2.19442)/0.39761))+0.05928;
      else if (idx == 39  ) num = (0.01128*TMath::Erf((x-4.49926)/9.97057))+0.98323;
      else if (idx == 40  ) num = (0.01215*TMath::Erf((x-4.36385)/0.03160))+0.97481;
      else if (idx == 41  ) num = (0.00000*TMath::Erf((x-4.62980)/9.93975))+0.98127;
      else if (idx == 42  ) num = (0.01316*TMath::Erf((x-3.26365)/0.15704))+0.96935;
      else if (idx == 43  ) num = (0.00521*TMath::Erf((x-0.03623)/0.38553))+0.97682;
      else if (idx == 44  ) num = (0.02152*TMath::Erf((x-3.00242)/0.49726))+0.96400;
      else if (idx == 45  ) num = (0.03872*TMath::Erf((x-0.00691)/6.46206))+0.95523;
      else if (idx == 46  ) num = (0.00750*TMath::Erf((x-6.75129)/9.93606))+0.97827;
      else if (idx == 47  ) num = (0.00376*TMath::Erf((x-3.78416)/8.99843))+0.98098;
      else if (idx == 48  ) num = (0.04502*TMath::Erf((x-1.01609)/4.21667))+0.93773;
      else if (idx == 49  ) num = (0.02707*TMath::Erf((x-0.00118)/9.44463))+0.96760;
      else if (idx == 50  ) num = (0.00962*TMath::Erf((x-6.02643)/9.99919))+0.97619;
      else if (idx == 51  ) num = (0.42449*TMath::Erf((x-0.87898)/1.40779))+0.55945;
      else if (idx == 52  ) num = (0.01550*TMath::Erf((x-4.46179)/9.78694))+0.98374;
      else if (idx == 53  ) num = (0.00685*TMath::Erf((x-7.94336)/9.97777))+0.98141;
      else if (idx == 54  ) num = (0.00687*TMath::Erf((x-4.96863)/9.99857))+0.98158;
      else if (idx == 55  ) num = (0.02018*TMath::Erf((x-6.43505)/6.01923))+0.97942;
      else if (idx == 56  ) num = (0.00000*TMath::Erf((x-0.36676)/2.37384))+0.98214;
      else if (idx == 57  ) num = (0.00000*TMath::Erf((x-9.92242)/9.99939))+0.97309;
      else if (idx == 58  ) num = (0.00668*TMath::Erf((x-9.97428)/9.99977))+0.98347;
      else if (idx == 59  ) num = (0.00988*TMath::Erf((x-9.29244)/0.75776))+0.98906;
      else if (idx == 60  ) num = (0.01449*TMath::Erf((x-5.37556)/0.00593))+0.97489;
      else if (idx == 61  ) num = (0.01614*TMath::Erf((x-7.36244)/9.78174))+0.97844;
      else if (idx == 62  ) num = (0.01818*TMath::Erf((x-2.98224)/0.08243))+0.96564;
      else if (idx == 63  ) num = (0.00020*TMath::Erf((x-9.81342)/0.50523))+0.97746;
      else if (idx == 64  ) num = (0.00756*TMath::Erf((x-4.62848)/0.16948))+0.97370;
      else if (idx == 65  ) num = (0.00000*TMath::Erf((x-1.79164)/8.86880))+0.97914;
      else if (idx == 66  ) num = (0.00042*TMath::Erf((x-6.74663)/9.99658))+0.97908;
      else if (idx == 67  ) num = (0.00312*TMath::Erf((x-3.76840)/4.51264))+0.97982;
      else if (idx == 68  ) num = (0.01730*TMath::Erf((x-4.94032)/7.12698))+0.98331;
      else if (idx == 69  ) num = (0.02059*TMath::Erf((x-0.01048)/9.78680))+0.96953;
      else if (idx == 70  ) num = (0.10724*TMath::Erf((x-0.99565)/0.58495))+0.87941;
      else if (idx == 71  ) num = (0.00515*TMath::Erf((x-9.37961)/3.01867))+0.99175;
      else if (idx == 72  ) num = (0.06026*TMath::Erf((x-0.00048)/5.28534))+0.93200;
      else if (idx == 73  ) num = (0.00668*TMath::Erf((x-8.59713)/0.04927))+0.98436;
      else if (idx == 74  ) num = (0.00603*TMath::Erf((x-4.97847)/9.99977))+0.98153;
      else if (idx == 75  ) num = (0.00000*TMath::Erf((x-9.04356)/9.99461))+0.97762;
      else if (idx == 76  ) num = (0.00445*TMath::Erf((x-8.68461)/0.02187))+0.98634;
      else if (idx == 77  ) num = (0.03153*TMath::Erf((x-2.43133)/1.50034))+0.95343;
      else if (idx == 78  ) num = (0.01121*TMath::Erf((x-6.67375)/2.47009))+0.98573;
      else if (idx == 79  ) num = (0.80029*TMath::Erf((x-2.30555)/0.36271))+0.18062;
      else if (idx == 80  ) num = (0.17088*TMath::Erf((x-0.97699)/1.86668))+0.81245;
      else if (idx == 81  ) num = (0.00000*TMath::Erf((x-7.50633)/9.97689))+0.97833;
      else if (idx == 82  ) num = (0.00185*TMath::Erf((x-4.69943)/9.99992))+0.98482;
      else if (idx == 83  ) num = (0.00169*TMath::Erf((x-9.99764)/9.94047))+0.98101;
      else if (idx == 84  ) num = (0.00275*TMath::Erf((x-9.97517)/9.96644))+0.98804;
      else if (idx == 85  ) num = (0.04852*TMath::Erf((x-2.10701)/1.16846))+0.93910;
      else if (idx == 86  ) num = (0.00102*TMath::Erf((x-3.51616)/9.99134))+0.98391;
      else if (idx == 87  ) num = (0.00000*TMath::Erf((x-7.45945)/9.98449))+0.97997;
      else if (idx == 88  ) num = (0.00305*TMath::Erf((x-9.98948)/9.99131))+0.97964;
      else if (idx == 89  ) num = (0.00936*TMath::Erf((x-4.53171)/0.04084))+0.98181;
      else if (idx == 90  ) num = (0.05330*TMath::Erf((x-0.42369)/4.81723))+0.93541;
      else if (idx == 91  ) num = (0.00010*TMath::Erf((x-0.49921)/3.17135))+0.98043;
      else if (idx == 92  ) num = (0.00413*TMath::Erf((x-5.06056)/9.99450))+0.98216;
      else if (idx == 93  ) num = (0.10634*TMath::Erf((x-0.06331)/0.37948))+0.87904;
      else if (idx == 94  ) num = (0.21357*TMath::Erf((x-1.95245)/0.83414))+0.76931;
      else if (idx == 95  ) num = (0.00806*TMath::Erf((x-3.05679)/9.96035))+0.98511;
      else if (idx == 96  ) num = (0.00000*TMath::Erf((x-2.06480)/9.91022))+0.97691;
      else if (idx == 97  ) num = (0.00237*TMath::Erf((x-9.99984)/9.99880))+0.98051;
      else if (idx == 98  ) num = (0.00904*TMath::Erf((x-7.15537)/4.97318))+0.98257;
      else if (idx == 99  ) num = (0.08340*TMath::Erf((x-0.84331)/2.48669))+0.90425;
      else if (idx == 100 ) num = (0.03027*TMath::Erf((x-1.60165)/2.79258))+0.95561;
   }
   else if (fabs(eta)<2.1)
   {
      if (idx==0) num = (0.52738*TMath::Erf((x-0.00120)/0.58543))+0.46394;
      else if (idx == -1   ) num = (0.53055*TMath::Erf((x-0.00032)/0.57456))+0.46714;
      else if (idx == -2   ) num = (0.51981*TMath::Erf((x-1.37234)/0.48277))+0.45680;
      else if (idx == 1   ) num = (0.51877*TMath::Erf((x-0.95937)/0.46548))+0.45555;
      else if (idx == 2   ) num = (0.52019*TMath::Erf((x-0.00031)/0.57439))+0.45689;
      else if (idx == 3   ) num = (0.51956*TMath::Erf((x-0.00031)/0.57437))+0.45629;
      else if (idx == 4   ) num = (0.52039*TMath::Erf((x-0.00031)/0.57439))+0.45708;
      else if (idx == 5   ) num = (0.52473*TMath::Erf((x-0.00032)/0.57445))+0.46131;
      else if (idx == 6   ) num = (0.52185*TMath::Erf((x-0.00031)/0.57441))+0.45849;
      else if (idx == 7   ) num = (0.52206*TMath::Erf((x-0.98475)/0.48490))+0.45870;
      else if (idx == 8   ) num = (0.52635*TMath::Erf((x-1.22640)/0.57798))+0.46291;
      else if (idx == 9   ) num = (0.52265*TMath::Erf((x-0.00031)/0.57438))+0.45927;
      else if (idx == 10  ) num = (0.51934*TMath::Erf((x-1.11083)/0.42686))+0.45613;
      else if (idx == 11  ) num = (0.52094*TMath::Erf((x-0.97008)/0.49055))+0.45762;
      else if (idx == 12  ) num = (0.52065*TMath::Erf((x-0.96974)/0.46913))+0.45735;
      else if (idx == 13  ) num = (0.51928*TMath::Erf((x-0.00031)/0.57436))+0.45602;
      else if (idx == 14  ) num = (0.52297*TMath::Erf((x-0.00031)/0.57441))+0.45958;
      else if (idx == 15  ) num = (0.52560*TMath::Erf((x-0.00032)/0.57448))+0.46217;
      else if (idx == 16  ) num = (0.52544*TMath::Erf((x-0.00032)/0.57445))+0.46201;
      else if (idx == 17  ) num = (0.52444*TMath::Erf((x-0.00032)/0.57444))+0.46102;
      else if (idx == 18  ) num = (0.51991*TMath::Erf((x-1.14726)/0.32956))+0.45663;
      else if (idx == 19  ) num = (0.52441*TMath::Erf((x-0.00032)/0.57447))+0.46099;
      else if (idx == 20  ) num = (0.52119*TMath::Erf((x-0.00031)/0.57439))+0.45785;
      else if (idx == 21  ) num = (0.52641*TMath::Erf((x-0.00032)/0.57448))+0.46297;
      else if (idx == 22  ) num = (0.52124*TMath::Erf((x-0.00031)/0.57439))+0.45791;
      else if (idx == 23  ) num = (0.52331*TMath::Erf((x-0.00031)/0.57415))+0.45991;
      else if (idx == 24  ) num = (0.52498*TMath::Erf((x-0.00032)/0.57438))+0.46155;
      else if (idx == 25  ) num = (0.52146*TMath::Erf((x-0.00031)/0.57440))+0.45811;
      else if (idx == 26  ) num = (0.52360*TMath::Erf((x-0.00032)/0.57410))+0.46020;
      else if (idx == 27  ) num = (0.51932*TMath::Erf((x-0.93423)/0.45709))+0.45606;
      else if (idx == 28  ) num = (0.52175*TMath::Erf((x-0.98176)/0.47628))+0.45840;
      else if (idx == 29  ) num = (0.51952*TMath::Erf((x-0.93517)/0.46966))+0.45625;
      else if (idx == 30  ) num = (0.52309*TMath::Erf((x-0.00031)/0.57444))+0.45970;
      else if (idx == 31  ) num = (0.52467*TMath::Erf((x-0.00032)/0.57447))+0.46125;
      else if (idx == 32  ) num = (0.52538*TMath::Erf((x-0.00032)/0.57448))+0.46194;
      else if (idx == 33  ) num = (0.51991*TMath::Erf((x-0.00031)/0.57437))+0.45663;
      else if (idx == 34  ) num = (0.52042*TMath::Erf((x-1.11789)/0.43008))+0.45717;
      else if (idx == 35  ) num = (0.51948*TMath::Erf((x-0.00031)/0.57437))+0.45622;
      else if (idx == 36  ) num = (0.51865*TMath::Erf((x-0.97828)/0.46262))+0.45543;
      else if (idx == 37  ) num = (0.52495*TMath::Erf((x-0.00032)/0.57441))+0.46152;
      else if (idx == 38  ) num = (0.51404*TMath::Erf((x-1.06130)/0.37719))+0.45115;
      else if (idx == 39  ) num = (0.52158*TMath::Erf((x-0.00031)/0.57438))+0.45824;
      else if (idx == 40  ) num = (0.52467*TMath::Erf((x-0.00032)/0.57447))+0.46124;
      else if (idx == 41  ) num = (0.52213*TMath::Erf((x-0.00031)/0.57423))+0.45876;
      else if (idx == 42  ) num = (0.52410*TMath::Erf((x-0.00032)/0.57425))+0.46069;
      else if (idx == 43  ) num = (0.52116*TMath::Erf((x-0.00031)/0.57441))+0.45783;
      else if (idx == 44  ) num = (0.52132*TMath::Erf((x-0.00031)/0.57437))+0.45798;
      else if (idx == 45  ) num = (0.52111*TMath::Erf((x-0.00031)/0.57440))+0.45777;
      else if (idx == 46  ) num = (0.52325*TMath::Erf((x-0.53684)/0.33949))+0.45985;
      else if (idx == 47  ) num = (0.51999*TMath::Erf((x-0.00031)/0.57436))+0.45670;
      else if (idx == 48  ) num = (0.52562*TMath::Erf((x-0.85114)/0.50692))+0.46218;
      else if (idx == 49  ) num = (0.52296*TMath::Erf((x-0.00031)/0.57443))+0.45957;
      else if (idx == 50  ) num = (0.52566*TMath::Erf((x-0.00032)/0.57448))+0.46222;
      else if (idx == 51  ) num = (0.52431*TMath::Erf((x-1.02324)/0.50634))+0.46090;
      else if (idx == 52  ) num = (0.52118*TMath::Erf((x-0.00031)/0.57426))+0.45785;
      else if (idx == 53  ) num = (0.52279*TMath::Erf((x-0.73273)/0.45814))+0.45941;
      else if (idx == 54  ) num = (0.52295*TMath::Erf((x-0.79158)/0.04821))+0.45956;
      else if (idx == 55  ) num = (0.51912*TMath::Erf((x-0.00031)/0.57428))+0.45587;
      else if (idx == 56  ) num = (0.51974*TMath::Erf((x-1.10957)/0.40618))+0.45653;
      else if (idx == 57  ) num = (0.52663*TMath::Erf((x-1.13158)/0.57474))+0.46319;
      else if (idx == 58  ) num = (0.51990*TMath::Erf((x-0.00031)/0.57433))+0.45661;
      else if (idx == 59  ) num = (0.52183*TMath::Erf((x-0.73312)/0.38747))+0.45847;
      else if (idx == 60  ) num = (0.52221*TMath::Erf((x-0.00031)/0.57442))+0.45885;
      else if (idx == 61  ) num = (0.52339*TMath::Erf((x-1.00870)/0.49868))+0.46000;
      else if (idx == 62  ) num = (0.52165*TMath::Erf((x-0.00031)/0.57441))+0.45830;
      else if (idx == 63  ) num = (0.52299*TMath::Erf((x-0.00031)/0.57439))+0.45960;
      else if (idx == 64  ) num = (0.52159*TMath::Erf((x-0.00031)/0.57440))+0.45824;
      else if (idx == 65  ) num = (0.52271*TMath::Erf((x-0.00031)/0.57441))+0.45933;
      else if (idx == 66  ) num = (0.52019*TMath::Erf((x-0.35377)/0.30739))+0.45689;
      else if (idx == 67  ) num = (0.52043*TMath::Erf((x-1.36689)/0.47622))+0.45740;
      else if (idx == 68  ) num = (0.52432*TMath::Erf((x-0.00032)/0.57443))+0.46091;
      else if (idx == 69  ) num = (0.52160*TMath::Erf((x-0.00031)/0.57406))+0.45825;
      else if (idx == 70  ) num = (0.52214*TMath::Erf((x-0.73918)/0.43745))+0.45877;
      else if (idx == 71  ) num = (0.52642*TMath::Erf((x-0.00032)/0.57450))+0.46297;
      else if (idx == 72  ) num = (0.52588*TMath::Erf((x-0.00032)/0.57448))+0.46244;
      else if (idx == 73  ) num = (0.52047*TMath::Erf((x-0.00031)/0.57437))+0.45716;
      else if (idx == 74  ) num = (0.52033*TMath::Erf((x-0.00031)/0.57454))+0.45703;
      else if (idx == 75  ) num = (0.52265*TMath::Erf((x-0.99006)/0.48302))+0.45928;
      else if (idx == 76  ) num = (0.52443*TMath::Erf((x-1.06422)/0.54060))+0.46101;
      else if (idx == 77  ) num = (0.51846*TMath::Erf((x-0.00031)/0.57425))+0.45525;
      else if (idx == 78  ) num = (0.52100*TMath::Erf((x-0.00031)/0.57435))+0.45768;
      else if (idx == 79  ) num = (0.52339*TMath::Erf((x-1.03258)/0.52512))+0.46000;
      else if (idx == 80  ) num = (0.52042*TMath::Erf((x-0.00031)/0.57437))+0.45711;
      else if (idx == 81  ) num = (0.52567*TMath::Erf((x-0.00032)/0.57447))+0.46224;
      else if (idx == 82  ) num = (0.52411*TMath::Erf((x-0.81900)/0.49001))+0.46069;
      else if (idx == 83  ) num = (0.52404*TMath::Erf((x-0.99263)/0.48609))+0.46063;
      else if (idx == 84  ) num = (0.52064*TMath::Erf((x-0.96857)/0.47125))+0.45734;
      else if (idx == 85  ) num = (0.52259*TMath::Erf((x-0.00031)/0.57443))+0.45921;
      else if (idx == 86  ) num = (0.52390*TMath::Erf((x-1.00840)/0.49325))+0.46050;
      else if (idx == 87  ) num = (0.52390*TMath::Erf((x-0.00032)/0.57440))+0.46049;
      else if (idx == 88  ) num = (0.52006*TMath::Erf((x-0.80364)/0.49253))+0.45677;
      else if (idx == 89  ) num = (0.52737*TMath::Erf((x-1.12955)/0.57368))+0.46392;
      else if (idx == 90  ) num = (0.52483*TMath::Erf((x-0.00032)/0.57447))+0.46140;
      else if (idx == 91  ) num = (0.52471*TMath::Erf((x-0.60374)/0.45598))+0.46129;
      else if (idx == 92  ) num = (0.52402*TMath::Erf((x-0.00032)/0.57443))+0.46061;
      else if (idx == 93  ) num = (0.00003*TMath::Erf((x-9.82161)/3.05417))+0.99437;
      else if (idx == 94  ) num = (0.52142*TMath::Erf((x-0.00031)/0.57439))+0.45807;
      else if (idx == 95  ) num = (0.52203*TMath::Erf((x-0.87043)/0.49791))+0.45867;
      else if (idx == 96  ) num = (0.52302*TMath::Erf((x-0.66262)/0.45686))+0.45963;
      else if (idx == 97  ) num = (0.51874*TMath::Erf((x-0.98373)/0.46248))+0.45552;
      else if (idx == 98  ) num = (0.52210*TMath::Erf((x-0.00031)/0.57442))+0.45873;
      else if (idx == 99  ) num = (0.52014*TMath::Erf((x-0.00031)/0.57432))+0.45685;
      else if (idx == 100 ) num = (0.52173*TMath::Erf((x-0.00031)/0.57442))+0.45837;
   }
   else
   {
      if (idx==0) num = (0.52196*TMath::Erf((x-0.00031)/1.71500))+0.45823;
      else if (idx == -1   ) num = (0.52518*TMath::Erf((x-0.00001)/0.94216))+0.46239;
      else if (idx == -2   ) num = (0.51944*TMath::Erf((x-0.97798)/1.06998))+0.44553;
      else if (idx == 1   ) num = (0.65158*TMath::Erf((x-1.11230)/0.73330))+0.30682;
      else if (idx == 2   ) num = (0.13140*TMath::Erf((x-0.01972)/4.79355))+0.86149;
      else if (idx == 3   ) num = (0.51388*TMath::Erf((x-0.00011)/1.23801))+0.45091;
      else if (idx == 4   ) num = (0.41467*TMath::Erf((x-0.06535)/1.73932))+0.55160;
      else if (idx == 5   ) num = (0.51476*TMath::Erf((x-0.00009)/1.29729))+0.45177;
      else if (idx == 6   ) num = (0.02811*TMath::Erf((x-4.40424)/0.46762))+0.94925;
      else if (idx == 7   ) num = (0.51314*TMath::Erf((x-0.00269)/1.56981))+0.45013;
      else if (idx == 8   ) num = (0.51326*TMath::Erf((x-1.54979)/0.41108))+0.44631;
      else if (idx == 9   ) num = (0.51787*TMath::Erf((x-0.04374)/1.64907))+0.45438;
      else if (idx == 10  ) num = (0.51226*TMath::Erf((x-0.00015)/1.17491))+0.44942;
      else if (idx == 11  ) num = (0.93320*TMath::Erf((x-1.40057)/0.49704))+0.04443;
      else if (idx == 12  ) num = (0.52308*TMath::Erf((x-1.60571)/0.41712))+0.45428;
      else if (idx == 13  ) num = (0.51946*TMath::Erf((x-0.00009)/1.49651))+0.45606;
      else if (idx == 14  ) num = (0.52254*TMath::Erf((x-1.60456)/0.39333))+0.44965;
      else if (idx == 15  ) num = (0.51573*TMath::Erf((x-0.00113)/1.71759))+0.45398;
      else if (idx == 16  ) num = (0.51085*TMath::Erf((x-0.00057)/1.38865))+0.44795;
      else if (idx == 17  ) num = (0.51781*TMath::Erf((x-0.00010)/1.51935))+0.45439;
      else if (idx == 18  ) num = (0.51316*TMath::Erf((x-0.00020)/1.31865))+0.45014;
      else if (idx == 19  ) num = (0.51294*TMath::Erf((x-0.00348)/1.44121))+0.44979;
      else if (idx == 20  ) num = (0.51286*TMath::Erf((x-0.00071)/1.47696))+0.44976;
      else if (idx == 21  ) num = (0.51637*TMath::Erf((x-1.66219)/0.36424))+0.44717;
      else if (idx == 22  ) num = (0.51243*TMath::Erf((x-0.00016)/0.77164))+0.45004;
      else if (idx == 23  ) num = (0.52195*TMath::Erf((x-0.00000)/1.36475))+0.45862;
      else if (idx == 24  ) num = (0.04780*TMath::Erf((x-9.92774)/8.47034))+0.98426;
      else if (idx == 25  ) num = (0.51829*TMath::Erf((x-0.00006)/1.43923))+0.45493;
      else if (idx == 26  ) num = (0.51769*TMath::Erf((x-0.00113)/1.67750))+0.45426;
      else if (idx == 27  ) num = (0.51315*TMath::Erf((x-0.45679)/1.51073))+0.44848;
      else if (idx == 28  ) num = (0.51210*TMath::Erf((x-0.00060)/1.46649))+0.44912;
      else if (idx == 29  ) num = (0.51580*TMath::Erf((x-0.00000)/1.51162))+0.45254;
      else if (idx == 30  ) num = (0.51478*TMath::Erf((x-0.00088)/1.47608))+0.45150;
      else if (idx == 31  ) num = (0.02112*TMath::Erf((x-6.47299)/2.27533))+0.98159;
      else if (idx == 32  ) num = (0.51785*TMath::Erf((x-0.00152)/1.65385))+0.45434;
      else if (idx == 33  ) num = (0.51807*TMath::Erf((x-0.00011)/1.50878))+0.45474;
      else if (idx == 34  ) num = (0.03416*TMath::Erf((x-9.62949)/9.99901))+0.97408;
      else if (idx == 35  ) num = (0.03485*TMath::Erf((x-9.90403)/9.51530))+0.98199;
      else if (idx == 36  ) num = (0.58230*TMath::Erf((x-1.56927)/0.41627))+0.39202;
      else if (idx == 37  ) num = (0.51206*TMath::Erf((x-0.49001)/1.27927))+0.44740;
      else if (idx == 38  ) num = (0.03530*TMath::Erf((x-4.95109)/0.75042))+0.95920;
      else if (idx == 39  ) num = (0.51949*TMath::Erf((x-0.00006)/1.52838))+0.45606;
      else if (idx == 40  ) num = (0.51755*TMath::Erf((x-0.00018)/1.58100))+0.45412;
      else if (idx == 41  ) num = (0.51759*TMath::Erf((x-0.00000)/1.85016))+0.45602;
      else if (idx == 42  ) num = (0.51894*TMath::Erf((x-0.00024)/1.59899))+0.45545;
      else if (idx == 43  ) num = (0.51885*TMath::Erf((x-0.00039)/1.26987))+0.45576;
      else if (idx == 44  ) num = (0.07124*TMath::Erf((x-1.87602)/9.01167))+0.92698;
      else if (idx == 45  ) num = (0.51681*TMath::Erf((x-0.00007)/1.34320))+0.45362;
      else if (idx == 46  ) num = (0.51484*TMath::Erf((x-0.00069)/1.47100))+0.45163;
      else if (idx == 47  ) num = (0.51389*TMath::Erf((x-0.00046)/0.83783))+0.45132;
      else if (idx == 48  ) num = (0.52610*TMath::Erf((x-1.66186)/0.39669))+0.45612;
      else if (idx == 49  ) num = (0.51383*TMath::Erf((x-0.00011)/0.75089))+0.45133;
      else if (idx == 50  ) num = (0.52412*TMath::Erf((x-0.00002)/1.59718))+0.46056;
      else if (idx == 51  ) num = (0.51872*TMath::Erf((x-0.00006)/1.52323))+0.45530;
      else if (idx == 52  ) num = (0.01853*TMath::Erf((x-5.48158)/0.34381))+0.97339;
      else if (idx == 53  ) num = (0.51475*TMath::Erf((x-0.00026)/1.40703))+0.45158;
      else if (idx == 54  ) num = (0.13880*TMath::Erf((x-0.55029)/4.03962))+0.84579;
      else if (idx == 55  ) num = (0.51762*TMath::Erf((x-0.54838)/1.38486))+0.45186;
      else if (idx == 56  ) num = (0.51130*TMath::Erf((x-0.00014)/0.70692))+0.44876;
      else if (idx == 57  ) num = (0.51474*TMath::Erf((x-0.06578)/1.69583))+0.45173;
      else if (idx == 58  ) num = (0.51878*TMath::Erf((x-0.00018)/1.39072))+0.45549;
      else if (idx == 59  ) num = (0.54114*TMath::Erf((x-1.53529)/0.45255))+0.43299;
      else if (idx == 60  ) num = (0.52454*TMath::Erf((x-1.63488)/0.41427))+0.45343;
      else if (idx == 61  ) num = (0.08065*TMath::Erf((x-1.81474)/4.52511))+0.91779;
      else if (idx == 62  ) num = (0.51655*TMath::Erf((x-0.00072)/1.56834))+0.45312;
      else if (idx == 63  ) num = (0.51719*TMath::Erf((x-0.00010)/1.46958))+0.45385;
      else if (idx == 64  ) num = (0.51246*TMath::Erf((x-0.05341)/0.57703))+0.45008;
      else if (idx == 65  ) num = (0.51646*TMath::Erf((x-0.00015)/1.47931))+0.45308;
      else if (idx == 66  ) num = (0.51812*TMath::Erf((x-0.00010)/1.36804))+0.45491;
      else if (idx == 67  ) num = (0.52001*TMath::Erf((x-0.92896)/1.00961))+0.45417;
      else if (idx == 68  ) num = (0.51292*TMath::Erf((x-0.00019)/0.85289))+0.45023;
      else if (idx == 69  ) num = (0.50982*TMath::Erf((x-0.00053)/1.18656))+0.44705;
      else if (idx == 70  ) num = (0.51808*TMath::Erf((x-0.00014)/1.57221))+0.45467;
      else if (idx == 71  ) num = (0.51328*TMath::Erf((x-0.00013)/1.28801))+0.45029;
      else if (idx == 72  ) num = (0.51483*TMath::Erf((x-0.00015)/1.27967))+0.45178;
      else if (idx == 73  ) num = (0.51681*TMath::Erf((x-1.64161)/0.43335))+0.44791;
      else if (idx == 74  ) num = (0.51502*TMath::Erf((x-0.00010)/1.34015))+0.45187;
      else if (idx == 75  ) num = (0.52054*TMath::Erf((x-0.00004)/1.51463))+0.45706;
      else if (idx == 76  ) num = (0.51746*TMath::Erf((x-1.44169)/0.61086))+0.44972;
      else if (idx == 77  ) num = (0.51008*TMath::Erf((x-0.04970)/0.54049))+0.44757;
      else if (idx == 78  ) num = (0.51388*TMath::Erf((x-0.00017)/1.01973))+0.45104;
      else if (idx == 79  ) num = (0.51576*TMath::Erf((x-0.00023)/1.47230))+0.45251;
      else if (idx == 80  ) num = (0.51453*TMath::Erf((x-0.00003)/1.61643))+0.45187;
      else if (idx == 81  ) num = (0.89680*TMath::Erf((x-0.21475)/1.31634))+0.06023;
      else if (idx == 82  ) num = (0.51753*TMath::Erf((x-0.00010)/1.51397))+0.45416;
      else if (idx == 83  ) num = (0.51639*TMath::Erf((x-0.01292)/1.54253))+0.45304;
      else if (idx == 84  ) num = (0.52343*TMath::Erf((x-0.42147)/1.44618))+0.45521;
      else if (idx == 85  ) num = (0.51805*TMath::Erf((x-0.00009)/1.57594))+0.45466;
      else if (idx == 86  ) num = (0.20201*TMath::Erf((x-0.01147)/2.93439))+0.78637;
      else if (idx == 87  ) num = (0.50736*TMath::Erf((x-0.00005)/0.75234))+0.44502;
      else if (idx == 88  ) num = (0.52209*TMath::Erf((x-0.00000)/1.68505))+0.45842;
      else if (idx == 89  ) num = (0.51186*TMath::Erf((x-0.02469)/1.73065))+0.45003;
      else if (idx == 90  ) num = (0.51634*TMath::Erf((x-0.00022)/1.72547))+0.45366;
      else if (idx == 91  ) num = (0.04311*TMath::Erf((x-9.90480)/9.88915))+0.99340;
      else if (idx == 92  ) num = (0.51561*TMath::Erf((x-0.00015)/0.89445))+0.45294;
      else if (idx == 93  ) num = (0.51986*TMath::Erf((x-0.00000)/0.79247))+0.45734;
      else if (idx == 94  ) num = (0.52155*TMath::Erf((x-0.00000)/1.37730))+0.45821;
      else if (idx == 95  ) num = (0.52384*TMath::Erf((x-0.10106)/1.84166))+0.46014;
      else if (idx == 96  ) num = (0.50630*TMath::Erf((x-0.00547)/1.27866))+0.44390;
      else if (idx == 97  ) num = (0.50809*TMath::Erf((x-0.00005)/0.98670))+0.44559;
      else if (idx == 98  ) num = (0.51113*TMath::Erf((x-0.01912)/0.54316))+0.44877;
      else if (idx == 99  ) num = (0.51183*TMath::Erf((x-0.03253)/0.53965))+0.44923;
      else if (idx == 100 ) num = (0.52161*TMath::Erf((x-0.00217)/1.70550))+0.45789;
   }

   // return
   return num/den;
}

#endif //#ifndef tnp_weight_h
