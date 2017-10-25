import FWCore.ParameterSet.Config as cms
import sys
import os

# To execute test, run
#  cmsRun boostedAnalysis_cfg.py isData=False outputFile=testrun maxEvents=100 inputFiles=/store/user/mschrode/ttHTobb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/Skim-V1_3j20_1l20/170217_163603/0000/Skim_1.root

# parse command-line arguments
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCommandLineParsing
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
# The following variables are already defined in VarParsing class:
# maxEvents: singleton, int; default = -1
# inputFiles: (comma separated, no spaces!) list, string: default empty
options.register( "outName", "testrun", VarParsing.multiplicity.singleton, VarParsing.varType.string, "name and path of the output files (without extension)" )
options.register( "weight", 1, VarParsing.multiplicity.singleton, VarParsing.varType.float, "xs*lumi/(nPosEvents-nNegEvents)" )
options.register( "skipEvents", 0, VarParsing.multiplicity.singleton, VarParsing.varType.int, "Number of events to skip" )
options.register( "isData", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "is it data or MC?" )
options.register( "isBoostedMiniAOD", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "has the file been prepared with the BoostedProducer ('custom' MiniAOD)?" )
options.register( "generatorName", "POWHEG", VarParsing.multiplicity.singleton, VarParsing.varType.string, "'POWHEG','aMC', 'MadGraph' or 'pythia8'" )
options.register( "globalTag", "NONE", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )
#options.register( "globalTag", "80X_mcRun2_asymptotic_2016_TrancheIV_v8", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )

options.register( "useJson",False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "apply the json filter (on the grid there are better ways to do this)" )
options.register( "additionalSelection","NONE", VarParsing.multiplicity.singleton, VarParsing.varType.string, "addition Selection to use for this sample" )
datasets=['NA','mu','el','elel','elmu','mumu']
options.register( "dataset", "NA", VarParsing.multiplicity.singleton, VarParsing.varType.string, "flag to identify which dataset is used, can be "+','.join(datasets))
options.register( "calcBJetness",False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "Calculate BJetness variables" )
options.register( "dumpSyncExe", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "Dump textfiles for sync exe?" )
options.register( "systematicVariations","nominal", VarParsing.multiplicity.list, VarParsing.varType.string, "comma-separated list of systematic variations ('nominal' or systematics base name, up/down will be added)" )
options.register("deterministicSeeds",True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,"create collections with deterministic seeds")
options.register("electronRegression","GT",VarParsing.multiplicity.singleton,VarParsing.varType.string,"'GT' or an absolute path to a sqlite file for electron energy regression")
options.register("electronSmearing","Moriond17_23Jan",VarParsing.multiplicity.singleton,VarParsing.varType.string,"correction type for electron energy smearing")
options.register( "useMuonRC", True, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "use Rochester Correction for muons" )
options.register("recorrectMET",     True,     VarParsing.multiplicity.singleton,     VarParsing.varType.bool,     "recorrect MET using latest JES and e/g corrections" )
options.register("dataEra",     "",     VarParsing.multiplicity.singleton,     VarParsing.varType.string,     "the era of the data taking period, e.g. '2016B', empty for MC" )
options.register("updatePUJetId",     True,     VarParsing.multiplicity.singleton,     VarParsing.varType.bool,     "update the PUJetId values" )
options.register( "ProduceMemNtuples", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "do you want to produce slimmed ntuples as input to mem code?" )
options.register( "LeptonChannel", "veto", VarParsing.multiplicity.singleton, VarParsing.varType.string, "'el' or 'mu' or 'both' or 'veto'" )



options.parseArguments()

if options.globalTag is "NONE":

	# These GT contain the latest 2015-data derived JEC:
	# https://hypernews.cern.ch/HyperNews/CMS/get/JetMET/1630.html
	if options.isData:
		options.globalTag = "80X_dataRun2_Prompt_ICHEP16JEC_v0"
	else:
		options.globalTag = "80X_mcRun2_asymptotic_2016_miniAODv2_v1"


# re-set some defaults
if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
    #options.maxEvents = 10000 # reset for testing
    options.maxEvents = 999999999 # reset for testing
    #options.maxEvents = 10 # reset for testing
    #options.maxEvents = 100 # reset for testing

if not options.inputFiles:
    #options.inputFiles=['file:/pnfs/desy.de/cms/tier2/store/user/mschrode/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/Skim-V1_3j20_1l20/170217_171402/0000/Skim_1.root']
    #options.inputFiles=['/store/mc/RunIISpring16MiniAODv2/ZprimeToTprimeT_TprimeToWB_MZp-2500Nar_MTp-1500Nar_LH_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/70000/469FD823-443D-E611-AF27-D4AE526EAB7F.root']
    options.inputFiles=['file:/nfs/dust/cms/user/skudella/E22941D1-F526-E611-9437-B499BAAC078E.root']
# checks for correct values and consistency

if options.LeptonChannel not in ["el","mu","both","veto"]:
    print "\n\nConfig ERROR: unknown analysisType '"+options.analysisType+"'"
    print "Options are 'el' or 'mu' or 'both' or 'veto'\n\n"
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

writeNominal=False
systsJES=[] 
systsJER=[]
if options.systematicVariations:
    print options.systematicVariations
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

process = cms.Process("boostedAnalysis")

# cmssw options
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = options.globalTag
process.load("CondCore.CondDB.CondDB_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
#process.options.allowUnscheduled = cms.untracked.bool(False)
process.options.allowUnscheduled = cms.untracked.bool(True)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(int(options.maxEvents)))
process.source = cms.Source(  "PoolSource",
                              fileNames = cms.untracked.vstring(options.inputFiles),
                              skipEvents=cms.untracked.uint32(int(options.skipEvents)),
)
process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_38T_cff")


### some standard collections ####
electronCollection = cms.InputTag("slimmedElectrons", "", "PAT")
photonCollection   = cms.InputTag("slimmedPhotons", "", "PAT")
muonCollection	   = cms.InputTag("slimmedMuons", "", "PAT")
tauCollection      = cms.InputTag("slimmedTaus", "", "PAT")
METCollection      = cms.InputTag("slimmedMETs", "", "PAT")
jetCollection      = cms.InputTag("slimmedJets", "", "PAT")



###### deterministic seed producer ######

if options.deterministicSeeds:
    process.load("PhysicsTools.PatUtils.deterministicSeeds_cfi")
    process.deterministicSeeds.produceCollections = cms.bool(True)
    process.deterministicSeeds.produceValueMaps   = cms.bool(False)
    process.deterministicSeeds.electronCollection = electronCollection
    process.deterministicSeeds.muonCollection     = muonCollection
    process.deterministicSeeds.tauCollection      = tauCollection
    process.deterministicSeeds.photonCollection   = photonCollection
    process.deterministicSeeds.jetCollection      = jetCollection
    process.deterministicSeeds.METCollection      = METCollection

    # overwrite output collections
    electronCollection = cms.InputTag("deterministicSeeds", "electronsWithSeed", process.name_())
    muonCollection     = cms.InputTag("deterministicSeeds", "muonsWithSeed", process.name_())
    tauCollection      = cms.InputTag("deterministicSeeds", "tausWithSeed", process.name_())
    photonCollection   = cms.InputTag("deterministicSeeds", "photonsWithSeed", process.name_())
    jetCollection      = cms.InputTag("deterministicSeeds", "jetsWithSeed", process.name_())
    METCollection      = cms.InputTag("deterministicSeeds", "METsWithSeed", process.name_())







