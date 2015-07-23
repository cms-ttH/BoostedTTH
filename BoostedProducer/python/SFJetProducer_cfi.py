################################################################################
# see: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideSubjetFilterJetProducer
################################################################################

import FWCore.ParameterSet.Config as cms

from RecoJets.JetProducers.PFJetParameters_cfi import *
from RecoJets.JetProducers.GenJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

SFJetProducer = cms.EDProducer(
    "SFJetProducer",
    PFJetParameters.clone(
      src = cms.InputTag("pfNoElectronsCHS"),
      doAreaFastjet = cms.bool(True),
      jetPtMin = cms.double(180.0)
    ),
    AnomalousCellParameters,
    verbose 		= cms.bool(False),
    jetAlgorithm 	= cms.string("CambridgeAachen"),
    rParam       	= cms.double(1.2),
    nFatMax      	= cms.uint32(0),
    centralEtaCut	= cms.double(2.5),
    massDropCut  	= cms.double(0.67),
    rFilt        	= cms.double(0.3),
    asymmCut     	= cms.double(0.3),
    asymmCutLater	= cms.bool(True),
    filterJetPtMin     	= cms.double(15)	
)

SFJetProducerPath = cms.Path(SFJetProducer)

SFJetProducerGen = cms.EDProducer(
    "SFJetProducer",
    GenJetParameters.clone(
      doAreaFastjet = cms.bool(True),
      jetPtMin = cms.double(150.0)
    ),
    AnomalousCellParameters,
    verbose 		= cms.bool(False),
    jetAlgorithm 	= cms.string("CambridgeAachen"),
    rParam       	= cms.double(1.2),
    nFatMax    		= cms.uint32(0),
    centralEtaCut	= cms.double(2.5),
    massDropCut  	= cms.double(0.67),
    rFilt        	= cms.double(0.3),
    asymmCut     	= cms.double(0.3),
    asymmCutLater	= cms.bool(True),
    filterJetPtMin     	= cms.double(15)	
)
