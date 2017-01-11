import FWCore.ParameterSet.Config as cms
import sys
import os

# To execute test, run
#  cmsRun boostedAnalysis_cfg.py isData=False outputFile=testrun maxEvents=100 inputFiles=file:/pnfs/desy.de/cms/tier2/store/user/hmildner/ttHTobb_M125_13TeV_powheg_pythia8/Boostedv2MiniAOD/151017_154254/0000/BoostedTTH_MiniAOD_1.root,file:/pnfs/desy.de/cms/tier2/store/user/hmildner/ttHTobb_M125_13TeV_powheg_pythia8/Boostedv2MiniAOD/151017_154254/0000/BoostedTTH_MiniAOD_2.root

# parse command-line arguments
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCommandLineParsing
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
# The following variables are already defined in VarParsing class:
# maxEvents: singleton, int; default = -1
# inputFiles: (comma separated, no spaces!) list, string: default empty
options.register( "outName", "testrun", VarParsing.multiplicity.singleton, VarParsing.varType.string, "name and path of the output files (without extension)" )
options.register( "weight", 0.01, VarParsing.multiplicity.singleton, VarParsing.varType.float, "xs*lumi/(nPosEvents-nNegEvents)" )
options.register( "skipEvents", 0, VarParsing.multiplicity.singleton, VarParsing.varType.int, "Number of events to skip" )
options.register( "isData", True, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "is it data or MC?" )
options.register( "isBoostedMiniAOD", True, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "has the file been prepared with the BoostedProducer ('custom' MiniAOD)?" )
options.register( "makeSystematicsTrees", True, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "do you need all systematics (e.g. to calculate limits)?" )
options.register( "generatorName", "notSpecified", VarParsing.multiplicity.singleton, VarParsing.varType.string, "'POWHEG','aMC', 'MadGraph' or 'pythia8'" )
options.register( "analysisType", "SL", VarParsing.multiplicity.singleton, VarParsing.varType.string, "'SL' or 'DL'" )
options.register( "globalTag", "76X_dataRun2_v15", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )
options.register( "useJson",False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "apply the json filter (on the grid there are better ways to do this)" )
options.register( "additionalSelection","NONE", VarParsing.multiplicity.singleton, VarParsing.varType.string, "addition Selection to use for this sample" )
options.parseArguments()

# re-set some defaults
if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 10 # reset for testing

if not options.inputFiles:
    options.inputFiles=['file:/pnfs/desy.de/cms/tier2/store/user/shwillia/SingleMuon/Boostedv5MiniAODsilverJson/160217_171824/0000/BoostedTTH_MiniAOD_1.root']

# checks for correct values and consistency
if options.analysisType not in ["SL","DL"]:
    print "\n\nConfig ERROR: unknown analysisType '"+options.analysisType+"'"
    print "Options are 'SL' or 'DL'\n\n"
    sys.exit()
if "data" in options.globalTag.lower() and not options.isData:
    print "\n\nConfig ERROR: GT contains seems to be for data but isData==False\n\n"
    sys.exit()
