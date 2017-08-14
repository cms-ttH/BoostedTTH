import FWCore.ParameterSet.Config as cms
import sys
import os

from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')

options.register( "outName", "testrun", VarParsing.multiplicity.singleton, VarParsing.varType.string, "name and path of the output files (without extension)" )
options.register( "weight", 1., VarParsing.multiplicity.singleton, VarParsing.varType.float, "xs*lumi/(nPosEvents-nNegEvents)" )
options.register( "skipEvents", 0, VarParsing.multiplicity.singleton, VarParsing.varType.int, "Number of events to skip" )
options.register( "isData", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "is it data or MC?" )
options.register( "globalTag", "80X_mcRun2_asymptotic_2016_TrancheIV_v8", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )
options.register( "useJson",False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "apply the json filter (on the grid there are better ways to do this)" )
options.register("dataEra",     "",     VarParsing.multiplicity.singleton,     VarParsing.varType.string,     "the era of the data taking period, e.g. '2016B', empty for MC" )
options.register( "systematicVariations","nominal", VarParsing.multiplicity.list, VarParsing.varType.string, "comma-separated list of systematic variations ('nominal' or systematics base name, up/down will be added)" )
datasets=['NA','mu','el','elel','elmu','mumu','MET']
options.register( "dataset", "NA", VarParsing.multiplicity.singleton, VarParsing.varType.string, "flag to identify which dataset is used, can be "+','.join(datasets))

options.parseArguments()

if not options.inputFiles:
    if options.isData:
        options.inputFiles=['root://xrootd-cms.infn.it//store/data/Run2016B/MET/MINIAOD/03Feb2017_ver2-v2/100000/028C28AD-47EE-E611-861A-0025905A48EC.root']
        options.globalTag="80X_dataRun2_2016SeptRepro_v7"
        options.dataEra="2016B"
    else:
        options.inputFiles=['root://xrootd-cms.infn.it//store/mc/RunIISummer16MiniAODv2/Vector_MonoJ_NLO_Mphi-1000_Mchi-300_gSM-0p25_gDM-1p0_13TeV-madgraph/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/80000/0405BA3B-71DE-E611-9560-002590E7E01A.root']

if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 1000 # reset for testing
    
# checks for correct values and consistency
if "data" in options.globalTag.lower() and not options.isData:
    print "\n\nConfig ERROR: GT contains seems to be for data but isData==False\n\n"
    sys.exit()
if "mc" in options.globalTag.lower() and options.isData:
    print "\n\nConfig ERROR: GT contains seems to be for MC but isData==True\n\n"
    sys.exit()
if not options.inputFiles:
    print "\n\nConfig ERROR: no inputFiles specified\n\n"
    sys.exit()
if not options.dataset in datasets:
    print options.dataset,'not an allowed dataset, options are',datasets
    sys.exit()
    
# print settings
print "\n\n***** JOB SETUP *************************"
for key in options._register:
    # do not print unused default options
    if key not in ["secondaryInputFiles","section","tag","totalSections","outputFile","secondaryOutputFile","filePrepend"]:
        print str(key)+" : "+str( options.__getattr__(key) )
print "*****************************************\n\n"

### read in which JES/JER Variations to use ###

writeNominal=False
systsJES=[] 
systsJER=[]
if options.systematicVariations:
    for var in options.systematicVariations:
        if var.lower() == "nominal":
            writeNominal=True
        elif var.startswith("JES"):
            systsJES.append( var+"up" )
            systsJES.append( var+"down")
        elif var.startswith("JER"):
            systsJER.append( var+"up" )
            systsJER.append( var+"down")
        else:
            print "ERROR: unknown variation '"+var+"'"
            sys.exit()
systs=systsJER+systsJES

if options.isData:
    systsJER=[]
    systsJES=[]
    systs=[]
    writeNominal=True

###################### start of the cms process #######################

process = cms.Process("boostedAnalysis")

