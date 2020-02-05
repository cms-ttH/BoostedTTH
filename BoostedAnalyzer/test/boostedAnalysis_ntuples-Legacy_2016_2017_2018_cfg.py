import FWCore.ParameterSet.Config as cms
import sys
import os

# parse command-line arguments
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCommandLineParsing
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing("analysis")
# The following variables are already defined in VarParsing class:
# maxEvents: singleton, int; default = -1
# inputFiles: (comma separated, no spaces!) list, string: default empty
options.register(
    "outName",
    "testrun",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "name and path of the output files (without extension)",
)
options.register(
    "weight",
    0.01,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.float,
    "xs*lumi/(nPosEvents-nNegEvents)",
)
options.register(
    "skipEvents",
    0,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.int,
    "Number of events to skip",
)
options.register(
    "isData",
    False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "is it data or MC?",
)
options.register(
    "isBoostedMiniAOD",
    False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "has the file been prepared with the BoostedProducer ('custom' MiniAOD)?",
)
options.register(
    "generatorName",
    "POWHEG",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "'POWHEG','aMC', 'MadGraph' or 'pythia8'",
)
options.register(
    "globalTag",
    "94X_mc2017_realistic_v17",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "global tag",
)
options.register(
    "useJson",
    True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "apply the json filter (on the grid there are better ways to do this)",
)
options.register(
    "additionalSelection",
    "NONE",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "addition Selection to use for this sample",
)
datasets = ["NA", "mu", "el", "elel", "elmu", "mumu"]
options.register(
    "dataset",
    "NA",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "flag to identify which dataset is used, can be " + ",".join(datasets),
)
options.register(
    "dumpSyncExe",
    False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Dump textfiles for sync exe?",
)
options.register(
    "systematicVariations",
    "nominal",
    VarParsing.multiplicity.list,
    VarParsing.varType.string,
    "comma-separated list of systematic variations ('nominal' or systematics base name, up/down will be added)",
)
options.register(
    "deterministicSeeds",
    False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "create collections with deterministic seeds",
)
options.register(
    "electronRegression",
    "",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "'GT' or an absolute path to a sqlite file for electron energy regression",
)
options.register(
    "electronSmearing",
    "",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "correction type for electron energy smearing",
)
options.register(
    "useMuonRC",
    True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "use Rochester Correction for muons",
)
options.register(
    "recorrectMET",
    True,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "recorrect MET using latest JES and e/g corrections",
)
options.register(
    "dataEra",
    "2017",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "the era of the data taking period or mc campaign, e.g. '2016B' or '2017'",
)
options.register(
    "updatePUJetId",
    False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "update the PUJetId values",
)
options.register(
    "ProduceMemNtuples",
    False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "do you want to produce slimmed ntuples as input to mem code?",
)

options.parseArguments()

# re-set some defaults
if options.maxEvents is -1:  # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 1001  # reset for testing

if options.isData:
    if "2016" in options.dataEra:
        options.globalTag = "102X_dataRun2_v12"
    elif "2017" in options.dataEra:
        options.globalTag = "102X_dataRun2_v12"
    elif "2018" in options.dataEra:
        options.globalTag = "102X_dataRun2_v12"
    else:
        raise Exception(
            "dataEra "
            + options.dataEra
            + " not supported for this config: USE dataEra=2016/2017"
        )
elif not options.isData:
    if "2016" in options.dataEra:
        options.globalTag = "102X_mcRun2_asymptotic_v7"
    elif "2017" in options.dataEra:
        options.globalTag = "102X_mc2017_realistic_v7"
    elif "2018" in options.dataEra:
        options.globalTag = "102X_upgrade2018_realistic_v20"
    else:
        raise Exception(
            "dataEra "
            + options.dataEra
            + " not supported for this config: USE dataEra=2016/2017"
        )
else:
    raise Exception("Problem with isData option! This should never happen!")

if not options.inputFiles:
    if not options.isData:
        if "2016" in options.dataEra:
            options.inputFiles = [
                "file:///pnfs/desy.de/cms/tier2/store/user/mwassmer/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/KIT_Monotop_skims_2016_102X/191230_154242/0000/Skim_9.root"
            ]
        elif "2017" in options.dataEra:
            options.inputFiles = [
                "file:///pnfs/desy.de/cms/tier2/store/user/mwassmer/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/KIT_Monotop_skims_2017_102X_v1/191227_111420/0000/Skim_9.root"
            ]
        elif "2018" in options.dataEra:
            options.inputFiles = [
                "file:///pnfs/desy.de/cms/tier2/store/user/mwassmer/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/KIT_Monotop_skims_2018_102X_v2/191222_173237/0000/Skim_9.root"
            ]
    else:
        if "2016" in options.dataEra:  # CAREFUL: NO 2016 Data Skims ready yet
            # options.inputFiles=['file:///pnfs/desy.de/cms/tier2/store/user/swieland/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/KIT_tthbb_skims_MC_94X_LEG_2016/190328_111449/0000/Skim_1.root']
            options.inputFiles = [
                "file:///pnfs/desy.de/cms/tier2/store/user/mwassmer/MET/KIT_Monotop_skims_2016_102X_Run2016H/191229_144538/0000/Skim_1.root"
            ]
        elif "2017" in options.dataEra:
            options.inputFiles = [
                "file:///pnfs/desy.de/cms/tier2/store/user/mwassmer/MET/KIT_Monotop_skims_2017_102X_Run2017F_v1/191225_110902/0000/Skim_99.root"
            ]
        elif "2018" in options.dataEra:
            options.inputFiles = [
                "file:///pnfs/desy.de/cms/tier2/store/user/mwassmer/MET/KIT_Monotop_skims_2018_102X_Run2018D_v2/191218_152014/0000/Skim_99.root"
            ]


# checks for correct values and consistency
if "data" in options.globalTag.lower() and not options.isData:
    print ("\n\nConfig ERROR: GT contains seems to be for data but isData==False\n\n")
    sys.exit()
if "mc" in options.globalTag.lower() and options.isData:
    print ("\n\nConfig ERROR: GT contains seems to be for MC but isData==True\n\n")
    sys.exit()
if not options.inputFiles:
    print ("\n\nConfig ERROR: no inputFiles specified\n\n")
    sys.exit()
if not options.dataset in datasets:
    print (options.dataset, "not an allowed dataset, options are", datasets)
    sys.exit()

# print settings
print ("\n\n***** JOB SETUP *************************")
for key in options._register:
    # do not print unused default options
    if key not in [
        "secondaryInputFiles",
        "section",
        "tag",
        "totalSections",
        "outputFile",
        "secondaryOutputFile",
        "filePrepend",
    ]:
        print (str(key) + " : " + str(options.__getattr__(key)))
print ("*****************************************\n\n")

writeNominal = False
systsJES = []
systsJER = []
if options.systematicVariations:
    for var in options.systematicVariations:
        if var.lower() == "nominal":
            writeNominal = True
        elif var.startswith("JES"):
            systsJES.append(var + "up")
            systsJES.append(var + "down")
        elif var.startswith("JER"):
            systsJER.append(var + "up")
            systsJER.append(var + "down")
        else:
            print ("ERROR: unknown variation '" + var + "'")
            sys.exit()
