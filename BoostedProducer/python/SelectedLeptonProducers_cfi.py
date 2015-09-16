import FWCore.ParameterSet.Config as cms

SelectedElectronProducer = cms.EDProducer(
    "SelectedLeptonProducer",
    leptonType = cms.string("electron"),

    era          = cms.string("2015_74x"),
    analysisType = cms.string("LJ"),
    isData       = cms.bool(False),

    leptons = cms.InputTag("slimmedElectrons"),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    ptMin   = cms.double(10),
    etaMax  = cms.double(2.5),
    leptonID = cms.string("loose"),
    isoConeSize = cms.string("R04"),
    isoCorrType = cms.string("rhoEA")
    )


SelectedMuonProducer = cms.EDProducer(
    "SelectedLeptonProducer",
    leptonType = cms.string("muon"),

    era          = cms.string("2015_74x"),
    analysisType = cms.string("LJ"),
    isData       = cms.bool(False),

    leptons = cms.InputTag("slimmedMuons"),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    ptMin   = cms.double(10),
    etaMax  = cms.double(2.5),
    leptonID = cms.string("loose"),
    isoConeSize = cms.string("R04"),
    isoCorrType = cms.string("deltaBeta")    
    )

SelectedLeptonProducerPath = cms.Path(SelectedElectronProducer*SelectedMuonProducer)
