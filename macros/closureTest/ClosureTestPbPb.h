//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan 17 15:39:08 2017 by ROOT version 6.08/04
// from TTree myTree/My TTree of dimuons
// found on file: root://xrootd.unl.edu//store/group/phys_heavyions/dileptons/MC2015/pp502TeV/TTrees/OniaTree_JpsiMM_5p02TeV_TuneCUETP8M1_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1.root
//////////////////////////////////////////////////////////

#ifndef ClosureTestPbPb_h
#define ClosureTestPbPb_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"
#include "TLorentzVector.h"

class ClosureTestPbPb {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
  UInt_t          eventNb;
  UInt_t          runNb;
  UInt_t          LS;
  Float_t         zVtx;
  Float_t         nPV;
  Int_t           Centrality;
  Int_t           Npix;
  Int_t           NpixelTracks;
  Int_t           Ntracks;
  Int_t           nTrig;
  Int_t           trigPrescale[100];   //[nTrig]
  ULong64_t       HLTriggers;
  Int_t           Reco_QQ_size;
  Int_t           Reco_QQ_type[100];   //[Reco_QQ_size]
  Int_t           Reco_QQ_sign[100];   //[Reco_QQ_size]
  TClonesArray    *Reco_QQ_4mom;
  Int_t           Reco_QQ_mupl_idx[100];   //[Reco_QQ_size]
  Int_t           Reco_QQ_mumi_idx[100];   //[Reco_QQ_size]
  ULong64_t       Reco_QQ_trig[100];   //[Reco_QQ_size]
  Bool_t          Reco_QQ_isCowboy[100];   //[Reco_QQ_size]
  Float_t         Reco_QQ_ctau[100];   //[Reco_QQ_size]
  Float_t         Reco_QQ_ctauErr[100];   //[Reco_QQ_size]
  Float_t         Reco_QQ_cosAlpha[100];   //[Reco_QQ_size]
  Float_t         Reco_QQ_ctau3D[100];   //[Reco_QQ_size]
  Float_t         Reco_QQ_ctauErr3D[100];   //[Reco_QQ_size]
  Float_t         Reco_QQ_cosAlpha3D[100];   //[Reco_QQ_size]
  Int_t           Reco_QQ_whichGen[100];   //[Reco_QQ_size]
  Float_t         Reco_QQ_VtxProb[100];   //[Reco_QQ_size]
  Float_t         Reco_QQ_dca[100];   //[Reco_QQ_size]
  Float_t         Reco_QQ_MassErr[100];   //[Reco_QQ_size]
  TClonesArray    *Reco_QQ_vtx;
  Int_t           Reco_QQ_Ntrk[100];   //[Reco_QQ_size]
  Int_t           Reco_mu_size;
  Int_t           Reco_mu_type[100];   //[Reco_mu_size]
  Int_t           Reco_mu_whichGen[100];   //[Reco_mu_size]
  Int_t           Reco_mu_SelectionType[100];   //[Reco_mu_size]
  Int_t           Reco_mu_charge[100];   //[Reco_mu_size]
  TClonesArray    *Reco_mu_4mom;
  ULong64_t       Reco_mu_trig[100];   //[Reco_mu_size]
  Bool_t          Reco_mu_isPF[100];   //[Reco_mu_size]
  Bool_t          Reco_mu_highPurity[100];   //[Reco_mu_size]
  Bool_t          Reco_mu_TrkMuArb[100];   //[Reco_mu_size]
  Bool_t          Reco_mu_TMOneStaTight[100];   //[Reco_mu_size]
  Int_t           Reco_mu_nPixValHits[100];   //[Reco_mu_size]
  Int_t           Reco_mu_nMuValHits[100];   //[Reco_mu_size]
  Int_t           Reco_mu_nTrkHits[100];   //[Reco_mu_size]
  Float_t         Reco_mu_normChi2_inner[100];   //[Reco_mu_size]
  Float_t         Reco_mu_normChi2_global[100];   //[Reco_mu_size]
  Int_t           Reco_mu_nPixWMea[100];   //[Reco_mu_size]
  Int_t           Reco_mu_nTrkWMea[100];   //[Reco_mu_size]
  Int_t           Reco_mu_StationsMatched[100];   //[Reco_mu_size]
  Float_t         Reco_mu_dxy[100];   //[Reco_mu_size]
  Float_t         Reco_mu_dxyErr[100];   //[Reco_mu_size]
  Float_t         Reco_mu_dz[100];   //[Reco_mu_size]
  Float_t         Reco_mu_dzErr[100];   //[Reco_mu_size]
  Float_t         Reco_mu_pt_inner[100];   //[Reco_mu_size]
  Float_t         Reco_mu_pt_global[100];   //[Reco_mu_size]
  Float_t         Reco_mu_ptErr_inner[100];   //[Reco_mu_size]
  Float_t         Reco_mu_ptErr_global[100];   //[Reco_mu_size]
  Int_t           Reco_trk_size;
  Int_t           Reco_trk_genIdx[100];   //[Reco_trk_size]
  Int_t           Reco_trk_charge[100];   //[Reco_trk_size]
  TClonesArray    *Reco_trk_4mom;
  Bool_t          Reco_trk_highPurity[100];   //[Reco_trk_size]
  Int_t           Reco_trk_nPixValHits[100];   //[Reco_trk_size]
  Int_t           Reco_trk_nTrkHits[100];   //[Reco_trk_size]
  Float_t         Reco_trk_normChi2[100];   //[Reco_trk_size]
  Int_t           Reco_trk_nPixWMea[100];   //[Reco_trk_size]
  Int_t           Reco_trk_nTrkWMea[100];   //[Reco_trk_size]
  Float_t         Reco_trk_dxy[100];   //[Reco_trk_size]
  Float_t         Reco_trk_dxyError[100];   //[Reco_trk_size]
  Float_t         Reco_trk_dz[100];   //[Reco_trk_size]
  Float_t         Reco_trk_dzError[100];   //[Reco_trk_size]
  Float_t         Reco_trk_ptErr[100];   //[Reco_trk_size]
  Int_t           Reco_trk_algo[100];   //[Reco_trk_size]
  Int_t           Reco_trk_origAlgo[100];   //[Reco_trk_size]
  Float_t         Gen_weight;
  Float_t         Gen_pthat;
  Int_t           Gen_QQ_size;
  Int_t           Gen_QQ_type[100];   //[Gen_QQ_size]
  TClonesArray    *Gen_QQ_4mom;
  Int_t           Gen_QQ_momId[100];   //[Gen_QQ_size]
  Float_t         Gen_QQ_ctau[100];   //[Gen_QQ_size]
  Float_t         Gen_QQ_ctau3D[100];   //[Gen_QQ_size]
  Int_t           Gen_QQ_mupl_idx[100];   //[Gen_QQ_size]
  Int_t           Gen_QQ_mumi_idx[100];   //[Gen_QQ_size]
  Int_t           Gen_QQ_whichRec[100];   //[Gen_QQ_size]
  Int_t           Gen_mu_size;
  Int_t           Gen_mu_type[100];   //[Gen_mu_size]
  Int_t           Gen_mu_charge[100];   //[Gen_mu_size]
  TClonesArray    *Gen_mu_4mom;
  Int_t           Gen_mu_whichRec[100];   //[Gen_mu_size]

