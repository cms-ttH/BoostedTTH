import FWCore.ParameterSet.Config as cms
from BoostedTTH.StandardAnalyzer.Selection_cff import *

StandardAnalyzer = cms.EDAnalyzer(
    'StandardAnalyzer',
    LeptonSelection,
    JetTagSelection,
    relevantTriggers = cms.vstring("HLT_IsoMu24_eta2p1_v1","HLT_Ele27_eta2p1_WP85_Gsf_HT200_v1"),
    era = cms.string("2015_74x"),
    analysisType = cms.string("LJ"),
    luminosity = cms.double(10000.),
    sampleID = cms.int32(9125),
    xs = cms.double(0.5),
    nMCEvents = cms.int32(100000),
    isData = cms.bool(False),
    useGenHadronMatch = cms.bool(False),
    outfileName = cms.string("RUNIIComp"),
    selectionNames = cms.vstring("VertexSelection","LeptonSelection"),
    processorNames = cms.vstring("WeightProcessor","MCMatchVarProcessor","MVAVarProcessor","BoostedJetVarProcessor","BoostedTopHiggsVarProcessor","BoostedTopVarProcessor","BoostedHiggsVarProcessor")
)
