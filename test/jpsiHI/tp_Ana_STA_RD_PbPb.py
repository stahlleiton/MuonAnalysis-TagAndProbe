import FWCore.ParameterSet.Config as cms

import sys
args =sys.argv[1:]
if len(args) < 2: scenario = "0"
else: 
   scenario = args[1]
print("Will run scenario " + scenario) 

process = cms.Process("TagProbe")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )
PDFName = "twoGausPlusPol1" #twoGausPlusPol1, GausPlusPol1

# defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
# there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 

VEFFICIENCYSET =cms.VPSet(
    cms.PSet(
        STA_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8,30.),
              pair_pt = cms.vdouble(3.,30),
              eta = cms.vdouble(-2.4,2.4),
              tag_hiBin = cms.vdouble(140,200),
              #dz = cms.vdouble(0,4),
              InAcceptance_2018_Tight = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
            )
        ),
    cms.PSet(
        STA_pt = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8, 2.5, 3, 3.5, 4.0, 4.5, 5.0, 6.0, 7.0, 10.0, 30.0),
              pair_pt = cms.vdouble(3., 30),
              eta = cms.vdouble(-2.4, 2.4),
              tag_hiBin = cms.vdouble(140,200),
              #dz = cms.vdouble(0,4),
              InAcceptance_2018_Tight = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
            )
        ),
    cms.PSet(
        STA_abseta00_12 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(3.5, 4.0, 4.5, 5.0, 6.0, 7.0, 10.0, 30.0),
              pair_pt = cms.vdouble(3., 30),
              abseta = cms.vdouble(0.0, 1.2),
              tag_hiBin = cms.vdouble(140,200),
              #dz = cms.vdouble(0,4),
              InAcceptance_2018_Tight = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
            )
        ),
    cms.PSet(
        STA_abseta12_21 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8,2,2.5,3,3.5,4, 5,8, 30),
              pair_pt = cms.vdouble(3.,30),
              abseta = cms.vdouble(1.2, 2.1),
              tag_hiBin = cms.vdouble(140,200),
              #dz = cms.vdouble(0,4),
              InAcceptance_2018_Tight = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
            )
        ),
    cms.PSet(
        STA_abseta21_24 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8,2,2.5,3,3.5,4, 5,8, 30),
              pair_pt = cms.vdouble(3.,30),
              abseta = cms.vdouble(2.1, 2.4),
              tag_hiBin = cms.vdouble(140,200),
              #dz = cms.vdouble(0,4),
              InAcceptance_2018_Tight = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
            )
        ),
    cms.PSet(
        STA_eta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              eta = cms.vdouble(-2.4,-2.1,-1.2,0.,1.2,2.1,2.4),
              pair_pt = cms.vdouble(3.,30),
              pt = cms.vdouble(1.8,30.),
              tag_hiBin = cms.vdouble(140,200),
              #dz = cms.vdouble(0,4),
              InAcceptance_2018_Tight = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
            )
        ),
    cms.PSet(
        STA_abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              abseta = cms.vdouble(0.,1.2,2.1,2.4),
              pair_pt = cms.vdouble(3.,30),
              pt = cms.vdouble(1.8,30),
              tag_hiBin = cms.vdouble(140,200),
              #dz = cms.vdouble(0,4),
              InAcceptance_2018_Tight = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
            )
        ),
    cms.PSet(
        STA_centdep = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8, 30),
              pair_pt = cms.vdouble(3.,30),
              eta = cms.vdouble(-2.4,2.4),
              tag_hiBin = cms.vdouble(100,150,200),
              #dz = cms.vdouble(0,4),
              InAcceptance_2018_Tight = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
            )
        ),
   )
#Actual selection
if scenario == "1": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0], VEFFICIENCYSET[1])
if scenario == "2": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[2], VEFFICIENCYSET[3], VEFFICIENCYSET[4])
if scenario == "3": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[5])
if scenario == "4": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[6])
if scenario == "5": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[7])
if scenario == "0": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0], VEFFICIENCYSET[1], VEFFICIENCYSET[2], VEFFICIENCYSET[3],VEFFICIENCYSET[4], VEFFICIENCYSET[5],VEFFICIENCYSET[6], VEFFICIENCYSET[7])


process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/eos/cms/store/group/phys_heavyions/dileptons/TNPTagAndProbe2018/Data2018/PbPb502TeV/tnpJpsi_Data_PbPb_mod_v3.root"),
    InputDirectoryName = cms.string("tpTreeTrk"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("Output/Sta/tnp_Ana_RD_PbPb_STA_%s_%s.root" % (PDFName,scenario)),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(16),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(False),
    binsForMassPlots = cms.uint32(50),
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "2.6", "3.5", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        p = cms.vstring("Probe p", "0", "1000", "GeV/c"),
        pair_pt = cms.vstring("Dimuon p_{T}", "0", "1000", "GeV/c"),
        eta = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
        abseta = cms.vstring("Probe |#eta|", "0", "2.4", ""),
        tag_pt = cms.vstring("Tag p_{T}", "0", "1000", "GeV/c"),
        tag_hiBin = cms.vstring("Centrality", "0", "200", ""),
        dz = cms.vstring("dz", "0", "100", ""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
         isSTA = cms.vstring("isSTA", "dummy[true=1,false=0]"),
         InAcceptance_2018_Tight = cms.vstring("InAcceptance_2018_Tight", "dummy[true=1,false=0]"),
    ),   

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
      twoGausPlusPol1 = cms.vstring(
        "Gaussian::signal1(mass, mean[3.08,3.02,3.3], sigma1[0.02, 0.009, 0.2])",
        "Gaussian::signal2(mass, mean, sigma2[0.05, 0.009, 0.2])",
        "SUM::signal(vFrac[0.8,0.1,1]*signal1, signal2)",
        "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ),
    # alternate:
      GausPlusPol1 = cms.vstring(
        "Gaussian::signal(mass, mean[3.1,2.9,3.3], sigma[0.025, 0.005, 0.3])",
        "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1]})", 
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ),
    ),
    Efficiencies = EFFICIENCYSET
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)
