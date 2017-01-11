import FWCore.ParameterSet.Config as cms
jecpath='BJetnessTTHbb/BJetness/data/'

BJetness = cms.EDProducer(
    'BJetness',
    is_data   = cms.bool(False),
    vertices            = cms.InputTag("offlineSlimmedPrimaryVertices"),
    patElectrons        = cms.InputTag("slimmedElectrons"),
    eleMVAnonTrigIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring16-GeneralPurpose-V1-wp80"),                                       
    muons               = cms.InputTag("slimmedMuons"),
    jets                = cms.InputTag("slimmedJets"),
    jecPayloadNamesAK4PFchsMC1 = cms.FileInPath(jecpath+"JEC/MC/Spring16_25nsV6_MC_L1FastJet_AK4PFchs.txt"),
    jecPayloadNamesAK4PFchsMC2 = cms.FileInPath(jecpath+"JEC/MC/Spring16_25nsV6_MC_L2Relative_AK4PFchs.txt"),
    jecPayloadNamesAK4PFchsMC3 = cms.FileInPath(jecpath+"JEC/MC/Spring16_25nsV6_MC_L3Absolute_AK4PFchs.txt"),
    jecPayloadNamesAK4PFchsMCUnc = cms.FileInPath(jecpath+"JEC/MC/Spring16_25nsV6_MC_Uncertainty_AK4PFchs.txt"),
    jecPayloadNamesAK4PFchsDATA1 = cms.FileInPath(jecpath+"JEC/DATA/Spring16_25nsV6_DATA_L1FastJet_AK4PFchs.txt"),
    jecPayloadNamesAK4PFchsDATA2 = cms.FileInPath(jecpath+"JEC/DATA/Spring16_25nsV6_DATA_L2Relative_AK4PFchs.txt"),
    jecPayloadNamesAK4PFchsDATA3 = cms.FileInPath(jecpath+"JEC/DATA/Spring16_25nsV6_DATA_L3Absolute_AK4PFchs.txt"),
    jecPayloadNamesAK4PFchsDATA4 = cms.FileInPath(jecpath+"JEC/DATA/Spring16_25nsV6_DATA_L2L3Residual_AK4PFchs.txt"),
    jecPayloadNamesAK4PFchsDATAUnc = cms.FileInPath(jecpath+"JEC/DATA/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt"),
    jerAK4PFchs   = cms.FileInPath(jecpath+"JER/Spring16_25nsV6_MC_PtResolution_AK4PFchs.txt"),
    jerAK4PFchsSF = cms.FileInPath(jecpath+"JER/Spring16_25nsV6_MC_SF_AK4PFchs.txt"),
)
