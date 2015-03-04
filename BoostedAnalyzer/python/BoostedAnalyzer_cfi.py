import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *

BoostedAnalyzer = cms.EDAnalyzer(
    'BoostedAnalyzer',
    LeptonSelectionNoTrigger,
    JetTagSelection,  
    era = cms.string("2012_53x"),
    analysisType = cms.string("LJ"),
    luminostiy = cms.double(19.7),
    sampleID = cms.int32(9125),
    xs = cms.double(248),
    nMCEvents = cms.int32(25000000),
    isData = cms.bool(True),
    useFatJets = cms.bool(False),
    disableObjectSelections = cms.bool(False), # disables selection of some objects for synch exe
    outfileName = cms.string("BoostedTTH"),
    selectionNames = cms.vstring("LeptonSelection"),
    processorNames = cms.vstring("MVAVarProcessor","BoostedJetVarProcessor","BoostedTopHiggsVarProcessor","BoostedTopVarProcessor","BoostedHiggsVarProcessor")
)
