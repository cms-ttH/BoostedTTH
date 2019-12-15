from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'THEREQUESTNAME'
config.General.workArea = 'crab_skims'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'CMSSWPATH/RUNCONFIG'
config.JobType.outputFiles = ['Skim.root']
# config.JobType.maxJobRuntimeMin = 2800
config.JobType.maxMemoryMB = 2000 
config.JobType.pyCfgParams = ['isData=ISDATA','maxEvents=99999999', 'dataEra=DATAERA']
config.JobType.sendPythonFolder=True

config.Data.inputDataset = 'THEINPUTDATASET'
config.Data.inputDBS = 'global'
config.Data.splitting = 'Automatic'
# config.Data.unitsPerJob = UNITSPERJOB
config.Data.publication = True
config.Data.publishDBS = 'phys03'
config.Data.outputDatasetTag = 'OUTPUTDATASETTAG'

config.User.voGroup = 'dcms'

config.Site.storageSite = 'T2_DE_DESY'
#config.Site.blacklist = ['T2_US_*']
#config.Site.whitelist = ['T2_DE_DESY']