###########################################################################
runonMC=str(not options.isData)
print "runonMC  ", runonMC

#JETTOOLBOX
from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox

jetToolbox( process, 'ak8', 'ak8JetSubs', 'out', runOnMC=runonMC, PUMethod='CHS', miniAOD=True,  addSoftDrop=True, addPruning=True, addSoftDropSubjets=True, addPrunedSubjets=True, addNsub=True,  addNsubSubjets=True,  addCMSTopTagger=True, Cut='pt > 150', JETCorrPayload = 'AK8PFchs', subJETCorrPayload='AK4PFchs', JETCorrLevels = ['L1FastJet','L2Relative', 'L3Absolute'], subJETCorrLevels=['L1FastJet','L2Relative', 'L3Absolute']  )
#jetToolbox( process, 'ak12', 'ak12JetSubs', 'out', runOnMC=runonMC, PUMethod='CHS', miniAOD=True,  addSoftDrop=True, addSoftDropSubjets=True, addNsub=True,  addNsubSubjets=True,  addCMSTopTagger=True, Cut='pt > 80', JETCorrPayload = 'AK8PFchs', JETCorrLevels = ['L2Relative', 'L3Absolute'])
#jetToolbox( process, 'ak15', 'ak15JetSubs', 'out', runOnMC=runonMC, PUMethod='CHS', miniAOD=True,  addSoftDrop=True, addSoftDropSubjets=True, addNsub=True,  addNsubSubjets=True,  addCMSTopTagger=True, Cut='pt > 80', JETCorrPayload = 'AK8PFchs', JETCorrLevels = ['L2Relative', 'L3Absolute'])
#jetToolbox( process, 'ak4', 'ak4JetSubs', 'out', runOnMC=runonMC, PUMethod='PUPPI', miniAOD=True, Cut='pt > 75', JETCorrPayload = 'AK4PFchs', JETCorrLevels = ['L1FastJet','L2Relative', 'L3Absolute'])
jetToolbox( process, 'ak8', 'ak8JetSubs', 'out', runOnMC=runonMC, PUMethod='PUPPI',miniAOD=True,  addSoftDrop=True, addPruning=True, addSoftDropSubjets=True, addPrunedSubjets=True, addNsub=True,  addNsubSubjets=True,  addCMSTopTagger=True, Cut='pt > 150', JETCorrPayload = 'AK8PFPUPPI', subJETCorrPayload='AK4PFPUPPI', JETCorrLevels = ['L1FastJet','L2Relative', 'L3Absolute'], subJETCorrLevels=['L1FastJet','L2Relative', 'L3Absolute']  )



process.load('CommonTools/PileupAlgos/Puppi_cff')

jetCollectionAK4PUPPI             = cms.InputTag('slimmedJetsPuppi')
#jetCollectionAK4PUPPI             = cms.InputTag("packedPatJetsAK4PF")
jetCollectionAK8CHSSoftDrop       = cms.InputTag("packedPatJetsAK8PFCHSSoftDrop")
jetCollectionAK8CHSPruning        = cms.InputTag("packedPatJetsAK8PFPruned")
jetCollectionAK8PUPPISoftDrop     = cms.InputTag("packedPatJetsAK8PFSoftDrop")
jetCollectionAK8PUPPIPruning      = cms.InputTag("packedPatJetsAK8PFPruned")

#packedPatJetsAK8PFSoftDroppackedPatJetsAK8PFPruned


#jetCollectionAK8      = cms.InputTag("packedPatJetsAK8PFCHSSoftDrop")
#jetCollectionAK12     = cms.InputTag("packedPatJetsAK12PFCHSSoftDrop")
#jetCollectionAK15     = cms.InputTag("packedPatJetsAK15PFCHSSoftDrop")


#process.content = cms.EDAnalyzer("EventContentAnalyzer")











##########################################

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


process.ak4PFPuppiL1Fastjet = cms.ESProducer(
  'L1FastjetCorrectionESProducer',
  level = cms.string('L1FastJet'),
  algorithm = cms.string('AK4PFPuppi'),
  srcRho = cms.InputTag( 'fixedGridRhoFastjetAll' )
  )
process.ak4PFPuppiL2Relative = ak4CaloL2Relative.clone( algorithm = 'AK4PFPuppi' )
process.ak4PFPuppiL3Absolute = ak4CaloL3Absolute.clone( algorithm = 'AK4PFPuppi' )
process.ak4PFPuppiResidual = ak4CaloResidual.clone( algorithm = 'AK4PFPuppi' )
process.ak4PFPuppiL1L2L3 = cms.ESProducer("JetCorrectionESChain",
  correctors = cms.vstring(
    'ak4PFPuppiL1Fastjet',
    'ak4PFPuppiL2Relative',
    'ak4PFPuppiL3Absolute')
)
if options.isData:
  process.ak4PFPuppiL1L2L3.correctors.append('ak4PFPuppiResidual') # add residual JEC for data



process.ak8PFPuppiL1Fastjet = cms.ESProducer(
  'L1FastjetCorrectionESProducer',
  level = cms.string('L1FastJet'),
  algorithm = cms.string('AK8PFPuppi'),
  srcRho = cms.InputTag( 'fixedGridRhoFastjetAll' )
  )
process.ak8PFPuppiL2Relative = ak4CaloL2Relative.clone( algorithm = 'AK8PFPuppi' )
process.ak8PFPuppiL3Absolute = ak4CaloL3Absolute.clone( algorithm = 'AK8PFPuppi' )
process.ak8PFPuppiResidual = ak4CaloResidual.clone( algorithm = 'AK8PFPuppi' )
process.ak8PFPuppiL1L2L3 = cms.ESProducer("JetCorrectionESChain",
  correctors = cms.vstring(
    'ak8PFPuppiL1Fastjet',
    'ak8PFPuppiL2Relative',
    'ak8PFPuppiL3Absolute')
)
if options.isData:
  process.ak8PFPuppiL1L2L3.correctors.append('ak8PFPuppiResidual') # add residual JEC for data






  

## update jes
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
            tag    = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016AllV4_DATA_AK4PFchs'),
            label  = cms.untracked.string('AK8PFchs')
            )
        )

    process.GlobalTag.toGet.append(
        cms.PSet(
            connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016AllV4_DATA_AK4PFPuppi'),
            label  = cms.untracked.string('AK4PFPuppi')
            )
        )
    process.GlobalTag.toGet.append(
        cms.PSet(
            connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016AllV4_DATA_AK8PFPuppi'),
            label  = cms.untracked.string('AK8PFPuppi')
            )
        )





















###### electron energy regression #######

