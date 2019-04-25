import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/himc/pPb816Summer16DR/Psi1SToMuMu_pTMu-2p5_pPb-Bst_8p16-Pythia8/AODSIM/pPbBst_80X_mcRun2_pA_v4-v1/00000/20B400D8-181A-E711-A561-549F3525E81C.root')
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.GlobalTag.globaltag = cms.string('80X_mcRun2_pA_v4')

## ==== Filters ====
### pPb Event Selection
process.load('HeavyIonsAnalysis.Configuration.hfCoincFilter_cff')
process.primaryVertexFilterPA = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
    filter = cms.bool(True),
)
process.noScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False), ## Or 'True' to get some per-event info
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)
### Trigger selection
process.load("HLTrigger.HLTfilters.triggerResultsFilter_cfi")
process.triggerResultsFilter.triggerConditions = cms.vstring('HLT_PAL2Mu*_v*', 'HLT_PAL3Mu*_v*')
process.triggerResultsFilter.hltResults = cms.InputTag("TriggerResults","","HLT")
process.triggerResultsFilter.l1tResults = cms.InputTag("gtStage2Digis") #O: needs to be this
process.triggerResultsFilter.throw = False
### Filter sequence
process.fastFilter = cms.Sequence(process.hfCoincFilter + process.primaryVertexFilterPA + process.noScraping + process.triggerResultsFilter)

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
    muonsCut     = cms.string(InAcceptance + " && track.isNonnull"),
    caloMuonsCut = cms.string(InAcceptance),
    tracksCut    = cms.string(InAcceptance),
)

## ==== Trigger matching
process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")
from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import *
changeRecoMuonInput(process, "mergedMuons")
## with some customization
process.muonL1Info.maxDeltaR = 0.3
process.muonL1Info.maxDeltaEta = 0.2
process.muonL1Info.fallbackToME1 = True
process.muonMatchHLTL1.maxDeltaR = 0.3
process.muonMatchHLTL1.maxDeltaEta = 0.2
process.muonMatchHLTL1.fallbackToME1 = True
process.muonMatchHLTL2.maxDeltaR = 0.3
process.muonMatchHLTL2.maxDPtRel = 10.0
process.muonMatchHLTL3.maxDeltaR = 0.1
process.muonMatchHLTL3.maxDPtRel = 10.0
## For trigger muons
switchOffAmbiguityResolution(process) # Switch off ambiguity resolution: allow multiple reco muons to match to the same trigger muon
## For L1 muons
addHLTL1Passthrough(process)
useL1Stage2Candidates(process)
process.patTrigger.collections.remove("hltL1extraParticles")
process.patTrigger.collections.append("hltGmtStage2Digis:Muon")
process.muonMatchHLTL1.matchedCuts = cms.string('coll("hltGmtStage2Digis:Muon")')
process.muonMatchHLTL1.useStage2L1 = cms.bool(True)
process.muonMatchHLTL1.useMB2InOverlap = cms.bool(True)
process.muonMatchHLTL1.preselection = cms.string("")
appendL1MatchingAlgo(process)

## ==== Tag and probe variables
from MuonAnalysis.TagAndProbe.common_variables_cff import *
process.load("MuonAnalysis.TagAndProbe.common_modules_cff")
from MuonAnalysis.TagAndProbe.heavyIon_variables_cff import *
process.load("MuonAnalysis.TagAndProbe.heavyIon_modules_cff")
process.centralityInfo.CentralitySrc = cms.InputTag("pACentrality")
## Flags
### Muon Id
TightIdReco = "isGlobalMuon && isPFMuon && globalTrack.normalizedChi2 < 10 && globalTrack.hitPattern.numberOfValidMuonHits > 0 && numberOfMatchedStations > 1 && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0"
TightId = TightIdReco+" && abs(dB('PV2D')) < 0.2 && abs(dB('PVDZ')) < 0.5"
HybridSoftIdReco = "isTrackerMuon && isGlobalMuon && innerTrack.hitPattern.trackerLayersWithMeasurement > 5 && innerTrack.hitPattern.pixelLayersWithMeasurement > 0"
HybridSoftId = HybridSoftIdReco + " && muonID('TMOneStationTight') && abs(dB('PV2D')) < 0.3 && abs(dB('PVDZ')) < 20.0"
SoftId = "muonID('TMOneStationTight') && innerTrack.hitPattern.trackerLayersWithMeasurement > 5 && innerTrack.hitPattern.pixelLayersWithMeasurement > 0 && innerTrack.quality(\"highPurity\") && abs(dB('PV2D')) < 0.3 && abs(dB('PVDZ')) < 20.0"
### Tracking
track_cuts = "track.isNonnull && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.pixelLayersWithMeasurement > 0" #currently used only as a flag
### Trigger
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
   HLT_PAL3Mu3 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu3_v*',1,0).empty()"),
   HLT_PAL3Mu5 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu5_v*',1,0).empty()"),
   HLT_PAL3Mu7 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu7_v*',1,0).empty()"),
   HLT_PAL2Mu12 = cms.string("!triggerObjectMatchesByPath('HLT_PAL2Mu12_v*',1,0).empty()"),
   HLT_PAL3Mu12 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu12_v*',1,0).empty()"),
   HLT_PAL2Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_PAL2Mu15_v*',1,0).empty()"),
   HLT_PAL3Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_PAL3Mu15_v*',1,0).empty()"),
)

