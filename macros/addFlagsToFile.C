#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <memory>
#include "pres.C"

#define DXYCUT_TIGHT 0.2
#define DZCUT_TIGHT 0.5
#define DXYCUT_SOFT 0.3
#define DZCUT_SOFT 20.0

float findNcoll(const int hiBin)
{
  const int nbins = 200;
  const float Ncoll[nbins] = {1976.95, 1944.02, 1927.29, 1891.9, 1845.3, 1807.2, 1760.45, 1729.18, 1674.8, 1630.3, 1590.52, 1561.72, 1516.1, 1486.5, 1444.68, 1410.88, 1376.4, 1347.32, 1309.71, 1279.98, 1255.31, 1219.89, 1195.13, 1165.96, 1138.92, 1113.37, 1082.26, 1062.42, 1030.6, 1009.96, 980.229, 955.443, 936.501, 915.97, 892.063, 871.289, 847.364, 825.127, 806.584, 789.163, 765.42, 751.187, 733.001, 708.31, 690.972, 677.711, 660.682, 640.431, 623.839, 607.456, 593.307, 576.364, 560.967, 548.909, 530.475, 519.575, 505.105, 490.027, 478.133, 462.372, 451.115, 442.642, 425.76, 416.364, 405.154, 392.688, 380.565, 371.167, 360.28, 348.239, 340.587, 328.746, 320.268, 311.752, 300.742, 292.172, 281.361, 274.249, 267.025, 258.625, 249.931, 240.497, 235.423, 228.63, 219.854, 214.004, 205.425, 199.114, 193.618, 185.644, 180.923, 174.289, 169.641, 161.016, 157.398, 152.151, 147.425, 140.933, 135.924, 132.365, 127.017, 122.127, 117.817, 113.076, 109.055, 105.16, 101.323, 98.098, 95.0548, 90.729, 87.6495, 84.0899, 80.2237, 77.2201, 74.8848, 71.3554, 68.7745, 65.9911, 63.4136, 61.3859, 58.1903, 56.4155, 53.8486, 52.0196, 49.2921, 47.0735, 45.4345, 43.8434, 41.7181, 39.8988, 38.2262, 36.4435, 34.8984, 33.4664, 31.8056, 30.351, 29.2074, 27.6924, 26.7754, 25.4965, 24.2802, 22.9651, 22.0059, 21.0915, 19.9129, 19.1041, 18.1487, 17.3218, 16.5957, 15.5323, 14.8035, 14.2514, 13.3782, 12.8667, 12.2891, 11.61, 11.0026, 10.3747, 9.90294, 9.42648, 8.85324, 8.50121, 7.89834, 7.65197, 7.22768, 6.7755, 6.34855, 5.98336, 5.76555, 5.38056, 5.11024, 4.7748, 4.59117, 4.23247, 4.00814, 3.79607, 3.68702, 3.3767, 3.16309, 2.98282, 2.8095, 2.65875, 2.50561, 2.32516, 2.16357, 2.03235, 1.84061, 1.72628, 1.62305, 1.48916, 1.38784, 1.28366, 1.24693, 1.18552, 1.16085, 1.12596, 1.09298, 1.07402, 1.06105, 1.02954};
  return Ncoll[hiBin];
}

