import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *
from BoostedTTH.BoostedAnalyzer.VarProcessors_cff import *

BoostedAnalyzer = cms.EDAnalyzer(
    'BoostedAnalyzer',

    # Selection-specific config blocks, # defined in Selection_cff
    LeptonSelectionMC,
    DiLeptonSelectionMC,
    JetTagSelection,
    METSelection,
    checkBasicMCTriggers, 
    
    # VarProcessor-specific config blocks, defined in VarProcessors_cff
    DiJetVarProcessor,

    era = cms.string("2015_74x"), # has little effect so far, might become important for MiniAODhelper
    analysisType = cms.string("LJ"), # has little effect so far, might become important for MiniAODhelper
    sampleID = cms.int32(9125), # has little effect so far, might become important for MiniAODhelper


    eventWeight = cms.double(1.),
    isData = cms.bool(False),

    makeSystematicsTrees = cms.bool(False),

    useFatJets = cms.bool(True),
    useForwardJets = cms.bool(False),
    useGenHadronMatch = cms.bool(True),

    dumpSyncExe = cms.bool(False),
    dumpSyncExe2 = cms.bool(False),

    selectionNames = cms.vstring("VertexSelection","LeptonSelection"),
    processorNames = cms.vstring("WeightProcessor","MCMatchVarProcessor","BoostedMCMatchVarProcessor","BasicVarProcessor","MVAVarProcessor","BDTVarProcessor","DiLeptonVarProcessor","TriggerVarProcessor","BoostedJetVarProcessor","BoostedTopHiggsVarProcessor","BoostedTopVarProcessor","BoostedHiggsVarProcessor"),
    #,"DiJetVarProcessor"), -- conflict

    outfileName = cms.string("BoostedTTH"),

    # Input collections
    # Not yet fully configurable, only change for dijet analysis
    # Else, keep default values to guarantee consistency
    jets = cms.InputTag("slimmedJets","",""),
)
