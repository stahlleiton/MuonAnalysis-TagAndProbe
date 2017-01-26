#include "TFile.h"
#include "tnp_weight.h"
#include "tnp_mc.h"
#include "helper.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TRatioPlot.h"

Double_t tnp_mc_trg_pbpb_wrapper(Double_t *x, Double_t *par) {
   return tnp_mc_trg_pbpb(x[0],par[0]);
}
Double_t tnp_mc_trg_pp_wrapper(Double_t *x, Double_t *par) {
   return tnp_mc_trg_pp(x[0],par[0]);
}
Double_t tnp_mc_muid_pbpb_wrapper(Double_t *x, Double_t *par) {
   return tnp_mc_muid_pbpb(x[0],par[0]);
}
Double_t tnp_mc_muid_pp_wrapper(Double_t *x, Double_t *par) {
   return tnp_mc_muid_pp(x[0],par[0]);
}
Double_t tnp_mc_sta_pp_wrapper(Double_t *x, Double_t *par) {
   return tnp_mc_sta_pp(x[0],par[0]);
}
Double_t tnp_mc_full_pbpb_wrapper(Double_t *x, Double_t *par) {
   return tnp_mc_sta_pp(x[0],par[0])
      * tnp_mc_muid_pbpb(x[0],par[0])
      * tnp_mc_trg_pbpb(x[0],par[0]);
}
Double_t tnp_mc_full_pp_wrapper(Double_t *x, Double_t *par) {
   return tnp_mc_sta_pp(x[0],par[0])
      * tnp_mc_muid_pp(x[0],par[0])
      * tnp_mc_trg_pp(x[0],par[0]);
}

float ptmin(float etamax) {
   float ans=0;
   if (etamax<1.2) ans = 3.5;
   else if (etamax<2.1) ans = 5.77-1.89*fabs(etamax);
   else ans = 1.8;
   // ans = (int) (ans*10.);
   // ans = ans/10.;
   return ans;
}

