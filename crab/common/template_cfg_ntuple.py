from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'THEREQUESTNAME'
config.General.workArea = 'crab_ntuple'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/nfs/dust/cms/user/swieland/ttH_legacy/ntuple/RELEASE/src/BoostedTTH/BoostedAnalyzer/test/boostedAnalysis_ntuples-Legacy_2016_2017_2018_cfg.py'
config.JobType.outputFiles = ['Ntuple.root']
# config.JobType.maxJobRuntimeMin = 2800
config.JobType.maxMemoryMB = 2000 
config.JobType.pyCfgParams = ['isData=ISDATA','maxEvents=99999999','outName=ntuple', 'dataEra=DATAERA','systematicVariations=SYSTEMATICVARIATIONS','weight=WEIGHT']
config.JobType.sendPythonFolder=True

config.Data.inputDataset = 'THEINPUTDATASET'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 50000
config.Data.publication = False
config.Data.publishDBS = 'phys03'
config.Data.outputDatasetTag = 'KIT_tthbb_sl_ntuple_DATAERA'

config.User.voGroup = 'dcms'

config.Site.storageSite = 'T2_DE_DESY'
#config.Site.blacklist = ['T2_US_*']
#config.Site.whitelist = ['T2_DE_DESY']
