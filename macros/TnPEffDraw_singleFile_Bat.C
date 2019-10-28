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
// Possible values: MUIDTRG, TRK, STA, MUID, TRGL2JPSI, TRGL3JPSI, TRGL2UPSI, TRGL3UPSI, TRGDMOPEN
#define TRK
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
// 

const double c_ptRange = 30; // how far to plot the pt
const double c_centralityRange = 200; // how far to plot the centrality (hibin goes to 200)

//////////////////////////////////////////////////////////////////////////
// Other parameters
#ifdef MUID
const int nSyst = 4;
const char* systName[nSyst] = {
  "nominal",
  "signal syst",
  "bkg syst",
  "mass range syst"};
TString outputTag = "Effplots/MuonID/";
TString etaTag("MuId_etadep");
TString absetaTag("MuId_absetadep");
TString centTag("MuId_centdep");
const int nAbsEtaBins = 5;
TString ptTag[nAbsEtaBins] = {"MuId_pt", "MuId_abseta00_12", "MuId_abseta12_18", "MuId_abseta18_21", "MuId_abseta21_24" };
TString allTag("MuId_1bin");
TString absetaVar("abseta");
TString centVar("tag_hiBin");
ofstream file_sfs(outputTag + "correction_functions.txt");
ofstream file_Eta(outputTag + "EtaValues_MuId.txt");
ofstream file_Cent(outputTag + "CentValues_MuId.txt");
ofstream file_TestErr(outputTag + "MuId_ExpErr.txt");
ofstream file_binnedsfs(outputTag +"correction_binned.txt");
TString treeTag("tpTree");
TString cutLegend("Hybrid Soft ID 2018");
const double effmin = 0.801;
const double sfrange = 0.026;
const char* fDataName[nSyst] = { "../test/jpsiHI/Output/MuonID/tnp_Ana_RD_PbPb_MuonID_cbPlusPol1.root",
				 "../test/jpsiHI/Output/MuonID/tnp_Ana_RD_PbPb_MuonID_cbGausPlusPol1.root",
				 "../test/jpsiHI/Output/MuonID/tnp_Ana_RD_PbPb_MuonID_cbPlusPol2.root",
				 "../test/jpsiHI/Output/MuonID/tnp_Ana_RD_PbPb_MuonID_mass2834.root"};

const char* fMCName[nSyst] = { "../test/jpsiHI/Output/MuonID/tnp_Ana_MC_PbPb_MuonID_cbPlusPol1.root",
			       "../test/jpsiHI/Output/MuonID/tnp_Ana_MC_PbPb_MuonID_cbGausPlusPol1.root",
			       "../test/jpsiHI/Output/MuonID/tnp_Ana_MC_PbPb_MuonID_cbPlusPol2.root",
			       "../test/jpsiHI/Output/MuonID/tnp_Ana_MC_PbPb_MuonID_mass2834.root"};
int fitfcn = 1;
#endif

#ifdef TRGL2JPSI
const int nSyst = 4;
const char* systName[nSyst] = {
  "nominal",
  "signal syst",
  "bkg syst",
  "mass range syst"};
