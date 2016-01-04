import FWCore.ParameterSet.Config as cms

process = cms.Process("analysis")

# cmssw options
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = "74X_dataRun2_v5"
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(999999999))
    

process.source = cms.Source(  "PoolSource",
                              fileNames = cms.untracked.vstring('file:/pnfs/desy.de/cms/tier2/store/user/shwillia/EndOf2015_HbbSync/el_skim_EndOf2015_HbbSync.root'),
                              skipEvents=cms.untracked.uint32(0)
)


## Set up JetCorrections chain to be used in MiniAODHelper
## Note: name is hard-coded to ak4PFchsL1L2L3 and does not
## necessarily reflect actual corrections level
from JetMETCorrections.Configuration.JetCorrectionServices_cff import *
from JetMETCorrections.Configuration.JetCorrectionCondDB_cff import *
process.ak4PFCHSL1Fastjet = cms.ESProducer(
  'L1FastjetCorrectionESProducer',
  level = cms.string('L1FastJet'),
  algorithm = cms.string('AK4PFchs'),
  srcRho = cms.InputTag( 'fixedGridRhoFastjetAll' )
  )
process.ak4PFchsL2Relative = ak4CaloL2Relative.clone( algorithm = 'AK4PFchs' )
process.ak4PFchsL3Absolute = ak4CaloL3Absolute.clone( algorithm = 'AK4PFchs' )
process.ak4PFchsResidual = ak4CaloResidual.clone( algorithm = 'AK4PFchs' )
process.ak4PFchsL1L2L3 = cms.ESProducer("JetCorrectionESChain",
  correctors = cms.vstring(
    'ak4PFCHSL1Fastjet',
    'ak4PFchsL2Relative',
    'ak4PFchsL3Absolute')
)
process.ak4PFchsL1L2L3.correctors.append('ak4PFchsResidual') # add residual JEC for data

# load and run the boosted analyzer
process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_data_cfi")

process.BoostedAnalyzer.outfileName = "sync_el_skim_decSyncHbb"
process.BoostedAnalyzer.processorNames=[]
process.BoostedAnalyzer.selectionNames=[]
process.BoostedAnalyzer.dumpSyncExe2=True
process.BoostedAnalyzer.makeSystematicsTrees=True
process.BoostedAnalyzer.recorrectMET=False
process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")
process.p = cms.Path(process.electronMVAValueMapProducer * process.BoostedAnalyzer)
