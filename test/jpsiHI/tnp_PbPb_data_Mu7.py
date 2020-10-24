import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/hidata/HIRun2018A/HISingleMuon/AOD/04Apr2019-v1/270003/21A8A05E-B3C5-4445-A76E-1433602ED7FF.root'),
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.GlobalTag.globaltag = cms.string('103X_dataRun2_Prompt_fixEcalADCToGeV_v2')

## PbPb centrality bin producer
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("HeavyIonRcd"),
        tag = cms.string("CentralityTable_HFtowers200_DataPbPb_periHYDJETshape_run2v1033p1x01_offline"),
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        label = cms.untracked.string("HFtowers")
        ),
    ])

## ==== FILTERS ====
### PbPb Event Selection
process.load("MuonAnalysis.TagAndProbe.OfflinePrimaryVerticesRecovery_cfi")
process.load('MuonAnalysis.TagAndProbe.collisionEventSelection_cff')
### Trigger selection
process.load("HLTrigger.HLTfilters.triggerResultsFilter_cfi")
process.triggerResultsFilter.triggerConditions = cms.vstring( 'HLT_HIL3Mu7_NHitQ10_v*' )
process.triggerResultsFilter.hltResults = cms.InputTag("TriggerResults","","HLT")
process.triggerResultsFilter.l1tResults = cms.InputTag("") # keep empty!
process.triggerResultsFilter.throw = False
### Filter sequence
process.fastFilter = cms.Sequence(process.triggerResultsFilter + process.offlinePrimaryVerticesRecovery + process.collisionEventSelectionAODv2)

##    __  __
##   |  \/  |_   _  ___  _ __  ___
##   | |\/| | | | |/ _ \| '_ \/ __|
##   | |  | | |_| | (_) | | | \__ \
##   |_|  |_|\__,_|\___/|_| |_|___/
##
## ==== Merge CaloMuons and Tracks into the collection of reco::Muons  ====

InAcceptance_2015       = '((abs(eta)<1.2 && pt>=3.5) || (1.2<=abs(eta) && abs(eta)<2.1 && pt>=5.77-1.89*abs(eta)) || (2.1<=abs(eta) && abs(eta)<2.4 && pt>=1.8))'
InAcceptance_2018_Tight = '((abs(eta)<1.2 && pt>=3.5) || (1.2<=abs(eta) && abs(eta)<2.1 && pt>=5.47-1.89*abs(eta)) || (2.1<=abs(eta) && abs(eta)<2.4 && pt>=1.5))'
InAcceptance_2018_Loose = '((abs(eta)<0.3 && pt>=3.4) || (0.3<=abs(eta) && abs(eta)<1.1 && pt>=3.3) || (1.1<=abs(eta) && abs(eta)<1.4 && pt>=7.7-4.0*abs(eta)) || (1.4<=abs(eta) && abs(eta)<1.55 && pt>=2.1) || (1.55<=abs(eta) && abs(eta)<2.2 && pt>=4.25-1.39*abs(eta)) || (2.2<=abs(eta) && abs(eta)<2.4 && pt>=1.2))'

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
process.twoMuons = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("mergedMuons"), minNumber = cms.uint32(2))

