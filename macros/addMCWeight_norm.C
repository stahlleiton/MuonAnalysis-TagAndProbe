#include "TTree.h"
#include "TFile.h"

// Just creates a branch with normalised weights (so the number of events is conserved)

//type is added because muonTrk should only have the tags in accept
TTree* copyTree(TTree* told) {
  TTree *tnew = told->CloneTree(0);
  float weight_norm = 1.;
  float weight = 1.;
  told->SetBranchAddress("weight",&weight);
  tnew->Branch("weight_norm",&weight_norm,"weight_norm/F");
  
  int nentries = told->GetEntries();
  float normF = 0.;
  for (int i=0; i<nentries; i++) {
    told->GetEntry(i);
    normF += weight;
  }
  
  normF = nentries/normF;
  
  for (int i=0; i<nentries; i++) {
    told->GetEntry(i);
    weight_norm = weight*normF;
    tnew->Fill();
  }
  
  return tnew;
}

void addMCWeight(const char *filein, const char *fileout) {
  TFile *fin = new TFile(filein);
  TFile *fout = new TFile(fileout,"RECREATE");
  
  fout->cd();
  TDirectory *tdir = fout->mkdir("tpTree");
  tdir->cd();
  TTree *tr = copyTree((TTree*) fin->Get("tpTree/fitter_tree"));
  
  fout->cd();
  TDirectory *tdirSta = fout->mkdir("tpTreeSta");
  tdirSta->cd();
  TTree *trSta = copyTree((TTree*) fin->Get("tpTreeSta/fitter_tree"));
  
  fout->cd();
  TDirectory *tdirTrk = fout->mkdir("tpTreeTrk");
  tdirTrk->cd();
  TTree *trTrk = copyTree((TTree*) fin->Get("tpTreeTrk/fitter_tree"));
  
  fout->Write();
  fout->Close();
}