if options.electronRegression:
    if options.electronRegression == "GT":
        from EgammaAnalysis.ElectronTools.regressionWeights_cfi import regressionWeights
        process = regressionWeights(process)
    else:
        from EgammaAnalysis.ElectronTools.regressionWeights_local_cfi import GBRDWrapperRcd
        GBRDWrapperRcd.connect = cms.string("sqlite_file:" + options.electronRegression)
        process.regressions = GBRDWrapperRcd
        process.regressions.DumpStat = cms.untracked.bool(False)
        process.es_prefer_regressions = cms.ESPrefer("PoolDBESSource", "regressions")
    process.load("EgammaAnalysis.ElectronTools.regressionApplication_cff")

    # set the electron and photon sources
    process.slimmedElectrons.src = electronCollection
    process.slimmedPhotons.src = photonCollection

    # overwrite output collections
    electronCollection = cms.InputTag("slimmedElectrons", "", process.name_())
    photonCollection = cms.InputTag("slimmedPhotons", "", process.name_())

##########################################

##### electron energy smearing #####

if options.electronSmearing and options.electronRegression:
    # the smearing procedure requires a preselection
    process.selectedElectrons = cms.EDFilter("PATElectronSelector",
        src = electronCollection,
        cut = cms.string("pt>5 && abs(superCluster.eta)<2.5")
    )
    electronCollection = cms.InputTag("selectedElectrons", "", process.name_())
    # setup the smearing
    process.load("EgammaAnalysis.ElectronTools.calibratedPatElectronsRun2_cfi")
    from EgammaAnalysis.ElectronTools.calibratedPatElectronsRun2_cfi import files
    process.calibratedPatElectrons.isMC           = cms.bool(not options.isData)
    process.calibratedPatElectrons.correctionFile = cms.string(files[options.electronSmearing])
    process.calibratedPatElectrons.electrons      = electronCollection
    #seq += process.calibratedPatElectrons

    # use our deterministic seeds or a random generator service
    if options.deterministicSeeds:
        process.calibratedPatElectrons.seedUserInt = process.deterministicSeeds.seedUserInt
    else:
        process.load("Configuration.StandardSequences.Services_cff")
        process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
            calibratedPatElectrons = cms.PSet(
                initialSeed = cms.untracked.uint32(81),
                engineName  = cms.untracked.string("TRandom3")
            )
        )

    # overwrite output collections
    electronCollection = cms.InputTag("calibratedPatElectrons", "", process.name_())

##########################################

### electron ID ####
eleMVAid=True
if eleMVAid:
    from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
    dataFormat = DataFormat.MiniAOD
    switchOnVIDElectronIdProducer(process, dataFormat)
# Spring 16 MVA ID 
    my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff',
                     #'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring15_25ns_Trig_V1_cff',
                     #'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff'
                     ]
    for idmod in my_id_modules:
        setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

process.egmGsfElectronIDs.physicsObjectSrc = electronCollection
process.electronRegressionValueMapProducer.srcMiniAOD = electronCollection
process.electronMVAValueMapProducer.srcMiniAOD = electronCollection

### BJetness ###
if options.calcBJetness:
    process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")        
    process.load('BoostedTTH.BoostedAnalyzer.BJetness_cfi')
    process.BJetness.is_data = options.isData
    process.BJetness.patElectrons = electronCollection
    process.BJetness.muons = muonCollection

# lepton selection
process.load('BoostedTTH.Producers.SelectedLeptonProducers_cfi')
process.SelectedElectronProducer.leptons=electronCollection
process.SelectedElectronProducer.ptMins=[15.,15.,30.]
process.SelectedElectronProducer.etaMaxs=[2.4,2.4,2.4]
process.SelectedElectronProducer.leptonIDs=["electronGeneralPurposeMVA2016WP80","electronGeneralPurposeMVA2016WP90","electronGeneralPurposeMVA2016WP90"]
process.SelectedElectronProducer.collectionNames=["selectedElectronsLoose","selectedElectronsDL","selectedElectrons"]
process.SelectedElectronProducer.isData=options.isData

process.SelectedMuonProducer.leptons=muonCollection
process.SelectedMuonProducer.ptMins=[15.,15.,30.]
process.SelectedMuonProducer.etaMaxs=[2.4,2.4,2.4]
process.SelectedMuonProducer.leptonIDs=["loose","muonMediumICHEP","muonMediumICHEP"]
process.SelectedMuonProducer.muonIsoConeSizes=["R04","R04","R04"]
process.SelectedMuonProducer.muonIsoCorrTypes=["deltaBeta"]*3
process.SelectedMuonProducer.collectionNames=["selectedMuonsLoose","selectedMuonsDL","selectedMuons"]
process.SelectedMuonProducer.useMuonRC=options.useMuonRC
process.SelectedMuonProducer.useDeterministicSeeds=options.deterministicSeeds
process.SelectedMuonProducer.isData=options.isData

#process.SelectedMuonProducerUncorr=process.SelectedMuonProducer.clone(ptMins=[15.],etaMaxs=[2.4],leptonIDs=["tight"],muonIsoConeSizes=["R04"],muonIsoCorrTypes=["deltaBeta"],collectionNames=["selectedMuonsUncorr"],useMuonRC=False)

### MET correction with official met tool ###
if options.recorrectMET:
    # patch the phi correction parameter sets that are used in runMetCorAndUncFromMiniAOD,
    # we only need to overwrite patMultPhiCorrParams_T1Txy_25ns with the new one
    if options.isData:
        if options.dataEra in ("2016B", "2016C", "2016D", "2016E", "2016F"):
            from MetTools.MetPhiCorrections.tools.multPhiCorr_ReMiniAOD_Data_BCDEF_80X_sumPt_cfi \
                    import multPhiCorr_Data_BCDEF_80X as metPhiCorrParams
        else: # "2016G", "2016Hv2", "2016Hv3"
            from MetTools.MetPhiCorrections.tools.multPhiCorr_ReMiniAOD_Data_GH_80X_sumPt_cfi \
                    import multPhiCorr_Data_GH_80X as metPhiCorrParams
    else:
        from MetTools.MetPhiCorrections.tools.multPhiCorr_Summer16_MC_DY_80X_sumPt_cfi \
                import multPhiCorr_MC_DY_sumPT_80X as metPhiCorrParams
    # actual patch
    import PhysicsTools.PatUtils.patPFMETCorrections_cff as metCors
    metCors.patMultPhiCorrParams_T1Txy_25ns = metPhiCorrParams

    # use the standard tool
    from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
    # do not use a postfix here!
    runMetCorAndUncFromMiniAOD(process,
        isData           = options.isData,
        electronColl     = electronCollection.value(),
        muonColl         = muonCollection.value(),
        tauColl          = tauCollection.value(),
        photonColl       = photonCollection.value(),
        jetCollUnskimmed = jetCollection.value(),
        recoMetFromPFCs  = True
    )

    # overwrite output collections
    METCollection = cms.InputTag("slimmedMETs", "", process.name_())

    # also add MET corrections due to e/g corrections, such as the slew rate fix in reMiniAOD
    if options.isData:
        from PhysicsTools.PatUtils.tools.corMETFromMuonAndEG import corMETFromMuonAndEG
        corMETFromMuonAndEG(process,
            pfCandCollection      = "",
            electronCollection    = "slimmedElectronsBeforeGSFix",
            photonCollection      = "slimmedPhotonsBeforeGSFix",
            corElectronCollection = electronCollection.value(),
            corPhotonCollection   = photonCollection.value(),
            allMETEGCorrected     = True,
            muCorrection          = False,
            eGCorrection          = True,
            runOnMiniAOD          = True,
            postfix               = "MuEGClean"
        )
        
        process.slimmedMETsMuEGClean = process.slimmedMETs.clone(
            src             = cms.InputTag("patPFMetT1MuEGClean"),
            rawVariation    = cms.InputTag("patPFMetRawMuEGClean"),
            t1Uncertainties = cms.InputTag("patPFMetT1%sMuEGClean")
        )
        del process.slimmedMETsMuEGClean.caloMET
        
        process.egcorrMET = cms.Sequence(
		    process.cleanedPhotonsMuEGClean+process.cleanedCorPhotonsMuEGClean+
		    process.matchedPhotonsMuEGClean + process.matchedElectronsMuEGClean +
		    process.corMETPhotonMuEGClean+process.corMETElectronMuEGClean+
		    process.patPFMetT1MuEGClean+process.patPFMetRawMuEGClean+
		    process.patPFMetT1SmearMuEGClean+process.patPFMetT1TxyMuEGClean+
		    process.patPFMetTxyMuEGClean+process.patPFMetT1JetEnUpMuEGClean+
		    process.patPFMetT1JetResUpMuEGClean+process.patPFMetT1SmearJetResUpMuEGClean+
		    process.patPFMetT1ElectronEnUpMuEGClean+process.patPFMetT1PhotonEnUpMuEGClean+
		    process.patPFMetT1MuonEnUpMuEGClean+process.patPFMetT1TauEnUpMuEGClean+
		    process.patPFMetT1UnclusteredEnUpMuEGClean+process.patPFMetT1JetEnDownMuEGClean+
		    process.patPFMetT1JetResDownMuEGClean+process.patPFMetT1SmearJetResDownMuEGClean+
		    process.patPFMetT1ElectronEnDownMuEGClean+process.patPFMetT1PhotonEnDownMuEGClean+
		    process.patPFMetT1MuonEnDownMuEGClean+process.patPFMetT1TauEnDownMuEGClean+
		    process.patPFMetT1UnclusteredEnDownMuEGClean+process.slimmedMETsMuEGClean)

        # overwrite output collections
        METCollection = cms.InputTag("slimmedMETsMuEGClean", "", process.name_())


