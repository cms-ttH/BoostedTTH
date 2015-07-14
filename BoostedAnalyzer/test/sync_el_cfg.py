import FWCore.ParameterSet.Config as cms
import os
values={}
values['filenames']=['file:/pnfs/desy.de/cms/tier2/store/user/hmildner/ttjets_phys14_20bx25_withfatjetsandtthf.root']
values['outfilename']="sync_el_2"
values['sampleID']="9125"
values['xs']="0.5"
values['mcevents']="100000"

filenamestring=os.environ.get("FILENAMES")
if filenamestring != None:
    values['filenames']=filenamestring.split(' ')
if os.environ.get("OUTFILENAME") != None:
    values['outfilename']=os.environ.get("OUTFILENAME")
if os.environ.get("SAMPLEID") != None:
    values['sampleID']=os.environ.get("SAMPLEID")
if os.environ.get("XS") != None:
    values['xs']=os.environ.get("XS")
if os.environ.get("MCEVENTS") != None:
    values['mcevents']=os.environ.get("MCEVENTS")



process = cms.Process("analyze")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'PHYS14_25_V2::All'

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)

process.source = cms.Source(  "PoolSource",
                              fileNames = cms.untracked.vstring(values['filenames']),      
)

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
#process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
#process.load("BoostedTTH.BoostedAnalyzer.genHadronMatching_cfi")

process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
process.BoostedAnalyzer.useFatJets=False
process.BoostedAnalyzer.useGenHadronMatch=True
process.BoostedAnalyzer.dumpSyncExe=True
if values['outfilename'] is not None:
    process.BoostedAnalyzer.outfileName=values['outfilename']
if values['sampleID'] is not None:
    process.BoostedAnalyzer.sampleID=cms.int32(int(values['sampleID']))
if values['xs'] is not None:
    process.BoostedAnalyzer.xs=cms.double(float(values['xs']))
if values['mcevents'] is not None:
    process.BoostedAnalyzer.nMCEvents=cms.int32(int(values['mcevents']))
    

process.BoostedAnalyzer.processorNames = []#["WeightProcessor","BDTVarProcessor","MVAVarProcessor"]
process.BoostedAnalyzer.selectionNames = ["VertexSelection","LeptonSelection1","LeptonSelection3","LeptonSelection2","LeptonSelection4","4JetSelection","2TagSelection"]
process.BoostedAnalyzer.channel=cms.string("el")
#process.content = cms.EDAnalyzer("EventContentAnalyzer")
#process.p = cms.Path(process.content *process.BoostedAnalyzer)
process.p = cms.Path(process.BoostedAnalyzer)
