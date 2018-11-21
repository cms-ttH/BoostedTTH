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
options.register( "weight", 0.01, VarParsing.multiplicity.singleton, VarParsing.varType.float, "xs*lumi/(nPosEvents-nNegEvents)" )
options.register( "skipEvents", 0, VarParsing.multiplicity.singleton, VarParsing.varType.int, "Number of events to skip" )
options.register( "isData", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "is it data or MC?" )
options.register( "isBoostedMiniAOD", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "has the file been prepared with the BoostedProducer ('custom' MiniAOD)?" )
options.register( "generatorName", "POWHEG", VarParsing.multiplicity.singleton, VarParsing.varType.string, "'POWHEG','aMC', 'MadGraph' or 'pythia8'" )
options.register( "globalTag", "80X_mcRun2_asymptotic_2016_TrancheIV_v8", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )
options.register( "useJson",True, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "apply the json filter (on the grid there are better ways to do this)" )
options.register( "additionalSelection","NONE", VarParsing.multiplicity.singleton, VarParsing.varType.string, "addition Selection to use for this sample" )
datasets=['NA','mu','el','elel','elmu','mumu']
options.register( "dataset", "NA", VarParsing.multiplicity.singleton, VarParsing.varType.string, "flag to identify which dataset is used, can be "+','.join(datasets))
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
options.register("neventsToProcess",10000,VarParsing.multiplicity.singleton, VarParsing.varType.int, "Number of events which should be processed" )

options.parseArguments()

# re-set some defaults
if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 10000 # reset for testing

if not options.inputFiles:
    if options.isData:
        options.inputFiles=['file:///pnfs/desy.de/cms/tier2/store/user/mwassmer/MET/KIT_MonoJet_skims-Run2016B/180219_141209/0000/Skim_68.root']
        options.globalTag="80X_dataRun2_2016SeptRepro_v7"
        options.dataEra="2016B"
    else:
        options.inputFiles=['file:///pnfs/desy.de/cms/tier2/store/user/mwassmer/DYJetsToNuNu_PtZ-250To400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/KIT_MonoJet_skims/180217_120902/0000/Skim_1.root']

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
systsJEC=systsJER+systsJES

if options.isData:
    systsJER=[]
    systsJES=[]
    systsJEC=[]
    writeNominal=True

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
AK8jetCollection   = cms.InputTag("slimmedJetsAK8","","PAT")

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
    #process.deterministicSeeds.AK8jetCollection   = AK8jetCollection

    # overwrite output collections
    electronCollection = cms.InputTag("deterministicSeeds", "electronsWithSeed", process.name_())
    muonCollection     = cms.InputTag("deterministicSeeds", "muonsWithSeed", process.name_())
    tauCollection      = cms.InputTag("deterministicSeeds", "tausWithSeed", process.name_())
    photonCollection   = cms.InputTag("deterministicSeeds", "photonsWithSeed", process.name_())
    jetCollection      = cms.InputTag("deterministicSeeds", "jetsWithSeed", process.name_())
    METCollection      = cms.InputTag("deterministicSeeds", "METsWithSeed", process.name_())
    #AK8jetCollection   = cms.InputTag("deterministicSeeds", "AK8jetsWithSeed", process.name_())

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
eleMVAid=False
if eleMVAid:
    from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
    dataFormat = DataFormat.MiniAOD
    switchOnVIDElectronIdProducer(process, dataFormat)
# Spring 16 MVA ID 
    my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff']
    for idmod in my_id_modules:
        setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)
        
### Photon ID ####
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDPhotonIdProducer(process, dataFormat)
my_id_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring16_V2p2_cff']
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)


# lepton selection
process.load('BoostedTTH.Producers.SelectedLeptonProducers_cfi')
process.SelectedElectronProducer.leptons=electronCollection
process.SelectedElectronProducer.ptMins=[10.,10.,40.]
process.SelectedElectronProducer.etaMaxs=[2.5,2.5,2.5]
process.SelectedElectronProducer.leptonIDs=["electron80XCutBasedV","electron80XCutBasedT","electron80XCutBasedT"]
#process.SelectedElectronProducer.leptonIDs=["none","none","none"]
process.SelectedElectronProducer.collectionNames=["selectedElectronsLoose","selectedElectronsDL","selectedElectrons"]
process.SelectedElectronProducer.isData=options.isData

