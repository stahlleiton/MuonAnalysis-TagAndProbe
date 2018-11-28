import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
    #fileNames =  cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/himc/pPb816Summer16DR/Psi1SToMuMu_pTMu-2p5_pPb-Bst_8p16-Pythia8/AODSIM/pPbBst_80X_mcRun2_pA_v4-v1/00000/20B400D8-181A-E711-A561-549F3525E81C.root'),
    fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/o/okukral20B400D8-181A-E711-A561-549F3525E81C.root'),
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )    

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.ReconstructionHeavyIons_cff")

process.GlobalTag.globaltag = cms.string('80X_mcRun2_pA_v4')

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")

CentralityVariablesNoHiBin = cms.PSet(
	hiBin	= cms.InputTag("centralityBinInfo"),
	hiHF	= cms.InputTag("centralityInfo","HFtowers"),
	hiHFplus	= cms.InputTag("centralityInfo","HFtowersPlus"),
	hiHFminus	= cms.InputTag("centralityInfo","HFtowersMinus"),
	hiHFeta4	= cms.InputTag("centralityInfo","HFtowersTrunc"),
	hiHFplusEta4	= cms.InputTag("centralityInfo","HFtowersPlusTrunc"),
	hiHFminusEta4	= cms.InputTag("centralityInfo","HFtowersMinusTrunc"),
	hiHFhit	= cms.InputTag("centralityInfo","HFhits"),
	hiNpix	= cms.InputTag("centralityInfo","PixelHits"),
	hiNpixelTracks	= cms.InputTag("centralityInfo","PixelTracks"),
	hiNtracks	= cms.InputTag("centralityInfo","Tracks"),
	hiEB	= cms.InputTag("centralityInfo","EB"),
	hiEE	= cms.InputTag("centralityInfo","EE"),
	hiET	= cms.InputTag("centralityInfo","ET"),
)

## ==== Filters ====
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
#process.load('HeavyIonsAnalysis.EventAnalysis.HIClusterCompatibilityFilter_cfi')
#process.clusterCompatibilityFilter.clusterPars = cms.vdouble(0.0,0.006)

## ==== Fast Filters ====
#process.fastFilter = cms.Sequence(process.hfCoincFilter3 * process.primaryVertexFilter * process.clusterCompatibilityFilter)
process.goodVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && ndof > 4 && abs(z) <= 25 && position.Rho <= 2"),
    filter = cms.bool(True),
)
process.noScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False), ## Or 'True' to get some per-event info
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)

process.load("HLTrigger.HLTfilters.triggerResultsFilter_cfi")

process.triggerResultsFilter.triggerConditions = cms.vstring( 'HLT_PAL1DoubleMuOpen_v*', 'HLT_PAL2DoubleMu0_v*', 'HLT_PAL3DoubleMu0_v*', 'HLT_PAL3DoubleMu0_HIon_v*', 'HLT_PAL1DoubleMu0_v*', 'HLT_PAL1DoubleMu0_HighQ_v*', 'HLT_PAL1DoubleMu0_MGT1_v*', 'HLT_PAL1DoubleMuOpen_OS_v*', 'HLT_PAL1DoubleMuOpen_SS_v*', 'HLT_PAL1DoubleMu10_v*', 'HLT_PAL2DoubleMu10_v*', 'HLT_PAL3DoubleMu10_v*', 'HLT_PAL3Mu3_v*', 'HLT_PAL3Mu5_v*', 'HLT_PAL3Mu7_v*', 'HLT_PAL2Mu12_v*', 'HLT_PAL3Mu12_v*', 'HLT_PAL2Mu15_v*', 'HLT_PAL3Mu15_v*', 'HLT_PAL1*', 'HLT_PAL2*',)

process.triggerResultsFilter.l1tResults = "gtStage2Digis" #O: needs to be this
#process.triggerResultsFilter.l1tResults = "gtDigis"
process.triggerResultsFilter.throw = False
process.triggerResultsFilter.hltResults = cms.InputTag("TriggerResults","","HLT")


#process.fastFilter     = cms.Sequence(process.collisionEventSelectionPA + process.triggerResultsFilter)
process.fastFilter     = cms.Sequence(process.triggerResultsFilter + process.goodVertexFilter)

##    __  __                       
##   |  \/  |_   _  ___  _ __  ___ 
##   | |\/| | | | |/ _ \| '_ \/ __|
##   | |  | | |_| | (_) | | | \__ \
##   |_|  |_|\__,_|\___/|_| |_|___/
##                                 
## ==== Merge CaloMuons and Tracks into the collection of reco::Muons  ====

