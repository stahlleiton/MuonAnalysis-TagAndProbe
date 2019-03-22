import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(),
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) ) 

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

# process.Tracer = cms.Service('Tracer')
import os
if "CMSSW_7_6_" in os.environ['CMSSW_VERSION']:
    process.GlobalTag.globaltag = cms.string('76X_dataRun2_v15')
    process.source.fileNames = [
        '/store/data/Run2015D/Charmonium/AOD/16Dec2015-v1/50000/0013A0EA-94AE-E511-9B84-001E67398683.root',
        '/store/data/Run2015D/Charmonium/AOD/16Dec2015-v1/50000/02A9F67F-A2AE-E511-939A-0CC47A4C8EB6.root',
        '/store/data/Run2015D/Charmonium/AOD/16Dec2015-v1/50000/02D39573-BDAE-E511-AF22-00266CF9AF00.root',
        '/store/data/Run2015D/Charmonium/AOD/16Dec2015-v1/50000/0639B2A3-A7AE-E511-887E-A0000420FE80.root',
        '/store/data/Run2015D/Charmonium/AOD/16Dec2015-v1/50000/06C00544-AAAE-E511-831D-00A0D1EE2BBC.root',
        '/store/data/Run2015D/Charmonium/AOD/16Dec2015-v1/50000/06DCCB30-C7AE-E511-A318-0025905A6092.root',
        '/store/data/Run2015D/Charmonium/AOD/16Dec2015-v1/50000/0ADF8F02-94AE-E511-96F0-549F358EB72E.root',
        '/store/data/Run2015D/Charmonium/AOD/16Dec2015-v1/50000/0C78D007-95AE-E511-87A9-0CC47A4DEDCA.root',
        '/store/data/Run2015D/Charmonium/AOD/16Dec2015-v1/50000/10438105-95AE-E511-ADCD-0090FAA59634.root',
        '/store/data/Run2015D/Charmonium/AOD/16Dec2015-v1/50000/1077A155-AAAE-E511-A1C7-0CC47A4DEF3E.root',
    ]
elif "CMSSW_8_0_" in os.environ['CMSSW_VERSION']:
    process.GlobalTag.globaltag = cms.string('80X_dataRun2_2016SeptRepro_v4')
    process.source.fileNames = [
        '/store/data/Run2016G/Charmonium/AOD/23Sep2016-v1/100000/0006BA63-7097-E611-BBE8-001E67E71412.root',
        '/store/data/Run2016G/Charmonium/AOD/23Sep2016-v1/100000/0018FFBA-5B94-E611-AD99-008CFAFBF52E.root',
        '/store/data/Run2016G/Charmonium/AOD/23Sep2016-v1/100000/003343EB-7496-E611-B5EC-848F69FD2997.root',
        '/store/data/Run2016G/Charmonium/AOD/23Sep2016-v1/100000/0060EAA8-9197-E611-9D75-001E67E59BE3.root',
        '/store/data/Run2016G/Charmonium/AOD/23Sep2016-v1/100000/00E2CD87-9798-E611-8CA4-848F69FD4598.root',
        '/store/data/Run2016G/Charmonium/AOD/23Sep2016-v1/100000/020BB297-5B97-E611-82B5-848F69FD4541.root',
        '/store/data/Run2016G/Charmonium/AOD/23Sep2016-v1/100000/04CA2B1A-0897-E611-A716-0025907FD242.root',
        '/store/data/Run2016G/Charmonium/AOD/23Sep2016-v1/100000/06069075-3C97-E611-92D8-008CFA00018C.root',
        '/store/data/Run2016G/Charmonium/AOD/23Sep2016-v1/100000/061698EB-E096-E611-840C-848F69FD3EC9.root',
        '/store/data/Run2016G/Charmonium/AOD/23Sep2016-v1/100000/062B282E-8097-E611-9710-001E67E6F86E.root',
    ]
    #process.source.fileNames = [ 'file:/tmp/gpetrucc/0006BA63-7097-E611-BBE8-001E67E71412.root' ]
    import FWCore.PythonUtilities.LumiList as LumiList
    json = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
    process.source.lumisToProcess = LumiList.LumiList(filename = json).getVLuminosityBlockRange()
