import FWCore.ParameterSet.Config as cms

# To execute test, run
#  cmsRun mktrees_run2_dijets_cfg.py isData=False label=Test

# parse command-line arguments
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCommandLineParsing
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.register( "label", "Analysis", VarParsing.multiplicity.singleton, VarParsing.varType.string, "prefix of out name" )
options.register( "isData", True, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "is it data or MC?" )
options.register( "globalTag", "NONE", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )
options.register( "xs", 1.0, VarParsing.multiplicity.singleton, VarParsing.varType.float, "cross section" )
options.register( "lumi", 1000, VarParsing.multiplicity.singleton, VarParsing.varType.float, "luminosity" )
options.register( "nEvents", 1, VarParsing.multiplicity.singleton, VarParsing.varType.int, "number of events in sample" )
options.register( "era", "2015_74x", VarParsing.multiplicity.singleton, VarParsing.varType.string, "data era" )
options.parseArguments()

# re-set some defaults
if options.globalTag is "NONE":

	# These GT contain the latest 2015-data derived JEC:
	# https://hypernews.cern.ch/HyperNews/CMS/get/JetMET/1630.html
	if options.isData:
		options.globalTag = "74X_dataRun2_Prompt_v2"
	else:
		options.globalTag = "74X_mcRun2_asymptotic_v2"
if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
	options.maxEvents = 1000


# print settings
print "\n\n***** JOB SETUP *************************"
print " label     : "+options.label
print " isData    : "+str(options.isData)
print " globalTag : "+options.globalTag
print " era       : "+options.era
if not options.isData:
	print " xs        : "+str(options.xs)
	print " lumi      : "+str(options.lumi)
	print " nEvents   : "+str(options.nEvents)
print "*****************************************\n\n"

process = cms.Process("InclusiveJetSelection")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = options.globalTag

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

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
process.ak4PFchsL1L2L3 = cms.ESProducer(
  "JetCorrectionESChain",
  correctors = cms.vstring(
    'ak4PFCHSL1Fastjet',
    'ak4PFchsL2Relative',
    'ak4PFchsL3Absolute'
    )
)
if options.isData:
  process.ak4PFchsL1L2L3.correctors.append('ak4PFchsResidual')

process.load('CommonTools.RecoAlgos.HBHENoiseFilterResultProducer_cfi')
process.HBHENoiseFilterResultProducer.minZeros = cms.int32(99999)
process.ApplyBaselineHBHENoiseFilter = cms.EDFilter('BooleanFlagFilter',
   inputLabel = cms.InputTag('HBHENoiseFilterResultProducer','HBHENoiseFilterResult'),
   reverseDecision = cms.bool(False)
)

process.source = cms.Source(
	"PoolSource",
	fileNames = cms.untracked.vstring(
		#'/store/mc/RunIISpring15DR74/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/221B185A-3502-E511-AC72-0025905C4262.root'

		# /QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM
		'/store/mc/RunIISpring15DR74/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/6E887F0F-EDFB-E411-875B-BCAEC54B303A.root'
		)
	)

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
process.BoostedAnalyzer.outfileName = "DiJets_"+options.label
process.BoostedAnalyzer.processorNames = ["TriggerVarProcessor","DiJetVarProcessor","WeightProcessor"]
process.BoostedAnalyzer.selectionNames = ["VertexSelection","DiJetSelection"]
process.BoostedAnalyzer.useGenHadronMatch = False
process.BoostedAnalyzer.era = options.era
process.BoostedAnalyzer.analysisType = "LJ"
process.BoostedAnalyzer.luminosity = options.lumi
process.BoostedAnalyzer.xs = options.xs
process.BoostedAnalyzer.nMCEvents = options.nEvents
process.BoostedAnalyzer.isData = options.isData
process.BoostedAnalyzer.makeSystematicsTrees = False

datatrigger = [
    'HLT_DiPFJetAve100_HFJEC_v3',
    'HLT_DiPFJetAve140_v2',
    'HLT_DiPFJetAve160_HFJEC_v3',
    'HLT_DiPFJetAve200_v2',
    'HLT_DiPFJetAve220_HFJEC_v3',
    'HLT_DiPFJetAve260_v2',
    'HLT_DiPFJetAve300_HFJEC_v3',
    'HLT_DiPFJetAve320_v2',
    'HLT_DiPFJetAve400_v2',
    'HLT_DiPFJetAve40_v2',
    'HLT_DiPFJetAve500_v2',
    'HLT_DiPFJetAve60_HFJEC_v3',
    'HLT_DiPFJetAve60_v2',
    'HLT_DiPFJetAve80_HFJEC_v3',
    'HLT_DiPFJetAve80_v2',

    'HLT_PFJet140_v3',
    'HLT_PFJet200_v3',
    'HLT_PFJet260_v3',
    'HLT_PFJet320_v3',
    'HLT_PFJet400_v3',
    'HLT_PFJet40_v3',
    'HLT_PFJet450_v3',
    'HLT_PFJet500_v3',
    'HLT_PFJet60_v3',
    'HLT_PFJet80_v3',
    ]

MCtrigger = []

if options.isData:
	process.BoostedAnalyzer.relevantTriggers = datatrigger
else: 
	process.BoostedAnalyzer.relevantTriggers = MCtrigger


process.p = cms.Path(
	process.HBHENoiseFilterResultProducer *
	process.ApplyBaselineHBHENoiseFilter *
	process.BoostedAnalyzer
	)
