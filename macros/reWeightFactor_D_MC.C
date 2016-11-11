#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#include "TSystem.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TPave.h"
#include "TText.h"

#include "TROOT.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"

#include "RooFit.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooFitResult.h"

#include "TStyle.h"
#include "TLatex.h"

#include "TMath.h"

using namespace RooFit;
using namespace std;

// This macro compares the data and mc pt distributions in different eta regions and computes a weighting function from the ratio of the distributions

/////////////////////////////////////////////////
//              P A R A M E T E R S            //
/////////////////////////////////////////////////

// Choose the efficiency type.
// Possible values: MUIDTRG, TRK, STA
#define MUIDTRG

// pp or PbPb?
bool isPbPb = true; // if true, will compute the centrality dependence
TString collTag = "PbPb"; // isPbPb ? "PbPb" : "pp";

// do the toy study for the correction factors? (only applies if MUIDTRG)
bool doToys = false;

// Location of the files
const int nSyst = 1;//5;
// the first file is for the nominal case, the following ones are for the systematics
const char* fDataName[nSyst] = {
   "../test/jpsiHI/Fits/Data/PbPb/MuIdTrg/Results_MuIDTrig_L1_fullRun/tnp_Ana_RD_PbPb_MuonIDTrg_AllMB.root",
   // "/home/emilien/Documents/Postdoc_LLR/TagAndProbe/systs/massrange/pbpb_data/tnp_Ana_RD_PbPb_MuonIDTrg_AllMB.root",
   // "/home/emilien/Documents/Postdoc_LLR/TagAndProbe/systs/signalfcn/pbpb_data/tnp_Ana_RD_PbPb_MuonIDTrg_AllMB.root",
   // "/home/emilien/Documents/Postdoc_LLR/TagAndProbe/systs/bkgdfcn/pbpb_data/tnp_Ana_RD_PbPb_MuonIDTrg_AllMB.root",
   // "/home/emilien/Documents/Postdoc_LLR/TagAndProbe/systs/tagsel/pbpb_data/tnp_Ana_RD_PbPb_MuonIDTrg_AllMB.root",
};
const char* fMCName[nSyst] = {
   "../test/jpsiHI/Fits/MC/PbPb/MuIdTrg/Results_MuIDTrig_HLT/tnp_Ana_MC_PbPb_MuonIDTrg_AllMB.root",
   // "/home/emilien/Documents/Postdoc_LLR/TagAndProbe/systs/massrange/pbpb_mc/tnp_Ana_MC_PbPb_MuonIDTrg_AllMB.root",
   // "/home/emilien/Documents/Postdoc_LLR/TagAndProbe/systs/signalfcn/pbpb_mc/tnp_Ana_MC_PbPb_MuonIDTrg_AllMB.root",
   // "/home/emilien/Documents/Postdoc_LLR/TagAndProbe/systs/bkgdfcn/pbpb_mc/tnp_Ana_MC_PbPb_MuonIDTrg_AllMB.root",
   // "/home/emilien/Documents/Postdoc_LLR/TagAndProbe/systs/tagsel/pbpb_mc/tnp_Ana_MC_PbPb_MuonIDTrg_AllMB.root",
};

// names for systematics
const char* systName[nSyst] = {
   "nominal",
   // "massrange",
   // "signalfcn",
   // "bkgfcn",
   // "tagsel"
};



//////////////////////////////////////////////////////////////////////////

// Other parameters
#ifdef MUIDTRG
const int nAbsEtaBins = 3;
TString ptTag[nAbsEtaBins] = {"MuIdTrg_abseta00_12", "MuIdTrg_abseta12_21", "MuIdTrg_abseta21_24"};
TString absetaVar("abseta");
TString cutTag("tpTree"); 
TString cutLegend("Muon ID + trigger");
const double ratiomin[nAbsEtaBins] = {0.001,0.001,0.001};
const double ratiomax[nAbsEtaBins] = {1.,1.,10.};
const double sfrangeU[nAbsEtaBins] = {0.6,1.4,1.};
const double sfrangeD[nAbsEtaBins] = {0.3,0.3,0.9};
#endif

#ifdef STA
const int nAbsEtaBins = 2;
TString ptTag[nAbsEtaBins] = {"STA_pt1", "STA_pt2"};
TString absetaVar("abseta");
TString cutTag("tpTreeTrk"); 
TString cutLegend("Standalone");
const double ratiomin = 0.001;
const double sfrangeU = 2.4;
const double sfrangeD = 0.60;
#endif

