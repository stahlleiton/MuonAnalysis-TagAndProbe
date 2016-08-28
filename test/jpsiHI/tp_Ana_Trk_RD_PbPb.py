import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "twoGaussPlusPoly6v1"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/home/llr/cms/chapon/data_CMS/tag_and_probe_2015data/tnpJpsi_Data_PbPb_AOD.root"),
    InputDirectoryName = cms.string("tpTreeSta"),
    InputTreeName = cms.string("fitter_tree"),
    #numbrer of CPUs to use for fitting
    OutputFileName = cms.string("tnp_Ana_RD_PbPb_MuonTrk_AllMB_isGlb.root"),
    NumCPU = cms.uint32(25),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(True),
    binsForMassPlots = cms.uint32(50),
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),
    #WeightVariable = cms.string("weight"),
    
    # defines all the real variables of the probes available in the input tree; can be used to select a subset of the probes
    Variables = cms.PSet(
        mass             = cms.vstring("Tag-Probe Mass", "2.0", "5.0", "GeV/c^{2}"),
        pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
        p                = cms.vstring("Probe p", "0", "1000", "GeV/c"),
        eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
        abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
        staValidStations = cms.vstring("Probe ValidStations", "0", "15", ""),
        tag_hiBin        = cms.vstring("Centrality bin", "0", "200", ""),
    ),
    # defines all the Flags on which one can test the probe against (if true, is 'pass', if false is 'failed')
    Categories = cms.PSet(
        Glb        = cms.vstring("Glb", "dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
      twoGaussPlusPoly6v1 = cms.vstring(
          "Gaussian::signal1(mass, mean[3.1,3.0,3.2], sigma[0.10,0.05,1.0])",
          "Gaussian::signal2(mass, mean1[3.7,3.5,3.9], sigma2[0.15,0.05,1.00])",
          "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
          "Chebychev::backgroundPass(mass, {cP[0,-0.4,0.4], cP2[0.0,-0.04,0.04], cP3[-0.031,-0.3,0.3]})", ### good
          "Chebychev::backgroundFail(mass, {cF[-0.33,-1.0,1.0], cF2[0.05,-1.0,1.0], cF3[0.02,-1.0,1.0]})", ### good
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
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt  = cms.vdouble(0,30),
                    eta = cms.vdouble(-2.4,2.4),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_1binSeg = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt  = cms.vdouble(0,30),
                    eta = cms.vdouble(-2.4,2.4),
                    staValidStations= cms.vdouble(1,10),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_pt = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(0, 3.5, 7., 10.5, 30.0),
                    eta = cms.vdouble(-2.4,2.4),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_ptSeg = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(0, 3.5, 7., 10.5, 30.0),
                    eta = cms.vdouble(-2.4,2.4),
                    staValidStations= cms.vdouble(1,10),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_eta = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    eta = cms.vdouble(-2.4,-1.6,-1.2,-0.9,0.9,1.2,1.6,2.4),
                    pt = cms.vdouble(0.,30.0),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_etaSeg = cms.PSet(
                    EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                    UnbinnedVariables = cms.vstring("mass"),
                    BinnedVariables = cms.PSet(
                        eta = cms.vdouble(-2.4,-1.6,-1.2,-0.9,0.9,1.2,1.6,2.4),
                        pt = cms.vdouble(0.,30.0),
                        staValidStations= cms.vdouble(1,10),
                    ),
                    BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_cent = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    eta = cms.vdouble(-2.4,2.4),
                    pt = cms.vdouble(0.,30.0),
                    tag_hiBin = cms.vdouble(0,10,20,40,60,80,100,150,200),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_centSeg = cms.PSet(
                    EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                    UnbinnedVariables = cms.vstring("mass"),
                    BinnedVariables = cms.PSet(
                       eta = cms.vdouble(-2.4,2.4),
                       pt = cms.vdouble(0.,30.0),
                       tag_hiBin = cms.vdouble(0,10,20,40,60,80,100,150,200),
                       staValidStations = cms.vdouble(1,10),
                    ),
                    BinToPDFmap = cms.vstring(PDFName)
            ),
    )
)

process.fitness = cms.Path(
        process.TagProbeFitTreeAnalyzer
)

