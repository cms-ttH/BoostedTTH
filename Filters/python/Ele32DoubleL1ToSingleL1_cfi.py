import FWCore.ParameterSet.Config as cms

Ele32DoubleL1ToSingleL1 = cms.EDFilter(
    "Ele32DoubleL1ToSingleL1",
    trigObjs=cms.InputTag("slimmedPatTrigger"),
    trigResults=cms.InputTag("TriggerResults", "", "HLT"),
    eles=cms.InputTag("slimmedElectrons"),
    tagging_mode=cms.bool(True),
)
