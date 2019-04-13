import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/user/anstahll/Dilepton/MC/Embedded/JpsiMM_5p02TeV_TuneCP5_Embd_RECO_20190117/JpsiMM_5p02TeV_TuneCP5/JpsiMM_5p02TeV_TuneCP5_Embd_RECO_20190117/190118_020651/0001/JpsiMM_5p02TeV_TuneCP5_Embd_step2_1074.root')
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.GlobalTag.globaltag = cms.string('103X_upgrade2018_realistic_HI_v11')

## PbPb centrality bin producer
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("HeavyIonRcd"),
        tag = cms.string("CentralityTable_HFtowers200_HydjetDrum5F_v1032x01_mc"),
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        label = cms.untracked.string("HFtowers")
        ),
    ])

## ==== FILTERS ====
### PbPb Event Selection
process.load("RecoVertex.PrimaryVertexProducer.OfflinePrimaryVerticesRecovery_cfi")
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
### Trigger selection
process.load("HLTrigger.HLTfilters.triggerResultsFilter_cfi")
process.triggerResultsFilter.triggerConditions = cms.vstring( 'HLT_HIL3Mu3_NHitQ10*' , 'HLT_HIL3Mu5_NHitQ10*' , 'HLT_HIL3Mu7_NHitQ10*',
                                                              'HLT_HIL3Mu12_v*' , 'HLT_HIL3Mu15_v*' , 'HLT_HIL3Mu20_v*' )
process.triggerResultsFilter.hltResults = cms.InputTag("TriggerResults","","HLT")
process.triggerResultsFilter.l1tResults = cms.InputTag("") # keep empty!
process.triggerResultsFilter.throw = False
### Filter sequence
process.fastFilter = cms.Sequence(process.offlinePrimaryVerticesRecovery + process.collisionEventSelectionAODv2 + process.triggerResultsFilter)

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

