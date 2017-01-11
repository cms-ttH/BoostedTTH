import FWCore.ParameterSet.Config as cms
import os


ISDATA=os.getenv("ISDATA")
XS = os.getenv("XS")
if XS==None:
	XS=999999.9
MCEvents = os.getenv("MCEVENTS")
if MCEvents==None:
	MCEvents=100
ERA = os.getenv("ERA")
if ERA==None:
	ERA="2015_74x"
INSAMPLE = os.getenv("INSAMPLE")
if INSAMPLE==None:
	INSAMPLE="9125"
DOSYSTEMATICS=os.getenv("DOSYSTEMATICS")
OUTFILE = os.getenv("OUTFILE_NAME")
INFILE = os.getenv("FILE_NAMES")

print ISDATA, type(ISDATA)
List_FileNames=[]
if INFILE!=None:
	List_INFILES = INFILE.split(" ")
	for fn in List_INFILES:
	  List_FileNames.append(fn)
#	  List_FileNames.append("file:"+fn)
	#print List_FileNames
        if List_FileNames[-1]=="" or List_FileNames[-1]==" ":
		List_FileNames.pop()
	#print List_FileNames

process = cms.Process("boosted")
# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

if ISDATA=="TRUE":
  process.GlobalTag.globaltag = 'GR_P_V56'
elif ISDATA=="FALSE" or ISDATA==None:
  process.GlobalTag.globaltag = 'MCRUN2_74_V9'

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("BoostedTTH.Producers.genHadronMatching_cfi")

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

if INFILE==None:
	process.source = cms.Source(  "PoolSource",
			      fileNames = cms.untracked.vstring()
				)
else:
	print List_FileNames
	process.source = cms.Source(  "PoolSource",
			      fileNames = cms.untracked.vstring(List_FileNames)
				)

## use this to use lumi mask in cmsRun

#import FWCore.PythonUtilities.LumiList as LumiList
#import FWCore.ParameterSet.Types as CfgTypes
#process.source.lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange())
#JSONfile = '/nfs/dust/cms/user/kelmorab/json_DCSONLY_Run2015B.txt'
#myLumis = LumiList.LumiList(filename = JSONfile).getCMSSWString().split(',')
#process.source.lumisToProcess.extend(myLumis)


process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
process.BoostedAnalyzer.useFatJets=False
#process.BoostedAnalyzer.disableObjectSelections=False
if OUTFILE!=None:
	process.BoostedAnalyzer.outfileName = OUTFILE
process.BoostedAnalyzer.selectionNames = ["VertexSelection","LeptonSelection"]
process.BoostedAnalyzer.processorNames = cms.vstring("WeightProcessor","MVAVarProcessor","DiLeptonVarProcessor","MCMatchVarProcessor","BDTVarProcessor")
process.BoostedAnalyzer.era = ERA
process.BoostedAnalyzer.analysisType = cms.string("LJ")
process.BoostedAnalyzer.luminosity = cms.double(10000.0)
process.BoostedAnalyzer.sampleID = cms.int32(int(INSAMPLE))
process.BoostedAnalyzer.xs = cms.double(float(XS))
process.BoostedAnalyzer.nMCEvents = cms.int32(int(MCEvents))
process.BoostedAnalyzer.dumpSyncExe2=True
if ISDATA=="TRUE":
	process.BoostedAnalyzer.isData = cms.bool(True)
	process.BoostedAnalyzer.useGenHadronMatch = cms.bool(False)
elif ISDATA==None:
	process.BoostedAnalyzer.isData = cms.bool(False)
	process.BoostedAnalyzer.useGenHadronMatch = cms.bool(True)
elif ISDATA=="FALSE":
	process.BoostedAnalyzer.isData = cms.bool(False)
	process.BoostedAnalyzer.useGenHadronMatch = cms.bool(True)
if DOSYSTEMATICS==None:
	process.BoostedAnalyzer.makeSystematicsTrees=cms.bool(False)
elif DOSYSTEMATICS=="FALSE":
	process.BoostedAnalyzer.makeSystematicsTrees=cms.bool(False)
elif DOSYSTEMATICS=="TRUE":
	process.BoostedAnalyzer.makeSystematicsTrees=cms.bool(True)
process.BoostedAnalyzer.muonTriggers=["any"]
process.BoostedAnalyzer.electronTriggers=["any"]

if ISDATA==None or ISDATA=="FALSE":
	process.p = cms.Path(process.ak4GenJetsCustom*process.selectedHadronsAndPartons*process.genJetFlavourPlusLeptonInfos*process.matchGenBHadron*process.matchGenCHadron*process.BoostedAnalyzer)
elif ISDATA=="TRUE":
	process.p = cms.Path(process.BoostedAnalyzer)