## ==== Trigger matching
process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")
from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import *
changeRecoMuonInput(process, "mergedMuons")
## For trigger muons
switchOffAmbiguityResolution(process)
## For L1 muons
addHLTL1Passthrough(process)
useL1Stage2Candidates(process) # Enable L1 stage2 setup
process.muonMatchHLTL1.useStage2L1 = cms.bool(True)
process.muonMatchHLTL1.useMB2InOverlap = cms.bool(True)
process.muonMatchHLTL1.preselection = cms.string("")
appendL1MatchingAlgo(process)
process.muonL1Info.maxDeltaR = 0.3
process.muonL1Info.maxDeltaEta = 0.2
process.muonL1Info.fallbackToME1 = True
process.muonMatchHLTL1.maxDeltaR = 0.3
process.muonMatchHLTL1.maxDeltaEta = 0.2
process.muonMatchHLTL1.fallbackToME1 = True
process.patTrigger.collections.remove("hltL1extraParticles")
process.patTrigger.collections.append("hltGtStage2Digis:Muon")
process.muonL1Info.matched = cms.InputTag("gtStage2Digis:Muon")
process.muonMatchHLTL1.matchedCuts = cms.string('coll("hltGtStage2Digis:Muon")')
## For L2 muons
process.muonMatchHLTL2.maxDeltaR = 0.3
process.muonMatchHLTL2.maxDPtRel = 10.0
process.patTrigger.collections.remove("hltL2MuonCandidates")
process.patTrigger.collections.append("hltL2MuonCandidatesPPOnAA")
process.muonMatchHLTL2.matchedCuts = cms.string('coll("hltL2MuonCandidatesPPOnAA")')
## For L3 muons
process.muonMatchHLTL3.maxDeltaR = 0.1
process.muonMatchHLTL3.maxDPtRel = 10.0
process.patTrigger.collections.remove("hltIterL3MuonCandidates")
process.patTrigger.collections.append("hltIterL3MuonCandidatesPPOnAA")
process.muonMatchHLTL3.matchedCuts = cms.string('coll("hltIterL3MuonCandidatesPPOnAA")')

