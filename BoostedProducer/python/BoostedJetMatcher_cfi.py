import FWCore.ParameterSet.Config as cms

BoostedJetMatcher = cms.EDProducer(
    "BoostedJetMatcher",
    verbose             = cms.bool(False),
    recoFatJetsTag      = cms.InputTag('SFJetProducer','fat'),
    patFatJetsTag       = cms.InputTag('selectedPatJetsSFFatJetsPF'),
    recoTopJetsTag      = cms.InputTag('HTTTopJetProducer',''),
    patTopJetsTag       = cms.InputTag('selectedPatJetsHTTTopJetsPF'),
    patTopSubjetsTag    = cms.InputTag('selectedPatJetsHTTSubjetsPF'),
    httInfosTag         = cms.InputTag('HTTTopJetProducer',''),
    patSFSubJetsTag     = cms.InputTag('selectedPatJetsSFSubjetsPF'),
    patSFFilterJetsTag  = cms.InputTag('selectedPatJetsSFFilterjetsPF'),
    softdropSubjettiness1Tag = cms.InputTag('ca15SoftdropSubjettiness','tau1'),
    softdropSubjettiness2Tag = cms.InputTag('ca15SoftdropSubjettiness','tau2'),
    softdropSubjettiness3Tag = cms.InputTag('ca15SoftdropSubjettiness','tau3'),
    recoSDZ2B1JetsTag   = cms.InputTag('ca15PFSoftdropZ2B1JetsCHS',''),
    recoSubJetsTag      = cms.InputTag('ca15PFSoftdropZ2B1JetsCHS','subjets')
)

#BoostedJetMatcherPath = cms.Path(BoostedJetMatcher)
