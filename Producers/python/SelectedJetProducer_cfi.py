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
    ptMins   = cms.vdouble(30,20),
    etaMaxs  = cms.vdouble(2.4,2.4),
    PUJetIDMins = cms.vstring("none","none"),
    leptonJetDr = cms.double(0.4),
    collectionNames  = cms.vstring("selectedJets","selectedJetsLoose"),
    systematics = cms.vstring(""),
    JetID = cms.string("none"),
    JetType = cms.string("AK4PFchs"),
    jecFileAK4 = cms.string("Fall17_17Nov2017_V32_MC_UncertaintySources_AK4PFchs.txt"),
    jecFileAK8 = cms.string("Fall17_17Nov2017_V32_MC_UncertaintySources_AK8PFchs.txt")
    )

