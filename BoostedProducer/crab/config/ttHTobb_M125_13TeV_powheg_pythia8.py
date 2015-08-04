from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'ttHTobb_M125_13TeV_powheg_pythia8'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/nfs/dust/cms/user/shwillia/CMSSW_7_4_6_patch6/src/BoostedTTH/BoostedProducer/test/boostedProducer_cfg.py'
config.JobType.outputFiles = ['BoostedTTH_MiniAOD.root']

config.section_("Data")
config.Data.inputDataset = '/ttHTobb_M125_13TeV_powheg_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.publication = True
#config.Data.totalUnits = 5
config.Data.publishDBS = 'phys03'
config.Data.publishDataName = 'BoostedTTH_MiniAOD'

config.section_("Site")
config.Site.storageSite = 'T2_DE_DESY'


