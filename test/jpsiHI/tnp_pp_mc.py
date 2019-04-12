import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/himc/RunIIpp5Spring18DR/JPsiMM_TuneCUETP8M1_5p02TeV_pythia8/AODSIM/94X_mc2017_realistic_forppRef5TeV-v2/60000/FC0EFD70-DC46-E911-BF6B-1418774117C7.root')
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.GlobalTag.globaltag = cms.string('94X_mc2017_realistic_forppRef5TeV_v1')

InAcceptance_2015       = '((abs(eta)<1.2 && pt>=3.5) || (1.2<=abs(eta) && abs(eta)<2.1 && pt>=5.77-1.89*abs(eta)) || (2.1<=abs(eta) && abs(eta)<2.4 && pt>=1.8))'
InAcceptance_2018_Tight = '((abs(eta)<1.2 && pt>=3.5) || (1.2<=abs(eta) && abs(eta)<2.1 && pt>=5.47-1.89*abs(eta)) || (2.1<=abs(eta) && abs(eta)<2.4 && pt>=1.5))'
InAcceptance_2018_Loose = '((abs(eta)<0.3 && pt>=3.4) || (0.3<=abs(eta) && abs(eta)<1.1 && pt>=3.3) || (1.1<=abs(eta) && abs(eta)<1.4 && pt>=7.7-4.0*abs(eta)) || (1.4<=abs(eta) && abs(eta)<1.55 && pt>=2.1) || (1.55<=abs(eta) && abs(eta)<2.2 && pt>=4.25-1.39*abs(eta)) || (2.2<=abs(eta) && abs(eta)<2.4 && pt>=1.2))'