  Int_t           hiBin;
  Float_t         hiHF;


  // List of branches
  TBranch        *b_eventNb;   //!
  TBranch        *b_runNb;   //!
  TBranch        *b_LS;   //!
  TBranch        *b_zVtx;   //!
  TBranch        *b_nPV;   //!
  TBranch        *b_Centrality;   //!
  TBranch        *b_Npix;   //!
  TBranch        *b_NpixelTracks;   //!
  TBranch        *b_Ntracks;   //!
  TBranch        *b_nTrig;   //!
  TBranch        *b_trigPrescale;   //!
  TBranch        *b_HLTriggers;   //!
  TBranch        *b_Reco_QQ_size;   //!
  TBranch        *b_Reco_QQ_type;   //!
  TBranch        *b_Reco_QQ_sign;   //!
  TBranch        *b_Reco_QQ_4mom;   //!
  TBranch        *b_Reco_QQ_mupl_idx;   //!
  TBranch        *b_Reco_QQ_mumi_idx;   //!
  TBranch        *b_Reco_QQ_trig;   //!
  TBranch        *b_Reco_QQ_isCowboy;   //!
  TBranch        *b_Reco_QQ_ctau;   //!
  TBranch        *b_Reco_QQ_ctauErr;   //!
  TBranch        *b_Reco_QQ_cosAlpha;   //!
  TBranch        *b_Reco_QQ_ctau3D;   //!
  TBranch        *b_Reco_QQ_ctauErr3D;   //!
  TBranch        *b_Reco_QQ_cosAlpha3D;   //!
  TBranch        *b_Reco_QQ_whichGen;   //!
  TBranch        *b_Reco_QQ_VtxProb;   //!
  TBranch        *b_Reco_QQ_dca;   //!
  TBranch        *b_Reco_QQ_MassErr;   //!
  TBranch        *b_Reco_QQ_vtx;   //!
  TBranch        *b_Reco_QQ_Ntrk;   //!
  TBranch        *b_Reco_mu_size;   //!
  TBranch        *b_Reco_mu_type;   //!
  TBranch        *b_Reco_mu_whichGen;   //!
  TBranch        *b_Reco_mu_SelectionType;   //!
  TBranch        *b_Reco_mu_charge;   //!
  TBranch        *b_Reco_mu_4mom;   //!
  TBranch        *b_Reco_mu_trig;   //!
  TBranch        *b_Reco_mu_isPF;   //!
  TBranch        *b_Reco_mu_highPurity;   //!
  TBranch        *b_Reco_mu_TrkMuArb;   //!
  TBranch        *b_Reco_mu_TMOneStaTight;   //!
  TBranch        *b_Reco_mu_nPixValHits;   //!
  TBranch        *b_Reco_mu_nMuValHits;   //!
  TBranch        *b_Reco_mu_nTrkHits;   //!
  TBranch        *b_Reco_mu_normChi2_inner;   //!
  TBranch        *b_Reco_mu_normChi2_global;   //!
  TBranch        *b_Reco_mu_nPixWMea;   //!
  TBranch        *b_Reco_mu_nTrkWMea;   //!
  TBranch        *b_Reco_mu_StationsMatched;   //!
  TBranch        *b_Reco_mu_dxy;   //!
  TBranch        *b_Reco_mu_dxyErr;   //!
  TBranch        *b_Reco_mu_dz;   //!
  TBranch        *b_Reco_mu_dzErr;   //!
  TBranch        *b_Reco_mu_pt_inner;   //!
  TBranch        *b_Reco_mu_pt_global;   //!
  TBranch        *b_Reco_mu_ptErr_inner;   //!
  TBranch        *b_Reco_mu_ptErr_global;   //!
  TBranch        *b_Reco_trk_size;   //!
  TBranch        *b_Reco_trk_genIdx;   //!
  TBranch        *b_Reco_trk_charge;   //!
  TBranch        *b_Reco_trk_4mom;   //!
  TBranch        *b_Reco_trk_highPurity;   //!
  TBranch        *b_Reco_trk_nPixValHits;   //!
  TBranch        *b_Reco_trk_nTrkHits;   //!
  TBranch        *b_Reco_trk_normChi2;   //!
  TBranch        *b_Reco_trk_nPixWMea;   //!
  TBranch        *b_Reco_trk_nTrkWMea;   //!
  TBranch        *b_Reco_trk_dxy;   //!
  TBranch        *b_Reco_trk_dxyError;   //!
  TBranch        *b_Reco_trk_dz;   //!
  TBranch        *b_Reco_trk_dzError;   //!
  TBranch        *b_Reco_trk_ptErr;   //!
  TBranch        *b_Reco_trk_algo;   //!
  TBranch        *b_Reco_trk_origAlgo;   //!
  TBranch        *b_Gen_weight;   //!
  TBranch        *b_Gen_pthat;   //!
  TBranch        *b_Gen_QQ_size;   //!
  TBranch        *b_Gen_QQ_type;   //!
  TBranch        *b_Gen_QQ_4mom;   //!
  TBranch        *b_Gen_QQ_momId;   //!
  TBranch        *b_Gen_QQ_ctau;   //!
  TBranch        *b_Gen_QQ_ctau3D;   //!
  TBranch        *b_Gen_QQ_mupl_idx;   //!
  TBranch        *b_Gen_QQ_mumi_idx;   //!
  TBranch        *b_Gen_QQ_whichRec;   //!
  TBranch        *b_Gen_mu_size;   //!
  TBranch        *b_Gen_mu_type;   //!
  TBranch        *b_Gen_mu_charge;   //!
  TBranch        *b_Gen_mu_4mom;   //!
  TBranch        *b_Gen_mu_whichRec;   //!

