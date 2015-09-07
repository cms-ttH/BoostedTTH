import FWCore.ParameterSet.Config as cms

# Set Process and Variables
#------------------------------------------------------------------------------------------------------------------------------------
process = cms.Process("analysis")

# set input, output, maxevents
filenames=['/store/user/shwillia/Spring15_HbbSync/ttHTobb_Spring15_HbbSync_NewBoostedJets.root']
outfilename='sync_tth_spring15Hbb'
maxevents=10000000

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 5000

# set global tag
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = 'MCRUN2_74_V9'
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevents))

# allow for automatically loading modules (e.g. HF stuff)
process.options.allowUnscheduled = cms.untracked.bool(True)

# open input
process.source = cms.Source(  "PoolSource",
                              fileNames = cms.untracked.vstring(filenames)
)

#needed for jet corrections
from JetMETCorrections.Configuration.JetCorrectionServices_cff import *
from JetMETCorrections.Configuration.JetCorrectionCondDB_cff import *
process.ak4PFCHSL1Fastjet = cms.ESProducer(
  'L1FastjetCorrectionESProducer',
  level = cms.string('L1FastJet'),
  algorithm = cms.string('AK4PFchs'),
  srcRho = cms.InputTag( 'fixedGridRhoFastjetAll' )
  )
process.ak4PFchsL2Relative = ak4CaloL2Relative.clone( algorithm = 'AK4PFchs' )
process.ak4PFchsL3Absolute = ak4CaloL3Absolute.clone( algorithm = 'AK4PFchs' )
process.ak4PFchsL1L2L3 = cms.ESProducer("JetCorrectionESChain",
  correctors = cms.vstring(
    'ak4PFCHSL1Fastjet',
    'ak4PFchsL2Relative',
    'ak4PFchsL3Absolute')
)

# Supplies PDG ID to real name resolution of MC particles
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
# Needed to determine tt+x category -- is usually run when producing boosted jets in miniAOD 
process.load("BoostedTTH.BoostedProducer.genHadronMatching_cfi")

# load analyzer
process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
# configure the analyzer here!
process.BoostedAnalyzer.outfileName=outfilename
# can be set to true because the necessary tt+x input is generated above
process.BoostedAnalyzer.useGenHadronMatch=True
process.BoostedAnalyzer.useFatJets=True
process.BoostedAnalyzer.dumpSyncExe2=True
# JES systematics for sync
process.BoostedAnalyzer.makeSystematicsTrees=True
# only minimal selections applied
process.BoostedAnalyzer.selectionNames = ["VertexSelection"]
# run some basic processors
process.BoostedAnalyzer.processorNames = cms.vstring("WeightProcessor","MVAVarProcessor","DiLeptonVarProcessor")

# evaluate some triggers but do not use them for the lepton selection
process.BoostedAnalyzer.relevantTriggers = ["HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1","HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1","HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v1","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v1","HLT_Ele27_eta2p1_WP85_Gsf_HT200_v1","HLT_IsoMu24_eta2p1_v1"]
# set this according to your sample
process.BoostedAnalyzer.isData=False
process.BoostedAnalyzer.luminosity = 10000.
process.BoostedAnalyzer.xs = 1.
process.BoostedAnalyzer.nMCEvents = 10000

process.p = cms.Path(process.BoostedAnalyzer)