systs = systsJER + systsJES

if options.isData:
    systsJER = []
    systsJES = []
    systs = []
    writeNominal = True

process = cms.Process("boostedAnalysis")

# cmssw options
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = options.globalTag
process.load("CondCore.CondDB.CondDB_cfi")
process.options = cms.untracked.PSet(wantSummary=cms.untracked.bool(False))
# process.options.allowUnscheduled = cms.untracked.bool(False)
process.maxEvents = cms.untracked.PSet(
    input=cms.untracked.int32(int(options.maxEvents))
)
process.source = cms.Source(
    "PoolSource",
    fileNames=cms.untracked.vstring(options.inputFiles),
    skipEvents=cms.untracked.uint32(int(options.skipEvents)),
)
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

# ------------------------------------------------------------------------------------------------------------------------------------------------- #

# jec_mc_data = 'DATA' if options.isData else 'MC'
# print jec_mc_data
# process.CondDB.connect = cms.string('sqlite_fip:BoostedTTH/BoostedAnalyzer/data/jecs/Fall17_17Nov2017_V32_94X_'+jec_mc_data+'.db')
# process.jec = cms.ESSource('PoolDBESSource',
# process.CondDB,
##connect = cms.string('sqlite_fip:BoostedTTH/BoostedAnalyzer/data/jecs/Fall17_17Nov2017_V32_94X_'+jec_mc_data+'.db'),
# toGet = cms.VPSet(
# cms.PSet(
# record = cms.string('JetCorrectionsRecord'),
# tag    = cms.string('JetCorrectorParametersCollection_Fall17_17Nov2017_V32_94X_'+jec_mc_data+'_AK4PFchs'),
# label  = cms.untracked.string('AK4PFchs')
# ),
# cms.PSet(
# record = cms.string('JetCorrectionsRecord'),
# tag    = cms.string('JetCorrectorParametersCollection_Fall17_17Nov2017_V32_94X_'+jec_mc_data+'_AK8PFchs'),
# label  = cms.untracked.string('AK8PFchs')
# ),
## ...and so on for all jet types you need
# )
# )
# process.es_prefer_jec = cms.ESPrefer('PoolDBESSource', 'jec')

# process.GlobalTag.toGet = cms.VPSet(
# cms.PSet(record = cms.string("JetCorrectionsRecord"),
# tag = cms.string('JetCorrectorParametersCollection_Fall17_17Nov2017_V32_94X_'+jec_mc_data+'_AK4PFchs'),
# connect = cms.string('sqlite_fip:BoostedTTH/BoostedAnalyzer/data/jecs/Fall17_17Nov2017_V32_94X_'+jec_mc_data+'.db')
# ),
# cms.PSet(record = cms.string("JetCorrectionsRecord"),
# tag = cms.string('JetCorrectorParametersCollection_Fall17_17Nov2017_V32_94X_'+jec_mc_data+'_AK8PFchs'),
# connect = cms.string('sqlite_fip:BoostedTTH/BoostedAnalyzer/data/jecs/Fall17_17Nov2017_V32_94X_'+jec_mc_data+'.db')
# )
# )


# Set up JetCorrections chain to be used in MiniAODHelper
# Note: name is hard-coded to ak4PFchsL1L2L3 and does not
# necessarily reflect actual corrections level
from JetMETCorrections.Configuration.JetCorrectionServices_cff import *

process.ak4PFPUPPIL1Fastjet = cms.ESProducer(
    "L1FastjetCorrectionESProducer",
    level=cms.string("L1FastJet"),
    algorithm=cms.string("AK4PFPuppi"),
    srcRho=cms.InputTag("fixedGridRhoFastjetAll"),
)
process.ak4PFPuppiL2Relative = ak4CaloL2Relative.clone(algorithm="AK4PFPuppi")
process.ak4PFPuppiL3Absolute = ak4CaloL3Absolute.clone(algorithm="AK4PFPuppi")
process.ak4PFPuppiResidual = ak4CaloResidual.clone(algorithm="AK4PFPuppi")
process.ak4PFPuppiL1L2L3 = cms.ESProducer(
    "JetCorrectionESChain",
    correctors=cms.vstring(
        "ak4PFPUPPIL1Fastjet", "ak4PFPuppiL2Relative", "ak4PFPuppiL3Absolute"
    ),
)
if options.isData:
    process.ak4PFPuppiL1L2L3.correctors.append(
        "ak4PFPuppiResidual"
    )  # add residual JEC for data


process.ak8PFPUPPIL1Fastjet = cms.ESProducer(
    "L1FastjetCorrectionESProducer",
    level=cms.string("L1FastJet"),
    algorithm=cms.string("AK8PFPuppi"),
    srcRho=cms.InputTag("fixedGridRhoFastjetAll"),
)
process.ak8PFPuppiL2Relative = ak4CaloL2Relative.clone(algorithm="AK8PFPuppi")
process.ak8PFPuppiL3Absolute = ak4CaloL3Absolute.clone(algorithm="AK8PFPuppi")
process.ak8PFPuppiResidual = ak4CaloResidual.clone(algorithm="AK8PFPuppi")
process.ak8PFPuppiL1L2L3 = cms.ESProducer(
    "JetCorrectionESChain",
    correctors=cms.vstring(
        "ak8PFPUPPIL1Fastjet", "ak8PFPuppiL2Relative", "ak8PFPuppiL3Absolute"
    ),
)

if options.isData:
    process.ak8PFPuppiL1L2L3.correctors.append(
        "ak8PFPuppiResidual"
    )  # add residual JEC for data

# ------------------------------------------------------------------------------------------------------------------------------------------------- #
# from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection

# updateJetCollection(
# process,
# labelName = 'AK15SoftDropSubjetsWithDeepJet',
# jetSource = cms.InputTag("selectedPatJetsAK15PFPuppiSoftDropPacked","SubJets","SKIM"),
# jetCorrections = ('AK4PFPuppi', cms.vstring(['L1FastJet','L2Relative', 'L3Absolute', 'L2L3Residual']), 'None'),# Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
# btagDiscriminators = ['pfDeepFlavourJetTags:probb',
#'pfDeepFlavourJetTags:probbb',
#'pfDeepFlavourJetTags:problepb',
#'pfDeepFlavourJetTags:probc',
#'pfDeepFlavourJetTags:probuds',
#'pfDeepFlavourJetTags:probg'],
# explicitJTA = True,          # needed for subjet b tagging
# svClustering = False,        # needed for subjet b tagging (IMPORTANT: Needs to be set to False to disable ghost-association which does not work with slimmed jets)
# fatJets = cms.InputTag("selectedUpdatedPatJetsAK15WithPuppiDaughters", "", "SKIM"), # needed for subjet b tagging
# rParam = 1.5,                # needed for subjet b tagging
# algo = 'ak'                  # has to be defined but is not used with svClustering=False
# )

## this producer merges the ak15 fat jets (groomed with softdrop) with the softdrop subjets
# process.MergeAK15FatjetsAndSubjets=cms.EDProducer("BoostedJetMerger",
# jetSrc=cms.InputTag("selectedPatJetsAK15PFPuppiSoftDrop", "", "SKIM"),
# subjetSrc=cms.InputTag("selectedUpdatedPatJetsAK15SoftDropSubjetsWithDeepJet"))

