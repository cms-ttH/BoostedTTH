import FWCore.ParameterSet.Config as cms

SynchSelection = cms.PSet(
)

LeptonSelection = cms.PSet(
   muonTriggers = cms.vstring("HLT_IsoMu24_eta2p1_v2"),
   electronTriggers = cms.vstring("HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v1"),
   channel = cms.string("both")
)

LeptonSelectionNoTrigger = cms.PSet(
    muonTriggers = cms.vstring("None"),
    electronTriggers = cms.vstring("None"),
    channel = cms.string("both")
)

JetTagSelection = cms.PSet(
    minJets = cms.vint32(4,6),
    maxJets = cms.vint32(-1,-1),
    minTags = cms.vint32(3,2),
    maxTags = cms.vint32(-1,-1)
)

checkBasicTriggers= cms.PSet(
    relevantTriggers=cms.vstring("HLT_IsoMu24_eta2p1_v2",
                                 "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v1"
                                 )
    )

checkNoTriggers= cms.PSet(
    relevantTriggers=cms.vstring()
    )

checkManyRun2DataTriggers = cms.PSet(
    relevantTriggers=cms.vstring("HLT_Ele15_PFHT300_v2",
                                "HLT_Ele22_eta2p1_WPLoose_Gsf_v1",
                                "HLT_Ele22_eta2p1_WPTight_Gsf_v1",
                                "HLT_Ele23_WPLoose_Gsf_v1",
                                "HLT_Ele27_WPLoose_Gsf_WHbbBoost_v1",
                                "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v1",
                                "HLT_Ele27_eta2p1_WPLoose_Gsf_TriCentralPFJet30_v1",
                                "HLT_Ele27_eta2p1_WPLoose_Gsf_TriCentralPFJet50_40_30_v1",
                                "HLT_Ele27_eta2p1_WPLoose_Gsf_v1",
                                "HLT_Ele27_eta2p1_WPTight_Gsf_v1",
                                "HLT_Ele32_eta2p1_WPLoose_Gsf_TriCentralPFJet30_v1",
                                "HLT_Ele32_eta2p1_WPLoose_Gsf_TriCentralPFJet50_40_30_v1",
                                "HLT_Ele32_eta2p1_WPLoose_Gsf_v1",
                                "HLT_Ele32_eta2p1_WPTight_Gsf_v1",

                                "HLT_DoubleIsoMu17_eta2p1_v2",
                                "HLT_IsoMu20_eta2p1_CentralPFJet30_BTagCSV07_v2",
                                "HLT_IsoMu20_eta2p1_TriCentralPFJet30_v2",
                                "HLT_IsoMu20_eta2p1_TriCentralPFJet50_40_30_v2",
                                "HLT_IsoMu20_eta2p1_v2",
                                "HLT_IsoMu20_v2",
                                "HLT_IsoMu24_eta2p1_TriCentralPFJet30_v2",
                                "HLT_IsoMu24_eta2p1_TriCentralPFJet50_40_30_v2",
                                "HLT_IsoMu24_eta2p1_v2",
                                "HLT_IsoMu27_v2",
                                "HLT_IsoTkMu20_eta2p1_v2",
                                "HLT_IsoTkMu20_v2",
                                "HLT_IsoTkMu24_eta2p1_v2",
                                "HLT_IsoTkMu27_v2",
                                "HLT_Mu15_PFHT300_v2",
                                "HLT_Mu20_v1",
                                "HLT_Mu24_eta2p1_v1",
                                "HLT_Mu27_v1",

                                "HLT_Mu17_Mu8_DZ_v1",
                                "HLT_Mu17_Mu8_SameSign_DZ_v1",
                                "HLT_Mu17_Mu8_v1",
                                "HLT_Mu17_TkMu8_DZ_v2",
                                "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2",
                                "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v2",
                                "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2",
                                "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v2",
                                "HLT_Mu17_TrkIsoVVL_v2",
                                "HLT_Mu17_v1",
                                "HLT_Mu20_Mu10_DZ_v1",
                                "HLT_Mu20_Mu10_v1",
                                "HLT_Mu24_TrkIsoVVL_v2",
                                "HLT_Mu24_v1",
                                "HLT_Mu27_TkMu8_v2",

                                "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2",
                                "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_v2",
                                "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2",
                                "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v2",

                                "HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2",
                                "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2",
                                "HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v2",
                                "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v2",
                                "HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v2",
                                "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2"
                                )
    )
