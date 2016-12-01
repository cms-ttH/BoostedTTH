import FWCore.ParameterSet.Config as cms
import sys
import os

#import ssl
#ssl._create_default_https_context = ssl._create_unverified_contextimport ssl



# To execute test, run
#  cmsRun mktrees_2016_cfg.py isData=False outName=testrun maxEvents=100 inputFiles=/store/data/Run2016B/SingleElectron/MINIAOD/PromptReco-v2/000/273/158/00000/06277EC1-181A-E611-870F-02163E0145E5.root

# parse command-line arguments
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCommandLineParsing
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
# The following variables are already defined in VarParsing class:
# maxEvents: singleton, int; default = -1
# inputFiles: (comma separated, no spaces!) list, string: default empty
options.register( "outName", "testrun_simon", VarParsing.multiplicity.singleton, VarParsing.varType.string, "name and path of the output files (without extension)" )
options.register( "weight", 1., VarParsing.multiplicity.singleton, VarParsing.varType.float, "xs*lumi/(nPosEvents-nNegEvents)" )
options.register( "skipEvents", 0, VarParsing.multiplicity.singleton, VarParsing.varType.int, "Number of events to skip" )
options.register( "isData", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "is it data or MC?" )
options.register( "isBoostedMiniAOD", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "has the file been prepared with the BoostedProducer ('custom' MiniAOD)?" )
options.register( "makeSystematicsTrees", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "do you need all systematics (e.g. to calculate limits)?" )
options.register( "generatorName", "POWHEG", VarParsing.multiplicity.singleton, VarParsing.varType.string, "'POWHEG','aMC', 'MadGraph' or 'pythia8'" )
options.register( "analysisType", "VetoL", VarParsing.multiplicity.singleton, VarParsing.varType.string, "'SL' or 'DL' or 'VetoL'" )
#options.register( "processType", "ZPrime", VarParsing.multiplicity.singleton, VarParsing.varType.string, "'ZPrime' or 'ttH'" )
options.register( "channel", "VETO", VarParsing.multiplicity.singleton, VarParsing.varType.string, "'el' or 'mu' or 'both' or 'VETO'" )
options.register( "globalTag", "NONE", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )
options.register( "additionalSelection","NONE", VarParsing.multiplicity.singleton, VarParsing.varType.string, "addition Selection to use for this sample" )
options.parseArguments()



# re-set some defaults
if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 100000 # reset for testing

if options.globalTag is "NONE":

	# These GT contain the latest 2015-data derived JEC:
	# https://hypernews.cern.ch/HyperNews/CMS/get/JetMET/1630.html
	if options.isData:
		options.globalTag = "80X_dataRun2_Prompt_ICHEP16JEC_v0"
	else:
		options.globalTag = "80X_mcRun2_asymptotic_2016_miniAODv2_v1"

if not options.inputFiles:
    options.inputFiles=['file:/nfs/dust/cms/user/skudella/processed_MC/MC_boosted/MC_QCD_1000_1500.root']

# checks for correct values and consistency
if options.analysisType not in ["SL","DL","VetoL"]:
    print "\n\nConfig ERROR: unknown analysisType '"+options.analysisType+"'"
    print "Options are 'SL' or 'DL' or 'VetoL'\n\n"
    sys.exit()
#if options.processType not in ["ZPrime","ttH"]:
#    print "\n\nConfig ERROR: unknown processType '"+options.processType+"'"
#    print "Options are 'ZPrime' or 'ttH'\n\n"
#    sys.exit()
if "data" in options.globalTag.lower() and not options.isData:
    print "\n\nConfig ERROR: GT contains seems to be for data but isData==False\n\n"
    sys.exit()
if "mc" in options.globalTag.lower() and options.isData:
    print "\n\nConfig ERROR: GT contains seems to be for MC but isData==True\n\n"
    sys.exit()
if not options.inputFiles:
    print "\n\nConfig ERROR: no inputFiles specified\n\n"
    sys.exit()
if not options.channel:
    print "\n\nConfig ERROR: no channel ('el' or 'mu') specified\n\n"
    sys.exit()

