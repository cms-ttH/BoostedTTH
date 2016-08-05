from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'ttHTobb'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/nfs/dust/cms/user/kschweig/CMSSW_8_0_12/src/BoostedTTH/BoostedProducer/test/boostedProducer_cfg.py'
config.JobType.outputFiles = ['BoostedTTH_MiniAOD.root']

config.section_("Data")
config.Data.inputDataset = '/ttHTobb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.publication = False
#config.Data.totalUnits = 5
config.Data.publishDBS = 'phys03'
config.Data.publishDataName = 'BoostedTTH_MiniAOD'

config.section_("Site")
config.Site.storageSite = 'T2_DE_DESY'
