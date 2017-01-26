#define ClosureTestPbPb_cxx
#include "ClosureTestPbPb.h"
#include "TFile.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "tnp_mc.h"

#include <iostream>

using std::cout;
using std::endl;

const int trg_tag1 = pow(2,19);
const int trg_tag2 = pow(2,21);
const int trg_tag3 = pow(2,23);
const int trg_tag4 = pow(2,25);
const int trg_tag5 = pow(2,27);
const int trg_tag6 = pow(2,29);
const int trg_probe = pow(2,0);
const double drmax = 0.1;
const double mumass = 105.6583715e-3;

// define the bins
double bins_00_12[11] = {3.5, 4, 4.5, 5, 5.5, 6.5, 8, 10.5, 14, 18, 30};
double bins_12_18[11] = {2.37, 3.0, 3.5, 4, 4.5, 5., 6., 7.5, 10, 15, 30};
double bins_18_21[13] = {1.8, 2, 2.5, 3, 3.5, 4, 4.5, 5.5, 6.5, 8, 9.5, 13,20};
double bins_21_24[10] = {1.8, 2.2, 2.7, 3.2, 3.7, 4.7, 6.5, 8.5, 11, 20};

void ClosureTestPbPb::Loop(const char* filename, int centmin, int centmax)
{
//   In a ROOT session, you can do:
//      root> .L ClosureTestPbPb.C
//      root> ClosureTestPbPb t
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
   Long64_t nentries = fChain->GetEntriesFast();

   TFile *f = new TFile(filename,"RECREATE");
   f->cd();
   TH1D *hden_00_12 = new TH1D("hden_00_12","hden_00_12",10,bins_00_12);
   TH1D *hden_stawt_00_12 = new TH1D("hden_stawt_00_12","hden_stawt_00_12",10,bins_00_12);
   TH1D *hden_staIDwt_00_12 = new TH1D("hden_staIDwt_00_12","hden_staIDwt_00_12",10,bins_00_12);
   TH1D *hden_staIDtrgwt_00_12 = new TH1D("hden_staIDtrgwt_00_12","hden_staIDtrgwt_00_12",10,bins_00_12);
   TH1D *hnumglb_00_12 = new TH1D("hnumglb_00_12","hnumglb_00_12",10,bins_00_12);
   TH1D *hnumglbID_00_12 = new TH1D("hnumglbID_00_12","hnumglbID_00_12",10,bins_00_12);
   TH1D *hnumglbIDtrg_00_12 = new TH1D("hnumglbIDtrg_00_12","hnumglbIDtrg_00_12",10,bins_00_12);

   TH1D *hden_12_18 = new TH1D("hden_12_18","hden_12_18",10,bins_12_18);
   TH1D *hden_stawt_12_18 = new TH1D("hden_stawt_12_18","hden_stawt_12_18",10,bins_12_18);
   TH1D *hden_staIDwt_12_18 = new TH1D("hden_staIDwt_12_18","hden_staIDwt_12_18",10,bins_12_18);
   TH1D *hden_staIDtrgwt_12_18 = new TH1D("hden_staIDtrgwt_12_18","hden_staIDtrgwt_12_18",10,bins_12_18);
   TH1D *hnumglb_12_18 = new TH1D("hnumglb_12_18","hnumglb_12_18",10,bins_12_18);
   TH1D *hnumglbID_12_18 = new TH1D("hnumglbID_12_18","hnumglbID_12_18",10,bins_12_18);
   TH1D *hnumglbIDtrg_12_18 = new TH1D("hnumglbIDtrg_12_18","hnumglbIDtrg_12_18",10,bins_12_18);
   
   TH1D *hden_18_21 = new TH1D("hden_18_21","hden_18_21",12,bins_18_21);
   TH1D *hden_stawt_18_21 = new TH1D("hden_stawt_18_21","hden_stawt_18_21",12,bins_18_21);
   TH1D *hden_staIDwt_18_21 = new TH1D("hden_staIDwt_18_21","hden_staIDwt_18_21",12,bins_18_21);
   TH1D *hden_staIDtrgwt_18_21 = new TH1D("hden_staIDtrgwt_18_21","hden_staIDtrgwt_18_21",12,bins_18_21);
   TH1D *hnumglb_18_21 = new TH1D("hnumglb_18_21","hnumglb_18_21",12,bins_18_21);
   TH1D *hnumglbID_18_21 = new TH1D("hnumglbID_18_21","hnumglbID_18_21",12,bins_18_21);
   TH1D *hnumglbIDtrg_18_21 = new TH1D("hnumglbIDtrg_18_21","hnumglbIDtrg_18_21",12,bins_18_21);
   
   TH1D *hden_21_24 = new TH1D("hden_21_24","hden_21_24",9,bins_21_24);
   TH1D *hden_stawt_21_24 = new TH1D("hden_stawt_21_24","hden_stawt_21_24",9,bins_21_24);
   TH1D *hden_staIDwt_21_24 = new TH1D("hden_staIDwt_21_24","hden_staIDwt_21_24",9,bins_21_24);
   TH1D *hden_staIDtrgwt_21_24 = new TH1D("hden_staIDtrgwt_21_24","hden_staIDtrgwt_21_24",9,bins_21_24);
   TH1D *hnumglb_21_24 = new TH1D("hnumglb_21_24","hnumglb_21_24",9,bins_21_24);
   TH1D *hnumglbID_21_24 = new TH1D("hnumglbID_21_24","hnumglbID_21_24",9,bins_21_24);
   TH1D *hnumglbIDtrg_21_24 = new TH1D("hnumglbIDtrg_21_24","hnumglbIDtrg_21_24",9,bins_21_24);

   TH1D *hpt = new TH1D("hpt","gen pt",100,0,50);
   TH1D *hcent = new TH1D("hcent","hcent",200,0,100);

   double weight = 1.;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if (ientry%10000==0) cout << ientry << endl;
      if (weight != fChain->GetWeight()) {
        weight = fChain->GetWeight();
        cout << "New Weight: " << weight << endl;
      }   

      // centrality filter
      b_Centrality->GetEntry(ientry);
      if (Centrality<centmin || Centrality>centmax) continue;

      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      // if there's no reco muon is that event, just skip it
      if (Reco_mu_size==0) continue;

      // Get weighting factors
      double NcollWeight = findNcoll(Centrality);

      hcent->Fill(Centrality/2,weight*NcollWeight);

      // cout << eventNb << " " << runNb << " " << LS << endl;

      // loop on the generated dimuons
      for (int igen=0; igen<Gen_QQ_size; igen++) {
         TLorentzVector genpl = *((TLorentzVector*) Gen_QQ_mupl_4mom->At(igen));
         TLorentzVector genmi = *((TLorentzVector*) Gen_QQ_mumi_4mom->At(igen));
         TLorentzVector genmumu = *((TLorentzVector*) Gen_QQ_4mom->At(igen));
         if (igen==0) hpt->Fill(genmumu.Pt(),weight*NcollWeight);

         // is the gen muon associated to a tag? loop on the reco single muons to figure out
         bool isgenpltag=false, isgenmitag=false;
         TLorentzVector tlvrecomatchtagpl, tlvrecomatchtagmi;
         for (int ireco=0; ireco<Reco_mu_size; ireco++) {
            TLorentzVector recomu = *((TLorentzVector*) Reco_mu_4mom->At(ireco));
            double drpl = genpl.DeltaR(recomu);
            double drmi = genmi.DeltaR(recomu);
            // cout << drmi << " " << drpl << " " << recomu.Pt() << " " << recomu.Eta() << ", " 
            //    << (Reco_mu_trig[ireco]&trg_tag1) << " "
            //    << (Reco_mu_trig[ireco]&trg_tag2) << " "
            //    << (Reco_mu_trig[ireco]&trg_tag3) << " "
            //    << isGlobalMuonInAccept2015(&recomu) << endl;
            if (drpl<drmax && drpl<drmi && Cut(ireco) &&
                  ((Reco_mu_trig[ireco]&trg_tag1) == trg_tag1 ||
                   (Reco_mu_trig[ireco]&trg_tag2) == trg_tag2 ||
                   (Reco_mu_trig[ireco]&trg_tag3) == trg_tag3 ||
                   (Reco_mu_trig[ireco]&trg_tag4) == trg_tag4 ||
                   (Reco_mu_trig[ireco]&trg_tag5) == trg_tag5 ||
                   (Reco_mu_trig[ireco]&trg_tag6) == trg_tag6)
                  && isGlobalMuonInAccept2015(&recomu)) {
               // cout << __LINE__ << " " << Reco_QQ_size << endl;
               isgenpltag = true; tlvrecomatchtagpl = recomu;
            }
            if (drmi<drmax && drmi<drpl && Cut(ireco) &&
                  ((Reco_mu_trig[ireco]&trg_tag1) == trg_tag1 ||
                   (Reco_mu_trig[ireco]&trg_tag2) == trg_tag2 ||
                   (Reco_mu_trig[ireco]&trg_tag3) == trg_tag3 ||
                   (Reco_mu_trig[ireco]&trg_tag4) == trg_tag4 ||
                   (Reco_mu_trig[ireco]&trg_tag5) == trg_tag5 ||
                   (Reco_mu_trig[ireco]&trg_tag6) == trg_tag6)
                  && isGlobalMuonInAccept2015(&recomu)) {
               // cout << __LINE__ << " " << Reco_QQ_size << endl;
               isgenmitag = true; tlvrecomatchtagmi = recomu;
            }
         }

         // is the positive gen muon a tag, and the negative gen muon in acceptance?
         if (isgenpltag && isGlobalMuonInAccept2015(&genmi)) {
            double genpt = genmi.Pt(); double geneta = genmi.Eta(); 
            double totweight = weight*NcollWeight;
            if (fabs(geneta)<1.2) {
               hden_00_12->Fill(genpt,totweight);
               totweight *= tnp_mc_sta_pp(genpt,geneta)*tnp_mc_trk_pbpb();
               hden_stawt_00_12->Fill(genpt,totweight);
               totweight *= tnp_mc_muid_pbpb(genpt,geneta);
               hden_staIDwt_00_12->Fill(genpt,totweight);
               totweight *= tnp_mc_trg_pbpb(genpt,geneta);
               hden_staIDtrgwt_00_12->Fill(genpt,totweight);
            } else if (fabs(geneta)<1.8) {
               hden_12_18->Fill(genpt,weight*NcollWeight);
               totweight *= tnp_mc_sta_pp(genpt,geneta)*tnp_mc_trk_pbpb();
               hden_stawt_12_18->Fill(genpt,totweight);
               totweight *= tnp_mc_muid_pbpb(genpt,geneta);
               hden_staIDwt_12_18->Fill(genpt,totweight);
               totweight *= tnp_mc_trg_pbpb(genpt,geneta);
               hden_staIDtrgwt_12_18->Fill(genpt,totweight);
            } else if (fabs(geneta)<2.1) {
               hden_18_21->Fill(genpt,weight*NcollWeight);
               totweight *= tnp_mc_sta_pp(genpt,geneta)*tnp_mc_trk_pbpb();
               hden_stawt_18_21->Fill(genpt,totweight);
               totweight *= tnp_mc_muid_pbpb(genpt,geneta);
               hden_staIDwt_18_21->Fill(genpt,totweight);
               totweight *= tnp_mc_trg_pbpb(genpt,geneta);
               hden_staIDtrgwt_18_21->Fill(genpt,totweight);
            } else if (fabs(geneta)<2.4) {
               hden_21_24->Fill(genpt,weight*NcollWeight);
               totweight *= tnp_mc_sta_pp(genpt,geneta)*tnp_mc_trk_pbpb();
               hden_stawt_21_24->Fill(genpt,totweight);
               totweight *= tnp_mc_muid_pbpb(genpt,geneta);
               hden_staIDwt_21_24->Fill(genpt,totweight);
               totweight *= tnp_mc_trg_pbpb(genpt,geneta);
               hden_staIDtrgwt_21_24->Fill(genpt,totweight);
            }
         }
         // is the negative gen muon a tag, and the positive gen muon in acceptance?
         if (isgenmitag && isGlobalMuonInAccept2015(&genpl)) {
            double genpt = genpl.Pt(); double geneta = genpl.Eta(); 
            double totweight = weight*NcollWeight;
            if (fabs(geneta)<1.2) {
               hden_00_12->Fill(genpt,totweight);
               totweight *= tnp_mc_sta_pp(genpt,geneta)*tnp_mc_trk_pbpb();
               hden_stawt_00_12->Fill(genpt,totweight);
               totweight *= tnp_mc_muid_pbpb(genpt,geneta);
               hden_staIDwt_00_12->Fill(genpt,totweight);
               totweight *= tnp_mc_trg_pbpb(genpt,geneta);
               hden_staIDtrgwt_00_12->Fill(genpt,totweight);
            } else if (fabs(geneta)<1.8) {
               hden_12_18->Fill(genpt,weight*NcollWeight);
               totweight *= tnp_mc_sta_pp(genpt,geneta)*tnp_mc_trk_pbpb();
               hden_stawt_12_18->Fill(genpt,totweight);
               totweight *= tnp_mc_muid_pbpb(genpt,geneta);
               hden_staIDwt_12_18->Fill(genpt,totweight);
               totweight *= tnp_mc_trg_pbpb(genpt,geneta);
               hden_staIDtrgwt_12_18->Fill(genpt,totweight);
            } else if (fabs(geneta)<2.1) {
               hden_18_21->Fill(genpt,weight*NcollWeight);
               totweight *= tnp_mc_sta_pp(genpt,geneta)*tnp_mc_trk_pbpb();
               hden_stawt_18_21->Fill(genpt,totweight);
               totweight *= tnp_mc_muid_pbpb(genpt,geneta);
               hden_staIDwt_18_21->Fill(genpt,totweight);
               totweight *= tnp_mc_trg_pbpb(genpt,geneta);
               hden_staIDtrgwt_18_21->Fill(genpt,totweight);
            } else if (fabs(geneta)<2.4) {
               hden_21_24->Fill(genpt,weight*NcollWeight);
               totweight *= tnp_mc_sta_pp(genpt,geneta)*tnp_mc_trk_pbpb();
               hden_stawt_21_24->Fill(genpt,totweight);
               totweight *= tnp_mc_muid_pbpb(genpt,geneta);
               hden_staIDwt_21_24->Fill(genpt,totweight);
               totweight *= tnp_mc_trg_pbpb(genpt,geneta);
               hden_staIDtrgwt_21_24->Fill(genpt,totweight);
            }
         }
         
         // loop on QQ's: they should be 
         // - opposite sign, 
         // - one leg corresponding to the +/- tag muon found above, 
         // - within [2.7,3.3], 
         // - matched to the trigger, 
         // - and the other leg than the tag should be in acceptance
         for (int ireco=0; ireco<Reco_QQ_size; ireco++) {
            // does it match our tag(s)? and if yes, is the other leg in acceptance?
            TLorentzVector *tlvrecomupl = (TLorentzVector*) Reco_QQ_mupl_4mom->At(ireco);
            TLorentzVector *tlvrecomumi = (TLorentzVector*) Reco_QQ_mumi_4mom->At(ireco);
            TLorentzVector *tlvrecoqq = (TLorentzVector*) Reco_QQ_4mom->At(ireco);
            // cout << isgenpltag << " " << isgenmitag << " " << tlvrecoqq->M() << endl;
            // if (!((isgenpltag && tlvrecomupl->DeltaR(tlvrecomatchtagpl)<1e-1
            //             && isGlobalMuonInAccept2015(tlvrecomumi->Pt(),tlvrecomumi->Eta()) && fabs(tlvrecomumi->Eta())>absetamin && fabs(tlvrecomumi->Eta())<absetamax)
            //       || (isgenmitag && tlvrecomumi->DeltaR(tlvrecomatchtagmi)<1e-1 
            //          && isGlobalMuonInAccept2015(tlvrecomupl->Pt(),tlvrecomupl->Eta()) && fabs(tlvrecomupl->Eta())>absetamin && fabs(tlvrecomupl->Eta())<absetamax))) continue;

            // dimuon cuts
            if (tlvrecoqq->M()<2.7 || tlvrecoqq->M()>3.3) continue;
            if (Reco_QQ_sign[ireco] != 0) continue;

            bool okTrg=false;

            // trigger
            if ((Reco_QQ_trig[ireco] & trg_probe) == trg_probe) okTrg=true;

            // increment the counter
            if (isgenpltag && tlvrecomupl->DeltaR(tlvrecomatchtagpl)<1e-2 && isGlobalMuonInAccept2015(tlvrecomumi)) {
               if (fabs(tlvrecomumi->Eta())<1.2) hnumglb_00_12->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
               else if (fabs(tlvrecomumi->Eta())<1.8) hnumglb_12_18->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
               else if (fabs(tlvrecomumi->Eta())<2.1) hnumglb_18_21->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
               else if (fabs(tlvrecomumi->Eta())<2.4) hnumglb_21_24->Fill(tlvrecomumi->Pt(),weight*NcollWeight);

               // ID
               if (Cut_mumi(ireco)) {
                  if (fabs(tlvrecomumi->Eta())<1.2) hnumglbID_00_12->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
                  else if (fabs(tlvrecomumi->Eta())<1.8) hnumglbID_12_18->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
                  else if (fabs(tlvrecomumi->Eta())<2.1) hnumglbID_18_21->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
                  else if (fabs(tlvrecomumi->Eta())<2.4) hnumglbID_21_24->Fill(tlvrecomumi->Pt(),weight*NcollWeight);

                  // trigger: do it on the single muon
                  bool oktrig=false;
                  for (int ireco2=0; ireco2<Reco_mu_size; ireco2++) {
                     TLorentzVector recomu = *((TLorentzVector*) Reco_mu_4mom->At(ireco2));
                     if (tlvrecomumi->DeltaR(recomu)<1e-2 && (Reco_mu_trig[ireco2] & trg_probe) == trg_probe) oktrig=true;
                  }

                  if (oktrig && okTrg) {
                     if (fabs(tlvrecomumi->Eta())<1.2) hnumglbIDtrg_00_12->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
                     else if (fabs(tlvrecomumi->Eta())<1.8) hnumglbIDtrg_12_18->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
                     else if (fabs(tlvrecomumi->Eta())<2.1) hnumglbIDtrg_18_21->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
                     else if (fabs(tlvrecomumi->Eta())<2.4) hnumglbIDtrg_21_24->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
                  }
               }
            } // isgenpltag
            if (isgenmitag && tlvrecomumi->DeltaR(tlvrecomatchtagmi)<1e-2 && isGlobalMuonInAccept2015(tlvrecomupl)) {
               if (fabs(tlvrecomupl->Eta())<1.2) hnumglb_00_12->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
               else if (fabs(tlvrecomupl->Eta())<1.8) hnumglb_12_18->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
               else if (fabs(tlvrecomupl->Eta())<2.1) hnumglb_18_21->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
               else if (fabs(tlvrecomupl->Eta())<2.4) hnumglb_21_24->Fill(tlvrecomupl->Pt(),weight*NcollWeight);

               // ID
               if (Cut_mupl(ireco)) {
                  if (fabs(tlvrecomupl->Eta())<1.2) hnumglbID_00_12->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
                  else if (fabs(tlvrecomupl->Eta())<1.8) hnumglbID_12_18->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
                  else if (fabs(tlvrecomupl->Eta())<2.1) hnumglbID_18_21->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
                  else if (fabs(tlvrecomupl->Eta())<2.4) hnumglbID_21_24->Fill(tlvrecomupl->Pt(),weight*NcollWeight);

                  // trigger: do it on the single muon
                  bool oktrig=false;
                  for (int ireco2=0; ireco2<Reco_mu_size; ireco2++) {
                     TLorentzVector recomu = *((TLorentzVector*) Reco_mu_4mom->At(ireco2));
                     if (tlvrecomupl->DeltaR(recomu)<1e-2 && (Reco_mu_trig[ireco2] & trg_probe) == trg_probe) oktrig=true;
                  }

                  if (oktrig && okTrg) {
                     if (fabs(tlvrecomupl->Eta())<1.2) hnumglbIDtrg_00_12->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
                     else if (fabs(tlvrecomupl->Eta())<1.8) hnumglbIDtrg_12_18->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
                     else if (fabs(tlvrecomupl->Eta())<2.1) hnumglbIDtrg_18_21->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
                     else if (fabs(tlvrecomupl->Eta())<2.4) hnumglbIDtrg_21_24->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
                  }
               }
            } // isgenmitag
         } // recoQQsize (probe) loop
      } // genQQsize loop
   } // event loop


   f->Write();
   f->Close();
   delete f;
}
