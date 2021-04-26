# ========================================================= Imports ========================================================= #

### general imports ###
import sys
import os

### cmssw imports ###
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing # parse command-line arguments, https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCommandLineParsing
# jet stuff (create new jet collections, update jet collections, ...)
from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox
from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
from PhysicsTools.PatAlgos.patPuppiJetSpecificProducer_cfi import patPuppiJetSpecificProducer
# egamma sequence (create electron ID decisions, update electron energy corrections, ...)
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
# met stuff (recalculate MET with new corrections, stuff for puppi MET, ...)
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import (
    runMetCorAndUncFromMiniAOD,
)
from PhysicsTools.PatAlgos.slimming.puppiForMET_cff import makePuppiesFromMiniAOD

# ========================================================= Read input arguments ========================================================= #
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
    "systematicVariations",
    "nominal",
    VarParsing.multiplicity.list,
    VarParsing.varType.string,
    "comma-separated list of systematic variations ('nominal' or systematics base name, up/down will be added)",
)
options.register(
    "dataEra",
    "2017",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "the era of the data taking period or mc campaign, e.g. '2016B' or '2017'",
)

options.parseArguments()

# re-set some defaults
if options.maxEvents is -1:  # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 1001  # reset for testing

if options.isData:
    if "2016" in options.dataEra:
        options.globalTag = "102X_dataRun2_v13"
    elif "2017" in options.dataEra:
        options.globalTag = "102X_dataRun2_v13"
    elif "2018" in options.dataEra:
        if "D" in options.dataEra:
            options.globalTag = "102X_dataRun2_Prompt_v16"
        else:
            options.globalTag = "102X_dataRun2_v13"
    else:
        raise Exception(
            "dataEra "
            + options.dataEra
            + " not supported for this config: USE dataEra=2016/2017"
        )
elif not options.isData:
    if "2016" in options.dataEra:
        options.globalTag = "102X_mcRun2_asymptotic_v8"
    elif "2017" in options.dataEra:
        options.globalTag = "102X_mc2017_realistic_v8"
    elif "2018" in options.dataEra:
        options.globalTag = "102X_upgrade2018_realistic_v21"
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
        if "2018" in options.dataEra:
            options.inputFiles = [
                "root://xrootd-cms.infn.it///store/mc/RunIIAutumn18MiniAOD/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/40000/E26C264E-6FAE-BA4B-B729-1FDD04B0B2AC.root"
            ]
        elif "2017" in options.dataEra:
            options.inputFiles = [
                "root://xrootd-cms.infn.it///store/mc/RunIIFall17MiniAODv2/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/100000/44A5063A-27D3-E811-BE88-0CC47AFB7DDC.root"
            ]
        elif "2016" in options.dataEra:
            options.inputFiles = [
                "root://xrootd-cms.infn.it///store/mc/RunIISummer16MiniAODv3/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v1/270000/68E65DC7-2C79-E911-A393-F01FAFE5CBE2.root"
            ]
        else:
            raise Exception(
                "dataEra "
                + options.dataEra
                + " not supported for this config: USE dataEra=2016/2017/2018"
            )
    else:
        if "2018" in options.dataEra:
            options.inputFiles = [
                "root://xrootd-cms.infn.it///store/data/Run2018B/MET/MINIAOD/17Sep2018-v1/100000/84F4D3C4-7275-834A-ADDF-E34194D17EB3.root"
            ]
        elif "2017" in options.dataEra:
            options.inputFiles = [
                "root://xrootd-cms.infn.it///store/data/Run2017E/MET/MINIAOD/31Mar2018-v1/80000/5E616617-8C38-E811-B665-0025905B859E.root"
            ]
        elif "2016" in options.dataEra:
            options.inputFiles = [
                "root://xrootd-cms.infn.it///store/data/Run2016G/MET/MINIAOD/17Jul2018-v1/50000/C64557A4-228C-E811-9543-0090FAA587C4.root"
            ]
        else:
            raise Exception(
                "dataEra "
                + options.dataEra
                + " not supported for this config: USE dataEra=2016/2017/2018"
            )

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

# ========================================================= Start cmssw process ========================================================= #

process = cms.Process("boostedAnalysis")

# read input file
process.source = cms.Source(
    "PoolSource",
    fileNames=cms.untracked.vstring(options.inputFiles),
    skipEvents=cms.untracked.uint32(int(options.skipEvents)),
)
process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(options.maxEvents))

# messages
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.options = cms.untracked.PSet(wantSummary=cms.untracked.bool(True))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = options.globalTag
process.load("CondCore.CondDB.CondDB_cfi")

# these are needed to write the new AK15 jet collections - dont know why ...
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("Configuration.Geometry.GeometryRecoDB_cff")

############################### first, skimming stuff ###############################

# -------------- AK4 jet stuff -------------- #

# update slimmedJets collection with DeepJet variables and update JECs
jetToolbox(
    process,
    "ak4",
    "ak4Jetchs",
    "noOutput",
    updateCollection="slimmedJets",
    JETCorrPayload="AK4PFchs",
    JETCorrLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual'],
    bTagDiscriminators=[
        "pfDeepFlavourJetTags:probb",
        "pfDeepFlavourJetTags:probbb",
        "pfDeepFlavourJetTags:problepb",
        "pfDeepFlavourJetTags:probc",
        "pfDeepFlavourJetTags:probuds",
        "pfDeepFlavourJetTags:probg",
    ],
    runOnMC=not options.isData,
    Cut="pt > 20. && abs(eta) < 2.5",
)

# update slimmedJetsPuppi collection with DeepJet variables and update JECs
# WARNING DeepJet has been trained on AK4PFchs jets, so the tagging variables might not make sense
#jetToolbox(
    #process,
    #"ak4",
    #"ak4Jetpuppi",
    #"noOutput",
    #updateCollection="slimmedJetsPuppi",
    #JETCorrPayload="AK4PFPuppi",
    #JETCorrLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual'],
    #bTagDiscriminators=[
        #"pfDeepFlavourJetTags:probb",
        #"pfDeepFlavourJetTags:probbb",
        #"pfDeepFlavourJetTags:problepb",
        #"pfDeepFlavourJetTags:probc",
        #"pfDeepFlavourJetTags:probuds",
        #"pfDeepFlavourJetTags:probg",
    #],
    #runOnMC=not options.isData,
    #Cut="pt > 20. && abs(eta) < 2.5",
#)

# -------------- AK15 jet stuff -------------- #

