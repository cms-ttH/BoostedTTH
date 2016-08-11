import FWCore.ParameterSet.Config as cms
# input
process = cms.Process("p")
process.source = cms.Source("PoolSource",
                            #fileNames = cms.untracked.vstring('file:/pnfs/desy.de/cms/tier2/store/mc/RunIISpring16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/00000/D2D9E71A-121B-E611-97D4-0CC47A4C6FDC.root')
                            #fileNames = cms.untracked.vstring('file:/pnfs/desy.de/cms/tier2/store/mc/RunIIFall15MiniAODv2/ttHTobb_M125_13TeV_powheg_pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/74B638CC-44B8-E511-8F19-1CC1DE19283E.root')
                            #fileNames = cms.untracked.vstring('file:/pnfs/desy.de/cms/tier2/store/user/koschwei/ttHTobb_M125_13TeV_powheg_pythia8/BoostedMiniAODICHEPv1/160729_220552/0000/BoostedTTH_MiniAOD_12.root')
                            fileNames = cms.untracked.vstring('file:/pnfs/desy.de/cms/tier2/store/mc/RunIISpring16MiniAODv2/ttHTobb_M125_13TeV_powheg_pythia8/MINIAODSIM/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/40000/0232CD05-9C38-E611-B4BD-02163E014E9C.root')
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) ) #default 1000

# messages
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.suppressWarning = cms.untracked.vstring('ecalLaserCorrFilter','manystripclus53X','toomanystripclus53X')
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)

# Load the producer for MVA IDs
process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")

# select loose lepton collections
#process.load('BoostedTTH.BoostedProducer.SelectedLeptonProducers_cfi')
process.load('BoostedTTH.Producers.SelectedLeptonProducers_cfi')

#do projections
process.pfCHS = cms.EDFilter("CandPtrSelector", src = cms.InputTag("packedPFCandidates"), cut = cms.string("fromPV"))
#process.pfNoMuonCHS =  cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfCHS"), veto = cms.InputTag("SelectedMuonProducer"))
#process.pfNoElectronsCHS = cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfNoMuonCHS"), veto =  cms.InputTag("SelectedElectronProducer"))
process.pfNoMuonCHS =  cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfCHS"), veto = cms.InputTag("SelectedMuonProducer:selectedLeptonsDL"))
process.pfNoElectronsCHS = cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfNoMuonCHS"), veto =  cms.InputTag("SelectedElectronProducer:selectedLeptonsDL"))

# make patJets
process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_miniAODv2_v1')

# make Boosted Jets
process.load('BoostedTTH.BoostedProducer.BoostedJetProducer_cfi')

# make PAT Jets from Boosted Jets
from PhysicsTools.PatAlgos.tools.jetTools import addJetCollection

# HTT topjet
addJetCollection(
    process,
    labelName = 'HTTTopJetsPF',
    postfix="",
    jetSource = cms.InputTag('HTTTopJetProducer',''),
    algo = 'CA',
    rParam = 1.5,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = None
)

