#include "ClosureTestPbPb.C"
#include "helper.h"
#include "tnp_weight.h"

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "RooDataSet.h"
#include "TFile.h"
#include "TLegend.h"
#include "TAxis.h"
#include <vector>
#include <map>
#include "TLorentzVector.h"
#include "TChain.h"
#include "TLatex.h"

int macro(int ieta=0, int dphimode=0, int tagmode=0) {
   // ieta: 0 = <1.6, 1 = >1.6
   // dphimode: 0: all, 1: only cowboys, -1: only sailors

   int nfiles = 1;
   string filelist[1] = {
      "root://eoscms//eos/cms/store/user/miheejo/TREE/2013pp/PRMC_Histos_2013pp_GlbGlb_STARTHI53_V28-v1_GenCtau_muLessPV_noCuts.root",
   };

   TChain *chain = new TChain("myTree");
   for (int i=0; i<nfiles; i++) {
      chain->Add(filelist[i].c_str());
   }

   ClosureTestPbPb objreco(chain);

   int nbins = ieta==0 ? 10 : 8;
   double pts[11] = {2.1,2.5,3,3.5, 4,4.5, 5,6, 7,10, 30};
   // double pts_fwd[11] = {3.5,4,5,6,7,8,10,13,15,20,30}; 
   double pts_fwd[9] = {1.5,2,2.5,3,3.5,4, 5,8, 30};
   if (ieta==1) for (int i=0; i<nbins+1; i++) pts[i] = pts_fwd[i];

   // int nbins = 50;
   // double pts[51] = {2,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,
   // 3,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,
   // 4,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,
   // 5,5.1,5.2,5.3,5.4,5.5,5.6,5.7,5.8,5.9,
   // 6,6.5,7,7.5,8,8.5,9,9.5,10,15,30};


   double etamin=0, etamax=1.6;
   if (ieta==1) {etamin=1.6; etamax=2.4;}
   double *eff = objreco.Loop(nbins, pts, etamin, etamax, dphimode, tagmode);

   TFile *ftnp_muidtrg = new TFile("../tnpfiles/pp_MuIdTrg.root");
   TFile *ftnp_sta = new TFile("../tnpfiles/pp_STA.root");
   TFile *ftnp_trk = new TFile("../tnpfiles/pp_trk_2bins.root");

   RooDataSet *da_muidtrg = ieta==0 ? (RooDataSet*)ftnp_muidtrg->Get("MuonIDTrg/PassingGlb_pt1/fit_eff") : (RooDataSet*)ftnp_muidtrg->Get("MuonIDTrg/PassingGlb_pt3/fit_eff");
   RooDataSet *da_sta = ieta==0 ? (RooDataSet*)ftnp_sta->Get("tpTree/PassingSTA_pt1/fit_eff") : (RooDataSet*)ftnp_sta->Get("tpTree/PassingSTA_pt2/fit_eff");
   RooDataSet *da_trk = (RooDataSet*)ftnp_trk->Get("MuonTrk/PassingGlb_absetaSeg/fit_eff");

   TGraphAsymmErrors *gmuidtrg = plotEff(da_muidtrg,0,"pt");
   TGraphAsymmErrors *gsta = plotEff(da_sta,0,"pt");
   TGraphAsymmErrors *gtrk = plotEff(da_trk,0,"pt");

   if (nbins != gmuidtrg->GetN() || nbins != gsta->GetN() || gtrk->GetN() != 1) return 0;

   double *xtnp = gmuidtrg->GetX();
   double *extnp = new double[nbins];
   double *ytnp = new double[nbins];
   double *eyhtnp = new double[nbins];
   double *eyltnp = new double[nbins];
   for (int i=0; i<nbins; i++) {
      extnp[i] = 0;
      ytnp[i] = gmuidtrg->GetY()[i]
         *gsta->GetY()[i]
         *gtrk->GetY()[0]; 

      // TNP UNCERTAINTIES
      // a) uncertainty from the mass fit (MC statistics)
      eyhtnp[i] = sqrt(pow(gmuidtrg->GetEYhigh()[i]/gmuidtrg->GetY()[i],2)
            +pow(gsta->GetEYhigh()[i]/gsta->GetY()[i],2)
            +pow(gtrk->GetEYhigh()[0]/gtrk->GetY()[0],2)) * ytnp[i];
      eyltnp[i] = sqrt(pow(gmuidtrg->GetEYlow()[i]/gmuidtrg->GetY()[i],2)
            +pow(gsta->GetEYlow()[i]/gsta->GetY()[i],2)
            +pow(gtrk->GetEYlow()[0]/gtrk->GetY()[0],2)) * ytnp[i];
      // b) uncertainty from MuId+trg (from data; quoted on the final result)
      double eta = (etamin+etamax)/2.;
      double uncert_muidtrg = ytnp[i]*(1.-tnp_weight_muidtrg_pp(xtnp[i],eta,-1)/tnp_weight_muidtrg_pp(xtnp[i],eta,0));
      // c) uncertainty from STA (= full STA correction; quoted on the final result
      double uncert_sta = ytnp[i]*(1.-tnp_weight_sta_pp(xtnp[i],eta,0));
      // d) total uncertainty
      eyhtnp[i] = sqrt(pow(eyhtnp[i],2)+pow(uncert_muidtrg,2)+pow(uncert_sta,2));
      eyltnp[i] = sqrt(pow(eyltnp[i],2)+pow(uncert_muidtrg,2)+pow(uncert_sta,2));
   }
   TGraphAsymmErrors *gtnp = new TGraphAsymmErrors(nbins,xtnp,ytnp,extnp,extnp,eyltnp,eyhtnp);
   gtnp->SetMarkerColor(kRed);
   gtnp->SetLineColor(kRed);
   gtnp->SetMarkerStyle(20);

   // double *xtnp = new double[nbins];
   double *ytrd = new double[nbins];
   double *eytrd = new double[nbins];
   for (int i=0; i<nbins; i++) {
      // xtnp[i] = (pts[i]+pts[i+1])/2.;
      ytrd[i] = eff[i];
      eytrd[i] = 0;
   }

   TGraphErrors *gtrd = new TGraphErrors(nbins,xtnp,ytrd,extnp,eytrd);
   gtrd->SetMarkerColor(kBlack);
   gtrd->SetLineColor(kBlack);
   gtrd->SetMarkerStyle(21);

   // ratio trd / tnp
   double *yratio = new double[nbins];
   double *eylratio = new double[nbins];
   double *eyhratio = new double[nbins];

   for (int i=0; i<nbins; i++) {
      yratio[i] = ytrd[i] / ytnp[i];
      if (ytrd[i]<ytnp[i]) {
         eylratio[i] = sqrt(pow(eytrd[i]/ytrd[i],2) + pow(eyltnp[i]/ytnp[i],2)) * yratio[i];
         eyhratio[i] = sqrt(pow(eytrd[i]/ytrd[i],2) + pow(eyhtnp[i]/ytnp[i],2)) * yratio[i];
      }
      else {
         eyhratio[i] = sqrt(pow(eytrd[i]/ytrd[i],2) + pow(eyltnp[i]/ytnp[i],2)) * yratio[i];
         eylratio[i] = sqrt(pow(eytrd[i]/ytrd[i],2) + pow(eyhtnp[i]/ytnp[i],2)) * yratio[i];
      }
   }
   TGraphAsymmErrors *gratio = new TGraphAsymmErrors(nbins,xtnp,yratio,extnp,extnp,eylratio,eyhratio);

   TH1F *haxis = new TH1F("haxis","haxis",1,0,pts[nbins]);
   haxis->GetXaxis()->SetTitle("p_{T}");
   haxis->GetYaxis()->SetTitle("Efficiency");
   haxis->GetYaxis()->SetRangeUser(0,1);
   haxis->GetXaxis()->SetLabelSize(0.);
   haxis->GetXaxis()->SetTitleSize(0.);
   haxis->GetXaxis()->SetTitleOffset(1.2);
   haxis->GetYaxis()->SetLabelSize(0.05);
   haxis->GetYaxis()->SetTitleSize(0.05);
   haxis->GetYaxis()->SetTitleOffset(1.);
   TH1F *haxis2 = new TH1F("haxis2","haxis2",1,0,pts[nbins]);
   haxis2->GetXaxis()->SetTitle("p_{T}");
   haxis2->GetYaxis()->SetTitle("Efficiency");
   haxis2->GetYaxis()->SetRangeUser(0.88,1.52);
   haxis2->GetYaxis()->SetTitle("Scale Factor");
   double tsize = (1./0.36)*haxis->GetYaxis()->GetTitleSize(); // 1./0.36
   haxis2->GetXaxis()->SetTitleSize(tsize);
   haxis2->GetXaxis()->SetLabelSize(tsize);
   haxis2->GetYaxis()->SetTitleSize(tsize);
   haxis2->GetYaxis()->SetLabelSize(tsize);
   haxis2->GetYaxis()->SetNdivisions(504,kTRUE);

   TCanvas *c1 = new TCanvas("c1","",700,600);
   c1->cd();
   TPad *pad1 = new TPad("pad1","pad1",0, 0.26 ,1,1);
   c1->cd();
   TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3*0.96);
   pad1->SetBottomMargin(0.04);
   pad2->SetTopMargin(0);
   pad2->SetFillColor(0);
   pad2->SetFillStyle(0);
   pad2->SetBottomMargin(gStyle->GetPadBottomMargin()/0.3);
   pad1->SetTopMargin(gStyle->GetPadTopMargin()/0.7);
   // pad2->SetGridy();
   pad1->Draw();
   pad1->cd();


   haxis->Draw();
   gtrd->Draw("P");
   gtnp->Draw("P");

   TLegend *tleg = new TLegend(0.4,0.07,1.,0.37);
   tleg->SetFillStyle(0);
   tleg->SetFillColor(0);
   tleg->SetBorderSize(0);
   tleg->SetTextSize(0.07);
   tleg->SetHeader(Form("Muon eff., |#eta^{#mu}| #in [%.1f, %.1f]",etamin,etamax));
   tleg->AddEntry(gtrd,"Trd way","P");
   tleg->AddEntry(gtnp,"T&P","P");
   tleg->Draw();
   TLatex *lt1 = new TLatex(); lt1->SetNDC();
   lt1->SetTextSize(0.07);
   lt1->DrawLatex(0.54,0.93,"PbPb  #sqrt{s_{NN}} = 2.76 TeV");
   if (dphimode == 1) lt1->DrawLatex(0.4,0.4,"Cowboys only");
   if (dphimode == -1) lt1->DrawLatex(0.4,0.4,"Sailors only");


   c1->cd();
   pad2->Draw();
   pad2->cd();
   pad2->SetGridy();
   haxis2->Draw();
   gratio->Draw("P");

   c1->SaveAs(Form("c1_eta%i_dphimode%i.pdf",ieta,dphimode));

   return 1;
}
