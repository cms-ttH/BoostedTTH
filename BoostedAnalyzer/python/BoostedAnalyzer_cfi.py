import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *

BoostedAnalyzer = cms.EDAnalyzer(
    'BoostedAnalyzer',
    LeptonSelection,
    JetTagSelection,  
    relevantTriggers = cms.vstring("HLT_IsoMu24_eta2p1_IterTrk02_v1","HLT_Ele27_eta2p1_WP85_Gsf_v1","HLT_Ele23_Ele12_CaloId_TrackId_Iso_v1","HLT_Mu30_TkMu11_v1","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1","HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v1","HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v1"),
    era = cms.string("2015_72x"),
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
    makeSystematicsTrees = cms.bool(False),
    processorNames = cms.vstring("WeightProcessor","MCMatchVarProcessor","BoostedMCMatchVarProcessor","MVAVarProcessor","BoostedJetVarProcessor","BoostedTopHiggsVarProcessor","BoostedTopVarProcessor","BoostedHiggsVarProcessor")
)
