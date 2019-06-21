import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox
from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection


options = VarParsing ('analysis')
options.register( "isData", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "is it data or MC?" )
options.register( "skipEvents", 0, VarParsing.multiplicity.singleton, VarParsing.varType.int, "Number of events to skip" )
options.register( "globalTag", "102X_upgrade2018_realistic_v18", VarParsing.multiplicity.singleton, VarParsing.varType.string, "global tag" )
options.register( "dataEra",     "2018",     VarParsing.multiplicity.singleton,     VarParsing.varType.string,     "the era of the data taking period or mc campaign, e.g. '2016B' or '2017'" )
options.parseArguments()

if options.maxEvents is -1: # maxEvents is set in VarParsing class by default to -1
    options.maxEvents = 1001 # reset for testing
    
if options.isData:
    if "2016" in options.dataEra:
        options.globalTag="94X_dataRun2_v10"
    elif "2017" in options.dataEra:
        options.globalTag="94X_dataRun2_v11"
    elif "2018" in options.dataEra:
        if "D" in options.dataEra:
            options.globalTag="102X_dataRun2_Prompt_v13"
        else:
            options.globalTag="102X_dataRun2_Sep2018ABC_v2"
    else:
        raise Exception( "dataEra "+options.dataEra+" not supported for this config: USE dataEra=2016/2017")
elif not options.isData:
    if "2016" in options.dataEra:
        options.globalTag="94X_mcRun2_asymptotic_v3"
    elif "2017" in options.dataEra:
        options.globalTag="94X_mc2017_realistic_v17"
    elif "2018" in options.dataEra:
        options.globalTag="102X_upgrade2018_realistic_v18"
    else:
        raise Exception( "dataEra "+options.dataEra+" not supported for this config: USE dataEra=2016/2017")
else:
    raise Exception("Problem with isData option! This should never happen!")

if not options.inputFiles:
    if not options.isData:
        options.inputFiles=['root://xrootd-cms.infn.it///store/mc/RunIIAutumn18MiniAOD/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/40000/E26C264E-6FAE-BA4B-B729-1FDD04B0B2AC.root']
    else:
        options.inputFiles=['root://xrootd-cms.infn.it///store/data/Run2018B/MET/MINIAOD/17Sep2018-v1/100000/84F4D3C4-7275-834A-ADDF-E34194D17EB3.root']
        
# checks for correct values and consistency
if "data" in options.globalTag.lower() and not options.isData:
    print "\n\nConfig ERROR: GT contains seems to be for data but isData==False\n\n"
    sys.exit()
if "mc" in options.globalTag.lower() and options.isData:
    print "\n\nConfig ERROR: GT contains seems to be for MC but isData==True\n\n"
    sys.exit()
if not options.inputFiles:
    print "\n\nConfig ERROR: no inputFiles specified\n\n"
    sys.exit()

process = cms.Process("SKIM")

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(options.inputFiles),
                            skipEvents=cms.untracked.uint32(int(options.skipEvents))

)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

# messages
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = options.globalTag
process.load("CondCore.CondDB.CondDB_cfi")

# these are needed to write the new AK15 jet collections - dont know why ...
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.Geometry.GeometryRecoDB_cff')


jetToolbox( process, 'ak15', 'ak15JetSubs', 'noOutput',
  PUMethod='Puppi',
  addPruning=True, addSoftDrop=True ,           # add basic grooming
  addTrimming=True, addFiltering=True,
  addSoftDropSubjets=True,
  addPrunedSubjets=True,
  addNsub=True, maxTau=4,                       # add Nsubjettiness tau1, tau2, tau3, tau4
  JETCorrPayload = 'AK8PFPuppi', #JETCorrLevels = ['L2Relative', 'L3Absolute'],
  runOnMC=not options.isData,
  miniAOD=True,
  #bTagDiscriminators=[
            #'pfDeepCSVJetTags:probb',
			#'pfDeepCSVJetTags:probbb',
			#'pfDeepCSVJetTags:probc',
			#'pfDeepCSVJetTags:probudsg',
            #'pfDeepFlavourJetTags:probb',
			#'pfDeepFlavourJetTags:probbb',
			#'pfDeepFlavourJetTags:problepb',
			#'pfDeepFlavourJetTags:probc',
			#'pfDeepFlavourJetTags:probuds',
			#'pfDeepFlavourJetTags:probg',    
  #],
  Cut='pt > 100 && abs(eta) < 2.5',
  GetJetMCFlavour=not options.isData,
  #GetSubJetMCFlavour=True,
  addHEPTopTagger=True
  )

