import FWCore.ParameterSet.Config as cms

# PU weights
# ------------------------------------------------------------
NominalPUWeight = cms.PSet(
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/Summer16_NumTruePU.root"),
    histNameMCNPU = cms.string("hNumTruePUPdf"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2016/DataPileupHistogram_Run2016-Complete_MinBias69200.root"),
    histNameDataNPUEstimated = cms.string("pileup")
)
AdditionalPUWeights = cms.VPSet(
  cms.PSet(
    namePUWeight = cms.string("Weight_pu69p2"),
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/Summer16_NumTruePU.root"),
    histNameMCNPU = cms.string("hNumTruePUPdf"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2016/DataPileupHistogram_Run2016-Complete_MinBias69200.root"),
    histNameDataNPUEstimated = cms.string("pileup")
  ),
  cms.PSet(
    namePUWeight = cms.string("Weight_pu69p2"),
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/Summer16_NumTruePU.root"),
    histNameMCNPU = cms.string("hNumTruePUPdf"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2016/DataPileupHistogram_Run2016-Complete_MinBias69200.root"),
    histNameDataNPUEstimated = cms.string("pileup")
  ),
  cms.PSet(
    namePUWeight = cms.string("Weight_pu69p2"),
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/Summer16_NumTruePU.root"),
    histNameMCNPU = cms.string("hNumTruePUPdf"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2016/DataPileupHistogram_Run2016-Complete_MinBias69200.root"),
    histNameDataNPUEstimated = cms.string("pileup")
  ),

  cms.PSet(
    namePUWeight = cms.string("Weight_pu69p2Up"),
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/Summer16_NumTruePU.root"),
    histNameMCNPU = cms.string("hNumTruePUPdf"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2016/DataPileupHistogram_Run2016-Complete_MinBias72383.root"),
    histNameDataNPUEstimated = cms.string("pileup")
  ),

  cms.PSet(
    namePUWeight = cms.string("Weight_pu69p2Down"),
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/Summer16_NumTruePU.root"),
    histNameMCNPU = cms.string("hNumTruePUPdf"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2016/DataPileupHistogram_Run2016-Complete_MinBias66017.root"),
    histNameDataNPUEstimated = cms.string("pileup")
  ),
  
)


# B-tagging SF
# ------------------------------------------------------------
# The 76X SF
BTagSFs76X = cms.PSet(
    fileNameHF = cms.string("MiniAOD/MiniAODHelper/data/csv_rwt_fit_hf_76x_2016_02_08.root"),
    nHFPtBins = cms.int32(5),
    fileNameLF = cms.string("MiniAOD/MiniAODHelper/data/csv_rwt_fit_lf_76x_2016_02_08.root")
)

# The 80X SF
BTagSFs80X = cms.PSet(
    fileNameHF = cms.string("MiniAOD/MiniAODHelper/data/csv_rwt_fit_hf_v2_final_2017_1_10test.root"),
    nHFPtBins = cms.int32(5),
    fileNameLF = cms.string("MiniAOD/MiniAODHelper/data/csv_rwt_fit_lf_v2_final_2017_1_10test.root")
)
