#ifndef tnp_weight_h
#define tnp_weight_h

#include "TMath.h"

// IN THIS FILE YOU WILL FIND:
// ++++++++++++++
//
// - Iso, MuID: (tnp_weight_(iso|muid)_ppb)
//   * idx = 0:  nominal
//   * idx = 1..100: toy variations, stat. only
//   * idx = -1: syst variation, "new_MAX", +1 sigma NOT YET IMPLEMENTED
//   * idx = -2: syst variation, "new_MAX", -1 sigma NOT YET IMPLEMENTED
//   * idx = -10: binned
// - Trigger: (tnp_weight_trg_ppb)
//   * idx = 0: nominal
//   * idx = 1: +1 sigma stat
//   * idx = 2: -1 sigma stat

// THE INDIVIDUAL SFs
// ++++++++++++++++++
double tnp_weight_trg_ppb(double eta, int idx=0);
double tnp_weight_muid_ppb(double pt, double eta, int idx=0);
double tnp_weight_iso_ppb(double pt, double eta, int idx=0);


///////////////////////////////////////////////////
//                 T R G    P P b                //
///////////////////////////////////////////////////
double tnp_weight_trg_ppb(double eta, int idx)
{
   double num=1,den=1;
   
   // MC
   if (eta>-2.4&&eta<=-2.1) den = 0.90958;
   if (eta>-2.1&&eta<=-1.6) den = 0.914958;
   if (eta>-1.6&&eta<=-1.2) den = 0.925803;
   if (eta>-1.2&&eta<=-0.9) den = 0.982331;
   if (eta>-0.9&&eta<=-0.6) den = 0.959744;
   if (eta>-0.6&&eta<=-0.3) den = 0.979351;
   if (eta>-0.3&&eta<=0) den = 0.962077;
   if (eta>0&&eta<=0.3) den = 0.961293;
   if (eta>0.3&&eta<=0.6) den = 0.979905;
   if (eta>0.6&&eta<=0.9) den = 0.961278;
   if (eta>0.9&&eta<=1.2) den = 0.983568;
   if (eta>1.2&&eta<=1.6) den = 0.928204;
   if (eta>1.6&&eta<=2.1) den = 0.937549;
   if (eta>2.1&&eta<=2.4) den = 0.913236;

   // data
   if (idx==0) {
      if (eta>-2.4&&eta<=-2.1) num = 0.914757;
      if (eta>-2.1&&eta<=-1.6) num = 0.915707;
      if (eta>-1.6&&eta<=-1.2) num = 0.980875;
      if (eta>-1.2&&eta<=-0.9) num = 0.965562;
      if (eta>-0.9&&eta<=-0.6) num = 0.946875;
      if (eta>-0.6&&eta<=-0.3) num = 0.973219;
      if (eta>-0.3&&eta<=0) num = 0.946914;
      if (eta>0&&eta<=0.3) num = 0.944109;
      if (eta>0.3&&eta<=0.6) num = 0.970999;
      if (eta>0.6&&eta<=0.9) num = 0.949765;
      if (eta>0.9&&eta<=1.2) num = 0.964778;
      if (eta>1.2&&eta<=1.6) num = 0.963716;
      if (eta>1.6&&eta<=2.1) num = 0.937614;
      if (eta>2.1&&eta<=2.4) num = 0.903346;
   } else if (idx==1) {
      if (eta>-2.4&&eta<=-2.1) num = 0.923176;
      if (eta>-2.1&&eta<=-1.6) num = 0.921974;
      if (eta>-1.6&&eta<=-1.2) num = 0.983923;
      if (eta>-1.2&&eta<=-0.9) num = 0.969641;
      if (eta>-0.9&&eta<=-0.6) num = 0.951873;
      if (eta>-0.6&&eta<=-0.3) num = 0.976934;
      if (eta>-0.3&&eta<=0) num = 0.951967;
      if (eta>0&&eta<=0.3) num = 0.949635;
      if (eta>0.3&&eta<=0.6) num = 0.974764;
      if (eta>0.6&&eta<=0.9) num = 0.955019;
      if (eta>0.9&&eta<=1.2) num = 0.969394;
      if (eta>1.2&&eta<=1.6) num = 0.967597;
      if (eta>1.6&&eta<=2.1) num = 0.942947;
      if (eta>2.1&&eta<=2.4) num = 0.91254;
   } else if (idx==2) {
      if (eta>-2.4&&eta<=-2.1) num = 0.905883;
      if (eta>-2.1&&eta<=-1.6) num = 0.909178;
      if (eta>-1.6&&eta<=-1.2) num = 0.977542;
      if (eta>-1.2&&eta<=-0.9) num = 0.961157;
      if (eta>-0.9&&eta<=-0.6) num = 0.941572;
      if (eta>-0.6&&eta<=-0.3) num = 0.96919;
      if (eta>-0.3&&eta<=0) num = 0.941579;
      if (eta>0&&eta<=0.3) num = 0.938245;
      if (eta>0.3&&eta<=0.6) num = 0.966952;
      if (eta>0.6&&eta<=0.9) num = 0.944165;
      if (eta>0.9&&eta<=1.2) num = 0.959776;
      if (eta>1.2&&eta<=1.6) num = 0.959548;
      if (eta>1.6&&eta<=2.1) num = 0.932013;
      if (eta>2.1&&eta<=2.4) num = 0.893693;
   }

   return num / den;
}

