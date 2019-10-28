import FWCore.ParameterSet.Config as cms

import sys
args =sys.argv[1:]
if len(args) < 2: scenario = "0"
else: 
   scenario = args[1]
print("Will run scenario " + scenario) 
# scenario: 1 pT, 2-3 pT in detailed abseta bins, 4-5 pT in overall abseta bins, 6 abseta, 7, eta, 8 centrality, 9 added nPV, 0 (or no parameter) run all


process = cms.Process("TagProbe")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    
PDFName = "BWConvCBPol1Exp"


VEFFICIENCYSET =cms.VPSet(
# Order: 0 total, 1 pT, 2-8 pT fits in abseta bins, 9 abseta, 10 eta, 11-12 centrality   NOTE: IS NOT SAME AS SCENARIO, SCENARIO DEFINED BELOW
    cms.PSet(
        Trk_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
#                tag_nVertices = cms.vdouble(0, 6),
                pt = cms.vdouble(15, 100),
                eta = cms.vdouble(-2.4, 2.4),
                TM = cms.vstring("true"),
                #TrackCuts = cms.vstring("true"),
                #isRndProbe = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ),
   cms.PSet(
       Trk_pt = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
           UnbinnedVariables = cms.vstring("mass"),
           BinnedVariables = cms.PSet(
               pt = cms.vdouble(15, 30, 50, 100),
               eta = cms.vdouble(-2.4,2.4),
               TM = cms.vstring("true"),
#               tag_nVertices = cms.vdouble(0, 1, 2, 6),
               #TrackCuts = cms.vstring("true"),
               #isRndProbe = cms.vstring("true"),

           ),
           BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
        Trk_abseta00_09 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
#                tag_nVertices = cms.vdouble(0, 1, 2, 6),
                pt = cms.vdouble(15, 30, 50, 100),
                abseta = cms.vdouble(0, 0.9),
                TM = cms.vstring("true"),
               #TrackCuts = cms.vstring("true"),
               #isRndProbe = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_abseta09_12 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(0.9,1.2),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_abseta00_12 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(0.0,1.2),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_abseta12_16 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(1.2, 1.6),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_abseta16_21 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(1.6, 2.1),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_abseta12_21 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(1.2, 2.1),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_abseta21_24 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(2.1,2.4),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_absetadep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 100),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_etadep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 100),
                 eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,0,0.9,1.2,1.6,2.1,2.4),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
        Trk_centdep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 100),
                 eta = cms.vdouble(-2.4,2.4),
                 tag_hiBin = cms.vdouble(0, 20, 40, 60, 80, 100, 200),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(
       Trk_pt_cent0010 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
           UnbinnedVariables = cms.vstring("mass"),
           BinnedVariables = cms.PSet(
               pt = cms.vdouble(15, 30, 50, 100),
               eta = cms.vdouble(-2.4,2.4),
               tag_hiBin = cms.vdouble(0, 20),
               TM = cms.vstring("true"),
               #TrackCuts = cms.vstring("true"),
               #isRndProbe = cms.vstring("true"),
#               tag_nVertices = cms.vdouble(0, 1, 2, 6),
           ),
           BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
       Trk_pt_cent1040 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
           UnbinnedVariables = cms.vstring("mass"),
           BinnedVariables = cms.PSet(
               pt = cms.vdouble(15, 30, 50, 100),
               eta = cms.vdouble(-2.4,2.4),
               tag_hiBin = cms.vdouble(20, 80),
               TM = cms.vstring("true"),
               #TrackCuts = cms.vstring("true"),
               #isRndProbe = cms.vstring("true"),
#               tag_nVertices = cms.vdouble(0, 1, 2, 6),
           ),
           BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
       Trk_pt_cent40100 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
           UnbinnedVariables = cms.vstring("mass"),
           BinnedVariables = cms.PSet(
               pt = cms.vdouble(15, 30, 50, 100),
               eta = cms.vdouble(-2.4,2.4),
               tag_hiBin = cms.vdouble(80, 200),
               TM = cms.vstring("true"),
               #TrackCuts = cms.vstring("true"),
               #isRndProbe = cms.vstring("true"),
#               tag_nVertices = cms.vdouble(0, 1, 2, 6),
           ),
           BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_absetadep_cent0010 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 100),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(0, 20),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_absetadep_cent1040 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 100),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(20, 80),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_absetadep_cent40100 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 100),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(80, 200),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
        Trk_phidep_eta0912p = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 100),
                 eta = cms.vdouble(0.9,1.2),
                 phi = cms.vdouble(-3.1416, -2.6180, -2.0944, -1.5708, -1.0472, -0.5236, 0.00, 0.5236, 1.0472, 1.5708, 2.0944, 2.6180, 3.1416),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(
        Trk_phidep_eta0912m = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 100),
                 eta = cms.vdouble(-1.2,-0.9),
                 phi = cms.vdouble(-3.1416, -2.6180, -2.0944, -1.5708, -1.0472, -0.5236, 0.00, 0.5236, 1.0472, 1.5708, 2.0944, 2.6180, 3.1416),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(
          Trk_etadep_cent0010 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 100),
                 eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(0, 20),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_etadep_cent1040 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 100),
                 eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(20, 80),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_etadep_cent40100 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 100),
                 eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(80, 200),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_absetadep_cent0040 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 100),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(00, 80),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_etadep_cent0040 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 6),
                 pt = cms.vdouble(15, 100),
                 eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(00, 80),
                 TM = cms.vstring("true"),
                 #TrackCuts = cms.vstring("true"),
                 #isRndProbe = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
)