# cluster AK15 jets and use PUPPI pileup mitigation method
jetToolbox(
    process,
    "ak15",
    "ak15JetSubs",
    "noOutput",
    PUMethod="Puppi",
    addPruning=False,
    addSoftDrop=True,  # add basic grooming
    addTrimming=False,
    addFiltering=False,
    addSoftDropSubjets=True,
    addPrunedSubjets=False,
    addNsub=True,
    maxTau=3,  # add Nsubjettiness tau1, tau2, tau3, tau4
    JETCorrPayload="AK8PFPuppi",
    JETCorrLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual'],
    subJETCorrPayload='AK4PFPuppi',
    subJETCorrLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual'],
    runOnMC=not options.isData,
    dataTier="miniAOD",
    Cut="pt > 150. && abs(rapidity()) < 2.4",
    GetJetMCFlavour=not options.isData,
    bTagDiscriminators=["None"],
    # GetSubJetMCFlavour=True,
    addHEPTopTagger=False
)

# load DeepBoostedJet outputs
from RecoBTag.MXNet.pfDeepBoostedJet_cff import (
    _pfMassDecorrelatedDeepBoostedJetTagsProbs as pfMassDecorrelatedDeepBoostedJetTagsProbs,
    _pfMassDecorrelatedDeepBoostedJetTagsMetaDiscrs as pfMassDecorrelatedDeepBoostedJetTagsMetaDiscrs,
    _pfDeepBoostedJetTagsProbs as pfDeepBoostedJetTagsProbs,
    _pfDeepBoostedJetTagsMetaDiscrs as pfDeepBoostedJetTagsMetaDiscrs,
)

print (pfMassDecorrelatedDeepBoostedJetTagsProbs)
print (pfMassDecorrelatedDeepBoostedJetTagsMetaDiscrs)
print (pfDeepBoostedJetTagsProbs)
print (pfDeepBoostedJetTagsMetaDiscrs)

# update the new AK15 jet collection with DeepAK15 tagger outputs
updateJetCollection(
    process,
    jetSource=cms.InputTag("packedPatJetsAK15PFPuppiSoftDrop"),
    pvSource=cms.InputTag('offlineSlimmedPrimaryVertices'),
    svSource=cms.InputTag('slimmedSecondaryVertices'),
    rParam=1.5,
    jetCorrections=("AK8PFPuppi", cms.vstring(["L1FastJet", "L2Relative", "L3Absolute", "L2L3Residual"]), "None"),
    btagDiscriminators=pfMassDecorrelatedDeepBoostedJetTagsProbs
    + pfMassDecorrelatedDeepBoostedJetTagsMetaDiscrs + pfDeepBoostedJetTagsProbs + pfDeepBoostedJetTagsMetaDiscrs,
    postfix="AK15WithPuppiDaughters",
)
# since DeepAK15 is not standard, preprocessing parameters have to be provided -> from LPC-DM colleagues
from MonoTop.MonoTopSkim.pfDeepBoostedJetPreprocessParamsAK15_cfi_new import (
    pfDeepBoostedJetPreprocessParams as params,
)
# provide parameter and model file for DeepAK15 tagger -> from LPC-DM colleagues
process.pfDeepBoostedJetTagInfosAK15WithPuppiDaughters.jet_radius = 1.5
process.pfMassDecorrelatedDeepBoostedJetTagsAK15WithPuppiDaughters.preprocessParams = (
    params
)
process.pfMassDecorrelatedDeepBoostedJetTagsAK15WithPuppiDaughters.model_path = (
    "MonoTop/MonoTopSkim/data/deepak15/decorrelated/resnet-symbol.json"
)
process.pfMassDecorrelatedDeepBoostedJetTagsAK15WithPuppiDaughters.param_path = (
    "MonoTop/MonoTopSkim/data/deepak15/decorrelated/resnet.params"
)
process.pfDeepBoostedJetTagsAK15WithPuppiDaughters.preprocessParams = (
    params
)
process.pfDeepBoostedJetTagsAK15WithPuppiDaughters.model_path = (
    "MonoTop/MonoTopSkim/data/deepak15/full/resnet-symbol.json"
)
process.pfDeepBoostedJetTagsAK15WithPuppiDaughters.param_path = (
    "MonoTop/MonoTopSkim/data/deepak15/full/resnet.params"
)

updateJetCollection(
    process,
    labelName="AK15SoftDropSubjetsWithBtagInfo",
    jetSource=cms.InputTag(
        "selectedPatJetsAK15PFPuppiSoftDropPacked", "SubJets", process.name_()
    ),
    jetCorrections=(
        "AK4PFPuppi",
        cms.vstring(["L1FastJet", "L2Relative", "L3Absolute", "L2L3Residual"]),
        "None"
    ),  # Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
    btagDiscriminators=[
        "pfDeepFlavourJetTags:probb",
        "pfDeepFlavourJetTags:probbb",
        "pfDeepFlavourJetTags:problepb",
        "pfDeepFlavourJetTags:probc",
        "pfDeepFlavourJetTags:probuds",
        "pfDeepFlavourJetTags:probg",
        "pfDeepCSVJetTags:probb",
        "pfDeepCSVJetTags:probc",
        "pfDeepCSVJetTags:probudsg",
        "pfDeepCSVJetTags:probbb",
    ],
    explicitJTA=True,  # needed for subjet b tagging
    svClustering=False,  # needed for subjet b tagging (IMPORTANT: Needs to be set to False to disable ghost-association which does not work with slimmed jets)
    fatJets=cms.InputTag(
        "selectedUpdatedPatJetsAK15WithPuppiDaughters", "", process.name_()
    ),  # needed for subjet b tagging
    rParam=1.5,  # needed for subjet b tagging
    algo="ak",  # has to be defined but is not used with svClustering=False
)

# this producer merges the ak15 fat jets (groomed with softdrop) with the softdrop subjets
process.MergeAK15FatjetsAndSubjets = cms.EDProducer(
    "BoostedJetMerger",
    jetSrc=cms.InputTag("selectedPatJetsAK15PFPuppiSoftDrop", "", process.name_()),
    subjetSrc=cms.InputTag("selectedUpdatedPatJetsAK15SoftDropSubjetsWithBtagInfo"),
)