## ==== Tag and probe variables
from MuonAnalysis.TagAndProbe.common_variables_cff import *
process.load("MuonAnalysis.TagAndProbe.common_modules_cff")
## PbPb centrality variables
from MuonAnalysis.TagAndProbe.heavyIon_variables_cff import *
process.load("MuonAnalysis.TagAndProbe.heavyIon_modules_cff")
## Flags
### Muon Id
TightId = "passed('CutBasedIdTight')"
HybridSoftIdReco_2018 = "isGlobalMuon && isTrackerMuon && innerTrack.hitPattern.trackerLayersWithMeasurement > 5 && innerTrack.hitPattern.pixelLayersWithMeasurement > 0"
HybridSoftId_2018 = HybridSoftIdReco_2018 + " && abs(dB('PV2D')) < 0.3 && abs(dB('PVDZ')) < 20.0"
HybridSoftIdReco_2015 = HybridSoftIdReco_2018
HybridSoftId_2015 = HybridSoftId_2018 + " && muonID('TMOneStationTight')"
SoftId = "passed('SoftCutBasedId')"
### Trigger
LowPtTriggerProbeFlags = cms.PSet(
    # Double Muon Trigger Paths
    HLT_HIL1DoubleMuOpen = cms.string("!triggerObjectMatchesByPath('HLT_HIL1DoubleMuOpen_v*',1,0).empty()"),
    HLT_HIL1DoubleMuOpen_OS_Centrality_40_100 = cms.string("!triggerObjectMatchesByPath('HLT_HIL1DoubleMuOpen_OS_Centrality_40_100_v*',1,0).empty()"),
    HLT_HIL1DoubleMuOpen_Centrality_50_100 = cms.string("!triggerObjectMatchesByPath('HLT_HIL1DoubleMuOpen_Centrality_50_100_v*',1,0).empty()"),
    HLT_HIL2DoubleMuOpen = cms.string("!triggerObjectMatchesByPath('HLT_HIL2DoubleMuOpen_v*',1,0).empty()"),
    HLT_HIL3DoubleMuOpen = cms.string("!triggerObjectMatchesByPath('HLT_HIL3DoubleMuOpen_v*',1,0).empty()"),
    HLT_HIL3DoubleMuOpen_M60120 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3DoubleMuOpen_M60120_v*',1,0).empty()"),
    HLT_HIL3DoubleMuOpen_JpsiPsi = cms.string("!triggerObjectMatchesByPath('HLT_HIL3DoubleMuOpen_JpsiPsi_v*',1,0).empty()"),
    HLT_HIL3DoubleMuOpen_Upsi = cms.string("!triggerObjectMatchesByPath('HLT_HIL3DoubleMuOpen_Upsi_v*',1,0).empty()"),
    HLT_HIL3Mu0_L2Mu0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu0_L2Mu0_v*',1,0).empty()"),
    HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v*',1,0).empty()"),
    HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v2 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v*',0,1).empty()"),
    HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_v*',1,0).empty()"),
    HLT_HIL3Mu3_L1TripleMuOpen = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu3_L1TripleMuOpen_v*',1,0).empty()"),
    # Double Muon Trigger Filters
    HLT_HIL1DoubleMuOpen_Filter = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sL1DoubleMuOpenL1Filtered0').empty()"),
    HLT_HIL1DoubleMuOpen_OS_Centrality_40_100_Filter = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sL1DoubleMuOpenOSCentrality40100L1Filtered0').empty()"),
    HLT_HIL1DoubleMuOpen_Centrality_50_100_Filter = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sL1DoubleMuOpenCentrality50100L1Filtered0').empty()"),
    HLT_HIL2DoubleMuOpen_Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sL1DoubleMuOpenL1f0L2Filtered0').empty()"),
    HLT_HIL3DoubleMuOpen_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1DoubleMuOpenL3Filtered0').empty()"),
    HLT_HIL3DoubleMuOpen_M60120_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1DoubleMuOpenL3FilteredM60120').empty()"),
    HLT_HIL3DoubleMuOpen_JpsiPsi_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1DoubleMuOpenL3FilteredPsi').empty()"),
    HLT_HIL3DoubleMuOpen_Upsi_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1DoubleMuOpenL3FilteredUpsi').empty()"),
    HLT_HIL3Mu0_L2Mu0_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3f0L3Mu0L2Mu0Filtered0').empty()"),
    HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_L1Filter = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sL1DoubleMuOpenMAXdR3p5L1Filtered0').empty()"),
    HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_L2Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fDoubleMuOpenL2DR3p5PreFiltered0').empty()"),
    HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_L3Filter = cms.string("!triggerObjectMatchesByFilter('hltL3f0DR3p5L3FilteredNHitQ10').empty()"),
    HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3f0L3Mu0L2Mu0DR3p5FilteredNHitQ10M1to5').empty()"),
    HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_FilterL2 = cms.string("!triggerObjectMatchesByCollection('hltL2MuonCandidatesPPOnAA').empty() && !triggerObjectMatchesByCollection('hltL2MuonCandidatesPPOnAA').at(0).hasFilterLabel('hltL3f0L3Mu0L2Mu0DR3p5FilteredNHitQ10M1to5')"),
    HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_FilterL3 = cms.string("!triggerObjectMatchesByCollection('hltIterL3MuonCandidatesPPOnAA').empty() && !triggerObjectMatchesByCollection('hltIterL3MuonCandidatesPPOnAA').at(0).hasFilterLabel('hltL3f0L3Mu0L2Mu0DR3p5FilteredNHitQ10M1to5')"),
    HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_L1Filter = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sL1DoubleMuOpenL1Filtered0').empty()"),
    HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_L2Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fDoubleMuOpenL2PreFiltered0').empty()"),
    HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_L3Filter = cms.string("!triggerObjectMatchesByFilter('hltL3f0L3Filtered2p5NHitQ10').empty()"),
    HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3f0L3Mu2p5NHitQ10L2Mu2FilteredM7toinf').empty()"),
    HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_FilterL2 = cms.string("!triggerObjectMatchesByCollection('hltL2MuonCandidatesPPOnAA').empty() && !triggerObjectMatchesByCollection('hltL2MuonCandidatesPPOnAA').at(0).hasFilterLabel('hltL3f0L3Mu2p5NHitQ10L2Mu2FilteredM7toinf')"),
    HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_FilterL3 = cms.string("!triggerObjectMatchesByCollection('hltIterL3MuonCandidatesPPOnAA').empty() && !triggerObjectMatchesByCollection('hltIterL3MuonCandidatesPPOnAA').at(0).hasFilterLabel('hltL3f0L3Mu2p5NHitQ10L2Mu2FilteredM7toinf')"),
    HLT_HIL3Mu3_L1TripleMuOpen_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1DoubleMuOpenL1fN3L2f0L3Filtered3').empty()"),
    # Single Muon Trigger Paths
    HLT_HIL1MuOpen_Centrality_70_100 = cms.string("!triggerObjectMatchesByPath('HLT_HIL1MuOpen_Centrality_70_100_v*',1,0).empty()"),
    HLT_HIL1MuOpen_Centrality_80_100 = cms.string("!triggerObjectMatchesByPath('HLT_HIL1MuOpen_Centrality_80_100_v*',1,0).empty()"),
    # Single Muon Trigger Filters
    HLT_HIL1MuOpen_Centrality_70_100_Filter = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sL1MuOpenCentrality70100L1Filtered0').empty()"),
    HLT_HIL1MuOpen_Centrality_80_100_Filter = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sL1MuOpenCentrality80100L1Filtered0').empty()"),
)
LowPtTriggerTagFlags = cms.PSet(
    # Single Muon Trigger Paths
    HLT_HIL2Mu3_NHitQ15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ15_v*',1,0).empty()"),
    HLT_HIL2Mu5_NHitQ15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ15_v*',1,0).empty()"),
    HLT_HIL2Mu7_NHitQ15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu7_NHitQ15_v*',1,0).empty()"),
    HLT_HIL3Mu3_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ10_v*',1,0).empty()"),
    HLT_HIL3Mu5_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ10_v*',1,0).empty()"),
    HLT_HIL3Mu7_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu7_NHitQ10_v*',1,0).empty()"),
    # Single Muon Trigger Filters
    HLT_HIL2Mu3_NHitQ15_Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sMu*Open*L1f0L2Filtered3NHitQ15').empty()"),
    HLT_HIL2Mu5_NHitQ15_Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sMu*Open*L1f0L2Filtered5NHitQ15').empty()"),
    HLT_HIL2Mu7_NHitQ15_Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sMu*Open*L1f0L2Filtered7NHitQ15').empty()"),
    HLT_HIL3Mu3_NHitQ10_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu*Open*L1f0L2f0L3Filtered3NHitQ10').empty()"),
    HLT_HIL3Mu5_NHitQ10_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu*Open*L1f0L2f0L3Filtered5NHitQ10').empty()"),
    HLT_HIL3Mu7_NHitQ10_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu*Open*L1f0L2f0L3Filtered7NHitQ10').empty()"),
)
HighPtTriggerTagFlags = cms.PSet(
    # Single Muon Trigger Paths
    HLT_HIL3Mu12 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu12_v*',1,0).empty()"),
    HLT_HIL3Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu15_v*',1,0).empty()"),
    HLT_HIL3Mu20 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu20_v*',1,0).empty()"),
    # Single Muon Trigger Filters
    HLT_HIL3Mu12_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu*OpenL1f*L2f0L3Filtered12').empty()"),
    HLT_HIL3Mu15_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu*OpenL1f*L2f0L3Filtered15').empty()"),
    HLT_HIL3Mu20_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu*OpenL1f*L2f0L3Filtered20').empty()"),
)
### Tracking
TRACK_CUTS = "track.isNonnull && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.pixelLayersWithMeasurement > 0"