# print settings
print "\n\n***** JOB SETUP *************************"
for key in options._register:
    # do not print unused default options
    if key not in ["secondaryInputFiles","section","tag","totalSections","outputFile","secondaryOutputFile","filePrepend"]:
        print str(key)+" : "+str( options.__getattr__(key) )
print "*****************************************\n\n"


process = cms.Process("treemaker")

# cmssw options
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = options.globalTag
process.load("CondCore.CondDB.CondDB_cfi")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(int(options.maxEvents)))
process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(options.inputFiles),
    skipEvents=cms.untracked.uint32(int(options.skipEvents)),
)

#
#JETTOOLBOX
#from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox
#jetToolbox( process, 'ak8', 'jetSequence', 'out', PUMethod='CHS', miniAOD=True, addPruning=True, addNsub=True ) 


# Set up JetCorrections chain to be used in MiniAODHelper
# Note: name is hard-coded to ak4PFchsL1L2L3 and does not
# necessarily reflect actual corrections level

from JetMETCorrections.Configuration.JetCorrectionServices_cff import *
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
    process.ak4PFchsL1L2L3.correctors.append('ak4PFchsResidual') # add residual JEC for data

process.ak8PFCHSL1Fastjet = cms.ESProducer(
    'L1FastjetCorrectionESProducer',
    level = cms.string('L1FastJet'),
    algorithm = cms.string('AK8PFchs'),
    srcRho = cms.InputTag( 'fixedGridRhoFastjetAll' )
)
process.ak8PFchsL2Relative = fixedGridRhoFastjetAllak4CaloL2Relative.clone( algorithm = 'AK8PFchs' )
process.ak8PFchsL3Absolute = ak4CaloL3Absolute.clone( algorithm = 'AK8PFchs' )
process.ak8PFchsResidual = ak4CaloResidual.clone( algorithm = 'AK8PFchs' )
process.ak8PFchsL1L2L3 = cms.ESProducer(
    "JetCorrectionESChain",
    correctors = cms.vstring(
        'ak8PFCHSL1Fastjet',
        'ak8PFchsL2Relative',
        'ak8PFchsL3Absolute'
    )
)

if options.isData:
    process.ak8PFchsL1L2L3.correctors.append('ak8PFchsResidual') # add residual JEC for data



#===============================================================

process.load('BoostedTTH.Producers.SelectedLeptonProducers_cfi')
process.SelectedElectronProducer.ptMins=[15.,20.,30.]
process.SelectedElectronProducer.etaMaxs=[2.4,2.4,2.1]
process.SelectedElectronProducer.leptonIDs=["EndOf15MVA80iso0p15"]*3
process.SelectedElectronProducer.collectionNames=["selectedElectronsLoose","selectedElectronsDL","selectedElectrons"]

process.SelectedMuonProducer.ptMins=[15.,20.,25.]
process.SelectedMuonProducer.etaMaxs=[2.4,2.4,2.1]
process.SelectedMuonProducer.leptonIDs=["tightDL","tightDL","tight"]
process.SelectedMuonProducer.muonIsoConeSizes=["R04"]*3
process.SelectedMuonProducer.muonIsoCorrTypes=["deltaBeta"]*3
process.SelectedMuonProducer.collectionNames=["selectedMuonsLoose","selectedMuonsDL","selectedMuons"]

process.load("BoostedTTH.Producers.SelectedJetProducer_cfi")
process.SelectedJetProducer.jets='slimmedJets'
process.SelectedJetProducer.ptMins=[20,30,20,30]
process.SelectedJetProducer.etaMaxs=[2.4,2.4,2.4,2.4]
process.SelectedJetProducer.collectionNames=["selectedJetsLoose","selectedJets","selectedJetsLooseDL","selectedJetsDL"]
process.load("BoostedTTH.Producers.CorrectedMETproducer_cfi")



# load and run the boosted analyzer
if options.isData:
    if options.analysisType=='SL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_data_cfi")
        process.BoostedAnalyzer.channel = options.channel
    if options.analysisType=='DL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_dilepton_data_cfi")
