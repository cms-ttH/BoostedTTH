import FWCore.ParameterSet.Config as cms

process = cms.Process("boosted")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'PHYS14_25_V2::All'

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.source = cms.Source(  "PoolSource",
                              #fileNames = cms.untracked.vstring( 'file:/storage/9/mildner/ttbar_miniAODtest.root' )
                              #fileNames = cms.untracked.vstring( 'file:/storage/9/mildner/BoostedMiniAOD_150.root' )
                              fileNames = cms.untracked.vstring('file:/pnfs/desy.de/cms/tier2/store/user/shwillia/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/BoostedTTH_MiniAOD/150223_082502/0000/BoostedMiniAOD_4.root')
)

process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
process.BoostedAnalyzer.useFatJets=True

#process.content = cms.EDAnalyzer("EventContentAnalyzer")
#process.p = cms.Path(process.content*process.BoostedAnalyzer)

process.p = cms.Path(process.BoostedAnalyzer)