process.SelectedMuonProducer.leptons=muonCollection
process.SelectedMuonProducer.ptMins=[10.,10.,20.]
process.SelectedMuonProducer.etaMaxs=[2.4,2.4,2.4]
process.SelectedMuonProducer.leptonIDs=["loose","tight","tight"]
#process.SelectedMuonProducer.leptonIDs=["none","none","none"]
process.SelectedMuonProducer.muonIsoConeSizes=["R04"]*3
process.SelectedMuonProducer.muonIsoCorrTypes=["deltaBeta"]*3
process.SelectedMuonProducer.collectionNames=["selectedMuonsLoose","selectedMuonsDL","selectedMuons"]
process.SelectedMuonProducer.useMuonRC=options.useMuonRC
process.SelectedMuonProducer.useDeterministicSeeds=options.deterministicSeeds
process.SelectedMuonProducer.isData=options.isData

process.SelectedTauProducer.leptons=tauCollection
process.SelectedTauProducer.ptMins=[18.,18.,18.]
process.SelectedTauProducer.etaMaxs=[2.3,2.3,2.3]
process.SelectedTauProducer.leptonIDs=["MVAveryloose","loose","medium"]
#process.SelectedTauProducer.leptonIDs=["none","none","none"]
process.SelectedTauProducer.collectionNames=["selectedTausLoose","selectedTausDL","selectedTaus"]
process.SelectedTauProducer.isData=options.isData

# photon selection
process.load('BoostedTTH.Producers.SelectedPhotonProducer_cfi')
process.SelectedPhotonProducer.photons = cms.InputTag("slimmedPhotons")
process.SelectedPhotonProducer.ptMins = [15.]
process.SelectedPhotonProducer.etaMaxs = [2.5]
process.SelectedPhotonProducer.collectionNames = ["selectedPhotonsLoose"]
process.SelectedPhotonProducer.IDs = ["loose"]


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
        #electronColl     = electronCollection.value(),
        #muonColl         = muonCollection.value(),
        #tauColl          = tauCollection.value(),
        #photonColl       = photonCollection.value(),
        #jetCollUnskimmed = jetCollection.value(),
        #recoMetFromPFCs  = True
    )

    # overwrite output collections
    METCollection = cms.InputTag("slimmedMETs", "", process.name_())
    
"""
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
"""

### additional MET filters ###
process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.BadPFMuonFilter.muons = muonCollection
process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadPFMuonFilter.taggingMode   = cms.bool(True)
process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.BadChargedCandidateFilter.muons = muonCollection
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadChargedCandidateFilter.taggingMode = cms.bool(True)
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
process.SelectedJetProducerAK4=process.SelectedJetProducer.clone()
# selection of corrected and smeared jets -- one producer for every jet systematic that selects two collections (regular and loose jets) each
# selection of the nominal jets
process.SelectedJetProducerAK4.jets=cms.InputTag('patSmearedJetsAK4',"",process.name_())
process.SelectedJetProducerAK4.applyCorrection=False
process.SelectedJetProducerAK4.ptMins=[20,30]
process.SelectedJetProducerAK4.etaMaxs=[2.4,2.4]
process.SelectedJetProducerAK4.collectionNames=["selectedJetsLooseAK4","selectedJetsAK4"]
process.SelectedJetProducerAK4.systematics=[""]
process.SelectedJetProducerAK4.PUJetIDMins=["none","none"]
process.SelectedJetProducerAK4.JetID="none"
# selection of the systematically shifted jets
for syst in systsJEC:
    setattr(process,'SelectedJetProducerAK4'+syst,process.SelectedJetProducerAK4.clone(jets='patSmearedJetsAK4'+syst,collectionNames=[n+syst for n in list(process.SelectedJetProducerAK4.collectionNames)]))

# correction of  miniAOD jets -- one producer creates a jet collection for nominal JES and every JES systematic
process.CorrectedJetProducerAK4=process.SelectedJetProducerAK4.clone(jets=jetCollection, 
                                                               ptMins=[-1.],
                                                               etaMaxs=[999.],
                                                               collectionNames=["correctedJetsAK4"],
                                                               applyCorrection=True,
                                                               systematics=[""]+systsJES,
                                                               JetID="loose",
                                                               PUJetIDMins=["none"])

process.CorrectedJetProducerAK8=process.CorrectedJetProducerAK4.clone(jets=AK8jetCollection, 
                                                               ptMins=[-1.],
                                                               etaMaxs=[999.],
                                                               collectionNames=["correctedJetsAK8"],
                                                               applyCorrection=True,
                                                               systematics=[""]+systsJES,
                                                               JetID="loose",
                                                               PUJetIDMins=["none"],
                                                               miniAODGenJets=cms.InputTag("slimmedGenJetsAK8"),
                                                               leptonJetDr=0.8,
                                                               JetType="AK8PFchs"
                                                               )

