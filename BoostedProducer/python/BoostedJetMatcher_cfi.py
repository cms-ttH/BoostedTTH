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
    patSFFilterJetsTag  = cms.InputTag('selectedPatJetsSFFilterjetsPF')
)

#BoostedJetMatcherPath = cms.Path(BoostedJetMatcher)
