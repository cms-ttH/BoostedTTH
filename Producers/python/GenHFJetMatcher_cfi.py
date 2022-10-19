import FWCore.ParameterSet.Config as cms

genHFJetMatcher = cms.EDProducer("GenHFJetMatcher",
    src = cms.InputTag("ak4GenJetsCustom"),
    cut = cms.string("pt > 10"),
    deltaR = cms.double(0.1),
    jetFlavourInfos = cms.InputTag("genJetFlavourInfos"),
)
