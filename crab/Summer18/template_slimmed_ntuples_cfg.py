from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'THEREQUESTNAME'
config.General.workArea = 'crab_slims'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/nfs/dust/cms/user/mwassmer/ttH_2018/JECTest/CMSSW_9_4_10/src/BoostedTTH/BoostedAnalyzer/test/boostedAnalysis_ntuples-ICHEP18_cg.py'
config.JobType.outputFiles = ['Mem_slimmed_ntuples_Tree.root']
config.JobType.maxJobRuntimeMin = 2700
config.JobType.maxMemoryMB = 2000 
config.JobType.pyCfgParams = ['isData=ISDATA','maxEvents=99999999','globalTag=GLOBALTAG','outName=Mem','systematicVariations=SYSTEMATICVARIATIONS','dataEra=DATAERA','ProduceMemNtuples=True']
config.JobType.sendPythonFolder=True

config.Data.inputDataset = 'THEINPUTDATASET'
config.Data.inputDBS = 'global'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 50000
config.Data.publication = False
config.Data.publishDBS = 'phys03'
config.Data.outputDatasetTag = 'mem_input_2017_v2'

config.User.voGroup = 'dcms'

config.Site.storageSite = 'T2_DE_DESY'
#config.Site.blacklist = ['T2_US_*']
#config.Site.whitelist = ['T2_DE_DESY']
