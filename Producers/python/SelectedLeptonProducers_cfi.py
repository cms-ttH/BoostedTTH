# Default lepton selection of the "loose electrons/muons" defined at
# https://twiki.cern.ch/twiki/bin/view/CMS/TTbarHbbRun2ReferenceAnalysis#Object_selection_SPRING15

import FWCore.ParameterSet.Config as cms

SelectedElectronProducer2017 = cms.EDProducer(
    "SelectedLeptonProducer",
    leptonType=cms.string("electron"),
    isData=cms.bool(False),
    era=cms.string("2017"),
    leptons=cms.InputTag("slimmedElectrons"),
    vertices=cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho=cms.InputTag("fixedGridRhoFastjetAll"),
    # eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-medium","","boostedAnalysis"),
    # eleLooseIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-loose","","boostedAnalysis"),
    # eleVetoIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-veto","","boostedAnalysis"),
    # eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-tight","","boostedAnalysis"),
    ptMins=cms.vdouble(15),
    etaMaxs=cms.vdouble(2.4),
    leptonIDs=cms.vstring("loose"),
    collectionNames=cms.vstring("selectedElectronsLoose"),
    isoConeSizes=cms.vstring("R03"),
    isoCorrTypes=cms.vstring("rhoEA"),
    muonIsoTypes=cms.vstring("loose"),
    useMuonRC=cms.bool(False),
    useDeterministicSeeds=cms.bool(False),
    rc_dir=cms.string("BoostedTTH/Producers/data/muonSFs/RoccoR2017.txt"),
    ea_dir=cms.string(
        "BoostedTTH/Producers/data/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt"
    ),
    file_EleLooseIDSF=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2017_ElectronLoose_Fall17V2.root"
    ),
    file_EleMediumIDSF=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2017_ElectronMedium_Fall17V2.root"
    ),
    file_EleTightIDSF=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2017_ElectronTight_Fall17V2.root"
    ),
    file_EleRecoSF_highPt=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2017_ElectronReco.root"
    ),
    file_EleRecoSF_lowPt=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2017_ElectronReco_lowpt.root"
    ),
    file_MuonLooseIDSF=cms.string(""),
    file_MuonMediumIDSF=cms.string(""),
    file_MuonTightIDSF=cms.string(""),
    file_MuonIsoSF=cms.string(""),
    # file_MuonIsoSF_lowPt=cms.string("")
)

SelectedElectronProducer2016 = SelectedElectronProducer2017.clone(
    era=cms.string("2016"),
    file_EleLooseIDSF=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2016_ElectronLoose_Fall17V2.root"
    ),
    file_EleMediumIDSF=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2016_ElectronMedium_Fall17V2.root"
    ),
    file_EleTightIDSF=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2016_ElectronTight_Fall17V2.root"
    ),
    file_EleRecoSF_highPt=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2016_ElectronReco.root"
    ),
    file_EleRecoSF_lowPt=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2016_ElectronReco_lowpt.root"
    ),
)

SelectedElectronProducer2018 = SelectedElectronProducer2017.clone(
    era=cms.string("2018"),
    file_EleLooseIDSF=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2018_ElectronLoose_Fall17V2.root"
    ),
    file_EleMediumIDSF=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2018_ElectronMedium_Fall17V2.root"
    ),
    file_EleTightIDSF=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2018_ElectronTight_Fall17V2.root"
    ),
    file_EleRecoSF_highPt=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2018_ElectronReco.root"
    ),
    file_EleRecoSF_lowPt=cms.string(
        "BoostedTTH/Producers/data/electronSFs/2018_ElectronReco.root"
    ),
)

SelectedMuonProducer2017 = cms.EDProducer(
    "SelectedLeptonProducer",
    leptonType=cms.string("muon"),
    isData=cms.bool(False),
    era=cms.string("2017"),
    leptons=cms.InputTag("slimmedMuons"),
    vertices=cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho=cms.InputTag("fixedGridRhoFastjetAll"),
    ptMins=cms.vdouble(15),
    etaMaxs=cms.vdouble(2.4),
    leptonIDs=cms.vstring("loose"),
    collectionNames=cms.vstring("selectedMuonsLoose"),
    isoConeSizes=cms.vstring("R04"),
    isoCorrTypes=cms.vstring("deltaBeta"),
    muonIsoTypes=cms.vstring("loose"),
    useMuonRC=cms.bool(True),
    useDeterministicSeeds=cms.bool(False),
    rc_dir=cms.string("BoostedTTH/Producers/data/muonSFs/RoccoR2017.txt"),
    # The following two parameters are dummies in case of muons
    # they are not used for the muon selection, which is defined
    # via the 'leptonID' value
    # eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-medium","","boostedAnalysis"),
    # eleLooseIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-loose","","boostedAnalysis"),
    # eleVetoIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-veto","","boostedAnalysis"),
    # eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-tight","","boostedAnalysis"),
    ea_dir=cms.string(
        "BoostedTTH/Producers/data/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt"
    ),
    file_EleLooseIDSF=cms.string(""),
    file_EleMediumIDSF=cms.string(""),
    file_EleTightIDSF=cms.string(""),
    file_EleRecoSF_highPt=cms.string(""),
    file_EleRecoSF_lowPt=cms.string(""),
    file_MuonIDSF=cms.string(
        "BoostedTTH/Producers/data/muonSFs/2017/RunBCDEF_SF_ID_syst.root"
    ),
    histname_MuonLooseIDSF=cms.string("NUM_LooseID_DEN_genTracks_pt_abseta"),
    histname_MuonMediumIDSF=cms.string("NUM_MediumID_DEN_genTracks_pt_abseta"),
    histname_MuonTightIDSF=cms.string("NUM_TightID_DEN_genTracks_pt_abseta"),
    file_MuonIsoSF=cms.string(
        "BoostedTTH/Producers/data/muonSFs/2017/RunBCDEF_SF_ISO_syst.root"
    ),
    histname_MuonLooseISO_LooseIDSF=cms.string("NUM_LooseRelIso_DEN_LooseID_pt_abseta"),
    histname_MuonLooseISO_MediumIDSF=cms.string(
        "NUM_LooseRelIso_DEN_MediumID_pt_abseta"
    ),
    histname_MuonLooseISO_TightIDSF=cms.string(
        "NUM_LooseRelIso_DEN_TightIDandIPCut_pt_abseta"
    ),
    histname_MuonTightISO_MediumIDSF=cms.string(
        "NUM_TightRelIso_DEN_MediumID_pt_abseta"
    ),
    histname_MuonTightISO_TightIDSF=cms.string(
        "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta"
    ),
)

