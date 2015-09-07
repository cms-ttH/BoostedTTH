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
#include "DataFormats/METReco/interface/HcalNoiseSummary.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"
#include "MiniAOD/MiniAODHelper/interface/HiggsTagger.h"

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/CSVHelper.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeWriter.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/HistoReweighter.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMassSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/VertexSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/HbbSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/THQJetSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedSelection.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/WeightProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedMCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/AdditionalJetProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MVAVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/RawVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/StdTopVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/SingleTopVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedJetVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/ttHVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/EventInfo.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Synchronizer.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TriggerVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/ReconstructionVarProcessor.hpp"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

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
      map<string,float> GetWeights(const GenEventInfoProduct& genEventInfo, const EventInfo& eventInfo, const reco::VertexCollection& selectedPVs, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon>& selectedMuons, const std::vector<reco::GenParticle>& genParticles, sysType::sysType systype=sysType::NA);

      // ----------member data ---------------------------
      
      /** the miniAODhelper is used for selections and reweighting */
      MiniAODHelper helper;

  
      CSVHelper csvReweighter;
      HistoReweighter pvWeight;
      
      /** writes flat trees for MVA analysis */
      TreeWriter treewriter_nominal;
      TreeWriter treewriter_jesup;
      TreeWriter treewriter_jesdown;
          
      /** stores cutflow*/
      Cutflow cutflow_nominal;
      Cutflow cutflow_jesup;
      Cutflow cutflow_jesdown;
      
      /** selections that are applied */
      vector<Selection*> selections;

      /** triggers that are checked */
      vector<std::string> relevantTriggers;
        
      std::string outfileName;

      /** sample ID */
      int sampleID;
      
      /** stops the time needed */
      TStopwatch watch;
      
      /** events to be analyzed */
      int maxEvents;
      
      /** data luminosity */
      float luminosity;
      
      /** sample cross section*/
      float xs;
      
      /** total number of events in input file(s) */
      int totalMCevents;
     
      /** Event counter */
      int eventcount;
      
       /** is analyzed sample data? */
      bool isData;

       /** use fat jets? this is only possible if the miniAOD contains them */
      bool useFatJets;

       /** use forward jets (for single top studies) */
      bool useForwardJets;

       /** use GenBmatching info? this is only possible if the miniAOD contains them */
      bool useGenHadronMatch;
      
      /** dump some event content for synchronization */
      bool dumpSyncExe;
      bool dumpSyncExe2;
      Synchronizer synchronizer;

      /** write systematics trees */
      bool makeSystematicsTrees;

      
  // TOKENS =========================
      /** pu summary data access token **/
      edm::EDGetTokenT< std::vector<PileupSummaryInfo> > EDMPUInfoToken;
      
      /** pileup density data access token **/
      edm::EDGetTokenT <double> EDMRhoToken;

      /** hcal noise data access token **/
      edm::EDGetTokenT< HcalNoiseSummary > EDMHcalNoiseToken;
      
      /** selected trigger data access token **/
      edm::EDGetTokenT< pat::TriggerObjectStandAloneCollection > EDMSelectedTriggerToken;
      
      /** trigger results data access token **/
      edm::EDGetTokenT< edm::TriggerResults > EDMTriggerResultToken;
      HLTConfigProvider hlt_config;

      /** beam spot data access token **/
      edm::EDGetTokenT< reco::BeamSpot > EDMBeamSpotToken;
      
      /** vertex data access token **/
      edm::EDGetTokenT< reco::VertexCollection > EDMVertexToken;
      
      /** muons data access token **/
      edm::EDGetTokenT< std::vector<pat::Muon> > EDMMuonsToken;
      
      /** electrons data access token **/
      edm::EDGetTokenT< std::vector<pat::Electron> > EDMElectronsToken;
      
      /** jets data access token **/
      edm::EDGetTokenT< std::vector<pat::Jet> > EDMJetsToken;

      /** mets data access token **/
      edm::EDGetTokenT< std::vector<pat::MET> > EDMMETsToken;
      
      /** boosted jets data access token **/
      edm::EDGetTokenT< boosted::BoostedJetCollection > EDMBoostedJetsToken;
      
      /** gen info data access token **/
      edm::EDGetTokenT< GenEventInfoProduct > EDMGenInfoToken;
      
      /** gen particles data access token **/
      edm::EDGetTokenT< std::vector<reco::GenParticle> > EDMGenParticlesToken;
      
      /** gen jets data access token **/
      edm::EDGetTokenT< std::vector<reco::GenJet> > EDMGenJetsToken;
     // custom genjets for tt+X categorization
      edm::EDGetTokenT< std::vector<reco::GenJet> > EDMCustomGenJetsToken;
    
     /** tt+X categorization tokens **/
      edm::EDGetTokenT<std::vector<int> > genBHadJetIndexToken;
      edm::EDGetTokenT<std::vector<int> > genBHadFlavourToken;
      edm::EDGetTokenT<std::vector<int> > genBHadFromTopWeakDecayToken;
      edm::EDGetTokenT<std::vector<reco::GenParticle> > genBHadPlusMothersToken;
      edm::EDGetTokenT<std::vector<std::vector< int > > > genBHadPlusMothersIndicesToken;
      edm::EDGetTokenT<std::vector<int> > genBHadIndexToken;
      edm::EDGetTokenT<std::vector<int> > genBHadLeptonHadronIndexToken;
      edm::EDGetTokenT<std::vector<int> > genBHadLeptonViaTauToken;
      edm::EDGetTokenT<std::vector<int> > genCHadJetIndexToken;
      edm::EDGetTokenT<std::vector<int> > genCHadFlavourToken;
      edm::EDGetTokenT<std::vector<int> > genCHadFromTopWeakDecayToken;
      edm::EDGetTokenT<std::vector<int> > genCHadBHadronIdToken;
      edm::EDGetTokenT<std::vector<int> > genCHadIndexToken;
      edm::EDGetTokenT<std::vector<reco::GenParticle> > genCHadPlusMothersToken;
      edm::EDGetTokenT<int> genTtbarIdToken;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
