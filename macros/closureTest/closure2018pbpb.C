#include "TFile.h"
//#include "tnp_weight.h"
//#include "tnp_mc.h"
#include "helper.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
//#include "TRatioPlot.h"
#include "TCanvas.h"
//#include "TH1.h"
#include "TLegend.h"

float ptmin(float etamax) {
   float ans=0;
   if (etamax<1.2) ans = 3.5;
   else if (etamax<2.1) ans = 5.77-1.89*fabs(etamax);
   else ans = 1.8;
   // ans = (int) (ans*10.);
   // ans = ans/10.;
   return ans;
}

void closure2018pbpb(int centmin, int centmax, int trigIdx) {

  string trgTag = (trigIdx==0)?"L2Jpsi":(trigIdx==1)?"L3Jpsi":(trigIdx==2)?"L2Upsi":(trigIdx==3)?"L3Upsi":"DMOpen";

  TFile *f = new TFile(Form("histos_trd_pbpb_cent%d%d_%s.root",centmin, centmax, trgTag.c_str()));
   // Trg eff comparison: Trd vs Tnp (binned)
   TCanvas *c1 = new TCanvas();
   //TFile *ftnp_trg = new TFile("../../test/jpsiHI/Output/MuonID/tnp_Ana_MC_PbPb_MuonID_cbPlusPol1.root");
   RooDataSet *da_trg=NULL;

   TGraphAsymmErrors *gtrg=NULL;
   TH1D *hnum=NULL, *hden=NULL;
   TH1D *hnum2=NULL, *hden2=NULL;
   TGraphAsymmErrors *eff=new TGraphAsymmErrors();
   TGraphAsymmErrors *eff2=new TGraphAsymmErrors();
   TRatioPlot *tr = NULL;
   TLegend *tleg = new TLegend(0.6,0.2,0.9,0.5);
   tleg->SetBorderSize(0); tleg->SetFillColor(0);

   string caseTag [] = {"","trk", "trkID", "trkIDtrg"};
   string plotTag [] = {"tracking", "MuonID", "trigger"};
   double rapBins [] = {0, 1.2, 1.8, 2.1, 2.4};
   // Trg eff comparison: Trd vs Tnp (functions)
   for (int i=1; i<4; i++) {
       for (int j=0; j<4; j++) {
	 c1->cd(); c1->Clear();
	 /*if (i==2) {
	   da_trg = (RooDataSet*)ftnp_trg->Get(Form("tpTree/MuId_abseta%s/fit_eff",j==0?Form("00_%d",(int) (10*rapBins[j+1])):Form("%d_%d",(int) (10*rapBins[j]), (int) (10*rapBins[j+1]) )));
	   gtrg = plotEff(da_trg,1,"pt");
	   gtrg->SetLineColor(kRed);
	   gtrg->SetMarkerColor(kRed);
	   }*/
	 hnum = (TH1D*) f->Get(Form("hnum%s_%d_%d",caseTag[i].c_str(), (int) (10*rapBins[j]), (int) (10*rapBins[j+1])));
	 hden = (TH1D*) f->Get(Form("hnum%s_%d_%d",caseTag[i-1].c_str(), (int) (10*rapBins[j]), (int) (10*rapBins[j+1])));
	 //hden = (TH1D*) f->Get(Form("hden_%d_%d", (int) (10*rapBins[j]), (int) (10*rapBins[j+1])));
	 eff->Divide(hnum,hden,"pois");
	 eff->SetLineColor(kBlack);
	 eff->SetMarkerColor(kBlack);
	 eff->SetMarkerStyle(kFullSquare);

	 hnum2 = (TH1D*) f->Get(Form("hden_%swt_%d_%d",caseTag[i].c_str(), (int) (10*rapBins[j]), (int) (10*rapBins[j+1])));
	 hden2 = (TH1D*) f->Get((i==1)?Form("hden_%d_%d", (int) (10*rapBins[j]), (int) (10*rapBins[j+1])):Form("hden_%swt_%d_%d",caseTag[i-1].c_str(), (int) (10*rapBins[j]), (int) (10*rapBins[j+1])));
	 //hden2 = (TH1D*) f->Get(Form("hden_%d_%d", (int) (10*rapBins[j]), (int) (10*rapBins[j+1])));
	 eff2->Divide(hnum2,hden2,"pois");
	 eff2->SetLineColor(kMagenta);
	 eff2->SetMarkerColor(kMagenta);
	 if (i==1 && j==0) {
	   tleg->AddEntry(eff2,"Tag and probe (weights)","lp");
	   tleg->AddEntry(eff,"Traditional","lp");
	 }
	 tleg->SetHeader(Form("pbpb, %s, %f<|y|<%f",plotTag[i-1].c_str(),rapBins[j], rapBins[j+1]));
	 tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
	 setTRatioPlotStyle(tr);
	 c1->Update();
	 tr->GetUpperPad()->cd();
	 //if (i==2) gtrg->Draw("same");
	 tleg->Draw();
	 c1->SaveAs(Form("plots/pbpb_%s_%s_%d_%d_cent%d%d.pdf",trgTag.c_str(), plotTag[i-1].c_str(), (int) (10*rapBins[j]), (int) (10*rapBins[j+1]), centmin, centmax));
       }
   }

   
   // Full eff comparison: Trd vs Tnp (functions)
   for (int j=0; j<4; j++) {
     c1->cd(); c1->Clear();
     hnum = (TH1D*) f->Get(Form("hnum%s_%d_%d",caseTag[3].c_str(), (int) (10*rapBins[j]), (int) (10*rapBins[j+1])));
     //hden = (TH1D*) f->Get(Form("hnum%s_%d_%d",caseTag[0].c_str(), (int) (10*rapBins[j]), (int) (10*rapBins[j+1])));
     hden = (TH1D*) f->Get(Form("hden_%d_%d", (int) (10*rapBins[j]), (int) (10*rapBins[j+1])));
     eff->Divide(hnum,hden,"pois");
     eff->SetLineColor(kBlack);
     eff->SetMarkerColor(kBlack);
     eff->SetMarkerStyle(kFullSquare);
     hnum2 = (TH1D*) f->Get(Form("hden_%swt_%d_%d",caseTag[3].c_str(), (int) (10*rapBins[j]), (int) (10*rapBins[j+1])));
     //hden2 = (TH1D*) f->Get(Form("hden_%d_%d", (int) (10*rapBins[j]), (int) (10*rapBins[j+1])));
     hden2 = (TH1D*) f->Get(Form("hden_%d_%d", (int) (10*rapBins[j]), (int) (10*rapBins[j+1])));
     eff2->Divide(hnum2,hden2,"pois");
     eff2->SetLineColor(kMagenta);
     eff2->SetMarkerColor(kMagenta);
     tleg->SetHeader(Form("pbpb, %s, %f<|y|<%f",plotTag[0].c_str(),rapBins[j], rapBins[j+1]));
     tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
     setTRatioPlotStyle(tr);
     c1->Update();
     tr->GetUpperPad()->cd();
     tleg->Draw();
     c1->SaveAs(Form("plots/pbpb_%s_full_%d_%d_cetn%d%d_usingDen.pdf", trgTag.c_str(), (int) (10*rapBins[j]), (int) (10*rapBins[j+1]), centmin, centmax));
   }
}
