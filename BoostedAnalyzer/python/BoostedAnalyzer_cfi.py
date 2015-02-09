import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *

BoostedAnalyzer = cms.EDAnalyzer('BoostedAnalyzer',
  LeptonSelectionNoTrigger,
  JetTagSelection,  
  era = cms.string("2012_53x"),
  sampleID = cms.int32(9125),
  isData = cms.bool(True),
  analysisType = cms.string("LJ"),
  outfileName = cms.string("test"),
  selectionNames = cms.vstring("LeptonSelection","JetTagSelection"),
  processorNames = cms.vstring("MVAVarProcessor")
)