### additional MET filters ###
process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.BadPFMuonFilter.muons = muonCollection
process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.BadChargedCandidateFilter.muons = muonCollection
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.load("RecoMET.METFilters.badGlobalMuonTaggersMiniAOD_cff")
process.badGlobalMuonTaggerMAOD.muons         = muonCollection
process.badGlobalMuonTaggerMAOD.taggingMode   = cms.bool(True)
process.cloneGlobalMuonTaggerMAOD.muons       = muonCollection
process.cloneGlobalMuonTaggerMAOD.taggingMode = cms.bool(True)

###############################################

### update PUJetID

if options.updatePUJetId:
    process.load("RecoJets.JetProducers.PileupJetID_cfi")
    process.pileupJetIdUpdated = process.pileupJetId.clone(
        jets             = jetCollection,
        vertexes         = cms.InputTag("offlineSlimmedPrimaryVertices"),
        inputIsCorrected = cms.bool(True),
        applyJec         = cms.bool(True)
    )


    process.load("PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff")
    process.updatedPatJets.jetSource         = jetCollection
    process.updatedPatJets.addJetCorrFactors = cms.bool(False)
    process.updatedPatJets.userData.userFloats.src.append("pileupJetIdUpdated:fullDiscriminant")
    process.updatedPatJets.userData.userInts.src.append("pileupJetIdUpdated:fullId")

    # overwrite output collections
    jetCollection = cms.InputTag("updatedPatJets", "", process.name_())


##############################################

# jet selection
process.load("BoostedTTH.Producers.SelectedJetProducer_cfi")
# selection of corrected and smeared jets -- one producer for every jet systematic that selects two collections (regular and loose jets) each
# selection of the nominal jets
process.SelectedJetProducerAK4=process.SelectedJetProducer.clone(jets='patSmearedJetsAK4',
                                                                applyCorrection=False,
                                                                ptMins=[75,75],
                                                                etaMaxs=[2.4,2.4],
                                                                collectionNames=["selectedJetsAK4Loose","selectedJetsAK4"],
                                                                systematics=[""],
                                                                PUJetIDMins=["loose","loose"],
                                                                JetID="none",
                                                                )

process.SelectedJetProducerAK4PUPPI=process.SelectedJetProducer.clone(jets='patSmearedJetsAK4PUPPI',
                                                                applyCorrection=False,
                                                                ptMins=[75],
                                                                etaMaxs=[2.4],
                                                                collectionNames=["selectedJetsAK4PUPPI"],
                                                                systematics=[""],
                                                                PUJetIDMins=["loose"],
                                                                JetID="none",
                                                                )

process.SelectedJetProducerAK8CHSSoftDrop=process.SelectedJetProducer.clone(jets='patSmearedJetsAK8CHSSoftDrop',
                                                                applyCorrection=False,
                                                                ptMins=[150],
                                                                etaMaxs=[2.4],
                                                                collectionNames=["selectedJetsAK8CHSSoftDrop"],
                                                                systematics=[""],
                                                                PUJetIDMins=["loose"],
                                                                JetID="none",
                                                                )
process.SelectedJetProducerAK8CHSPruning=process.SelectedJetProducer.clone(jets='patSmearedJetsAK8CHSPruning',
                                                                applyCorrection=False,
                                                                ptMins=[150],
                                                                etaMaxs=[2.4],
                                                                collectionNames=["selectedJetsAK8CHSPruning"],
                                                                systematics=[""],
                                                                PUJetIDMins=["loose"],
                                                                JetID="none",
                                                                )
process.SelectedJetProducerAK8PUPPISoftDrop=process.SelectedJetProducer.clone(jets='patSmearedJetsAK8PUPPISoftDrop',
                                                                applyCorrection=False,
                                                                ptMins=[150],
                                                                etaMaxs=[2.4],
                                                                collectionNames=["selectedJetsAK8PUPPISoftDrop"],
                                                                systematics=[""],
                                                                PUJetIDMins=["loose"],
                                                                JetID="none",
                                                                )
process.SelectedJetProducerAK8PUPPIPruning=process.SelectedJetProducer.clone(jets='patSmearedJetsAK8PUPPIPruning',
                                                                applyCorrection=False,
                                                                ptMins=[150],
                                                                etaMaxs=[2.4],
                                                                collectionNames=["selectedJetsAK8PUPPIPruning"],
                                                                systematics=[""],
                                                                PUJetIDMins=["loose"],
                                                                JetID="none",
                                                                )


# selection of the systematically shifted jets
for syst in systs:
    setattr(process,'SelectedJetProducerAK4'+syst,process.SelectedJetProducerAK4.clone(jets='patSmearedJetsAK4'+syst,collectionNames=[n+syst for n in list(process.SelectedJetProducerAK4.collectionNames)]))
for syst in systs:
    setattr(process,'SelectedJetProducerAK4PUPPI'+syst,process.SelectedJetProducerAK4PUPPI.clone(jets='patSmearedJetsAK4PUPPI'+syst,collectionNames=[n+syst for n in list(process.SelectedJetProducerAK4PUPPI.collectionNames)]))

