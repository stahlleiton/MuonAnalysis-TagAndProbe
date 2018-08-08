import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/j/jjay/public/TagAndProbe_pPb/Data/0249A3C5-A2B1-E611-8E3E-FA163ED701FA.root'),
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )    

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.ReconstructionHeavyIons_cff")

process.GlobalTag.globaltag = cms.string('80X_dataRun2_Prompt_v15')

#process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")

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

## SELECT WHAT DATASET YOU'RE RUNNING ON
TRIGGER="SingleMu"
#TRIGGER="DoubleMu"

if TRIGGER == "SingleMu":
    process.triggerResultsFilter.triggerConditions = cms.vstring( 'HLT_PAL3Mu12_v1', 'HLT_PAL3Mu15_v1'  )
   # process.triggerResultsFilter.triggerConditions = cms.vstring( 'hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered12', 'hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered15'  )
    #process.triggerResultsFilter.triggerConditions = cms.vstring( 'HLT_Mu45_eta2p1_v*', 'HLT_Mu50_v*',
    #                                                              'HLT_IsoMu27_v*',   'HLT_IsoMu24_v*',   'HLT_IsoMu22_v*',   'HLT_IsoMu20_v*',
    #                                                              'HLT_IsoTkMu27_v*', 'HLT_IsoTkMu24_v*', 'HLT_IsoTkMu22_v*', 'HLT_IsoTkMu20_v*'  )
elif TRIGGER == "DoubleMu":
    process.triggerResultsFilter.triggerConditions = cms.vstring( 'HLT_Mu8_v*', 'HLT_Mu17_v*',
                                                                  'HLT_Mu8_TrkIsoVVL_v*', 'HLT_Mu17_TrkIsoVVL_v*',
                                                                  'HLT_Mu17_TkMu8_v*', 'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v*' )
else:
    raise RuntimeError, "TRIGGER must be 'SingleMu' or 'DoubleMu'"

process.triggerResultsFilter.l1tResults = "gtStage2Digis"
process.triggerResultsFilter.throw = False
process.triggerResultsFilter.hltResults = cms.InputTag("TriggerResults","","HLT")

#decomment when you have it
#process.triggerResultsFilterFake = process.triggerResultsFilter.clone(
#    triggerConditions = cms.vstring( 'HLT_Mu40_v*', 'HLT_Mu5_v*', 'HLT_Mu12_v*', 'HLT_Mu24_v*')
#)

#process.fastFilter     = cms.Sequence(process.collisionEventSelectionPA + process.triggerResultsFilter)
process.fastFilter     = cms.Sequence(process.triggerResultsFilter)

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
## with some customization
#O.J. Check this block
process.muonL1Info.maxDeltaR = 0.3
process.muonL1Info.fallbackToME1 = True
process.muonMatchHLTL1.maxDeltaR = 0.3
process.muonMatchHLTL1.fallbackToME1 = True
process.muonMatchHLTL2.maxDeltaR = 0.3
process.muonMatchHLTL2.maxDPtRel = 10.0
process.muonMatchHLTL3.maxDeltaR = 0.1
process.muonMatchHLTL3.maxDPtRel = 10.0

from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import *
changeRecoMuonInput(process, "mergedMuons")
switchOffAmbiguityResolution(process) # Switch off ambiguity resolution: allow multiple reco muons to match to the same trigger muon
addHLTL1Passthrough(process)

process.patMuonsWithoutTrigger.pvSrc = "hiSelectedVertex"
process.patTriggerFull.l1GtReadoutRecordInputTag = cms.InputTag("gtDigis","","RECO")                 
process.patTrigger.collections.remove("hltL3MuonCandidates")
process.patTrigger.collections.append("hltHIL3MuonCandidates")
process.muonMatchHLTL3.matchedCuts = cms.string('coll("hltHIL3MuonCandidates")')
from MuonAnalysis.TagAndProbe.common_variables_cff import *
process.load("MuonAnalysis.TagAndProbe.common_modules_cff")
from MuonAnalysis.TagAndProbe.heavyIon_variables_cff import *
process.load("MuonAnalysis.TagAndProbe.heavyIon_modules_cff")

TightId =  "isGlobalMuon && globalTrack.normalizedChi2 < 10 && globalTrack.hitPattern.numberOfValidMuonHits > 0 && numberOfMatchedStations > 1 && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0 && abs(dB) < 0.2"

