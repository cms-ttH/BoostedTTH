import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("analysis")
# Start of configuration
#------------------------------------------------------------------------------------------------------------------------------------
# list of input files
#filenames=['/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/00000/0AB045B5-BB0C-E511-81FD-0025905A60B8.root']
filenames=['file:/pnfs/desy.de/cms/tier2/store/user/hmildner/ttHTobb_M125_13TeV_powheg_pythia8/Boostedv2MiniAOD/151017_154254/0000/BoostedTTH_MiniAOD_1.root']
# name and path of the output files (without extension)
outfilename='testrun'
# number of events ofthis file to analyze
maxevents=999999999
eventweight=0.01 # xs*lumi/(nPosEvents-nNegEvents)
isData=False
# has the file been prepared with the BoostedProducer?
isBoostedMiniAOD=True
# do you need all systematics (e.g. to calculate limits)?
makeSystematicsTrees=False
# analysisType ('SL' or 'DL')
analysisType='SL'

#------------------------------------------------------------------------------------------------------------------------------------
# End of configuration
filenamestring=os.environ.get("FILENAMES")
if filenamestring != None:
    filenames=filenamestring.split(' ')
if os.environ.get("OUTFILENAME") != None:
    outfilename=os.environ.get("OUTFILENAME")
if os.environ.get("EVENTWEIGHT") != None:
    eventweight=os.environ.get("EVENTWEIGHT")
if os.environ.get("SKIPEVENTS") != None:
    skip=os.environ.get("SKIPEVENTS")
if os.environ.get("MAXEVENTS") != None:
    maxevents=os.environ.get("MAXEVENTS")
if os.environ.get("SYSTEMATICS") != None:
    syststring=os.environ.get("SYSTEMATICS")
    if syststring=='True':
        makeSystematicsTrees=True
    if syststring=='False':
        makeSystematicsTrees=False


#------------------------------------------------------------------------------------------------------------------------------------
# End of configuration

# cmssw options
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
# global tag, you need to change this for data
process.GlobalTag.globaltag = '74X_mcRun2_asymptotic_v2'
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
    process.BoostedAnalyzer.eventWeight = eventweight
process.BoostedAnalyzer.makeSystematicsTrees=makeSystematicsTrees

process.p = cms.Path(process.BoostedAnalyzer)