# selection of the systematically shifted jets
for syst in systs:
    setattr(process,'SelectedJetProducerAK8CHSSoftDrop'+syst,process.SelectedJetProducerAK8CHSSoftDrop.clone(jets='patSmearedJetsAK8CHSSoftDrop'+syst,collectionNames=[n+syst for n in list(process.SelectedJetProducerAK8CHSSoftDrop.collectionNames)]))
for syst in systs:
    setattr(process,'SelectedJetProducerAK8CHSPruning'+syst,process.SelectedJetProducerAK8CHSPruning.clone(jets='patSmearedJetsAK8CHSPruning'+syst,collectionNames=[n+syst for n in list(process.SelectedJetProducerAK8CHSPruning.collectionNames)]))
for syst in systs:
    setattr(process,'SelectedJetProducerAK8PUPPISoftDrop'+syst,process.SelectedJetProducerAK8PUPPISoftDrop.clone(jets='patSmearedJetsAK8PUPPISoftDrop'+syst,collectionNames=[n+syst for n in list(process.SelectedJetProducerAK8PUPPISoftDrop.collectionNames)]))
for syst in systs:
    setattr(process,'SelectedJetProducerAK8PUPPIPruning'+syst,process.SelectedJetProducerAK8PUPPIPruning.clone(jets='patSmearedJetsAK8PUPPIPruning'+syst,collectionNames=[n+syst for n in list(process.SelectedJetProducerAK8PUPPIPruning.collectionNames)]))

## selection of the systematically shifted jets
#for syst in systs:
    #setattr(process,'SelectedJetProducerAK12'+syst,process.SelectedJetProducerAK12.clone(jets='patSmearedJetsAK12'+syst,collectionNames=[n+syst for n in list(process.SelectedJetProducerAK12.collectionNames)]))

## selection of the systematically shifted jets
#for syst in systs:
    #setattr(process,'SelectedJetProducerAK15'+syst,process.SelectedJetProducerAK15.clone(jets='patSmearedJetsAK15'+syst,collectionNames=[n+syst for n in list(process.SelectedJetProducerAK15.collectionNames)]))









# correction of  miniAOD jets -- one producer creates a jet collection for nominal JES and every JES systematic
process.CorrectedJetProducerAK4=process.SelectedJetProducer.clone(jets=jetCollection, 
                                                               ptMins=[-1.],
                                                               etaMaxs=[999.],
                                                               collectionNames=["correctedJetsAK4"],#
                                                               applyCorrection=True,
                                                               systematics=[""]+systsJES,
                                                               JetID="loose",
                                                               PUJetIDMins=["none"],
                                                               corrLable="ak4PFchsL1L2L3",
                                                               )
process.CorrectedJetProducerAK4PUPPI=process.SelectedJetProducer.clone(jets=jetCollectionAK4PUPPI, 
                                                               ptMins=[-1.],
                                                               etaMaxs=[999.],
                                                               collectionNames=["correctedJetsAK4PUPPI"],#
                                                               applyCorrection=True,
                                                               systematics=[""]+systsJES,
                                                               JetID="loose",
                                                               PUJetIDMins=["none"],
                                                               corrLable="ak4PFPuppiL1L2L3",
                                                               )
# correction of  JETTOOLBOX jets -- one producer creates a jet collection for nominal JES and every JES systematic
process.CorrectedJetProducerAK8CHSSoftDrop=process.SelectedJetProducer.clone(jets=jetCollectionAK8CHSSoftDrop, 
                                                               ptMins=[-1.],
                                                               etaMaxs=[999.],
                                                               collectionNames=["correctedJetsAK8CHSSoftDrop"],
                                                               applyCorrection=True,
                                                               systematics=[""]+systsJES,
                                                               JetID="loose",
                                                               PUJetIDMins=["none"],
                                                               corrLable="ak8PFchsL1L2L3",
                                                               )
process.CorrectedJetProducerAK8CHSPruning=process.SelectedJetProducer.clone(jets=jetCollectionAK8CHSPruning, 
                                                               ptMins=[-1.],
                                                               etaMaxs=[999.],
                                                               collectionNames=["correctedJetsAK8CHSPruning"],
                                                               applyCorrection=True,
                                                               systematics=[""]+systsJES,
                                                               JetID="loose",
                                                               PUJetIDMins=["none"],
                                                               corrLable="ak8PFchsL1L2L3",
                                                               )
process.CorrectedJetProducerAK8PUPPISoftDrop=process.SelectedJetProducer.clone(jets=jetCollectionAK8PUPPISoftDrop, 
                                                               ptMins=[-1.],
                                                               etaMaxs=[999.],
                                                               collectionNames=["correctedJetsAK8PUPPISoftDrop"],
                                                               applyCorrection=True,
                                                               systematics=[""]+systsJES,
                                                               JetID="loose",
                                                               PUJetIDMins=["none"],
                                                               corrLable="ak8PFPuppiL1L2L3",
                                                               )
process.CorrectedJetProducerAK8PUPPIPruning=process.SelectedJetProducer.clone(jets=jetCollectionAK8PUPPIPruning, 
                                                               ptMins=[-1.],
                                                               etaMaxs=[999.],
                                                               collectionNames=["correctedJetsAK8PUPPIPruning"],
                                                               applyCorrection=True,
                                                               systematics=[""]+systsJES,
                                                               JetID="loose",
                                                               PUJetIDMins=["none"],
                                                               corrLable="ak8PFPuppiL1L2L3",
                                                               )

## correction of  JETTOOLBOX jets -- one producer creates a jet collection for nominal JES and every JES systematic
#process.CorrectedJetProducerAK12=process.SelectedJetProducer.clone(jets=jetCollectionAK12, 
                                                               #ptMins=[-1.],
                                                               #etaMaxs=[999.],
                                                               #collectionNames=["correctedJetsAK12"],
                                                               #applyCorrection=True,
                                                               #systematics=[""]+systsJES,
                                                               #JetID="loose",
                                                               #PUJetIDMins=["none"],
                                                               #corrLable="ak8PFchsL1L2L3",
                                                               #)

## correction of  JETTOOLBOX jets -- one producer creates a jet collection for nominal JES and every JES systematic
#process.CorrectedJetProducerAK15=process.SelectedJetProducer.clone(jets=jetCollectionAK15, 
                                                               #ptMins=[-1.],
                                                               #etaMaxs=[999.],
                                                               #collectionNames=["correctedJetsAK15"],
                                                               #applyCorrection=True,
                                                               #systematics=[""]+systsJES,
                                                               #JetID="loose",
                                                               #PUJetIDMins=["none"],
                                                               #corrLable="ak8PFchsL1L2L3",
                                                               #)



# smearing of corrected jets -- producers that create the nominal and up/down JER correction
# jer shift of nominal sample
process.patSmearedJetsAK4 = cms.EDProducer("SmearedPATJetProducer",
    src = cms.InputTag("CorrectedJetProducerAK4:correctedJetsAK4"),
    enabled = cms.bool(True),  # If False, no smearing is performed
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching = cms.bool(False),  # If True, always skip gen jet matching and smear jet with a random gaussian
#    algopt = cms.string('AK4PFchs_pt'),
#    algo = cms.string('AK4PFchs'),
    genJets = cms.InputTag("slimmedGenJets"),
    dRMax = cms.double(0.2),  # = cone size (0.4) / 2
    dPtMaxFactor = cms.double(3),  # dPt < 3 * resolution
    variation = cms.int32(0),  # systematic +1 0 -1 sigma
    debug = cms.untracked.bool(False),
    resolutionFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt"),
    scaleFactorFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_SF_AK4PFchs.txt"),
)

