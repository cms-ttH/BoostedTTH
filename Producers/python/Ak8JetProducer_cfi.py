import FWCore.ParameterSet.Config as cms

Ak8JetProducer = cms.EDProducer(
    "Ak8JetProducer",
    isData       = cms.bool(False),
    applyCorrection = cms.bool(True),
    doJER = cms.bool(False),
    jets = cms.InputTag("slimmedJetsAK8"),
    # jets = cms.InputTag("slimmedJetsAK8PFCHSSoftDropPacked"),

    miniAODGenJets = cms.InputTag("slimmedGenJets"),
    electrons = cms.InputTag("SelectedElectronProducer:selectedElectronsLoose"),
    muons = cms.InputTag("SelectedMuonProducer:selectedMuonsLoose"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    ptMins   = cms.vdouble(30),
    etaMaxs  = cms.vdouble(2.4),
    PUJetIDMins = cms.vstring("none","none"),
    leptonJetDr = cms.double(0.4),
    collectionNames  = cms.vstring("AK8Jet"),
    systematics = cms.vstring(""),
    JetID = cms.string("none"),
    )