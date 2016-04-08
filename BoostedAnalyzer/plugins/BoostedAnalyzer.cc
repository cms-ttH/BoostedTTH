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
#include "BoostedTTH/BoostedAnalyzer/interface/MEMProcessor.hpp"
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
    
    // ----------member data ---------------------------
    
    /** the miniAODhelper is used for selections and reweighting */
    MiniAODHelper helper;
    /** the csv reweighter calculates the event weight from b-tag reweightung */
    CSVHelper csvReweighter;
    // reweight the number of primary vertices distribution
    //      HistoReweighter pvWeight;
    /** reweights the event so that pielup is the same as expected for MC*/
    PUWeights puWeights_;
      
    /** writes flat trees  */
    TreeWriter treewriter_nominal;
    /** writes flat trees for jets with JES shifted up*/
    TreeWriter treewriter_jesup;
    /** writes flat trees for jets with JES shifted down*/
    TreeWriter treewriter_jesdown;
    /** writes flat trees for jets with JER shifted up*/
    TreeWriter treewriter_jerup;
    /** writes flat trees for jets with JER shifted down */
    TreeWriter treewriter_jerdown;
          
    /** stores cutflow*/
    Cutflow cutflow_nominal;
    /** stores cutflow for JES up trees*/
    Cutflow cutflow_jesup;
    /** stores cutflow for JES down trees*/
    Cutflow cutflow_jesdown;
    /** stores cutflow for JER up trees*/
    Cutflow cutflow_jerup;
    /** stores cutflow for JER down trees*/
    Cutflow cutflow_jerdown;
      
    /** selections that are applied before writing the tree*/
    vector<Selection*> selections;
    
    /** triggers that are checked (independtend of the ones used for selected)*/
    vector<std::string> relevantTriggers;

    /** outfile base name*/
    std::string outfileName
    /** nominal outfile base name */;
    std::string outfileNameNominal;
    /** jes up outfile base name */;
    std::string outfileNameJESup;
    /** jes down outfile base name */;
    std::string outfileNameJESdown;
    /** jer up outfile base name */;
    std::string outfileNameJERup;
    /** jer down outfile base name */;
    std::string outfileNameJERdown;

    // not needed:
    //    int sampleID;
      
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

    /** use fat jets? this is only possible if the miniAOD contains them */
    bool useFatJets;

    /** use GenBmatching info? this is only possible if the miniAOD contains them */
    bool useGenHadronMatch;

    /**recorrect the jets and MET that were in MiniAOD? **/
    bool recorrectMET;
      
    /** dump some event content for older synchronization */
    bool dumpSyncExe;
    /** dump some event content for newer synchronization */ 
    bool dumpSyncExe2;
    /** Class that tests objects and event selections */ 
    Synchronizer synchronizer;

    /** write systematics trees (JES and JER up/down) */
    bool makeSystematicsTrees;
    /** really produce JER trees? */
    bool doJERsystematic;

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

    /** loose jets data access token **/
    edm::EDGetTokenT< std::vector<pat::Jet> > selectedJetsToken;

    /** tight jets data access token **/
    edm::EDGetTokenT< std::vector<pat::Jet> > selectedJetsLooseToken;

    /** mets data access token **/
    edm::EDGetTokenT< std::vector<pat::MET> > correctedMETsToken;
      
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
    // initialize CSV reweighter with 76X weights (require only 5 HF pt-bins)
    csvReweighter(CSVHelper("MiniAOD/MiniAODHelper/data/csv_rwt_fit_hf_76x_2016_02_08.root","MiniAOD/MiniAODHelper/data/csv_rwt_fit_lf_76x_2016_02_08.root",5)), \
    // initialize gen top event with consumes collector (allows to access data from file within this class)
    genTopEvtProd(GenTopEventProducer(consumesCollector()))
{
    //
    // get all configurations from the python config
    // meaning of the parameters is explained in python/BoostedAnalyzer_cfi.py
    eventWeight = iConfig.getParameter<double>("eventWeight");
    isData = iConfig.getParameter<bool>("isData");
    useFatJets = iConfig.getParameter<bool>("useFatJets");
    useGenHadronMatch = iConfig.getParameter<bool>("useGenHadronMatch");
    if(isData) useGenHadronMatch=false;
    recorrectMET = iConfig.getParameter<bool>("recorrectMET");
    dumpSyncExe = iConfig.getParameter<bool>("dumpSyncExe");
    dumpSyncExe2 = iConfig.getParameter<bool>("dumpSyncExe2");
    makeSystematicsTrees = iConfig.getParameter<bool>("makeSystematicsTrees");
    doJERsystematic = iConfig.getParameter<bool>("doJERsystematic");
    usedGenerator = iConfig.getParameter<std::string>("generatorName");
    doBoostedMEM = iConfig.getParameter<bool>("doBoostedMEM");
    outfileName = iConfig.getParameter<std::string>("outfileName");
    relevantTriggers = iConfig.getParameter< std::vector<std::string> >("relevantTriggers");
    processorNames= iConfig.getParameter< std::vector<std::string> >("processorNames");
    selectionNames= iConfig.getParameter< std::vector<std::string> >("selectionNames");

    // construct outfile names
    outfileNameNominal=outfileName;
    outfileNameJESup=outfileName;
    outfileNameJESdown=outfileName;
    outfileNameJERup=outfileName;
    outfileNameJERdown=outfileName;
    // if the file name contains nominal it is replaced by JESUP etc for the systematics output
    size_t stringIndex = outfileName.find("nominal");
    if(stringIndex!=std::string::npos){
	outfileNameJESup.replace(stringIndex,7,"JESUP");
	outfileNameJESdown.replace(stringIndex,7,"JESDOWN");
	outfileNameJERup.replace(stringIndex,7,"JERUP");
	outfileNameJERdown.replace(stringIndex,7,"JERDOWN");
    }
    // otherwise nominal, JESUP, etc is appended to the name
    else{
	outfileNameNominal=outfileName+"_nominal";
	outfileNameJESup=outfileName+"_JESUP";
	outfileNameJESdown=outfileName+"_JESDOWN";
	outfileNameJERup=outfileName+"_JERUP";
	outfileNameJERdown=outfileName+"_JERDOWN";
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
    selectedJetsToken            = consumes< std::vector<pat::Jet> >(iConfig.getParameter<edm::InputTag>("selectedJets"));
    selectedJetsLooseToken       = consumes< std::vector<pat::Jet> >(iConfig.getParameter<edm::InputTag>("selectedJetsLoose"));
    correctedMETsToken           = consumes< std::vector<pat::MET> >(iConfig.getParameter<edm::InputTag>("correctedMETs"));
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
    
    // INITIALIZE PU WEIGHTS
    puWeights_.init(iConfig);

    // initialize cutflows
    cutflow_nominal.Init();
    if(makeSystematicsTrees){
	cutflow_jesup.Init();
	cutflow_jesdown.Init();
	if(doJERsystematic){
	    cutflow_jerup.Init();
	    cutflow_jerdown.Init();
	}
    }

    // initialize synchronizer 
    int nselection=0;
    if(dumpSyncExe){
	synchronizer.InitDumpSyncFile1((outfileName+"_Dump1_"+std::to_string(nselection)));
    }
    if(dumpSyncExe2){
	synchronizer.InitDumpSyncFile2(outfileName);
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
	selections.back()->InitCutflow(cutflow_nominal);
	if(makeSystematicsTrees){
	    selections.back()->InitCutflow(cutflow_jesup);
	    selections.back()->InitCutflow(cutflow_jesdown);
	    if(doJERsystematic){
		selections.back()->InitCutflow(cutflow_jerup);
		selections.back()->InitCutflow(cutflow_jerdown);
	    }
	}
	// dump some event info after selection step
	nselection++;     
	if(dumpSyncExe){
	    synchronizer.InitDumpSyncFile1(outfileName+"_Dump1_"+std::to_string(nselection));
	}  
    }


    // INITIALIZE TREEWRITER
    treewriter_nominal.Init(outfileNameNominal);  
    // in case of systematics: initialize additional tree writers that will be used with modified jets
    if(makeSystematicsTrees){
	// this is are the usual tree names
	treewriter_jesup.Init(outfileNameJESup);
	treewriter_jesdown.Init(outfileNameJESdown);
	if(doJERsystematic){
	    treewriter_jerup.Init(outfileNameJERup);
	    treewriter_jerdown.Init(outfileNameJERdown);
	}
    }

    // add processors to nominal tree writers
    cout << "using processors:" << endl; 
    for(vector<string>::const_iterator itPro = processorNames.begin();itPro != processorNames.end();++itPro) {
	cout << *itPro << endl;
    }
    // add processors that have been requested in the config
    if(std::find(processorNames.begin(),processorNames.end(),"WeightProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new WeightProcessor(),"WeightProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"BasicVarProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new BasicVarProcessor(),"BasicVarProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"MVAVarProcessor")!=processorNames.end()) {
	if(std::find(processorNames.begin(),processorNames.end(),"BasicVarProcessor")==processorNames.end()) {
	    cout << "adding BasicVarProcessor, needed for MVAVarProcessor" << endl; 
	    treewriter_nominal.AddTreeProcessor(new BasicVarProcessor(),"MVAVarProcessor");
	}
	treewriter_nominal.AddTreeProcessor(new MVAVarProcessor(),"MVAVarProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"StdTopVarProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new StdTopVarProcessor(),"StdTopVarProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"BoostedJetVarProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new BoostedJetVarProcessor(&helper),"BoostedJetVarProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopHiggsVarProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::SecondCSV,"","BoostedTopHiggs_",doBoostedMEM),"BoostedTopHiggsVarProcessor");
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::HEP,TopTag::Pt,"",HiggsTag::DoubleCSV,"","BoostedTopHiggs_"));
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::HEP,TopTag::CSV,"",HiggsTag::DoubleCSV,"","BoostedTopHiggs_"));
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::Likelihood,TopTag::CSV,"toplikelihoodtaggerhistos.root",HiggsTag::DoubleCSV,"","BoostedTopHiggs_"));
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::DoubleCSV,"","BoostedTopHiggs_"));
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_PSO.weights.xml",HiggsTag::DoubleCSV,"","BoostedTopHiggs_"));
    }
    if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopVarProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::SecondCSV,"","BoostedTop_"),"BoostedTopVarProcessor");
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::HEP,TopTag::Pt,"",HiggsTag::DoubleCSV,"","BoostedTop_"));
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::HEP,TopTag::CSV,"",HiggsTag::DoubleCSV,"","BoostedTop_"));
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::Likelihood,TopTag::CSV,"toplikelihoodtaggerhistos.root",HiggsTag::DoubleCSV,"","BoostedTop_"));
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::DoubleCSV,"","BoostedTop_"));
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_PSO.weights.xml",HiggsTag::DoubleCSV,"","BoostedTop_"));
    }
    if(std::find(processorNames.begin(),processorNames.end(),"BoostedHiggsVarProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::SecondCSV,"","BoostedHiggs_"),"BoostedHiggsVarProcessor");
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::HEP,TopTag::Pt,"",HiggsTag::DoubleCSV,"","BoostedHiggs_"));
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::HEP,TopTag::CSV,"",HiggsTag::DoubleCSV,"","BoostedHiggs_"));
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::Likelihood,TopTag::CSV,"toplikelihoodtaggerhistos.root",HiggsTag::DoubleCSV,"","BoostedHiggs_"));
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::DoubleCSV,"","BoostedHiggs_"));
	//treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_PSO.weights.xml",HiggsTag::DoubleCSV,"","BoostedHiggs_"));
    }
    if(std::find(processorNames.begin(),processorNames.end(),"BDTVarProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new BDTVarProcessor(),"BDTVarProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"MEMProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new MEMProcessor(iConfig),"MEMProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"MCMatchVarProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new MCMatchVarProcessor(),"MCMatchVarProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"BoostedMCMatchVarProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new BoostedMCMatchVarProcessor(),"BoostedMCMatchVarProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"AdditionalJetProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new AdditionalJetProcessor(),"AdditionalJetProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"DiLeptonVarProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new DiLeptonVarProcessor(),"DiLeptonVarProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"TriggerVarProcessor")!=processorNames.end()) {
	// TODO how to handle this? -- what?
	treewriter_nominal.AddTreeProcessor(new TriggerVarProcessor(relevantTriggers),"TriggerVarProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"TTbarReconstructionVarProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new TTbarReconstructionVarProcessor(),"TTbarReconstructionVarProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"ReconstructionMEvarProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new ReconstructionMEvarProcessor(),"ReconstructionMEvarProcessor");
    }
    if(std::find(processorNames.begin(),processorNames.end(),"BJetnessProcessor")!=processorNames.end()) {
	treewriter_nominal.AddTreeProcessor(new BJetnessProcessor(consumesCollector()),"BJetnessProcessor");
    }
    
    // add processors to systematics tree writers
    // the systematics tree writers use the same processors that are used for the nominal trees
    // it might improve the performance to turn some of them off
    if(makeSystematicsTrees){
	std::vector<TreeProcessor*> tps = treewriter_nominal.GetTreeProcessors();
	std::vector<string> tpsn = treewriter_nominal.GetTreeProcessorNames();
	for(uint i=0; i<tps.size();i++){
	    treewriter_jesup.AddTreeProcessor(tps[i],tpsn[i]);
	    treewriter_jesdown.AddTreeProcessor(tps[i],tpsn[i]);
	    if(doJERsystematic){
		treewriter_jerup.AddTreeProcessor(tps[i],tpsn[i]);
		treewriter_jerdown.AddTreeProcessor(tps[i],tpsn[i]);
	    }
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
    edm::Handle< pat::JetCollection > h_selectedJets;
    edm::Handle< pat::JetCollection > h_selectedJetsLoose;
    iEvent.getByToken( selectedJetsToken,h_selectedJets );
    iEvent.getByToken( selectedJetsLooseToken,h_selectedJetsLoose );
    // TODO: get systematics jets
    // METs
    edm::Handle< std::vector<pat::MET> > h_correctedMETs;
    iEvent.getByToken( correctedMETsToken,h_correctedMETs );
    // get MC only stugg
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
    const JetCorrector* ak8corrector = JetCorrector::getJetCorrector( "ak8PFchsL1L2L3", iSetup );
    helper.SetBoostedJetCorrector(ak8corrector);
    edm::Handle<boosted::BoostedJetCollection> h_boostedjet;
    boosted::BoostedJetCollection selectedBoostedJets;
    boosted::BoostedJetCollection selectedBoostedJets_uncorrected;
    boosted::BoostedJetCollection selectedBoostedJets_jesup;
    boosted::BoostedJetCollection selectedBoostedJets_jesdown;
    boosted::BoostedJetCollection selectedBoostedJets_jerup;
    boosted::BoostedJetCollection selectedBoostedJets_jerdown;
    if(useFatJets){
	iEvent.getByToken( boostedJetsToken,h_boostedjet);
	boosted::BoostedJetCollection const &boostedjets_unsorted = *h_boostedjet;
	boosted::BoostedJetCollection boostedjets = BoostedUtils::GetSortedByPt(boostedjets_unsorted);
	boosted::BoostedJetCollection idBoostedJets = helper.GetSelectedBoostedJets(boostedjets, 0., 9999., 0., 9999., jetID::jetLoose);
	boosted::BoostedJetCollection correctedBoostedJets = helper.GetCorrectedBoostedJets(idBoostedJets, iEvent, iSetup, sysType::NA, true, true);
	selectedBoostedJets = helper.GetSelectedBoostedJets(correctedBoostedJets, 200., 2.0, 20., 2.4, jetID::none);
	//selectedBoostedJets = helper.GetSelectedBoostedJets(boostedjets, 200., 2.0, 20., 2.4, jetID::jetLoose);
	selectedBoostedJets_uncorrected = helper.GetSelectedBoostedJets(idBoostedJets, 200., 2.0, 20., 2.4, jetID::none);
	
	if(makeSystematicsTrees){
	    boosted::BoostedJetCollection correctedBoostedJets_jesup = helper.GetCorrectedBoostedJets(idBoostedJets, iEvent, iSetup, sysType::JESup, true, true);
	    boosted::BoostedJetCollection correctedBoostedJets_jesdown = helper.GetCorrectedBoostedJets(idBoostedJets, iEvent, iSetup, sysType::JESdown, true, true);
	    
	    selectedBoostedJets_jesup = helper.GetSelectedBoostedJets(correctedBoostedJets_jesup, 200., 2.0, 20., 2.4, jetID::none);
	    selectedBoostedJets_jesdown = helper.GetSelectedBoostedJets(correctedBoostedJets_jesdown, 200., 2.0, 20., 2.4, jetID::none);
	    
	    if(makeSystematicsTrees){
		boosted::BoostedJetCollection correctedBoostedJets_jerup = helper.GetCorrectedBoostedJets(idBoostedJets, iEvent, iSetup, sysType::JERup, true, true);
		boosted::BoostedJetCollection correctedBoostedJets_jerdown = helper.GetCorrectedBoostedJets(idBoostedJets, iEvent, iSetup, sysType::JERdown, true, true);
		
		selectedBoostedJets_jerup = helper.GetSelectedBoostedJets(correctedBoostedJets_jerup, 200., 2.0, 20., 2.4, jetID::none);
		selectedBoostedJets_jerdown = helper.GetSelectedBoostedJets(correctedBoostedJets_jerdown, 200., 2.0, 20., 2.4, jetID::none);
	    }
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
    
    // DO REWEIGHTING
    map<string,float> weights = GetWeights(*h_genInfo,*h_lheInfo,eventInfo,selectedPVs,*h_selectedJets,*h_selectedElectrons,*h_selectedMuons,genTopEvt,sysType::NA);
    // TODO systematics
    /*    map<string,float> weights_jesup = GetWeights(*h_genInfo,*h_lheevent,eventInfo,selectedPVs,selectedJets_jesup,selectedElectrons,selectedMuons,genTopEvt,sysType::JESup);
    map<string,float> weights_jesdown = GetWeights(*h_genInfo,*h_lheevent,eventInfo,selectedPVs,selectedJets_jesdown,selectedElectrons,selectedMuons,genTopEvt,sysType::JESdown);
    map<string,float> weights_jerup = GetWeights(*h_genInfo,*h_lheevent,eventInfo,selectedPVs,selectedJets_jerup,selectedElectrons,selectedMuons,genTopEvt,sysType::JERup);
    map<string,float> weights_jerdown = GetWeights(*h_genInfo,*h_lheevent,eventInfo,selectedPVs,selectedJets_jerdown,selectedElectrons,selectedMuons,genTopEvt,sysType::JERdown);
    map<string,float> weights_uncorrjets = GetWeights(*h_genInfo,*h_lheevent,eventInfo,selectedPVs,selectedJets_uncorrected,selectedElectrons,selectedMuons,genTopEvt,sysType::NA);
    //Only needed for Hbb synch exercise: dilepton uses loose jet selection -> different csv weights
    map<string,float> weights_DL_nominal = GetWeights(*h_genInfo,*h_lheevent,eventInfo,selectedPVs,selectedJetsLoose_nominal,selectedElectrons,selectedMuons,genTopEvt,sysType::NA);
    map<string,float> weights_DL_jesup = GetWeights(*h_genInfo,*h_lheevent,eventInfo,selectedPVs,selectedJetsLoose_jesup,selectedElectrons,selectedMuons,genTopEvt,sysType::JESup);
    map<string,float> weights_DL_jesdown = GetWeights(*h_genInfo,*h_lheevent,eventInfo,selectedPVs,selectedJetsLoose_jesdown,selectedElectrons,selectedMuons,genTopEvt,sysType::JESdown);
    map<string,float> weights_DL_jerup = GetWeights(*h_genInfo,*h_lheevent,eventInfo,selectedPVs,selectedJetsLoose_jerup,selectedElectrons,selectedMuons,genTopEvt,sysType::JERup);
    map<string,float> weights_DL_jerdown = GetWeights(*h_genInfo,*h_lheevent,eventInfo,selectedPVs,selectedJetsLoose_jerdown,selectedElectrons,selectedMuons,genTopEvt,sysType::JERdown);
    map<string,float> weights_DL_uncorrjets = GetWeights(*h_genInfo,*h_lheevent,eventInfo,selectedPVs,selectedJetsLoose_uncorrected,selectedElectrons,selectedMuons,genTopEvt,sysType::NA);
    */
    // DEFINE INPUT
    InputCollections input_nominal( eventInfo,
				    triggerInfo,
				    selectedPVs,
				    *h_selectedMuons,
				    *h_selectedMuonsDL,
				    *h_selectedMuonsLoose,
				    *h_selectedElectrons,
				    *h_selectedElectronsDL,
				    *h_selectedElectronsLoose,
				    *h_selectedJets,
				    *h_selectedJetsLoose,
				    (*h_correctedMETs)[0],
				    selectedBoostedJets,
				    genTopEvt,
				    *h_genJets,
				    sampleType,
				    higgsdecay,
				    weights,
				    iEvent,
				    iSetup
				    );
    /*
    // define systematically shifted input (replace quantaties affected by jets)
    InputCollections input_jesup( input_nominal,selectedJets_jesup,selectedJetsLoose_jesup,selectedJetsSingleTop_jesup,correctedMETs_jesup[0],selectedBoostedJets_jesup,weights_jesup);
    InputCollections input_jesdown( input_nominal,selectedJets_jesdown,selectedJetsLoose_jesdown,selectedJetsSingleTop_jesdown,correctedMETs_jesdown[0],selectedBoostedJets_jesdown,weights_jesdown);
    InputCollections input_jerup( input_nominal,selectedJets_jerup,selectedJetsLoose_jerup,selectedJetsSingleTop_jerup,correctedMETs_jerup[0],selectedBoostedJets_jerup,weights_jerup);
    InputCollections input_jerdown( input_nominal,selectedJets_jerdown,selectedJetsLoose_jerdown,selectedJetsSingleTop_jerdown,correctedMETs_jerdown[0],selectedBoostedJets_jerdown,weights_jerdown);
    InputCollections input_uncorrjets( input_nominal,selectedJets_uncorrected,selectedJetsLoose_uncorrected,selectedJetsSingleTop_uncorrected,correctedMETs[0],selectedBoostedJets_uncorrected,weights_uncorrjets);
    //Only needed for Hbb synch exercise: dilepton uses loose jet selection -> different csv weights and input collection
    InputCollections input_DL_nominal( input_nominal,selectedJetsLoose_nominal,selectedJetsLoose_nominal,selectedJetsSingleTop_nominal,correctedMETs_nominal[0],selectedBoostedJets,weights_DL_nominal);
    InputCollections input_DL_jesup( input_nominal,selectedJetsLoose_jesup,selectedJetsLoose_jesup,selectedJetsSingleTop_jesup,correctedMETs_jesup[0],selectedBoostedJets_jesup,weights_DL_jesup);
    InputCollections input_DL_jesdown( input_nominal,selectedJetsLoose_jesdown,selectedJetsLoose_jesdown,selectedJetsSingleTop_jesdown,correctedMETs_jesdown[0],selectedBoostedJets_jesdown,weights_DL_jesdown);
    InputCollections input_DL_jerup( input_nominal,selectedJetsLoose_jerup,selectedJetsLoose_jerup,selectedJetsSingleTop_jerup,correctedMETs_jerup[0],selectedBoostedJets_jerup,weights_DL_jerup);
    InputCollections input_DL_jerdown( input_nominal,selectedJetsLoose_jerdown,selectedJetsLoose_jerdown,selectedJetsSingleTop_jerdown,correctedMETs_jerdown[0],selectedBoostedJets_jerdown,weights_DL_jerdown);
    InputCollections input_DL_uncorrjets( input_nominal,selectedJetsLoose_uncorrected,selectedJetsLoose_uncorrected,selectedJetsSingleTop_uncorrected,correctedMETs[0],selectedBoostedJets_uncorrected,weights_DL_uncorrjets);
    */
    // DO SELECTION
    
    // all events survive step 0
    cutflow_nominal.EventSurvivedStep("all",input_nominal.weights.at("Weight"));
    /*    if(makeSystematicsTrees){
	cutflow_jesup.EventSurvivedStep("all",input_jesup.weights.at("Weight"));
	cutflow_jesdown.EventSurvivedStep("all",input_jesdown.weights.at("Weight"));
	if(doJERsystematic){
	    cutflow_jerup.EventSurvivedStep("all",input_jerup.weights.at("Weight"));
	    cutflow_jerdown.EventSurvivedStep("all",input_jerdown.weights.at("Weight"));
	}
	}*/
    bool selected_nominal=true;
    
    // dump l+jets sync exe for all events
    /*    if(dumpSyncExe){
	synchronizer.DumpSyncExe1(0,input_nominal);
	}*/
    
    // dump globl Hbb sync exe for all events
    /*    if(dumpSyncExe2){
	synchronizer.DumpSyncExe2(0,input_nominal,input_jesup,input_jesdown,input_uncorrjets,input_DL_nominal,input_DL_jesup,input_DL_jesdown,input_DL_uncorrjets,helper);
	}*/
    
    for(size_t i=0; i<selections.size() && selected_nominal; i++){
	// see if event is selected
	if(!selections.at(i)->IsSelected(input_nominal,cutflow_nominal)){
	    selected_nominal=false;
	}
	// dump lj sync exe after every selection step
	if(dumpSyncExe&&selected_nominal){
	    synchronizer.DumpSyncExe1(i+1,input_nominal);
	}
	
    }
    
    // WRITE (nominal) TREE  
    if(selected_nominal){
	treewriter_nominal.Process(input_nominal);
    }
    /*
    if(makeSystematicsTrees){
	// selection of systematically shifted events
	bool selected_jesup=true;
	for(size_t i=0; i<selections.size() && selected_jesup; i++){
	    if(!selections.at(i)->IsSelected(input_jesup,cutflow_jesup)){
		selected_jesup=false;
	    }
	}
	bool selected_jesdown=true;
	for(size_t i=0; i<selections.size() && selected_jesdown; i++){
	    if(!selections.at(i)->IsSelected(input_jesdown,cutflow_jesdown)){
		selected_jesdown=false;
	    }
	}
	// write systematically shifted trees
	if(selected_jesup){
	    treewriter_jesup.Process(input_jesup);
	}
	if(selected_jesdown){
	    treewriter_jesdown.Process(input_jesdown);
	}
	if(doJERsystematic){
	    bool selected_jerdown=true;
	    for(size_t i=0; i<selections.size() && selected_jerdown; i++){
		if(!selections.at(i)->IsSelected(input_jerdown,cutflow_jerdown)){
		    selected_jerdown=false;
		}
	    }
	    bool selected_jerup=true;
	    for(size_t i=0; i<selections.size() && selected_jerup; i++){
		if(!selections.at(i)->IsSelected(input_jerup,cutflow_jerup)){
		    selected_jerup=false;
		}
	    }
	    if(selected_jerup){
		treewriter_jerup.Process(input_jerup);
	    }
	    if(selected_jerdown){
		treewriter_jerdown.Process(input_jerdown);
	    }
	}
    }
    */    
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
    puWeights_.compute(eventInfo);
    puweight = puWeights_.nominalWeight();
    
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
	for(std::vector<PUWeights::Weight>::const_iterator it = puWeights_.additionalWeightsBegin();
	    it != puWeights_.additionalWeightsEnd(); ++it) {
	    weights[it->name()] = it->value();
	}
	//Add Genweights to the weight map
	genweights.GetGenWeights(weights, lheInfo, dogenweights);
    }
    
    
    return weights;
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
    std::ofstream fout_nominal(outfileNameNominal+"_Cutflow.txt");
    cutflow_nominal.Print(fout_nominal);
    fout_nominal.close();
    if(makeSystematicsTrees){
	std::ofstream fout_jesup(outfileNameJESup+"_Cutflow.txt");
	std::ofstream fout_jesdown(outfileNameJESdown+"_Cutflow.txt");
	cutflow_jesup.Print(fout_jesup);
	cutflow_jesdown.Print(fout_jesdown);
	fout_jesup.close();
	fout_jesdown.close();
	
	if(doJERsystematic){
	    std::ofstream fout_jerup(outfileNameJERup+"_Cutflow.txt");
	    std::ofstream fout_jerdown(outfileNameJERdown+"_Cutflow.txt");
	    cutflow_jerup.Print(fout_jerup);
	    cutflow_jerdown.Print(fout_jerdown);
	    fout_jerup.close();
	    fout_jerdown.close();
	    
	}
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
