#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"

using namespace std;

// Just creates a branch with normalised weights (so the number of events is conserved) and or a re-weighting factor due to the difference between the data and MC distributions
TF1* heta0(0x0);
TF1* heta1(0x0);
TF1* heta2(0x0);

void setWHistos()
{
  TFile* f0 = new TFile("tpTree_Weights_EtaBin0PbPb_nominal_RD_MC_PT.root");
  TFile* f1 = new TFile("tpTree_Weights_EtaBin1PbPb_nominal_RD_MC_PT.root");
  TFile* f2 = new TFile("tpTree_Weights_EtaBin2PbPb_nominal_RD_MC_PT.root");
  if (!f0 || !f1 || !f2)
  {
    cout << "ERROR no file with histos found" << endl;
    return;
  }
  
  heta0 = static_cast<TF1*>(f0->FindObjectAny("weightsFunction"));
  heta1 = static_cast<TF1*>(f1->FindObjectAny("weightsFunction"));
  heta2 = static_cast<TF1*>(f2->FindObjectAny("weightsFunction"));
  if (!heta0 || !heta1 || !heta2)
  {
    cout << "ERROR no histos found in file" << endl;
    return;
  }
}

double getDMCWeight(float pt,float abseta)
{
  double weight(1.);
  if (heta0 && heta1 && heta2)
  {
    if (abseta < 1.2) weight = heta0->Eval(pt);
    else if (abseta < 1.6) weight = heta1->Eval(pt);
    else if (abseta < 2.4) weight = heta2->Eval(pt);
//    else cout << "ERROR abseta range out of boundaries" << endl;
  }
  else{
    cout << "WARNING histos for weights not defined but function is called: returning 1" << endl;
  }
  return weight;
}

//type is added because muonTrk should only have the tags in accept
TTree* copyTree(TTree* told, bool applyNorm, bool applyDMCReW) {
  TTree *tnew = told->CloneTree(0);
  float weight_norm = 1.;
  float weight = 1.;
  float pt = 0.; float abseta = 0.;
  told->SetBranchAddress("weight",&weight);
  told->SetBranchAddress("pt",&pt);
  told->SetBranchAddress("abseta",&abseta);
  tnew->Branch("weight_norm",&weight_norm,"weight_norm/F");
  
  int nentries = told->GetEntries();
  float normF = 1.;
  if (applyNorm)
  {
    for (int i=0; i<nentries; i++) {
      told->GetEntry(i);
      normF += weight;
    }
    normF = nentries/normF;
  }
  
  for (int i=0; i<nentries; i++) {
    told->GetEntry(i);
    if (applyNorm && applyDMCReW) weight_norm = weight*normF*getDMCWeight(pt,abseta);
    else if (applyNorm) weight_norm = weight*normF;
    else if (applyDMCReW) weight_norm = weight*getDMCWeight(pt,abseta);
    else
    {
      cout << "ERROR you are using a macro to re-weight the tree but no weights were selected" << endl;
      return 0x0;
    }
    
    tnew->Fill();
  }
  
  return tnew;
}

void addMCWeight(const char *filein, const char *fileout, bool applyNorm=true, bool applyDMCReW=true) {
  TFile *fin = new TFile(filein);
  TFile *fout = new TFile(fileout,"RECREATE");

  if (applyDMCReW) setWHistos();
  
  fout->cd();
  TDirectory *tdir = fout->mkdir("tpTree");
  tdir->cd();
  TTree *tr = copyTree((TTree*) fin->Get("tpTree/fitter_tree"),applyNorm,applyDMCReW);
  
  fout->cd();
  TDirectory *tdirSta = fout->mkdir("tpTreeSta");
  tdirSta->cd();
  TTree *trSta = copyTree((TTree*) fin->Get("tpTreeSta/fitter_tree"),applyNorm,applyDMCReW);
  
  fout->cd();
  TDirectory *tdirTrk = fout->mkdir("tpTreeTrk");
  tdirTrk->cd();
  TTree *trTrk = copyTree((TTree*) fin->Get("tpTreeTrk/fitter_tree"),applyNorm,applyDMCReW);
  
  fout->Write();
  fout->Close();
}
