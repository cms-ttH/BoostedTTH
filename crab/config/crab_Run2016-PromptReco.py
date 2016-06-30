from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = ''
config.General.workArea = '/nfs/dust/cms/user/matsch/crab/ttH/Run2016'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/afs/desy.de/user/m/matsch/CMSSW_8_0_11/src/BoostedTTH/BoostedAnalyzer/test/mktrees_2016_cfg.py'
config.JobType.pyCfgParams = []
config.JobType.outputFiles = []

config.section_("Data")
config.Data.inputDataset = ''
config.Data.lumiMask = '/afs/desy.de/user/m/matsch/CertifiedRuns/Collisions2016/Cert_271036-275125_13TeV_PromptReco_Collisions16_JSON.txt'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 200
config.Data.publication = False

config.section_("Site")
config.Site.storageSite = 'T2_DE_DESY'
config.Site.whitelist = ['T2_DE_DESY']


if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    config.General.requestName = 'SingleMuon_Run2016B_PromptReco_v1'
    config.Data.inputDataset = '/SingleMuon/Run2016B-PromptReco-v1/MINIAOD'
    config.JobType.pyCfgParams = ["outName=SingleMu","isData=True","globalTag=80X_dataRun2_Prompt_v8"]
    config.JobType.outputFiles = ['SingleMu_nominal_Tree.root','SingleMu_nominal_Cutflow.txt']
# apparently not selected by lumi mask?
#    submit(config)

    config.General.requestName = 'SingleMuon_Run2016B_PromptReco_v2'
    config.Data.inputDataset = '/SingleMuon/Run2016B-PromptReco-v2/MINIAOD'
    config.JobType.pyCfgParams = ["outName=SingleMu","isData=True","globalTag=80X_dataRun2_Prompt_v8"]
    config.JobType.outputFiles = ['SingleMu_nominal_Tree.root','SingleMu_nominal_Cutflow.txt']
    submit(config)

    config.General.requestName = 'SingleMuon_Run2016C_PromptReco_v2'
    config.Data.inputDataset = '/SingleMuon/Run2016C-PromptReco-v2/MINIAOD'
    config.JobType.pyCfgParams = ["outName=SingleMu","isData=True","globalTag=80X_dataRun2_Prompt_v8"]
    config.JobType.outputFiles = ['SingleMu_nominal_Tree.root','SingleMu_nominal_Cutflow.txt']
# not yet certified
#    submit(config)

    config.General.requestName = 'SingleElectron_Run2016B_PromptReco_v1'
    config.Data.inputDataset = '/SingleElectron/Run2016B-PromptReco-v1/MINIAOD'
    config.JobType.pyCfgParams = ["outName=SingleEl","isData=True","globalTag=80X_dataRun2_Prompt_v8"]
    config.JobType.outputFiles = ['SingleEl_nominal_Tree.root','SingleEl_nominal_Cutflow.txt']
# apparently not selected by lumi mask?
#    submit(config)

    config.General.requestName = 'SingleElectron_Run2016B_PromptReco_v2'
    config.Data.inputDataset = '/SingleElectron/Run2016B-PromptReco-v2/MINIAOD'
    config.JobType.pyCfgParams = ["outName=SingleEl","isData=True","globalTag=80X_dataRun2_Prompt_v8"]
    config.JobType.outputFiles = ['SingleEl_nominal_Tree.root','SingleEl_nominal_Cutflow.txt']
    submit(config)

    config.General.requestName = 'SingleElectron_Run2016C_PromptReco_v2'
    config.Data.inputDataset = '/SingleElectron/Run2016C-PromptReco-v2/MINIAOD'
    config.JobType.pyCfgParams = ["outName=SingleEl","isData=True","globalTag=80X_dataRun2_Prompt_v8"]
    config.JobType.outputFiles = ['SingleEl_nominal_Tree.root','SingleEl_nominal_Cutflow.txt']
# not yet certified
#    submit(config)