process.patSmearedJetsAK4PUPPI = cms.EDProducer("SmearedPATJetProducer",
    src = cms.InputTag("CorrectedJetProducerAK4PUPPI:correctedJetsAK4PUPPI"),
    enabled = cms.bool(True),  # If False, no smearing is performed
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching = cms.bool(False),  # If True, always skip gen jet matching and smear jet with a random gaussian
#    algopt = cms.string('AK4PFchs_pt'),
#    algo = cms.string('AK4PFchs'),
    genJets = cms.InputTag("slimmedGenJets"),
    dRMax = cms.double(0.2),  # = cone size (0.4) / 2
    dPtMaxFactor = cms.double(3),  # dPt < 3 * resolution
    variation = cms.int32(0),  # systematic +1 0 -1 sigma
    debug = cms.untracked.bool(False),
    resolutionFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_PtResolution_AK4PFPuppi.txt"),
    scaleFactorFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_SF_AK4PFPuppi.txt"),
)

process.patSmearedJetsAK8CHSSoftDrop = cms.EDProducer("SmearedPATJetProducer",
    src = cms.InputTag("CorrectedJetProducerAK8CHSSoftDrop:correctedJetsAK8CHSSoftDrop"),
    enabled = cms.bool(True),  # If False, no smearing is performed
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching = cms.bool(False),  # If True, always skip gen jet matching and smear jet with a random gaussian
#    algopt = cms.string('AK4PFchs_pt'),
#    algo = cms.string('AK4PFchs'),
    genJets = cms.InputTag("slimmedGenJets"),
    #dRMax = cms.double(0.2),  # = cone size (0.4) / 2
    dRMax = cms.double(0.4),  # = cone size (0.4) / 2
    dPtMaxFactor = cms.double(3),  # dPt < 3 * resolution
    variation = cms.int32(0),  # systematic +1 0 -1 sigma
    debug = cms.untracked.bool(False),
    resolutionFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_PtResolution_AK8PFchs.txt"),
    scaleFactorFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_SF_AK8PFchs.txt"),
)
process.patSmearedJetsAK8CHSPruning = cms.EDProducer("SmearedPATJetProducer",
    src = cms.InputTag("CorrectedJetProducerAK8CHSPruning:correctedJetsAK8CHSPruning"),
    enabled = cms.bool(True),  # If False, no smearing is performed
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching = cms.bool(False),  # If True, always skip gen jet matching and smear jet with a random gaussian
#    algopt = cms.string('AK4PFchs_pt'),
#    algo = cms.string('AK4PFchs'),
    genJets = cms.InputTag("slimmedGenJets"),
    #dRMax = cms.double(0.2),  # = cone size (0.4) / 2
    dRMax = cms.double(0.4),  # = cone size (0.4) / 2
    dPtMaxFactor = cms.double(3),  # dPt < 3 * resolution
    variation = cms.int32(0),  # systematic +1 0 -1 sigma
    debug = cms.untracked.bool(False),
    resolutionFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_PtResolution_AK8PFchs.txt"),
    scaleFactorFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_SF_AK8PFchs.txt"),
)
process.patSmearedJetsAK8PUPPISoftDrop = cms.EDProducer("SmearedPATJetProducer",
    src = cms.InputTag("CorrectedJetProducerAK8PUPPISoftDrop:correctedJetsAK8PUPPISoftDrop"),
    enabled = cms.bool(True),  # If False, no smearing is performed
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching = cms.bool(False),  # If True, always skip gen jet matching and smear jet with a random gaussian
#    algopt = cms.string('AK4PFchs_pt'),
#    algo = cms.string('AK4PFchs'),
    genJets = cms.InputTag("slimmedGenJets"),
    #dRMax = cms.double(0.2),  # = cone size (0.4) / 2
    dRMax = cms.double(0.4),  # = cone size (0.4) / 2
    dPtMaxFactor = cms.double(3),  # dPt < 3 * resolution
    variation = cms.int32(0),  # systematic +1 0 -1 sigma
    debug = cms.untracked.bool(False),
    resolutionFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_PtResolution_AK8PFPuppi.txt"),
    scaleFactorFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_SF_AK8PFPuppi.txt"),
)
process.patSmearedJetsAK8PUPPIPruning = cms.EDProducer("SmearedPATJetProducer",
    src = cms.InputTag("CorrectedJetProducerAK8PUPPIPruning:correctedJetsAK8PUPPIPruning"),
    enabled = cms.bool(True),  # If False, no smearing is performed
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching = cms.bool(False),  # If True, always skip gen jet matching and smear jet with a random gaussian
#    algopt = cms.string('AK4PFchs_pt'),
#    algo = cms.string('AK4PFchs'),
    genJets = cms.InputTag("slimmedGenJets"),
    #dRMax = cms.double(0.2),  # = cone size (0.4) / 2
    dRMax = cms.double(0.4),  # = cone size (0.4) / 2
    dPtMaxFactor = cms.double(3),  # dPt < 3 * resolution
    variation = cms.int32(0),  # systematic +1 0 -1 sigma
    debug = cms.untracked.bool(False),
    resolutionFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_PtResolution_AK8PFPuppi.txt"),
    scaleFactorFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_SF_AK8PFPuppi.txt"),
)
#process.patSmearedJetsAK12 = cms.EDProducer("SmearedPATJetProducer",
    #src = cms.InputTag("CorrectedJetProducerAK12:correctedJetsAK12"),
    #enabled = cms.bool(True),  # If False, no smearing is performed
    #rho = cms.InputTag("fixedGridRhoFastjetAll"),
    #skipGenMatching = cms.bool(False),  # If True, always skip gen jet matching and smear jet with a random gaussian
##    algopt = cms.string('AK4PFchs_pt'),
##    algo = cms.string('AK4PFchs'),
    #genJets = cms.InputTag("slimmedGenJets"),
    ##dRMax = cms.double(0.2),  # = cone size (0.4) / 2
    #dRMax = cms.double(0.6),  # = cone size (0.4) / 2
    #dPtMaxFactor = cms.double(3),  # dPt < 3 * resolution
    #variation = cms.int32(0),  # systematic +1 0 -1 sigma
    #debug = cms.untracked.bool(False),
    #resolutionFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_PtResolution_AK8PFchs.txt"),
    #scaleFactorFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_SF_AK8PFchs.txt"),
#)

#process.patSmearedJetsAK15 = cms.EDProducer("SmearedPATJetProducer",
    #src = cms.InputTag("CorrectedJetProducerAK15:correctedJetsAK15"),
    #enabled = cms.bool(True),  # If False, no smearing is performed
    #rho = cms.InputTag("fixedGridRhoFastjetAll"),
    #skipGenMatching = cms.bool(False),  # If True, always skip gen jet matching and smear jet with a random gaussian
