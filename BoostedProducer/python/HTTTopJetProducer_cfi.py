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
      jetPtMin = cms.double(0.0)
    ),
    AnomalousCellParameters,
    algorithm = cms.int32(1),
    jetAlgorithm = cms.string("CambridgeAachen"),
    rParam = cms.double(1.5),
    optimalR = cms.bool(True),
    qJets = cms.bool(False),
    minFatjetPt = cms.double(180.),
    minSubjetPt = cms.double(0.),
    minCandPt = cms.double(0.),
    maxFatjetAbsEta = cms.double(2.0),
    subjetMass = cms.double(30.),
    muCut = cms.double(0.8),
    filtR = cms.double(0.3),
    filtN = cms.int32(5),
    mode = cms.int32(4),
    minCandMass = cms.double(0.),
    maxCandMass = cms.double(999999.),
    massRatioWidth = cms.double(999999.),
    minM23Cut = cms.double(0.),
    minM13Cut = cms.double(0.),
    maxM13Cut = cms.double(999999.),
    writeCompound = cms.bool(True),
    jetCollInstanceName = cms.string("subjets")
)

HTTTopJetProducerPath = cms.Path(HTTTopJetProducer)