## ==== Tag muons
process.tagMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(InAcceptance_2018_Tight+" && "+HybridSoftId_2018+" && !triggerObjectMatchesByPath('HLT_HIL3Mu7_NHitQ10_v*',1,0).empty()"),
)
process.oneTag = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tagMuons"), minNumber = cms.uint32(1))
process.pseudoTag = cms.EDFilter("MuonSelector",
    src = cms.InputTag("mergedMuons"),
    cut = cms.string(InAcceptance_2018_Tight+" && "+HybridSoftIdReco_2018),
)
process.onePseudoTag = process.oneTag.clone(src = cms.InputTag("pseudoTag"))

## ==== Probe muons
process.probeMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string("isTrackerMuon || isGlobalMuon || isPFMuon"),
)
process.oneProbe = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("probeMuons"), minNumber = cms.uint32(1))
process.pseudoProbe = cms.EDFilter("MuonSelector",
    src = cms.InputTag("mergedMuons"),
    cut = process.probeMuons.cut,
)
process.onePseudoProbe = process.oneProbe.clone(src = cms.InputTag("pseudoProbe"))

## ==== Tag and Probe muon pairs
process.tpPairs = cms.EDProducer("CandViewShallowCloneCombiner",
    cut = cms.string('2.0 < mass < 4.0'),
    decay = cms.string('tagMuons@+ probeMuons@-')
)
process.onePair = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairs"), minNumber = cms.uint32(1))
process.pseudoPairs = process.tpPairs.clone(
    decay = cms.string('pseudoTag@+ pseudoProbe@-')
)
process.onePseudoPair = process.onePair.clone(src = cms.InputTag("pseudoPairs"))

