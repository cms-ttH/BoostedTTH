import FWCore.ParameterSet.Config as cms

LeptonJetsSkim = cms.EDFilter(
    "LeptonJetsSkim",
    era          = cms.string("NA"),
    isData       = cms.bool(False),
    electrons = cms.InputTag("slimmedElectrons"),
    muons = cms.InputTag("slimmedMuons"),
    jets = cms.InputTag("slimmedJets"),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    muonPtMin   = cms.double(15),
    muonEtaMax  = cms.double(2.5),
    electronPtMin   = cms.double(15),
    electronEtaMax  = cms.double(2.5),
    jetPtMin   = cms.double(15),
    jetEtaMax  = cms.double(2.5),
    minJets  = cms.int32(3),
    

    )