#Actual selection 
if scenario == "1": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0], VEFFICIENCYSET[1])
if scenario == "2": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[2], VEFFICIENCYSET[3])
if scenario == "3": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[5], VEFFICIENCYSET[6])
if scenario == "4": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[4], VEFFICIENCYSET[7])
if scenario == "5": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[8])
if scenario == "6": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[9])
if scenario == "7": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[10])
if scenario == "8": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[11], VEFFICIENCYSET[12], VEFFICIENCYSET[13], VEFFICIENCYSET[14])
#if scenario == "9": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[15], VEFFICIENCYSET[16], VEFFICIENCYSET[17])
#if scenario == "10": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[18], VEFFICIENCYSET[19])
if scenario == "9": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[20], VEFFICIENCYSET[21], VEFFICIENCYSET[22])
if scenario == "10": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[23], VEFFICIENCYSET[24])
if scenario == "0": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0],VEFFICIENCYSET[1],VEFFICIENCYSET[2], VEFFICIENCYSET[3],VEFFICIENCYSET[4], VEFFICIENCYSET[5],VEFFICIENCYSET[6], VEFFICIENCYSET[7],VEFFICIENCYSET[8], VEFFICIENCYSET[9], VEFFICIENCYSET[10],VEFFICIENCYSET[11])#,VEFFICIENCYSET[12])