void closure2016pbpb() {
   TFile *f = new TFile("histos_trd_pbpb_cent120200.root");

   TH1D *haxes20 = new TH1D("haxes20","haxes20",1,0,20);
   TH1D *haxes30 = new TH1D("haxes30","haxes30",1,0,30);
   haxes20->GetYaxis()->SetRangeUser(0,1.1);
   haxes30->GetYaxis()->SetRangeUser(0,1.1);
   haxes20->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   haxes30->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   haxes20->GetYaxis()->SetTitle("Efficiency");
   haxes30->GetYaxis()->SetTitle("Efficiency");

   // Trg eff comparison: Trd vs Tnp (binned)
   TCanvas *c1 = new TCanvas();
   TFile *ftnp_trg = new TFile("tnpfiles/tnp_Ana_MC_PbPb_Trg_AllMB.root");
   RooDataSet *da_trg=NULL;
   TGraphAsymmErrors *gtrg=NULL;
   TH1D *hnum=NULL, *hden=NULL;
   TH1D *hnum2=NULL, *hden2=NULL;
   TGraphAsymmErrors *eff=new TGraphAsymmErrors();
   TGraphAsymmErrors *eff2=new TGraphAsymmErrors();
   TRatioPlot *tr = NULL;
   TLegend *tleg = new TLegend(0.6,0.2,0.9,0.5);
   tleg->SetBorderSize(0); tleg->SetFillColor(0);

   // 0<|y|<1.2
   c1->cd(); c1->Clear();
   da_trg = (RooDataSet*)ftnp_trg->Get("tpTree/MuIdTrg_abseta00_12/fit_eff");
   gtrg = plotEff(da_trg,1,"pt");
   gtrg->SetLineColor(kRed);
   gtrg->SetMarkerColor(kRed);
   hnum = (TH1D*) f->Get("hnumglbIDtrg_00_12");
   hden = (TH1D*) f->Get("hnumglbID_00_12");
   eff->Divide(hnum,hden,"pois");
   eff->SetLineColor(kBlack);
   eff->SetMarkerColor(kBlack);
   tleg->AddEntry(gtrg,"Tag and probe","lp");
   tleg->AddEntry(eff,"Traditional","lp");
   tleg->SetHeader("pbpb, trigger, 0<|y|<1.2");
   tr = new TRatioPlot(g2h(eff,20),g2h(gtrg,2));
   tr->Draw();
   setTRatioPlotStyle(tr);
   c1->Update();
   tr->GetUpperPad()->cd();
   tleg->Draw();
   c1->SaveAs("pbpb_trg_binned_00_12.pdf");

   // 1.2<|y|<1.8
   c1->cd(); c1->Clear();
   da_trg = (RooDataSet*)ftnp_trg->Get("tpTree/MuIdTrg_abseta12_18/fit_eff");
   gtrg = plotEff(da_trg,1,"pt");
   gtrg->SetLineColor(kRed);
   gtrg->SetMarkerColor(kRed);
   hnum = (TH1D*) f->Get("hnumglbIDtrg_12_18");
   hden = (TH1D*) f->Get("hnumglbID_12_18");
   eff->Divide(hnum,hden,"pois");
   eff->SetLineColor(kBlack);
   eff->SetMarkerColor(kBlack);
   eff->SetMarkerStyle(kFullSquare);
   tleg->SetHeader("pbpb, trigger, 1.2<|y|<1.8");
   tr = new TRatioPlot(g2h(eff,20),g2h(gtrg,2));
   setTRatioPlotStyle(tr);
   c1->Update();
   tr->GetUpperPad()->cd();
   tleg->Draw();
   c1->SaveAs("pbpb_trg_binned_12_18.pdf");

   // 1.8<|y|<2.1
   c1->cd(); c1->Clear();
   da_trg = (RooDataSet*)ftnp_trg->Get("tpTree/MuIdTrg_abseta18_21/fit_eff");
   gtrg = plotEff(da_trg,1,"pt");
   gtrg->SetLineColor(kRed);
   gtrg->SetMarkerColor(kRed);
   hnum = (TH1D*) f->Get("hnumglbIDtrg_18_21");
   hden = (TH1D*) f->Get("hnumglbID_18_21");
   eff->Divide(hnum,hden,"pois");
   eff->SetLineColor(kBlack);
   eff->SetMarkerColor(kBlack);
   eff->SetMarkerStyle(kFullSquare);
   tleg->SetHeader("pbpb, trigger, 1.8<|y|<2.1");
   tr = new TRatioPlot(g2h(eff,20),g2h(gtrg,2));
   setTRatioPlotStyle(tr);
   c1->Update();
   tr->GetUpperPad()->cd();
   tleg->Draw();
   c1->SaveAs("pbpb_trg_binned_18_21.pdf");

   // 2.1<|y|<2.4
   c1->cd(); c1->Clear();
   da_trg = (RooDataSet*)ftnp_trg->Get("tpTree/MuIdTrg_abseta21_24/fit_eff");
   gtrg = plotEff(da_trg,1,"pt");
   gtrg->SetLineColor(kRed);
   gtrg->SetMarkerColor(kRed);
   hnum = (TH1D*) f->Get("hnumglbIDtrg_21_24");
   hden = (TH1D*) f->Get("hnumglbID_21_24");
   eff->Divide(hnum,hden,"pois");
   eff->SetLineColor(kBlack);
   eff->SetMarkerColor(kBlack);
   eff->SetMarkerStyle(kFullSquare);
   tleg->SetHeader("pbpb, trigger, 2.1<|y|<2.4");
   tr = new TRatioPlot(g2h(eff,20),g2h(gtrg,2));
   setTRatioPlotStyle(tr);
   c1->Update();
   tr->GetUpperPad()->cd();
   tleg->Draw();
   c1->SaveAs("pbpb_trg_binned_21_24.pdf");

   // Trg eff comparison: Trd vs Tnp (functions)
   // 0<|y|<1.2
   c1->cd(); c1->Clear();
   double y=1.2-1e-4; double ptminval = ptmin(y);
   TF1 *fpbpb_trg = new TF1("fpbpb_trg_00_12",tnp_mc_trg_pbpb_wrapper,ptminval,30,1);
   fpbpb_trg->SetLineColor(kRed);
   fpbpb_trg->SetParameter(0,y);
   hnum = (TH1D*) f->Get("hnumglbIDtrg_00_12");
   hden = (TH1D*) f->Get("hnumglbID_00_12");
   eff->Divide(hnum,hden,"pois");
   eff->SetLineColor(kBlack);
   eff->SetMarkerColor(kBlack);
   eff->SetMarkerStyle(kFullSquare);
   hnum2 = (TH1D*) f->Get("hden_staIDtrgwt_00_12");
   hden2 = (TH1D*) f->Get("hden_staIDwt_00_12");
   eff2->Divide(hnum2,hden2,"pois");
   eff2->SetLineColor(kMagenta);
   eff2->SetMarkerColor(kMagenta);
   tleg->AddEntry(eff2,"Tag and probe (weights)","lp");
   tleg->SetHeader("pbpb, trigger (fitted), 0<|y|<1.2");
   tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
   setTRatioPlotStyle(tr);
   c1->Update();
   tr->GetUpperPad()->cd();
   fpbpb_trg->Draw("same");
   tleg->Draw();
   c1->SaveAs("pbpb_trg_00_12.pdf");

   // 1.2<|y|<1.8
   c1->cd(); c1->Clear();
   y=1.8-1e-4; ptminval = ptmin(y);
   fpbpb_trg = new TF1("fpbpb_trg_12_18",tnp_mc_trg_pbpb_wrapper,ptminval,30,1);
   fpbpb_trg->SetLineColor(kRed);
   fpbpb_trg->SetParameter(0,y);
   hnum = (TH1D*) f->Get("hnumglbIDtrg_12_18");
   hden = (TH1D*) f->Get("hnumglbID_12_18");
   eff->Divide(hnum,hden,"pois");
   eff->SetLineColor(kBlack);
   eff->SetMarkerColor(kBlack);
   eff->SetMarkerStyle(kFullSquare);
   hnum2 = (TH1D*) f->Get("hden_staIDtrgwt_12_18");
   hden2 = (TH1D*) f->Get("hden_staIDwt_12_18");
   eff2->Divide(hnum2,hden2,"pois");
   eff2->SetLineColor(kMagenta);
   eff2->SetMarkerColor(kMagenta);
   tleg->SetHeader("pbpb, trigger (fitted), 1.2<|y|<1.8");
   tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
   setTRatioPlotStyle(tr);
   c1->Update();
   tr->GetUpperPad()->cd();
   fpbpb_trg->Draw("same");
   tleg->Draw();
   c1->SaveAs("pbpb_trg_12_18.pdf");

   // 1.8<|y|<2.1
   c1->cd(); c1->Clear();
   y=2.1-1e-4; ptminval = ptmin(y);
   fpbpb_trg = new TF1("fpbpb_trg_18_21",tnp_mc_trg_pbpb_wrapper,ptminval,20,1);
   fpbpb_trg->SetLineColor(kRed);
   fpbpb_trg->SetParameter(0,y);
   hnum = (TH1D*) f->Get("hnumglbIDtrg_18_21");
   hden = (TH1D*) f->Get("hnumglbID_18_21");
   eff->Divide(hnum,hden,"pois");
   eff->SetLineColor(kBlack);
   eff->SetMarkerColor(kBlack);
   eff->SetMarkerStyle(kFullSquare);
   hnum2 = (TH1D*) f->Get("hden_staIDtrgwt_18_21");
   hden2 = (TH1D*) f->Get("hden_staIDwt_18_21");
   eff2->Divide(hnum2,hden2,"pois");
   eff2->SetLineColor(kMagenta);
   eff2->SetMarkerColor(kMagenta);
   tleg->SetHeader("pbpb, trigger (fitted), 1.8<|y|<2.1");
   tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
   setTRatioPlotStyle(tr);
   c1->Update();
   tr->GetUpperPad()->cd();
   fpbpb_trg->Draw("same");
   tleg->Draw();
   c1->SaveAs("pbpb_trg_18_21.pdf");

   // 2.1<|y|<2.4
   c1->cd(); c1->Clear();
   y=2.4-1e-4; ptminval = ptmin(y);
   fpbpb_trg = new TF1("fpbpb_trg_21_24",tnp_mc_trg_pbpb_wrapper,ptminval,20,1);
   fpbpb_trg->SetLineColor(kRed);
   fpbpb_trg->SetParameter(0,y);
   hnum = (TH1D*) f->Get("hnumglbIDtrg_21_24");
   hden = (TH1D*) f->Get("hnumglbID_21_24");
   eff->Divide(hnum,hden,"pois");
   eff->SetLineColor(kBlack);
   eff->SetMarkerColor(kBlack);
   eff->SetMarkerStyle(kFullSquare);
   hnum2 = (TH1D*) f->Get("hden_staIDtrgwt_21_24");
   hden2 = (TH1D*) f->Get("hden_staIDwt_21_24");
   eff2->Divide(hnum2,hden2,"pois");
   eff2->SetLineColor(kMagenta);
   eff2->SetMarkerColor(kMagenta);
   tleg->SetHeader("pbpb, trigger (fitted), 2.1<|y|<2.4");
   tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
   setTRatioPlotStyle(tr);
   c1->Update();
   tr->GetUpperPad()->cd();
   fpbpb_trg->Draw("same");
   tleg->Draw();
   c1->SaveAs("pbpb_trg_21_24.pdf");


   // Full eff comparison: Trd vs Tnp (functions)
   // 0<|y|<1.2
   c1->cd(); c1->Clear();
   y=1.2-1e-4; ptminval = ptmin(y);
   TF1 *fpbpb_full = new TF1("fpbpb_full_00_12",tnp_mc_full_pbpb_wrapper,ptminval,30,1);
   fpbpb_full->SetLineColor(kRed);
   fpbpb_full->SetParameter(0,y);
   hnum = (TH1D*) f->Get("hnumglbIDtrg_00_12");
   hden = (TH1D*) f->Get("hden_00_12");
   eff->Divide(hnum,hden,"pois");
   eff->SetLineColor(kBlack);
   eff->SetMarkerColor(kBlack);
   eff->SetMarkerStyle(kFullSquare);
   hnum2 = (TH1D*) f->Get("hden_staIDtrgwt_00_12");
   hden2 = (TH1D*) f->Get("hden_00_12");
   eff2->Divide(hnum2,hden2,"pois");
   eff2->SetLineColor(kMagenta);
   eff2->SetMarkerColor(kMagenta);
   tleg->SetHeader("pbpb, full eff, 0<|y|<1.2");
   tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
   setTRatioPlotStyle(tr);
   c1->Update();
   tr->GetUpperPad()->cd();
   fpbpb_full->Draw("same");
   tleg->Draw();
   c1->SaveAs("pbpb_full_00_12.pdf");

   // 1.2<|y|<1.8
   c1->cd(); c1->Clear();
   y=1.8-1e-4; ptminval = ptmin(y);
   fpbpb_full = new TF1("fpbpb_full_12_18",tnp_mc_full_pbpb_wrapper,ptminval,30,1);
   fpbpb_full->SetLineColor(kRed);
   fpbpb_full->SetParameter(0,y);
   hnum = (TH1D*) f->Get("hnumglbIDtrg_12_18");
   hden = (TH1D*) f->Get("hden_12_18");
   eff->Divide(hnum,hden,"pois");
   eff->SetLineColor(kBlack);
   eff->SetMarkerColor(kBlack);
   eff->SetMarkerStyle(kFullSquare);
   hnum2 = (TH1D*) f->Get("hden_staIDtrgwt_12_18");
   hden2 = (TH1D*) f->Get("hden_12_18");
   eff2->Divide(hnum2,hden2,"pois");
   eff2->SetLineColor(kMagenta);
   eff2->SetMarkerColor(kMagenta);
   tleg->SetHeader("pbpb, full eff, 1.2<|y|<1.8");
   tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
   setTRatioPlotStyle(tr);
   c1->Update();
   tr->GetUpperPad()->cd();
   fpbpb_full->Draw("same");
   tleg->Draw();
   c1->SaveAs("pbpb_full_12_18.pdf");

   // 1.8<|y|<2.1
   c1->cd(); c1->Clear();
   y=2.1-1e-4; ptminval = ptmin(y);
   fpbpb_full = new TF1("fpbpb_full_18_21",tnp_mc_full_pbpb_wrapper,ptminval,20,1);
   fpbpb_full->SetLineColor(kRed);
   fpbpb_full->SetParameter(0,y);
   hnum = (TH1D*) f->Get("hnumglbIDtrg_18_21");
   hden = (TH1D*) f->Get("hden_18_21");
   eff->Divide(hnum,hden,"pois");
   eff->SetLineColor(kBlack);
   eff->SetMarkerColor(kBlack);
   eff->SetMarkerStyle(kFullSquare);
   hnum2 = (TH1D*) f->Get("hden_staIDtrgwt_18_21");
   hden2 = (TH1D*) f->Get("hden_18_21");
   eff2->Divide(hnum2,hden2,"pois");
   eff2->SetLineColor(kMagenta);
   eff2->SetMarkerColor(kMagenta);
   tleg->SetHeader("pbpb, full eff, 1.8<|y|<2.1");
   tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
   setTRatioPlotStyle(tr);
   c1->Update();
   tr->GetUpperPad()->cd();
   fpbpb_full->Draw("same");
   tleg->Draw();
   c1->SaveAs("pbpb_full_18_21.pdf");

   // 2.1<|y|<2.4
   c1->cd(); c1->Clear();
   y=2.4-1e-4; ptminval = ptmin(y);
   fpbpb_full = new TF1("fpbpb_full_21_24",tnp_mc_full_pbpb_wrapper,ptminval,20,1);
   fpbpb_full->SetLineColor(kRed);
   fpbpb_full->SetParameter(0,y);
   hnum = (TH1D*) f->Get("hnumglbIDtrg_21_24");
   hden = (TH1D*) f->Get("hden_21_24");
   eff->Divide(hnum,hden,"pois");
   eff->SetLineColor(kBlack);
   eff->SetMarkerColor(kBlack);
   hnum2 = (TH1D*) f->Get("hden_staIDtrgwt_21_24");
   hden2 = (TH1D*) f->Get("hden_21_24");
   eff2->Divide(hnum2,hden2,"pois");
   eff2->SetLineColor(kMagenta);
   eff2->SetMarkerColor(kMagenta);
   tleg->SetHeader("pbpb, full eff, 2.1<|y|<2.4");
   tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
   setTRatioPlotStyle(tr);
   c1->Update();
   tr->GetUpperPad()->cd();
   fpbpb_full->Draw("same");
   tleg->Draw();
   c1->SaveAs("pbpb_full_21_24.pdf");
}
