import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("analysis")

# Start of configuration
#------------------------------------------------------------------------------------------------------------------------------------
defconf = {}
# name of sample
defconf['nickname'] = 'MC_Pythia_TTHbb'
# list of input files
defconf['filenames'] = 'file:/nfs/dust/cms/user/shwillia/BoostedJets/CMSSW_7_4_6_patch6/src/ttHTobb_Spring15_HbbSync_NewBoostedJets.root'
#defconf['filenames'] = 'file:/nfs/dust/cms/user/shwillia/BoostedJets/CMSSW_7_4_6_patch6/src/ttbar_Spring15_HbbSync_NewBoostedJets.root'
# name and path of the output files (without extension)
defconf['outfilename'] = 'BoostedTTH'
# number of events ofthis file to analyze
defconf['maxevents'] = '100000'
# number of events to skip
defconf['skipevents'] = '0'
# total number of mcevents in sample
#in case of positive and negative weights (of same absolut value, like in MC@NLO): nevents with weight >0 minus nevents with weight <0
defconf['mcevents'] = '10000'
# cross section of the process in pb
defconf['xs'] = '1'
# is this a data sample
defconf['isData'] = False
# has the file been prepared with the BoostedProducer?
defconf['isBoostedMiniAOD'] = True
# do you need all systematics (e.g. to calculate limits)?
defconf['makeSystematicsTrees'] = False
# analysisType ('SL' or 'DL')
defconf['analysisType'] = 'SL'

# envoirnment variables
envconf = {}
envconf['nickname'] = str(os.getenv('NICK_NAME'))
envconf['filenames'] = str(os.getenv('FILE_NAMES'))
envconf['outfilename'] = str(os.getenv('OUTFILE_NAME'))
envconf['skipevents'] = int(os.getenv('SKIP_EVENTS'))
envconf['maxevents'] = int(os.getenv('MAX_EVENTS'))

envconf['mcevents'] = int(os.getenv('MCEVENTS'))
envconf['xs'] = float(os.getenv('XS'))

isData = str(os.getenv('ISDATA'))
if isData == 'True':
  envconf['isData'] = True
elif isData == 'False':
  envconf['isData'] = False
else:
  envconf['isData'] = None

isBoostedMiniAOD = str(os.getenv('ISBOOSTEDMINIAOD'))
if isBoostedMiniAOD == 'True':
  envconf['isBoostedMiniAOD'] = True
elif isBoostedMiniAOD == 'False':
  envconf['isBoostedMiniAOD'] = False
else:
  envconf['isBoostedMiniAOD'] = None
  
makeSystematicsTrees = str(os.getenv('MAKESYSTEMATICSTREE'))
if makeSystematicsTrees == 'True':
  envconf['makeSystematicsTrees'] = True
elif makeSystematicsTrees == 'False':
  envconf['makeSystematicsTrees'] = False
else:
  envconf['makeSystematicsTrees'] = None

envconf['analysisType'] = str(os.getenv('ANALYSISTYPE'))

# fill in default conf if not set by gc
conf = defconf.copy()
for key, value in conf.iteritems():  
  if not envconf[key] is None:
    conf[key] = envconf[key]

# convert strings
conf['filenames'] = conf['filenames'].strip(',')
conf['filenames'] = map(lambda s: s.strip('" '), conf['filenames'].split(","))
#------------------------------------------------------------------------------------------------------------------------------------
# End of configuration

# cmssw options
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
# global tag, you need to change this for data
process.GlobalTag.globaltag = 'MCRUN2_74_V9'
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(int(conf['maxevents'])))
process.source = cms.Source(  "PoolSource",
                              fileNames = cms.untracked.vstring(conf['filenames']),
                              skipEvents = cms.untracked.uint32(int(conf['skipevents']))
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

# load and run the boosted analyzer
if conf['isData']:
    if conf['analysisType']=='SL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_data_cfi")        
    if conf['analysisType']=='DL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_dilepton_data_cfi")        
else:
    if conf['analysisType']=='SL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_cfi")
    if conf['analysisType']=='DL':
        process.load("BoostedTTH.BoostedAnalyzer.BoostedAnalyzer_dilepton_cfi")

    if not conf['isBoostedMiniAOD']:
        # Supplies PDG ID to real name resolution of MC particles
        process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
        # Needed to determine tt+x category -- is usually run when producing boosted jets in miniAOD 
        process.load("BoostedTTH.BoostedProducer.genHadronMatching_cfi")

if conf['isBoostedMiniAOD']:
    process.BoostedAnalyzer.useFatJets=True

if conf['outfilename'] is not None:
    process.BoostedAnalyzer.outfileName=conf['outfilename']
    
if not conf['isData']:
    process.BoostedAnalyzer.luminosity = 10000.
    process.BoostedAnalyzer.xs = cms.double(float(conf['xs']))
    process.BoostedAnalyzer.nMCEvents = cms.int32(int(conf['mcevents']))
    
process.BoostedAnalyzer.makeSystematicsTrees = conf['makeSystematicsTrees']

process.p = cms.Path(process.BoostedAnalyzer)

