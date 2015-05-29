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

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/CSVHelper.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeWriter.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/TopTagger.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/HiggsTagger.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/VertexSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/HbbSelection.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/WeightProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedMCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MVAVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedJetVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/ttHVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/EventInfo.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

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
  map<string,float> GetWeights(const GenEventInfoProduct& genEventInfo, const EventInfo& eventInfo, const reco::VertexCollection& selectedPVs, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon>& selectedMuons, const std::vector<reco::GenParticle>& genParticles);

      // ----------member data ---------------------------
      
      /** the miniAODhelper is used for selections and reweighting */
      MiniAODHelper helper;

      /** the miniAODhelper is used for selections and reweighting */
      CSVHelper csvReweighter;
      
      /** writes flat trees for MVA analysis */
      TreeWriter treewriter;
      
      /** stores cutflow*/
      Cutflow cutflow;
      
      /** toptagger used for selection */
      TopTagger toptagger;
      
      /** higgstagger used for selection */
      HiggsTagger higgstagger;
      
      /** selections that are applied */
      vector<Selection*> selections;

      /** triggers that are checked */
      vector<std::string> relevantTriggers;

      /** files to dump eventnumber into */
      vector<std::ofstream*> dumpFiles;
        
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

       /** use GenBmatching info? this is only possible if the miniAOD contains them */
      bool useGenHadronMatch;
      
      /** dump some event content for synchronization */
      bool dumpSyncExe;
      
      /** jet systematic that is applied (the outher systematics are done at a different place with reweighting)*/
      sysType::sysType jsystype;
      
  // TOKENS =========================
      /** pu summary data access token **/
      edm::EDGetTokenT< std::vector<PileupSummaryInfo> > EDMPUInfoToken;
      
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
      
      /** hep top jets data access token **/
      edm::EDGetTokenT< boosted::HEPTopJetCollection > EDMHEPTopJetsToken;
      
      /** subjet filterjets data access token **/
      edm::EDGetTokenT< boosted::SubFilterJetCollection > EDMSubFilterJetsToken;
      
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
      edm::EDGetTokenT<std::vector<std::vector<int> > > genBHadPlusMothersIndicesToken;
      edm::EDGetTokenT<std::vector<int> > genBHadIndexToken;
      edm::EDGetTokenT<std::vector<int> > genBHadLeptonHadronIndexToken;
      edm::EDGetTokenT<std::vector<int> > genBHadLeptonViaTauToken;
      edm::EDGetTokenT<std::vector<int> > genCHadJetIndexToken;
      edm::EDGetTokenT<std::vector<int> > genCHadFlavourToken;
      edm::EDGetTokenT<std::vector<int> > genCHadFromTopWeakDecayToken;
      edm::EDGetTokenT<std::vector<int> > genCHadBHadronIdToken;
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
BoostedAnalyzer::BoostedAnalyzer(const edm::ParameterSet& iConfig)
{

  std::string era = iConfig.getParameter<std::string>("era");
  string analysisType = iConfig.getParameter<std::string>("analysisType");
  analysisType::analysisType iAnalysisType = analysisType::LJ;
  if(analysisType == "LJ") iAnalysisType = analysisType::LJ;
  else if(analysisType == "DIL") iAnalysisType = analysisType::DIL;
  else if(analysisType == "TauLJ") iAnalysisType = analysisType::TauLJ;
  else if(analysisType == "TauDIL") iAnalysisType = analysisType::TauDIL;
  else cerr << "No matching analysis type found for: " << analysisType << endl;
  
  jsystype=sysType::NA;
  std::string SystematicType= iConfig.getParameter<std::string>("systematicType");
  if(SystematicType=="JESUP" ||  SystematicType=="JESUp" )jsystype=sysType::JESup;
  else if(SystematicType=="JESDOWN" || SystematicType=="JESDown" )jsystype=sysType::JESdown;
  else jsystype=sysType::NA;

  luminosity = iConfig.getParameter<double>("luminosity");
  sampleID = iConfig.getParameter<int>("sampleID");
  xs = iConfig.getParameter<double>("xs");
  totalMCevents = iConfig.getParameter<int>("nMCEvents");
  isData = iConfig.getParameter<bool>("isData");
  
  useFatJets = iConfig.getParameter<bool>("useFatJets");
  useGenHadronMatch = iConfig.getParameter<bool>("useGenHadronMatch");

  dumpSyncExe = iConfig.getParameter<bool>("dumpSyncExe");

  string outfileName = iConfig.getParameter<std::string>("outfileName");
  // REGISTER DATA ACCESS
  EDMPUInfoToken          = consumes< std::vector<PileupSummaryInfo> >(edm::InputTag("addPileupInfo","",""));
  EDMHcalNoiseToken       = consumes< HcalNoiseSummary >(edm::InputTag("hcalnoise","",""));
  EDMSelectedTriggerToken = consumes< pat::TriggerObjectStandAloneCollection > (edm::InputTag("selectedPatTrigger","",""));
  EDMTriggerResultToken   = consumes< edm::TriggerResults > (edm::InputTag("TriggerResults","","HLT"));
  EDMBeamSpotToken        = consumes< reco::BeamSpot > (edm::InputTag("offlineBeamSpot","",""));
  EDMVertexToken          = consumes< reco::VertexCollection > (edm::InputTag("offlineSlimmedPrimaryVertices","",""));
  EDMMuonsToken           = consumes< std::vector<pat::Muon> >(edm::InputTag("slimmedMuons","",""));
  EDMElectronsToken       = consumes< std::vector<pat::Electron> >(edm::InputTag("slimmedElectrons","",""));
  EDMJetsToken            = consumes< std::vector<pat::Jet> >(edm::InputTag("slimmedJets","",""));
  EDMMETsToken            = consumes< std::vector<pat::MET> >(edm::InputTag("slimmedMETs","",""));
  EDMHEPTopJetsToken      = consumes< boosted::HEPTopJetCollection >(edm::InputTag("HEPTopJetsPFMatcher","heptopjets",""));
  EDMSubFilterJetsToken   = consumes< boosted::SubFilterJetCollection >(edm::InputTag("CA12JetsCA3FilterjetsPFMatcher","subfilterjets",""));
  EDMGenInfoToken         = consumes< GenEventInfoProduct >(edm::InputTag("generator","",""));
  EDMGenParticlesToken    = consumes< std::vector<reco::GenParticle> >(edm::InputTag("prunedGenParticles","",""));
  EDMGenJetsToken         = consumes< std::vector<reco::GenJet> >(edm::InputTag("slimmedGenJets","",""));
  EDMCustomGenJetsToken   = consumes< std::vector<reco::GenJet> >(edm::InputTag("ak4GenJetsCustom","",""));
  // for tt+X categorizations
  genBHadJetIndexToken           = consumes<std::vector<int> >(edm::InputTag("matchGenBHadron","genBHadJetIndex","p"));
  genBHadFlavourToken            = consumes<std::vector<int> >(edm::InputTag("matchGenBHadron","genBHadFlavour","p"));
  genBHadFromTopWeakDecayToken   = consumes<std::vector<int> >(edm::InputTag("matchGenBHadron","genBHadFromTopWeakDecay","p"));
  genBHadPlusMothersToken        = consumes<std::vector<reco::GenParticle> >(edm::InputTag("matchGenBHadron","genBHadPlusMothers","p"));
  genBHadPlusMothersIndicesToken = consumes<std::vector<std::vector<int> > >(edm::InputTag("matchGenBHadron","genBHadPlusMothersIndices","p"));
  genBHadIndexToken              = consumes<std::vector<int> >(edm::InputTag("matchGenBHadron","genBHadIndex"));
  genBHadLeptonHadronIndexToken  = consumes<std::vector<int> >(edm::InputTag("matchGenBHadron","genBHadLeptonHadronIndex","p"));
  genBHadLeptonViaTauToken       = consumes<std::vector<int> >(edm::InputTag("matchGenBHadron","genBHadLeptonViaTau","p"));
  genCHadJetIndexToken           = consumes<std::vector<int> >(edm::InputTag("matchGenCHadron","genCHadJetIndex","p"));
  genCHadFlavourToken            = consumes<std::vector<int> >(edm::InputTag("matchGenCHadron","genCHadFlavour","p"));
  genCHadFromTopWeakDecayToken   = consumes<std::vector<int> >(edm::InputTag("matchGenCHadron","genCHadFromTopWeakDecay","p"));
  genCHadBHadronIdToken          = consumes<std::vector<int> >(edm::InputTag("matchGenCHadron","genCHadBHadronId","p"));
  // INITIALIZE MINIAOD HELPER
  helper.SetUp(era, sampleID, iAnalysisType, isData);
  helper.SetJetCorrectorUncertainty();
  
  // INITIALIZE SELECTION & CUTFLOW
  cutflow.Init((outfileName+"_Cutflow.txt").c_str());
  cutflow.AddStep("all");
  std::vector<std::string> selectionNames = iConfig.getParameter< std::vector<std::string> >("selectionNames");
  int nselection=0;
  for(vector<string>::const_iterator itSel = selectionNames.begin();itSel != selectionNames.end();itSel++) {    
    cout << *itSel << endl;
    if(*itSel == "VertexSelection") selections.push_back(new VertexSelection());
    else if(*itSel == "LeptonSelection") selections.push_back(new LeptonSelection(iConfig));
    else if(*itSel == "JetTagSelection") selections.push_back(new JetTagSelection(iConfig));
    else if(*itSel == "LeptonSelection1") selections.push_back(new LeptonSelection(iConfig,1));
    else if(*itSel == "LeptonSelection2") selections.push_back(new LeptonSelection(iConfig,2));
    else if(*itSel == "LeptonSelection3") selections.push_back(new LeptonSelection(iConfig,3));
    else if(*itSel == "LeptonSelection4") selections.push_back(new LeptonSelection(iConfig,4));
    else if(*itSel == "HbbSelection") selections.push_back(new HbbSelection());
    else if(*itSel == "4JetSelection"){
      vector<int> njets;
      njets.push_back(4);
      vector<int> ntags;
      ntags.push_back(-1);
      selections.push_back(new JetTagSelection(njets,ntags));
    }
    else if(*itSel == "2TagSelection") {
      vector<int> ntags;
      ntags.push_back(2);
      vector<int> njets;
      njets.push_back(-1);
      selections.push_back(new JetTagSelection(njets,ntags));
    }
    else cout << "No matching selection found for: " << *itSel << endl;    
    selections.back()->InitCutflow(cutflow);
    nselection++;       
    if(dumpSyncExe){
      dumpFiles.push_back(new ofstream((outfileName+"_Dump_"+std::to_string(nselection)+".txt").c_str()));
    }   
  }
  relevantTriggers = iConfig.getParameter< std::vector<std::string> >("relevantTriggers");
  // INITIALIZE TREEWRITER
  treewriter.Init(outfileName);
  std::vector<std::string> processorNames = iConfig.getParameter< std::vector<std::string> >("processorNames");
  cout << "using processors:" << endl; 
  for(vector<string>::const_iterator itPro = processorNames.begin();itPro != processorNames.end();++itPro) {
    cout << *itPro << endl;
  }
  if(std::find(processorNames.begin(),processorNames.end(),"WeightProcessor")!=processorNames.end()) treewriter.AddTreeProcessor(new WeightProcessor());
  if(std::find(processorNames.begin(),processorNames.end(),"MVAVarProcessor")!=processorNames.end()) treewriter.AddTreeProcessor(new MVAVarProcessor());
  if(std::find(processorNames.begin(),processorNames.end(),"BoostedJetVarProcessor")!=processorNames.end()) treewriter.AddTreeProcessor(new BoostedJetVarProcessor());
  if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopHiggsVarProcessor")!=processorNames.end()) treewriter.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,"TopLikelihood","HiggsCSV","BoostedTopHiggs_"));
  if(std::find(processorNames.begin(),processorNames.end(),"BoostedTopVarProcessor")!=processorNames.end()) treewriter.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,"TopLikelihood","HiggsCSV","BoostedTop_"));
  if(std::find(processorNames.begin(),processorNames.end(),"BoostedHiggsVarProcessor")!=processorNames.end()) treewriter.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,"TopLikelihood","HiggsCSV","BoostedHiggs_"));
  if(std::find(processorNames.begin(),processorNames.end(),"BDTVarProcessor")!=processorNames.end()) treewriter.AddTreeProcessor(new BDTVarProcessor());
  if(std::find(processorNames.begin(),processorNames.end(),"MCMatchVarProcessor")!=processorNames.end()) treewriter.AddTreeProcessor(new MCMatchVarProcessor());
  if(std::find(processorNames.begin(),processorNames.end(),"BoostedMCMatchVarProcessor")!=processorNames.end()) treewriter.AddTreeProcessor(new BoostedMCMatchVarProcessor());
}


