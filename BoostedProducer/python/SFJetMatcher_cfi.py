import FWCore.ParameterSet.Config as cms

SFJetMatcher = cms.EDProducer(
    "SFJetMatcher",
    verbose           = cms.bool(False),
    minJetPt          = cms.double(15),
    recofatjetsTag    = cms.InputTag('SFJetProducer','fatjets'),
    patfatjetsTag     = cms.InputTag('selectedPatJetsSFFatJetsPF'),
    patsubjetsTag     = cms.InputTag('selectedPatJetsSFSubjetsPF'),
    patfilterjetsTag  = cms.InputTag('selectedPatJetsSFFilterjetsPF'),
    subjettiness1Tag  = cms.InputTag('SFJetProducer','tau1'),
    subjettiness2Tag  = cms.InputTag('SFJetProducer','tau2'),
    subjettiness3Tag  = cms.InputTag('SFJetProducer','tau3'),
    subjettiness4Tag  = cms.InputTag('SFJetProducer','tau4')
)

SFJetMatcherPath = cms.Path(SFJetMatcher)
