import FWCore.ParameterSet.Config as cms
import sys
import os

# To execute test, run
#  cmsRun validateJECUncertainty_cfg.py outputFile=validateJECUnc maxEvents=100 inputFiles=/store/mc/RunIISpring16MiniAODv2/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/MINIAODSIM/premix_withHLT_80X_mcRun2_asymptotic_v14-v1/100000/00B939E4-F982-E611-AB1C-F46D042E833B.root

# parse command-line arguments
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCommandLineParsing
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
# The following variables are already defined in VarParsing class:
# maxEvents: singleton, int; default = -1
# inputFiles: (comma separated, no spaces!) list, string: default empty
options.register( "outName", "testrun", VarParsing.multiplicity.singleton, VarParsing.varType.string, "name and path of the output files (without extension)" )
options.register( "globalTag", "80X_mcRun2_asymptotic_2016_miniAODv2_v1", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )
options.parseArguments()


# re-set some defaults
if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 1000 # reset for testing

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
                              fileNames = cms.untracked.vstring(options.inputFiles)
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

#=================================== JEC from DB file for data ===============
process.GlobalTag.toGet.append(
    cms.PSet(
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        record = cms.string('JetCorrectionsRecord'),
        tag    = cms.string('JetCorrectorParametersCollection_Fall15_25nsV2_MC_AK4PFchs'),
        label  = cms.untracked.string('AK4PFchs')
)
)
process.GlobalTag.toGet.append(
    cms.PSet(
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        record = cms.string('JetCorrectionsRecord'),
    tag    = cms.string('JetCorrectorParametersCollection_Fall15_25nsV2_MC_AK8PFchs'),
        label  = cms.untracked.string('AK8PFchs')
    )
)

#===============================================================
#
process.load('BoostedTTH.Producers.SelectedLeptonProducers_cfi')
process.SelectedElectronProducer.ptMins=[15.,25.,30.]
process.SelectedElectronProducer.etaMaxs=[2.4,2.4,2.1]
process.SelectedElectronProducer.leptonIDs=["electronNonTrigMVAid80"]*3
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
#process.load("BoostedTTH.Producers.CorrectedMETproducer_cfi")



# load and run the boosted analyzer
process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")

systs=[
    "",
    "JESup","JESdown",
    "JESAbsoluteScaleup","JESAbsoluteScaledown"
]
process.SelectedJetProducer.systematics=systs

process.BoostedAnalyzer.selectedJets=[cms.InputTag("SelectedJetProducer:selectedJets"+s) for s in systs]
process.BoostedAnalyzer.selectedJetsLoose=[cms.InputTag("SelectedJetProducer:selectedJetsLoose"+s) for s in systs]
process.BoostedAnalyzer.selectedJetsDL=[cms.InputTag("SelectedJetProducer:selectedJetsDL"+s) for s in systs]
process.BoostedAnalyzer.selectedJetsLooseDL=[cms.InputTag("SelectedJetProducer:selectedJetsLooseDL"+s) for s in systs]

process.BoostedAnalyzer.useGenHadronMatch = False
process.BoostedAnalyzer.useFatJets=False
process.BoostedAnalyzer.outfileName=options.outName
process.BoostedAnalyzer.eventWeight = 1.
process.BoostedAnalyzer.systematics=process.SelectedJetProducer.systematics
process.BoostedAnalyzer.muonTriggers = "None",
process.BoostedAnalyzer.electronTriggers = "None",
process.BoostedAnalyzer.channel = "both"
process.BoostedAnalyzer.bTagSFs.AllowJetsOutOfBinning = cms.bool(True)

### electron MVA ####
# Load the producer for MVA IDs
process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")
process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.BoostedAnalyzer.minJets = [4]
process.BoostedAnalyzer.maxJets = [-1]
process.BoostedAnalyzer.minTags = [-1]
process.BoostedAnalyzer.maxTags = [-1]
#process.BoostedAnalyzer.minJetsForMEM = 4
#process.BoostedAnalyzer.minTagsForMEM = 3
#process.BoostedAnalyzer.doJERsystematic = False

process.BoostedAnalyzer.selectionNames = []

process.BoostedAnalyzer.processorNames = ["GenJetOrderedJetCollectionProcessor"]


# Needed to determine tt+x category
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("BoostedTTH.BoostedProducer.genHadronMatching_cfi")
process.produceGenInfo = cms.Sequence(
    process.genParticlesForJetsNoNu *
    process.ak4GenJetsCustom *
    process.selectedHadronsAndPartons *
    process.genJetFlavourInfos *
    process.matchGenBHadron *
    process.matchGenCHadron *
    process.categorizeGenTtbar
)

process.p = cms.Path(process.electronMVAValueMapProducer
                     *process.SelectedElectronProducer
                     *process.SelectedMuonProducer
 #                    *process.content
                     *process.SelectedJetProducer
#                     *process.CorrectedMETproducer
                     *process.produceGenInfo
                     *process.BoostedAnalyzer
                     )