TString outputTag = "Effplots/Trg/L2Jpsi/";
TString etaTag("Trg_etadep");
TString absetaTag("Trg_absetadep");
TString centTag("Trg_centdep");
const int nAbsEtaBins = 5;
TString ptTag[nAbsEtaBins] = { "Trg_pt", "Trg_abseta00_12", "Trg_abseta12_18", "Trg_abseta18_21", "Trg_abseta21_24"};
TString allTag("Trg_1bin");
TString absetaVar("abseta");
TString centVar("tag_hiBin");
ofstream file_sfs(outputTag + "correction_functions.txt");
ofstream file_Eta(outputTag + "EtaValues_Trg.txt");
ofstream file_Cent(outputTag + "CentValues_Trg.txt");
ofstream file_TestErr(outputTag + "Trg_ExpErr.txt");
ofstream file_binnedsfs(outputTag +"correction_binned.txt");
TString treeTag("tpTree");
TString cutLegend("L2 Jpsi Trigger");
const double effmin = 0.;
const double sfrange = 0.066;
const char* fDataName[nSyst] = { "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L2Jpsi_cbPlusPol1.root",
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L2Jpsi_cbGausPlusPol1.root",
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L2Jpsi_cbPlusPol2.root",
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L2Jpsi_mass2834.root" };
const char* fMCName[nSyst] = { "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L2Jpsi_cbPlusPol1.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L2Jpsi_cbGausPlusPol1.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L2Jpsi_cbPlusPol2.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L2Jpsi_mass2834.root" };
int fitfcn = 1;
#endif

#ifdef TRGL3JPSI
const int nSyst = 4;
const char* systName[nSyst] = {
  "nominal",
  "signal syst",
  "bkg syst",
  "mass range syst"};
TString outputTag = "Effplots/Trg/L3Jpsi/";
TString etaTag("Trg_etadep");
TString absetaTag("Trg_absetadep");
TString centTag("Trg_centdep");
const int nAbsEtaBins = 5;
TString ptTag[nAbsEtaBins] = { "Trg_pt", "Trg_abseta00_12", "Trg_abseta12_18", "Trg_abseta18_21", "Trg_abseta21_24" };
TString allTag("Trg_1bin");
TString absetaVar("abseta");
TString centVar("tag_hiBin");
ofstream file_sfs(outputTag + "correction_functions.txt");
ofstream file_Eta(outputTag + "EtaValues_Trg.txt");
ofstream file_Cent(outputTag + "CentValues_Trg.txt");
ofstream file_TestErr(outputTag + "Trg_ExpErr.txt");
ofstream file_binnedsfs(outputTag +"correction_binned.txt");
TString treeTag("tpTree");
TString cutLegend("L3 Jpsi Trigger");
const double effmin = 0.;
const double sfrange = 0.35;
const char* fDataName[nSyst] = { "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L3Jpsi_cbPlusPol1.root",
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L3Jpsi_cbGausPlusPol1.root",
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L3Jpsi_cbPlusPol2.root",
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L3Jpsi_mass2834.root"};
const char* fMCName[nSyst] = { "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L3Jpsi_cbPlusPol1.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L3Jpsi_cbGausPlusPol1.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L3Jpsi_cbPlusPol2.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L3Jpsi_mass2834.root" };
int fitfcn = 1;
#endif

#ifdef TRGL2UPSI
const int nSyst = 4;
const char* systName[nSyst] = {
  "nominal",
  "signal syst",
  "bkg syst",
  "mass range syst"};
TString outputTag = "Effplots/Trg/L2Upsi/";
TString etaTag("Trg_etadep");
TString absetaTag("Trg_absetadep");
TString centTag("Trg_centdep");
const int nAbsEtaBins = 5;
TString ptTag[nAbsEtaBins] = { "Trg_pt", "Trg_abseta00_12", "Trg_abseta12_18", "Trg_abseta18_21", "Trg_abseta21_24" };
TString allTag("Trg_1bin");
TString absetaVar("abseta");
TString centVar("tag_hiBin");
ofstream file_sfs(outputTag + "correction_functions.txt");
ofstream file_Eta(outputTag + "EtaValues_Trg.txt");
ofstream file_Cent(outputTag + "CentValues_Trg.txt");
ofstream file_TestErr(outputTag + "Trg_ExpErr.txt");
ofstream file_binnedsfs(outputTag +"correction_binned.txt");
TString treeTag("tpTree");
TString cutLegend("L2 Upsilon Trigger");
const double effmin = 0.;
const double sfrange = 0.15;
const char* fDataName[nSyst] = { "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L2Upsi_cbPlusPol1.root",
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L2Upsi_cbGausPlusPol1.root",
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L2Upsi_cbPlusPol2.root",
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L2Upsi_mass2834.root"};
const char* fMCName[nSyst] = { "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L2Upsi_cbPlusPol1.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L2Upsi_cbGausPlusPol1.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L2Upsi_cbPlusPol2.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L2Upsi_mass2834.root" };

int fitfcn = 1;
#endif

#ifdef TRGL3UPSI
const int nSyst = 4;
const char* systName[nSyst] = {
  "nominal"
  "signal syst",
  "bkg syst",
  "mass range syst"};
TString outputTag = "Effplots/Trg/L3Upsi/";
TString etaTag("Trg_etadep");
TString absetaTag("Trg_absetadep");
TString centTag("Trg_centdep");
const int nAbsEtaBins = 5;
TString ptTag[nAbsEtaBins] = { "Trg_pt", "Trg_abseta00_12", "Trg_abseta12_18", "Trg_abseta18_21", "Trg_abseta21_24" };
TString allTag("Trg_1bin");
TString absetaVar("abseta");
TString centVar("tag_hiBin");
ofstream file_sfs(outputTag + "correction_functions.txt");
ofstream file_Eta(outputTag + "EtaValues_Trg.txt");
ofstream file_Cent(outputTag + "CentValues_Trg.txt");
ofstream file_TestErr(outputTag + "Trg_ExpErr.txt");
ofstream file_binnedsfs(outputTag +"correction_binned.txt");
TString treeTag("tpTree");
TString cutLegend("L3 Upsilon Trigger");
const double effmin = 0.;
const double sfrange = 0.35;
const char* fDataName[nSyst] = { "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L3Upsi_cbPlusPol1.root", 
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L3Upsi_cbGausPlusPol1.root",
                                 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L3Upsi_cbPlusPol2.root",
                                 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_L3Upsi_mass2834.root"};
const char* fMCName[nSyst] = { "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L3Upsi_cbPlusPol1.root", 
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L3Upsi_cbGausPlusPol1.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L3Upsi_cbPlusPol2.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_L3Upsi_mass2834.root"};
int fitfcn = 1;
#endif

#ifdef TRGDMOPEN
const int nSyst = 1;
const char* systName[nSyst] = {
  "nominal"};/*,
  "signal syst",
  "bkg syst",
  "mass range syst"};*/
TString outputTag = "Effplots/Trg/DoubleMuOpen/";
TString etaTag("Trg_etadep");
TString absetaTag("Trg_absetadep");
TString centTag("Trg_centdep");
const int nAbsEtaBins = 4;
TString ptTag[nAbsEtaBins] = { "Trg_pt", "Trg_abseta00_12", "Trg_abseta12_18", "Trg_abseta18_24" };
TString allTag("Trg_1bin");
TString absetaVar("abseta");
TString centVar("tag_hiBin");
ofstream file_sfs(outputTag + "correction_functions.txt");
ofstream file_Eta(outputTag + "EtaValues_Trg.txt");
ofstream file_Cent(outputTag + "CentValues_Trg.txt");
ofstream file_TestErr(outputTag + "Trg_ExpErr.txt");
ofstream file_binnedsfs(outputTag +"correction_binned.txt");
TString treeTag("tpTree");
TString cutLegend("DoubleMuOpen");
const double effmin = 0.;
const double sfrange = 0.35;
const char* fDataName[nSyst] = { "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_DoubleMuOpen_cbPlusPol1.root"};/*, 
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_DoubleMuOpen_cbGausPlusPol1.root",
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_DoubleMuOpen_cbPlusPol2.root",
				 "../test/jpsiHI/Output/Trg/tnp_Ana_RD_PbPb_Trg_DoubleMuOpen_mass2834.root"};*/
const char* fMCName[nSyst] = { "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_DoubleMuOpen_cbPlusPol1.root"};/*,
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_DoubleMuOpen_cbGausPlusPol1.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_DoubleMuOpen_cbPlusPol2.root",
			       "../test/jpsiHI/Output/Trg/tnp_Ana_MC_PbPb_Trg_DoubleMuOpen_mass2834.root"};*/
int fitfcn = 1;
#endif

#ifdef STA
const int nSyst = 1;
const char* systName[nSyst] = {
  "nominal"};
TString outputTag = "Effplots/Sta/";
TString etaTag("STA_eta");
TString absetaTag("STA_abseta");
TString centTag("STA_centdep");
const int nAbsEtaBins = 4;
TString ptTag[nAbsEtaBins] = { "STA_pt", "STA_abseta00_12", "STA_abseta12_21", "STA_abseta21_24" };
TString allTag("STA_1bin");
TString absetaVar("abseta");
TString centVar("tag_hiBin");
ofstream file_sfs(outputTag + "correction_functions.txt");
ofstream file_Eta(outputTag + "EtaValues_Sta.txt");
ofstream file_Cent(outputTag + "CentValues_Sta.txt");
ofstream file_binnedsfs(outputTag +"correction_binned.txt");
TString treeTag("tpTreeTrk");
TString cutLegend("Standalone");
const double effmin = 0.7;
const double sfrange = 0.2;
const char* fDataName[nSyst] = { "../test/jpsiHI/Output/Sta/tnp_Ana_RD_PbPb_STA_twoGausPlusPol1.root" };
const char* fMCName[nSyst] = { "../test/jpsiHI/Output/Sta/tnp_Ana_MC_PbPb_STA_twoGausPlusPol1.root" };
int fitfcn = 1;
#endif

#ifdef TRK
const int nSyst = 4;
const char* systName[nSyst] = {
  "nominal",
  "signal syst",
  "bkg syst",
  "mass range syst"};
TString outputTag = "Effplots/Trk/";
TString etaTag("Trk_etadep");
TString absetaTag("Trk_absetadep");
TString centTag("Trk_centdep");
const int nAbsEtaBins = 5;
TString ptTag[nAbsEtaBins] = {"Trk_pt", "Trk_abseta00_12", "Trk_abseta12_18", "Trk_abseta18_21", "Trk_abseta21_24" };
TString allTag("Trk_1bin");
TString absetaVar("abseta");
TString centVar("tag_hiBin");
ofstream file_sfs(outputTag + "correction_functions.txt");
ofstream file_Eta(outputTag + "EtaValues_Trk.txt");
ofstream file_Cent(outputTag + "CentValues_Trk.txt");
ofstream file_binnedsfs(outputTag +"correction_binned.txt");
TString treeTag("tpTreeSta");
TString cutLegend("Inner tracking");
const double effmin = 0.6;
const double sfrange = 0.0199;
const char* fDataName[nSyst] = { "../test/jpsiHI/Output/Trk/tnp_Ana_RD_PbPb_Trk_twoGausPlusPol2.root",
				 "../test/jpsiHI/Output/Trk/tnp_Ana_RD_PbPb_Trk_GausPlusPol2.root",
				 "../test/jpsiHI/Output/Trk/tnp_Ana_RD_PbPb_Trk_twoGausPlusPol3.root",
				 "../test/jpsiHI/Output/Trk/tnp_Ana_RD_PbPb_Trk_mass2347.root" };
const char* fMCName[nSyst] = { "../test/jpsiHI/Output/Trk/tnp_Ana_MC_PbPb_Trk_twoGausPlusPol2.root",
			       "../test/jpsiHI/Output/Trk/tnp_Ana_MC_PbPb_Trk_GausPlusPol2.root",
			       "../test/jpsiHI/Output/Trk/tnp_Ana_MC_PbPb_Trk_twoGausPlusPol3.root",
			       "../test/jpsiHI/Output/Trk/tnp_Ana_MC_PbPb_Trk_mass2347.root" };
int fitfcn = 1;
#endif

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
void TnPEffDraw_singleFile_Bat() {

  gSystem->mkdir("Effplots");
  if (outputTag.Contains("Trg")) gSystem->mkdir("Effplots/Trg");
  gSystem->mkdir(outputTag);
  gSystem->mkdir(outputTag+"/root");
  gSystem->mkdir(outputTag+"/pdf");
  gSystem->mkdir(outputTag+"/png");

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

  // Loading the values for abseta bins
  vector<RooDataSet*> rds_absetaPtDep_MC[nSyst], rds_absetaPtDep_RD[nSyst];  

  for (int k = 0; k < nSyst; k++) {
    for (int i = 0; i < nAbsEtaBins; i++)
      {
	rds_absetaPtDep_MC[k].push_back((RooDataSet*)fMC[k]->Get(treeTag + "/" + ptTag[i] + "/fit_eff"));
	rds_absetaPtDep_RD[k].push_back((RooDataSet*)fData[k]->Get(treeTag + "/" + ptTag[i] + "/fit_eff"));
      }
  }

  vector<TGraphAsymmErrors*> ComPt_MC[nSyst], ComPt_RD[nSyst];

  //Loading the TGraphAsymmErrors for  abseta bins - 1 bin
  for (int k = 0; k < nSyst; k++) {
    for (unsigned int i = 0; i < rds_absetaPtDep_MC[k].size(); i++)
      {
	cout << k << " " << i << " " << rds_absetaPtDep_RD[k][i] << endl;
	cout <<"start MC 1"<<endl;
	ComPt_MC[k].push_back(plotEff_1bin(rds_absetaPtDep_MC[k][i], 1, "pt"));
	cout << k << " " << i << " " << rds_absetaPtDep_RD[k][i] << endl;
	cout <<"done with MC start RD 1"<<endl;
	ComPt_RD[k].push_back(plotEff_1bin(rds_absetaPtDep_RD[k][i], 1, "pt"));
      }
  }
  cout << "HERE1" << endl;

  //Loading the eta dependence
  RooDataSet* rds_eta_MC[nSyst];
  RooDataSet* rds_eta_RD[nSyst];

  for (int i = 0; i < nSyst; i++) {
    rds_eta_MC[i] = (RooDataSet*)fMC[i]->Get(treeTag + "/" + etaTag + "/fit_eff");
    rds_eta_RD[i] = (RooDataSet*)fData[i]->Get(treeTag + "/" + etaTag + "/fit_eff");
  }

  // Loading the TGraphAsymmErrors for  eta bins - 1 bin
  TGraphAsymmErrors* ComEta_MC[nSyst];
  TGraphAsymmErrors* ComEta_RD[nSyst];
  cout << "HERE1a" << endl;
  for (int i = 0; i < nSyst; i++) {
    ComEta_MC[i] = plotEff_1bin(rds_eta_MC[i], 1, "eta");
    ComEta_RD[i] = plotEff_1bin(rds_eta_RD[i], 1, "eta");
  }
  cout << "HERE1b" << endl;

  // Loading the other data sets
  RooDataSet* rds_bin0_MC[nSyst];
  RooDataSet* rds_bin0_RD[nSyst];
  RooDataSet* rds_abseta_MC[nSyst];
  RooDataSet* rds_abseta_RD[nSyst];
  RooDataSet* rds_cent_MC[nSyst];
  RooDataSet* rds_cent_RD[nSyst];

  for (int i = 0; i < nSyst; i++) {
    rds_bin0_MC[i] = (RooDataSet*)fMC[i]->Get(treeTag + "/" + allTag + "/fit_eff");
    rds_bin0_RD[i] = (RooDataSet*)fData[i]->Get(treeTag + "/" + allTag + "/fit_eff");
    rds_abseta_MC[i] = (RooDataSet*)fMC[i]->Get(treeTag + "/" + absetaTag + "/fit_eff");
    rds_abseta_RD[i] = (RooDataSet*)fData[i]->Get(treeTag + "/" + absetaTag + "/fit_eff");
    if (isPbPb) {
      rds_cent_MC[i] = (RooDataSet*)fMC[i]->Get(treeTag + "/" + centTag + "/fit_eff");
      rds_cent_RD[i] = (RooDataSet*)fData[i]->Get(treeTag + "/" + centTag + "/fit_eff");
    }
  }

  TGraphAsymmErrors* eff1bin_MC[nSyst];
  TGraphAsymmErrors* eff1bin_RD[nSyst];
  vector<TGraphAsymmErrors*> effAbsEta_MC[nSyst];
  vector<TGraphAsymmErrors*> effAbsEta_RD[nSyst];
  TGraphAsymmErrors* effCentMC = NULL;
  TGraphAsymmErrors* effCentData = NULL;
  cout << "HERE2" << endl;
  
  for (int k = 0; k < nSyst; k++) {
    eff1bin_MC[k] = plotEff_1bin(rds_bin0_MC[k], 0, "eta");
    eff1bin_RD[k] = plotEff_1bin(rds_bin0_RD[k], 0, "eta");
    cout <<"start MC"<<endl;
    effAbsEta_MC[k] = plotEff_Nbins(rds_abseta_MC[k], 0, "pt", absetaVar);
    cout <<"done with MC start RD"<<endl;
    effAbsEta_RD[k] = plotEff_Nbins(rds_abseta_RD[k], 0, "pt", absetaVar);
    if (isPbPb && k == 0) {
      cout <<"start centrality dependence for MC"<<endl;
      effCentMC = plotEff_1bin(rds_cent_MC[k], 0, centVar);
      cout <<"start centrality dependence for RD"<<endl;
      effCentData = plotEff_1bin(rds_cent_RD[k], 0, centVar);
    }
  }
  
  cout << endl<< "Loading of roo data sets and efficiencies done " << endl << endl;

  // loading done, set style
    if (isPbPb) {
    effCentMC->SetMarkerStyle(20);
    effCentMC->SetMarkerSize(1.4);
    effCentMC->SetMarkerColor(kRed + 1);
    effCentMC->SetLineColor(kRed + 1);
    effCentData->SetMarkerStyle(25);
    effCentData->SetMarkerSize(1.4);
    effCentData->SetMarkerColor(kBlue + 1);
    effCentData->SetLineColor(kBlue + 1);
  }
  
  int nbins_abseta = ComPt_MC[0].size();
  for (int k = 0; k < nSyst; k++)
    {
      for (int i = 0; i < nbins_abseta; i++)
	{
	  ComPt_MC[k][i]->SetMarkerStyle(20);
	  ComPt_MC[k][i]->SetMarkerSize(1.4);
	  ComPt_MC[k][i]->SetMarkerColor(kRed + 1);
	  ComPt_MC[k][i]->SetLineColor(kRed + 1);
	  ComPt_RD[k][i]->SetMarkerStyle(25);
	  ComPt_RD[k][i]->SetMarkerSize(1.4);
	  ComPt_RD[k][i]->SetMarkerColor(kBlue + 1);
	  ComPt_RD[k][i]->SetLineColor(kBlue + 1);
	}

      ComEta_MC[k]->SetMarkerStyle(20);
      ComEta_MC[k]->SetMarkerSize(1.4);
      ComEta_MC[k]->SetMarkerColor(kRed + 1);
      ComEta_MC[k]->SetLineColor(kRed + 1);
      ComEta_RD[k]->SetMarkerStyle(25);
      ComEta_RD[k]->SetMarkerSize(1.4);
      ComEta_RD[k]->SetMarkerColor(kBlue + 1);
      ComEta_RD[k]->SetLineColor(kBlue + 1);
    }

  ////////////////// get some averages

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
    /*
    CalEffErr(eff1bin_MC[k], Trk0[k]);
    CalEffErr(eff1bin_RD[k], Trk1[k]);
    CalEffErr(effAbsEta_MC[k], TrkAbsEta0[k]);
    CalEffErr(effAbsEta_RD[k], TrkAbsEta1[k]);*/
  }

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
  TH1F *hPad1 = new TH1F("hPad1", ";#eta^{#mu};Single #mu Efficiency", 5, -2.4, 2.4);
  TH1F *hPad2 = new TH1F("hPad2", ";Centrality - hiBin ;Single #mu Efficiency", 5, 0, c_centralityRange);
  hPad->GetXaxis()->CenterTitle();
  hPad1->GetXaxis()->CenterTitle();
  hPad2->GetXaxis()->CenterTitle();
  hPad->GetXaxis()->SetLabelSize(0.05);
  hPad->GetXaxis()->SetTitleSize(0.05);
  hPad->GetXaxis()->SetTitleOffset(1.2);
  hPad->GetYaxis()->SetLabelSize(0.05);
  hPad->GetYaxis()->SetTitleSize(0.05);
  hPad->GetYaxis()->SetTitleOffset(1.);
  hPad1->GetXaxis()->SetLabelSize(0.05);
  hPad1->GetXaxis()->SetTitleSize(0.05);
  hPad1->GetXaxis()->SetTitleOffset(1.2);
  hPad1->GetYaxis()->SetLabelSize(0.05);
  hPad1->GetYaxis()->SetTitleSize(0.05);
  hPad1->GetYaxis()->SetTitleOffset(1.);
  hPad2->GetXaxis()->SetLabelSize(0.);
  hPad2->GetXaxis()->SetTitleSize(0.);
  hPad2->GetXaxis()->SetTitleOffset(1.2);
  hPad2->GetYaxis()->SetLabelSize(0.05);
  hPad2->GetYaxis()->SetTitleSize(0.05);
  hPad2->GetYaxis()->SetTitleOffset(1.);


  hPad->GetYaxis()->SetRangeUser(effmin, 1.05);
  hPad1->GetYaxis()->SetRangeUser(effmin, 1.05);
  hPad2->GetYaxis()->SetRangeUser(effmin, 1.05);

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
  TH1F *hPadr_syst = (TH1F*)hPadr->Clone("hPadr_syst");hPadr_syst->GetYaxis()->SetRangeUser(1. - sfrange, 1. + sfrange);
  TH1F *hPad_syst = (TH1F*)hPad->Clone("hPad_syst");
  TH1F *hPad1r = (TH1F*)hPad1->Clone("hPad1r"); hPad1r->GetYaxis()->SetRangeUser(1. - sfrange, 1. + sfrange);
  hPad1r->GetYaxis()->SetTitle("Scale Factor");
  hPad1r->GetXaxis()->SetTitleSize(tsize);
  hPad1r->GetXaxis()->SetLabelSize(tsize);
  hPad1r->GetYaxis()->SetTitleSize(tsize);
  hPad1r->GetYaxis()->SetLabelSize(tsize);
  hPad1r->GetYaxis()->SetNdivisions(504, kTRUE);
  TH1F *hPad1r_syst = (TH1F*)hPad1r->Clone("hPad1r_syst");hPad1r_syst->GetYaxis()->SetRangeUser(1. - sfrange, 1. + sfrange);
  TH1F *hPad1_syst = (TH1F*)hPad1->Clone("hPad1_syst");
  TH1F *hPad2r = (TH1F*)hPad2->Clone("hPad2r"); hPad2r->GetYaxis()->SetRangeUser(1. - sfrange, 1. + sfrange);
  hPad2r->GetYaxis()->SetTitle("Scale Factor");
  hPad2r->GetXaxis()->SetTitleSize(tsize);
  hPad2r->GetXaxis()->SetLabelSize(tsize);
  hPad2r->GetYaxis()->SetTitleSize(tsize);
  hPad2r->GetYaxis()->SetLabelSize(tsize);
  hPad2r->GetYaxis()->SetNdivisions(504, kTRUE);

  pad1->cd();

  // draw pt dependence in abseta bins 
  TString header;
  for (int i = 0; i < nbins_abseta; i++)
    {
      TF1 *fdata = NULL;
      TF1 *fmc = NULL;
      double ptmin, ptmax;

      for (int k = 0; k < nSyst; k++)
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
	  ptmin = ((RooRealVar*)rds_absetaPtDep_MC[k][i]->get()->find("pt"))->getBinning().binLow(0);
	  double etamin, etamax;
	  if (rds_absetaPtDep_MC[k][i]->get()->find("abseta"))
	    {
	      etamin = ((RooRealVar*)rds_absetaPtDep_MC[k][i]->get()->find("abseta"))->getBinning().binLow(0);
	      etamax = ((RooRealVar*)rds_absetaPtDep_MC[k][i]->get()->find("abseta"))->getBinning().binHigh(0);
	      header = TString("#splitline{") + cutLegend + Form(" Efficiency}{(p^{#mu}_{T}>%.1f, |#eta| #in [%.1f, %.1f])}", ptmin, etamin, etamax);
	    }
	  else
	    {
	      etamin = ((RooRealVar*)rds_absetaPtDep_MC[k][i]->get()->find("eta"))->getBinning().binLow(0);
	      etamax = ((RooRealVar*)rds_absetaPtDep_MC[k][i]->get()->find("eta"))->getBinning().binHigh(0);
	      header = TString("#splitline{") + cutLegend + Form(" Efficiency}{(p^{#mu}_{T}>%.1f, #eta #in [%.1f, %.1f])}", ptmin, etamin, etamax);
	    }
	  leg1->SetHeader(header);
	  //sprintf(legs, "MC PYTHIA+HYDJET: %.4f^{ + %.3f}_{ - %.3f}", TrkAbsEta0[k][i][0], TrkAbsEta0[k][i][1], TrkAbsEta0[k][i][2]);
	  sprintf(legs, "MC PYTHIA+HYDJET");
	  leg1->AddEntry(ComPt_MC[k][i], legs, "pl");
	  //sprintf(legs, "Data: %.4f^{ + %.3f}_{ - %.3f}", TrkAbsEta1[k][i][0], TrkAbsEta1[k][i][1], TrkAbsEta1[k][i][2]);
	  sprintf(legs, "Data");
	  leg1->AddEntry(ComPt_RD[k][i], legs, "pl");
	  leg1->Draw("same");

	  ComPt_MC[k][i]->Draw("pz same");
	  ComPt_RD[k][i]->Draw("pz same");

	  lt1->SetTextSize(0.05);
	  lt1->DrawLatex(0.20, 0.30, "CMS Preliminary");
	  //lt1->DrawLatex(0.20, 0.24, collTag + "  #sqrt{s_{NN}} = 8.16 TeV");
	  lt1->DrawLatex(0.20, 0.24, collTag + "  #sqrt{s_{NN}} = 5.02 TeV");

	  // now take care of the data/mc ratio panel
	  c1->cd();
	  // pad2->SetFrameFillStyle(4000);
	  pad2->Draw();
	  pad2->cd();
	  hPadr->Draw();

	  int nbins_mc = ComPt_MC[k][i]->GetN();
	  int nbins = ComPt_RD[k][i]->GetN();
	  double *xr = new double[nbins];
	  double *yr = new double[nbins];
	  double *xrlo = new double[nbins];
	  double *yrlo = new double[nbins];
	  double *xrhi = new double[nbins];
	  double *yrhi = new double[nbins];

	  TGraphAsymmErrors* ComPt0_forRatio = NULL;
	  if (nbins_mc == nbins) {
	    ComPt0_forRatio = ComPt_MC[k][i];
	  }
	  else {
	    double* tntot = new double[nbins_mc];
	    TString tag = absetaVar + "_bin0__pt_bin";
	    for (int j = 0; j < nbins_mc; j++) {
	      RooFitResult *fitres = NULL;
	      // Loop on the directories to find the one we are looking for
	      TDirectory *tdir = (TDirectory*)fMC[0]->Get(treeTag + "/" + ptTag[i]);
	      TIter next(tdir->GetListOfKeys()); TObject *obj;
	      while ((obj = next())) {
		obj = ((TKey*)obj)->ReadObj();
		if (TString(obj->ClassName()) != "TDirectoryFile") continue;
		if (TString(obj->GetName()).Contains(Form("__pt_bin%i", j))) { tdir = (TDirectory*)obj; break; }
	      }

	      fitres = (RooFitResult*)tdir->Get("fitresults");
	      if (!fitres) cerr << "ERROR I couldn't find the fit results! Expect a crash soon..." << endl;
	      tntot[j] = ((RooRealVar*)fitres->floatParsFinal().find("numTot"))->getVal() * (((RooRealVar*)fitres->floatParsFinal().find("fSigAll"))->getVal());
	      delete fitres;
	    }
	    ComPt0_forRatio = plotEff_1bin(rds_absetaPtDep_MC[k][i], 1, "pt", nbins_mc / nbins, tntot);
	    delete[] tntot;
	  }

	  // here we assume that the mc uncertainty is negligible compared to the data one: simply scale everything by the central value.
	  for (int j = 0; j < nbins; j++)
	    {
	      xr[j] = ComPt_RD[k][i]->GetX()[j];
	      xrlo[j] = ComPt_RD[k][i]->GetErrorXlow(j);
	      xrhi[j] = ComPt_RD[k][i]->GetErrorXhigh(j);
	      yr[j] = ComPt_RD[k][i]->GetY()[j] / ComPt0_forRatio->GetY()[j];
	      yrlo[j] = ComPt_RD[k][i]->GetErrorYlow(j) / ComPt0_forRatio->GetY()[j];
	      yrhi[j] = ComPt_RD[k][i]->GetErrorYhigh(j) / ComPt0_forRatio->GetY()[j];
	    }
	  TGraphAsymmErrors *gratio = new TGraphAsymmErrors(nbins, xr, yr, xrlo, xrhi, yrlo, yrhi);
	  gratio->SetMarkerStyle(20);
	  gratio->SetMarkerColor(kBlack);
	  gratio->SetMarkerSize(1.0);
	  gratio->SetLineColor(kBlack);
	  gratio->SetLineWidth(1);
	  gratio->Draw("pz same");

	  // save (nominal only)
	  if (k == 0) {
	    c1->SaveAs(outputTag + "root/" + treeTag + Form("Eff%i_", i) + collTag + "_RD_MC_PT.root");
	    c1->SaveAs(outputTag + "pdf/" + treeTag + Form("Eff%i_", i) + collTag + "_RD_MC_PT.pdf");
	    c1->SaveAs(outputTag + "png/" + treeTag + Form("Eff%i_", i) + collTag + "_RD_MC_PT.png");
	  }

	  cout << "Done with the first part of abseta fitting" << endl;
	  
	  // in case we are looking at muon Id + trigger: get the scale factor at the same time
#if defined MUIDTRG || defined STA || defined MUID || defined TRG || defined TRGL2JPSI || defined TRGL3JPSI || defined TRGL2UPSI || defined TRGL3UPSI || defined TRGDMOPEN
	  pad1->cd();
	  ptmax = ((RooRealVar*)rds_absetaPtDep_MC[k][i]->get()->find("pt"))->getMax();
	  TLatex tchi; tchi.SetNDC();
	  tchi.SetTextSize(0.035);
	  double chi2, pval; int dof;

	  if (k == 0) {
	    // fit data
	    fdata = initfcn("fdata", fitfcn, ptmin, ptmax, 0.9);// ComPt_RD[k][i]->GetX()[ComPt_RD[k][i]->GetN() - 1]);
	    fdata->SetLineWidth(2);
	    fdata->SetLineColor(kBlue);
	    /*ComPt_RD[k][i]->Fit(fdata, "RME");
	      leg1->AddEntry(fdata, formula(fdata), "pl");

	      chi2 = ComPt_RD[k][i]->Chisquare(fdata);
	      dof = ComPt_RD[k][i]->GetN() - fdata->GetNpar();
	      pval = TMath::Prob(chi2, dof);
	      tchi.SetTextColor(kBlue);
	      tchi.DrawLatex(0.6, 0.92, Form("#chi^{2}/dof = %.1f/%d (p-value: %.2f)", chi2, dof, pval));*/

	    // in the case of the exponential fall at high pt, do the fit first without it
	    if (fitfcn == 2) {  //O: check whether not better to be removed
	    fdata->FixParameter(4, 0);
	    //ComPt_RD[k][i]->Fit(fdata, "RME");
	    fdata->SetParLimits(4, -1.5, 0);
	    }
	    //ComPt_RD[k][i]->Fit(fdata, "RME");

	    // fit mc
	    //fmc = (TF1*)fdata->Clone("fmc");
	    fmc = initfcn("fmc", fitfcn, ptmin, ptmax, 0.9);
	    // Initialize the normalization to the efficiency in the last point
	    //if (isPbPb) fmc->SetParameters(ComPt_MC[k][i]->GetX()[ComPt_MC[k][i]->GetN() - 1], 0.5, 2.5);
	    //else fmc->SetParameters(ComPt_MC[k][i]->GetX()[ComPt_MC[k][i]->GetN() - 1], 2.2, 1.5);
	    fmc->SetLineColor(kRed);
	    //ComPt_MC[k][i]->Fit(fmc, "WRME");
	    //ComPt_MC[k][i]->Fit(fmc, "RME");



	    //Errors on exponential
	    //file_TestErr << "RD value: " << fdata->GetParameter(4) << endl;
	    //file_TestErr << "RD error: " << fdata->GetParError(4) << endl;
	    //file_TestErr << "RD Sigma away from 0: " << 0-(fdata->GetParameter(4) / fdata->GetParError(4)) << endl<<endl;

	    //file_TestErr << "MC value: " << fmc->GetParameter(4)<<endl;
	    //file_TestErr << "MC error: " << fmc->GetParError(4) << endl;
	    //file_TestErr << "MC Sigma away from 0: " << 0-(fmc->GetParameter(4)/fmc->GetParError(4)) << endl<<endl<<endl;

	    //draw


	    leg1->AddEntry(fmc, formula(fmc,5), "pl");
	    leg1->AddEntry(fdata, formula(fdata,5), "pl");

	    chi2 = ComPt_RD[k][i]->Chisquare(fdata);
	    dof = ComPt_RD[k][i]->GetN() - fdata->GetNpar();
	    pval = TMath::Prob(chi2, dof);
	    tchi.SetTextColor(kBlue);
	    //tchi.DrawLatex(0.6, 0.92, Form("#chi^{2}/dof = %.1f/%d (p-value: %.2f)", chi2, dof, pval));


	    chi2 = ComPt_MC[k][i]->Chisquare(fmc);
	    dof = ComPt_MC[k][i]->GetN() - fmc->GetNpar();
	    pval = TMath::Prob(chi2, dof);
	    tchi.SetTextColor(kRed);
	    //tchi.DrawLatex(0.6, 0.88, Form("#chi^{2}/dof = %.1f/%d (p-value: %.2f)", chi2, dof, pval));

	    leg1->Draw();

	    // now the bottom panel
	    pad2->cd();
	    // hPadr->Draw();
	    TF1 *fratio = ratiofunc("fratio", fdata, fmc);
	    fratio->Draw("same");

	    chi2 = gratio->Chisquare(fratio);
	    dof = gratio->GetN() - fratio->GetNpar() / 2;
	    pval = TMath::Prob(chi2, dof);
	    tchi.SetTextColor(kBlack);
	    tchi.SetTextSize(0.035*0.7 / 0.3);
	    //tchi.DrawLatex(0.6, 0.8, Form("#chi^{2}/dof = %.1f/%d (p-value: %.2f)", chi2, dof, pval));

	    // save (nominal only)
	    c1->SaveAs(outputTag + "root/" + treeTag + Form("SF%i_", i) + collTag + "_RD_MC_PT.root");
	    c1->SaveAs(outputTag + "pdf/" + treeTag + Form("SF%i_", i) + collTag + "_RD_MC_PT.pdf");
	    c1->SaveAs(outputTag + "png/" + treeTag + Form("SF%i_", i) + collTag + "_RD_MC_PT.png");

	    // print the fit results to file
	    file_sfs << "Data " << etamin << " " << etamax << endl;
	    file_sfs << formula(fdata, 5) << endl;
	    file_sfs << "MC " << etamin << " " << etamax << endl;
	    file_sfs << formula(fmc, 5) << endl;
	    file_sfs << endl;

	    // print the binned ratio to the other file only for the eta binned pt dependant corrections
	    if (etamin>=0){
	      file_binnedsfs << "// SF for " << etamin << " < |eta| < " << etamax << endl;
	      
	      file_binnedsfs <<"if (fabs(eta) >= "<< etamin <<" && fabs(eta) < "<< etamax <<") {"<<endl;
	      for (int j = 0; j<ComPt_RD[k][i]->GetN(); j++) {
		if (j>0) file_binnedsfs << "else ";
		if (j==ComPt_RD[k][i]->GetN()-1) 
		  file_binnedsfs << "{num = " << ComPt_RD[k][i]->GetY()[j] << ";" << " den = " << ComPt_MC[k][i]->GetY()[j] << "; statUp = "<< ComPt_RD[k][i]->GetEYhigh()[j] <<"; statDown = "<<ComPt_RD[k][i]->GetEYlow()[j]<< ";}" << endl;
		else
		  file_binnedsfs << "if (x >= "<< ComPt_RD[k][i]->GetX()[j] - ComPt_RD[k][i]->GetEXlow()[j] << " && x <" << ComPt_RD[k][i]->GetX()[j] + ComPt_RD[k][i]->GetEXhigh()[j] << ") {num = " << ComPt_RD[k][i]->GetY()[j] << ";" << " den = " << ComPt_MC[k][i]->GetY()[j] << "; statUp = "<< ComPt_RD[k][i]->GetEYhigh()[j] <<"; statDown = "<<ComPt_RD[k][i]->GetEYlow()[j]<<";}" <<endl;
	      }
	      file_binnedsfs << "}"<< endl;
	      /*
	      file_binnedsfs << "// MC for " << etamin << " < |eta| < " << etamax << endl;
	      file_binnedsfs <<"if (fabs(eta) >= "<< etamin <<" && fabs(eta) < "<< etamax <<") {"<<endl;
	      for (int j = 0; j<ComPt_MC[k][i]->GetN(); j++) {
		if (j>0) file_binnedsfs << "else ";
		if (j==ComPt_MC[k][i]->GetN()-1)
		  file_binnedsfs << "den = " << ComPt_MC[k][i]->GetY()[j] << ";" << endl;
		else
                file_binnedsfs << "if (pt<" << ComPt_MC[k][i]->GetX()[j] + ComPt_MC[k][i]->GetEXhigh()[j] << ") den = " << ComPt_MC[k][i]->GetY()[j] << ";" << endl;
	      }
	      file_binnedsfs << "}"<< endl; */
	    }
	  }
	}
      // plot systematics //still abseta
      TGraphAsymmErrors *graphssyst_data[nSyst];
      //data
      for (int k = 0; k < nSyst; k++) graphssyst_data[k] = ComPt_RD[k][i];
      plotSysts(graphssyst_data, c1, pad1, hPad_syst, pad2, hPadr_syst, header, Form("syst_data_pt_%i", i));
      //mc
      TGraphAsymmErrors *graphssyst_mc[nSyst];
      for (int k = 0; k < nSyst; k++) graphssyst_mc[k] = ComPt_MC[k][i];
      plotSysts(graphssyst_mc, c1, pad1, hPad_syst, pad2, hPadr_syst, header, Form("syst_mc_pt_%i", i));

      // toys study 
      if (doToys) toyStudy(nSyst, graphssyst_data, graphssyst_mc, fdata, fmc, treeTag + Form("toys%i_", i) + collTag + "_RD_MC_PT", 0);
      cout << "SURVIVED SO FAR" << endl;
#else
    }
#endif // ifdef MUIDTRG or STA or TRG
}

//---------- This is for eta dependence
TLegend *leg1 = new TLegend(0.43, 0.05, 0.66, 0.26);
TLatex *lt1 = new TLatex();
for (int k = 0; k < nSyst; k++)
  {
    pad1->cd();
    hPad1->Draw();

    ComEta_MC[k]->Draw("pz same");
    ComEta_RD[k]->Draw("pz same");

    lt1->SetNDC();
    char legs[512];
    leg1->SetFillStyle(0);
    leg1->SetFillColor(0);
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.035);
    double ptmin = ((RooRealVar*)rds_eta_MC[k]->get()->find("pt"))->getBinning().binLow(0);
    leg1->SetHeader(TString("#splitline{") + cutLegend + Form(" Efficiency}{(p^{#mu}_{T}>%.1f)}", ptmin));
    //sprintf(legs, "MC PYTHIA+HYDJET: %.4f^{ + %.3f}_{ - %.3f}", Trk0[k][0], Trk0[k][1], Trk0[k][2]);
    sprintf(legs, "MC PYTHIA+HYDJET");
    leg1->AddEntry(ComPt_MC[k][0], legs, "pl");
    //sprintf(legs, "Data: %.4f^{ + %.3f}_{ - %.3f}", Trk1[k][0], Trk1[k][1], Trk1[k][2]);
    sprintf(legs, "Data");
    leg1->AddEntry(ComPt_RD[k][0], legs, "pl");
    leg1->Draw("same");
    leg1->Draw("same");

    lt1->SetTextSize(0.05);
    lt1->DrawLatex(0.43, 0.40, "CMS Preliminary");
    lt1->DrawLatex(0.43, 0.34, collTag + "  #sqrt{s_{NN}} = 5.02 TeV");
    //lt1->DrawLatex(0.43, 0.34, collTag + "  #sqrt{s_{NN}} = 8.16 TeV");

    // now take care of the data/mc ratio panel
    c1->cd();
    // pad2->SetFrameFillStyle(4000);
    pad2->Draw();
    pad2->cd();
    hPad1r->Draw();

    int nbins = ComEta_MC[k]->GetN();
    double *xr = new double[nbins];
    double *yr = new double[nbins];
    double *xrlo = new double[nbins];
    double *yrlo = new double[nbins];
    double *xrhi = new double[nbins];
    double *yrhi = new double[nbins];

    // here we assume that the mc uncertainty is negligible compared to the data one: simply scale everything by the central value.
    for (int j = 0; j < nbins; j++)
      {
	xr[j] = ComEta_RD[k]->GetX()[j];
	xrlo[j] = ComEta_RD[k]->GetErrorXlow(j);
	xrhi[j] = ComEta_RD[k]->GetErrorXhigh(j);
	yr[j] = ComEta_RD[k]->GetY()[j] / ComEta_MC[k]->GetY()[j];
	yrlo[j] = ComEta_RD[k]->GetErrorYlow(j) / ComEta_MC[k]->GetY()[j];
	yrhi[j] = ComEta_RD[k]->GetErrorYhigh(j) / ComEta_MC[k]->GetY()[j];
      }
    TGraphAsymmErrors *gratio1 = new TGraphAsymmErrors(nbins, xr, yr, xrlo, xrhi, yrlo, yrhi);
    gratio1->SetMarkerStyle(20);
    gratio1->SetMarkerColor(kBlack);
    gratio1->SetMarkerSize(1.0);
    gratio1->SetLineColor(kBlack);
    gratio1->SetLineWidth(1);
    gratio1->Draw("pz same");

    if (k == 0) {
      c1->SaveAs(outputTag + "root/" + treeTag + "Eff_" + collTag + "_RD_MC_Eta.root");
      c1->SaveAs(outputTag + "pdf/" + treeTag + "Eff_" + collTag + "_RD_MC_Eta.pdf");
      c1->SaveAs(outputTag + "png/" + treeTag + "Eff_" + collTag + "_RD_MC_Eta.png");


      // print the eta dependence to file
      double xVal, yVal, ErrDown, ErrUp;
      file_Eta << "//SF in eta bins" << endl;
      //file_Eta << "Eta Value ErrDown ErrUp" << endl;
      for (int bin = 0; bin < ComEta_RD[k]->GetN(); bin++)
	{
	  ComEta_RD[k]->GetPoint(bin, xVal, yVal);
	  ErrDown = ComEta_RD[k]->GetErrorYlow(bin);
	  ErrUp = ComEta_RD[k]->GetErrorYhigh(bin);
	  //file_Eta << xVal << " " << yVal << " " << ErrDown << " " << ErrUp << endl;
	  file_Eta <<"if (x >= " <<(ComEta_RD[k]->GetX()[bin])-(ComEta_RD[k]->GetErrorXlow(bin));
	  file_Eta << " && x < "<<(ComEta_RD[k]->GetX()[bin])+(ComEta_RD[k]->GetErrorXhigh(bin));
	  file_Eta <<") {num = " << yVal <<";";
	  ComEta_MC[k]->GetPoint(bin, xVal, yVal);
	  file_Eta <<" den = " << yVal<<";";
	  file_Eta <<" statUp = " <<ComEta_RD[k]->GetErrorYhigh(bin)<<"; statDown = "<<ComEta_RD[k]->GetErrorYlow(bin)<<";}"<< endl;
	}
      /*
      file_Eta << endl << endl << "//MC " << endl << endl;
      //file_Eta << "Eta Value ErrDown ErrUp" << endl;
      for (int bin = 0; bin < ComEta_MC[k]->GetN(); bin++)
	{
	  ComEta_MC[k]->GetPoint(bin, xVal, yVal);
	  ErrDown = ComEta_MC[k]->GetErrorYlow(bin);
	  ErrUp = ComEta_MC[k]->GetErrorYhigh(bin);
	  //file_Eta << xVal << " " << yVal << " " << ErrDown << " " << ErrUp << endl;
	  file_Eta <<"if (eta >= " <<(ComEta_MC[k]->GetX()[bin])-(ComEta_MC[k]->GetErrorXlow(bin));
	  file_Eta << " && eta < "<<(ComEta_MC[k]->GetX()[bin])+(ComEta_MC[k]->GetErrorXhigh(bin));
	  file_Eta <<") den = " << yVal <<";"<< endl;
	}
      */
      file_Eta.close();
    }
  }

// plot systematics
//data
plotSysts(ComEta_RD, c1, pad1, hPad1_syst, pad2, hPad1r_syst, header, "syst_data_eta");
//mc
plotSysts(ComEta_MC, c1, pad1, hPad1_syst, pad2, hPad1r_syst, header, "syst_mc_eta");

//-------- This is for centrality dependence
if (isPbPb) {
  pad1->cd();
  hPad2->Draw();

  effCentMC->Draw("pz same");
  effCentData->Draw("pz same");

  leg1->Draw("same");

  lt1->SetTextSize(0.05);
  lt1->DrawLatex(0.43, 0.45, "CMS Preliminary");
  lt1->DrawLatex(0.43, 0.39, collTag + "  #sqrt{s_{NN}} = 5.02 TeV");
  //lt1->DrawLatex(0.43, 0.39, collTag + "  #sqrt{s_{NN}} = 8.16 TeV");

  // now take care of the data/mc ratio panel
  c1->cd();
  // pad2->SetFrameFillStyle(4000);
  pad2->Draw();
  pad2->cd();
  hPad2r->Draw();

  int nbins2 = effCentMC->GetN();
  double* xr2 = new double[nbins2];
  double* yr2 = new double[nbins2];
  double* xr2lo = new double[nbins2];
  double* yr2lo = new double[nbins2];
  double* xr2hi = new double[nbins2];
  double* yr2hi = new double[nbins2];

  // here we assume that the mc uncertainty is negligible compared to the data one: simply scale everything by the central value.
  for (int j = 0; j < nbins2; j++)
    {
      xr2[j] = effCentData->GetX()[j];
      xr2lo[j] = effCentData->GetErrorXlow(j);
      xr2hi[j] = effCentData->GetErrorXhigh(j);
      yr2[j] = effCentData->GetY()[j] / effCentMC->GetY()[j];
      yr2lo[j] = effCentData->GetErrorYlow(j) / effCentMC->GetY()[j];
      yr2hi[j] = effCentData->GetErrorYhigh(j) / effCentMC->GetY()[j];
    }
  TGraphAsymmErrors *gratio2 = new TGraphAsymmErrors(nbins2, xr2, yr2, xr2lo, xr2hi, yr2lo, yr2hi);
  gratio2->SetMarkerStyle(20);
  gratio2->SetMarkerColor(kBlack);
  gratio2->SetMarkerSize(1.0);
  gratio2->SetLineColor(kBlack);
  gratio2->SetLineWidth(1);
  gratio2->Draw("pz same");

  c1->SaveAs(outputTag + "root/" + treeTag + "Eff_" + collTag + "_RD_MC_Cent.root");
  c1->SaveAs(outputTag + "pdf/" + treeTag + "Eff_" + collTag + "_RD_MC_Cent.pdf");
  c1->SaveAs(outputTag + "png/" + treeTag + "Eff_" + collTag + "_RD_MC_Cent.png");

  // print the centrality dependence to file
  double xVal, yVal, ErrDown, ErrUp;
  file_Cent << "Data " << endl << endl;
  file_Cent << "Centrality Value ErrDown ErrUp" << endl;
  for (int bin = 0; bin < effCentData->GetN(); bin++)
    {
      effCentData->GetPoint(bin, xVal, yVal);
      ErrDown = effCentData->GetErrorYlow(bin);
      ErrUp = effCentData->GetErrorYhigh(bin);
      file_Cent << xVal << " " << yVal << " " << ErrDown << " " << ErrUp << endl;
    }

  file_Cent << endl << endl << "MC " << endl << endl;
  file_Cent << "Centrality Value ErrDown ErrUp" << endl;
  for (int bin = 0; bin < effCentMC->GetN(); bin++)
    {
      effCentMC->GetPoint(bin, xVal, yVal);
      ErrDown = effCentMC->GetErrorYlow(bin);
      ErrUp = effCentMC->GetErrorYhigh(bin);
      file_Cent << xVal << " " << yVal << " " << ErrDown << " " << ErrUp << endl;
    }
  file_Cent.close();
 }


file_sfs.close();
file_binnedsfs.close();
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
  cout << nbins << " " << nbins2 << endl;

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

  cout<<"NBins pt: "<<nbins<<endl;

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

  //compute the syst errors
  ofstream file_syst(outputTag + tag + ".txt");
  file_syst << "// syst uncertainties" << endl;
  for (int j = 0; j < nbins; j++)
    {
      double maxdiff =-1;
      for (int k = 1; k < nSyst; k++){
	double diff = fabs(graphs[k]->GetY()[j] - ComPt0_forRatio->GetY()[j]);
	if (diff>maxdiff) maxdiff = diff;
      }
      if (j>0) file_syst <<"else ";
      if (j<nbins-1)
	file_syst << "if (x >= " << ComPt0_forRatio->GetX()[j] - ComPt0_forRatio->GetEXlow()[j] <<" && x < "<< ComPt0_forRatio->GetX()[j] + ComPt0_forRatio->GetEXhigh()[j] << ") syst = " << maxdiff <<";"<<endl;
      else 
	file_syst << "syst = " << maxdiff <<";"<<endl;
    }
  file_syst.close();
  // save
  c1->SaveAs(outputTag + "root/" + tag + ".root");
  c1->SaveAs(outputTag + "pdf/" + tag + ".pdf");
  c1->SaveAs(outputTag + "png/" + tag + ".png");
}

TF1 *initfcn(const char* fname, int ifcn, double ptmin, double ptmax, double effguess) {
  TString formula;
  if (ifcn == 0) formula = "[0]*TMath::Erf((x-[1])/[2])";
  else if (ifcn == 1) formula = "[0]*TMath::Erf((x-[1])/[2])+[3]";
  else if (ifcn == 2) formula = "[0]*(TMath::Erf((x-[1])/[2])*TMath::Exp([4]*x)) + [3]";
  else if (ifcn == 3) formula = "[0]";
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
    //ans->SetParameters(effguess, 2., 1.0, 0.);
    ans->SetParameters(0.7, 2., 1.0, 0.);
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
