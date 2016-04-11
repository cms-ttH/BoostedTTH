import FWCore.ParameterSet.Config as cms

from RecoJets.JetProducers.PFJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

ca15PFJetsCHS = cms.EDProducer(
    "FastjetJetProducer",
    PFJetParameters.clone(
      src               = cms.InputTag("pfNoElectronsCHS"),
      jetPtMin          = cms.double(180.0)
    ),
    AnomalousCellParameters,
    jetAlgorithm = cms.string("CambridgeAachen"),
    rParam       = cms.double(1.5)
)
    
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
    maxFatjetAbsEta     = cms.double(99.),
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
    "SubjetFilterJetProducer",
    PFJetParameters.clone(
      src           = cms.InputTag("pfNoElectronsCHS"),
      doAreaFastjet = cms.bool(True),
      doRhoFastjet  = cms.bool(False),
      jetPtMin      = cms.double(180.0)
    ),
    AnomalousCellParameters,
    jetAlgorithm 	  = cms.string("CambridgeAachen"),
    nFatMax      	  = cms.uint32(0),
    rParam       	  = cms.double(1.5),
    rFilt        	  = cms.double(0.3),
    massDropCut  	  = cms.double(0.67),
    asymmCut     	  = cms.double(0.3),
    asymmCutLater	  = cms.bool(True)	
)

ca15PFPrunedJetsCHS = ca15PFJetsCHS.clone(
    usePruning = cms.bool(True),
    nFilt = cms.int32(2),
    zcut = cms.double(0.1),
    rcut_factor = cms.double(0.5),
    useExplicitGhosts = cms.bool(True),
    writeCompound = cms.bool(True), # Also write subjets for pruned fj
    jetCollInstanceName=cms.string("subjets")
)

ca15PFSoftdropJetsCHS = ca15PFJetsCHS.clone(
    useSoftDrop = cms.bool(True),
    zcut = cms.double(0.1),
    beta = cms.double(0.0),
    R0 = cms.double(1.5),
    useExplicitGhosts = cms.bool(True),
    writeCompound = cms.bool(True),
    jetCollInstanceName=cms.string("subjets")
)

ca15PFSoftdropZ2B1JetsCHS = ca15PFJetsCHS.clone(
    useSoftDrop = cms.bool(True),
    zcut = cms.double(0.2),
    beta = cms.double(1.),
    R0 = cms.double(1.5),
    useExplicitGhosts = cms.bool(True),
    writeCompound = cms.bool(True),
    jetCollInstanceName=cms.string("subjets")
)

#BoostedProducerPath = cms.Path(HTTTopJetProducer*SFJetProducer)
