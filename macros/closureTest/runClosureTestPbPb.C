#include "ClosureTestPbPb.C"
#include "TChain.h"

void runClosureTestPbPb() {
   TChain *tr = new TChain("hionia/myTree");
   // tr->AddFile("root://xrootd.unl.edu//store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_00_03_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
   tr->AddFile("root://xrootd.unl.edu//store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_03_06_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1_Extended.root");
   tr->AddFile("root://xrootd.unl.edu//store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_06_09_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1_Extended.root");
   tr->AddFile("root://xrootd.unl.edu//store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_09_12_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
   tr->AddFile("root://xrootd.unl.edu//store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_12_15_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
   tr->AddFile("root://xrootd.unl.edu//store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_15_30_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
   // tr->AddFile("root://xrootd.unl.edu//store/group/phys_heavyions/dileptons/MC2015/PbPb502TeV/TTrees/OniaTree_Pythia8_JpsiMM_ptJpsi_30_Inf_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
   ClosureTestPbPb toto(tr);
   toto.Loop("histos_trd_pbpb_cent120200.root",120,200);
}
