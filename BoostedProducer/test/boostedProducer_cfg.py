import FWCore.ParameterSet.Config as cms
from PhysicsTools.PatAlgos.tools.jetTools import addJetCollection

process = cms.Process("p")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    #fileNames = cms.untracked.vstring('file:/nfs/dust/cms/user/shwillia/Test/ttbar_miniAODtest.root')
    fileNames = cms.untracked.vstring('file:/nfs/dust/cms/user/shwillia/Test/ttH_Phys14_miniAOD.root')
)


process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.GlobalTag.globaltag = 'PHYS14_25_V2::All'
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10
process.MessageLogger.suppressWarning = cms.untracked.vstring('ecalLaserCorrFilter','manystripclus53X','toomanystripclus53X')
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

# unpack tracks and vertices
process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')
process.unpackedTracksAndVertices = cms.EDProducer("PATTrackAndVertexUnpacker",
    slimmedVertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    slimmedSecondaryVertices = cms.InputTag("slimmedSecondaryVertices"),
    packedCandidates = cms.InputTag("packedPFCandidates"),
    additionalTracks = cms.InputTag("lostTracks")
)

#select isolated collections
process.selectedMuons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedMuons"), cut = cms.string('''abs(eta)<2.5 && pt>10. &&
(pfIsolationR04().sumChargedHadronPt+
max(0.,pfIsolationR04().sumNeutralHadronEt+
pfIsolationR04().sumPhotonEt-
0.50*pfIsolationR04().sumPUPt))/pt < 0.20 &&
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
process.pfNoMuonCHS = cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfCHS"), veto = cms.InputTag("selectedMuons"))
process.pfNoElectronsCHS = cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfNoMuonCHS"), veto = cms.InputTag("selectedElectrons"))

# load subfilterjet algorithm
process.load("BoostedTTH.BoostedProducer.SubjetsFilterjets_cfi")

# load heptoptagger
process.load("BoostedTTH.BoostedProducer.HEPTopJetParameters_cfi")

# use pfNoElectron
process.CA12JetsCA3FilterjetsPF.src = cms.InputTag("pfNoElectronsCHS")
process.HEPTopJetsPF.src=cms.InputTag("pfNoElectronsCHS")
# use all genparticles as src (incl neutrinos etc)
process.CA12JetsCA3FilterjetsGen.src = cms.InputTag("packedGenParticles")

# create pat jets from reco jets
# fatjets
addJetCollection(
    process,
    postfix="",
    jetSource=    cms.InputTag('CA12JetsCA3FilterjetsPF','fatjet'),
    pfCandidates = cms.InputTag('packedPFCandidates'), 
    labelName = 'CA12PF',
    trackSource = cms.InputTag('unpackedTracksAndVertices'),
    pvSource = cms.InputTag('unpackedTracksAndVertices'),
    btagDiscriminators = [ 'combinedSecondaryVertexBJetTags' ],
    jetCorrections = None,
    getJetMCFlavour = False,
    genJetCollection = None
)
# the two subjets that created the mass drop
addJetCollection(
    process,
    postfix="",
    jetSource=    cms.InputTag('CA12JetsCA3FilterjetsPF','subjets'),
    pfCandidates = cms.InputTag('packedPFCandidates'), 
    labelName = 'CA3SubPF',
    trackSource = cms.InputTag('unpackedTracksAndVertices'),
    pvSource = cms.InputTag('unpackedTracksAndVertices'),
    btagDiscriminators = [ 'combinedSecondaryVertexBJetTags' ],
    jetCorrections = None,
    getJetMCFlavour = False,
    genJetCollection = cms.InputTag('CA12JetsCA3FilterjetsGen','subjets')
)
# filterjets (reclustered from subjets)
addJetCollection(
    process,
    postfix="",
    jetSource=    cms.InputTag('CA12JetsCA3FilterjetsPF','filterjets'),
    pfCandidates = cms.InputTag('packedPFCandidates'), 
    labelName = 'CA3FiltPF',
    trackSource = cms.InputTag('unpackedTracksAndVertices'),
    pvSource = cms.InputTag('unpackedTracksAndVertices'),
    btagDiscriminators = [ 'combinedSecondaryVertexBJetTags' ],
    jetCorrections = None,
    getJetMCFlavour = False,
    genJetCollection = cms.InputTag('CA12JetsCA3FilterjetsGen','filterjets')
)
# fatjet for HEPTopTagger
addJetCollection(
    process,
    postfix="",
    jetSource=     cms.InputTag('HEPTopJetsPF', 'fatjet'),
    pfCandidates = cms.InputTag('packedPFCandidates'), 
    labelName = 'HEPTopFatPF',
    trackSource = cms.InputTag('unpackedTracksAndVertices'),
    pvSource = cms.InputTag('unpackedTracksAndVertices'),
    btagDiscriminators = [ 'combinedSecondaryVertexBJetTags' ],
    jetCorrections = None,
    getJetMCFlavour = False,
    genJetCollection = None 
)
# 3 subjets corresbonding to W and b
addJetCollection(
    process,
    postfix="",
    jetSource= cms.InputTag('HEPTopJetsPF', 'subjets'),
    pfCandidates = cms.InputTag('packedPFCandidates'), 
    labelName = 'HEPTopSubPF',
    trackSource = cms.InputTag('unpackedTracksAndVertices'),
    pvSource = cms.InputTag('unpackedTracksAndVertices'),
    btagDiscriminators = [ 'combinedSecondaryVertexBJetTags' ],
    jetCorrections = None,
    getJetMCFlavour = False,
    genJetCollection = None #cms.InputTag('HEPTopJetsGen', 'subjets')
)