## ==== FILTERS ====
### pp Event Selection
process.goodVertexFilter = cms.EDFilter("VertexSelector",
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
process.triggerResultsFilter.triggerConditions = cms.vstring( 'HLT_HIL2Mu*', 'HLT_HIL3Mu*', 'HLT_HIMu*' )
process.triggerResultsFilter.hltResults = cms.InputTag("TriggerResults","","HLT")
process.triggerResultsFilter.l1tResults = cms.InputTag("") # keep empty!
process.triggerResultsFilter.throw = False
### Filter sequence
process.fastFilter = cms.Sequence(process.triggerResultsFilter + process.goodVertexFilter + process.noScraping)

##    __  __
##   |  \/  |_   _  ___  _ __  ___
##   | |\/| | | | |/ _ \| '_ \/ __|
##   | |  | | |_| | (_) | | | \__ \
##   |_|  |_|\__,_|\___/|_| |_|___/
##
## ==== Merge CaloMuons and Tracks into the collection of reco::Muons  ====
from RecoMuon.MuonIdentification.calomuons_cfi import calomuons;
process.mergedMuons = cms.EDProducer("CaloMuonMerger",
    mergeTracks = cms.bool(True),
    mergeCaloMuons = cms.bool(False), # AOD
    muons     = cms.InputTag("muons"),
    caloMuons = cms.InputTag("calomuons"),
    tracks    = cms.InputTag("generalTracks"),
    minCaloCompatibility = calomuons.minCaloCompatibility,
    ## Apply some minimal pt cut
    muonsCut     = cms.string(InAcceptance_2018_Loose + " && track.isNonnull"),
    caloMuonsCut = cms.string(InAcceptance_2018_Loose),
    tracksCut    = cms.string(InAcceptance_2018_Loose),
)

## ==== Trigger matching
process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")
from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import *
changeRecoMuonInput(process, "mergedMuons")
process.patMuonsWithoutTrigger.muonSimInfo = cms.InputTag("")
## with some customization ## Probably the same than addHLTL1Passthrough(process)
process.muonL1Info.maxDeltaR = 0.3
process.muonL1Info.fallbackToME1 = True
process.muonMatchHLTL1.maxDeltaR = 0.3
process.muonMatchHLTL1.fallbackToME1 = True
process.muonMatchHLTL2.maxDeltaR = 0.3
process.muonMatchHLTL2.maxDPtRel = 10.0
process.muonMatchHLTL3.maxDeltaR = 0.1
process.muonMatchHLTL3.maxDPtRel = 10.0
## For trigger muons (NEED TO CHECK)
switchOffAmbiguityResolution(process)
## For L1 muons
addHLTL1Passthrough(process)
useL1Stage2Candidates(process) # Enable L1 stage2 setup
process.patTrigger.collections.remove("hltL1extraParticles")
process.patTrigger.collections.append("hltGtStage2Digis:Muon")
process.muonMatchHLTL1.matchedCuts = cms.string('coll("hltGtStage2Digis:Muon")')
process.muonMatchHLTL1.useStage2L1 = cms.bool(True)
process.muonMatchHLTL1.useMB2InOverlap = cms.bool(True)
process.muonMatchHLTL1.preselection = cms.string("")
appendL1MatchingAlgo(process)

## ==== Tag and probe variables
from MuonAnalysis.TagAndProbe.common_variables_cff import *
process.load("MuonAnalysis.TagAndProbe.common_modules_cff")
## Flags
### Muon Id
TightIdReco = "isGlobalMuon && isPFMuon && globalTrack.normalizedChi2 < 10 && globalTrack.hitPattern.numberOfValidMuonHits > 0 && numberOfMatchedStations > 1 && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0"
TightId = TightIdReco+" && abs(dB) < 0.2"
HybridSoftIdReco_2018 = "isGlobalMuon && innerTrack.hitPattern.trackerLayersWithMeasurement > 5 && innerTrack.hitPattern.pixelLayersWithMeasurement > 0"
HybridSoftId_2018 = HybridSoftIdReco_2018
HybridSoftIdReco_2015 = HybridSoftIdReco_2018
HybridSoftId_2015 = HybridSoftIdReco_2015 + " && isTrackerMuon && muonID('TMOneStationTight')"
SoftId = "muonID('TMOneStationTight') && innerTrack.hitPattern.trackerLayersWithMeasurement > 5 && innerTrack.hitPattern.pixelLayersWithMeasurement > 0 && innerTrack.quality(\"highPurity\")"
### Trigger
LowPtTriggerProbeFlags = cms.PSet(
    HLTL1_DoubleMuOpen_v0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL1DoubleMuOpen_v*',1,0).empty()"),
    HLTL1_DoubleMu0_v0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL1DoubleMu0_v*',1,0).empty()"),
    HLTL1_DoubleMu0_v2 = cms.string("(!triggerObjectMatchesByPath('HLT_HIL1DoubleMu0_v*',1,0).empty() && !triggerObjectMatchesByFilter('hltL1fL1sDoubleMu0L1Filtered0').empty())"),
    HLTL2_DoubleMu0_v0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2DoubleMu0_v*',1,0).empty()"),
    HLTL3_DoubleMu0_v0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3DoubleMu0_v*',1,0).empty()"),
)
LowPtTriggerTagFlags = cms.PSet(
    # Single Muon Trigger Paths
    HLT_HIL2Mu3_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ10_v*',1,0).empty()"),
    HLT_HIL3Mu3 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu3_v*',1,0).empty()"),
    HLT_HIL3Mu3_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ10_v*',1,0).empty()"),
    HLT_HIL2Mu5_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ10_v*',1,0).empty()"),
    HLT_HIL3Mu5 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu5_v*',1,0).empty()"),
    HLT_HIL3Mu5_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ10_v*',1,0).empty()"),
    HLT_HIL2Mu7 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu7_v*',1,0).empty()"),
    HLT_HIL3Mu7 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu7_v*',1,0).empty()"),
)
HighPtTriggerTagFlags = cms.PSet(
    # Single Muon Trigger Paths
    HLT_HIL2Mu12 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu12_v*',1,0).empty()"),
    HLT_HIL3Mu12 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu12_v*',1,0).empty()"),
    HLT_HIL2Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu15_v*',1,0).empty()"),
    HLT_HIL3Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu15_v*',1,0).empty()"),
    HLT_HIMu15 = cms.string("!triggerObjectMatchesByPath('HLT_HIMu15_v*',1,0).empty()"),
    HLT_HIMu17 = cms.string("!triggerObjectMatchesByPath('HLT_HIMu17_v*',1,0).empty()"),
    HLT_HIL2Mu20 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu20_v*',1,0).empty()"),
    HLT_HIL3Mu20 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu20_v*',1,0).empty()"),
)
### Tracking
TRACK_CUTS = "track.isNonnull && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.pixelLayersWithMeasurement > 0"

## ==== Tag muons
process.tagMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(InAcceptance_2015+" && "+HybridSoftId_2015+" && ("
                     +    "!triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ10_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu3_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ10_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ10_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu5_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ10_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu7_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu7_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu12_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu12_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu15_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu15_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIMu15_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIMu17_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu20_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu20_v*',1,0).empty())"),
)
process.oneTag = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tagMuons"), minNumber = cms.uint32(1))
process.pseudoTag = cms.EDFilter("MuonSelector",
    src = cms.InputTag("mergedMuons"),
    cut = cms.string(InAcceptance_2015+" && "+HybridSoftIdReco_2015),
)
process.onePseudoTag = process.oneTag.clone(src = cms.InputTag("pseudoTag"))

