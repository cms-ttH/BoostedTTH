import FWCore.ParameterSet.Config as cms
# input
process = cms.Process("p")
process.source = cms.Source("PoolSource",
#                            fileNames = cms.untracked.vstring('file:/nfs/dust/cms/user/tpfotzer/MiniAOD_raw/ttH_01.root')
                            #fileNames = cms.untracked.vstring('file:/storage/9/mildner/ttbar_phys14.root')
                            fileNames = cms.untracked.vstring('root://xrootd.unl.edu//store/mc/Phys14DR/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/00000/00C90EFC-3074-E411-A845-002590DB9262.root')
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )

# messages
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.suppressWarning = cms.untracked.vstring('ecalLaserCorrFilter','manystripclus53X','toomanystripclus53X')
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)

# select loose lepton collections
process.selectedMuons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedMuons"), cut = cms.string('''abs(eta)<2.5 && pt>10. &&
(pfIsolationR03().sumChargedHadronPt+
max(0.,pfIsolationR03().sumNeutralHadronEt+
pfIsolationR03().sumPhotonEt-
0.50*pfIsolationR03().sumPUPt))/pt < 0.20 &&
(isPFMuon && (isGlobalMuon || isTrackerMuon) )'''))
process.selectedElectrons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedElectrons"), cut = cms.string('''abs(eta)<2.5 && pt>20. &&
gsfTrack.isAvailable() &&
gsfTrack.hitPattern().numberOfLostHits(\'MISSING_INNER_HITS\') < 2 &&
(pfIsolationVariables().sumChargedHadronPt+
max(0.,pfIsolationVariables().sumNeutralHadronEt+
pfIsolationVariables().sumPhotonEt-
0.5*pfIsolationVariables().sumPUPt))/pt < 0.15'''))

#do projections
process.pfCHS = cms.EDFilter("CandPtrSelector", src = cms.InputTag("packedPFCandidates"), cut = cms.string("fromPV"))
process.pfNoMuonCHS =  cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfCHS"), veto = cms.InputTag("selectedMuons"))
process.pfNoElectronsCHS = cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfNoMuonCHS"), veto =  cms.InputTag("selectedElectrons"))

# make patJets
process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load('Configuration.StandardSequences.Geometry_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'PHYS14_25_V2::All'

# Fat jets
from BoostedTTH.BoostedProducer.SubjetsFilterjets_cfi import CA12JetsCA3FilterjetsPF
from BoostedTTH.BoostedProducer.HEPTopJetParameters_cfi import HEPTopJetsPF
process.CA12JetsCA3FilterjetsPF=CA12JetsCA3FilterjetsPF.clone(src = 'pfNoElectronsCHS')
process.CA12JetsCA3FilterjetsPF.jetPtMin=cms.double(180.)
process.CA12JetsCA3FilterjetsPF.doAreaFastjet=cms.bool(False)
process.HEPTopJetsPF=HEPTopJetsPF.clone(src = 'pfNoElectronsCHS')
process.HEPTopJetsPF.jetPtMin=cms.double(180.)
process.HEPTopJetsPF.doAreaFastjet=cms.bool(True)

#from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets
from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
#process.ak4PFJetsCHS = ak4PFJets.clone(src = 'pfNoElectronsCHS', doAreaFastjet = True)
process.ak4GenJets = ak4GenJets.clone(src = 'packedGenParticles')

from PhysicsTools.PatAlgos.tools.jetTools import addJetCollection
# add fat CA1.2 pat jet
addJetCollection(
    process,
    postfix = "",
    jetSource = cms.InputTag('CA12JetsCA3FilterjetsPF','fatjet'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    labelName = 'CA12PF',
    algo = 'CA',
    rParam = 1.2,
    trackSource = cms.InputTag('unpackedTracksAndVertices'),
    pvSource = cms.InputTag('unpackedTracksAndVertices'),
    btagDiscriminators = None,
    jetCorrections = None,
    getJetMCFlavour = False,
    genJetCollection = None
)
# the two subjets that created the mass drop
addJetCollection(
    process,
    postfix = "",
    jetSource = cms.InputTag('CA12JetsCA3FilterjetsPF','subjets'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    labelName = 'CA3SubPF',
    algo = 'CA',
    rParam = 1.2,
    #fatJets = cms.InputTag('CA12JetsCA3FilterjetsPF','fatjet'),
    trackSource = cms.InputTag('unpackedTracksAndVertices'),
    pvSource = cms.InputTag('unpackedTracksAndVertices'),
    btagDiscriminators = None,
    jetCorrections = None,
    getJetMCFlavour = False,
    genJetCollection = None
)
# filterjets (reclustered from subjets)
addJetCollection(
    process,
    postfix = "",
    jetSource = cms.InputTag('CA12JetsCA3FilterjetsPF','filterjets'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    labelName = 'CA3FiltPF',
    algo = 'CA',
    rParam = 1.2,
    #fatJets = cms.InputTag('CA12JetsCA3FilterjetsPF','fatjet'),
    #groomedFatJets = cms.InputTag('CA12JetsCA3FilterjetsPF','subjets'),
    trackSource = cms.InputTag('unpackedTracksAndVertices'),
    pvSource = cms.InputTag('unpackedTracksAndVertices'),
    btagDiscriminators =  [ 'pfCombinedInclusiveSecondaryVertexV2BJetTags','combinedSecondaryVertexBJetTags' ],
    jetCorrections = None,
    getJetMCFlavour = False,
    genJetCollection = None #cms.InputTag('CA12JetsCA3FilterjetsGen','filterjets')
)
# fatjet for HEPTopTagger
addJetCollection(
    process,
    postfix="",
    jetSource = cms.InputTag('HEPTopJetsPF', 'fatjet'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    labelName = 'HEPTopFatPF',
    algo = 'CA',
    rParam = 1.5,
    trackSource = cms.InputTag('unpackedTracksAndVertices'),
    pvSource = cms.InputTag('unpackedTracksAndVertices'),
    btagDiscriminators = None,
    jetCorrections = None,
    getJetMCFlavour = False,
    genJetCollection = None
)
# 3 subjets corresbonding to W and b
addJetCollection(
    process,
    postfix="",
    jetSource = cms.InputTag('HEPTopJetsPF', 'subjets'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    labelName = 'HEPTopSubPF',
    algo = 'CA',
    rParam = 1.5,
    #fatJets = cms.InputTag('HEPTopJetsPF', 'fatjet'),
    #groomedFatJets = cms.InputTag("ak8PFJetsCHSPruned"),
    trackSource = cms.InputTag('unpackedTracksAndVertices'),
    pvSource = cms.InputTag('unpackedTracksAndVertices'),
    btagDiscriminators = [ 'pfCombinedInclusiveSecondaryVertexV2BJetTags','combinedSecondaryVertexBJetTags' ],
    jetCorrections = None,
    getJetMCFlavour = False,
    genJetCollection = None
)

# match sub, filter and fat jet
from BoostedTTH.BoostedProducer.SubjetsFilterjetsMatcher_cfi import CA12JetsCA3FilterjetsPFMatcher
process.CA12JetsCA3FilterjetsPFMatcher=CA12JetsCA3FilterjetsPFMatcher.clone()
# match top sub to fat jet
from BoostedTTH.BoostedProducer.HEPTopJetMatcher_cfi import HEPTopJetsPFMatcher
process.HEPTopJetsPFMatcher=HEPTopJetsPFMatcher.clone()

#adjust MC matching for all jet collections
process.patJetsCA12PF.addGenJetMatch=False
process.patJetsCA3SubPF.addGenJetMatch=False
process.patJetsCA3FiltPF.addGenJetMatch=False
process.patJetsHEPTopFatPF.addGenJetMatch=False
process.patJetsHEPTopSubPF.addGenJetMatch=False
process.patJetPartonMatchCA12PF.matched = "prunedGenParticles"
process.patJetPartonMatchCA3SubPF.matched = "prunedGenParticles"
process.patJetPartonMatchCA3FiltPF.matched = "prunedGenParticles"
process.patJetPartonMatchHEPTopSubPF.matched = "prunedGenParticles"
process.patJetPartonMatchHEPTopFatPF.matched = "prunedGenParticles"
process.patJetPartons.particles = "prunedGenParticles"

#recreate tracks and pv for btagging
process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')

process.inclusiveVertexFinder.primaryVertices=cms.InputTag("offlineSlimmedPrimaryVertices")
process.inclusiveVertexFinder.tracks=cms.InputTag("unpackedTracksAndVertices")
process.trackVertexArbitrator.tracks=cms.InputTag("unpackedTracksAndVertices")
process.trackVertexArbitrator.primaryVertices=cms.InputTag("offlineSlimmedPrimaryVertices")

# gen hadron matching for tt+X categorization
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("BoostedTTH.BoostedProducer.genHadronMatching_cfi")


process.OUT = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('BoostedTTH_MiniAOD.root'),
    outputCommands = cms.untracked.vstring(['drop *','keep *_*_*_PAT','keep *_*_*_RECO','keep *_*_*_HLT','keep *_*_*_SIM','keep *_*_*_LHE','keep *_*HEPTopJetsPFMatcher_*_*','keep *_*CA12JetsCA3FilterjetsPFMatcher_*_*','keep *_matchGen*Hadron_*_*', 'keep *_ak4GenJetsCustom_*_*'])
)
process.endpath = cms.EndPath(process.OUT)

