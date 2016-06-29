import FWCore.ParameterSet.Config as cms

NominalPUWeight = cms.PSet(
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/Fall15_NumTruePU.root"),
    histNameMCNPU = cms.string("h_numTruePVs"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2015/DataPileupHistogram_Run2015D-ReReco-Silver-v2_Fall15_MinBias69000.root"),
    histNameDataNPUEstimated = cms.string("pileup")
    )

AdditionalPUWeights = cms.VPSet(
    cms.PSet(
        namePUWeight = cms.string("Weight_PU_80mb"),
        fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/Spring15_NumTruePU.root"),
        histNameMCNPU = cms.string("h_numTruePVs"),
        fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2015/DataPileupHistogram_Run2015D-PromptReco-Silver_MinBias80000.root"),
        histNameDataNPUEstimated = cms.string("pileup")
        ),
    cms.PSet(
        namePUWeight = cms.string("Weight_PUdown"),
        fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/Fall15_NumTruePU.root"),
        histNameMCNPU = cms.string("h_numTruePVs"),
        fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2015/DataPileupHistogram_Run2015D-ReReco-Silver-v2_Fall15_MinBias65550.root"),
        histNameDataNPUEstimated = cms.string("pileup")
        ),
        cms.PSet(
        namePUWeight = cms.string("Weight_PUup"),
        fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/Fall15_NumTruePU.root"),
        histNameMCNPU = cms.string("h_numTruePVs"),
        fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2015/DataPileupHistogram_Run2015D-ReReco-Silver-v2_Fall15_MinBias72450.root"),
        histNameDataNPUEstimated = cms.string("pileup")
        )
)
