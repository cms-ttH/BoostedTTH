import FWCore.ParameterSet.Config as cms

# PU weights
# ------------------------------------------------------------
NominalPUWeight = cms.PSet(
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/MCNPUTrue.root"),
    histNameMCNPU = cms.string("MCPUDistributionProducer/NumTruePU"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2017/DataPileupHistogram_Run2017_294927-306462_13TeV_EOY2017ReReco_MinBiasNominal-69200.root"),
    histNameDataNPUEstimated = cms.string("pileup")
)
AdditionalPUWeights = cms.VPSet(
  cms.PSet(
    namePUWeight = cms.string("Weight_pu69p2"),
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/MCNPUTrue.root"),
    histNameMCNPU = cms.string("MCPUDistributionProducer/NumTruePU"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2017/DataPileupHistogram_Run2017_294927-306462_13TeV_EOY2017ReReco_MinBiasNominal-69200.root"),
    histNameDataNPUEstimated = cms.string("pileup")
  ),

  cms.PSet(
    namePUWeight = cms.string("Weight_pu69p2Up"),
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/MCNPUTrue.root"),
    histNameMCNPU = cms.string("MCPUDistributionProducer/NumTruePU"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2017/DataPileupHistogram_Run2017_294927-306462_13TeV_EOY2017ReReco_MinBiasUp-72383.root"),
    histNameDataNPUEstimated = cms.string("pileup")
  ),

  cms.PSet(
    namePUWeight = cms.string("Weight_pu69p2Down"),
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/MCNPUTrue.root"),
    histNameMCNPU = cms.string("MCPUDistributionProducer/NumTruePU"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2017/DataPileupHistogram_Run2017_294927-306462_13TeV_EOY2017ReReco_MinBiasDown-66017.root"),
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
    fileNameHF = cms.string("MiniAOD/MiniAODHelper/data/factorized_jes/csv_rwt_fit_hf_v2_final_2017_6_7_all.root"),
    #fileNameHF = cms.string("MiniAOD/MiniAODHelper/data/csv_rwt_fit_hf_v2_final_2017_3_29test.root"),
    nHFPtBins = cms.int32(5),
    nLFPtBins = cms.int32(4),
    nLFEtaBins = cms.int32(3),
    #fileNameLF = cms.string("MiniAOD/MiniAODHelper/data/csv_rwt_fit_lf_v2_final_2017_3_29test.root"),
    fileNameLF = cms.string("MiniAOD/MiniAODHelper/data/factorized_jes/csv_rwt_fit_lf_v2_final_2017_6_7_all.root")
)

# The 94X DeepCSV SF
BTagSFs94XDeepCSV = cms.PSet(
    fileNameHF = cms.string("MiniAOD/MiniAODHelper/data/deepCSV_sfs_hf.root"),
    nHFPtBins = cms.int32(5),
    nLFPtBins = cms.int32(4),
    nLFEtaBins = cms.int32(3),
    fileNameLF = cms.string("MiniAOD/MiniAODHelper/data/deepCSV_sfs_lf.root")
)





