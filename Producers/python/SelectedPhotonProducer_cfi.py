import FWCore.ParameterSet.Config as cms

SelectedPhotonProducer = cms.EDProducer(
    "SelectedPhotonProducer",

    photons = cms.InputTag("slimmedPhotons"),
    phoLooseIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-loose"),
    phoMediumIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-medium"),
    phoTightIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-tight"),

    ptMins   = cms.vdouble(15),
    etaMaxs  = cms.vdouble(2.5),
    collectionNames= cms.vstring("selectedPhotonsLoose"),
    IDs= cms.vstring("loose")
    )