# this producer puts all information from the ak15 fat jets (groomed and ungroomed) and the subjets into one collection containing everything
process.AK15PFPuppiComplete = cms.EDProducer(
    "JetSubstructurePacker",
    jetSrc=cms.InputTag("selectedUpdatedPatJetsAK15WithPuppiDaughters", "", process.name_()),
    distMax=cms.double(1.5),
    algoTags=cms.VInputTag(cms.InputTag("MergeAK15FatjetsAndSubjets")),
    algoLabels=cms.vstring("SoftDropWithBtagInfo"),
    fixDaughters=cms.bool(False),
)

# -------------- AK8 jet stuff -------------- #

# cluster AK8 jets and use PUPPI pileup mitigation method
#jetToolbox(
    #process,
    #"ak8",
    #"ak8JetSubs",
    #"noOutput",
    #PUMethod="Puppi",
    #addPruning=False,
    #addSoftDrop=True,  # add basic grooming
    #addTrimming=False,
    #addFiltering=False,
    #addSoftDropSubjets=True,
    #addPrunedSubjets=False,
    #addNsub=True,
    #maxTau=3,  # add Nsubjettiness tau1, tau2, tau3, tau4
    #JETCorrPayload="AK8PFPuppi",
    #JETCorrLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual'],
    #subJETCorrPayload='AK4PFPuppi',
    #subJETCorrLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual'],
    #runOnMC=not options.isData,
    #dataTier="miniAOD",
    #Cut="pt > 170. && abs(rapidity()) < 2.4",
    #GetJetMCFlavour=not options.isData,
    #bTagDiscriminators=["None"],
    ## GetSubJetMCFlavour=True,
    #addHEPTopTagger=False
#)

# update the new AK8 jet collection with DeepAK8 tagger outputs
#from RecoBTag.MXNet.Parameters.V02.pfDeepBoostedJetPreprocessParams_cfi import pfDeepBoostedJetPreprocessParams as pfDeepBoostedJetPreprocessParamsV02
#from RecoBTag.MXNet.Parameters.V02.pfMassDecorrelatedDeepBoostedJetPreprocessParams_cfi import pfMassDecorrelatedDeepBoostedJetPreprocessParams as pfMassDecorrelatedDeepBoostedJetPreprocessParamsV02
#updateJetCollection(
    #process,
    #jetSource=cms.InputTag("packedPatJetsAK8PFPuppiSoftDrop"),
    #pvSource=cms.InputTag('offlineSlimmedPrimaryVertices'),
    #svSource=cms.InputTag('slimmedSecondaryVertices'),
    #rParam=0.8,
    #jetCorrections=("AK8PFPuppi", cms.vstring(["L1FastJet", "L2Relative", "L3Absolute", "L2L3Residual"]), "None"),
    #btagDiscriminators=pfMassDecorrelatedDeepBoostedJetTagsProbs
    #+ pfMassDecorrelatedDeepBoostedJetTagsMetaDiscrs + pfDeepBoostedJetTagsProbs + pfDeepBoostedJetTagsMetaDiscrs,
    #postfix="AK8WithPuppiDaughters",
#)
#process.pfMassDecorrelatedDeepBoostedJetTagsAK8WithPuppiDaughters.preprocessParams = (
    #pfMassDecorrelatedDeepBoostedJetPreprocessParamsV02
#)
#process.pfMassDecorrelatedDeepBoostedJetTagsAK8WithPuppiDaughters.model_path = (
    #"RecoBTag/Combined/data/DeepBoostedJet/V02/decorrelated/resnet-symbol.json"
    ##"MonoTop/MonoTopSkim/data/deepak8/V02/decorrelated/resnet-symbol.json"
#)
#process.pfMassDecorrelatedDeepBoostedJetTagsAK8WithPuppiDaughters.param_path = (
    #"RecoBTag/Combined/data/DeepBoostedJet/V02/decorrelated/resnet-0000.params"
    ##"MonoTop/MonoTopSkim/data/deepak8/V02/decorrelated/resnet-0000.params"
#)
#process.pfDeepBoostedJetTagsAK8WithPuppiDaughters.preprocessParams = (
    #pfDeepBoostedJetPreprocessParamsV02
#)
#process.pfDeepBoostedJetTagsAK8WithPuppiDaughters.model_path = (
    #"RecoBTag/Combined/data/DeepBoostedJet/V02/full/resnet-symbol.json"
    ##"MonoTop/MonoTopSkim/data/deepak8/V02/full/resnet-symbol.json"
#)
#process.pfDeepBoostedJetTagsAK8WithPuppiDaughters.param_path = (
    #"RecoBTag/Combined/data/DeepBoostedJet/V02/full/resnet-0000.params"
    ##"MonoTop/MonoTopSkim/data/deepak8/V02/full/resnet-0000.params"
#)

#updateJetCollection(
    #process,
    #labelName="AK8SoftDropSubjetsWithBtagInfo",
    #jetSource=cms.InputTag(
        #"selectedPatJetsAK8PFPuppiSoftDropPacked", "SubJets", process.name_()
    #),
    #jetCorrections=(
        #"AK4PFPuppi",
        #cms.vstring(["L1FastJet", "L2Relative", "L3Absolute", "L2L3Residual"]),
        #"None"
    #),  # Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
    #btagDiscriminators=[
        #"pfDeepFlavourJetTags:probb",
        #"pfDeepFlavourJetTags:probbb",
        #"pfDeepFlavourJetTags:problepb",
        #"pfDeepFlavourJetTags:probc",
        #"pfDeepFlavourJetTags:probuds",
        #"pfDeepFlavourJetTags:probg",
        #"pfDeepCSVJetTags:probb",
        #"pfDeepCSVJetTags:probc",
        #"pfDeepCSVJetTags:probudsg",
        #"pfDeepCSVJetTags:probbb",
    #],
    #explicitJTA=True,  # needed for subjet b tagging
    #svClustering=False,  # needed for subjet b tagging (IMPORTANT: Needs to be set to False to disable ghost-association which does not work with slimmed jets)
    #fatJets=cms.InputTag(
        #"selectedUpdatedPatJetsAK8WithPuppiDaughters", "", process.name_()
    #),  # needed for subjet b tagging
    #rParam=0.8,  # needed for subjet b tagging
    #algo="ak",  # has to be defined but is not used with svClustering=False
#)

# this producer merges the ak15 fat jets (groomed with softdrop) with the softdrop subjets
#process.MergeAK8FatjetsAndSubjets = cms.EDProducer(
    #"BoostedJetMerger",
    #jetSrc=cms.InputTag("selectedPatJetsAK8PFPuppiSoftDrop", "", process.name_()),
    #subjetSrc=cms.InputTag("selectedUpdatedPatJetsAK8SoftDropSubjetsWithBtagInfo"),
