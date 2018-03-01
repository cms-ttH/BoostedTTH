import FWCore.ParameterSet.Config as cms

GenCollectionProducer = cms.EDProducer('GenCollectionProducer',
                      collection_name = cms.vstring("CustomGenElectrons","CustomGenMuons","CustomGenTaus","CustomGenPhotons","CustomGenJets"),
                      collection_type = cms.vstring("Electron","Muon","Tau","Photon","Jet"),
                      pt_min = cms.vdouble(10.,10.,10.,10.,10.),
                      eta_max = cms.vdouble(2.4,2.4,2.4,2.4,2.4),
                      genParticles=cms.InputTag("prunedGenParticles"),
                      genJets=cms.InputTag("slimmedGenJets")
)