## ==== Trigger matching
process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")
from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import *
changeRecoMuonInput(process, "mergedMuons")
## with some customization
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
process.muonL1Info.matched = cms.InputTag("gtStage2Digis:Muon:RECO")
process.muonMatchHLTL1.matchedCuts = cms.string('coll("hltGtStage2Digis:Muon")')
process.muonMatchHLTL1.useStage2L1 = cms.bool(True)
appendL1MatchingAlgo(process)
## For L2 muons
process.patTrigger.collections.remove("hltL2MuonCandidates")
process.patTrigger.collections.append("hltL2MuonCandidatesPPOnAA")
process.muonMatchHLTL2.matchedCuts = cms.string('coll("hltL2MuonCandidatesPPOnAA")')
## For L3 muons
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
TightIdReco = "isGlobalMuon && isPFMuon && globalTrack.normalizedChi2 < 10 && globalTrack.hitPattern.numberOfValidMuonHits > 0 && numberOfMatchedStations > 1 && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0"
TightId = TightIdReco+" && abs(dB) < 0.2"
HybridSoftIdReco_2018 = "isTrackerMuon && isGlobalMuon && innerTrack.hitPattern.trackerLayersWithMeasurement > 5 && innerTrack.hitPattern.numberOfValidPixelHits > 0"
HybridSoftId_2018 = HybridSoftIdReco_2018
HybridSoftIdReco_2015 = HybridSoftIdReco_2018
HybridSoftId_2015 = HybridSoftIdReco_2015 + " && muonID('TMOneStationTight')"
SoftId = "muonID('TMOneStationTight') && innerTrack.hitPattern.trackerLayersWithMeasurement > 5 && innerTrack.hitPattern.pixelLayersWithMeasurement > 0 && innerTrack.quality(\"highPurity\")"
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
    HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_v*',1,0).empty()"),
    HLT_HIL3Mu3_L1TripleMuOpen = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu3_L1TripleMuOpen_v*',1,0).empty()"),
    HLT_HIL1MuOpen_Centrality_70_100 = cms.string("!triggerObjectMatchesByPath('HLT_HIL1MuOpen_Centrality_70_100_v*',1,0).empty()"),
    HLT_HIL1MuOpen_Centrality_80_100 = cms.string("!triggerObjectMatchesByPath('HLT_HIL1MuOpen_Centrality_80_100_v*',1,0).empty()"),
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
    HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_L1Filter = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sL1DoubleMuOpenL1Filtered0').empty()"),
    HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_L2Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fDoubleMuOpenL2PreFiltered0').empty()"),
    HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_L3Filter = cms.string("!triggerObjectMatchesByFilter('hltL3f0L3Filtered2p5NHitQ10').empty()"),
    HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3f0L3Mu2p5NHitQ10L2Mu2FilteredM7toinf').empty()"),
    HLT_HIL3Mu3_L1TripleMuOpen_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1DoubleMuOpenL1fN3L2f0L3Filtered3').empty()"),
)
LowPtTriggerTagFlags = cms.PSet(
    # Single Muon Trigger Paths
    HLT_HIL2Mu3_NHitQ15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ15_v*',1,0).empty()"),
    HLT_HIL2Mu5_NHitQ15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ15_v*',1,0).empty()"),
    HLT_HIL2Mu7_NHitQ15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu7_NHitQ15_v*',1,0).empty()"),
    HLT_HIL3Mu3_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ10_v*',1,0).empty()"),
    HLT_HIL3Mu5_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ10_v*',1,0).empty()"),
    HLT_HIL3Mu7_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu7_NHitQ10_v*',1,0).empty()"),
    HLT_HIL2Mu3_NHitQ15_tagging = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ15_tagging_v*',1,0).empty()"),
    HLT_HIL2Mu5_NHitQ15_tagging = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ15_tagging_v*',1,0).empty()"),
    HLT_HIL2Mu7_NHitQ15_tagging = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu7_NHitQ15_tagging_v*',1,0).empty()"),
    HLT_HIL3Mu3_NHitQ10_tagging = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ10_tagging_v*',1,0).empty()"),
    HLT_HIL3Mu5_NHitQ10_tagging = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ10_tagging_v*',1,0).empty()"),
    HLT_HIL3Mu7_NHitQ10_tagging = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu7_NHitQ10_tagging_v*',1,0).empty()"),
    # Single Muon Trigger Filters
    HLT_HIL1MuOpen_Centrality_70_100_Filter = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sL1MuOpenCentrality70100L1Filtered0').empty()"),
    HLT_HIL1MuOpen_Centrality_80_100_Filter = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sL1MuOpenCentrality80100L1Filtered0').empty()"),
    HLT_HIL2Mu3_NHitQ15_Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sMu3OpenL1f0L2Filtered3NHitQ15').empty() || !triggerObjectMatchesByFilter('hltL2fL1sMuOpenL1f0L2Filtered3NHitQ15').empty()"),
    HLT_HIL2Mu5_NHitQ15_Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sMu3OpenL1f0L2Filtered5NHitQ15').empty() || !triggerObjectMatchesByFilter('hltL2fL1sMuOpenL1f0L2Filtered5NHitQ15').empty()"),
    HLT_HIL2Mu7_NHitQ15_Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sMu3OpenL1f0L2Filtered7NHitQ15').empty() || !triggerObjectMatchesByFilter('hltL2fL1sMuOpenL1f0L2Filtered7NHitQ15').empty()"),
    HLT_HIL3Mu3_NHitQ10_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu3OpenL1f0L2f0L3Filtered3NHitQ10').empty() || !triggerObjectMatchesByFilter('hltL3fL1sL1SingleMuOpenL1f0L2f0L3Filtered3NHitQ10').empty()"),
    HLT_HIL3Mu5_NHitQ10_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu3OpenL1f0L2f0L3Filtered5NHitQ10').empty() || !triggerObjectMatchesByFilter('hltL3fL1sL1SingleMuOpenL1f0L2f0L3Filtered5NHitQ10').empty()"),
    HLT_HIL3Mu7_NHitQ10_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu3OpenL1f0L2f0L3Filtered7NHitQ10').empty() || !triggerObjectMatchesByFilter('hltL3fL1sL1SingleMuOpenL1f0L2f0L3Filtered7NHitQ10').empty()"),
    HLT_HIL2Mu3_NHitQ15_tagging_Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sMu3OpenMinimumBiasL1f0L2Filtered3NHitQ15').empty() || !triggerObjectMatchesByFilter('hltL2fL1sMuOpenMinimumBiasL1f0L2Filtered3NHitQ15').empty()"),
    HLT_HIL2Mu5_NHitQ15_tagging_Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sMu3OpenMinimumBiasL1f0L2Filtered5NHitQ15').empty() || !triggerObjectMatchesByFilter('hltL2fL1sMuOpenMinimumBiasL1f0L2Filtered5NHitQ15').empty()"),
    HLT_HIL2Mu7_NHitQ15_tagging_Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sMu3OpenMinimumBiasL1f0L2Filtered7NHitQ15').empty() || !triggerObjectMatchesByFilter('hltL2fL1sMuOpenMinimumBiasL1f0L2Filtered7NHitQ15').empty()"),
    HLT_HIL3Mu3_NHitQ10_tagging_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu3OpenMinimumBiasL1f0L2f0L3Filtered3NHitQ10').empty() || !triggerObjectMatchesByFilter('hltL3fL1sL1SingleMuOpenMinimumBiasL1f0L2f0L3Filtered3NHitQ10').empty()"),
    HLT_HIL3Mu5_NHitQ10_tagging_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu3OpenMinimumBiasL1f0L2f0L3Filtered5NHitQ10').empty() || !triggerObjectMatchesByFilter('hltL3fL1sL1SingleMuOpenMinimumBiasL1f0L2f0L3Filtered5NHitQ10').empty()"),
    HLT_HIL3Mu7_NHitQ10_tagging_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu3OpenMinimumBiasL1f0L2f0L3Filtered7NHitQ10').empty() || !triggerObjectMatchesByFilter('hltL3fL1sL1SingleMuOpenMinimumBiasL1f0L2f0L3Filtered7NHitQ10').empty()"),
    # Trigger objects
    isL1Muon = cms.string("!triggerObjectMatchesByCollection('hltGtStage2Digis:Muon').empty()"),
    isL2Muon = cms.string("!triggerObjectMatchesByCollection('hltL2MuonCandidatesPPOnAA').empty()"),
    isL3Muon = cms.string("!triggerObjectMatchesByCollection('hltIterL3MuonCandidatesPPOnAA').empty()"),
)
HighPtTriggerProbeFlags = cms.PSet(
    # Double Muon Trigger Paths
    HLT_HIL1DoubleMu10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL1DoubleMu10_v*',1,0).empty()"),
    HLT_HIL2_L1DoubleMu10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2_L1DoubleMu10_v*',1,0).empty()"),
    HLT_HIL3_L1DoubleMu10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3_L1DoubleMu10_v*',1,0).empty()"),
    # Double Muon Trigger Filters
    HLT_HIL1DoubleMu10_Filter = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sL1DoubleMu10L1Filtered0').empty()"),
    HLT_HIL2_L1DoubleMu10_Filter = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sL1DoubleMu10L1f0L2Filtered0').empty()"),
    HLT_HIL3_L1DoubleMu10_Filter = cms.string("!triggerObjectMatchesByFilter('hltDoubleMuOpenL1DoubleMu10Filtered').empty()"),
)
HighPtTriggerTagFlags = cms.PSet(
    # Single Muon Trigger Paths
    HLT_HIL3Mu12 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu12_v*',1,0).empty()"),
    HLT_HIL3Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu15_v*',1,0).empty()"),
    HLT_HIL3Mu20 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu20_v*',1,0).empty()"),
    # Single Muon Trigger Filters
    HLT_HIL3Mu12_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu3OpenL1f7L2f0L3Filtered12').empty() || !triggerObjectMatchesByFilter('hltL3fL1sL1SingleMuOpenL1f7L2f0L3Filtered12').empty() || !triggerObjectMatchesByFilter('hltL3fL1sL1SingleMuOpenL1f0L2f0L3Filtered12').empty()"),
    HLT_HIL3Mu15_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu3OpenL1f7L2f0L3Filtered15').empty() || !triggerObjectMatchesByFilter('hltL3fL1sL1SingleMuOpenL1f7L2f0L3Filtered15').empty() || !triggerObjectMatchesByFilter('hltL3fL1sL1SingleMuOpenL1f0L2f0L3Filtered15').empty()"),
    HLT_HIL3Mu20_Filter = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sL1SingleMu3OpenL1f7L2f0L3Filtered20').empty() || !triggerObjectMatchesByFilter('hltL3fL1sL1SingleMuOpenL1f7L2f0L3Filtered20').empty() || !triggerObjectMatchesByFilter('hltL3fL1sL1SingleMuOpenL1f0L2f0L3Filtered20').empty()"),
)
### Tracking
TRACK_CUTS = "track.isNonnull && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0"