# load subfilterjet matcher
process.load("BoostedTTH.BoostedProducer.SubjetsFilterjetsMatcher_cfi")

# load heptopjet matcher
process.load("BoostedTTH.BoostedProducer.HEPTopJetMatcher_cfi")


process.combinedSecondaryVertex.trackMultiplicityMin = 1 #silly sv, uses un filtered tracks.. i.e. any pt

#adjust MC matching
process.patJetPartons.src = "prunedGenParticles"
process.patJetPartons.skipFirstN = cms.uint32(0) # do not skip first 6 particles, we already pruned some!
process.patJetPartons.acceptNoDaughters = cms.bool(True) # as we drop intermediate stuff, we need to accept quarks with no siblings
process.patJetPartonMatch.matched="prunedGenParticles"
process.patJetPartons.paticles=cms.InputTag("packedGenParticles")
process.patJetPartonMatchCA3SubPF.matched="prunedGenParticles"
process.patJetPartonMatchCA3FiltPF.matched="prunedGenParticles"
process.patJetPartonMatchCA12PF.matched="prunedGenParticles"
process.patJetPartonMatchHEPTopFatPF.matched="prunedGenParticles"
process.patJetPartonMatchHEPTopSubPF.matched="prunedGenParticles"

process.selectedPatJetsCA3FiltPF.cut="pt>10"

process.content = cms.EDAnalyzer("EventContentAnalyzer")

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('BoostedMiniAOD.root'),
#    outputCommands = cms.untracked.vstring(['keep *','drop *_pfCHS_*','drop *_selectedMuons_*','drop *_selectedElectrons_*','drop *_pfNoElectronsCHS_*','drop *_pfNoMuonCHS_*','drop *_*CA12*_*_*','drop *_*CA3*_*_*','drop *_*HEP*_*_*','keep *_*Matcher_*_*'])
)

process.patJetsCA12PF.addGenJetMatch=False
process.patJetsHEPTopFatPF.addGenJetMatch=False
process.patJetsHEPTopSubPF.addGenJetMatch=False

process.endpath= cms.EndPath(
    process.pfCHS
    *process.selectedMuons
    *process.selectedElectrons
    *process.pfNoMuonCHS
    *process.pfNoElectronsCHS
    *process.unpackedTracksAndVertices
    *process.filtjet_gen_seq
    *process.filtjet_pf_seq
    *process.heptopjet_pf_seq
    *process.jetTracksAssociatorAtVertexCA3FiltPF
    *process.jetTracksAssociatorAtVertexCA3SubPF
    *process.jetTracksAssociatorAtVertexCA12PF
    *process.jetTracksAssociatorAtVertexHEPTopFatPF
    *process.jetTracksAssociatorAtVertexHEPTopSubPF
    *process.impactParameterTagInfosCA3FiltPF
    *process.impactParameterTagInfosCA3SubPF
    *process.impactParameterTagInfosCA12PF
    *process.impactParameterTagInfosHEPTopFatPF
    *process.impactParameterTagInfosHEPTopSubPF
    *process.secondaryVertexTagInfosCA3FiltPF
    *process.secondaryVertexTagInfosCA3SubPF
    *process.secondaryVertexTagInfosCA12PF
    *process.secondaryVertexTagInfosHEPTopFatPF
    *process.secondaryVertexTagInfosHEPTopSubPF
    *process.combinedSecondaryVertexBJetTagsCA3FiltPF
    *process.combinedSecondaryVertexBJetTagsCA3SubPF
    *process.combinedSecondaryVertexBJetTagsCA12PF
    *process.combinedSecondaryVertexBJetTagsHEPTopFatPF
    *process.combinedSecondaryVertexBJetTagsHEPTopSubPF
    *process.patJetChargeCA3FiltPF
    *process.patJetChargeCA3SubPF
    *process.patJetChargeCA12PF
    *process.patJetChargeHEPTopFatPF
    *process.patJetChargeHEPTopSubPF
    *process.patJetGenJetMatchCA3FiltPF
    *process.patJetGenJetMatchCA3SubPF
    *process.patJetPartonMatchCA3FiltPF
    *process.patJetPartonMatchCA3SubPF
    *process.patJetPartonMatchCA12PF
    *process.patJetPartonMatchHEPTopFatPF
    *process.patJetPartonMatchHEPTopSubPF
    *process.patJetsCA3FiltPF
    *process.patJetsCA3SubPF
    *process.patJetsCA12PF
    *process.patJetsHEPTopFatPF
    *process.patJetsHEPTopSubPF
    *process.selectedPatJetsCA12PF
    *process.selectedPatJetsCA3SubPF
    *process.selectedPatJetsCA3FiltPF
    *process.selectedPatJetsHEPTopFatPF
    *process.selectedPatJetsHEPTopSubPF
    *process.CA12JetsCA3FilterjetsPFMatcher
    *process.HEPTopJetsPFMatcher
    *process.out
)

