/////////////  Check 1 file, otherwise same as the main TnPDraw (thus some redundant structure). Original (and fairly bad) naming schemes mostly kept.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#include "TSystem.h"
#include "TTree.h"
#include "TKey.h"
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
#include "TDirectory.h"
#include "TCollection.h"
#include "TPostScript.h"
#include "TMath.h"

#include "toyStudy_syst.h"

using namespace RooFit;
using namespace std;

/////////////////////////////////////////////////
//              P A R A M E T E R S            //
/////////////////////////////////////////////////

// Choose the efficiency type.
// Possible values: MUIDTRG, TRK, STA, MUID, TRG

// pp or PbPb?
bool isPbPb = true; // if true, will compute the centrality dependence
TString collTag = "PbPb"; // isPbPb ? "PbPb" : "pp";

// do the toy study for the correction factors? (only applies if MUIDTRG)
bool doToys = false;

// how to fit efficiencies?
// 0 = [0]*Erf((x-[1])/[2])
// 1 = [0]*Erf((x-[1])/[2]) + [3]
// 2 = ([0]*Erf((x-[1])/[2]))*Exp([4]*x)+ [3]
// 3 = [0]
// 4 = [0]-[1]*TMath::Exp(-[2]*x) 
// 5 = [0]*TMath::Erf((x-[1])/[2]) 
//
int fitfcn = 5;

// Location of the files
const int nSyst = 1;//5;
// the first file is for the nominal case, the following ones are for the systematics
/*const char* fDataName[nSyst] = {
	//"tnp_Ana_RD_PbPb_MuonIDTrg_AllMB.root",
	"./190507/tnp_Ana_Data_RecoSTA_PbPb_moreEta_v2.root",
	"./190502/tnp_Ana_Data_RecoSTA_PbPb_moreEta_v2_signal.root",
	"./190502/tnp_Ana_Data_RecoSTA_PbPb_moreEta_v2_background.root",
	"./190502/tnp_Ana_Data_RecoSTA_PbPb_moreEta_v2_mass.root",
};
const char* fMCName[nSyst] = {
   //"tnp_Ana_MC_PbPb_MuonIDTrg_AllMB.root",
	"./190430/tnp_Ana_MC_STA_PbPb_moreEta_v2.root",
	"./190502/tnp_Ana_MC_STA_PbPb_moreEta_v2_signal.root",
	"./190502/tnp_Ana_MC_STA_PbPb_moreEta_v2_background.root",
	"./190502/tnp_Ana_MC_STA_PbPb_moreEta_v2_mass.root",
};//
*/
// names for systematics
const char* systName[nSyst] = {
//   "nominal","signal","mass","bkg"
   "nominal"
};

const double c_ptRange = 200; // how far to plot the pt
const double c_centralityRange = 200; // how far to plot the centrality (hibin goes to 200)
const double c_runRange = 327600; // how far to plot the run number

//////////////////////////////////////////////////////////////////////////

vector<vector<TString> > ptTag = { {"Trg_abseta00_12_0_20", "Trg_abseta00_12_20_40", "Trg_abseta00_12_40_200"}, {"Trg_abseta12_21_0_20", "Trg_abseta12_21_20_40", "Trg_abseta12_21_40_200"}, {"Trg_abseta21_24_0_40", "Trg_abseta21_24_40_200"} };
TString absetaVar("abseta");
TString centVar("tag_hiBin");
TString treeTag("tpTree");
TString cutLegend("Trigger");
const double effmin = 0.6;
const double sfrange = 0.05;
const char* fDataName[nSyst] = { 
	"./tnp_Ana_RD_L3Mu12_PbPb_0_v5_nominal_v2_0904.root"
	};
const char* fMCName[nSyst] = { 
	"./tnp_Ana_MC_L3Mu12_PbPb_0_v5_nominal_v2_0904.root"
	};


// Function Define
TH2F *plotEff2D(RooDataSet *a, TString b);
vector<TGraphAsymmErrors*> plotEff_Nbins(RooDataSet *a, int aa, const char* varx, const char* var2);
TGraphAsymmErrors *plotEff_1bin(RooDataSet *a, int aa, const char* varx, int rebin = 1, double* tntot = NULL);
TGraphAsymmErrors *plotEffCent(RooDataSet **a1, int aa);
void formatTH1F(TH1* a, int b, int c, int d);
void formatTGraph(TGraph* a, int b, int c, int d);
void formatTLeg(TLegend* a);
void CalEffErr(TGraph *a, double *b);
void CalEffErr(vector<TGraphAsymmErrors*> a, double **b);
void plotSysts(TGraphAsymmErrors *graphs[nSyst], TCanvas *c1, TPad *p1, TH1F *h1, TPad *pr, TH1F *hr, TString header, TString tag);
TF1 *initfcn(const char* fname, int ifcn, double ptmin, double ptmax, double effguess);
TF1 *ratiofunc(const char* fname, TF1 *fnum, TF1 *fden);


