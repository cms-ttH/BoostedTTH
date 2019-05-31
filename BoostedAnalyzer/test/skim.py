import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('analysis')
options.register( "isData", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "is it data or MC?" )
options.register( "skipEvents", 0, VarParsing.multiplicity.singleton, VarParsing.varType.int, "Number of events to skip" )
options.register( "dataEra",     "2017",     VarParsing.multiplicity.singleton,     VarParsing.varType.string,     "the era of the data taking period or mc campaign, e.g. '2016B' or '2017'" )
options.register( "globalTag", "94X_mc2017_realistic_v17", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )

options.parseArguments()

if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 10000 # reset for testing
if not options.inputFiles:
    if not options.isData:
        if "2016" in options.dataEra:
            options.inputFiles=['root://xrootd-cms.infn.it//store/mc/RunIISummer16MiniAODv3/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v2/90000/60E75231-23F4-E811-8A2F-0CC47AC52BAE.root']
        elif "2017" in options.dataEra: 
            options.inputFiles=['root://xrootd-cms.infn.it//store/mc/RunIIFall17MiniAODv2/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/100000/484BE1B6-EED2-E811-B121-AC1F6B0DE13A.root']
        elif "2018" in options.dataEra:
            options.inputFiles=['root://xrootd-cms.infn.it//store/mc/RunIIAutumn18MiniAOD/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/40000/EAA9C941-768D-164B-B5C1-C12306823C6E.root']
    else:
        if "2016" in options.dataEra: # CAREFUL: NO 2016 Data Skims ready yet
            options.inputFiles=['root://xrootd-cms.infn.it//store/data/Run2016C/SingleElectron/MINIAOD/17Jul2018-v1/00000/FC3F1149-ED8C-E811-843D-0242AC130002.root']
        elif "2017" in options.dataEra:
            options.inputFiles=['root://xrootd-cms.infn.it//store/data/Run2017B/SingleElectron/MINIAOD/31Mar2018-v1/30000/AC1A4B95-0438-E811-B60D-008CFAE452E0.root']
        elif "2018" in options.dataEra:
            options.inputFiles=['root://xrootd-cms.infn.it//store/data/Run2018B/EGamma/MINIAOD/17Sep2018-v1/60000/37FD0663-1A14-2647-A16B-0ABB87234B43.root']
    
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
        options.globalTag="94X_dataRun2_v10"
    elif "2017" in options.dataEra:
        options.globalTag="94X_dataRun2_v11"
    elif "2018" in options.dataEra:
        if "D" in options.dataEra:
            options.globalTag="102X_dataRun2_Prompt_v13"
        else:
            options.globalTag="102X_dataRun2_Sep2018ABC_v2"
    else:
        raise Exception( "dataEra "+options.dataEra+" not supported for this config: USE dataEra=2016/2017")
elif not options.isData:
    if "2016" in options.dataEra:
        options.globalTag="94X_mcRun2_asymptotic_v3"
    elif "2017" in options.dataEra:
        options.globalTag="94X_mc2017_realistic_v17"
    elif "2018" in options.dataEra:
        options.globalTag="102X_upgrade2018_realistic_v18"
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
    fileName = cms.untracked.string('Skim.root'),
    outputCommands = cms.untracked.vstring(['drop *','keep *_*_*_PAT','keep *_*_*_DQM','keep *_*_*_RECO','keep *_*_*_HLT*','keep *_*_*_SIM',
                    'keep *_*_*_LHE','keep *_matchGen*Hadron_*_*', 'keep *_ak4GenJetsCustom_*_*', 'keep *_categorizeGenTtbar_*_*', 
                    'drop *_*AK8*_*_*', 'drop *_*Puppi*_*_*', 'drop *_*slimmedTausBoosted*_*_*', 'drop *_*oniaPhotonCandidates*_*_*',
                    'drop *_*slimmedMETsNoHF*_*_*']),
   SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring("skimmed")
    )
)

# process.OUT = cms.OutputModule(
#     "PoolOutputModule",
#     fileName = cms.untracked.string('Skim.root'),
#     outputCommands = cms.untracked.vstring([
#         'keep *'
#     ]),
#     SelectEvents = cms.untracked.PSet(
#         SelectEvents = cms.vstring("skimmed")
#     )
# )
process.endpath = cms.EndPath(process.OUT)
