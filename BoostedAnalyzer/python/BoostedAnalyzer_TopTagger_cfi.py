import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *

BoostedAnalyzer = cms.EDAnalyzer(
    'BoostedAnalyzer',
    LeptonSelectionNoTrigger,
    JetTagSelection,
    checkNoTriggers, 
    mumuTriggers = cms.vstring("None"),
    elelTriggers = cms.vstring("None"),
    elmuTriggers = cms.vstring("None"),
    minMET = cms.double(-1),
    maxMET = cms.double(800),
    dlchannel = cms.string("all"),  
    era = cms.string("2015_74x"),
    analysisType = cms.string("LJ"),
    luminosity = cms.double(10000),
    sampleID = cms.int32(9125),
    xs = cms.double(831.76),
    nMCEvents = cms.int32(25446993),
    isData = cms.bool(False),
    useFatJets = cms.bool(True),
    useForwardJets = cms.bool(False),
    useGenHadronMatch = cms.bool(False),
    dumpSyncExe = cms.bool(False),
    dumpSyncExe2 = cms.bool(False),
    outfileName = cms.string("BoostedTTH"),
    selectionNames = cms.vstring("VertexSelection","LeptonSelection"),
    makeSystematicsTrees = cms.bool(False),
    processorNames = cms.vstring("WeightProcessor","MCMatchVarProcessor","BoostedMCMatchVarProcessor","BoostedJetVarProcessor")
)
