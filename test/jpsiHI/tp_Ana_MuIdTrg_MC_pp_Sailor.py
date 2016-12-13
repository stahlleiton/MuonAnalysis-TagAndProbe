import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "CBGPlusPol2"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    #InputFileNames = cms.vstring("root://cms-xrd-global.cern.ch//store/group/phys_heavyions/dileptons/TNPTagAndProbe2015/Data2015/pp502TeV/TTrees/tnpJPsi_Data_pp5TeV_AOD.root"),
    InputFileNames = cms.vstring("file:/afs/cern.ch/work/v/vabdulla/private/TnP/tnpJPsi_MC_pp5TeV_AOD.root"),
    InputDirectoryName = cms.string("tpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("file:/afs/cern.ch/work/v/vabdulla/private/TnP/tnp_Ana_MuonIDTrg_MC_pp_sailor_pTbins2.root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(50),
    # specifies whether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(False),
    #binsForFit = cms.uint32(30),
    binsForMassPlots = cms.uint32(50),
    SaveWorkspace = cms.bool(False),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         mass             = cms.vstring("Tag-Probe Mass", "2.6", "3.5", "GeV/c^{2}"),
                         pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
                         pair_deltaPhi         = cms.vstring("Tag-Probe Delta Phi", "-3.2", "3.2", ""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
                          HybridSoftHI = cms.vstring("HybridSoftHI", "dummy[true=1,false=0]"),
                          HLTL1v0   = cms.vstring("HLTL1v0", "dummy[true=1,false=0]"),
                          HLTL1v1   = cms.vstring("HLTL1v1", "dummy[true=1,false=0]"),
                          HLTL1v2   = cms.vstring("HLTL1v2", "dummy[true=1,false=0]"),
                          dzPV = cms.vstring("dzPV","dummy[true=1,false=0]"),
                          dxyPVdzmin = cms.vstring("dxyPVdzmin","dummy[true=1,false=0]"),
                          dxyzPVCuts = cms.vstring("dxyzPVCuts","dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
        CBPlusPol2 = cms.vstring(
            "CBShape::signal1(mass, mean[3.1,3.0,3.2], sigma1[0.025, 0.008, 0.08], alpha[2.1, 0.9, 50.0], n[3.0, 0.2, 50.])",
            "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1]})",
            "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1]})",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        
        CBGPlusPol2 = cms.vstring(
            "CBShape::signal1(mass, mean[3.1,3.05,3.15], sigma1[0.025, 0.008, 0.1], alpha[2.1, 0.9, 50.0], n[3.0, 0.2, 50.])",
            "Gaussian::signal2(mass, mean, sigma2[0.04, 0.01, 0.2])",
            "SUM::signal(vFrac[0.6,0.0,1.0]*signal1, signal2)",
            "Chebychev::backgroundPass(mass, {cPass[0,-2.0,2.0], cPass2[0,-2.0,2.0]})",
            "Chebychev::backgroundFail(mass, {cFail[0,-2.0,2.0], cFail2[0,-2.0,2.0]})",
            "efficiency[0.9,0.0,1.0]",
            "signalFractionInPassing[0.9]"
        ),
    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
     Efficiencies = cms.PSet(
         MuIdTrg_1bin = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(1.8, 30),
                 eta = cms.vdouble(-2.4, 2.4),
                 pair_deltaPhi = cms.vdouble(-3.2, 0),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),
         
         MuIdTrg_abseta00_12 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(3.0, 3.5, 3.75, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9.5, 10.5, 12, 16, 30),
                 abseta = cms.vdouble(0, 1.2),
                 pair_deltaPhi = cms.vdouble(-3.2, 0),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),
         
         MuIdTrg_abseta12_21 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(1.8, 2.0, 2.25, 2.5, 3, 3.25, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8.5, 9.5, 11.5, 16, 30),
                 abseta = cms.vdouble(1.2,2.1),
                 pair_deltaPhi = cms.vdouble(-3.2, 0),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),
         
         #MuIdTrg_abseta12_16 = cms.PSet(
          #   EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
           #  UnbinnedVariables = cms.vstring("mass"),
            # BinnedVariables = cms.PSet(
             #    pt = cms.vdouble(2.75, 3.0, 3.25, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7.5, 9, 15, 30),
              #   abseta = cms.vdouble(1.2,1.6),
               #  pair_deltaPhi = cms.vdouble(-3.2, 0),
             #),
             #BinToPDFmap = cms.vstring(PDFName)
         #),
         
         #MuIdTrg_abseta16_21 = cms.PSet(
          #   EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
           #  UnbinnedVariables = cms.vstring("mass"),
            # BinnedVariables = cms.PSet(
             #    pt = cms.vdouble(1.8, 2.0, 2.25, 2.5, 2.75, 3, 3.25, 3.5, 4, 4.5, 5, 5.5, 6, 7, 8.5, 14, 30),
              #   abseta = cms.vdouble(1.6,2.1),
               #  pair_deltaPhi = cms.vdouble(-3.2, 0),
             #),
             #BinToPDFmap = cms.vstring(PDFName)
         #),
         
         MuIdTrg_abseta21_24 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(1.8, 2, 2.25, 2.5, 2.75, 3, 3.5, 4, 4.5, 5.5, 7.5, 14, 30),
                 abseta = cms.vdouble(2.1,2.4),
                 pair_deltaPhi = cms.vdouble(-3.2, 0),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),
         
         MuIdTrg_etadep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(1.8, 30),
                 eta = cms.vdouble(-2.4,-2.1,-1.2,0,1.2,2.1,2.4),
                 pair_deltaPhi = cms.vdouble(-3.2, 0),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),
         
         MuIdTrg_absetadep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(1.8, 30),
                 abseta = cms.vdouble(0,1.2,2.1,2.4),
                 pair_deltaPhi = cms.vdouble(-3.2, 0),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),
         
         #MuIdTrg_etadep_ext = cms.PSet(
          #   EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
           #  UnbinnedVariables = cms.vstring("mass"),
            # BinnedVariables = cms.PSet(
             #    pt = cms.vdouble(1.8, 30),
              #   eta = cms.vdouble(-2.4,-2.1,-1.2,0,1.2,2.1,2.4),
               #  pair_deltaPhi = cms.vdouble(-3.2, 0),
             #),
             #BinToPDFmap = cms.vstring(PDFName)
         #),
         
        # MuIdTrg_absetadep_ext = cms.PSet(
         #    EfficiencyCategoryAndState = cms.vstring("HybridSoftHI","true","HLTL1v0","true","HLTL1v1","true","HLTL1v2","true","dxyPVdzmin","true","dzPV","true"),
          #   UnbinnedVariables = cms.vstring("mass"),
           #  BinnedVariables = cms.PSet(
            #     pt = cms.vdouble(1.8, 30),
             #    abseta = cms.vdouble(0,1.2,2.1,2.4),
              #   pair_deltaPhi = cms.vdouble(-3.2, 0),
             #),
             #BinToPDFmap = cms.vstring(PDFName)
         #),
     )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)