double tnp_weight_muid_ppb(double pt, double eta, int idx=0) {
   if (idx == -10) {
      if (fabs(eta)<0.9) {
         // 0 < |eta| < 1.2
         if (pt<15) return 0.981368;
         else if (pt<25) return 1.00046;
         else if (pt<30) return 0.994334;
         else if (pt<35) return 0.993332;
         else if (pt<40) return 0.989234;
         else if (pt<45) return 0.993883;
         else if (pt<50) return 0.987967;
         else if (pt<80) return 0.992879;
         else if (pt<200) return 0.981644;
      } else if (fabs(eta)<2.1) {
         // 1.2 < |eta| < 2.1
         if (pt<15) return 1.00312;
         else if (pt<25) return 1.00038;
         else if (pt<30) return 0.999194;
         else if (pt<35) return 0.993943;
         else if (pt<40) return 0.997737;
         else if (pt<45) return 1.00063;
         else if (pt<50) return 0.993474;
         else if (pt<80) return 0.999515;
         else if (pt<200) return 0.999484;
      } else {
         // 2.1 < |eta| < 2.4
         if (pt<15) return 1.00685;
         else if (pt<25) return 0.998931;
         else if (pt<40) return 0.994741;
         else if (pt<80) return 0.984098;
         else if (pt<200) return 0.954343;
      }
   }

   double num = 1, den = 1;

   // nominal
   if (fabs(eta)<1.2) {
      num = 0.98425-0.00014*pt;
      den = 0.98956-0.00005*pt;
   } else if (fabs(eta)<2.1) {
      num = 0.99477-0.00003*pt;
      den = 0.99546-0.00001*pt;
   } else {
      num = 1.00640-0.00076*pt;
      den = 0.99384-0.00019*pt;
   }

   // 100 variations
   if (fabs(eta)<1.2) {
      if (idx == 1   ) num = 0.97917-0.00003*pt;
      else if (idx == 2   ) num = 0.98160-0.00007*pt;
      else if (idx == 3   ) num = 0.98802-0.00026*pt;
      else if (idx == 4   ) num = 0.96812+0.00021*pt;
      else if (idx == 5   ) num = 0.98832-0.00021*pt;
      else if (idx == 6   ) num = 0.98949-0.00021*pt;
      else if (idx == 7   ) num = 0.98044-0.00008*pt;
      else if (idx == 8   ) num = 0.98273-0.00018*pt;
      else if (idx == 9   ) num = 0.97299+0.00015*pt;
      else if (idx == 10  ) num = 0.98792-0.00017*pt;
      else if (idx == 11  ) num = 0.97394+0.00006*pt;
      else if (idx == 12  ) num = 0.98540-0.00023*pt;
      else if (idx == 13  ) num = 0.98747-0.00023*pt;
      else if (idx == 14  ) num = 0.99123-0.00033*pt;
      else if (idx == 15  ) num = 0.97693-0.00008*pt;
      else if (idx == 16  ) num = 0.99411-0.00039*pt;
      else if (idx == 17  ) num = 0.97220+0.00008*pt;
      else if (idx == 18  ) num = 0.99688-0.00042*pt;
      else if (idx == 19  ) num = 0.98346-0.00010*pt;
      else if (idx == 20  ) num = 0.98773-0.00016*pt;
      else if (idx == 21  ) num = 0.98438-0.00014*pt;
      else if (idx == 22  ) num = 0.98327-0.00013*pt;
      else if (idx == 23  ) num = 0.98257-0.00006*pt;
      else if (idx == 24  ) num = 0.98171-0.00007*pt;
      else if (idx == 25  ) num = 0.97669-0.00000*pt;
      else if (idx == 26  ) num = 0.97609+0.00003*pt;
      else if (idx == 27  ) num = 0.99263-0.00030*pt;
      else if (idx == 28  ) num = 0.99722-0.00043*pt;
      else if (idx == 29  ) num = 0.97681+0.00009*pt;
      else if (idx == 30  ) num = 0.96844+0.00019*pt;
      else if (idx == 31  ) num = 0.97892-0.00001*pt;
      else if (idx == 32  ) num = 0.98234-0.00007*pt;
      else if (idx == 33  ) num = 0.97859+0.00001*pt;
      else if (idx == 34  ) num = 0.99296-0.00031*pt;
      else if (idx == 35  ) num = 0.98621-0.00024*pt;
      else if (idx == 36  ) num = 0.99154-0.00027*pt;
      else if (idx == 37  ) num = 0.98915-0.00026*pt;
      else if (idx == 38  ) num = 0.97162+0.00013*pt;
      else if (idx == 39  ) num = 0.97692-0.00002*pt;
      else if (idx == 40  ) num = 0.98736-0.00014*pt;
      else if (idx == 41  ) num = 0.98659-0.00018*pt;
      else if (idx == 42  ) num = 0.97975-0.00007*pt;
      else if (idx == 43  ) num = 0.97948-0.00002*pt;
      else if (idx == 44  ) num = 0.97712+0.00007*pt;
      else if (idx == 45  ) num = 0.98420-0.00018*pt;
      else if (idx == 46  ) num = 0.97708+0.00013*pt;
      else if (idx == 47  ) num = 0.98607-0.00019*pt;
      else if (idx == 48  ) num = 0.98422-0.00021*pt;
      else if (idx == 49  ) num = 0.98681-0.00018*pt;
      else if (idx == 50  ) num = 0.97452+0.00002*pt;
      else if (idx == 51  ) num = 0.97260+0.00012*pt;
      else if (idx == 52  ) num = 0.99448-0.00045*pt;
      else if (idx == 53  ) num = 0.97780-0.00002*pt;
      else if (idx == 54  ) num = 0.98582-0.00024*pt;
      else if (idx == 55  ) num = 0.98696-0.00014*pt;
      else if (idx == 56  ) num = 0.98806-0.00014*pt;
      else if (idx == 57  ) num = 0.98820-0.00027*pt;
      else if (idx == 58  ) num = 0.99277-0.00027*pt;
      else if (idx == 59  ) num = 0.99119-0.00028*pt;
      else if (idx == 60  ) num = 0.98337-0.00011*pt;
      else if (idx == 61  ) num = 0.97668+0.00003*pt;
      else if (idx == 62  ) num = 0.99047-0.00029*pt;
      else if (idx == 63  ) num = 0.98961-0.00026*pt;
      else if (idx == 64  ) num = 0.99126-0.00031*pt;
      else if (idx == 65  ) num = 0.98007+0.00005*pt;
      else if (idx == 66  ) num = 0.97688-0.00011*pt;
      else if (idx == 67  ) num = 0.99367-0.00029*pt;
      else if (idx == 68  ) num = 0.98905-0.00021*pt;
      else if (idx == 69  ) num = 0.99844-0.00050*pt;
      else if (idx == 70  ) num = 0.97928-0.00010*pt;
      else if (idx == 71  ) num = 0.99133-0.00032*pt;
      else if (idx == 72  ) num = 0.98551-0.00009*pt;
      else if (idx == 73  ) num = 0.99108-0.00042*pt;
      else if (idx == 74  ) num = 0.98401-0.00020*pt;
      else if (idx == 75  ) num = 0.99436-0.00033*pt;
      else if (idx == 76  ) num = 0.99136-0.00029*pt;
      else if (idx == 77  ) num = 0.97864-0.00003*pt;
      else if (idx == 78  ) num = 0.97941+0.00003*pt;
      else if (idx == 79  ) num = 0.97822-0.00004*pt;
      else if (idx == 80  ) num = 0.98945-0.00024*pt;
      else if (idx == 81  ) num = 0.98402-0.00010*pt;
      else if (idx == 82  ) num = 0.98973-0.00042*pt;
      else if (idx == 83  ) num = 0.97983-0.00010*pt;
      else if (idx == 84  ) num = 0.98317-0.00010*pt;
      else if (idx == 85  ) num = 0.99878-0.00051*pt;
      else if (idx == 86  ) num = 0.99946-0.00050*pt;
      else if (idx == 87  ) num = 0.97653-0.00003*pt;
      else if (idx == 88  ) num = 0.98135-0.00005*pt;
      else if (idx == 89  ) num = 0.97950-0.00001*pt;
      else if (idx == 90  ) num = 0.97883-0.00006*pt;
      else if (idx == 91  ) num = 0.98543-0.00013*pt;
      else if (idx == 92  ) num = 0.97847-0.00003*pt;
      else if (idx == 93  ) num = 0.97835+0.00004*pt;
      else if (idx == 94  ) num = 0.97263+0.00003*pt;
      else if (idx == 95  ) num = 0.98420-0.00017*pt;
      else if (idx == 96  ) num = 0.97888-0.00003*pt;
      else if (idx == 97  ) num = 0.97829-0.00001*pt;
      else if (idx == 98  ) num = 0.97313+0.00012*pt;
      else if (idx == 99  ) num = 0.99337-0.00039*pt;
      else if (idx == 100 ) num = 0.97600-0.00001*pt;
   } else if (fabs(eta)<2.1) {
      if (idx == 1   ) num = 0.99097+0.00001*pt;
      else if (idx == 2   ) num = 0.99405+0.00001*pt;
      else if (idx == 3   ) num = 0.99829-0.00015*pt;
      else if (idx == 4   ) num = 0.99482-0.00008*pt;
      else if (idx == 5   ) num = 0.98910+0.00004*pt;
      else if (idx == 6   ) num = 0.99736-0.00016*pt;
      else if (idx == 7   ) num = 0.99749-0.00009*pt;
      else if (idx == 8   ) num = 0.99424-0.00003*pt;
      else if (idx == 9   ) num = 0.99440-0.00005*pt;
      else if (idx == 10  ) num = 0.99433+0.00001*pt;
      else if (idx == 11  ) num = 0.99866-0.00019*pt;
      else if (idx == 12  ) num = 1.00191-0.00028*pt;
      else if (idx == 13  ) num = 0.99386-0.00002*pt;
      else if (idx == 14  ) num = 0.99212+0.00003*pt;
      else if (idx == 15  ) num = 0.99204+0.00001*pt;
      else if (idx == 16  ) num = 0.99487-0.00003*pt;
      else if (idx == 17  ) num = 0.99707-0.00018*pt;
      else if (idx == 18  ) num = 1.00069-0.00020*pt;
      else if (idx == 19  ) num = 0.99176+0.00002*pt;
      else if (idx == 20  ) num = 0.99061+0.00007*pt;
      else if (idx == 21  ) num = 1.00027-0.00019*pt;
      else if (idx == 22  ) num = 0.99103+0.00004*pt;
      else if (idx == 23  ) num = 0.99586-0.00006*pt;
      else if (idx == 24  ) num = 0.99249+0.00003*pt;
      else if (idx == 25  ) num = 0.99657-0.00012*pt;
      else if (idx == 26  ) num = 0.99365+0.00001*pt;
      else if (idx == 27  ) num = 0.99492-0.00003*pt;
      else if (idx == 28  ) num = 0.99491+0.00001*pt;
      else if (idx == 29  ) num = 1.00138-0.00020*pt;
      else if (idx == 30  ) num = 0.99799-0.00009*pt;
      else if (idx == 31  ) num = 1.00168-0.00026*pt;
      else if (idx == 32  ) num = 1.00441-0.00031*pt;
      else if (idx == 33  ) num = 0.99273+0.00002*pt;
      else if (idx == 34  ) num = 0.99885-0.00019*pt;
      else if (idx == 35  ) num = 0.99575-0.00007*pt;
      else if (idx == 36  ) num = 0.99978-0.00022*pt;
      else if (idx == 37  ) num = 0.99210+0.00002*pt;
      else if (idx == 38  ) num = 0.99100+0.00007*pt;
      else if (idx == 39  ) num = 0.99192+0.00002*pt;
      else if (idx == 40  ) num = 0.99199+0.00004*pt;
      else if (idx == 41  ) num = 0.99196+0.00002*pt;
      else if (idx == 42  ) num = 0.99575-0.00012*pt;
      else if (idx == 43  ) num = 0.99437-0.00005*pt;
      else if (idx == 44  ) num = 0.99578-0.00008*pt;
      else if (idx == 45  ) num = 0.99518-0.00001*pt;
      else if (idx == 46  ) num = 1.00643-0.00045*pt;
      else if (idx == 47  ) num = 1.00335-0.00030*pt;
      else if (idx == 48  ) num = 0.99815-0.00017*pt;
      else if (idx == 49  ) num = 0.99572-0.00006*pt;
      else if (idx == 50  ) num = 0.99216+0.00001*pt;
      else if (idx == 51  ) num = 0.99248+0.00002*pt;
      else if (idx == 52  ) num = 0.99734-0.00006*pt;
      else if (idx == 53  ) num = 0.99152+0.00004*pt;
      else if (idx == 54  ) num = 0.99626-0.00017*pt;
      else if (idx == 55  ) num = 0.99257+0.00003*pt;
      else if (idx == 56  ) num = 0.99561-0.00010*pt;
      else if (idx == 57  ) num = 0.99700-0.00011*pt;
      else if (idx == 58  ) num = 0.99572-0.00004*pt;
      else if (idx == 59  ) num = 0.99671-0.00014*pt;
      else if (idx == 60  ) num = 0.99668-0.00007*pt;
      else if (idx == 61  ) num = 0.99323+0.00001*pt;
      else if (idx == 62  ) num = 0.99543-0.00012*pt;
      else if (idx == 63  ) num = 1.00153-0.00030*pt;
      else if (idx == 64  ) num = 1.00048-0.00025*pt;
      else if (idx == 65  ) num = 0.99224-0.00002*pt;
      else if (idx == 66  ) num = 0.99794-0.00013*pt;
      else if (idx == 67  ) num = 0.99133+0.00005*pt;
      else if (idx == 68  ) num = 0.99822-0.00014*pt;
      else if (idx == 69  ) num = 1.00460-0.00036*pt;
      else if (idx == 70  ) num = 0.99673-0.00008*pt;
      else if (idx == 71  ) num = 0.99334-0.00003*pt;
      else if (idx == 72  ) num = 0.99906-0.00021*pt;
      else if (idx == 73  ) num = 0.99565-0.00003*pt;
      else if (idx == 74  ) num = 0.99314+0.00001*pt;
      else if (idx == 75  ) num = 0.99960-0.00020*pt;
      else if (idx == 76  ) num = 0.99471-0.00003*pt;
      else if (idx == 77  ) num = 0.99355-0.00006*pt;
      else if (idx == 78  ) num = 0.99355-0.00005*pt;
      else if (idx == 79  ) num = 0.99772-0.00011*pt;
      else if (idx == 80  ) num = 0.99352+0.00001*pt;
      else if (idx == 81  ) num = 0.99338+0.00002*pt;
      else if (idx == 82  ) num = 0.99361-0.00001*pt;
      else if (idx == 83  ) num = 0.99391-0.00004*pt;
      else if (idx == 84  ) num = 0.99642-0.00006*pt;
      else if (idx == 85  ) num = 0.99993-0.00017*pt;
      else if (idx == 86  ) num = 0.99369+0.00000*pt;
      else if (idx == 87  ) num = 0.99142+0.00002*pt;
      else if (idx == 88  ) num = 0.99581-0.00008*pt;
      else if (idx == 89  ) num = 0.98892+0.00005*pt;
      else if (idx == 90  ) num = 0.99164+0.00002*pt;
      else if (idx == 91  ) num = 0.99968-0.00023*pt;
      else if (idx == 92  ) num = 0.99331-0.00002*pt;
      else if (idx == 93  ) num = 0.99404-0.00005*pt;
      else if (idx == 94  ) num = 0.99302+0.00002*pt;
      else if (idx == 95  ) num = 0.99029+0.00006*pt;
      else if (idx == 96  ) num = 0.99444-0.00003*pt;
      else if (idx == 97  ) num = 0.99186+0.00004*pt;
      else if (idx == 98  ) num = 1.00664-0.00037*pt;
      else if (idx == 99  ) num = 0.99217+0.00004*pt;
      else if (idx == 100 ) num = 0.99248-0.00000*pt;
   } else {
      if (idx == 1   ) num = 0.99055-0.00021*pt;
      else if (idx == 2   ) num = 1.00575-0.00076*pt;
      else if (idx == 3   ) num = 1.00723-0.00105*pt;
      else if (idx == 4   ) num = 1.01257-0.00113*pt;
      else if (idx == 5   ) num = 1.01794-0.00122*pt;
      else if (idx == 6   ) num = 0.98201+0.00006*pt;
      else if (idx == 7   ) num = 1.00617-0.00089*pt;
      else if (idx == 8   ) num = 1.02141-0.00125*pt;
      else if (idx == 9   ) num = 0.98474+0.00002*pt;
      else if (idx == 10  ) num = 1.02044-0.00144*pt;
      else if (idx == 11  ) num = 1.02361-0.00157*pt;
      else if (idx == 12  ) num = 1.01460-0.00112*pt;
      else if (idx == 13  ) num = 0.98953-0.00013*pt;
      else if (idx == 14  ) num = 1.01341-0.00107*pt;
      else if (idx == 15  ) num = 0.99410-0.00033*pt;
      else if (idx == 16  ) num = 1.00246-0.00049*pt;
      else if (idx == 17  ) num = 1.01780-0.00126*pt;
      else if (idx == 18  ) num = 0.98720-0.00013*pt;
      else if (idx == 19  ) num = 1.01077-0.00098*pt;
      else if (idx == 20  ) num = 0.98846-0.00021*pt;
      else if (idx == 21  ) num = 1.02426-0.00141*pt;
      else if (idx == 22  ) num = 1.02677-0.00160*pt;
      else if (idx == 23  ) num = 0.98160+0.00001*pt;
      else if (idx == 24  ) num = 1.00190-0.00069*pt;
      else if (idx == 25  ) num = 1.00656-0.00097*pt;
      else if (idx == 26  ) num = 1.00116-0.00053*pt;
      else if (idx == 27  ) num = 1.03282-0.00199*pt;
      else if (idx == 28  ) num = 1.03228-0.00171*pt;
      else if (idx == 29  ) num = 1.00219-0.00054*pt;
      else if (idx == 30  ) num = 0.99247-0.00033*pt;
      else if (idx == 31  ) num = 1.00282-0.00057*pt;
      else if (idx == 32  ) num = 1.01004-0.00116*pt;
      else if (idx == 33  ) num = 0.98343-0.00001*pt;
      else if (idx == 34  ) num = 0.97948+0.00012*pt;
      else if (idx == 35  ) num = 1.00953-0.00106*pt;
      else if (idx == 36  ) num = 1.01481-0.00112*pt;
      else if (idx == 37  ) num = 0.99723-0.00043*pt;
      else if (idx == 38  ) num = 1.00172-0.00074*pt;
      else if (idx == 39  ) num = 1.01495-0.00140*pt;
      else if (idx == 40  ) num = 0.99862-0.00066*pt;
      else if (idx == 41  ) num = 0.98936-0.00042*pt;
      else if (idx == 42  ) num = 0.99775-0.00073*pt;
      else if (idx == 43  ) num = 1.02736-0.00175*pt;
      else if (idx == 44  ) num = 1.00350-0.00066*pt;
      else if (idx == 45  ) num = 0.99788-0.00044*pt;
      else if (idx == 46  ) num = 1.02699-0.00162*pt;
      else if (idx == 47  ) num = 1.00365-0.00076*pt;
      else if (idx == 48  ) num = 1.03050-0.00179*pt;
      else if (idx == 49  ) num = 1.03802-0.00207*pt;
      else if (idx == 50  ) num = 1.00410-0.00068*pt;
      else if (idx == 51  ) num = 1.00182-0.00062*pt;
      else if (idx == 52  ) num = 1.00505-0.00068*pt;
      else if (idx == 53  ) num = 0.99925-0.00051*pt;
      else if (idx == 54  ) num = 1.01962-0.00122*pt;
      else if (idx == 55  ) num = 0.99921-0.00066*pt;
      else if (idx == 56  ) num = 0.98260+0.00001*pt;
      else if (idx == 57  ) num = 0.99913-0.00063*pt;
      else if (idx == 58  ) num = 1.00406-0.00069*pt;
      else if (idx == 59  ) num = 1.02864-0.00162*pt;
      else if (idx == 60  ) num = 1.03402-0.00202*pt;
      else if (idx == 61  ) num = 0.99506-0.00030*pt;
      else if (idx == 62  ) num = 0.99301-0.00040*pt;
      else if (idx == 63  ) num = 0.99860-0.00059*pt;
      else if (idx == 64  ) num = 1.00168-0.00057*pt;
      else if (idx == 65  ) num = 0.99589-0.00032*pt;
      else if (idx == 66  ) num = 0.99860-0.00069*pt;
      else if (idx == 67  ) num = 0.99715-0.00063*pt;
      else if (idx == 68  ) num = 1.02335-0.00169*pt;
      else if (idx == 69  ) num = 1.01927-0.00142*pt;
      else if (idx == 70  ) num = 0.98856-0.00039*pt;
      else if (idx == 71  ) num = 1.00034-0.00072*pt;
      else if (idx == 72  ) num = 1.02930-0.00168*pt;
      else if (idx == 73  ) num = 0.98463-0.00006*pt;
      else if (idx == 74  ) num = 1.01116-0.00110*pt;
      else if (idx == 75  ) num = 0.98192-0.00007*pt;
      else if (idx == 76  ) num = 1.00140-0.00068*pt;
      else if (idx == 77  ) num = 0.99682-0.00046*pt;
      else if (idx == 78  ) num = 1.00440-0.00060*pt;
      else if (idx == 79  ) num = 1.03347-0.00179*pt;
      else if (idx == 80  ) num = 1.00934-0.00099*pt;
      else if (idx == 81  ) num = 1.02519-0.00154*pt;
      else if (idx == 82  ) num = 1.01039-0.00095*pt;
      else if (idx == 83  ) num = 0.99749-0.00043*pt;
      else if (idx == 84  ) num = 1.02613-0.00176*pt;
      else if (idx == 85  ) num = 1.01355-0.00095*pt;
      else if (idx == 86  ) num = 1.00029-0.00057*pt;
      else if (idx == 87  ) num = 0.98476-0.00003*pt;
      else if (idx == 88  ) num = 0.99401-0.00046*pt;
      else if (idx == 89  ) num = 1.00248-0.00063*pt;
      else if (idx == 90  ) num = 1.00679-0.00087*pt;
      else if (idx == 91  ) num = 1.03927-0.00210*pt;
      else if (idx == 92  ) num = 0.99516-0.00041*pt;
      else if (idx == 93  ) num = 1.01881-0.00136*pt;
      else if (idx == 94  ) num = 0.99210-0.00046*pt;
      else if (idx == 95  ) num = 1.01780-0.00120*pt;
      else if (idx == 96  ) num = 1.01905-0.00131*pt;
      else if (idx == 97  ) num = 0.99506-0.00027*pt;
      else if (idx == 98  ) num = 1.02405-0.00160*pt;
      else if (idx == 99  ) num = 1.02782-0.00154*pt;
      else if (idx == 100 ) num = 0.99645-0.00031*pt;
   }

   return num / den;
}