## this producer puts all information from the ak15 fat jets (groomed and ungroomed) and the subjets into one collection containing everything
# process.AK15PFPuppiWithDeepAK15WithSoftDropSubjetsWithDeepJet=cms.EDProducer("JetSubstructurePacker",
# jetSrc = cms.InputTag("selectedUpdatedPatJetsAK15WithPuppiDaughters", "", "SKIM"),
# distMax = cms.double(1.5),
# algoTags = cms.VInputTag(
# cms.InputTag("MergeAK15FatjetsAndSubjets")
# ),
# algoLabels = cms.vstring(
#'SoftDropWithDeepJet'
# ),
# fixDaughters = cms.bool(False),
# )

# ------------------------------------------------------------------------------------------------------------------------------------------------- #

if options.recorrectMET:
    from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import (
        runMetCorAndUncFromMiniAOD,
    )
    from PhysicsTools.PatAlgos.slimming.puppiForMET_cff import makePuppiesFromMiniAOD

    makePuppiesFromMiniAOD(process, True)

    runMetCorAndUncFromMiniAOD(
        process,
        isData=options.isData,
        fixEE2017=True if "2017" in options.dataEra else False,
        fixEE2017Params={
            "userawPt": True,
            "ptThreshold": 50.0,
            "minEtaThreshold": 2.65,
            "maxEtaThreshold": 3.139,
        },
    )

    runMetCorAndUncFromMiniAOD(
        process,
        isData=options.isData,
        metType="Puppi",
        postfix="Puppi",
        jetFlavor="AK4PFPuppi",
    )
    process.puppiNoLep.useExistingWeights = True
    process.puppi.useExistingWeights = True

# METCollection      = cms.InputTag("slimmedMETs", "", process.name_())

# ------------------------------------------------------------------------------------------------------------------------------------------------- #

# run ecalBadCalibReducedMINIAODFilter for 2017 data
if "2017" or "2018" in options.dataEra:
    process.load("RecoMET.METFilters.ecalBadCalibFilter_cfi")

    baddetEcallist = cms.vuint32(
        [
            872439604,
            872422825,
            872420274,
            872423218,
            872423215,
            872416066,
            872435036,
            872439336,
            872420273,
            872436907,
            872420147,
            872439731,
            872436657,
            872420397,
            872439732,
            872439339,
            872439603,
            872422436,
            872439861,
            872437051,
            872437052,
            872420649,
            872422436,
            872421950,
            872437185,
            872422564,
            872421566,
            872421695,
            872421955,
            872421567,
            872437184,
            872421951,
            872421694,
            872437056,
            872437057,
            872437313,
        ]
    )

    process.ecalBadCalibReducedMINIAODFilter = cms.EDFilter(
        "EcalBadCalibFilter",
        EcalRecHitSource=cms.InputTag("reducedEgamma:reducedEERecHits"),
        ecalMinEt=cms.double(50.0),
        baddetEcal=baddetEcallist,
        taggingMode=cms.bool(True),
        debug=cms.bool(False),
    )

# ------------------------------------------------------------------------------------------------------------------------------------------------- #

### E/Gamma recommendations ###

### Electron scale and smearing corrections ###
#from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq

#EG_era = None
#EG_corrections = None
#EG_vid = None
#if "2016" in options.dataEra:
#    EG_era = "2016-Legacy"
#    EG_corrections = False
#    EG_vid = True
#elif "2017" in options.dataEra:
#    EG_era = "2017-Nov17ReReco"
#    EG_corrections = True
#    EG_vid = True
#elif "2018" in options.dataEra:
#    EG_era = "2018-Prompt"
#    EG_corrections = True
#    EG_vid = True
#else:
#    raise Exception(
#        "dataEra "
#        + options.dataEra
#        + " not supported for Egamma tools: USE dataEra=2016/2017/2018"
#    )

#setupEgammaPostRecoSeq(
#    process, runVID=EG_vid, runEnergyCorrections=EG_corrections, era=EG_era
#)
# a sequence egammaPostRecoSeq has now been created and should be added to your path, eg process.p=cms.Path(process.egammaPostRecoSeq)
# electronCollection = cms.InputTag("slimmedElectrons","",process.name_())

#-------------------------------------------------------------------------------------------------------------------------------------------------- #
from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
from PhysicsTools.PatAlgos.patPuppiJetSpecificProducer_cfi import patPuppiJetSpecificProducer

process.patPuppiJetSpecificProducerAK8 = patPuppiJetSpecificProducer.clone(
  src=cms.InputTag("AK8PFPuppiComplete", "", "SKIM"),
)
updateJetCollection(
   process,
   labelName = 'PuppiVarsAK8',
   jetSource = cms.InputTag("AK8PFPuppiComplete", "", "SKIM"),
   )
process.updatedPatJetsPuppiVarsAK8.userData.userFloats.src = ['patPuppiJetSpecificProducerAK8:puppiMultiplicity', 'patPuppiJetSpecificProducerAK8:neutralPuppiMultiplicity']
process.updatedPatJetsPuppiVarsAK8.userData.userFunctions = ["userFloat(\"patPuppiJetSpecificProducerAK8:puppiMultiplicity\")","userFloat(\"patPuppiJetSpecificProducerAK8:neutralPuppiMultiplicity\")"]
process.updatedPatJetsPuppiVarsAK8.userData.userFunctionLabels = ['patPuppiJetSpecificProducer:puppiMultiplicity','patPuppiJetSpecificProducer:neutralPuppiMultiplicity']

process.patPuppiJetSpecificProducerAK15 = patPuppiJetSpecificProducer.clone(
  src=cms.InputTag("AK15PFPuppiComplete", "", "SKIM"),
)
updateJetCollection(
   process,
   labelName = 'PuppiVarsAK15',
   jetSource = cms.InputTag("AK15PFPuppiComplete", "", "SKIM"),
   )
process.updatedPatJetsPuppiVarsAK15.userData.userFloats.src = ['patPuppiJetSpecificProducerAK15:puppiMultiplicity', 'patPuppiJetSpecificProducerAK15:neutralPuppiMultiplicity']
process.updatedPatJetsPuppiVarsAK15.userData.userFunctions = ["userFloat(\"patPuppiJetSpecificProducerAK15:puppiMultiplicity\")","userFloat(\"patPuppiJetSpecificProducerAK15:neutralPuppiMultiplicity\")"]
process.updatedPatJetsPuppiVarsAK15.userData.userFunctionLabels = ['patPuppiJetSpecificProducer:puppiMultiplicity','patPuppiJetSpecificProducer:neutralPuppiMultiplicity']
# ------------------------------------------------------------------------------------------------------------------------------------------------- #
# L1 Prefiring issue
if ("2016" in options.dataEra or "2017" in options.dataEra) and (not options.isData):
    from PhysicsTools.PatUtils.l1ECALPrefiringWeightProducer_cfi import l1ECALPrefiringWeightProducer
    prefire_era = None
    if "2016" in options.dataEra:
        prefire_era = "2016BtoH"
    elif "2017" in options.dataEra:
        prefire_era = "2017BtoF"
    else:
        prefire_era = None
    process.prefiringweight = l1ECALPrefiringWeightProducer.clone(
        DataEra = cms.string(prefire_era), #Use 2016BtoH for 2016
        UseJetEMPt = cms.bool(False),
        PrefiringRateSystematicUncty = cms.double(0.2),
        SkipWarnings = False)


