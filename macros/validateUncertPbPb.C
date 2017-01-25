#define validateUncertPbPb_cxx
#include "validateUncertPbPb.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "tnp_weight.h"
#include "TChain.h"
#include <iostream>

// #define server "xrootd.unl.edu/"
#define server "eoscms//eos/cms"

using namespace std;

const int trg_probe = pow(2,0);


void runValidateUncertPbPb() {
   TChain *tr = new TChain("hionia/myTree");
   // tr->AddFile("root://xrootd.unl.edu//store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_00_03_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
   tr->AddFile("root://" server "/store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_03_06_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1_Extended.root");
   tr->AddFile("root://" server "/store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_06_09_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1_Extended.root");
   tr->AddFile("root://" server "/store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_09_12_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
   tr->AddFile("root://" server "/store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_12_15_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
   tr->AddFile("root://" server "/store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_15_30_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
   // tr->AddFile("root://xrootd.unl.edu//store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_30_Inf_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
   validateUncertPbPb toto(tr);
   toto.Loop("histos_pbpb.root");
}

void validateUncertPbPb::Loop(const char* filename)
{
//   In a ROOT session, you can do:
//      root> .L validateUncertPbPb.C
//      root> validateUncertPbPb t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   fChain->SetBranchStatus("*",1);
   // fChain->SetBranchStatus("Reco_trk*",0);
   fChain->SetBranchStatus("*vtx",0);
   fChain->SetBranchStatus("Gen_mu*",0);

   const int nbins_mid = 10;
   const int nbins_fwd = 11;
   double bins_mid[nbins_mid+1] = {6.5,7,7.5,8,8.5,9,10,12,15,20,30};
   double bins_fwd[nbins_fwd+1] = {3,3.5,4,4.5,5,6.5,8,10,12,15,20,30};

   TFile *f = new TFile(filename, "RECREATE");

   for (int ieta=0; ieta<6; ieta++) {
      int nbins; double *bins;
      if (ieta<5) {nbins = nbins_mid; bins = bins_mid;}
      else {nbins = nbins_fwd; bins = bins_fwd;}
      TString seta = Form("%d_%d",ieta*4,(ieta+1)*4);
      new TH1F(TString("hden_")+seta,TString("hden_")+seta, nbins, bins);
      new TH1F(TString("hnum_")+seta,TString("hnum_")+seta, nbins, bins);

      // all-in-one
      new TH1F(TString("hnum_allpl_")+seta,TString("hnum_allpl_")+seta, nbins, bins);
      new TH1F(TString("hnum_allmi_")+seta,TString("hnum_allmi_")+seta, nbins, bins);
      for (int ivar=1; ivar<=100; ivar++) {
         new TH1F(TString(Form("hnum_all%i_",ivar))+seta,TString(Form("hnum_all%i_",ivar))+seta, nbins, bins);
      }

      // trigger
      new TH1F(TString("hnum_trgpl_")+seta,TString("hnum_trgpl_")+seta, nbins, bins);
      new TH1F(TString("hnum_trgmi_")+seta,TString("hnum_trgmi_")+seta, nbins, bins);
      new TH1F(TString("hnum_trgb_")+seta,TString("hnum_trgb_")+seta, nbins, bins);
      for (int ivar=1; ivar<=100; ivar++) {
         new TH1F(TString(Form("hnum_trg%i_",ivar))+seta,TString(Form("hnum_trg%i_",ivar))+seta, nbins, bins);
      }

      // muon ID
      new TH1F(TString("hnum_muidpl_")+seta,TString("hnum_muidpl_")+seta, nbins, bins);
      new TH1F(TString("hnum_muidmi_")+seta,TString("hnum_muidmi_")+seta, nbins, bins);
      new TH1F(TString("hnum_muidb_")+seta,TString("hnum_muidb_")+seta, nbins, bins);
      for (int ivar=0; ivar<=100; ivar++) {
         new TH1F(TString(Form("hnum_muid%i_",ivar))+seta,TString(Form("hnum_muid%i_",ivar))+seta, nbins, bins);
      }

      // STA
      new TH1F(TString("hnum_stapl_")+seta,TString("hnum_stapl_")+seta, nbins, bins);
      new TH1F(TString("hnum_stami_")+seta,TString("hnum_stami_")+seta, nbins, bins);
      new TH1F(TString("hnum_stab_")+seta,TString("hnum_stab_")+seta, nbins, bins);
      for (int ivar=0; ivar<=100; ivar++) {
         new TH1F(TString(Form("hnum_sta%i_",ivar))+seta,TString(Form("hnum_sta%i_",ivar))+seta, nbins, bins);
      }
   }
   

   TH1D *hpt = new TH1D("hpt","gen pt",100,0,50);
   TH1D *hcent = new TH1D("hcent","hcent",200,0,100);

   double weight = 1.;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if (ientry%10000==0) cout << ientry << endl;
      if (weight != fChain->GetWeight()) {
        weight = fChain->GetWeight();
        cout << "New Weight: " << weight << endl;
      }   
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      // if there's no reco muon is that event, just skip it
      if (Reco_mu_size==0) continue;

      // Get weighting factors
      double NcollWeight = findNcoll(Centrality);

      hcent->Fill(Centrality/2,weight*NcollWeight);

      // loop on the generated dimuons
      for (int igen=0; igen<Gen_QQ_size; igen++) {
         TLorentzVector genpl = *((TLorentzVector*) Gen_QQ_mupl_4mom->At(igen));
         TLorentzVector genmi = *((TLorentzVector*) Gen_QQ_mumi_4mom->At(igen));
         TLorentzVector genmumu = *((TLorentzVector*) Gen_QQ_4mom->At(igen));
         if (igen==0) hpt->Fill(genmumu.Pt(),weight*NcollWeight);

         int irap = 10*fabs(genmumu.Rapidity())/4;
         TString seta = Form("%i_%i",irap*4,(irap+1)*4);
         if (isGlobalMuonInAccept2015(&genmi)&&isGlobalMuonInAccept2015(&genpl)&&fabs(genmumu.Rapidity())<2.4) {
            TString hname = TString("hden_") + seta;
            ((TH1F*) gDirectory->Get(hname))->Fill(genmumu.Pt(),weight*NcollWeight);
         }
      }

      // loop on QQ's: they should be 
      // - opposite sign, 
      // - one leg corresponding to the +/- tag muon found above, 
      // - within [2.7,3.3], 
      // - matched to the trigger, and passing all cuts
      for (int ireco=0; ireco<Reco_QQ_size; ireco++) {
         // does it match our tag(s)? and if yes, is the other leg in acceptance?
         TLorentzVector *tlvrecomupl = (TLorentzVector*) Reco_QQ_mupl_4mom->At(ireco);
         TLorentzVector *tlvrecomumi = (TLorentzVector*) Reco_QQ_mumi_4mom->At(ireco);
         double pt1=tlvrecomupl->Pt();
         double pt2=tlvrecomumi->Pt();
         double eta1=tlvrecomupl->Eta();
         double eta2=tlvrecomumi->Eta();
         TLorentzVector *tlvrecoqq = (TLorentzVector*) Reco_QQ_4mom->At(ireco);
         // dimuon cuts
         if (tlvrecoqq->M()<2.7 || tlvrecoqq->M()>3.3 || fabs(tlvrecoqq->Rapidity())>2.4) continue;
         if (Reco_QQ_sign[ireco] != 0) continue;

         // trigger
         if (!((Reco_QQ_trig[ireco] & trg_probe) == trg_probe && (HLTriggers & trg_probe) == trg_probe)) continue;

         // increment the counter
         if (isGlobalMuonInAccept2015(tlvrecomumi) && isGlobalMuonInAccept2015(tlvrecomupl) && passQualityCuts2015(ireco)) {
            int irap = 10*fabs(tlvrecoqq->Rapidity())/4;
            TString seta = Form("%i_%i",irap*4,(irap+1)*4);
            TH1F *hist=NULL;
            double pt = tlvrecoqq->Pt();
            double y = tlvrecoqq->Rapidity();

            hist = (TH1F*) gDirectory->Get(TString("hnum_")+seta);
            double wnom = tnp_weight_pbpb(pt1,eta1,0)*tnp_weight_pbpb(pt2,eta2,0);
            hist->Fill(pt,weight*NcollWeight*wnom);

            // all-in-one
            hist = (TH1F*) gDirectory->Get(TString("hnum_allpl_")+seta);
            hist->Fill(pt,weight*NcollWeight*tnp_weight_pbpb(pt1,eta1,-1)*tnp_weight_pbpb(pt2,eta2,-1));
            hist = (TH1F*) gDirectory->Get(TString("hnum_allmi_")+seta);
            hist->Fill(pt,weight*NcollWeight*tnp_weight_pbpb(pt1,eta1,-2)*tnp_weight_pbpb(pt2,eta2,-2));
            for (int ivar=1; ivar<=100; ivar++) {
               hist = (TH1F*) gDirectory->Get(TString(Form("hnum_all%i_",ivar))+seta);
               hist->Fill(pt,weight*NcollWeight*tnp_weight_pbpb(pt1,eta1,ivar)*tnp_weight_pbpb(pt2,eta2,ivar));
            }

            // trigger
            hist = (TH1F*) gDirectory->Get(TString("hnum_trgpl_")+seta);
            hist->Fill(pt,weight*NcollWeight*tnp_weight_trg_pbpb(pt1,eta1,-1)*tnp_weight_trg_pbpb(pt2,eta2,-1));
            hist = (TH1F*) gDirectory->Get(TString("hnum_trgmi_")+seta);
            hist->Fill(pt,weight*NcollWeight*tnp_weight_trg_pbpb(pt1,eta1,-2)*tnp_weight_trg_pbpb(pt2,eta2,-2));
            hist = (TH1F*) gDirectory->Get(TString("hnum_trgb_")+seta);
            hist->Fill(pt,weight*NcollWeight*tnp_weight_trg_pbpb(pt1,eta1,-10)*tnp_weight_trg_pbpb(pt2,eta2,-10));
            for (int ivar=1; ivar<=100; ivar++) {
               hist = (TH1F*) gDirectory->Get(TString(Form("hnum_trg%i_",ivar))+seta);
               hist->Fill(pt,weight*NcollWeight*tnp_weight_trg_pbpb(pt1,eta1,ivar)*tnp_weight_trg_pbpb(pt2,eta2,ivar));
            }

            // muon ID
            hist = (TH1F*) gDirectory->Get(TString("hnum_muidpl_")+seta);
            hist->Fill(pt,weight*NcollWeight*wnom*tnp_weight_muid_pbpb(pt1,eta1,-1)*tnp_weight_muid_pbpb(pt2,eta2,-1));
            hist = (TH1F*) gDirectory->Get(TString("hnum_muidmi_")+seta);
            hist->Fill(pt,weight*NcollWeight*wnom*tnp_weight_muid_pbpb(pt1,eta1,-2)*tnp_weight_muid_pbpb(pt2,eta2,-2));
            hist = (TH1F*) gDirectory->Get(TString("hnum_muidb_")+seta);
            hist->Fill(pt,weight*NcollWeight*wnom*tnp_weight_muid_pbpb(pt1,eta1,-10)*tnp_weight_muid_pbpb(pt2,eta2,-10));
            for (int ivar=0; ivar<=100; ivar++) {
               hist = (TH1F*) gDirectory->Get(TString(Form("hnum_muid%i_",ivar))+seta);
               hist->Fill(pt,weight*NcollWeight*wnom*tnp_weight_muid_pbpb(pt1,eta1,ivar)*tnp_weight_muid_pbpb(pt2,eta2,ivar));
            }

            // STA
            hist = (TH1F*) gDirectory->Get(TString("hnum_stapl_")+seta);
            hist->Fill(pt,weight*NcollWeight*wnom*tnp_weight_sta_pp(pt1,eta1,-1)*tnp_weight_sta_pp(pt2,eta2,-1));
            hist = (TH1F*) gDirectory->Get(TString("hnum_stami_")+seta);
            hist->Fill(pt,weight*NcollWeight*wnom*tnp_weight_sta_pp(pt1,eta1,-2)*tnp_weight_sta_pp(pt2,eta2,-2));
            hist = (TH1F*) gDirectory->Get(TString("hnum_stab_")+seta);
            hist->Fill(pt,weight*NcollWeight*wnom*tnp_weight_sta_pp(pt1,eta1,-10)*tnp_weight_sta_pp(pt2,eta2,-10));
            for (int ivar=0; ivar<=100; ivar++) {
               hist = (TH1F*) gDirectory->Get(TString(Form("hnum_sta%i_",ivar))+seta);
               hist->Fill(pt,weight*NcollWeight*wnom*tnp_weight_sta_pp(pt1,eta1,ivar)*tnp_weight_sta_pp(pt2,eta2,ivar));
            }
         }
      }
   }

   f->Write();
   f->Close();
   delete f;
}
