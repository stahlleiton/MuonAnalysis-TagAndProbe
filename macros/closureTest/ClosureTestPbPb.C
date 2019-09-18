#define ClosureTestPbPb_cxx
#include "ClosureTestPbPb.h"
#include "TFile.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "tnp_mc_lowptPbPb.h"

#include <iostream>

using std::cout;
using std::endl;

const ULong64_t trg_tag1 = pow(2,20);
const ULong64_t trg_tag2 = pow(2,21);
const ULong64_t trg_tag3 = pow(2,22);
const ULong64_t trg_tag4 = pow(2,23);
const ULong64_t trg_tag5 = pow(2,24);
const ULong64_t trg_tag6 = pow(2,25);
const ULong64_t trg_probe_l2Jpsi = pow(2,26);
const ULong64_t trg_probe_l3Jpsi = pow(2,27);
const ULong64_t trg_probe_DMOpen = pow(2,0);

ULong64_t trg_probe = pow(2,0);
ULong64_t trg_probe_QQ = pow(2,0);

const double drmax = 0.1;
const double mumass = 105.6583715e-3;

// define the bins
double bins_0_12[11] = {3.5, 4, 4.5, 5, 5.5, 6.5, 8, 10.5, 14, 18, 30};
double bins_12_18[11] = {2.37, 3.0, 3.5, 4, 4.5, 5., 6., 7.5, 10, 15, 30};
double bins_18_21[13] = {1.8, 2, 2.5, 3, 3.5, 4, 4.5, 5.5, 6.5, 8, 9.5, 13,20};
double bins_21_24[10] = {1.8, 2.2, 2.7, 3.2, 3.7, 4.7, 6.5, 8.5, 11, 20};

