################################################################################
# see: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideSubjetFilterJetProducer
################################################################################

import FWCore.ParameterSet.Config as cms

from RecoJets.JetProducers.PFJetParameters_cfi import *
from RecoJets.JetProducers.GenJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

CA12JetsCA3FilterjetsPF = cms.EDProducer(
    "SubjetFilterJetProducer",
    PFJetParameters,
    AnomalousCellParameters,
    verbose 		= cms.bool(False),
    jetAlgorithm 	= cms.string("CambridgeAachen"),
    rParam       	= cms.double(1.2),
    nFatMax      	= cms.uint32(0),
    centralEtaCut	= cms.double(2.0),
    massDropCut  	= cms.double(0.67),
    rFilt        	= cms.double(0.3),
    asymmCut     	= cms.double(0.3),
    asymmCutLater	= cms.bool(True),
    filterJetPtMin     	= cms.double(15)	
)

CA12JetsCA3FilterjetsPF.jetPtMin		= cms.double(180.)
CA12JetsCA3FilterjetsPF.doAreaFastjet	= cms.bool(False)

CA12JetsCA3FilterjetsGen = cms.EDProducer(
    "SubjetFilterJetProducer",
    GenJetParameters,
    AnomalousCellParameters,
    verbose 		= cms.bool(False),
    jetAlgorithm 	= cms.string("CambridgeAachen"),
    rParam       	= cms.double(1.2),
    nFatMax    		= cms.uint32(0),
    centralEtaCut	= cms.double(2.1),
    massDropCut  	= cms.double(0.67),
    rFilt        	= cms.double(0.3),
    asymmCut     	= cms.double(0.3),
    asymmCutLater	= cms.bool(True),
    filterJetPtMin     	= cms.double(15)	
)

CA12JetsCA3FilterjetsGen.jetPtMin		= cms.double(150.)
CA12JetsCA3FilterjetsGen.doAreaFastjet	= cms.bool(False)

filtjet_pf_seq = cms.Sequence(CA12JetsCA3FilterjetsPF)
filtjet_gen_seq = cms.Sequence(CA12JetsCA3FilterjetsGen)