#ifdef TRK
const int nAbsEtaBins = 1;
TString ptTag[nAbsEtaBins] = {"Trk_ptSeg"};
TString absetaVar("eta");
TString cutTag("tpTreeSta"); 
TString cutLegend("Standalone");
const double ratiomin = 0.001;
const double sfrangeU = 2.4;
const double sfrangeD = 0.60;
#endif

// Function Define
TGraphAsymmErrors *plotEff_1bin(RooDataSet *a, int aa, const char* varx, int rebin=1, double* tntot=NULL);
double funcFitRatioUp(double *x, double *par);
double funcFitRatio(double *x, double *par);
double funcFitRatioPol2(double *x, double *par);
double funcPtDistr(double *x, double *par);
double funcRatioPtDistr(double *x, double *par);

// From here you need to set up your environments.
void reWeightFactor_D_MC() {
  
  // gROOT->Macro("~/logon.C");
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetTitle(0);
  gStyle->SetPadLeftMargin(0.11);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetTitleYOffset(1.0);
  
  
  //data and MC root files as well as single bin for integrated efficiency
  TFile* fMC[nSyst];
  TFile* fData[nSyst];
  
  for (int i=0; i<nSyst; i++) {
    fMC[i] = new TFile(fMCName[i]);
    fData[i] = new TFile(fDataName[i]);
  }
  
  TCanvas *c1 = new TCanvas("c1","",700,600);
  
  vector<RooDataSet*> daPtData0[nSyst], daPtData1[nSyst];
  
  for (int k=0; k<nSyst; k++) {
    for (int i=0; i<nAbsEtaBins; i++)
    {
      daPtData0[k].push_back((RooDataSet*)fMC[k]->Get(cutTag + "/" + ptTag[i] + "/fit_eff"));
      daPtData1[k].push_back((RooDataSet*)fData[k]->Get(cutTag + "/" + ptTag[i] + "/fit_eff"));
    }
  }
  
  vector<TGraphAsymmErrors*> ComPt0[nSyst], ComPt1[nSyst];
  
  for (int k=0; k<nSyst; k++) {
    for (unsigned int i=0; i<daPtData0[k].size(); i++)
    {
      ComPt0[k].push_back(plotEff_1bin(daPtData0[k][i], 1, "pt"));
      ComPt1[k].push_back(plotEff_1bin(daPtData1[k][i], 1, "pt"));
    }
  }
  
  int nbins_abseta = ComPt0[0].size();
  
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
  
  // // adapt text size
  // lTextSize *= 1./0.7;
  
  
  TH1F *hPad = new TH1F("hPad",";p^{#mu}_{T} [GeV/c];(1/N_{J/#psi})dN_{J/#psi}/dp_{T}^{#mu}",5,0,30);
  hPad->GetXaxis()->CenterTitle();
  hPad->GetXaxis()->SetLabelSize(0.);
  hPad->GetXaxis()->SetTitleSize(0.);
  hPad->GetXaxis()->SetTitleOffset(1.2);
  hPad->GetYaxis()->SetLabelSize(0.05);
  hPad->GetYaxis()->SetTitleSize(0.05);
  hPad->GetYaxis()->SetTitleOffset(1.);
  
  hPad->GetXaxis()->SetRangeUser(0.,20);
  
  pad2->cd();
  pad2->SetGridy();
  double tsize = (1./0.36)*hPad->GetYaxis()->GetTitleSize(); // 1./0.36
  TH1F *hPadr = (TH1F*) hPad->Clone("hPadr");
  hPadr->GetXaxis()->SetRangeUser(0.,20);
  hPadr->GetYaxis()->SetTitle("Scale Factor");
  hPadr->GetXaxis()->SetTitleSize(tsize);
  hPadr->GetXaxis()->SetLabelSize(tsize);
  hPadr->GetYaxis()->SetTitleSize(tsize);
  hPadr->GetYaxis()->SetLabelSize(tsize);
  hPadr->GetYaxis()->SetNdivisions(504,kTRUE);
  
  pad1->cd();
  
  TString header;
  for (int i=0; i<nbins_abseta; i++)
  {
    double ptmin, ptmax(30.);
    
    hPad->GetYaxis()->SetRangeUser(ratiomin[i],ratiomax[i]);
    hPadr->GetYaxis()->SetRangeUser(1.-sfrangeD[i],1.+sfrangeU[i]);
    
    for (int k=0; k<nSyst; k++)
    {
      int nbins_mc = ComPt0[k][i]->GetN();
      int nbins = ComPt1[k][i]->GetN();
      
      if (nbins_mc == nbins)
      {
        cout << "Computing weighting factor for file " << systName[k] << " in Eta bin " << i << endl;
        
        ofstream file_sfs(cutTag + Form("_ReWFactor_EtaBin%i_",i) + collTag + Form("_%s",systName[k]) + "_RD_MC_PT.txt");
        
        double *xr = new double[nbins];
        double *xrlo = new double[nbins];
        double *xrhi = new double[nbins];
        
        for (int j=0; j<nbins; j++)
        {
          double x = ComPt1[k][i]->GetX()[j];
          double xerrlo = ComPt1[k][i]->GetErrorXlow(j);
          double xerrhi = ComPt1[k][i]->GetErrorXhigh(j);
          
          xr[j] = (x - xerrlo) + (((x + xerrhi) - (x - xerrlo))/2.); // Set x position at the center of the bin
          xrlo[j] = xr[j] - (x - xerrlo);
          xrhi[j] = (x + xerrhi) - xr[j];
        }
        
        //============= Reweighting factor computation ============//
        // Here we compute a reweighting factor for each abseta bin vs pt
        double* tntotMC = new double[nbins];
        double* tntotMCErrhi = new double[nbins];
        double* tntotMCErrlo = new double[nbins];
        double sumTntotMC(0.);
        double sumTntotMCErr(0.);
        double* tntotD = new double[nbins];
        double* tntotDErrhi = new double[nbins];
        double* tntotDErrlo = new double[nbins];
        double sumTntotD(0.);
        double sumTntotDErr(0.);
        double* rewF = new double[nbins]; // Define reweigting factor
        double* rewFErr = new double[nbins];
        TString tag = absetaVar + "_bin0__pt_bin";
        for (int j=0; j<nbins; j++)
        {
          RooFitResult *fitresMC = (RooFitResult*) fMC[k]->Get(cutTag + "/" + ptTag[i] + "/" + tag + Form("%i__cbGausPlusPol2/fitresults",j));
          if (!fitresMC) cerr << "ERROR I couldn't find the MC fit results! Expect a crash soon..." << endl;
          tntotMC[j] = ((RooRealVar*) fitresMC->floatParsFinal().find("numTot"))->getVal(); // Get the NJpsi value
          tntotMCErrhi[j] = ((RooRealVar*) fitresMC->floatParsFinal().find("numTot"))->getErrorHi(); // Get the NJpsi error
          tntotMCErrlo[j] = ((RooRealVar*) fitresMC->floatParsFinal().find("numTot"))->getErrorLo();
          
          sumTntotMC += tntotMC[j];
          sumTntotMCErr += tntotMCErrhi[j]*tntotMCErrhi[j];
          
          RooFitResult *fitresD = (RooFitResult*) fData[k]->Get(cutTag + "/" + ptTag[i] + "/" + tag + Form("%i__cbGausPlusPol2/fitresults",j));
          if (!fitresD) cerr << "ERROR I couldn't find the data fit results! Expect a crash soon..." << endl;
          tntotD[j] = ((RooRealVar*) fitresD->floatParsFinal().find("numTot"))->getVal(); // Get the NJpsi value
          tntotDErrhi[j] = ((RooRealVar*) fitresD->floatParsFinal().find("numTot"))->getErrorHi(); // Get the NJpsi error and
          tntotDErrlo[j] = ((RooRealVar*) fitresD->floatParsFinal().find("numTot"))->getErrorLo();
          
          sumTntotD += tntotD[j];
          sumTntotDErr += tntotDErrhi[j]*tntotDErrhi[j];
          
          rewF[j] = 0.;
          if (tntotD[j] > 0)
          {
            if (tntotMC[j] > 0)
            {
              rewF[j] = tntotD[j]/tntotMC[j];
              rewFErr[j] = rewF[j]*TMath::Sqrt(TMath::Power(tntotDErrhi[j]/tntotD[j],2.) + TMath::Power(tntotMCErrhi[j]/tntotMC[j],2.));
            }
            else
            {
              rewF[j] = 1.;
              rewFErr[j] = 1.;
            }
          }
          
          delete fitresMC;
          delete fitresD;
        }
        // normalise by binwidht and NJpsiTotal
        sumTntotMCErr = TMath::Sqrt(sumTntotMCErr);
        sumTntotDErr = TMath::Sqrt(sumTntotDErr);
        for (int j=0; j<nbins; j++)
        {
          tntotMC[j] /= sumTntotMC*(xrlo[j]+xrhi[j]); // Normalise NJpsi
          tntotD[j] /= sumTntotD*(xrlo[j]+xrhi[j]);
          
          tntotMCErrhi[j] /= sumTntotMC*(xrlo[j]+xrhi[j]);// Normalise NJpsi errors
          tntotMCErrlo[j] /= sumTntotMC*(xrlo[j]+xrhi[j]);
          tntotDErrhi[j] /= sumTntotD*(xrlo[j]+xrhi[j]);
          tntotDErrlo[j] /= sumTntotD*(xrlo[j]+xrhi[j]);
        }
        
        double ratio_MC_D(1.);
        double ratio_MC_D_Err(1.);
        if ((sumTntotMC != 0) && (sumTntotD != 0))
        {
          ratio_MC_D = sumTntotMC/sumTntotD;
          ratio_MC_D_Err = ratio_MC_D*TMath::Sqrt(TMath::Power(sumTntotMCErr/sumTntotMC,2.) + TMath::Power(sumTntotDErr/sumTntotD,2.));
        }
        else
        {
          cout << "ERROR No signal found in data and/or MC" << endl;
          return;
        }
        
        for (int j=0; j<nbins; j++)
        {
          double tempRewF = rewF[j]*ratio_MC_D; //Normalise distributions in the reweigting factor to 1
          rewFErr[j] = tempRewF*TMath::Sqrt( TMath::Power(rewFErr[j]/rewF[j],2.) + TMath::Power(ratio_MC_D_Err/ratio_MC_D,2.));
          rewF[j] = tempRewF;
          
          cout << rewF[j] << " +- " << rewFErr[j] << endl;
        }
        //===========================================//
        
        //============= Plotting of distributions ============//
        for (int j=0; j<nbins; j++)
        {
          if (j == 0)
          {
            file_sfs << "Pt interval  " << "  Weight" << endl;
            file_sfs << xr[j]-xrlo[j] << " - " << xr[j]+xrhi[j] << "    " << rewF[j] << endl;
          }
          else file_sfs << xr[j]-xrlo[j] << " - " << xr[j]+xrhi[j] << "    " << rewF[j] << endl;
        }
        file_sfs.close();
        
        TGraphAsymmErrors* gData = new TGraphAsymmErrors(nbins,xr,tntotD,xrlo,xrhi,tntotDErrlo,tntotDErrhi);
        gData->SetMarkerStyle(25);
        gData->SetMarkerSize(1.4);
        gData->SetMarkerColor(kBlue+1);
        gData->SetLineColor(kBlue+1);
        TGraphAsymmErrors* gMC = new TGraphAsymmErrors(nbins,xr,tntotMC,xrlo,xrhi,tntotMCErrlo,tntotMCErrhi);
        gMC->SetMarkerStyle(20);
        gMC->SetMarkerSize(1.4);
        gMC->SetMarkerColor(kRed+1);
        gMC->SetLineColor(kRed+1);

        pad1->cd();
        pad1->SetLogy();
        hPad->Draw();
        TLatex *lt1 = new TLatex();
        lt1->SetNDC();
        
        char legs[512];
        TLegend *leg1 = new TLegend(0.64,0.37,0.86,0.71);
        leg1->SetFillStyle(0);
        leg1->SetFillColor(0);
        leg1->SetBorderSize(0);
        leg1->SetTextSize(0.035);
        ptmin = ((RooRealVar*) daPtData0[k][i]->get()->find("pt"))->getBinning().binLow(0);
        double etamin, etamax;
        if (daPtData0[k][i]->get()->find("abseta"))
        {
          etamin = ((RooRealVar*) daPtData0[k][i]->get()->find("abseta"))->getBinning().binLow(0);
          etamax = ((RooRealVar*) daPtData0[k][i]->get()->find("abseta"))->getBinning().binHigh(0);
          header = TString("#splitline{") + cutLegend + Form(" N_{J/#psi}}{(p^{#mu}_{T}>%.1f, |#eta| #in [%.1f, %.1f])}",ptmin,etamin,etamax);
        }
        else
        {
          etamin = ((RooRealVar*) daPtData0[k][i]->get()->find("eta"))->getBinning().binLow(0);
          etamax = ((RooRealVar*) daPtData0[k][i]->get()->find("eta"))->getBinning().binHigh(0);
          header = TString("#splitline{") + cutLegend + Form(" N_{J/#psi}}{(p^{#mu}_{T}>%.1f, #eta #in [%.1f, %.1f])}",ptmin,etamin,etamax);
        }
        
//        // Fit distributions and plot them
//        TF1* fD = new TF1("ptData",funcPtDistr,ptmin,ptmax,3);
//        fD->SetParameters(1.,5.,4.);
//        fD->SetParLimits(0,0.,1000.);
//        fD->SetParLimits(1,0.1,10.);
//        fD->SetParLimits(2,1.,7.);
//        fD->SetLineColor(kBlue+1);
//        TF1* fMC = new TF1("ptMC",funcPtDistr,ptmin,ptmax,3);
//        fMC->SetParameters(1.,5.,4.);
//        fMC->SetParLimits(0,0.,1000.);
//        fMC->SetParLimits(1,0.1,10.);
//        fMC->SetParLimits(2,1.,7.);
//        fMC->SetLineColor(kRed+1);
//        
//        gData->Fit(fD,"I");
//        gMC->Fit(fMC,"I");
        
        leg1->SetHeader(header);
        sprintf(legs,"MC PYTHIA+EvtGen");
        leg1->AddEntry(gMC,legs,"pl");
        sprintf(legs,"Data");
        leg1->AddEntry(gData,legs,"pl");
        leg1->Draw("same");
        
        gData->Draw("pz same");
        gMC->Draw("pz same");
        
        lt1->SetTextSize(0.05);
        //        lt1->DrawLatex(0.43,0.60,"CMS Preliminary");
        lt1->DrawLatex(0.57,0.77,collTag + "  #sqrt{s_{NN}} = 5.02 TeV");
        
        // now take care of the data/mc ratio panel
        c1->cd();
        // pad2->SetFrameFillStyle(4000);
        pad2->Draw();
        pad2->cd();
        hPadr->Draw();
        
        TGraphAsymmErrors* gratio = new TGraphAsymmErrors(nbins,xr,rewF,xrlo,xrhi,rewFErr,rewFErr);
        gratio->SetMarkerStyle(20);
        gratio->SetMarkerColor(kBlack);
        gratio->SetMarkerSize(1.2);
        gratio->SetLineColor(kBlack);
        gratio->SetLineWidth(1);
        
//        TF1* fRatio = new TF1("weightsFunction",funcRatioPtDistr,ptmin,ptmax,6);
//        for (int j = 0 ; j < 7 ; j++)
//        {
//          fRatio->SetParameter(j,(j<3 ? fD->GetParameter(j) : fMC->GetParameter(j-3)));
//        }
//        
//        gratio->GetListOfFunctions()->Add(fRatio->Clone());
        
        TF1* fRatio(0x0);
        if (i == 0)
        {
          fRatio = new TF1("weightsFunction",funcFitRatioUp,ptmin,ptmax,4);
          fRatio->SetParameters(0.5,0.1,20,4.);
          fRatio->SetParLimits(0,0.1,10.);
          fRatio->SetParLimits(1,0.,10.);
          fRatio->SetParLimits(1,0.,100.);
          fRatio->SetParLimits(2,-1000.,1000.);
        }
        else
        {
          fRatio = new TF1("weightsFunction",funcFitRatio,ptmin,ptmax,3);
          fRatio->SetParameters(0.5,20,4.);
          fRatio->SetParLimits(0,0.1,10.);
          fRatio->SetParLimits(1,0.,100.);
          fRatio->SetParLimits(2,-1000.,1000.);
        }
        gratio->Fit(fRatio);
        
        gratio->Draw("pz same");
        
        
        // save
        c1->SaveAs(cutTag + Form("_RatioDMC_EtaBin%i",i) + collTag + Form("_%s",systName[k]) + "_RD_MC_PT.root");
        c1->SaveAs(cutTag + Form("_RatioDMC_EtaBin%i",i) + collTag + Form("_%s",systName[k]) + "_RD_MC_PT.pdf");
        //===========================================//
        
        // Produce and save histogram for latter usage
        double* binsx = new double[nbins+1];
        for (int j=0; j<nbins+1; j++)
        {
          if (j == nbins) binsx[j] = xr[j-1] + xrhi[j-1];
          else binsx[j] = xr[j] - xrlo[j]; // Low edges
        }
        
        TH1F* gratioHist = new TH1F("weightsHisto","weights",nbins,binsx);
        for (int j=0; j<nbins; j++)
        {
          gratioHist->SetBinContent(j+1,rewF[j]);
        }
        TFile* fsave = new TFile(cutTag + Form("_Weights_EtaBin%i",i) + collTag + Form("_%s",systName[k]) + "_RD_MC_PT.root","RECREATE");
        gratioHist->Write();
        fRatio->Write();
        fsave->Close();
        delete fsave;
        delete gratioHist;
      }
    }
    
  }
  
}

