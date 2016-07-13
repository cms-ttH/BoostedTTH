import FWCore.ParameterSet.Config as cms

# Setting input particle collections to be used by the tools
genJetCollection = 'ak4GenJetsCustom'
genParticleCollection = 'prunedGenParticles'
genJetInputParticleCollection = 'packedGenParticles'

## producing a subset of particles to be used for jet clustering
from RecoJets.Configuration.GenJetParticles_cff import genParticlesForJets
genParticlesForJetswNu = genParticlesForJets.clone(
    src = genJetInputParticleCollection,
    excludeResonances = cms.bool(True),
    excludeFromResonancePids = cms.vuint32(12, 14, 16),
)

# Producing own jets for testing purposes
from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
ak4GenJetsCustomwNu = ak4GenJets.clone(
    src = 'genParticlesForJetswNu',
    rParam = cms.double(0.4),
    jetAlgorithm = cms.string("AntiKt"),
#    jetPtMin = 20.
)
