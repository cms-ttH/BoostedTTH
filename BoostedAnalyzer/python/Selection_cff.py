import FWCore.ParameterSet.Config as cms

LeptonSelectionNoTrigger = cms.PSet(
    muonTriggers = cms.vstring("None"),
    electronTriggers = cms.vstring("None"),
    channel = cms.string("both")
)

LeptonSelectionData = cms.PSet(
    muonTriggers = cms.vstring("HLT_IsoMu24_eta2p1_v*","HLT_IsoMu27_v*"),
    electronTriggers = cms.vstring("HLT_Ele35_WPTight_Gsf_v*","HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v*"),
    channel = cms.string("both")
)
LeptonSelectionMC = cms.PSet(
    muonTriggers = cms.vstring("HLT_IsoMu24_eta2p1_v*","HLT_IsoMu27_v*"),
    electronTriggers = cms.vstring("HLT_Ele35_WPTight_Gsf_v*","HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v*"),
    channel = cms.string("both")
)

DiLeptonSelectionNoTrigger  = cms.PSet(
    mumuTriggers = cms.vstring("None"),
    elelTriggers = cms.vstring("None"),
    elmuTriggers = cms.vstring("None"),
    dlchannel = cms.string("all"),
)

DiLeptonSelectionMC = cms.PSet(
    mumuTriggers = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*",
                               "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*"),
    elelTriggers = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    elmuTriggers = cms.vstring("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                               "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    dlchannel = cms.string("all"),
)
DiLeptonSelectionData = cms.PSet(
    mumuTriggers = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*",
                               "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*"),
    elelTriggers = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    elmuTriggers = cms.vstring("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                               "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    dlchannel = cms.string("all"),
)

METSelection = cms.PSet(
    minMET = cms.double(20.),
    maxMET = cms.double(100000.),
)

DiLeptonMETSelection = cms.PSet(
    minMET = cms.double(-1),
    maxMET = cms.double(800),
)

JetTagSelection = cms.PSet(
    minJets = cms.vint32(4),
    maxJets = cms.vint32(-1),
    minTags = cms.vint32(2),
    maxTags = cms.vint32(-1)
)

checkBasicDataTriggers= cms.PSet(
    relevantTriggers=cms.vstring(
				 "HLT_Ele35_WPTight_Gsf_v*",
                                 "HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v*",
                                 "HLT_IsoMu24_eta2p1_v*",
                                 "HLT_IsoMu27_v*",
                                 "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
                                 "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                                 "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
                                 "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                                 "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                                 "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                                 "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*",
                                 "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*",
                                 "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*",
                                 )
)
checkBasicMCTriggers= cms.PSet(
    relevantTriggers=cms.vstring(
                                 "HLT_Ele35_WPTight_Gsf_v*",
                                 "HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v*",
                                 "HLT_IsoMu24_eta2p1_v*",
                                 "HLT_IsoMu27_v*",
                                 "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
                                 "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                                 "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
                                 "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                                 "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                                 "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                                 "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*",
                                 "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*",
                                 "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*",
                                 )
)

checkNoTriggers= cms.PSet(
    relevantTriggers=cms.vstring()
    )

filtersData= cms.PSet(
    filters=cms.vstring("Flag_goodVertices",
                        "Flag_globalSuperTightHalo2016Filter",
                        "Flag_HBHENoiseFilter",
                        "Flag_HBHENoiseIsoFilter",
                        "Flag_EcalDeadCellTriggerPrimitiveFilter",
                        "Flag_eeBadScFilter",
                        "Flag_BadPFMuonFilter",
                        "Flag_BadChargedCandidateFilter",
                        "Flag_ecalBadCalibFilter"
                        )
)

filtersMC= cms.PSet(
    filters=cms.vstring("Flag_goodVertices",
                        "Flag_globalSuperTightHalo2016Filter",
                        "Flag_HBHENoiseFilter",
                        "Flag_HBHENoiseIsoFilter",
                        "Flag_EcalDeadCellTriggerPrimitiveFilter",
                        "Flag_BadPFMuonFilter",
                        "Flag_BadChargedCandidateFilter",
                        "Flag_ecalBadCalibFilter"
                        )
)
