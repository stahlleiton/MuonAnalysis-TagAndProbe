#define ClosureTestPbPb_cxx
#include "ClosureTestPbPb.h"
#include "TFile.h"
#include <TH1.h>
#include "TEfficiency.h"
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "tnp_weight.h"
#include "helper.h"
#include <iostream>

void ClosureTestPbPb::Loop(const std::string& filename)
{
  // Derive the weight normalization
  if (fChain == 0) return;
  fChain->SetBranchStatus("*", 0);
  fChain->SetBranchStatus("SumET_HF", 1);
  fChain->SetBranchStatus("Gen_weight", 1);
  const Long64_t& nentries = fChain->GetEntries();
  double sumWeight = 0.;
  for (Long64_t jentry=0; jentry<nentries; jentry++) {
    if (LoadTree(jentry) < 0) { std::cout << "[ERROR] Entry: " << jentry << " is corrupted" << std::endl; return; }
    fChain->GetEntry(jentry);
    const auto& cntBin = getMCHiBinFromhiHF(hiHF);
    const auto& NcollWeight = findNcoll(cntBin);
    sumWeight += NcollWeight*Gen_weight;
  }
  sumWeight = (nentries/sumWeight);
    
  // Initialize all the branches
  fChain->SetBranchStatus("*", 0);
  fChain->SetBranchStatus("SumET_HF", 1);
  fChain->SetBranchStatus("HLTriggers", 1);
  fChain->SetBranchStatus("Gen_weight", 1);
  fChain->SetBranchStatus("Reco_mu_trig", 1);
  fChain->SetBranchStatus("Reco_mu_SelectionType", 1);
  fChain->SetBranchStatus("Reco_mu_isPF", 1);
  fChain->SetBranchStatus("Reco_mu_normChi2_global", 1);
  fChain->SetBranchStatus("Reco_mu_nMuValHits", 1);
  fChain->SetBranchStatus("Reco_mu_StationsMatched", 1);
  fChain->SetBranchStatus("Reco_mu_dxy", 1);
  fChain->SetBranchStatus("Reco_mu_dz", 1);
  fChain->SetBranchStatus("Reco_mu_nPixValHits", 1);
  fChain->SetBranchStatus("Reco_mu_nTrkWMea", 1);
  fChain->SetBranchStatus("Reco_trk_size", 1);
  fChain->SetBranchStatus("Reco_trk_genIdx", 1);
  fChain->SetBranchStatus("Reco_trk_origAlgo", 1);
  fChain->SetBranchStatus("Reco_trk_nTrkWMea", 1);
  fChain->SetBranchStatus("Reco_trk_nPixValHits", 1);
  fChain->SetBranchStatus("Gen_mu_size", 1);
  fChain->SetBranchStatus("Gen_mu_4mom", 1);
  fChain->SetBranchStatus("Gen_mu_whichRec", 1);
  
  // Initialize the TEfficiency objects
  std::map< std::string , std::map< std::string , std::map< anaBinT , TEfficiency > > > effM;
  for (const auto& e : {"Trd", "TnP"}) {
    for (const auto& t : effType) {
      for (const auto& c : centBins) {
	for (const auto& b : etaPtBins) {
	  const auto& bin = anaBinT({c, b.first});
	  const auto& etaMin = (b.first.first>2.4 ? b.second[0] : b.first.first);
	  const auto& etaMax = (b.first.first>2.4 ? b.second[b.second.size()-1] : b.first.second);
	  const auto& name = Form("eff%s_%s_Cent_%.0f_%.0f_Eta_%.0f_%.0f", e, t.c_str(), c.first, c.second, etaMin*10., etaMax*10.);
	  effM[e][t][bin].SetName(name);
	  effM.at(e).at(t).at(bin).SetBins(b.second.size()-1, b.second.data());
	  effM.at(e).at(t).at(bin).SetUseWeightedEvents(true);
	  //effM.at(e).at(t).at(bin).SetStatisticOption(TEfficiency::kBJeffrey);
	}
      }
    }
  }

  // Loop over the entries
  for (Long64_t jentry=0; jentry<nentries; jentry++) {
    // Load the entry
    if (jentry%1000000==0) std::cout << "[INFO] Entry: " << jentry << " / " << nentries << std::endl;
    if (LoadTree(jentry) < 0) { std::cout << "[ERROR] Entry: " << jentry << " is corrupted" << std::endl; return; }
    fChain->GetEntry(jentry);
    // Determine the event weight
    const auto& cntBin = getMCHiBinFromhiHF(hiHF);
    const auto& NcollWeight = findNcoll(cntBin);
    const auto& weight = sumWeight*NcollWeight*Gen_weight;
    const auto& cent = cntBin/2.;
    //if (weight<=0.) { std::cout << "[ERROR] Negative event weight: " << weight << std::endl; continue; }
    // Extract the reco tracks
    std::map< int , int > trkInfo;
    for (int iTrk=0; iTrk<Reco_trk_size; iTrk++) { trkInfo[Reco_trk_genIdx[iTrk]] = iTrk; }
    // Loop over the generated muons
    for (int iGen=0; iGen<Gen_mu_size; iGen++) {
      // Check if gen muon is a probe
      const auto& probeP4 = *dynamic_cast<TLorentzVector*>(Gen_mu_4mom->At(iGen));
      const bool& isProbe = (probeP4.Pt() > 15. && fabs(probeP4.Eta()) < 2.4);
      if (!isProbe) continue;
      const auto& iProbe = Gen_mu_whichRec[iGen];
      const int& iTrack = (trkInfo.find(iGen)!=trkInfo.end() ? trkInfo.at(iGen) : -1);
      // Derive the different probe conditions
      const bool& isTrack = (iTrack>=0); 
      const bool& isTrackNoMu = (iTrack>=0 && (Reco_trk_origAlgo[iTrack]!=13 && Reco_trk_origAlgo[iTrack]!=14));
      const bool& isTrackID = (iTrack>=0 && (Reco_trk_nTrkWMea[iTrack]>5 && Reco_trk_nPixValHits[iTrack]>0));
      const bool& isTrackerMu = (iProbe>=0 && ((Reco_mu_SelectionType[iProbe]&8) > 0));
      const bool& isPFGlobalMu = (iProbe>=0 && ((Reco_mu_SelectionType[iProbe]&2) > 0) && Reco_mu_isPF[iProbe]);
      const bool& isTightMu = isTightID(iProbe);
      const bool& isTriggerMu = isTriggerMatched(iProbe, 26, 26);
      for (auto& e : effM) {
	for (auto& t : e.second) {
	  for (auto& b : t.second) {
	    auto& eff = b.second;
	    const auto& type = t.first;
	    const auto& cntBin = b.first.first;
	    const auto& varBin = b.first.second;
	    bool inBin = (cent >= cntBin.first && cent < cntBin.second);
	    if (varBin.first>2.4) { inBin = inBin && (probeP4.Pt() >= varBin.first && probeP4.Pt() < varBin.second); }
	    else { inBin = inBin && (fabs(probeP4.Eta()) >= varBin.first && fabs(probeP4.Eta()) < varBin.second); }
	    const auto& probeVar = (varBin.first>2.4 ? probeP4.Eta() : probeP4.Pt());
	    if (inBin) {
	      if (e.first=="Trd") {
		// Fill the traditional efficiencies
		if (type=="Track") { eff.FillWeighted(isTrack, weight, probeVar); }
		else if (type=="TrackNoMu" && isTrack) { eff.FillWeighted(isTrackNoMu, weight, probeVar); }
		else if (type=="TrackID" && isTrack) { eff.FillWeighted(isTrackID, weight, probeVar); }
		else if (type=="TrackerMuon" && isTrackID) { eff.FillWeighted(isTrackerMu, weight, probeVar); }
		else if (type=="PFGlobalMuon" && isTrackerMu) { eff.FillWeighted(isPFGlobalMu, weight, probeVar); }
		else if (type=="MuonID" && isPFGlobalMu) { eff.FillWeighted(isTightMu, weight, probeVar); }
		else if (type=="Trigger" && isTightMu) { eff.FillWeighted(isTriggerMu, weight, probeVar); }
		else if (type=="Full" && isTrack) {  eff.FillWeighted((isTightMu && isTriggerMu), weight, probeVar); }
		else if (type=="FullFromTM" && isTrackerMu) {  eff.FillWeighted((isTightMu && isTriggerMu), weight, probeVar); }
		else if (type=="FullFromPFGlb" && isPFGlobalMu) {  eff.FillWeighted((isTightMu && isTriggerMu), weight, probeVar); }
	      }
	      else if (e.first=="TnP") {
		// Derive the different TnP efficiency weights
		const auto& hPass = const_cast<TH1*>(eff.GetPassedHistogram());
		const auto& hTotal = const_cast<TH1*>(eff.GetTotalHistogram());
		const auto& wTrack = 1.0;
		const auto& wTrackNoMu = 1.0;
		const auto& wTrackID = 1.0;
		const auto& wTracM = tnp_weight_TM_pbpb(probeP4.Eta());
		const auto& wPFGlbM = tnp_weight_glbtrk_pbpb(probeP4.Eta(), cent, 300);
		const auto& wMuID = tnp_weight_muid_pbpb(probeP4.Eta(), 300);
		const auto& wTrig = tnp_weight_trig_pbpb(probeP4.Pt(), probeP4.Eta(), cent, 300);
		// Fill the TnP efficiencies
		double numW = -1.0, denW = -1.0;
		if (type=="Track") { numW = weight*wTrack; denW = weight; }
		else if (type=="TrackNoMu") { numW = weight*wTrack*wTrackNoMu; denW = weight*wTrack; }
		else if (type=="TrackID") { numW = weight*wTrack*wTrackID; denW = weight*wTrack; }
		else if (type=="TrackerMuon") { numW = weight*wTrack*wTracM; denW = weight*wTrack; }
		else if (type=="PFGlobalMuon") { numW = weight*wTrack*wTracM*wPFGlbM; denW = weight*wTrack*wTracM; }
		else if (type=="MuonID") { numW = weight*wTrack*wTracM*wPFGlbM*wMuID; denW = weight*wTrack*wTracM*wPFGlbM; }
		else if (type=="Trigger") { numW = weight*wTrack*wTracM*wPFGlbM*wMuID*wTrig; denW = weight*wTrack*wTracM*wPFGlbM*wMuID; }
		else if (type=="Full") { numW = weight*wTrack*wTracM*wPFGlbM*wMuID*wTrig; denW = weight*wTrack; }
		//if (numW<=0. || denW<=0.) { std::cout << "[ERROR] Negative TnP weights: " << numW << "  " << denW << std::endl; return; }
		hPass->Fill(probeVar, numW);
		hTotal->Fill(probeVar, denW);
	      }
	    }
	  }
	}
      }
    }
  }

  // Save the efficiencies
  TFile f(filename.c_str(), "RECREATE");
  if (f.IsOpen() && !f.IsZombie()) {
    for (auto& e : effM) {
      for (auto& t : e.second) {
	for (auto& b : t.second) {
	  b.second.Write(b.second.GetName());
	}
      }
    }
    f.Write();
    f.Close();
  }
  else { std::cout << "[ERROR] The fitle " << filename << " was not created" << std::endl; }
}
