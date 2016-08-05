import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *

BoostedAnalyzer = cms.EDAnalyzer(
    'BoostedAnalyzer',
    LeptonSelectionMC, # defined in Selection_cff
    DiLeptonSelectionMC, # defined in Selection_cff
    JetTagSelection, # defined in Selection_cff
    DiLeptonMETSelection, # defined in Selection_cff
    checkBasicMCTriggers, # defined in Selection_cff

    era = cms.string("2015_74x"), # has little effect so far, might become important for MiniAODhelper
    analysisType = cms.string("DL"), # has little effect so far, might become important for MiniAODhelper
    sampleID = cms.int32(9125), # has little effect so far, might become important for MiniAODhelper
    eventWeight = cms.double(1.),
    generatorName = cms.string("notSpecified"),
    
    minJetsForMEM = cms.int32(4),
    minTagsForMEM = cms.int32(3),
    
    luminosity = cms.double(10000),
    xs = cms.double(831.76),

    nMCEvents = cms.int32(25446993),

    isData = cms.bool(False),

    makeSystematicsTrees = cms.bool(True),

    useFatJets = cms.bool(False),
    useForwardJets = cms.bool(False),
    useGenHadronMatch = cms.bool(True),

    dumpSyncExe = cms.bool(False),
    dumpSyncExe2 = cms.bool(False),

    selectionNames = cms.vstring("VertexSelection"),#,"MinDiLeptonMassSelection"),
    processorNames = cms.vstring("WeightProcessor","TriggerVarProcessor","MCMatchVarProcessor","AdditionalJetProcessor","SpinCorrelationProcessor"),

    outfileName = cms.string("BoostedTTH"),
)
