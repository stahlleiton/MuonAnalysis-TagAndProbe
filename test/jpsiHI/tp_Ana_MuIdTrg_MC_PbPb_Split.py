import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "cbPlusPol1"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/afs/cern.ch/user/o/okukral/TnP/Data/tnpJpsi_MC_PbPb_merged_pt03inf_wtNcoll_norm.root"),
    InputDirectoryName = cms.string("tpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_MC_PbPb_MuonIDTrg_AllMB.root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(16),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(False),
    binsForMassPlots = cms.uint32(50),
    binnedFit = cms.bool(False),
    #binsForFit = cms.uint32(50),
    WeightVariable = cms.string("weight_norm"),
    
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         mass             = cms.vstring("Tag-Probe Mass", "2.6", "3.5", "GeV/c^{2}"),
                         pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
                         tag_hiBin        = cms.vstring("Centrality", "0", "200", ""),
                         weight_norm     = cms.vstring("weight_norm","0","100000",""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
                          HybridSoftHI = cms.vstring("HybridSoftHI", "dummy[true=1,false=0]"),
                          L1Filter  = cms.vstring("L1Filter", "dummy[true=1,false=0]"),
                          L1Seed    = cms.vstring("L1Seed", "dummy[true=1,false=0]"),
                          HLTL1v0   = cms.vstring("HLTL1v0", "dummy[true=1,false=0]"),
                          HLTL1v1   = cms.vstring("HLTL1v1", "dummy[true=1,false=0]"),
                          HLTL1v2   = cms.vstring("HLTL1v2", "dummy[true=1,false=0]"),
                          dxyzPVCuts = cms.vstring("dxyzPVCuts","dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
      cbPlusPol2 = cms.vstring(
        "CBShape::signal(mass, mean[3.08,3.06,3.1], sigma[0.03, 0.01, 0.06], alpha[1.85, 1.1, 2.7], n[1.7, 1.2, 3.5])",
        "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ),
      cbGausPlusPol2 = cms.vstring(
        "CBShape::signal1(mass, mean[3.08,3.06,3.1], sigma1[0.03, 0.01, 0.06], alpha[1.85, 1.1, 2.7], n[1.7, 1.2, 3.5])",
        "RooFormulaVar::sigma2('@0*@1',{fracS[1.8,1.2,2.4],sigma1})",
        "Gaussian::signal2(mass, mean, sigma2)",
        "SUM::signal(frac[0.8,0.5,1.]*signal1,signal2)",
        "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
     ),
      cbPlusPol1 = cms.vstring(
        "CBShape::signal(mass, mean[3.08,3.06,3.1], sigma[0.03, 0.01, 0.06], alpha[1.85, 1.1, 2.7], n[1.7, 1.2, 3.5])",
        "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ),
      cbGausPlusPol1 = cms.vstring(
        "CBShape::signal1(mass, mean[3.08,3.06,3.1], sigma1[0.03, 0.01, 0.06], alpha[1.85, 1.1, 2.7], n[1.7, 1.2, 3.5])",
        "RooFormulaVar::sigma2('@0*@1',{fracS[1.8,1.2,2.4],sigma1})",
        "Gaussian::signal2(mass, mean, sigma2)",
        "SUM::signal(frac[0.8,0.5,1.]*signal1,signal2)",
        "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ),
    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
            MuIdTrg_1bin = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyzPVCuts","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 30),
                    eta = cms.vdouble(-2.4, 2.4),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_abseta00_12 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyzPVCuts","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(3.5,3.75, 4, 4.25, 4.5, 4.75, 5, 5.25, 5.5, 6.0, 6.5, 7.0, 8., 9.0, 10.5, 11.5, 12.5, 17.5, 30.),
                    abseta = cms.vdouble(0, 1.2),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_abseta12_18 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyzPVCuts","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(2.37, 2.7, 3.0, 3.25, 3.5, 3.75, 4, 4.25, 4.5, 5.25, 5.0, 5.5, 6.0, 6.5, 7.5, 9.0, 12.5, 17.5, 30),
                    abseta = cms.vdouble(1.2,1.8),
                 ),
                 BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_abseta18_21 = cms.PSet(
               EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyzPVCuts","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 1.9, 2, 2.25, 2.5, 2.75, 3, 3.25, 3.5, 3.75, 4, 4.25, 4.5, 5.0, 5.5, 6.0, 7.0, 9.0, 12.5, 17.5, 30),
                    abseta = cms.vdouble(1.8,2.1),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_abseta21_24 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyzPVCuts","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 2.0, 2.2, 2.45, 2.7, 2.95, 3.2, 3.45, 3.7, 4.1, 4.7, 6.0, 8., 12.0, 30.),
                    abseta = cms.vdouble(2.1,2.4),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_absetadep = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyzPVCuts","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 30),
                    abseta = cms.vdouble(0,1.2,1.8,2.1,2.4),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_etadep = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyzPVCuts","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 30),
                    eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,-0.6,-0.3,0,0.3,0.6,0.9,1.2,1.6,2.1,2.4), #same
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            MuIdTrg_centdep = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyzPVCuts","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 30),
                    eta = cms.vdouble(-2.4,2.4),
                    tag_hiBin = cms.vdouble(0,10,20,40,60,80,100,150,200) #same
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
    )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)

