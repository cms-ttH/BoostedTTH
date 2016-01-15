import FWCore.ParameterSet.Config as cms

# Setting input particle collections to be used by the tools
genParticleCollection = 'prunedGenParticles'
genJetCollection = 'slimmedGenJets'

# Ghost particle collection used for Hadron-Jet association 
# MUST use proper input particle collection
from PhysicsTools.JetMCAlgos.HadronAndPartonSelector_cfi import selectedHadronsAndPartons
selectedHadronsAndPartons = selectedHadronsAndPartons.clone(
    particles = genParticleCollection
)

## Input particle collection for matching to gen jets (partons + leptons) 
# MUST use use proper input jet collection: the jets to which hadrons should be associated
# rParam and jetAlgorithm MUST match those used for jets to be associated with hadrons
# More details on the tool: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideBTagMCTools#New_jet_flavour_definition
from PhysicsTools.JetMCAlgos.AK4PFJetsMCFlavourInfos_cfi import ak4JetFlavourInfos
genJetFlavourInfos = ak4JetFlavourInfos.clone(
    jets = genJetCollection,
)


## Plugin for analysing B hadrons
# MUST use the same particle collection as in selectedHadronsAndPartons
from PhysicsTools.JetMCAlgos.GenHFHadronMatcher_cff import matchGenBHadron
matchGenBHadron = matchGenBHadron.clone(
    genParticles = genParticleCollection,
    jetFlavourInfos = "genJetFlavourInfos"
)

## Plugin for analysing C hadrons
# MUST use the same particle collection as in selectedHadronsAndPartons
from PhysicsTools.JetMCAlgos.GenHFHadronMatcher_cff import matchGenCHadron
matchGenCHadron = matchGenCHadron.clone(
    genParticles = genParticleCollection,
    jetFlavourInfos = "genJetFlavourInfos"
)


## Producer for ttbar categorisation ID
# MUST use same genJetCollection as used for tools above
from TopQuarkAnalysis.TopTools.GenTtbarCategorizer_cfi import categorizeGenTtbar
categorizeGenTtbar = categorizeGenTtbar.clone(
    genJetPtMin = 20.,
    genJetAbsEtaMax = 2.4,
    genJets = genJetCollection,
)
