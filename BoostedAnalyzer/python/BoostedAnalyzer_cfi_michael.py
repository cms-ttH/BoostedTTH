import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *
from BoostedTTH.BoostedAnalyzer.Weights_cff import *

BoostedAnalyzer = cms.EDAnalyzer(
    'BoostedAnalyzer',
    LeptonSelectionMC, # defined in Selection_cff
    DiLeptonSelectionMC, # defined in Selection_cff
    JetTagSelection, # defined in Selection_cff
    METSelection, # defined in Selection_cff
    checkBasicMCTriggers, # defined in Selection_cff

    era = cms.string("2015_74x"), # has little effect so far, might become important for MiniAODhelper
    analysisType = cms.string("LJ"), # has little effect so far, might become important for MiniAODhelper
    sampleID = cms.int32(9125), # has little effect so far, might become important for MiniAODhelper

    eventWeight = cms.double(1.),
    isData = cms.bool(False),
    
    recorrectMET = cms.bool(True),

    # PU weights, defined in Weights_cff
    #nominalPUWeight = cms.PSet(NominalPUWeight),
    #additionalPUWeights = cms.VPSet(AdditionalPUWeights),

    makeSystematicsTrees = cms.bool(False),
    doJERsystematic = cms.bool(False),
    generatorName = cms.string("notSpecified"),

    useFatJets = cms.bool(True),
    useForwardJets = cms.bool(False),
    useGenHadronMatch = cms.bool(True),

    dumpSyncExe = cms.bool(False),
    dumpSyncExe2 = cms.bool(False),

    doBoostedMEM = cms.bool(False),

    minJetsForMEM = cms.int32(4),
    minTagsForMEM = cms.int32(3),

    selectionNames = cms.vstring("VertexSelection","LeptonSelection"),
    processorNames = cms.vstring("WeightProcessor","MCMatchVarProcessor","BasicVarProcessor","TriggerVarProcessor","TTbarReconstructionVarProcessor","AdditionalJetProcessor","SpinCorrelationProcessor"),
    #,"DiJetVarProcessor"), -- conflict

    outfileName = cms.string("BoostedTTH"),
)