elif "CMSSW_9_4_" in os.environ['CMSSW_VERSION']:
    process.GlobalTag.globaltag = cms.string('94X_dataRun2_Prompt_v2')
    process.source.fileNames = [
        'file:pp5TeV2017_testfile3.root'#'/store/data/Run2017G/SingleMuon/AOD/17Nov2017-v1/910000/E4B056C8-3031-E811-9D14-001E67E6F490.root'
    ]
    #process.source.fileNames = [ 'file:/tmp/gpetrucc/0006BA63-7097-E611-BBE8-001E67E71412.root' ]
    import FWCore.PythonUtilities.LumiList as LumiList
    json = '/home/llr/cms/falmagne/TnP/CMSSW_9_4_10/src/MuonAnalysis/TagAndProbe/test/Cert_306546-306826_5TeV_EOY2017ReReco_Collisions17_JSON_MuonPhys.txt'#'/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/5TeV/ReReco/Cert_306546-306826_5TeV_EOY2017ReReco_Collisions17_JSON_MuonPhys.txt'
    process.source.lumisToProcess = LumiList.LumiList(filename = json).getVLuminosityBlockRange()

else: raise RuntimeError, "Unknown CMSSW version %s" % os.environ['CMSSW_VERSION']

#InTMAcceptance = '((abs(eta)<1.2 && pt>=3.3) || (1.2<=abs(eta) && abs(eta)<2.1 && pt>=4-1.1*abs(eta)) || (2.1<=abs(eta) && abs(eta)<2.4 && pt>=1.3))' ##HIN-16-015 pPb tracker muon acceptance cuts
InLooseAcceptance = '((abs(eta)<0.3 && pt>=3.4) || (0.3<=abs(eta) && abs(eta)<1.1 && pt>=3.3) || (1.1<=abs(eta) && abs(eta)<1.4 && pt>=7.7-4.0*abs(eta)) || (1.4<=abs(eta) && abs(eta)<1.55 && pt>=2.1) || (1.55<=abs(eta) && abs(eta)<2.2 && pt>=4.25-1.39*abs(eta)) || (2.2<=abs(eta) && abs(eta)<2.4 && pt>=1.2))'
InTightAcceptance = '((abs(eta)<1.2 && pt>=3.5) || (1.2<=abs(eta) && abs(eta)<2.1 && pt>=5.47-1.89*abs(eta)) || (2.1<=abs(eta) && abs(eta)<2.4 && pt>=1.5))'

## ==== Fast Filters ====
process.goodVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && tracksSize >= 2 && abs(z) <= 25 && position.Rho <= 2"),
    filter = cms.bool(True),
)
process.noScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False), ## Or 'True' to get some per-event info
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)
process.fastFilter = cms.Sequence(process.goodVertexFilter + process.noScraping)

process.load("HLTrigger.HLTfilters.triggerResultsFilter_cfi")
process.triggerResultsFilter.triggerConditions = cms.vstring( 'HLT_HI*Mu*' ) #'HLT_Mu*_L2Mu*'
process.triggerResultsFilter.l1tResults = ''
process.triggerResultsFilter.throw = True
process.triggerResultsFilter.hltResults = cms.InputTag( "TriggerResults", "", "HLT" )
process.HLTMu   = process.triggerResultsFilter.clone(triggerConditions = [ 'HLT_HI*Mu*' ])
process.HLTBoth = process.triggerResultsFilter.clone(triggerConditions = [ 'HLT_HI*Mu*', 'HLT_HI*Mu*_Track*_Jpsi*' ])

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
    muonsCut     = cms.string(InLooseAcceptance + " && track.isNonnull"),
    caloMuonsCut = cms.string(InLooseAcceptance),
    tracksCut    = cms.string(InLooseAcceptance),
)

## ==== Trigger matching
process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")
## with some customization
from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import *
changeRecoMuonInput(process, "mergedMuons")
useL1Stage2Candidates(process)
appendL1MatchingAlgo(process)
switchOffAmbiguityResolution(process) # Switch off ambiguity resolution: allow multiple reco muons to match to the same trigger muon     
addHLTL1Passthrough(process)

#process.patTrigger.collections.append("hltL3MuonCandidates")
#process.muonMatchHLTL3.matchedCuts = cms.string('coll("hltL3MuonCandidates")')

process.patTrigger.collections.append("hltGtStage2Digis")
process.muonMatchHLTL1.matchedCuts = cms.string('coll("hltGtStage2Digis:Muon")')
process.muonMatchHLTL1.useMB2InOverlap = cms.bool(True)
process.muonMatchHLTL1.useStage2L1 = cms.bool(True)
process.muonMatchHLTL1.preselection = cms.string("")

## ==== Tag and probe definitions        
from MuonAnalysis.TagAndProbe.common_variables_cff import *
process.load("MuonAnalysis.TagAndProbe.common_modules_cff")

