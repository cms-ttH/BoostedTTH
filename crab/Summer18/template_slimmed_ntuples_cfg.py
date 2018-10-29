from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'THEREQUESTNAME'
config.General.workArea = 'crab_slims'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/nfs/dust/cms/user/mwassmer/ttH_2018/dev/CMSSW_9_4_9/src/BoostedTTH/BoostedAnalyzer/test/boostedAnalysis_ntuples-ICHEP18_cg.py'
config.JobType.outputFiles = ['Mem_slimmed_ntuples_Tree.root']
config.JobType.maxJobRuntimeMin = 1440
config.JobType.maxMemoryMB = 2000 
config.JobType.pyCfgParams = ['isData=ISDATA','maxEvents=99999999','globalTag=GLOBALTAG','outName=Mem','systematicVariations=SYSTEMATICVARIATIONS','dataEra=DATAERA','ProduceMemNtuples=True']
config.JobType.sendPythonFolder=True

config.Data.inputDataset = 'THEINPUTDATASET'
config.Data.inputDBS = 'global'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 75000
config.Data.publication = False
config.Data.publishDBS = 'phys03'
config.Data.outputDatasetTag = 'KIT_tthbb_sl_slims_94X_v1'

config.User.voGroup = 'dcms'

config.Site.storageSite = 'T2_DE_DESY'
#config.Site.blacklist = ['T2_US_*']
#config.Site.whitelist = ['T2_DE_DESY']