##    algopt = cms.string('AK4PFchs_pt'),
##    algo = cms.string('AK4PFchs'),
    #genJets = cms.InputTag("slimmedGenJets"),
    ##dRMax = cms.double(0.2),  # = cone size (0.4) / 2
    #dRMax = cms.double(0.75),  # = cone size (0.4) / 2
    #dPtMaxFactor = cms.double(3),  # dPt < 3 * resolution
    #variation = cms.int32(0),  # systematic +1 0 -1 sigma
    #debug = cms.untracked.bool(False),
    #resolutionFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_PtResolution_AK8PFchs.txt"),
    #scaleFactorFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_SF_AK8PFchs.txt"),
#)










# up/down jer shift of nominal sample and nominal jer shift of jes systematic samples
for s in systsJER:
    v=0
    if s=='JERup': v=+1
    elif s=='JERdown': v=-1
    setattr(process,'patSmearedJetsAK4'+s,process.patSmearedJetsAK4.clone(variation=v,src=cms.InputTag("CorrectedJetProducerAK4:correctedJetsAK4")))
    setattr(process,'patSmearedJetsAK4PUPPI'+s,process.patSmearedJetsAK4PUPPI.clone(variation=v,src=cms.InputTag("CorrectedJetProducerAK4PUPPI:correctedJetsAK4PUPPI")))
    setattr(process,'patSmearedJetsAK8CHSSoftDrop'+s,process.patSmearedJetsAK8CHSSoftDrop.clone(variation=v,src=cms.InputTag("CorrectedJetProducerAK8CHSSoftDrop:correctedJetsAK8CHSSoftDrop")))
    setattr(process,'patSmearedJetsAK8CHSPruning'+s,process.patSmearedJetsAK8CHSPruning.clone(variation=v,src=cms.InputTag("CorrectedJetProducerAK8CHSPruning:correctedJetsAK8CHSPruning")))
    setattr(process,'patSmearedJetsAK8PUPPISoftDrop'+s,process.patSmearedJetsAK8PUPPISoftDrop.clone(variation=v,src=cms.InputTag("CorrectedJetProducerAK8PUPPISoftDrop:correctedJetsAK8PUPPISoftDrop")))
    setattr(process,'patSmearedJetsAK8PUPPIPruning'+s,process.patSmearedJetsAK8PUPPIPruning.clone(variation=v,src=cms.InputTag("CorrectedJetProducerAK8PUPPIPruning:correctedJetsAK8PUPPIPruning")))
    #setattr(process,'patSmearedJetsAK12'+s,process.patSmearedJetsAK12.clone(variation=v,src=cms.InputTag("CorrectedJetProducerAK12:correctedJetsAK12")))
    #setattr(process,'patSmearedJetsAK15'+s,process.patSmearedJetsAK15.clone(variation=v,src=cms.InputTag("CorrectedJetProducerAK15:correctedJetsAK15")))
for s in systsJES:
    setattr(process,'patSmearedJetsAK4'+s,process.patSmearedJetsAK4.clone(variation=0,src=cms.InputTag("CorrectedJetProducerAK4:correctedJetsAK4"+s)))
    setattr(process,'patSmearedJetsAK4PUPPI'+s,process.patSmearedJetsAK4PUPPI.clone(variation=0,src=cms.InputTag("CorrectedJetProducerAK4PUPPI:correctedJetsAK4PUPPI"+s)))
    setattr(process,'patSmearedJetsAK8CHSSoftDrop'+s,process.patSmearedJetsAK8CHSSoftDrop.clone(variation=0,src=cms.InputTag("CorrectedJetProducerAK8CHSSoftDrop:correctedJetsAK8CHSSoftDrop"+s)))
    setattr(process,'patSmearedJetsAK8CHSPruning'+s,process.patSmearedJetsAK8CHSPruning.clone(variation=0,src=cms.InputTag("CorrectedJetProducerAK8CHSPruning:correctedJetsAK8CHSPruning"+s)))
    setattr(process,'patSmearedJetsAK8PUPPISoftDrop'+s,process.patSmearedJetsAK8PUPPISoftDrop.clone(variation=0,src=cms.InputTag("CorrectedJetProducerAK8PUPPISoftDrop:correctedJetsAK8PUPPISoftDrop"+s)))
    setattr(process,'patSmearedJetsAK8PUPPIPruning'+s,process.patSmearedJetsAK8PUPPIPruning.clone(variation=0,src=cms.InputTag("CorrectedJetProducerAK8PUPPIPruning:correctedJetsAK8PUPPIPruning"+s)))
    #setattr(process,'patSmearedJetsAK12'+s,process.patSmearedJetsAK12.clone(variation=0,src=cms.InputTag("CorrectedJetProducerAK12:correctedJetsAK12"+s)))
    #setattr(process,'patSmearedJetsAK15'+s,process.patSmearedJetsAK15.clone(variation=0,src=cms.InputTag("CorrectedJetProducerAK15:correctedJetsAK15"+s)))

###############################################


### correct MET manually ###
process.load("BoostedTTH.Producers.CorrectedMETproducer_cfi")
process.CorrectedMETproducer.isData=options.isData
#process.CorrectedMETproducer.oldJets=cms.InputTag("slimmedJets", "", "PAT")
#process.CorrectedMETproducer.newJets=cms.InputTag("slimmedJets", "", "PAT")
#process.CorrectedMETproducer.oldElectrons=cms.InputTag("slimmedElectrons", "", "PAT")
#process.CorrectedMETproducer.newElectrons=cms.InputTag("slimmedElectrons", "", "PAT")
#process.CorrectedMETproducer.oldMuons=cms.InputTag("SelectedMuonProducerUncorr:selectedMuonsUncorr")
#process.CorrectedMETproducer.newMuons=cms.InputTag("SelectedMuonProducer:selectedMuons")
process.CorrectedMETproducer.mets=METCollection

# load and run the boosted analyzer
if options.isData:
    process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_data_cfi")
    process.BoostedAnalyzer.filterBits=cms.InputTag("TriggerResults::RECO")
    process.BoostedAnalyzer.channel=options.LeptonChannel

else:
    process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
    process.BoostedAnalyzer.channel=options.LeptonChannel

    if not options.isBoostedMiniAOD:
        # Supplies PDG ID to real name resolution of MC particles
        process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
        # Needed to determine tt+x category -- is usually run when producing boosted jets in miniAOD
        process.load("BoostedTTH.Producers.genHadronMatching_cfi")

# which systematic variations to store in the ntuple?
variations = systs
if writeNominal:
    variations.insert(0,"") # also store nominal case
process.BoostedAnalyzer.selectedJets=[cms.InputTag("SelectedJetProducerAK4"+s+":selectedJetsAK4"+s) for s in variations]
process.BoostedAnalyzer.selectedJetsLoose=[cms.InputTag("SelectedJetProducerAK4"+s+":selectedJetsAK4Loose"+s) for s in variations]