void ClosureTestPbPb::Loop(const char* filename, int centmin, int centmax, int trigIdx)
{
  if (trigIdx == 0) trg_probe = trg_probe_l2Jpsi;
  else if (trigIdx == 1) trg_probe = trg_probe_l3Jpsi;
  else if (trigIdx == 4) trg_probe = trg_probe_DMOpen;
  if (trigIdx<=1) trg_probe_QQ = pow(2,12);

  if (fChain == 0) return;
  fChain->SetBranchStatus("*",1);
  Long64_t nentries = fChain->GetEntries();
  nentries = 5000000;

  TFile *f = new TFile(filename,"RECREATE");
  f->cd();
  TH1D *hden_0_12 = new TH1D("hden_0_12","hden_0_12",10,bins_0_12); hden_0_12->Sumw2();
  TH1D *hden_trkwt_0_12 = new TH1D("hden_trkwt_0_12","hden_trkwt_0_12",10,bins_0_12); hden_trkwt_0_12->Sumw2();
  TH1D *hden_trkIDwt_0_12 = new TH1D("hden_trkIDwt_0_12","hden_trkIDwt_0_12",10,bins_0_12); hden_trkIDwt_0_12->Sumw2();
  TH1D *hden_trkIDtrgwt_0_12 = new TH1D("hden_trkIDtrgwt_0_12","hden_trkIDtrgwt_0_12",10,bins_0_12); hden_trkIDtrgwt_0_12->Sumw2();
  TH1D *hnum_0_12 = new TH1D("hnum_0_12","hnum_0_12",10,bins_0_12); hnum_0_12->Sumw2();
  TH1D *hnumtrk_0_12 = new TH1D("hnumtrk_0_12","hnumtrk_0_12",10,bins_0_12); hnumtrk_0_12->Sumw2();
  TH1D *hnumtrkID_0_12 = new TH1D("hnumtrkID_0_12","hnumtrkID_0_12",10,bins_0_12); hnumtrkID_0_12->Sumw2();
  TH1D *hnumtrkIDtrg_0_12 = new TH1D("hnumtrkIDtrg_0_12","hnumtrkIDtrg_0_12",10,bins_0_12); hnumtrkIDtrg_0_12->Sumw2();

  TH1D *hden_12_18 = new TH1D("hden_12_18","hden_12_18",10,bins_12_18); hden_12_18->Sumw2();
  TH1D *hden_trkwt_12_18 = new TH1D("hden_trkwt_12_18","hden_trkwt_12_18",10,bins_12_18); hden_trkwt_12_18->Sumw2();
  TH1D *hden_trkIDwt_12_18 = new TH1D("hden_trkIDwt_12_18","hden_trkIDwt_12_18",10,bins_12_18); hden_trkIDwt_12_18->Sumw2();
  TH1D *hden_trkIDtrgwt_12_18 = new TH1D("hden_trkIDtrgwt_12_18","hden_trkIDtrgwt_12_18",10,bins_12_18); hden_trkIDtrgwt_12_18->Sumw2();
  TH1D *hnum_12_18 = new TH1D("hnum_12_18","hnum_12_18",10,bins_12_18); hnum_12_18->Sumw2();
  TH1D *hnumtrk_12_18 = new TH1D("hnumtrk_12_18","hnumtrk_12_18",10,bins_12_18); hnumtrk_12_18->Sumw2();
  TH1D *hnumtrkID_12_18 = new TH1D("hnumtrkID_12_18","hnumtrkID_12_18",10,bins_12_18); hnumtrkID_12_18->Sumw2();
  TH1D *hnumtrkIDtrg_12_18 = new TH1D("hnumtrkIDtrg_12_18","hnumtrkIDtrg_12_18",10,bins_12_18); hnumtrkID_12_18->Sumw2();
   
  TH1D *hden_18_21 = new TH1D("hden_18_21","hden_18_21",12,bins_18_21); hden_18_21->Sumw2();
  TH1D *hden_trkwt_18_21 = new TH1D("hden_trkwt_18_21","hden_trkwt_18_21",12,bins_18_21); hden_trkwt_18_21->Sumw2();
  TH1D *hden_trkIDwt_18_21 = new TH1D("hden_trkIDwt_18_21","hden_trkIDwt_18_21",12,bins_18_21); hden_trkIDwt_18_21->Sumw2();
  TH1D *hden_trkIDtrgwt_18_21 = new TH1D("hden_trkIDtrgwt_18_21","hden_trkIDtrgwt_18_21",12,bins_18_21); hden_trkIDtrgwt_18_21->Sumw2();
  TH1D *hnum_18_21 = new TH1D("hnum_18_21","hnum_18_21",12,bins_18_21); hnum_18_21->Sumw2();
  TH1D *hnumtrk_18_21 = new TH1D("hnumtrk_18_21","hnumtrk_18_21",12,bins_18_21); hnumtrk_18_21->Sumw2();
  TH1D *hnumtrkID_18_21 = new TH1D("hnumtrkID_18_21","hnumtrkID_18_21",12,bins_18_21); hnumtrkID_18_21->Sumw2();
  TH1D *hnumtrkIDtrg_18_21 = new TH1D("hnumtrkIDtrg_18_21","hnumtrkIDtrg_18_21",12,bins_18_21); hnumtrkIDtrg_18_21->Sumw2();
   
  TH1D *hden_21_24 = new TH1D("hden_21_24","hden_21_24",9,bins_21_24); hden_21_24->Sumw2();
  TH1D *hden_trkwt_21_24 = new TH1D("hden_trkwt_21_24","hden_trkwt_21_24",9,bins_21_24); hden_trkwt_21_24->Sumw2();
  TH1D *hden_trkIDwt_21_24 = new TH1D("hden_trkIDwt_21_24","hden_trkIDwt_21_24",9,bins_21_24); hden_trkIDwt_21_24->Sumw2();
  TH1D *hden_trkIDtrgwt_21_24 = new TH1D("hden_trkIDtrgwt_21_24","hden_trkIDtrgwt_21_24",9,bins_21_24); hden_trkIDtrgwt_21_24->Sumw2();
  TH1D *hnum_21_24 = new TH1D("hnum_21_24","hnum_21_24",9,bins_21_24); hnum_21_24->Sumw2();
  TH1D *hnumtrk_21_24 = new TH1D("hnumtrk_21_24","hnumtrk_21_24",9,bins_21_24); hnumtrk_21_24->Sumw2();
  TH1D *hnumtrkID_21_24 = new TH1D("hnumtrkID_21_24","hnumtrkID_21_24",9,bins_21_24); hnumtrkID_21_24->Sumw2();
  TH1D *hnumtrkIDtrg_21_24 = new TH1D("hnumtrkIDtrg_21_24","hnumtrkIDtrg_21_24",9,bins_21_24); hnumtrkIDtrg_21_24->Sumw2();

  TH1D *hpt = new TH1D("hpt","gen pt",10,0,50);
  TH1D *hcent = new TH1D("hcent","hcent",100,0,100);

  double weight = 1.;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    if (ientry%1000000==0) cout << ientry <<"/"<<nentries<< endl;

    nb = fChain->GetEntry(jentry);   nbytes += nb;

    // centrality filter
    Centrality = getMCHiBinFromhiHF(hiHF);
    if (Centrality < centmin || Centrality > centmax) continue;
    //cout <<"centrality = "<<Centrality<<endl;

    // if there's no reco muon is that event, just skip it
    if (Reco_mu_size==0) continue;

    //cout <<"Reco_mu_size = "<<Reco_mu_size<<endl;
    // Get weighting factors
    weight = Gen_weight;
    double NcollWeight = findNcoll(Centrality);

    hcent->Fill(Centrality/2,weight*NcollWeight);

    // loop on the generated dimuons
    for (int igen=0; igen<Gen_QQ_size; igen++) {
      TLorentzVector genpl = *((TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mupl_idx[igen]));
      TLorentzVector genmi = *((TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mumi_idx[igen]));
      TLorentzVector genmumu = *((TLorentzVector*) Gen_QQ_4mom->At(igen));
      if (igen==0) hpt->Fill(genmumu.Pt(),weight*NcollWeight);

      // is the gen muon associated to a tag? loop on the reco single muons to figure out
      bool isgenpltag=false, isgenmitag=false;
      TLorentzVector tlvrecomatchtagpl, tlvrecomatchtagmi;

      int ireco = Gen_QQ_whichRec[igen];
      int recomuplIdx = Gen_mu_whichRec[Gen_QQ_mupl_idx[igen]];
      int recomumiIdx = Gen_mu_whichRec[Gen_QQ_mumi_idx[igen]];


      if (recomuplIdx>-1){
	TLorentzVector recomu = *((TLorentzVector*) Reco_mu_4mom->At(recomuplIdx));

	if (CutSgMuon(recomuplIdx) &&
	    (
	     ((HLTriggers&trg_tag1)>0 && (Reco_mu_trig[recomuplIdx]&trg_tag1)>0) ||
	     ((HLTriggers&trg_tag2)>0 && (Reco_mu_trig[recomuplIdx]&trg_tag2)>0) ||
	     ((HLTriggers&trg_tag3)>0 && (Reco_mu_trig[recomuplIdx]&trg_tag3)>0) ||
	     ((HLTriggers&trg_tag4)>0 && (Reco_mu_trig[recomuplIdx]&trg_tag4)>0) ||
	     ((HLTriggers&trg_tag5)>0 && (Reco_mu_trig[recomuplIdx]&trg_tag5)>0) ||
	     ((HLTriggers&trg_tag6)>0 && (Reco_mu_trig[recomuplIdx]&trg_tag6)>0))
	    && isGlobalMuonInTightAccept2018(&recomu)) {  
	  //cout << " mupl is tag" << endl;
	  isgenpltag = true; tlvrecomatchtagpl = recomu;
	}
      }
      if (recomumiIdx>-1){
	TLorentzVector recomu = *((TLorentzVector*) Reco_mu_4mom->At(recomumiIdx));

	if (CutSgMuon(recomumiIdx) &&
	    (
	     ((HLTriggers&trg_tag1)>0 && (Reco_mu_trig[recomumiIdx]&trg_tag1)>0) ||
	     ((HLTriggers&trg_tag2)>0 && (Reco_mu_trig[recomumiIdx]&trg_tag2)>0) ||
	     ((HLTriggers&trg_tag3)>0 && (Reco_mu_trig[recomumiIdx]&trg_tag3)>0) ||
	     ((HLTriggers&trg_tag4)>0 && (Reco_mu_trig[recomumiIdx]&trg_tag4)>0) ||
	     ((HLTriggers&trg_tag5)>0 && (Reco_mu_trig[recomumiIdx]&trg_tag5)>0) ||
	     ((HLTriggers&trg_tag6)>0 && (Reco_mu_trig[recomumiIdx]&trg_tag6)>0))
	    && isGlobalMuonInTightAccept2018(&recomu)) {
	  //cout << " mumi is tag" << endl;
	  isgenmitag = true; tlvrecomatchtagmi = recomu;
	}
      }
      // is the positive gen muon a tag, and the negative gen muon in acceptance?
      if (isgenpltag && isGlobalMuonInTightAccept2018(&genmi)) {
	double genpt = genmi.Pt(); double geneta = genmi.Eta(); 
	double totweight = weight*NcollWeight; 
	if (fabs(geneta)<1.2) {
	  hden_0_12->Fill(genpt,totweight);
	  //totweight *= tnp_mc_sta_pbpb()*tnp_mc_trk_pbpb(geneta);
	  hden_trkwt_0_12->Fill(genpt,totweight);
	  totweight *= tnp_mc_muid_pbpb(genpt,geneta);
	  hden_trkIDwt_0_12->Fill(genpt,totweight);
	  totweight *= tnp_mc_trg_pbpb(genpt,geneta,trigIdx);
	  hden_trkIDtrgwt_0_12->Fill(genpt,totweight);
	} else if (fabs(geneta)<1.8) {
	  hden_12_18->Fill(genpt,weight*NcollWeight);
	  //totweight *= tnp_mc_sta_pbpb()*tnp_mc_trk_pbpb(geneta);
	  hden_trkwt_12_18->Fill(genpt,totweight);
	  totweight *= tnp_mc_muid_pbpb(genpt,geneta);
	  hden_trkIDwt_12_18->Fill(genpt,totweight);
	  totweight *= tnp_mc_trg_pbpb(genpt,geneta,trigIdx);
	  hden_trkIDtrgwt_12_18->Fill(genpt,totweight);
	} else if (fabs(geneta)<2.1) {
	  hden_18_21->Fill(genpt,weight*NcollWeight);
	  //totweight *= tnp_mc_sta_pbpb()*tnp_mc_trk_pbpb(geneta);
	  hden_trkwt_18_21->Fill(genpt,totweight);
	  totweight *= tnp_mc_muid_pbpb(genpt,geneta);
	  hden_trkIDwt_18_21->Fill(genpt,totweight);
	  totweight *= tnp_mc_trg_pbpb(genpt,geneta,trigIdx);
	  hden_trkIDtrgwt_18_21->Fill(genpt,totweight);
	} else if (fabs(geneta)<2.4) {
	  hden_21_24->Fill(genpt,weight*NcollWeight);
	  //totweight *= tnp_mc_sta_pbpb()*tnp_mc_trk_pbpb(geneta);
	  hden_trkwt_21_24->Fill(genpt,totweight);
	  totweight *= tnp_mc_muid_pbpb(genpt,geneta);
	  hden_trkIDwt_21_24->Fill(genpt,totweight);
	  totweight *= tnp_mc_trg_pbpb(genpt,geneta,trigIdx);
	  hden_trkIDtrgwt_21_24->Fill(genpt,totweight);
	}
      }
      // is the negative gen muon a tag, and the positive gen muon in acceptance?
      if (isgenmitag && isGlobalMuonInTightAccept2018(&genpl)) {
	double genpt = genpl.Pt(); double geneta = genpl.Eta(); 
	double totweight = weight*NcollWeight;
	if (fabs(geneta)<1.2) {
	  hden_0_12->Fill(genpt,totweight);
	  //totweight *= tnp_mc_sta_pbpb()*tnp_mc_trk_pbpb(geneta);
	  hden_trkwt_0_12->Fill(genpt,totweight);
	  totweight *= tnp_mc_muid_pbpb(genpt,geneta);
	  hden_trkIDwt_0_12->Fill(genpt,totweight);
	  totweight *= tnp_mc_trg_pbpb(genpt,geneta,trigIdx);
	  hden_trkIDtrgwt_0_12->Fill(genpt,totweight);
	} else if (fabs(geneta)<1.8) {
	  hden_12_18->Fill(genpt,weight*NcollWeight);
	  //totweight *= tnp_mc_sta_pbpb()*tnp_mc_trk_pbpb(geneta);
	  hden_trkwt_12_18->Fill(genpt,totweight);
	  totweight *= tnp_mc_muid_pbpb(genpt,geneta);
	  hden_trkIDwt_12_18->Fill(genpt,totweight);
	  totweight *= tnp_mc_trg_pbpb(genpt,geneta,trigIdx);
	  hden_trkIDtrgwt_12_18->Fill(genpt,totweight);
	} else if (fabs(geneta)<2.1) {
	  hden_18_21->Fill(genpt,weight*NcollWeight);
	  //totweight *= tnp_mc_sta_pbpb()*tnp_mc_trk_pbpb(geneta);
	  hden_trkwt_18_21->Fill(genpt,totweight);
	  totweight *= tnp_mc_muid_pbpb(genpt,geneta);
	  hden_trkIDwt_18_21->Fill(genpt,totweight);
	  totweight *= tnp_mc_trg_pbpb(genpt,geneta,trigIdx);
	  hden_trkIDtrgwt_18_21->Fill(genpt,totweight);
	} else if (fabs(geneta)<2.4) {
	  hden_21_24->Fill(genpt,weight*NcollWeight);
	  //totweight *= tnp_mc_sta_pbpb()*tnp_mc_trk_pbpb(geneta);
	  hden_trkwt_21_24->Fill(genpt,totweight);
	  totweight *= tnp_mc_muid_pbpb(genpt,geneta);
	  hden_trkIDwt_21_24->Fill(genpt,totweight);
	  totweight *= tnp_mc_trg_pbpb(genpt,geneta,trigIdx);
	  hden_trkIDtrgwt_21_24->Fill(genpt,totweight);
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
	TLorentzVector *tlvrecomupl = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mupl_idx[ireco]);
	TLorentzVector *tlvrecomumi = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mupl_idx[ireco]);
	TLorentzVector *tlvrecoqq = (TLorentzVector*) Reco_QQ_4mom->At(ireco);
	// dimuon cuts
	if (tlvrecoqq->M()<2.7 || tlvrecoqq->M()>3.3) continue;
	if (Reco_QQ_sign[ireco] != 0) continue;

	bool okTrg=false;

	// trigger
	if ((Reco_QQ_trig[ireco]&trg_probe_QQ) == trg_probe_QQ && (HLTriggers&trg_probe_QQ)>0) 
	  okTrg=true;

	// increment the counter
	if (isgenpltag && tlvrecomupl->DeltaR(tlvrecomatchtagpl)<1e-2 && isGlobalMuonInTightAccept2018(tlvrecomumi) && (Reco_mu_SelectionType[Reco_QQ_mumi_idx[ireco]]&4)>0) {
	  if (fabs(tlvrecomumi->Eta())<1.2) hnum_0_12->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	  else if (fabs(tlvrecomumi->Eta())<1.8) hnum_12_18->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	  else if (fabs(tlvrecomumi->Eta())<2.1) hnum_18_21->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	  else if (fabs(tlvrecomumi->Eta())<2.4) hnum_21_24->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	  //Trk //check if global
	  if ((Reco_mu_SelectionType[Reco_QQ_mumi_idx[ireco]]&2)>0){
	    if (fabs(tlvrecomumi->Eta())<1.2) hnumtrk_0_12->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	    else if (fabs(tlvrecomumi->Eta())<1.8) hnumtrk_12_18->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	    else if (fabs(tlvrecomumi->Eta())<2.1) hnumtrk_18_21->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	    else if (fabs(tlvrecomumi->Eta())<2.4) hnumtrk_21_24->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	      
	    // ID
	    if (Cut_muplmi(Reco_QQ_mumi_idx[ireco])) {
	      if (fabs(tlvrecomumi->Eta())<1.2) hnumtrkID_0_12->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	      else if (fabs(tlvrecomumi->Eta())<1.8) hnumtrkID_12_18->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	      else if (fabs(tlvrecomumi->Eta())<2.1) hnumtrkID_18_21->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	      else if (fabs(tlvrecomumi->Eta())<2.4) hnumtrkID_21_24->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	      
	      // trigger: do it on the single muon
	      bool oktrig=false;
	      /*
	      for (int ireco2=0; ireco2<Reco_mu_size; ireco2++) {
		TLorentzVector recomu = *((TLorentzVector*) Reco_mu_4mom->At(ireco2));
		if (tlvrecomumi->DeltaR(recomu)<1e-2 && (Reco_mu_trig[ireco2]&((ULong64_t)trg_probe)) == ((ULong64_t)trg_probe)) oktrig=true;
	      }
	      */
	      if ((Reco_mu_trig[Reco_QQ_mupl_idx[ireco]]&((ULong64_t)trg_probe)) == ((ULong64_t)trg_probe)) oktrig=true;
	      if (oktrig && okTrg) {
		if (fabs(tlvrecomumi->Eta())<1.2) hnumtrkIDtrg_0_12->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
		else if (fabs(tlvrecomumi->Eta())<1.8) hnumtrkIDtrg_12_18->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
		else if (fabs(tlvrecomumi->Eta())<2.1) hnumtrkIDtrg_18_21->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
		else if (fabs(tlvrecomumi->Eta())<2.4) hnumtrkIDtrg_21_24->Fill(tlvrecomumi->Pt(),weight*NcollWeight);
	      }
	    }
	  }
	} // isgenpltag
	if (isgenmitag && tlvrecomumi->DeltaR(tlvrecomatchtagmi)<1e-2 && isGlobalMuonInTightAccept2018(tlvrecomupl) && (Reco_mu_SelectionType[Reco_QQ_mupl_idx[ireco]]&4)>0) {
	  if (fabs(tlvrecomupl->Eta())<1.2) hnum_0_12->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	  else if (fabs(tlvrecomupl->Eta())<1.8) hnum_12_18->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	  else if (fabs(tlvrecomupl->Eta())<2.1) hnum_18_21->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	  else if (fabs(tlvrecomupl->Eta())<2.4) hnum_21_24->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	  //Trk //check if global
	  if ((Reco_mu_SelectionType[Reco_QQ_mupl_idx[ireco]]&2)>0){
	    if (fabs(tlvrecomupl->Eta())<1.2) hnumtrk_0_12->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	    else if (fabs(tlvrecomupl->Eta())<1.8) hnumtrk_12_18->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	    else if (fabs(tlvrecomupl->Eta())<2.1) hnumtrk_18_21->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	    else if (fabs(tlvrecomupl->Eta())<2.4) hnumtrk_21_24->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	    
	    // ID
	    if (Cut_muplmi(Reco_QQ_mupl_idx[ireco])) {
	      if (fabs(tlvrecomupl->Eta())<1.2) hnumtrkID_0_12->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	      else if (fabs(tlvrecomupl->Eta())<1.8) hnumtrkID_12_18->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	      else if (fabs(tlvrecomupl->Eta())<2.1) hnumtrkID_18_21->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	      else if (fabs(tlvrecomupl->Eta())<2.4) hnumtrkID_21_24->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	      
	      // trigger: do it on the single muon
	      bool oktrig=false;
	      /*
	      for (int ireco2=0; ireco2<Reco_mu_size; ireco2++) {
		TLorentzVector recomu = *((TLorentzVector*) Reco_mu_4mom->At(ireco2));
		if (tlvrecomupl->DeltaR(recomu)<1e-2 && (Reco_mu_trig[ireco2]&((ULong64_t)trg_probe)) == ((ULong64_t)trg_probe)) oktrig=true;
	      }
	      */
	      if ((Reco_mu_trig[Reco_QQ_mupl_idx[ireco]]&((ULong64_t)trg_probe)) == ((ULong64_t)trg_probe)) oktrig=true;
	      if (oktrig && okTrg) {
		if (fabs(tlvrecomupl->Eta())<1.2) hnumtrkIDtrg_0_12->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
		else if (fabs(tlvrecomupl->Eta())<1.8) hnumtrkIDtrg_12_18->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
		else if (fabs(tlvrecomupl->Eta())<2.1) hnumtrkIDtrg_18_21->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
		else if (fabs(tlvrecomupl->Eta())<2.4) hnumtrkIDtrg_21_24->Fill(tlvrecomupl->Pt(),weight*NcollWeight);
	      }
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