# ------------------------------------------------------------------------------------------------------------------------------------------------- #

if "2017" in options.dataEra:
    process.load("BoostedTTH.Filters.Ele32DoubleL1ToSingleL1_cfi")


### some standard collections ####
# if not options.isData:
electronCollection = cms.InputTag("slimmedElectrons", "", "SKIM")
photonCollection = cms.InputTag("slimmedPhotons", "", "SKIM")
muonCollection = cms.InputTag("slimmedMuons")
tauCollection = cms.InputTag("slimmedTaus")
METCollection = cms.InputTag("slimmedMETs", "", process.name_())
PuppiMETCollection = cms.InputTag("slimmedMETsPuppi", "", process.name_())
jetCollection = cms.InputTag("selectedPatJetsAK4PFPuppi", "", "SKIM")
AK8jetCollection = cms.InputTag(
    "updatedPatJetsPuppiVarsAK8","",process.name_()
)
AK15jetCollection = cms.InputTag(
    "updatedPatJetsPuppiVarsAK15","",process.name_()
)


###### deterministic seed producer ######

if options.deterministicSeeds:
    process.load("PhysicsTools.PatUtils.deterministicSeeds_cfi")
    process.deterministicSeeds.produceCollections = cms.bool(True)
    process.deterministicSeeds.produceValueMaps = cms.bool(False)
    process.deterministicSeeds.electronCollection = electronCollection
    process.deterministicSeeds.muonCollection = muonCollection
    process.deterministicSeeds.tauCollection = tauCollection
    process.deterministicSeeds.photonCollection = photonCollection
    process.deterministicSeeds.jetCollection = jetCollection
    process.deterministicSeeds.METCollection = METCollection
    # process.deterministicSeeds.AK8jetCollection   = AK8jetCollection

    # overwrite output collections
    electronCollection = cms.InputTag(
        "deterministicSeeds", "electronsWithSeed", process.name_()
    )
    muonCollection = cms.InputTag(
        "deterministicSeeds", "muonsWithSeed", process.name_()
    )
    tauCollection = cms.InputTag("deterministicSeeds", "tausWithSeed", process.name_())
    photonCollection = cms.InputTag(
        "deterministicSeeds", "photonsWithSeed", process.name_()
    )
    jetCollection = cms.InputTag("deterministicSeeds", "jetsWithSeed", process.name_())
    METCollection = cms.InputTag("deterministicSeeds", "METsWithSeed", process.name_())
    # AK8jetCollection   = cms.InputTag("deterministicSeeds", "AK8jetsWithSeed", process.name_())

# ------------------------------------------------------------------------------------------------------------------------------------------------- #
# lepton and photon selection
# process.load('BoostedTTH.Producers.SelectedLeptonProducers_cfi')
from BoostedTTH.Producers.SelectedLeptonProducers_cfi import *
from BoostedTTH.Producers.SelectedPhotonProducers_cfi import *

if "2016" in options.dataEra:
    process.SelectedElectronProducer = SelectedElectronProducer2016
    process.SelectedElectronProducer.ptMins = [10.0, 20.0, 29.0]
    ###
    process.SelectedMuonProducer = SelectedMuonProducer2016
    process.SelectedMuonProducer.ptMins = [10.0, 20.0, 26.0]
    ###
    process.SelectedPhotonProducer = SelectedPhotonProducer2016
elif "2017" in options.dataEra:
    process.SelectedElectronProducer = SelectedElectronProducer2017
    process.SelectedElectronProducer.ptMins = [10.0, 20.0, 34.0]
    ###
    process.SelectedMuonProducer = SelectedMuonProducer2017
    process.SelectedMuonProducer.ptMins = [10.0, 20.0, 29.0]
    ###
    process.SelectedPhotonProducer = SelectedPhotonProducer2017
elif "2018" in options.dataEra:
    process.SelectedElectronProducer = SelectedElectronProducer2018
    process.SelectedElectronProducer.ptMins = [10.0, 20.0, 34.0]
    ###
    process.SelectedMuonProducer = SelectedMuonProducer2018
    process.SelectedMuonProducer.ptMins = [10.0, 20.0, 26.0]
    ###
    process.SelectedPhotonProducer = SelectedPhotonProducer2018


process.SelectedElectronProducer.leptons = electronCollection
process.SelectedElectronProducer.etaMaxs = [2.4, 2.4, 2.4]
process.SelectedElectronProducer.leptonIDs = ["loose", "tight", "tight"]
process.SelectedElectronProducer.isoConeSizes = ["R03"] * 3
process.SelectedElectronProducer.isoCorrTypes = ["rhoEA"] * 3
process.SelectedElectronProducer.collectionNames = [
    "selectedElectronsLoose",
    "selectedElectronsDL",
    "selectedElectrons",
]
process.SelectedElectronProducer.isData = options.isData
process.SelectedElectronProducer.era = options.dataEra


process.SelectedMuonProducer.leptons = muonCollection
process.SelectedMuonProducer.etaMaxs = [2.4, 2.4, 2.4]
process.SelectedMuonProducer.leptonIDs = ["loose", "tight", "tight"]
process.SelectedMuonProducer.isoConeSizes = ["R04"] * 3
process.SelectedMuonProducer.isoCorrTypes = ["deltaBeta"] * 3
process.SelectedMuonProducer.muonIsoTypes = ["loose", "tight", "tight"]
process.SelectedMuonProducer.collectionNames = [
    "selectedMuonsLoose",
    "selectedMuonsDL",
    "selectedMuons",
]
process.SelectedMuonProducer.useMuonRC = options.useMuonRC
process.SelectedMuonProducer.useDeterministicSeeds = options.deterministicSeeds
process.SelectedMuonProducer.isData = options.isData
process.SelectedMuonProducer.era = options.dataEra

process.SelectedPhotonProducer.electrons = cms.InputTag(
    "SelectedElectronProducer:selectedElectronsLoose"
)
process.SelectedPhotonProducer.ptMins = [15.0, 175.0]
process.SelectedPhotonProducer.etaMaxs = [2.4, 2.4]
process.SelectedPhotonProducer.IDs = ["loose", "tight"]
process.SelectedPhotonProducer.collectionNames = [
    "selectedPhotonsLoose",
    "selectedPhotons",
]
process.SelectedPhotonProducer.isData = options.isData
process.SelectedPhotonProducer.era = options.dataEra

# ------------------------------------------------------------------------------------------------------------------------------------------------- #
# apply JES correction to AK4 jets
from BoostedTTH.Producers.SelectedJetProducer_cfi import *