  TBranch        *b_hiBin;
  TBranch        *b_hiHF;

  ClosureTestPbPb(TTree *tree=0);
  virtual ~ClosureTestPbPb();
  virtual Int_t    CutSgMuon(Long64_t entry);
  virtual Bool_t   isGlobalMuonInAccept2015 (TLorentzVector* Muon);
  virtual Bool_t   isGlobalMuonInTightAccept2018 (TLorentzVector* Muon);
  virtual Bool_t   areMuonsInAcceptance2015 (Int_t iRecoQQ);
  virtual Bool_t   passQualityCuts2015 (Int_t iRecoQQ);
  virtual Bool_t   Cut_muplmi (Int_t iRecoQQ);
  virtual Bool_t   isTightID (Int_t iMu);
  virtual Bool_t   isTriggerMatched (Int_t iMu, Int_t iTrg, Int_t iMuTrg);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop(const std::string& filename);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ClosureTestPbPb_cxx
ClosureTestPbPb::ClosureTestPbPb(TTree *tree) : fChain(0) 
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/group/phys_heavyions/bdiab/dilepton/oniaTree/PbPb2018/MC/Prompt/merged_HiForestAOD.root");
    if (!f || !f->IsOpen()) {
      f = new TFile("/eos/cms/store/group/phys_heavyions/bdiab/dilepton/oniaTree/PbPb2018/MC/Prompt/merged_HiForestAOD.root");
    }
    TDirectory * dir = (TDirectory*)f->Get("/eos/cms/store/group/phys_heavyions/bdiab/dilepton/oniaTree/PbPb2018/MC/Prompt/merged_HiForestAOD.root:/hionia");
    dir->GetObject("myTree",tree);
  }
  Init(tree);
}

