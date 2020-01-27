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
PDFName = "CBGausExp"



VEFFICIENCYSET =cms.VPSet(
# Order: 0 total, 1 pT, 2-8 pT fits in abseta bins, 9 abseta, 10 eta, 11 centrality, 12+ various   NOTE: IS NOT SAME AS SCENARIO, SCENARIO DEFINED BELOW
    cms.PSet(
        Trk_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
            UnbinnedVariables = cms.vstring("mass", "weight"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(15, 100),
                eta = cms.vdouble(-2.4, 2.4),
                TM = cms.vstring("true"),
                TrackCuts = cms.vstring("true"),
                PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ),
   cms.PSet(
       Trk_pt = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
           UnbinnedVariables = cms.vstring("mass", "weight"),
           BinnedVariables = cms.PSet(
               pt = cms.vdouble(15, 30, 50, 100),
               eta = cms.vdouble(-2.4,2.4),
               TM = cms.vstring("true"),
               TrackCuts = cms.vstring("true"),
               PF = cms.vstring("true"),
           ),
           BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
        Trk_abseta00_09 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
            UnbinnedVariables = cms.vstring("mass", "weight"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(15, 30, 50, 100),
                abseta = cms.vdouble(0, 0.9),
                TM = cms.vstring("true"),
                TrackCuts = cms.vstring("true"),
                PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_abseta09_12 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(0.9,1.2),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_abseta00_12 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(0.0,1.2),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_abseta12_16 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(1.2, 1.6),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_abseta16_21 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(1.6, 2.1),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_abseta12_21 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(1.2, 2.1),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_abseta21_24 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(2.1,2.4),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_absetadep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 100),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
         Trk_etadep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 100),
                 eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,0,0.9,1.2,1.6,2.1,2.4),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
        Trk_centdep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 100),
                 eta = cms.vdouble(-2.4,2.4),
                 tag_hiBin = cms.vdouble(0, 20, 40, 60, 80, 100, 200),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(
          Trk_absetadep_cent0040 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 100),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(00, 80),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_absetadep_cent40100 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 100),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(80, 200),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ), 

    cms.PSet(
          Trk_absetadepPF_cent0040 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 100),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(00, 80),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_absetadepPF_cent40100 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(15, 100),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(80, 200),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_absetadep_cent0040_lowPT = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(10, 30),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(00, 80),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_absetadep_cent40100_lowPT = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("Glb","true","PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(10, 30),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(80, 200),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
                 PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ), 

    cms.PSet(
          Trk_absetadepPF_cent0040_lowPT = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(10, 30),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(00, 80),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
          Trk_absetadepPF_cent40100_lowPT = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("PF","true"),
             UnbinnedVariables = cms.vstring("mass", "weight"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(10, 30),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                 tag_hiBin = cms.vdouble(80, 200),
                 TM = cms.vstring("true"),
                 TrackCuts = cms.vstring("true"),
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
if scenario == "8": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[11])
if scenario == "9": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[12], VEFFICIENCYSET[13])
if scenario == "10": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[14], VEFFICIENCYSET[15])
if scenario == "11": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[16], VEFFICIENCYSET[17])
if scenario == "12": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[18], VEFFICIENCYSET[19])
if scenario == "0": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0], VEFFICIENCYSET[1],VEFFICIENCYSET[2], VEFFICIENCYSET[3],VEFFICIENCYSET[4], VEFFICIENCYSET[5], VEFFICIENCYSET[6], VEFFICIENCYSET[7], VEFFICIENCYSET[8], VEFFICIENCYSET[9], VEFFICIENCYSET[10], VEFFICIENCYSET[11], VEFFICIENCYSET[12], VEFFICIENCYSET[13], VEFFICIENCYSET[14], VEFFICIENCYSET[15])



process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
   # InputFileNames = cms.vstring("file:/eos/cms/store/group/phys_heavyions/dileptons/TNPTagAndProbe2018/MC2018/PbPb502TeV/tnpZ_MC_PbPb_Official_mod_v5.root"),
    InputFileNames = cms.vstring("file:/afs/cern.ch/work/o/okukral/TnP_PbPb/CMSSW_10_3_2/src/MuonAnalysis/TagAndProbe/test/zmumuHI/tnpZ_MC_PbPb_Official_mod_v6.root"),
    InputDirectoryName = cms.string("tpTreeTrk"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_MC_TrkfromTrkM9_PbPb_sig_%s.root" % scenario),   #m5->6 added TC
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(16),
    # specifies whether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),
    binsForMassPlots = cms.uint32(50),
    SaveWorkspace = cms.bool(False),
    WeightVariable = cms.string("weight"),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         mass             = cms.vstring("Tag-Probe Mass", "70.0", "120.0", "GeV/c^{2}"), # mass range syst:       #orig 45
                         pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
                         tag_hiBin        = cms.vstring("Centrality bin", "0", "200", ""),
                         phi              = cms.vstring("phi", "-3.2", "3.2", ""),
                         weight           = cms.vstring("weight", "0", "10000", ""),

    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
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
    BWConvCBExp = cms.vstring( #n fixed to integrated bin in MC
		"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
		"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[1.9])",
		"FCONV::signal(mass, bw, res)",
		"Exponential::backgroundPass(mass, lp[0,-5,5])",
		"Exponential::backgroundFail(mass, lf[0,-5,5])",
		"efficiency[0.9,0.5,1]",
		"signalFractionInPassing[0.9]",
	),
    BWConvCBPol1 = cms.vstring( #n fixed to integrated bin in MC
		"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
		"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[1.9])",
		"FCONV::signal(mass, bw, res)",
        "Chebychev::backgroundPass(mass, {cPass[0.0,-1.5,1.5]})",
        "Chebychev::backgroundFail(mass, {cFail[0.1,-1.5,1.5]})",
		"efficiency[0.9,0.5,1]",
		"signalFractionInPassing[0.9]",
	),
    CBGausExp = cms.vstring( #n fixed to integrated bin in MC
        "CBShape::signal1(mass, mean[91, 80, 100], sigma1[3, 1, 10], alpha[1.9], n[0.8])",
        "RooFormulaVar::sigma2('@0*@1',{fracS[1.6,0.8,3.2],sigma1})",
        "Gaussian::signal2(mass, mean, sigma2)",
        "SUM::signal(frac[0.8,0.2,1.]*signal1,signal2)",
		"Exponential::backgroundPass(mass, lp[0,-5,5])",
		"Exponential::backgroundFail(mass, lf[0,-5,5])",
		"efficiency[0.9,0.5,1]",
		"signalFractionInPassing[0.9]",
	),
    #BWConvCBExpPol2 = cms.vstring( #n fixed to integrated bin in MC
	#	"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
	#	"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[1.92])",
	#	"FCONV::signal(mass, bw, res)",
    #   "Exponential::backgroundPass(mass, lp[0,-5,5])",
    #   "Chebychev::backgroundFail(mass, {cFail[-0.3,-1.5,1.5], cFail2[0.01,-0.5,0.5]})",
	#   "efficiency[0.9,0.5,1]",
	#	"signalFractionInPassing[0.9]",
	#),
    #BWConvCBPol1Exp = cms.vstring( #n fixed to integrated bin in MC
	#	"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
	#	"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[1.92])",
	#	"FCONV::signal(mass, bw, res)",
    #   "Chebychev::backgroundPass(mass, {cPass[0.0,-1.5,1.5]})",
    #   "Exponential::backgroundFail(mass, lf[0,-5,5])",
	#	"efficiency[0.9,0.5,1]",
	#	"signalFractionInPassing[0.9]",
	#),

    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = EFFICIENCYSET 
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)