import FWCore.ParameterSet.Config as cms

HEPTopJetsPFMatcher = cms.EDProducer(
    "HEPTopJetMatcher",
    verbose = cms.bool(False),
    minJetPt          = cms.double(15),
    recofatjetsTag    = cms.InputTag('HEPTopJetsPF','fatjet'),
    patfatjetsTag     = cms.InputTag('selectedPatJetsHEPTopFatPF'),
    patsubjetsTag     = cms.InputTag('selectedPatJetsHEPTopSubPF'),
    toptagsTag        = cms.InputTag('HEPTopJetsPF','toptag'),
    subjettiness1Tag  = cms.InputTag('HEPTopJetsPF','tau1'),
    subjettiness2Tag  = cms.InputTag('HEPTopJetsPF','tau2'),
    subjettiness3Tag  = cms.InputTag('HEPTopJetsPF','tau3'),
    subjettiness4Tag  = cms.InputTag('HEPTopJetsPF','tau4')
)