TGraphAsymmErrors *plotEff_1bin(RooDataSet *a, int aa, const char* varx, int rebin, double *tntot){
  const RooArgSet *set = a->get();
  RooRealVar *xAx = (RooRealVar*)set->find(varx);
  RooRealVar *eff = (RooRealVar*)set->find("efficiency");
  
  int nbins = xAx->getBinning().numBins();
  
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
  
  // do the rebinning here if necessary
  if (rebin>1)
  {
    if (nbins % rebin != 0) cout << "ERROR YOU ARE TRYING TO REBIN " << nbins << " BY " << rebin << " HOW IS THIS SUPPOSED TO WORK ???" << endl;
    
    nbins = nbins/rebin;
    for (int i=0; i<nbins; i++) {
      double ntot1 = tntot[2*i];
      double ntot2 = tntot[2*i+1];
      ty[i] = (ty[2*i]*ntot1 + ty[2*i+1]*ntot2) / (ntot1 + ntot2);
      tx[i] = (tx[2*i]*ntot1 + tx[2*i+1]*ntot2) / (ntot1 + ntot2);
      cout << "..." << ntot1 << " " << tx[2*i] << " " << ntot2 << " " << tx[2*i+1] << " " << tx[i] << endl;
      txhi[i] = (txhi[2*i]*ntot1 + txhi[2*i+1]*ntot2) / (ntot1 + ntot2);
      txlo[i] = (txlo[2*i]*ntot1 + txlo[2*i+1]*ntot2) / (ntot1 + ntot2);
      tyhi[i] = (tyhi[2*i]*ntot1 + tyhi[2*i+1]*ntot2) / (ntot1 + ntot2);
      tylo[i] = (tylo[2*i]*ntot1 + tylo[2*i+1]*ntot2) / (ntot1 + ntot2);
    }
  }
  
  
//  cout<<"NBins : "<<nbins<<endl;
  
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
  //b->Draw("apz");
  
//  for (int i=0; i<nbins; i++) {
//    cout << x[i] << " " << y[i] << " " << yhi[i] << " " << ylo[i] << endl;
//  }
  
  return b;
  
}


double funcFitRatioUp(double *x, double *par)
{
  // Function to fit the pt distributions
  // 4 parameters
  
  return par[0] + par[1]*x[0] + par[2]/TMath::Power(x[0],par[3]);
}

double funcFitRatio(double *x, double *par)
{
  // Function to fit the pt distributions
  // 3 parameters
  
  return par[0] + par[1]/TMath::Power(x[0],par[2]);
}

double funcFitRatioPol2(double *x, double *par)
{
  // Function to fit the pt distributions
  // 3 parameters
  
  return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}

double funcPtDistr(double *x, double *par)
{
  // Function to fit the pt distributions
  // 3 parameters
  
  return par[0]*(x[0]/(TMath::Power(1.+TMath::Power(x[0]/par[1],2.),par[2])));
}

double funcRatioPtDistr(double *x, double *par)
{
  // Function to fit the pt distributions
  // 6 parameters
  
  return funcPtDistr(x,par) / funcPtDistr(x,&par[3]);
}