ClosureTestPbPb::~ClosureTestPbPb()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t ClosureTestPbPb::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t ClosureTestPbPb::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void ClosureTestPbPb::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  Reco_QQ_4mom = 0;
  Reco_QQ_vtx = 0;
  Reco_mu_4mom = 0;
  Reco_trk_4mom = 0;
  Gen_QQ_4mom = 0;
  Gen_mu_4mom = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  if (fChain->GetBranch("eventNb")) fChain->SetBranchAddress("eventNb", &eventNb, &b_eventNb);
   if (fChain->GetBranch("runNb")) fChain->SetBranchAddress("runNb", &runNb, &b_runNb);
   if (fChain->GetBranch("LS")) fChain->SetBranchAddress("LS", &LS, &b_LS);
   if (fChain->GetBranch("zVtx")) fChain->SetBranchAddress("zVtx", &zVtx, &b_zVtx);
   if (fChain->GetBranch("nPV")) fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   if (fChain->GetBranch("Centrality")) fChain->SetBranchAddress("Centrality", &Centrality, &b_Centrality);
   if (fChain->GetBranch("Npix")) fChain->SetBranchAddress("Npix", &Npix, &b_Npix);
   if (fChain->GetBranch("NpixelTracks")) fChain->SetBranchAddress("NpixelTracks", &NpixelTracks, &b_NpixelTracks);
   if (fChain->GetBranch("Ntracks")) fChain->SetBranchAddress("Ntracks", &Ntracks, &b_Ntracks);
   if (fChain->GetBranch("nTrig")) fChain->SetBranchAddress("nTrig", &nTrig, &b_nTrig);
   if (fChain->GetBranch("trigPrescale")) fChain->SetBranchAddress("trigPrescale", trigPrescale, &b_trigPrescale);
   if (fChain->GetBranch("HLTriggers")) fChain->SetBranchAddress("HLTriggers", &HLTriggers, &b_HLTriggers);
   if (fChain->GetBranch("Reco_QQ_size")) fChain->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
   if (fChain->GetBranch("Reco_QQ_type")) fChain->SetBranchAddress("Reco_QQ_type", Reco_QQ_type, &b_Reco_QQ_type);
   if (fChain->GetBranch("Reco_QQ_sign")) fChain->SetBranchAddress("Reco_QQ_sign", Reco_QQ_sign, &b_Reco_QQ_sign);
   if (fChain->GetBranch("Reco_QQ_4mom")) fChain->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
   if (fChain->GetBranch("Reco_QQ_mupl_idx")) fChain->SetBranchAddress("Reco_QQ_mupl_idx", Reco_QQ_mupl_idx, &b_Reco_QQ_mupl_idx);
   if (fChain->GetBranch("Reco_QQ_mumi_idx")) fChain->SetBranchAddress("Reco_QQ_mumi_idx", Reco_QQ_mumi_idx, &b_Reco_QQ_mumi_idx);
   if (fChain->GetBranch("Reco_QQ_trig")) fChain->SetBranchAddress("Reco_QQ_trig", Reco_QQ_trig, &b_Reco_QQ_trig);
   if (fChain->GetBranch("Reco_QQ_isCowboy")) fChain->SetBranchAddress("Reco_QQ_isCowboy", Reco_QQ_isCowboy, &b_Reco_QQ_isCowboy);
   if (fChain->GetBranch("Reco_QQ_ctau")) fChain->SetBranchAddress("Reco_QQ_ctau", Reco_QQ_ctau, &b_Reco_QQ_ctau);
   if (fChain->GetBranch("Reco_QQ_ctauErr")) fChain->SetBranchAddress("Reco_QQ_ctauErr", Reco_QQ_ctauErr, &b_Reco_QQ_ctauErr);
   if (fChain->GetBranch("Reco_QQ_cosAlpha")) fChain->SetBranchAddress("Reco_QQ_cosAlpha", Reco_QQ_cosAlpha, &b_Reco_QQ_cosAlpha);
   if (fChain->GetBranch("Reco_QQ_ctau3D")) fChain->SetBranchAddress("Reco_QQ_ctau3D", Reco_QQ_ctau3D, &b_Reco_QQ_ctau3D);
   if (fChain->GetBranch("Reco_QQ_ctauErr3D")) fChain->SetBranchAddress("Reco_QQ_ctauErr3D", Reco_QQ_ctauErr3D, &b_Reco_QQ_ctauErr3D);
   if (fChain->GetBranch("Reco_QQ_cosAlpha3D")) fChain->SetBranchAddress("Reco_QQ_cosAlpha3D", Reco_QQ_cosAlpha3D, &b_Reco_QQ_cosAlpha3D);
   if (fChain->GetBranch("Reco_QQ_whichGen")) fChain->SetBranchAddress("Reco_QQ_whichGen", Reco_QQ_whichGen, &b_Reco_QQ_whichGen);
   if (fChain->GetBranch("Reco_QQ_VtxProb")) fChain->SetBranchAddress("Reco_QQ_VtxProb", Reco_QQ_VtxProb, &b_Reco_QQ_VtxProb);
   if (fChain->GetBranch("Reco_QQ_dca")) fChain->SetBranchAddress("Reco_QQ_dca", Reco_QQ_dca, &b_Reco_QQ_dca);
   if (fChain->GetBranch("Reco_QQ_MassErr")) fChain->SetBranchAddress("Reco_QQ_MassErr", Reco_QQ_MassErr, &b_Reco_QQ_MassErr);
   if (fChain->GetBranch("Reco_QQ_vtx")) fChain->SetBranchAddress("Reco_QQ_vtx", &Reco_QQ_vtx, &b_Reco_QQ_vtx);
   if (fChain->GetBranch("Reco_QQ_Ntrk")) fChain->SetBranchAddress("Reco_QQ_Ntrk", Reco_QQ_Ntrk, &b_Reco_QQ_Ntrk);
   if (fChain->GetBranch("Reco_mu_size")) fChain->SetBranchAddress("Reco_mu_size", &Reco_mu_size, &b_Reco_mu_size);
   if (fChain->GetBranch("Reco_mu_type")) fChain->SetBranchAddress("Reco_mu_type", Reco_mu_type, &b_Reco_mu_type);
   if (fChain->GetBranch("Reco_mu_whichGen")) fChain->SetBranchAddress("Reco_mu_whichGen", Reco_mu_whichGen, &b_Reco_mu_whichGen);
   if (fChain->GetBranch("Reco_mu_SelectionType")) fChain->SetBranchAddress("Reco_mu_SelectionType", Reco_mu_SelectionType, &b_Reco_mu_SelectionType);
   if (fChain->GetBranch("Reco_mu_charge")) fChain->SetBranchAddress("Reco_mu_charge", Reco_mu_charge, &b_Reco_mu_charge);
   if (fChain->GetBranch("Reco_mu_4mom")) fChain->SetBranchAddress("Reco_mu_4mom", &Reco_mu_4mom, &b_Reco_mu_4mom);
   if (fChain->GetBranch("Reco_mu_trig")) fChain->SetBranchAddress("Reco_mu_trig", Reco_mu_trig, &b_Reco_mu_trig);
   if (fChain->GetBranch("Reco_mu_isPF")) fChain->SetBranchAddress("Reco_mu_isPF", Reco_mu_isPF, &b_Reco_mu_isPF);
   if (fChain->GetBranch("Reco_mu_highPurity")) fChain->SetBranchAddress("Reco_mu_highPurity", Reco_mu_highPurity, &b_Reco_mu_highPurity);
   if (fChain->GetBranch("Reco_mu_TrkMuArb")) fChain->SetBranchAddress("Reco_mu_TrkMuArb", Reco_mu_TrkMuArb, &b_Reco_mu_TrkMuArb);
   if (fChain->GetBranch("Reco_mu_TMOneStaTight")) fChain->SetBranchAddress("Reco_mu_TMOneStaTight", Reco_mu_TMOneStaTight, &b_Reco_mu_TMOneStaTight);
   if (fChain->GetBranch("Reco_mu_nPixValHits")) fChain->SetBranchAddress("Reco_mu_nPixValHits", Reco_mu_nPixValHits, &b_Reco_mu_nPixValHits);
   if (fChain->GetBranch("Reco_mu_nMuValHits")) fChain->SetBranchAddress("Reco_mu_nMuValHits", Reco_mu_nMuValHits, &b_Reco_mu_nMuValHits);
   if (fChain->GetBranch("Reco_mu_nTrkHits")) fChain->SetBranchAddress("Reco_mu_nTrkHits", Reco_mu_nTrkHits, &b_Reco_mu_nTrkHits);
   if (fChain->GetBranch("Reco_mu_normChi2_inner")) fChain->SetBranchAddress("Reco_mu_normChi2_inner", Reco_mu_normChi2_inner, &b_Reco_mu_normChi2_inner);
   if (fChain->GetBranch("Reco_mu_normChi2_global")) fChain->SetBranchAddress("Reco_mu_normChi2_global", Reco_mu_normChi2_global, &b_Reco_mu_normChi2_global);
   if (fChain->GetBranch("Reco_mu_nPixWMea")) fChain->SetBranchAddress("Reco_mu_nPixWMea", Reco_mu_nPixWMea, &b_Reco_mu_nPixWMea);
   if (fChain->GetBranch("Reco_mu_nTrkWMea")) fChain->SetBranchAddress("Reco_mu_nTrkWMea", Reco_mu_nTrkWMea, &b_Reco_mu_nTrkWMea);
   if (fChain->GetBranch("Reco_mu_StationsMatched")) fChain->SetBranchAddress("Reco_mu_StationsMatched", Reco_mu_StationsMatched, &b_Reco_mu_StationsMatched);
   if (fChain->GetBranch("Reco_mu_dxy")) fChain->SetBranchAddress("Reco_mu_dxy", Reco_mu_dxy, &b_Reco_mu_dxy);
   if (fChain->GetBranch("Reco_mu_dxyErr")) fChain->SetBranchAddress("Reco_mu_dxyErr", Reco_mu_dxyErr, &b_Reco_mu_dxyErr);
   if (fChain->GetBranch("Reco_mu_dz")) fChain->SetBranchAddress("Reco_mu_dz", Reco_mu_dz, &b_Reco_mu_dz);
   if (fChain->GetBranch("Reco_mu_dzErr")) fChain->SetBranchAddress("Reco_mu_dzErr", Reco_mu_dzErr, &b_Reco_mu_dzErr);
   if (fChain->GetBranch("Reco_mu_pt_inner")) fChain->SetBranchAddress("Reco_mu_pt_inner", Reco_mu_pt_inner, &b_Reco_mu_pt_inner);
   if (fChain->GetBranch("Reco_mu_pt_global")) fChain->SetBranchAddress("Reco_mu_pt_global", Reco_mu_pt_global, &b_Reco_mu_pt_global);
   if (fChain->GetBranch("Reco_mu_ptErr_inner")) fChain->SetBranchAddress("Reco_mu_ptErr_inner", Reco_mu_ptErr_inner, &b_Reco_mu_ptErr_inner);
   if (fChain->GetBranch("Reco_mu_ptErr_global")) fChain->SetBranchAddress("Reco_mu_ptErr_global", Reco_mu_ptErr_global, &b_Reco_mu_ptErr_global);
   if (fChain->GetBranch("Reco_trk_size")) fChain->SetBranchAddress("Reco_trk_size", &Reco_trk_size, &b_Reco_trk_size);
   if (fChain->GetBranch("Reco_trk_genIdx")) fChain->SetBranchAddress("Reco_trk_genIdx", Reco_trk_genIdx, &b_Reco_trk_genIdx);
   if (fChain->GetBranch("Reco_trk_charge")) fChain->SetBranchAddress("Reco_trk_charge", Reco_trk_charge, &b_Reco_trk_charge);
   if (fChain->GetBranch("Reco_trk_4mom")) fChain->SetBranchAddress("Reco_trk_4mom", &Reco_trk_4mom, &b_Reco_trk_4mom);
   if (fChain->GetBranch("Reco_trk_highPurity")) fChain->SetBranchAddress("Reco_trk_highPurity", Reco_trk_highPurity, &b_Reco_trk_highPurity);
   if (fChain->GetBranch("Reco_trk_nPixValHits")) fChain->SetBranchAddress("Reco_trk_nPixValHits", Reco_trk_nPixValHits, &b_Reco_trk_nPixValHits);
   if (fChain->GetBranch("Reco_trk_nTrkHits")) fChain->SetBranchAddress("Reco_trk_nTrkHits", Reco_trk_nTrkHits, &b_Reco_trk_nTrkHits);
   if (fChain->GetBranch("Reco_trk_normChi2")) fChain->SetBranchAddress("Reco_trk_normChi2", Reco_trk_normChi2, &b_Reco_trk_normChi2);
   if (fChain->GetBranch("Reco_trk_nPixWMea")) fChain->SetBranchAddress("Reco_trk_nPixWMea", Reco_trk_nPixWMea, &b_Reco_trk_nPixWMea);
   if (fChain->GetBranch("Reco_trk_nTrkWMea")) fChain->SetBranchAddress("Reco_trk_nTrkWMea", Reco_trk_nTrkWMea, &b_Reco_trk_nTrkWMea);
   if (fChain->GetBranch("Reco_trk_dxy")) fChain->SetBranchAddress("Reco_trk_dxy", Reco_trk_dxy, &b_Reco_trk_dxy);
   if (fChain->GetBranch("Reco_trk_dxyError")) fChain->SetBranchAddress("Reco_trk_dxyError", Reco_trk_dxyError, &b_Reco_trk_dxyError);
   if (fChain->GetBranch("Reco_trk_dz")) fChain->SetBranchAddress("Reco_trk_dz", Reco_trk_dz, &b_Reco_trk_dz);
   if (fChain->GetBranch("Reco_trk_dzError")) fChain->SetBranchAddress("Reco_trk_dzError", Reco_trk_dzError, &b_Reco_trk_dzError);
   if (fChain->GetBranch("Reco_trk_ptErr")) fChain->SetBranchAddress("Reco_trk_ptErr", Reco_trk_ptErr, &b_Reco_trk_ptErr);
   if (fChain->GetBranch("Reco_trk_algo")) fChain->SetBranchAddress("Reco_trk_algo", Reco_trk_algo, &b_Reco_trk_algo);
   if (fChain->GetBranch("Reco_trk_origAlgo")) fChain->SetBranchAddress("Reco_trk_origAlgo", Reco_trk_origAlgo, &b_Reco_trk_origAlgo);
   if (fChain->GetBranch("Gen_weight")) fChain->SetBranchAddress("Gen_weight", &Gen_weight, &b_Gen_weight);
   if (fChain->GetBranch("Gen_pthat")) fChain->SetBranchAddress("Gen_pthat", &Gen_pthat, &b_Gen_pthat);
   if (fChain->GetBranch("Gen_QQ_size")) fChain->SetBranchAddress("Gen_QQ_size", &Gen_QQ_size, &b_Gen_QQ_size);
   if (fChain->GetBranch("Gen_QQ_type")) fChain->SetBranchAddress("Gen_QQ_type", Gen_QQ_type, &b_Gen_QQ_type);
   if (fChain->GetBranch("Gen_QQ_4mom")) fChain->SetBranchAddress("Gen_QQ_4mom", &Gen_QQ_4mom, &b_Gen_QQ_4mom);
   if (fChain->GetBranch("Gen_QQ_momId")) fChain->SetBranchAddress("Gen_QQ_momId", Gen_QQ_momId, &b_Gen_QQ_momId);
   if (fChain->GetBranch("Gen_QQ_ctau")) fChain->SetBranchAddress("Gen_QQ_ctau", Gen_QQ_ctau, &b_Gen_QQ_ctau);
   if (fChain->GetBranch("Gen_QQ_ctau3D")) fChain->SetBranchAddress("Gen_QQ_ctau3D", Gen_QQ_ctau3D, &b_Gen_QQ_ctau3D);
   if (fChain->GetBranch("Gen_QQ_mupl_idx")) fChain->SetBranchAddress("Gen_QQ_mupl_idx", Gen_QQ_mupl_idx, &b_Gen_QQ_mupl_idx);
   if (fChain->GetBranch("Gen_QQ_mumi_idx")) fChain->SetBranchAddress("Gen_QQ_mumi_idx", Gen_QQ_mumi_idx, &b_Gen_QQ_mumi_idx);
   if (fChain->GetBranch("Gen_QQ_whichRec")) fChain->SetBranchAddress("Gen_QQ_whichRec", Gen_QQ_whichRec, &b_Gen_QQ_whichRec);
   if (fChain->GetBranch("Gen_mu_size")) fChain->SetBranchAddress("Gen_mu_size", &Gen_mu_size, &b_Gen_mu_size);
   if (fChain->GetBranch("Gen_mu_type")) fChain->SetBranchAddress("Gen_mu_type", Gen_mu_type, &b_Gen_mu_type);
   if (fChain->GetBranch("Gen_mu_charge")) fChain->SetBranchAddress("Gen_mu_charge", Gen_mu_charge, &b_Gen_mu_charge);
   if (fChain->GetBranch("Gen_mu_4mom")) fChain->SetBranchAddress("Gen_mu_4mom", &Gen_mu_4mom, &b_Gen_mu_4mom);
   if (fChain->GetBranch("Gen_mu_whichRec")) fChain->SetBranchAddress("Gen_mu_whichRec", Gen_mu_whichRec, &b_Gen_mu_whichRec);
  if (fChain->GetBranch("Centrality")) fChain->SetBranchAddress("Centrality", &hiBin, &b_hiBin);
  if (fChain->GetBranch("SumET_HF")) fChain->SetBranchAddress("SumET_HF", &hiHF, &b_hiHF);
  Notify();
}