InAcceptance = '((abs(eta)<1.2 && pt>=3.5) || (1.2<=abs(eta) && abs(eta)<2.1 && pt>=5.77-1.89*abs(eta)) || (2.1<=abs(eta) && abs(eta)<2.4 && pt>=1.8))'

from RecoMuon.MuonIdentification.calomuons_cfi import calomuons;
process.mergedMuons = cms.EDProducer("CaloMuonMerger",
    mergeTracks = cms.bool(True),
    mergeCaloMuons = cms.bool(False), # AOD
    muons     = cms.InputTag("muons"), 
    caloMuons = cms.InputTag("calomuons"),
    tracks    = cms.InputTag("generalTracks"),
    minCaloCompatibility = calomuons.minCaloCompatibility,
    ## Apply some minimal pt cut
    muonsCut     = cms.string(InAcceptance),
    caloMuonsCut = cms.string(InAcceptance),
    tracksCut    = cms.string(InAcceptance),
)

## ==== Trigger matching
process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")

from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import *
changeRecoMuonInput(process, "mergedMuons")
switchOffAmbiguityResolution(process) # Switch off ambiguity resolution: allow multiple reco muons to match to the same trigger muon
useL1Stage2Candidates(process)
appendL1MatchingAlgo(process)
addHLTL1Passthrough(process)

process.patMuonsWithoutTrigger.pvSrc = "offlinePrimaryVertices"
#process.patTriggerFull.l1GtReadoutRecordInputTag = cms.InputTag("gmtStage2Digis","Muon","RECO")       
process.patTriggerFull.l1GtReadoutRecordInputTag = cms.InputTag("gtDigis","","RECO")           #O: Settings doesn't seem to do anything      
process.patTrigger.collections.append("hltGmtStage2Digis:Muon")
process.muonMatchHLTL1.matchedCuts = cms.string('coll("hltGmtStage2Digis:Muon")')


from MuonAnalysis.TagAndProbe.common_variables_cff import *
process.load("MuonAnalysis.TagAndProbe.common_modules_cff")
from MuonAnalysis.TagAndProbe.heavyIon_variables_cff import *
process.load("MuonAnalysis.TagAndProbe.heavyIon_modules_cff")

process.centralityInfo.CentralitySrc = cms.InputTag("pACentrality")

TightId =  "isGlobalMuon && globalTrack.normalizedChi2 < 10 && globalTrack.hitPattern.numberOfValidMuonHits > 0 && numberOfMatchedStations > 1 && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0 && abs(dB) < 0.2"

HybridSoftId = "isTrackerMuon && isGlobalMuon && muonID('TMOneStationTight') && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0"

SoftId = "muonID('TMOneStationTight') && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.pixelLayersWithMeasurement > 0  && track.quality(\"highPurity\") && abs(track.dxy) < 0.3 && abs(track.dz)<20.0"

track_cuts = "track.isNonnull && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0" #currently used only as a flag


