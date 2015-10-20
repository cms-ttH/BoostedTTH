import FWCore.ParameterSet.Config as cms

# To execute test, run
#  cmsRun mktrees_run2_dijets_cfg.py isData=False label=Test

# parse command-line arguments
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCommandLineParsing
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.register( "label", "Analysis", VarParsing.multiplicity.singleton, VarParsing.varType.string, "prefix of out name" )
options.register( "isData", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "is it data or MC?" )
options.register( "globalTag", "NONE", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )
options.register( "weight", 1.0, VarParsing.multiplicity.singleton, VarParsing.varType.float, "event weight" )
options.register( "era", "2015_74x", VarParsing.multiplicity.singleton, VarParsing.varType.string, "data era" )
options.parseArguments()

# re-set some defaults
if options.globalTag is "NONE":
	if options.isData:
		options.globalTag = "74X_dataRun2_Prompt_v4"
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
print " weight    : "+str(options.weight)
print "*****************************************\n\n"

process = cms.Process("DiJetSelection")

## initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = options.globalTag

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )


## Remake jets to access SV information
# following https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD2015#Advanced_topics_re_clustering_ev

# Define GenJets:
# - filter out neutrinos from packed GenParticles
# - cluster jets from neutrino-cleaned GenParticles
process.packedGenParticlesForJetsNoNu = cms.EDFilter(
	"CandPtrSelector",
	src = cms.InputTag("packedGenParticles"),
	cut = cms.string("abs(pdgId) != 12 && abs(pdgId) != 14 && abs(pdgId) != 16")
	)
from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
process.ak4GenJetsNoNu = ak4GenJets.clone(
	src =  "packedGenParticlesForJetsNoNu"
	)

# Define PFJetsCHS:
# - cluster jets from charged hadron subtracted packed PF candidates
process.pfCHS = cms.EDFilter(
	"CandPtrSelector",
	src =  cms.InputTag("packedPFCandidates"),
	cut = cms.string("fromPV")
	)
from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets
process.ak4PFJetsCHS = ak4PFJets.clone(
	src = 'pfCHS',
	doAreaFastjet = True
	)


# Add PAT jet collection based on the above-defined ak4PFJetsCHS
jetCorrectionsLevels = ['L1FastJet', 'L2Relative', 'L3Absolute']
if options.isData:
	jetCorrectionsLevels.append('L2L3Residual')
from PhysicsTools.PatAlgos.tools.jetTools import *
addJetCollection(
    process,
    labelName = 'AK4PFCHS', # will produce collections 'patJets<labelName>' and 'selectedPatJets<labelName>'
    jetSource = cms.InputTag('ak4PFJetsCHS'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    btagDiscriminators = ['pfCombinedInclusiveSecondaryVertexV2BJetTags'],
    jetCorrections = ('AK4PFchs',jetCorrectionsLevels, 'None'),
    genJetCollection = cms.InputTag('ak4GenJetsNoNu'),
    genParticles = cms.InputTag('prunedGenParticles'),
    algo = 'AK',
    rParam = 0.4
)
# Keep tag info from b-tagging, e.g. SV info 
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideCMSDataAnalysisSchool2015BTaggingExercise#Accessing_additional_b_tag_infor
# Don't really understand why it is only "patJet..." here; "selectedPatJets..." does not work
getattr(process,"patJetsAK4PFCHS").addTagInfos = cms.bool(True)
# Want low pt cut on third jet. Cuts on leading two jets are applied
# by DiJetSelection module.
getattr(process,"selectedPatJetsAK4PFCHS").cut = cms.string('pt > 3')

# The following is needed to produce the selectedPatJets
# Don't know why the process does not run otherwise
process.options = cms.untracked.PSet(
        allowUnscheduled = cms.untracked.bool(True)
)

# Adapt primary vertex collection
# NB: don't know if this is necessary
from PhysicsTools.PatAlgos.tools.pfTools import *
adaptPVs(process, pvCollection=cms.InputTag("offlineSlimmedPrimaryVertices"))


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
		# Spring15 MiniAOVv2
		'/store/mc/RunIISpring15MiniAODv2/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/02E34E6D-3475-E511-9E34-003048CB87A4.root'
		)
	)

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
process.BoostedAnalyzer.outfileName = "DiJets_"+options.label
process.BoostedAnalyzer.processorNames = ["TriggerVarProcessor","DiJetVarProcessor","WeightProcessor"]
process.BoostedAnalyzer.selectionNames = ["VertexSelection","DiJetSelection"]
process.BoostedAnalyzer.useGenHadronMatch = False
process.BoostedAnalyzer.useFatJets = False
process.BoostedAnalyzer.era = options.era
process.BoostedAnalyzer.analysisType = "LJ"
process.BoostedAnalyzer.eventWeight = options.weight
process.BoostedAnalyzer.isData = options.isData
process.BoostedAnalyzer.makeSystematicsTrees = False

# use above re-fitted AK4 jets
process.BoostedAnalyzer.jets               = "selectedPatJetsAK4PFCHS"
process.BoostedAnalyzer.bTagger            = "pfCombinedInclusiveSecondaryVertexV2BJetTags"
process.BoostedAnalyzer.jetTagInfoSV       = "pfInclusiveSecondaryVertexFinder"
process.BoostedAnalyzer.minSVFlightDistSig = 1.
process.BoostedAnalyzer.puJetIDDiscr       = "pileupJetId:fullDiscriminant"

if options.isData:
	process.BoostedAnalyzer.relevantTriggers = cms.vstring(
		'HLT_DiPFJetAve100_HFJEC_v*',
		'HLT_DiPFJetAve140_v*',
		'HLT_DiPFJetAve160_HFJEC_v*',
		'HLT_DiPFJetAve200_v*',
		'HLT_DiPFJetAve220_HFJEC_v*',
		'HLT_DiPFJetAve260_v*',
		'HLT_DiPFJetAve300_HFJEC_v*',
		'HLT_DiPFJetAve320_v*',
		'HLT_DiPFJetAve400_v*',
		'HLT_DiPFJetAve40_v*',
		'HLT_DiPFJetAve500_v*',
		'HLT_DiPFJetAve60_HFJEC_v*',
		'HLT_DiPFJetAve60_v*',
		'HLT_DiPFJetAve80_HFJEC_v*',
		'HLT_DiPFJetAve80_v*',
		
		'HLT_PFJet140_v*',
		'HLT_PFJet200_v*',
		'HLT_PFJet260_v*',
		'HLT_PFJet320_v*',
		'HLT_PFJet400_v*',
		'HLT_PFJet40_v*',
		'HLT_PFJet450_v*',
		'HLT_PFJet500_v*',
		'HLT_PFJet60_v*',
		'HLT_PFJet80_v*',
		)


process.p = cms.Path(
	process.HBHENoiseFilterResultProducer *
	process.ApplyBaselineHBHENoiseFilter *
	process.BoostedAnalyzer
	)