process.CorrectedJetProducerAK4 = SelectedJetProducer
process.CorrectedJetProducerAK4.era = cms.string(options.dataEra)
process.CorrectedJetProducerAK4.JetType = cms.string("AK4PFPUPPI")
process.CorrectedJetProducerAK4.jets = jetCollection
process.CorrectedJetProducerAK4.ptMins = cms.vdouble(-1.0)
process.CorrectedJetProducerAK4.etaMaxs = cms.vdouble(999.0)
process.CorrectedJetProducerAK4.applyCorrection = cms.bool(True)
process.CorrectedJetProducerAK4.collectionNames = cms.vstring("correctedJetsAK4")
process.CorrectedJetProducerAK4.systematics = cms.vstring([""] + systsJES)
process.CorrectedJetProducerAK4.JetID = cms.vstring("tight")
process.CorrectedJetProducerAK4.PUJetIDMins = cms.vstring("none")
process.CorrectedJetProducerAK4.isData = cms.bool(options.isData)
process.CorrectedJetProducerAK4.doJER = cms.bool(False)
process.CorrectedJetProducerAK4.electrons = cms.InputTag(
    "SelectedElectronProducer:selectedElectronsLoose"
)
process.CorrectedJetProducerAK4.muons = cms.InputTag(
    "SelectedMuonProducer:selectedMuonsLoose"
)
process.CorrectedJetProducerAK4.photons = cms.InputTag(
    "SelectedPhotonProducer:selectedPhotonsLoose"
)
process.CorrectedJetProducerAK4.leptonJetDr = cms.double(0.4)

process.CorrectedJetProducerLooseAK4 = process.CorrectedJetProducerAK4.clone(
    jets=cms.InputTag("slimmedJetsPuppi"),
    JetID=["none"],
    leptonJetDr = -1.0,
    collectionNames = ["correctedJetsLooseAK4"],
    applyCorrection = True,
    systematics = [""]
)

# nominal AK4 jet selection
process.SelectedJetProducerAK4 = process.CorrectedJetProducerAK4.clone(
    jets=cms.InputTag("patSmearedJetsAK4", "", process.name_()),
    applyCorrection=False,
    ptMins=[30],
    etaMaxs=[2.4],
    collectionNames=["selectedJetsAK4"],
    systematics=[""],
    PUJetIDMins=["none"],
    JetID=["none"],
)

process.SelectedJetProducerLooseAK4 = process.CorrectedJetProducerLooseAK4.clone(
    jets=cms.InputTag("patSmearedJetsLooseAK4", "", process.name_()),
    applyCorrection=False,
    ptMins=[10.],
    etaMaxs=[4.7],
    collectionNames=["selectedJetsLooseAK4"],
    systematics=[""],
    PUJetIDMins=["none"],
    JetID=["none"],
)

# selection of the systematically shifted (JES) AK4 jets
for syst in systs:
    setattr(
        process,
        "SelectedJetProducerAK4" + syst,
        process.SelectedJetProducerAK4.clone(
            jets="patSmearedJetsAK4" + syst,
            collectionNames=[
                n + syst for n in list(process.SelectedJetProducerAK4.collectionNames)
            ],
        ),
    )
    #setattr(
        #process,
        #"SelectedJetProducerLooseAK4" + syst,
        #process.SelectedJetProducerLooseAK4.clone(
            #jets="patSmearedJetsLooseAK4" + syst,
            #collectionNames=[
                #n + syst for n in list(process.SelectedJetProducerLooseAK4.collectionNames)
            #],
        #),
    #)

# apply JES correction to AK8 jets
process.CorrectedJetProducerAK8 = process.CorrectedJetProducerAK4.clone(
    jets=AK8jetCollection,
    JetType="AK8PFPUPPI",
    collectionNames=["correctedJetsAK8"],
    leptonJetDr=0.8,
)

# nominal AK8 jet selection
process.SelectedJetProducerAK8 = process.CorrectedJetProducerAK8.clone(
    jets=cms.InputTag("patSmearedJetsAK8", "", process.name_()),
    ptMins=[170.0],
    etaMaxs=[2.4],
    collectionNames=["selectedJetsAK8"],
    applyCorrection=False,
    systematics=[""],
    JetID=["none"],
    PUJetIDMins=["none"],
)

# selection of the systematically shifted (JES) AK8 jets
for syst in systs:
    setattr(
        process,
        "SelectedJetProducerAK8" + syst,
        process.SelectedJetProducerAK8.clone(
            jets="patSmearedJetsAK8" + syst,
            collectionNames=[
                n + syst for n in list(process.SelectedJetProducerAK8.collectionNames)
            ],
        ),
    )

# apply JES correction to AK15 jets
process.CorrectedJetProducerAK15 = process.CorrectedJetProducerAK8.clone(
    jets=AK15jetCollection,
    JetType="AK15PFPUPPI",
    collectionNames=["correctedJetsAK15"],
    leptonJetDr=1.5,
)

# nominal AK15 jet selection
process.SelectedJetProducerAK15 = process.CorrectedJetProducerAK15.clone(
    jets=cms.InputTag("patSmearedJetsAK15", "", process.name_()),
    ptMins=[200.0],
    etaMaxs=[2.4],
    collectionNames=["selectedJetsAK15"],
    applyCorrection=False,
    systematics=[""],
    JetID=["none"],
    PUJetIDMins=["none"],
)

# selection of the systematically shifted (JES) AK15 jets
for syst in systs:
    setattr(
        process,
        "SelectedJetProducerAK15" + syst,
        process.SelectedJetProducerAK15.clone(
            jets="patSmearedJetsAK15" + syst,
            collectionNames=[
                n + syst for n in list(process.SelectedJetProducerAK15.collectionNames)
            ],
        ),
    )

# smearing of corrected jets -- producers that create the nominal and up/down JER correction
# jer shift of nominal sample
if "2016" in options.dataEra:
    jerResFileAK4 = "Summer16_25nsV1_MC_PtResolution_AK4PFPuppi.txt"
    jerResFileAK8 = "Summer16_25nsV1_MC_PtResolution_AK8PFPuppi.txt"
    jerSFFileAK4 = "Summer16_25nsV1_MC_SF_AK4PFPuppi.txt"
    jerSFFileAK8 = "Summer16_25nsV1_MC_SF_AK8PFPuppi.txt"
elif "2017" in options.dataEra:
    jerResFileAK4 = "Fall17_V3_MC_PtResolution_AK4PFPuppi.txt"
    jerResFileAK8 = "Fall17_V3_MC_PtResolution_AK8PFPuppi.txt"
    jerSFFileAK4 = "Fall17_V3_MC_SF_AK4PFPuppi.txt"
    jerSFFileAK8 = "Fall17_V3_MC_SF_AK8PFPuppi.txt"
elif "2018" in options.dataEra:
    jerResFileAK4 = "Autumn18_V7_MC_PtResolution_AK4PFPuppi.txt"
    jerResFileAK8 = "Autumn18_V7_MC_PtResolution_AK8PFPuppi.txt"
    jerSFFileAK4 = "Autumn18_V7_MC_SF_AK4PFPuppi.txt"
    jerSFFileAK8 = "Autumn18_V7_MC_SF_AK8PFPuppi.txt"