TightId =  "isGlobalMuon && globalTrack.normalizedChi2 < 10 && globalTrack.hitPattern.numberOfValidMuonHits > 0 && numberOfMatchedStations > 1 && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0 && abs(dB) < 0.2"

SoftId = "muonID('TMOneStationTight') && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0"

HybridSoftId = "isTrackerMuon && isGlobalMuon && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0"#&& muonID('TMOneStationTight') ---> removed

HighPtTriggerFlags = cms.PSet(
   HIL2Mu5_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ10_v*',1,0).empty()"),
   HIL3Mu5_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ10_v*',1,0).empty()"),   
   HIL2Mu12 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu12_v*',1,0).empty()"),
   HIL3Mu12 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu12_v*',1,0).empty()"),   
   HIL2Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu15_v*',1,0).empty()"),
   HIL3Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu15_v*',1,0).empty()"),   
   HIL2Mu20 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu20_v*',1,0).empty()"),
   HIL3Mu20 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu20_v*',1,0).empty()"),
)

LowPtTriggerFlags = cms.PSet(
   HIL2Mu3_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ10_v*',1,0).empty()"),
   HIL3Mu3_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ10_v*',1,0).empty()"),
)

TRACK_CUTS = "track.isNonnull && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0"

TrigTagFlags = cms.PSet(HighPtTriggerFlags, LowPtTriggerFlags)

TrigProbeFlags = cms.PSet(
      HLTL2_DoubleMu0_v0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2DoubleMu0_v*',1,0).empty()"),
      #HLTL2_DoubleMu0_v1 = cms.string("!triggerObjectMatchesByFilter('hltL2fL1sDoubleMu0L1f0L2Filtered0').empty()"),
      HLTL3_DoubleMu0_v0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3DoubleMu0_v*',1,0).empty()"),
      #HLTL3_DoubleMu0_v1 = cms.string("!triggerObjectMatchesByFilter('hltL3fL1sDoubleMu0L1f0L2f0L3Filtered0').empty()"),
      HLTL1_DoubleMuOpen_v0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL1DoubleMuOpen_v*',1,0).empty()"),
      HLTL1_DoubleMu0_v0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL1DoubleMu0_v*',1,0).empty()"),
      #HLTL1_DoubleMu0_v1 = cms.string("!triggerObjectMatchesByFilter('hltL1fL1sDoubleMu0L1Filtered0').empty()"),
      HLTL1_DoubleMu0_v2 = cms.string("(!triggerObjectMatchesByPath('HLT_HIL1DoubleMu0_v*',1,0).empty() && !triggerObjectMatchesByFilter('hltL1fL1sDoubleMu0L1Filtered0').empty())"),
      )

process.tagMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(InTightAcceptance + ' && ' +  HybridSoftId 
                     + " && (!triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ10_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ10_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ10_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ10_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu12_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu15_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu15_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu20_v*',1,0).empty()"
                     + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu20_v*',1,0).empty()"
                     + ")"
                     #" && !triggerObjectMatchesByCollection('hltHIL3MuonCandidates').empty()"),
                     ),
)

process.oneTag  = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tagMuons"), minNumber = cms.uint32(1))

process.probeMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string("isTrackerMuon")#("track.isNonnull && (!triggerObjectMatchesByCollection('hltTracksIter').empty() || !triggerObjectMatchesByCollection('hltMuTrackJpsiEffCtfTrackCands').empty() || !triggerObjectMatchesByCollection('hltMuTrackJpsiCtfTrackCands').empty() || !triggerObjectMatchesByCollection('hltL2MuonCandidates').empty())")
)

process.muonDxyPVdzMinID = cms.EDProducer("MuonDxyPVdzmin",
    probes = cms.InputTag("probeMuons"),
)

process.tpPairs = cms.EDProducer("CandViewShallowCloneCombiner",
    cut = cms.string('2.5 < mass < 3.5'),
    decay = cms.string('tagMuons@+ probeMuons@-')
)

#process.tnPairsDeltaPhiID = cms.EDProducer("DiMuonDeltaPhi",
#                                           tagProbePairs = cms.InputTag("tpPairs")
#)

process.onePair = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairs"), minNumber = cms.uint32(1))

#from MuonAnalysis.TagAndProbe.muon.tag_probe_muon_extraIso_cff import ExtraIsolationVariables

