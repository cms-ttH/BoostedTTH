import FWCore.ParameterSet.Config as cms

RegressedJetProducer = cms.EDProducer(
    "RegressedJetProducer",
    isData = cms.bool(False),
    inputjets = cms.VInputTag(""),
#    inputjets = cms.VInputTag("SelectedJetProducer:selectedJets"),
    electrons = cms.InputTag("slimmedElectrons"),
    muons = cms.InputTag("slimmedMuons"),
    pVs = cms.InputTag("offlineSlimmedPrimaryVertices"),
    genjets = cms.InputTag("ak4GenJetsCustomwNu"),
    #Soft electron cuts: pT, eta, dxy, dz, lostHits
    electroncuts   = cms.vdouble(5.0,2.5,0.5,1.0,1.0),
    #Soft muon cuts: pT, eta, dxy, dz
    muoncuts  = cms.vdouble(3.0,2.4,0.5,1.0),
    softleptonJetDr = cms.double(0.4),
    weightfile = cms.string("TMVARegression_0619_GenJet_1200_BSF05minNS06Shr075_patronFlav_BDTG.weights.xml"),
    doGenJetMatchingforRegression = cms.bool(False),
    outputprefix = cms.string("regressedJets"),
    collectionpostfix = cms.vstring("")
    )
