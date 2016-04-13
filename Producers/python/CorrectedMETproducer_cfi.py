import FWCore.ParameterSet.Config as cms

CorrectedMETproducer = cms.EDProducer(
    "CorrectedMETproducer",
    isData       = cms.bool(False),
    oldJets = cms.InputTag("slimmedJets"),
    newJets = cms.InputTag("slimmedJets"),
    mets =cms.InputTag("slimmedMETs"),
    collectionName=cms.string("correctedMET"),
      
    )