process.tpTree = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tpPairs"),
    arbitration   = cms.string("None"),
    # probe variables: all useful ones
    variables = cms.PSet(
        KinematicVariables,
        MuonIDVariables,
        #TrackQualityVariables,
        GlobalTrackQualityVariables,
        #StaOnlyVariables,
        #AllVariables,
        #ExtraIsolationVariables,
        #dxyBS      = cms.InputTag("muonDxyPVdzmin","dxyBS"),
        dxyPVdzmin = cms.InputTag("muonDxyPVdzmin","dxyPVdzmin"),
        dzPV       = cms.InputTag("muonDxyPVdzmin","dzPV"),
        #dxyzPVCuts       = cms.InputTag("muonDxyPVdzmin","dxyzPVCuts"),
        #nSplitTk   = cms.InputTag("splitTrackTagger"),
    ),
    flags = cms.PSet(
       TrackQualityFlags,
       MuonIDFlags,
       LowPtTriggerFlags,
       HighPtTriggerFlags,
       TrigProbeFlags,
       #HighPtTriggerFlagsDebug,
       #LowPtTriggerFlagsPhysics,
       #LowPtTriggerFlagsEfficienciesProbe,
       TightHI = cms.string(TightId),
       InTightAcceptance = cms.string(InTightAcceptance),
       HybridSoftHI = cms.string(HybridSoftId),
       SoftIDWithoutDxyz = cms.string(SoftId),
       #StaTkSameCharge = cms.string("outerTrack.isNonnull && innerTrack.isNonnull && (outerTrack.charge == innerTrack.charge)"),
       #outerValidHits = cms.string("outerTrack.isNonnull && outerTrack.numberOfValidHits > 0"),
    ),
    tagVariables = cms.PSet(
        #pt  = cms.string('pt'),
        #eta = cms.string('eta'),
        #phi = cms.string('phi'),
        KinematicVariables,
        MuonIDVariables,
        TrackQualityVariables,
        GlobalTrackQualityVariables,
        #StaOnlyVariables,
        nVertices = cms.InputTag("nverticesModule"),
        l1rate = cms.InputTag("l1rate"),
        bx     = cms.InputTag("l1rate","bx"),
        instLumi = cms.InputTag("addEventInfo", "instLumi"),
    ),
    tagFlags     = cms.PSet(
        TrigTagFlags,
        #HighPtTriggerFlags,
        #HighPtTriggerFlagsDebug,
        #LowPtTriggerFlagsPhysics,
        #LowPtTriggerFlagsEfficienciesTag,
    ),
    pairVariables = cms.PSet(
        dz            = cms.string("daughter(0).vz - daughter(1).vz"),
        pt            = cms.string("pt"),
        rapidity      = cms.string("rapidity"),
        deltaR        = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
        #deltaPhi      = cms.InputTag("tnPairsDeltaPhiID","deltaPhi"),
        #dphiVtxTimesQ = cms.InputTag("tagProbeSeparation", "dphiVtxTimesQ"),
        #drM1          = cms.InputTag("tagProbeSeparation", "drM1"),
        #dphiM1        = cms.InputTag("tagProbeSeparation", "dphiM1"),
        #distM1        = cms.InputTag("tagProbeSeparation", "distM1"),
        #drM2          = cms.InputTag("tagProbeSeparation", "drM2"),
        #dphiM2        = cms.InputTag("tagProbeSeparation", "dphiM2"),
        #distM2        = cms.InputTag("tagProbeSeparation", "distM2"),
        #drVtx         = cms.InputTag("tagProbeSeparation", "drVtx"),
        probeMultiplicity = cms.InputTag("probeMultiplicity"),
        #probeMultiplicity_TMGM = cms.InputTag("probeMultiplicityTMGM"),
    ),
    pairFlags = cms.PSet(),
    isMC           = cms.bool(False),
    addRunLumiInfo = cms.bool(True),
    allProbes      = cms.InputTag("probeMuons")
)

#process.load("MuonAnalysis.TagAndProbe.muon.tag_probe_muon_extraIso_cfi")

process.tnpSimpleSequence = cms.Sequence(
    process.tagMuons +
    process.oneTag     +
    process.probeMuons +
    process.tpPairs    +
    process.onePair    +
    process.muonDxyPVdzmin +
    process.nverticesModule +
    #process.tagProbeSeparation +
    #process.computeCorrectedIso + 
    process.probeMultiplicity + 
    process.splitTrackTagger +
    process.addEventInfo +
    process.l1rate +
    process.tpTree
)