## ==== Tag muons
process.tagMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(InAcceptance_2015+" && "+HybridSoftId_2015+" && !triggerObjectMatchesByCollection('hltIterL3MuonCandidatesPPOnAA').empty() && (!triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ10_v*',1,0).empty() || !triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ10_v*',1,0).empty() || !triggerObjectMatchesByPath('HLT_HIL3Mu7_NHitQ10_v*',1,0).empty() || !triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ10_tagging_v*',1,0).empty() || !triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ10_tagging_v*',1,0).empty() || !triggerObjectMatchesByPath('HLT_HIL3Mu7_NHitQ10_tagging_v*',1,0).empty() || !triggerObjectMatchesByPath('HLT_HIL3Mu12_v*',1,0).empty() || !triggerObjectMatchesByPath('HLT_HIL3Mu15_v*',1,0).empty() || !triggerObjectMatchesByPath('HLT_HIL3Mu20_v*',1,0).empty())"),
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
    cut = cms.string('2.0 < mass < 4.0'),
    decay = cms.string('tagMuons@+ probeMuons@-')
)
process.onePair = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairs"), minNumber = cms.uint32(1))

process.pseudoPairs = process.tpPairs.clone(decay = cms.string('pseudoTag@+ pseudoProbe@-'))
process.onePseudoPair = process.onePair.clone(src = cms.InputTag("pseudoPairs"))
process.fastPseudoTnP = cms.Sequence(process.mergedMuons + process.pseudoTag + process.onePseudoTag + process.pseudoProbe + process.pseudoPairs + process.onePseudoPair)