#    if options.analysisType=='VetoL':
#        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_data_cfi")
#        process.BoostedAnalyzer.channel = ["VETO"]
        
else:
    if options.analysisType=='SL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
        process.BoostedAnalyzer.channel = options.channel
        process.BoostedAnalyzer.muonTriggers = ["None"]
        process.BoostedAnalyzer.electronTriggers = ["None"]
    if options.analysisType=='DL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_dilepton_cfi")
    if options.analysisType=='VetoL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
        process.BoostedAnalyzer.channel = options.channel
        

    if not options.isBoostedMiniAOD:
        # Supplies PDG ID to real name resolution of MC particles
        process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
        # Needed to determine tt+x category -- is usually run when producing boosted jets in miniAOD
        process.load("BoostedTTH.BoostedProducer.genHadronMatching_cfi")

if options.makeSystematicsTrees:
    systs=["","jesup","jesdown"]#,"jerup","jerdown"]
    process.SelectedJetProducer.systematics=systs
    process.BoostedAnalyzer.selectedJets=[cms.InputTag("SelectedJetProducer:selectedJets"+s) for s in systs]
    process.BoostedAnalyzer.selectedJetsLoose=[cms.InputTag("SelectedJetProducer:selectedJetsLoose"+s) for s in systs]
    process.BoostedAnalyzer.correctedMETs=[cms.InputTag("slimmedMETs")]*len(systs)

if options.isBoostedMiniAOD:
    process.BoostedAnalyzer.useFatJets=True
else:
    process.BoostedAnalyzer.useFatJets=False

process.BoostedAnalyzer.outfileName=options.outName
if not options.isData:
    process.BoostedAnalyzer.eventWeight = options.weight

process.BoostedAnalyzer.systematics=process.SelectedJetProducer.systematics
process.BoostedAnalyzer.generatorName=options.generatorName


### electron MVA ####
# Load the producer for MVA IDs
process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")
process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.BoostedAnalyzer.minJets = [3]
process.BoostedAnalyzer.maxJets = [-1]
process.BoostedAnalyzer.minTags = []
process.BoostedAnalyzer.maxTags = [-1]
process.BoostedAnalyzer.minJetsForMEM = 3
process.BoostedAnalyzer.minTagsForMEM = 1
process.BoostedAnalyzer.doJERsystematic = False


process.BoostedAnalyzer.selectionNames = ["VertexSelection","LeptonSelection","JetTagSelection"]
process.BoostedAnalyzer.selectionNames = ["VertexSelection"]

if options.additionalSelection!="NONE":
    process.BoostedAnalyzer.selectionNames+=cms.vstring(options.additionalSelection)

process.BoostedAnalyzer.processorNames = ["WeightProcessor",
"BasicVarProcessor",
"MVAVarProcessor",
"MCMatchVarProcessor",
"ZPrimeToTPrimeAllHadProcessor",
"BoostedJetVarProcessor",
"BoostedMCMatchVarProcessor"]
#process.BoostedAnalyzer.processorNames = ["WeightProcessor","BasicVarProcessor","BoostedJetVarProcessor","BoostedMCMatchVarProcessor"]
process.BoostedAnalyzer.dumpSyncExe2=False

process.content = cms.EDAnalyzer("EventContentAnalyzer")
if options.isData or options.isBoostedMiniAOD:
    process.p = cms.Path(
        process.electronMVAValueMapProducer
        *process.SelectedElectronProducer
        *process.SelectedMuonProducer
        #                    *process.content
        *process.SelectedJetProducer
        *process.CorrectedMETproducer
        *process.BoostedAnalyzer
    )
else:
    process.p = cms.Path(
        process.electronMVAValueMapProducer
        *process.SelectedElectronProducer
        *process.SelectedMuonProducer
        #                    *process.content
        *process.SelectedJetProducer
        *process.CorrectedMETproducer
      	*process.genParticlesForJetsNoNu
	*process.ak4GenJetsCustom
	*process.selectedHadronsAndPartons
	*process.genJetFlavourInfos
	*process.matchGenBHadron
	*process.matchGenCHadron
	*process.categorizeGenTtbar

        *process.BoostedAnalyzer
    )
