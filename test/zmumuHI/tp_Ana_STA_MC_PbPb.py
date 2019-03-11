import FWCore.ParameterSet.Config as cms

import sys
args =sys.argv[1:]
if len(args) < 2: scenario = "0"
else: 
   scenario = args[1]
print("Will run scenario " + scenario) 

process = cms.Process("TagProbe")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    
PDFName = "BWResCBExp"

VEFFICIENCYSET =cms.VPSet(

	cms.PSet(
        STA_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
#                tag_nVertices = cms.vdouble(0, 4),
                pt = cms.vdouble(15, 80),
                eta = cms.vdouble(-2.4, 2.4),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
	),

	cms.PSet(
       STA_pt = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
           UnbinnedVariables = cms.vstring("mass"),
           BinnedVariables = cms.PSet( 
               pt = cms.vdouble(5, 15, 30, 50, 80),
               eta = cms.vdouble(-2.4,2.4),
#               tag_nVertices = cms.vdouble(0, 1, 2, 4),
           ),
           BinToPDFmap = cms.vstring(PDFName)
         )
	 ),

	cms.PSet(
        STA_abseta00_09 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
#                tag_nVertices = cms.vdouble(0, 1, 2, 4),
                pt = cms.vdouble(15, 30, 50, 80),
                abseta = cms.vdouble(0, 0.9),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
	),

	cms.PSet(
         STA_abseta09_12 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 30, 50, 80),
                 abseta = cms.vdouble(0.9,1.2),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),

	cms.PSet(
         STA_abseta12_16 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 30, 50, 80),
                 abseta = cms.vdouble(1.2, 1.6),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),

	cms.PSet(
         STA_abseta16_21 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 30, 50, 80),
                 abseta = cms.vdouble(1.6, 2.1),
             ),
             BinToPDFmap = cms.vstring(PDFName)
          )
	),

	  cms.PSet(
         STA_abseta21_24 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 30, 50, 80),
                 abseta = cms.vdouble(2.1,2.4),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),

	  cms.PSet(
          STA_absetadep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 80),
                 abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),

	  cms.PSet(
         STA_etadep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 80),
                 eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,0,0.9,1.2,1.6,2.1,2.4),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),
	cms.PSet(
	  STA_centdep = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(15, 80),
              eta = cms.vdouble(-2.4,2.4),
	      tag_hiBin = cms.vdouble(0, 20, 40, 60, 80, 100, 200),
            ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),
)
#)

#Actual selection
if scenario == "1": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0], VEFFICIENCYSET[1])
if scenario == "2": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[2], VEFFICIENCYSET[3])
if scenario == "3": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[5], VEFFICIENCYSET[6])
if scenario == "4": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[4], VEFFICIENCYSET[7])
if scenario == "0": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0], VEFFICIENCYSET[1], VEFFICIENCYSET[2], VEFFICIENCYSET[3],VEFFICIENCYSET[4], VEFFICIENCYSET[5],VEFFICIENCYSET[6], VEFFICIENCYSET[7], VEFFICIENCYSET[8], VEFFICIENCYSET[9])



