#include "ClosureTestPbPb.C"
#include "TChain.h"

void runClosureTestPbPb() {
  TChain tr("hionia/myTree");
  tr.AddFile("OniaTree_HINPbPbAutumn18DR-mva98_DYJetsToLL_MLL-50_MC_20190928.root");
  ClosureTestPbPb toto(&tr);
  toto.Loop("eff_PbPb_HighPt.root");
}
