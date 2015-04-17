import FWCore.ParameterSet.Config as cms

HTTTopJetMatcher = cms.EDProducer(
    "HTTTopJetMatcher",
    verbose = cms.bool(False),
    recoFatJetsTag    = cms.InputTag('HTTTopJetProducer',''),
    patFatJetsTag     = cms.InputTag('selectedPatJetsHTTFatJetsPF'),
    patSubjetsTag     = cms.InputTag('selectedPatJetsHTTSubjetsPF'),
    httInfosTag       = cms.InputTag('HTTTopJetProducer',''),
)

HTTTopJetMatcherPath = cms.Path(HTTTopJetMatcher)