process.SelectedJetProducerAK8=process.CorrectedJetProducerAK8.clone(jets=cms.InputTag('patSmearedJetsAK8',"",process.name_()),
                                                                     ptMins=[30.],
                                                                     etaMaxs=[2.4],
                                                                     collectionNames=["selectedJetsAK8"],
                                                                     applyCorrection=False,
                                                                     systematics=[""],
                                                                     JetID="none"
                                                                    )
for syst in systsJEC:
    setattr(process,'SelectedJetProducerAK8'+syst,process.SelectedJetProducerAK8.clone(jets='patSmearedJetsAK8'+syst,collectionNames=[n+syst for n in list(process.SelectedJetProducerAK8.collectionNames)]))

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
process.patSmearedJetsAK8 = cms.EDProducer("SmearedPATJetProducer",
    src = cms.InputTag("CorrectedJetProducerAK8:correctedJetsAK8"),
    enabled = cms.bool(True),  # If False, no smearing is performed
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching = cms.bool(False),  # If True, always skip gen jet matching and smear jet with a random gaussian
#    algopt = cms.string('AK4PFchs_pt'),
#    algo = cms.string('AK4PFchs'),
    genJets = cms.InputTag("slimmedGenJetsAK8"),
    dRMax = cms.double(0.4),  # = cone size (0.8) / 2
    dPtMaxFactor = cms.double(3),  # dPt < 3 * resolution
    variation = cms.int32(0),  # systematic +1 0 -1 sigma
    debug = cms.untracked.bool(False),
    resolutionFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_PtResolution_AK8PFchs.txt"),
    scaleFactorFile = cms.FileInPath("BoostedTTH/BoostedAnalyzer/data/jerfiles/Spring16_25nsV10_MC_SF_AK8PFchs.txt"),
)
# up/down jer shift of nominal sample and nominal jer shift of jes systematic samples
for s in systsJER:
    v=0
    if s=='JERup': v=+1
    elif s=='JERdown': v=-1
    setattr(process,'patSmearedJetsAK4'+s,process.patSmearedJetsAK4.clone(variation=v,src=cms.InputTag("CorrectedJetProducerAK4:correctedJetsAK4")))
    setattr(process,'patSmearedJetsAK8'+s,process.patSmearedJetsAK8.clone(variation=v,src=cms.InputTag("CorrectedJetProducerAK8:correctedJetsAK8")))
for s in systsJES:
    setattr(process,'patSmearedJetsAK4'+s,process.patSmearedJetsAK4.clone(variation=0,src=cms.InputTag("CorrectedJetProducerAK4:correctedJetsAK4"+s)))
    setattr(process,'patSmearedJetsAK8'+s,process.patSmearedJetsAK8.clone(variation=0,src=cms.InputTag("CorrectedJetProducerAK8:correctedJetsAK8"+s)))

###############################################


###############################################

# GenCollectionProducer
process.load("BoostedTTH.GenCollectionProducer.GenCollectionProducer_cfi")
process.GenCollectionProducer.collection_name=["CustomGenElectrons","CustomGenMuons","CustomGenTaus","CustomGenPhotons","CustomGenJets","CustomGenJetsLoose","CustomGenJetsAK8",]
process.GenCollectionProducer.collection_type=["Electron","Muon","Tau","Photon","AK4Jet","AK4Jet","AK8Jet"]
process.GenCollectionProducer.pt_min=[10.,10.,18.,15.,30.,20.,30.]
process.GenCollectionProducer.eta_max=[2.4,2.4,2.3,2.5,2.4,2.4,2.4]
process.GenCollectionProducer.doDeltaRCleaning=True

### correct MET manually ###
#process.load("BoostedTTH.Producers.CorrectedMETproducer_cfi")
#process.CorrectedMETproducer.isData=options.isData
#process.CorrectedMETproducer.oldJets=cms.InputTag("slimmedJets", "", "PAT")
#process.CorrectedMETproducer.newJets=cms.InputTag("slimmedJets", "", "PAT")
#process.CorrectedMETproducer.oldElectrons=cms.InputTag("slimmedElectrons", "", "PAT")
#process.CorrectedMETproducer.newElectrons=cms.InputTag("slimmedElectrons", "", "PAT")
#process.CorrectedMETproducer.oldMuons=cms.InputTag("SelectedMuonProducerUncorr:selectedMuonsUncorr")
#process.CorrectedMETproducer.newMuons=cms.InputTag("SelectedMuonProducer:selectedMuons")
#process.CorrectedMETproducer.mets=METCollection

