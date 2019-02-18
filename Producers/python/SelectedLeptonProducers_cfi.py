# Default lepton selection of the "loose electrons/muons" defined at
# https://twiki.cern.ch/twiki/bin/view/CMS/TTbarHbbRun2ReferenceAnalysis#Object_selection_SPRING15

import FWCore.ParameterSet.Config as cms

SelectedElectronProducer = cms.EDProducer(
    "SelectedLeptonProducer",
    leptonType = cms.string("electron"),

    era          = cms.string("NA"),
    analysisType = cms.string("LJ"),
    isData       = cms.bool(False),

    leptons = cms.InputTag("slimmedElectrons"),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    #eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-medium","","boostedAnalysis"),
    #eleLooseIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-loose","","boostedAnalysis"),
    #eleVetoIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-veto","","boostedAnalysis"),
    #eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-tight","","boostedAnalysis"),

    ptMins   = cms.vdouble(15),
    etaMaxs  = cms.vdouble(2.4),
    leptonIDs = cms.vstring("loose"),
    collectionNames= cms.vstring("selectedElectronsLoose"),


    # The following two parameters are dummies in case of electrons
    # they are not used for the electron selection, which is defined
    # via the 'leptonID' value
    isoConeSizes = cms.vstring("R03"),
    isoCorrTypes = cms.vstring("rhoEA"),
    muonIsoTypes = cms.vstring("loose"),
    useMuonRC = cms.bool(True),
    useDeterministicSeeds = cms.bool(False),
    rc_dir = cms.string("BoostedTTH/Producers/data/rcdata2017v1/RoccoR2017v1.txt"),
    ea_dir = cms.string("BoostedTTH/Producers/data/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt")
    )


SelectedMuonProducer = cms.EDProducer(
    "SelectedLeptonProducer",
    leptonType = cms.string("muon"),

    era          = cms.string("NA"),
    analysisType = cms.string("LJ"),
    isData       = cms.bool(False),

    leptons = cms.InputTag("slimmedMuons"),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),

    ptMins   = cms.vdouble(15),
    etaMaxs  = cms.vdouble(2.4),
    leptonIDs = cms.vstring("loose"),
    collectionNames= cms.vstring("selectedMuonsLoose"),
    isoConeSizes = cms.vstring("R04"),
    isoCorrTypes = cms.vstring("deltaBeta"),
    muonIsoTypes = cms.vstring("loose"),
    useMuonRC = cms.bool(True),
    useDeterministicSeeds = cms.bool(False),
    rc_dir = cms.string("BoostedTTH/Producers/data/rcdata2017v1/RoccoR2017v1.txt"),
    ea_dir = cms.string("BoostedTTH/Producers/data/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt")
    # The following two parameters are dummies in case of muons
    # they are not used for the muon selection, which is defined
    # via the 'leptonID' value
    #eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-medium","","boostedAnalysis"),
    #eleLooseIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-loose","","boostedAnalysis"),
    #eleVetoIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-veto","","boostedAnalysis"),
    #eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-tight","","boostedAnalysis"),
    )