if "mc" in options.globalTag.lower() and options.isData:
    print "\n\nConfig ERROR: GT contains seems to be for MC but isData==True\n\n"
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
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = options.globalTag
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(int(options.maxEvents)))
process.source = cms.Source(  "PoolSource",
                              fileNames = cms.untracked.vstring(options.inputFiles),
                              skipEvents=cms.untracked.uint32(int(options.skipEvents)),
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
if options.isData:
  process.ak4PFchsL1L2L3.correctors.append('ak4PFchsResidual') # add residual JEC for data

process.ak8PFCHSL1Fastjet = cms.ESProducer(
  'L1FastjetCorrectionESProducer',
  level = cms.string('L1FastJet'),
  algorithm = cms.string('AK8PFchs'),
  srcRho = cms.InputTag( 'fixedGridRhoFastjetAll' )
  )
process.ak8PFchsL2Relative = ak4CaloL2Relative.clone( algorithm = 'AK8PFchs' )
process.ak8PFchsL3Absolute = ak4CaloL3Absolute.clone( algorithm = 'AK8PFchs' )
process.ak8PFchsResidual = ak4CaloResidual.clone( algorithm = 'AK8PFchs' )
process.ak8PFchsL1L2L3 = cms.ESProducer("JetCorrectionESChain",
  correctors = cms.vstring(
    'ak8PFCHSL1Fastjet',
    'ak8PFchsL2Relative',
    'ak8PFchsL3Absolute')
)

if options.isData:
  process.ak8PFchsL1L2L3.correctors.append('ak8PFchsResidual') # add residual JEC for data

#=================================== JEC from DB file for data ===============
if options.isData:
    process.load("CondCore.DBCommon.CondDBCommon_cfi")
    from CondCore.DBCommon.CondDBSetup_cfi import *
    process.jec = cms.ESSource("PoolDBESSource",
                               DBParameters = cms.PSet(
            messageLevel = cms.untracked.int32(0)
            ),
                               timetype = cms.string('runnumber'), # what does this do?
                               toGet = cms.VPSet(
            cms.PSet(
                record = cms.string('JetCorrectionsRecord'),
                tag    = cms.string('JetCorrectorParametersCollection_Fall15_25nsV2_DATA_AK4PFchs'),
                label  = cms.untracked.string('AK4PFchs')
                ),
            cms.PSet(
                record = cms.string('JetCorrectionsRecord'),
                tag    = cms.string('JetCorrectorParametersCollection_Fall15_25nsV2_DATA_AK8PFchs'),
                label  = cms.untracked.string('AK8PFchs')
                ),
#        ..................................................
            ## here you add as many jet types as you need
            ## note that the tag name is specific for the particular sqlite file 
            ), 
                               connect = cms.string('sqlite:///'+os.environ.get('CMSSW_BASE')+'/src/BoostedTTH/BoostedAnalyzer/data/jecs/Fall15_25nsV2_DATA.db')
#                               connect = cms.string('sqlite:../data/jecs/Fall15_25nsV2_DATA.db')
                               )
## add an es_prefer statement to resolve a possible conflict from simultaneous connection to a global tag
    process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')

#===============================================================


# load and run the boosted analyzer
if options.isData:
    if options.analysisType=='SL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_data_cfi")        
    if options.analysisType=='DL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_dilepton_data_cfi")        
else:
    if options.analysisType=='SL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
    if options.analysisType=='DL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_dilepton_cfi")

    if not options.isBoostedMiniAOD:
        # Supplies PDG ID to real name resolution of MC particles
        process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
        # Needed to determine tt+x category -- is usually run when producing boosted jets in miniAOD 
        process.load("BoostedTTH.Producers.genHadronMatching_cfi")

if options.isBoostedMiniAOD:
    process.BoostedAnalyzer.useFatJets=True
else:
    process.BoostedAnalyzer.useFatJets=False

process.BoostedAnalyzer.outfileName=options.outName
if not options.isData:
    process.BoostedAnalyzer.eventWeight = options.weight
process.BoostedAnalyzer.makeSystematicsTrees=options.makeSystematicsTrees
process.BoostedAnalyzer.generatorName=options.generatorName


   
if options.isData and options.useJson:
    print 'use JSON is no longer supported'
### electron MVA ####
# Load the producer for MVA IDs
process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")
process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.BoostedAnalyzer.minJets = [4]
process.BoostedAnalyzer.maxJets = [-1]
process.BoostedAnalyzer.minTags = [2]
process.BoostedAnalyzer.maxTags = [-1]
process.BoostedAnalyzer.minJetsForMEM = 4
process.BoostedAnalyzer.minTagsForMEM = 3
process.BoostedAnalyzer.doBoostedMEM = False
process.BoostedAnalyzer.doJERsystematic = True


process.BoostedAnalyzer.selectionNames = ["VertexSelection","LeptonSelection","JetTagSelection"]
if options.additionalSelection!="NONE":
  process.BoostedAnalyzer.selectionNames+=cms.vstring(options.additionalSelection)

process.BoostedAnalyzer.processorNames = ["WeightProcessor","BasicVarProcessor","MVAVarProcessor","BDTVarProcessor","TTbarReconstructionVarProcessor","BoostedJetVarProcessor","BoostedTopHiggsVarProcessor","BJetnessProcessor","AdditionalJetProcessor","MCMatchVarProcessor","BoostedMCMatchVarProcessor"]

process.p = cms.Path(process.electronMVAValueMapProducer * process.BoostedAnalyzer)
