import FWCore.ParameterSet.Config as cms

LeptonSelectionNoTrigger = cms.PSet(
    muonTriggers = cms.vstring("None"),
    electronTriggers = cms.vstring("None"),
    channel = cms.string("both")
)

LeptonSelectionData = cms.PSet(
    muonTriggers = cms.vstring("HLT_IsoMu20_v*"),
    electronTriggers = cms.vstring("HLT_Ele27_eta2p1_WPLoose_Gsf_v*"),
    channel = cms.string("both")
)
LeptonSelectionMC = cms.PSet(
    muonTriggers = cms.vstring("HLT_IsoMu20_v*"),
    electronTriggers = cms.vstring("HLT_Ele27_eta2p1_WPLoose_Gsf_v*"),
    channel = cms.string("both")
)

DiLeptonSelectionNoTrigger  = cms.PSet(
    mumuTriggers = cms.vstring("None"),
    elelTriggers = cms.vstring("None"),
    elmuTriggers = cms.vstring("None"),
    dlchannel = cms.string("all"),
)

DiLeptonSelectionMC = cms.PSet(
    mumuTriggers = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*"),
    elelTriggers = cms.vstring("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    elmuTriggers = cms.vstring("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*"),
    dlchannel = cms.string("all"),
)
DiLeptonSelectionData = cms.PSet(
    mumuTriggers = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*"),
    elelTriggers = cms.vstring("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    elmuTriggers = cms.vstring("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*"),
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
    minJets = cms.vint32(4,6),
    maxJets = cms.vint32(-1,-1),
    minTags = cms.vint32(3,2),
    maxTags = cms.vint32(-1,-1)
)

checkBasicDataTriggers= cms.PSet(
    relevantTriggers=cms.vstring("HLT_IsoMu24_eta2p1_v*",
                                 "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v*",
                                 "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                                 "HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
                                 "HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*",
                                 "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*",
                                 "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*",
                                 "HLT_IsoMu18_v*",
                                 "HLT_IsoMu22_v*",
                                 "HLT_Ele23_WPLoose_Gsf_v*",
                                 "HLT_IsoMu20_v*",
                                 "HLT_Ele27_eta2p1_WPLoose_Gsf_v*")
)
checkBasicMCTriggers= cms.PSet(
    relevantTriggers=cms.vstring("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
                                 "HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
                                 "HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*",
                                 "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*",
                                 "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*",
                                 "HLT_Ele27_eta2p1_WP85_Gsf_HT200_v*",
                                 "HLT_IsoMu24_eta2p1_v*",
                                 "HLT_IsoMu20_eta2p1_v*",
                                 "HLT_Ele22_eta2p1_WP75_Gsf_v*",
 				  "HLT_IsoMu20_v*",
                                 "HLT_Ele27_eta2p1_WPLoose_Gsf_v*")
)

checkNoTriggers= cms.PSet(
    relevantTriggers=cms.vstring()
    )