else:
    raise Exception("NO JER FILES SPECIFIED: USE dataEra=2016/2017/2018")

process.patSmearedJetsAK4 = cms.EDProducer(
    "SmearedPATJetProducer",
    src=cms.InputTag("CorrectedJetProducerAK4:correctedJetsAK4"),
    enabled=cms.bool(True),  # If False, no smearing is performed
    rho=cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching=cms.bool(
        False
    ),  # If True, always skip gen jet matching and smear jet with a random gaussian
    # algopt = cms.string('AK4PFchs_pt'),
    # algo = cms.string('AK4PFchs'),
    genJets=cms.InputTag("selectedPatJetsAK4PFPuppi", "genJets", "SKIM"),
    dRMax=cms.double(0.2),  # = cone size (0.4) / 2
    dPtMaxFactor=cms.double(3),  # dPt < 3 * resolution
    variation=cms.int32(0),  # systematic +1 0 -1 sigma
    debug=cms.untracked.bool(False),
    useDeterministicSeed=cms.bool(
        False
    ),  # default deterministic seeds not used, but our own
    resolutionFile=cms.FileInPath(
        "BoostedTTH/BoostedAnalyzer/data/jerfiles/" + jerResFileAK4
    ),
    scaleFactorFile=cms.FileInPath(
        "BoostedTTH/BoostedAnalyzer/data/jerfiles/" + jerSFFileAK4
    ),
)

process.patSmearedJetsLooseAK4 = process.patSmearedJetsAK4.clone(
    src=cms.InputTag("CorrectedJetProducerLooseAK4:correctedJetsLooseAK4"),
    genJets=cms.InputTag("slimmedGenJets")
)


process.patSmearedJetsAK8 = cms.EDProducer(
    "SmearedPATJetProducer",
    src=cms.InputTag("CorrectedJetProducerAK8:correctedJetsAK8"),
    enabled=cms.bool(True),  # If False, no smearing is performed
    rho=cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching=cms.bool(
        False
    ),  # If True, always skip gen jet matching and smear jet with a random gaussian
    #    algopt = cms.string('AK4PFchs_pt'),
    #    algo = cms.string('AK4PFchs'),
    genJets=cms.InputTag("selectedPatJetsAK8PFPuppi", "genJets", "SKIM"),
    dRMax=cms.double(0.4),  # = cone size (0.8) / 2
    dPtMaxFactor=cms.double(3),  # dPt < 3 * resolution
    variation=cms.int32(0),  # systematic +1 0 -1 sigma
    debug=cms.untracked.bool(False),
    useDeterministicSeed=cms.bool(
        False
    ),  # default deterministic seeds not used, but our own
    resolutionFile=cms.FileInPath(
        "BoostedTTH/BoostedAnalyzer/data/jerfiles/" + jerResFileAK8
    ),
    scaleFactorFile=cms.FileInPath(
        "BoostedTTH/BoostedAnalyzer/data/jerfiles/" + jerSFFileAK8
    ),
)

process.patSmearedJetsAK15 = cms.EDProducer(
    "SmearedPATJetProducer",
    src=cms.InputTag("CorrectedJetProducerAK15:correctedJetsAK15"),
    enabled=cms.bool(True),  # If False, no smearing is performed
    rho=cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching=cms.bool(
        False
    ),  # If True, always skip gen jet matching and smear jet with a random gaussian
    #    algopt = cms.string('AK4PFchs_pt'),
    #    algo = cms.string('AK4PFchs'),
    genJets=cms.InputTag("selectedPatJetsAK15PFPuppi", "genJets", "SKIM"),
    dRMax=cms.double(0.75),  # = cone size (1.5) / 2
    dPtMaxFactor=cms.double(3),  # dPt < 3 * resolution
    variation=cms.int32(0),  # systematic +1 0 -1 sigma
    debug=cms.untracked.bool(False),
    useDeterministicSeed=cms.bool(
        False
    ),  # default deterministic seeds not used, but our own
    resolutionFile=cms.FileInPath(
        "BoostedTTH/BoostedAnalyzer/data/jerfiles/" + jerResFileAK8
    ),
    scaleFactorFile=cms.FileInPath(
        "BoostedTTH/BoostedAnalyzer/data/jerfiles/" + jerSFFileAK8
    ),
)

# up/down jer shift of nominal sample and nominal jer shift of jes systematic samples
for s in systsJER:
    v = 0
    if s == "JERup":
        v = +1
    elif s == "JERdown":
        v = -1
    setattr(
        process,
        "patSmearedJetsAK4" + s,
        process.patSmearedJetsAK4.clone(
            variation=v, src=cms.InputTag("CorrectedJetProducerAK4:correctedJetsAK4")
        ),
    )
    #setattr(
        #process,
        #"patSmearedJetsLooseAK4" + s,
        #process.patSmearedJetsLooseAK4.clone(
            #variation=v, src=cms.InputTag("CorrectedJetProducerLooseAK4:correctedJetsLooseAK4")
        #),
    #)
    setattr(
        process,
        "patSmearedJetsAK8" + s,
        process.patSmearedJetsAK8.clone(
            variation=v, src=cms.InputTag("CorrectedJetProducerAK8:correctedJetsAK8")
        ),
    )
    setattr(
        process,
        "patSmearedJetsAK15" + s,
        process.patSmearedJetsAK15.clone(
            variation=v, src=cms.InputTag("CorrectedJetProducerAK15:correctedJetsAK15")
        ),
    )
for s in systsJES:
    setattr(
        process,
        "patSmearedJetsAK4" + s,
        process.patSmearedJetsAK4.clone(
            variation=0,
            src=cms.InputTag("CorrectedJetProducerAK4:correctedJetsAK4" + s),
        ),
    )
    #setattr(
        #process,
        #"patSmearedJetsLooseAK4" + s,
        #process.patSmearedJetsLooseAK4.clone(
            #variation=0,
            #src=cms.InputTag("CorrectedJetProducerLooseAK4:correctedJetsLooseAK4" + s),
        #),
    #)
    setattr(
        process,
        "patSmearedJetsAK8" + s,
        process.patSmearedJetsAK8.clone(
            variation=0,
            src=cms.InputTag("CorrectedJetProducerAK8:correctedJetsAK8" + s),
        ),
    )
    setattr(
        process,
        "patSmearedJetsAK15" + s,
        process.patSmearedJetsAK15.clone(
            variation=0,
            src=cms.InputTag("CorrectedJetProducerAK15:correctedJetsAK15" + s),
        ),
    )


# ------------------------------------------------------------------------------------------------------------------------------------------------- #
# JECs for Subjets
from PhysicsTools.PatAlgos.tools.jetTools import addJetCollection
addJetCollection(process,
                    jetSource = cms.InputTag("MergeAK15FatjetsAndSubjets","SubJets","SKIM"),
                    labelName = 'CreateRefs',
                    jetCorrections = ("AK4PFPuppi", cms.vstring(["L1FastJet", "L2Relative", "L3Absolute", "L2L3Residual"]), "None"),
                    getJetMCFlavour = False,
                    pvSource = cms.InputTag("offlineSlimmedPrimaryVertices"),
                    genParticles = cms.InputTag("prunedGenParticles"),
                    genJetCollection = cms.InputTag("slimmedGenJets")
                    )
