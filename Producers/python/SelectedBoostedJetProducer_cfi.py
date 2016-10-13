import FWCore.ParameterSet.Config as cms

SelectedBoostedJetProducer = cms.EDProducer(
    "SelectedBoostedJetProducer",
    boostedJets=cms.InputTag("BoostedJetMatcher:boostedjets:p"),    
    isData       = cms.bool(False),
    applyCorrection = cms.bool(True),
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
    useFatJets = cms.bool(True)
    )
