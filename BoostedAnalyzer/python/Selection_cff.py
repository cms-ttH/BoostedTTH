import FWCore.ParameterSet.Config as cms

#LeptonSelectionNoTrigger = cms.PSet(
    #muonTriggers = cms.vstring("None"),
    #electronTriggers = cms.vstring("None"),
    #channel = cms.string("both")
#)

#LeptonSelectionData = cms.PSet(
    #muonTriggers = cms.vstring("HLT_IsoMu24_v*","HLT_IsoTkMu24_v*"),
    #electronTriggers = cms.vstring("HLT_Ele27_WPTight_Gsf_v*"),
    #channel = cms.string("both")
#)
#LeptonSelectionMC = cms.PSet(
    #muonTriggers = cms.vstring("HLT_IsoMu24_v*","HLT_IsoTkMu24_v*"),
    #electronTriggers = cms.vstring("HLT_Ele27_WPTight_Gsf_v*"),
    #channel = cms.string("both")
#)

#DiLeptonSelectionNoTrigger  = cms.PSet(
    #mumuTriggers = cms.vstring("None"),
    #elelTriggers = cms.vstring("None"),
    #elmuTriggers = cms.vstring("None"),
    #dlchannel = cms.string("all"),
#)

#DiLeptonSelectionMC = cms.PSet(
    #mumuTriggers = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v*","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v*",
                               #"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*"),
    #elelTriggers = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    #elmuTriggers = cms.vstring("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*",
                               #"HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    #dlchannel = cms.string("all"),
#)
#DiLeptonSelectionData = cms.PSet(
    #mumuTriggers = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v*","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v*",
                               #"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*"),
    #elelTriggers = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    #elmuTriggers = cms.vstring("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*",
                               #"HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
    #dlchannel = cms.string("all"),
#)
    
MonoJetTriggers = cms.PSet(
    METTriggers = cms.vstring("HLT_PFMET170_*","HLT_PFMETNoMu90_PFMHTNoMu90_IDTight","HLT_PFMETNoMu100_PFMHTNoMu100_IDTight","HLT_PFMETNoMu110_PFMHTNoMu110_IDTight","HLT_PFMETNoMu120_PFMHTNoMu120_IDTight"),
    electronTriggers = cms.vstring("HLT_Ele27_WPTight","HLT_Ele105_CaloIdVT_GsfTrkIdT"),
    photonTriggers = cms.vstring("HLT_Photon165_HE10","HLT_Photon175"),
    HTTriggers = cms.vstring("HLT_EcalHT800")
    )

METSelection = cms.PSet(
    minMET = cms.double(250),
    maxMET = cms.double(100000),
)

#DiLeptonMETSelection = cms.PSet(
    #minMET = cms.double(-1),
    #maxMET = cms.double(800),
#)

#JetTagSelection = cms.PSet(
    #minJets = cms.vint32(-1),
    #maxJets = cms.vint32(50),
    #minTags = cms.vint32(-1),
    #maxTags = cms.vint32(0)
#)

checkBasicDataTriggers= cms.PSet(
    relevantTriggers=cms.vstring(
				 "HLT_PFMET170_*","HLT_PFMETNoMu90_PFMHTNoMu90_IDTight","HLT_PFMETNoMu100_PFMHTNoMu100_IDTight","HLT_PFMETNoMu110_PFMHTNoMu110_IDTight","HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
				 "HLT_Ele27_WPTight","HLT_Ele105_CaloIdVT_GsfTrkIdT",
				 "HLT_Photon165_HE10","HLT_Photon175",
				 "HLT_EcalHT800"
                                 )
)
checkBasicMCTriggers= cms.PSet(
    relevantTriggers=cms.vstring(
				 "HLT_PFMET170_*","HLT_PFMETNoMu90_PFMHTNoMu90_IDTight","HLT_PFMETNoMu100_PFMHTNoMu100_IDTight","HLT_PFMETNoMu110_PFMHTNoMu110_IDTight","HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
				 "HLT_Ele27_WPTight","HLT_Ele105_CaloIdVT_GsfTrkIdT",
				 "HLT_Photon165_HE10","HLT_Photon175",
				 "HLT_EcalHT800"
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
                        #"BadPFMuonFilter",
                        #"BadChargedCandidateFilter",
                        #"badGlobalMuonTaggerMAOD",
                        #"cloneGlobalMuonTaggerMAOD"
                        )
)

filtersMC= cms.PSet(
    filters=cms.vstring("Flag_goodVertices",
                        "Flag_globalTightHalo2016Filter",
                        "Flag_HBHENoiseFilter",
                        "Flag_HBHENoiseIsoFilter",
                        "Flag_EcalDeadCellTriggerPrimitiveFilter",
                        #"BadPFMuonFilter",
                        #"BadChargedCandidateFilter",
                        #"badGlobalMuonTaggerMAOD",
                        #"cloneGlobalMuonTaggerMAOD"
                        )
)
    
MonoJetSelection = cms.PSet(
    MonoJet_Pt=cms.double(100),
    MonoJet_Eta=cms.double(2.5),
    MonoJet_Chf=cms.double(0.1),
    MonoJet_Nhf=cms.double(0.8)
)
