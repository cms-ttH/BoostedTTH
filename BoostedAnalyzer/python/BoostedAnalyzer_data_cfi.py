import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *
from BoostedTTH.BoostedAnalyzer.Inputs_cff import *

BoostedAnalyzer2017 = cms.EDAnalyzer(
    'BoostedAnalyzer',
    Inputs_tth_sl, # defined in Inputs_cff
    DiLeptonSelectionData, # defined in Selection_cff
    JetTagSelection, # defined in Selection_cff
    METSelection, # defined in Selection_cff
    checkBasicDataTriggers, # defined in Selection_cff
    # filtersMC, # defined in Selection_cff
    MonoTopSelection,
    
    LeptonSelection = LeptonSelectionData2017,

    era = cms.string("2016_80X"), # has little effect so far, might become important for MiniAODhelper
    analysisType = cms.string("LJ"), # has little effect so far, might become important for MiniAODhelper
    sampleID = cms.int32(9125), # has little effect so far, might become important for MiniAODhelper

    eventWeight = cms.double(1.),
    isData = cms.bool(True),
    datasetFlag=cms.int32(0),
    dataEra = cms.string("2017"),

   #MET Filters
    METfilters = filtersData1718,

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

    selectionNames = cms.vstring("VertexSelection","LeptonSelection"),
    processorNames = cms.vstring("WeightProcessor","BasicVarProcessor","MVAVarProcessor","BDTVarProcessor","TriggerVarProcessor","BoostedJetVarProcessor","BoostedTopHiggsVarProcessor", "AK8JetProcessor", "SelectionTagProcessor"),

    outfileName = cms.string("BoostedTTH"),
    taggingSelection=cms.bool(False)
)

BoostedAnalyzer2016 = BoostedAnalyzer2017.clone(
    dataEra = cms.string("2016"),
    LeptonSelection = LeptonSelectionData2016,
    METfilters = filtersData16
)

BoostedAnalyzer2018 = BoostedAnalyzer2017.clone(
    dataEra = cms.string("2018"),
    LeptonSelection = LeptonSelectionData2018
)