# cmssw options
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = options.globalTag
process.load("CondCore.CondDB.CondDB_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(False)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(int(options.maxEvents)))
process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

process.source = cms.Source(  "PoolSource",
                              fileNames = cms.untracked.vstring(options.inputFiles),
                              skipEvents=cms.untracked.uint32(int(options.skipEvents)),
)

### some standard collections ####
electronCollection = cms.InputTag("slimmedElectrons", "", "PAT")
photonCollection   = cms.InputTag("slimmedPhotons", "", "PAT")
muonCollection	   = cms.InputTag("slimmedMuons", "", "PAT")
tauCollection      = cms.InputTag("slimmedTaus", "", "PAT")
METCollection      = cms.InputTag("slimmedMETs", "", "PAT")
jetCollection      = cms.InputTag("slimmedJets", "", "PAT")

########################## AK4 Jet Correction ##############################
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
  
if options.isData:
  process.ak4PFchsL1L2L3.correctors.append('ak4PFchsResidual') # add residual JEC for data

########################## AK8 Jet Correction ##############################
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

#################### update jes ######################
if options.isData:
    process.GlobalTag.toGet.append(
        cms.PSet(
            connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016AllV4_DATA_AK4PFchs'),
            label  = cms.untracked.string('AK4PFchs')
            )
        )
    process.GlobalTag.toGet.append(
        cms.PSet(
            connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016AllV4_DATA_AK8PFchs'),
            label  = cms.untracked.string('AK8PFchs')
            )
        )
        
# lepton selection
process.load('BoostedTTH.Producers.SelectedLeptonProducers_cfi')
process.SelectedElectronProducer.leptons=electronCollection
process.SelectedElectronProducer.ptMins=[15.,25.,30.]
process.SelectedElectronProducer.etaMaxs=[2.4,2.4,2.1]
process.SelectedElectronProducer.leptonIDs=["electron80XCutBasedT"]*3
process.SelectedElectronProducer.collectionNames=["selectedElectronsLoose","selectedElectronsDL","selectedElectrons"]
process.SelectedElectronProducer.isData=options.isData

process.SelectedMuonProducer.leptons=muonCollection
process.SelectedMuonProducer.ptMins=[15.,25.,26.]
process.SelectedMuonProducer.etaMaxs=[2.4,2.4,2.1]
process.SelectedMuonProducer.leptonIDs=["tightDL","tightDL","tight"]
process.SelectedMuonProducer.muonIsoConeSizes=["R04"]*3
process.SelectedMuonProducer.muonIsoCorrTypes=["deltaBeta"]*3
process.SelectedMuonProducer.collectionNames=["selectedMuonsLoose","selectedMuonsDL","selectedMuons"]
process.SelectedMuonProducer.useMuonRC=False
process.SelectedMuonProducer.useDeterministicSeeds=False
process.SelectedMuonProducer.isData=options.isData

# jet selection
process.load("BoostedTTH.Producers.SelectedJetProducer_cfi")
process.SelectedJetProducer.jets=jetCollection
process.SelectedJetProducer.applyCorrection=False
process.SelectedJetProducer.ptMins=[20,30]
process.SelectedJetProducer.etaMaxs=[2.4,2.4]
process.SelectedJetProducer.collectionNames=["selectedJetsLoose","selectedJets"]
process.SelectedJetProducer.systematics=[""]
process.SelectedJetProducer.PUJetIDMins=["none","none"]
process.SelectedJetProducer.JetID="none"

# load and run the boosted analyzer
if options.isData:
    process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_data_cfi")
    process.BoostedAnalyzer.filterBits=cms.InputTag("TriggerResults::RECO")

else:
    process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")

    
    # Supplies PDG ID to real name resolution of MC particles
    process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
    # Needed to determine tt+x category -- is usually run when producing boosted jets in miniAOD
    process.load("BoostedTTH.Producers.genHadronMatching_cfi")

variations = systs    
if writeNominal:
    variations.insert(0,"") # also store nominal case
print "blabla", variations
process.BoostedAnalyzer.selectedJets=[cms.InputTag("SelectedJetProducer"+s+":selectedJets"+s) for s in variations]
process.BoostedAnalyzer.selectedJetsLoose=[cms.InputTag("SelectedJetProducer"+s+":selectedJetsLoose"+s) for s in variations]
process.BoostedAnalyzer.useFatJets=False
process.BoostedAnalyzer.outfileName=options.outName
if not options.isData:
    process.BoostedAnalyzer.eventWeight = options.weight
process.BoostedAnalyzer.systematics=variations
if options.isData and options.useJson:
    import FWCore.PythonUtilities.LumiList as LumiList
    process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt').getVLuminosityBlockRange()
    
if options.isData:
  process.BoostedAnalyzer.dataset=cms.string(options.dataset)
  
process.BoostedAnalyzer.selectionNames = [
#"FilterSelection",
#"VertexSelection",
#"LeptonSelection",
#"JetTagSelection"
]

if options.isData:
  process.BoostedAnalyzer.processorNames=cms.vstring(
  #"WeightProcessor",
  #"essentialBasicVarProcessor",
  #"essentialMVAVarProcessor",
  #"BDTVarProcessor",
  #"TriggerVarProcessor",
  #"ReconstructionMEvarProcessor",
  #"TTBBStudienProcessor"
  )
else:
  process.BoostedAnalyzer.processorNames=cms.vstring(
  #"WeightProcessor",
  #"essentialMCMatchVarProcessor",
  "essentialBasicVarProcessor",
  #"essentialMVAVarProcessor",
  #"BDTVarProcessor",
  #"TriggerVarProcessor",
  #"ReconstructionMEvarProcessor",
  #"TTBBStudienProcessor"
  )
  
  ##### DEFINE PATH ##########
process.p = cms.Path()

process.p*=process.SelectedElectronProducer*process.SelectedMuonProducer*process.SelectedJetProducer

if not options.isData:
    process.p *= process.genParticlesForJetsNoNu*process.ak4GenJetsCustom*process.selectedHadronsAndPartons*process.genJetFlavourInfos*process.matchGenBHadron*process.matchGenCHadron*process.categorizeGenTtbar


process.p *= process.BoostedAnalyzer