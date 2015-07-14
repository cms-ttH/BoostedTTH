import FWCore.ParameterSet.Config as cms

from RecoJets.JetProducers.PFJetParameters_cfi import *
from RecoJets.JetProducers.GenJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

# HEP top jet producer parameters
# $Id

HEPTopJetsPF = cms.EDProducer(
    "HEPTopJetProducer",
    PFJetParameters.clone(
      src = cms.InputTag("pfNoElectronsCHS"),
      doAreaFastjet = cms.bool(True),
      jetPtMin = cms.double(180.0)
    ),
    AnomalousCellParameters,
    verbose 		= cms.bool(False),
    jetAlgorithm 	= cms.string("CambridgeAachen"),
    rParam       	= cms.double(1.5),
    nFatMax      	= cms.uint32(0),
    centralEtaCut	= cms.double(2.0),
    massDropCut		= cms.double(0.8),
    subjetMassCut 	= cms.double(30.),
    requireTopTag	= cms.bool(False)
)

HEPTopJetsGen = cms.EDProducer(
    "HEPTopJetProducer",
    GenJetParameters.clone(
      doAreaFastjet = cms.bool(True),
      jetPtMin = cms.double(150.0)
    ),
    AnomalousCellParameters,
    verbose 		= cms.bool(False),
    jetAlgorithm 	= cms.string("CambridgeAachen"),
    rParam       	= cms.double(1.5),
    nFatMax      	= cms.uint32(0),
    centralEtaCut	= cms.double(2.1),
    massDropCut		= cms.double(0.8),
    subjetMassCut 	= cms.double(30.),
    requireTopTag	= cms.bool(False)
)
