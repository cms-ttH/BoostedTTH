from CRABClient.UserUtilities import config, getUsernameFromSiteDB

config = config()

config.General.requestName = "THEREQUESTNAME"
config.General.workArea = "crab_ntuples"
config.General.transferLogs = True

config.JobType.pluginName = "Analysis"
config.JobType.psetName = "/nfs/dust/cms/user/mwassmer/MonoTop/test/CMSSW_10_2_18/src/BoostedTTH/BoostedAnalyzer/test/boostedAnalysis_ntuples-Legacy_2016_2017_2018_cfg.py"
config.JobType.outputFiles = OUTPUTFILES
# config.JobType.maxJobRuntimeMin = 2800
config.JobType.maxMemoryMB = 2000
config.JobType.pyCfgParams = [
    "outName=ntuples",
    "isData=ISDATA",
    "maxEvents=999999999",
    "dataEra=DATAERA",
    "globalTag=GLOBALTAG",
    "weight=WEIGHT",
    "ProduceMemNtuples=False",
    "systematicVariations=SYSTEMATICVARIATIONS"
]
config.JobType.sendPythonFolder = True

config.Data.inputDataset = "THEINPUTDATASET"
config.Data.inputDBS = "phys03"
config.Data.splitting = "Automatic"
config.Data.unitsPerJob = 540
config.Data.publication = False
config.Data.publishDBS = "phys03"
config.Data.outputDatasetTag = "KIT_Monotop_ntuples_DATAERA"

config.User.voGroup = "dcms"

config.Site.storageSite = "T2_DE_DESY"
# config.Site.blacklist = ['T2_US_*']
# config.Site.whitelist = ['T2_DE_DESY']
