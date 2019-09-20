#include "TFile.h"
#include "helper.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TRatioPlot.h"
#include "TCanvas.h"
#include "TLegend.h"


void getStaMCEff() {

  TFile *ftnp_trg = new TFile("../../test/jpsiHI/Output/Sta/tnp_Ana_MC_PbPb_STA_twoGausPlusPol1_2.root");
  RooDataSet *da_trg=NULL;
  TGraphAsymmErrors *gtrg=NULL;
  
  da_trg = (RooDataSet*)ftnp_trg->Get("tpTreeTrk/STA_abseta00_12/fit_eff");
  gtrg = plotEff(da_trg,1,"pt");

  da_trg = (RooDataSet*)ftnp_trg->Get("tpTreeTrk/STA_abseta12_21/fit_eff");
  gtrg = plotEff(da_trg,1,"pt");

  da_trg = (RooDataSet*)ftnp_trg->Get("tpTreeTrk/STA_abseta21_24/fit_eff");
  gtrg = plotEff(da_trg,1,"pt");
}

void getTrig_ptcentBin() {
  TFile *ftnp_RD = new TFile("../../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L3Jpsi_cbPlusPol1_8.root");
  TFile *ftnp_MC = new TFile("../../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L3Jpsi_cbPlusPol1_8.root");
  RooDataSet *ds_RD=NULL;  RooDataSet *ds_MC=NULL;
  TGraphAsymmErrors *gRD=NULL;  TGraphAsymmErrors *gMC=NULL; TGraphAsymmErrors* pull=NULL;
  TCanvas* c = new TCanvas(); 
  TRatioPlot *tr = NULL;

  TLegend* leg = new TLegend(0.6,0.2,0.9,0.5);
  leg->SetBorderSize(0); leg->SetFillColor(0);


  string plots [] = {"Trg_cent020","Trg_cent2060","Trg_cent60200", "Trg_eta012_cent020", "Trg_eta012_cent2060", "Trg_eta012_cent60200"};
  int nPlots = 6;
  //string plots [] = {"Trg_pt", "Trg_abseta00_12", "Trg_abseta12_18", "Trg_abseta18_21", "Trg_abseta21_24"};
  //int nPlots = 5;

  for (int i=0; i<nPlots; i++) {
    c->cd(); c->Clear();
    ds_RD = (RooDataSet*) ftnp_RD->Get(Form("tpTree/%s/fit_eff",plots[i].c_str()));
    ds_MC = (RooDataSet*) ftnp_MC->Get(Form("tpTree/%s/fit_eff",plots[i].c_str()));
    gRD = plotEff(ds_RD,1,"pt");
    gMC = plotEff(ds_MC,1,"pt");
    gRD->SetLineColor(kBlue);
    gRD->SetMarkerColor(kBlue);
    gRD->SetMarkerStyle(kOpenSquare);
    gMC->SetLineColor(kRed);
    gMC->SetMarkerColor(kRed);
    gMC->SetMarkerStyle(kFullCircle);
    if (i==0){
      leg->AddEntry(gRD,"Data","lp");
      leg->AddEntry(gMC,"MC","lp");
    }
    leg->SetHeader(Form("pbpb, trigger, %s",plots[i].c_str()));

    tr = new TRatioPlot(g2h(gRD,1),g2h(gMC,1));
    setTRatioPlotStyle(tr);
    tr->GetLowerRefYaxis()->SetRangeUser(0.79,1.21);
    tr->GetLowerRefYaxis()->SetTitle("trd / tnp");
    c->Update();
    tr->GetUpperPad()->cd();
    leg->Draw();
    c->SaveAs(Form("plots/%s.pdf",plots[i].c_str()));
  }

}