process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:./tnpZ_MC_PbPb_mod.root"),
    InputDirectoryName = cms.string("tpTreeTrk"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_MC_STA_PbPb.root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(16),
    # specifies whether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(100),
    binsForMassPlots = cms.uint32(100),
    SaveWorkspace = cms.bool(False),
	WeightVariable = cms.string("weight"),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         mass             = cms.vstring("Tag-Probe Mass", "60.0", "120.0", "GeV/c^{2}"), # mass range syst: 2.8-3.4
                         pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
			 tag_hiBin        = cms.vstring("Centrality bin", "0", "200", ""),
			 weight		  = cms.vstring("weight", "0", "10", ""),
#                         tag_nVertices    = cms.vstring("Number of Primary Vertices", "0", "4", ""),
#                         tag_hiHF         = cms.vstring("HF energy", "0", "400", ""),
#                         tag_hiNtracks    = cms.vstring("Number of tracks", "0", "300", ""),
#                         tag_hiNtracks    = cms.vstring("N Tracks", "0", "400", ""),
#			 staValidStations = cms.vstring("Valid stations in muon system", "-2", "10", "cm"),
#			 Glb		  = cms.vstring("Probe Global", "0.0", "2.0", ""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
			 # MuIDForOutsideInTk = cms.vstring("OITK Seed", "dummy[pass=1,fail=0]"),
			 isSTA = cms.vstring("isSTA", "dummy[true=1,false=0]"),
#			  Glb = cms.vstring("Glb", "dummy[true=1,false=0]"),
#                          PF  = cms.vstring("PF", "dummy[true=1, false=0]"),
                        #Tight2012 = cms.vstring("Tight2012", "dummy[true=1,false=0]"),
                          #HybridSoftHI = cms.vstring("HybridSoftHI", "dummy[true=1,false=0]"),
                          #L1Filter  = cms.vstring("L1Filter", "dummy[true=1,false=0]"),
                          #L1Seed    = cms.vstring("L1Seed", "dummy[true=1,false=0]"),
                          #HLTL1v0   = cms.vstring("HLTL1v0", "dummy[true=1,false=0]"),
                          #HLTL1v1   = cms.vstring("HLTL1v1", "dummy[true=1,false=0]"),
                          #HLTL1v2   = cms.vstring("HLTL1v2", "dummy[true=1,false=0]"),
                          #dxyzPVCuts = cms.vstring("dxyzPVCuts","dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
	VoigtExp = cms.vstring(
		"Voigtian::signal(mass, mean[91,80,100], width[3,-5,15], sigma[3,-5,15])",
		"Exponential::backgroundPass(mass, lp[0,-5,5])",
		"Exponential::backgroundFail(mass, lf[0,-5,5])",
		"efficiency[0.9,0,1]",
		"signalFractionInPassing[0.9]"
	),
	BWResCBExp = cms.vstring(
		"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
		"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[0.8,0,10])",
		"FCONV::signal(mass, bw, res)",
		"Exponential::backgroundPass(mass, lp[0,-5,5])",
		"Exponential::backgroundFail(mass, lf[0,-5,5])",
		"efficiency[0.9,0.5,1]",
		"signalFractionInPassing[0.9]",
	),
	BWResCBCheb = cms.vstring(
		"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
		"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[0.8,0,10])",
		"FCONV::signal(mass, bw, res)",
		"Chebychev::backgroundPass(mass, {c1p[0,-10,10], c2p[0,-10,10], c3p[0,-10,10]})",
		"Chebychev::backgroundFail(mass, {c1f[0,-10,10], c2f[0,-10,10], c3f[0,-10,10]})",
		"efficiency[0.9,0.5,1]",
		"signalFractionInPassing[0.9]",
	),
      #  #nominal:
      #cbPlusPol1 = cms.vstring(
      #  "CBShape::signal(mass, mean[3.08,3.00,3.3], sigma[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
      #  "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1]})",
      #  "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1]})",
      #  "efficiency[0.9,0,1]",
      #  "signalFractionInPassing[0.9]"
      #),
      #  #background syst:
      #cbPlusPol2 = cms.vstring(
      #  "CBShape::signal(mass, mean[3.08,3.00,3.2], sigma[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
      #  "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1]})",
      #  "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1]})",
      #  "efficiency[0.9,0,1]",
      #  "signalFractionInPassing[0.9]"
      #),
      #  #signal syst:
      #cbGausPlusPol1 = cms.vstring(
      #  "CBShape::signal1(mass, mean[3.08,3.00,3.3], sigma1[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
      #  "RooFormulaVar::sigma2('@0*@1',{fracS[1.8,1.2,2.4],sigma1})",
      #  "Gaussian::signal2(mass, mean, sigma2)",
      #  "SUM::signal(frac[0.8,0.5,1.]*signal1,signal2)",
      #  "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1]})",
      #  "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1]})",
      #  "efficiency[0.9,0,1]",
      #  "signalFractionInPassing[0.9]"
  ),

    
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = EFFICIENCYSET
#        STA_nPVdep = cms.PSet(
#           EfficiencyCategoryAndState = cms.vstring("MuIDForOutsideInTk","pass"),
#            EfficiencyCategoryAndState = cms.vstring("Glb","true"),
#            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                tag_nVertices = cms.vdouble(0, 1, 4),
#                pt = cms.vdouble(15, 80),
#                eta = cms.vdouble(-2.4, 2.4),
#            ),
#            BinToPDFmap = cms.vstring(PDFName)
#        ),

#        STA_HFdep = cms.PSet(
#            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                tag_hiHF = cms.vdouble(0, 50, 75, 95, 115, 150, 400),
#                pt = cms.vdouble(15, 80),
#                eta = cms.vdouble(-2.4, 2.4),
#            ),
#            BinToPDFmap = cms.vstring(PDFName)
#        ),
#
#        STA_nTracksdep = cms.PSet(
#            EfficiencyCategoryAndState = cms.vstring("isSTA","true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                tag_hiNtracks = cms.vdouble(0, 50, 75, 95, 115, 150, 300),
#                pt = cms.vdouble(15, 80),
#                eta = cms.vdouble(-2.4, 2.4),
#            ),
#            BinToPDFmap = cms.vstring(PDFName)

)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)
