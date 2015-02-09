import FWCore.ParameterSet.Config as cms

CA12JetsCA3FilterjetsPFMatcher = cms.EDProducer(
    "SubjetFilterJetMatcher",
    verbose           = cms.bool(False),
    minJetPt          = cms.double(15),
    recofatjetsTag    = cms.InputTag('CA12JetsCA3FilterjetsPF','fatjet'),
    patfatjetsTag     = cms.InputTag('selectedPatJetsCA12PF'),
    patsubjetsTag     = cms.InputTag('selectedPatJetsCA3SubPF'),
    patfilterjetsTag  = cms.InputTag('selectedPatJetsCA3FiltPF'),
    subjettiness1Tag  = cms.InputTag('CA12JetsCA3FilterjetsPF','tau1'),
    subjettiness2Tag  = cms.InputTag('CA12JetsCA3FilterjetsPF','tau2'),
    subjettiness3Tag  = cms.InputTag('CA12JetsCA3FilterjetsPF','tau3'),
    subjettiness4Tag  = cms.InputTag('CA12JetsCA3FilterjetsPF','tau4')
)
