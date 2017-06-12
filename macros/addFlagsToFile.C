#include "TTree.h"
#include "TFile.h"

#define DXYCUT 0.2
#define DZCUT 0.5

TTree* copyTree(TTree* told) {
   TTree *tnew = told->CloneTree(0);
   tnew->SetAutoSave(0);
   tnew->SetAutoFlush(0);
   int isIso_3_15, isIso_3_20, isIso_4_15, isIso_4_20, isTightMuonO;
   float combRelIsoPF03;
   float combRelIsoPF04;
   float dzPV, dB, tkValidPixelHits, tkTrackerLay, numberOfMatchedStations, glbValidMuHits, glbChi2;

   told->SetBranchAddress("combRelIsoPF03", &combRelIsoPF03);
   told->SetBranchAddress("combRelIsoPF04", &combRelIsoPF04);
   told->SetBranchAddress("dzPV",&dzPV);
   told->SetBranchAddress("dB",&dB);
   told->SetBranchAddress("tkValidPixelHits", &tkValidPixelHits);
   told->SetBranchAddress("tkTrackerLay", &tkTrackerLay);
   told->SetBranchAddress("numberOfMatchedStations", &numberOfMatchedStations);
   told->SetBranchAddress("glbValidMuHits", &glbValidMuHits);
   told->SetBranchAddress("glbChi2", &glbChi2);

   tnew->Branch("isIso_3_15",&isIso_3_15,"isIso_3_15/I");
   tnew->Branch("isIso_3_20", &isIso_3_20, "isIso_3_20/I");
   tnew->Branch("isIso_4_15", &isIso_4_15, "isIso_4_15/I");
   tnew->Branch("isIso_4_20", &isIso_4_20, "isIso_4_20/I");
   tnew->Branch("isTightMuonO", &isTightMuonO, "isTightMuonO/I");

   int nentries = told->GetEntries();
   for (int i=0; i<nentries; i++) {
      told->GetEntry(i);
	  // Isolations
	  isIso_3_15 = ((combRelIsoPF03)<0.15);
	  isIso_3_20 = ((combRelIsoPF03)<0.20);
	  isIso_4_15 = ((combRelIsoPF04)<0.15);
	  isIso_4_20 = ((combRelIsoPF04)<0.20);

	  //TightMuonID

	  isTightMuonO = (fabs(dB)<DXYCUT && fabs(dzPV)<DZCUT && tkValidPixelHits>0.1 && tkTrackerLay>5.1 && numberOfMatchedStations>1.1 && glbValidMuHits>0.1 && glbChi2<10);

      tnew->Fill();
   }

   return tnew;
}

TTree* justCopyTree(TTree* told) {
	TTree *tnew = told->CloneTree(0);
	tnew->SetAutoSave(0);
	tnew->SetAutoFlush(0);

	int nentries = told->GetEntries();
	for (int i = 0; i<nentries; i++) {
		told->GetEntry(i);
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
   TTree *tr_trk = justCopyTree((TTree*)fin->Get("tpTreeSta/fitter_tree"));

   fout->cd();
   TDirectory *tdir_muidtrg = fout->mkdir("tpTree");
   tdir_muidtrg->cd();
   TTree *tr_muidtrg = copyTree((TTree*) fin->Get("tpTree/fitter_tree"));

   fout->cd();
   TDirectory *tdir_trg = fout->mkdir("tpTreeTrk");
   tdir_trg->cd();
   TTree *tr_trg = justCopyTree((TTree*)fin->Get("tpTreeTrk/fitter_tree"));


   fout->Write();
   fout->Close();
}
