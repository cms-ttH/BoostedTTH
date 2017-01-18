import FWCore.ParameterSet.Config as cms

SelectedJetProducer = cms.EDProducer(
    "SelectedJetProducer",
    isData       = cms.bool(False),
    applyCorrection = cms.bool(True),
    doJER = cms.bool(False),
    jets = cms.InputTag("slimmedJets"),
    miniAODGenJets = cms.InputTag("slimmedGenJets"),
    electrons = cms.InputTag("SelectedElectronProducer:selectedElectronsLoose"),
    muons = cms.InputTag("SelectedMuonProducer:selectedMuonsLoose"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    ptMins   = cms.vdouble(30,20,30,20),
    etaMaxs  = cms.vdouble(2.4,2.4,2.4,2.4),
    leptonJetDr = cms.double(0.4),
    collectionNames  = cms.vstring("rawJets","selectedJets","selectedJetsLoose","selectedJetsDL","selectedJetsLooseDL"),
    systematics = cms.vstring(""),
    )

