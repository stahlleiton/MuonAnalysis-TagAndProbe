#include "TTree.h"
#include "TFile.h"

#define DXYCUT_TIGHT 0.2
#define DZCUT_TIGHT 0.5
#define DXYCUT_SOFT 0.3
#define DZCUT_SOFT 20.0

TTree* copyTreeAndAddWeight(TTree* told, int nentries=0) {
   TTree *tnew = told->CloneTree(0);
   tnew->SetAutoSave(0);
   tnew->SetAutoFlush(0);
   int isTightMuon, passedDXY_TIGHT, passedDZ_TIGHT, passedValidPixelHits, passedTrackerLayers, passedMatchedStations, passedMuHits, passedglbChi2, Glb, PF;
   int isSoftMuon, passedDXY_SOFT, passedDZ_SOFT, passedPixelLayers, TMOST, Track_HP;
   float dzPV, dxyPV, dB, tkValidPixelHits, tkPixelLay, tkTrackerLay, numberOfMatchedStations, glbValidMuHits, glbChi2, hiHF=-1.0, genWeight=-1.0, weight=1.0;

   told->SetBranchAddress("dzPV",&dzPV);
   told->SetBranchAddress("dxyPVdzmin",&dxyPV);
   told->SetBranchAddress("dB",&dB);
   told->SetBranchAddress("tkValidPixelHits", &tkValidPixelHits);
   told->SetBranchAddress("tkPixelLay", &tkPixelLay);
   told->SetBranchAddress("tkTrackerLay", &tkTrackerLay);
   told->SetBranchAddress("numberOfMatchedStations", &numberOfMatchedStations);
   told->SetBranchAddress("glbValidMuHits", &glbValidMuHits);
   told->SetBranchAddress("glbChi2", &glbChi2);
   told->SetBranchAddress("Glb", &Glb);
   told->SetBranchAddress("PF", &PF);
   told->SetBranchAddress("TMOST", &TMOST);
   told->SetBranchAddress("Track_HP", &Track_HP);
   if (told->GetBranch("hiHF")!=NULL) { told->SetBranchAddress("hiHF", &hiHF); }
   if (told->GetBranch("genWeight")!=NULL) { told->SetBranchAddress("genWeight", &genWeight); }
   
   tnew->Branch("isTightMuon", &isTightMuon, "isTightMuon/I");
   tnew->Branch("passedDXY_TIGHT", &passedDXY_TIGHT, "passedDXY_TIGHT/I");
   tnew->Branch("passedDZ_TIGHT", &passedDZ_TIGHT, "passedDZ_TIGHT/I");
   tnew->Branch("passedValidPixelHits", &passedValidPixelHits, "passedValidPixelHits/I");
   tnew->Branch("passedTrackerLayers", &passedTrackerLayers, "passedTrackerLayers/I");
   tnew->Branch("passedMatchedStations", &passedMatchedStations, "passedMatchedStations/I");
   tnew->Branch("passedMuHits", &passedMuHits, "passedMuHits/I");
   tnew->Branch("passedglbChi2", &passedglbChi2, "passedglbChi2/I");
   tnew->Branch("isSoftMuon", &isSoftMuon, "isSoftMuon/I");
   tnew->Branch("passedDXY_SOFT", &passedDXY_SOFT, "passedDXY_SOFT/I");
   tnew->Branch("passedDZ_SOFT", &passedDZ_SOFT, "passedDZ_SOFT/I");
   tnew->Branch("passedPixelLayers", &passedPixelLayers, "passedPixelLayers/I");
   tnew->Branch("weight", &weight, "weight/F");
 
   if (nentries == 0)
   {
	   nentries = told->GetEntries();
   }
   for (int i=0; i<nentries; i++) {
      told->GetEntry(i);

	  //TightMuonID
	  isTightMuon = (Glb && PF && fabs(dB)<DXYCUT_TIGHT && fabs(dzPV)<DZCUT_TIGHT && tkValidPixelHits>0.1 && tkTrackerLay>5.1 && numberOfMatchedStations>1.1 && glbValidMuHits>0.1 && glbChi2<10.);
	  passedDXY_TIGHT = (fabs(dB) < DXYCUT_TIGHT);
	  passedDZ_TIGHT = (fabs(dzPV) < DZCUT_TIGHT);
	  passedValidPixelHits = (tkValidPixelHits > 0.1);
	  passedTrackerLayers = (tkTrackerLay > 5.1);
	  passedMatchedStations = (numberOfMatchedStations > 1.1);
	  passedMuHits = (glbValidMuHits > 0.1);
	  passedglbChi2 = (glbChi2 < 10.);
      
      //SoftMuonID
      isSoftMuon = (TMOST && Track_HP && fabs(dxyPV)<DXYCUT_SOFT && fabs(dzPV)<DZCUT_SOFT && tkPixelLay>0.1 && tkTrackerLay>5.1);
      passedDXY_SOFT = (fabs(dxyPV) < DXYCUT_SOFT);
      passedDZ_SOFT = (fabs(dzPV) < DZCUT_SOFT);
      passedPixelLayers = (tkPixelLay > 0.1);
      passedTrackerLayers = (tkTrackerLay > 5.1);

      //Weight
      weight = 1.0;
      if (genWeight>0.) { weight = genWeight; }
          
      tnew->Fill();
   }

   return tnew;
}

TTree* justCopyTreeAndAddWeight(TTree* told, int nentries=0) {
   TTree *tnew = told->CloneTree(0);
   tnew->SetAutoSave(0);
   tnew->SetAutoFlush(0);
   float hiHF=-1.0, genWeight=-1.0, weight=1.0;

   if (told->GetBranch("hiHF")!=NULL) { told->SetBranchAddress("hiHF", &hiHF); }
   if (told->GetBranch("genWeight")!=NULL) { told->SetBranchAddress("genWeight", &genWeight); }
   tnew->Branch("weight", &weight, "weight/F");

   if (nentries == 0)
   {
       nentries = told->GetEntries();
   }
   for (int i=0; i<nentries; i++) {
      told->GetEntry(i);
      //Weight
      weight = 1.0;
      if (genWeight>0.) { weight = genWeight; }
      tnew->Fill();
   }
   return tnew;
}

void addFlagsToFile(const char *filein, const char *fileout) {
   TFile *fin = new TFile(filein);
   TFile *fout = new TFile(fileout,"RECREATE");

   fout->cd();
   TDirectory *tdir_trk = fout->mkdir("tpTreeSta");
   tdir_trk->cd();
   TTree *tr_trk = justCopyTreeAndAddWeight((TTree*)fin->Get("tpTreeSta/fitter_tree"),0);

   fout->cd();
   TDirectory *tdir_muidtrg = fout->mkdir("tpTree");
   tdir_muidtrg->cd();
   TTree *tr_muidtrg = copyTreeAndAddWeight((TTree*) fin->Get("tpTree/fitter_tree"),0);

   fout->cd();
   TDirectory *tdir_trg = fout->mkdir("tpTreeTrk");
   tdir_trg->cd();
   TTree *tr_trg = justCopyTreeAndAddWeight((TTree*)fin->Get("tpTreeTrk/fitter_tree"),0);

   fout->Write();
   fout->Close();
}
