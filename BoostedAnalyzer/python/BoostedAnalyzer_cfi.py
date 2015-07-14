import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *

BoostedAnalyzer = cms.EDAnalyzer(
    'BoostedAnalyzer',
    LeptonSelection,
    JetTagSelection, 
#    relevantTriggers = cms.vstring("HLT_IsoMu24_eta2p1_IterTrk02_v1","HLT_Ele27_eta2p1_WP85_Gsf_v1","HLT_Ele23_Ele12_CaloId_TrackId_Iso_v1","HLT_Mu30_TkMu11_v1","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1","HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v1","HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v1"),
    relevantTriggers = cms.vstring("HLT_IsoMu24_eta2p1_v2","HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v1"),
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
    useFatJets = cms.bool(False),
    useForwardJets = cms.bool(False),
    useGenHadronMatch = cms.bool(False),
    dumpSyncExe = cms.bool(False),
    dumpSyncExe2 = cms.bool(False),
    outfileName = cms.string("BoostedTTH"),
    selectionNames = cms.vstring("VertexSelection","LeptonSelection"),
    makeSystematicsTrees = cms.bool(False),
    processorNames = cms.vstring("WeightProcessor","MCMatchVarProcessor","BoostedMCMatchVarProcessor","MVAVarProcessor","BoostedJetVarProcessor","BoostedTopHiggsVarProcessor","BoostedTopVarProcessor","BoostedHiggsVarProcessor")
)