## ==== Probe muons
process.probeMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string("isTrackerMuon || isGlobalMuon || isPFMuon"),
)
process.pseudoProbe = cms.EDFilter("MuonSelector",
    src = cms.InputTag("mergedMuons"),
    cut = cms.string("isTrackerMuon || isGlobalMuon || isPFMuon"),
)

## ==== Tag and Probe muon pairs
process.tpPairs = cms.EDProducer("CandViewShallowCloneCombiner",
    cut = cms.string('2.5 < mass < 3.5'),
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
        #dxyBS = cms.InputTag("muonDxyPVdzmin","dxyBS"),
        dxyPVdzmin = cms.InputTag("muonDxyPVdzmin","dxyPVdzmin"),
        dzPV = cms.InputTag("muonDxyPVdzmin","dzPV"),
        dxyPV = cms.InputTag("muonDxyPVdzmin","dxyPV"),
    ),
    flags = cms.PSet(
        TrackQualityFlags,
        MuonIDFlags,
        LowPtTriggerProbeFlags,
        InAcceptance_2015 = cms.string(InAcceptance_2015),
        InAcceptance_2018_Loose = cms.string(InAcceptance_2018_Loose),
        InAcceptance_2018_Tight = cms.string(InAcceptance_2018_Tight),
        TightId = cms.string(TightIdReco),
        HybridSoftId_2015 = cms.string(HybridSoftId_2015),
        HybridSoftId_2018 = cms.string(HybridSoftId_2018),
        SoftIdWithoutDxyz = cms.string(SoftId),
        #dxyzPVCuts = cms.InputTag("muonDxyPVdzmin","dxyzPVCuts"),
    ),
    tagVariables = cms.PSet(
        KinematicVariables,
        MuonIDVariables,
        TrackQualityVariables,
        GlobalTrackQualityVariables,
        nVertices = cms.InputTag("nverticesModule"),
        #dxyBS = cms.InputTag("muonDxyPVdzminTags","dxyBS"),
        dxyPVdzmin = cms.InputTag("muonDxyPVdzminTags","dxyPVdzmin"),
        dzPV = cms.InputTag("muonDxyPVdzminTags","dzPV"),
        dxyPV = cms.InputTag("muonDxyPVdzminTags","dxyPV"),
    ),
    tagFlags = cms.PSet(
        LowPtTriggerTagFlags,
        HighPtTriggerTagFlags,
    ),
    pairVariables = cms.PSet(
        dz = cms.string("daughter(0).vz - daughter(1).vz"),
        pt = cms.string("pt"),
        rapidity = cms.string("rapidity"),
        deltaR = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
        probeMultiplicity = cms.InputTag("probeMultiplicity"),
        probeMultiplicity_TMGM = cms.InputTag("probeMultiplicityTMGM"),
        genWeight = cms.InputTag("genWeightInfo", "genWeight"),
        truePileUp   = cms.InputTag("genWeightInfo", "truePileUp"),
        actualPileUp = cms.InputTag("genWeightInfo", "actualPileUp"),
    ),
    pairFlags = cms.PSet(
        BestJPsi = cms.InputTag("bestPairByJpsiMass"),
    ),
    isMC = cms.bool(False),
    addRunLumiInfo = cms.bool(True),
)