process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    # InputFileNames = cms.vstring("file:/eos/cms/store/group/phys_heavyions/dileptons/TNPTagAndProbe2018/Data2018/PbPb502TeV/tnpZ_Data_PbPb_mod_v5.root"),
    InputFileNames = cms.vstring("file:/afs/cern.ch/work/o/okukral/TnP_PbPb/CMSSW_10_3_2/src/MuonAnalysis/TagAndProbe/test/zmumuHI/tnpZ_Data_PbPb_mod_v5_1.root"),
    InputDirectoryName = cms.string("tpTreeTrk"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_RD_TrkfromTrkM5_PbPb_bkg_%s.root" % scenario),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(16),
    # specifies whether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),
    binsForMassPlots = cms.uint32(50),
    SaveWorkspace = cms.bool(False),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         mass             = cms.vstring("Tag-Probe Mass", "70.0", "120.0", "GeV/c^{2}"), # mass range syst:         #orig 45
                         pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
                         tag_hiBin        = cms.vstring("Centrality bin", "0", "200", ""),
                         phi              = cms.vstring("phi", "-3.2", "3.2", ""),

    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
			 # MuIDForOutsideInTk = cms.vstring("OITK Seed", "dummy[pass=1,fail=0]"),
			             Glb = cms.vstring("Glb", "dummy[true=1,false=0]"),
                         PF  = cms.vstring("PF", "dummy[true=1, false=0]"),
                         TrackCuts  = cms.vstring("TrackCuts", "dummy[true=1, false=0]"),
                         isRndProbe  = cms.vstring("isRndProbe", "dummy[true=1, false=0]"),
                         TM  = cms.vstring("TM", "dummy[true=1, false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
	VoigtExp = cms.vstring(
		"Voigtian::signal(mass, mean[91,75,105], width[3,-5,15], sigma[3,-5,15])", # mean 85-95, width, sigma 1-10
		"Exponential::backgroundPass(mass, lp[0,-5,5])",
		"Exponential::backgroundFail(mass, lf[0,-5,5])",
		"efficiency[0.9,0,1]",
		"signalFractionInPassing[0.9]"
	),
    VoigtPol2 = cms.vstring(
		"Voigtian::signal(mass, mean[91,75,105], width[3,-5,15], sigma[3,-5,15])", # mean 85-95, width, sigma 1-10
        "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1]})",
		"efficiency[0.9,0,1]",
		"signalFractionInPassing[0.9]"
	),
	BWResCBExp = cms.vstring(
		"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
		"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[0.8,0,10])",
		"FCONV::signal(mass, bw, res)",
		"Exponential::backgroundPass(mass, lp[0,-5,5])",
		"Exponential::backgroundFail(mass, lf[0,-5,5])",
		"efficiency[0.9,0.5,1]",
		"signalFractionInPassing[0.9]",
	),
	BWResCBCheb = cms.vstring(
		"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
		"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[0.8,0,10])",
		"FCONV::signal(mass, bw, res)",
		"Chebychev::backgroundPass(mass, {c1p[0,-10,10], c2p[0,-10,10], c3p[0,-10,10]})",
		"Chebychev::backgroundFail(mass, {c1f[0,-10,10], c2f[0,-10,10], c3f[0,-10,10]})",
		"efficiency[0.9,0.5,1]",
		"signalFractionInPassing[0.9]",
	),
    cbPlusPol3 = cms.vstring(
        "CBShape::signal(mass, mean[91, 80, 100], sigma[3, 1, 10], alpha[1.85, 0.3, 50], n[1.4,0.5,5.0])",
        "Chebychev::backgroundPass(mass, {cPass[0.1,-1.5,1.5], cPass2[0.01,-0.5,0.5], cPass3[0.01,-0.1,0.1]})",
        "Chebychev::backgroundFail(mass, {cFail[0.1,-1.5,1.5], cFail2[0.01,-0.5,0.5], cFail3[0.01,-0.1,0.1]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
    ),
    cbFixedNGausPol3 = cms.vstring( #n , alpha fixed to integrated bin in MC 
        "CBShape::signal1(mass, mean[91, 80, 100], sigma1[3, 1, 10], alpha[1.60], n[1.09])",
        "RooFormulaVar::sigma2('@0*@1',{fracS[1.2,0.8,2.4],sigma1})",
        "Gaussian::signal2(mass, mean, sigma2)",
        "SUM::signal(frac[0.8,0.2,1.]*signal1,signal2)",
        #"Chebychev::backgroundPass(mass, {cPass[-0.1,-1.5,1.5], cPass2[-0.01,-1.5,1.5], cPass3[0.01,-0.9,0.9]})",
        "Exponential::backgroundPass(mass, lp[0,-5,5])",
        "Chebychev::backgroundFail(mass, {cFail[-0.3,-1.5,1.5], cFail2[0.01,-0.5,0.5], cFail3[0.01,-0.2,0.2]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
    ),
    BWConvCBExpPol2 = cms.vstring( #n fixed to integrated bin in MC
		"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
		"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[1.92])",
		"FCONV::signal(mass, bw, res)",
        "Exponential::backgroundPass(mass, lp[0,-5,5])",
        "Chebychev::backgroundFail(mass, {cFail[-0.3,-1.5,1.5], cFail2[0.01,-0.5,0.5]})",
		"efficiency[0.9,0.5,1]",
		"signalFractionInPassing[0.9]",
	),
    BWConvCBPol1Exp = cms.vstring( #n fixed to integrated bin in MC
		"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
		"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[1.92])",
		"FCONV::signal(mass, bw, res)",
        "Chebychev::backgroundPass(mass, {cPass[0.0,-1.5,1.5]})",
 		"Exponential::backgroundFail(mass, lf[0,-5,5])",
		"efficiency[0.9,0.5,1]",
		"signalFractionInPassing[0.9]",
	),
    CBExpPol2 = cms.vstring( 
		"RooCBShape::signal(mass, m0[91.2,81.2,101.2], sigma[1.7,0.01,10], alpha[1.8,0,3], n[1.92, 0.2, 50])",
        "Exponential::backgroundPass(mass, lp[0,-5,5])",
        "Chebychev::backgroundFail(mass, {cFail[-0.3,-1.5,1.5], cFail2[0.01,-0.5,0.5]})",
		"efficiency[0.9,0.5,1]",
		"signalFractionInPassing[0.9]",
	),
      #  #nominal:
      #cbPlusPol1 = cms.vstring(
      #  "CBShape::signal(mass, mean[3.08,3.00,3.3], sigma[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
      #  "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1]})",
      #  "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1]})",
      #  "efficiency[0.9,0,1]",
      #  "signalFractionInPassing[0.9]"
      #),
      #  #background syst:
      #cbPlusPol2 = cms.vstring(
      #  "CBShape::signal(mass, mean[3.08,3.00,3.2], sigma[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
      #  "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1]})",
      #  "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1]})",
      #  "efficiency[0.9,0,1]",
      #  "signalFractionInPassing[0.9]"
      #),
      #  #signal syst:
      #cbGausPlusPol1 = cms.vstring(
      #  "CBShape::signal1(mass, mean[3.08,3.00,3.3], sigma1[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
      #  "RooFormulaVar::sigma2('@0*@1',{fracS[1.8,1.2,2.4],sigma1})",
      #  "Gaussian::signal2(mass, mean, sigma2)",
      #  "SUM::signal(frac[0.8,0.5,1.]*signal1,signal2)",
      #  "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1]})",
      #  "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1]})",
      #  "efficiency[0.9,0,1]",
      #  "signalFractionInPassing[0.9]"
      #),

    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = EFFICIENCYSET 
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)