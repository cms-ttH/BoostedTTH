import FWCore.ParameterSet.Config as cms

# PU weights
# ------------------------------------------------------------

#2018
NominalPUWeight2018 = cms.PSet(
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/N_True2018.root"),
    histNameMCNPU = cms.string("N_True"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2017/DataPileupHistogram_Run2017_294927-306462_13TeV_EOY2017ReReco_MinBiasNominal-69200.root"),
    histNameDataNPUEstimated = cms.string("pileup")
)
AdditionalPUWeights2018 = cms.VPSet(
  cms.PSet(
    namePUWeight = cms.string("Weight_pu69p2"),
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/N_True2018.root"),
    histNameMCNPU = cms.string("N_True"),
    fileNameDataNPUEstimated = cms.string("MiniAODHelper/data/puweights/Run2018/DataPileupHistogram_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_MinBiasNominal-69200.root"),
    histNameDataNPUEstimated = cms.string("pileup")
  ),

  cms.PSet(
    namePUWeight = cms.string("Weight_pu69p2Up"),
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/N_True2018.root"),
    histNameMCNPU = cms.string("N_True"),
    fileNameDataNPUEstimated = cms.string("MiniAODHelper/data/puweights/Run2018/DataPileupHistogram_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_MinBiasUp-72383.root"),
    histNameDataNPUEstimated = cms.string("pileup")
  ),

  cms.PSet(
    namePUWeight = cms.string("Weight_pu69p2Down"),
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/N_True2018.root"),
    histNameMCNPU = cms.string("N_True"),
    fileNameDataNPUEstimated = cms.string("MiniAODHelper/data/puweights/Run2018/DataPileupHistogram_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_MinBiasDown-66017.root"),
    histNameDataNPUEstimated = cms.string("pileup")
  ),
)

#2017
NominalPUWeight2017 = cms.PSet(
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/MCNPUTrue.root"),
    histNameMCNPU = cms.string("MCPUDistributionProducer/NumTruePU"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2017/DataPileupHistogram_Run2017_294927-306462_13TeV_EOY2017ReReco_MinBiasNominal-69200.root"),
    histNameDataNPUEstimated = cms.string("pileup")
)
AdditionalPUWeights2017 = cms.VPSet(
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

# 2016
NominalPUWeight2016 = cms.PSet(
    fileNameMCNPU = cms.string("MiniAOD/MiniAODHelper/data/puweights/MC/Summer16_NumTruePU.root"),
    histNameMCNPU = cms.string("hNumTruePUPdf"),
    fileNameDataNPUEstimated = cms.string("MiniAOD/MiniAODHelper/data/puweights/Run2016/DataPileupHistogram_Run2016-Complete_MinBias69200.root"),
    histNameDataNPUEstimated = cms.string("pileup")
)
AdditionalPUWeights2016 = cms.VPSet(
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
    fileNameHF = cms.string("MiniAOD/MiniAODHelper/data/sfs_deepcsv_2017_hf.root"),
    nHFPtBins = cms.int32(5),
    nLFPtBins = cms.int32(4),
    nLFEtaBins = cms.int32(3),
    fileNameLF = cms.string("MiniAOD/MiniAODHelper/data/sfs_deepcsv_2017_lf.root")
)

# The 94X DeepJet SF
BTagSFs94XDeepJet2018 = cms.PSet(
    fileNameHF = cms.string("MiniAOD/MiniAODHelper/data/sfs_deepjet_2018_hf.root"),
    nHFPtBins = cms.int32(5),
    nLFPtBins = cms.int32(4),
    nLFEtaBins = cms.int32(3),
    fileNameLF = cms.string("MiniAOD/MiniAODHelper/data/sfs_deepjet_2018_lf.root")
)
BTagSFs94XDeepJet2017 = cms.PSet(
    fileNameHF = cms.string("MiniAOD/MiniAODHelper/data/sfs_deepjet_2017_hf.root"),
    nHFPtBins = cms.int32(5),
    nLFPtBins = cms.int32(4),
    nLFEtaBins = cms.int32(3),
    fileNameLF = cms.string("MiniAOD/MiniAODHelper/data/sfs_deepjet_2017_lf.root")
)
BTagSFs94XDeepJet2016 = cms.PSet(
    fileNameHF = cms.string("MiniAOD/MiniAODHelper/data/sfs_deepjet_2016_hf.root"),
    nHFPtBins = cms.int32(5),
    nLFPtBins = cms.int32(4),
    nLFEtaBins = cms.int32(3),
    fileNameLF = cms.string("MiniAOD/MiniAODHelper/data/sfs_deepjet_2016_lf.root")
)




