import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "cbGausPlusPol2"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/home/llr/cms/chapon/data_CMS/tag_and_probe_2015data/tnpJpsi_Data_PbPb_AOD.root"),
    InputDirectoryName = cms.string("tpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_RD_PbPb_MuonIDTrg_AllMB.root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(25),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    #binnedFit = cms.bool(True),
    #binsForFit = cms.uint32(30),
    #binsForMassPlots = cms.uint32(50),
    binsForMassPlots = cms.uint32(50),
    #binnedFit = cms.bool(True),
    #binsForFit = cms.uint32(50),
    SaveWorkspace = cms.bool(True),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         mass             = cms.vstring("Tag-Probe Mass", "2.6", "3.5", "GeV/c^{2}"),
                         pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
                         tag_hiBin        = cms.vstring("Centrality", "0", "200", ""),
                         # TEMPORARY FIX: SELECT ONLY THE SECOND PART OF THE RUN (WHEN THE TRIGGER WAS MOSTLY UNPRESCALED)
                         run              = cms.vstring("Run number", "263322", "263757", ""), 
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
      cbGausPlusPol2 = cms.vstring(
        "Gaussian::signal1(mass, mean[3.1,3.0,3.2], sigma[0.02, 0.01, 0.1])",
        "CBShape::signal2(mass, mean, sigma2[0.05, 0.005, 0.1], alpha[1.9, 1.5, 2.5], n[1.7, 1.5, 3.])",
        "SUM::signal(frac[0.2,0,1]*signal1,signal2)",
        "Chebychev::backgroundPass(mass, {cPass[0,-1.0,1.0], cPass2[0,-1.0,1.0]})",
        "Chebychev::backgroundFail(mass, {cFail[0,-1.0,1.0], cFail2[0,-1.0,1.0]})",
        "efficiency[0.8,0,1]",
        "signalFractionInPassing[0.9]"
      ),
    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
            MuIdTrg_1bin = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
                # EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","dxyPVdzmin","true","dzPV","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 30),
                    eta = cms.vdouble(-2.4, 2.4),
                    run = cms.vdouble(263322, 263757),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_abseta00_12 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
                # EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","dxyPVdzmin","true","dzPV","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(3.5, 4, 4.5, 5, 5.5, 6.5, 30),
                    eta = cms.vdouble(0, 1.2),
                    run = cms.vdouble(263322, 263757),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_abseta12_21 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
                # EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","dxyPVdzmin","true","dzPV","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 2, 2.5, 3, 3.5, 4, 4.5, 5.5, 30),
                    eta = cms.vdouble(1.2,2.1),
                    run = cms.vdouble(263322, 263757),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_abseta21_24 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
                # EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","dxyPVdzmin","true","dzPV","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 2, 2.5, 3, 3.5, 4, 5, 30),
                    eta = cms.vdouble(2.1,2.4),
                    run = cms.vdouble(263322, 263757),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_absetadep = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
                # EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","dxyPVdzmin","true","dzPV","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 30),
                    abseta = cms.vdouble(0,1.2,2.1,2.4),
                    run = cms.vdouble(263322, 263757),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_etadep = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
                # EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","dxyPVdzmin","true","dzPV","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 30),
                    eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,0,0.9,1.2,1.6,2.1,2.4),
                    run = cms.vdouble(263322, 263757),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_centdep = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
                # EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","dxyPVdzmin","true","dzPV","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 30),
                    eta = cms.vdouble(-2.4,2.4),
                    tag_hiBin = cms.vdouble(0,10,20,40,60,80,100,150,200),
                    run = cms.vdouble(263322, 263757),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
    )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)