if options.isData:
    process.patJetsCreateRefs.addGenPartonMatch = cms.bool(False)
    process.patJetsCreateRefs.addGenJetMatch = cms.bool(False)
    process.patJetsCreateRefs.addPartonJetMatch = cms.bool(False)

process.CorrectedSubjetProducer = process.CorrectedJetProducerAK4.clone(
    jets=cms.InputTag("selectedPatJetsCreateRefs"),
    JetID=["none"],
    leptonJetDr = -1.0,
    collectionNames = ["correctedSubjets"],
    doDeltaRCleaning = cms.bool(False),
    isSubjetCollection = cms.bool(True)
)
process.patSmearedSubjets = process.patSmearedJetsAK4.clone(
    src=cms.InputTag("CorrectedSubjetProducer:correctedSubjets"),
    skipGenMatching=cms.bool(True)
)
for s in systsJES:
    setattr(
        process,
        "patSmearedSubjets" + s,
        process.patSmearedSubjets.clone(
            variation=0,
            src=cms.InputTag("CorrectedSubjetProducer:correctedSubjets"+s),
        )
    )
for s in systsJER:
    v = 0
    if s == "JERup":
        v = +1
    elif s == "JERdown":
        v = -1
    setattr(
        process,
        "patSmearedSubjets" + s,
        process.patSmearedSubjets.clone(
            variation=v, src=cms.InputTag("CorrectedSubjetProducer:correctedSubjets")
        )
    )
process.LinkAK15JetsAndCorrectedSubjets = cms.EDProducer(
    "BoostedJetMerger",
    jetSrc=cms.InputTag("MergeAK15FatjetsAndSubjets","","SKIM"),
    subjetSrc=cms.InputTag("patSmearedSubjets", "", process.name_())
)
process.CombineAK15JetsWithCorrectedSubjets = cms.EDProducer(
    "JetSubstructurePacker",
    jetSrc=cms.InputTag("SelectedJetProducerAK15:selectedJetsAK15"),
    distMax=cms.double(1.5),
    algoTags=cms.VInputTag(cms.InputTag("LinkAK15JetsAndCorrectedSubjets")),
    algoLabels=cms.vstring("SoftDropWithBtagInfoCorrected"),
    fixDaughters=cms.bool(False),
)
for syst in systs:
    setattr(
        process,
        "LinkAK15JetsAndCorrectedSubjets" + syst,
        process.LinkAK15JetsAndCorrectedSubjets.clone(
            jetSrc=cms.InputTag("MergeAK15FatjetsAndSubjets","","SKIM"),
            subjetSrc=cms.InputTag("patSmearedSubjets"+syst, "", process.name_())
        )
    )
    setattr(
        process,
        "CombineAK15JetsWithCorrectedSubjets" + syst,
        process.CombineAK15JetsWithCorrectedSubjets.clone(
            jetSrc=cms.InputTag("SelectedJetProducerAK15"+syst+":selectedJetsAK15"+syst),
            algoTags=cms.VInputTag(cms.InputTag("LinkAK15JetsAndCorrectedSubjets"+syst))
        )
    )
# ------------------------------------------------------------------------------------------------------------------------------------------------- #

### correct MET manually ###
# process.load("BoostedTTH.Producers.CorrectedMETproducer_cfi")
# process.CorrectedMETproducer.isData=options.isData
# process.CorrectedMETproducer.oldJets=cms.InputTag("slimmedJets", "", "PAT")
# process.CorrectedMETproducer.newJets=cms.InputTag("slimmedJets", "", "PAT")
# process.CorrectedMETproducer.oldElectrons=cms.InputTag("slimmedElectrons", "", "PAT")
# process.CorrectedMETproducer.newElectrons=cms.InputTag("slimmedElectrons", "", "PAT")
# process.CorrectedMETproducer.oldMuons=cms.InputTag("SelectedMuonProducerUncorr:selectedMuonsUncorr")
# process.CorrectedMETproducer.newMuons=cms.InputTag("SelectedMuonProducer:selectedMuons")
# process.CorrectedMETproducer.mets=METCollection

# load and run the boosted analyzer
if options.isData:
    from BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_data_cfi import *

    if "2016" in options.dataEra:
        process.BoostedAnalyzer = BoostedAnalyzer2016
    elif "2017" in options.dataEra:
        process.BoostedAnalyzer = BoostedAnalyzer2017
    elif "2018" in options.dataEra:
        process.BoostedAnalyzer = BoostedAnalyzer2018

    process.BoostedAnalyzer.filterBits = cms.InputTag("TriggerResults::RECO")
    process.BoostedAnalyzer.dataEra = options.dataEra

else:
    from BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi import *

    if "2016" in options.dataEra:
        process.BoostedAnalyzer = BoostedAnalyzer2016
    elif "2017" in options.dataEra:
        process.BoostedAnalyzer = BoostedAnalyzer2017
    elif "2018" in options.dataEra:
        process.BoostedAnalyzer = BoostedAnalyzer2018

    process.BoostedAnalyzer.dataEra = options.dataEra

    if not options.isBoostedMiniAOD:
        # Supplies PDG ID to real name resolution of MC particles
        process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
        # Needed to determine tt+x category -- is usually run when producing boosted jets in miniAOD
        process.load("BoostedTTH.Producers.genHadronMatching_cfi")

# which systematic variations to store in the ntuple?
variations = systs
if writeNominal:
    variations.insert(0, "")  # also store nominal case
process.BoostedAnalyzer.selectedJets = [
    cms.InputTag("SelectedJetProducerAK4" + s + ":selectedJetsAK4" + s)
    for s in variations
]
process.BoostedAnalyzer.selectedJetsLoose = [
    cms.InputTag("SelectedJetProducerLooseAK4:selectedJetsLooseAK4")
    for s in variations
]
process.BoostedAnalyzer.selectedJetsAK8 = [
    cms.InputTag("SelectedJetProducerAK8" + s + ":selectedJetsAK8" + s)
    for s in variations
]
process.BoostedAnalyzer.selectedJetsAK15 = [
    cms.InputTag("CombineAK15JetsWithCorrectedSubjets" + s)
    for s in variations
]
process.BoostedAnalyzer.correctedMETs = [METCollection] * (len(variations))
process.BoostedAnalyzer.correctedMETsPuppi = [PuppiMETCollection] * (len(variations))

process.BoostedAnalyzer.outfileName = options.outName
if not options.isData:
    process.BoostedAnalyzer.eventWeight = options.weight

process.BoostedAnalyzer.systematics = variations
process.BoostedAnalyzer.generatorName = options.generatorName