process.nverticesModule = cms.EDProducer("VertexMultiplicityCounter",
    probes = cms.InputTag("tagMuons"),
    objects = cms.InputTag("offlinePrimaryVertices"),
    objectSelection = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2")
)
process.bestPairByJpsiMass = cms.EDProducer("BestPairByMass",
    pairs = cms.InputTag("tpPairs"),
    mass  = cms.double(3.096916)
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
process.genWeightInfo = process.genAdditionalInfo.clone(
    pairTag = cms.InputTag("tpPairs")
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
    process.bestPairByJpsiMass +
    process.genWeightInfo +
    process.tpTree
)

process.tagAndProbe = cms.Path(
    process.fastFilter
    * process.fastPseudoTnP ##includes mergedMuons
    * process.patMuonsWithTriggerSequence
    * process.tnpSimpleSequence
)


##    _____               _    _
##   |_   _| __ __ _  ___| | _(_)_ __   __ _
##     | || '__/ _` |/ __| |/ / | '_ \ / _` |
##     | || | | (_| | (__|   <| | | | | (_| |
##     |_||_|  \__,_|\___|_|\_\_|_| |_|\__, |
##                                     |___/

## Then make another collection for standalone muons, using standalone track to define the 4-momentum
process.muonsSta = cms.EDProducer("RedefineMuonP4FromTrack",
    src   = cms.InputTag("muons"),
    track = cms.string("outer"),
)
## Match to trigger, to measure the efficiency of HLT tracking
from PhysicsTools.PatAlgos.tools.helpers import *
process.patMuonsWithTriggerSequenceSta = cloneProcessingSnippet(process, process.patMuonsWithTriggerSequence, "Sta")
process.patMuonsWithTriggerSequenceSta.replace(process.patTriggerFullSta, process.patTriggerFull)
process.patTriggerSta.src = cms.InputTag("patTriggerFull")
process.muonMatchHLTL2Sta.maxDeltaR = 0.5
process.muonMatchHLTL3Sta.maxDeltaR = 0.5
massSearchReplaceAnyInputTag(process.patMuonsWithTriggerSequenceSta, "mergedMuons", "muonsSta")

## Define probes and T&P pairs
process.probeMuonsSta = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTriggerSta"),
    cut = cms.string("outerTrack.isNonnull"), # no real cut now
)
process.pseudoProbeSta = cms.EDFilter("MuonSelector",
    src = cms.InputTag("muonsSta"),
    cut = cms.string("outerTrack.isNonnull"),
)

process.tpPairsSta = process.tpPairs.clone(decay = cms.string('tagMuons@+ probeMuonsSta@-'), cut = cms.string('2. < mass < 5.'))

process.onePairSta = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairsSta"), minNumber = cms.uint32(1))

process.pseudoPairsSta = process.tpPairsSta.clone(decay = cms.string('pseudoTag@+ pseudoProbeSta@-'))
process.onePseudoPairSta = process.onePairSta.clone(src = cms.InputTag("pseudoPairsSta"))
process.fastPseudoTnPSta = cms.Sequence(process.mergedMuons + process.pseudoTag + process.onePseudoTag + process.muonsSta + process.pseudoProbeSta + process.pseudoPairsSta + process.onePseudoPairSta)

process.staToTkMatch.maxDeltaR = 0.3
process.staToTkMatch.maxDeltaPtRel = 2.
process.staToTkMatchNoZ.maxDeltaR = 0.3
process.staToTkMatchNoZ.maxDeltaPtRel = 2.

process.load("MuonAnalysis.TagAndProbe.tracking_reco_info_cff")

