// -*- C++ -*-
//
// Package:    BoostedTTH/BoostedAnalyzer
// Class:      BoostedAnalyzer
//
/**\class BoostedAnalyzer BoostedAnalyzer.cc BoostedTTH/BoostedAnalyzer/plugins/BoostedAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shawn Williamson, Hannes Mildner
//
//
//


// system include files
#include <memory>
#include <vector>
#include <map>
#include <fstream>

#include "TStopwatch.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "DataFormats/METReco/interface/HcalNoiseSummary.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/View.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"
#include "MiniAOD/MiniAODHelper/interface/HiggsTagger.h"
#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"
#include "MiniAOD/MiniAODHelper/interface/LeptonSFHelper.h"

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeWriter.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenWeights.hpp"


#include "BoostedTTH/BoostedAnalyzer/interface/HistoReweighter.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/PUWeights.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LooseLeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMassSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/VertexSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/EvenOddSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/HbbSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopDLSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopSLSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopFHSelection.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/WeightProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedMCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/AdditionalJetProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BasicVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MVAVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/StdTopVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
//DANGERZONE
// #include "BoostedTTH/BoostedAnalyzer/interface/MEMProcessor.hpp"
//DANGERZONE
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedJetVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/ttHVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiJetVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/EventInfo.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Synchronizer.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TriggerVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/ReconstructionMEvarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TTbarReconstructionVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BJetnessProcessor.hpp"

//
// class declaration
//

class BoostedAnalyzer : public edm::EDAnalyzer {
public:
    explicit BoostedAnalyzer(const edm::ParameterSet&);
    ~BoostedAnalyzer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    virtual void beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup) override;
    float GetTopPtWeight(float toppt1, float toppt2);
    map<string,float> GetWeights(const GenEventInfoProduct& genEventInfo, const LHEEventProduct&  lheInfo, const EventInfo& eventInfo, const reco::VertexCollection& selectedPVs, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon>& selectedMuons, const GenTopEvent& genTopEvt, sysType::sysType systype=sysType::NA);
    std::string outfileName(const std::string& basename,const sysType::sysType& sysType);
    std::string systName(const sysType::sysType& sysType);
    sysType::sysType systType(const std::string& name);


    // ----------member data ---------------------------

    /** the miniAODhelper is used for selections and reweighting */
    MiniAODHelper helper;
    /** the csv reweighter calculates the event weight from b-tag reweightung */
    CSVHelper csvReweighter;
    //calculate the scalefactor for leptons
     LeptonSFHelper leptonSFhelper;
    // reweight the number of primary vertices distribution
    PUWeights puWeights;
    /** writes flat trees  */
    std::vector<TreeWriter*> treewriters;
    /** stores cutflows*/
    std::vector<Cutflow> cutflows;
    /** selections that are applied before writing the tree*/
    vector<Selection*> selections;
    /** triggers that are checked (independtend of the ones used for selected)*/
    vector<std::string> relevantTriggers;
    /** base name for outfiles (incl path)**/
    std::string outfileNameBase;
    /** outfile base names*/
    vector<std::string> outfileNames;
    /** stops the time spent in every processor*/
    TStopwatch watch;
    // TODO: does not function properly
    /** events to be analyzed */
    int maxEvents;
    /** event weight:  xs*lumi/(nPosEvents-nNegEvents) */
    double eventWeight;
    /** Event counter */
    int eventcount;
    /** is analyzed sample data? */
    bool isData;
    /** flag to recognize if electron dataset, muon dataset ... is analyzed*/
    int dataset_flag;
    /** use fat jets? this is only possible if the miniAOD contains them */
    bool useFatJets;
    /** use GenBmatching info? this is only possible if the miniAOD contains them */
    bool useGenHadronMatch;
    /** dump some event content for newer synchronization */
    bool dumpSyncExe2;
    /** Class that tests objects and event selections */
    Synchronizer synchronizer;
    /** systematics */
    std::vector<sysType::sysType> jetSystematics;
    /** generator systematics weigths (pdf, ME scale, etc) */
    bool dogenweights;
    /** class to extract generator weights */
    GenWeights genweights;
    /** which generator was used on ME level for this sample? */
    std::string usedGenerator;
    /** produces MC truth information for ttbar and ttH samples (genTopEvent)*/
    GenTopEventProducer genTopEvtProd;
    /** Calculated MEM for "boosted" events? Takes several seconds per event */
    bool doBoostedMEM;
    /** processors run */
    std::vector<std::string> processorNames;
    /** selections applied */
    std::vector<std::string> selectionNames;

  // TOKENS =========================
    /** pu summary data access token **/
    edm::EDGetTokenT< std::vector<PileupSummaryInfo> > puInfoToken;
    /** pileup density data access token **/
    edm::EDGetTokenT <double> rhoToken;
    /** hcal noise data access token **/
    edm::EDGetTokenT< HcalNoiseSummary > hcalNoiseToken;
    /** trigger results data access token **/
    edm::EDGetTokenT<edm::TriggerResults> triggerBitsToken;
    /** trigger objects data access token **/
    edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectsToken;
    /** trigger prescales data access token **/
    edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescalesToken;
    /** beam spot data access token **/
    edm::EDGetTokenT< reco::BeamSpot > beamSpotToken;
    /** Conversions data access token **/
    edm::EDGetTokenT< reco::ConversionCollection > conversionCollectionToken;
    /** vertex data access token **/
    edm::EDGetTokenT< reco::VertexCollection > primaryVerticesToken;
    /** tight muons data access token **/
    edm::EDGetTokenT< std::vector<pat::Muon> > selectedMuonsToken;
    /** medium muons data access token **/
    edm::EDGetTokenT< std::vector<pat::Muon> > selectedMuonsDLToken;
    /** loose muons data access token **/
    edm::EDGetTokenT< std::vector<pat::Muon> > selectedMuonsLooseToken;
    /** tight electrons data access token **/
    edm::EDGetTokenT< pat::ElectronCollection > selectedElectronsToken;
    /** medium electrons data access token **/
    edm::EDGetTokenT< pat::ElectronCollection > selectedElectronsDLToken;
    /** loose electrons data access token **/
    edm::EDGetTokenT< pat::ElectronCollection > selectedElectronsLooseToken;
    /** raw jets data access token **/
    edm::EDGetTokenT< std::vector<pat::Jet> >  rawJetsToken;
    /** loose jets data access token **/
    std::vector<edm::EDGetTokenT< std::vector<pat::Jet> > > selectedJetsTokens;
    /** tight jets data access token **/
    std::vector<edm::EDGetTokenT< std::vector<pat::Jet> > > selectedJetsLooseTokens;
    std::vector<edm::EDGetTokenT< std::vector<pat::Jet> > > selectedJetsDLTokens;
    std::vector<edm::EDGetTokenT< std::vector<pat::Jet> > > selectedJetsLooseDLTokens;
    /** mets data access token **/
    std::vector<edm::EDGetTokenT< std::vector<pat::MET> > > correctedMETsTokens;
    /** boosted jets data access token **/
    edm::EDGetTokenT< boosted::BoostedJetCollection > boostedJetsToken;
    /** gen info data access token **/
    edm::EDGetTokenT< GenEventInfoProduct > genInfoToken;
    /** LHE data access token **/
    edm::EDGetTokenT< LHEEventProduct > lheInfoToken;
    /** gen particles data access token **/
    edm::EDGetTokenT< std::vector<reco::GenParticle> > genParticlesToken;
    /** gen jets data access token **/
    edm::EDGetTokenT< std::vector<reco::GenJet> > genJetsToken;
};

