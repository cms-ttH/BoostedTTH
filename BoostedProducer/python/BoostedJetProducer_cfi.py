import FWCore.ParameterSet.Config as cms

from RecoJets.JetProducers.PFJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *
    
HTTTopJetProducer = cms.EDProducer(
    "HTTTopJetProducer",
    PFJetParameters.clone(
      src               = cms.InputTag("pfNoElectronsCHS"),
      doAreaFastjet     = cms.bool(True),
      doRhoFastjet      = cms.bool(False),
      jetPtMin          = cms.double(180.0)
    ),
    AnomalousCellParameters,
    algorithm           = cms.int32(1),
    jetAlgorithm        = cms.string("CambridgeAachen"),
    rParam              = cms.double(1.5),
    optimalR            = cms.bool(True),
    qJets               = cms.bool(False),
    minFatjetPt         = cms.double(180.),
    minSubjetPt         = cms.double(0.),
    minCandPt           = cms.double(0.),
    maxFatjetAbsEta     = cms.double(2.0),
    subjetMass          = cms.double(30.),
    muCut               = cms.double(0.8),
    filtR               = cms.double(0.3),
    filtN               = cms.int32(5),
    mode                = cms.int32(4),
    minCandMass         = cms.double(0.),
    maxCandMass         = cms.double(999999.),
    massRatioWidth      = cms.double(999999.),
    minM23Cut           = cms.double(0.),
    minM13Cut           = cms.double(0.),
    maxM13Cut           = cms.double(999999.),
    writeCompound       = cms.bool(True),
    jetCollInstanceName = cms.string("subjets")
)

SFJetProducer = cms.EDProducer(
    "SFJetProducer",
    PFJetParameters.clone(
      src           = cms.InputTag("pfNoElectronsCHS"),
      doAreaFastjet = cms.bool(True),
      doRhoFastjet  = cms.bool(False),
      jetPtMin      = cms.double(180.0)
    ),
    AnomalousCellParameters,
    verbose 		    = cms.bool(False),
    jetAlgorithm 	  = cms.string("CambridgeAachen"),
    rParam       	  = cms.double(1.5),
    nFatMax      	  = cms.uint32(0),
    centralEtaCut	  = cms.double(2.0),
    massDropCut  	  = cms.double(0.67),
    rFilt        	  = cms.double(0.3),
    asymmCut     	  = cms.double(0.3),
    asymmCutLater	  = cms.bool(True),
    filterJetPtMin  = cms.double(15)	
)

BoostedProducerPath = cms.Path(HTTTopJetProducer*SFJetProducer)