process.tpTreeSta = process.tpTree.clone(
    tagProbePairs = "tpPairsSta",
    arbitration   = "OneProbe",
    variables = cms.PSet(
        KinematicVariables,
        StaOnlyVariables,
        ## track matching variables
        tk_deltaR = cms.InputTag("staToTkMatch","deltaR"),
        tk_deltaEta = cms.InputTag("staToTkMatch","deltaEta"),
        tk_deltaR_NoJPsi = cms.InputTag("staToTkMatchNoJPsi","deltaR"),
        tk_deltaEta_NoJPsi = cms.InputTag("staToTkMatchNoJPsi","deltaEta"),
        tk_deltaR_NoBestJPsi = cms.InputTag("staToTkMatchNoBestJPsi","deltaR"),
        tk_deltaEta_NoBestJPsi = cms.InputTag("staToTkMatchNoBestJPsi","deltaEta"),
    ),
    flags = cms.PSet(
        outerValidHits = cms.string("outerTrack.numberOfValidHits > 0"),
        TM  = cms.string("isTrackerMuon"),
        Glb = cms.string("isGlobalMuon"),
        PF  = cms.string("isPFMuon"),
        tk  = cms.string("track.isNonnull"),
        InAcceptance_2015 = cms.string(InAcceptance_2015),
        InAcceptance_2018_Loose = cms.string(InAcceptance_2018_Loose),
        InAcceptance_2018_Tight = cms.string(InAcceptance_2018_Tight),
        isNonMuonSeeded = cms.string("innerTrack.isNonnull && innerTrack.originalAlgo<13"),
        StaTkSameCharge = cms.string("outerTrack.isNonnull && innerTrack.isNonnull && (outerTrack.charge == innerTrack.charge)"),
    ),
    tagVariables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        phi = cms.string("phi"),
        nVertices = cms.InputTag("nverticesModule"),
    ),
    tagFlags = cms.PSet(
        LowPtTriggerTagFlags,
        HighPtTriggerTagFlags,
    ),
    pairVariables = cms.PSet(
        dz = cms.string("daughter(0).vz - daughter(1).vz"),
        pt = cms.string("pt"),
        rapidity = cms.string("rapidity"),
        deltaR = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
        genWeight = cms.InputTag("genWeightInfoSta", "genWeight"),
        truePileUp   = cms.InputTag("genWeightInfoSta", "truePileUp"),
        actualPileUp = cms.InputTag("genWeightInfoSta", "actualPileUp"),
    ),
    pairFlags = cms.PSet(),
)

process.genWeightInfoSta = process.genAdditionalInfo.clone(
    pairTag = cms.InputTag("tpPairsSta")
)

process.tnpSimpleSequenceSta = cms.Sequence(
    process.tagMuons +
    process.oneTag     +
    process.probeMuonsSta   +
    process.tpPairsSta      +
    process.onePairSta      +
    process.nverticesModule +
    process.staToTkMatchSequenceJPsi +
    process.genWeightInfoSta +
    process.tpTreeSta
)

process.RandomNumberGeneratorService.tkTracksNoJPsi      = cms.PSet( initialSeed = cms.untracked.uint32(81) )
process.RandomNumberGeneratorService.tkTracksNoBestJPsi  = cms.PSet( initialSeed = cms.untracked.uint32(81) )

process.tagAndProbeSta = cms.Path(
    process.fastFilter
    * process.fastPseudoTnPSta ##includes mergedMuons
    * process.patMuonsWithTriggerSequence
    * process.muonsSta * process.patMuonsWithTriggerSequenceSta
    * process.tnpSimpleSequenceSta
)

#--------------------------------------------------------------------
##    ____                   _____               _      ____            _
##   | __ )  __ _ _ __ ___  |_   _| __ __ _  ___| | __ |  _ \ _ __ ___ | |__   ___  ___
##   |  _ \ / _` | '__/ _ \   | || '__/ _` |/ __| |/ / | |_) | '__/ _ \| '_ \ / _ \/ __|
##   | |_) | (_| | | |  __/   | || | | (_| | (__|   <  |  __/| | | (_) | |_) |  __/\__ \
##   |____/ \__,_|_|  \___|   |_||_|  \__,_|\___|_|\_\ |_|   |_|  \___/|_.__/ \___||___/
##
##

process.probeMuonsTrk = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(TRACK_CUTS + ' && ' + InAcceptance_2018_Loose + ' &&' + 'innerTrack.isNonnull && innerTrack.originalAlgo<13'), #   muonSeededStepInOut = 13
)
process.pseudoProbeTrk = cms.EDFilter("MuonSelector",
    src = cms.InputTag("mergedMuons"),
    cut = cms.string(TRACK_CUTS + ' && ' + InAcceptance_2018_Loose + ' &&' + 'innerTrack.isNonnull && innerTrack.originalAlgo<13'), #   muonSeededStepInOut = 13
)

process.tpPairsTrk = cms.EDProducer("CandViewShallowCloneCombiner",
    cut = cms.string('2.5 < mass < 3.5'),
    decay = cms.string('tagMuons@+ probeMuonsTrk@-')
)

