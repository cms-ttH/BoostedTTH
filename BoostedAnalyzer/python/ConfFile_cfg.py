import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/nfs/dust/cms/user/shwillia/Test/ttbar_miniAODtest.root'
    )
)

process.demo = cms.EDAnalyzer('BoostedAnalyzer'
)


process.p = cms.Path(process.demo)
