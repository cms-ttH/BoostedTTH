import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('analysis')
options.register( "isData", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "is it data or MC?" )
options.register( "skipEvents", 0, VarParsing.multiplicity.singleton, VarParsing.varType.int, "Number of events to skip" )
options.register( "dataEra",     "2017",     VarParsing.multiplicity.singleton,     VarParsing.varType.string,     "the era of the data taking period or mc campaign, e.g. '2016B' or '2017'" )

options.parseArguments()
if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 10000 # reset for testing

if not options.inputFiles:
    if not options.isData:
        options.inputFiles=['root://xrootd-cms.infn.it//store/mc/RunIIFall17MiniAODv2/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/10000/968BB369-8542-E811-A8CF-002481CFE864.root']
    else:
        options.inputFiles=['root://xrootd-cms.infn.it//store/data/Run2017B/SingleElectron/MINIAOD/31Mar2018-v1/90000/6052A1DF-9B37-E811-AA01-008CFA110C88.root']

process = cms.Process("p")
#set some defaults


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(options.inputFiles),
                            skipEvents=cms.untracked.uint32(int(options.skipEvents))

)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

# messages
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

if options.isData:
    if "2016" in options.dataEra:
        process.GlobalTag.globaltag="94X_dataRun2_v10"
    elif "2017" in options.dataEra:
        process.GlobalTag.globaltag="94X_dataRun2_v11"
    else:
        raise Exception( "dataEra "+options.dataEra+" not supported for this config: USE dataEra=2016/2017")
elif not options.isData:
    if "2016" in options.dataEra:
        process.GlobalTag.globaltag="94X_mcRun2_asymptotic_v3"
    elif "2017" in options.dataEra:
        process.GlobalTag.globaltag="94X_mc2017_realistic_v17"
    else:
        raise Exception( "dataEra "+options.dataEra+" not supported for this config: USE dataEra=2016/2017")
else:
    raise Exception("Problem with isData option! This should never happen!")

process.load("CondCore.CondDB.CondDB_cfi")

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
if options.isData==True:
  process.ak4PFchsL1L2L3.correctors.append('ak4PFchsResidual') # add residual JEC for data


process.load("BoostedTTH.BoostedAnalyzer.LeptonJetsSkim_cfi")
process.LeptonJetsSkim.isData=cms.bool(options.isData)
process.LeptonJetsSkim.era=options.dataEra 

process.skimmed=cms.Path(process.LeptonJetsSkim)

process.OUT = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('SkimTest2.root'),
    outputCommands = cms.untracked.vstring(['drop *','keep *_*_*_PAT','keep *_*_*_RECO','keep *_*_*_HLT*','keep *_*_*_SIM','keep *_*_*_LHE','keep *_matchGen*Hadron_*_*', 'keep *_ak4GenJetsCustom_*_*', 'keep *_categorizeGenTtbar_*_*', 
            'drop *_*AK8*_*_*', 'drop *_*Puppi*_*_*', 'drop *_*slimmedTausBoosted*_*_*', 'drop *_*oniaPhotonCandidates*_*_*', 'drop *_*slimmedMETsNoHF*_*_*']),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring("skimmed")
    )
)
process.endpath = cms.EndPath(process.OUT)
