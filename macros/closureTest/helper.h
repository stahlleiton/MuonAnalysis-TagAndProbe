#ifndef helper_h
#define helper_h

#include "TGraphAsymmErrors.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "TAxis.h"

TGraphAsymmErrors *plotEff(RooDataSet *a, int aa, const char* varx){
  const RooArgSet *set = a->get();
  RooRealVar *xAx = (RooRealVar*)set->find(varx);
  RooRealVar *eff = (RooRealVar*)set->find("efficiency");

  const int nbins = xAx->getBinning().numBins();

  double tx[nbins], txhi[nbins], txlo[nbins];
  double ty[nbins], tyhi[nbins], tylo[nbins];

  for (int i=0; i<nbins; i++) {
    a->get(i);
    ty[i] = eff->getVal();
    tx[i] = xAx->getVal();
    txhi[i] = fabs(xAx->getErrorHi());
    txlo[i] = fabs(xAx->getErrorLo());
    tyhi[i] = fabs(eff->getErrorHi());
    tylo[i] = fabs(eff->getErrorLo());
  }

  cout<<"NBins : "<<nbins<<endl;

  const double *x = tx;
  const double *xhi = txhi;
  const double *xlo = txlo;
  const double *y = ty;
  const double *yhi = tyhi;
  const double *ylo = tylo;


  TGraphAsymmErrors *b = new TGraphAsymmErrors();
  if(aa == 1) {*b = TGraphAsymmErrors(nbins,x,y,xlo,xhi,ylo,yhi);}
  if(aa == 0) {*b = TGraphAsymmErrors(nbins,x,y,0,0,ylo,yhi);}

  b->SetMaximum(1.1);
  b->SetMinimum(0.0);
  b->SetMarkerStyle(20);
  b->SetMarkerColor(kRed+2);
  b->SetMarkerSize(1.0);
  b->SetTitle("");
  b->GetXaxis()->SetTitleSize(0.1);
  b->GetYaxis()->SetTitleSize(0.1);
  b->GetXaxis()->SetTitle("#eta");
  b->GetYaxis()->SetTitle("Efficiency");
  b->GetXaxis()->CenterTitle();

  for (int i=0; i<nbins; i++) {
    cout << x[i] << " " << y[i] << " " << yhi[i] << " " << ylo[i] << endl;
  }

  return b;

};

bool IsAccept(Double_t pt, Double_t eta)
{

     //return(1);
     //return (TMath::Abs(eta) < 2.4); 

   return (TMath::Abs(eta) < 2.4 &&
         (    ( TMath::Abs(eta) < 1.0 && pt >= 3.4 ) ||
              (  1.0 <= TMath::Abs(eta) && TMath::Abs(eta) < 1.5 && pt >= 5.8-2.4*TMath::Abs(eta) ) ||
              (  1.5 <= TMath::Abs(eta) && pt >= 3.3667 - 7.0/9.0*TMath::Abs(eta)) ));
};

double findCenWeight(const int Bin) {
  double NCollArray[40]={
    1747.8600, 1567.5300, 1388.3900, 1231.7700, 1098.2000, 980.4390, 861.6090, 766.0420, 676.5150, 593.4730,
    521.9120, 456.5420, 398.5460, 346.6470, 299.3050, 258.3440, 221.2160, 188.6770, 158.9860, 134.7000,
    112.5470, 93.4537, 77.9314, 63.5031, 52.0469, 42.3542, 33.9204, 27.3163, 21.8028, 17.2037,
    13.5881, 10.6538, 8.3555, 6.4089, 5.1334, 3.7322, 3.0663, 2.4193, 2.1190, 1.7695
  };
  return(NCollArray[Bin]);
};
#endif // #ifndef helper_h
