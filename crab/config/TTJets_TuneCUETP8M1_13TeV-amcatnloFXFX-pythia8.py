from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/afs/desy.de/user/k/kelmorab/CMSSW_7_4_6_patch6/src/BoostedTTH/BoostedAnalyzer/test/BaseLineSel_cfg.py'
config.JobType.outputFiles = ['BoostedTTH_Tree.root','BoostedTTH_Cutflow.txt','BoostedTTH_JESup_Tree.root','BoostedTTH_JESup_Cutflow.txt','BoostedTTH_JESdown_Tree.root','BoostedTTH_JESdown_Cutflow.txt']

config.section_("Data")
config.Data.inputDataset = '/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.publication = False
#config.Data.totalUnits = 1
#config.Data.publishDbsUrl = 'phys03'
config.Data.publishDataName = 'Ana_TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8'

config.section_("Site")
config.Site.storageSite = 'T2_DE_DESY'