//
// constructors and destructor
//
BoostedAnalyzer::BoostedAnalyzer(const edm::ParameterSet& iConfig): \
    // initialize gen top event with consumes collector (allows to access data from file within this class)
    genTopEvtProd(GenTopEventProducer(consumesCollector()))
{
  const bool BTagSystematics = false;
    //
    // get all configurations from the python config
    // meaning of the parameters is explained in python/BoostedAnalyzer_cfi.py
    eventWeight = iConfig.getParameter<double>("eventWeight");
    isData = iConfig.getParameter<bool>("isData");
    useFatJets = iConfig.getParameter<bool>("useFatJets");
    useGenHadronMatch = iConfig.getParameter<bool>("useGenHadronMatch");
    if(isData) useGenHadronMatch=false;
    dumpSyncExe2 = iConfig.getParameter<bool>("dumpSyncExe2");
    usedGenerator = iConfig.getParameter<std::string>("generatorName");
    doBoostedMEM = iConfig.getParameter<bool>("doBoostedMEM");
    outfileNameBase = iConfig.getParameter<std::string>("outfileName");
    dataset_flag = iConfig.getParameter<int>("datasetFlag");
    relevantTriggers = iConfig.getParameter< std::vector<std::string> >("relevantTriggers");
    processorNames= iConfig.getParameter< std::vector<std::string> >("processorNames");
    selectionNames= iConfig.getParameter< std::vector<std::string> >("selectionNames");
    std::vector<std::string> systematicsNames = iConfig.getParameter<std::vector<std::string> >("systematics");
    for (auto const &s : systematicsNames){
	jetSystematics.push_back(systType(s));
    }

    for (auto const &s : jetSystematics){
	outfileNames.push_back(outfileName(outfileNameBase,s));
    }
    // REGISTER DATA ACCESS
    // This needs to be done in the constructor of this class or via the consumes collector in the constructor of helper classes
    puInfoToken             = consumes< std::vector<PileupSummaryInfo> >(iConfig.getParameter<edm::InputTag>("puInfo") );
    rhoToken                = consumes<double> (iConfig.getParameter<edm::InputTag>("rho") );
    hcalNoiseToken          = consumes< HcalNoiseSummary >(iConfig.getParameter<edm::InputTag>("hcalNoise"));
    triggerBitsToken        = consumes< edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerBits"));
    triggerObjectsToken     = consumes< pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("triggerObjects"));
    triggerPrescalesToken   = consumes< pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("triggerPrescales"));
    beamSpotToken           = consumes< reco::BeamSpot > (iConfig.getParameter<edm::InputTag>("beamSpot"));
    primaryVerticesToken      = consumes< reco::VertexCollection > (iConfig.getParameter<edm::InputTag>("primaryVertices"));
    selectedMuonsToken      = consumes< std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("selectedMuons"));
    selectedMuonsDLToken    = consumes< std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("selectedMuonsDL"));
    selectedMuonsLooseToken      = consumes< std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("selectedMuonsLoose"));
    selectedElectronsToken       = consumes< pat::ElectronCollection >(iConfig.getParameter<edm::InputTag>("selectedElectrons"));
    selectedElectronsDLToken     = consumes< pat::ElectronCollection >(iConfig.getParameter<edm::InputTag>("selectedElectronsDL"));
    selectedElectronsLooseToken  = consumes< pat::ElectronCollection >(iConfig.getParameter<edm::InputTag>("selectedElectronsLoose"));

    rawJetsToken = consumes< std::vector <pat::Jet > >(iConfig.getParameter<edm::InputTag>("rawJets"));


    for(auto &tag : iConfig.getParameter<std::vector<edm::InputTag> >("selectedJets")){
	selectedJetsTokens.push_back(consumes< std::vector<pat::Jet> >(tag));
    }
    for(auto &tag : iConfig.getParameter<std::vector<edm::InputTag> >("selectedJetsLoose")){
	selectedJetsLooseTokens.push_back(consumes< std::vector<pat::Jet> >(tag));
    }
    for(auto &tag : iConfig.getParameter<std::vector<edm::InputTag> >("selectedJetsDL")){
	selectedJetsDLTokens.push_back(consumes< std::vector<pat::Jet> >(tag));
    }
    for(auto &tag : iConfig.getParameter<std::vector<edm::InputTag> >("selectedJetsLooseDL")){
	selectedJetsLooseDLTokens.push_back(consumes< std::vector<pat::Jet> >(tag));
    }
    for(auto &tag : iConfig.getParameter<std::vector<edm::InputTag> >("correctedMETs")){
	correctedMETsTokens.push_back(consumes< std::vector<pat::MET> >(tag));
    }

    boostedJetsToken        = consumes< boosted::BoostedJetCollection >(iConfig.getParameter<edm::InputTag>("boostedJets"));
    genInfoToken            = consumes< GenEventInfoProduct >(iConfig.getParameter<edm::InputTag>("genInfo"));
    lheInfoToken            = consumes< LHEEventProduct >(iConfig.getParameter<edm::InputTag>("lheInfo"));
    genParticlesToken       = consumes< std::vector<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("genParticles"));
    genJetsToken            = consumes< std::vector<reco::GenJet> >(iConfig.getParameter<edm::InputTag>("genJets"));
    conversionCollectionToken    = consumes< reco::ConversionCollection > (iConfig.getParameter<edm::InputTag>("conversionCollection"));

    // initialize helper classes
    helper.SetUp("2015_74x", isData ? -1 : 1, analysisType::LJ, isData);
    helper.SetJetCorrectorUncertainty();
    helper.SetBoostedJetCorrectorUncertainty();

    // initialize CSV reweighter
    if( iConfig.existsAs<edm::ParameterSet>("bTagSFs",true) ) {
      const edm::ParameterSet bTagSFsPS = iConfig.getParameter<edm::ParameterSet>("bTagSFs");
      csvReweighter.init( bTagSFsPS.getParameter<std::string>("fileNameHF"),
			  bTagSFsPS.getParameter<std::string>("fileNameLF"),
			  bTagSFsPS.getParameter<int>("nHFPtBins") );
    }

    // INITIALIZE PU WEIGHTS
    puWeights.init(iConfig);

    // initialize cutflows
    for (uint i=0; i<jetSystematics.size();i++){
	cutflows.push_back(Cutflow());
	cutflows.back().Init();
    }

    // initialize synchronizer
    if(dumpSyncExe2){
	synchronizer.InitDumpSyncFile2(outfileNameBase,BTagSystematics);
    }

    // initialize selections
    // add requested selections
    for(vector<string>::const_iterator itSel = selectionNames.begin();itSel != selectionNames.end();itSel++) {
	cout << "Initializing " << *itSel << endl;
	if(*itSel == "VertexSelection") selections.push_back(new VertexSelection());
	else if(*itSel == "EvenSelection") selections.push_back(new EvenOddSelection(true));
	else if(*itSel == "OddSelection") selections.push_back(new EvenOddSelection(false));
	else if(*itSel == "GenTopFHSelection") selections.push_back(new GenTopFHSelection());
	else if(*itSel == "GenTopSLSelection") selections.push_back(new GenTopSLSelection());
	else if(*itSel == "GenTopDLSelection") selections.push_back(new GenTopDLSelection());
	else if(*itSel == "LeptonSelection") selections.push_back(new LeptonSelection(iConfig));
	else if(*itSel == "LooseLeptonSelection") selections.push_back(new LooseLeptonSelection(iConfig));
	else if(*itSel == "JetTagSelection") selections.push_back(new JetTagSelection(iConfig));
	else if(*itSel == "LeptonSelection1") selections.push_back(new LeptonSelection(iConfig,1));
	else if(*itSel == "LeptonSelection2") selections.push_back(new LeptonSelection(iConfig,2));
	else if(*itSel == "LeptonSelection3") selections.push_back(new LeptonSelection(iConfig,3));
	else if(*itSel == "LeptonSelection4") selections.push_back(new LeptonSelection(iConfig,4));
	else if(*itSel == "DiLeptonSelection") selections.push_back(new DiLeptonSelection(iConfig));
	else if(*itSel == "MinDiLeptonMassSelection") selections.push_back(new DiLeptonMassSelection(20.,9999.));
	else if(*itSel == "ZVetoSelection") selections.push_back(new DiLeptonMassSelection(76.,106,true,false));
	else if(*itSel == "ZWindowSelection") selections.push_back(new DiLeptonMassSelection(76.,106,false));
	else if(*itSel == "METSelection") selections.push_back(new METSelection(iConfig));
	else if(*itSel == "DiLeptonMETSelection") selections.push_back(new DiLeptonMETSelection(iConfig));
	else if(*itSel == "HbbSelection") selections.push_back(new HbbSelection());
	else if(*itSel == "4JetSelection") selections.push_back(new JetTagSelection(4,-1));
	else if(*itSel == "2TagSelection") selections.push_back(new JetTagSelection(-1,2));
	else if(*itSel == "BoostedTopSelection") selections.push_back(new BoostedSelection(1,0));
	else if(*itSel == "BoostedSelection") selections.push_back(new BoostedSelection(0,1));
	else cout << "No matching selection found for: " << *itSel << endl;
	// connect added selection to cutflow
	for (auto &c : cutflows){
	    selections.back()->InitCutflow(c);
	}
	// dump some event info after selection step
    }


    // INITIALIZE TREEWRITERs
    for (uint i=0; i<jetSystematics.size();i++){
	cout << "creating tree writer " << outfileNames[i] << endl;
	treewriters.push_back(new TreeWriter());
	treewriters.back()->Init(outfileNames[i]);
    }
    // add processors to first tree writer
    cout << "using processors:" << endl;
    for(vector<string>::const_iterator itPro = processorNames.begin();itPro != processorNames.end();++itPro) {
	cout << *itPro << endl;
    }
    // add processors that have been requested in the config
    for(auto treewriter : treewriters){
	if(std::find(processorNames.begin(),processorNames.end(),"WeightProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new WeightProcessor(),"WeightProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"BasicVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new BasicVarProcessor(),"BasicVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"MVAVarProcessor")!=processorNames.end()) {
	    if(std::find(processorNames.begin(),processorNames.end(),"BasicVarProcessor")==processorNames.end()) {
		cout << "adding BasicVarProcessor, needed for MVAVarProcessor" << endl;
		treewriter->AddTreeProcessor(new BasicVarProcessor(),"MVAVarProcessor");
	    }
	    treewriter->AddTreeProcessor(new MVAVarProcessor(),"MVAVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"StdTopVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new StdTopVarProcessor(),"StdTopVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"BoostedJetVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new BoostedJetVarProcessor(&helper),"BoostedJetVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopHiggsVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::SecondCSV,"","BoostedTopHiggs_",doBoostedMEM),"BoostedTopHiggsVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopVarProcessor")!=processorNames.end()) {
	treewriter->AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::SecondCSV,"","BoostedTop_"),"BoostedTopVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"BoostedHiggsVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::SecondCSV,"","BoostedHiggs_"),"BoostedHiggsVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"BDTVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new BDTVarProcessor(),"BDTVarProcessor");
	}
