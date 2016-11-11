import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "twoGausPlusPol3"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/afs/cern.ch/work/j/jmartinb/DataSets/HIRun2015/TagAndProbe/MC/PbPb/tnpJpsi_MC_PbPb_merged_pt03inf_wtNcoll_norm.root"),
    InputDirectoryName = cms.string("tpTreeSta"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_MC_PbPb_MuonTrk_AllMB_isGlb.root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(16),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(True),
    binsForMassPlots = cms.uint32(50),
    binnedFit = cms.bool(False),
    #binsForFit = cms.uint32(50),
    WeightVariable = cms.string("weight_norm"),
    
    # defines all the real variables of the probes available in the input tree; can be used to select a subset of the probes
    Variables = cms.PSet(
        mass             = cms.vstring("Tag-Probe Mass", "2.0", "5.0", "GeV/c^{2}"),
        pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
        p                = cms.vstring("Probe p", "0", "1000", "GeV/c"),
        eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
        abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
        staValidStations = cms.vstring("Probe ValidStations", "0", "15", ""),
        tag_hiBin        = cms.vstring("Centrality bin", "0", "200", ""),
        weight_norm           = cms.vstring("weight_norm", "0", "100000", ""),
    ),
    # defines all the Flags on which one can test the probe against (if true, is 'pass', if false is 'failed')
    Categories = cms.PSet(
        Glb        = cms.vstring("Glb", "dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
      twoGausPlusPol3 = cms.vstring(
          "Gaussian::signal1(mass, mean1[3.08,2.9,3.4], sigma1[0.02, 0.009, 0.4])",
          "Gaussian::signal2(mass, mean2[3.11,2.9,3.4], sigma2[0.025, 0.009, 0.4])",
          "SUM::signal(vFrac[0.8,0.5,1]*signal1, signal2)",
          "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1], cPass3[0.,-1.1,1.1]})", ### good
          "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1], cFail3[0.,-1.1,1.1]})", ### good
          "efficiency[0.9,0,1]",
          "signalFractionInPassing[0.9]"
       ),
       cbGausPlusPol3 = cms.vstring(
          "CBShape::signal1(mass, mean1[3.08,3.06,3.4], sigma1[0.02, 0.009, 0.07], alpha[1.85, 1.1, 2.7], n[1.7, 1.2, 3.5])",
          "Gaussian::signal2(mass, mean2[3.11,3.08,3.4], sigma2[0.025, 0.009, 0.07])",
          "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
          "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1], cPass3[0.,-1.1,1.1]})", ### good
          "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1], cFail3[0.,-1.1,1.1]})", ### good
          "efficiency[0.9,0,1]",
          "signalFractionInPassing[0.9]"
       ),
    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
        #the name of the parameter set becomes the name of the directory
        # for multiple passing flags in EfficiencyCategorAndState = cms.vstring("flag1","state","flag2","state",...),
            Trk_1bin = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    pt  = cms.vdouble(0,30),
                    eta = cms.vdouble(-2.4,2.4),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_1binSeg = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    pt  = cms.vdouble(0,30),
                    eta = cms.vdouble(-2.4,2.4),
                    staValidStations= cms.vdouble(1,15),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_pt = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(0, 3.5, 7., 10.5, 14.5, 30.0),
                    eta = cms.vdouble(-2.4,2.4),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_ptSeg = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(0, 3.5, 7., 10.5, 14.5, 30.0),
                    eta = cms.vdouble(-2.4,2.4),
                    staValidStations= cms.vdouble(1,15),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_eta = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    eta = cms.vdouble(-2.4,-1.6,-1.2,-0.9,-0.6,-0.3,0.3,0.6,0.9,1.2,1.6,2.4),
                    pt = cms.vdouble(0.,30.0),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_etaSeg = cms.PSet(
                    EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                    UnbinnedVariables = cms.vstring("mass","weight_norm"),
                    BinnedVariables = cms.PSet(
                        eta = cms.vdouble(-2.4,-1.6,-1.2,-0.9,-0.6,-0.3,0.3,0.6,0.9,1.2,1.6,2.4),
                        pt = cms.vdouble(0.,30.0),
                        staValidStations= cms.vdouble(1,15),
                    ),
                    BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_cent = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass","weight_norm"),
                BinnedVariables = cms.PSet(
                    eta = cms.vdouble(-2.4,2.4),
                    pt = cms.vdouble(0.,30.0),
                    tag_hiBin = cms.vdouble(0,10,20,40,60,80,100,150,200),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_centSeg = cms.PSet(
                    EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                    UnbinnedVariables = cms.vstring("mass","weight_norm"),
                    BinnedVariables = cms.PSet(
                       eta = cms.vdouble(-2.4,2.4),
                       pt = cms.vdouble(0.,30.0),
                       tag_hiBin = cms.vdouble(0,10,20,40,60,80,100,150,200),
                       staValidStations= cms.vdouble(1,15),
                    ),
                    BinToPDFmap = cms.vstring(PDFName)
            ),
    )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)

