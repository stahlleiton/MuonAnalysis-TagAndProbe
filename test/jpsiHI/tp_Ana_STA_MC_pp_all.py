import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "twoGaussPlusPoly2"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    #InputFileNames = cms.vstring("root://cms-xrd-global.cern.ch//store/group/phys_heavyions/dileptons/TNPTagAndProbe2015/Data2015/pp502TeV/TTrees/tnpJPsi_Data_pp5TeV_AOD.root"),
    InputFileNames = cms.vstring("tnpJPsi_MC_pp5TeV_AOD.root"),
    InputDirectoryName = cms.string("tpTreeTrk"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_STA_pp_MC.root"),
    NumCPU = cms.uint32(25),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(False),
    binsForMassPlots = cms.uint32(50),
    binnedFit = cms.bool(False),
    #binsForFit = cms.uint32(45),
    #WeightVariable = cms.string("weight"),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "2.8", "3.4", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        pair_pt = cms.vstring("Dimuon p_{T}", "0", "1000", "GeV/c"),
        eta = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
        abseta = cms.vstring("Probe |#eta|", "0", "2.4", ""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
        isSTA = cms.vstring("isSTA", "dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
       twoGaussPlusPoly2 = cms.vstring(
             "Gaussian::signal1(mass, mean[3.1,3.0,3.2], sigma1[0.025, 0.005, 0.08])",
             "Gaussian::signal2(mass, mean, sigma2[0.035, 0.008, 0.09])",
             "SUM::signal(vFrac[0.9,0.0,1.0]*signal1, signal2)",
             "Chebychev::backgroundPass(mass, {cP[0.0,-1.0,1.0], cP2[0.0,-1.0,1.0]})", ### good
             "Chebychev::backgroundFail(mass, {cF[0.0,-1.0,1.0], cF2[0.0,-1.0,1.0]})", ### good
             "efficiency[0.9,0.0,1.0]",
             "signalFractionInPassing[0.9]"
             ),
    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
        #the name of the parameter set becomes the name of the directory
        STA_pt1 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 6.0, 7.0, 10.0, 30.0),
              pair_pt = cms.vdouble(3., 30),
              abseta = cms.vdouble(0.0, 1.6), 
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_pt2 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
               pt = cms.vdouble(1.8,2,2.5,3,3.5,4, 5,8, 30),
               pair_pt = cms.vdouble(3.,30),
               abseta = cms.vdouble(1.6, 2.4),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(1.8,30.),
                eta = cms.vdouble(-2.4,2.4),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_eta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
               eta = cms.vdouble(-2.4,-1.6,0,1.6,2.4),
               pair_pt = cms.vdouble(3.,30),
               pt = cms.vdouble(1.8,30.),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble(0.,1.6,2.4),
                pair_pt = cms.vdouble(3.,30),
                pt = cms.vdouble(1.8,30),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),

    )
)


process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)