HybridSoftId = "isTrackerMuon && isGlobalMuon && muonID('TMOneStationTight') && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0"

TRACK_CUTS = "track.isNonnull && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0"

#HighPtTriggerFlags = cms.PSet(
#   HIL2Mu5_NHitQ10_2HF = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ10_2HF_v*',1,0).empty()"),
#   HIL3Mu5_NHitQ15_2HF = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ15_2HF_v*',1,0).empty()"),
#   HIL2Mu5_NHitQ10_2HF0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ10_2HF0_v*',1,0).empty()"),
#   HIL3Mu5_NHitQ15_2HF0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ15_2HF0_v*',1,0).empty()"),
#   HIL2Mu7_NHitQ10_2HF = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu7_NHitQ10_2HF_v*',1,0).empty()"),
#   HIL3Mu7_NHitQ15_2HF = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu7_NHitQ15_2HF_v*',1,0).empty()"),
#   HIL2Mu7_NHitQ10_2HF0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu7_NHitQ10_2HF0_v*',1,0).empty()"),
#   HIL3Mu7_NHitQ15_2HF0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu7_NHitQ15_2HF0_v*',1,0).empty()"),
#   HIL2Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu15_v*',1,0).empty()"),
#   HIL3Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu15_v*',1,0).empty()"),
#   HIL2Mu20 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu20_v*',1,0).empty()"),
#   HIL3Mu20 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu20_v*',1,0).empty()"),
#)
#
#LowPtTriggerFlags = cms.PSet(
#   HIL2Mu3_NHitQ10_2HF = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ10_2HF_v*',1,0).empty()"),
#   HIL3Mu3_NHitQ15_2HF = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ15_2HF_v*',1,0).empty()"),
#   HIL2Mu3_NHitQ10_2HF0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ10_2HF0_v*',1,0).empty()"),
#   HIL3Mu3_NHitQ15_2HF0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ15_2HF0_v*',1,0).empty()"),
#)

#TrigTagFlags = cms.PSet(HighPtTriggerFlags, LowPtTriggerFlags)

#TrigProbeFlags = cms.PSet(
#      HLTL1v0 = cms.string("(!triggerObjectMatchesByPath('HLT_HIL1DoubleMu0_v*',1,0).empty() || !triggerObjectMatchesByPath('HLT_HIL1DoubleMu0_part*',1,0).empty())"),
#      HLTL1v1 = cms.string("!triggerObjectMatchesByFilter('hltHIDoubleMu0L1Filtered').empty()"),
#      HLTL1v2 = cms.string("((!triggerObjectMatchesByPath('HLT_HIL1DoubleMu0_v*',1,0).empty() || !triggerObjectMatchesByPath('HLT_HIL1DoubleMu0_part*',1,0).empty()) && !triggerObjectMatchesByFilter('hltHIDoubleMu0L1Filtered').empty())"),
#      L1Seed = cms.string("!triggerObjectMatchesByCollection('hltL1extraParticles').empty() && triggerObjectMatchesByCollection('hltL1extraParticles').at(0).hasFilterLabel('hltL1sL1DoubleMu0BptxAND')"),
#      L1Filter = cms.string("!triggerObjectMatchesByCollection('hltL1extraParticles').empty() && triggerObjectMatchesByCollection('hltL1extraParticles').at(0).hasFilterLabel('hltL1sL1DoubleMu0BptxAND') && abs(triggerObjectMatchesByCollection('hltL1extraParticles').at(0).eta)<2.5"),
#      )

#L1SeedVariables = cms.PSet(
#    l1SeedEta = cms.string("? !triggerObjectMatchesByCollection('hltL1extraParticles').empty() && triggerObjectMatchesByCollection('hltL1extraParticles').at(0).hasFilterLabel('hltL1sL1DoubleMu0BptxAND') ? triggerObjectMatchesByCollection('hltL1extraParticles').at(0).eta : -999"),
#    l1SeedPt = cms.string("? !triggerObjectMatchesByCollection('hltL1extraParticles').empty() && triggerObjectMatchesByCollection('hltL1extraParticles').at(0).hasFilterLabel('hltL1sL1DoubleMu0BptxAND') ? triggerObjectMatchesByCollection('hltL1extraParticles').at(0).pt : -999"),
#    )

