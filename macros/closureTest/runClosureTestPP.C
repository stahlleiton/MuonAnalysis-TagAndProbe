#include "ClosureTestPP.C"

void runClosureTestPP() {
   TFile *f = TFile::Open("root://xrootd.unl.edu//store/group/phys_heavyions/dileptons/MC2015/pp502TeV/TTrees/OniaTree_JpsiMM_5p02TeV_TuneCUETP8M1_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_Extended.root");
   TTree *tr = (TTree*) f->Get("hionia/myTree");
   ClosureTestPP toto(tr);
   toto.Loop("histos_trd_pp.root");
}
