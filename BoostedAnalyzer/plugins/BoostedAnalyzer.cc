
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
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
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
#include "BoostedTTH/BoostedAnalyzer/interface/FilterInfo.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection_QCDControlregion.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LooseLeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMassSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/VertexSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/FilterSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/EvenOddSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/HbbSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopDLSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopSLSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopFHSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MonoJetSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonVetoSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BTagVetoSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/PhotonVetoSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/monoVselection.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/WeightProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MCMatchVarProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/BoostedMCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/AdditionalJetProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BasicVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/essentialBasicVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MVAVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/StdTopVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DNNVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/essentialMVAVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/essentialMCMatchVarProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/BoostedJetVarProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/BoostedAk4VarProcessor.hpp"
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
#include "BoostedTTH/BoostedAnalyzer/interface/SpinCorrelationProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenJetOrderedJetCollectionProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Ak4Cluster.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/SlimmedNtuples.hpp"
#include "TTH/CommonClassifier/interface/MEMClassifier.h"
#include "TTH/CommonClassifier/interface/BDTClassifier.h"
#include "TTH/CommonClassifier/interface/DLBDTClassifier.h"
#include "TTH/CommonClassifier/interface/DNNClassifier.h"
#include "BoostedTTH/BoostedAnalyzer/interface/ResourceMonitor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TTBBStudienProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenDarkMatterEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DarkMatterProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MonoJetGenSelectionProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/SelectionTagProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BosonWeightProcessor.hpp"

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
    virtual void endRun(edm::Run const& iRun, edm::EventSetup const& iSetup) override;
    virtual void beginLuminosityBlock(edm::LuminosityBlock const& iBlock, edm::EventSetup const& iSetup) override;
    float GetTopPtWeight(const float& toppt1, const float& toppt2);
    map<string,float> GetWeights(const GenEventInfoProduct& genEventInfo, const LHEEventProduct&  lheInfo, const EventInfo& eventInfo, const reco::VertexCollection& selectedPVs, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Jet>& selectedJetsLoose, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon>& selectedMuons, const GenTopEvent& genTopEvt, const Systematics::Type& systype=Systematics::NA);
    std::string outfileName(const std::string& basename,const Systematics::Type& sysType);
    std::string systName(const Systematics::Type& sysType);


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
    std::vector<std::unique_ptr<TreeWriter>> treewriters;
    /** stores cutflows*/
    std::vector<Cutflow> cutflows;
    /** selections that are applied before writing the tree*/
    std::vector<std::unique_ptr<Selection>> selections;
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
    /** number of events to process */
    int nevents_to_process;
    /** is analyzed sample data? */
    bool isData;
    /** use fat jets? this is only possible if the miniAOD contains them */
    bool useFatJets;
    /** use GenBmatching info? this is only possible if the miniAOD contains them */
    bool useGenHadronMatch;
    /** dump some event content for newer synchronization */
    bool dumpSyncExe;
    bool dumpExtended;
    std::vector<int> dumpAlwaysEvents;
    /** Class that tests objects and event selections */
    Synchronizer synchronizer;
    /** systematics */
    std::vector<Systematics::Type> jetSystematics;
    /** generator systematics weigths (pdf, ME scale, etc) */
    bool dogenweights;
    /** class to extract generator weights */
    GenWeights genweights;
    /** which generator was used on ME level for this sample? */
    std::string usedGenerator;
    /** produces MC truth information for ttbar and ttH samples (genTopEvent)*/
    GenTopEventProducer genTopEvtProd;
    /** produces trigger information */
    TriggerInfoProducer triggerInfoProd;
    /** produces filter information */
    FilterInfoProducer filterInfoProd;
    /** Calculated MEM for "boosted" events? Takes several seconds per event */
    bool doBoostedMEM;
    /** processors run */
    std::vector<std::string> processorNames;
    /** selections applied */
    std::vector<std::string> selectionNames;
    /** use tagging for selections **/
    bool taggingSelection;
    
    bool ProduceMemNtuples;
    uint jet_tag_pos;

  // TOKENS =========================
    /** pu summary data access token **/
    edm::EDGetTokenT< std::vector<PileupSummaryInfo> > puInfoToken;
    /** pileup density data access token **/
    edm::EDGetTokenT <double> rhoToken;
    /** hcal noise data access token **/
    edm::EDGetTokenT< HcalNoiseSummary > hcalNoiseToken;
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
    /** tau token **/
    edm::EDGetTokenT< pat::TauCollection > selectedTausToken;
    /** loose photons token **/
    edm::EDGetTokenT< pat::PhotonCollection > selectedPhotonsLooseToken;
    /** loose jets data access token **/
    std::vector<edm::EDGetTokenT< std::vector<pat::Jet> > > selectedJetsTokens;
    /** tight jets data access token **/
    std::vector<edm::EDGetTokenT< std::vector<pat::Jet> > > selectedJetsLooseTokens;
    /** AK8Jet jets data access token **/
    std::vector<edm::EDGetTokenT< std::vector<pat::Jet> > > AK8Jets_Tokens;
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
    // LHERunInfo data access token
    edm::EDGetTokenT< LHERunInfoProduct > LHERunInfoToken;
    
    edm::EDGetTokenT< std::vector<reco::GenParticle> > customGenElectrons;
    edm::EDGetTokenT< std::vector<reco::GenParticle> > customGenMuons;
    edm::EDGetTokenT< std::vector<reco::GenParticle> > customGenTaus;
    edm::EDGetTokenT< std::vector<reco::GenParticle> > customGenPhotons;
    edm::EDGetTokenT< std::vector<reco::GenJet> > customGenJets;
    edm::EDGetTokenT< std::vector<reco::GenJet> > customGenJetsLoose;
    edm::EDGetTokenT< std::vector<reco::GenJet> > customGenJetsAK8;

    std::map<std::string, int> selectionTags;
    
    //mem classifier for MVAVarProcessor
    std::unique_ptr<MEMClassifier> pointerToMEMClassifier = nullptr;
    std::unique_ptr<BDTClassifier> pointerToCommonBDT5Classifier = nullptr;
    std::unique_ptr<DLBDTClassifier> pointerToDLBDTClassifier = nullptr;
    std::unique_ptr<DNNClassifier_SL> pointerToDnnSLClassifier = nullptr;
    std::unique_ptr<DNNClassifier_DL> pointerToDnnDLClassifier = nullptr;
    
    std::unique_ptr<ResourceMonitor> ResMon = nullptr;
};

