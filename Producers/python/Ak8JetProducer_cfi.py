import FWCore.ParameterSet.Config as cms

Ak8JetProducer = cms.EDProducer(
    "Ak8JetProducer",
    isData       = cms.bool(False),
    applyCorrection = cms.bool(True),
    doJER = cms.bool(False),
    jets = cms.InputTag("slimmedJetsAK8"),
    miniAODGenJets = cms.InputTag("slimmedGenJetsAK8"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    electrons = cms.InputTag("SelectedElectronProducer:selectedElectronsLoose"),
    muons = cms.InputTag("SelectedMuonProducer:selectedMuonsLoose"),
    ptMins   = cms.vdouble(30),
    etaMaxs  = cms.vdouble(2.4),
    PUJetIDMins = cms.vstring("none"),
    leptonJetDr = cms.double(0.4),
    collectionNames  = cms.vstring("AK8Jets"),
    systematics = cms.vstring(""),
    JetID = cms.string("none"),
    )