jetToolbox( process, 'ak8', 'ak8JetSubs', 'noOutput',
  PUMethod='Puppi',
  addPruning=True, addSoftDrop=True ,           # add basic grooming
  addTrimming=True, addFiltering=True,
  addSoftDropSubjets=True,
  addPrunedSubjets=True,
  addNsub=True, maxTau=4,                       # add Nsubjettiness tau1, tau2, tau3, tau4
  JETCorrPayload = 'AK8PFPuppi', #JETCorrLevels = ['L2Relative', 'L3Absolute'],
  runOnMC=not options.isData,
  miniAOD=True,
  #bTagDiscriminators=[
            #'pfDeepCSVJetTags:probb',
			#'pfDeepCSVJetTags:probbb',
			#'pfDeepCSVJetTags:probc',
			#'pfDeepCSVJetTags:probudsg',
            #'pfDeepFlavourJetTags:probb',
			#'pfDeepFlavourJetTags:probbb',
			#'pfDeepFlavourJetTags:problepb',
			#'pfDeepFlavourJetTags:probc',
			#'pfDeepFlavourJetTags:probuds',
			#'pfDeepFlavourJetTags:probg',    
  #],
  Cut='pt > 60 && abs(eta) < 2.5',
  GetJetMCFlavour=not options.isData,
  #GetSubJetMCFlavour=True,
  addHEPTopTagger=True
  )

jetToolbox( process, 'ak4', 'ak4Jetchs', 'noOutput',
           updateCollection='slimmedJets',
           JETCorrPayload='AK4PFchs',
           bTagDiscriminators= [
                'pfDeepFlavourJetTags:probb',
                'pfDeepFlavourJetTags:probbb',
                'pfDeepFlavourJetTags:problepb',
                'pfDeepFlavourJetTags:probc',
                'pfDeepFlavourJetTags:probuds',
                'pfDeepFlavourJetTags:probg'
           ],
           runOnMC=not options.isData,
           Cut='pt > 20 && abs(eta) < 2.5'
  )
           
jetToolbox( process, 'ak4', 'ak4Jetpuppi', 'noOutput',
           updateCollection='slimmedJetsPuppi',
           JETCorrPayload='AK4PFPuppi',
           bTagDiscriminators= [
                'pfDeepFlavourJetTags:probb',
                'pfDeepFlavourJetTags:probbb',
                'pfDeepFlavourJetTags:problepb',
                'pfDeepFlavourJetTags:probc',
                'pfDeepFlavourJetTags:probuds',
                'pfDeepFlavourJetTags:probg'
           ],
           runOnMC=not options.isData,
           Cut='pt > 20 && abs(eta) < 2.5'
  )

#updateJetCollection(
   #process,
   #jetSource = cms.InputTag('selectedPatJetsAK15PFPuppiPrunedSubjets'),
   #pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
   #svSource = cms.InputTag('slimmedSecondaryVertices'),
   #jetCorrections = ('AK4PFPuppi', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None'),
   #btagDiscriminators = [
      #'pfDeepFlavourJetTags:probb',
      #'pfDeepFlavourJetTags:probbb',
      #'pfDeepFlavourJetTags:problepb',
      #'pfDeepFlavourJetTags:probc',
      #'pfDeepFlavourJetTags:probuds',
      #'pfDeepFlavourJetTags:probg'
      #],
   #postfix='AK15PFPuppiPrunedSubjetsNewDFTraining'
#)
   
#updateJetCollection(
   #process,
   #jetSource = cms.InputTag('selectedPatJetsAK15PFPuppiSoftDropSubjets'),
   #pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
   #svSource = cms.InputTag('slimmedSecondaryVertices'),
   #jetCorrections = ('AK4PFPuppi', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None'),
   #btagDiscriminators = [
      #'pfDeepFlavourJetTags:probb',
      #'pfDeepFlavourJetTags:probbb',
      #'pfDeepFlavourJetTags:problepb',
      #'pfDeepFlavourJetTags:probc',
      #'pfDeepFlavourJetTags:probuds',
      #'pfDeepFlavourJetTags:probg'
      #],
   #postfix='AK15PFPuppiSoftDropSubjetsNewDFTraining'
#)
   
  

####################### MET stuff #############################

from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
from PhysicsTools.PatAlgos.slimming.puppiForMET_cff import makePuppiesFromMiniAOD
makePuppiesFromMiniAOD( process, False )