process.fastPseudoTnP = cms.Sequence(process.mergedMuons + process.twoMuons + process.pseudoTag + process.onePseudoTag + process.pseudoProbe + process.onePseudoProbe + process.pseudoPairs + process.onePseudoPair)

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
        L1Variables,
        L2Variables,
        L3Variables,
        dxyPVdzmin = cms.InputTag("muonDxyPVdzmin","dxyPVdzmin"),
        dzPV = cms.InputTag("muonDxyPVdzmin","dzPV"),
        dxyPV = cms.InputTag("muonDxyPVdzmin","dxyPV"),
        dzError = cms.string("? innerTrack.isNull() ? -1 : innerTrack.dzError"),
        dxyError = cms.string("? innerTrack.isNull() ? -1 : innerTrack.dxyError"),
        trackOrigAlgo = cms.string("? innerTrack.isNull() ? -1 : innerTrack.originalAlgo"),
        trackAlgo = cms.string("? innerTrack.isNull() ? -1 : innerTrack.algo"),
    ),
    flags = cms.PSet(
        TrackQualityFlags,
        MuonIDFlags,
        LowPtTriggerProbeFlags,
        LowPtTriggerTagFlags,
        HighPtTriggerTagFlags,
        TightId = cms.string(TightId),
        HybridSoftId_2015 = cms.string(HybridSoftId_2015),
        HybridSoftId_2018 = cms.string(HybridSoftId_2018),
        SoftId = cms.string(SoftId),
        InAcceptance_2015 = cms.string(InAcceptance_2015),
        InAcceptance_2018_Loose = cms.string(InAcceptance_2018_Loose),
        InAcceptance_2018_Tight = cms.string(InAcceptance_2018_Tight),
        TrackCuts = cms.string(TRACK_CUTS),
    ),
    tagVariables = cms.PSet(
        KinematicVariables,
        MuonIDVariables,
        TrackQualityVariables,
        GlobalTrackQualityVariables,
        L3Variables,
        CentralityVariables,
        nVertices = cms.InputTag("nverticesModule"),
        dxyPVdzmin = cms.InputTag("muonDxyPVdzminTags","dxyPVdzmin"),
        dzPV = cms.InputTag("muonDxyPVdzminTags","dzPV"),
        dxyPV = cms.InputTag("muonDxyPVdzminTags","dxyPV"),
        dzError = cms.string("? innerTrack.isNull() ? -1 : innerTrack.dzError"),
        dxyError = cms.string("? innerTrack.isNull() ? -1 : innerTrack.dxyError"),
        trackOrigAlgo = cms.string("? innerTrack.isNull() ? -1 : innerTrack.originalAlgo"),
        trackAlgo = cms.string("? innerTrack.isNull() ? -1 : innerTrack.algo"),
    ),
    tagFlags = cms.PSet(
        LowPtTriggerProbeFlags,
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

process.tnpSimpleSequence = cms.Sequence(
    process.tagMuons +
    process.oneTag     +
    process.probeMuons +
    process.oneProbe   +
    process.tpPairs    +
    process.onePair    +
    process.nverticesModule +
    process.muonDxyPVdzmin + process.muonDxyPVdzminTags +
    process.probeMultiplicity + process.probeMultiplicityTMGM +
    process.bestPairByJpsiMass +
    process.centralityInfo +
    process.centralityBinInfo +
    process.tpTree
)

process.tagAndProbe = cms.Path(
    process.fastFilter
    * process.fastPseudoTnP
    * process.centralityBin
    * process.mergedMuons * process.patMuonsWithTriggerSequence
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
process.oneProbeSta = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("probeMuonsSta"), minNumber = cms.uint32(1))
process.pseudoProbeSta = cms.EDFilter("MuonSelector",
    src = cms.InputTag("muonsSta"),
    cut = process.probeMuonsSta.cut,
)
process.onePseudoProbeSta = process.oneProbeSta.clone(src = cms.InputTag("pseudoProbeSta"))

process.tpPairsSta = process.tpPairs.clone(
    cut = cms.string('1. < mass < 6.'),
    decay = cms.string('tagMuons@+ probeMuonsSta@-')
)
process.onePairSta = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairsSta"), minNumber = cms.uint32(1))
process.pseudoPairsSta = process.tpPairsSta.clone(
    decay = cms.string('pseudoTag@+ pseudoProbeSta@-')
)
process.onePseudoPairSta = process.onePairSta.clone(src = cms.InputTag("pseudoPairsSta"))

process.fastPseudoTnPSta = cms.Sequence(process.mergedMuons + process.pseudoTag + process.onePseudoTag + process.muonsSta + process.pseudoProbeSta + process.onePseudoProbeSta + process.pseudoPairsSta + process.onePseudoPairSta)

process.staToTkMatch.maxDeltaR = 0.3
process.staToTkMatch.maxDeltaPtRel = 2.
process.staToTkMatchNoJPsi.maxDeltaR = 0.3
process.staToTkMatchNoJPsi.maxDeltaPtRel = 2.
process.staToTkMatchNoBestJPsi.maxDeltaR = 0.3
process.staToTkMatchNoBestJPsi.maxDeltaPtRel = 2.

process.load("MuonAnalysis.TagAndProbe.tracking_reco_info_cff")

process.tpTreeSta = process.tpTree.clone(
    tagProbePairs = cms.InputTag("tpPairsSta"),
    arbitration   = cms.string("OneProbe"),
    variables = cms.PSet(
        KinematicVariables,
        StaOnlyVariables,
        dzError = cms.string("? innerTrack.isNull() ? -1 : innerTrack.dzError"),
        dxyError = cms.string("? innerTrack.isNull() ? -1 : innerTrack.dxyError"),
        trackOrigAlgo = cms.string("? innerTrack.isNull() ? -1 : innerTrack.originalAlgo"),
        trackAlgo = cms.string("? innerTrack.isNull() ? -1 : innerTrack.algo"),
    ),
    flags = cms.PSet(
        outerValidHits = cms.string("outerTrack.numberOfValidHits > 0"),
        TM  = cms.string("isTrackerMuon"),
        Glb = cms.string("isGlobalMuon"),
        PF  = cms.string("isPFMuon"),
        tk  = cms.string("track.isNonnull"),
        isSTA = cms.string("isStandAloneMuon"),
        TrackCuts = cms.string(TRACK_CUTS),
        StaTkSameCharge = cms.string("outerTrack.isNonnull && innerTrack.isNonnull && (outerTrack.charge == innerTrack.charge)"),
        InAcceptance_2015 = cms.string(InAcceptance_2015),
        InAcceptance_2018_Loose = cms.string(InAcceptance_2018_Loose),
        InAcceptance_2018_Tight = cms.string(InAcceptance_2018_Tight),
    ),
    tagVariables = cms.PSet(
        CentralityVariables,
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        phi = cms.string("phi"),
        nVertices = cms.InputTag("nverticesModule"),
        dxyPVdzmin = cms.InputTag("muonDxyPVdzminTags","dxyPVdzmin"),
        dzPV = cms.InputTag("muonDxyPVdzminTags","dzPV"),
        dxyPV = cms.InputTag("muonDxyPVdzminTags","dxyPV"),
        dzError = cms.string("? innerTrack.isNull() ? -1 : innerTrack.dzError"),
        dxyError = cms.string("? innerTrack.isNull() ? -1 : innerTrack.dxyError"),
        trackOrigAlgo = cms.string("? innerTrack.isNull() ? -1 : innerTrack.originalAlgo"),
        trackAlgo = cms.string("? innerTrack.isNull() ? -1 : innerTrack.algo"),
    ),
    tagFlags = cms.PSet(
        LowPtTriggerProbeFlags,
        LowPtTriggerTagFlags,
        HighPtTriggerTagFlags,
    ),
    pairVariables = cms.PSet(
        dz = cms.string("daughter(0).vz - daughter(1).vz"),
        pt = cms.string("pt"),
        rapidity = cms.string("rapidity"),
        deltaR = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
    ),
    pairFlags = cms.PSet(),
)

process.tnpSimpleSequenceSta = cms.Sequence(
    process.tagMuons +
    process.oneTag     +
    process.probeMuonsSta   +
    process.oneProbeSta     +
    process.tpPairsSta      +
    process.onePairSta      +
    process.nverticesModule +
    process.muonDxyPVdzminTags +
    #process.staToTkMatchSequenceJPsi +
    process.centralityInfo +
    process.centralityBinInfo +
    process.tpTreeSta
)

process.tagAndProbeSta = cms.Path(
    process.fastFilter
    * process.fastPseudoTnPSta
    * process.centralityBin
    * process.mergedMuons * process.patMuonsWithTriggerSequence
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
    cut = cms.string(TRACK_CUTS + ' && ' + InAcceptance_2018_Loose),
)
process.oneProbeTrk = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("probeMuonsTrk"), minNumber = cms.uint32(1))
process.pseudoProbeTrk = cms.EDFilter("MuonSelector",
    src = cms.InputTag("mergedMuons"),
    cut = process.probeMuonsTrk.cut
)
process.onePseudoProbeTrk = process.oneProbeTrk.clone(src = cms.InputTag("pseudoProbeTrk"))

