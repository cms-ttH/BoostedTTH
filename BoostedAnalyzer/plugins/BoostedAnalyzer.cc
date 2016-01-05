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
#include "BoostedTTH/BoostedAnalyzer/interface/HbbSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/THQJetSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiJetSelection.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/WeightProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedMCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/AdditionalJetProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BasicVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MVAVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/RawVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/StdTopVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/SingleTopVarProcessor.hpp"
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
  map<string,float> GetWeights(const GenEventInfoProduct& genEventInfo, const LHEEventProduct&  LHEEvent, const EventInfo& eventInfo, const reco::VertexCollection& selectedPVs, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon>& selectedMuons, const std::vector<reco::GenParticle>& genParticles, sysType::sysType systype=sysType::NA);

      // ----------member data ---------------------------
      
      /** the miniAODhelper is used for selections and reweighting */
      MiniAODHelper helper;

      CSVHelper csvReweighter;
      HistoReweighter pvWeight;
      PUWeights puWeights_;
      
      /** writes flat trees for MVA analysis */
      TreeWriter treewriter_nominal;
      TreeWriter treewriter_jesup;
      TreeWriter treewriter_jesdown;
      TreeWriter treewriter_jerup;
      TreeWriter treewriter_jerdown;
          
      /** stores cutflow*/
      Cutflow cutflow_nominal;
      Cutflow cutflow_jesup;
      Cutflow cutflow_jesdown;
      Cutflow cutflow_jerup;
      Cutflow cutflow_jerdown;
      
      /** selections that are applied */
      vector<Selection*> selections;

      /** triggers that are checked */
      vector<std::string> relevantTriggers;
        
      std::string outfileName;
      std::string outfileNameNominal;
      std::string outfileNameJESup;
      std::string outfileNameJESdown;
      std::string outfileNameJERup;
      std::string outfileNameJERdown;

      /** sample ID */
      int sampleID;
      
      /** stops the time needed */
      TStopwatch watch;
      
      /** events to be analyzed */
      int maxEvents;
      
      /** xs*lumi/(nPosEvents-nNegEvents) */
      double eventWeight;
     
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

     /**recorrect the jets and MET that were in MiniAOD? **/
      bool recorrectMET;
      
      /** dump some event content for synchronization */
      bool dumpSyncExe;
      bool dumpSyncExe2;
      Synchronizer synchronizer;

      /** write systematics trees */
      bool makeSystematicsTrees;
      bool doJERsystematic;

      /** generator weigths */
      bool dogenweights;
      GenWeights genweights;
      std::string usedGenerator;

      GenTopEventProducer genTopEvtProd;

  // TOKENS =========================
      /** pu summary data access token **/
      edm::EDGetTokenT< std::vector<PileupSummaryInfo> > EDMPUInfoToken;
      
      /** pileup density data access token **/
      edm::EDGetTokenT <double> EDMRhoToken;

      /** hcal noise data access token **/
      edm::EDGetTokenT< HcalNoiseSummary > EDMHcalNoiseToken;
      

      edm::EDGetTokenT<edm::TriggerResults> triggerBitsToken;
      edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectsToken;
      edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescalesToken;

      /** beam spot data access token **/
      edm::EDGetTokenT< reco::BeamSpot > EDMBeamSpotToken;

      /** Conversions data access token **/
      edm::EDGetTokenT< reco::ConversionCollection > EDMConversionCollectionToken;
      
      /** vertex data access token **/
      edm::EDGetTokenT< reco::VertexCollection > EDMVertexToken;
      
      /** muons data access token **/
      edm::EDGetTokenT< std::vector<pat::Muon> > EDMMuonsToken;
      
      /** electrons data access token **/
      edm::EDGetTokenT< edm::View<pat::Electron> > EDMElectronsToken;
      
      /** jets data access token **/
      edm::EDGetTokenT< std::vector<pat::Jet> > EDMJetsToken;

      /** mets data access token **/
      edm::EDGetTokenT< std::vector<pat::MET> > EDMMETsToken;
      
      /** boosted jets data access token **/
      edm::EDGetTokenT< boosted::BoostedJetCollection > EDMBoostedJetsToken;
      
      /** gen info data access token **/
      edm::EDGetTokenT< GenEventInfoProduct > EDMGenInfoToken;
      
      /** LHE data access token **/
      edm::EDGetTokenT< LHEEventProduct > EDMLHEToken;

      /** gen particles data access token **/
      edm::EDGetTokenT< std::vector<reco::GenParticle> > EDMGenParticlesToken;
      
      /** gen jets data access token **/
      edm::EDGetTokenT< std::vector<reco::GenJet> > EDMGenJetsToken;

    /** electron MVA id tokens (implementation B) **/
    // TODO: the bools can only accessed with 
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/MultivariateElectronIdentificationRun2#VID_based_recipe_provides_pa_AN1
    //      edm::EDGetTokenT<edm::ValueMap<bool> > EDMele90idsToken;
    //      edm::EDGetTokenT<edm::ValueMap<bool> > EDMele80idsToken;
      // MVA values and categories
      edm::EDGetTokenT<edm::ValueMap<float> > EDMeleMVAvaluesToken;
      edm::EDGetTokenT<edm::ValueMap<int> > EDMeleMVAcategoriesToken;
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
BoostedAnalyzer::BoostedAnalyzer(const edm::ParameterSet& iConfig):csvReweighter(CSVHelper("MiniAOD/MiniAODHelper/data/csv_rwt_fit_hf_2015_11_20.root","MiniAOD/MiniAODHelper/data/csv_rwt_fit_lf_2015_11_20.root",5)),pvWeight((BoostedUtils::GetAnalyzerPath()+"/data/pvweights/PUhistos.root").c_str(),"data","mc"),genTopEvtProd(GenTopEventProducer(consumesCollector()))
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
  
  sampleID = iConfig.getParameter<int>("sampleID");
  eventWeight = iConfig.getParameter<double>("eventWeight");
  isData = iConfig.getParameter<bool>("isData");
  
  useFatJets = iConfig.getParameter<bool>("useFatJets");
  useForwardJets = iConfig.getParameter<bool>("useForwardJets");
  useGenHadronMatch = iConfig.getParameter<bool>("useGenHadronMatch");
  if(isData) useGenHadronMatch=false;

  recorrectMET = iConfig.getParameter<bool>("recorrectMET");

  dumpSyncExe = iConfig.getParameter<bool>("dumpSyncExe");
  dumpSyncExe2 = iConfig.getParameter<bool>("dumpSyncExe2");

  makeSystematicsTrees = iConfig.getParameter<bool>("makeSystematicsTrees");
  doJERsystematic = iConfig.getParameter<bool>("doJERsystematic");
  usedGenerator = iConfig.getParameter<std::string>("generatorName");
  outfileName = iConfig.getParameter<std::string>("outfileName");
  outfileNameNominal=outfileName;
  outfileNameJESup=outfileName;
  outfileNameJESdown=outfileName;
  outfileNameJERup=outfileName;
  outfileNameJERdown=outfileName;
  // the default filename should contain nominal
  size_t stringIndex = outfileName.find("nominal");
  if(stringIndex!=std::string::npos){
      outfileNameJESup.replace(stringIndex,7,"JESUP");
      outfileNameJESdown.replace(stringIndex,7,"JESDOWN");
      outfileNameJERup.replace(stringIndex,7,"JERUP");
      outfileNameJERdown.replace(stringIndex,7,"JERDOWN");
  }
  else{
      outfileNameNominal=outfileName+"_nominal";
      outfileNameJESup=outfileName+"_JESUP";
      outfileNameJESdown=outfileName+"_JESDOWN";
      outfileNameJERup=outfileName+"_JERUP";
      outfileNameJERdown=outfileName+"_JERDOWN";
  }


  // REGISTER DATA ACCESS
  EDMPUInfoToken          = consumes< std::vector<PileupSummaryInfo> >(edm::InputTag("slimmedAddPileupInfo","",""));
  EDMRhoToken             = consumes<double> (edm::InputTag(std::string("fixedGridRhoFastjetAll")));
  EDMHcalNoiseToken       = consumes< HcalNoiseSummary >(edm::InputTag("hcalnoise","",""));
  triggerBitsToken        = consumes< edm::TriggerResults>(edm::InputTag("TriggerResults","","HLT"));
  triggerObjectsToken     = consumes< pat::TriggerObjectStandAloneCollection>(edm::InputTag("selectedPatTrigger","",""));
  triggerPrescalesToken   = consumes< pat::PackedTriggerPrescales>(edm::InputTag("patTrigger","",""));
  EDMBeamSpotToken        = consumes< reco::BeamSpot > (edm::InputTag("offlineBeamSpot","",""));
  EDMVertexToken          = consumes< reco::VertexCollection > (edm::InputTag("offlineSlimmedPrimaryVertices","",""));
  EDMMuonsToken           = consumes< std::vector<pat::Muon> >(edm::InputTag("slimmedMuons","",""));
  EDMElectronsToken       = consumes< edm::View<pat::Electron> >(edm::InputTag("slimmedElectrons","",""));
  EDMJetsToken            = consumes< std::vector<pat::Jet> >(edm::InputTag("slimmedJets","",""));
  EDMMETsToken            = consumes< std::vector<pat::MET> >(edm::InputTag("slimmedMETs","",""));
  EDMBoostedJetsToken     = consumes< boosted::BoostedJetCollection >(edm::InputTag("BoostedJetMatcher","boostedjets","p"));
  EDMGenInfoToken         = consumes< GenEventInfoProduct >(edm::InputTag("generator","",""));
  EDMLHEToken             = consumes< LHEEventProduct >(edm::InputTag("externalLHEProducer","",""));
  EDMGenParticlesToken    = consumes< std::vector<reco::GenParticle> >(edm::InputTag("prunedGenParticles","",""));
  EDMGenJetsToken         = consumes< std::vector<reco::GenJet> >(edm::InputTag("slimmedGenJets","",""));
  EDMConversionCollectionToken        = consumes< reco::ConversionCollection > (edm::InputTag("reducedEgamma","reducedConversions",""));
  // electron MVA info
  // TODO: these (and many of the names above) shouldn't be hard coded but set in python cfg
  EDMeleMVAvaluesToken           = consumes<edm::ValueMap<float> >(edm::InputTag("electronMVAValueMapProducer","ElectronMVAEstimatorRun2Spring15Trig25nsV1Values",""));
  EDMeleMVAcategoriesToken       = consumes<edm::ValueMap<int> >(edm::InputTag("electronMVAValueMapProducer","ElectronMVAEstimatorRun2Spring15Trig25nsV1Categories",""));
  
  // INITIALIZE MINIAOD HELPER
  helper.SetUp(era, sampleID, iAnalysisType, isData);
  helper.SetJetCorrectorUncertainty();

  // INITIALIZE PU WEIGHTS
  puWeights_.init(iConfig);

  // INITIALIZE SELECTION & CUTFLOW
  cutflow_nominal.Init();
  if(makeSystematicsTrees){
    cutflow_jesup.Init();
    cutflow_jesdown.Init();
    if(doJERsystematic){
	cutflow_jerup.Init();
	cutflow_jerdown.Init();
    }
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
    else if(*itSel == "LooseLeptonSelection") selections.push_back(new LooseLeptonSelection(iConfig));
    else if(*itSel == "JetTagSelection") selections.push_back(new JetTagSelection(iConfig));
    else if(*itSel == "THQJetSelection") selections.push_back(new THQJetSelection());
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
    else if(*itSel == "FastSimMETSelection") selections.push_back(new METSelection(-1,800));
    else if(*itSel == "HbbSelection") selections.push_back(new HbbSelection());
    else if(*itSel == "4JetSelection") selections.push_back(new JetTagSelection(4,-1));
    else if(*itSel == "2TagSelection") selections.push_back(new JetTagSelection(-1,2));
    else if(*itSel == "BoostedTopSelection") selections.push_back(new BoostedSelection(1,0));
    else if(*itSel == "BoostedSelection") selections.push_back(new BoostedSelection(0,1));
    else if(*itSel == "DiJetSelection") selections.push_back(new DiJetSelection());
    else cout << "No matching selection found for: " << *itSel << endl;    
    selections.back()->InitCutflow(cutflow_nominal);
    if(makeSystematicsTrees){
      selections.back()->InitCutflow(cutflow_jesup);
      selections.back()->InitCutflow(cutflow_jesdown);
      if(doJERsystematic){
	  selections.back()->InitCutflow(cutflow_jerup);
	  selections.back()->InitCutflow(cutflow_jerdown);
      }
    }
    
    nselection++;     
    if(dumpSyncExe){
      synchronizer.InitDumpSyncFile1(outfileName+"_Dump1_"+std::to_string(nselection));
    }  
  }
  relevantTriggers = iConfig.getParameter< std::vector<std::string> >("relevantTriggers");

  // INITIALIZE TREEWRITER
  treewriter_nominal.Init(outfileNameNominal);  
  // in case of systematics
  if(makeSystematicsTrees){
      // this is are the usual tree names
      treewriter_jesup.Init(outfileNameJESup);
      treewriter_jesdown.Init(outfileNameJESdown);
      if(doJERsystematic){
	  treewriter_jerup.Init(outfileNameJERup);
	  treewriter_jerdown.Init(outfileNameJERdown);
      }
  }

  std::vector<std::string> processorNames = iConfig.getParameter< std::vector<std::string> >("processorNames");
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
  if(std::find(processorNames.begin(),processorNames.end(),"RawVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new RawVarProcessor(),"RawVarProcessor");
  }
  if(std::find(processorNames.begin(),processorNames.end(),"StdTopVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new StdTopVarProcessor(),"StdTopVarProcessor");
  }
  if(std::find(processorNames.begin(),processorNames.end(),"SingleTopVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new SingleTopVarProcessor(),"SingleTopVarProcessor");
  }
  if(std::find(processorNames.begin(),processorNames.end(),"BoostedJetVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new BoostedJetVarProcessor(&helper),"BoostedJetVarProcessor");
  }
  if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopHiggsVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,&helper,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml",HiggsTag::SecondCSV,"","BoostedTopHiggs_"),"BoostedTopHiggsVarProcessor");
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
    treewriter_nominal.AddTreeProcessor(new MEMProcessor(),"MEMProcessor");
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
  if(std::find(processorNames.begin(),processorNames.end(),"DiJetVarProcessor")!=processorNames.end()) {
    treewriter_nominal.AddTreeProcessor(new DiJetVarProcessor(),"DiJetVarProcessor");
  }


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


  /**** GET BEAMSPOT ****/
  edm::Handle<reco::BeamSpot> h_beamspot;
  iEvent.getByToken( EDMBeamSpotToken,h_beamspot );

  /**** GET Conversions ****/
  edm::Handle<reco::ConversionCollection> h_conversioncollection;
  iEvent.getByToken( EDMConversionCollectionToken,h_conversioncollection );
  
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
  helper.AddMuonRelIso(rawMuons, coneSize::R04, corrType::deltaBeta,"relIso");
  std::vector<pat::Muon> selectedMuons = helper.GetSelectedMuons( rawMuons, 25., muonID::muonTight, coneSize::R04, corrType::deltaBeta, 2.1);
  std::vector<pat::Muon> selectedMuonsDL = helper.GetSelectedMuons( rawMuons, 20., muonID::muonTightDL, coneSize::R04, corrType::deltaBeta, 2.4 );
  std::vector<pat::Muon> selectedMuonsLoose = helper.GetSelectedMuons( rawMuons, 15., muonID::muonTightDL, coneSize::R04, corrType::deltaBeta, 2.4);

  // ELECTRONS
  edm::Handle< edm::View<pat::Electron> > h_electrons;
  iEvent.getByToken( EDMElectronsToken,h_electrons );
  // add electron mva info to electrons
  edm::Handle<edm::ValueMap<float> > h_mvaValues; 
  edm::Handle<edm::ValueMap<int> > h_mvaCategories;
  iEvent.getByToken(EDMeleMVAvaluesToken,h_mvaValues);
  iEvent.getByToken(EDMeleMVAcategoriesToken,h_mvaCategories);  
  std::vector<pat::Electron> electrons = helper.GetElectronsWithMVAid(h_electrons,h_mvaValues,h_mvaCategories);
  helper.AddElectronRelIso(electrons,coneSize::R03, corrType::rhoEA,effAreaType::spring15,"relIso");
  std::vector<pat::Electron> rawElectrons = electrons;
  std::vector<pat::Electron> selectedElectrons = helper.GetSelectedElectrons( electrons, 30., electronID::electronEndOf15MVA80iso0p15, 2.1 );
  std::vector<pat::Electron> selectedElectronsDL = helper.GetSelectedElectrons( electrons, 20., electronID::electronEndOf15MVA80iso0p15, 2.4 );
  std::vector<pat::Electron> selectedElectronsLoose = helper.GetSelectedElectrons( electrons, 15., electronID::electronEndOf15MVA80iso0p15, 2.4 );
  /**** GET MET ****/
  edm::Handle< std::vector<pat::MET> > h_pfmet;
  iEvent.getByToken( EDMMETsToken,h_pfmet );
  std::vector<pat::MET> const &pfMETs = *h_pfmet;

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
  // Get the jets for MET correction
  std::vector<pat::Jet> idJetsForMET = helper.GetSelectedJets(pfjets, 0., 5.4, jetID::jetMETcorrection, '-' );
  std::vector<pat::Jet> rawJetsForMET = helper.GetUncorrectedJets(idJetsForMET);
  std::vector<pat::Jet> correctedJetsForMET_nominal = helper.GetCorrectedJets(rawJetsForMET, iEvent, iSetup, sysType::NA, true, false);
  //correct MET 
  std::vector<pat::MET> correctedMETs_nominal = recorrectMET ? helper.CorrectMET(idJetsForMET,correctedJetsForMET_nominal,pfMETs) : pfMETs;
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

  std::vector<pat::Jet> correctedJetsForMET_jesup;
  std::vector<pat::Jet> correctedJetsForMET_jesdown;
  std::vector<pat::MET> correctedMETs_jesup;
  std::vector<pat::MET> correctedMETs_jesdown;

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
 
    correctedJetsForMET_jesup = helper.GetCorrectedJets(rawJetsForMET, iEvent, iSetup, sysType::JESup);
    correctedJetsForMET_jesdown = helper.GetCorrectedJets(rawJetsForMET, iEvent, iSetup, sysType::JESdown);
    correctedMETs_jesup = recorrectMET ? helper.CorrectMET(idJetsForMET,correctedJetsForMET_jesup,pfMETs) : pfMETs;
    correctedMETs_jesdown = recorrectMET ? helper.CorrectMET(idJetsForMET,correctedJetsForMET_jesdown,pfMETs) : pfMETs;

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

  // Apply systematically shifted jet resolution -- these vector stay empty if you dont use makeSystematicsTrees
  std::vector<pat::Jet> correctedJets_unsorted_jerup;
  std::vector<pat::Jet> correctedJets_unsorted_jerdown;

  std::vector<pat::Jet> correctedJetsForMET_jerup;
  std::vector<pat::Jet> correctedJetsForMET_jerdown;
  std::vector<pat::MET> correctedMETs_jerup;
  std::vector<pat::MET> correctedMETs_jerdown;

  std::vector<pat::Jet> selectedJets_unsorted_jerup;
  std::vector<pat::Jet> selectedJets_unsorted_jerdown;
  std::vector<pat::Jet> selectedJetsLoose_unsorted_jerup;
  std::vector<pat::Jet> selectedJetsLoose_unsorted_jerdown;

  std::vector<pat::Jet> selectedJets_jerup;
  std::vector<pat::Jet> selectedJets_jerdown;
  std::vector<pat::Jet> selectedJetsLoose_jerup;
  std::vector<pat::Jet> selectedJetsLoose_jerdown;

  std::vector<pat::Jet> selectedJetsSingleTop_jerup;
  std::vector<pat::Jet> selectedJetsSingleTop_jerdown;
  
  if(makeSystematicsTrees && doJERsystematic){
    correctedJets_unsorted_jerup = helper.GetCorrectedJets(cleanJets, iEvent, iSetup, sysType::JERup);
    correctedJets_unsorted_jerdown = helper.GetCorrectedJets(cleanJets, iEvent, iSetup, sysType::JERdown);

    correctedJetsForMET_jerup = helper.GetCorrectedJets(rawJetsForMET, iEvent, iSetup, sysType::JERup);
    correctedJetsForMET_jerdown = helper.GetCorrectedJets(rawJetsForMET, iEvent, iSetup, sysType::JERdown);
    correctedMETs_jerup = recorrectMET ? helper.CorrectMET(idJetsForMET,correctedJetsForMET_jerup,pfMETs) : pfMETs;
    correctedMETs_jerdown = recorrectMET ? helper.CorrectMET(idJetsForMET,correctedJetsForMET_jerdown,pfMETs) : pfMETs;

    selectedJets_unsorted_jerup = helper.GetSelectedJets(correctedJets_unsorted_jerup, jetptcut, jetetacut, jetID::none, '-' );
    selectedJets_unsorted_jerdown = helper.GetSelectedJets(correctedJets_unsorted_jerdown, jetptcut, jetetacut, jetID::none, '-' );
    selectedJetsLoose_unsorted_jerup = helper.GetSelectedJets(correctedJets_unsorted_jerup, jetptcut_loose, jetetacut_loose, jetID::none, '-' ); 
    selectedJetsLoose_unsorted_jerdown = helper.GetSelectedJets(correctedJets_unsorted_jerdown, jetptcut_loose,jetetacut_loose, jetID::none, '-' ); 

    selectedJets_jerup = helper.GetSortedByPt(selectedJets_unsorted_jerup);
    selectedJets_jerdown = helper.GetSortedByPt(selectedJets_unsorted_jerdown);
    selectedJetsLoose_jerup = helper.GetSortedByPt(selectedJetsLoose_unsorted_jerup);
    selectedJetsLoose_jerdown = helper.GetSortedByPt(selectedJetsLoose_unsorted_jerdown);

    if(useForwardJets){

	std::vector<pat::Jet> selectedJetsForward_unsorted_jerup = helper.GetSelectedJets(correctedJets_unsorted_jerup, jetptcut_forward, jetetacut_forward, jetID::none, '-' ); 
	std::vector<pat::Jet> selectedJetsForward_unsorted_jerdown = helper.GetSelectedJets(correctedJets_unsorted_jerdown, jetptcut_forward,jetetacut_forward, jetID::none, '-' ); 
	
	std::vector<pat::Jet> selectedJetsSingleTop_unsorted_jerup = BoostedUtils::GetSingleTopJets(selectedJetsLoose_jerup,selectedJetsForward_unsorted_jerup,jetetacut_loose);
	std::vector<pat::Jet> selectedJetsSingleTop_unsorted_jerdown = BoostedUtils::GetSingleTopJets(selectedJetsLoose_jerdown,selectedJetsForward_unsorted_jerdown,jetetacut_loose);

	selectedJetsSingleTop_jerup = helper.GetSortedByPt(selectedJetsSingleTop_unsorted_jerup);
	selectedJetsSingleTop_jerdown = helper.GetSortedByPt(selectedJetsSingleTop_unsorted_jerdown);
    }
  }

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

  /**** GET LHEEVENTPRODUCT ****/

  edm::Handle<LHEEventProduct> h_lheevent;
  edm::Handle<LHEEventProduct> h_dummie;
  if(!isData){
    iEvent.getByToken( EDMLHEToken, h_dummie );
    if (h_dummie.isValid()){
      iEvent.getByToken( EDMLHEToken, h_lheevent );
      dogenweights = true;
    }
    else {
      dogenweights = false;
    }
  }


  /**** Get GENPARTICLES ****/
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
  
  
 
  // Fill Event Info Object
  EventInfo eventInfo(iEvent,h_beamspot,h_hcalnoisesummary,h_puinfosummary,firstVertexIsGood,*h_rho);
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
  GenTopEvent genTopEvt=genTopEvtProd.Produce(iEvent,useGenHadronMatch,!isData&&foundT&&foundTbar);
  int ttid = genTopEvt.GetTTxIdFromProducer();
      
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
  map<string,float> weights = GetWeights(*h_geneventinfo,*h_lheevent,eventInfo,selectedPVs,selectedJets_nominal,selectedElectrons,selectedMuons,*h_genParticles,sysType::NA);
  map<string,float> weights_jesup = GetWeights(*h_geneventinfo,*h_lheevent,eventInfo,selectedPVs,selectedJets_jesup,selectedElectrons,selectedMuons,*h_genParticles,sysType::JESup);
  map<string,float> weights_jesdown = GetWeights(*h_geneventinfo,*h_lheevent,eventInfo,selectedPVs,selectedJets_jesdown,selectedElectrons,selectedMuons,*h_genParticles,sysType::JESdown);
  map<string,float> weights_jerup = GetWeights(*h_geneventinfo,*h_lheevent,eventInfo,selectedPVs,selectedJets_jerup,selectedElectrons,selectedMuons,*h_genParticles,sysType::JERup);
  map<string,float> weights_jerdown = GetWeights(*h_geneventinfo,*h_lheevent,eventInfo,selectedPVs,selectedJets_jerdown,selectedElectrons,selectedMuons,*h_genParticles,sysType::JERdown);
  map<string,float> weights_uncorrjets = GetWeights(*h_geneventinfo,*h_lheevent,eventInfo,selectedPVs,selectedJets_uncorrected,selectedElectrons,selectedMuons,*h_genParticles,sysType::NA);
     //Only needed for Hbb synch exercise: dilepton uses loose jet selection -> different csv weights
  map<string,float> weights_DL_nominal = GetWeights(*h_geneventinfo,*h_lheevent,eventInfo,selectedPVs,selectedJetsLoose_nominal,selectedElectrons,selectedMuons,*h_genParticles,sysType::NA);
  map<string,float> weights_DL_jesup = GetWeights(*h_geneventinfo,*h_lheevent,eventInfo,selectedPVs,selectedJetsLoose_jesup,selectedElectrons,selectedMuons,*h_genParticles,sysType::JESup);
  map<string,float> weights_DL_jesdown = GetWeights(*h_geneventinfo,*h_lheevent,eventInfo,selectedPVs,selectedJetsLoose_jesdown,selectedElectrons,selectedMuons,*h_genParticles,sysType::JESdown);
  map<string,float> weights_DL_jerup = GetWeights(*h_geneventinfo,*h_lheevent,eventInfo,selectedPVs,selectedJetsLoose_jerup,selectedElectrons,selectedMuons,*h_genParticles,sysType::JERup);
  map<string,float> weights_DL_jerdown = GetWeights(*h_geneventinfo,*h_lheevent,eventInfo,selectedPVs,selectedJetsLoose_jerdown,selectedElectrons,selectedMuons,*h_genParticles,sysType::JERdown);
  map<string,float> weights_DL_uncorrjets = GetWeights(*h_geneventinfo,*h_lheevent,eventInfo,selectedPVs,selectedJetsLoose_uncorrected,selectedElectrons,selectedMuons,*h_genParticles,sysType::NA);
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
				  idJets,
				  rawJets,
				  selectedJets_nominal,
				  selectedJetsLoose_nominal,
				  selectedJetsSingleTop_nominal,
				  correctedMETs_nominal[0],
				  selectedBoostedJets,
				  genTopEvt,
				  selectedGenJets,
				  sampleType,
				  higgsdecay,
				  weights
				  );

  // define systematically shifted input (replace quantaties affected by jets)
  InputCollections input_jesup( input_nominal,selectedJets_jesup,selectedJetsLoose_jesup,selectedJetsSingleTop_jesup,correctedMETs_jesup[0],weights_jesup);
  InputCollections input_jesdown( input_nominal,selectedJets_jesdown,selectedJetsLoose_jesdown,selectedJetsSingleTop_jesdown,correctedMETs_jesdown[0],weights_jesdown);
  InputCollections input_jerup( input_nominal,selectedJets_jerup,selectedJetsLoose_jerup,selectedJetsSingleTop_jerup,correctedMETs_jerup[0],weights_jerup);
  InputCollections input_jerdown( input_nominal,selectedJets_jerdown,selectedJetsLoose_jerdown,selectedJetsSingleTop_jerdown,correctedMETs_jerdown[0],weights_jerdown);
  InputCollections input_uncorrjets( input_nominal,selectedJets_uncorrected,selectedJetsLoose_uncorrected,selectedJetsSingleTop_uncorrected,pfMETs[0],weights_uncorrjets);
     //Only needed for Hbb synch exercise: dilepton uses loose jet selection -> different csv weights and input collection
  InputCollections input_DL_nominal( input_nominal,selectedJetsLoose_nominal,selectedJetsLoose_nominal,selectedJetsSingleTop_nominal,correctedMETs_nominal[0],weights_DL_nominal);
  InputCollections input_DL_jesup( input_nominal,selectedJetsLoose_jesup,selectedJetsLoose_jesup,selectedJetsSingleTop_jesup,correctedMETs_jesup[0],weights_DL_jesup);
  InputCollections input_DL_jesdown( input_nominal,selectedJetsLoose_jesdown,selectedJetsLoose_jesdown,selectedJetsSingleTop_jesdown,correctedMETs_jesdown[0],weights_DL_jesdown);
  InputCollections input_DL_jerup( input_nominal,selectedJetsLoose_jerup,selectedJetsLoose_jerup,selectedJetsSingleTop_jerup,correctedMETs_jerup[0],weights_DL_jerup);
  InputCollections input_DL_jerdown( input_nominal,selectedJetsLoose_jerdown,selectedJetsLoose_jerdown,selectedJetsSingleTop_jerdown,correctedMETs_jerdown[0],weights_DL_jerdown);
  InputCollections input_DL_uncorrjets( input_nominal,selectedJetsLoose_uncorrected,selectedJetsLoose_uncorrected,selectedJetsSingleTop_uncorrected,pfMETs[0],weights_DL_uncorrjets);

  // DO SELECTION

  // all events survive step 0
  cutflow_nominal.EventSurvivedStep("all",input_nominal.weights.at("Weight"));
  if(makeSystematicsTrees){
    cutflow_jesup.EventSurvivedStep("all",input_jesup.weights.at("Weight"));
    cutflow_jesdown.EventSurvivedStep("all",input_jesdown.weights.at("Weight"));
    if(doJERsystematic){
	cutflow_jerup.EventSurvivedStep("all",input_jerup.weights.at("Weight"));
	cutflow_jerdown.EventSurvivedStep("all",input_jerdown.weights.at("Weight"));
    }
  }
  bool selected_nominal=true;

  // dump l+jets sync exe for all events
  if(dumpSyncExe){
    synchronizer.DumpSyncExe1(0,input_nominal);
  }

  // dump globl Hbb sync exe for all events
  if(dumpSyncExe2){
      synchronizer.DumpSyncExe2(0,input_nominal,input_jesup,input_jesdown,input_uncorrjets,input_DL_nominal,input_DL_jesup,input_DL_jesdown,input_DL_uncorrjets,helper);
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

}


map<string,float> BoostedAnalyzer::GetWeights(const GenEventInfoProduct&  genEventInfo, const LHEEventProduct&  LHEEvent, const EventInfo& eventInfo, const reco::VertexCollection& selectedPVs, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon>& selectedMuons, const std::vector<reco::GenParticle>& genParticles, sysType::sysType systype){
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
  
  //dummy variables for the getCSVWeight function, might be useful for checks
  double csvWgtHF, csvWgtLF, csvWgtCF;

  float xsweight = eventWeight;
  float csvweight = 1.;
  float puweight = 1.;
  //  float topptweight = 1.;

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
  
  weight *= xsweight*csvweight*puweight;
  weights["Weight"] = weight;
  weights["Weight_XS"] = xsweight;
  weights["Weight_CSV"] = csvweight;
  weights["Weight_PU"] = puweight;
  //  weights["Weight_TopPt"] = topptweight;
  weights["Weight_PV"] = pvWeight.GetWeight(selectedPVs.size());
  
  bool doSystematics=true;  
  if(doSystematics && systype != sysType::JESup && systype != sysType::JESup && systype != sysType::JERup && systype != sysType::JERdown) {

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
    
    //weights["Weight_Q2up"] = beanHelper.GetQ2ScaleUp(event[0]);
    //weights["Weight_Q2down"] = beanHelper.GetQ2ScaleDown(event[0]);
    

    // set optional additional PU weights
    for(std::vector<PUWeights::Weight>::const_iterator it = puWeights_.additionalWeightsBegin();
	it != puWeights_.additionalWeightsEnd(); ++it) {
      weights[it->name()] = it->value();
    }
    //Add Genweights to the weight map
    genweights.GetGenWeights(weights, LHEEvent, dogenweights);
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
