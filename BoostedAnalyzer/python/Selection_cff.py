import FWCore.ParameterSet.Config as cms

# LeptonSelectionNoTrigger = cms.PSet(
# muonTriggers = cms.vstring("None"),
# electronTriggers = cms.vstring("None"),
# channel = cms.string("both")
# )

# LeptonSelectionData2016 = cms.PSet(
# muonTriggers = cms.vstring("HLT_IsoMu24_v*","HLT_IsoTkMu24_v*"),
# electronTriggers = cms.vstring("HLT_Ele27_WPTight_Gsf_v*"),
# channel = cms.string("both")
# )

# LeptonSelectionData2017 = cms.PSet(
# muonTriggers = cms.vstring("HLT_IsoMu27_v*"),
# electronTriggers = cms.vstring("HLT_Ele35_WPTight_Gsf_v*","HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v*"),
# channel = cms.string("both")
# )

# LeptonSelectionData2018 = cms.PSet(
# muonTriggers = cms.vstring("HLT_IsoMu24_v*"),
# electronTriggers = cms.vstring("HLT_Ele32_WPTight_Gsf_v*","HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v*"),
# channel = cms.string("both")
# )


# LeptonSelectionMC2016 = cms.PSet(
# muonTriggers = cms.vstring("HLT_IsoMu24_v*","HLT_IsoTkMu24_v*"),
# electronTriggers = cms.vstring("HLT_Ele27_WPTight_Gsf_v*"),
# channel = cms.string("both")
# )

# LeptonSelectionMC2017 = cms.PSet(
# muonTriggers = cms.vstring("HLT_IsoMu27_v*"),
# electronTriggers = cms.vstring("HLT_Ele35_WPTight_Gsf_v*","HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v*"),
# channel = cms.string("both")
# )

# LeptonSelectionMC2018 = cms.PSet(
# muonTriggers = cms.vstring("HLT_IsoMu24_v*"),
# electronTriggers = cms.vstring("HLT_Ele32_WPTight_Gsf_v*","HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v*"),
# channel = cms.string("both")
# )

# DiLeptonSelectionNoTrigger  = cms.PSet(
# mumuTriggers = cms.vstring("None"),
# elelTriggers = cms.vstring("None"),
# elmuTriggers = cms.vstring("None"),
# dlchannel = cms.string("all"),
# )

# DiLeptonSelectionMC = cms.PSet(
# mumuTriggers = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*",
# "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*"),
# elelTriggers = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
# elmuTriggers = cms.vstring("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
# "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
# dlchannel = cms.string("all"),
# )
# DiLeptonSelectionData = cms.PSet(
# mumuTriggers = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*",
# "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*"),
# elelTriggers = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
# elmuTriggers = cms.vstring("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
# "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
# dlchannel = cms.string("all"),
# )

METSelection = cms.PSet(minMET=cms.double(250.0), maxMET=cms.double(100000.0))

# JetTagSelection = cms.PSet(
# minJets = cms.vint32(4),
# maxJets = cms.vint32(-1),
# minTags = cms.vint32(3),
# maxTags = cms.vint32(-1)
# )

checkBasicDataTriggers = cms.PSet(
    relevantTriggers=cms.vstring(
        "HLT_Ele35_WPTight_Gsf_v*",
        "HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v*",
        "HLT_Ele27_WPTight_Gsf_v*",
        "HLT_Ele32_WPTight_Gsf_v*",
        "HLT_IsoMu27_v*",
        "HLT_IsoMu24_v*",
        "HLT_IsoTkMu24_v*",
        "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
        "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
        # "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
        # "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
        # "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*",
        # "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*",
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*",
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*",
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*",
        "HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v*",
        "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v*",
        "HLT_PFMETNoMu130_PFMHTNoMu130_IDTight_v*",
        "HLT_PFMETNoMu140_PFMHTNoMu140_IDTight_v*",
        "HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60_v*",
        "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_v*",
    )
)
checkBasicMCTriggers = cms.PSet(
    relevantTriggers=cms.vstring(
        "HLT_Ele35_WPTight_Gsf_v*",
        "HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v*",
        "HLT_Ele27_WPTight_Gsf_v*",
        "HLT_Ele32_WPTight_Gsf_v*",
        "HLT_IsoMu27_v*",
        "HLT_IsoMu24_v*",
        "HLT_IsoTkMu24_v*",
        "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
        "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
        # "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
        # "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",
        # "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*",
        # "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*",
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*",
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*",
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*",
        "HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v*",
        "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v*",
        "HLT_PFMETNoMu130_PFMHTNoMu130_IDTight_v*",
        "HLT_PFMETNoMu140_PFMHTNoMu140_IDTight_v*",
        "HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60_v*",
        "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_v*",
    )
)

checkNoTriggers = cms.PSet(relevantTriggers=cms.vstring())

filtersData1718 = cms.vstring(
    "Flag_goodVertices",
    "Flag_globalSuperTightHalo2016Filter",
    "Flag_HBHENoiseFilter",
    "Flag_HBHENoiseIsoFilter",
    "Flag_EcalDeadCellTriggerPrimitiveFilter",
    "Flag_BadPFMuonFilter",
    "ecalBadCalibReducedMINIAODFilter",
    "Flag_eeBadScFilter",
)

filtersMC1718 = cms.vstring(
    "Flag_goodVertices",
    "Flag_globalSuperTightHalo2016Filter",
    "Flag_HBHENoiseFilter",
    "Flag_HBHENoiseIsoFilter",
    "Flag_EcalDeadCellTriggerPrimitiveFilter",
    "Flag_BadPFMuonFilter",
    "ecalBadCalibReducedMINIAODFilter",
)

filtersData16 = cms.vstring(
    "Flag_goodVertices",
    "Flag_globalSuperTightHalo2016Filter",
    "Flag_HBHENoiseFilter",
    "Flag_HBHENoiseIsoFilter",
    "Flag_EcalDeadCellTriggerPrimitiveFilter",
    "Flag_BadPFMuonFilter",
    "Flag_eeBadScFilter",
)

filtersMC16 = cms.vstring(
    "Flag_goodVertices",
    "Flag_globalSuperTightHalo2016Filter",
    "Flag_HBHENoiseFilter",
    "Flag_HBHENoiseIsoFilter",
    "Flag_EcalDeadCellTriggerPrimitiveFilter",
    "Flag_BadPFMuonFilter",
)

# process.BoostedAnalyzer.additionalFilters = cms.VInputTag(["ecalBadCalibReducedMINIAODFilter"])
MonoTopSelection = cms.PSet(
    AK15Jet_Pt=cms.double(250.0),
    AK15Jet_Eta=cms.double(2.4),
    AK15Jet_Chf=cms.double(0.1),
    AK15Jet_Nhf=cms.double(0.8),
    DeltaR_MET_AK15Jet=cms.double(1.5),
)
