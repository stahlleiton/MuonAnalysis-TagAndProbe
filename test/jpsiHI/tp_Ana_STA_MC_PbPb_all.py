import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    


PDFName = "twoGausPlusPol2"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/afs/cern.ch/work/j/jmartinb/DataSets/HIRun2015/TagAndProbe/MC/PbPb/tnpJpsi_MC_PbPb_merged_pt03inf_wtNcoll_norm.root"),
    InputDirectoryName = cms.string("tpTreeTrk"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_PbPb_MC_GLB_MB_ArbNone_AllMB_nopt06.root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(16),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(True),
    binsForMassPlots = cms.uint32(50),
    binnedFit = cms.bool(False),
    #binsForFit = cms.uint32(50),
    WeightVariable = cms.string("weight_norm"),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "2.8", "3.4", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        p = cms.vstring("Probe p", "0", "1000", "GeV/c"),
        eta = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
        abseta = cms.vstring("Probe |#eta|", "0", "2.4", ""),
        tag_pt = cms.vstring("Tag p_{T}", "0", "1000", "GeV/c"),
        pair_pt = cms.vstring("Dimuon p_{T}", "0", "1000", "GeV/c"),
        tag_hiBin = cms.vstring("Centrality", "0", "200", ""),
        weight_norm = cms.vstring("weight_norm","0.0","1500.0",""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
         isSTA = cms.vstring("isSTA", "dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
      twoGausPlusPol2 = cms.vstring(
         "Gaussian::signal1(mass, mean[3.08,3.02,3.3], sigma1[0.02, 0.009, 0.08])",
         "Gaussian::signal2(mass, mean, sigma2[0.025, 0.009, 0.08])",
         "SUM::signal(vFrac[0.8,0.5,1]*signal1, signal2)",
         "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1]})", ### good
         "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1]})", ### good
         "efficiency[0.9,0,1]",
         "signalFractionInPassing[0.9]"
       ),
       cbGausPlusPol2 = cms.vstring(
          "CBShape::signal1(mass, mean1[3.08,3.06,3.2], sigma1[0.02, 0.009, 0.07], alpha[1.85, 1.1, 2.7], n[1.7, 1.2, 3.5])",
          "Gaussian::signal2(mass, mean2[3.11,3.08,3.3], sigma2[0.025, 0.009, 0.07])",
          "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
          "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1], cPass3[0.,-1.1,1.1]})", ### good
          "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1], cFail3[0.,-1.1,1.1]})", ### good
          "efficiency[0.9,0,1]",
          "signalFractionInPassing[0.9]"
       ),
       cbPlusExpo = cms.vstring(
        "CBShape::signal(mass, mean[3.08,3.0,3.2], sigma[0.01,0.0,0.2], alpha[2.0, 0.2, 10.0], n[4, 0.5, 100.])",
       # "CBShape::signal(mass, mean[3.1,3.0,3.2], sigma[0.02,0.02,0.1], alpha[1.0, 0.2, 3.0], n[4, 0.5, 100.])",
        "Exponential::backgroundPass(mass, lp[0,-5,5])",
        "Exponential::backgroundFail(mass, lf[0,-5,5])",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ),
      cbGausPlusExpo = cms.vstring(
       "Gaussian::signal1(mass, mean[3.08,3.05,3.2], sigma[0.02, 0.01, 0.1])",
       "CBShape::signal2(mass, mean1[3.1,3.0,3.2], sigma2[0.1, 0.02, 0.3], alpha[2.0, 1.0, 10.0], n[4, 0.5, 100.])",
        "SUM::signalPass(fracP[0.8,0,1]*signal1,signal2)",
        "SUM::signalFail(fracF[0.8,0,1]*signal1,signal2)",
        "Exponential::backgroundPass(mass, lp[0,-5,5])",
        "Exponential::backgroundFail(mass, lf[0,-5,5])",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ),
    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
        #the name of the parameter set becomes the name of the directory
        STA_pt1 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass","weight_norm"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(3.5, 4.0, 4.5, 5.0, 6.0, 7.0, 10.0, 30.0),
              pair_pt = cms.vdouble(3., 30),
              abseta = cms.vdouble(0.0, 1.2),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_pt2 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass","weight_norm"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8,2,2.5,3,3.5,4, 5,8, 30),
              pair_pt = cms.vdouble(3.,30),
              abseta = cms.vdouble(1.2, 2.1),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_pt3 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass","weight_norm"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8,2,2.5,3,3.5,4, 5,8, 30),
              pair_pt = cms.vdouble(3.,30),
              abseta = cms.vdouble(2.1, 2.4),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass","weight_norm"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8,30.),
              pair_pt = cms.vdouble(3.,30),
              eta = cms.vdouble(-2.4,2.4),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_eta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass","weight_norm"),
            BinnedVariables = cms.PSet(
              eta = cms.vdouble(-2.4,-2.1,-1.2,0.,1.2,2.1,2.4),
              pair_pt = cms.vdouble(3.,30),
              pt = cms.vdouble(1.8,30.),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass","weight_norm"),
            BinnedVariables = cms.PSet(
              abseta = cms.vdouble(0.,1.2,2.1,2.4),
              pair_pt = cms.vdouble(3.,30),
              pt = cms.vdouble(1.8,30),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_centdep = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass","weight_norm"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8, 30),
              pair_pt = cms.vdouble(3.,30),
              eta = cms.vdouble(-2.4,2.4),
              tag_hiBin = cms.vdouble(0,10,20,40,60,80,100,150,200),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
   )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)

