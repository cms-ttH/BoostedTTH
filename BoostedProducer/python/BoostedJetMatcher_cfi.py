import FWCore.ParameterSet.Config as cms

BoostedJetMatcher = cms.EDProducer(
    "BoostedJetMatcher",
    verbose                           = cms.bool(False),
    recoFatJetsTag                    = cms.InputTag('ca15PFJetsCHS'),
    recoTopJetsTag                    = cms.InputTag('HTTTopJetProducer'),
    recoSFJetsTag                     = cms.InputTag('SFJetProducer','fat'),
    recoPrunedJetsTag                 = cms.InputTag('ca15PFPrunedJetsCHS'),
    recoSDJetsTag                     = cms.InputTag('ca15PFSoftdropJetsCHS'),
    recoSDJetsForSubjettinessTag      = cms.InputTag('ca15PFSoftdropJetsCHSforSubjettiness'),
    patFatJetsTag                     = cms.InputTag('selectedPatJetsFatJetsPF'),
    patTopJetsTag                     = cms.InputTag('selectedPatJetsHTTTopJetsPF'),
    patTopSubjetsTag                  = cms.InputTag('selectedPatJetsHTTSubjetsPF'),
    httInfosTag                       = cms.InputTag('HTTTopJetProducer',''),
    patSFSubjetsTag                   = cms.InputTag('selectedPatJetsSFSubjetsPF'),
    patSFFilterjetsTag                = cms.InputTag('selectedPatJetsSFFilterjetsPF'),
    patPrunedSubjetsTag               = cms.InputTag('selectedPatJetsPrunedSubjetsPF'),
    patSDSubjetsTag                   = cms.InputTag('selectedPatJetsSDSubjetsPF'),
    softdropSubjettiness1Tag          = cms.InputTag('ca15SoftdropSubjettiness','tau1'),
    softdropSubjettiness2Tag          = cms.InputTag('ca15SoftdropSubjettiness','tau2'),
    softdropSubjettiness3Tag          = cms.InputTag('ca15SoftdropSubjettiness','tau3')
)
