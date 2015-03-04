import FWCore.ParameterSet.Config as cms

process = cms.Process("boosted")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'PHYS14_25_V2::All'

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )

process.source = cms.Source(  "PoolSource",
                              fileNames = cms.untracked.vstring('root://xrootd.unl.edu//store/user/puigh/TTHSync/ttjets_phys14_20bx25_withfatjets_v2.root')
)

process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
process.BoostedAnalyzer.useFatJets=True
process.BoostedAnalyzer.disableObjectSelections=True
process.BoostedAnalyzer.outfileName = "Synchronization"
process.BoostedAnalyzer.selectionNames = ["SynchSelection"]
process.BoostedAnalyzer.processorNames = []


process.p = cms.Path(process.BoostedAnalyzer)
