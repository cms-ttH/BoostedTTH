import FWCore.ParameterSet.Config as cms

NominalPUWeight = cms.PSet(
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/Spring16_25nsV1_NumTruePU.root"),
    histNameMCNPU = cms.string("hNumTruePUPdf"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2016/DataPileupHistogram_Run2016B-PromptReco-271036-275125_MinBias71300.root"),
    histNameDataNPUEstimated = cms.string("pileup")
    )

AdditionalPUWeights = cms.VPSet()