TrigProbeFlags = cms.PSet( 
     HLT_PAL1DoubleMuOpen = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMuOpen_v*',1,0).empty()"),
     HLT_PAL2DoubleMu0 = cms.string("!triggerObjectMatchesByPath('HLT_PAL2DoubleMu0_v*',1,0).empty()"),
     HLT_PAL3DoubleMu0 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3DoubleMu0_v*',1,0).empty()"),
     HLT_PAL3DoubleMu0_HIon = cms.string("!triggerObjectMatchesByPath('HLT_PAL3DoubleMu0_HIon_v*',1,0).empty()"),
     HLT_PAL1DoubleMu0 = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMu0_v*',1,0).empty()"),
     HLT_PAL1DoubleMu0_HighQ = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMu0_HighQ_v*',1,0).empty()"),
     HLT_PAL1DoubleMu0_MGT1 = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMu0_MGT1_v*',1,0).empty()"),
     HLT_PAL1DoubleMuOpen_OS = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMuOpen_OS_v*',1,0).empty()"),
     HLT_PAL1DoubleMuOpen_SS = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMuOpen_SS_v*',1,0).empty()"),
     HLT_PAL1DoubleMu10 = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMu10_v*',1,0).empty()"),
     HLT_PAL2DoubleMu10 = cms.string("!triggerObjectMatchesByPath('HLT_PAL2DoubleMu10_v*',1,0).empty()"),
     HLT_PAL3DoubleMu10 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3DoubleMu10_v*',1,0).empty()"),
     HLT_PAL3Mu3 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu3_v*',1,0).empty()"),
     HLT_PAL3Mu5 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu5_v*',1,0).empty()"),
     HLT_PAL3Mu7 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu7_v*',1,0).empty()"),
     HLT_PAL2Mu12 = cms.string("!triggerObjectMatchesByPath('HLT_PAL2Mu12_v*',1,0).empty()"),
     HLT_PAL3Mu12 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu12_v*',1,0).empty()"),
     HLT_PAL2Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_PAL2Mu15_v*',1,0).empty()"),
     HLT_PAL3Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu15_v*',1,0).empty()"),
     L1Seed = cms.string("!triggerObjectMatchesByCollection('hltL1extraParticles').empty() && triggerObjectMatchesByCollection('hltL1extraParticles').at(0).hasFilterLabel('hltL1sL1DoubleMu0BptxAND')"),
     L1Filter = cms.string("!triggerObjectMatchesByCollection('hltL1extraParticles').empty() && triggerObjectMatchesByCollection('hltL1extraParticles').at(0).hasFilterLabel('hltL1sL1DoubleMu0BptxAND') && abs(triggerObjectMatchesByCollection('hltL1extraParticles').at(0).eta)<2.5"),
     HLT_PAL1 = cms.string("!triggerObjectMatchesByPath('HLT_PAL1*',1,0).empty()"),
     HLT_PAL2 = cms.string("!triggerObjectMatchesByPath('HLT_PAL2*',1,0).empty()"),
     HLT_PAL2Mu12filt = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sSingleMu7BptxANDL1f0L2Filtered12').empty()"),
     HLT_PAL1DoubleMuOpenfilt = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sDoubleMuOpenBptxANDL1Filtered0').empty()"),
      )


TrigTagFlags = cms.PSet(
   HLT_PAL1DoubleMuOpen = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMuOpen_v*',1,0).empty()"),
   HLT_PAL2DoubleMu0 = cms.string("!triggerObjectMatchesByPath('HLT_PAL2DoubleMu0_v*',1,0).empty()"),
   HLT_PAL3DoubleMu0 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3DoubleMu0_v*',1,0).empty()"),
   HLT_PAL3DoubleMu0_HIon = cms.string("!triggerObjectMatchesByPath('HLT_PAL3DoubleMu0_HIon_v*',1,0).empty()"),
   HLT_PAL1DoubleMu0 = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMu0_v*',1,0).empty()"),
   HLT_PAL1DoubleMu0_HighQ = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMu0_HighQ_v*',1,0).empty()"),
   HLT_PAL1DoubleMu0_MGT1 = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMu0_MGT1_v*',1,0).empty()"),
   HLT_PAL1DoubleMuOpen_OS = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMuOpen_OS_v*',1,0).empty()"),
   HLT_PAL1DoubleMuOpen_SS = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMuOpen_SS_v*',1,0).empty()"),
   HLT_PAL1DoubleMu10 = cms.string("!triggerObjectMatchesByPath('HLT_PAL1DoubleMu10_v*',1,0).empty()"),
   HLT_PAL2DoubleMu10 = cms.string("!triggerObjectMatchesByPath('HLT_PAL2DoubleMu10_v*',1,0).empty()"),
   HLT_PAL3DoubleMu10 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3DoubleMu10_v*',1,0).empty()"),
   HLT_PAL3Mu3 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu3_v*',1,0).empty()"),
   HLT_PAL3Mu5 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu5_v*',1,0).empty()"),
   HLT_PAL3Mu7 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu7_v*',1,0).empty()"),
   HLT_PAL2Mu12 = cms.string("!triggerObjectMatchesByPath('HLT_PAL2Mu12_v*',1,0).empty()"),
   HLT_PAL3Mu12 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu12_v*',1,0).empty()"),
   HLT_PAL2Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_PAL2Mu15_v*',1,0).empty()"),
   HLT_PAL3Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu15_v*',1,0).empty()"),
)

process.tagMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(InAcceptance + ' && ' + HybridSoftId 
       + " && (!triggerObjectMatchesByPath('HLT_PAL3Mu3_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_PAL3Mu5_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_PAL3Mu7_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_PAL2Mu12_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_PAL3Mu12_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_PAL2Mu15_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_PAL3Mu15_v*',1,0).empty())"
   ),
)

process.oneTag  = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tagMuons"), minNumber = cms.uint32(1))

