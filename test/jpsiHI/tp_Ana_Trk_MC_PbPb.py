import FWCore.ParameterSet.Config as cms

import sys
args =sys.argv[1:]
if len(args) < 2: scenario = "0"
else: 
   scenario = args[1]
print("Will run scenario " + scenario) 
# scenario: 1 pT, 2-3 pT in abseta bins, 4 abseta, 5 eta, 6 centrality, 0 (or no parameter) run all

process = cms.Process("TagProbe")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )
PDFName = "twoGausPlusPol2" #twoGausPlusPol2, twoGausPlusPol3, GausPlusPol2

# defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
# there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 

VEFFICIENCYSET =cms.VPSet(
   # Order: 0 total, 1 pT, 2-5 pT fits in abseta bins, 6 abseta, 7 eta, 8 centrality NOTE: IS NOT SAME AS SCENARIO
   cms.PSet(
      Trk_1bin = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring("Glb","true"),
         UnbinnedVariables = cms.vstring("mass","weight"),
         BinnedVariables = cms.PSet(
            pt  = cms.vdouble(0,30),
            eta = cms.vdouble(-2.4,2.4),
            isSTA = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(
      Trk_pt = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring("Glb","true"),
         UnbinnedVariables = cms.vstring("mass","weight"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(0, 3.5, 7., 10.5, 14.5, 30.0),
            eta = cms.vdouble(-2.4,2.4),
            isSTA = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(
      Trk_abseta00_12 = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring("Glb","true"),
         UnbinnedVariables = cms.vstring("mass","weight"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(0, 3.5, 7., 10.5, 14.5, 30.0),
            abseta = cms.vdouble(0.0,1.2),
            isSTA = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(
      Trk_abseta12_18 = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring("Glb","true"),
         UnbinnedVariables = cms.vstring("mass","weight"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(0, 5., 10., 30.0),
            abseta = cms.vdouble(1.2,1.8),
            isSTA = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(
      Trk_abseta18_21 = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring("Glb","true"),
         UnbinnedVariables = cms.vstring("mass","weight"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(0, 5., 10., 30.0),
            abseta = cms.vdouble(1.8,2.1),
            isSTA = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(
      Trk_abseta21_24 = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring("Glb","true"),
         UnbinnedVariables = cms.vstring("mass","weight"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(0, 5., 10., 30.0),
            abseta = cms.vdouble(2.1,2.4),
            isSTA = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(
      Trk_etadep = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring("Glb","true"),
         UnbinnedVariables = cms.vstring("mass","weight"),
         BinnedVariables = cms.PSet(
            eta = cms.vdouble(-2.4,-1.6,-1.2,-0.9,-0.6,-0.3,0.3,0.6,0.9,1.2,1.6,2.4),
            pt = cms.vdouble(0.,30.0),
            isSTA = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(
      Trk_absetadep = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring("Glb","true"),
         UnbinnedVariables = cms.vstring("mass","weight"),
         BinnedVariables = cms.PSet(
            abseta = cms.vdouble(0,1.2,1.8,2.1,2.4),
            pt = cms.vdouble(0,30.0),
            isSTA = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(
      Trk_centdep = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring("Glb","true"),
         UnbinnedVariables = cms.vstring("mass","weight"),
         BinnedVariables = cms.PSet(
            eta = cms.vdouble(-2.4,2.4),
            pt = cms.vdouble(0.,30.0),
            tag_hiBin = cms.vdouble(0,10,20,40,60,80,100,150,200),
            isSTA = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   )

#Actual selection
if scenario == "1": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0], VEFFICIENCYSET[1])
if scenario == "2": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[2], VEFFICIENCYSET[3])
if scenario == "3": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[4], VEFFICIENCYSET[5])
if scenario == "4": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[6])
if scenario == "5": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[7])
if scenario == "6": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[8])
if scenario == "0": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0],VEFFICIENCYSET[1],VEFFICIENCYSET[2], VEFFICIENCYSET[3],VEFFICIENCYSET[4], VEFFICIENCYSET[5],VEFFICIENCYSET[6], VEFFICIENCYSET[7],VEFFICIENCYSET[8])

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/eos/cms/store/group/phys_heavyions/dileptons/TNPTagAndProbe2018/MC2018/PbPb502TeV/tnpJpsi_MC_PbPb_Official_mod_v3.root"),
    InputDirectoryName = cms.string("tpTreeSta"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("Output/Trk/tnp_Ana_MC_PbPb_Trk_%s_%s.root" % ("mass2347", scenario)),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(16),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(False),
    binsForMassPlots = cms.uint32(50),
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),
    WeightVariable = cms.string("weight"),
    
    # defines all the real variables of the probes available in the input tree; can be used to select a subset of the probes
    Variables = cms.PSet(
        mass             = cms.vstring("Tag-Probe Mass", "2.3", "4.7", "GeV/c^{2}"),  # mass range syst:  2.3-4.7 nominal: 2.0-5.0
        pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
        p                = cms.vstring("Probe p", "0", "1000", "GeV/c"),
        eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
        abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
        staNumValidHits  = cms.vstring("Probe Valid Hits", "0", "60", ""),
        tag_hiBin        = cms.vstring("Centrality bin", "0", "200", ""),
        weight           = cms.vstring("weight", "0", "100", ""),
    ),
    # defines all the Flags on which one can test the probe against (if true, is 'pass', if false is 'failed')
    Categories = cms.PSet(
       Glb        = cms.vstring("Glb", "dummy[true=1,false=0]"),
       isSTA      = cms.vstring("isSTA", "dummy[true=1,false=0]"),
       InAcceptance_2018_Tight = cms.vstring("InAcceptance_2018_Tight", "dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
        #nominal:
     twoGausPlusPol2 = cms.vstring(
          "Gaussian::signal1(mass, mean1[3.08,2.9,3.4], sigma1[0.02, 0.019, 0.6])",
          "Gaussian::signal2(mass, mean2[3.11,2.9,3.4], sigma2[0.025, 0.019, 0.6])",
          "SUM::signal(vFrac[0.8,0.1,1]*signal1, signal2)",
          "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1]})",
          "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1]})",
          "efficiency[0.9,0,1]",
          "signalFractionInPassing[0.9]"
       ),
    #background syst:
      twoGausPlusPol3 = cms.vstring(  
          "Gaussian::signal1(mass, mean1[3.08,2.9,3.4], sigma1[0.02, 0.009, 0.4])",
          "Gaussian::signal2(mass, mean2[3.11,2.9,3.4], sigma2[0.025, 0.009, 0.4])",
          "SUM::signal(vFrac[0.8,0.1,1]*signal1, signal2)",
          "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1], cPass3[0.,-1.1,1.1]})",
          "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1], cFail3[0.,-1.1,1.1]})",
          "efficiency[0.9,0,1]",
          "signalFractionInPassing[0.9]"
       ),
        #signal syst:
     GausPlusPol2 = cms.vstring( 
          "Gaussian::signal(mass, mean1[3.08,2.9,3.4], sigma1[0.02, 0.009, 0.4])",
          "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1]})", 
          "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1]})", 
          "efficiency[0.9,0,1]",
          "signalFractionInPassing[0.9]"
       ),

    ),
    Efficiencies = EFFICIENCYSET
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)
