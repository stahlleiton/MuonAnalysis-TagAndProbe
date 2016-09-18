#define ClosureTestPbPb_cxx
#include "ClosureTestPbPb.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"

#include <iostream>

using std::cout;
using std::endl;

const int trg_tag1 = pow(2,4);
const int trg_tag2 = pow(2,5);
const int trg_tag3 = pow(2,6);
const int trg_probe = pow(2,1);//pow(2,0);
const double drmax = 0.1;
const double mumass = 105.6583715e-3;

bool etasel(double eta, int mode) {
   if (mode==0) return true;
   else if (mode==1 && fabs(eta)<1.6) return true;
   else if (mode==2 && fabs(eta)>1.6) return true;
   else return false;
}

double* ClosureTestPbPb::Loop(int nbins, double* pts, double absetamin, double absetamax, int dphimode, int tagmode)
{
   cout << "abseta in [" << absetamin << ", " << absetamax << "]" << endl;
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
   if (fChain == 0) return NULL;

   fChain->SetBranchStatus("*",1);
   // fChain->SetBranchStatus("Reco_trk*",0);
   fChain->SetBranchStatus("*vtx",0);
   fChain->SetBranchStatus("Gen_mu*",0);
   Long64_t nentries = fChain->GetEntriesFast();

   double *res = new double[nbins];
   double *num = new double[nbins];
   double *den = new double[nbins];
   for (int i=0; i<nbins; i++) {
      res[i]=0; num[i]=0; den[i]=0;
   }

   double weight = 1.;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      // if (jentry>1000) break;
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
      double NcollWeight = findCenWeight(Centrality);

      // cout << eventNb << " " << runNb << " " << LS << endl;

      // loop on the generated dimuons
      for (int igen=0; igen<Gen_QQ_size; igen++) {
         TLorentzVector genpl = *((TLorentzVector*) Gen_QQ_mupl_4mom->At(igen));
         TLorentzVector genmi = *((TLorentzVector*) Gen_QQ_mumi_4mom->At(igen));

         if (dphimode != 0 && TVector2::Phi_mpi_pi(genpl.Phi()-genmi.Phi())*dphimode<0) continue;

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
            //    << IsAccept(recomu.Pt(),recomu.Eta()) << endl;
            if (drpl<drmax && drpl<drmi && etasel(tagmode,recomu.Eta()) && Cut(ireco) &&
                  ((Reco_mu_trig[ireco]&trg_tag1) == trg_tag1 ||
                   (Reco_mu_trig[ireco]&trg_tag2) == trg_tag2 ||
                   (Reco_mu_trig[ireco]&trg_tag3) == trg_tag3)
                  && IsAccept(recomu.Pt(), recomu.Eta())) {
               // cout << __LINE__ << " " << Reco_QQ_size << endl;
               isgenpltag = true; tlvrecomatchtagpl = recomu;
            }
            if (drmi<drmax && drmi<drpl && etasel(tagmode,recomu.Eta()) && Cut(ireco) &&
                  ((Reco_mu_trig[ireco]&trg_tag1) == trg_tag1 ||
                   (Reco_mu_trig[ireco]&trg_tag2) == trg_tag2 ||
                   (Reco_mu_trig[ireco]&trg_tag3) == trg_tag3)
                  && IsAccept(recomu.Pt(), recomu.Eta())) {
               // cout << __LINE__ << " " << Reco_QQ_size << endl;
               isgenmitag = true; tlvrecomatchtagmi = recomu;
            }
         }

         // is the positive gen muon a tag, and the negative gen muon in acceptance?
         if (isgenpltag && IsAccept(genmi.Pt(),genmi.Eta()) && fabs(genmi.Eta())>absetamin && fabs(genmi.Eta())<absetamax) {
            for (int ibin=0; ibin<nbins; ibin++) {
               if (genmi.Pt()>pts[ibin] && genmi.Pt()<pts[ibin+1]) den[ibin]+=weight*NcollWeight;
            }
         }
         // is the negative gen muon a tag, and the positive gen muon in acceptance?
         if (isgenmitag && IsAccept(genpl.Pt(),genpl.Eta()) && fabs(genpl.Eta())>absetamin && fabs(genpl.Eta())<absetamax) {
            for (int ibin=0; ibin<nbins; ibin++) {
               if (genpl.Pt()>pts[ibin] && genpl.Pt()<pts[ibin+1]) den[ibin]+=weight*NcollWeight;
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
            //             && IsAccept(tlvrecomumi->Pt(),tlvrecomumi->Eta()) && fabs(tlvrecomumi->Eta())>absetamin && fabs(tlvrecomumi->Eta())<absetamax)
            //       || (isgenmitag && tlvrecomumi->DeltaR(tlvrecomatchtagmi)<1e-1 
            //          && IsAccept(tlvrecomupl->Pt(),tlvrecomupl->Eta()) && fabs(tlvrecomupl->Eta())>absetamin && fabs(tlvrecomupl->Eta())<absetamax))) continue;

            // dimuon cuts
            if (tlvrecoqq->M()<2.7 || tlvrecoqq->M()>3.3) continue;
            if (Reco_QQ_sign[ireco] != 0) continue;

            // trigger
            if ((Reco_QQ_trig[ireco] & trg_probe) != trg_probe) continue;

            // increment the counter
            if (isgenpltag && tlvrecomupl->DeltaR(tlvrecomatchtagpl)<1e-2 && Cut_mumi(ireco)
                  && IsAccept(tlvrecomumi->Pt(),tlvrecomumi->Eta()) && fabs(tlvrecomumi->Eta())>absetamin && fabs(tlvrecomumi->Eta())<absetamax) {
               // trigger: do it on the single muon
               bool oktrig=false;
               for (int ireco2=0; ireco2<Reco_mu_size; ireco2++) {
                  TLorentzVector recomu = *((TLorentzVector*) Reco_mu_4mom->At(ireco2));
                  if (tlvrecomumi->DeltaR(recomu)<1e-2 && (Reco_mu_trig[ireco2] & trg_probe) == trg_probe) oktrig=true;
               }

               if (oktrig) {
                  for (int ibin=0; ibin<nbins; ibin++) {
                     if (tlvrecomumi->Pt()>pts[ibin] && tlvrecomumi->Pt()<pts[ibin+1]) num[ibin]+=weight*NcollWeight;
                  }
               }
            }
            if (isgenmitag && tlvrecomumi->DeltaR(tlvrecomatchtagmi)<1e-2 && Cut_mupl(ireco)
                  && IsAccept(tlvrecomupl->Pt(),tlvrecomupl->Eta()) && fabs(tlvrecomupl->Eta())>absetamin && fabs(tlvrecomupl->Eta())<absetamax) {
               // trigger: do it on the single muon
               bool oktrig=false;
               for (int ireco2=0; ireco2<Reco_mu_size; ireco2++) {
                  TLorentzVector recomu = *((TLorentzVector*) Reco_mu_4mom->At(ireco2));
                  if (tlvrecomupl->DeltaR(recomu)<1e-2 && (Reco_mu_trig[ireco2] & trg_probe) == trg_probe) oktrig=true;
               }

               if (oktrig) {
                  for (int ibin=0; ibin<nbins; ibin++) {
                     if (tlvrecomupl->Pt()>pts[ibin] && tlvrecomupl->Pt()<pts[ibin+1]) num[ibin]+=weight*NcollWeight;
                  }
               }
            }
         }
      }
   }

   for (int i=0; i<nbins; i++) {
      cout << i << ": " << num[i] << " "<< den[i] << endl;
      res[i]= num[i] / den[i];
   }
   return res;
}
