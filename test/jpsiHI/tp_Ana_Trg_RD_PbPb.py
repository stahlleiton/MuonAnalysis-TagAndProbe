import FWCore.ParameterSet.Config as cms

import sys
args =sys.argv[1:]
if len(args) < 2: scenario = "0"
else: 
   scenario = args[1]
   filterTag = args[2]
print("Will run scenario " + scenario) 

# scenario: 1 pT, 2-3 pT in abseta bins, 4 abseta, 5 eta, 6 centrality, 7 runNb, 0 (or no parameter) run all

process = cms.Process("TagProbe")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    
PDFName = "cbPlusPol1" #cbPlusPol1, cbPlusPol2, cbGausPlusPol1, cbGausPlusPol2
TagTrg = "TagMu5" #"TagMu3"

filterName = "HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_L2Filter"
if filterTag == "L3Jpsi" : filterName = "HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_L3Filter"
if filterTag == "L2Upsi": filterName = "HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_L2Filter"
if filterTag == "L3Upsi" : filterName = "HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_L3Filter"

triggerName = "HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5" #matching to the trigger path 
if filterTag == "L2Upsi": triggerName = "isUnprescaled" # in the case of the upsilon trigger this becomes a dummy flag because we don't want mass gating 
if filterTag == "L3Upsi": triggerName = "isUnprescaled"

print("the filter used is " + filterName)
print("the trigger is " + triggerName)

# defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
# there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 

VEFFICIENCYSET =cms.VPSet(
   # Order: 0 total, 1 pT, 2-5 pT fits in abseta bins, 6 abseta, 7 eta, 8 centrality NOTE: IS NOT SAME AS SCENARIO
   cms.PSet(
      Trg_1bin = cms.PSet( #0 sc 1
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(1.5, 30),
            eta = cms.vdouble(-2.4, 2.4),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),
         ),
         BinToPDFmap = cms.vstring(PDFName)
      )
   ),
   cms.PSet( #1 sc 1
      Trg_pt = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(3.5, 4, 4.5, 5, 5.5, 6.5, 8., 10.5, 14, 18, 30.),
            eta = cms.vdouble(-2.4, 2.4),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),             
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),                        
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(#2 sc 2     
      Trg_abseta00_12 = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(3.5, 4, 4.5, 5, 5.5, 6.5, 8., 10.5, 14, 18, 30.),
            abseta = cms.vdouble(0, 1.2),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),             
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),                        
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(#3 sc 2
      Trg_abseta12_18 = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(2.07, 3.0, 3.5, 4, 4.5, 5., 6., 7.5, 10, 15, 30),
            abseta = cms.vdouble(1.2,1.8),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),             
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),                        
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(#4 sc 3
      Trg_abseta18_21 = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(1.5, 2.5, 3, 3.5, 4, 4.5, 5.5, 6.5, 8, 9.5, 13, 20),
            abseta = cms.vdouble(1.8,2.1),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),             
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),                        
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(#5 sc 3
      Trg_abseta21_24 = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(1.5, 2.2, 2.7, 3.2, 3.7, 4.7, 6.5, 8.5, 11, 20),
            abseta = cms.vdouble(2.1,2.4),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),             
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),                        
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(#6 sc 4
      Trg_absetadep = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(1.5, 30),
            abseta = cms.vdouble(0,1.2,1.8,2.1,2.4),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),             
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),                        
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ), 
   cms.PSet(#7 sc 5
      Trg_etadep = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(1.5, 30),
            eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,-0.6,-0.3,0,0.3,0.6,0.9,1.2,1.6,2.1,2.4),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),             
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),                        
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(#8 sc 6
      Trg_centdep = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(1.5, 30),
            eta = cms.vdouble(-2.4,2.4),
            tag_hiBin = cms.vdouble(0,10,20,40,60,80,100,150,200),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),             
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),                        
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(#9 sc 7
      Trg_rundep = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(1.5, 30),
            eta = cms.vdouble(-2.4,2.4),
            run = cms.vdouble(326381, 326618, 326791, 326921, 327051, 327181, 327312, 327438, 327564),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),             
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),                        
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(#10 sc 8     
      Trg_abseta00_12_largerbins = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(3.5, 4.5, 5.5, 8., 10.5, 14, 18, 30.),
            abseta = cms.vdouble(0, 1.2),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),                        
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(#11 sc 8 
      Trg_abseta12_18_largerbins = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(2.07, 3.5, 4.5, 6., 8., 10, 15, 30),
            abseta = cms.vdouble(1.2,1.8),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),             
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),                        
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(#12 sc 8 
      Trg_abseta18_21_largerbins = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(1.5, 3, 4, 5.5, 8, 9.5, 13, 20),
            abseta = cms.vdouble(1.8,2.1),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),             
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),                        
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
   cms.PSet(#13 sc 8
      Trg_abseta21_24_largerbins = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring(filterName,"true",triggerName,"true"),
         UnbinnedVariables = cms.vstring("mass"),
         BinnedVariables = cms.PSet(
            pt = cms.vdouble(1.5, 2.5, 3., 4.5, 6.5, 8.5, 11, 20),
            abseta = cms.vdouble(2.1,2.4),
            isHybridSoftMuon2018 = cms.vstring("true"),
            InAcceptance_2018_Tight = cms.vstring("true"),
            isUnprescaled = cms.vstring("true"),
            tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("true"),
            ),
         BinToPDFmap = cms.vstring(PDFName)
         )
      ),
)