//DANGERZONE
// 	if(std::find(processorNames.begin(),processorNames.end(),"MEMProcessor")!=processorNames.end()) {
// 	    treewriter->AddTreeProcessor(new MEMProcessor(iConfig),"MEMProcessor");
// 	}
//DANGERZONE
	if(std::find(processorNames.begin(),processorNames.end(),"MCMatchVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new MCMatchVarProcessor(),"MCMatchVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"BoostedMCMatchVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new BoostedMCMatchVarProcessor(),"BoostedMCMatchVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"AdditionalJetProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new AdditionalJetProcessor(),"AdditionalJetProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"DiLeptonVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new DiLeptonVarProcessor(),"DiLeptonVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"TriggerVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new TriggerVarProcessor(relevantTriggers),"TriggerVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"TTbarReconstructionVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new TTbarReconstructionVarProcessor(),"TTbarReconstructionVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"ReconstructionMEvarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new ReconstructionMEvarProcessor(),"ReconstructionMEvarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"BJetnessProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new BJetnessProcessor(consumesCollector()),"BJetnessProcessor");
	}
    }

    // Genweights: Initialize the weightnames for the generator, that was used for this sample
    bool generatorflag;
    if (usedGenerator == "POWHEG"){ generatorflag = genweights.SetGenerator(Generator::POWHEG); }
    else if (usedGenerator == "aMC"){ generatorflag = genweights.SetGenerator(Generator::aMC);}
    else if (usedGenerator == "MadGraph"){ generatorflag = genweights.SetGenerator(Generator::MadGraph);}
    else if (usedGenerator == "pythia8"){ generatorflag = genweights.SetGenerator(Generator::pythia8);}
    else{ generatorflag = false; }

    if (generatorflag) { std::cout << usedGenerator << " was set as Generator" << endl; }
    else { std::cout << "No Generator was set for Genweight -> no GenWeights are written in tree" << endl; }

    genweights.initLHAPDF("CT14nlo");

    assert(selectedJetsTokens.size()==selectedJetsLooseTokens.size());
    assert(selectedJetsTokens.size()==jetSystematics.size());
    assert(selectedJetsTokens.size()==cutflows.size());
}


