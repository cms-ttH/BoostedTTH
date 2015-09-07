from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/nfs/dust/cms/user/shwillia/AddHiggsTagger/CMSSW_7_4_6_patch6/src/BoostedTTH/BoostedProducer/test/boostedProducer_cfg.py'
config.JobType.outputFiles = ['BoostedTTH_MiniAOD.root']

config.section_("Data")
config.Data.inputDataset = '/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.publication = False
#config.Data.totalUnits = 5
config.Data.publishDBS = 'phys03'
config.Data.publishDataName = 'BoostedTTH_MiniAOD'

config.section_("Site")
config.Site.storageSite = 'T2_DE_DESY'