process.tagAndProbe = cms.Path( 
    #process.HLTBoth    +
    process.fastFilter +
    process.mergedMuons                 *
    process.patMuonsWithTriggerSequence *
    process.tnpSimpleSequence
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
process.muonMatchHLTL2Sta.maxDeltaR = 0.5
process.muonMatchHLTL3Sta.maxDeltaR = 0.5
massSearchReplaceAnyInputTag(process.patMuonsWithTriggerSequenceSta, "mergedMuons", "muonsSta")

## Define probes and T&P pairs
process.probeMuonsSta = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTriggerSta"),
    cut = cms.string("outerTrack.isNonnull") #&& !triggerObjectMatchesByCollection('hltHIL2MuonCandidates').empty()"), 
)

process.tpPairsSta = process.tpPairs.clone(decay = "tagMuons@+ probeMuonsSta@-", cut = "2 < mass < 5")

process.onePairSta = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairsSta"), minNumber = cms.uint32(1))

process.staToTkMatch.maxDeltaR     = 0.3
process.staToTkMatch.maxDeltaPtRel = 2.
process.staToTkMatchNoJPsi.maxDeltaR     = 0.3
process.staToTkMatchNoJPsi.maxDeltaPtRel = 2.

process.load("MuonAnalysis.TagAndProbe.tracking_reco_info_cff")

process.tpTreeSta = process.tpTree.clone(
    tagProbePairs = "tpPairsSta",
    arbitration   = "OneProbe",
    variables = cms.PSet(
        KinematicVariables, 
        StaOnlyVariables,
        ## track matching variables
        tk_deltaR     = cms.InputTag("staToTkMatch","deltaR"),
        tk_deltaEta   = cms.InputTag("staToTkMatch","deltaEta"),
        tk_deltaR_NoJPsi     = cms.InputTag("staToTkMatchNoJPsi","deltaR"),
        tk_deltaEta_NoJPsi   = cms.InputTag("staToTkMatchNoJPsi","deltaEta"),
        tk_deltaR_NoBestJPsi     = cms.InputTag("staToTkMatchNoBestJPsi","deltaR"),
        tk_deltaEta_NoBestJPsi   = cms.InputTag("staToTkMatchNoBestJPsi","deltaEta"),
    ),
    flags = cms.PSet(
        LowPtTriggerFlagsEfficienciesProbe,
        TrigProbeFlags,
        outerValidHits = cms.string("outerTrack.numberOfValidHits > 0"),
        TM  = cms.string("isTrackerMuon"),
        Glb = cms.string("isGlobalMuon"),
        Tk  = cms.string("track.isNonnull"),
        InTightAcceptance = cms.string(InTightAcceptance),
        isNonMuonSeeded = cms.string("innerTrack.isNonnull && innerTrack.originalAlgo<13"), #   muonSeededStepInOut = 13
        StaTkSameCharge = cms.string("outerTrack.isNonnull && innerTrack.isNonnull && (outerTrack.charge == innerTrack.charge)"),
    ),
    tagVariables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        phi = cms.string("phi"),
        nVertices = cms.InputTag("nverticesModule"),
        #combRelIso = cms.string("(isolationR03.emEt + isolationR03.hadEt + isolationR03.sumPt)/pt"),
        #chargedHadIso04 = cms.string("pfIsolationR04().sumChargedHadronPt"),
        #neutralHadIso04 = cms.string("pfIsolationR04().sumNeutralHadronEt"),
        #photonIso04 = cms.string("pfIsolationR04().sumPhotonEt"),
        #combRelIsoPF04dBeta = IsolationVariables.combRelIsoPF04dBeta,
    ),
    tagFlags = cms.PSet(
        TrigTagFlags,
        LowPtTriggerFlagsEfficienciesTag,
        LowPtTriggerFlagsEfficienciesProbe,
    ),
    pairVariables = cms.PSet(
        dz      = cms.string("daughter(0).vz - daughter(1).vz"),
        pt      = cms.string("pt"),
        rapidity = cms.string("rapidity"),
        deltaR   = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
        #deltaPhi = cms.InputTag("tnPairsDeltaPhiSta","deltaPhi"),
    ),
    pairFlags     = cms.PSet(),
    allProbes     = cms.InputTag("probeMuonsSta")
)

process.tnpSimpleSequenceSta = cms.Sequence(
    process.tagMuons +
    process.oneTag     +
    process.probeMuonsSta +
    process.tpPairsSta      +
    process.onePairSta      +
    process.nverticesModule +
    process.staToTkMatchSequenceJPsi +
    process.addEventInfo +
    process.l1rate +
    process.tpTreeSta
)

