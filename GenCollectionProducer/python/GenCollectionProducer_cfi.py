import FWCore.ParameterSet.Config as cms

GenCollectionProducer = cms.EDProducer('GenCollectionProducer',
                      collection_name = cms.vstring("Electrons","Muons","Taus","Jets"),
                      collection_type = cms.vstring("Electron","Muon","Tau","Jet"),
                      pt_min = cms.vdouble(10.,10.,10.,10.),
                      eta_max = cms.vdouble(2.4,2.4,2.4,2.4),
                      genParticles=cms.InputTag("prunedGenParticles"),
                      genJets=cms.InputTag("slimmedGenJets")
)