TTree* copyTreeAndAddWeight(TTree* told, int nentries=0)
{
  TTree *tnew = told->CloneTree(0);
  tnew->SetAutoSave(0);
  tnew->SetAutoFlush(0);
  int TightId=-1, SoftId=-1;
  int isTightMuon=-1, passedDXY_TIGHT=-1, passedDZ_TIGHT=-1, passedValidPixelHits=-1, passedTrackerLayers=-1, passedMatchedStations=-1, passedMuHits=-1, passedglbChi2=-1, Glb=-1, PF=-1;
  int isSoftMuon=-1, isHybridSoftMuon2015=-1, isHybridSoftMuon2018=-1, passedDXY_SOFT=-1, passedDZ_SOFT=-1, passedPixelLayers=-1, TMOST=-1, Track_HP=-1, TM=-1;
  float dzPV=-999., dxyPV=-999., dB=-999., tkValidPixelHits=-1., tkPixelLay=-1., tkTrackerLay=-1., numberOfMatchedStations=-1., glbValidMuHits=-1., glbChi2=999., hiBin=-1., genWeight=-999., weight=1., pT=-999.;

  auto hist = pres();
  uint run=-1, ls=-1;
  int isUnprescaled=-1;
  told->SetBranchAddress("run",&run);
  told->SetBranchAddress("lumi",&ls);
  tnew->Branch("isUnprescaled", &isUnprescaled, "isUnprescaled/I");

  told->SetBranchAddress("pt",&pT);
  told->SetBranchAddress("dzPV",&dzPV);
  told->SetBranchAddress("dxyPV",&dxyPV);
  told->SetBranchAddress("dB",&dB);
  told->SetBranchAddress("tkValidPixelHits", &tkValidPixelHits);
  told->SetBranchAddress("tkPixelLay", &tkPixelLay);
  told->SetBranchAddress("tkTrackerLay", &tkTrackerLay);
  told->SetBranchAddress("numberOfMatchedStations", &numberOfMatchedStations);
  told->SetBranchAddress("glbValidMuHits", &glbValidMuHits);
  told->SetBranchAddress("glbChi2", &glbChi2);
  told->SetBranchAddress("Glb", &Glb);
  told->SetBranchAddress("PF", &PF);
  told->SetBranchAddress("TM", &TM);
  told->SetBranchAddress("TMOST", &TMOST);
  told->SetBranchAddress("Track_HP", &Track_HP);
  told->SetBranchAddress("TightId", &TightId);
  if (told->GetBranch("SoftId")!=NULL) { told->SetBranchAddress("SoftId", &SoftId); }
  if (told->GetBranch("tag_hiBin")!=NULL) { told->SetBranchAddress("tag_hiBin", &hiBin); }
  if (told->GetBranch("pair_genWeight")!=NULL) { told->SetBranchAddress("pair_genWeight", &genWeight); }
   
  tnew->Branch("isTightMuon", &isTightMuon, "isTightMuon/I");
  tnew->Branch("passedDXY_TIGHT", &passedDXY_TIGHT, "passedDXY_TIGHT/I");
  tnew->Branch("passedDZ_TIGHT", &passedDZ_TIGHT, "passedDZ_TIGHT/I");
  tnew->Branch("passedValidPixelHits", &passedValidPixelHits, "passedValidPixelHits/I");
  tnew->Branch("passedTrackerLayers", &passedTrackerLayers, "passedTrackerLayers/I");
  tnew->Branch("passedMatchedStations", &passedMatchedStations, "passedMatchedStations/I");
  tnew->Branch("passedMuHits", &passedMuHits, "passedMuHits/I");
  tnew->Branch("passedglbChi2", &passedglbChi2, "passedglbChi2/I");
  tnew->Branch("isSoftMuon", &isSoftMuon, "isSoftMuon/I");
  tnew->Branch("isHybridSoftMuon2015", &isHybridSoftMuon2015, "isHybridSoftMuon2015/I");
  tnew->Branch("isHybridSoftMuon2018", &isHybridSoftMuon2018, "isHybridSoftMuon2018/I");
  tnew->Branch("passedDXY_SOFT", &passedDXY_SOFT, "passedDXY_SOFT/I");
  tnew->Branch("passedDZ_SOFT", &passedDZ_SOFT, "passedDZ_SOFT/I");
  tnew->Branch("passedPixelLayers", &passedPixelLayers, "passedPixelLayers/I");
  tnew->Branch("weight", &weight, "weight/F");
  
  if (nentries == 0) nentries = told->GetEntries();
  float sumWeight = nentries;
  if (told->GetBranch("pair_genWeight")!=NULL) {
    told->SetBranchStatus("*", 0);
    told->SetBranchStatus("pair_genWeight", 1);
    if (told->GetBranch("tag_hiBin")!=NULL) { told->SetBranchStatus("tag_hiBin", 1); }
    sumWeight = 0.;
    for (int i=0; i<nentries; i++) {
      told->GetEntry(i);
      const float nColl = ((hiBin>=0 && hiBin<200) ? findNcoll(hiBin) : 1.);
      sumWeight += genWeight*nColl;
    }
    told->SetBranchStatus("*", 1);
  }
  for (int i=0; i<nentries; i++) {
    told->GetEntry(i);

    //TightMuonID
    isTightMuon = (Glb==1 && PF==1 && fabs(dB)<DXYCUT_TIGHT && fabs(dzPV)<DZCUT_TIGHT && tkValidPixelHits>0.1 && tkTrackerLay>5.1 && numberOfMatchedStations>1.1 && glbValidMuHits>0.1 && glbChi2<10.);
    if (TightId>-1 && isTightMuon!=TightId) {
        std::cout << "Tight ID muon with pT="<<pT<<" GeV/c is not consistent: Official " << TightId << " and Custom " << isTightMuon << std::endl;
        std::cout << Glb << "(==1)  " << PF << "(==1)  " << fabs(dB) << "(<0.2)  " << fabs(dxyPV) << "(<0.2)  " << fabs(dzPV) << "(<0.5)  " << tkValidPixelHits << "(>0)  " << tkTrackerLay << "(>5)  " << numberOfMatchedStations << "(>1) " << glbValidMuHits << "(>0)  " << glbChi2 << "(<10) "<< std::endl;
        isTightMuon = TightId;
    }
    passedDXY_TIGHT = (fabs(dB) < DXYCUT_TIGHT);
    passedDZ_TIGHT = (fabs(dzPV) < DZCUT_TIGHT);
    passedValidPixelHits = (tkValidPixelHits > 0.1);
    passedTrackerLayers = (tkTrackerLay > 5.1);
    passedMatchedStations = (numberOfMatchedStations > 1.1);
    passedMuHits = (glbValidMuHits > 0.1);
    passedglbChi2 = (glbChi2 < 10.);

    const auto& val = hist->GetBinContent(hist->FindBin(ls, run));
    isUnprescaled = (val>0.9 && val<1.1);
      
    //SoftMuonID
    isSoftMuon = (TMOST==1 && Track_HP==1 && fabs(dxyPV)<DXYCUT_SOFT && fabs(dzPV)<DZCUT_SOFT && tkPixelLay>0.1 && tkTrackerLay>5.1);
    if (SoftId>-1 && isSoftMuon!=SoftId) {
        std::cout << "Soft ID muon with pT="<<pT<<" GeV/c is not consistent: Offical " << SoftId << " and Custom " << isSoftMuon << std::endl;
        std::cout << TMOST << "(==1)  " << Track_HP << "(==1)  " << fabs(dxyPV) << "(<0.3)  " << fabs(dzPV) << "(<20.0)  " << tkPixelLay << "(>0)  " << tkTrackerLay << "(>5)  " << std::endl;
        isSoftMuon = SoftId;
    }
    passedDXY_SOFT = (fabs(dxyPV) < DXYCUT_SOFT);
    passedDZ_SOFT = (fabs(dzPV) < DZCUT_SOFT);
    passedPixelLayers = (tkPixelLay > 0.1);
    passedTrackerLayers = (tkTrackerLay > 5.1);

    //HybridSoftMuonID PbPb
    isHybridSoftMuon2015 = (Glb==1 && TM==1 && TMOST==1 && fabs(dxyPV)<DXYCUT_SOFT && fabs(dzPV)<DZCUT_SOFT && tkPixelLay>0.1 && tkTrackerLay>5.1);
    isHybridSoftMuon2018 = (Glb==1 && TM==1 && fabs(dxyPV)<DXYCUT_SOFT && fabs(dzPV)<DZCUT_SOFT && tkPixelLay>0.1 && tkTrackerLay>5.1);

    //Weight
    weight = (nentries/sumWeight);
    const float nColl = ((hiBin>=0 && hiBin<200) ? findNcoll(hiBin) : 1.);
    if (genWeight!=-999.) { weight *= genWeight*nColl; }

    tnew->Fill();
  }

  return tnew;
}