## Add extra RECO-level info
if False:
    process.tnpSimpleSequenceSta.replace(process.tpTreeSta, process.tkClusterInfo+process.tpTreeSta)
    process.tpTreeSta.tagVariables.nClustersStrip = cms.InputTag("tkClusterInfo","siStripClusterCount")
    process.tpTreeSta.tagVariables.nClustersPixel = cms.InputTag("tkClusterInfo","siPixelClusterCount")
    process.tnpSimpleSequenceSta.replace(process.tpTreeSta, process.tkLogErrors+process.tpTreeSta)
    process.tpTreeSta.tagVariables.nLogErrFirst = cms.InputTag("tkLogErrors","firstStep")
    process.tpTreeSta.tagVariables.nLogErrPix   = cms.InputTag("tkLogErrors","pixelSteps")
    process.tpTreeSta.tagVariables.nLogErrAny   = cms.InputTag("tkLogErrors","anyStep")

if False: # turn on for tracking efficiency from RECO/AOD + earlyGeneralTracks
    process.tracksNoMuonSeeded = cms.EDFilter("TrackSelector",
      src = cms.InputTag("generalTracks"),
      cut = cms.string(" || ".join("isAlgoInMask('%s')" % a for a in [
                    'initialStep', 'lowPtTripletStep', 'pixelPairStep', 'detachedTripletStep',
                    'mixedTripletStep', 'pixelLessStep', 'tobTecStep', 'jetCoreRegionalStep' ] ) )
    )
    process.pCutTracks0 = process.pCutTracks.clone(src = 'tracksNoMuonSeeded')
    process.tkTracks0 = process.tkTracks.clone(src = 'pCutTracks0')
    process.tkTracksNoJPsi0 = process.tkTracksNoJPsi.clone(src = 'tkTracks0')
    process.tkTracksNoBestJPsi0 = process.tkTracksNoBestJPsi.clone(src = 'tkTracks0')
    process.preTkMatchSequenceJPsi.replace(
            process.tkTracksNoJPsi, process.tkTracksNoJPsi +
            process.tracksNoMuonSeeded + process.pCutTracks0 + process.tkTracks0 + process.tkTracksNoJPsi0 +process.tkTracksNoBestJPsi0
    )
    process.staToTkMatch0 = process.staToTkMatch.clone(matched = 'tkTracks0')
    process.staToTkMatchNoJPsi0 = process.staToTkMatchNoJPsi.clone(matched = 'tkTracksNoJPsi0')
    process.staToTkMatchNoBestJPsi0 = process.staToTkMatchNoBestJPsi.clone(matched = 'tkTracksNoJPsi0')
    process.staToTkMatchSequenceJPsi.replace( process.staToTkMatch, process.staToTkMatch + process.staToTkMatch0 )
    process.staToTkMatchSequenceJPsi.replace( process.staToTkMatchNoJPsi, process.staToTkMatchNoJPsi + process.staToTkMatchNoJPsi0 )
    process.staToTkMatchSequenceJPsi.replace( process.staToTkMatchNoBestJPsi, process.staToTkMatchNoBestJPsi + process.staToTkMatchNoBestJPsi0 )
    process.tpTreeSta.variables.tk0_deltaR     = cms.InputTag("staToTkMatch0","deltaR")
    process.tpTreeSta.variables.tk0_deltaEta   = cms.InputTag("staToTkMatch0","deltaEta")
    process.tpTreeSta.variables.tk0_deltaR_NoJPsi   = cms.InputTag("staToTkMatchNoJPsi0","deltaR")
    process.tpTreeSta.variables.tk0_deltaEta_NoJPsi = cms.InputTag("staToTkMatchNoJPsi0","deltaEta")
    process.tpTreeSta.variables.tk0_deltaR_NoBestJPsi   = cms.InputTag("staToTkMatchNoBestJPsi0","deltaR")
    process.tpTreeSta.variables.tk0_deltaEta_NoBestJPsi = cms.InputTag("staToTkMatchNoBestJPsi0","deltaEta")

process.tagAndProbeSta = cms.Path( 
    #process.HLTMu      +
    process.fastFilter +
    process.muonsSta                       +
    process.patMuonsWithTriggerSequenceSta +
    process.tnpSimpleSequenceSta
)



