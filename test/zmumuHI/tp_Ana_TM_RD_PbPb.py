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
PDFName = "VoigtPol2" #VoigtExp, BWResCBExp, BWResCBCheb, VoigtPol2, BWResCBPol2

VEFFICIENCYSET =cms.VPSet(

	cms.PSet(
        TM_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("TM","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
#                tag_nVertices = cms.vdouble(0, 4),
                pt = cms.vdouble(15, 200),
                eta = cms.vdouble(-2.4, 2.4),
		TrackCuts = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
	),

	cms.PSet(
       TM_pt = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("TM","true"),
           UnbinnedVariables = cms.vstring("mass"),
           BinnedVariables = cms.PSet( 
               pt = cms.vdouble(15, 30, 50, 100),
               eta = cms.vdouble(-2.4,2.4),
#               tag_nVertices = cms.vdouble(0, 1, 2, 4),
		TrackCuts = cms.vstring("true"),
           ),
           BinToPDFmap = cms.vstring(PDFName)
         )
	 ),

	cms.PSet(
        TM_abseta00_09 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("TM","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
#                tag_nVertices = cms.vdouble(0, 1, 2, 4),
                pt = cms.vdouble(15, 30, 50, 100),
                abseta = cms.vdouble(0, 0.9),
		TrackCuts = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
	),

	cms.PSet(
         TM_abseta09_12 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("TM","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(0.9,1.2),
		 TrackCuts = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),

	cms.PSet(
         TM_abseta00_12 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("TM","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(0.0,1.2),
		 TrackCuts = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),

	cms.PSet(
         TM_abseta12_16 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("TM","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(1.2, 1.6),
		 TrackCuts = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),

	cms.PSet(
         TM_abseta16_21 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("TM","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(1.6, 2.1),
		 TrackCuts = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
          )
	),

	cms.PSet(
         TM_abseta12_21 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("TM","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(1.2, 2.1),
		 TrackCuts = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
          )
	),

	  cms.PSet(
         TM_abseta21_24 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("TM","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 30, 50, 100),
                 abseta = cms.vdouble(2.1,2.4),
		 TrackCuts = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),

	  cms.PSet(
          TM_absetadep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("TM","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 200),
                 #abseta = cms.vdouble(0.9,1.2,1.6,2.1,2.4),
                 abseta = cms.vdouble(0,0.3,0.5,0.9,1.2,1.6,2.0,2.4),
		 TrackCuts = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),

	  cms.PSet(
         TM_etadep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("TM","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
#                 tag_nVertices = cms.vdouble(0, 1, 2, 4),
                 pt = cms.vdouble(15, 200),
                 #eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,0,0.9,1.2,1.6,2.1,2.4),
                 eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,-0.5,-0.3,-0.2,0.2,0.3,0.5,0.9,1.2,1.6,2.1,2.4),
	         TrackCuts = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),
	cms.PSet(
	  TM_centdep = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("TM","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
              pt = cms.vdouble(15, 200),
              eta = cms.vdouble(-2.4,2.4),
	      tag_hiBin = cms.vdouble(0, 20, 40, 60, 80, 100, 200),
              TrackCuts = cms.vstring("true"),
            ),
             BinToPDFmap = cms.vstring(PDFName)
         )
	),

	cms.PSet(
	TM_phi = cms.PSet(
	  EfficiencyCategoryAndState = cms.vstring("TM","true"),
	  UnbinnedVariables = cms.vstring("mass"),
	  BinnedVariables = cms.PSet(
	    pt = cms.vdouble(15,200),
	    eta = cms.vdouble(-2.4,2.4),
	    phi = cms.vdouble(-3.5, -2.5, -1.5, -0.5, 0.5, 1.5,  2.5, 3.5),
	    TrackCuts = cms.vstring("true"),
	  ),
	    BinToPDFmap = cms.vstring(PDFName)
	 )
	),

)
#)

#Actual selection
if scenario == "1": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0], VEFFICIENCYSET[1])
if scenario == "2": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[2], VEFFICIENCYSET[3])
if scenario == "3": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[4], VEFFICIENCYSET[6])
if scenario == "4": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[5]) 
if scenario == "5": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[7], VEFFICIENCYSET[8])
if scenario == "6": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[9])
if scenario == "7": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[10])
if scenario == "8": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[11])
if scenario == "0": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0],VEFFICIENCYSET[1],VEFFICIENCYSET[2], VEFFICIENCYSET[3],VEFFICIENCYSET[4], VEFFICIENCYSET[5],VEFFICIENCYSET[6], VEFFICIENCYSET[7],VEFFICIENCYSET[8], VEFFICIENCYSET[9], VEFFICIENCYSET[10],VEFFICIENCYSET[11],VEFFICIENCYSET[12])