BoostedAnalyzer::~BoostedAnalyzer()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void BoostedAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    if(eventcount<10||eventcount%1000==0){
	cout << "Analyzing event " << eventcount << endl;
	watch.Print();
	watch.Continue();
    }

    eventcount++;


    edm::Handle< std::vector<PileupSummaryInfo> >  h_puInfo;
    iEvent.getByToken( puInfoToken, h_puInfo);
    edm::Handle<double> h_rho;
    iEvent.getByToken(rhoToken,h_rho);
    edm::Handle<HcalNoiseSummary> h_hcalNoiseSummary;
    iEvent.getByToken( hcalNoiseToken,h_hcalNoiseSummary );
    edm::Handle<reco::BeamSpot> h_beamSpot;
    iEvent.getByToken( beamSpotToken,h_beamSpot );
    edm::Handle<reco::ConversionCollection> h_conversionCollection;
    iEvent.getByToken( conversionCollectionToken,h_conversionCollection );
    edm::Handle< reco::VertexCollection > h_primaryVertices;
    iEvent.getByToken( primaryVerticesToken,h_primaryVertices );
    // MUONS
    edm::Handle< pat::MuonCollection > h_selectedMuons;
    edm::Handle< pat::MuonCollection > h_selectedMuonsDL;
    edm::Handle< pat::MuonCollection > h_selectedMuonsLoose;
    iEvent.getByToken( selectedMuonsToken,h_selectedMuons );
    iEvent.getByToken( selectedMuonsDLToken,h_selectedMuonsDL );
    iEvent.getByToken( selectedMuonsLooseToken,h_selectedMuonsLoose );
    // ELECTRONS
    edm::Handle< pat::ElectronCollection > h_selectedElectrons;
    edm::Handle< pat::ElectronCollection > h_selectedElectronsDL;
    edm::Handle< pat::ElectronCollection > h_selectedElectronsLoose;
    iEvent.getByToken( selectedElectronsToken,h_selectedElectrons );
    iEvent.getByToken( selectedElectronsDLToken,h_selectedElectronsDL );
    iEvent.getByToken( selectedElectronsLooseToken,h_selectedElectronsLoose );
    // JETs


    edm::Handle< pat::JetCollection > h_rawJets;
    iEvent.getByToken( rawJetsToken, h_rawJets );
    std::vector<edm::Handle< pat::JetCollection > >hs_selectedJets;
    std::vector<edm::Handle< pat::JetCollection > >hs_selectedJetsLoose;
    std::vector<edm::Handle< pat::JetCollection > >hs_selectedJetsDL;
    std::vector<edm::Handle< pat::JetCollection > >hs_selectedJetsLooseDL;
    for(auto & selectedJetsToken : selectedJetsTokens){
    	edm::Handle< pat::JetCollection > h_selectedJets;
    	iEvent.getByToken( selectedJetsToken,h_selectedJets );
    	hs_selectedJets.push_back(h_selectedJets);
    }
    for(auto & selectedJetsLooseToken : selectedJetsLooseTokens){
	edm::Handle< pat::JetCollection > h_selectedJetsLoose;
	iEvent.getByToken( selectedJetsLooseToken,h_selectedJetsLoose );
	hs_selectedJetsLoose.push_back(h_selectedJetsLoose);
    }
    for(auto & selectedJetsDLToken : selectedJetsDLTokens){
	edm::Handle< pat::JetCollection > h_selectedJetsDL;
	iEvent.getByToken( selectedJetsDLToken,h_selectedJetsDL );
	hs_selectedJetsDL.push_back(h_selectedJetsDL);
    }
    for(auto & selectedJetsLooseDLToken : selectedJetsLooseDLTokens){
	edm::Handle< pat::JetCollection > h_selectedJetsLooseDL;
	iEvent.getByToken( selectedJetsLooseDLToken,h_selectedJetsLooseDL );
	hs_selectedJetsLooseDL.push_back(h_selectedJetsLooseDL);
    }
    std::vector<edm::Handle< pat::METCollection > > hs_correctedMETs;
    for(auto & correctedMETsToken : correctedMETsTokens){
	edm::Handle< pat::METCollection > h_correctedMETs;
	iEvent.getByToken( correctedMETsToken,h_correctedMETs );
	hs_correctedMETs.push_back(h_correctedMETs);
    }

    // MC only
    edm::Handle<GenEventInfoProduct> h_genInfo;
    edm::Handle<LHEEventProduct> h_lheInfo;
    edm::Handle<LHEEventProduct> h_dummie;
    edm::Handle< std::vector<reco::GenParticle> > h_genParticles;
    edm::Handle< std::vector<reco::GenJet> > h_genJets;
    if(!isData){
	iEvent.getByToken( genInfoToken, h_genInfo );
	iEvent.getByToken( lheInfoToken, h_dummie );
	if (h_dummie.isValid()){
	    iEvent.getByToken( lheInfoToken, h_lheInfo );
	    dogenweights = true;
	}
	else {
	    dogenweights = false;
	}
	iEvent.getByToken( genParticlesToken,h_genParticles );
	iEvent.getByToken( genJetsToken,h_genJets );
    }

    // selected vertices and set vertex for MiniAODhelper
    // TODO: vertex selection in external producer
    reco::VertexCollection const &vtxs = *h_primaryVertices;
    reco::VertexCollection selectedPVs;
    bool firstVertexIsGood=false;
    bool isFirst=true;
    if( h_primaryVertices.isValid() ){
	for( reco::VertexCollection::const_iterator itvtx = vtxs.begin(); itvtx!=vtxs.end(); ++itvtx ){
	    bool isGood = ( !(itvtx->isFake()) &&
			    (itvtx->ndof() >= 4.0) &&
			    (abs(itvtx->z()) <= 24.0) &&
			    (abs(itvtx->position().Rho()) <= 2.0)
			    );
	    if( isGood ) selectedPVs.push_back(*itvtx);
	    if( isFirst ) firstVertexIsGood=isGood;
	    isFirst=false;
	}
    }
    if( vtxs.size()>0 ) helper.SetVertex( vtxs[0] );

    // set rho in MiniAODhelper
    // TODO: setup MiniAODhelper more transparently
    helper.SetRho(*h_rho);

    /**** GET BOOSTEDJETS ****/
    //TODO: also in external producer?
    const JetCorrector* ak4corrector = JetCorrector::getJetCorrector( "ak4PFchsL1L2L3", iSetup );
    helper.SetJetCorrector(ak4corrector);

    const JetCorrector* ak8corrector = JetCorrector::getJetCorrector( "ak8PFchsL1L2L3", iSetup );
    helper.SetBoostedJetCorrector(ak8corrector);
    edm::Handle<boosted::BoostedJetCollection> h_boostedjet;
    std::vector<boosted::BoostedJetCollection> selectedBoostedJets;
    if(useFatJets){
	iEvent.getByToken( boostedJetsToken,h_boostedjet);
	boosted::BoostedJetCollection const &boostedjets_unsorted = *h_boostedjet;
	boosted::BoostedJetCollection boostedjets = BoostedUtils::GetSortedByPt(boostedjets_unsorted);
	boosted::BoostedJetCollection idBoostedJets = helper.GetSelectedBoostedJets(boostedjets, 0., 9999., 0., 9999., jetID::jetLoose);
	for(auto syst : jetSystematics){
	    boosted::BoostedJetCollection correctedBoostedJets = helper.GetCorrectedBoostedJets(idBoostedJets, iEvent, iSetup, syst, true, true);
	    selectedBoostedJets.push_back(helper.GetSelectedBoostedJets(correctedBoostedJets, 200., 2.0, 20., 2.4, jetID::none));
	}
    }
    else{
	for(uint i =0; i<jetSystematics.size();i++){
	    selectedBoostedJets.push_back(boosted::BoostedJetCollection());
	}
    }

    // Fill Event Info Object
    EventInfo eventInfo(iEvent,h_beamSpot,h_hcalNoiseSummary,h_puInfo,firstVertexIsGood,*h_rho);
    TriggerInfo triggerInfo(iEvent,triggerBitsToken,triggerObjectsToken,triggerPrescalesToken);

    // FIGURE OUT SAMPLE

    bool foundT=false;
    bool foundTbar=false;
    bool foundHiggs=false;
    HiggsDecay::HiggsDecay higgsdecay=HiggsDecay::NA;
    if(!isData){
	std::vector<reco::GenParticle> const &genParticles = *h_genParticles;
	for(size_t i=0; i<genParticles.size();i++){
	    if(genParticles[i].pdgId()==6) foundT=true;
	    if(genParticles[i].pdgId()==-6) foundTbar=true;
	    if(genParticles[i].pdgId()==25){
		foundHiggs=true;
		if(higgsdecay==HiggsDecay::NA)higgsdecay=HiggsDecay::nonbb;
		for(uint j=0;j<genParticles[i].numberOfDaughters();j++){
		    if (abs(genParticles[i].daughter(j)->pdgId())==5){
			higgsdecay=HiggsDecay::bb;
		    }
		}
	    }
	}
    }
    GenTopEvent genTopEvt=genTopEvtProd.Produce(iEvent,useGenHadronMatch,!(!isData&&foundT&&foundTbar));
    int ttid = genTopEvt.IsFilled()? genTopEvt.GetTTxIdFromProducer() : -1;

    SampleType sampleType= SampleType::nonttbkg;
    if(isData) sampleType = SampleType::data;
    else if(foundT&&foundTbar&&foundHiggs) sampleType = SampleType::tth;
    else if(foundT&&foundTbar){
	sampleType =SampleType::ttl;
	//if(ttid==51||ttid==52) sampleType = SampleType::ttb;
	if(ttid==51) sampleType = SampleType::ttb;
	else if(ttid==52) sampleType = SampleType::tt2b;
	else if(ttid==53||ttid==54||ttid==55) sampleType = SampleType::ttbb;
	else if(ttid==41||ttid==42) sampleType = SampleType::ttcc;
	else if(ttid==43||ttid==44||ttid==45) sampleType = SampleType::ttcc;
    }
    else if(((foundT&&!foundTbar)||(!foundT&&foundTbar))&&foundHiggs) sampleType = SampleType::thq;

    // nominal weight and weights for reweighting
    std::vector<map<string,float> >weightsVector;
    // inputs
    vector<InputCollections> inputs;
    for(uint isys=0; isys<jetSystematics.size(); isys++){
        auto weights = GetWeights(*h_genInfo,*h_lheInfo,eventInfo,selectedPVs,*(hs_selectedJets[isys]),*h_selectedElectrons,*h_selectedMuons,genTopEvt,jetSystematics[isys]);
	auto weightsDL = GetWeights(*h_genInfo,*h_lheInfo,eventInfo,selectedPVs,*(hs_selectedJetsLooseDL[isys]),*h_selectedElectronsLoose,*h_selectedMuonsLoose,genTopEvt,jetSystematics[isys]);
	inputs.push_back(InputCollections(eventInfo,
					  triggerInfo,
					  selectedPVs,
					  *h_selectedMuons,
					  *h_selectedMuonsDL,
					  *h_selectedMuonsLoose,
					  *h_selectedElectrons,
					  *h_selectedElectronsDL,
					  *h_selectedElectronsLoose,
					  *h_rawJets,
					  *(hs_selectedJets[isys]),
					  *(hs_selectedJetsLoose[isys]),
					  *(hs_selectedJetsDL[isys]),
					  *(hs_selectedJetsLooseDL[isys]),
					  (*(hs_correctedMETs[isys]))[0],
					  selectedBoostedJets[isys],
					  genTopEvt,
					  *h_genJets,
					  sampleType,
					  higgsdecay,
					  weights,
					  weightsDL,
					  iEvent,
					  iSetup
					  ));

    }
    //todo: adapt to new synch exe

    if(dumpSyncExe2){
    	    synchronizer.DumpSyncExe2(0,inputs[0], inputs[1], inputs[2], inputs[0],inputs[0], inputs[1], inputs[2], inputs[0], helper,dataset_flag);
        }