if False: # turn on for tracking efficiency using L1 seeds
    process.probeL1 = cms.EDFilter("CandViewSelector",
        src = cms.InputTag("l1extraParticles"),
        cut = cms.string("pt >= 2 && abs(eta) < 2.4"),
    )
    process.tpPairsTkL1 = process.tpPairs.clone(decay = "tagMuons@+ probeL1@-", cut = 'mass > 2')
    process.l1ToTkMatch    = process.staToTkMatch.clone(src = "probeL1", srcTrack="none")
    process.l1ToTkMatchNoJPsi = process.staToTkMatchNoJPsi.clone(src = "probeL1", srcTrack="none")
    process.l1ToTkMatchNoBestJPsi = process.staToTkMatchNoBestJPsi.clone(src = "probeL1", srcTrack="none")
    process.l1ToTkMatch0    = process.staToTkMatch0.clone(src = "probeL1", srcTrack="none")
    process.l1ToTkMatchNoJPsi0 = process.staToTkMatchNoJPsi0.clone(src = "probeL1", srcTrack="none")
    process.l1ToTkMatchNoBestJPsi0 = process.staToTkMatchNoBestJPsi0.clone(src = "probeL1", srcTrack="none")
    process.tpTreeL1 = process.tpTreeSta.clone(
        tagProbePairs = "tpPairsTkL1",
        arbitration   = "OneProbe",
        variables = cms.PSet(
            KinematicVariables,
            bx = cms.string("bx"),
            quality = cms.string("gmtMuonCand.quality"),
            ## track matching variables
            tk_deltaR     = cms.InputTag("l1ToTkMatch","deltaR"),
            tk_deltaEta   = cms.InputTag("l1ToTkMatch","deltaEta"),
            tk_deltaR_NoJPsi   = cms.InputTag("l1ToTkMatchNoJPsi","deltaR"),
            tk_deltaEta_NoJPsi = cms.InputTag("l1ToTkMatchNoJPsi","deltaEta"),
            tk_deltaR_NoBestJPsi   = cms.InputTag("l1ToTkMatchNoBestJPsi","deltaR"),
            tk_deltaEta_NoBestJPsi = cms.InputTag("l1ToTkMatchNoBestJPsi","deltaEta"),
            ## track matching variables (early general tracks)
            tk0_deltaR     = cms.InputTag("l1ToTkMatch0","deltaR"),
            tk0_deltaEta   = cms.InputTag("l1ToTkMatch0","deltaEta"),
            tk0_deltaR_NoJPsi   = cms.InputTag("l1ToTkMatchNoJPsi0","deltaR"),
            tk0_deltaEta_NoJPsi = cms.InputTag("l1ToTkMatchNoJPsi0","deltaEta"),
            tk0_deltaR_NoBestJPsi   = cms.InputTag("l1ToTkMatchNoBestJPsi0","deltaR"),
            tk0_deltaEta_NoBestJPsi = cms.InputTag("l1ToTkMatchNoBestJPsi0","deltaEta"),
        ),
        flags = cms.PSet(
            TrigProbeFlags
        ),
        tagVariables = cms.PSet(
            pt = cms.string("pt"),
            eta = cms.string("eta"),
            phi = cms.string("phi"),
            nVertices   = cms.InputTag("nverticesModule"),
        ),
        pairVariables = cms.PSet(
            #nJets30 = cms.InputTag("njets30ModuleSta"),
            pt      = cms.string("pt"),
            rapidity = cms.string("rapidity"),
            deltaR   = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
        ),
        pairFlags = cms.PSet(),
        allProbes     = cms.InputTag("probeL1"),
    )
    process.tagAndProbeTkL1 = cms.Path(
        #process.HLTMu + 
        process.fastFilter +
        process.probeL1 +
        process.tpPairsTkL1 +
        process.preTkMatchSequenceJPsi +
        process.l1ToTkMatch + 
        process.l1ToTkMatchNoJPsi + process.l1ToTkMatchNoBestJPsi +
        process.l1ToTkMatch0 + 
        process.l1ToTkMatchNoJPsi0 + process.l1ToTkMatchNoBestJPsi0 +
        process.nverticesModule +
        process.tpTreeL1
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
    cut = cms.string(TRACK_CUTS + ' && ' + InLooseAcceptance + ' && innerTrack.originalAlgo<13'), #   muonSeededStepInOut = 13              
)

process.muonDxyPVdzMinTrk = cms.EDProducer("MuonDxyPVdzmin",
    probes = cms.InputTag("probeMuonsTrk"),
)

process.tpPairsTrk = cms.EDProducer("CandViewShallowCloneCombiner",
    cut = cms.string('2.5 < mass < 3.5'),
    decay = cms.string('tagMuons@+ probeMuonsTrk@-')
)

