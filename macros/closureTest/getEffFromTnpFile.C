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
  TFile *ftnp_RD = new TFile("../../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_L3Filter_cbPlusPol1_0_v3.root");
  TFile *ftnp_MC = new TFile("../../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_L3Filter_cbPlusPol1_0_v3.root");
  RooDataSet *ds_RD=NULL;  RooDataSet *ds_MC=NULL;
  TGraphAsymmErrors *gRD=NULL;  TGraphAsymmErrors *gMC=NULL; TGraphAsymmErrors* pull=NULL;
  TCanvas* c = new TCanvas(); 
  TRatioPlot *tr = NULL;

  TLegend* leg = new TLegend(0.4,0.6,0.7,0.8);
  leg->SetBorderSize(0); leg->SetFillColor(0);


  std::vector<string> plots = {"Trg_glbChi2", "Trg_glbTrackProb", "Trg_glbValidMuHits", "Trg_l3pt", "Trg_l3dr", "Trg_numberOfMatchedStations", "Trg_numberOfMatches", "Trg_eta", "Trg_phi", "Trg_tagPt"};
  std::vector<string> vars = {"glbChi2", "glbTrackProb", "glbValidMuHits", "l3pt", "l3dr", "numberOfMatchedStations", "numberOfMatches", "eta", "phi", "tag_pt"};

  for (uint i=0; i<plots.size(); i++) {
    c->cd(); c->Clear();
    ds_RD = (RooDataSet*) ftnp_RD->Get(Form("tpTree/%s/fit_eff",plots[i].c_str()));
    ds_MC = (RooDataSet*) ftnp_MC->Get(Form("tpTree/%s/fit_eff",plots[i].c_str()));
    if (!ds_RD || !ds_MC) continue;
    gRD = plotEff(ds_RD,1,vars[i].c_str());
    gMC = plotEff(ds_MC,1,vars[i].c_str());
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

    tr = new TRatioPlot(g2h(gRD,vars[i]),g2h(gMC,vars[i]));
    setTRatioPlotStyle(tr);
    tr->GetLowerRefYaxis()->SetRangeUser(0.69,1.41);
    tr->GetLowerRefYaxis()->SetTitle("trd / tnp");
    c->Update();
    tr->GetUpperPad()->cd();
    leg->Draw();
    c->SaveAs(Form("plots/%s.pdf",plots[i].c_str()));
  }

}

