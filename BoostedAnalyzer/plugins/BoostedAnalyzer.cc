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
// Original Author:  Shawn Williamson
//         Created:  Tue, 13 Jan 2015 10:48:49 GMT
//
//


// system include files
#include <memory>
#include <vector>
#include <map>

#include "TStopwatch.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeWriter.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/TopTagger.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/HiggsTagger.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/MVAVarProcessor.hpp"

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

      // ----------member data ---------------------------
      
      /** the beanhelper is used for selections and reweighting */
      MiniAODHelper helper;
      
      /** writes flat trees for MVA analysis */
      TreeWriter treewriter;
      
      /** stores cutflow*/
      Cutflow cutflow;
      
      /** toptagger used for selection */
      TopTagger toptagger;
      
      /** toptagger used for selection */
      HiggsTagger higgstagger;
      
      /** selections that are applied */
      vector<Selection*> selections;
      
      /** stops the time needed */
      TStopwatch watch;
      
      /** events to be analyzed */
      int maxEvents;
      
      /** total number of events in input file(s) */
      int totalMCevents;
     
      /** sample cross section*/
      float xs;
      
      /** jet systematic that is applied (the outher systematics are done at a different place with reweighting)*/
      sysType::sysType jsystype;
      
      /** calculate and store systematic weights? */
      bool doSystematics;
      
      /** is analyzed sample data? */
      bool isData;
      int eventcount;
      
      /** selected trigger data access token **/
      edm::EDGetTokenT< pat::TriggerObjectStandAloneCollection > EDMSelectedTriggerToken;
      
      /** trigger results data access token **/
      edm::EDGetTokenT< edm::TriggerResults > EDMTriggerResultToken;
      
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
      
      /** gen particles data access token **/
      edm::EDGetTokenT< std::vector<reco::GenParticle> > EDMGenParticlesToken;
      
      /** gen jets data access token **/
      edm::EDGetTokenT< std::vector<reco::GenJet> > EDMGenJetsToken;
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
  int sampleID = iConfig.getParameter<int>("sampleID");
  isData = iConfig.getParameter<bool>("isData");
  
  string analysisType = iConfig.getParameter<std::string>("analysisType");
  analysisType::analysisType iAnalysisType = analysisType::LJ;
  if(analysisType == "LJ") iAnalysisType = analysisType::LJ;
  else if(analysisType == "DIL") iAnalysisType = analysisType::DIL;
  else if(analysisType == "TauLJ") iAnalysisType = analysisType::TauLJ;
  else if(analysisType == "TauDIL") iAnalysisType = analysisType::TauDIL;
  else cerr << "No matching analysis type found for: " << analysisType << endl;
  
  string outfileName = iConfig.getParameter<std::string>("outfileName");
  
  // REGISTER DATA ACCESS
  EDMSelectedTriggerToken = consumes< pat::TriggerObjectStandAloneCollection > (edm::InputTag("selectedPatTrigger","","PAT"));
  EDMTriggerResultToken   = consumes< edm::TriggerResults > (edm::InputTag("TriggerResults","","PAT"));
  EDMVertexToken          = consumes< reco::VertexCollection > (edm::InputTag("offlineSlimmedPrimaryVertices","","PAT"));
  EDMMuonsToken           = consumes< std::vector<pat::Muon> >(edm::InputTag("slimmedMuons","","PAT"));
  EDMElectronsToken       = consumes< std::vector<pat::Electron> >(edm::InputTag("slimmedElectrons","","PAT"));
  EDMJetsToken            = consumes< std::vector<pat::Jet> >(edm::InputTag("slimmedJets","","PAT"));
  EDMMETsToken            = consumes< std::vector<pat::MET> >(edm::InputTag("slimmedMETs","","PAT"));
  EDMHEPTopJetsToken      = consumes< boosted::HEPTopJetCollection >(edm::InputTag("HEPTopJetsPFMatcher","heptopjets","p"));
  EDMSubFilterJetsToken   = consumes< boosted::SubFilterJetCollection >(edm::InputTag("CA12JetsCA3FilterjetsPFMatcher","subfilterjets","p"));
  EDMGenParticlesToken    = consumes< std::vector<reco::GenParticle> >(edm::InputTag("prunedGenParticles","","PAT"));
  EDMGenJetsToken         = consumes< std::vector<reco::GenJet> >(edm::InputTag("slimmedGenJets","","PAT"));
  
  // INITIALIZE MINIAOD HELPER
  helper.SetUp(era, sampleID, iAnalysisType, isData);
  
  // INITIALIZE SELECTION & CUTFLOW
  cutflow.Init((outfileName+"_cutflow.txt").c_str());
  cutflow.AddStep("all");
  
  std::vector<std::string> selectionNames = iConfig.getParameter< std::vector<std::string> >("selectionNames");
  for(vector<string>::const_iterator itSel = selectionNames.begin();itSel != selectionNames.end();itSel++) {
    
    if(*itSel == "LeptonSelection") selections.push_back(new LeptonSelection());
    else if(*itSel == "JetTagSelection") selections.push_back(new JetTagSelection());
    else cout << "No matching selection found for: " << *itSel << endl;
    
    selections.back()->Init(iConfig,cutflow);
  }
  
  // INITIALIZE TREEWRITER
  treewriter.Init(outfileName);
  std::vector<std::string> processorNames = iConfig.getParameter< std::vector<std::string> >("processorNames");
  for(vector<string>::const_iterator itPro = processorNames.begin();itPro != processorNames.end();++itPro) {
    
    if(*itPro == "MVAVarProcessor") treewriter.AddTreeProcessor(new MVAVarProcessor());
    else cout << "No matching processor found for: " << *itPro << endl;    
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
void
BoostedAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  if(eventcount<10||eventcount%1000==0){
    cout << "Analyzing event " << eventcount << endl;
    watch.Print();
    watch.Continue();
  }
  
  eventcount++;
    
  /**** GET EVENT ****/

  /**** GET TRIGGER ****/
  edm::Handle<pat::TriggerObjectStandAloneCollection> h_selectedtrigger;
  iEvent.getByToken( EDMSelectedTriggerToken,h_selectedtrigger );
  pat::TriggerObjectStandAloneCollection const &selectedTrigger = *h_selectedtrigger;
  
  edm::Handle<edm::TriggerResults> h_triggerresults;
  iEvent.getByToken( EDMTriggerResultToken,h_triggerresults );
  edm::TriggerResults const &triggerResults = *h_triggerresults;
  
  /**** GET PRIMARY VERTICES ****/
  edm::Handle< reco::VertexCollection > h_vtxs;
  iEvent.getByToken( EDMVertexToken,h_vtxs );
  reco::VertexCollection const &vtxs = *h_vtxs;
  
  // Primary Vertex Selection
  reco::VertexCollection selectedPVs;
  if( h_vtxs.isValid() ){
    for( reco::VertexCollection::const_iterator itvtx = vtxs.begin(); itvtx!=vtxs.end(); ++itvtx ){

      bool isGood = ( !(itvtx->isFake()) &&
		                  (itvtx->ndof() >= 4.0) &&
		                  (abs(itvtx->z()) <= 24.0) &&
		                  (abs(itvtx->position().Rho()) <= 2.0) 
		                );

      if( !isGood ) continue;
      
      selectedPVs.push_back(*itvtx);
    }
  }

  if( selectedPVs.size()>0 ) helper.SetVertex( selectedPVs.at(0) );
  if( selectedPVs.size() == 0 ) return;
  
  /**** GET LEPTONS ****/
  // MUONS
  edm::Handle< std::vector<pat::Muon> > h_muons;
  iEvent.getByToken( EDMMuonsToken,h_muons );
  std::vector<pat::Muon> const &muons = *h_muons; 
  std::vector<pat::Muon> selectedMuons = helper.GetSelectedMuons( muons, 20., muonID::muonTight );
  std::vector<pat::Muon> selectedMuonsLoose = helper.GetSelectedMuons( muons, 10., muonID::muonLoose );

  // ELECTRONS
  edm::Handle< std::vector<pat::Electron> > h_electrons;
  iEvent.getByToken( EDMElectronsToken,h_electrons );
  std::vector<pat::Electron> const &electrons = *h_electrons;
  std::vector<pat::Electron> selectedElectrons = helper.GetSelectedElectrons( electrons, 20., electronID::electronTight );
  std::vector<pat::Electron> selectedElectronsLoose = helper.GetSelectedElectrons( electrons, 10., electronID::electronLoose );

  // Leptons
  /*
  std::vector<pat::Pat>BNleptonCollection selectedLeptons_loose;
  for(size_t i=0; i<selectedElectronsLoose.size();i++){
    selectedLeptons_loose.push_back(&(selectedElectronsLoose[i]));
  }
  for(size_t i=0; i<selectedMuonsLoose.size();i++){
    selectedLeptons_loose.push_back(&(selectedMuonsLoose[i]));
  }    
  */

  /**** GET JETS ****/
  edm::Handle< std::vector<pat::Jet> > h_pfjets;
  iEvent.getByToken( EDMJetsToken,h_pfjets );
  std::vector<pat::Jet> const &pfjets = *h_pfjets;
  
  const JetCorrector* corrector = JetCorrector::getJetCorrector( "ak4PFchsL1L2L3", iSetup );   
  helper.SetJetCorrector(corrector);
  
  // Get raw jets
  std::vector<pat::Jet> rawJets = helper.GetUncorrectedJets(pfjets);
  // Clean muons from jets
  std::vector<pat::Jet> jetsNoMu = helper.RemoveOverlaps(selectedMuonsLoose, rawJets);
  // Clean electrons from jets
  std::vector<pat::Jet> jetsNoEle = helper.RemoveOverlaps(selectedElectronsLoose, jetsNoMu);
  // Apply jet corrections
  std::vector<pat::Jet> correctedJets = helper.GetCorrectedJets(jetsNoEle, iEvent, iSetup);
  // Get jet Collection which pass selection
  std::vector<pat::Jet> selectedJets = helper.GetSelectedJets(correctedJets, 30., 2.4, jetID::jetLoose, '-' );
  // Get jet Collection which pass loose selection
  std::vector<pat::Jet> selectedJetsLoose = helper.GetSelectedJets(correctedJets, 20., 2.5, jetID::jetLoose, '-' );

  /**** GET MET ****/
  edm::Handle< std::vector<pat::MET> > h_pfmet;
  iEvent.getByToken( EDMMETsToken,h_pfmet );
  std::vector<pat::MET> const &pfMETs = *h_pfmet;

  /**** GET TOPJETS ****/
  edm::Handle<boosted::HEPTopJetCollection> h_heptopjet;
  iEvent.getByToken( EDMHEPTopJetsToken,h_heptopjet);
  boosted::HEPTopJetCollection const &heptopjets_unsorted = *h_heptopjet;
  boosted::HEPTopJetCollection heptopjets = BoostedUtils::GetSortedByPt(heptopjets_unsorted);
  
  /**** GET SUBFILTERJETS ****/
  edm::Handle<boosted::SubFilterJetCollection> h_subfilterjet;                   
  iEvent.getByToken( EDMSubFilterJetsToken,h_subfilterjet );
  boosted::SubFilterJetCollection const &subfilterjets_unsorted = *h_subfilterjet;
  boosted::SubFilterJetCollection subfilterjets = BoostedUtils::GetSortedByPt(subfilterjets_unsorted);
  
  /**** GET GENPARTICLES****/
  edm::Handle< std::vector<reco::GenParticle> > h_genParticles;
  iEvent.getByToken( EDMGenParticlesToken,h_genParticles );
  std::vector<reco::GenParticle> const &genParticles = *h_genParticles;
  
  /**** GET GENJETS ****/
  edm::Handle< std::vector<reco::GenJet> > h_genjets;
  iEvent.getByToken( EDMGenJetsToken,h_genjets );
  std::vector<reco::GenJet> const &genjets = *h_genjets;
  std::vector<reco::GenJet> selectedGenJets;
  for(size_t i=0; i<genjets.size();i++){
    if(genjets[i].pt()>30&&fabs(genjets[i].eta())<2.5)
      selectedGenJets.push_back(genjets[i]);
  }
  
  // FIGURE OUT SAMPLE
  SampleType sampleType;
  if(isData)
    sampleType=SampleType::data;
  else if(BoostedUtils::MCContainsTTbar(genParticles) && BoostedUtils::MCContainsHiggs(genParticles)){
    sampleType=SampleType::tth;
  }
  else if(BoostedUtils::MCContainsTTbar(genParticles)){
    sampleType=SampleType::tt;
  }
  else{
    sampleType=SampleType::nonttbkg;
  }

  // DO REWEIGHTING
  map<string,float> weights;
  //    map<string,float> weights=GetWeights(isData,doSystematics,jsystype,events,selectedPVs,selectedJets,selectedElectrons,selectedMuons,genParticles);

  // DEFINE INPUT
  InputCollections input( selectedTrigger,
                          triggerResults,
                          selectedPVs,
                          selectedMuons,
                          selectedMuonsLoose,
                          selectedElectrons,
                          selectedElectronsLoose,
                          selectedJets,
                          selectedJetsLoose,
                          pfMETs,
                          heptopjets,
                          subfilterjets,
                          genParticles,
                          selectedGenJets,
                          sampleType,
                          weights
                        );
  
  /*
  cout << "Number of primary Vertices: " << selectedPVs.size() << endl;
  cout << "Number of selected Muons: " << selectedMuons.size() << endl;
  cout << "Number of selected Muons (Loose): " << selectedMuonsLoose.size() << endl;
  cout << "Number of selected Electrons: " << selectedElectrons.size() << endl;
  cout << "Number of selected Electrons (Loose): " << selectedElectronsLoose.size() << endl;
  cout << "Number of selected Jets: " << selectedJets.size() << endl;
  cout << "Number of selected Jets (Loose): " << selectedJetsLoose.size() << endl;
  cout << "Number of selected HEP Top Jets: " << heptopjets.size() << endl;
  cout << "Number of selected Subjet Filterjets: " << subfilterjets.size() << endl;
  cout << "Number of Gen Particles: " << genParticles.size() << endl;
  cout << "Number of selected Genjets: " << selectedGenJets.size() << endl;
  */
  
  // DO SELECTION
  cutflow.EventSurvivedStep("all");
  bool selected=true;
  for(size_t i=0; i<selections.size() && selected; i++){
    if(!selections.at(i)->IsSelected(input,cutflow))
	    selected=false;
  }
  
  if(!selected) return;    

  // WRITE TREE
  treewriter.Process(input);  
}


// ------------ method called once each job just before starting event loop  ------------
void 
BoostedAnalyzer::beginJob()
{
  eventcount=0;
  // INITIALIZE Selections

  /*  cutflow.AddStep("all");
  for(size_t i=0; i<selections.size(); i++){
    selections.at(i)->Init(cutflow);
    }*/

  watch.Start();
}

// ------------ method called once each job just after ending the event loop  ------------
void 
BoostedAnalyzer::endJob() 
{
  cutflow.Print();
}

// ------------ method called when starting to processes a run  ------------
/*
void 
BoostedAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
BoostedAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
BoostedAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
BoostedAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BoostedAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BoostedAnalyzer);
