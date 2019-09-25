#include "ClosureTestPbPb.C"
#include "TChain.h"

void runClosureTestPbPb() {
  TChain *tr = new TChain("hionia/myTree");
  tr->AddFile("/eos/cms/store/group/phys_heavyions/bdiab/dilepton/oniaTree/PbPb2018/MC/Prompt/HiForestAOD_merged.root");
  TChain *centtr = new TChain("hiEvtAnalyzer/HiTree");
  centtr->AddFile("/eos/cms/store/group/phys_heavyions/bdiab/dilepton/oniaTree/PbPb2018/MC/Prompt/HiForestAOD_merged.root");
  tr->AddFriend(centtr);
  ClosureTestPbPb toto(tr);
  //toto.Loop("histos_trd_pbpb_cent0200_L2Jpsi.root", 0, 200, 0);
  toto.Loop("histos_trd_pbpb_cent0200_L3Jpsi.root", 0, 200, 1);
  toto.Loop("histos_trd_pbpb_cent100200_DMOpen.root", 100, 200, 4);
}