#)

# this producer puts all information from the ak15 fat jets (groomed and ungroomed) and the subjets into one collection containing everything
#process.AK8PFPuppiComplete = cms.EDProducer(
    #"JetSubstructurePacker",
    #jetSrc=cms.InputTag("selectedUpdatedPatJetsAK8WithPuppiDaughters", "", process.name_()),
    #distMax=cms.double(0.8),
    #algoTags=cms.VInputTag(cms.InputTag("MergeAK8FatjetsAndSubjets")),
    #algoLabels=cms.vstring("SoftDropWithBtagInfo"),
    #fixDaughters=cms.bool(False),
#)

# fat jet tasks during skimming
process.jets_from_skims = cms.Task()
process.jets_from_skims.add(process.MergeAK15FatjetsAndSubjets)
process.jets_from_skims.add(process.AK15PFPuppiComplete)
#process.jets_from_skims.add(process.MergeAK8FatjetsAndSubjets)
#process.jets_from_skims.add(process.AK8PFPuppiComplete)

# -------------- MET corrections and uncertainties -------------- #

# Puppi stuff currently not used, however the (puppi-related) used lines are needed to be in sync with the separated skimming and ntupling workflow

from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import (
    runMetCorAndUncFromMiniAOD,
)
from PhysicsTools.PatAlgos.slimming.puppiForMET_cff import makePuppiesFromMiniAOD

makePuppiesFromMiniAOD(process, False)

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

#runMetCorAndUncFromMiniAOD(
    #process,
    #isData=options.isData,
    #metType="Puppi",
    #postfix="Puppi",
    #jetFlavor="AK4PFPuppi",
#)

process.puppiNoLep.useExistingWeights = True
process.puppi.useExistingWeights = True

# -------------- MET filters -------------- #

process.load("MonoTop.METFilter.METFilter_cfi")
if options.isData:
    process.METFilter.filterData = cms.InputTag("TriggerResults","","RECO")
    process.METFilter.filterNames += ["Flag_eeBadScFilter"]
#print process.METFilter.filterNames

# -------------- E/Gamma stuff -------------- #

from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq

EG_era = None
EG_corrections = None
EG_vid = None
if "2016" in options.dataEra:
    EG_era = "2016-Legacy"
    EG_corrections = True
    EG_vid = True
elif "2017" in options.dataEra:
    EG_era = "2017-Nov17ReReco"
    EG_corrections = True
    EG_vid = True
elif "2018" in options.dataEra:
    EG_era = "2018-Prompt"
    EG_corrections = True
    EG_vid = True
else:
    raise Exception(
        "dataEra "
        + options.dataEra
        + " not supported for Egamma tools: USE dataEra=2016/2017/2018"
    )

setupEgammaPostRecoSeq(
    process,
    runVID=EG_vid,
    runEnergyCorrections=EG_corrections,
    era=EG_era,
    isMiniAOD=True,
)

# -------------- configure skimming module -------------- #

process.load("MonoTop.MonoTopSkim.MonoTopSkim_cfi")
process.MonoTopSkim.isData = cms.bool(options.isData)
process.MonoTopSkim.era = cms.string(options.dataEra)
process.MonoTopSkim.electrons = cms.InputTag("slimmedElectrons", "", process.name_())
process.MonoTopSkim.photons = cms.InputTag("slimmedPhotons", "", process.name_())
process.MonoTopSkim.met = cms.InputTag("slimmedMETs", "", process.name_())
# next lines only needed because of combined skim-ntuple workflow with deactivated AK8 and Puppi stuff
process.MonoTopSkim.met_puppi = cms.InputTag("slimmedMETsPuppi")#, "", process.name_())
process.MonoTopSkim.AK4jets_puppi = cms.InputTag("slimmedJetsPuppi")
process.MonoTopSkim.AK8jets = cms.InputTag("slimmedJetsAK8")

if "2016" in options.dataEra:
    if options.isData:
        process.MonoTopSkim.met_original = cms.InputTag("slimmedMETs", "", "DQM")
        process.MonoTopSkim.met_puppi_original = cms.InputTag("slimmedMETsPuppi", "", "DQM")
    else:
        process.MonoTopSkim.met_original = cms.InputTag("slimmedMETs", "", "PAT")
        process.MonoTopSkim.met_puppi_original = cms.InputTag("slimmedMETsPuppi", "", "PAT")
elif "2017" in options.dataEra:
    if options.isData:
        process.MonoTopSkim.met_original = cms.InputTag("slimmedMETs", "", "PAT")
        process.MonoTopSkim.met_puppi_original = cms.InputTag("slimmedMETsPuppi", "", "PAT")
    else:
        process.MonoTopSkim.met_original = cms.InputTag("slimmedMETs", "", "PAT")
        process.MonoTopSkim.met_puppi_original = cms.InputTag("slimmedMETsPuppi", "", "PAT")
elif "2018" in options.dataEra:
    if options.isData:
        process.MonoTopSkim.met_original = cms.InputTag("slimmedMETs", "", "RECO")
        process.MonoTopSkim.met_puppi_original = cms.InputTag("slimmedMETsPuppi", "", "RECO")
    else:
        process.MonoTopSkim.met_original = cms.InputTag("slimmedMETs", "", "PAT")
        process.MonoTopSkim.met_puppi_original = cms.InputTag("slimmedMETsPuppi", "", "PAT")
else:
    raise Exception(
        "dataEra "
        + options.dataEra
        + " not supported: USE dataEra=2016/2017/2018"
    )


############################### second, ntupling stuff ###############################


# -------------- JES stuff -------------- #

writeNominal = False
systsJES = []
systsJER = []
if options.systematicVariations:
    for var in options.systematicVariations:
        if var.lower() == "nominal":
            writeNominal = True
        elif var == "METUnclEn":
            print "doing unclustered energy uncertainties"
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

# Set up JetCorrections chain to be used in MiniAODHelper
# Note: name is hard-coded to ak4PFchsL1L2L3 and does not
# necessarily reflect actual corrections level
from JetMETCorrections.Configuration.JetCorrectionServices_cff import *

