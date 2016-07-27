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
    #GenJet cuts
    genjetcuts = cms.vdouble(25,2.4),
    softleptonJetDr = cms.double(0.4),
    minpT = cms.double(25.0),
    weightfile = cms.string("BReg_0720_80XReg_BDTG.weights.xml"),
    doGenJetMatchingforRegression = cms.bool(False),
    outputprefix = cms.string("regressedJets"),
    collectionpostfix = cms.vstring("")
    )
