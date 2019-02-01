#!/bin/bash
cd /afs/cern.ch/work/j/jjay/public/TagAndProbe_pPb/CMSSW_8_0_30/src
eval `scramv1 runtime -sh`
cd MuonAnalysis/TagAndProbe/test/jpsiHI
cmsRun tp_Ana_$2_$1_pPb.py $3 
