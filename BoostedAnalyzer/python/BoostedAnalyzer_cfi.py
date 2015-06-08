import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *

BoostedAnalyzer = cms.EDAnalyzer(
    'BoostedAnalyzer',
    LeptonSelection,
    JetTagSelection,  
    relevantTriggers = cms.vstring("HLT_IsoMu24_eta2p1_v1","HLT_Ele27_eta2p1_WP85_Gsf_HT200_v1"),
    era = cms.string("2012_53x"),
    analysisType = cms.string("LJ"),
    luminosity = cms.double(10000.),
    sampleID = cms.int32(9125),
    xs = cms.double(0.5),
    nMCEvents = cms.int32(100000),
    isData = cms.bool(False),
    useFatJets = cms.bool(False),
    useGenHadronMatch = cms.bool(False),
    dumpSyncExe = cms.bool(False),
    outfileName = cms.string("BoostedTTH"),
    selectionNames = cms.vstring("VertexSelection","LeptonSelection"),
    systematicType = cms.string("nominal"),
    processorNames = cms.vstring("WeightProcessor","MCMatchVarProcessor","BoostedMCMatchVarProcessor","MVAVarProcessor","BoostedJetVarProcessor","BoostedTopHiggsVarProcessor","BoostedTopVarProcessor","BoostedHiggsVarProcessor")
)
