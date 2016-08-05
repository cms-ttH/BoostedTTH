from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = ''
config.General.workArea = '/nfs/dust/cms/user/matsch/crab/ttH/Spring16/v1'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/afs/desy.de/user/m/matsch/CMSSW_8_0_11/src/BoostedTTH/BoostedAnalyzer/test/mktrees_2016_cfg.py'
config.JobType.pyCfgParams = []
config.JobType.outputFiles = []

config.section_("Data")
config.Data.inputDataset = ''
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
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

    config.General.requestName = 'TT_TuneCUETP8M1_13TeV-powheg-pythia8_asymptotic_2016_miniAODv2_v0_ext3-v1'
    config.Data.inputDataset = '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext3-v1/MINIAODSIM'
    # N(evts) = 93121240, XS = 832pb, Target Lumi: 1000pb --> weight = 0.008934589
    config.JobType.pyCfgParams = ["outName=TTJets","isData=False","globalTag=80X_mcRun2_asymptotic_2016_miniAODv2","channel=both","weight=0.008934589"]
    config.JobType.outputFiles = ['TTJets_nominal_Tree.root','TTJets_nominal_Cutflow.txt']
    submit(config)
