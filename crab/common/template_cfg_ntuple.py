from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'THEREQUESTNAME'
config.General.workArea = 'WORKAREA'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'CMSSWPATH/RUNCONFIG'
config.JobType.outputFiles = OUTPUTFILES
# config.JobType.maxJobRuntimeMin = 2800
config.JobType.maxMemoryMB = 4000 
config.JobType.pyCfgParams = ['isData=ISDATA','maxEvents=99999999','outName=OUTNAME', 'dataEra=DATAERA','systematicVariations=SYSTEMATICVARIATIONS','weight=WEIGHT','ProduceMemNtuples=SLIMMED', 'deterministicSeeds=SEEDS']
config.JobType.sendPythonFolder=True

config.Data.inputDataset = 'THEINPUTDATASET'
config.Data.inputDBS = 'DBSINSTANCE'
# config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 600
config.Data.splitting = 'Automatic'
config.Data.publication = False
config.Data.publishDBS = 'phys03'
config.Data.outputDatasetTag = 'KIT_tthbb_sl_LEG_NTUPLETAG_DATAERA'

config.User.voGroup = 'dcms'

config.Site.storageSite = 'T2_DE_DESY'
#config.Site.blacklist = ['T2_US_*']
#config.Site.whitelist = ['T2_DE_DESY']
