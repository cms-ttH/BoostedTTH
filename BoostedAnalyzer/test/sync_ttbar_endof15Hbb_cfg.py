import FWCore.ParameterSet.Config as cms
import sys

# To execute test, run
#  cmsRun boostedAnalysis_cfg.py isData=False outputFile=testrun maxEvents=100 inputFiles=file:/pnfs/desy.de/cms/tier2/store/user/hmildner/ttHTobb_M125_13TeV_powheg_pythia8/Boostedv2MiniAOD/151017_154254/0000/BoostedTTH_MiniAOD_1.root,file:/pnfs/desy.de/cms/tier2/store/user/hmildner/ttHTobb_M125_13TeV_powheg_pythia8/Boostedv2MiniAOD/151017_154254/0000/BoostedTTH_MiniAOD_2.root

# parse command-line arguments
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCommandLineParsing
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
# The following variables are already defined in VarParsing class:
# maxEvents: singleton, int; default = -1
# inputFiles: (comma separated, no spaces!) list, string: default empty
options.register( "globalTag", "MCRUN2_74_V9", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )
options.parseArguments()

# re-set some defaults
if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 10000000 # reset to 100 for testing
if not options.inputFiles:
    options.inputFiles=['file:/pnfs/desy.de/cms/tier2/store/user/shwillia/EndOf2015_HbbSync/ttbar_EndOf2015_HbbSync.root']

# checks for correct values and consistency
if "data" in options.globalTag.lower():
    print "\n\nConfig ERROR: GT contains seems to be for data\n\n"
    sys.exit()
if not options.inputFiles:
    print "\n\nConfig ERROR: no inputFiles specified\n\n"
    sys.exit()
    
# print settings
print "\n\n***** JOB SETUP *************************"
for key in options._register:
    # do not print unused default options
    if key not in ["secondaryInputFiles","section","tag","totalSections","outputFile","secondaryOutputFile","filePrepend"]:
        print str(key)+" : "+str( options.__getattr__(key) )
print "*****************************************\n\n"


process = cms.Process("analysis")

# cmssw options
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = options.globalTag
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(int(options.maxEvents)))
process.source = cms.Source(  "PoolSource",
                              fileNames = cms.untracked.vstring(options.inputFiles),
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

# load and run the boosted analyzer
process.load("BoostedTTH.BoostedAnalyzer.EndOf2015HbbSync_cfi")

process.BoostedAnalyzer.outfileName = "sync_ttbar_endof15Hbb"

process.p = cms.Path(process.BoostedAnalyzer)
