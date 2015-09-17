import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("analysis")
# Start of configuration
#------------------------------------------------------------------------------------------------------------------------------------
# list of input files
filenames=['/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/00000/0AB045B5-BB0C-E511-81FD-0025905A60B8.root']
# name and path of the output files (without extension)
outfilename='testrun'
# number of events ofthis file to analyze
maxevents=10000
# total number of mcevents in sample
#in case of positive and negative weights (of same absolut value, like in MC@NLO): nevents with weight >0 minus nevents with weight <0
mcevents=10000
xs=1 # cross section of the process in pb
isData=False
# has the file been prepared with the BoostedProducer?
isBoostedMiniAOD=False
# do you need all systematics (e.g. to calculate limits)?
makeSystematicsTrees=False
# analysisType ('SL' or 'DL')
analysisType='SL'

#------------------------------------------------------------------------------------------------------------------------------------
# End of configuration

# cmssw options
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = 'MCRUN2_74_V9'
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(int(maxevents)))
process.source = cms.Source(  "PoolSource",
                              fileNames = cms.untracked.vstring(filenames),
)
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
process.ak4PFchsL1L2L3 = cms.ESProducer("JetCorrectionESChain",
  correctors = cms.vstring(
    'ak4PFCHSL1Fastjet',
    'ak4PFchsL2Relative',
    'ak4PFchsL3Absolute')
)

# load and run the boosted analyzer
if isData:
    if analysisType=='SL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_data_cfi")        
    if analysisType=='DL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_dilepton_data_cfi")        
else:
    if analysisType=='SL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
    if analysisType=='DL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_dilepton_cfi")

    if not isBoostedMiniAOD:
        # Supplies PDG ID to real name resolution of MC particles
        process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
        # Needed to determine tt+x category -- is usually run when producing boosted jets in miniAOD 
        process.load("BoostedTTH.BoostedProducer.genHadronMatching_cfi")

if isBoostedMiniAOD:
    process.BoostedAnalyzer.useFatJets=True

process.BoostedAnalyzer.outfileName=outfilename
if not isData:
    process.BoostedAnalyzer.luminosity = 10000.
    process.BoostedAnalyzer.xs = xs
    process.BoostedAnalyzer.nMCEvents = int(mcevents)
process.BoostedAnalyzer.makeSystematicsTrees=makeSystematicsTrees

process.p = cms.Path(process.BoostedAnalyzer)
