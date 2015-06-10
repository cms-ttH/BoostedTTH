from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/afs/desy.de/user/k/kelmorab/CMSSW_7_4_4_patch2/src/BoostedTTH/BoostedAnalyzer/test/Crab_PreSel_cfg.py'
config.JobType.outputFiles = ['BoostedTTH_Tree.root','BoostedTTH_Cutflow.txt']

config.section_("Data")
config.Data.inputDataset = '/ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
config.Data.publication = False
#config.Data.totalUnits = 1
#config.Data.publishDbsUrl = 'phys03'
config.Data.publishDataName = 'Ana_ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8'

config.section_("Site")
config.Site.storageSite = 'T2_DE_DESY'


