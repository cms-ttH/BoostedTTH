import FWCore.ParameterSet.Config as cms

GenCollectionProducer = cms.EDProducer('GenCollectionProducer',
                      collection_name = cms.vstring("CustomGenElectrons","CustomGenMuons","CustomGenTaus","CustomGenPhotons"),#,"CustomGenJets","CustomGenJetsAK8"),
                      collection_type = cms.vstring("Electron","Muon","Tau","Photon"),#,"AK4Jet","AK8Jet"),
                      pt_min = cms.vdouble(27.,27.,10.,10.),#,10.),
                      eta_max = cms.vdouble(2.5,2.5,2.4,2.4),#,2.4),
                      genParticles=cms.InputTag("prunedGenParticles"),
                      genJets=cms.InputTag("slimmedGenJets"),
                      genJetsAK8=cms.InputTag("slimmedGenJetsAK8"),
                      doDeltaRCleaning = cms.bool(False)
)
