import FWCore.ParameterSet.Config as cms

# Setting input particle collections to be used by the tools
genJetCollection = 'ak4GenJetsCustom'
genParticleCollection = 'prunedGenParticles'
genJetInputParticleCollection = 'packedGenParticles'

## producing a subset of particles to be used for jet clustering
from RecoJets.Configuration.GenJetParticles_cff import genParticlesForJetsNoNu
genParticlesForJetsNoNu = genParticlesForJetsNoNu.clone(
    src = genJetInputParticleCollection
)

# Producing own jets for testing purposes
from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
ak4GenJetsCustom = ak4GenJets.clone(
    src = 'genParticlesForJetsNoNu',
    rParam = cms.double(0.4),
    jetAlgorithm = cms.string("AntiKt"),
#    jetPtMin = 20.
)

# Ghost particle collection used for Hadron-Jet association 
# MUST use proper input particle collection
from PhysicsTools.JetMCAlgos.HadronAndPartonSelector_cfi import selectedHadronsAndPartons
selectedHadronsAndPartons = selectedHadronsAndPartons.clone(
    particles = genParticleCollection
)

# Input particle collection for matching to gen jets (partons + leptons) 
# MUST use use proper input jet collection: the jets to which hadrons should be associated
# rParam and jetAlgorithm MUST match those used for jets to be associated with hadrons
# More details on the tool: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideBTagMCTools#New_jet_flavour_definition
from PhysicsTools.JetMCAlgos.sequences.GenHFHadronMatching_cff import genJetFlavourPlusLeptonInfos
genJetFlavourPlusLeptonInfos = genJetFlavourPlusLeptonInfos.clone(
    jets = genJetCollection,
    rParam = cms.double(0.4),
    jetAlgorithm = cms.string("AntiKt")
)


# Plugin for analysing B hadrons
# MUST use the same particle collection as in selectedHadronsAndPartons
from PhysicsTools.JetMCAlgos.sequences.GenHFHadronMatching_cff import matchGenBHadron
matchGenBHadron = matchGenBHadron.clone(
    genParticles = genParticleCollection
)

# Plugin for analysing C hadrons
# MUST use the same particle collection as in selectedHadronsAndPartons
from PhysicsTools.JetMCAlgos.sequences.GenHFHadronMatching_cff import matchGenCHadron
matchGenCHadron = matchGenCHadron.clone(
    genParticles = genParticleCollection
)

## Producer for ttbar categorisation ID
# MUST use same genJetCollection as used for tools above
from PhysicsTools.JetMCAlgos.GenTtbarCategorizer_cfi import categorizeGenTtbar
categorizeGenTtbar = categorizeGenTtbar.clone(
    genJetPtMin = 20.,
    genJetAbsEtaMax = 2.4,
    genJets = genJetCollection,
)