Bool_t ClosureTestPbPb::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void ClosureTestPbPb::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t ClosureTestPbPb::CutSgMuon(Long64_t irec)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  // return 1;
  if (Reco_mu_nTrkWMea[irec] > 5 &&   //Reco_mu_nTrkHits[irec]>10 &&
      Reco_mu_nPixWMea[irec]>0 &&
      //Reco_mu_normChi2_inner[irec]<4.0 &&
      fabs(Reco_mu_dxy[irec])<0.3 &&
      fabs(Reco_mu_dz[irec])<20 &&
      //Reco_mu_normChi2_global[irec]<10.0 &&
      //Reco_mu_nMuValHits[irec]>0 &&
      //Reco_mu_StationsMatched[irec]>0 &&
      (Reco_mu_SelectionType[irec]&2)>0 && //isGlobal
      (Reco_mu_SelectionType[irec]&4096)>0 //isTracker + TMOneStationTight (2^12) --- match the tag cuts in jpsiHI/tnp_pp_mc.py
      )
    return 1;
  else
    return 0;
}

Bool_t ClosureTestPbPb::isGlobalMuonInAccept2015 (TLorentzVector* Muon) 
{
  return (fabs(Muon->Eta()) < 2.4 &&
	  ((fabs(Muon->Eta()) < 1.2 && Muon->Pt() >= 3.5) ||
	   (1.2 <= fabs(Muon->Eta()) && fabs(Muon->Eta()) < 2.1 && Muon->Pt() >= 5.77-1.89*fabs(Muon->Eta())) ||
	   (2.1 <= fabs(Muon->Eta()) && Muon->Pt() >= 1.8)));
};

