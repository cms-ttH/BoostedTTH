import FWCore.ParameterSet.Config as cms

LeptonSelectionNoTrigger = cms.PSet(
    muonTriggers = cms.vstring("None"),
    electronTriggers = cms.vstring("None"),
    channel = cms.string("both")
)

LeptonSelectionData = cms.PSet(
    muonTriggers = cms.vstring("HLT_IsoMu24_v*","HLT_IsoTkMu24_v*"),
    electronTriggers = cms.vstring("HLT_Ele27_WPTight_Gsf_v*"),
    channel = cms.string("both")
)
LeptonSelectionMC = cms.PSet(
    muonTriggers = cms.vstring("HLT_IsoMu24_v*","HLT_IsoTkMu24_v*"),
    electronTriggers = cms.vstring("HLT_Ele27_WPTight_Gsf_v*"),
    channel = cms.string("both")
)

LeptonSelectionVetoMC = cms.PSet(
    muonTriggers = cms.vstring("HLT_IsoMu20_v*"),
    electronTriggers = cms.vstring("HLT_Ele27_eta2p1_WPLoose_Gsf_v*"),
    channel = cms.string("veto")
)

LeptonSelectionVetoData = cms.PSet(
    muonTriggers = cms.vstring("HLT_IsoMu20_v*"),
    electronTriggers = cms.vstring("HLT_Ele27_eta2p1_WPLoose_Gsf_v*"),
    channel = cms.string("veto")
)

DiLeptonSelectionNoTrigger  = cms.PSet(
    mumuTriggers = cms.vstring("None"),
    elelTriggers = cms.vstring("None"),
    elmuTriggers = cms.vstring("None"),
    dlchannel = cms.string("all"),
)

DiLeptonSelectionMC = cms.PSet(
    mumuTriggers = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v*","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v*",
                               "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*"),
    elelTriggers = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    elmuTriggers = cms.vstring("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*",
                               "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    dlchannel = cms.string("all"),
)
DiLeptonSelectionData = cms.PSet(
    mumuTriggers = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v*","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v*",
                               "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*"),
    elelTriggers = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    elmuTriggers = cms.vstring("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*",
                               "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    dlchannel = cms.string("all"),
)

METSelection = cms.PSet(
    minMET = cms.double(-1),
    maxMET = cms.double(800),
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
				 #"HLT_IsoMu24_eta2p1_v*",
                                 #"HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v*",
                                 #"HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                                 ##"HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
                                 #"HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*",
                                 #"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*",
                                 #"HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*",
                                 #"HLT_IsoMu18_v*",
                                 "HLT_IsoMu24_v*",
                                 "HLT_IsoTkMu24_v*",
                                 "HLT_Ele27_eta2p1_WPTight_Gsf_v*",
                                 "HLT_PFHT900_v*",
                                 "HLT_PFHT800_v*",
                                 "HLT_PFHT650_v*",
                                 #"HLT_Ele23_WPLoose_Gsf_v*",
                                 #"HLT_IsoMu20_v*",
                                 #"HLT_Ele27_eta2p1_WPLoose_Gsf_v*"
                                 )
)
checkBasicMCTriggers= cms.PSet(
    relevantTriggers=cms.vstring(
				 #"HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                                 #"HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
                                 #"HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*",
                                 #"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*",
                                 #"HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*",
                                 #"HLT_Ele27_eta2p1_WP85_Gsf_HT200_v*",
                                 #"HLT_IsoMu24_eta2p1_v*",
                                 #"HLT_IsoMu20_eta2p1_v*",
                                 #"HLT_Ele22_eta2p1_WP75_Gsf_v*",
 				 #"HLT_IsoMu20_v*",
                                 #"HLT_Ele27_eta2p1_WPLoose_Gsf_v*",
                                 "HLT_IsoMu24_v*",
                                 "HLT_IsoTkMu24_v*",
                                 "HLT_Ele27_eta2p1_WPTight_Gsf_v*",
                                 "HLT_PFHT900_v*",
                                 "HLT_PFHT800_v*",
                                 "HLT_PFHT650_v*",
                                 )
)

checkNoTriggers= cms.PSet(
    relevantTriggers=cms.vstring()
    )

filtersData= cms.PSet(
    filters=cms.vstring("Flag_goodVertices",
                        "Flag_globalTightHalo2016Filter",
                        "Flag_HBHENoiseFilter",
                        "Flag_HBHENoiseIsoFilter",
                        "Flag_EcalDeadCellTriggerPrimitiveFilter",
                        "Flag_eeBadScFilter",
                        "BadPFMuonFilter",
                        "BadChargedCandidateFilter",
                        "badGlobalMuonTaggerMAOD",
                        "cloneGlobalMuonTaggerMAOD"
                        )
)

filtersMC= cms.PSet(
    filters=cms.vstring("Flag_goodVertices",
                        "Flag_globalTightHalo2016Filter",
                        "Flag_HBHENoiseFilter",
                        "Flag_HBHENoiseIsoFilter",
                        "Flag_EcalDeadCellTriggerPrimitiveFilter",
                        "BadPFMuonFilter",
                        "BadChargedCandidateFilter",
                        "badGlobalMuonTaggerMAOD",
                        "cloneGlobalMuonTaggerMAOD"
                        )
)