if options.isData and options.useJson:
    import FWCore.PythonUtilities.LumiList as LumiList

    if "2016" in options.dataEra:
        process.source.lumisToProcess = LumiList.LumiList(
            filename=os.getenv("CMSSW_BASE")
            + "/src/BoostedTTH/BoostedAnalyzer/data/lumi_jsons/Cert_271036-284044_13TeV_ReReco_07Aug2017_Collisions16_JSON.txt"
        ).getVLuminosityBlockRange()
    elif "2017" in options.dataEra:
        process.source.lumisToProcess = LumiList.LumiList(
            filename=os.getenv("CMSSW_BASE")
            + "/src/BoostedTTH/BoostedAnalyzer/data/lumi_jsons/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt"
        ).getVLuminosityBlockRange()
    elif "2018" in options.dataEra:
        process.source.lumisToProcess = LumiList.LumiList(
            filename=os.getenv("CMSSW_BASE")
            + "/src/BoostedTTH/BoostedAnalyzer/data/lumi_jsons/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt"
        ).getVLuminosityBlockRange()

if options.isData:
    process.BoostedAnalyzer.dataset = cms.string(options.dataset)


process.BoostedAnalyzer.selectionNames = [
    "FilterSelection",
    "VertexSelection",
    "MonoTopSelection",
]
if options.additionalSelection != "NONE":
    process.BoostedAnalyzer.selectionNames += cms.vstring(options.additionalSelection)

if options.isData:
    process.BoostedAnalyzer.processorNames = cms.vstring(
        "WeightProcessor",
        "essentialBasicVarProcessor",
        "TriggerVarProcessor",
        "PhotonVarProcessor",
        "JetVarProcessor",
        "DarkMatterProcessor",
        "LeptonVarProcessor"
    )
else:
    process.BoostedAnalyzer.processorNames = cms.vstring(
        "WeightProcessor",
        "MCMatchVarProcessor",
        "essentialBasicVarProcessor",
        "TriggerVarProcessor",
        "PhotonVarProcessor",
        "JetVarProcessor",
        "DarkMatterProcessor",
        "LeptonVarProcessor",
        "BosonWeightProcessor"
    )

if process.BoostedAnalyzer.taggingSelection:
    process.BoostedAnalyzer.processorNames.append("SelectionTagProcessor")


printContent = False
if printContent:
    process.content = cms.EDAnalyzer("EventContentAnalyzer")

if options.dumpSyncExe:
    process.BoostedAnalyzer.processorNames = []
    process.BoostedAnalyzer.selectionNames = []
    process.BoostedAnalyzer.dumpSyncExe = True
    process.BoostedAnalyzer.dumpExtended = False
    process.BoostedAnalyzer.dumpAlwaysEvents = [
        # 3222838,
        # 3211421,
        # 527273,
        # 3163883,
        # 2865714,
        # 2688365,
        # 2786936,
    ]

if options.ProduceMemNtuples == True:
    process.BoostedAnalyzer.memNtuples = True
    process.BoostedAnalyzer.processorNames = cms.vstring("SlimmedNtuples")

# ------------------------------------------------------------------------------------------------------------------------------------------------- #

##### DEFINE PATHS ##########

process.final = cms.EndPath(process.BoostedAnalyzer)
process.final.associate(process.patAlgosToolsTask)

# run ecalBadCalibReducedMINIAODFilter for 2017/2018 data
if "2017" or "2018" in options.dataEra:
    process.BoostedAnalyzer.additionalFilters = cms.VInputTag(
        ["ecalBadCalibReducedMINIAODFilter"]
    )
    process.metfilters = cms.Task(process.ecalBadCalibReducedMINIAODFilter)
    process.final.associate(process.metfilters)

if options.recorrectMET:
    process.met = cms.Path(process.fullPatMetSequence)
    process.met_puppi = cms.Path(
        process.puppiMETSequence * process.fullPatMetSequencePuppi
    )

if "2017" in options.dataEra:
    process.eletrigger = cms.Path(process.Ele32DoubleL1ToSingleL1)
# electron scale and smearing corrections
#process.egamma = cms.Path(process.egammaPostRecoSeq)

if options.deterministicSeeds:
    process.seeds = cms.Task(process.deterministicSeeds)
    process.final.associate(process.seeds)

process.leptons_photons = cms.Task()
process.leptons_photons.add(
    process.SelectedElectronProducer,
    process.SelectedMuonProducer,
    process.SelectedPhotonProducer,
)
process.final.associate(process.leptons_photons)

process.puppimults = cms.Path(process.patPuppiJetSpecificProducerAK8*process.patPuppiJetSpecificProducerAK15)

process.jets = cms.Task()
process.jets.add(process.updatedPatJetsPuppiVarsAK8)
process.jets.add(process.updatedPatJetsPuppiVarsAK15)
# process.jets.add(process.MergeAK15FatjetsAndSubjets)
# process.jets.add(process.AK15PFPuppiWithDeepAK15WithSoftDropSubjetsWithDeepJet)
process.jets.add(process.CorrectedJetProducerAK4)
process.jets.add(process.CorrectedJetProducerLooseAK4)
process.jets.add(process.CorrectedJetProducerAK8)
process.jets.add(process.CorrectedJetProducerAK15)
# always produce (but not necessarily write to ntuple) nominal case as collections might be needed
for s in [""] + systs:
    process.jets.add(getattr(process, "patSmearedJetsAK4" + s))
    #process.jets.add(getattr(process, "patSmearedJetsLooseAK4" + s))
    process.jets.add(getattr(process, "patSmearedJetsAK8" + s))
    process.jets.add(getattr(process, "patSmearedJetsAK15" + s))
    process.jets.add(getattr(process, "SelectedJetProducerAK4" + s))
    #process.jets.add(getattr(process, "SelectedJetProducerLooseAK4" + s))
    process.jets.add(getattr(process, "SelectedJetProducerAK8" + s))
    process.jets.add(getattr(process, "SelectedJetProducerAK15" + s))
process.jets.add(getattr(process, "patSmearedJetsLooseAK4"))
process.jets.add(getattr(process, "SelectedJetProducerLooseAK4"))
# process.final.associate(process.patAlgosToolsTask)
process.final.associate(process.jets)

# subjet corrections
process.subjets = cms.Task()
process.subjets.add(process.CorrectedSubjetProducer)
process.subjets.add(process.patSmearedSubjets)
process.subjets.add(process.LinkAK15JetsAndCorrectedSubjets)
process.subjets.add(process.CombineAK15JetsWithCorrectedSubjets)
for s in systs:
    process.subjets.add(getattr(process, "patSmearedSubjets" + s))
    process.subjets.add(getattr(process, "LinkAK15JetsAndCorrectedSubjets" + s))
    process.subjets.add(getattr(process, "CombineAK15JetsWithCorrectedSubjets" + s))
process.final.associate(process.subjets)

# L1 prefiring issue
if ("2016" in options.dataEra or "2017" in options.dataEra) and (not options.isData):
    process.prefire = cms.Task()
    process.prefire.add(process.prefiringweight)
    process.final.associate(process.prefire)

#if not options.isData and not options.isBoostedMiniAOD:
    #process.tthfmatcher = cms.Task()
    #process.tthfmatcher.add(
        #process.genParticlesForJetsNoNu,
        #process.ak4GenJetsCustom,
        #process.selectedHadronsAndPartons,
        #process.genJetFlavourInfos,
        #process.matchGenBHadron,
        #process.matchGenCHadron,
        #process.categorizeGenTtbar,
    #)
    #process.final.associate(process.tthfmatcher)

#print process.dumpPython()