#process.tnPairsDeltaPhiTrk = cms.EDProducer("DiMuonDeltaPhi",
#    tagProbePairs = cms.InputTag("tpPairsTrk"),
#)

process.onePairTrk = cms.EDFilter("CandViewCountFilter",
     src = cms.InputTag('tpPairsTrk'),
     minNumber = cms.uint32(1),
)

process.tpTreeTrk = cms.EDAnalyzer("TagProbeFitTreeProducer",
     # choice of tag and probe pairs, and arbitration
     tagProbePairs = cms.InputTag("tpPairsTrk"),
     arbitration   = cms.string("OneProbe"),
     # probe variables: all useful ones
     variables = cms.PSet(
        KinematicVariables,
        StaOnlyVariables,
        dxyPVdzmin = cms.InputTag("muonDxyPVdzMinTrk","dxyPVdzmin"),
        dzPV       = cms.InputTag("muonDxyPVdzMinTrk","dzPV"),
        #dxyzPVCuts       = cms.InputTag("muonDxyPVdzmin","dxyzPVCuts"),
     ),
     flags = cms.PSet(
        TrigProbeFlags,
        isSTA = cms.string("isStandAloneMuon"),
        outerValidHits  = cms.string("? outerTrack.isNull() ? 0 : outerTrack.numberOfValidHits > 0"),
        TM  = cms.string("isTrackerMuon"),
        Glb = cms.string("isGlobalMuon"),
        InTightAcceptance = cms.string(InTightAcceptance),
     ),
     tagVariables = cms.PSet(
        TrackQualityVariables,
        GlobalTrackQualityVariables,
        pt  = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
        l2dr  = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() ? 999 : "+
                           " deltaR( eta, phi, " +
                           "         triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).eta, "+
                           "         triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).phi ) "),

     ),
     tagFlags     = cms.PSet(
        TrigTagFlags,
     ),
     pairVariables = cms.PSet(
        pt  = cms.string("pt"),
        y = cms.string("rapidity"),
        absy = cms.string("abs(rapidity)"),
        deltaR   = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
        #deltaPhi = cms.InputTag("tnPairsDeltaPhiTrk","deltaPhi"),
     ),
     pairFlags = cms.PSet(),
     isMC           = cms.bool(False),
     #addRunLumiInfo = cms.bool(True),
     allProbes     = cms.InputTag("probeMuonsTrk")
)

process.tnpSimpleSequenceTrk = cms.Sequence(
    process.probeMuonsTrk +
    process.muonDxyPVdzMinTrk +
    process.tpPairsTrk    +
    process.onePairTrk +
    #process.tnPairsDeltaPhiTrk +
    process.tpTreeTrk
)

process.tagAndProbeTrk = cms.Path(
      process.fastFilter
    * process.tnpSimpleSequenceTrk
)

process.load('HLTrigger.HLTanalyzers.HLTBitAnalyser_cfi')
process.hltbitanalysis.HLTProcessName = cms.string('HLT')
process.hltbitanalysis.hltresults = cms.InputTag('TriggerResults', '', 'HLT')
process.hltbitanalysis.l1results = cms.InputTag('gtStage2Digis', '', 'RECO')#hltGtStage2Digis
process.hltbitanalysis.UseTFileService = cms.untracked.bool(True)
process.hltbitanalysis.RunParameters = cms.PSet(isData = cms.untracked.bool(True), 
                                                Monte = cms.untracked.bool(False))
process.hltBitAnalysis = cms.EndPath(process.hltbitanalysis)

process.schedule = cms.Schedule(
    process.tagAndProbe,
    process.tagAndProbeSta,
    process.tagAndProbeTrk,
   #process.hltBitAnalysis
   #process.tagAndProbeTkL1
)

process.RandomNumberGeneratorService.tkTracksNoJPsi      = cms.PSet( initialSeed = cms.untracked.uint32(81) )
process.RandomNumberGeneratorService.tkTracksNoJPsi0      = cms.PSet( initialSeed = cms.untracked.uint32(81) )
process.RandomNumberGeneratorService.tkTracksNoBestJPsi  = cms.PSet( initialSeed = cms.untracked.uint32(81) )
process.RandomNumberGeneratorService.tkTracksNoBestJPsi0  = cms.PSet( initialSeed = cms.untracked.uint32(81) )

process.TFileService = cms.Service("TFileService", fileName = cms.string("tnpJPsi_Data_pp5TeVRun2017G_AOD.root"))
