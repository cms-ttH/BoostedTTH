import FWCore.ParameterSet.Config as cms

SynchSelection = cms.PSet(
)

LeptonSelection = cms.PSet(
    muonTriggers = cms.vstring("HLT_IsoMu24_eta2p1_v"),
    electronTriggers = cms.vstring("HLT_Ele27_WP80_v")
)

LeptonSelectionNoTrigger = cms.PSet(
    muonTriggers = cms.vstring("None"),
    electronTriggers = cms.vstring("None")
)

JetTagSelection = cms.PSet(
    minJets = cms.vint32(4),
    maxJets = cms.vint32(-1),
    minTags = cms.vint32(2),
    maxTags = cms.vint32(-1)
)