process.tagMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(InAcceptance + ' && ' + TightId 
#       + " && (!triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ10_2HF_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ15_2HF_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ10_2HF0_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ15_2HF0_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ10_2HF_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ15_2HF_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ10_2HF0_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ15_2HF0_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu7_NHitQ10_2HF_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu7_NHitQ15_2HF_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu7_NHitQ10_2HF0_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu7_NHitQ15_2HF0_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu15_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu15_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu20_v*',1,0).empty()"
#       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu20_v*',1,0).empty()"
#       + ")"
       ),
)

process.oneTag  = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tagMuons"), minNumber = cms.uint32(1))

process.probeMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string("isGlobalMuon"),
)

process.muonDxyPVdzMinID = cms.EDProducer("MuonDxyPVdzmin",
    probes = cms.InputTag("probeMuons"),
    vertexes = cms.InputTag("hiSelectedVertex"),
)

process.tpPairs = cms.EDProducer("CandViewShallowCloneCombiner",
    cut = cms.string('2.5 < mass < 3.5'),
    decay = cms.string('tagMuons@+ probeMuons@-')
)

#process.tnPairsDeltaPhiID = cms.EDProducer("DiMuonDeltaPhi",
#    tagProbePairs = cms.InputTag("tpPairs"),
#)

process.onePair = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairs"), minNumber = cms.uint32(1))

from MuonAnalysis.TagAndProbe.muon.tag_probe_muon_extraIso_cff import ExtraIsolationVariables

from MuonAnalysis.TagAndProbe.puppiIso_cfi import load_fullPFpuppiIsolation
process.fullPuppIsolationSequence = load_fullPFpuppiIsolation(process)
from MuonAnalysis.TagAndProbe.puppiIso_cff import PuppiIsolationVariables
from MuonAnalysis.TagAndProbe.heavyIon_variables_cff import *

