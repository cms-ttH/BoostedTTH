import FWCore.ParameterSet.Config as cms

BoostedJetMatcher = cms.EDProducer(
    "BoostedJetMatcher",
    verbose             = cms.bool(False),
    recoFatJetsTag      = cms.InputTag('ca15PFJetsCHS'),
    recoHTTJetsTag      = cms.InputTag('HTTTopJetProducer',''),
    recoSFJetsTag       = cms.InputTag('SFJetProducer','fat'),
    recoPrunedJetsTag   = cms.InputTag('ca15PFPrunedJetsCHS',''),
    recoSDJetsTag       = cms.InputTag('ca15PFSoftdropJetsCHS',''),
    recoSDZ2B1JetsTag   = cms.InputTag('ca15PFSoftdropZ2B1JetsCHS',''),
    patFatJetsTag       = cms.InputTag('selectedPatJetsFatJetsPF'),
    patHTTTopJetsTag    = cms.InputTag('selectedPatJetsHTTTopJetsPF'),
    patHTTSubjetsTag    = cms.InputTag('selectedPatJetsHTTSubjetsPF'),
    httInfosTag         = cms.InputTag('HTTTopJetProducer',''),
    patSFSubjetsTag     = cms.InputTag('selectedPatJetsSFSubjetsPF'),
    patSFFilterjetsTag  = cms.InputTag('selectedPatJetsSFFilterjetsPF'),
    patPrunedSubjetsTag = cms.InputTag('selectedPatJetsPrunedSubjetsPF'),
    patSDSubjetsTag     = cms.InputTag('selectedPatJetsSDSubjetsPF'),
    patSDZ2B1SubjetsTag = cms.InputTag('selectedPatJetsSDZ2B1SubjetsPF')
)

#BoostedJetMatcherPath = cms.Path(BoostedJetMatcher)
