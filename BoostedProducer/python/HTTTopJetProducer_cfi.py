import FWCore.ParameterSet.Config as cms

from RecoJets.JetProducers.PFJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

# HEP top jet producer parameters
# $Id
HTTTopJetProducer = cms.EDProducer(
    "HTTTopJetProducer",
    PFJetParameters.clone( src = cms.InputTag("pfNoElectronsCHS"),
      doAreaFastjet = cms.bool(True),
      doRhoFastjet = cms.bool(False),
      jetPtMin = cms.double(180.0)
    ),
    AnomalousCellParameters,
    optimalR = cms.bool(True),
    algorithm = cms.int32(1),
    jetAlgorithm = cms.string("CambridgeAachen"),
    rParam = cms.double(1.5),
    mode = cms.int32(4),
    minFatjetPt = cms.double(180.),
    minCandPt = cms.double(180.),
    minSubjetPt = cms.double(30.),
    writeCompound = cms.bool(True),
    jetCollInstanceName = cms.string("subjets"),
    minCandMass = cms.double(0.),
    maxCandMass = cms.double(1000),
    massRatioWidth = cms.double(100.),
    minM23Cut = cms.double(0.),
    minM13Cut = cms.double(0.),
    maxM13Cut = cms.double(2.)
)

HTTTopJetProducerPath = cms.Path(HTTTopJetProducer)