process.tpPairsTrk = cms.EDProducer("CandViewShallowCloneCombiner",
    cut = cms.string('2.5 < mass < 3.5'),
    decay = cms.string('tagMuons@+ probeMuonsTrk@-')
)
process.onePairTrk = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairsTrk"), minNumber = cms.uint32(1))
process.pseudoPairsTrk = process.tpPairsTrk.clone(
    decay = cms.string('pseudoTag@+ pseudoProbeTrk@-')
)
process.onePseudoPairTrk = process.onePairTrk.clone(src = cms.InputTag("pseudoPairsTrk"))

process.fastPseudoTnPTrk = cms.Sequence(process.mergedMuons + process.twoMuons + process.pseudoTag + process.onePseudoTag + process.pseudoProbeTrk + process.onePseudoProbeTrk + process.pseudoPairsTrk + process.onePseudoPairTrk)

process.tpTreeTrk = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tpPairsTrk"),
    arbitration   = cms.string("OneProbe"),
    # probe variables: all useful ones
    variables = cms.PSet(
      KinematicVariables,
      StaOnlyVariables,
      dxyPVdzmin = cms.InputTag("muonDxyPVdzminTrk","dxyPVdzmin"),
      dzPV = cms.InputTag("muonDxyPVdzminTrk","dzPV"),
      dxyPV = cms.InputTag("muonDxyPVdzminTrk","dxyPV"),
      dzError = cms.string("? innerTrack.isNull() ? -1 : innerTrack.dzError"),
      dxyError = cms.string("? innerTrack.isNull() ? -1 : innerTrack.dxyError"),
      trackOrigAlgo = cms.string("? innerTrack.isNull() ? -1 : innerTrack.originalAlgo"),
      trackAlgo = cms.string("? innerTrack.isNull() ? -1 : innerTrack.algo"),
    ),
    flags = cms.PSet(
      isSTA = cms.string("isStandAloneMuon"),
      Glb   = cms.string("isGlobalMuon"),
      PF    = cms.string("isPFMuon"),
      TM    = cms.string("isTrackerMuon"),
      TrackCuts = cms.string(TRACK_CUTS),
      outerValidHits = cms.string("? outerTrack.isNull() ? 0 : outerTrack.numberOfValidHits > 0"),
      InAcceptance_2015 = cms.string(InAcceptance_2015),
      InAcceptance_2018_Loose = cms.string(InAcceptance_2018_Loose),
      InAcceptance_2018_Tight = cms.string(InAcceptance_2018_Tight),
    ),
    tagVariables = cms.PSet(
      TrackQualityVariables,
      GlobalTrackQualityVariables,
      CentralityVariables,
      pt  = cms.string("pt"),
      eta = cms.string("eta"),
      abseta = cms.string("abs(eta)"),
      phi = cms.string("phi"),
      nVertices = cms.InputTag("nverticesModule"),
      l2dr = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidatesPPOnAA').empty() ? 999 : "+
        " deltaR( eta, phi, " +
        "         triggerObjectMatchesByCollection('hltL2MuonCandidatesPPOnAA').at(0).eta, "+
        "         triggerObjectMatchesByCollection('hltL2MuonCandidatesPPOnAA').at(0).phi ) "),
    ),
    tagFlags = cms.PSet(
       LowPtTriggerProbeFlags,
       LowPtTriggerTagFlags,
       HighPtTriggerTagFlags
    ),
    pairVariables = cms.PSet(
      pt = cms.string("pt"),
      y = cms.string("rapidity"),
      absy = cms.string("abs(rapidity)"),
      dz = cms.string("daughter(0).vz - daughter(1).vz"),
      deltaR = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
    ),
    pairFlags = cms.PSet(),
    isMC = cms.bool(False),
    addRunLumiInfo = cms.bool(True),
)

