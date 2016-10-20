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
options.register( "isData", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "is it data or MC?" )
options.register( "isBoostedMiniAOD", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "has the file been prepared with the BoostedProducer ('custom' MiniAOD)?" )
options.register( "makeSystematicsTrees", True, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "do you need all systematics (e.g. to calculate limits)?" )
options.register( "generatorName", "POWHEG", VarParsing.multiplicity.singleton, VarParsing.varType.string, "'POWHEG','aMC', 'MadGraph' or 'pythia8'" )
options.register( "analysisType", "SL", VarParsing.multiplicity.singleton, VarParsing.varType.string, "'SL' or 'DL'" )
options.register( "globalTag", "80X_mcRun2_asymptotic_2016_miniAODv2_v1", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )
options.register( "useJson",False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "apply the json filter (on the grid there are better ways to do this)" )
options.register( "additionalSelection","NONE", VarParsing.multiplicity.singleton, VarParsing.varType.string, "addition Selection to use for this sample" )
options.register( "datasetFlag", 0, VarParsing.multiplicity.singleton, VarParsing.varType.int, "int flag to identify which dataset is used")#(0,1,2,3,4,5)->(MC,single ele, single mu,ele ele,ele mu,mu mu)
options.register( "isreHLT",False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "use different trigger process name for the TriggerResults collection when using reHLT Samples" )
options.parseArguments()


# re-set some defaults
if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 1000 # reset for testing

if not options.inputFiles:
    options.inputFiles=['root://xrootd-cms.infn.it//store/mc/RunIISpring16MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext3-v1/00000/0064B539-803A-E611-BDEA-002590D0B060.root']

if options.isData:
  options.globalTag="80X_dataRun2_Prompt_ICHEP16JEC_v0"

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

process = cms.Process("wtf")

