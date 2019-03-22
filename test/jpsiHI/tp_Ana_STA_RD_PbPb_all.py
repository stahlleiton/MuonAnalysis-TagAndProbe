import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "twoGausPlusPol1"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/afs/cern.ch/user/o/okukral/TnP/Data/tnpJPsi_Data_PbPb_AOD.root"),
    InputDirectoryName = cms.string("tpTreeTrk"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_PbPb_RD_STA_AllMB.root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(16),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(False),
    binsForMassPlots = cms.uint32(50),
    binnedFit = cms.bool(False),
    #binsForFit = cms.uint32(50),
    
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

    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
         isSTA = cms.vstring("isSTA", "dummy[true=1,false=0]"),
         outerValidHits = cms.vstring("outerValidHits", "dummy[true=1,false=0]"),
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
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
        #the name of the parameter set becomes the name of the directory

        STA_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true","outerValidHits","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8,30.),
              pair_pt = cms.vdouble(3.,30),
              eta = cms.vdouble(-2.4,2.4),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_1bin_70100 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true","outerValidHits","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8,30.),
              pair_pt = cms.vdouble(3.,30),
              eta = cms.vdouble(-2.4,2.4),
              tag_hiBin = cms.vdouble(140,200),  
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_1bin_60100 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true","outerValidHits","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8,30.),
              pair_pt = cms.vdouble(3.,30),
              eta = cms.vdouble(-2.4,2.4),
              tag_hiBin = cms.vdouble(120,200),  
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_1bin_50100 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true","outerValidHits","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8,30.),
              pair_pt = cms.vdouble(3.,30),
              eta = cms.vdouble(-2.4,2.4),
              tag_hiBin = cms.vdouble(100,200),  
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_1bin_40100 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true","outerValidHits","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8,30.),
              pair_pt = cms.vdouble(3.,30),
              eta = cms.vdouble(-2.4,2.4),
              tag_hiBin = cms.vdouble(80,200),  
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_pt_periph = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true","outerValidHits","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8, 3.0, 4.5, 7.0, 15.0),
              pair_pt = cms.vdouble(3.,30),
              abseta = cms.vdouble(0.0, 2.4),
              tag_hiBin = cms.vdouble(120,200),          
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_eta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true","outerValidHits","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              eta = cms.vdouble(-2.4,-2.1,-1.2,0.,1.2,2.1,2.4),
              pair_pt = cms.vdouble(3.,30),
              pt = cms.vdouble(1.8,30.),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        STA_abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true","outerValidHits","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              abseta = cms.vdouble(0.,1.2,2.1,2.4),
              pair_pt = cms.vdouble(3.,30),
              pt = cms.vdouble(1.8,30),
            ),
            BinToPDFmap = cms.vstring(PDFName)
         ),
        STA_abseta_periph = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true","outerValidHits","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              abseta = cms.vdouble(0.,1.2,2.1,2.4),
              pair_pt = cms.vdouble(3.,30),
              pt = cms.vdouble(1.8,30),
              tag_hiBin = cms.vdouble(120,200), 
            ),
            BinToPDFmap = cms.vstring(PDFName)
         ),
        STA_centdep = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true","outerValidHits","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(1.8, 30),
              pair_pt = cms.vdouble(3.,30),
              eta = cms.vdouble(-2.4,2.4),
              tag_hiBin = cms.vdouble(0,80,140,200),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
    )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)