# load and run the boosted analyzer
if options.isData:
    process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_data_cfi")
    process.BoostedAnalyzer.filterBits=cms.InputTag("TriggerResults::RECO")

else:
    process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")

    if not options.isBoostedMiniAOD:
        # Supplies PDG ID to real name resolution of MC particles
        process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
        # Needed to determine tt+x category -- is usually run when producing boosted jets in miniAOD
        process.load("BoostedTTH.Producers.genHadronMatching_cfi")

# which systematic variations to store in the ntuple?
variations = systsJEC
if writeNominal:
    variations.insert(0,"") # also store nominal case
process.BoostedAnalyzer.selectedJets=[cms.InputTag("SelectedJetProducerAK4"+s+":selectedJetsAK4"+s) for s in variations]
process.BoostedAnalyzer.selectedJetsLoose=[cms.InputTag("SelectedJetProducerAK4"+s+":selectedJetsLooseAK4"+s) for s in variations]
process.BoostedAnalyzer.AK8Jets=[cms.InputTag("SelectedJetProducerAK8"+s+":selectedJetsAK8"+s) for s in variations]
process.BoostedAnalyzer.correctedMETs=[METCollection]*(len(variations))

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

process.BoostedAnalyzer.selectionNames = [
"FilterSelection",
"VertexSelection",
#"LeptonSelection",
#"JetTagSelection",
"METSelection",
"MonoJetSelection",
"LeptonVetoSelection",
"BTagVetoSelection",
"PhotonVetoSelection",
"monoVselection"
]
if options.additionalSelection!="NONE":
  process.BoostedAnalyzer.selectionNames+=cms.vstring(options.additionalSelection)

if options.isData:
  process.BoostedAnalyzer.processorNames=cms.vstring(
  "WeightProcessor",
  "essentialBasicVarProcessor",
  #"essentialMVAVarProcessor",
  #"BDTVarProcessor",
  "TriggerVarProcessor",
  "DarkMatterProcessor"
  #"ReconstructionMEvarProcessor",
  #"TTBBStudienProcessor",
  )
else:
  process.BoostedAnalyzer.processorNames=cms.vstring(
  "WeightProcessor",
  #"essentialMCMatchVarProcessor",
  "essentialBasicVarProcessor",
  #"essentialMVAVarProcessor",
  #"BDTVarProcessor",
  "TriggerVarProcessor",
  #"ReconstructionMEvarProcessor",
  #"TTBBStudienProcessor"
  "DarkMatterProcessor",
  "MonoJetGenSelectionProcessor",
  "BosonWeightProcessor"
  )
if (process.BoostedAnalyzer.taggingSelection): process.BoostedAnalyzer.processorNames.append("SelectionTagProcessor")

process.BoostedAnalyzer.nevents_to_process = options.neventsToProcess

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
if eleMVAid:
    process.p *= process.egmGsfElectronIDSequence
process.p *= process.egmPhotonIDSequence*process.SelectedPhotonProducer
process.p*=process.regressionApplication*process.selectedElectrons*process.calibratedPatElectrons*process.SelectedElectronProducer*process.SelectedMuonProducer*process.SelectedTauProducer
if not options.isData:
    process.p*=process.GenCollectionProducer
if options.updatePUJetId:
	process.p*=process.pileupJetIdUpdated*process.updatedPatJets
process.p*=process.CorrectedJetProducerAK4
process.p*=process.CorrectedJetProducerAK8
# always produce (but not necessarily write to ntuple) nominal case as collections might be needed                                    
for s in [""]+systsJEC:
    process.p *= getattr(process,'patSmearedJetsAK4'+s)
    process.p *= getattr(process,'patSmearedJetsAK8'+s)
    process.p *= getattr(process,'SelectedJetProducerAK4'+s)
    process.p *= getattr(process,'SelectedJetProducerAK8'+s)


#if options.recorrectMET:
    
process.p *= process.fullPatMetSequence
#if options.isData:
	#process.p *= process.egcorrMET

#process.p *= process.CorrectedMETproducer

if printContent:
    process.p *= process.content

process.p *= process.BoostedAnalyzer
