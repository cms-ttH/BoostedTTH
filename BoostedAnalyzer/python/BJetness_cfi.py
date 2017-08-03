import FWCore.ParameterSet.Config as cms

demo = cms.EDProducer('BJetness',
  # Format
  is_data   = cms.bool(False),
  # Input tags
  vertices            = cms.InputTag("offlineSlimmedPrimaryVertices"),
  patElectrons        = cms.InputTag("slimmedElectrons"),
  eleMVAnonTrigIdMap  = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring15-25ns-nonTrig-V1-wp80"),
  electronVetoIdMap   = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-veto"),
  electronLooseIdMap  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose"),
  electronMediumIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium"),
  electronTightIdMap  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-tight"),
  muons               = cms.InputTag("slimmedMuons"),
  jets                = cms.InputTag("slimmedJets"),
  jecPayloadNamesAK4PFchsMC1 = cms.FileInPath("MiniAOD/MiniAODHelper/data/jec/Summer16_23Sep2016V4_MC_L1FastJet_AK4PFchs.txt"),
  jecPayloadNamesAK4PFchsMC2 = cms.FileInPath("MiniAOD/MiniAODHelper/data/jec/Summer16_23Sep2016V4_MC_L2Relative_AK4PFchs.txt"),
  jecPayloadNamesAK4PFchsMC3 = cms.FileInPath("MiniAOD/MiniAODHelper/data/jec/Summer16_23Sep2016V4_MC_L3Absolute_AK4PFchs.txt"),
  jecPayloadNamesAK4PFchsMCUnc = cms.FileInPath("MiniAOD/MiniAODHelper/data/jec/Summer16_23Sep2016V4_MC_Uncertainty_AK4PFchs.txt"),
  jecPayloadNamesAK4PFchsDATA1 = cms.FileInPath("MiniAOD/MiniAODHelper/data/jec/Summer16_23Sep2016BCDV4_DATA_L1FastJet_AK4PFchs.txt"),
  jecPayloadNamesAK4PFchsDATA2 = cms.FileInPath("MiniAOD/MiniAODHelper/data/jec/Summer16_23Sep2016BCDV4_DATA_L2Relative_AK4PFchs.txt"),
  jecPayloadNamesAK4PFchsDATA3 = cms.FileInPath("MiniAOD/MiniAODHelper/data/jec/Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK4PFchs.txt"),
  jecPayloadNamesAK4PFchsDATA4 = cms.FileInPath("MiniAOD/MiniAODHelper/data/jec/Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK4PFchs.txt"),
  jecPayloadNamesAK4PFchsDATAUnc = cms.FileInPath("MiniAOD/MiniAODHelper/data/jec/Summer16_23Sep2016BCDV4_DATA_Uncertainty_AK4PFchs.txt"),
  jerAK4PFchs   = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt"),
  jerAK4PFchsSF = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_SF_AK4PFchs.txt"),
)
