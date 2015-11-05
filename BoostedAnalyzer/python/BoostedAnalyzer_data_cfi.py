import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *

BoostedAnalyzer = cms.EDAnalyzer(
    'BoostedAnalyzer',
    LeptonSelectionData, # defined in Selection_cff
    DiLeptonSelectionData, # defined in Selection_cff
    JetTagSelection, # defined in Selection_cff
    METSelection, # defined in Selection_cff
    checkBasicDataTriggers, # defined in Selection_cff

    era = cms.string("2015_74x"), # has little effect so far, might become important for MiniAODhelper
    analysisType = cms.string("LJ"), # has little effect so far, might become important for MiniAODhelper
    sampleID = cms.int32(9125), # has little effect so far, might become important for MiniAODhelper

    eventWeight = cms.double(1.),
    isData = cms.bool(True),

    makeSystematicsTrees = cms.bool(False),

    useFatJets = cms.bool(False),
    useForwardJets = cms.bool(False),
    useGenHadronMatch = cms.bool(False),

    dumpSyncExe = cms.bool(False),
    dumpSyncExe2 = cms.bool(False),

    selectionNames = cms.vstring("VertexSelection","LeptonSelection"),
    processorNames = cms.vstring("WeightProcessor","BasicVarProcessor","MVAVarProcessor","BDTVarProcessor","DiLeptonVarProcessor","TriggerVarProcessor","BoostedJetVarProcessor","BoostedTopHiggsVarProcessor","BoostedTopVarProcessor","BoostedHiggsVarProcessor"),

    outfileName = cms.string("BoostedTTH"),
)
