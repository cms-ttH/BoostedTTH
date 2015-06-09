import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *

BoostedAnalyzer = cms.EDAnalyzer(
    'BoostedAnalyzer',
    LeptonSelection,
    JetTagSelection,  
    era = cms.string("2015_72x"),
    analysisType = cms.string("LJ"),
    luminosity = cms.double(10000),
    sampleID = cms.int32(9125),
    xs = cms.double(831.76),
    nMCEvents = cms.int32(25446993),
    isData = cms.bool(False),
    useFatJets = cms.bool(True),
    disableObjectSelections = cms.bool(False), # disables selection of some objects for synch exe
    outfileName = cms.string("BoostedTTH"),
    selectionNames = cms.vstring(""),
    processorNames = cms.vstring("WeightProcessor","MCMatchVarProcessor","MVAVarProcessor","BoostedJetVarProcessor")
)
