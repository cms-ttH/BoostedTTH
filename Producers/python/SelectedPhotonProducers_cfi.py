import FWCore.ParameterSet.Config as cms

SelectedPhotonProducer2017 = cms.EDProducer(
    "SelectedPhotonProducer",
    
    isData       = cms.bool(False),
    
    era = cms.string("2017"),

    photons = cms.InputTag("slimmedPhotons"),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),

    ptMins   = cms.vdouble(15),
    etaMaxs  = cms.vdouble(2.4),
    IDs = cms.vstring("loose"),
    collectionNames= cms.vstring("selectedPhotons"),
    
    useDeterministicSeeds = cms.bool(False),
    
    ea_dir = cms.string("BoostedTTH/Producers/data/effAreaPhotons_cone03_pfNeuHadronsAndPhotons_94X.txt"),
    file_PhoLooseIDSF=cms.string("BoostedTTH/Producers/data/electronSFs/2017_PhotonLoose_Fall17V2.root"),
    file_PhoMediumIDSF=cms.string("BoostedTTH/Producers/data/electronSFs/2017_PhotonMedium_Fall17V2.root"),
    file_PhoTightIDSF=cms.string("BoostedTTH/Producers/data/electronSFs/2017_PhotonTight_Fall17V2.root"),
    file_PhoRecoSF_highPt=cms.string("BoostedTTH/Producers/data/electronSFs/2017_PhotonReco.root"),
    file_PhoRecoSF_lowPt=cms.string("BoostedTTH/Producers/data/electronSFs/2017_PhotonReco_lowpt.root"),
    
    )

SelectedPhotonProducer2016 = SelectedPhotonProducer2017.clone(
    era = cms.string("2016"),
    file_PhoLooseIDSF=cms.string("BoostedTTH/Producers/data/electronSFs/2016_PhotonLoose_Fall17V2.root"),
    file_PhoMediumIDSF=cms.string("BoostedTTH/Producers/data/electronSFs/2016_PhotonMedium_Fall17V2.root"),
    file_PhoTightIDSF=cms.string("BoostedTTH/Producers/data/electronSFs/2016_PhotonTight_Fall17V2.root"),
    file_PhoRecoSF_highPt=cms.string("BoostedTTH/Producers/data/electronSFs/2016_PhotonReco.root"),
    file_PhoRecoSF_lowPt=cms.string("BoostedTTH/Producers/data/electronSFs/2016_PhotonReco_lowpt.root")
    )

SelectedPhotonProducer2018 = SelectedPhotonProducer2017.clone(
    era = cms.string("2018"),
    file_PhoLooseIDSF=cms.string("BoostedTTH/Producers/data/electronSFs/2018_PhotonLoose_Fall17V2.root"),
    file_PhoMediumIDSF=cms.string("BoostedTTH/Producers/data/electronSFs/2018_PhotonMedium_Fall17V2.root"),
    file_PhoTightIDSF=cms.string("BoostedTTH/Producers/data/electronSFs/2018_PhotonTight_Fall17V2.root"),
    file_PhoRecoSF_highPt=cms.string("BoostedTTH/Producers/data/electronSFs/2018_PhotonReco.root"),
    file_PhoRecoSF_lowPt=cms.string("BoostedTTH/Producers/data/electronSFs/2018_PhotonReco.root")
    )