#Actual selection
if scenario == "1": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0], VEFFICIENCYSET[1])
if scenario == "2": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[2], VEFFICIENCYSET[3])
if scenario == "3": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[4], VEFFICIENCYSET[5])
if scenario == "4": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[6])
if scenario == "5": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[7])
if scenario == "6": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[8])
if scenario == "7": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[9])
if scenario == "8": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[10], VEFFICIENCYSET[11], VEFFICIENCYSET[12], VEFFICIENCYSET[13])

if scenario == "0": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0],VEFFICIENCYSET[1],VEFFICIENCYSET[2], VEFFICIENCYSET[3],VEFFICIENCYSET[4], VEFFICIENCYSET[5],VEFFICIENCYSET[6], VEFFICIENCYSET[7],VEFFICIENCYSET[8],VEFFICIENCYSET[9])

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/eos/cms/store/group/phys_heavyions/dileptons/TNPTagAndProbe2018/Data2018/PbPb502TeV/tnpJpsi_Data_PbPb_%s_mod_v4.root" % (TagTrg)),
    InputDirectoryName = cms.string("tpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("Output/Trg/tnp_Ana_RD_PbPb_Trg_%s_%s_%sFilter_%s.root" % (filterTag, "mass2834", TagTrg, scenario) ), #"mass2834" for mass range systematics #L3M310QH, L3M12
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(25),
    # specifies whether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(False),
    binsForFit = cms.uint32(30),
    binsForMassPlots = cms.uint32(50),
    SaveWorkspace = cms.bool(False),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
       mass             = cms.vstring("Tag-Probe Mass", "2.8", "3.4", "GeV/c^{2}"),   # mass range syst: 2.8-3.4, nominal:2.6-3.5 
       pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
       eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
       abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
       tag_hiBin        = cms.vstring("Centrality", "0", "200", ""),
       run              = cms.vstring("run number", "326000", "328000", ""),
       tkChi2           = cms.vstring("trk Chi^2", "-5", "20", ""),
       tkHitFract       = cms.vstring("trk Hit Fraction", "0", "2", ""),
       tkPixelLay       = cms.vstring("trk Pixel Layer", "0", "20", ""),
       tkTrackerLay     = cms.vstring("trk Tracker Layer", "0", "50", ""),
       tkValidHits      = cms.vstring("trk Valid Hits", "0", "50", ""),
       tkValidPixelHits = cms.vstring("trk Valid Pixel Hits", "0", "10", ""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
                        Categories = cms.PSet(
                           isHybridSoftMuon2018 = cms.vstring("isHybridSoftMuon2018", "dummy[true=1,false=0]"),
                           InAcceptance_2018_Tight = cms.vstring("InAcceptance_2018_Tight", "dummy[true=1,false=0]"),
                           HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_L2Filter = cms.vstring("HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_L2Filter", "dummy[true=1,false=0]"),
                           HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_L3Filter = cms.vstring("HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_L3Filter", "dummy[true=1,false=0]"),
                           HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5 = cms.vstring("HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5", "dummy[true=1,false=0]"),
                           HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_L2Filter = cms.vstring("HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_L2Filter", "dummy[true=1,false=0]"),
                           HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_L3Filter = cms.vstring("HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_L3Filter", "dummy[true=1,false=0]"),
                           HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf = cms.vstring("HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf", "dummy[true=1,false=0]"),
                           isUnprescaled = cms.vstring("isUnprescaled", "dummy[true=1,false=0]"),
                           isNonMuonSeeded = cms.vstring("isNonMuonSeeded", "dummy[true=1,false=0]"),
                           passedDZ_TIGHT = cms.vstring("passedDZ_TIGHT", "dummy[true=1,false=0]"),
                           isNonFake = cms.vstring("isNonFake", "dummy[true=1,false=0]"),
                           tag_HLT_HIL3Mu12 = cms.vstring("tag_HLT_HIL3Mu12", "dummy[true=1,false=0]"),
                           tag_HLT_HIL3Mu15 = cms.vstring("tag_HLT_HIL3Mu15", "dummy[true=1,false=0]"),
                           tag_HLT_HIL3Mu20 = cms.vstring("tag_HLT_HIL3Mu20", "dummy[true=1,false=0]"),
                           tag_HLT_HIL3Mu3_NHitQ10 = cms.vstring("tag_HLT_HIL3Mu3_NHitQ10", "dummy[true=1,false=0]"),
                           tag_HLT_HIL3Mu5_NHitQ10 = cms.vstring("tag_HLT_HIL3Mu5_NHitQ10", "dummy[true=1,false=0]"),
                           tag_HLT_HIL3Mu7_NHitQ10 = cms.vstring("tag_HLT_HIL3Mu7_NHitQ10", "dummy[true=1,false=0]"),
                        ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
        #nominal:
       cbPlusPol1 = cms.vstring(
          #"CBShape::signal(mass, mean[3.08,3.00,3.2], sigma[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[2.7, 0.5, 50])",
          "CBShape::signal(mass, mean[3.08,3.00,3.2], sigma[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.5, 50])",
          "Chebychev::backgroundPass(mass, {cPass[0.,-1,1]})",
          "Chebychev::backgroundFail(mass, {cFail[0.,-1,1]})",
          "efficiency[0.9,0,1]",
          "signalFractionInPassing[0.9]"
      ), 
        #background syst:
        cbPlusPol2 = cms.vstring(
           "CBShape::signal(mass, mean[3.08,3.00,3.2], sigma[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[2.7, 0.5, 50])",
           "Chebychev::backgroundPass(mass, {cPass[0.,-1,1], cPass2[0.,-1,1]})",
           "Chebychev::backgroundFail(mass, {cFail[0.,-1,1], cFail2[0.,-1,1]})",
           "efficiency[0.9,0,1]",
           "signalFractionInPassing[0.9]"
        ),
        #signal syst:
      cbGausPlusPol1 = cms.vstring(
        "CBShape::signal1(mass, mean[3.08,3.00,3.2], sigma1[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
        "RooFormulaVar::sigma2('@0*@1',{fracS[1.8,1.2,2.4],sigma1})",
        "Gaussian::signal2(mass, mean, sigma2)",
        "SUM::signal(frac[0.8,0.1,1.]*signal1,signal2)",
        "Chebychev::backgroundPass(mass, {cPass[0.,-2,2]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-2,2]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ),
      cbGausPlusPol2 = cms.vstring(
        "CBShape::signal1(mass, mean[3.08,3.00,3.2], sigma1[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
        "RooFormulaVar::sigma2('@0*@1',{fracS[1.8,1.2,2.4],sigma1})",
        "Gaussian::signal2(mass, mean, sigma2)",
        "SUM::signal(frac[0.8,0.1,1.]*signal1,signal2)",
        "Chebychev::backgroundPass(mass, {cPass[0.,-2,2], cPass2[0.,-2,2]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-2,2], cFail2[0.,-2,2]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ),
    ),
   Efficiencies = EFFICIENCYSET

)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)