BoostedAnalyzer::~BoostedAnalyzer()
{
  for(auto f = dumpFiles.begin(); f!=dumpFiles.end(); f++){
    (*f)->close();
  }
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
  std::vector<pat::Muon> selectedMuons = helper.GetSelectedMuons( muons, 30., muonID::muonTight, 2.1 );
  std::vector<pat::Muon> selectedMuonsLoose = helper.GetSelectedMuons( muons, 10., muonID::muonLoose, 2.4 );  // for the sake of sync: loose == tight

  // ELECTRONS
  edm::Handle< std::vector<pat::Electron> > h_electrons;
  iEvent.getByToken( EDMElectronsToken,h_electrons );
  std::vector<pat::Electron> const &electrons = *h_electrons;
  std::vector<pat::Electron> selectedElectrons = helper.GetSelectedElectrons( electrons, 30., electronID::electronPhys14M, 2.1 );
  std::vector<pat::Electron> selectedElectronsLoose = helper.GetSelectedElectrons( electrons, 10., electronID::electronPhys14L, 2.4 );

  /**** GET JETS ****/
  edm::Handle< std::vector<pat::Jet> > h_pfjets;
  iEvent.getByToken( EDMJetsToken,h_pfjets );
  std::vector<pat::Jet> const &pfjets = *h_pfjets;

  // initialize jetcorrector
  const JetCorrector* corrector = JetCorrector::getJetCorrector( "ak4PFchsL1L2L3", iSetup );
  helper.SetJetCorrector(corrector);


  // Get raw jets
  std::vector<pat::Jet> rawJets = helper.GetUncorrectedJets(pfjets);
  // selected jets with jet ID cuts
  std::vector<pat::Jet> idJets = helper.GetSelectedJets(rawJets, 0., 999., jetID::jetLoose, '-' );
  // Clean muons from jets
  std::vector<pat::Jet> jetsNoMu = helper.RemoveOverlaps(selectedMuonsLoose, idJets);
  // Clean electrons from jets
  std::vector<pat::Jet> jetsNoEle = helper.RemoveOverlaps(selectedElectronsLoose, jetsNoMu);
  // Apply jet corrections
   std::vector<pat::Jet> correctedJets_unsorted = helper.GetCorrectedJets(jetsNoEle, iEvent, iSetup, jsystype);
  // Sort jets
   std::vector<pat::Jet> correctedJets = helper.GetSortedByPt(correctedJets_unsorted);
  //Get jet Collection which pass selection
  std::vector<pat::Jet> selectedJets = helper.GetSelectedJets(correctedJets, 30., 2.4, jetID::none, '-' );
  // Get jet Collection which pass loose selection
  std::vector<pat::Jet> selectedJetsLoose = helper.GetSelectedJets(correctedJets, 20., 2.4, jetID::none, '-' ); 


  /**** GET MET ****/
  edm::Handle< std::vector<pat::MET> > h_pfmet;
  iEvent.getByToken( EDMMETsToken,h_pfmet );
  std::vector<pat::MET> const &pfMETs = *h_pfmet;
  // type I met corrections?
  assert(pfMETs.size()>0);

  /**** GET TOPJETS ****/
  edm::Handle<boosted::HEPTopJetCollection> h_heptopjet;
  boosted::HEPTopJetCollection heptopjets;
  if(useFatJets){
    iEvent.getByToken( EDMHEPTopJetsToken,h_heptopjet);
    boosted::HEPTopJetCollection const &heptopjets_unsorted = *h_heptopjet;
    heptopjets = BoostedUtils::GetSortedByPt(heptopjets_unsorted);
  }
  
  /**** GET SUBFILTERJETS ****/
  edm::Handle<boosted::SubFilterJetCollection> h_subfilterjet;
  boosted::SubFilterJetCollection subfilterjets;
  if(useFatJets){
    iEvent.getByToken( EDMSubFilterJetsToken,h_subfilterjet );
    boosted::SubFilterJetCollection const &subfilterjets_unsorted = *h_subfilterjet;
    subfilterjets = BoostedUtils::GetSortedByPt(subfilterjets_unsorted);
  }
  
  /**** GET GENEVENTINFO ****/
  edm::Handle<GenEventInfoProduct> h_geneventinfo;
  iEvent.getByToken( EDMGenInfoToken, h_geneventinfo );
  GenEventInfoProduct const &genEventInfo=*h_geneventinfo;
  /**** GET GENPARTICLES ****/
  edm::Handle< std::vector<reco::GenParticle> > h_genParticles;
  iEvent.getByToken( EDMGenParticlesToken,h_genParticles );
  std::vector<reco::GenParticle> const &genParticles = *h_genParticles;
  
  /**** GET GENJETS ****/
  edm::Handle< std::vector<reco::GenJet> > h_genjets;
  iEvent.getByToken( EDMGenJetsToken,h_genjets );
  std::vector<reco::GenJet> const &genjets = *h_genjets;
  std::vector<reco::GenJet> selectedGenJets;
  for(size_t i=0; i<genjets.size();i++){
    if(genjets[i].pt()>25&&fabs(genjets[i].eta())<2.4)
      selectedGenJets.push_back(genjets[i]);
  }
  // custom genjets for tt+X categorization
  edm::Handle< std::vector<reco::GenJet> > h_customgenjets;
  iEvent.getByToken( EDMCustomGenJetsToken,h_customgenjets );

  // Fill Event Info Object
  EventInfo eventInfo(iEvent,h_beamspot,h_hcalnoisesummary,h_puinfosummary,firstVertexIsGood);
  // Fill Trigger Info
  map<string,bool> triggerMap;
  for(auto name=relevantTriggers.begin(); name!=relevantTriggers.end();name++){
    unsigned int TriggerID =  hlt_config.triggerIndex(*name);
    if( TriggerID >= triggerResults.size() ) { 
      std::cerr <<"triggerID > trigger results.size: "<<TriggerID<<" > "<<triggerResults.size()<<std::endl; 
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
  if(!isData){
    for(size_t i=0; i<genParticles.size();i++){
      if(genParticles[i].pdgId()==6) foundT=true;
      if(genParticles[i].pdgId()==-6) foundTbar=true;	
      if(genParticles[i].pdgId()==25) foundHiggs=true;
    }
  }

  int ttid=-1;
  if(useGenHadronMatch&&foundT&&foundTbar){
    /**** tt+X categorization ****/
    // Reading gen jets from the event
    // Reading B hadrons related information
    edm::Handle<std::vector<int> > genBHadFlavour;
    edm::Handle<std::vector<int> > genBHadJetIndex;
    edm::Handle<std::vector<int> > genBHadFromTopWeakDecay;
    edm::Handle<std::vector<reco::GenParticle> > genBHadPlusMothers;
    edm::Handle<std::vector<std::vector<int> > > genBHadPlusMothersIndices;
    edm::Handle<std::vector<int> > genBHadIndex;
    edm::Handle<std::vector<int> > genBHadLeptonHadronIndex;
    edm::Handle<std::vector<int> > genBHadLeptonViaTau;
    // Reading C hadrons related information
    edm::Handle<std::vector<int> > genCHadFlavour;
    edm::Handle<std::vector<int> > genCHadJetIndex;
    edm::Handle<std::vector<int> > genCHadFromTopWeakDecay;
    edm::Handle<std::vector<int> > genCHadBHadronId;
    iEvent.getByToken(genCHadBHadronIdToken, genCHadBHadronId);
    iEvent.getByToken(genBHadFlavourToken, genBHadFlavour);
    iEvent.getByToken(genBHadJetIndexToken, genBHadJetIndex);  
    iEvent.getByToken(genBHadFromTopWeakDecayToken, genBHadFromTopWeakDecay);  
    iEvent.getByToken(genBHadPlusMothersToken, genBHadPlusMothers);    
    iEvent.getByToken(genBHadPlusMothersIndicesToken, genBHadPlusMothersIndices);
    iEvent.getByToken(genBHadIndexToken, genBHadIndex);
    iEvent.getByToken(genBHadLeptonHadronIndexToken, genBHadLeptonHadronIndex);
    iEvent.getByToken(genBHadLeptonViaTauToken, genBHadLeptonViaTau);
    iEvent.getByToken(genCHadFlavourToken, genCHadFlavour);
    iEvent.getByToken(genCHadJetIndexToken, genCHadJetIndex);
    iEvent.getByToken(genCHadFromTopWeakDecayToken, genCHadFromTopWeakDecay);
    ttid = helper.ttHFCategorization(*h_customgenjets, *genBHadIndex, *genBHadJetIndex, *genBHadFlavour, *genBHadFromTopWeakDecay, *genBHadPlusMothers, *genBHadPlusMothersIndices, *genBHadLeptonHadronIndex, *genBHadLeptonViaTau, *genCHadFlavour, *genCHadJetIndex, *genCHadFromTopWeakDecay, *genCHadBHadronId, 20, 2.4);
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
  GenTopEvent genTopEvt;
  if(foundT&&foundTbar) genTopEvt.Fill(genParticles,ttid); // might want to store also genjets linked to ttHF event



  // DO REWEIGHTING
  map<string,float> weights = GetWeights(genEventInfo,eventInfo,selectedPVs,selectedJets,selectedElectrons,selectedMuons,genParticles);

  // DEFINE INPUT
  InputCollections input( eventInfo,			  
			  triggerInfo,			  
			  selectedPVs,
			  selectedMuons,
			  selectedMuonsLoose,
			  selectedElectrons,
                          selectedElectronsLoose,
                          selectedJets,
                          selectedJetsLoose,
                          pfMETs[0],
                          heptopjets,
                          subfilterjets,
                          genTopEvt,
                          selectedGenJets,
                          sampleType,
                          weights			  
			  );
        
  
  // DO SELECTION
  cutflow.EventSurvivedStep("all",input);
  bool selected=true;
  for(size_t i=0; i<selections.size() && selected; i++){
    if(!selections.at(i)->IsSelected(input,cutflow)){
      selected=false;
    }
    if(dumpSyncExe&&selected){
      input.DumpSyncExe(*(dumpFiles[i]));
    }
  }
  
  if(!selected) return;
  // WRITE TREE
    treewriter.Process(input);
}




map<string,float> BoostedAnalyzer::GetWeights(const GenEventInfoProduct&  genEventInfo,const EventInfo& eventInfo, const reco::VertexCollection& selectedPVs, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon>& selectedMuons, const std::vector<reco::GenParticle>& genParticles){
  map<string,float> weights;
  
  if(isData){
    weights["Weight"] = 1.0;
    weights["Weight_XS"] = 1.0;
    weights["Weight_CSV"] = 1.0;
    weights["Weight_PU"] = 1.0;
    weights["Weight_TopPt"] = 1.0;
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
  if(jsystype==sysType::JESup)csvweight= csvReweighter.get_csv_wgt(selectedJets,7, csvWgtHF, csvWgtLF, csvWgtCF);
  else if(jsystype==sysType::JESdown)csvweight= csvReweighter.get_csv_wgt(selectedJets,8, csvWgtHF, csvWgtLF, csvWgtCF);
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

  bool doSystematics=true;  
  if(doSystematics && jsystype != sysType::JESup && jsystype != sysType::JESup){
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
  cutflow.Print();
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