process.muonDxyPVdzminTrk = process.muonDxyPVdzmin.clone(
    probes = cms.InputTag("probeMuonsTrk")
)

process.tnpSimpleSequenceTrk = cms.Sequence(
    process.tagMuons +
    process.oneTag +
    process.probeMuonsTrk +
    process.oneProbeTrk +
    process.tpPairsTrk +
    process.onePairTrk +
    process.muonDxyPVdzminTrk +
    process.nverticesModule +
    process.centralityInfo +
    process.centralityBinInfo +
    process.tpTreeTrk
)

process.tagAndProbeTrk = cms.Path(
    process.fastFilter
    * process.fastPseudoTnPTrk
    * process.centralityBin
    * process.mergedMuons * process.patMuonsWithTriggerSequence
    * process.tnpSimpleSequenceTrk
)

process.schedule = cms.Schedule(
   process.tagAndProbe,
   process.tagAndProbeSta,
   process.tagAndProbeTrk,
)

process.RandomNumberGeneratorService.tkTracksNoJPsi = cms.PSet( initialSeed = cms.untracked.uint32(81) )
process.RandomNumberGeneratorService.tkTracksNoBestJPsi = cms.PSet( initialSeed = cms.untracked.uint32(81) )

process.TFileService = cms.Service("TFileService", fileName = cms.string("tnpJpsi_Data_PbPb.root"))

from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
process = MassReplaceInputTag(process,"offlinePrimaryVertices","offlinePrimaryVerticesRecovery")
process.offlinePrimaryVerticesRecovery.oldVertexLabel = "offlinePrimaryVertices"