process.probeMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string("innerTrack.isNonnull"),
)

process.muonDxyPVdzMinID = cms.EDProducer("MuonDxyPVdzmin",
    probes = cms.InputTag("probeMuons"),
    vertexes = cms.InputTag("hiSelectedVertex"),
)
process.muonDxyPVdzMinTags = cms.EDProducer("MuonDxyPVdzmin",
    probes = cms.InputTag("tagMuons"),
    vertexes = cms.InputTag("hiSelectedVertex"),
)

process.tpPairs = cms.EDProducer("CandViewShallowCloneCombiner",
    cut = cms.string('2.0 < mass < 4.0'),
    decay = cms.string('tagMuons@+ probeMuons@-')
)

process.onePair = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairs"), minNumber = cms.uint32(1))

from MuonAnalysis.TagAndProbe.heavyIon_variables_cff import *

process.tpTree = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tpPairs"),
    arbitration   = cms.string("None"),
    # probe variables: all useful ones
    variables = cms.PSet(
        #AllVariables,
        KinematicVariables,
	    MuonIDVariables,
	    TrackQualityVariables,
	    GlobalTrackQualityVariables,
	    StaOnlyVariables,
        dxyBS = cms.InputTag("muonDxyPVdzmin","dxyBS"),
        dxyPVdzmin = cms.InputTag("muonDxyPVdzMinID","dxyPVdzmin"),
        dzPV       = cms.InputTag("muonDxyPVdzMinID","dzPV"),
        nSplitTk  = cms.InputTag("splitTrackTagger"),
    ),
    flags = cms.PSet(
       TrackQualityFlags,
       MuonIDFlags,
       TrigProbeFlags,
       TightHI = cms.string(TightId),
       HybridSoftHI = cms.string(HybridSoftId),
       SoftHI = cms.string(SoftId),
       InAcceptance = cms.string(InAcceptance),
       Custom_track_cuts = cms.string(track_cuts),
       StaTkSameCharge = cms.string("outerTrack.isNonnull && innerTrack.isNonnull && (outerTrack.charge == innerTrack.charge)"),
       outerValidHits = cms.string("outerTrack.isNonnull && outerTrack.numberOfValidHits > 0"),
    ),
    tagVariables = cms.PSet(
        #L1Variables,
        #L1SeedVariables,
        KinematicVariables,
	    MuonIDVariables,
	    TrackQualityVariables,
	    GlobalTrackQualityVariables,
	    StaOnlyVariables,
        CentralityVariablesNoHiBin,
        nVertices   = cms.InputTag("nverticesModule"),
        dxyPVdzmin = cms.InputTag("muonDxyPVdzMinTags","dxyPVdzmin"),
        dzPV = cms.InputTag("muonDxyPVdzMinTags","dzPV"),
    ),
    tagFlags = cms.PSet(
        TrigTagFlags  
    ),
    pairVariables = cms.PSet(
        dz      = cms.string("daughter(0).vz - daughter(1).vz"),
        pt      = cms.string("pt"), 
        rapidity = cms.string("rapidity"),
        deltaR   = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
        probeMultiplicity = cms.InputTag("probeMultiplicity"),
        probeMultiplicity_TMGM = cms.InputTag("probeMultiplicityTMGM"),
    ),
    pairFlags = cms.PSet(
        #BestJPsi = cms.InputTag("bestPairByJpsiMass"),
    ),
    isMC           = cms.bool(False),
    addRunLumiInfo = cms.bool(True),
    allProbes      = cms.InputTag("probeMuons")
)

process.extraProbeVariablesSeq = cms.Sequence(
    process.splitTrackTagger +
    process.muonDxyPVdzmin
)

process.tnpSimpleSequence = cms.Sequence(
    process.tagMuons +
    process.oneTag     +
    process.probeMuons +
    process.muonDxyPVdzMinID +
    process.muonDxyPVdzMinTags +
    process.tpPairs    +
    process.onePair    +
    process.nverticesModule +
    process.extraProbeVariablesSeq +
    process.probeMultiplicities + 
    #process.bestPairByJpsiMass + 
    process.centralityInfo +
    #process.centralityBinInfo +
    process.tpTree
)

process.tagAndProbe = cms.Path( 
    process.fastFilter *
    # process.centralityBin
     process.mergedMuons
    * process.patMuonsWithTriggerSequence
    * process.tnpSimpleSequence
)

process.schedule = cms.Schedule(
   process.tagAndProbe, 
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("tnpJPsi_MC_pPb_AOD.root"))