//
// constructors and destructor
//
BoostedAnalyzer::BoostedAnalyzer(const edm::ParameterSet& iConfig): \
    // initialize gen top event with consumes collector (allows to access data from file within this class)
    synchronizer(Synchronizer(iConfig,consumesCollector())),
    genTopEvtProd(GenTopEventProducer(consumesCollector())),
    triggerInfoProd(TriggerInfoProducer(iConfig,consumesCollector())),
    filterInfoProd(FilterInfoProducer(iConfig,consumesCollector()))

{
  
  //set up resource monitor
  ResMon.reset(new ResourceMonitor());
    //
    // get all configurations from the python config
    // meaning of the parameters is explained in python/BoostedAnalyzer_cfi.py
    eventWeight = iConfig.getParameter<double>("eventWeight");
    isData = iConfig.getParameter<bool>("isData");
    useFatJets = iConfig.getParameter<bool>("useFatJets");
    useGenHadronMatch = iConfig.getParameter<bool>("useGenHadronMatch");
    if(isData) useGenHadronMatch=false;
    dumpSyncExe = iConfig.getParameter<bool>("dumpSyncExe");
    dumpExtended = iConfig.getParameter<bool>("dumpExtended");
    dumpAlwaysEvents = iConfig.getParameter<std::vector<int> >("dumpAlwaysEvents");
    usedGenerator = iConfig.getParameter<std::string>("generatorName");
    doBoostedMEM = iConfig.getParameter<bool>("doBoostedMEM");
    outfileNameBase = iConfig.getParameter<std::string>("outfileName");
    relevantTriggers = iConfig.getParameter< std::vector<std::string> >("relevantTriggers");
    processorNames= iConfig.getParameter< std::vector<std::string> >("processorNames");
    selectionNames= iConfig.getParameter< std::vector<std::string> >("selectionNames");
    ProduceMemNtuples = iConfig.getParameter<bool>("memNtuples");
    std::vector<std::string> systematicsNames = iConfig.getParameter<std::vector<std::string> >("systematics");
    taggingSelection= iConfig.getParameter<bool>("taggingSelection");
    nevents_to_process = iConfig.getParameter<int>("nevents_to_process");
    for (auto const &s : systematicsNames){
      jetSystematics.push_back(Systematics::get(s));
    }
   
    for (auto const &s : jetSystematics){
    outfileNames.push_back(outfileName(outfileNameBase,s));
    }
    
    // REGISTER DATA ACCESS
    // This needs to be done in the constructor of this class or via the consumes collector in the constructor of helper classes
    puInfoToken             = consumes< std::vector<PileupSummaryInfo> >(iConfig.getParameter<edm::InputTag>("puInfo") );
    rhoToken                = consumes<double> (iConfig.getParameter<edm::InputTag>("rho") );
    hcalNoiseToken          = consumes< HcalNoiseSummary >(iConfig.getParameter<edm::InputTag>("hcalNoise"));
    beamSpotToken           = consumes< reco::BeamSpot > (iConfig.getParameter<edm::InputTag>("beamSpot"));
    primaryVerticesToken    = consumes< reco::VertexCollection > (iConfig.getParameter<edm::InputTag>("primaryVertices"));
    selectedMuonsToken      = consumes< std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("selectedMuons"));
    selectedMuonsDLToken    = consumes< std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("selectedMuonsDL"));
    selectedMuonsLooseToken      = consumes< std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("selectedMuonsLoose"));
    selectedElectronsToken       = consumes< pat::ElectronCollection >(iConfig.getParameter<edm::InputTag>("selectedElectrons"));
    selectedElectronsDLToken     = consumes< pat::ElectronCollection >(iConfig.getParameter<edm::InputTag>("selectedElectronsDL"));
    selectedElectronsLooseToken  = consumes< pat::ElectronCollection >(iConfig.getParameter<edm::InputTag>("selectedElectronsLoose"));
    selectedTausToken       = consumes< pat::TauCollection >(iConfig.getParameter<edm::InputTag>("selectedTaus"));
    selectedPhotonsLooseToken       = consumes< pat::PhotonCollection >(iConfig.getParameter<edm::InputTag>("selectedPhotonsLoose"));
    for(auto &tag : iConfig.getParameter<std::vector<edm::InputTag> >("selectedJets")){
	     selectedJetsTokens.push_back(consumes< std::vector<pat::Jet> >(tag));
    }
    for(auto &tag : iConfig.getParameter<std::vector<edm::InputTag> >("selectedJetsLoose")){
	     selectedJetsLooseTokens.push_back(consumes< std::vector<pat::Jet> >(tag));
    }
    for(auto &tag : iConfig.getParameter<std::vector<edm::InputTag> >("AK8Jets")){
	     AK8Jets_Tokens.push_back(consumes< std::vector<pat::Jet> >(tag));
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
    LHERunInfoToken = consumes<LHERunInfoProduct,edm::InRun>(edm::InputTag("externalLHEProducer"));
    
    customGenElectrons = consumes< std::vector<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("customGenElectrons"));
    customGenMuons = consumes< std::vector<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("customGenMuons"));
    customGenTaus = consumes< std::vector<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("customGenTaus"));
    customGenPhotons = consumes< std::vector<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("customGenPhotons"));
    customGenJets = consumes< std::vector<reco::GenJet> >(iConfig.getParameter<edm::InputTag>("customGenJets"));
    customGenJetsLoose = consumes< std::vector<reco::GenJet> >(iConfig.getParameter<edm::InputTag>("customGenJetsLoose"));
    customGenJetsAK8 = consumes< std::vector<reco::GenJet> >(iConfig.getParameter<edm::InputTag>("customGenJetsAK8"));
    
    // initialize helper classes
    helper.SetUp("2015_74x", isData ? -1 : 1, analysisType::LJ, isData);

    // initialize CSV reweighter
    if( iConfig.existsAs<edm::ParameterSet>("bTagSFs",true) ) {
      const edm::ParameterSet bTagSFsPS = iConfig.getParameter<edm::ParameterSet>("bTagSFs");
      csvReweighter.init( bTagSFsPS.getParameter<std::string>("fileNameHF"),
			  bTagSFsPS.getParameter<std::string>("fileNameLF"),
			  bTagSFsPS.getParameter<int>("nHFPtBins"),
                          bTagSFsPS.getParameter<int>("nLFPtBins"),
                          bTagSFsPS.getParameter<int>("nLFEtaBins"),
                          jetSystematics
                        );
      if( bTagSFsPS.existsAs<bool>("AllowJetsOutOfBinning",true) ) {
	csvReweighter.allowJetsOutOfBinning(bTagSFsPS.getParameter<bool>("AllowJetsOutOfBinning"));
      }
    }

    // INITIALIZE PU WEIGHTS
    puWeights.init(iConfig);

    // initialize cutflows
    for (size_t i=0; i<jetSystematics.size();i++){
        cutflows.push_back(Cutflow());
        cutflows.back().Init();
    }
    

    // initialize selections
    // add requested selections
    for(const auto& itSel : selectionNames) {
	cout << "Initializing " << itSel << endl;
        std::unique_ptr<Selection> selection = nullptr;
	if(itSel == "VertexSelection") selection.reset(new VertexSelection());
	else if(itSel == "FilterSelection") selection.reset(new FilterSelection(iConfig));
	else if(itSel == "EvenSelection") selection.reset(new EvenOddSelection(true));
	else if(itSel == "OddSelection") selection.reset(new EvenOddSelection(false));
	else if(itSel == "GenTopFHSelection") selection.reset(new GenTopFHSelection());
	else if(itSel == "GenTopSLSelection") selection.reset(new GenTopSLSelection());
	else if(itSel == "GenTopDLSelection") selection.reset(new GenTopDLSelection());
	else if(itSel == "LeptonSelection") selection.reset(new LeptonSelection(iConfig));
        else if(itSel == "LeptonSelection_QCDControlregion") selection.reset(new LeptonSelection_QCDControlregion(iConfig));
	else if(itSel == "LooseLeptonSelection") selection.reset(new LooseLeptonSelection(iConfig));
	else if(itSel == "JetTagSelection") selection.reset(new JetTagSelection(iConfig));
	else if(itSel == "DiLeptonJetTagSelection") selection.reset(new DiLeptonJetTagSelection(iConfig));
	else if(itSel == "DiLeptonSelection") selection.reset(new DiLeptonSelection(iConfig));
	else if(itSel == "MinDiLeptonMassSelection") selection.reset(new DiLeptonMassSelection(20.,9999.));
	else if(itSel == "ZVetoSelection") selection.reset(new DiLeptonMassSelection(76.,106,true,false));
	else if(itSel == "ZWindowSelection") selection.reset(new DiLeptonMassSelection(76.,106,false));
	else if(itSel == "METSelection") selection.reset(new METSelection(iConfig));
	else if(itSel == "DiLeptonMETSelection") selection.reset(new DiLeptonMETSelection(iConfig));
	else if(itSel == "HbbSelection") selection.reset(new HbbSelection());
	else if(itSel == "4JetSelection") selection.reset(new JetTagSelection(4,-1));
	else if(itSel == "2TagSelection") selection.reset(new JetTagSelection(-1,2));
	else if(itSel == "BoostedTopSelection") selection.reset(new BoostedSelection(1,0));
	else if(itSel == "BoostedSelection") selection.reset(new BoostedSelection(0,1));
        else if(itSel == "MonoJetSelection") selection.reset(new MonoJetSelection(iConfig));
        else if(itSel == "LeptonVetoSelection") selection.reset(new LeptonVetoSelection());
        else if(itSel == "BTagVetoSelection") selection.reset(new BTagVetoSelection());
        else if(itSel == "PhotonVetoSelection") selection.reset(new PhotonVetoSelection());
        else if (itSel == "monoVselection") selection.reset(new monoVselection(iConfig));
	else {
            cout << "No matching selection found for: " << itSel << endl;
            continue;
        }
        selections.push_back(std::move(selection));
	// connect added selection to cutflow
	for (auto &c : cutflows){
	    selections.back()->InitCutflow(c);
	}
	// dump some event info after selection step
    }
    // find the position of the JetTagSelection to check later if the failed selection is the JetTagSelection or not
    jet_tag_pos = find (selectionNames.begin(), selectionNames.end(), "JetTagSelection") - selectionNames.begin();
    
    pointerToMEMClassifier.reset(new MEMClassifier());
    pointerToCommonBDT5Classifier.reset(new BDTClassifier(string(getenv("CMSSW_BASE"))+"/src/TTH/CommonClassifier/data/lj_BDT_DeepCSV_Summer18_v1/"));
    DNNClassifierBase::pyInitialize();
    pointerToDnnSLClassifier.reset(new DNNClassifier_SL("v6a"));
    
    // initialize synchronizer
    if(dumpSyncExe){
        pointerToDLBDTClassifier.reset(new DLBDTClassifier(string(getenv("CMSSW_BASE"))+"/src/TTH/CommonClassifier/data/dlbdtweights_v5/"));
        pointerToDnnDLClassifier.reset(new DNNClassifier_DL("v3a"));
        synchronizer.Init(outfileNameBase,systematicsNames,iConfig,&helper,&leptonSFhelper,pointerToCommonBDT5Classifier.get(),pointerToDLBDTClassifier.get(),pointerToDnnSLClassifier.get(),pointerToDnnDLClassifier.get(),pointerToMEMClassifier.get(),dumpExtended);
    }

    // INITIALIZE TREEWRITERs
    if(!ProduceMemNtuples) {
        for (size_t i=0; i<jetSystematics.size();i++){
            cout << "creating tree writer " << outfileNames[i] << endl;
            std::unique_ptr<TreeWriter> treewriter(new TreeWriter());
            treewriters.push_back(std::move(treewriter));
            treewriters.back()->Init(outfileNames[i]);
        }
    }
    else {
        cout << "creating tree writer " << "slimmed_ntuples" << endl;
        std::unique_ptr<TreeWriter> treewriter(new TreeWriter());
        treewriters.push_back(std::move(treewriter));
        treewriters.back()->Init(outfileNameBase+"_slimmed_ntuples");
    }
    // add processors to first tree writer
    cout << "using processors:" << endl;
    for(const auto& itPro : processorNames) {
	     cout << itPro << endl;
    }
    // add processors that have been requested in the config
    for(auto& treewriter : treewriters){
	     if(std::find(processorNames.begin(),processorNames.end(),"WeightProcessor")!=processorNames.end()) {
		treewriter->AddTreeProcessor(new WeightProcessor(),"WeightProcessor");
	     }
	     if(std::find(processorNames.begin(),processorNames.end(),"BasicVarProcessor")!=processorNames.end()) {
		treewriter->AddTreeProcessor(new BasicVarProcessor(),"BasicVarProcessor");
	     }
	     if(std::find(processorNames.begin(),processorNames.end(),"essentialBasicVarProcessor")!=processorNames.end()) {
		treewriter->AddTreeProcessor(new essentialBasicVarProcessor(),"essentialBasicVarProcessor");
	     }
	if(std::find(processorNames.begin(),processorNames.end(),"MVAVarProcessor")!=processorNames.end()) {
	    if(std::find(processorNames.begin(),processorNames.end(),"BasicVarProcessor")==processorNames.end()) {
		cout << "adding BasicVarProcessor, needed for MVAVarProcessor" << endl;
		treewriter->AddTreeProcessor(new BasicVarProcessor(),"BasicVarProcessor");
	    }
	    treewriter->AddTreeProcessor(new MVAVarProcessor(pointerToMEMClassifier.get()),"MVAVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"essentialMVAVarProcessor")!=processorNames.end()) {
	    if(std::find(processorNames.begin(),processorNames.end(),"essentialBasicVarProcessor")==processorNames.end()) {
		cout << "adding essentialBasicVarProcessor, needed for essentialMVAVarProcessor" << endl;
		treewriter->AddTreeProcessor(new essentialBasicVarProcessor(),"essentialBasicVarProcessor");
	    }
	    treewriter->AddTreeProcessor(new essentialMVAVarProcessor(pointerToMEMClassifier.get()),"essentialMVAVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"StdTopVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new StdTopVarProcessor(),"StdTopVarProcessor");
	}
        //if(std::find(processorNames.begin(),processorNames.end(),"BoostedJetVarProcessor")!=processorNames.end()) {
            //treewriter->AddTreeProcessor(new BoostedJetVarProcessor(&helper),"BoostedJetVarProcessor");
        //}
        //if(std::find(processorNames.begin(),processorNames.end(),"BoostedAk4VarProcessor")!=processorNames.end()) {
            //treewriter->AddTreeProcessor(new BoostedAk4VarProcessor(),"BoostedAk4VarProcessor");
        //}
        //if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopHiggsVarProcessor")!=processorNames.end()) {
        //treewriter->AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",boosted::SubjetType::SF_Filter,HiggsTag::SecondCSV,"","BoostedTopHiggs_",doBoostedMEM),"BoostedTopHiggsVarProcessor");
        //}
        //if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopVarProcessor")!=processorNames.end()) {
        //treewriter->AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",boosted::SubjetType::SF_Filter,HiggsTag::SecondCSV,"","BoostedTop_"),"BoostedTopVarProcessor");
        //}
        //if(std::find(processorNames.begin(),processorNames.end(),"BoostedHiggsVarProcessor")!=processorNames.end()) {
        //treewriter->AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",boosted::SubjetType::SF_Filter,HiggsTag::SecondCSV,"","BoostedHiggs_"),"BoostedHiggsVarProcessor");
        //}
        //if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopAk4HiggsVarProcessor")!=processorNames.end()) {
        //treewriter->AddTreeProcessor(new //ttHVarProcessor(BoostedRecoType::BoostedTopAk4Higgs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",boosted::SubjetType::SF_Filter,HiggsTag::SecondCSV,"","BoostedTopAk4Higgs_",doBoostedMEM),"BoostedTopAk4HiggsVarProcessor");
        //}
        //if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopAk4HiggsFromAk4CVarProcessor")!=processorNames.end()) {
        //treewriter->AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopAk4HiggsFromAk4C,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",boosted::SubjetType::SF_Filter,HiggsTag::SecondCSV,"","BoostedTopAk4HiggsFromAk4Cluster_",doBoostedMEM),"BoostedTopAk4HiggsFromAk4CVarProcessor");
        //}
	if(std::find(processorNames.begin(),processorNames.end(),"BDTVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new BDTVarProcessor(pointerToCommonBDT5Classifier.get()),"BDTVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"DNNVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new DNNVarProcessor(pointerToDnnSLClassifier.get()),"DNNVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"MCMatchVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new MCMatchVarProcessor(),"MCMatchVarProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"essentialMCMatchVarProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new essentialMCMatchVarProcessor(),"essentialMCMatchVarProcessor");
	}
	//if(std::find(processorNames.begin(),processorNames.end(),"BoostedMCMatchVarProcessor")!=processorNames.end()) {
	    //treewriter->AddTreeProcessor(new BoostedMCMatchVarProcessor(),"BoostedMCMatchVarProcessor");
	//}
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
	if(std::find(processorNames.begin(),processorNames.end(),"SpinCorrelationProcessor")!=processorNames.end()) {
	    treewriter->AddTreeProcessor(new SpinCorrelationProcessor(),"SpinCorrelationProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"GenJetOrderedJetCollectionProcessor")!=processorNames.end()) {
	  treewriter->AddTreeProcessor(new GenJetOrderedJetCollectionProcessor,"GenJetOrderedJetCollectionProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"TTBBStudienProcessor")!=processorNames.end()) {
	  treewriter->AddTreeProcessor(new TTBBStudienProcessor,"TTBBStudienProcessor");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"SlimmedNtuples")!=processorNames.end()) {
	  treewriter->AddTreeProcessor(new SlimmedNtuples(),"SlimmedNtuples");
	}
	if(std::find(processorNames.begin(),processorNames.end(),"DarkMatterProcessor")!=processorNames.end()) {
		treewriter->AddTreeProcessor(new DarkMatterProcessor(),"DarkMatterProcessor");
        }
        if(std::find(processorNames.begin(),processorNames.end(),"MonoJetGenSelectionProcessor")!=processorNames.end()) {
		treewriter->AddTreeProcessor(new MonoJetGenSelectionProcessor(),"MonoJetGenSelectionProcessor");
        }
    if(std::find(processorNames.begin(),processorNames.end(),"SelectionTagProcessor")!=processorNames.end()) {
        treewriter->AddTreeProcessor(new SelectionTagProcessor(),"SelectionTagProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"BosonWeightProcessor")!=processorNames.end()) {
        treewriter->AddTreeProcessor(new BosonWeightProcessor(),"BosonWeightProcessor");
    }
    }

    // Genweights: Initialize the weightnames for the generator, that was used for this sample
    /*
    if (usedGenerator == "POWHEG"){ generatorflag = genweights.SetGenerator(Generator::POWHEG); }
    else if (usedGenerator == "aMC"){ generatorflag = genweights.SetGenerator(Generator::aMC);}
    else if (usedGenerator == "MadGraph"){ generatorflag = genweights.SetGenerator(Generator::MadGraph);}
    else if (usedGenerator == "pythia8"){ generatorflag = genweights.SetGenerator(Generator::pythia8);}
    else{ generatorflag = false; }
    */
    std::vector<std::string> pdfs = {"NNPDF30_nlo_nf_5_pdfas"};
    genweights.initLHAPDF(pdfs);

    assert(selectedJetsTokens.size()==selectedJetsLooseTokens.size());
    assert(selectedJetsTokens.size()==jetSystematics.size());
    assert(selectedJetsTokens.size()==cutflows.size());
}


BoostedAnalyzer::~BoostedAnalyzer()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
  //delete pointerToMEMClassifier;
  //delete pointerToCommonBDT5Classifier;
  //delete pointerToDnnSLClassifier;
  //if(dumpSyncExe) {
      //delete pointerToDLBDTClassifier;
      //delete pointerToDnnDLClassifier;
  //}
  DNNClassifierBase::pyFinalize();
  //delete ResMon;
}


//
// member functions
//

// ------------ method called for each event  ------------
void BoostedAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    if(eventcount<20||eventcount%1000==0){
	cout << "Analyzing event " << eventcount << endl;
	watch.Print();
	watch.Continue();
	ResMon->PrintMemoryUsage();
	ResMon->PrintSystemMemory();
	
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
    
    // TAUS
    edm::Handle< pat::TauCollection > h_selectedTaus;
    iEvent.getByToken( selectedTausToken,h_selectedTaus );
    
    // PHOTONS
    edm::Handle< pat::PhotonCollection > h_selectedPhotonsLoose;
    iEvent.getByToken( selectedPhotonsLooseToken,h_selectedPhotonsLoose );
    
    // JETs
    std::vector<edm::Handle< pat::JetCollection > >hs_selectedJets;
    std::vector<edm::Handle< pat::JetCollection > >hs_selectedJetsLoose;
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
    
    //AK8PFCHSSoftDropPackedJets
    std::vector<edm::Handle< pat::JetCollection > > hs_AK8Jets;
    for(auto & AK8JetsToken : AK8Jets_Tokens){
    	edm::Handle< pat::JetCollection > h_AK8Jets;
    	iEvent.getByToken( AK8JetsToken,h_AK8Jets );
    	hs_AK8Jets.push_back(h_AK8Jets);
    }
    
    // MET
    std::vector<edm::Handle< pat::METCollection > > hs_correctedMETs;
    for(auto & correctedMETsToken : correctedMETsTokens){
	edm::Handle< pat::METCollection > h_correctedMETs;
	iEvent.getByToken( correctedMETsToken,h_correctedMETs );
	hs_correctedMETs.push_back(h_correctedMETs);
    }

    // MC only (generator weights for example)
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
    
    edm::Handle< std::vector<reco::GenParticle> > CustomGenElectrons;
    edm::Handle< std::vector<reco::GenParticle> > CustomGenMuons;
    edm::Handle< std::vector<reco::GenParticle> > CustomGenTaus;
    edm::Handle< std::vector<reco::GenParticle> > CustomGenPhotons;
    edm::Handle< std::vector<reco::GenJet> > CustomGenJets;
    edm::Handle< std::vector<reco::GenJet> > CustomGenJetsLoose;
    edm::Handle< std::vector<reco::GenJet> > CustomGenJetsAK8;
    if(!isData){
    	iEvent.getByToken( customGenElectrons,CustomGenElectrons );
    	iEvent.getByToken( customGenMuons,CustomGenMuons );
    	iEvent.getByToken( customGenTaus,CustomGenTaus );
        iEvent.getByToken( customGenPhotons,CustomGenPhotons );
    	iEvent.getByToken( customGenJets,CustomGenJets );
    	iEvent.getByToken( customGenJetsLoose,CustomGenJetsLoose );
        iEvent.getByToken( customGenJetsAK8,CustomGenJetsAK8 );
    }
    // selected vertices and set vertex for MiniAODhelper
    // TODO: vertex selection in external producer
    reco::VertexCollection const &vtxs = *h_primaryVertices;
    reco::VertexCollection selectedPVs;
    bool firstVertexIsGood=false;
    bool isFirst=true;
    if( h_primaryVertices.isValid() ){
	for( const auto& itvtx : vtxs ){
	    bool isGood = ( !(itvtx.isFake()) &&
			    (itvtx.ndof() >= 4.0) &&
			    (abs(itvtx.z()) <= 24.0) &&
			    (abs(itvtx.position().Rho()) <= 2.0)
			    );
	    if( isGood ) selectedPVs.push_back(itvtx);
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
    	boosted::BoostedJetCollection idBoostedJets = helper.GetSelectedBoostedJets(boostedjets, 0., 9999., 0., 9999., jetID::jetLoose, "A");
    	for(auto syst : jetSystematics){
    	    boosted::BoostedJetCollection correctedBoostedJets = helper.GetCorrectedBoostedJets(idBoostedJets, iEvent, iSetup, h_genJets, syst, true, true);
    	    selectedBoostedJets.push_back(helper.GetSelectedBoostedJets(correctedBoostedJets, 200., 2.0, 20., 2.4, jetID::none, "A"));
    	}
    }
    else{
    	for(size_t i =0; i<jetSystematics.size();i++){
    	    selectedBoostedJets.push_back(boosted::BoostedJetCollection());
    	}
    }

    // Get CA15 Ak4 jet cluster (alternative to CA15 fatjets)
    pat::JetCollection ak4Jets = *(hs_selectedJets[0]);
    boosted::Ak4ClusterCollection ak4Cluster = Ak4Cluster::GetAk4Cluster(ak4Jets, 0);
    boosted::Ak4ClusterCollection selectedAk4Cluster = Ak4Cluster::GetSelectedAk4Cluster(ak4Cluster, 200., "A");
    

    // Fill Event Info Object
    EventInfo eventInfo(iEvent,h_beamSpot,h_hcalNoiseSummary,h_puInfo,firstVertexIsGood,*h_rho);
    TriggerInfo triggerInfo = triggerInfoProd.Produce(iEvent);
    FilterInfo filterInfo = filterInfoProd.Produce(iEvent);

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
		for(size_t j=0;j<genParticles[i].numberOfDaughters();j++){
		    if (abs(genParticles[i].daughter(j)->pdgId())==5){
			higgsdecay=HiggsDecay::bb;
		    }
		}
	    }
	}
    }
    GenTopEvent genTopEvt;//genTopEvtProd.Produce(iEvent,useGenHadronMatch,!(!isData&&foundT&&foundTbar));
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
    
    // create GenDarkMatterEvent object
    GenDarkMatterEvent genDarkMatterEvent;
    // create empty packedGenParticle dummy since this collection is not yet needed, but maybe later
    std::vector<pat::PackedGenParticle> packedGenParticles_dummy;
    // initialze the GenDarkMatterEvent object with the collections of genparticles
    if(!isData){
    	genDarkMatterEvent.Initialize(*h_genParticles,packedGenParticles_dummy);
    	// fill the event
    	genDarkMatterEvent.Fill();
        genDarkMatterEvent.FillBoson();
    	//cout << "DarkMatterEvent MET: " << genDarkMatterEvent.ReturnNaiveMET() << endl;
    }
    
    // nominal weight and weights for reweighting
    std::vector<map<string,float> >weightsVector;
    //selectiontags
    // map<string, int> &pselectionTags = *selectionTags;
    // map<string, int>* selectionTags = new map<string, int>() ;
    map<string, int> selectionTags;

    // inputs
    std::vector<InputCollections> inputs;
    for(size_t isys=0; isys<jetSystematics.size(); isys++){
        auto weights = GetWeights(*h_genInfo,*h_lheInfo,eventInfo,selectedPVs,*(hs_selectedJets[isys]),*(hs_selectedJetsLoose[isys]),*h_selectedElectrons,*h_selectedMuons,genTopEvt,jetSystematics[isys]);
	inputs.push_back(InputCollections(eventInfo,
					  triggerInfo,
					  filterInfo,
					  selectedPVs,
					  *h_selectedMuons,
					  *h_selectedMuonsDL,
					  *h_selectedMuonsLoose,
					  *h_selectedElectrons,
					  *h_selectedElectronsDL,
					  *h_selectedElectronsLoose,
                                          *h_selectedTaus,
                                          *h_selectedPhotonsLoose,
					  *(hs_selectedJets[isys]),
					  *(hs_selectedJetsLoose[isys]),
                                          *(hs_AK8Jets[isys]),
					  (*(hs_correctedMETs[isys]))[0],
					  selectedBoostedJets[isys],
                                          selectedAk4Cluster,
					  genTopEvt,
                                          genDarkMatterEvent,
					  *h_genJets,
					  sampleType,
					  higgsdecay,
					  weights,
					  iEvent,
					  iSetup,
                                          jetSystematics[isys],
                                          *CustomGenJets,
                                          *CustomGenJetsLoose,
                                          *CustomGenJetsAK8,
                                          *CustomGenElectrons,
                                          *CustomGenMuons,
                                          *CustomGenTaus,
                                          *CustomGenPhotons,
                      selectionTags

					  ));

    }
    // TODO: adapt to new synch exe

    if(dumpSyncExe){
	synchronizer.DumpSyncExe(inputs,dumpExtended, dumpAlwaysEvents);
    }

    assert(inputs.size()==cutflows.size());
    assert(inputs.size()==jetSystematics.size());
    // flag to identifiy if the event is selected for at least one of the possible jet collections corresponding to the jec sources
    bool at_least_one_selected=false;
    // flag to identify if the event does not fulfill selection criteria independent of the jet collections (vertex,filter,lepton) so it can be skipped no matter which jet collection is looked at
    bool next_event = false;
    // DO SELECTION
    // loop over jet systematics
    for(size_t i_sys=0; i_sys<jetSystematics.size(); i_sys++){
    	// all events survive step 0
        cutflows[i_sys].EventSurvivedStep("all",inputs[i_sys].weights.at("Weight"));
        // start with selection=true and change this if one selection fails
    	bool selected=true;
    	// for every systematic: loop over selections
        for(size_t i_sel=0; i_sel<selections.size() && selected; i_sel++){
            // see if event is selected
            if(!taggingSelection){
                // std::cout << "not running in tagging mode" << std::endl;        
        	    if(!selections.at(i_sel)->IsSelected(inputs[i_sys],cutflows[i_sys])){
        		    selected=false;
                    // if the vertex,filter or lepton selection is not fulfilled, set the flag to skip the other jec variations
                    if(!selected && i_sel!=jet_tag_pos && jet_tag_pos!=selections.size()) next_event=true;
        	    }
        	}
            else{
                selected=true;
                next_event=false;
                selectionTags[selectionNames.at(i_sel)] = selections.at(i_sel)->IsSelected(inputs[i_sys],cutflows[i_sys]); 
            }
        }
        // if the vertex,filter or lepton selection is not fulfilled, skip the other jec variations
        if(next_event) break;
        // if one of the jet collections fulfills the selection and mem ntuples are supposed to be written, skip the checks for the other jet collections and go directly to writing 
        at_least_one_selected = at_least_one_selected || selected;
        if(ProduceMemNtuples&&at_least_one_selected) break;
        // if normal ntuples are supposed to be written and the selections are fulfilled for the jet collection, then write
        if(!ProduceMemNtuples&&selected) treewriters[i_sys]->Process(inputs[i_sys], false);    // second parameter: verbose
    }
    // write the mem ntuples if the mem ntuples flag is set and at least one jet collection fulfills the selection criteria
    if(ProduceMemNtuples&&at_least_one_selected) treewriters.back()->Process(inputs, false);
    

}