process.ak4PFchsL1Fastjet = cms.ESProducer(
    "L1FastjetCorrectionESProducer",
    level=cms.string("L1FastJet"),
    algorithm=cms.string("AK4PFchs"),
    srcRho=cms.InputTag("fixedGridRhoFastjetAll"),
)
process.ak4PFchsL2Relative = ak4CaloL2Relative.clone(algorithm="AK4PFchs")
process.ak4PFchsL3Absolute = ak4CaloL3Absolute.clone(algorithm="AK4PFchs")
process.ak4PFchsResidual = ak4CaloResidual.clone(algorithm="AK4PFchs")
process.ak4PFchsL1L2L3 = cms.ESProducer(
    "JetCorrectionESChain",
    correctors=cms.vstring(
        "ak4PFchsL1Fastjet", "ak4PFchsL2Relative", "ak4PFchsL3Absolute"
    ),
)
if options.isData:
    process.ak4PFchsL1L2L3.correctors.append(
        "ak4PFchsResidual"
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

# -------------- additional MET filters -------------- #

# run ecalBadCalibReducedMINIAODFilter for 2017 data
if "2017" or "2018" in options.dataEra:
    process.load("RecoMET.METFilters.ecalBadCalibFilter_cfi")

    baddetEcallist = cms.vuint32(
        [872439604,872422825,872420274,872423218,872423215,872416066,872435036,872439336,
         872420273,872436907,872420147,872439731,872436657,872420397,872439732,872439339,
         872439603,872422436,872439861,872437051,872437052,872420649,872421950,872437185,
         872422564,872421566,872421695,872421955,872421567,872437184,872421951,872421694,
         872437056,872437057,872437313,872438182,872438951,872439990,872439864,872439609,
         872437181,872437182,872437053,872436794,872436667,872436536,872421541,872421413,
         872421414,872421031,872423083,872421439]
    )

    process.ecalBadCalibReducedMINIAODFilter = cms.EDFilter(
        "EcalBadCalibFilter",
        EcalRecHitSource=cms.InputTag("reducedEgamma:reducedEERecHits"),
        ecalMinEt=cms.double(50.0),
        baddetEcal=baddetEcallist,
        taggingMode=cms.bool(True),
        debug=cms.bool(False),
    )

# -------------- Puppi quantities -------------- #

#process.patPuppiJetSpecificProducerAK4 = patPuppiJetSpecificProducer.clone(
  #src=cms.InputTag("selectedPatJetsAK4PFPuppi", "", process.name_()),
#)
#updateJetCollection(
   #process,
   #labelName = 'PuppiVarsAK4',
   #jetSource = cms.InputTag("selectedPatJetsAK4PFPuppi", "", process.name_()),
   #)
#process.updatedPatJetsPuppiVarsAK4.userData.userFloats.src = ['patPuppiJetSpecificProducerAK4:puppiMultiplicity', 'patPuppiJetSpecificProducerAK4:neutralPuppiMultiplicity']
#process.updatedPatJetsPuppiVarsAK4.userData.userFunctions = ["userFloat(\"patPuppiJetSpecificProducerAK4:puppiMultiplicity\")","userFloat(\"patPuppiJetSpecificProducerAK4:neutralPuppiMultiplicity\")"]
#process.updatedPatJetsPuppiVarsAK4.userData.userFunctionLabels = ['patPuppiJetSpecificProducer:puppiMultiplicity','patPuppiJetSpecificProducer:neutralPuppiMultiplicity']

#process.patPuppiJetSpecificProducerAK8 = patPuppiJetSpecificProducer.clone(
  #src=cms.InputTag("AK8PFPuppiComplete", "", process.name_()),
#)
#updateJetCollection(
   #process,
   #labelName = 'PuppiVarsAK8',
   #jetSource = cms.InputTag("AK8PFPuppiComplete", "", process.name_()),
   #)
#process.updatedPatJetsPuppiVarsAK8.userData.userFloats.src = ['patPuppiJetSpecificProducerAK8:puppiMultiplicity', 'patPuppiJetSpecificProducerAK8:neutralPuppiMultiplicity']
#process.updatedPatJetsPuppiVarsAK8.userData.userFunctions = ["userFloat(\"patPuppiJetSpecificProducerAK8:puppiMultiplicity\")","userFloat(\"patPuppiJetSpecificProducerAK8:neutralPuppiMultiplicity\")"]
#process.updatedPatJetsPuppiVarsAK8.userData.userFunctionLabels = ['patPuppiJetSpecificProducer:puppiMultiplicity','patPuppiJetSpecificProducer:neutralPuppiMultiplicity']

process.patPuppiJetSpecificProducerAK15 = patPuppiJetSpecificProducer.clone(
  src=cms.InputTag("AK15PFPuppiComplete", "", process.name_()),
)
updateJetCollection(
   process,
   labelName = 'PuppiVarsAK15',
   jetSource = cms.InputTag("AK15PFPuppiComplete", "", process.name_()),
   )
process.updatedPatJetsPuppiVarsAK15.userData.userFloats.src = ['patPuppiJetSpecificProducerAK15:puppiMultiplicity', 'patPuppiJetSpecificProducerAK15:neutralPuppiMultiplicity']
process.updatedPatJetsPuppiVarsAK15.userData.userFunctions = ["userFloat(\"patPuppiJetSpecificProducerAK15:puppiMultiplicity\")","userFloat(\"patPuppiJetSpecificProducerAK15:neutralPuppiMultiplicity\")"]
process.updatedPatJetsPuppiVarsAK15.userData.userFunctionLabels = ['patPuppiJetSpecificProducer:puppiMultiplicity','patPuppiJetSpecificProducer:neutralPuppiMultiplicity']

# -------------- L1 Prefiring issue -------------- #

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

# -------------- run Tau IDs -------------- #

updatedTauName = "slimmedTausNewID"
import RecoTauTag.RecoTau.tools.runTauIdMVA as tauIdConfig
tauIdEmbedder = tauIdConfig.TauIDEmbedder(process, cms, debug = False,
                    updatedTauName = updatedTauName,
                    toKeep = ["2017v2"#,"deepTau2017v2p1"
                               ])
tauIdEmbedder.runTauID()

# -------------- Ele32 trigger path for 2017 -------------- #

if "2017" in options.dataEra:
    process.load("BoostedTTH.Filters.Ele32DoubleL1ToSingleL1_cfi")

# -------------- read outputs from skimming process as input to ntupling process -------------- #

### some standard collections ####
# if not options.isData:
electronCollection = cms.InputTag("slimmedElectrons", "", process.name_())
photonCollection = cms.InputTag("slimmedPhotons", "", process.name_())
muonCollection = cms.InputTag("slimmedMuons")
tauCollection = cms.InputTag("slimmedTausNewID")
METCollection = cms.InputTag("slimmedMETs", "", process.name_())
PuppiMETCollection = cms.InputTag("slimmedMETsPuppi")#cms.InputTag("slimmedMETsPuppi", "", process.name_())
jetCollection = cms.InputTag("selectedPatJetsAK4PFCHS", "", process.name_())
AK8jetCollection = cms.InputTag(
    "slimmedJetsAK8"#"updatedPatJetsPuppiVarsAK8","",process.name_()
)
AK15jetCollection = cms.InputTag(
    "updatedPatJetsPuppiVarsAK15","",process.name_()
)

# -------------- lepton and photon selection -------------- #

# process.load('BoostedTTH.Producers.SelectedLeptonProducers_cfi')
from BoostedTTH.Producers.SelectedLeptonProducers_cfi import *
from BoostedTTH.Producers.SelectedPhotonProducers_cfi import *

if "2016" in options.dataEra:
    process.SelectedElectronProducer = SelectedElectronProducer2016
    process.SelectedElectronProducer.ptMins = [10.0, 20.0, 40.0]
    ###
    process.SelectedMuonProducer = SelectedMuonProducer2016
    process.SelectedMuonProducer.ptMins = [20.0, 20.0, 30.0]
    ###
    process.SelectedPhotonProducer = SelectedPhotonProducer2016
    process.SelectedPhotonProducer.ptMins = [15.0, 200.0]
    ###
    process.SelectedTauProducer = SelectedTauProducer2016
elif "2017" in options.dataEra:
    process.SelectedElectronProducer = SelectedElectronProducer2017
    process.SelectedElectronProducer.ptMins = [10.0, 20.0, 40.0]
    ###
    process.SelectedMuonProducer = SelectedMuonProducer2017
    process.SelectedMuonProducer.ptMins = [20.0, 20.0, 30.0]
    ###
    process.SelectedPhotonProducer = SelectedPhotonProducer2017
    process.SelectedPhotonProducer.ptMins = [15.0, 230.0]
    ###
    process.SelectedTauProducer = SelectedTauProducer2017
elif "2018" in options.dataEra:
    process.SelectedElectronProducer = SelectedElectronProducer2018
    process.SelectedElectronProducer.ptMins = [10.0, 20.0, 40.0]
    ###
    process.SelectedMuonProducer = SelectedMuonProducer2018
    process.SelectedMuonProducer.ptMins = [15.0, 20.0, 30.0]
    ###
    process.SelectedPhotonProducer = SelectedPhotonProducer2018
    process.SelectedPhotonProducer.ptMins = [15.0, 230.0]
    ###
    process.SelectedTauProducer = SelectedTauProducer2018


process.SelectedElectronProducer.electrons = electronCollection
process.SelectedElectronProducer.etaMaxs = [2.5, 2.5, 2.5]
process.SelectedElectronProducer.leptonIDs = ["veto", "tight", "tight"]
process.SelectedElectronProducer.isoConeSizes = ["R03"] * 3
process.SelectedElectronProducer.isoCorrTypes = ["rhoEA"] * 3
process.SelectedElectronProducer.collectionNames = [
    "selectedElectronsLoose",
    "selectedElectronsDL",
    "selectedElectrons",
]
process.SelectedElectronProducer.isData = options.isData
process.SelectedElectronProducer.era = options.dataEra


process.SelectedMuonProducer.muons = muonCollection
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
process.SelectedMuonProducer.useMuonRC = False
process.SelectedMuonProducer.useDeterministicSeeds = False
process.SelectedMuonProducer.isData = options.isData
process.SelectedMuonProducer.era = options.dataEra

process.SelectedPhotonProducer.electrons = cms.InputTag(
    "SelectedElectronProducer:selectedElectronsLoose"
)
process.SelectedPhotonProducer.muons = cms.InputTag(
    "SelectedMuonProducer:selectedMuonsLoose"
)
process.SelectedPhotonProducer.etaMaxs = [2.5, 1.479]
process.SelectedPhotonProducer.IDs = ["loose", "medium"]
process.SelectedPhotonProducer.collectionNames = [
    "selectedPhotonsLoose",
    "selectedPhotons",
]
process.SelectedPhotonProducer.isData = options.isData
process.SelectedPhotonProducer.era = options.dataEra
process.SelectedPhotonProducer.useMonojetSFs = cms.bool(True)

process.SelectedTauProducer.taus = tauCollection
process.SelectedTauProducer.ptMins = [18.]
process.SelectedTauProducer.etaMaxs = [2.3]
process.SelectedTauProducer.leptonIDs = ["veto"]
process.SelectedTauProducer.useDeepTau = cms.bool(False)
process.SelectedTauProducer.isData = options.isData
process.SelectedTauProducer.collectionNames = ["selectedTausLoose"]
process.SelectedTauProducer.electrons = cms.InputTag(
    "SelectedElectronProducer:selectedElectronsLoose"
)
process.SelectedTauProducer.muons = cms.InputTag(
    "SelectedMuonProducer:selectedMuonsLoose"
)

# -------------- apply JES correction to AK4 jets -------------- #

from BoostedTTH.Producers.SelectedJetProducer_cfi import *

process.CorrectedJetProducerAK4 = SelectedJetProducer
process.CorrectedJetProducerAK4.era = cms.string(options.dataEra)
process.CorrectedJetProducerAK4.JetType = cms.string("AK4PFCHS")
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
process.CorrectedJetProducerAK4.jecFileAK4_2016=cms.string("Summer16_07Aug2017_V11_MC_UncertaintySources_AK4PFchs.txt")
process.CorrectedJetProducerAK4.jecFileAK4_2017=cms.string("Fall17_17Nov2017_V32_MC_UncertaintySources_AK4PFchs.txt")
process.CorrectedJetProducerAK4.jecFileAK4_2018=cms.string("Autumn18_V19_MC_UncertaintySources_AK4PFchs.txt")

#process.CorrectedJetProducerLooseAK4 = process.CorrectedJetProducerAK4.clone(
#    jets=cms.InputTag("slimmedJets"),
#    JetID=["none"],
#    leptonJetDr = -1.0,
#    collectionNames = ["correctedJetsLooseAK4"],
#    applyCorrection = False,
#    systematics = [""]
#)

# nominal AK4 jet selection
process.SelectedJetProducerAK4 = process.CorrectedJetProducerAK4.clone(
    jets=cms.InputTag("patSmearedJetsAK4", "", process.name_()),
    applyCorrection=False,
    ptMins=[30],
    etaMaxs=[2.4],
    collectionNames=["selectedJetsAK4"],
    systematics=[""],
    PUJetIDMins=["loose"],
    JetID=["none"],
)

#process.SelectedJetProducerLooseAK4 = process.CorrectedJetProducerLooseAK4.clone(
#    jets=cms.InputTag("patSmearedJetsLooseAK4", "", process.name_()),
#    applyCorrection=False,
#    ptMins=[10.],
#    etaMaxs=[4.7],
#    collectionNames=["selectedJetsLooseAK4"],
#    systematics=[""],
#    PUJetIDMins=["none"],
#    JetID=["none"],
#)

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

# -------------- apply JES correction to AK8 jets -------------- #

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

# -------------- apply JES correction to AK15 jets -------------- #

process.CorrectedJetProducerAK15 = process.CorrectedJetProducerAK8.clone(
    jets=AK15jetCollection,
    JetType="AK15PFPUPPI",
    collectionNames=["correctedJetsAK15"],
    leptonJetDr=1.5,
)

# nominal AK15 jet selection
process.SelectedJetProducerAK15 = process.CorrectedJetProducerAK15.clone(
    jets=cms.InputTag("patSmearedJetsAK15", "", process.name_()),
    ptMins=[160.0],
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

# -------------- smearing of corrected jets -- producers that create the nominal and up/down JER correction -------------- #

# jer shift of nominal sample
#if "2016" in options.dataEra:
#    jerResFileAK4 = "Summer16_25nsV1_MC_PtResolution_AK4PFPuppi.txt"
#    jerResFileAK8 = "Summer16_25nsV1_MC_PtResolution_AK8PFPuppi.txt"
#    jerSFFileAK4 = "Summer16_25nsV1_MC_SF_AK4PFPuppi.txt"
#    jerSFFileAK8 = "Summer16_25nsV1_MC_SF_AK8PFPuppi.txt"
#elif "2017" in options.dataEra:
#    jerResFileAK4 = "Fall17_V3_MC_PtResolution_AK4PFPuppi.txt"
#    jerResFileAK8 = "Fall17_V3_MC_PtResolution_AK8PFPuppi.txt"
#    jerSFFileAK4 = "Fall17_V3_MC_SF_AK4PFPuppi.txt"
#    jerSFFileAK8 = "Fall17_V3_MC_SF_AK8PFPuppi.txt"
#elif "2018" in options.dataEra:
#    jerResFileAK4 = "Autumn18_V7b_MC_PtResolution_AK4PFPuppi.txt"
#    jerResFileAK8 = "Autumn18_V7b_MC_PtResolution_AK8PFPuppi.txt"
#    jerSFFileAK4 = "Autumn18_V7b_MC_SF_AK4PFPuppi.txt"
#    jerSFFileAK8 = "Autumn18_V7b_MC_SF_AK8PFPuppi.txt"
#else:
#    raise Exception("NO JER FILES SPECIFIED: USE dataEra=2016/2017/2018")

process.patSmearedJetsAK4 = cms.EDProducer(
    "SmearedPATJetProducer",
    src=cms.InputTag("CorrectedJetProducerAK4:correctedJetsAK4"),
    enabled=cms.bool(True),  # If False, no smearing is performed
    rho=cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching=cms.bool(
        False
    ),  # If True, always skip gen jet matching and smear jet with a random gaussian
    algopt = cms.string('AK4PFchs_pt'),
    algo = cms.string('AK4PFchs'),
    genJets=cms.InputTag("selectedPatJetsAK4PFCHS", "genJets", process.name_()),
    dRMax=cms.double(0.2),  # = cone size (0.4) / 2
    dPtMaxFactor=cms.double(3),  # dPt < 3 * resolution
    variation=cms.int32(0),  # systematic +1 0 -1 sigma
    debug=cms.untracked.bool(False),
    useDeterministicSeed=cms.bool(
        False
    ),  # default deterministic seeds not used, but our own
    #resolutionFile=cms.FileInPath(
    #    "BoostedTTH/BoostedAnalyzer/data/jerfiles/" + jerResFileAK4
    #),
    #scaleFactorFile=cms.FileInPath(
    #    "BoostedTTH/BoostedAnalyzer/data/jerfiles/" + jerSFFileAK4
    #),
)

#process.patSmearedJetsLooseAK4 = process.patSmearedJetsAK4.clone(
#    src=cms.InputTag("CorrectedJetProducerLooseAK4:correctedJetsLooseAK4"),
#    genJets=cms.InputTag("slimmedGenJets")
#)


process.patSmearedJetsAK8 = cms.EDProducer(
    "SmearedPATJetProducer",
    src=cms.InputTag("CorrectedJetProducerAK8:correctedJetsAK8"),
    enabled=cms.bool(True),  # If False, no smearing is performed
    rho=cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching=cms.bool(
        False
    ),  # If True, always skip gen jet matching and smear jet with a random gaussian
    algopt = cms.string('AK8PFPuppi_pt'),
    algo = cms.string('AK8PFPuppi'),
    genJets=cms.InputTag("selectedPatJetsAK8PFPuppi", "genJets", process.name_()),
    dRMax=cms.double(0.4),  # = cone size (0.8) / 2
    dPtMaxFactor=cms.double(3),  # dPt < 3 * resolution
    variation=cms.int32(0),  # systematic +1 0 -1 sigma
    debug=cms.untracked.bool(False),
    useDeterministicSeed=cms.bool(
        False
    ),  # default deterministic seeds not used, but our own
    #resolutionFile=cms.FileInPath(
    #    "BoostedTTH/BoostedAnalyzer/data/jerfiles/" + jerResFileAK8
    #),
    #scaleFactorFile=cms.FileInPath(
    #    "BoostedTTH/BoostedAnalyzer/data/jerfiles/" + jerSFFileAK8
    #),
)

process.patSmearedJetsAK15 = cms.EDProducer(
    "SmearedPATJetProducer",
    src=cms.InputTag("CorrectedJetProducerAK15:correctedJetsAK15"),
    enabled=cms.bool(True),  # If False, no smearing is performed
    rho=cms.InputTag("fixedGridRhoFastjetAll"),
    skipGenMatching=cms.bool(
        False
    ),  # If True, always skip gen jet matching and smear jet with a random gaussian
    algopt = cms.string('AK8PFPuppi_pt'),
    algo = cms.string('AK8PFPuppi'),
    genJets=cms.InputTag("selectedPatJetsAK15PFPuppi", "genJets", process.name_()),
    dRMax=cms.double(0.75),  # = cone size (1.5) / 2
    dPtMaxFactor=cms.double(3),  # dPt < 3 * resolution
    variation=cms.int32(0),  # systematic +1 0 -1 sigma
    debug=cms.untracked.bool(False),
    useDeterministicSeed=cms.bool(
        False
    ),  # default deterministic seeds not used, but our own
    #resolutionFile=cms.FileInPath(
    #    "BoostedTTH/BoostedAnalyzer/data/jerfiles/" + jerResFileAK8
    #),
    #scaleFactorFile=cms.FileInPath(
    #    "BoostedTTH/BoostedAnalyzer/data/jerfiles/" + jerSFFileAK8
    #),
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

# -------------- load and run the boosted analyzer -------------- #

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
    cms.InputTag("slimmedJets")
    for s in variations
]
process.BoostedAnalyzer.selectedJetsAK8 = [
    AK8jetCollection#cms.InputTag("SelectedJetProducerAK8" + s + ":selectedJetsAK8" + s)
    for s in variations
]
process.BoostedAnalyzer.selectedJetsAK15 = [
    cms.InputTag("SelectedJetProducerAK15" + s + ":selectedJetsAK15" + s)
    for s in variations
]
process.BoostedAnalyzer.correctedMETs = [METCollection] * (len(variations))
process.BoostedAnalyzer.correctedMETsPuppi = [PuppiMETCollection] * (len(variations))

process.BoostedAnalyzer.outfileName = options.outName
if not options.isData:
    process.BoostedAnalyzer.eventWeight = options.weight

process.BoostedAnalyzer.systematics = variations

# block for unclustered energy systematic
if "METUnclEn" in options.systematicVariations:
    process.BoostedAnalyzer.systematics += ["METUnclEnup","METUnclEndown"]
    process.BoostedAnalyzer.selectedJets += ["SelectedJetProducerAK4:selectedJetsAK4","SelectedJetProducerAK4:selectedJetsAK4"]
    process.BoostedAnalyzer.selectedJetsLoose += ["slimmedJets","slimmedJets"]
    process.BoostedAnalyzer.selectedJetsAK8 += ["slimmedJetsAK8","slimmedJetsAK8"]
    process.BoostedAnalyzer.selectedJetsAK15 += ["SelectedJetProducerAK15:selectedJetsAK15","SelectedJetProducerAK15:selectedJetsAK15"]
    process.BoostedAnalyzer.correctedMETs += [METCollection, METCollection]
    process.BoostedAnalyzer.correctedMETsPuppi += [PuppiMETCollection, PuppiMETCollection]

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

process.BoostedAnalyzer.selectionNames = [
    "FilterSelection",
    "VertexSelection",
    "MonoTopSelection",
]

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


# -------------- define final paths to be run -------------- #

# egamma sequence to recalculate electron/photon IDs
process.egamma = cms.Path(process.egammaPostRecoSeq)

# run ele32 trigger path in 2017
if "2017" in options.dataEra:
    process.eletrigger = cms.Path(process.Ele32DoubleL1ToSingleL1)

# met sequences to calculate corrected METs
#process.met = cms.Path(process.fullPatMetSequence)
#process.met_puppi = cms.Path(
    #process.puppiMETSequence * process.fullPatMetSequencePuppi
#)

# final process consists of the following steps: test metfilters -> test skimming selection -> run boostedAnalyzer
process.final = cms.Path(process.METFilter*process.MonoTopSkim*process.BoostedAnalyzer)

# jets during skimming task
process.final.associate(process.jets_from_skims)
#process.final.associate(process.patAlgosToolsTask)

# run ecalBadCalibReducedMINIAODFilter for 2017/2018 data
if "2017" or "2018" in options.dataEra:
    process.BoostedAnalyzer.additionalFilters = cms.VInputTag(
        ["ecalBadCalibReducedMINIAODFilter"]
    )
    process.metfilters = cms.Task(process.ecalBadCalibReducedMINIAODFilter)
    process.final.associate(process.metfilters)

# lepton and photon producers
process.leptons_photons = cms.Task()
process.leptons_photons.add(
    process.SelectedElectronProducer,
    process.SelectedMuonProducer,
    process.SelectedTauProducer,
    process.SelectedPhotonProducer,
)
process.final.associate(process.leptons_photons)

# run tau IDs
process.taus = cms.Path(process.rerunMvaIsolationSequence * process.slimmedTausNewID)

# calculate puppi quantities
process.puppimults = cms.Path(process.patPuppiJetSpecificProducerAK15)#process.patPuppiJetSpecificProducerAK4*process.patPuppiJetSpecificProducerAK8*

# run jet collection producers
process.jets = cms.Task()
#process.jets.add(process.updatedPatJetsPuppiVarsAK4)
#process.jets.add(process.updatedPatJetsPuppiVarsAK8)
process.jets.add(process.updatedPatJetsPuppiVarsAK15)
# process.jets.add(process.MergeAK15FatjetsAndSubjets)
# process.jets.add(process.AK15PFPuppiWithDeepAK15WithSoftDropSubjetsWithDeepJet)
process.jets.add(process.CorrectedJetProducerAK4)
#process.jets.add(process.CorrectedJetProducerLooseAK4)
#process.jets.add(process.CorrectedJetProducerAK8)
process.jets.add(process.CorrectedJetProducerAK15)
# always produce (but not necessarily write to ntuple) nominal case as collections might be needed
for s in [""] + systs:
    process.jets.add(getattr(process, "patSmearedJetsAK4" + s))
    #process.jets.add(getattr(process, "patSmearedJetsLooseAK4" + s))
    #process.jets.add(getattr(process, "patSmearedJetsAK8" + s))
    process.jets.add(getattr(process, "patSmearedJetsAK15" + s))
    process.jets.add(getattr(process, "SelectedJetProducerAK4" + s))
    #process.jets.add(getattr(process, "SelectedJetProducerLooseAK4" + s))
    #process.jets.add(getattr(process, "SelectedJetProducerAK8" + s))
    process.jets.add(getattr(process, "SelectedJetProducerAK15" + s))
#process.jets.add(getattr(process, "patSmearedJetsLooseAK4"))
#process.jets.add(getattr(process, "SelectedJetProducerLooseAK4"))
# process.final.associate(process.patAlgosToolsTask)
process.final.associate(process.jets)

# L1 prefiring issue
if ("2016" in options.dataEra or "2017" in options.dataEra) and (not options.isData):
    process.prefire = cms.Task()
    process.prefire.add(process.prefiringweight)
    process.final.associate(process.prefire)

#print process.dumpPython()



