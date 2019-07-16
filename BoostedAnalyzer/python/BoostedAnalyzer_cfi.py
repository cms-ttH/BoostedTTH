import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *
from BoostedTTH.BoostedAnalyzer.Inputs_cff import *
from BoostedTTH.BoostedAnalyzer.Weights_cff import *

BoostedAnalyzer2017 = cms.EDAnalyzer(
    'BoostedAnalyzer',
    Inputs_tth_sl, # defined in Inputs_cff
    #DiLeptonSelectionMC, # defined in Selection_cff
    #JetTagSelection, # defined in Selection_cff
    METSelection, # defined in Selection_cff
    checkBasicMCTriggers, # defined in Selection_cff
    # filtersMC, # defined in Selection_cff
    MonoTopSelection,
    
    #LeptonSelection = LeptonSelectionMC2017,
    
    # weight of one event: calculated as
    # cross section * lumi / (number of generated events with positive weight  -  number of generated events with negative weight )
    # so that the sum of weights corresponds to the number of events for the given lumi
    eventWeight = cms.double(1.),
    isData = cms.bool(False),
    dataset=cms.string("NA"),
    dataEra = cms.string("2017"),

    # b-tag SF, defined in Weights_cff
    bTagSFs = BTagSFs94XDeepJet2017,

    # PU weights, defined in Weights_cff
    nominalPUWeight = NominalPUWeight2017,
    additionalPUWeights = AdditionalPUWeights2017,

    # information about lepton trigger SFs, defined in Weights_cff
    leptonTriggerSFInfos = TriggerSFs2017,

    #MET Filters
    METfilters = filtersMC1718,

    systematics = cms.vstring(""),
    doJERsystematic = cms.bool(False),

    generatorName = cms.string("notSpecified"),

    isreHLT = cms.bool(False),

    useFatJets = cms.bool(True),
    useForwardJets = cms.bool(False),
    useGenHadronMatch = cms.bool(True),

    dumpSyncExe = cms.bool(False),
    dumpExtended = cms.bool(False),
    dumpAlwaysEvents = cms.vint32(),
    doBoostedMEM = cms.bool(True),
    
    memNtuples = cms.bool(False),

    minJetsForMEM = cms.int32(4),
    minTagsForMEM = cms.int32(3),

    selectionNames = cms.vstring("VertexSelection","LeptonSelection"),
    processorNames = cms.vstring("WeightProcessor","MCMatchVarProcessor","BoostedMCMatchVarProcessor","BasicVarProcessor","MVAVarProcessor","BDTVarProcessor","TriggerVarProcessor","BoostedJetVarProcessor","BoostedTopHiggsVarProcessor", "AK8JetProcessor", "SelectionTagProcessor"),
    outfileName = cms.string("BoostedTTH"),

    taggingSelection=cms.bool(False),
)

BoostedAnalyzer2016 = BoostedAnalyzer2017.clone(
    #LeptonSelection = LeptonSelectionMC2016,    
    dataEra = cms.string("2016"),
    bTagSFs = BTagSFs94XDeepJet2016,
    leptonTriggerSFInfos = TriggerSFs2016,
    nominalPUWeight = NominalPUWeight2016,
    additionalPUWeights = AdditionalPUWeights2016,
    METfilters = filtersMC16   
)

BoostedAnalyzer2018 = BoostedAnalyzer2017.clone(
    #LeptonSelection = LeptonSelectionMC2018,
    dataEra = cms.string("2018"),
    bTagSFs = BTagSFs94XDeepJet2018,
    leptonTriggerSFInfos = TriggerSFs2018,
    nominalPUWeight = NominalPUWeight2018,
    additionalPUWeights = AdditionalPUWeights2018
    
)