Bool_t ClosureTestPbPb::isGlobalMuonInTightAccept2018 (TLorentzVector* Muon) 
{
  double pt = Muon->Pt(), eta = Muon->Eta();
  return (fabs(eta) < 2.4 && 
	  ((fabs(eta) < 1.2 && pt >= 3.5 ) || 
	   (1.2 <= fabs(eta) && fabs(eta) < 2.1 && pt >= 5.47-1.89*fabs(eta)) || 
  	   (2.1 <= fabs(eta) && pt >= 1.5)));
};

Bool_t ClosureTestPbPb::areMuonsInAcceptance2015 (Int_t iRecoQQ)
{
  int recmumi = Reco_QQ_mumi_idx[iRecoQQ];
  int recmupl = Reco_QQ_mupl_idx[iRecoQQ];
  TLorentzVector *RecoQQmupl = (TLorentzVector*) Reco_mu_4mom->At(recmupl);
  TLorentzVector *RecoQQmumi = (TLorentzVector*) Reco_mu_4mom->At(recmumi);
  return ( isGlobalMuonInAccept2015(RecoQQmupl) && isGlobalMuonInAccept2015(RecoQQmumi) );
};  

Bool_t ClosureTestPbPb::passQualityCuts2015 (Int_t iRecoQQ) 
{
  Bool_t cond = true;
  
  int recmumi = Reco_QQ_mumi_idx[iRecoQQ];
  int recmupl = Reco_QQ_mupl_idx[iRecoQQ];
  cond = cond && Cut_muplmi(recmumi) && Cut_muplmi(recmupl) ;

  cond = cond && (Reco_QQ_VtxProb[iRecoQQ] > 0.01);

  return cond;
}; 