runMetCorAndUncFromMiniAOD(process,
                           isData=options.isData,
                           fixEE2017 = True if "2017" in options.dataEra else False,
                           fixEE2017Params = {'userawPt': True, 'ptThreshold':50.0, 'minEtaThreshold':2.65, 'maxEtaThreshold': 3.139} 
                           )

runMetCorAndUncFromMiniAOD(process,
                           isData=options.isData,
                           metType="Puppi",
                           postfix="Puppi",
                           jetFlavor="AK4PFPuppi",
                           )

process.puppiNoLep.useExistingWeights = True
process.puppi.useExistingWeights = True

process.load("RecoMET.METFilters.primaryVertexFilter_cfi")
process.primaryVertexFilter.vertexCollection = cms.InputTag("offlineSlimmedPrimaryVertices")
process.load("RecoMET.METFilters.globalSuperTightHalo2016Filter_cfi")
process.load("CommonTools.RecoAlgos.HBHENoiseFilterResultProducer_cfi")
process.load("CommonTools.RecoAlgos.HBHENoiseFilter_cfi")
process.load("RecoMET.METFilters.EcalDeadCellTriggerPrimitiveFilter_cfi")
process.load("RecoMET.METFilters.BadPFMuonFilter_cfi")
process.load("RecoMET.METFilters.eeBadScFilter_cfi")

###############################################################

####################### EGamma stuff ##########################   
   
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
EG_era = None
EG_corrections = None
EG_vid = None
if "2016" in options.dataEra:
    EG_era = '2016-Legacy'
    EG_corrections = False
    EG_vid = True
elif "2017" in options.dataEra:
    EG_era = '2017-Nov17ReReco'
    EG_corrections = True
    EG_vid = True
elif "2018" in options.dataEra:
    EG_era = '2018-Prompt'
    EG_corrections = False
    EG_vid = True
else:
    raise Exception( "dataEra "+options.dataEra+" not supported for Egamma tools: USE dataEra=2016/2017/2018")

setupEgammaPostRecoSeq(process,
                       runVID=EG_vid,
                       runEnergyCorrections=EG_corrections,
                       era=EG_era,
                       isMiniAOD=True
                       )   
   
###############################################################

####################### configure skimming process #############################

process.load("BoostedTTH.BoostedAnalyzer.LeptonJetsSkim_cfi")
process.LeptonJetsSkim.isData=cms.bool(options.isData)
process.LeptonJetsSkim.electrons = cms.InputTag("slimmedElectrons", "", process.name_())
process.LeptonJetsSkim.photons = cms.InputTag("slimmedPhotons", "", process.name_())
process.LeptonJetsSkim.met = cms.InputTag("slimmedMETs","",process.name_())
process.LeptonJetsSkim.met_puppi = cms.InputTag("slimmedMETsPuppi","",process.name_())

###############################################################

process.content = cms.EDAnalyzer("EventContentAnalyzer")


process.OUT = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('Skim.root'),
    outputCommands = cms.untracked.vstring(['drop *','keep *_*_*_PAT','keep *_*_*_RECO','keep *_*_*_HLT*','keep *_*_*_SIM','keep *_*_*_LHE',
        'keep *_selected*AK15*_*_SKIM',
        'drop *_selected*AK15*_*calo*_SKIM', 
        'drop *_selected*AK15*_*tagInfos*_SKIM',
        'keep *_selected*AK8*_*_SKIM',
        'drop *_selected*AK8*_*calo*_SKIM', 
        'drop *_selected*AK8*_*tagInfos*_SKIM',
        'keep *_selected*AK4*_*_SKIM',
        'drop *_selected*AK4*_*calo*_SKIM', 
        'drop *_selected*AK4*_*tagInfos*_SKIM',
        'keep *_*slimmedMET*_*_SKIM'
        ]),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring("skim")
    )
)
    
process.skim = cms.Path()

# these are MET filters which can be run on any era (data and mc) and do not need special recipes
process.skim *= process.HBHENoiseFilterResultProducer*process.HBHENoiseFilter*process.HBHENoiseIsoFilter
process.skim *= process.primaryVertexFilter
process.skim *= process.globalSuperTightHalo2016Filter
process.skim *= process.EcalDeadCellTriggerPrimitiveFilter
#if options.isData:
    #process.skim *= process.eeBadScFilter
process.skim *= process.LeptonJetsSkim

# egamma sequence to recalculate electron/photon IDs
process.egamma = cms.Path(process.egammaPostRecoSeq)

# met sequence to recalculate MET
process.met = cms.Path(process.fullPatMetSequence)

# write the events which pass the skimming selection and only keep the specified file content
process.write_skimmed = cms.EndPath(process.OUT)

#print process.dumpPython()
