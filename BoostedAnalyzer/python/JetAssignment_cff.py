import FWCore.ParameterSet.Config as cms

# PU weights
# ------------------------------------------------------------

#2018
JetAssignment2017 = cms.PSet(
    ttbar_weightpath = cms.string("BoostedTTH/BoostedAnalyzer/data/bdtweights/BDTrecoTTBar_expert_BDT.weights.xml")
)