import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox
from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection


options = VarParsing ('analysis')
options.register( "isData", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "is it data or MC?" )
options.register( "skipEvents", 0, VarParsing.multiplicity.singleton, VarParsing.varType.int, "Number of events to skip" )
options.register( "globalTag", "102X_upgrade2018_realistic_v18", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )
options.parseArguments()

if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 1001 # reset for testing

if not options.inputFiles:
    if not options.isData:
        options.inputFiles=['root://xrootd-cms.infn.it///store/mc/RunIIAutumn18MiniAOD/ZJetsToNuNu_HT-400To600_13TeV-madgraph/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/260000/5423A771-D3D4-BB4D-8289-91DF6108FA78.root']
    else:
        options.inputFiles=['root://xrootd-cms.infn.it///store/data/Run2018B/MET/MINIAOD/17Sep2018-v1/100000/84F4D3C4-7275-834A-ADDF-E34194D17EB3.root']

process = cms.Process("skim")

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(options.inputFiles),
                            skipEvents=cms.untracked.uint32(int(options.skipEvents))

)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

# messages
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = options.globalTag
process.load("CondCore.CondDB.CondDB_cfi")

# these are needed to write the new AK15 jet collections - dont know why ...
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.Geometry.GeometryRecoDB_cff')
#process.load('RecoVertex.AdaptiveVertexFinder.inclusiveCandidateVertexFinder_cfi')
#process.load('RecoVertex.AdaptiveVertexFinder.candidateVertexMerger_cfi')
#process.load('RecoVertex.AdaptiveVertexFinder.candidateVertexArbitrator_cfi')
#process.load('RecoVertex.AdaptiveVertexFinder.inclusiveVertexing_cff')

jetToolbox( process, 'ak15', 'ak15JetSubs', 'noOutput',
  PUMethod='Puppi',
  addPruning=True, addSoftDrop=True ,           # add basic grooming
  addTrimming=True, addFiltering=True,
  addSoftDropSubjets=True,
  addPrunedSubjets=True,
  addNsub=True, maxTau=4,                       # add Nsubjettiness tau1, tau2, tau3, tau4
  JETCorrPayload = 'AK8PFPuppi', #JETCorrLevels = ['L2Relative', 'L3Absolute'],
  runOnMC=not options.isData,
  miniAOD=True,
  #bTagDiscriminators=[
            #'pfDeepCSVJetTags:probb',
			#'pfDeepCSVJetTags:probbb',
			#'pfDeepCSVJetTags:probc',
			#'pfDeepCSVJetTags:probudsg',
            #'pfDeepFlavourJetTags:probb',
			#'pfDeepFlavourJetTags:probbb',
			#'pfDeepFlavourJetTags:problepb',
			#'pfDeepFlavourJetTags:probc',
			#'pfDeepFlavourJetTags:probuds',
			#'pfDeepFlavourJetTags:probg',    
  #],
  Cut='pt > 100 && abs(eta) < 2.5',
  GetJetMCFlavour=True,
  #GetSubJetMCFlavour=True,
  addHEPTopTagger=True
  )

updateJetCollection(
   process,
   jetSource = cms.InputTag('selectedPatJetsAK15PFPuppiPrunedSubjets'),
   pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
   svSource = cms.InputTag('slimmedSecondaryVertices'),
   jetCorrections = ('AK4PFPuppi', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None'),
   btagDiscriminators = [
      'pfDeepFlavourJetTags:probb',
      'pfDeepFlavourJetTags:probbb',
      'pfDeepFlavourJetTags:problepb',
      'pfDeepFlavourJetTags:probc',
      'pfDeepFlavourJetTags:probuds',
      'pfDeepFlavourJetTags:probg'
      ],
   postfix='AK15PFPuppiPrunedSubjetsNewDFTraining'
)
   
updateJetCollection(
   process,
   jetSource = cms.InputTag('selectedPatJetsAK15PFPuppiSoftDropSubjets'),
   pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
   svSource = cms.InputTag('slimmedSecondaryVertices'),
   jetCorrections = ('AK4PFPuppi', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None'),
   btagDiscriminators = [
      'pfDeepFlavourJetTags:probb',
      'pfDeepFlavourJetTags:probbb',
      'pfDeepFlavourJetTags:problepb',
      'pfDeepFlavourJetTags:probc',
      'pfDeepFlavourJetTags:probuds',
      'pfDeepFlavourJetTags:probg'
      ],
   postfix='AK15PFPuppiSoftDropSubjetsNewDFTraining'
)

process.load("BoostedTTH.BoostedAnalyzer.LeptonJetsSkim_cfi")
process.LeptonJetsSkim.isData=cms.bool(options.isData)

process.content = cms.EDAnalyzer("EventContentAnalyzer")


process.OUT = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('Skim.root'),
    outputCommands = cms.untracked.vstring(['drop *','keep *_*_*_PAT','keep *_*_*_RECO','keep *_*_*_HLT*','keep *_*_*_SIM','keep *_*_*_LHE','keep *_selected*AK15*_*_skim',
        'drop *_selected*AK15*_*calo*_skim', 
        'drop *_selected*AK15*_*tagInfos*_skim',
        ]),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring("skim")
    )
)
process.skim = cms.Path()
#process.skim*=process.content
process.skim*=process.LeptonJetsSkim
process.write_skimmed = cms.EndPath(process.OUT)

#print process.dumpPython()