//void Synchronizer::DumpSyncExe2(const InputCollections& input,const InputCollections& input_DL, MiniAODHelper& helper, std::ostream &out,Cutflow& cutflowSL,Cutflow& cutflowDL, const int number){
    // DO SELECTION
    // loop over jet systematics
    assert(inputs.size()==cutflows.size());
    assert(inputs.size()==jetSystematics.size());
    for(uint i_sys=0; i_sys<jetSystematics.size(); i_sys++){
	// all events survive step 0
	cutflows[i_sys].EventSurvivedStep("all",inputs[i_sys].weights.at("Weight"));
	bool selected=true;
	// for every systematic: loop over selections
	for(size_t i_sel=0; i_sel<selections.size() && selected; i_sel++){
	    // see if event is selected
	    if(!selections.at(i_sel)->IsSelected(inputs[i_sys],cutflows[i_sys])){
		selected=false;
	    }
	}
	if(selected) treewriters[i_sys]->Process(inputs[i_sys]);
    }

}

float BoostedAnalyzer::GetTopPtWeight(float toppt1,float toppt2){
    float sf1=exp(0.156-0.00137*toppt1);
    float sf2=exp(0.156-0.00137*toppt2);
    return sqrt(sf1*sf2);
}

map<string,float> BoostedAnalyzer::GetWeights(const GenEventInfoProduct&  genInfo, const LHEEventProduct&  lheInfo, const EventInfo& eventInfo, const reco::VertexCollection& selectedPVs, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon>& selectedMuons, const GenTopEvent& genTopEvt, sysType::sysType systype){
    map<string,float> weights;

    if(isData){
	weights["Weight"] = 1.0;
	weights["Weight_XS"] = 1.0;
	weights["Weight_CSV"] = 1.0;
	weights["Weight_PU"] = 1.0;
	weights["Weight_TopPt"] = 1.0;
	weights["Weight_PV"] = 1.0;
	return weights;
    }

    float weight = 1.;
    if(genInfo.weights().size()>0){
	weight = genInfo.weights()[0]>0 ? 1.: -1.;
    }

    //dummy variables for the getCSVWeight function, might be useful for checks
    double csvWgtHF, csvWgtLF, csvWgtCF;

    float xsweight = eventWeight;
    float csvweight = 1.;
    float puweight = 1.;
    float topptweight = genTopEvt.IsTTbar()? GetTopPtWeight(genTopEvt.GetTop().pt(),genTopEvt.GetTopBar().pt()) : 1.;
    float topptweightUp = 1.0 + 2.0*(topptweight-1.0);
    float topptweightDown = 1.0;
    //get vectors of jet properties
    std::vector<double> jetPts;
    std::vector<double> jetEtas;
    std::vector<double> jetCSVs;
    std::vector<int> jetFlavors;
    for(std::vector<pat::Jet>::const_iterator itJet = selectedJets.begin(); itJet != selectedJets.end(); ++itJet){
	jetPts.push_back(itJet->pt());
	jetEtas.push_back(itJet->eta());
	jetCSVs.push_back(helper.GetJetCSV(*itJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	jetFlavors.push_back(itJet->hadronFlavour());
    }

    if(systype==sysType::JESup)csvweight= csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,7, csvWgtHF, csvWgtLF, csvWgtCF);
    else if(systype==sysType::JESdown)csvweight= csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,8, csvWgtHF, csvWgtLF, csvWgtCF);
    else if(systype==sysType::JERup)csvweight= csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,0, csvWgtHF, csvWgtLF, csvWgtCF); //there are now SF for JER yet!!
    else if(systype==sysType::JERdown)csvweight= csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,0, csvWgtHF, csvWgtLF, csvWgtCF); //there are now SF for JER yet!!
    else csvweight= csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,0, csvWgtHF, csvWgtLF, csvWgtCF);

    // compute PU weights, and set nominal weight
    puWeights.compute(eventInfo);
    puweight = puWeights.nominalWeight();

    weight *= xsweight*csvweight;//*puweight;
    weights["Weight"] = weight;
    weights["Weight_XS"] = xsweight;
    weights["Weight_CSV"] = csvweight;
    weights["Weight_PU"] = puweight;
    weights["Weight_TopPt"] = topptweight;

    bool doSystematics=true;
    if(doSystematics && systype != sysType::JESup && systype != sysType::JESdown && systype != sysType::JERup && systype != sysType::JERdown) {

	weights["Weight_CSVLFup"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,9, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVLFdown"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,10, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVHFup"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,11, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVHFdown"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,12, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVHFStats1up"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,13, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVHFStats1down"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,14, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVLFStats1up"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,17, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVLFStats1down"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,18, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVHFStats2up"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,15, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVHFStats2down"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,16, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVLFStats2up"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,19, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVLFStats2down"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,20, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVCErr1up"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,21, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVCErr1down"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,22, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVCErr2up"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,23, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVCErr2down"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,24, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_TopPtup"] = topptweightUp;
	weights["Weight_TopPtdown"] = topptweightDown;

	// set optional additional PU weights
	for(std::vector<PUWeights::Weight>::const_iterator it = puWeights.additionalWeightsBegin();
	    it != puWeights.additionalWeightsEnd(); ++it) {
	    weights[it->name()] = it->value();
	}
	//Add Genweights to the weight map
	genweights.GetGenWeights(weights, lheInfo, dogenweights);
	genweights.GetLHAPDFWeight(weights, genInfo, "CT14nlo");
    //Add Lepton Scalefactors to weight map
    std::map<std::string, float> selectedScaleFactors = leptonSFhelper.GetLeptonSF(selectedElectrons,selectedMuons);

    for(  auto sfit = selectedScaleFactors.begin() ; sfit != selectedScaleFactors.end() ; sfit++  ){
      weights["Weight_"+sfit->first] = sfit->second;
    }
  }



    return weights;
}
std::string BoostedAnalyzer::systName(const sysType::sysType& sysType){
    if(sysType==sysType::NA) return "nominal";
    if(sysType==sysType::JESup) return "jesup";
    if(sysType==sysType::JESdown) return "jesdown";
    if(sysType==sysType::JERup) return "jerup";
    if(sysType==sysType::JERdown) return "jerdown";
    std::cerr << "BoostedAnalyzer: systematic not implemented" << std::endl;
    throw std::exception();
    return "";
}

