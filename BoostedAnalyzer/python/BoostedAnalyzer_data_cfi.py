import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *
from BoostedTTH.BoostedAnalyzer.Inputs_cff import *

BoostedAnalyzer = cms.EDAnalyzer(
    'BoostedAnalyzer',
    Inputs_tth_sl, # defined in Inputs_cff
    #LeptonSelectionData, # defined in Selection_cff
    #DiLeptonSelectionData, # defined in Selection_cff
    #JetTagSelection, # defined in Selection_cff
    METSelection, # defined in Selection_cff
    checkBasicDataTriggers, # defined in Selection_cff
    filtersData, # defined in Selection_cff
    MonoJetSelection,

    era = cms.string("2016_80X"), # has little effect so far, might become important for MiniAODhelper
    analysisType = cms.string("LJ"), # has little effect so far, might become important for MiniAODhelper
    sampleID = cms.int32(9125), # has little effect so far, might become important for MiniAODhelper

    eventWeight = cms.double(1.),
    isData = cms.bool(True),
    datasetFlag=cms.int32(0),

    recorrectMET = cms.bool(True),

    systematics = cms.vstring(""),
    doJERsystematic = cms.bool(False),
    generatorName = cms.string("notSpecified"),

    useFatJets = cms.bool(False),
    useForwardJets = cms.bool(False),
    useGenHadronMatch = cms.bool(False),

    dumpSyncExe = cms.bool(False),
    dumpExtended = cms.bool(False),
    dumpAlwaysEvents = cms.vint32(),

    doBoostedMEM = cms.bool(True),
    
    memNtuples = cms.bool(False),

    minJetsForMEM = cms.int32(4),
    minTagsForMEM = cms.int32(3),

    selectionNames = cms.vstring("FilterSelection","VertexSelection","METSelection","MonoJetSelection","LeptonVetoSelection","BTagVetoSelection","PhotonVetoSelection"),
    processorNames = cms.vstring("WeightProcessor","TriggerVarProcessor","DarkMatterProcessor"),

    outfileName = cms.string("BoostedTTH"),
)