TTree* justCopyTreeAndAddWeight(TTree* told, int nentries=0) {
  TTree *tnew = told->CloneTree(0);
  tnew->SetAutoSave(0);
  tnew->SetAutoFlush(0);
  float hiBin=-1., genWeight=-999., weight=1.0;

  if (told->GetBranch("tag_hiBin")!=NULL) { told->SetBranchAddress("tag_hiBin", &hiBin); }
  if (told->GetBranch("pair_genWeight")!=NULL) { told->SetBranchAddress("pair_genWeight", &genWeight); }
  tnew->Branch("weight", &weight, "weight/F");

  if (nentries == 0) nentries = told->GetEntries();
  float sumWeight = nentries;
  if (told->GetBranch("pair_genWeight")!=NULL) {
    told->SetBranchStatus("*", 0);
    told->SetBranchStatus("pair_genWeight", 1);
    if (told->GetBranch("tag_hiBin")!=NULL) { told->SetBranchStatus("tag_hiBin", 1); }
    sumWeight = 0.;
    for (int i=0; i<nentries; i++) {
      told->GetEntry(i);
      const float nColl = ((hiBin>=0 && hiBin<200) ? findNcoll(hiBin) : 1.);
      sumWeight += genWeight*nColl;
    }
    told->SetBranchStatus("*", 1);
  }
  for (int i=0; i<nentries; i++) {
    told->GetEntry(i);
    //Weight
    weight = (nentries/sumWeight);
    const float nColl = ((hiBin>=0 && hiBin<200) ? findNcoll(hiBin) : 1.);
    if (genWeight!=-999.) { weight *= genWeight*nColl; }
    tnew->Fill();
  }

  return tnew;
}

void addFlagsToFile(const std::string filein, const std::string fileout) {
  auto fin = std::unique_ptr<TFile>(new TFile(filein.c_str()));
  auto fout = std::unique_ptr<TFile>(new TFile(fileout.c_str(),"RECREATE"));
  if (!fin || !fin->IsOpen() || fin->IsZombie()) return;
  if (!fout || !fout->IsOpen() || fout->IsZombie()) return;

  fout->cd();
  TDirectory *tdir_trk = fout->mkdir("tpTreeSta");
  tdir_trk->cd();
  TTree *tr_trk = justCopyTreeAndAddWeight((TTree*)fin->Get("tpTreeSta/fitter_tree"),0);

  fout->cd();
  TDirectory *tdir_muidtrg = fout->mkdir("tpTree");
  tdir_muidtrg->cd();
  TTree *tr_muidtrg = copyTreeAndAddWeight((TTree*)fin->Get("tpTree/fitter_tree"),0);

  fout->cd();
  TDirectory *tdir_sta = fout->mkdir("tpTreeTrk");
  tdir_sta->cd();
  TTree *tr_sta = justCopyTreeAndAddWeight((TTree*)fin->Get("tpTreeTrk/fitter_tree"),0);

  fout->Write();
  fout->Close();
  fin->Close();
}