process.BoostedAnalyzer.selectedJetsAK4PUPPI=[cms.InputTag("SelectedJetProducerAK4PUPPI"+s+":selectedJetsAK4PUPPI"+s) for s in variations]
process.BoostedAnalyzer.selectedJetsAK8CHSSoftDrop=[cms.InputTag("SelectedJetProducerAK8CHSSoftDrop"+s+":selectedJetsAK8CHSSoftDrop"+s) for s in variations]
process.BoostedAnalyzer.selectedJetsAK8CHSPruning=[cms.InputTag("SelectedJetProducerAK8CHSPruning"+s+":selectedJetsAK8CHSPruning"+s) for s in variations]
process.BoostedAnalyzer.selectedJetsAK8PUPPISoftDrop=[cms.InputTag("SelectedJetProducerAK8PUPPISoftDrop"+s+":selectedJetsAK8PUPPISoftDrop"+s) for s in variations]
process.BoostedAnalyzer.selectedJetsAK8PUPPIPruning=[cms.InputTag("SelectedJetProducerAK8PUPPIPruning"+s+":selectedJetsAK8PUPPIPruning"+s) for s in variations]
#process.BoostedAnalyzer.selectedJetsAK12=[cms.InputTag("SelectedJetProducerAK12"+s+":selectedJetsAK12"+s) for s in variations]
#process.BoostedAnalyzer.selectedJetsAK15=[cms.InputTag("SelectedJetProducerAK15"+s+":selectedJetsAK15"+s) for s in variations]
process.BoostedAnalyzer.correctedMETs=[cms.InputTag("CorrectedMETproducer:correctedMET")]*(len(variations))

if options.isBoostedMiniAOD:
    process.BoostedAnalyzer.useFatJets=True
else:
    process.BoostedAnalyzer.useFatJets=False

process.BoostedAnalyzer.outfileName=options.outName
if not options.isData:
    process.BoostedAnalyzer.eventWeight = options.weight

process.BoostedAnalyzer.systematics=variations
process.BoostedAnalyzer.generatorName=options.generatorName

if options.isData and options.useJson:
    import FWCore.PythonUtilities.LumiList as LumiList
    process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt').getVLuminosityBlockRange()

if options.isData:
  process.BoostedAnalyzer.dataset=cms.string(options.dataset)



###############################
process.BoostedAnalyzer.minJets = [3]
process.BoostedAnalyzer.maxJets = [-1]
process.BoostedAnalyzer.minTags = [0]
process.BoostedAnalyzer.maxTags = [-1]
################################



process.BoostedAnalyzer.selectionNames = [
"FilterSelection",
"VertexSelection",
"LeptonSelection",
"JetTagSelection"
]
if options.additionalSelection!="NONE":
  process.BoostedAnalyzer.selectionNames+=cms.vstring(options.additionalSelection)

if options.isData:
  process.BoostedAnalyzer.processorNames=cms.vstring(
  "WeightProcessor",
  "essentialBasicVarProcessor",
  "TriggerVarProcessor",
  "ZPrimeToTPrimeAllHadProcessor",
  )

else:
  process.BoostedAnalyzer.processorNames=cms.vstring(
  "WeightProcessor",
  "essentialBasicVarProcessor",
  "TriggerVarProcessor",
  "ZPrimeToTPrimeAllHadProcessor",
  )

printContent=False
if printContent:
    process.content = cms.EDAnalyzer("EventContentAnalyzer")

if options.dumpSyncExe:
    process.BoostedAnalyzer.processorNames = []
    process.BoostedAnalyzer.selectionNames = []
    process.BoostedAnalyzer.dumpSyncExe=True
    process.BoostedAnalyzer.dumpExtended=False
    process.BoostedAnalyzer.dumpAlwaysEvents=[
        #3222838,
        #3211421,
        #527273,
        #3163883,
        #2865714,
        #2688365,
        #2786936,
        ]

if options.ProduceMemNtuples==True:
    process.BoostedAnalyzer.memNtuples=True
    process.BoostedAnalyzer.processorNames=cms.vstring("SlimmedNtuples")

##### DEFINE PATH ##########
process.p = cms.Path()
if options.deterministicSeeds:
    process.p*=process.deterministicSeeds
process.p *= process.BadPFMuonFilter*process.BadChargedCandidateFilter*process.badGlobalMuonTaggerMAOD*process.cloneGlobalMuonTaggerMAOD

#if options.calcBJetness:
    #process.p *= process.BJetness
#process.p*=process.regressionApplication#*process.SelectedMuonProducerUncorr
process.p*=process.regressionApplication*process.selectedElectrons*process.calibratedPatElectrons#*process.SelectedMuonProducerUncorr

if eleMVAid:
    process.p *= process.egmGsfElectronIDSequence
process.p*=process.SelectedElectronProducer*process.SelectedMuonProducer
if options.updatePUJetId:
	process.p*=process.pileupJetIdUpdated*process.updatedPatJets
process.p*=process.CorrectedJetProducerAK4
process.p*=process.CorrectedJetProducerAK4PUPPI
process.p*=process.CorrectedJetProducerAK8CHSSoftDrop
process.p*=process.CorrectedJetProducerAK8CHSPruning
process.p*=process.CorrectedJetProducerAK8PUPPISoftDrop
process.p*=process.CorrectedJetProducerAK8PUPPIPruning
#process.p*=process.CorrectedJetProducerAK12
#process.p*=process.CorrectedJetProducerAK15
# always produce (but not necessarily write to ntuple) nominal case as collections might be needed                                    
for s in [""]+systs:
    process.p *= getattr(process,'patSmearedJetsAK4'+s)
    process.p *= getattr(process,'SelectedJetProducerAK4'+s)
    process.p *= getattr(process,'patSmearedJetsAK4PUPPI'+s)
    process.p *= getattr(process,'SelectedJetProducerAK4PUPPI'+s)
    process.p *= getattr(process,'patSmearedJetsAK8CHSSoftDrop'+s)
    process.p *= getattr(process,'SelectedJetProducerAK8CHSSoftDrop'+s)
    process.p *= getattr(process,'patSmearedJetsAK8CHSPruning'+s)
    process.p *= getattr(process,'SelectedJetProducerAK8CHSPruning'+s)
    process.p *= getattr(process,'patSmearedJetsAK8PUPPISoftDrop'+s)
    process.p *= getattr(process,'SelectedJetProducerAK8PUPPISoftDrop'+s)
    process.p *= getattr(process,'patSmearedJetsAK8PUPPIPruning'+s)
    process.p *= getattr(process,'SelectedJetProducerAK8PUPPIPruning'+s)
    #process.p *= getattr(process,'patSmearedJetsAK12'+s)
    #process.p *= getattr(process,'SelectedJetProducerAK12'+s)
    #process.p *= getattr(process,'patSmearedJetsAK15'+s)
    #process.p *= getattr(process,'SelectedJetProducerAK15'+s)
#if options.recorrectMET:
    
process.p *= process.fullPatMetSequence
if options.isData:
	process.p *= process.egcorrMET

process.p *= process.CorrectedMETproducer

if not options.isData and not options.isBoostedMiniAOD:
    process.p *= process.genParticlesForJetsNoNu*process.ak4GenJetsCustom*process.selectedHadronsAndPartons*process.genJetFlavourInfos*process.matchGenBHadron*process.matchGenCHadron*process.categorizeGenTtbar

if printContent:
    process.p *= process.content

process.p *= process.BoostedAnalyzer
print "ENDE"