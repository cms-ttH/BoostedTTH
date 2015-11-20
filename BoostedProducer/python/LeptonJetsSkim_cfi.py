import FWCore.ParameterSet.Config as cms

LeptonJetsSkim = cms.EDFilter(
    "LeptonJetsSkim",
    era          = cms.string("2015_74x"),
    isData       = cms.bool(False),
    electrons = cms.InputTag("slimmedElectrons"),
    muons = cms.InputTag("slimmedMuons"),
    jets = cms.InputTag("slimmedJets"),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    electronMVAvalues = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring15Trig25nsV1Values"),
    electronMVAcategories = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring15Trig25nsV1Categories"),
    muonPtMin   = cms.double(20),
    muonEtaMax  = cms.double(2.4),
    electronPtMin   = cms.double(20),
    electronEtaMax  = cms.double(2.4),
    jetPtMin   = cms.double(20),
    jetEtaMax  = cms.double(2.4),
    minJets  = cms.int32(0),
    

    )
