import FWCore.ParameterSet.Config as cms

#2017
JetAssignment2017 = cms.PSet(
    ttbar_even_weightpath = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/2017/ttbar_even_weights.xml"),
    ttbar_odd_weightpath = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/2017/ttbar_odd_weights.xml"),
    ttbar_varlist = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/2017/ttbar_variables.csv"),

    ttH_even_weightpath = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/2017/ttH_even_weights.xml"),
    ttH_odd_weightpath = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/2017/ttH_odd_weights.xml"),
    ttH_varlist = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/2017/ttH_variables.csv"),

    thq_even_weightpath = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/2017/tHq_even_weights.xml"),
    thq_odd_weightpath = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/2017/tHq_odd_weights.xml"),
    thq_varlist = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/2017/tHq_variables.csv"),

    thw_even_weightpath = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/2017/tHW_even_weights.xml"),
    thw_odd_weightpath = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/2017/tHW_odd_weights.xml"),
    thw_varlist = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/2017/tHW_variables.csv"),

)
JetAssignment2016 = JetAssignment2017.clone()
JetAssignment2018 = JetAssignment2017.clone()
