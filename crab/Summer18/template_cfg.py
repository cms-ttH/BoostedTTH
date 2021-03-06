from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'THEREQUESTNAME'
config.General.workArea = 'crab_skims'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/nfs/dust/cms/user/mwassmer/ttH_2018/dev/CMSSW_9_4_6/src/BoostedTTH/BoostedAnalyzer/test/skim.py'
config.JobType.outputFiles = ['Skim.root']
config.JobType.maxJobRuntimeMin = 2880
config.JobType.maxMemoryMB = 2000 
config.JobType.pyCfgParams = ['isData=False','maxEvents=99999999']
config.JobType.sendPythonFolder=True

config.Data.inputDataset = 'THEINPUTDATASET'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.publication = True
config.Data.publishDBS = 'phys03'
config.Data.outputDatasetTag = 'KIT_tthbb_sl_skims_MC_94X'

config.User.voGroup = 'dcms'

config.Site.storageSite = 'T2_DE_DESY'
#config.Site.blacklist = ['T2_US_*']
#config.Site.whitelist = ['T2_DE_DESY']