SelectedMuonProducer2016 = SelectedMuonProducer2017.clone(
    era=cms.string("2016"),
    rc_dir=cms.string("BoostedTTH/Producers/data/muonSFs/RoccoR2016.txt"),
    file_MuonIDSF=cms.string(
        "BoostedTTH/Producers/data/muonSFs/2016/Merged_SF_ID.root"
    ),
    histname_MuonLooseIDSF=cms.string("NUM_LooseID_DEN_genTracks_eta_pt"),
    histname_MuonMediumIDSF=cms.string("NUM_MediumID_DEN_genTracks_eta_pt"),
    histname_MuonTightIDSF=cms.string("NUM_TightID_DEN_genTracks_eta_pt"),
    file_MuonIsoSF=cms.string(
        "BoostedTTH/Producers/data/muonSFs/2016/Merged_SF_ISO.root"
    ),
    histname_MuonLooseISO_LooseIDSF=cms.string("NUM_LooseRelIso_DEN_LooseID_eta_pt"),
    histname_MuonLooseISO_MediumIDSF=cms.string("NUM_LooseRelIso_DEN_MediumID_eta_pt"),
    histname_MuonLooseISO_TightIDSF=cms.string(
        "NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt"
    ),
    histname_MuonTightISO_MediumIDSF=cms.string("NUM_TightRelIso_DEN_MediumID_eta_pt"),
    histname_MuonTightISO_TightIDSF=cms.string(
        "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt"
    ),
)
SelectedMuonProducer2018 = SelectedMuonProducer2017.clone(
    era=cms.string("2018"),
    rc_dir=cms.string("BoostedTTH/Producers/data/muonSFs/RoccoR2018.txt"),
    file_MuonIDSF=cms.string(
        "BoostedTTH/Producers/data/muonSFs/2018/RunABCD_SF_ID.root"
    ),
    histname_MuonLooseIDSF=cms.string("NUM_LooseID_DEN_TrackerMuons_pt_abseta"),
    histname_MuonMediumIDSF=cms.string("NUM_MediumID_DEN_TrackerMuons_pt_abseta"),
    histname_MuonTightIDSF=cms.string("NUM_TightID_DEN_TrackerMuons_pt_abseta"),
    file_MuonIsoSF=cms.string(
        "BoostedTTH/Producers/data/muonSFs/2018/RunABCD_SF_ISO.root"
    ),
    histname_MuonLooseISO_LooseIDSF=cms.string("NUM_LooseRelIso_DEN_LooseID_pt_abseta"),
    histname_MuonLooseISO_MediumIDSF=cms.string(
        "NUM_LooseRelIso_DEN_MediumID_pt_abseta"
    ),
    histname_MuonLooseISO_TightIDSF=cms.string(
        "NUM_LooseRelIso_DEN_TightIDandIPCut_pt_abseta"
    ),
    histname_MuonTightISO_MediumIDSF=cms.string(
        "NUM_TightRelIso_DEN_MediumID_pt_abseta"
    ),
    histname_MuonTightISO_TightIDSF=cms.string(
        "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta"
    ),
)
    
SelectedTauProducer2017 = cms.EDProducer(
    "SelectedLeptonProducer",
    leptonType=cms.string("tau"),
    isData=cms.bool(False),
    era=cms.string("2017"),
    leptons=cms.InputTag("slimmedTaus"),
    vertices=cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho=cms.InputTag("fixedGridRhoFastjetAll"),
    ptMins=cms.vdouble(20.),
    etaMaxs=cms.vdouble(2.3),
    leptonIDs=cms.vstring("loose"),
    collectionNames=cms.vstring("selectedTausLoose"),
    isoConeSizes=cms.vstring("R03"),
    isoCorrTypes=cms.vstring("rhoEA"),
    muonIsoTypes=cms.vstring("loose"),
    useMuonRC=cms.bool(False),
    useDeterministicSeeds=cms.bool(False),
    rc_dir=cms.string("BoostedTTH/Producers/data/muonSFs/RoccoR2017.txt"),
    ea_dir=cms.string(
        "BoostedTTH/Producers/data/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt"
    ),
    file_EleLooseIDSF=cms.string(
        ""
    ),
    file_EleMediumIDSF=cms.string(
        ""
    ),
    file_EleTightIDSF=cms.string(
        ""
    ),
    file_EleRecoSF_highPt=cms.string(
        ""
    ),
    file_EleRecoSF_lowPt=cms.string(
        ""
    ),
    file_MuonLooseIDSF=cms.string(""),
    file_MuonMediumIDSF=cms.string(""),
    file_MuonTightIDSF=cms.string(""),
    file_MuonIsoSF=cms.string(""),
)

SelectedTauProducer2018 = SelectedTauProducer2017.clone(
    era=cms.string("2018")
)

SelectedTauProducer2016 = SelectedTauProducer2017.clone(
    era=cms.string("2016")
)