process.tpTree = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tpPairs"),
    arbitration   = cms.string("None"),
    # probe variables: all useful ones
    variables = cms.PSet(
        #AllVariables,
        ExtraIsolationVariables,
        PuppiIsolationVariables,
        L1Variables,
        #L1SeedVariables,
        KinematicVariables,
	MuonIDVariables,
	TrackQualityVariables,
	GlobalTrackQualityVariables,
	StaOnlyVariables,
        isoTrk03Abs = cms.InputTag("probeMuonsIsoValueMaps","probeMuonsIsoFromDepsTk"),
        isoTrk03Rel = cms.InputTag("probeMuonsIsoValueMaps","probeMuonsRelIsoFromDepsTk"),
        dxyBS = cms.InputTag("muonDxyPVdzmin","dxyBS"),
        dxyPVdzmin = cms.InputTag("muonDxyPVdzMinID","dxyPVdzmin"),
        dzPV       = cms.InputTag("muonDxyPVdzMinID","dzPV"),
        miniIsoCharged = cms.InputTag("muonMiniIsoCharged","miniIso"),
        activity_miniIsoCharged = cms.InputTag("muonMiniIsoCharged","activity"),
        miniIsoPUCharged = cms.InputTag("muonMiniIsoPUCharged","miniIso"),
        activity_miniIsoPUCharged = cms.InputTag("muonMiniIsoPUCharged","activity"),
        miniIsoNeutrals = cms.InputTag("muonMiniIsoNeutrals","miniIso"),
        activity_miniIsoNeutrals = cms.InputTag("muonMiniIsoNeutrals","activity"),
        miniIsoPhotons = cms.InputTag("muonMiniIsoPhotons","miniIso"),
        activity_miniIsoPhotons = cms.InputTag("muonMiniIsoPhotons","activity"),
        nSplitTk  = cms.InputTag("splitTrackTagger"),
        mt  = cms.InputTag("probeMetMt","mt"),
    ),
    flags = cms.PSet(
       TrackQualityFlags,
       MuonIDFlags,
       #LowPtTriggerFlags,
       #HighPtTriggerFlags,
       #TrigProbeFlags,
       TightHI = cms.string(TightId),
       HybridSoftHI = cms.string(HybridSoftId),
       StaTkSameCharge = cms.string("outerTrack.isNonnull && innerTrack.isNonnull && (outerTrack.charge == innerTrack.charge)"),
       outerValidHits = cms.string("outerTrack.isNonnull && outerTrack.numberOfValidHits > 0"),
    ),
    tagVariables = cms.PSet(
        L1Variables,
        #L1SeedVariables,
        KinematicVariables,
	MuonIDVariables,
	TrackQualityVariables,
	GlobalTrackQualityVariables,
	StaOnlyVariables,
        CentralityVariables,
        nVertices   = cms.InputTag("nverticesModule"),
        isoTrk03Abs = cms.InputTag("probeMuonsIsoValueMaps","probeMuonsIsoFromDepsTk"),
        isoTrk03Rel = cms.InputTag("probeMuonsIsoValueMaps","probeMuonsRelIsoFromDepsTk"),
        dxyBS = cms.InputTag("muonDxyPVdzminTags","dxyBS"),
        dxyPVdzmin = cms.InputTag("muonDxyPVdzminTags","dxyPVdzmin"),
        dzPV = cms.InputTag("muonDxyPVdzminTags","dzPV"),
    ),
    tagFlags = cms.PSet(
        #TrigTagFlags  
    ),
    pairVariables = cms.PSet(
        dz      = cms.string("daughter(0).vz - daughter(1).vz"),
        pt      = cms.string("pt"), 
        rapidity = cms.string("rapidity"),
        #deltaR   = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
        #deltaPhi = cms.InputTag("tnPairsDeltaPhiID","deltaPhi"),
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

process.load("MuonAnalysis.TagAndProbe.muon.tag_probe_muon_extraIso_cfi")
process.load("PhysicsTools.PatAlgos.recoLayer0.pfParticleSelectionForIso_cff")

process.miniIsoSeq = cms.Sequence(
    process.pfParticleSelectionForIsoSequence +
    process.muonMiniIsoCharged +
    process.muonMiniIsoPUCharged +
    process.muonMiniIsoNeutrals +
    process.muonMiniIsoPhotons
)

process.extraProbeVariablesSeq = cms.Sequence(
    process.probeMuonsIsoSequence +
    process.computeCorrectedIso +
    process.splitTrackTagger +
    process.muonDxyPVdzmin +
    process.miniIsoSeq +
    # process.ak4PFCHSJetsL1L2L3 +
    process.fullPuppIsolationSequence
)

process.tnpSimpleSequence = cms.Sequence(
    process.tagMuons +
    process.oneTag     +
    process.probeMuons +
    process.muonDxyPVdzMinID +
    process.tpPairs    +
    process.onePair    +
    #process.tnPairsDeltaPhiID +
    process.extraProbeVariablesSeq +
    process.probeMultiplicities + 
    #process.bestPairByJpsiMass + 
    #process.centralityInfo +
    #process.centralityBinInfo +
    process.tpTree
)

process.tagAndProbe = cms.Path( 
      process.fastFilter
    #* process.centralityBin
    * process.mergedMuons
    * process.patMuonsWithTriggerSequence
    * process.tnpSimpleSequence
)

##    _____               _    _             
##   |_   _| __ __ _  ___| | _(_)_ __   __ _ 
##     | || '__/ _` |/ __| |/ / | '_ \ / _` |
##     | || | | (_| | (__|   <| | | | | (_| |
##     |_||_|  \__,_|\___|_|\_\_|_| |_|\__, |
##                                     |___/ 
#
### Then make another collection for standalone muons, using standalone track to define the 4-momentum
#process.muonsSta = cms.EDProducer("RedefineMuonP4FromTrack",
#    src   = cms.InputTag("muons"),
#    track = cms.string("outer"),
#)
### Match to trigger, to measure the efficiency of HLT tracking
#from PhysicsTools.PatAlgos.tools.helpers import *
#process.patMuonsWithTriggerSequenceSta = cloneProcessingSnippet(process, process.patMuonsWithTriggerSequence, "Sta")
#process.muonMatchHLTL2Sta.maxDeltaR = 0.5
#process.muonMatchHLTL3Sta.maxDeltaR = 0.5
#massSearchReplaceAnyInputTag(process.patMuonsWithTriggerSequenceSta, "mergedMuons", "muonsSta")
#
### Define probes and T&P pairs
#process.probeMuonsSta = cms.EDFilter("PATMuonSelector",
#    src = cms.InputTag("patMuonsWithTriggerSta"),
#    cut = cms.string("outerTrack.isNonnull"), # no real cut now
#)
#
#process.tpPairsSta = process.tpPairs.clone(decay = "tagMuons@+ probeMuonsSta@-", cut = '1. < mass < 6.')
#
#process.tnPairsDeltaPhiSta = cms.EDProducer("DiMuonDeltaPhi",
#    tagProbePairs = cms.InputTag("tpPairsSta"),
#)
#
#process.onePairSta = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairsSta"), minNumber = cms.uint32(1))
#
#process.pCutTracks.src = cms.InputTag("hiGeneralTracks")
#process.staToTkMatch.maxDeltaR     = 0.3
#process.staToTkMatch.maxDeltaPtRel = 2.
#process.staToTkMatchNoJPsi.maxDeltaR     = 0.3
#process.staToTkMatchNoJPsi.maxDeltaPtRel = 2.
#
#process.load("MuonAnalysis.TagAndProbe.tracking_reco_info_cff")
#
#process.tpTreeSta = process.tpTree.clone(
#    tagProbePairs = "tpPairsSta",
#    arbitration   = "OneProbe",
#    variables = cms.PSet(
#        KinematicVariables, 
#        StaOnlyVariables,
#        ## track matching variables
#        tk_deltaR     = cms.InputTag("staToTkMatch","deltaR"),
#        tk_deltaEta   = cms.InputTag("staToTkMatch","deltaEta"),
#        tk_deltaR_NoJPsi   = cms.InputTag("staToTkMatchNoJPsi","deltaR"),
#        tk_deltaEta_NoJPsi = cms.InputTag("staToTkMatchNoJPsi","deltaEta"),
#    ),
#    flags = cms.PSet(
#        outerValidHits = cms.string("outerTrack.isNonnull && outerTrack.numberOfValidHits > 0"),
#        TM  = cms.string("isTrackerMuon"),
#        Glb = cms.string("isGlobalMuon"),
#        Tk  = cms.string("track.isNonnull"),
#        isNonHIRegit = cms.string("innerTrack.isNonnull && innerTrack.originalAlgo<37"), #   hiRegitMuInitialStep = 37
#        StaTkSameCharge = cms.string("outerTrack.isNonnull && innerTrack.isNonnull && (outerTrack.charge == innerTrack.charge)"),
#    ),
#    tagVariables = cms.PSet(
#        CentralityVariables,
#        pt = cms.string("pt"),
#        eta = cms.string("eta"),
#        phi = cms.string("phi"),
#    ),
#    tagFlags = cms.PSet(
#        TrigTagFlags
#    ),
#    pairVariables = cms.PSet(
#        dz      = cms.string("daughter(0).vz - daughter(1).vz"),
#        pt      = cms.string("pt"), 
#        rapidity = cms.string("rapidity"),
#        deltaR   = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
#        deltaPhi = cms.InputTag("tnPairsDeltaPhiSta","deltaPhi"),
#    ),
#    pairFlags = cms.PSet(),
#    allProbes = cms.InputTag("probeMuonsSta")
#)
#
#process.tnpSimpleSequenceSta = cms.Sequence(
#    process.tagMuons +
#    process.oneTag     +
#    process.probeMuonsSta   +
#    process.tpPairsSta      +
#    process.onePairSta      +
#    process.tnPairsDeltaPhiSta +
#    process.staToTkMatchSequenceJPsi +
#    process.centralityInfo +
#    process.centralityBinInfo +
#    process.tpTreeSta
#)
#
#process.tagAndProbeSta = cms.Path( 
#      process.fastFilter
#    * process.centralityBin
#    * process.muonsSta
#    * process.patMuonsWithTriggerSequenceSta
#    * process.tnpSimpleSequenceSta
#)
#
#
##--------------------------------------------------------------------
###    ____                   _____               _      ____            _               
###   | __ )  __ _ _ __ ___  |_   _| __ __ _  ___| | __ |  _ \ _ __ ___ | |__   ___  ___ 
###   |  _ \ / _` | '__/ _ \   | || '__/ _` |/ __| |/ / | |_) | '__/ _ \| '_ \ / _ \/ __|
###   | |_) | (_| | | |  __/   | || | | (_| | (__|   <  |  __/| | | (_) | |_) |  __/\__ \
###   |____/ \__,_|_|  \___|   |_||_|  \__,_|\___|_|\_\ |_|   |_|  \___/|_.__/ \___||___/
###                                                                                      
###   
#
#process.probeMuonsTrk = cms.EDFilter("PATMuonSelector",
#    src = cms.InputTag("patMuonsWithTrigger"),
#    cut = cms.string(TRACK_CUTS + ' && ' + InAcceptance + ' && ' + 'innerTrack.isNonnull && innerTrack.originalAlgo<37'), #   hiRegitMuInitialStep = 37              
#)
#
#process.muonDxyPVdzMinTrk = cms.EDProducer("MuonDxyPVdzmin",
#    probes = cms.InputTag("probeMuonsTrk"),
#    vertexes = cms.InputTag("hiSelectedVertex"),
#)
#
#process.tpPairsTrk = cms.EDProducer("CandViewShallowCloneCombiner",
#    cut = cms.string('2.5 < mass < 3.5'),
#    decay = cms.string('tagMuons@+ probeMuonsTrk@-')
#)
#
#process.tnPairsDeltaPhiTrk = cms.EDProducer("DiMuonDeltaPhi",
#    tagProbePairs = cms.InputTag("tpPairsTrk"),
#)
#
#process.onePairTrk = cms.EDFilter("CandViewCountFilter",
#     src = cms.InputTag('tpPairsTrk'),
#     minNumber = cms.uint32(1),
#)
#
#process.tpTreeTrk = cms.EDAnalyzer("TagProbeFitTreeProducer",
#     # choice of tag and probe pairs, and arbitration
#     tagProbePairs = cms.InputTag("tpPairsTrk"),
#     arbitration   = cms.string("OneProbe"),
#     # probe variables: all useful ones
#     variables = cms.PSet(
#        KinematicVariables,
#        StaOnlyVariables,
#        dxyPVdzmin = cms.InputTag("muonDxyPVdzMinTrk","dxyPVdzmin"),
#        dzPV       = cms.InputTag("muonDxyPVdzMinTrk","dzPV"),
#     ),
#     flags = cms.PSet(
#        isSTA = cms.string("isStandAloneMuon"),
#        outerValidHits  = cms.string("? outerTrack.isNull() ? 0 : outerTrack.numberOfValidHits > 0"),
#     ),
#     tagVariables = cms.PSet(
#        TrackQualityVariables,
#        GlobalTrackQualityVariables,
#        CentralityVariables,
#        pt  = cms.string("pt"),
#        eta = cms.string("eta"),
#        abseta = cms.string("abs(eta)"),
#        l2dr  = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() ? 999 : "+
#                           " deltaR( eta, phi, " +
#                           "         triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).eta, "+
#                           "         triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).phi ) "),
#
#     ),
#     tagFlags     = cms.PSet(
#        TrigTagFlags,
#     ),
#     pairVariables = cms.PSet(
#        pt  = cms.string("pt"),
#        y = cms.string("rapidity"),
#        absy = cms.string("abs(rapidity)"),
#        deltaR   = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
#        deltaPhi = cms.InputTag("tnPairsDeltaPhiTrk","deltaPhi"),
#     ),
#     pairFlags = cms.PSet(),
#     isMC           = cms.bool(False),
#     #addRunLumiInfo = cms.bool(True),
#     allProbes     = cms.InputTag("probeMuonsTrk")
#)
#
#process.tnpSimpleSequenceTrk = cms.Sequence(
#    process.probeMuonsTrk +
#    process.muonDxyPVdzMinTrk +
#    process.tpPairsTrk    +
#    process.onePairTrk +
#    process.tnPairsDeltaPhiTrk +
#    process.centralityInfo +
#    process.centralityBinInfo +
#    process.tpTreeTrk
#)
#
#process.tagAndProbeTrk = cms.Path(
#      process.fastFilter
#    * process.centralityBin
#    * process.tnpSimpleSequenceTrk
#)

process.RandomNumberGeneratorService.tkTracksNoJPsi = cms.PSet( initialSeed = cms.untracked.uint32(81) )
process.RandomNumberGeneratorService.tkTracksNoBestJPsi = cms.PSet( initialSeed = cms.untracked.uint32(81) )

process.schedule = cms.Schedule(
   process.tagAndProbe, 
#   process.tagAndProbeSta,
#   process.tagAndProbeTrk,
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("tnpJPsi_Data_PbPb_AOD.root"))
