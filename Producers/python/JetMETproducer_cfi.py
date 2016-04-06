import FWCore.ParameterSet.Config as cms

JetMETprodcuer = cms.EDProducer(
    "JetMETprodcuer",
    isData       = cms.bool(False),
    jets = cms.InputTag("slimmedJets"),
    mets=cms.InputTag("slimmedMETs"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    jetPtMin   = cms.double(30),
    jetEtaMax  = cms.double(2.4),
    looseJetPtMin   = cms.double(20),
    looseJetEtaMax  = cms.double(2.4),

    

    )