BoostedAnalyzer::BoostedAnalyzer(const edm::ParameterSet& iConfig):pvWeight((BoostedUtils::GetAnalyzerPath()+"/data/pvweights/PUhistos.root").c_str(),"data","mc")
{
  // get all configurations from the python config
  std::string era = iConfig.getParameter<std::string>("era");
  string analysisType = iConfig.getParameter<std::string>("analysisType");
  analysisType::analysisType iAnalysisType = analysisType::LJ;
  if(analysisType == "LJ") iAnalysisType = analysisType::LJ;
  else if(analysisType == "DIL") iAnalysisType = analysisType::DIL;
  else if(analysisType == "TauLJ") iAnalysisType = analysisType::TauLJ;
  else if(analysisType == "TauDIL") iAnalysisType = analysisType::TauDIL;
  else cerr << "No matching analysis type found for: " << analysisType << endl;
  
  luminosity = iConfig.getParameter<double>("luminosity");
  sampleID = iConfig.getParameter<int>("sampleID");
  xs = iConfig.getParameter<double>("xs");
  totalMCevents = iConfig.getParameter<int>("nMCEvents");
  isData = iConfig.getParameter<bool>("isData");
  
  useFatJets = iConfig.getParameter<bool>("useFatJets");
  useForwardJets = iConfig.getParameter<bool>("useForwardJets");
  useGenHadronMatch = iConfig.getParameter<bool>("useGenHadronMatch");
  if(isData) useGenHadronMatch=false;

  dumpSyncExe = iConfig.getParameter<bool>("dumpSyncExe");
  dumpSyncExe2 = iConfig.getParameter<bool>("dumpSyncExe2");

  makeSystematicsTrees = iConfig.getParameter<bool>("makeSystematicsTrees");

  outfileName = iConfig.getParameter<std::string>("outfileName");

  // REGISTER DATA ACCESS
  EDMPUInfoToken          = consumes< std::vector<PileupSummaryInfo> >(edm::InputTag("addPileupInfo","",""));
  EDMRhoToken             = consumes <double> (edm::InputTag(std::string("fixedGridRhoFastjetAll")));
  EDMHcalNoiseToken       = consumes< HcalNoiseSummary >(edm::InputTag("hcalnoise","",""));
  EDMSelectedTriggerToken = consumes< pat::TriggerObjectStandAloneCollection > (edm::InputTag("selectedPatTrigger","",""));
  EDMTriggerResultToken   = consumes< edm::TriggerResults > (edm::InputTag("TriggerResults","","HLT"));
  EDMBeamSpotToken        = consumes< reco::BeamSpot > (edm::InputTag("offlineBeamSpot","",""));
  EDMVertexToken          = consumes< reco::VertexCollection > (edm::InputTag("offlineSlimmedPrimaryVertices","",""));
  EDMMuonsToken           = consumes< std::vector<pat::Muon> >(edm::InputTag("slimmedMuons","",""));
  EDMElectronsToken       = consumes< std::vector<pat::Electron> >(edm::InputTag("slimmedElectrons","",""));
  EDMJetsToken            = consumes< std::vector<pat::Jet> >(edm::InputTag("slimmedJets","",""));
  EDMMETsToken            = consumes< std::vector<pat::MET> >(edm::InputTag("slimmedMETs","",""));
  EDMBoostedJetsToken     = consumes< boosted::BoostedJetCollection >(edm::InputTag("BoostedJetMatcher","boostedjets","p"));
  EDMGenInfoToken         = consumes< GenEventInfoProduct >(edm::InputTag("generator","",""));
  EDMGenParticlesToken    = consumes< std::vector<reco::GenParticle> >(edm::InputTag("prunedGenParticles","",""));
  EDMGenJetsToken         = consumes< std::vector<reco::GenJet> >(edm::InputTag("slimmedGenJets","",""));
  EDMCustomGenJetsToken   = consumes< std::vector<reco::GenJet> >(edm::InputTag("ak4GenJetsCustom","",""));

  // tt+X CATEGORIZATION data
  genBHadJetIndexToken           = consumes<std::vector<int> >(edm::InputTag("matchGenBHadron","genBHadJetIndex",""));
  genBHadFlavourToken            = consumes<std::vector<int> >(edm::InputTag("matchGenBHadron","genBHadFlavour",""));
  genBHadFromTopWeakDecayToken   = consumes<std::vector<int> >(edm::InputTag("matchGenBHadron","genBHadFromTopWeakDecay",""));
  genBHadPlusMothersToken        = consumes<std::vector<reco::GenParticle> >(edm::InputTag("matchGenBHadron","genBHadPlusMothers",""));
  genBHadPlusMothersIndicesToken = consumes<std::vector<std::vector<int> > >(edm::InputTag("matchGenBHadron","genBHadPlusMothersIndices",""));
  genBHadIndexToken              = consumes<std::vector<int> >(edm::InputTag("matchGenBHadron","genBHadIndex"));
  genBHadLeptonHadronIndexToken  = consumes<std::vector<int> >(edm::InputTag("matchGenBHadron","genBHadLeptonHadronIndex",""));
  genBHadLeptonViaTauToken       = consumes<std::vector<int> >(edm::InputTag("matchGenBHadron","genBHadLeptonViaTau",""));
  genCHadJetIndexToken           = consumes<std::vector<int> >(edm::InputTag("matchGenCHadron","genCHadJetIndex",""));
  genCHadFlavourToken            = consumes<std::vector<int> >(edm::InputTag("matchGenCHadron","genCHadFlavour",""));
  genCHadFromTopWeakDecayToken   = consumes<std::vector<int> >(edm::InputTag("matchGenCHadron","genCHadFromTopWeakDecay",""));
  genCHadBHadronIdToken          = consumes<std::vector<int> >(edm::InputTag("matchGenCHadron","genCHadBHadronId",""));
  genCHadIndexToken              = consumes<std::vector<int> >(edm::InputTag("matchGenCHadron","genCHadIndex"));
  genCHadPlusMothersToken        = consumes<std::vector<reco::GenParticle> >(edm::InputTag("matchGenCHadron","genCHadPlusMothers",""));
  genTtbarIdToken                = consumes<int>              (edm::InputTag("categorizeGenTtbar","genTtbarId",""));

  // INITIALIZE MINIAOD HELPER
  helper.SetUp(era, sampleID, iAnalysisType, isData);
  helper.SetJetCorrectorUncertainty();
  

  // INITIALIZE SELECTION & CUTFLOW
  cutflow_nominal.Init();
  if(makeSystematicsTrees){
    cutflow_jesup.Init();
    cutflow_jesdown.Init();
  }
  std::vector<std::string> selectionNames = iConfig.getParameter< std::vector<std::string> >("selectionNames");
  int nselection=0;
  if(dumpSyncExe){
    synchronizer.InitDumpSyncFile1((outfileName+"_Dump1_"+std::to_string(nselection)));
  }
  if(dumpSyncExe2){
    synchronizer.InitDumpSyncFile2(outfileName);
  }  
  // add requested selections
  for(vector<string>::const_iterator itSel = selectionNames.begin();itSel != selectionNames.end();itSel++) {    
    cout << "Initializing " << *itSel << endl;
    if(*itSel == "VertexSelection") selections.push_back(new VertexSelection());
    else if(*itSel == "LeptonSelection") selections.push_back(new LeptonSelection(iConfig));
    else if(*itSel == "JetTagSelection") selections.push_back(new JetTagSelection(iConfig));
    else if(*itSel == "THQJetSelection") selections.push_back(new THQJetSelection());
    else if(*itSel == "LeptonSelection1") selections.push_back(new LeptonSelection(iConfig,1));
    else if(*itSel == "LeptonSelection2") selections.push_back(new LeptonSelection(iConfig,2));
    else if(*itSel == "LeptonSelection3") selections.push_back(new LeptonSelection(iConfig,3));
    else if(*itSel == "LeptonSelection4") selections.push_back(new LeptonSelection(iConfig,4));
    else if(*itSel == "DiLeptonSelection") selections.push_back(new DiLeptonSelection(iConfig));
    else if(*itSel == "MinDiLeptonMassSelection") selections.push_back(new DiLeptonMassSelection(20.,9999.));
    else if(*itSel == "ZVetoSelection") selections.push_back(new DiLeptonMassSelection(76.,106,true));
    else if(*itSel == "METSelection") selections.push_back(new METSelection(iConfig));
    else if(*itSel == "FastSimMETSelection") selections.push_back(new METSelection(-1,800));
    else if(*itSel == "HbbSelection") selections.push_back(new HbbSelection());
    else if(*itSel == "4JetSelection") selections.push_back(new JetTagSelection(4,-1));
    else if(*itSel == "2TagSelection") selections.push_back(new JetTagSelection(-1,2));
    else if(*itSel == "BoostedTopSelection") selections.push_back(new BoostedSelection(1,0));
    else if(*itSel == "BoostedSelection") selections.push_back(new BoostedSelection(0,1));
    else cout << "No matching selection found for: " << *itSel << endl;    
    selections.back()->InitCutflow(cutflow_nominal);
    if(makeSystematicsTrees){
      selections.back()->InitCutflow(cutflow_jesup);
      selections.back()->InitCutflow(cutflow_jesdown);
    }
    
    nselection++;     
    if(dumpSyncExe){
      synchronizer.InitDumpSyncFile1(outfileName+"_Dump1_"+std::to_string(nselection));
    }  
  }
  relevantTriggers = iConfig.getParameter< std::vector<std::string> >("relevantTriggers");

  // INITIALIZE TREEWRITER
  treewriter_nominal.Init(outfileName);  
  // in case of systematics
  if(makeSystematicsTrees){
    std::string jesDownName = outfileName;
    std::string jesUpName = outfileName;
    // some filename changing for Karim
    size_t stringIndex = outfileName.find("nominal");
    if(stringIndex!=std::string::npos){
      jesUpName.replace(stringIndex,7,"JESUP");
      jesDownName.replace(stringIndex,7,"JESDOWN");
      std::cout<<jesUpName<<" "<<jesDownName<<std::endl;
      treewriter_jesup.Init(jesUpName);
      treewriter_jesdown.Init(jesDownName);
    }
    else{
      // this is are the usual tree names
      treewriter_jesup.Init(outfileName+"_JESup");
      treewriter_jesdown.Init(outfileName+"_JESdown");
    }
  }

  std::vector<std::string> processorNames = iConfig.getParameter< std::vector<std::string> >("processorNames");

  cout << "using processors:" << endl; 
  for(vector<string>::const_iterator itPro = processorNames.begin();itPro != processorNames.end();++itPro) {
    cout << *itPro << endl;
  }
  // add processors that have been requested in the config
  if(std::find(processorNames.begin(),processorNames.end(),"WeightProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new WeightProcessor());
  }
  if(std::find(processorNames.begin(),processorNames.end(),"MVAVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new MVAVarProcessor());
  }
  if(std::find(processorNames.begin(),processorNames.end(),"RawVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new RawVarProcessor());
  }
  if(std::find(processorNames.begin(),processorNames.end(),"StdTopVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new StdTopVarProcessor());
  }
  if(std::find(processorNames.begin(),processorNames.end(),"SingleTopVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new SingleTopVarProcessor());
  }
  if(std::find(processorNames.begin(),processorNames.end(),"BoostedJetVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new BoostedJetVarProcessor(&helper));
  }
  if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopHiggsVarProcessor")!=processorNames.end()) {
    //treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::HEP,TopTag::Pt,"",HiggsTag::DoubleCSV,"","BoostedTopHiggs_"));
    //treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::HEP,TopTag::CSV,"",HiggsTag::DoubleCSV,"","BoostedTopHiggs_"));
    //treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::Likelihood,TopTag::CSV,"toplikelihoodtaggerhistos.root",HiggsTag::DoubleCSV,"","BoostedTopHiggs_"));
    treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::DoubleCSV,"","BoostedTopHiggs_"));
    //treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_PSO.weights.xml",HiggsTag::DoubleCSV,"","BoostedTopHiggs_"));
  }
  if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopVarProcessor")!=processorNames.end()) {
    //treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::HEP,TopTag::Pt,"",HiggsTag::DoubleCSV,"","BoostedTop_"));
    //treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::HEP,TopTag::CSV,"",HiggsTag::DoubleCSV,"","BoostedTop_"));
    //treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::Likelihood,TopTag::CSV,"toplikelihoodtaggerhistos.root",HiggsTag::DoubleCSV,"","BoostedTop_"));
    treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::DoubleCSV,"","BoostedTop_"));
    //treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_PSO.weights.xml",HiggsTag::DoubleCSV,"","BoostedTop_"));
  }
  if(std::find(processorNames.begin(),processorNames.end(),"BoostedHiggsVarProcessor")!=processorNames.end()) {
    //treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::HEP,TopTag::Pt,"",HiggsTag::DoubleCSV,"","BoostedHiggs_"));
    //treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::HEP,TopTag::CSV,"",HiggsTag::DoubleCSV,"","BoostedHiggs_"));
    //treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::Likelihood,TopTag::CSV,"toplikelihoodtaggerhistos.root",HiggsTag::DoubleCSV,"","BoostedHiggs_"));
    treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::DoubleCSV,"","BoostedHiggs_"));
    //treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_PSO.weights.xml",HiggsTag::DoubleCSV,"","BoostedHiggs_"));
  }
  if(std::find(processorNames.begin(),processorNames.end(),"BDTVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new BDTVarProcessor());
  }
  if(std::find(processorNames.begin(),processorNames.end(),"MCMatchVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new MCMatchVarProcessor());
  }
  if(std::find(processorNames.begin(),processorNames.end(),"BoostedMCMatchVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new BoostedMCMatchVarProcessor());
  }
  if(std::find(processorNames.begin(),processorNames.end(),"AdditionalJetProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new AdditionalJetProcessor());
  }
  if(std::find(processorNames.begin(),processorNames.end(),"DiLeptonVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new DiLeptonVarProcessor());
  }
  if(std::find(processorNames.begin(),processorNames.end(),"TriggerVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new TriggerVarProcessor());
  }
  if(std::find(processorNames.begin(),processorNames.end(),"ReconstructionVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new ReconstructionVarProcessor());
  }


  // the systematics tree writers use the same processors that are used for the nominal trees
  // it might improve the performance to turn some of them off
  if(makeSystematicsTrees){
    std::vector<TreeProcessor*> tps = treewriter_nominal.GetTreeProcessors();
    for(uint i=0; i<tps.size();i++){
      treewriter_jesup.AddTreeProcessor(tps[i]);
      treewriter_jesdown.AddTreeProcessor(tps[i]);
    }
  }
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
  
  /**** GET PILEUPSUMMARYINFO ****/
  edm::Handle< std::vector<PileupSummaryInfo> >  h_puinfosummary;
  iEvent.getByToken( EDMPUInfoToken, h_puinfosummary);

  /**** GET RHO ****/
  edm::Handle<double> h_rho;
  iEvent.getByToken(EDMRhoToken,h_rho);
  helper.SetRho(*h_rho);
  
  /**** GET HCALNOISESUMMARY ****/
  edm::Handle<HcalNoiseSummary> h_hcalnoisesummary;
  iEvent.getByToken( EDMHcalNoiseToken,h_hcalnoisesummary );

  /**** GET TRIGGER ****/ 
  edm::Handle<edm::TriggerResults> h_triggerresults;
  iEvent.getByToken( EDMTriggerResultToken,h_triggerresults );
  edm::TriggerResults const &triggerResults = *h_triggerresults;

  /**** GET BEAMSPOT ****/
  edm::Handle<reco::BeamSpot> h_beamspot;
  iEvent.getByToken( EDMBeamSpotToken,h_beamspot );
  
  /**** GET PRIMARY VERTICES ****/
  edm::Handle< reco::VertexCollection > h_vtxs;
  iEvent.getByToken( EDMVertexToken,h_vtxs );
  reco::VertexCollection const &vtxs = *h_vtxs;
  reco::VertexCollection selectedPVs; 
  bool firstVertexIsGood=false;
  bool isFirst=true;
  if( h_vtxs.isValid() ){
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


  /*** GET LEPTONS ***/
  // MUONS
  edm::Handle< std::vector<pat::Muon> > h_muons;
  iEvent.getByToken( EDMMuonsToken,h_muons );

  std::vector<pat::Muon> const &muons = *h_muons;
  std::vector<pat::Muon> rawMuons = muons;
  // note: muon eta cuts and muonLoose ID no longer as in synch exe
  std::vector<pat::Muon> selectedMuons = helper.GetSelectedMuons( muons, 30., muonID::muonTight, coneSize::R04, corrType::deltaBeta, 2.1);
  std::vector<pat::Muon> selectedMuonsDL = helper.GetSelectedMuons( muons, 20., muonID::muonTight, coneSize::R04, corrType::deltaBeta, 2.4 );
  std::vector<pat::Muon> selectedMuonsLoose = helper.GetSelectedMuons( muons, 10., muonID::muonLoose, coneSize::R04, corrType::deltaBeta, 2.4);

  // ELECTRONS
  edm::Handle< std::vector<pat::Electron> > h_electrons;
  iEvent.getByToken( EDMElectronsToken,h_electrons );
  std::vector<pat::Electron> const &electrons = *h_electrons;
  std::vector<pat::Electron> rawElectrons = electrons;
  // note: electron eta cuts no longer as in synch exe, revert as soon as miniAODhelper os updated
  std::vector<pat::Electron> selectedElectrons = helper.GetSelectedElectrons( electrons, 30., electronID::electronPhys14M, 2.1 );
  std::vector<pat::Electron> selectedElectronsDL = helper.GetSelectedElectrons( electrons, 20., electronID::electronPhys14M, 2.4 );
  std::vector<pat::Electron> selectedElectronsLoose = helper.GetSelectedElectrons( electrons, 10., electronID::electronPhys14L, 2.4 );

  /**** GET JETS ****/
  edm::Handle< std::vector<pat::Jet> > h_pfjets;
  iEvent.getByToken( EDMJetsToken,h_pfjets );
  std::vector<pat::Jet> const &pfjets = *h_pfjets;

  // initialize jetcorrector
  const JetCorrector* corrector = JetCorrector::getJetCorrector( "ak4PFchsL1L2L3", iSetup );
  helper.SetJetCorrector(corrector);

  const double jetptcut=30.0; 
  const double jetetacut=2.4; 
  const double jetptcut_loose=20.0; 
  const double jetetacut_loose=2.4; 
  const double jetptcut_forward=40.0; 
  const double jetetacut_forward=4.7; 

  // selected jets with jet ID cuts
  std::vector<pat::Jet> idJets = helper.GetSelectedJets(pfjets, 0., 9999., jetID::jetLoose, '-' );
  // Get raw jets
  std::vector<pat::Jet> rawJets = helper.GetUncorrectedJets(idJets);
  // Clean muons and electrons from jets
  std::vector<pat::Jet> cleanJets = helper.GetDeltaRCleanedJets(rawJets,selectedMuonsLoose,selectedElectronsLoose,0.4);
  // Apply nominal jet corrections
  std::vector<pat::Jet> correctedJets_unsorted_nominal = helper.GetCorrectedJets(cleanJets, iEvent, iSetup, sysType::NA);
  //Get jet Collection which pass selection
  std::vector<pat::Jet> selectedJets_unsorted_nominal = helper.GetSelectedJets(correctedJets_unsorted_nominal, jetptcut, jetetacut, jetID::none, '-' );
  // Sort jets
  std::vector<pat::Jet> selectedJets_nominal = helper.GetSortedByPt(selectedJets_unsorted_nominal);
  // Get jet Collection which pass loose selection
  std::vector<pat::Jet> selectedJetsLoose_unsorted_nominal = helper.GetSelectedJets(correctedJets_unsorted_nominal, jetptcut_loose,jetetacut_loose, jetID::none, '-' ); 
  // Sort jets
  std::vector<pat::Jet> selectedJetsLoose_nominal = helper.GetSortedByPt(selectedJetsLoose_unsorted_nominal);
  // Get jet Collection which pass the forward selection
  std::vector<pat::Jet> selectedJetsSingleTop_nominal;
  if(useForwardJets){
      std::vector<pat::Jet> selectedJetsForward_unsorted_nominal = helper.GetSelectedJets(correctedJets_unsorted_nominal, jetptcut_forward,jetetacut_forward, jetID::none, '-' ); 
      std::vector<pat::Jet> selectedJetsSingleTop_unsorted_nominal = BoostedUtils::GetSingleTopJets(selectedJetsLoose_nominal,selectedJetsForward_unsorted_nominal,jetetacut_loose);
      selectedJetsSingleTop_nominal= helper.GetSortedByPt(selectedJetsSingleTop_unsorted_nominal);
  }

  // Apply systematically shifted jet corrections -- these vector stay empty if you dont use makeSystematicsTrees
  std::vector<pat::Jet> correctedJets_unsorted_jesup;
  std::vector<pat::Jet> correctedJets_unsorted_jesdown;

  std::vector<pat::Jet> selectedJets_unsorted_jesup;
  std::vector<pat::Jet> selectedJets_unsorted_jesdown;
  std::vector<pat::Jet> selectedJets_unsorted_uncorrected;
  std::vector<pat::Jet> selectedJetsLoose_unsorted_jesup;
  std::vector<pat::Jet> selectedJetsLoose_unsorted_jesdown;
  std::vector<pat::Jet> selectedJetsLoose_unsorted_uncorrected;

  std::vector<pat::Jet> selectedJets_jesup;
  std::vector<pat::Jet> selectedJets_jesdown;
  std::vector<pat::Jet> selectedJets_uncorrected;
  std::vector<pat::Jet> selectedJetsLoose_jesup;
  std::vector<pat::Jet> selectedJetsLoose_jesdown;
  std::vector<pat::Jet> selectedJetsLoose_uncorrected;

  std::vector<pat::Jet> selectedJetsSingleTop_jesup;
  std::vector<pat::Jet> selectedJetsSingleTop_jesdown;
  std::vector<pat::Jet> selectedJetsSingleTop_uncorrected;
  
  if(makeSystematicsTrees){
    correctedJets_unsorted_jesup = helper.GetCorrectedJets(cleanJets, iEvent, iSetup, sysType::JESup);
    correctedJets_unsorted_jesdown = helper.GetCorrectedJets(cleanJets, iEvent, iSetup, sysType::JESdown);

    selectedJets_unsorted_jesup = helper.GetSelectedJets(correctedJets_unsorted_jesup, jetptcut, jetetacut, jetID::none, '-' );
    selectedJets_unsorted_jesdown = helper.GetSelectedJets(correctedJets_unsorted_jesdown, jetptcut, jetetacut, jetID::none, '-' );
    selectedJets_unsorted_uncorrected = helper.GetSelectedJets(cleanJets, jetptcut, jetetacut, jetID::none, '-' );
    selectedJetsLoose_unsorted_jesup = helper.GetSelectedJets(correctedJets_unsorted_jesup, jetptcut_loose, jetetacut_loose, jetID::none, '-' ); 
    selectedJetsLoose_unsorted_jesdown = helper.GetSelectedJets(correctedJets_unsorted_jesdown, jetptcut_loose,jetetacut_loose, jetID::none, '-' ); 
    selectedJetsLoose_unsorted_uncorrected = helper.GetSelectedJets(cleanJets, jetptcut_loose, jetetacut_loose, jetID::none, '-' ); 

    selectedJets_jesup = helper.GetSortedByPt(selectedJets_unsorted_jesup);
    selectedJets_jesdown = helper.GetSortedByPt(selectedJets_unsorted_jesdown);
    selectedJets_uncorrected = helper.GetSortedByPt(selectedJets_unsorted_uncorrected);
    selectedJetsLoose_jesup = helper.GetSortedByPt(selectedJetsLoose_unsorted_jesup);
    selectedJetsLoose_jesdown = helper.GetSortedByPt(selectedJetsLoose_unsorted_jesdown);
    selectedJetsLoose_uncorrected = helper.GetSortedByPt(selectedJetsLoose_unsorted_uncorrected);

    if(useForwardJets){

	std::vector<pat::Jet> selectedJetsForward_unsorted_jesup = helper.GetSelectedJets(correctedJets_unsorted_jesup, jetptcut_forward, jetetacut_forward, jetID::none, '-' ); 
	std::vector<pat::Jet> selectedJetsForward_unsorted_jesdown = helper.GetSelectedJets(correctedJets_unsorted_jesdown, jetptcut_forward,jetetacut_forward, jetID::none, '-' ); 
	std::vector<pat::Jet> selectedJetsForward_unsorted_uncorrected = helper.GetSelectedJets(cleanJets, jetptcut_forward, jetetacut_forward, jetID::none, '-' ); 
	
	std::vector<pat::Jet> selectedJetsSingleTop_unsorted_jesup = BoostedUtils::GetSingleTopJets(selectedJetsLoose_jesup,selectedJetsForward_unsorted_jesup,jetetacut_loose);
	std::vector<pat::Jet> selectedJetsSingleTop_unsorted_jesdown = BoostedUtils::GetSingleTopJets(selectedJetsLoose_jesdown,selectedJetsForward_unsorted_jesdown,jetetacut_loose);
	std::vector<pat::Jet> selectedJetsSingleTop_unsorted_uncorrected = BoostedUtils::GetSingleTopJets(selectedJetsLoose_uncorrected,selectedJetsForward_unsorted_uncorrected,jetetacut_loose);

	selectedJetsSingleTop_jesup = helper.GetSortedByPt(selectedJetsSingleTop_unsorted_jesup);
	selectedJetsSingleTop_jesdown = helper.GetSortedByPt(selectedJetsSingleTop_unsorted_jesdown);
	selectedJetsSingleTop_uncorrected = helper.GetSortedByPt(selectedJetsSingleTop_unsorted_uncorrected);
    }
  }

  /**** GET MET ****/
  edm::Handle< std::vector<pat::MET> > h_pfmet;
  iEvent.getByToken( EDMMETsToken,h_pfmet );
  std::vector<pat::MET> const &pfMETs = *h_pfmet;
  // type I met corrections?
  assert(pfMETs.size()>0);

  /**** GET BOOSTEDJETS ****/
  edm::Handle<boosted::BoostedJetCollection> h_boostedjet;
  boosted::BoostedJetCollection selectedBoostedJets;
  if(useFatJets){
    iEvent.getByToken( EDMBoostedJetsToken,h_boostedjet);
    boosted::BoostedJetCollection const &boostedjets_unsorted = *h_boostedjet;
    boosted::BoostedJetCollection boostedjets = BoostedUtils::GetSortedByPt(boostedjets_unsorted);
    selectedBoostedJets = helper.GetSelectedBoostedJets(boostedjets, 200., 2.0, 20., 2.4, jetID::jetLoose);
  }
  
  /**** GET GENEVENTINFO ****/
  edm::Handle<GenEventInfoProduct> h_geneventinfo;
  if(!isData){
    iEvent.getByToken( EDMGenInfoToken, h_geneventinfo );
  }

  /**** GET GENPARTICLES ****/
  edm::Handle< std::vector<reco::GenParticle> > h_genParticles;
  if(!isData){
    iEvent.getByToken( EDMGenParticlesToken,h_genParticles );
  }
  
  /**** GET GENJETS ****/
  edm::Handle< std::vector<reco::GenJet> > h_genjets;
  std::vector<reco::GenJet> selectedGenJets;
  if(!isData){
    iEvent.getByToken( EDMGenJetsToken,h_genjets );
    std::vector<reco::GenJet> const &genjets = *h_genjets;
    for(size_t i=0; i<genjets.size();i++){
      if(genjets[i].pt()>jetptcut&&fabs(genjets[i].eta())<jetetacut)
	selectedGenJets.push_back(genjets[i]);
    }
  }
  // custom genjets for tt+X categorization
  edm::Handle< std::vector<reco::GenJet> > h_customgenjets;
  if(!isData){
    iEvent.getByToken( EDMCustomGenJetsToken,h_customgenjets );
  }
  // Fill Event Info Object
  EventInfo eventInfo(iEvent,h_beamspot,h_hcalnoisesummary,h_puinfosummary,firstVertexIsGood,*h_rho);
  // Fill Trigger Info -- a map with bools and some helper functions
  map<string,bool> triggerMap;
  for(auto name=relevantTriggers.begin(); name!=relevantTriggers.end();name++){
    unsigned int TriggerID =  hlt_config.triggerIndex(*name);
    if( TriggerID >= triggerResults.size() ) { 
      std::cerr <<"triggerID > trigger results.size, trigger name: "<< *name<<std::endl; 
      triggerMap[*name]=false;
    }
    else{
      triggerMap[*name]=triggerResults.accept(TriggerID);
    }
  }
  TriggerInfo triggerInfo(triggerMap);

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
  GenTopEvent genTopEvt;
  int ttid=-1;
  int ttid_full=-1;
  if(!isData&&useGenHadronMatch&&foundT&&foundTbar){
    /**** tt+X categorization ****/
    // Reading gen jets from the event
    // Reading B hadrons related information
    edm::Handle<std::vector<int> > genBHadFlavour;
    edm::Handle<std::vector<int> > genBHadJetIndex;
    edm::Handle<std::vector<int> > genBHadFromTopWeakDecay;
    edm::Handle<std::vector<reco::GenParticle> > genBHadPlusMothers;
    edm::Handle<std::vector<std::vector<int> > > genBHadPlusMothersIndices;
    edm::Handle<std::vector<reco::GenParticle> > genCHadPlusMothers;
    edm::Handle<std::vector<int> > genBHadIndex;
    edm::Handle<std::vector<int> > genBHadLeptonHadronIndex;
    edm::Handle<std::vector<int> > genBHadLeptonViaTau;
    // Reading C hadrons related information
    edm::Handle<std::vector<int> > genCHadIndex;
    edm::Handle<std::vector<int> > genCHadFlavour;
    edm::Handle<std::vector<int> > genCHadJetIndex;
    edm::Handle<std::vector<int> > genCHadFromTopWeakDecay;
    edm::Handle<std::vector<int> > genCHadBHadronId;
    edm::Handle<int> genTtbarId;
    iEvent.getByToken(genCHadBHadronIdToken, genCHadBHadronId);
    iEvent.getByToken(genBHadFlavourToken, genBHadFlavour);
    iEvent.getByToken(genBHadJetIndexToken, genBHadJetIndex);  
    iEvent.getByToken(genBHadFromTopWeakDecayToken, genBHadFromTopWeakDecay);  
    iEvent.getByToken(genBHadPlusMothersToken, genBHadPlusMothers);    
    iEvent.getByToken(genBHadPlusMothersIndicesToken, genBHadPlusMothersIndices);
    iEvent.getByToken(genCHadPlusMothersToken, genCHadPlusMothers);    
    iEvent.getByToken(genBHadIndexToken, genBHadIndex);
    iEvent.getByToken(genBHadLeptonHadronIndexToken, genBHadLeptonHadronIndex);
    iEvent.getByToken(genBHadLeptonViaTauToken, genBHadLeptonViaTau);
    iEvent.getByToken(genCHadFlavourToken, genCHadFlavour);
    iEvent.getByToken(genCHadJetIndexToken, genCHadJetIndex);
    iEvent.getByToken(genCHadFromTopWeakDecayToken, genCHadFromTopWeakDecay);
    iEvent.getByToken(genCHadIndexToken, genCHadIndex);
    iEvent.getByToken(genTtbarIdToken, genTtbarId);
    ttid_full = *genTtbarId;
    ttid = ttid_full%100;
    // fill additional jet info in genTopEvt
    genTopEvt.FillTTxDetails(*h_customgenjets, 
			     *genBHadIndex, *genBHadJetIndex, *genBHadFlavour, *genBHadFromTopWeakDecay, *genBHadPlusMothers, 
			     *genCHadIndex, *genCHadJetIndex, *genCHadFlavour, *genCHadFromTopWeakDecay, *genCHadPlusMothers,
			     *genCHadBHadronId,
			     20,2.4); 
  }
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
  if(!isData&&foundT&&foundTbar) {
    // fill genTopEvt with tt(H) information
    genTopEvt.Fill(*h_genParticles,ttid_full);
  }

  // DO REWEIGHTING
  map<string,float> weights = GetWeights(*h_geneventinfo,eventInfo,selectedPVs,selectedJets_nominal,selectedElectrons,selectedMuons,*h_genParticles,sysType::NA);
  map<string,float> weights_jesup = GetWeights(*h_geneventinfo,eventInfo,selectedPVs,selectedJets_jesup,selectedElectrons,selectedMuons,*h_genParticles,sysType::JESup);
  map<string,float> weights_jesdown = GetWeights(*h_geneventinfo,eventInfo,selectedPVs,selectedJets_jesdown,selectedElectrons,selectedMuons,*h_genParticles,sysType::JESdown);
  map<string,float> weights_uncorrjets = GetWeights(*h_geneventinfo,eventInfo,selectedPVs,selectedJets_uncorrected,selectedElectrons,selectedMuons,*h_genParticles,sysType::NA);

  // DEFINE INPUT
  InputCollections input_nominal( eventInfo,
				  triggerInfo,
				  selectedPVs,
				  rawMuons,
				  selectedMuons,
				  selectedMuonsDL,
				  selectedMuonsLoose,
				  rawElectrons,
				  selectedElectrons,
				  selectedElectronsDL,
				  selectedElectronsLoose,
				  rawJets,
				  selectedJets_nominal,
				  selectedJetsLoose_nominal,
				  selectedJetsSingleTop_nominal,
				  pfMETs[0],
				  selectedBoostedJets,
				  genTopEvt,
				  selectedGenJets,
				  sampleType,
				  higgsdecay,
				  weights
				  );

  // define systematically shifted input (replace quantaties affected by jets)
  InputCollections input_jesup( input_nominal,selectedJets_jesup,selectedJetsLoose_jesup,selectedJetsSingleTop_jesup,pfMETs[0],weights_jesup);
  InputCollections input_jesdown( input_nominal,selectedJets_jesdown,selectedJetsLoose_jesdown,selectedJetsSingleTop_jesdown,pfMETs[0],weights_jesdown);
  InputCollections input_uncorrjets( input_nominal,selectedJets_uncorrected,selectedJetsLoose_uncorrected,selectedJetsSingleTop_uncorrected,pfMETs[0],weights_uncorrjets);

  // DO SELECTION

  // all events survive step 0
  cutflow_nominal.EventSurvivedStep("all",input_nominal.weights.at("Weight"));
  if(makeSystematicsTrees){
    cutflow_jesup.EventSurvivedStep("all",input_jesup.weights.at("Weight"));
    cutflow_jesdown.EventSurvivedStep("all",input_jesdown.weights.at("Weight"));
  }
  bool selected_nominal=true;

  // dump l+jets sync exe for all events
  if(dumpSyncExe){
    synchronizer.DumpSyncExe1(0,input_nominal);
  }

  // dump globl Hbb sync exe for all events
  if(dumpSyncExe2){
      synchronizer.DumpSyncExe2(0,input_nominal,input_jesup,input_jesdown,input_uncorrjets,helper);
  }

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
  }

}


map<string,float> BoostedAnalyzer::GetWeights(const GenEventInfoProduct&  genEventInfo,const EventInfo& eventInfo, const reco::VertexCollection& selectedPVs, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon>& selectedMuons, const std::vector<reco::GenParticle>& genParticles, sysType::sysType systype){
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
  assert(genEventInfo.weights().size()<=1); // before we multiply any weights we should understand what they mean
  for(size_t i=0;i<genEventInfo.weights().size();i++){
     weight *= (genEventInfo.weights()[i]>0 ? 1.: -1.); // overwrite intransparent MC weights, use \pm 1 instead
  }
  
  //dummy variables for the get_csv_wgt function, might be useful for checks
  double csvWgtHF, csvWgtLF, csvWgtCF;

  float xsweight = xs*luminosity/totalMCevents;
  float csvweight = 1.;
  float puweight = 1.;
  float topptweight = 1.;
  if(systype==sysType::JESup)csvweight= csvReweighter.get_csv_wgt(selectedJets,7, csvWgtHF, csvWgtLF, csvWgtCF);
  else if(systype==sysType::JESdown)csvweight= csvReweighter.get_csv_wgt(selectedJets,8, csvWgtHF, csvWgtLF, csvWgtCF);
  else csvweight= csvReweighter.get_csv_wgt(selectedJets,0, csvWgtHF, csvWgtLF, csvWgtCF);
  //float puweight = beanHelper.GetPUweight(event[0].numTruePV);
  //float topptweight = beanHelper.GetTopPtweight(mcparticlesStatus3);
  //float q2scaleweight = beanHelper.GetQ2ScaleUp(const BNevent&);
  
  weight *= xsweight*csvweight*puweight*topptweight;
  weights["Weight"] = weight;
  weights["Weight_XS"] = xsweight;
  weights["Weight_CSV"] = csvweight;
  weights["Weight_PU"] = puweight;
  weights["Weight_TopPt"] = topptweight;
  weights["Weight_PV"] = pvWeight.GetWeight(selectedPVs.size());
  
  bool doSystematics=true;  
  if(doSystematics && systype != sysType::JESup && systype != sysType::JESup){
    //weights["Weight_TopPtup"] = beanHelper.GetTopPtweightUp(mcparticlesStatus3)/topptweight;
    //weights["Weight_TopPtdown"] = beanHelper.GetTopPtweightDown(mcparticlesStatus3)/topptweight;

    weights["Weight_CSVLFup"] = csvReweighter.get_csv_wgt(selectedJets,9, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVLFdown"] = csvReweighter.get_csv_wgt(selectedJets,10, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVHFup"] = csvReweighter.get_csv_wgt(selectedJets,11, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVHFdown"] = csvReweighter.get_csv_wgt(selectedJets,12, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVHFStats1up"] = csvReweighter.get_csv_wgt(selectedJets,13, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVHFStats1down"] = csvReweighter.get_csv_wgt(selectedJets,14, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVLFStats1up"] = csvReweighter.get_csv_wgt(selectedJets,17, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVLFStats1down"] = csvReweighter.get_csv_wgt(selectedJets,18, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVHFStats2up"] = csvReweighter.get_csv_wgt(selectedJets,15, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVHFStats2down"] = csvReweighter.get_csv_wgt(selectedJets,16, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVLFStats2up"] = csvReweighter.get_csv_wgt(selectedJets,19, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVLFStats2down"] = csvReweighter.get_csv_wgt(selectedJets,20, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVCErr1up"] = csvReweighter.get_csv_wgt(selectedJets,21, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVCErr1down"] = csvReweighter.get_csv_wgt(selectedJets,22, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVCErr2up"] = csvReweighter.get_csv_wgt(selectedJets,23, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    weights["Weight_CSVCErr2down"] = csvReweighter.get_csv_wgt(selectedJets,24, csvWgtHF, csvWgtLF, csvWgtCF)/csvweight;
    
    //weights["Weight_Q2up"] = beanHelper.GetQ2ScaleUp(event[0]);
    //weights["Weight_Q2down"] = beanHelper.GetQ2ScaleDown(event[0]);

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
  std::ofstream fout_nominal(outfileName+"_Cutflow.txt");
  cutflow_nominal.Print(fout_nominal);
  fout_nominal.close();
  if(makeSystematicsTrees){
    size_t stringIndex = outfileName.find("nominal");
    std::string jesDownName = outfileName;
    std::string jesUpName = outfileName;
    if(stringIndex==std::string::npos){
      jesUpName=outfileName+"_JESup_Cutflow.txt";
      jesDownName=outfileName+"_JESdown_Cutflow.txt";
    }
    else{
      jesUpName.replace(stringIndex,7,"JESUP");
      jesUpName+="_Cutflow.txt";
      jesDownName.replace(stringIndex,7,"JESDOWN");
      jesDownName+="_Cutflow.txt";
      std::cout<<jesUpName<<" "<<jesDownName<<std::endl;
    }
    std::ofstream fout_jesup(jesUpName);
    std::ofstream fout_jesdown(jesDownName);
    cutflow_jesup.Print(fout_jesup);
    cutflow_jesdown.Print(fout_jesdown);
    fout_jesup.close();
    fout_jesdown.close();
  }
}
// ------------ method called when starting to processes a run ------------
// needed for the hlt_config

void BoostedAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{

  std::string hltTag="HLT";
  bool hltchanged = true;
  if (!hlt_config.init(iRun, iSetup, hltTag, hltchanged)) {
    std::cout << "Warning, didn't find trigger process HLT,\t" << hltTag << std::endl;
    return;
  }

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