Bool_t ClosureTestPbPb::Cut_muplmi (Int_t irec) 
{
  Bool_t cond = true;

  // cond = cond && (Reco_QQ_mupl_highPurity[irec]);
  cond = cond && (Reco_mu_SelectionType[irec]&2)>0; //isGlobal
  cond = cond && (Reco_mu_SelectionType[irec]&8)>0; //isTracker
  //  cond = cond && (Reco_QQ_mupl_isGoodMuon[irec]==1);
  cond = cond && (Reco_mu_nTrkWMea[irec] > 5);
  cond = cond && (Reco_mu_nPixWMea[irec] > 0);
  cond = cond && (fabs(Reco_mu_dxy[irec]) < 0.3);
  cond = cond && (fabs(Reco_mu_dz[irec]) < 20.);

  return cond;
}; 

Bool_t ClosureTestPbPb::isTightID(Int_t irec) 
{
  if (irec<0) return false;
  Bool_t cond = true;
  cond = cond && ((Reco_mu_SelectionType[irec]&2) > 0); //isGlobal
  cond = cond && Reco_mu_isPF[irec];
  cond = cond && (Reco_mu_normChi2_global[irec] < 10.0);
  cond = cond && (Reco_mu_nMuValHits[irec] > 0);
  cond = cond && (Reco_mu_StationsMatched[irec] > 1);
  cond = cond && (fabs(Reco_mu_dxy[irec]) < 0.2);
  cond = cond && (fabs(Reco_mu_dz[irec]) < 0.5);
  cond = cond && (Reco_mu_nPixValHits[irec] > 0);
  cond = cond && (Reco_mu_nTrkWMea[irec] > 5);
  return cond;
};

Bool_t ClosureTestPbPb::isTriggerMatched(Int_t irec, Int_t itrg, Int_t iMuTrg) 
{
  if (irec<0 || itrg<0 || iMuTrg<0) return false;
  const auto& bit = ULong64_t(std::pow(2,itrg));
  const auto& mubit = ULong64_t(std::pow(2,iMuTrg));
  const bool& isTrig = ((HLTriggers & bit) > 0) && ((Reco_mu_trig[irec] & mubit) > 0);
  return isTrig;
};

#endif // #ifdef ClosureTestPbPb_cxx
