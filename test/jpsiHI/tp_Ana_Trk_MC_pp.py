import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "triGaussPlusPoly3"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    #InputFileNames = cms.vstring("root://cms-xrd-global.cern.ch//store/group/phys_heavyions/dileptons/TNPTagAndProbe2015/Data2015/pp502TeV/TTrees/tnpJPsi_Data_pp5TeV_AOD.root"),
    InputFileNames = cms.vstring("tnpJPsi_MC_pp5TeV_AOD.root"),
    InputDirectoryName = cms.string("tpTreeSta"),
    InputTreeName = cms.string("fitter_tree"),
    #numbrer of CPUs to use for fitting
    OutputFileName = cms.string("tnp_Ana_Trk_MC_pp.root"),
    NumCPU = cms.uint32(25),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(False),
    binsForMassPlots = cms.uint32(50),
    binnedFit = cms.bool(False),
    #binsForFit = cms.uint32(45),
    WeightVariable = cms.string("weight"),
    
    # defines all the real variables of the probes available in the input tree; can be used to select a subset of the probes
    Variables = cms.PSet(
        mass             = cms.vstring("Tag-Probe Mass", "2.0", "5.0", "GeV/c^{2}"),
        pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
        p                = cms.vstring("Probe p", "0", "1000", "GeV/c"),
        eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
        abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
        staQoverP        = cms.vstring("Probe Q/p", "-200", "200", ""),
        staQoverPerror   = cms.vstring("Probe Q/p error", "0", "650", ""),
        staValidStations = cms.vstring("Probe STA valid stations", "0", "15", ""),

        tag_pt           = cms.vstring("Tag p_{T}", "0.0", "1000", "GeV/c"),
        tag_eta          = cms.vstring("Tag #eta", "-2.4", "2.4", ""),
        tag_abseta       = cms.vstring("Tag |#eta|", "0", "2.5", ""),
        pair_pt          = cms.vstring("Pair p_{T}", "0.0", "1000", "GeV/c"),
        pair_absy        = cms.vstring("Pair |Y|", "-2.4", "2.4", ""),
        pair_y           = cms.vstring("Pair Y", "0", "2.5", ""),
        weight           = cms.vstring("weight","0","1000",""),
    ),
    # defines all the Flags on which one can test the probe against (if true, is 'pass', if false is 'failed')
    Categories = cms.PSet(
        Glb        = cms.vstring("Glb", "dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values
    PDFs = cms.PSet(
      triGaussPlusPoly3 = cms.vstring(
          "Gaussian::signal1(mass, m1[3.1,2.8,3.3], sigma1[0.1,0.005,0.3])",
          "Gaussian::signal2(mass, m1, sigma2[0.1,0.005,0.3])",
          "SUM::signalJpsi(vFrac[0.9,0.0,1.0]*signal1, signal2)",
          "Gaussian::signal3(mass, m2[3.5,3.3,3.9], sigma3[0.1,0.005,0.3])",
          "SUM::signal(vFracJpsi[0.9,0.0,1.0]*signalJpsi, signal3)",
          "Chebychev::backgroundPass(mass, {zP[0.0,-1.0,1.0], zP2[0.0,-1.0,1.0], zP3[0.0,-1.0,1.0]})", ### good
          "Chebychev::backgroundFail(mass, {zF[-0.0,-1.0,1.0], zF2[0.0,-1.0,1.0], zF3[0.0,-1.0,1.0]})", ### good
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
    )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)

