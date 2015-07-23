import FWCore.ParameterSet.Config as cms
import os

# Set Process and Variables
#------------------------------------------------------------------------------------------------------------------------------------
process = cms.Process("boosted")

# grid-control variables
gc = {}
gc['nickname'] = '__NICK__'
gc['filenames'] = '__FILE_NAMES__'
gc['outfilename'] = '__OUT_FILE__'
gc['skip'] = '__SKIP_EVENTS__'
gc['max'] = '__MAX_EVENTS__'

gc['sampletype'] = '__SAMPLE_TYPE__'
gc['xs'] = '__XS__'
gc['mcevents'] = '__MCEVENTS__'

# envoirnment variables
env = {}
env['nickname'] = os.getenv('NICK_NAME')
env['filenames'] = os.getenv('FILE_NAMES')
env['outfilename'] = os.getenv('OUTFILE_NAME')
env['skip'] = os.getenv('SKIP_EVENTS')
env['max'] = os.getenv('MAX_EVENTS')

env['sampletype'] = os.getenv('SAMPLE_TYPE')
env['xs'] = os.getenv('XS')
env['mcevents'] = os.getenv('MCEVENTS')

# default variables
default = {}
default['nickname'] = 'MC_Pythia_TTHbb'
#default['filenames'] = 'file:/pnfs/desy.de/cms/tier2/store/user/shwillia/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/BoostedTTH_MiniAOD/150223_082502/0000/BoostedMiniAOD_4.root'
#default['filenames'] = 'file:/pnfs/desy.de/cms/tier2/store/user/shwillia/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola/BoostedTTH_MiniAOD/150421_084810/0000/BoostedTTH_MiniAOD_4.root'
#default['filenames'] = 'file:/pnfs/desy.de/cms/tier2/store/user/shwillia/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/BoostedTTH_MiniAOD/150505_132803/0000/BoostedTTH_MiniAOD_6.root'
#default['filenames'] = 'file:/pnfs/desy.de/cms/tier2/store/user/shwillia/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/BoostedTTH_MiniAOD/150227_111650/0000/BoostedTTH_MiniAOD_15.root'
default['filenames'] = 'file:/nfs/dust/cms/user/shwillia/CMSSW_7_4_6_patch6/src/BoostedTTH_MiniAOD.root'
default['outfilename'] = None
default['skip'] = '0'
default['max'] = '1000'

default['sampletype'] = '9125'
default['xs'] = '831.76'
default['mcevents'] = '25446993'

# fill in default values if not set by gc
values = gc.copy()
for key, value in values.iteritems():
    if value.startswith('__'):
        if env[key] is None:
            values[key] = default[key]
        else:
            values[key] = env[key]

# convert strings
values['filenames'] = values['filenames'].strip(',')
values['filenames'] = map(lambda s: s.strip('" '), values['filenames'].split(","))

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'PHYS14_25_V2::All'

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(int(values['max'])))

process.source = cms.Source(  "PoolSource",
                              fileNames = cms.untracked.vstring(values['filenames']),
                              skipEvents = cms.untracked.uint32(int(values['skip']))
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

process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_Analysis_cfi")
process.BoostedAnalyzer.useFatJets=True
if values['outfilename'] is not None:
    process.BoostedAnalyzer.outfileName=values['outfilename']
if values['sampletype'] is not None:
    process.BoostedAnalyzer.sampleID=cms.int32(int(values['sampletype']))
if values['xs'] is not None:
    process.BoostedAnalyzer.xs=cms.double(float(values['xs']))
if values['mcevents'] is not None:
    process.BoostedAnalyzer.nMCEvents=cms.int32(int(values['mcevents']))
    
#process.content = cms.EDAnalyzer("EventContentAnalyzer")
#process.p = cms.Path(process.content*process.BoostedAnalyzer)

process.p = cms.Path(process.BoostedAnalyzer)
