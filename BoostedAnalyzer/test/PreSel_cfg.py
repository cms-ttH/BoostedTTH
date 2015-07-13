#Karims config file

import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("boosted")
OUTFILE = os.getenv("OUTFILE_NAME")
XS = os.getenv("XS")
MCEvents = os.getenv("MCEVENTS")
ERA = os.getenv("ERA")
INSAMPLE = os.getenv("INSAMPLE")
INFILE = os.getenv("FILE_NAMES")
SYSTEMATIC=os.getenv("SYSTEMATIC")

List_INFILES = INFILE.split(" ")
List_FileNames=[]
for fn in List_INFILES:
  List_FileNames.append("file:"+fn)
print List_FileNames
List_FileNames.pop()
print List_FileNames

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = 'MCRUN2_74_V9'
#process.GlobalTag.globaltag = 'auto:run2_mc'

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("BoostedTTH.BoostedProducer.genHadronMatching_cfi")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(999999999) )

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


#process.source = cms.Source(  "PoolSource",
#                              #fileNames = cms.untracked.vstring('file:/pnfs/desy.de/cms/tier2/store/user/hmildner/ttjets_phys14_20bx25_withfatjets_v2.root')
#			      fileNames = cms.untracked.vstring('file:'+INFILE)
#)
process.source = cms.Source(  "PoolSource",
			      fileNames = cms.untracked.vstring(List_FileNames)
                              #fileNames= = cms.untracked.vstring("root://xrootd-cms.infn.it///store/mc/RunIISpring15DR74/ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/80000/002AEC99-1003-E511-A57F-0CC47A4DEE12.root")
)
print "starz" 
process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
process.BoostedAnalyzer.useFatJets=False
process.BoostedAnalyzer.outfileName = OUTFILE
process.BoostedAnalyzer.selectionNames = ["VertexSelection","LeptonSelection","4JetSelection","2TagSelection"]
process.BoostedAnalyzer.processorNames = cms.vstring("WeightProcessor","MCMatchVarProcessor","MVAVarProcessor","BDTVarProcessor")
process.BoostedAnalyzer.era = ERA
process.BoostedAnalyzer.analysisType = cms.string("LJ")
process.BoostedAnalyzer.luminosity = cms.double(10000.0)
process.BoostedAnalyzer.sampleID = cms.int32(int(INSAMPLE))
process.BoostedAnalyzer.xs = cms.double(float(XS))
process.BoostedAnalyzer.nMCEvents = cms.int32(int(MCEvents))
process.BoostedAnalyzer.isData = cms.bool(False)
process.BoostedAnalyzer.useGenHadronMatch = cms.bool(True)
#process.BoostedAnalyzer.systematicType = SYSTEMATIC
process.BoostedAnalyzer.muonTriggers=["any"]
process.BoostedAnalyzer.electronTriggers=["any"]
process.BoostedAnalyzer.dumpSyncExe=cms.bool(False)
process.BoostedAnalyzer.makeSystematicsTrees=cms.bool(True)

process.p = cms.Path(process.ak4GenJetsCustom*process.selectedHadronsAndPartons*process.genJetFlavourPlusLeptonInfos*process.matchGenBHadron*process.matchGenCHadron*process.BoostedAnalyzer)