float BoostedAnalyzer::GetTopPtWeight(const float& toppt1,const float& toppt2){
    float sf1=exp(0.0615-0.0005*toppt1);
    float sf2=exp(0.0615-0.0005*toppt2);
    return sqrt(sf1*sf2);
}

map<string,float> BoostedAnalyzer::GetWeights(const GenEventInfoProduct&  genInfo, const LHEEventProduct&  lheInfo, const EventInfo& eventInfo, const reco::VertexCollection& selectedPVs, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Jet>& selectedJetsLoose, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon>& selectedMuons, const GenTopEvent& genTopEvt, const Systematics::Type& systype){
    map<string,float> weights;

    if(isData){
	weights["Weight"] = 1.0;
	weights["Weight_XS"] = 1.0;
	weights["Weight_CSV"] = 1.0;
	weights["Weight_PU"] = 1.0;
 	weights["Weight_TopPt"] = 1.0;
	weights["Weight_PV"] = 1.0;
	weights["Weight_GenValue"] = 1.0;
        weights["Weight_GEN_nom"] = 1.0;
	return weights;
    }

    // start with weight equals 1
    float weight = 1.;
    float weight_GenValue=1.0;
    
    // set weight +1 if nominal genweight > 0 and -1 if nominal genweight < 0
    // set weight_GenValue to nominal genweight
    if(genInfo.weights().size()>0){
	weight = genInfo.weights()[0]>0 ? 1.: -1.;
	weight_GenValue = genInfo.weights()[0];
    }

    //dummy variables for the getCSVWeight function, might be useful for checks
    double csvWgtHF, csvWgtLF, csvWgtCF;

    // set xsweight to weight which is given as option in cmsRun command 
    float xsweight = eventWeight;
    float csvweight = 1.;
    float puweight = 1.;
    float topptweight = genTopEvt.IsTTbar()? GetTopPtWeight(genTopEvt.GetHardTop().pt(),genTopEvt.GetHardTopBar().pt()) : 1.;
    //float topptweightUp = 1.0 + 2.0*(topptweight-1.0);
    //float topptweightDown = 1.0;
    
    // create vectors of jet properties
    std::vector<double> jetPts;
    std::vector<double> jetEtas;
    std::vector<double> jetCSVs;
    std::vector<int> jetFlavors;
    
    // fill jet properties
    for(const auto& itJet : selectedJetsLoose){
	jetPts.push_back(itJet.pt());
	jetEtas.push_back(itJet.eta());
	jetCSVs.push_back(helper.GetJetCSV(itJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
	jetFlavors.push_back(itJet.hadronFlavour());
    }
    
    // calculate the csv weight for the desired systematic using the information from the jet properties vectors
    csvweight= csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,systype, csvWgtHF, csvWgtLF, csvWgtCF);
    
    // compute PU weights, and set nominal weight
    puWeights.compute(eventInfo);
    puweight = puWeights.nominalWeight();

    // multiply +1 or -1 with xsweight
    weight *= xsweight;//puweight*csvweight;
    // fill map with weights
    weights["Weight_GenValue"] = weight_GenValue;
    weights["Weight"] = weight;
    weights["Weight_XS"] = xsweight;
    weights["Weight_CSV"] = csvweight;
    weights["Weight_PU"] = puweight;
    weights["Weight_TopPt"] = topptweight;
    
    // weights for csv systmatics
    // only do these for the nominal samples and NOT for JES/JER variations
    bool doSystematics=true;
    if(doSystematics && systype == Systematics::NA) { 
        //std::cout << "Do csv weights for csv systematics " << std::endl;
	weights["Weight_CSVLFup"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVLFup, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVLFdown"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVLFdown, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVHFup"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVHFup, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVHFdown"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVHFdown, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVHFStats1up"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVHFStats1up, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVHFStats1down"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVHFStats1down, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVLFStats1up"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVLFStats1up, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVLFStats1down"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVLFStats1down, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVHFStats2up"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVHFStats2up, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVHFStats2down"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVHFStats2down, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVLFStats2up"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVLFStats2up, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVLFStats2down"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVLFStats2down, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVCErr1up"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVCErr1up, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVCErr1down"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVCErr1down, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVCErr2up"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVCErr2up, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
	weights["Weight_CSVCErr2down"] = csvReweighter.getCSVWeight(jetPts,jetEtas,jetCSVs,jetFlavors,Systematics::CSVCErr2down, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
 	//weights["Weight_TopPtup"] = topptweightUp;
 	//weights["Weight_TopPtdown"] = topptweightDown;
    }
    
    //Add Lepton Scalefactors to weight map
    
    std::map<std::string, float> selectedScaleFactors = leptonSFhelper.GetLeptonSF(selectedElectrons,selectedMuons);

    for(  auto sfit : selectedScaleFactors  ){
      weights["Weight_"+sfit.first] = sfit.second;
    }
    
    // set optional additional PU weights
    for(std::vector<PUWeights::Weight>::const_iterator it = puWeights.additionalWeightsBegin();
	  it != puWeights.additionalWeightsEnd(); ++it) {
	  weights[it->name()] = it->value();
    }
	//Add Genweights to the weight map
    genweights.GetGenWeights(weights, lheInfo);
	//DANGERZONE
    genweights.GetLHAPDFWeight(weights, genInfo );
	//DANGERZONE

    return weights;
}

// function to convert sysType enum to string
std::string BoostedAnalyzer::systName(const Systematics::Type& sysType){
  if( sysType == Systematics::NA ) return "nominal";
  else return Systematics::toString(sysType);
}

// function to create name for output file of BoostedAnalyzer using basename and the sysType 
std::string BoostedAnalyzer::outfileName(const std::string& basename, const Systematics::Type& sysType){
  const std::string systLabel = Systematics::toString(sysType);
  const size_t stringIndex = basename.find("nominal");
  if(stringIndex!=std::string::npos){
    std::string outfileName=basename;
    outfileName.replace(stringIndex,7,systLabel);
    return outfileName;
  }
  if(sysType==Systematics::NA) return basename+"_nominal";
  else return basename+"_"+systLabel;
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
    for (size_t i=0; i<outfileNames.size();i++){
	std::ofstream fout(outfileNames[i]+"_Cutflow.txt");
	cutflows[i].Print(fout);
	fout.close();
    }
    std::cout << "#events to process "<< nevents_to_process << std::endl;
    std::cout << "#events processed " << eventcount << std::endl;
    std::cout << "#events processed / #events to process " << nevents_to_process*1.0/eventcount << std::endl;
    if(nevents_to_process != eventcount) {
        std::cerr << "Possible error: Number of events to process is not the same as the number of events which have been processed. This can happen if the maxevents options is set too low or if a lumi json was used to use only runs which were certified. On MC that should not happen." << std::endl;
        std::cout << "Possible error: Number of events to process is not the same as the number of events which have been processed. This can happen if the maxevents options is set too low or if a lumi json was used to use only runs which were certified. On MC that should not happen." << std::endl;
    }
}

// ------------ method called when starting to processes a run ------------
void BoostedAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup) {
    
    /*
    lhe_weights["1001"]="Weight_muRnmuFn";
    lhe_weights["1002"]="Weight_muRnmuFup";
    lhe_weights["1003"]="Weight_muRnmuFdown";
    lhe_weights["1004"]="Weight_muRupmuFn";
    lhe_weights["1005"]="Weight_muRupmuFup";
    lhe_weights["1006"]="Weight_muRupmuFdown";
    lhe_weights["1007"]="Weight_muRdownmuFn";
    lhe_weights["1008"]="Weight_muRdownmuFup";
    lhe_weights["1009"]="Weight_muRdownmuFdown";
    */
    edm::Handle<LHERunInfoProduct> runhandle;
    //iEvent.getRun()
    iRun.getByLabel("externalLHEProducer",runhandle);
    if(!runhandle.isValid()) {
        cout << "Attention: no genweights will be written because the LHERunInfoProduct is not available!" << endl;
        return;
    }
    LHERunInfoProduct myLHERunInfoProduct = *(runhandle.product());
    genweights.GetNamesFromLHE(myLHERunInfoProduct);
    
}

void BoostedAnalyzer::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup) {
    genweights.Clear();
}

// ------------ method called when starting a luminosity block ------------
void BoostedAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const& iBlock, edm::EventSetup const& iSetup)
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