## ==== Tag and Probe tree
process.tpTree = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tpPairs"),
    arbitration   = cms.string("None"),
    # probe variables: all useful ones
    variables = cms.PSet(
        KinematicVariables,
        MuonIDVariables,
        #MuonCaloVariables,
        TrackQualityVariables,
        GlobalTrackQualityVariables,
        StaOnlyVariables,
        L1Variables,
        L2Variables,
        L3Variables,
        dxyBS = cms.InputTag("muonDxyPVdzmin","dxyBS"),
        dxyPVdzmin = cms.InputTag("muonDxyPVdzmin","dxyPVdzmin"),
        dzPV = cms.InputTag("muonDxyPVdzmin","dzPV"),
        dxyPV = cms.InputTag("muonDxyPVdzmin","dxyPV"),
    ),
    flags = cms.PSet(
        TrackQualityFlags,
        MuonIDFlags,
        LowPtTriggerProbeFlags,
        HighPtTriggerProbeFlags,
        TightId = cms.string(TightIdReco),
        HybridSoftId_2015 = cms.string(HybridSoftId_2015),
        HybridSoftId_2018 = cms.string(HybridSoftId_2018),
        SoftId = cms.string(SoftId),
        InAcceptance_2015 = cms.string(InAcceptance_2015),
        InAcceptance_2018_Loose = cms.string(InAcceptance_2018_Loose),
        InAcceptance_2018_Tight = cms.string(InAcceptance_2018_Tight),
        TrackCuts = cms.string(TRACK_CUTS),
        StaTkSameCharge = cms.string("outerTrack.isNonnull && innerTrack.isNonnull && (outerTrack.charge == innerTrack.charge)"),
        outerValidHits = cms.string("outerTrack.isNonnull && outerTrack.numberOfValidHits > 0"),
    ),
    tagVariables = cms.PSet(
        KinematicVariables,
        MuonIDVariables,
        #MuonCaloVariables,
        TrackQualityVariables,
        GlobalTrackQualityVariables,
        StaOnlyVariables,
        L1Variables,
        #L1SeedVariables, (NEED CHECK)
        L2Variables,
        L3Variables,
        CentralityVariables,
        nVertices = cms.InputTag("nverticesModule"),
        dxyBS = cms.InputTag("muonDxyPVdzminTags","dxyBS"),
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
    process.centralityInfo +
    process.centralityBinInfo +
    process.genWeightInfo +
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
process.pseudoProbeSta = cms.EDFilter("MuonSelector",
    src = cms.InputTag("muonsSta"),
    cut = cms.string("outerTrack.isNonnull"),
)

process.tpPairsSta = process.tpPairs.clone(decay = cms.string('tagMuons@+ probeMuonsSta@-'), cut = cms.string('1. < mass < 6.'))

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
    process.centralityInfo +
    process.centralityBinInfo +
    process.genWeightInfoSta +
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
process.fastPseudoTnPTrk = cms.Sequence(process.mergedMuons + process.pseudoTag + process.onePseudoTag + process.pseudoProbeTrk + process.pseudoPairsTrk + process.onePseudoPairTrk)

process.tpTreeTrk = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tpPairsTrk"),
    arbitration   = cms.string("OneProbe"),
    # probe variables: all useful ones
    variables = cms.PSet(
      KinematicVariables,
      StaOnlyVariables,
      dxyBS = cms.InputTag("muonDxyPVdzminTrk","dxyBS"),
      dxyPVdzmin = cms.InputTag("muonDxyPVdzminTrk","dxyPVdzmin"),
      dzPV = cms.InputTag("muonDxyPVdzminTrk","dzPV"),
      dxyPV = cms.InputTag("muonDxyPVdzminTrk","dxyPV"),
    ),
    flags = cms.PSet(
      isSTA = cms.string("isStandAloneMuon"),
      Glb   = cms.string("isGlobalMuon"),
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
       LowPtTriggerTagFlags,
       HighPtTriggerTagFlags
    ),
    pairVariables = cms.PSet(
      pt = cms.string("pt"),
      y = cms.string("rapidity"),
      absy = cms.string("abs(rapidity)"),
      deltaR = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
      genWeight = cms.InputTag("genWeightInfoTrk", "genWeight"),
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
    process.centralityInfo +
    process.centralityBinInfo +
    process.genWeightInfoTrk +
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

process.TFileService = cms.Service("TFileService", fileName = cms.string("tnpJpsi_MC_PbPb.root"))

from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
process = MassReplaceInputTag(process,"offlinePrimaryVertices","offlinePrimaryVerticesRecovery")
process.offlinePrimaryVerticesRecovery.oldVertexLabel = "offlinePrimaryVertices"