# 3 HTT subjets
addJetCollection(
    process,
    labelName = 'HTTSubjetsPF',
    postfix="",
    jetSource = cms.InputTag('HTTTopJetProducer','subjets'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    elSource = cms.InputTag('slimmedElectrons'),
    muSource = cms.InputTag('slimmedMuons'),
    algo = 'CA',
    rParam = 1.5,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = [ 'pfCombinedInclusiveSecondaryVertexV2BJetTags','pfCombinedMVAV2BJetTags' ],
    explicitJTA = True,
    svClustering = True,
    fatJets=cms.InputTag('ca15PFJetsCHS'),
    groomedFatJets=cms.InputTag('HTTTopJetProducer')
)

# fatjet
addJetCollection(
    process,
    labelName = 'FatJetsPF',
    postfix = "",
    jetSource = cms.InputTag('ca15PFJetsCHS'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    elSource = cms.InputTag('slimmedElectrons'),
    muSource = cms.InputTag('slimmedMuons'),
    algo = 'CA',
    rParam = 1.5,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = ['pfBoostedDoubleSecondaryVertexCA15BJetTags']
)

# 2 SF subjets
addJetCollection(
    process,
    labelName = 'SFSubjetsPF',
    postfix = "",
    jetSource = cms.InputTag('SFJetProducer','sub'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    elSource = cms.InputTag('slimmedElectrons'),
    muSource = cms.InputTag('slimmedMuons'),
    algo = 'CA',
    rParam = 1.5,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = [ 'pfCombinedInclusiveSecondaryVertexV2BJetTags','pfCombinedMVAV2BJetTags' ],
    explicitJTA = True,
    svClustering = True,
    fatJets=cms.InputTag('ca15PFJetsCHS'),
    groomedFatJets=cms.InputTag('SFJetProducer','subcomp')
)

# SF filtered subjets
addJetCollection(
    process,
    labelName = 'SFFilterjetsPF',
    postfix = "",
    jetSource = cms.InputTag('SFJetProducer','filter'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    elSource = cms.InputTag('slimmedElectrons'),
    muSource = cms.InputTag('slimmedMuons'),
    algo = 'CA',
    rParam = 1.5,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = [ 'pfCombinedInclusiveSecondaryVertexV2BJetTags','pfCombinedMVAV2BJetTags' ],
    explicitJTA = True,
    svClustering = True,
    fatJets = cms.InputTag('ca15PFJetsCHS'),
    groomedFatJets = cms.InputTag('SFJetProducer','filtercomp')
)

# pruned subjets
addJetCollection(
    process,
    labelName = 'PrunedSubjetsPF',
    postfix = "",
    jetSource = cms.InputTag('ca15PFPrunedJetsCHS','subjets'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    elSource = cms.InputTag('slimmedElectrons'),
    muSource = cms.InputTag('slimmedMuons'),
    algo = 'CA',
    rParam = 1.5,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = [ 'pfCombinedInclusiveSecondaryVertexV2BJetTags','pfCombinedMVAV2BJetTags' ],
    explicitJTA = True,
    svClustering = True,
    fatJets=cms.InputTag('ca15PFJetsCHS'),
    groomedFatJets=cms.InputTag('ca15PFPrunedJetsCHS')
)

# softdrop subjets
addJetCollection(
    process,
    labelName = 'SDSubjetsPF',
    postfix = "",
    jetSource = cms.InputTag('ca15PFSoftdropJetsCHS','subjets'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    elSource = cms.InputTag('slimmedElectrons'),
    muSource = cms.InputTag('slimmedMuons'),
    algo = 'CA',
    rParam = 1.5,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = [ 'pfCombinedInclusiveSecondaryVertexV2BJetTags','pfCombinedMVAV2BJetTags' ],
    explicitJTA = True,
    svClustering = True,
    fatJets=cms.InputTag('ca15PFJetsCHS'),
    groomedFatJets=cms.InputTag('ca15PFSoftdropJetsCHS')
)

#adjust MC matching for all Boosted Jet collections
#fatjets
process.patJetsFatJetsPF.addGenJetMatch=False
process.patJetPartonMatchFatJetsPF.matched = "prunedGenParticles"
#HTT topjets
process.patJetsHTTTopJetsPF.addGenJetMatch=False
process.patJetPartonMatchHTTTopJetsPF.matched = "prunedGenParticles"
#HTT subjets
process.patJetsHTTSubjetsPF.addGenJetMatch=False
process.patJetPartonMatchHTTSubjetsPF.matched = "prunedGenParticles"
#SF subjets
process.patJetsSFSubjetsPF.addGenJetMatch=False
process.patJetPartonMatchSFSubjetsPF.matched = "prunedGenParticles"
#SF filterjets
process.patJetsSFFilterjetsPF.addGenJetMatch=False
process.patJetPartonMatchSFFilterjetsPF.matched = "prunedGenParticles"
#pruned subjets
process.patJetsPrunedSubjetsPF.addGenJetMatch=False
process.patJetPartonMatchPrunedSubjetsPF.matched = "prunedGenParticles"
#soft drop subjets
process.patJetsSDSubjetsPF.addGenJetMatch=False
process.patJetPartonMatchSDSubjetsPF.matched = "prunedGenParticles"

# all
process.patJetPartons.particles = "prunedGenParticles"

#from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets
from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
#process.ak4PFJetsCHS = ak4PFJets.clone(src = 'pfNoElectronsCHS', doAreaFastjet = True)
process.ak4GenJets = ak4GenJets.clone(src = 'packedGenParticles')

# match boosted reco Jets to pat jets
process.load('BoostedTTH.BoostedProducer.BoostedJetMatcher_cfi')

# gen hadron matching for tt+X categorization
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("BoostedTTH.BoostedProducer.genHadronMatching_cfi")

# skim
process.load("BoostedTTH.BoostedProducer.LeptonJetsSkim_cfi")

# dump event content
#process.content = cms.EDAnalyzer("EventContentAnalyzer")

# execute in the right order
process.boosted_skimmed=cms.Path(process.electronMVAValueMapProducer
                                 *process.LeptonJetsSkim
                                 *process.SelectedElectronProducer
                                 *process.SelectedMuonProducer
                                 *process.ca15PFJetsCHS
                                 *process.HTTTopJetProducer
                                 *process.SFJetProducer
                                 *process.ca15PFPrunedJetsCHS
                                 *process.ca15PFSoftdropJetsCHS
                                 *process.ca15PFSoftdropJetsCHSforSubjettiness
				                         *process.ca15SoftdropSubjettiness
                                 *process.patJetsFatJetsPF
                                 *process.patJetsHTTTopJetsPF
                                 *process.patJetsHTTSubjetsPF
                                 *process.patJetsSFSubjetsPF
                                 *process.patJetsSFFilterjetsPF
                                 *process.patJetsPrunedSubjetsPF
                                 *process.patJetsSDSubjetsPF
                                 *process.BoostedJetMatcher)

process.OUT = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('BoostedTTH_MiniAOD.root'),
    outputCommands = cms.untracked.vstring(['drop *','keep *_*_*_PAT','keep *_*_*_RECO','keep *_*_*_HLT*','keep *_*_*_SIM','keep *_*_*_LHE','keep *_*BoostedJetMatcher*_*_*','keep *_matchGen*Hadron_*_*', 'keep *_ak4GenJetsCustom_*_*', 'keep *_categorizeGenTtbar_*_*']),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring("boosted_skimmed")
    )
)
process.endpath = cms.EndPath(process.OUT)