process.onePairTrk = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("tpPairsTrk"),
    minNumber = cms.uint32(1),
)

process.pseudoPairsTrk = process.tpPairsTrk.clone(decay = cms.string('pseudoTag@+ pseudoProbeTrk@-'))
process.onePseudoPairTrk = process.onePairTrk.clone(src = cms.InputTag("pseudoPairsTrk"))
process.fastPseudoTnPTrk = cms.Sequence(process.mergedMuons + process.twoMuons + process.pseudoTag + process.onePseudoTag + process.pseudoProbeTrk + process.pseudoPairsTrk + process.onePseudoPairTrk)

process.tpTreeTrk = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tpPairsTrk"),
    arbitration   = cms.string("OneProbe"),
    # probe variables: all useful ones
    variables = cms.PSet(
      KinematicVariables,
      StaOnlyVariables,
      #dxyBS = cms.InputTag("muonDxyPVdzminTrk","dxyBS"),
      dxyPVdzmin = cms.InputTag("muonDxyPVdzminTrk","dxyPVdzmin"),
      dzPV = cms.InputTag("muonDxyPVdzminTrk","dzPV"),
      dxyPV = cms.InputTag("muonDxyPVdzminTrk","dxyPV"),
    ),
    flags = cms.PSet(
      isSTA = cms.string("isStandAloneMuon"),
      TM    = cms.string("isTrackerMuon"),
      Glb   = cms.string("isGlobalMuon"),
      outerValidHits = cms.string("? outerTrack.isNull() ? 0 : outerTrack.numberOfValidHits > 0"),
      InAcceptance_2015 = cms.string(InAcceptance_2015),
      InAcceptance_2018_Loose = cms.string(InAcceptance_2018_Loose),
      InAcceptance_2018_Tight = cms.string(InAcceptance_2018_Tight),
      #dxyzPVCuts = cms.InputTag("muonDxyPVdzminTrk","dxyzPVCuts"),
    ),
    tagVariables = cms.PSet(
      TrackQualityVariables,
      GlobalTrackQualityVariables,
      pt  = cms.string("pt"),
      eta = cms.string("eta"),
      abseta = cms.string("abs(eta)"),
      phi = cms.string("phi"),
      nVertices = cms.InputTag("nverticesModule"),
      l2dr = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() ? 999 : "+
        " deltaR( eta, phi, " +
        "         triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).eta, "+
        "         triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).phi ) "),

    ),
    tagFlags = cms.PSet(
       LowPtTriggerTagFlags,
       HighPtTriggerTagFlags
    ),
    pairVariables = cms.PSet(
      pt = cms.string("pt"),
      y = cms.string("rapidity"),
      absy = cms.string("abs(rapidity)"),
      deltaR = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
      genWeight = cms.InputTag("genWeightInfoTrk", "genWeight"),
        truePileUp   = cms.InputTag("genWeightInfoTrk", "truePileUp"),
        actualPileUp = cms.InputTag("genWeightInfoTrk", "actualPileUp"),
    ),
    pairFlags = cms.PSet(),
    isMC = cms.bool(False)
)

process.muonDxyPVdzminTrk = process.muonDxyPVdzmin.clone(
    probes = cms.InputTag("probeMuonsTrk")
)
process.genWeightInfoTrk = process.genAdditionalInfo.clone(
    pairTag = cms.InputTag("tpPairsTrk")
)

process.tnpSimpleSequenceTrk = cms.Sequence(
    process.tagMuons +
    process.oneTag +
    process.probeMuonsTrk +
    process.muonDxyPVdzminTrk +
    process.tpPairsTrk +
    process.onePairTrk +
    process.nverticesModule +
    process.genWeightInfoTrk +
    process.tpTreeTrk
)

process.tagAndProbeTrk = cms.Path(
    process.fastFilter
    * process.fastPseudoTnPTrk ##includes mergedMuons
    * process.patMuonsWithTriggerSequence
    * process.tnpSimpleSequenceTrk
)

process.schedule = cms.Schedule(
   process.tagAndProbe,
   process.tagAndProbeSta,
   process.tagAndProbeTrk,
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("tnpJpsi_MC_pp5TeV.root"))