## ==== Tag muons
process.tagMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(InAcceptance+" && "+HybridSoftId+" && (!triggerObjectMatchesByPath('HLT_PAL2Mu*_v*',1,0).empty() || !triggerObjectMatchesByPath('HLT_PAL3Mu*_v*',1,0).empty())"),
)
process.oneTag = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tagMuons"), minNumber = cms.uint32(1))
process.pseudoTag = cms.EDFilter("MuonSelector",
    src = cms.InputTag("mergedMuons"),
    cut = cms.string(InAcceptance+" && "+HybridSoftIdReco),
)
process.onePseudoTag = process.oneTag.clone(src = cms.InputTag("pseudoTag"))

## ==== Probe muons
process.probeMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string('innerTrack.isNonnull'),
)
process.pseudoProbe = cms.EDFilter("MuonSelector",
    src = cms.InputTag("mergedMuons"),
    cut = cms.string('innerTrack.isNonnull'),
)

## ==== Tag and Probe muon pairs
process.tpPairs = cms.EDProducer("CandViewShallowCloneCombiner",
    cut = cms.string('2.0 < mass < 4.0'),
    decay = cms.string('tagMuons@+ probeMuons@-')
)
process.onePair = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairs"), minNumber = cms.uint32(1))

process.pseudoPairs = process.tpPairs.clone(decay = cms.string('pseudoTag@+ pseudoProbe@-'))
process.onePseudoPair = process.onePair.clone(src = cms.InputTag("pseudoPairs"))
process.twoMuons = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("mergedMuons"), minNumber = cms.uint32(2))
process.fastPseudoTnP = cms.Sequence(process.mergedMuons + process.twoMuons + process.pseudoTag + process.onePseudoTag + process.pseudoProbe + process.pseudoPairs + process.onePseudoPair)

## ==== Tag and Probe tree
process.tpTree = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tpPairs"),
    arbitration   = cms.string("None"),
    # probe variables: all useful ones
    variables = cms.PSet(
        KinematicVariables,
        MuonIDVariables,
        TrackQualityVariables,
        GlobalTrackQualityVariables,
        StaOnlyVariables,
        dxyPVdzmin = cms.InputTag("muonDxyPVdzmin","dxyPVdzmin"),
        dzPV = cms.InputTag("muonDxyPVdzmin","dzPV"),
        dxyPV = cms.InputTag("muonDxyPVdzmin","dxyPV"),
    ),
    flags = cms.PSet(
       TrackQualityFlags,
       MuonIDFlags,
       TrigProbeFlags,
       TightHINoDz = cms.string(TightId),
       HybridSoftHINoDxyz = cms.string(HybridSoftId),
       SoftHINoDxyz = cms.string(SoftId),
       InAcceptance = cms.string(InAcceptance),
       Custom_track_cuts = cms.string(track_cuts),
       StaTkSameCharge = cms.string("outerTrack.isNonnull && innerTrack.isNonnull && (outerTrack.charge == innerTrack.charge)"),
       outerValidHits = cms.string("outerTrack.isNonnull && outerTrack.numberOfValidHits > 0"),
       isMuonSeeded = cms.string("innerTrack.isNonnull && innerTrack.originalAlgo<13"), #   muonSeededStepInOut = 13,
    ),
    tagVariables = cms.PSet(
        KinematicVariables,
        MuonIDVariables,
        TrackQualityVariables,
        GlobalTrackQualityVariables,
        StaOnlyVariables,
        CentralityVariables,
        nVertices  = cms.InputTag("nverticesModule"),
        dxyPVdzmin = cms.InputTag("muonDxyPVdzMinTags","dxyPVdzmin"),
        dzPV = cms.InputTag("muonDxyPVdzMinTags","dzPV"),
        dxyPV = cms.InputTag("muonDxyPVdzminTags","dxyPV"),
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
    pairFlags = cms.PSet(),
    isMC           = cms.bool(False),
    addRunLumiInfo = cms.bool(True),
)

process.nverticesModule = cms.EDProducer("VertexMultiplicityCounter",
    probes = cms.InputTag("tagMuons"),
    objects = cms.InputTag("offlinePrimaryVertices"),
    objectSelection = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2")
)
process.probeMultiplicity = cms.EDProducer("ProbeMulteplicityProducer",
    pairs = cms.InputTag("tpPairs")
)
process.probeMultiplicityTMGM = process.probeMultiplicity.clone(
    probeCut = cms.string("isTrackerMuon || isGlobalMuon")
)
process.muonDxyPVdzmin = cms.EDProducer("MuonDxyPVdzmin",
    probes = cms.InputTag("probeMuons")
)
process.muonDxyPVdzminTags = process.muonDxyPVdzmin.clone(
    probes = cms.InputTag("tagMuons")
)

process.tnpSimpleSequence = cms.Sequence(
    process.tagMuons +
    process.oneTag     +
    process.probeMuons +
    process.tpPairs    +
    process.onePair    +
    process.nverticesModule +
    process.muonDxyPVdzmin + process.muonDxyPVdzminTags +
    process.probeMultiplicity + process.probeMultiplicityTMGM +
    process.centralityInfo +
    process.tpTree
)

process.tagAndProbe = cms.Path(
    process.fastFilter
    * process.fastPseudoTnP
    * process.mergedMuons * process.patMuonsWithTriggerSequence
    * process.tnpSimpleSequence
)

process.schedule = cms.Schedule(
   process.tagAndProbe
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("tnpJPsi_MC_pPb_AOD.root"))
