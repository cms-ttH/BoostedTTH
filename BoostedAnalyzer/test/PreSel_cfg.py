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
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'PHYS14_25_V2::All'

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(999999999) )

from JetMETCorrections.Configuration.JetCorrectionServices_cff import *
#from JetMETCorrections.Configuration.JetCorrectionCondDB_cff import *

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
)

process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
process.BoostedAnalyzer.useFatJets=True
process.BoostedAnalyzer.disableObjectSelections=False
process.BoostedAnalyzer.outfileName = OUTFILE
process.BoostedAnalyzer.selectionNames = ["VertexSelection","LeptonSelection"]
process.BoostedAnalyzer.processorNames = cms.vstring("WeightProcessor","MCMatchVarProcessor","MVAVarProcessor","BDTVarProcessor","BoostedMCMatchVarProcessor","BoostedJetVarProcessor","BoostedTopHiggsVarProcessor","BoostedTopVarProcessor","BoostedHiggsVarProcessor")
process.BoostedAnalyzer.era = ERA
process.BoostedAnalyzer.analysisType = cms.string("LJ")
process.BoostedAnalyzer.luminosity = cms.double(10000.0)
process.BoostedAnalyzer.sampleID = cms.int32(int(INSAMPLE))
process.BoostedAnalyzer.xs = cms.double(float(XS))
process.BoostedAnalyzer.nMCEvents = cms.int32(int(MCEvents))
process.BoostedAnalyzer.isData = cms.bool(False)
process.BoostedAnalyzer.useGenHadronMatch = cms.bool(True)
process.BoostedAnalyzer.systematicType = SYSTEMATIC


process.p = cms.Path(process.BoostedAnalyzer)
