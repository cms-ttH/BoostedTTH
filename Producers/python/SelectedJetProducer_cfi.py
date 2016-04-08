import FWCore.ParameterSet.Config as cms

SelectedJetProducer = cms.EDProducer(
    "JetMETprodcuer",
    isData       = cms.bool(False),
    applyCorrection = cms.bool(True),
    jets = cms.InputTag("slimmedJets"),
    electrons = cms.InputTag("slimmedElectrons"),
    muons = cms.InputTag("slimmedMuns"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    jetPtMin   = cms.vdouble(30,20),
    jetEtaMax  = cms.vdouble(2.4,2.4),
    collectionNames  = cms.vdouble("selectedJets","selectedJetsLoose"),

    

    )
