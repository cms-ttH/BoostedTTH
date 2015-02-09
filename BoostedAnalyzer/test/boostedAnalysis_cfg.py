import FWCore.ParameterSet.Config as cms

process = cms.Process("boosted")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'PLS170_V7AN1::All'

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100000) )

## JEC
from JetMETCorrections.Configuration.JetCorrectionServices_cff import *

process.ak4PFCHSL1Fastjet = cms.ESProducer(
    'L1FastjetCorrectionESProducer',
    level       = cms.string('L1FastJet'),
    algorithm   = cms.string('AK4PFchs'),
    srcRho      = cms.InputTag( 'fixedGridRhoAll' )
    )

process.ak4PFchsL2Relative = ak5CaloL2Relative.clone( algorithm = 'AK4PFchs' )
process.ak4PFchsL3Absolute = ak5CaloL3Absolute.clone( algorithm = 'AK4PFchs' )

process.ak4PFchsL1L2L3 = cms.ESProducer("JetCorrectionESChain",
    correctors = cms.vstring(
	'ak4PFCHSL1Fastjet', 
        'ak4PFchsL2Relative', 
        'ak4PFchsL3Absolute')
)

process.source = cms.Source(  "PoolSource",
                              #fileNames = cms.untracked.vstring( 'file:/nfs/dust/cms/user/shwillia/Test/ttbar_miniAODtest.root' )
                              fileNames = cms.untracked.vstring( 'file:/nfs/dust/cms/user/shwillia/Test/BoostedMiniAOD.root' )
)

process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")

#process.content = cms.EDAnalyzer("EventContentAnalyzer")
#process.p = cms.Path(process.content*process.BoostedAnalyzer)

process.p = cms.Path(process.BoostedAnalyzer)