// From here you need to set up your environments.
void TnPEffDraw_singleFile_hwan_v2() {

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

	for (int i = 0; i < nSyst; i++) {
	  fMC[i] = new TFile(fMCName[i]);
	  fData[i] = new TFile(fDataName[i]);
	}

	TCanvas *c1 = new TCanvas("c1", "", 700, 600);

	// Loading the values for abseta and centrality bins
	vector<vector<RooDataSet*> > rds_absetaPtDep_MC[nSyst], rds_absetaPtDep_RD[nSyst];

	for (int k = 0; k < nSyst; k++) {
	  for (uint i = 0; i < ptTag.size(); i++)
	  {
	    vector<RooDataSet*> rds_MC, rds_RD;
	    for (uint j = 0; j < ptTag[i].size(); j++)
	    {
	      rds_MC.push_back((RooDataSet*)fMC[k]->Get(treeTag + "/" + ptTag[i][j] + "/fit_eff"));
	      rds_RD.push_back((RooDataSet*)fData[k]->Get(treeTag + "/" + ptTag[i][j] + "/fit_eff"));
	    }
	    rds_absetaPtDep_MC[k].push_back(rds_MC);
	    rds_absetaPtDep_RD[k].push_back(rds_RD);
	  }
	}
	cout << "Loading is DONE" << endl;
	
	//Loading the TGraphAsymmErrors for  abseta bins - 1 bin
	vector<vector<TGraphAsymmErrors*> > ComPt_MC[nSyst], ComPt_RD[nSyst];
	
	for (int k = 0; k < nSyst; k++) {
	  for (uint i = 0; i < rds_absetaPtDep_MC[k].size(); i++)
	  {
	    cout << i << " " << "rds_absetaPtDep_MC["<< k << "].size() : " << rds_absetaPtDep_MC[k].size() << endl;
	    vector<TGraphAsymmErrors*> gr_MC, gr_RD;
	    for (uint j = 0; j < rds_absetaPtDep_MC[k][i].size(); j++)
	    {
	      cout << j << " " << "rds_absetaPtDep_MC["<< k << "]["<< i << "].size() : " << rds_absetaPtDep_MC[k][i].size() << endl;
	      cout << k << " " << i << " " << j << " " << rds_absetaPtDep_MC[k][i][j] << endl;
	      gr_MC.push_back(plotEff_1bin(rds_absetaPtDep_MC[k][i][j], 1, "pt"));
	      cout << k << " " << i << " " << j << " " << rds_absetaPtDep_RD[k][i][j] << endl;
	      gr_RD.push_back(plotEff_1bin(rds_absetaPtDep_RD[k][i][j], 1, "pt"));
	    }
	    ComPt_MC[k].push_back(gr_MC);
	    ComPt_RD[k].push_back(gr_RD);
	  }
	  for (uint i = 0; i < ComPt_MC[k].size(); i++)
	  {
	    for (uint j = 0; j < ComPt_MC[k][i].size(); j++)
	    {
	      ComPt_MC[k][i][j]->SetMarkerStyle(20);
	      ComPt_MC[k][i][j]->SetMarkerSize(1.4);
	      ComPt_MC[k][i][j]->SetMarkerColor(kRed + 1);
	      ComPt_MC[k][i][j]->SetLineColor(kRed + 1);
	      ComPt_RD[k][i][j]->SetMarkerStyle(25);
	      ComPt_RD[k][i][j]->SetMarkerSize(1.4);
	      ComPt_RD[k][i][j]->SetMarkerColor(kBlue + 1);
	      ComPt_RD[k][i][j]->SetLineColor(kBlue + 1);
	    }
	  }
	}
	cout << "HERE1" << endl;

/*
	vector<TGraphAsymmErrors*> effAbsEta_MC[nSyst];
	vector<TGraphAsymmErrors*> effAbsEta_RD[nSyst];
	cout << "HERE2" << endl;
	for (int k = 0; k < nSyst; k++) {
		effAbsEta_MC[k] = plotEff_Nbins(rds_abseta_MC[k], 0, "pt", absetaVar);
		effAbsEta_RD[k] = plotEff_Nbins(rds_abseta_RD[k], 0, "pt", absetaVar);
	}

	cout << endl<< "Loading of roo data sets and efficiencies done " << endl << endl;

	// loading done, set style

		effabsEta_MC->SetMarkerStyle(20);
		effabsEta_MC->SetMarkerSize(1.4);
		effabsEta_MC->SetMarkerColor(kRed + 1);
		effabsEta_MC->SetLineColor(kRed + 1);
		effabsEta_RD->SetMarkerStyle(25);
		effabsEta_RD->SetMarkerSize(1.4);
		effabsEta_RD->SetMarkerColor(kBlue + 1);
		effabsEta_RD->SetLineColor(kBlue + 1);
*/

////////////////// get some averages
/*
	double Trk0[nSyst][4];
	double Trk1[nSyst][4];
	double*** TrkAbsEta0 = new double**[nSyst];
	double*** TrkAbsEta1 = new double**[nSyst];

	for (int k = 0; k < nSyst; k++) {
		TrkAbsEta0[k] = new double*[nbins_abseta];
		TrkAbsEta1[k] = new double*[nbins_abseta];

		for (int i = 0; i < nbins_abseta; i++)
		{
			TrkAbsEta0[k][i] = new double[4]; //	b[0] = sum / nBins;			b[1] = sqrt(sqSumHigh) / nBins; 		b[2] = sqrt(sqSumLow) / nBins;     b[3] unused
			TrkAbsEta1[k][i] = new double[4];
		}

		CalEffErr(eff1bin_MC[k], Trk0[k]);
		CalEffErr(eff1bin_RD[k], Trk1[k]);
		CalEffErr(effAbsEta_MC[k], TrkAbsEta0[k]);
		CalEffErr(effAbsEta_RD[k], TrkAbsEta1[k]);
	}
*/
	///////////////////////////////////////////////
	////////////////// start plotting  ///////////
	//////////////////////////////////////////////

	c1->cd();
	TPad *pad1 = new TPad("pad1", "pad1", 0, 0.26, 1, 1);
	c1->cd();
	TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.3*0.96);
	pad1->SetBottomMargin(0.04);
	pad2->SetTopMargin(0);
	pad2->SetFillColor(0);
	pad2->SetFillStyle(0);
	pad2->SetBottomMargin(gStyle->GetPadBottomMargin() / 0.3);
	pad1->SetTopMargin(gStyle->GetPadTopMargin() / 0.7);
	// pad2->SetGridy();
	pad1->Draw();
	pad1->cd();

	// // adapt text size
	// lTextSize *= 1./0.7;


	TH1F *hPad = new TH1F("hPad", ";p^{#mu}_{T} [GeV/c];Single #mu Efficiency", 5, 0, c_ptRange);
	hPad->GetXaxis()->CenterTitle();
	hPad->GetXaxis()->SetLabelSize(0.05);
	hPad->GetXaxis()->SetTitleSize(0.05);
	hPad->GetXaxis()->SetTitleOffset(1.2);
	hPad->GetYaxis()->SetLabelSize(0.05);
	hPad->GetYaxis()->SetTitleSize(0.05);
	hPad->GetYaxis()->SetTitleOffset(1.);
	hPad->GetYaxis()->SetRangeUser(effmin, 1.05);

	pad2->cd();
	pad2->SetGridy();
	double tsize = (1. / 0.36)*hPad->GetYaxis()->GetTitleSize(); // 1./0.36
	TH1F *hPadr = (TH1F*)hPad->Clone("hPadr"); hPadr->GetYaxis()->SetRangeUser(1. - sfrange, 1. + sfrange);
	hPadr->GetYaxis()->SetTitle("Scale Factor");
	hPadr->GetXaxis()->SetTitleSize(tsize);
	hPadr->GetXaxis()->SetLabelSize(tsize);
	hPadr->GetYaxis()->SetTitleSize(tsize);
	hPadr->GetYaxis()->SetLabelSize(tsize);
	hPadr->GetYaxis()->SetNdivisions(504, kTRUE);
	TH1F *hPadr_syst = (TH1F*)hPadr->Clone("hPadr_syst");hPadr_syst->GetYaxis()->SetRangeUser(1. - .1, 1. + .1);
	TH1F *hPad_syst = (TH1F*)hPad->Clone("hPad_syst");


	pad1->cd();

	// draw pt dependence in abseta bins 
	TString header;

	for (int k = 0; k < nSyst; k++)
	{
	  for (uint i = 0; i < ComPt_MC[k].size(); i++)
	  {
	    for (uint j = 0; j < ComPt_MC[k][i].size(); j++)
	    {
		
	      pad1->cd();
	      hPad->Draw();
	      TLatex *lt1 = new TLatex();
	      lt1->SetNDC();

	      char legs[512];
	      TLegend *leg1 = new TLegend(0.55, 0.10, 0.76, 0.33); //(x1, y1, x2, y2);
	      leg1->SetFillStyle(0);
	      leg1->SetFillColor(0);
	      leg1->SetBorderSize(0);
	      leg1->SetTextSize(0.030);
	      const auto& ptmin = ((RooRealVar*)rds_absetaPtDep_MC[k][i][j]->get()->find("pt"))->getBinning().binLow(0);
	      const auto& centmin = ((RooRealVar*)rds_absetaPtDep_MC[k][i][j]->get()->find("tag_hiBin"))->getBinning().binLow(0)/2.;
	      const auto& centmax = ((RooRealVar*)rds_absetaPtDep_MC[k][i][j]->get()->find("tag_hiBin"))->getBinning().binHigh(0)/2.;
	      double etamin, etamax;
	      TString perc = "%";
	      if (rds_absetaPtDep_MC[k][i][j]->get()->find("abseta"))
	      {
		etamin = ((RooRealVar*)rds_absetaPtDep_MC[k][i][j]->get()->find("abseta"))->getBinning().binLow(0);
		etamax = ((RooRealVar*)rds_absetaPtDep_MC[k][i][j]->get()->find("abseta"))->getBinning().binHigh(0);
		header = TString("#splitline{") + cutLegend + Form(" Efficiency}{(p^{#mu}_{T}>%.1f, |#eta| #in [%.1f, %.1f], Cent. %.0f%s-%.0f%s)}", ptmin, etamin, etamax, centmin, perc.Data(), centmax, perc.Data());
	      }
	      leg1->SetHeader(header);
	      sprintf(legs, "MC MadGraph5+HYDJET");
	      leg1->AddEntry(ComPt_MC[k][i][j], legs, "pl");
	      sprintf(legs, "Data");
	      leg1->AddEntry(ComPt_RD[k][i][j], legs, "pl");
	      leg1->Draw("same");

	      ComPt_MC[k][i][j]->Draw("pz same");
	      ComPt_RD[k][i][j]->Draw("pz same");

	      lt1->SetTextSize(0.05);
	      lt1->DrawLatex(0.20, 0.30, "CMS Preliminary");
	      lt1->DrawLatex(0.20, 0.24, collTag + "  #sqrt{s_{NN}} = 5.02 TeV");

	      // now take care of the data/mc ratio panel
	      c1->cd();
	      // pad2->SetFrameFillStyle(4000);
	      pad2->Draw();
	      pad2->cd();
	      hPadr->Draw();

	      int nbins_mc = ComPt_MC[k][i][j]->GetN();
	      int nbins = ComPt_RD[k][i][j]->GetN();
	      double xr[nbins];
	      double yr[nbins];
	      double xrlo[nbins];
	      double yrlo[nbins];
	      double xrhi[nbins];
	      double yrhi[nbins];

	      TGraphAsymmErrors* ComPt0_forRatio = NULL;
	      if (nbins_mc == nbins) {
		ComPt0_forRatio = ComPt_MC[k][i][j];
	      }
	      else {
		double tntot[nbins_mc];
		TString tag = absetaVar + "_bin0__pt_bin";
		for (int n = 0; n < nbins_mc; n++) {
		  // Loop on the directories to find the one we are looking for
		  TDirectory *tdir = (TDirectory*)fMC[0]->Get(treeTag + "/" + ptTag[i][j]);
		  TIter next(tdir->GetListOfKeys()); TObject *obj;
		  while ((obj = next())) {
		    obj = ((TKey*)obj)->ReadObj();
		    if (TString(obj->ClassName()) != "TDirectoryFile") continue;
		    if (TString(obj->GetName()).Contains(Form("__pt_bin%i", n))) { tdir = (TDirectory*)obj; break; }
		  }

		  const auto& fitres = (RooFitResult*)tdir->Get("fitresults");
		  if (!fitres) cerr << "ERROR I couldn't find the fit results! Expect a crash soon..." << endl;
		  tntot[n] = ((RooRealVar*)fitres->floatParsFinal().find("numTot"))->getVal() * (((RooRealVar*)fitres->floatParsFinal().find("fSigAll"))->getVal());
		  delete fitres;
		}
		ComPt0_forRatio = plotEff_1bin(rds_absetaPtDep_MC[k][i][j], 1, "pt", nbins_mc / nbins, tntot);
	      }

	      // here we assume that the mc uncertainty is negligible compared to the data one: simply scale everything by the central value.
	      for (int n = 0; n < nbins; n++)
	      {
		xr[n] = ComPt_RD[k][i][j]->GetX()[n];
		xrlo[n] = ComPt_RD[k][i][j]->GetErrorXlow(n);
		xrhi[n] = ComPt_RD[k][i][j]->GetErrorXhigh(n);
		yr[n] = ComPt_RD[k][i][j]->GetY()[n] / ComPt0_forRatio->GetY()[n];
		yrlo[n] = ComPt_RD[k][i][j]->GetErrorYlow(n) / ComPt0_forRatio->GetY()[n];
		yrhi[n] = ComPt_RD[k][i][j]->GetErrorYhigh(n) / ComPt0_forRatio->GetY()[n];
	      }
	      TGraphAsymmErrors gratio(nbins, xr, yr, xrlo, xrhi, yrlo, yrhi);
	      gratio.SetMarkerStyle(20);
	      gratio.SetMarkerColor(kBlack);
	      gratio.SetMarkerSize(1.0);
	      gratio.SetLineColor(kBlack);
	      gratio.SetLineWidth(1);
	      gratio.Draw("pz same");

	      // save (nominal only)
	      if (k == 0) {
		c1->SaveAs("./Efficiency/EtaCent/" + treeTag + Form("Eff%i_", i) + collTag + "_RD_MC_PT.root");
		c1->SaveAs("./Efficiency/EtaCent/" + treeTag + Form("Eff%i_", i) + collTag + "_RD_MC_PT.pdf");
		c1->SaveAs("./Efficiency/EtaCent/" + treeTag + Form("Eff%i_", i) + collTag + "_RD_MC_PT.png");
	      }

	      cout << "Done with the first part of abseta fitting" << endl;

	      // in case we are looking at muon Id + trigger: get the scale factor at the same time

	    }
	  }
	}

	// Compute the systematic uncertainties
        double errSystMC[10][10][20], errSystRD[10][10][20];
	for (uint i = 0; i < ComPt_MC[0].size(); i++)
	{
	  for (uint j = 0; j < ComPt_MC[0][i].size(); j++)
	  {
	    for (int n = 0; n < ComPt_MC[0][i][j]->GetN(); n++)
	    {
	      double errMC=0., errRD=0.;
	      for (int k = 0; k < nSyst; k++) {
		const auto& systMC = fabs(ComPt_MC[k][i][j]->GetY()[n] - ComPt_MC[0][i][j]->GetY()[n]);
		const auto& systRD = fabs(ComPt_RD[k][i][j]->GetY()[n] - ComPt_RD[0][i][j]->GetY()[n]);
		// Maximum
		errMC = std::max(errMC, systMC);
		errRD = std::max(errRD, systRD);
		/*
		// Average
		errMC += systMC/(nSyst-1);
		errRD += systRD/(nSyst-1);
		*/
	      }
	      errSystMC[i][j][n] = errMC;
	      errSystRD[i][j][n] = errRD;
	    }
          }
        }
	
	// print the binned ratio to the other file
	ofstream file_binnedsfs("correction_binned.txt");
        file_binnedsfs << "double tnp_weight_trig_pbpb(double pt, double eta, double cent, int idx)" << endl;
        file_binnedsfs << "{" << endl;
        file_binnedsfs << "  // Check input variables" << endl;
        file_binnedsfs << "  double abseta = fabs(eta);" << endl;
        file_binnedsfs << "  if (pt<15) { cout << \"[WARNING] Muon pT (\" << pt <<\") < 15 GeV/c\" << endl; return 1.0; }" << endl;
        file_binnedsfs << "  if (abseta>2.4) { cout << \"[WARNING] Muon pseudo-rapidity (\" << eta << \") outside [-2.4, 2.4]\" << endl; return 1.0; }" << endl;
        file_binnedsfs << "  if (cent<0 || cent>100) { cout << \"[ERROR] Centrality (\" << cent << \") outside [0%, 100%]\" << endl; return 1.0; }" << endl;
        file_binnedsfs << endl;
        file_binnedsfs << "  double num=1.0, den=1.0;" << endl;
        // Nominal efficiencies
        file_binnedsfs << endl;
        file_binnedsfs << "  // MC" << endl;
        for (uint i = 0; i < rds_absetaPtDep_MC[0].size(); i++) {
	  if (!rds_absetaPtDep_MC[0][i][0]->get()->find("abseta")) continue;
	  const auto& etamin = ((RooRealVar*)rds_absetaPtDep_MC[0][i][0]->get()->find("abseta"))->getBinning().binLow(0);
	  const auto& etamax = ((RooRealVar*)rds_absetaPtDep_MC[0][i][0]->get()->find("abseta"))->getBinning().binHigh(0);
	  if (!((etamin==0.0 && etamax==1.2) || (etamin==1.2 && etamax==2.1) || (etamin==2.1 && etamax==2.4))) continue;
	  file_binnedsfs << ((etamin==0) ? "  if " : "  else if ") << "(abseta >= " << etamin << " && abseta < " << etamax << ") { " << endl;
          for (uint j = 0; j < rds_absetaPtDep_MC[0][i].size(); j++) {
	    if (!rds_absetaPtDep_MC[0][i][j]->get()->find("tag_hiBin")) continue;
	    const auto& centmin = ((RooRealVar*)rds_absetaPtDep_MC[0][i][j]->get()->find("tag_hiBin"))->getBinning().binLow(0)/2.;
	    const auto& centmax = ((RooRealVar*)rds_absetaPtDep_MC[0][i][j]->get()->find("tag_hiBin"))->getBinning().binHigh(0)/2.;
            file_binnedsfs << ((centmin==0) ? "    if " : "    else if ") << "(cent >= " << centmin << " && cent < " << centmax << ") { " << endl;
	    const auto& nbins_pt = ComPt_MC[0][i][j]->GetN();
	    for (int n = 0; n < nbins_pt; n++) {
	      const auto& ptmin = ComPt_MC[0][i][j]->GetX()[n] - ComPt_MC[0][i][j]->GetEXlow()[n];
	      const auto& ptmax = ComPt_MC[0][i][j]->GetX()[n+1] - ComPt_MC[0][i][j]->GetEXlow()[n+1];
              file_binnedsfs << ((n==0) ? "      if " : "      else if ") << "(pt >= " << ptmin << " && pt < " << (n==(nbins_pt-1) ? 9999. : ptmax) << ") den = " << ComPt_MC[0][i][j]->GetY()[n] << ";" << endl;
            }
            file_binnedsfs << "    }" << endl;
	  }
	  file_binnedsfs << "  }" << endl;
	}
	file_binnedsfs << endl;
        file_binnedsfs << "  // data" << endl;
        file_binnedsfs << "  if (idx <= 0 || idx > 10) { // nominal" << endl;
        for (uint i = 0; i < rds_absetaPtDep_RD[0].size(); i++) {
	  if (!rds_absetaPtDep_RD[0][i][0]->get()->find("abseta")) continue;
	  const auto& etamin = ((RooRealVar*)rds_absetaPtDep_RD[0][i][0]->get()->find("abseta"))->getBinning().binLow(0);
	  const auto& etamax = ((RooRealVar*)rds_absetaPtDep_RD[0][i][0]->get()->find("abseta"))->getBinning().binHigh(0);
	  if (!((etamin==0.0 && etamax==1.2) || (etamin==1.2 && etamax==2.1) || (etamin==2.1 && etamax==2.4))) continue;
	  file_binnedsfs << ((etamin==0) ? "    if " : "    else if ") << "(abseta >= " << etamin << " && abseta < " << etamax << ") { " << endl;
          for (uint j = 0; j < rds_absetaPtDep_RD[0][i].size(); j++) {
	    if (!rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin")) continue;
	    const auto& centmin = ((RooRealVar*)rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin"))->getBinning().binLow(0)/2.;
	    const auto& centmax = ((RooRealVar*)rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin"))->getBinning().binHigh(0)/2.;
            file_binnedsfs << ((centmin==0) ? "      if " : "      else if ") << "(cent >= " << centmin << " && cent < " << centmax << ") { " << endl;
	    const auto& nbins_pt = ComPt_RD[0][i][j]->GetN();
	    for (int n = 0; n < nbins_pt; n++) {
	      const auto& ptmin = ComPt_RD[0][i][j]->GetX()[n] - ComPt_RD[0][i][j]->GetEXlow()[n];
	      const auto& ptmax = ComPt_RD[0][i][j]->GetX()[n+1] - ComPt_RD[0][i][j]->GetEXlow()[n+1];
	      file_binnedsfs << ((n==0) ? "        if " : "        else if ") << "(pt >= " << ptmin << " && pt < " << (n==(nbins_pt-1) ? 9999. : ptmax) << ") num = " << ComPt_RD[0][i][j]->GetY()[n] << ";" << endl;
	    }
            file_binnedsfs << "      }" << endl;
	  }
	  file_binnedsfs << "    }" << endl;
	}
	file_binnedsfs << "  }" << endl;
        file_binnedsfs << "  else if (idx == 1) { // stat up" << endl;
        for (uint i = 0; i < rds_absetaPtDep_RD[0].size(); i++) {
	  if (!rds_absetaPtDep_RD[0][i][0]->get()->find("abseta")) continue;
	  const auto& etamin = ((RooRealVar*)rds_absetaPtDep_RD[0][i][0]->get()->find("abseta"))->getBinning().binLow(0);
	  const auto& etamax = ((RooRealVar*)rds_absetaPtDep_RD[0][i][0]->get()->find("abseta"))->getBinning().binHigh(0);
	  if (!((etamin==0.0 && etamax==1.2) || (etamin==1.2 && etamax==2.1) || (etamin==2.1 && etamax==2.4))) continue;
	  file_binnedsfs << ((etamin==0) ? "    if " : "    else if ") << "(abseta >= " << etamin << " && abseta < " << etamax << ") { " << endl;
          for (uint j = 0; j < rds_absetaPtDep_RD[0][i].size(); j++) {
	    if (!rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin")) continue;
	    const auto& centmin = ((RooRealVar*)rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin"))->getBinning().binLow(0)/2.;
	    const auto& centmax = ((RooRealVar*)rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin"))->getBinning().binHigh(0)/2.;
            file_binnedsfs << ((centmin==0) ? "      if " : "      else if ") << "(cent >= " << centmin << " && cent < " << centmax << ") { " << endl;
	    const auto& nbins_pt = ComPt_RD[0][i][j]->GetN();
	    for (int n = 0; n < nbins_pt; n++) {
	      const auto& ptmin = ComPt_RD[0][i][j]->GetX()[n] - ComPt_RD[0][i][j]->GetEXlow()[n];
	      const auto& ptmax = ComPt_RD[0][i][j]->GetX()[n+1] - ComPt_RD[0][i][j]->GetEXlow()[n+1];
	      file_binnedsfs << ((n==0) ? "        if " : "        else if ") << "(pt >= " << ptmin << " && pt < " << (n==(nbins_pt-1) ? 9999. : ptmax) << ") num = " << ComPt_RD[0][i][j]->GetY()[n]+ComPt_RD[0][i][j]->GetErrorYhigh(n) << ";" << endl;
	    }
            file_binnedsfs << "      }" << endl;
	  }
	  file_binnedsfs << "    }" << endl;
	}
        file_binnedsfs << "  }" << endl;
        file_binnedsfs << "  else if (idx == 2) { // stat down" << endl;
        for (uint i = 0; i < rds_absetaPtDep_RD[0].size(); i++) {
	  if (!rds_absetaPtDep_RD[0][i][0]->get()->find("abseta")) continue;
	  const auto& etamin = ((RooRealVar*)rds_absetaPtDep_RD[0][i][0]->get()->find("abseta"))->getBinning().binLow(0);
	  const auto& etamax = ((RooRealVar*)rds_absetaPtDep_RD[0][i][0]->get()->find("abseta"))->getBinning().binHigh(0);
	  if (!((etamin==0.0 && etamax==1.2) || (etamin==1.2 && etamax==2.1) || (etamin==2.1 && etamax==2.4))) continue;
	  file_binnedsfs << ((etamin==0) ? "    if " : "    else if ") << "(abseta >= " << etamin << " && abseta < " << etamax << ") { " << endl;
          for (uint j = 0; j < rds_absetaPtDep_RD[0][i].size(); j++) {
	    if (!rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin")) continue;
	    const auto& centmin = ((RooRealVar*)rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin"))->getBinning().binLow(0)/2.;
	    const auto& centmax = ((RooRealVar*)rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin"))->getBinning().binHigh(0)/2.;
            file_binnedsfs << ((centmin==0) ? "      if " : "      else if ") << "(cent >= " << centmin << " && cent < " << centmax << ") { " << endl;
	    const auto& nbins_pt = ComPt_RD[0][i][j]->GetN();
	    for (int n = 0; n < nbins_pt; n++) {
	      const auto& ptmin = ComPt_RD[0][i][j]->GetX()[n] - ComPt_RD[0][i][j]->GetEXlow()[n];
	      const auto& ptmax = ComPt_RD[0][i][j]->GetX()[n+1] - ComPt_RD[0][i][j]->GetEXlow()[n+1];
	      file_binnedsfs << ((n==0) ? "        if " : "        else if ") << "(pt >= " << ptmin << " && pt < " << (n==(nbins_pt-1) ? 9999. : ptmax) << ") num = " << ComPt_RD[0][i][j]->GetY()[n]-ComPt_RD[0][i][j]->GetErrorYlow(n) << ";" << endl;
	    }
            file_binnedsfs << "      }" << endl;
	  }
	  file_binnedsfs << "    }" << endl;
	}
        file_binnedsfs << "  }" << endl;
        file_binnedsfs << "  else if (idx == -1) { // TnP fit syst up" << endl;
        for (uint i = 0; i < rds_absetaPtDep_RD[0].size(); i++) {
	  if (!rds_absetaPtDep_RD[0][i][0]->get()->find("abseta")) continue;
	  const auto& etamin = ((RooRealVar*)rds_absetaPtDep_RD[0][i][0]->get()->find("abseta"))->getBinning().binLow(0);
	  const auto& etamax = ((RooRealVar*)rds_absetaPtDep_RD[0][i][0]->get()->find("abseta"))->getBinning().binHigh(0);
	  if (!((etamin==0.0 && etamax==1.2) || (etamin==1.2 && etamax==2.1) || (etamin==2.1 && etamax==2.4))) continue;
	  file_binnedsfs << ((etamin==0) ? "    if " : "    else if ") << "(abseta >= " << etamin << " && abseta < " << etamax << ") { " << endl;
          for (uint j = 0; j < rds_absetaPtDep_RD[0][i].size(); j++) {
	    if (!rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin")) continue;
	    const auto& centmin = ((RooRealVar*)rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin"))->getBinning().binLow(0)/2.;
	    const auto& centmax = ((RooRealVar*)rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin"))->getBinning().binHigh(0)/2.;
            file_binnedsfs << ((centmin==0) ? "      if " : "      else if ") << "(cent >= " << centmin << " && cent < " << centmax << ") { " << endl;
	    const auto& nbins_pt = ComPt_RD[0][i][j]->GetN();
	    for (int n = 0; n < nbins_pt; n++) {
	      const auto& ptmin = ComPt_RD[0][i][j]->GetX()[n] - ComPt_RD[0][i][j]->GetEXlow()[n];
	      const auto& ptmax = ComPt_RD[0][i][j]->GetX()[n+1] - ComPt_RD[0][i][j]->GetEXlow()[n+1];
	      file_binnedsfs << ((n==0) ? "        if " : "        else if ") << "(pt >= " << ptmin << " && pt < " << (n==(nbins_pt-1) ? 9999. : ptmax) << ") num = " << ComPt_RD[0][i][j]->GetY()[n]+errSystRD[i][j][n] << ";" << endl;
	    }
            file_binnedsfs << "      }" << endl;
	  }
	  file_binnedsfs << "    }" << endl;
	}
        file_binnedsfs << "  }" << endl;
        file_binnedsfs << "  else if (idx == -2) { // TnP fit syst down" << endl;
        for (uint i = 0; i < rds_absetaPtDep_RD[0].size(); i++) {
	  if (!rds_absetaPtDep_RD[0][i][0]->get()->find("abseta")) continue;
	  const auto& etamin = ((RooRealVar*)rds_absetaPtDep_RD[0][i][0]->get()->find("abseta"))->getBinning().binLow(0);
	  const auto& etamax = ((RooRealVar*)rds_absetaPtDep_RD[0][i][0]->get()->find("abseta"))->getBinning().binHigh(0);
	  if (!((etamin==0.0 && etamax==1.2) || (etamin==1.2 && etamax==2.1) || (etamin==2.1 && etamax==2.4))) continue;
	  file_binnedsfs << ((etamin==0) ? "    if " : "    else if ") << "(abseta >= " << etamin << " && abseta < " << etamax << ") { " << endl;
          for (uint j = 0; j < rds_absetaPtDep_RD[0][i].size(); j++) {
	    if (!rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin")) continue;
	    const auto& centmin = ((RooRealVar*)rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin"))->getBinning().binLow(0)/2.;
	    const auto& centmax = ((RooRealVar*)rds_absetaPtDep_RD[0][i][j]->get()->find("tag_hiBin"))->getBinning().binHigh(0)/2.;
            file_binnedsfs << ((centmin==0) ? "      if " : "      else if ") << "(cent >= " << centmin << " && cent < " << centmax << ") { " << endl;
	    const auto& nbins_pt = ComPt_RD[0][i][j]->GetN();
	    for (int n = 0; n < nbins_pt; n++) {
	      const auto& ptmin = ComPt_RD[0][i][j]->GetX()[n] - ComPt_RD[0][i][j]->GetEXlow()[n];
	      const auto& ptmax = ComPt_RD[0][i][j]->GetX()[n+1] - ComPt_RD[0][i][j]->GetEXlow()[n+1];
	      file_binnedsfs << ((n==0) ? "        if " : "        else if ") << "(pt >= " << ptmin << " && pt < " << (n==(nbins_pt-1) ? 9999. : ptmax) << ") num = " << ComPt_RD[0][i][j]->GetY()[n]-errSystRD[i][j][n] << ";" << endl;
	    }
            file_binnedsfs << "      }" << endl;
	  }
	  file_binnedsfs << "    }" << endl;
	}
        file_binnedsfs << "  }" << endl;
	file_binnedsfs << endl;
        file_binnedsfs << "  if (idx == 200) den = 1.0;" << endl;
        file_binnedsfs << "  if (idx == 300) num = den * den;" << endl;
        file_binnedsfs << endl;
        file_binnedsfs << "  return (num/den);" << endl;
        file_binnedsfs << "}" << endl;
}






/////////////////////////
/// FUNCTION DECLARATION
////////////////////////


void formatTH1F(TH1* a, int b, int c, int d) {
	a->SetLineWidth(2);
	a->SetLineStyle(c);
	a->SetMarkerSize(2);
	a->SetLineColor(b);
	a->SetMarkerColor(b);
	a->GetYaxis()->SetTitle("Efficiency");
	if (d == 1) {
		a->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	}
	else if (d == 2) {
		a->GetXaxis()->SetTitle("#eta");
	}
	else if (d == 3) {
		a->GetXaxis()->SetTitle("rapidity");
	}
	else if (d == 4) {
		a->GetXaxis()->SetTitle("Centrality");
	}
	a->GetXaxis()->CenterTitle(true);
	a->GetXaxis()->SetLabelSize(0.05);
	a->GetXaxis()->SetTitleSize(0.05);
	a->GetXaxis()->SetTitleOffset(0.9);
	a->GetYaxis()->SetLabelSize(0.05);
	a->GetYaxis()->SetTitleSize(0.05);
	a->GetYaxis()->SetTitleOffset(0.8);

}

void formatTLeg(TLegend* a) {

	a->SetFillStyle(0);
	a->SetFillColor(0);
	a->SetBorderSize(0);
	a->SetTextSize(0.03);

}


void formatTGraph(TGraph* a, int b, int c, int d)
{

	a->SetMarkerStyle(c);
	a->SetMarkerColor(b);
	a->SetMarkerSize(1.0);
	a->SetLineColor(b);
	a->SetLineWidth(1);
	a->GetXaxis()->SetLabelSize(0.05);
	a->GetXaxis()->SetTitleSize(0.06);
	a->GetXaxis()->SetTitleOffset(0.9);
	a->GetYaxis()->SetTitle("Efficiency");
	a->GetXaxis()->CenterTitle();
	if (d == 1) {
		a->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	}
	else if (d == 2) {
		a->GetXaxis()->SetTitle("eta");
	}
	else if (d == 3) {
		a->GetXaxis()->SetTitle("rapidity");
	}
	else if (d == 4) {
		a->GetXaxis()->SetTitle("Centrality");
	}
	a->GetYaxis()->SetRangeUser(0, 1);
	a->GetXaxis()->SetRangeUser(0, 10);
	a->GetYaxis()->SetLabelSize(0.05);
	a->GetYaxis()->SetTitleSize(0.05);
	a->GetYaxis()->SetTitleOffset(0.9);


}

TGraphAsymmErrors *plotEff_1bin(RooDataSet *a, int aa, const char* varx, int rebin, double *tntot) {
	const RooArgSet *set = a->get();
	RooRealVar *xAx = (RooRealVar*)set->find(varx);
	RooRealVar *eff = (RooRealVar*)set->find("efficiency");

	int nbins = xAx->getBinning().numBins();

	double tx[nbins], txhi[nbins], txlo[nbins];
	double ty[nbins], tyhi[nbins], tylo[nbins];

	for (int i = 0; i < nbins; i++) {
		a->get(i);
		ty[i] = eff->getVal();
		tx[i] = xAx->getVal();
		txhi[i] = fabs(xAx->getErrorHi());
		txlo[i] = fabs(xAx->getErrorLo());
		tyhi[i] = fabs(eff->getErrorHi());
		tylo[i] = fabs(eff->getErrorLo());
	}

	// do the rebinning here if necessary
	if (rebin > 1)
	{
		if (nbins % rebin != 0) cout << "ERROR YOU ARE TRYING TO REBIN " << nbins << " BY " << rebin << " HOW IS THIS SUPPOSED TO WORK ???" << endl;

		nbins = nbins / rebin;
		for (int i = 0; i < nbins; i++) {
			double ntot1 = tntot[2 * i];
			double ntot2 = tntot[2 * i + 1];
			ty[i] = (ty[2 * i] * ntot1 + ty[2 * i + 1] * ntot2) / (ntot1 + ntot2);
			tx[i] = (tx[2 * i] * ntot1 + tx[2 * i + 1] * ntot2) / (ntot1 + ntot2);
			cout << "..." << ntot1 << " " << tx[2 * i] << " " << ntot2 << " " << tx[2 * i + 1] << " " << tx[i] << endl;
			txhi[i] = (txhi[2 * i] * ntot1 + txhi[2 * i + 1] * ntot2) / (ntot1 + ntot2);
			txlo[i] = (txlo[2 * i] * ntot1 + txlo[2 * i + 1] * ntot2) / (ntot1 + ntot2);
			tyhi[i] = (tyhi[2 * i] * ntot1 + tyhi[2 * i + 1] * ntot2) / (ntot1 + ntot2);
			tylo[i] = (tylo[2 * i] * ntot1 + tylo[2 * i + 1] * ntot2) / (ntot1 + ntot2);
		}
	}


	cout << "NBins : " << nbins << endl;

	const double *x = tx;
	const double *xhi = txhi;
	const double *xlo = txlo;
	const double *y = ty;
	const double *yhi = tyhi;
	const double *ylo = tylo;


	TGraphAsymmErrors *b = new TGraphAsymmErrors();
	if (aa == 1) { *b = TGraphAsymmErrors(nbins, x, y, xlo, xhi, ylo, yhi); }
	if (aa == 0) { *b = TGraphAsymmErrors(nbins, x, y, 0, 0, ylo, yhi); }
	b->SetMaximum(1.1);
	b->SetMinimum(0.0);
	b->SetMarkerStyle(20);
	b->SetMarkerColor(kRed + 2);
	b->SetMarkerSize(1.0);
	b->SetTitle("");
	b->GetXaxis()->SetTitleSize(0.1);
	b->GetYaxis()->SetTitleSize(0.1);
	b->GetXaxis()->SetTitle("#eta");
	b->GetYaxis()->SetTitle("Efficiency");
	b->GetXaxis()->CenterTitle();
	//b->Draw("apz");

	for (int i = 0; i < nbins; i++) {
		cout << x[i] << " " << y[i] << " " << yhi[i] << " " << ylo[i] << endl;
	}

	return b;

}

vector<TGraphAsymmErrors*> plotEff_Nbins(RooDataSet *a, int aa, const char* varx, const char* var2) {
	const RooArgSet *set = a->get();
	RooRealVar *xAx = (RooRealVar*)set->find(varx);
	RooRealVar *abseta = (RooRealVar*)set->find(var2);
	RooRealVar *eff = (RooRealVar*)set->find("efficiency");

	int nbins = xAx->getBinning().numBins();
	const int nbins2 = abseta->getBinning().numBins();
	// cout << nbins << " " << nbins2 << endl;

	double **tx = new double*[nbins2], **txhi = new double*[nbins2], **txlo = new double*[nbins2];
	double **ty = new double*[nbins2], **tyhi = new double*[nbins2], **tylo = new double*[nbins2];
	for (int i = 0; i < nbins2; i++)
	{
		tx[i] = new double[nbins];
		txlo[i] = new double[nbins];
		txhi[i] = new double[nbins];
		ty[i] = new double[nbins];
		tylo[i] = new double[nbins];
		tyhi[i] = new double[nbins];
	}

	for (int i = 0; i < nbins*nbins2; i++) {
		a->get(i);
		int bin1 = xAx->getBinning().binNumber(xAx->getVal());
		int bin2 = abseta->getBinning().binNumber(abseta->getVal());
		ty[bin2][bin1] = eff->getVal();
		tx[bin2][bin1] = xAx->getVal();
		txhi[bin2][bin1] = fabs(xAx->getErrorHi());
		txlo[bin2][bin1] = fabs(xAx->getErrorLo());
		tyhi[bin2][bin1] = fabs(eff->getErrorHi());
		tylo[bin2][bin1] = fabs(eff->getErrorLo());
	}

	// cout<<"NBins pt: "<<nbins<<endl;

	vector<TGraphAsymmErrors*> result;
	for (int i = 0; i < nbins2; i++)
	{
		const double *x = tx[i];
		const double *xhi = txhi[i];
		const double *xlo = txlo[i];
		const double *y = ty[i];
		const double *yhi = tyhi[i];
		const double *ylo = tylo[i];
		TGraphAsymmErrors *b = new TGraphAsymmErrors();
		if (aa == 1) { *b = TGraphAsymmErrors(nbins, x, y, xlo, xhi, ylo, yhi); }
		if (aa == 0) { *b = TGraphAsymmErrors(nbins, x, y, 0, 0, ylo, yhi); }
		b->SetMaximum(1.1);
		b->SetMinimum(0.0);
		b->SetMarkerStyle(20);
		b->SetMarkerColor(kRed + 2);
		b->SetMarkerSize(1.0);
		b->SetTitle("");
		b->GetXaxis()->SetTitleSize(0.05);
		b->GetYaxis()->SetTitleSize(0.05);
		b->GetXaxis()->SetTitle("p_{T} [GeV/c]");
		b->GetYaxis()->SetTitle("Efficiency");
		b->GetXaxis()->CenterTitle();
		//b->Draw("apz");
		result.push_back(b);
	}

	// for (int i=0; i<nbins; i++) {
	//   cout << x[i] << " " << y[i] << " " << yhi[i] << " " << ylo[i] << endl;
	// }

	return result;

}



TH2F *plotEff2D(RooDataSet *a, TString b) {
	const RooArgSet *set = a->get();
	RooRealVar *yAx = (RooRealVar*)set->find("pt");
	RooRealVar *xAx = (RooRealVar*)set->find("eta");
	RooRealVar *eff = (RooRealVar*)set->find("efficiency");

	//const int xnbins = xAx->getBinning().numBins();
	//const int ynbins = yAx->getBinning().numBins();

	const double *xvbins = xAx->getBinning().array();
	const double *yvbins = yAx->getBinning().array();

	TH2F* h = new TH2F(b, "", xAx->getBinning().numBins(), xvbins, yAx->getBinning().numBins(), yvbins);

	gStyle->SetPaintTextFormat("5.2f");
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPalette(1);
	h->SetOption("colztexte");
	h->GetZaxis()->SetRangeUser(-0.001, 1.001);
	h->SetStats(kFALSE);
	h->GetYaxis()->SetTitle("p_{T} [GeV/c]");
	h->GetXaxis()->SetTitle("#eta");
	h->GetXaxis()->CenterTitle();
	h->GetYaxis()->CenterTitle();
	h->GetXaxis()->SetTitleSize(0.05);
	h->GetYaxis()->SetTitleSize(0.05);
	h->GetYaxis()->SetTitleOffset(0.8);
	h->GetXaxis()->SetTitleOffset(0.9);
	for (int i = 0; i < a->numEntries(); i++) {
		a->get(i);
		h->SetBinContent(h->FindBin(xAx->getVal(), yAx->getVal()), eff->getVal());
		h->SetBinError(h->FindBin(xAx->getVal(), yAx->getVal()), (eff->getErrorHi() - eff->getErrorLo()) / 2.);
	}

	return h;

}


void CalEffErr(TGraph *a, double *b) {
	const int nbins = 100;
	double x[nbins], y[nbins];
	double sum = 0, errHighSum = 0, errLowSum = 0, sqSumHigh = 0, sqSumLow = 0;
	//double b[3] = 0;

	int nBins = a->GetN();
	for (int i = 0;i < a->GetN();i++) {
		a->GetPoint(i, x[i], y[i]);
		//cout<<"Eff x = "<<x[i]<<" y = "<<y[i]<<endl;
		double eHigh = a->GetErrorYhigh(i);
		double eLow = a->GetErrorYlow(i);
		//cout<<"Err high = "<<eHigh<<" low = "<<eLow<<endl;
		sum += y[i];
		errHighSum += eHigh;
		sqSumHigh += eHigh*eHigh;
		errLowSum += eLow;
		sqSumLow += eLow*eLow;
	}
	b[0] = sum / nBins;
	b[1] = sqrt(sqSumHigh) / nBins;
	b[2] = sqrt(sqSumLow) / nBins;
	//cout<<"b1 : "<<b[0]<<", b2 : "<<b[1]<<", b3 : "<<b[2]<<endl;

	cout << b[0] << "^{" << b[1] << "}_{" << b[2] << "}" << endl;
	//return b[3];
}

void CalEffErr(vector<TGraphAsymmErrors*> a, double **b) {
	const int nbins = 100;
	const int vsize = a.size();

	for (int vbin = 0; vbin < vsize; vbin++)
	{
		double x[nbins], y[nbins];
		double sum = 0, errHighSum = 0, errLowSum = 0, sqSumHigh = 0, sqSumLow = 0;
		//double b[3] = 0;

		int nBins = a[vbin]->GetN();
		for (int i = 0;i < a[vbin]->GetN();i++) {
			a[vbin]->GetPoint(i, x[i], y[i]);
			//cout<<"Eff x = "<<x[i]<<" y = "<<y[i]<<endl;
			double eHigh = a[vbin]->GetErrorYhigh(i);
			double eLow = a[vbin]->GetErrorYlow(i);
			//cout<<"Err high = "<<eHigh<<" low = "<<eLow<<endl;
			sum += y[i];
			errHighSum += eHigh;
			sqSumHigh += eHigh*eHigh;
			errLowSum += eLow;
			sqSumLow += eLow*eLow;
		}
		b[vbin][0] = sum / nBins;
		b[vbin][1] = sqrt(sqSumHigh) / nBins;
		b[vbin][2] = sqrt(sqSumLow) / nBins;
		//cout<<"b1 : "<<b[0]<<", b2 : "<<b[1]<<", b3 : "<<b[2]<<endl;

		cout << b[vbin][0] << "^{" << b[vbin][1] << "}_{" << b[vbin][2] << "}" << endl;
	}
	//return b[3];
}

void plotSysts(TGraphAsymmErrors *graphs[nSyst], TCanvas *c1, TPad *p1, TH1F *h1, TPad *pr, TH1F *hr, TString header, TString tag) {
	p1->cd();
	h1->Draw();
	TLatex *lt1 = new TLatex();
	lt1->SetNDC();

	char legs[512];
	TLegend *leg1 = new TLegend(0.43, 0.05, 0.66, 0.43);
	leg1->SetFillStyle(0);
	leg1->SetFillColor(0);
	leg1->SetBorderSize(0);
	leg1->SetTextSize(0.035);
	leg1->SetHeader(header);
	for (int k = 0; k < nSyst; k++) {
		graphs[k]->SetMarkerColor(k < 4 ? k + 1 : k + 2);
		graphs[k]->SetMarkerStyle(k + 20);
		graphs[k]->SetLineColor(k < 4 ? k + 1 : k + 2);
		leg1->AddEntry(graphs[k], systName[k], "pl");
		graphs[k]->Draw("pz same");
	}
	leg1->Draw("same");

	// lt1->SetTextSize(0.05);
	// lt1->DrawLatex(0.43,0.60,"CMS Preliminary");
	// //lt1->DrawLatex(0.43,0.54,"pp  #sqrt{s} = 5.02 TeV");
	// lt1->DrawLatex(0.43,0.54,collTag + "  #sqrt{s_{NN}} = 5.02 TeV");

	// now take care of the data/mc ratio panel
	c1->cd();
	// pad2->SetFrameFillStyle(4000);
	pr->Draw();
	pr->cd();
	hr->Draw();

	int nbins_mc = graphs[0]->GetN();
	int nbins = graphs[0]->GetN();
	double **xr = new double*[nSyst];
	double **yr = new double*[nSyst];
	double **xrlo = new double*[nSyst];
	double **yrlo = new double*[nSyst];
	double **xrhi = new double*[nSyst];
	double **yrhi = new double*[nSyst];
	for (int j = 0; j < nSyst; j++) {
		xr[j] = new double[nbins];
		yr[j] = new double[nbins];
		xrlo[j] = new double[nbins];
		yrlo[j] = new double[nbins];
		xrhi[j] = new double[nbins];
		yrhi[j] = new double[nbins];
	}

	TGraphAsymmErrors *gratio[nSyst];

	TGraphAsymmErrors* ComPt0_forRatio = NULL;
	ComPt0_forRatio = graphs[0];

	for (int k = 1; k < nSyst; k++) {
		double maxvar = -1;
		for (int j = 0; j < nbins; j++)
		{
			xr[k][j] = graphs[k]->GetX()[j];
			xrlo[k][j] = graphs[k]->GetErrorXlow(j);
			xrhi[k][j] = graphs[k]->GetErrorXhigh(j);
			yr[k][j] = graphs[k]->GetY()[j] / ComPt0_forRatio->GetY()[j];
			maxvar = max(maxvar, yr[k][j]); maxvar = max(maxvar, 1. / yr[k][j]);
			yrlo[k][j] = graphs[k]->GetErrorYlow(j) / ComPt0_forRatio->GetY()[j];
			yrhi[k][j] = graphs[k]->GetErrorYhigh(j) / ComPt0_forRatio->GetY()[j];
		}
		cout << "MAX (" << tag << ", " << systName[k] << "): " << maxvar << endl;
		gratio[k] = new TGraphAsymmErrors(nbins, xr[k], yr[k], xrlo[k], xrhi[k], yrlo[k], yrhi[k]);
		gratio[k]->SetMarkerStyle(20 + k);
		gratio[k]->SetMarkerColor(k < 4 ? k + 1 : k + 2);
		gratio[k]->SetMarkerSize(1.0);
		gratio[k]->SetLineColor(k < 4 ? k + 1 : k + 2);
		gratio[k]->SetLineWidth(1);
		gratio[k]->Draw("pz same");
	}

	// save
	c1->SaveAs("./Efficiency/EtaCent/" + tag + ".root");
	c1->SaveAs("./Efficiency/EtaCent/" + tag + ".pdf");
	c1->SaveAs("./Efficiency/EtaCent/" + tag + ".png");
}

TF1 *initfcn(const char* fname, int ifcn, double ptmin, double ptmax, double effguess) {
	TString formula;
	if (ifcn == 0) formula = "[0]*TMath::Erf((x-[1])/[2])";
	else if (ifcn == 1) formula = "[0]*TMath::Erf((x-[1])/[2])+[3]";
	else if (ifcn == 2) formula = "[0]*(TMath::Erf((x-[1])/[2])*TMath::Exp([4]*x)) + [3]";
	else if (ifcn == 3) formula = "[0]";
	//else if (ifcn == 4) formula = "[0]-[1]*TMath::Exp(-[2]*x)";
	else if (ifcn == 4) formula = "[0]*(1-[1]*TMath::Exp(-x/[2]))";
	else if (ifcn == 5) formula = "[0]*TMath::Erf((x+[1])/[2])";
	else formula = "[0]";
	TF1 *ans = new TF1(fname, formula, ptmin, ptmax);
	if (ifcn == 0) {
		ans->SetParNames("eff0", "x0", "m");
		// Initialize the normalization to the efficiency in the last point
		ans->SetParLimits(0, 0, 1);
		ans->SetParLimits(1, -5.5, 10.);
		ans->SetParLimits(2, 0, 20.);
		ans->SetParameters(effguess, 0.1, 0.5);
	}
	else if (ifcn == 1) {
		ans->SetParNames("eff0", "x0", "m", "cst");
		// Initialize the normalization to the efficiency in the last point
		ans->SetParLimits(0, 0, 9.5);
		ans->SetParLimits(1, -10., 10.);
		ans->SetParLimits(2, 0, 50.);
		ans->SetParLimits(3, -2., 2.);
		ans->SetParameters(effguess, 2., 1.0, 0.);
	}
	else if (ifcn == 2) {
		ans->SetParNames("eff0", "x0", "m", "cst", "fall");
		// Initialize the normalization to the efficiency in the last point
		ans->SetParLimits(0, 0, 95);
		ans->SetParLimits(1, -10., 10.);
		ans->SetParLimits(2, 0, 50.);
		ans->SetParLimits(3, -10., 10.);
		ans->SetParLimits(4, -0.5, 0.0);
		ans->SetParameters(effguess, 2., 1., 0., 0.);
	}
	else if (ifcn == 3) {
		ans->SetParNames("const");
		ans->SetParLimits(0, 0, 1.5);
		ans->SetParameter(0, effguess);
	}
	else if (ifcn == 4) {
		ans->SetParLimits(0,0.0,1.1);
		ans->SetParLimits(1,0,3.99);
		ans->SetParLimits(2,0.1,100.0);
		ans->SetParameter(0,0.9);
		ans->SetParameter(1,3);
		ans->SetParameter(2,8.0);
	}
	else if (ifcn == 5) {
		ans->SetParLimits(0,0.0,1.);
		ans->SetParLimits(1,2.5,150);
		ans->SetParLimits(2,1,76.0);
		ans->SetParameter(0,0.7);
		ans->SetParameter(1,40);
		ans->SetParameter(2,70.0);
	}
	return ans;
}

TF1 *ratiofunc(const char* fname, TF1 *fnum, TF1 *fden) {
	TString formnum = fnum->GetExpFormula();
	TString formden = fden->GetExpFormula();
	int nparnum = fnum->GetNpar();
	int nparden = fden->GetNpar();
	int npartot = nparnum + nparden;
	// replace the names of the parameters of the numerator
	for (int i = 0; i<nparnum; i++) {
		formnum.ReplaceAll(Form("[p%i]", i), Form("[%i]", i));
		formnum.ReplaceAll(Form("[%s]", fnum->GetParName(i)), Form("[%i]", i));
	}
	// replace the names of the parameters of the denominator
	for (int i = 0; i<nparden; i++) {
		formden.ReplaceAll(Form("[p%i]", i), Form("[%i]", i + nparnum));
		formden.ReplaceAll(Form("[%i]", i), Form("[%i]", i + nparnum));
		formden.ReplaceAll(Form("[%s]", fden->GetParName(i)), Form("[%i]", i + nparnum));
	}
	double xmin, xmax; fnum->GetRange(xmin, xmax);
	TF1 *ans = new TF1(fname, TString("(") + formnum + ")/(" + formden + ")", xmin, xmax);
	for (int i = 0; i<nparnum; i++) ans->SetParameter(i, fnum->GetParameter(i));
	for (int i = 0; i<nparden; i++) ans->SetParameter(i + nparnum, fden->GetParameter(i));
	return ans;
}