process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:./tnpZ_Data_PbPb_mod_v5.root"),
    InputDirectoryName = cms.string("tpTreeTrk"),
    InputTreeName = cms.string("fitter_tree"),
    #OutputFileName = cms.string("tnp_Ana_Data_RecoTM_PbPb.root"),
    OutputFileName = cms.string("tnp_Ana_RD_TM_PbPb_moreEta_v5_nominal_%s.root" % scenario),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(24),
    # specifies whether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(False),
    binsForFit = cms.uint32(100),
    binsForMassPlots = cms.uint32(100),
    SaveWorkspace = cms.bool(False),
#	WeightVariable = cms.string("weight"),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         mass             = cms.vstring("Tag-Probe Mass", "60.0", "120.0", "GeV/c^{2}"), # mass range syst: 2.8-3.4
                         #mass             = cms.vstring("Tag-Probe Mass", "50.0", "130.0", "GeV/c^{2}"), # Syst_mass
                         pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
			 tag_hiBin        = cms.vstring("Centrality bin", "0", "200", ""),
			 phi		  = cms.vstring("Probe #phi", "-3.5", "3.5", ""),
#			 weight	 	  = cms.vstring("weight", "0", "10000", ""),
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
			 TM = cms.vstring("TM", "dummy[true=1,false=0]"),
			 TrackCuts = cms.vstring("TrackCuts","dummy[true=1,false=0]")
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
		"Voigtian::signal(mass, mean[91,85,95], width[3,1,10], sigma[3,1,10])",
		"Exponential::backgroundPass(mass, lp[0,-5,5])",
		"Exponential::backgroundFail(mass, lf[0,-5,5])",
		"efficiency[0.9,0,1]",
		"signalFractionInPassing[0.9]"
	),
	BWResCBExp = cms.vstring(
		"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
		#"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[0.8,0,10])",
		"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0.5,5], n[2.0,0.5,15])",
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
	VoigtPol2 = cms.vstring(
		"Voigtian::signal(mass, mean[91,75,105], width[3,0.01,15], sigma[3,0.01,15])", # mean 85-95, width, sigma 1-10
	        "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1], cPass3[0.,-1.1,1.1]})",
	        "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1], cFail3[0.,-1.1,1.1]})",
		"efficiency[0.9,0,1]",
		"signalFractionInPassing[0.9]",
	),
	BWResCBPol2 = cms.vstring(
	        "BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
	        "RooCBShape::res(mass, peak[0], sigma[1.7,1,10], alpha[1.8,1,3], n[0.8,0,10])",
	        "FCONV::signal(mass, bw, res)",
	        "Chebychev::backgroundPass(mass, {c1p[0,-10,10], c2p[0,-10,10]})",
	        "Chebychev::backgroundFail(mass, {c1f[0,-10,10], c2f[0,-10,10]})",
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
#        TM_nPVdep = cms.PSet(
#           EfficiencyCategoryAndState = cms.vstring("MuIDForOutsideInTk","pass"),
#            EfficiencyCategoryAndState = cms.vstring("Glb","true"),
#            EfficiencyCategoryAndState = cms.vstring("TM","true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                tag_nVertices = cms.vdouble(0, 1, 4),
#                pt = cms.vdouble(15, 80),
#                eta = cms.vdouble(-2.4, 2.4),
#            ),
#            BinToPDFmap = cms.vstring(PDFName)
#        ),

#        TM_HFdep = cms.PSet(
#            EfficiencyCategoryAndState = cms.vstring("TM","true"),
#            UnbinnedVariables = cms.vstring("mass"),
#            BinnedVariables = cms.PSet(
#                tag_hiHF = cms.vdouble(0, 50, 75, 95, 115, 150, 400),
#                pt = cms.vdouble(15, 80),
#                eta = cms.vdouble(-2.4, 2.4),
#            ),
#            BinToPDFmap = cms.vstring(PDFName)
#        ),
#
#        TM_nTracksdep = cms.PSet(
#            EfficiencyCategoryAndState = cms.vstring("TM","true"),
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
