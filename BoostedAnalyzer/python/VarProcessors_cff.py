# Configuration parameters of variable processors
import FWCore.ParameterSet.Config as cms

DiJetVarProcessor = cms.PSet(
    bTagger            = cms.string("pfCombinedInclusiveSecondaryVertexV2BJetTags"),
    jetTagInfoSV       = cms.string("pfInclusiveSecondaryVertexFinder"),
    minSVFlightDistSig = cms.double(1.),
    puJetIDDiscr       = cms.string("pileupJetId:fullDiscriminant"),
)
