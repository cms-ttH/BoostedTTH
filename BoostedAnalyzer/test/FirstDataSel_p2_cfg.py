#Karims config file

import FWCore.ParameterSet.Config as cms
import os

List_INFILES = ["/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/250/987/00000/787E4EA9-A525-E511-9647-02163E011DE5.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/012/00000/7826B7B0-C425-E511-AB5A-02163E0124CC.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/025/00000/64817816-FC25-E511-9102-02163E011DCE.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/028/00000/705C6746-3C26-E511-92AC-02163E0139CF.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/131/00000/162D2CF4-9D26-E511-9C7D-02163E0136B5.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/134/00000/6A08FC5F-B026-E511-B810-02163E01376A.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/134/00000/72ECD463-B026-E511-BC0F-02163E0134B6.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/143/00000/C0A17602-A926-E511-9896-02163E011805.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/147/00000/E0D3E1C4-A626-E511-A5CA-02163E01383D.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/149/00000/0A723D09-AD26-E511-88C7-02163E013852.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/150/00000/1C03AABC-A826-E511-8068-02163E0133DC.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/153/00000/8CC958E7-AC26-E511-B270-02163E0133D1.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/155/00000/2A6050CD-AE26-E511-B679-02163E014531.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/156/00000/DACB2C56-B026-E511-B316-02163E011889.root","/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/160/00000/1E958638-9926-E511-9869-02163E0133F9.root"]

List_FileNames=[]
for fn in List_INFILES[5:9]:
  List_FileNames.append(fn)

process = cms.Process("boosted")
# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GR_P_V56'

#process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
#process.load("BoostedTTH.BoostedProducer.genHadronMatching_cfi")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(999999999) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )
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
                              #fileNames= cms.untracked.vstring("root://xrootd-cms.infn.it///store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/134/00000/6A08FC5F-B026-E511-B810-02163E01376A.root")
                              #fileNames= cms.untracked.vstring("/store/data/Run2015B/SingleMu/MINIAOD/PromptReco-v1/000/251/134/00000/6A08FC5F-B026-E511-B810-02163E01376A.root")
)
#import PhysicsTools.PythonAnalysis.LumiList as LumiList
#process.source.lumisToProcess = LumiList.LumiList(filename = '/nfs/dust/cms/user/kelmorab/json_DCSONLY_Run2015B.txt').getVLuminosityBlockRange()


#process.content = cms.EDAnalyzer("EventContentAnalyzer")
process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
process.BoostedAnalyzer.useFatJets=False
#process.BoostedAnalyzer.disableObjectSelections=False
process.BoostedAnalyzer.outfileName = cms.string("/nfs/dust/cms/user/kelmorab/FirstDataTest_part2")
process.BoostedAnalyzer.selectionNames = ["VertexSelection","LeptonSelection1"]
process.BoostedAnalyzer.processorNames = cms.vstring("WeightProcessor","MVAVarProcessor","DiLeptonVarProcessor")
process.BoostedAnalyzer.era = cms.string("2015_74x")
process.BoostedAnalyzer.analysisType = cms.string("LJ")
process.BoostedAnalyzer.luminosity = cms.double(10000.0)
process.BoostedAnalyzer.sampleID = cms.int32(int(9125))
process.BoostedAnalyzer.xs = cms.double(float(99999.9))
process.BoostedAnalyzer.nMCEvents = cms.int32(int(100))
process.BoostedAnalyzer.isData = cms.bool(True)
process.BoostedAnalyzer.useGenHadronMatch = cms.bool(False)
process.BoostedAnalyzer.systematicType = cms.string("nominal")
process.BoostedAnalyzer.muonTriggers=["HLT_IsoMu24_eta2p1_v2"]
process.BoostedAnalyzer.electronTriggers=["HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v1"]
#process.BoostedAnalyzer.makeSystematicsTrees=cms.bool(True)

process.p = cms.Path(process.BoostedAnalyzer)
