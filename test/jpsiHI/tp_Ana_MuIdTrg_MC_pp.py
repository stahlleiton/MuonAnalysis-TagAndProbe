import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "cbPlusPoly2nd"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/afs/cern.ch/user/e/echapon/workspace/private/tag_and_probe_2015data/CMSSW_7_5_8_patch3/src/MuonAnalysis/TagAndProbe/test/jpsiHI/tnpJPsi_Data_pp5TeV_AOD_99.root"),
    InputDirectoryName = cms.string("tpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_MC_pp_MuonIDTrg_AllMB.root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(1),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(False),
    #binsForFit = cms.uint32(30),
    binsForMassPlots = cms.uint32(50),
    SaveWorkspace = cms.bool(True),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         mass             = cms.vstring("Tag-Probe Mass", "2.6", "3.5", "GeV/c^{2}"),
                         pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
                          HybridSoftHI = cms.vstring("HybridSoftHI", "dummy[true=1,false=0]"),
                          HLTL1v0   = cms.vstring("HLTL1v0", "dummy[true=1,false=0]"),
                          HLTL1v1   = cms.vstring("HLTL1v1", "dummy[true=1,false=0]"),
                          HLTL1v2   = cms.vstring("HLTL1v2", "dummy[true=1,false=0]"),
                          dzPV = cms.vstring("dzPV","dummy[true=1,false=0]"),
                          dxyPVdzmin = cms.vstring("dxyPVdzmin","dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
      cbPlusPoly2nd = cms.vstring(
        "CBShape::signal(mass, mean[3.1,3.0,3.2], sigma[0.02, 0.01, 0.1], alpha[2.0, 0.2, 10.0], n[4, 0.5, 50.])",
        "Chebychev::backgroundPass(mass, {cPass[0,-0.5,0.5], cPass2[0,-0.5,0.5]})",
        "Chebychev::backgroundFail(mass, {cFail[0,-0.5,0.5], cFail2[0,-0.5,0.5]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ),
    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
            PassingGlb_1bin = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.5, 30),
                    eta = cms.vdouble(-2.4, 2.4),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
    )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)