double tnp_weight_iso_ppb(double pt, double eta, int idx=0) {
   if (idx == -10) {
      if (fabs(eta)<0.9) {
         // 0 < |eta| < 1.2
         if (pt<15) return 0.96411;
         else if (pt<25) return 0.940366;
         else if (pt<30) return 0.968303;
         else if (pt<35) return 0.976586;
         else if (pt<40) return 0.978119;
         else if (pt<45) return 0.994485;
         else if (pt<50) return 0.994079;
         else if (pt<80) return 0.992388;
         else if (pt<200) return 1.00418;
      } else if (fabs(eta)<2.1) {
         // 1.2 < |eta| < 2.1
         if (pt<15) return 0.994224;
         else if (pt<25) return 0.935425;
         else if (pt<30) return 0.979308;
         else if (pt<35) return 0.990986;
         else if (pt<40) return 0.99741;
         else if (pt<45) return 0.991717;
         else if (pt<50) return 0.989969;
         else if (pt<80) return 0.998137;
         else if (pt<200) return 1.00188;
      } else {
         // 2.1 < |eta| < 2.4
         if (pt<15) return 0.875673;
         else if (pt<25) return 0.960382;
         else if (pt<40) return 0.979153;
         else if (pt<80) return 0.991396;
         else if (pt<200) return 0.96754;
      }
   }

   double num = 1, den = 1;

   // nominal
   if (fabs(eta)<1.2) {
      num = 0.53624*TMath::Erf((pt+8.22202)/38.41131)+0.46426;
      den = 0.58560*TMath::Erf((pt+9.25763)/32.25275)+0.40929;
   } else if (fabs(eta)<2.1) {
      num = 0.44982*TMath::Erf((pt+9.99830)/38.48086)+0.55059;
      den = 0.55089*TMath::Erf((pt+9.96748)/30.03004)+0.44244;
   } else {
      num = 0.88466*TMath::Erf((pt+1.64971)/18.22598)+0.08429;
      den = 0.86567*TMath::Erf((pt+9.99595)/22.52523)+0.12230;
   }

   // 100 variations
   if (fabs(eta)<1.2) {
      if (idx == 1   ) num = 0.71171*TMath::Erf((pt+9.36328)/35.43679)+0.28652;
      else if (idx == 2   ) num = 0.40017*TMath::Erf((pt+1.10719)/35.04344)+0.59847;
      else if (idx == 3   ) num = 0.69234*TMath::Erf((pt+9.99977)/35.11500)+0.30339;
      else if (idx == 4   ) num = 0.72113*TMath::Erf((pt-3.34366)/19.67100)+0.26017;
      else if (idx == 5   ) num = 0.36392*TMath::Erf((pt+1.22608)/36.23530)+0.63608;
      else if (idx == 6   ) num = 0.31920*TMath::Erf((pt+1.56949)/39.17600)+0.68257;
      else if (idx == 7   ) num = 0.71025*TMath::Erf((pt+9.99873)/36.06450)+0.28759;
      else if (idx == 8   ) num = 0.64702*TMath::Erf((pt+9.99972)/37.35917)+0.34880;
      else if (idx == 9   ) num = 0.71360*TMath::Erf((pt+7.21989)/33.79814)+0.28630;
      else if (idx == 10  ) num = 0.06919*TMath::Erf((pt-31.61270)/10.42686)+0.91873;
      else if (idx == 11  ) num = 0.71146*TMath::Erf((pt+9.16653)/35.45365)+0.28393;
      else if (idx == 12  ) num = 0.11912*TMath::Erf((pt-26.08987)/15.72068)+0.87096;
      else if (idx == 13  ) num = 0.11790*TMath::Erf((pt-24.11218)/18.27307)+0.87204;
      else if (idx == 14  ) num = 0.08125*TMath::Erf((pt-31.00325)/11.00005)+0.90781;
      else if (idx == 15  ) num = 0.71491*TMath::Erf((pt+0.19890)/25.53791)+0.27353;
      else if (idx == 16  ) num = 0.07979*TMath::Erf((pt-29.36728)/10.15930)+0.90545;
      else if (idx == 17  ) num = 0.71537*TMath::Erf((pt+0.64547)/25.28390)+0.27194;
      else if (idx == 18  ) num = 0.06021*TMath::Erf((pt-34.54751)/10.84310)+0.93095;
      else if (idx == 19  ) num = 0.35614*TMath::Erf((pt+1.07358)/37.25166)+0.64375;
      else if (idx == 20  ) num = 0.07369*TMath::Erf((pt-31.97231)/11.80755)+0.91821;
      else if (idx == 21  ) num = 0.32871*TMath::Erf((pt-0.57605)/37.07682)+0.67099;
      else if (idx == 22  ) num = 0.64051*TMath::Erf((pt+9.99763)/36.41545)+0.35447;
      else if (idx == 23  ) num = 0.71042*TMath::Erf((pt+10.00000)/35.16391)+0.28892;
      else if (idx == 24  ) num = 0.56915*TMath::Erf((pt+9.98799)/38.44482)+0.42824;
      else if (idx == 25  ) num = 0.67472*TMath::Erf((pt+9.98491)/38.27270)+0.32688;
      else if (idx == 26  ) num = 0.68504*TMath::Erf((pt+9.49452)/36.64421)+0.31342;
      else if (idx == 27  ) num = 0.08351*TMath::Erf((pt-29.12168)/14.93574)+0.90799;
      else if (idx == 28  ) num = 0.07569*TMath::Erf((pt-30.29971)/12.90252)+0.91416;
      else if (idx == 29  ) num = 0.39587*TMath::Erf((pt-0.13956)/34.61386)+0.60588;
      else if (idx == 30  ) num = 0.71378*TMath::Erf((pt+3.04411)/28.56045)+0.27625;
      else if (idx == 31  ) num = 0.60853*TMath::Erf((pt+9.76041)/39.23656)+0.39503;
      else if (idx == 32  ) num = 0.12696*TMath::Erf((pt-24.12578)/17.76784)+0.86574;
      else if (idx == 33  ) num = 0.53931*TMath::Erf((pt+9.70250)/41.48066)+0.46532;
      else if (idx == 34  ) num = 0.10430*TMath::Erf((pt-26.83022)/20.76573)+0.89588;
      else if (idx == 35  ) num = 0.70864*TMath::Erf((pt+9.99664)/35.38716)+0.28689;
      else if (idx == 36  ) num = 0.09599*TMath::Erf((pt-28.10707)/16.91460)+0.89982;
      else if (idx == 37  ) num = 0.11343*TMath::Erf((pt-24.87533)/18.40406)+0.87842;
      else if (idx == 38  ) num = 0.71244*TMath::Erf((pt+4.59654)/29.50298)+0.27696;
      else if (idx == 39  ) num = 0.71320*TMath::Erf((pt+5.10805)/30.97529)+0.28102;
      else if (idx == 40  ) num = 0.29685*TMath::Erf((pt+1.47818)/41.05973)+0.70665;
      else if (idx == 41  ) num = 0.62463*TMath::Erf((pt+9.99726)/36.28384)+0.37140;
      else if (idx == 42  ) num = 0.14649*TMath::Erf((pt-22.14799)/21.65147)+0.84697;
      else if (idx == 43  ) num = 0.71080*TMath::Erf((pt+9.98892)/36.03427)+0.28798;
      else if (idx == 44  ) num = 0.09505*TMath::Erf((pt-28.96016)/15.01355)+0.89617;
      else if (idx == 45  ) num = 0.66738*TMath::Erf((pt+9.99949)/34.87761)+0.32317;
      else if (idx == 46  ) num = 0.08788*TMath::Erf((pt-29.91768)/15.03617)+0.90551;
      else if (idx == 47  ) num = 0.63654*TMath::Erf((pt+9.99803)/35.69627)+0.35766;
      else if (idx == 48  ) num = 0.55687*TMath::Erf((pt+8.11257)/37.64915)+0.43969;
      else if (idx == 49  ) num = 0.35495*TMath::Erf((pt+0.90249)/36.04664)+0.64369;
      else if (idx == 50  ) num = 0.71317*TMath::Erf((pt+3.70522)/29.12256)+0.27693;
      else if (idx == 51  ) num = 0.77295*TMath::Erf((pt+9.98675)/33.90700)+0.21839;
      else if (idx == 52  ) num = 0.44009*TMath::Erf((pt+3.86269)/35.68956)+0.55591;
      else if (idx == 53  ) num = 0.60668*TMath::Erf((pt+9.57166)/38.06886)+0.39127;
      else if (idx == 54  ) num = 0.56459*TMath::Erf((pt+9.96358)/40.47465)+0.43656;
      else if (idx == 55  ) num = 0.09594*TMath::Erf((pt-26.78121)/13.71426)+0.89249;
      else if (idx == 56  ) num = 0.06609*TMath::Erf((pt-33.39640)/11.63090)+0.92662;
      else if (idx == 57  ) num = 0.09481*TMath::Erf((pt-27.72014)/11.54018)+0.88973;
      else if (idx == 58  ) num = 0.06348*TMath::Erf((pt-32.64882)/10.58504)+0.92658;
      else if (idx == 59  ) num = 0.07685*TMath::Erf((pt-31.11384)/11.46491)+0.91339;
      else if (idx == 60  ) num = 0.67765*TMath::Erf((pt+10.00000)/35.25769)+0.31727;
      else if (idx == 61  ) num = 0.72045*TMath::Erf((pt+5.69656)/29.81852)+0.26916;
      else if (idx == 62  ) num = 0.07878*TMath::Erf((pt-30.98763)/10.96670)+0.91019;
      else if (idx == 63  ) num = 0.56089*TMath::Erf((pt+9.98237)/37.96761)+0.43649;
      else if (idx == 64  ) num = 0.33432*TMath::Erf((pt+0.50286)/36.14517)+0.66261;
      else if (idx == 65  ) num = 0.35019*TMath::Erf((pt+1.66380)/37.32890)+0.64983;
      else if (idx == 66  ) num = 0.71617*TMath::Erf((pt+0.24038)/25.50637)+0.27023;
      else if (idx == 67  ) num = 0.05709*TMath::Erf((pt-32.39754)/9.56402)+0.92881;
      else if (idx == 68  ) num = 0.06854*TMath::Erf((pt-32.50011)/9.95893)+0.92053;
      else if (idx == 69  ) num = 0.33935*TMath::Erf((pt+2.68942)/38.30565)+0.65965;
      else if (idx == 70  ) num = 0.71258*TMath::Erf((pt+6.45494)/32.94508)+0.28361;
      else if (idx == 71  ) num = 0.06667*TMath::Erf((pt-31.37687)/9.64718)+0.91662;
      else if (idx == 72  ) num = 0.08020*TMath::Erf((pt-29.87890)/13.09477)+0.91059;
      else if (idx == 73  ) num = 0.40976*TMath::Erf((pt-2.22774)/29.47626)+0.58102;
      else if (idx == 74  ) num = 0.71271*TMath::Erf((pt+6.65236)/32.63228)+0.28388;
      else if (idx == 75  ) num = 0.06062*TMath::Erf((pt-34.28353)/9.05722)+0.93067;
      else if (idx == 76  ) num = 0.08868*TMath::Erf((pt-29.44345)/12.48116)+0.90319;
      else if (idx == 77  ) num = 0.71061*TMath::Erf((pt+9.77144)/36.17611)+0.28781;
      else if (idx == 78  ) num = 0.63569*TMath::Erf((pt+9.99825)/37.37939)+0.36510;
      else if (idx == 79  ) num = 0.71171*TMath::Erf((pt+5.66241)/31.07945)+0.28091;
      else if (idx == 80  ) num = 0.07350*TMath::Erf((pt-31.02483)/12.34402)+0.91452;
      else if (idx == 81  ) num = 0.39847*TMath::Erf((pt+3.24920)/37.67446)+0.60283;
      else if (idx == 82  ) num = 0.70919*TMath::Erf((pt+9.57934)/36.09979)+0.28692;
      else if (idx == 83  ) num = 0.68316*TMath::Erf((pt+9.28782)/36.55986)+0.31484;
      else if (idx == 84  ) num = 0.09121*TMath::Erf((pt-29.02686)/10.07622)+0.89501;
      else if (idx == 85  ) num = 0.32466*TMath::Erf((pt+1.07299)/37.26200)+0.67342;
      else if (idx == 86  ) num = 0.06034*TMath::Erf((pt-33.54979)/9.69807)+0.92839;
      else if (idx == 87  ) num = 0.71318*TMath::Erf((pt+3.10828)/28.30722)+0.27618;
      else if (idx == 88  ) num = 0.70315*TMath::Erf((pt+6.80061)/32.05872)+0.29259;
      else if (idx == 89  ) num = 0.59180*TMath::Erf((pt+9.99098)/38.30765)+0.40687;
      else if (idx == 90  ) num = 0.55470*TMath::Erf((pt+9.00555)/39.52819)+0.44521;
      else if (idx == 91  ) num = 0.57693*TMath::Erf((pt+9.99060)/38.33827)+0.42309;
      else if (idx == 92  ) num = 0.52966*TMath::Erf((pt+7.10896)/37.79526)+0.46908;
      else if (idx == 93  ) num = 0.49572*TMath::Erf((pt+5.61189)/36.47477)+0.50256;
      else if (idx == 94  ) num = 0.71590*TMath::Erf((pt-1.41842)/22.15541)+0.26401;
      else if (idx == 95  ) num = 0.60688*TMath::Erf((pt+9.99313)/37.32513)+0.38978;
      else if (idx == 96  ) num = 0.71234*TMath::Erf((pt+6.63841)/32.09513)+0.28235;
      else if (idx == 97  ) num = 0.71314*TMath::Erf((pt+5.88965)/30.74107)+0.28010;
      else if (idx == 98  ) num = 0.71228*TMath::Erf((pt+6.56579)/32.50483)+0.28317;
      else if (idx == 99  ) num = 0.11068*TMath::Erf((pt-26.49019)/17.10899)+0.88323;
      else if (idx == 100 ) num = 0.71255*TMath::Erf((pt+4.55820)/29.83613)+0.27773;
   } else if (fabs(eta)<2.1) {
      if (idx == 1   ) num = 0.86349*TMath::Erf((pt+8.07992)/27.37254)+0.12131;
      else if (idx == 2   ) num = 0.17512*TMath::Erf((pt-10.77992)/26.37856)+0.81976;
      else if (idx == 3   ) num = 0.10874*TMath::Erf((pt-8.59857)/73.33249)+0.90870;
      else if (idx == 4   ) num = 0.42488*TMath::Erf((pt+7.42112)/35.63043)+0.56798;
      else if (idx == 5   ) num = 0.19455*TMath::Erf((pt-13.38780)/22.94396)+0.79525;
      else if (idx == 6   ) num = 0.26214*TMath::Erf((pt-5.61271)/26.35599)+0.72397;
      else if (idx == 7   ) num = 0.09533*TMath::Erf((pt-24.20377)/11.94557)+0.89211;
      else if (idx == 8   ) num = 0.06731*TMath::Erf((pt-27.73130)/10.64385)+0.91910;
      else if (idx == 9   ) num = 0.08314*TMath::Erf((pt-22.95013)/7.09152)+0.89281;
      else if (idx == 10  ) num = 0.09091*TMath::Erf((pt-24.18641)/15.91653)+0.90225;
      else if (idx == 11  ) num = 0.08632*TMath::Erf((pt-24.82080)/11.56567)+0.89531;
      else if (idx == 12  ) num = 0.10640*TMath::Erf((pt-23.03850)/9.18770)+0.87142;
      else if (idx == 13  ) num = 0.07662*TMath::Erf((pt-25.77804)/11.74013)+0.90886;
      else if (idx == 14  ) num = 0.06644*TMath::Erf((pt-28.98158)/8.93344)+0.92145;
      else if (idx == 15  ) num = 0.14063*TMath::Erf((pt-18.27949)/21.18759)+0.85188;
      else if (idx == 16  ) num = 0.06615*TMath::Erf((pt-26.73128)/7.36637)+0.91633;
      else if (idx == 17  ) num = 0.13760*TMath::Erf((pt-13.43088)/30.13992)+0.85196;
      else if (idx == 18  ) num = 0.20485*TMath::Erf((pt-14.79871)/13.53384)+0.77495;
      else if (idx == 19  ) num = 0.14338*TMath::Erf((pt-10.61783)/36.80908)+0.85807;
      else if (idx == 20  ) num = 0.14414*TMath::Erf((pt-19.35085)/19.19196)+0.85108;
      else if (idx == 21  ) num = 0.08278*TMath::Erf((pt-24.66163)/14.24753)+0.90252;
      else if (idx == 22  ) num = 0.23350*TMath::Erf((pt-7.98711)/27.92798)+0.76186;
      else if (idx == 23  ) num = 0.08542*TMath::Erf((pt-25.77495)/10.42786)+0.90131;
      else if (idx == 24  ) num = 0.06790*TMath::Erf((pt-28.95838)/11.97601)+0.92317;
      else if (idx == 25  ) num = 0.06068*TMath::Erf((pt-29.84462)/12.21460)+0.92553;
      else if (idx == 26  ) num = 0.06138*TMath::Erf((pt-29.06956)/9.34744)+0.92721;
      else if (idx == 27  ) num = 0.07381*TMath::Erf((pt-26.82531)/11.09679)+0.91302;
      else if (idx == 28  ) num = 0.20752*TMath::Erf((pt-14.33857)/15.92703)+0.78118;
      else if (idx == 29  ) num = 0.15127*TMath::Erf((pt-9.93445)/28.69037)+0.83926;
      else if (idx == 30  ) num = 0.06375*TMath::Erf((pt-27.14884)/7.92771)+0.92106;
      else if (idx == 31  ) num = 0.76942*TMath::Erf((pt+9.69291)/28.69545)+0.21400;
      else if (idx == 32  ) num = 0.13830*TMath::Erf((pt-11.94647)/23.65610)+0.84443;
      else if (idx == 33  ) num = 0.07378*TMath::Erf((pt-27.38314)/12.14425)+0.91541;
      else if (idx == 34  ) num = 0.06612*TMath::Erf((pt-26.68620)/2.21578)+0.90894;
      else if (idx == 35  ) num = 0.05587*TMath::Erf((pt-26.23877)/3.04897)+0.91988;
      else if (idx == 36  ) num = 0.43869*TMath::Erf((pt-2.26441)/22.73906)+0.54288;
      else if (idx == 37  ) num = 0.49745*TMath::Erf((pt-0.86704)/24.46942)+0.49171;
      else if (idx == 38  ) num = 0.50222*TMath::Erf((pt+3.47076)/30.38881)+0.49462;
      else if (idx == 39  ) num = 0.04351*TMath::Erf((pt-34.51105)/7.98916)+0.94741;
      else if (idx == 40  ) num = 0.58011*TMath::Erf((pt+5.80305)/30.45289)+0.41435;
      else if (idx == 41  ) num = 0.21489*TMath::Erf((pt-7.53766)/29.22944)+0.78014;
      else if (idx == 42  ) num = 0.32015*TMath::Erf((pt-5.44879)/23.69303)+0.66441;
      else if (idx == 43  ) num = 0.11343*TMath::Erf((pt+2.17599)/73.61471)+0.87662;
      else if (idx == 44  ) num = 0.23656*TMath::Erf((pt-8.05536)/23.29300)+0.75023;
      else if (idx == 45  ) num = 0.14745*TMath::Erf((pt-10.58350)/30.92344)+0.84978;
      else if (idx == 46  ) num = 0.07778*TMath::Erf((pt-24.01812)/9.81133)+0.89392;
      else if (idx == 47  ) num = 0.10253*TMath::Erf((pt+8.58560)/76.84117)+0.89424;
      else if (idx == 48  ) num = 0.06113*TMath::Erf((pt-28.83273)/10.08664)+0.92097;
      else if (idx == 49  ) num = 0.18151*TMath::Erf((pt-12.39950)/22.37806)+0.80821;
      else if (idx == 50  ) num = 0.17972*TMath::Erf((pt-15.71203)/17.07144)+0.80631;
      else if (idx == 51  ) num = 0.08881*TMath::Erf((pt-24.99060)/12.86231)+0.89898;
      else if (idx == 52  ) num = 0.06160*TMath::Erf((pt-27.05906)/12.49832)+0.92722;
      else if (idx == 53  ) num = 0.50198*TMath::Erf((pt+4.56976)/30.13441)+0.49161;
      else if (idx == 54  ) num = 0.06241*TMath::Erf((pt-29.40920)/8.56260)+0.91695;
      else if (idx == 55  ) num = 0.27927*TMath::Erf((pt-3.22014)/30.00102)+0.71669;
      else if (idx == 56  ) num = 0.63202*TMath::Erf((pt+6.73895)/29.14993)+0.35526;
      else if (idx == 57  ) num = 0.05075*TMath::Erf((pt-26.75777)/2.01079)+0.92414;
      else if (idx == 58  ) num = 0.20242*TMath::Erf((pt-8.91423)/26.37151)+0.79092;
      else if (idx == 59  ) num = 0.12640*TMath::Erf((pt-19.84619)/15.93088)+0.85694;
      else if (idx == 60  ) num = 0.06094*TMath::Erf((pt-28.97920)/11.37691)+0.92765;
      else if (idx == 61  ) num = 0.21827*TMath::Erf((pt-9.74725)/24.43130)+0.77385;
      else if (idx == 62  ) num = 0.09883*TMath::Erf((pt-23.04427)/15.92401)+0.88566;
      else if (idx == 63  ) num = 0.08668*TMath::Erf((pt-24.33696)/8.03752)+0.88786;
      else if (idx == 64  ) num = 0.08990*TMath::Erf((pt-24.87808)/11.30427)+0.89079;
      else if (idx == 65  ) num = 0.10040*TMath::Erf((pt-23.06964)/19.31583)+0.88969;
      else if (idx == 66  ) num = 0.22482*TMath::Erf((pt-1.48651)/31.83369)+0.76440;
      else if (idx == 67  ) num = 0.50702*TMath::Erf((pt+6.47217)/33.76253)+0.49131;
      else if (idx == 68  ) num = 0.06543*TMath::Erf((pt-28.05585)/10.49955)+0.91937;
      else if (idx == 69  ) num = 0.18593*TMath::Erf((pt-10.45016)/22.95164)+0.79469;
      else if (idx == 70  ) num = 0.05894*TMath::Erf((pt-25.57455)/3.05210)+0.91716;
      else if (idx == 71  ) num = 0.15530*TMath::Erf((pt-17.16131)/15.59863)+0.82763;
      else if (idx == 72  ) num = 0.10457*TMath::Erf((pt-21.91301)/10.22194)+0.87165;
      else if (idx == 73  ) num = 0.03432*TMath::Erf((pt-35.64744)/0.03280)+0.94849;
      else if (idx == 74  ) num = 0.29786*TMath::Erf((pt+8.48019)/43.98310)+0.70365;
      else if (idx == 75  ) num = 0.09942*TMath::Erf((pt-22.42558)/16.02762)+0.88524;
      else if (idx == 76  ) num = 0.07010*TMath::Erf((pt-25.89071)/14.44650)+0.91784;
      else if (idx == 77  ) num = 0.21727*TMath::Erf((pt-14.64656)/18.81864)+0.77039;
      else if (idx == 78  ) num = 0.13446*TMath::Erf((pt-20.91962)/15.92623)+0.85343;
      else if (idx == 79  ) num = 0.07670*TMath::Erf((pt-25.42378)/9.20285)+0.90619;
      else if (idx == 80  ) num = 0.91324*TMath::Erf((pt+9.19800)/27.22456)+0.07593;
      else if (idx == 81  ) num = 0.13146*TMath::Erf((pt-13.07970)/35.10025)+0.87165;
      else if (idx == 82  ) num = 0.14611*TMath::Erf((pt-18.29973)/16.38417)+0.84159;
      else if (idx == 83  ) num = 0.08879*TMath::Erf((pt-23.21557)/23.22080)+0.90419;
      else if (idx == 84  ) num = 0.20070*TMath::Erf((pt-3.08108)/35.17696)+0.79587;
      else if (idx == 85  ) num = 0.26870*TMath::Erf((pt+5.43169)/39.37626)+0.72587;
      else if (idx == 86  ) num = 0.21914*TMath::Erf((pt+5.76516)/47.71960)+0.78412;
      else if (idx == 87  ) num = 0.07201*TMath::Erf((pt-28.17309)/11.69402)+0.91642;
      else if (idx == 88  ) num = 0.78379*TMath::Erf((pt+6.49916)/26.90177)+0.20313;
      else if (idx == 89  ) num = 0.40532*TMath::Erf((pt-8.11503)/19.09341)+0.57935;
      else if (idx == 90  ) num = 0.07669*TMath::Erf((pt-27.50293)/15.88586)+0.91516;
      else if (idx == 91  ) num = 0.18714*TMath::Erf((pt-12.56768)/20.05342)+0.79373;
      else if (idx == 92  ) num = 0.17672*TMath::Erf((pt-10.47276)/26.10521)+0.81402;
      else if (idx == 93  ) num = 0.06828*TMath::Erf((pt-27.78211)/12.82167)+0.91798;
      else if (idx == 94  ) num = 0.09090*TMath::Erf((pt-24.63375)/12.69529)+0.89760;
      else if (idx == 95  ) num = 0.09374*TMath::Erf((pt-25.22080)/8.95559)+0.89151;
      else if (idx == 96  ) num = 0.20544*TMath::Erf((pt-8.27236)/25.88127)+0.78466;
      else if (idx == 97  ) num = 0.09203*TMath::Erf((pt-24.61620)/20.00726)+0.90444;
      else if (idx == 98  ) num = 0.07573*TMath::Erf((pt-23.55542)/10.95749)+0.90238;
      else if (idx == 99  ) num = 0.09192*TMath::Erf((pt-23.26430)/32.16077)+0.91379;
      else if (idx == 100 ) num = 0.11814*TMath::Erf((pt-22.20467)/14.73104)+0.86955;
   } else {
      if (idx == 1   ) num = 0.96378*TMath::Erf((pt-3.20931)/13.65281)+0.01212;
      else if (idx == 2   ) num = 0.94072*TMath::Erf((pt+9.99997)/24.01967)+0.02776;
      else if (idx == 3   ) num = 0.90116*TMath::Erf((pt+7.53096)/24.04852)+0.05565;
      else if (idx == 4   ) num = 0.95673*TMath::Erf((pt-4.75573)/11.77385)-0.00265;
      else if (idx == 5   ) num = 0.95261*TMath::Erf((pt-2.48778)/13.39726)+0.00421;
      else if (idx == 6   ) num = 0.95823*TMath::Erf((pt+3.97442)/21.53510)+0.02572;
      else if (idx == 7   ) num = 0.95246*TMath::Erf((pt+2.60846)/18.88834)+0.01069;
      else if (idx == 8   ) num = 0.93045*TMath::Erf((pt+10.00000)/18.37164)+0.02525;
      else if (idx == 9   ) num = 0.95982*TMath::Erf((pt+2.49912)/20.19537)+0.02685;
      else if (idx == 10  ) num = 0.23965*TMath::Erf((pt-8.82977)/13.63288)+0.70582;
      else if (idx == 11  ) num = 0.94529*TMath::Erf((pt-4.15152)/12.08725)-0.00164;
      else if (idx == 12  ) num = 0.98393*TMath::Erf((pt-7.74727)/8.03191)-0.02755;
      else if (idx == 13  ) num = 0.28325*TMath::Erf((pt+5.36480)/35.60913)+0.70786;
      else if (idx == 14  ) num = 0.93802*TMath::Erf((pt+9.99919)/24.83719)+0.02441;
      else if (idx == 15  ) num = 0.52134*TMath::Erf((pt+8.78065)/30.85593)+0.46331;
      else if (idx == 16  ) num = 0.94608*TMath::Erf((pt+10.00000)/23.85688)+0.03277;
      else if (idx == 17  ) num = 0.31020*TMath::Erf((pt+9.95397)/29.30049)+0.64204;
      else if (idx == 18  ) num = 0.41594*TMath::Erf((pt+7.31923)/35.50753)+0.57694;
      else if (idx == 19  ) num = 0.93560*TMath::Erf((pt+9.99993)/22.74865)+0.02478;
      else if (idx == 20  ) num = 0.39286*TMath::Erf((pt+7.44415)/36.23315)+0.59762;
      else if (idx == 21  ) num = 0.51684*TMath::Erf((pt+9.70668)/25.38600)+0.43659;
      else if (idx == 22  ) num = 0.92605*TMath::Erf((pt+9.99892)/21.94013)+0.01749;
      else if (idx == 23  ) num = 0.96155*TMath::Erf((pt-0.18739)/17.64558)+0.01704;
      else if (idx == 24  ) num = 0.85194*TMath::Erf((pt+10.00000)/26.30439)+0.11958;
      else if (idx == 25  ) num = 0.89396*TMath::Erf((pt+9.99149)/26.29052)+0.06754;
      else if (idx == 26  ) num = 0.93951*TMath::Erf((pt+10.00000)/21.33852)+0.03015;
      else if (idx == 27  ) num = 0.95071*TMath::Erf((pt-7.12019)/9.41597)-0.01935;
      else if (idx == 28  ) num = 0.93144*TMath::Erf((pt+9.99967)/23.78697)+0.01883;
      else if (idx == 29  ) num = 0.96620*TMath::Erf((pt-3.37905)/13.41142)+0.01069;
      else if (idx == 30  ) num = 0.96218*TMath::Erf((pt-2.39404)/14.01456)+0.00980;
      else if (idx == 31  ) num = 0.32395*TMath::Erf((pt+6.78666)/30.86378)+0.65525;
      else if (idx == 32  ) num = 0.94632*TMath::Erf((pt+0.10772)/17.53596)+0.00668;
      else if (idx == 33  ) num = 0.49425*TMath::Erf((pt+8.28798)/34.37108)+0.49967;
      else if (idx == 34  ) num = 0.98650*TMath::Erf((pt-6.37956)/11.87674)-0.00506;
      else if (idx == 35  ) num = 0.94955*TMath::Erf((pt-0.39847)/16.15760)+0.00589;
      else if (idx == 36  ) num = 0.96048*TMath::Erf((pt-5.23285)/11.06833)-0.00260;
      else if (idx == 37  ) num = 0.96868*TMath::Erf((pt-4.52244)/11.81532)+0.00478;
      else if (idx == 38  ) num = 0.96270*TMath::Erf((pt+0.70412)/16.49339)-0.00035;
      else if (idx == 39  ) num = 0.96504*TMath::Erf((pt-7.28395)/9.89952)-0.02064;
      else if (idx == 40  ) num = 0.96863*TMath::Erf((pt-6.78823)/10.54083)-0.00432;
      else if (idx == 41  ) num = 0.26740*TMath::Erf((pt+9.79865)/46.50262)+0.71568;
      else if (idx == 42  ) num = 0.95651*TMath::Erf((pt-2.88580)/14.44102)+0.00247;
      else if (idx == 43  ) num = 0.94412*TMath::Erf((pt+0.32721)/15.64570)-0.00664;
      else if (idx == 44  ) num = 0.17388*TMath::Erf((pt-13.32143)/10.89661)+0.79413;
      else if (idx == 45  ) num = 0.53075*TMath::Erf((pt+9.99175)/29.71717)+0.45044;
      else if (idx == 46  ) num = 0.27165*TMath::Erf((pt+8.49412)/28.17708)+0.67151;
      else if (idx == 47  ) num = 0.95441*TMath::Erf((pt+0.17470)/16.63332)+0.01145;
      else if (idx == 48  ) num = 0.94861*TMath::Erf((pt-2.43499)/12.95551)-0.00846;
      else if (idx == 49  ) num = 0.92191*TMath::Erf((pt+9.99924)/22.92814)+0.01148;
      else if (idx == 50  ) num = 0.46351*TMath::Erf((pt+9.84866)/30.39340)+0.51171;
      else if (idx == 51  ) num = 0.94489*TMath::Erf((pt+9.99999)/25.16575)+0.02956;
      else if (idx == 52  ) num = 1.96813*TMath::Erf((pt+9.99965)/20.62837)-0.99453;
      else if (idx == 53  ) num = 0.97772*TMath::Erf((pt-5.02873)/10.63483)-0.00828;
      else if (idx == 54  ) num = 0.37600*TMath::Erf((pt-5.24445)/14.46679)+0.58242;
      else if (idx == 55  ) num = 0.96651*TMath::Erf((pt-8.02646)/8.94717)-0.00290;
      else if (idx == 56  ) num = 0.96707*TMath::Erf((pt-5.00452)/11.52354)+0.00663;
      else if (idx == 57  ) num = 0.95713*TMath::Erf((pt-1.83669)/14.57463)+0.00743;
      else if (idx == 58  ) num = 0.95334*TMath::Erf((pt+2.86222)/19.65281)+0.01970;
      else if (idx == 59  ) num = 0.93412*TMath::Erf((pt+0.60691)/15.74695)+0.01282;
      else if (idx == 60  ) num = 0.96046*TMath::Erf((pt-6.93257)/10.41304)-0.02506;
      else if (idx == 61  ) num = 0.95011*TMath::Erf((pt+9.99998)/25.63359)+0.03391;
      else if (idx == 62  ) num = 0.97290*TMath::Erf((pt-4.84902)/12.68679)-0.00111;
      else if (idx == 63  ) num = 0.96739*TMath::Erf((pt-5.36917)/11.86538)+0.00072;
      else if (idx == 64  ) num = 0.61873*TMath::Erf((pt+9.83484)/28.71590)+0.36025;
      else if (idx == 65  ) num = 0.95173*TMath::Erf((pt+9.99994)/26.34242)+0.03449;
      else if (idx == 66  ) num = 0.95641*TMath::Erf((pt-1.59577)/16.08650)+0.00970;
      else if (idx == 67  ) num = 0.96462*TMath::Erf((pt-5.92618)/11.76891)+0.00068;
      else if (idx == 68  ) num = 1.13353*TMath::Erf((pt-1.01868)/14.56701)-0.19546;
      else if (idx == 69  ) num = 0.03405*TMath::Erf((pt-26.77121)/3.02153)+0.91035;
      else if (idx == 70  ) num = 0.96002*TMath::Erf((pt-2.44277)/16.40489)+0.01177;
      else if (idx == 71  ) num = 0.97216*TMath::Erf((pt-6.36140)/10.96999)-0.00720;
      else if (idx == 72  ) num = 2.50470*TMath::Erf((pt+8.85594)/17.34846)-1.56196;
      else if (idx == 73  ) num = 0.49741*TMath::Erf((pt+9.35427)/35.92619)+0.49696;
      else if (idx == 74  ) num = 0.98712*TMath::Erf((pt-7.64819)/9.49127)-0.03248;
      else if (idx == 75  ) num = 0.97020*TMath::Erf((pt-4.73910)/13.07035)+0.00443;
      else if (idx == 76  ) num = 0.96437*TMath::Erf((pt-3.25133)/14.42314)+0.00501;
      else if (idx == 77  ) num = 0.15171*TMath::Erf((pt+3.22769)/43.56760)+0.83115;
      else if (idx == 78  ) num = 0.93550*TMath::Erf((pt+10.00000)/18.53567)+0.03014;
      else if (idx == 79  ) num = 1.68491*TMath::Erf((pt-9.62903)/3.85157)-0.74276;
      else if (idx == 80  ) num = 0.96316*TMath::Erf((pt-4.83884)/12.82885)-0.00161;
      else if (idx == 81  ) num = 0.95342*TMath::Erf((pt-4.87752)/11.58552)-0.00385;
      else if (idx == 82  ) num = 0.18153*TMath::Erf((pt+5.76564)/31.77239)+0.78104;
      else if (idx == 83  ) num = 0.96170*TMath::Erf((pt-1.98085)/14.39623)+0.01172;
      else if (idx == 84  ) num = 0.90922*TMath::Erf((pt+10.00000)/8.15482)+0.01782;
      else if (idx == 85  ) num = 0.43481*TMath::Erf((pt+9.04862)/27.32006)+0.53345;
      else if (idx == 86  ) num = 0.94732*TMath::Erf((pt+9.99992)/26.35896)+0.03049;
      else if (idx == 87  ) num = 0.50616*TMath::Erf((pt+9.65962)/36.53277)+0.49232;
      else if (idx == 88  ) num = 0.54653*TMath::Erf((pt+9.78276)/32.80176)+0.43391;
      else if (idx == 89  ) num = 0.94229*TMath::Erf((pt+9.99999)/24.09454)+0.02935;
      else if (idx == 90  ) num = 0.42278*TMath::Erf((pt+9.17258)/31.68188)+0.54610;
      else if (idx == 91  ) num = 0.92029*TMath::Erf((pt+9.99968)/21.46950)+0.01199;
      else if (idx == 92  ) num = 1.02282*TMath::Erf((pt+9.99389)/25.48421)-0.04474;
      else if (idx == 93  ) num = 2.06104*TMath::Erf((pt+9.96442)/19.25260)-1.11117;
      else if (idx == 94  ) num = 0.65840*TMath::Erf((pt+9.99893)/32.71674)+0.32373;
      else if (idx == 95  ) num = 2.70763*TMath::Erf((pt+4.22677)/13.71222)-1.75509;
      else if (idx == 96  ) num = 0.93427*TMath::Erf((pt+9.99951)/24.16351)+0.02144;
      else if (idx == 97  ) num = 0.95038*TMath::Erf((pt+9.99998)/25.30352)+0.03446;
      else if (idx == 98  ) num = 0.94090*TMath::Erf((pt+3.99796)/18.51248)+0.00109;
      else if (idx == 99  ) num = 0.93067*TMath::Erf((pt+9.99933)/22.52115)+0.02018;
      else if (idx == 100 ) num = 0.94830*TMath::Erf((pt+9.99999)/24.47982)+0.03347;
   }

   return num / den;
}

#endif //#ifndef tnp_weight_h
