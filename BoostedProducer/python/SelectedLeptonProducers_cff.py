import FWCore.ParameterSet.Config as cms

SelectedElectronProducer = cms.EDProducer(
    "SelectedLeptonProducer",
    leptonType = cms.string("electron"),

    era          = cms.string("2015_74x"),
    analysisType = cms.string("LJ"),
    sampleID     = cms.int32(9125),
    isData       = cms.bool(False),

    leptons = cms.InputTag("slimmedElectrons"),
    ptMin   = cms.double(20),
    etaMax  = cms.double(2.5),
    )


SelectedMuonProducer = cms.EDProducer(
    "SelectedLeptonProducer",
    leptonType = cms.string("muon"),

    era          = cms.string("2015_74x"),
    analysisType = cms.string("LJ"),
    sampleID     = cms.int32(9125),
    isData       = cms.bool(False),

    leptons = cms.InputTag("slimmedMuons"),
    ptMin   = cms.double(10),
    etaMax  = cms.double(2.5),
    )

