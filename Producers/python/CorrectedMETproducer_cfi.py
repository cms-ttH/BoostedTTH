import FWCore.ParameterSet.Config as cms

CorrectedMETproducer = cms.EDProducer(
    "CorrectedMETproducer",
    isData       = cms.bool(False),
    oldJets = cms.InputTag("slimmedJets"),
    newJets = cms.InputTag("slimmedJets"),
    oldElectrons = cms.InputTag("slimmedElectrons"),
    newElectrons = cms.InputTag("slimmedElectrons"),
    oldMuons = cms.InputTag("slimmedMuons"),
    newMuons = cms.InputTag("slimmedMuons"),
    mets =cms.InputTag("slimmedMETs"),
    collectionName=cms.string("correctedMET"),
      
    )