# cmssw options
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = options.globalTag
process.load("CondCore.CondDB.CondDB_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(False)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(int(options.maxEvents)))
process.source = cms.Source(  "PoolSource",
                              fileNames = cms.untracked.vstring(options.inputFiles),
                              skipEvents=cms.untracked.uint32(int(options.skipEvents)),
)

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
process.ak4PFchsL1L2L3 = cms.ESProducer("JetCorrectionESChain",
  correctors = cms.vstring(
    'ak4PFCHSL1Fastjet',
    'ak4PFchsL2Relative',
    'ak4PFchsL3Absolute')
)
process.ak4PFchsL3 = cms.ESProducer("JetCorrectionESChain",
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
    process.GlobalTag.toGet.append(
        cms.PSet(
            connect = cms.string('sqlite:///'+os.environ.get('CMSSW_BASE')+'/src/BoostedTTH/BoostedAnalyzer/data/jecs/Spring16_25nsV6_DATA.db'),
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Spring16_25nsV6_DATA_AK4PFchs'),
            label  = cms.untracked.string('AK4PFchs')
        )
    )
    process.GlobalTag.toGet.append(
        cms.PSet(
            connect = cms.string('sqlite:///'+os.environ.get('CMSSW_BASE')+'/src/BoostedTTH/BoostedAnalyzer/data/jecs/Spring16_25nsV6_DATA.db'),
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Spring16_25nsV6_DATA_AK8PFchs'),
            label  = cms.untracked.string('AK8PFchs')
        )
    )
else:
    process.GlobalTag.toGet.append(
        cms.PSet(
            connect = cms.string('sqlite:///'+os.environ.get('CMSSW_BASE')+'/src/BoostedTTH/BoostedAnalyzer/data/jecs/Spring16_25nsV6_MC.db'),
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Spring16_25nsV6_MC_AK4PFchs'),
            label  = cms.untracked.string('AK4PFchs')
        )
    )
    process.GlobalTag.toGet.append(
        cms.PSet(
            connect = cms.string('sqlite:///'+os.environ.get('CMSSW_BASE')+'/src/BoostedTTH/BoostedAnalyzer/data/jecs/Spring16_25nsV6_MC.db'),
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Spring16_25nsV6_MC_AK8PFchs'),
            label  = cms.untracked.string('AK8PFchs')
        )
    )

#===============================================================
#

process.load('BoostedTTH.Producers.SelectedLeptonProducers_cfi')
process.SelectedElectronProducer.ptMins=[15.,25.,30.]
process.SelectedElectronProducer.etaMaxs=[2.4,2.4,2.1]
process.SelectedElectronProducer.leptonIDs=["electron80XCutBasedM"]*3
process.SelectedElectronProducer.collectionNames=["selectedElectronsLoose","selectedElectronsDL","selectedElectrons"]

process.SelectedMuonProducer.ptMins=[15.,25.,25.]
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

process.load("BoostedTTH.BoostedProducer.GenJetswNuProducer_cfi")

process.load("BoostedTTH.Producers.RegressedJetProducer_cfi")
#process.RegressedJetProducer.weightfile = cms.string("BReg_0912_BaseLine_wowortsVars_BDTG.weights.xml")
process.RegressedJetProducer.inputjets=["SelectedJetProducer:selectedJets"]
process.RegressedJetProducer.outputprefix="regressedJets"
process.RegressedJetProducer.doGenJetMatchingforRegression=True
process.RegressedJetProducer.isData=options.isData


# load and run the boosted analyzer
if options.isData:
    if options.analysisType=='SL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_data_cfi")
    if options.analysisType=='DL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_dilepton_data_cfi")
else:
    if options.analysisType=='SL':
        if options.isreHLT:
            process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
        else:
            process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzerNoTrigger_cfi")
    if options.analysisType=='DL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_dilepton_cfi")
    if not options.isBoostedMiniAOD:
        # Supplies PDG ID to real name resolution of MC particles
        process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
        # Needed to determine tt+x category -- is usually run when producing boosted jets in miniAOD
        process.load("BoostedTTH.BoostedProducer.genHadronMatching_cfi")

if options.isreHLT:
    process.BoostedAnalyzer.triggerBits="TriggerResults::HLT2"

if options.makeSystematicsTrees:
    systs=["","jesup","jesdown"]#,"jerup","jerdown"]
    process.SelectedJetProducer.systematics=systs
    process.BoostedAnalyzer.selectedJets=[cms.InputTag("SelectedJetProducer:selectedJets"+s) for s in systs]
    process.BoostedAnalyzer.selectedJetsLoose=[cms.InputTag("SelectedJetProducer:selectedJetsLoose"+s) for s in systs]
    process.BoostedAnalyzer.selectedJetsDL=[cms.InputTag("SelectedJetProducer:selectedJetsDL"+s) for s in systs]
    process.BoostedAnalyzer.selectedJetsLooseDL=[cms.InputTag("SelectedJetProducer:selectedJetsLooseDL"+s) for s in systs]
    process.BoostedAnalyzer.correctedMETs=[cms.InputTag("slimmedMETs")]*len(systs)
    process.RegressedJetProducer.collectionpostfix=systs
    process.RegressedJetProducer.inputjets=[cms.InputTag("SelectedJetProducer:selectedJets"+s) for s in systs]
    process.BoostedAnalyzer.regressedJets=[cms.InputTag("RegressedJetProducer:regressedJets"+s) for s in systs]
    process.BoostedAnalyzer.useregressedJets=True
else:
    process.BoostedAnalyzer.selectedJets=[cms.InputTag("SelectedJetProducer:selectedJets")]
    process.BoostedAnalyzer.selectedJetsLoose=[cms.InputTag("SelectedJetProducer:selectedJetsLoose")]
    process.BoostedAnalyzer.selectedJetsDL=[cms.InputTag("SelectedJetProducer:selectedJetsDL")]
    process.BoostedAnalyzer.selectedJetsLooseDL=[cms.InputTag("SelectedJetProducer:selectedJetsLooseDL")]
    process.BoostedAnalyzer.correctedMETs=[cms.InputTag("slimmedMETs")]
    process.RegressedJetProducer.inputjets=[cms.InputTag("SelectedJetProducer:selectedJets")]
    process.BoostedAnalyzer.regressedJets=[cms.InputTag("RegressedJetProducer:regressedJets")]
    process.BoostedAnalyzer.useregressedJets=True

if options.isBoostedMiniAOD:
    process.BoostedAnalyzer.useFatJets=True
else:
    process.BoostedAnalyzer.useFatJets=False

process.BoostedAnalyzer.outfileName=options.outName
if not options.isData:
    process.BoostedAnalyzer.eventWeight = options.weight

process.BoostedAnalyzer.systematics=process.SelectedJetProducer.systematics
process.BoostedAnalyzer.generatorName=options.generatorName


if options.isData and options.useJson:
    #print 'use JSON is no longer supported'
    import FWCore.PythonUtilities.LumiList as LumiList
    process.source.lumisToProcess = LumiList.LumiList(filename = '/nfs/dust/cms/user/kelmorab/CMSSW8/Cert_271036-276811_13TeV_PromptReco_Collisions16_JSON.txt').getVLuminosityBlockRange()
### electron MVA ####
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
#process.BoostedAnalyzer.doJERsystematic = False

if options.isData:
  process.BoostedAnalyzer.datasetFlag=cms.int32(options.datasetFlag)

process.BoostedAnalyzer.selectionNames = cms.vstring("VertexSelection","LeptonSelection","JetTagSelection")
#process.BoostedAnalyzer.selectionNames = ["VertexSelection","LeptonSelection","JetTagSelection"]
if options.additionalSelection!="NONE":
  process.BoostedAnalyzer.selectionNames+=cms.vstring(options.additionalSelection)

process.BoostedAnalyzer.processorNames = cms.vstring("BDTVarProcessor","WeightProcessor","MCMatchVarProcessor","BoostedMCMatchVarProcessor","BasicVarProcessor","MVAVarProcessor","TriggerVarProcessor","BoostedJetVarProcessor","RegressionVarProcessor","QuarkMatchingVarProcessor")

#process.content = cms.EDAnalyzer("EventContentAnalyzer")
if options.isData:
  process.p = cms.Path(process.electronMVAValueMapProducer
                     *process.SelectedElectronProducer
                     *process.SelectedMuonProducer
                     #*process.content
                     *process.SelectedJetProducer
                     *process.CorrectedMETproducer
                     *process.RegressedJetProducer
                     #*process.genParticlesForJetsNoNu*process.ak4GenJetsCustom*process.selectedHadronsAndPartons*process.genJetFlavourInfos*process.matchGenBHadron*process.matchGenCHadron*process.categorizeGenTtbar
                     *process.BoostedAnalyzer
                     )
elif  options.isBoostedMiniAOD:
    process.p = cms.Path(process.electronMVAValueMapProducer
                       *process.SelectedElectronProducer
                       *process.SelectedMuonProducer
                       #*process.content
                       *process.SelectedJetProducer
                       *process.CorrectedMETproducer
                       *process.genParticlesForJetswNu*process.ak4GenJetsCustomwNu
                       *process.RegressedJetProducer
                       #*process.genParticlesForJetsNoNu*process.ak4GenJetsCustom*process.selectedHadronsAndPartons*process.genJetFlavourInfos*process.matchGenBHadron*process.matchGenCHadron*process.categorizeGenTtbar
                       *process.BoostedAnalyzer
                       )
else:
  process.p = cms.Path(process.electronMVAValueMapProducer
                     *process.SelectedElectronProducer
                     *process.SelectedMuonProducer
 #                    *process.content
                     *process.SelectedJetProducer
                     *process.CorrectedMETproducer
                     *process.genParticlesForJetswNu*process.ak4GenJetsCustomwNu
                     *process.RegressedJetProducer
                     *process.genParticlesForJetsNoNu*process.ak4GenJetsCustom*process.selectedHadronsAndPartons*process.genJetFlavourInfos*process.matchGenBHadron*process.matchGenCHadron*process.categorizeGenTtbar
                     *process.BoostedAnalyzer
                     )