std::string BoostedAnalyzer::outfileName(const std::string& basename, const sysType::sysType& sysType){
    size_t stringIndex = basename.find("nominal");
    if(stringIndex!=std::string::npos){
	std::string outfileName=basename;
	if(sysType==sysType::JESup) outfileName.replace(stringIndex,7,"JESUP");
	else if(sysType==sysType::JESdown) outfileName.replace(stringIndex,7,"JESDOWN");
	else if(sysType==sysType::JERup) outfileName.replace(stringIndex,7,"JERUP");
	else if(sysType==sysType::JERdown) outfileName.replace(stringIndex,7,"JERDOWN");
	else {
	    std::cerr << "BoostedAnalyzer: systematic not implemented" << std::endl;
	    throw std::exception();
	}
	return outfileName;
    }
    if(sysType==sysType::NA) return basename+"_nominal";
    if(sysType==sysType::JESup) return basename+"_JESUP";
    if(sysType==sysType::JESdown) return basename+"_JESDOWN";
    if(sysType==sysType::JERup) return basename+"_JERUP";
    if(sysType==sysType::JERdown) return basename+"_JERDOWN";
    std::cerr << "BoostedAnalyzer: systematic not implemented" << std::endl;
    throw std::exception();
    return basename;
}



sysType::sysType BoostedAnalyzer::systType(const std::string& name){
    if(name=="") return sysType::NA;
    if(name=="jesup") return sysType::JESup;
    if(name=="jesdown") return sysType::JESdown;
    if(name=="jerup") return sysType::JERup;
    if(name=="jerdown") return sysType::JERdown;
    std::cerr << "BoostedAnalyzer: systematic "<< name <<" unknown" << std::endl;
    throw std::exception();
    return sysType::NA;
}


// ------------ method called once each job just before starting event loop  ------------
void BoostedAnalyzer::beginJob()
{
    eventcount=0;

    watch.Start();
}


// ------------ method called once each job just after ending the event loop  ------------
void BoostedAnalyzer::endJob()
{
    for (uint i=0; i<outfileNames.size();i++){
	std::ofstream fout(outfileNames[i]+"_Cutflow.txt");
	cutflows[i].Print(fout);
	fout.close();
	delete treewriters[i];
    }
}
// ------------ method called when starting to processes a run ------------


void BoostedAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{

}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void BoostedAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BoostedAnalyzer);
