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
#include "BoostedTTH/BoostedAnalyzer/interface/SynchSelection.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/WeightProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MVAVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedJetVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/ttHVarProcessor.hpp"

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
      
      boosted::Event FillEvent(const edm::Event& iEvent, const edm::Handle<GenEventInfoProduct>& genEvtInfo, const edm::Handle<reco::BeamSpot>& beamSpot, const edm::Handle<HcalNoiseSummary>& hcalNoiseSummary, const edm::Handle< std::vector<PileupSummaryInfo> >& puSummaryInfo);
      map<string,float> GetWeights(const boosted::Event& event, const reco::VertexCollection& selectedPVs, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon>& selectedMuons, const std::vector<reco::GenParticle>& genParticles);
      
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


      /** disable some object selections for synch exe? */
      bool disableObjectSelections;

       /** use fat jets? this is only possible if the miniAOD contains them */
      bool useFatJets;
      
      /** calculate and store systematic weights? */
      bool doSystematics;
      
      /** jet systematic that is applied (the outher systematics are done at a different place with reweighting)*/
      sysType::sysType jsystype;
      
      
      /** pu summary data access token **/
      edm::EDGetTokenT< std::vector<PileupSummaryInfo> > EDMPUInfoToken;
      
      /** hcal noise data access token **/
      edm::EDGetTokenT< HcalNoiseSummary > EDMHcalNoiseToken;
      
      /** selected trigger data access token **/
      edm::EDGetTokenT< pat::TriggerObjectStandAloneCollection > EDMSelectedTriggerToken;
      
      /** trigger results data access token **/
      edm::EDGetTokenT< edm::TriggerResults > EDMTriggerResultToken;
      HLTConfigProvider hlt_config_;

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
  
  luminosity = iConfig.getParameter<double>("luminostiy");
  sampleID = iConfig.getParameter<int>("sampleID");
  xs = iConfig.getParameter<double>("xs");
  totalMCevents = iConfig.getParameter<int>("nMCEvents");
  isData = iConfig.getParameter<bool>("isData");
  
  useFatJets = iConfig.getParameter<bool>("useFatJets");
  disableObjectSelections = iConfig.getParameter<bool>("disableObjectSelections");

  string outfileName = iConfig.getParameter<std::string>("outfileName");
  
  std::cout << "Outfile Name: " << outfileName << std::endl;
  
  // REGISTER DATA ACCESS
  EDMPUInfoToken          = consumes< std::vector<PileupSummaryInfo> >(edm::InputTag("addPileupInfo","","HLT"));
  EDMHcalNoiseToken       = consumes< HcalNoiseSummary >(edm::InputTag("hcalnoise","","RECO"));
  EDMSelectedTriggerToken = consumes< pat::TriggerObjectStandAloneCollection > (edm::InputTag("selectedPatTrigger","","PAT"));
  EDMTriggerResultToken   = consumes< edm::TriggerResults > (edm::InputTag("TriggerResults","","HLT"));
  EDMBeamSpotToken        = consumes< reco::BeamSpot > (edm::InputTag("offlineBeamSpot","","RECO"));
  EDMVertexToken          = consumes< reco::VertexCollection > (edm::InputTag("offlineSlimmedPrimaryVertices","","PAT"));
  EDMMuonsToken           = consumes< std::vector<pat::Muon> >(edm::InputTag("slimmedMuons","","PAT"));
  EDMElectronsToken       = consumes< std::vector<pat::Electron> >(edm::InputTag("slimmedElectrons","","PAT"));
  EDMJetsToken            = consumes< std::vector<pat::Jet> >(edm::InputTag("slimmedJets","","PAT"));
  EDMMETsToken            = consumes< std::vector<pat::MET> >(edm::InputTag("slimmedMETs","","PAT"));
  EDMHEPTopJetsToken      = consumes< boosted::HEPTopJetCollection >(edm::InputTag("HEPTopJetsPFMatcher","heptopjets","p"));
  EDMSubFilterJetsToken   = consumes< boosted::SubFilterJetCollection >(edm::InputTag("CA12JetsCA3FilterjetsPFMatcher","subfilterjets","p"));
  EDMGenInfoToken         = consumes< GenEventInfoProduct >(edm::InputTag("generator","","SIM"));
  EDMGenParticlesToken    = consumes< std::vector<reco::GenParticle> >(edm::InputTag("prunedGenParticles","","PAT"));
  EDMGenJetsToken         = consumes< std::vector<reco::GenJet> >(edm::InputTag("slimmedGenJets","","PAT"));
  
  // INITIALIZE MINIAOD HELPER
  helper.SetUp(era, sampleID, iAnalysisType, isData);
  
  // INITIALIZE SELECTION & CUTFLOW
  cutflow.Init((outfileName+"_Cutflow.txt").c_str());
  cutflow.AddStep("all");
  
  std::vector<std::string> selectionNames = iConfig.getParameter< std::vector<std::string> >("selectionNames");
  for(vector<string>::const_iterator itSel = selectionNames.begin();itSel != selectionNames.end();itSel++) {
    
    if(*itSel == "LeptonSelection") selections.push_back(new LeptonSelection());
    else if(*itSel == "JetTagSelection") selections.push_back(new JetTagSelection());
    else if(*itSel == "SynchSelection") selections.push_back(new SynchSelection());
    else cout << "No matching selection found for: " << *itSel << endl;
    
    selections.back()->Init(iConfig,cutflow);
  }
  
  // INITIALIZE TREEWRITER
  treewriter.Init(outfileName);
  std::vector<std::string> processorNames = iConfig.getParameter< std::vector<std::string> >("processorNames");
  for(vector<string>::const_iterator itPro = processorNames.begin();itPro != processorNames.end();++itPro) {
    
    if(*itPro == "WeightProcessor") treewriter.AddTreeProcessor(new WeightProcessor());
    else if(*itPro == "MCMatchVarProcessor") treewriter.AddTreeProcessor(new MCMatchVarProcessor());
    else if(*itPro == "MVAVarProcessor") treewriter.AddTreeProcessor(new MVAVarProcessor());
    else if(*itPro == "BoostedJetVarProcessor") treewriter.AddTreeProcessor(new BoostedJetVarProcessor());
    else if(*itPro == "BoostedTopHiggsVarProcessor") treewriter.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTopHiggs,"TopLikelihood","HiggsCSV","BoostedTopHiggs_"));
    else if(*itPro == "BoostedTopVarProcessor") treewriter.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedTop,"TopLikelihood","HiggsCSV","BoostedTop_"));
    else if(*itPro == "BoostedHiggsVarProcessor") treewriter.AddTreeProcessor(new ttHVarProcessor(BoostedRecoType::BoostedHiggs,"TopLikelihood","HiggsCSV","BoostedHiggs_"));
    // the BDT processor rely on the variables filled py the other producers and should be added at the end
    else if(*itPro == "BDTVarProcessor") treewriter.AddTreeProcessor(new BDTVarProcessor());
    
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
  
  /**** GET PILEUPSUMMARYINFO ****/
  edm::Handle< std::vector<PileupSummaryInfo> >  h_puinfosummary;
  iEvent.getByToken( EDMPUInfoToken, h_puinfosummary);
  
  /**** GET HCALNOISESUMMARY ****/
  edm::Handle<HcalNoiseSummary> h_hcalnoisesummary;
  iEvent.getByToken( EDMHcalNoiseToken,h_hcalnoisesummary );
  
  /**** GET TRIGGER ****/
  edm::Handle<pat::TriggerObjectStandAloneCollection> h_selectedtrigger;
  iEvent.getByToken( EDMSelectedTriggerToken,h_selectedtrigger );
  pat::TriggerObjectStandAloneCollection const &selectedTrigger = *h_selectedtrigger;
  
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
  
  //  const JetCorrector* corrector = JetCorrector::getJetCorrector( "ak4PFchsL1L2L3", iSetup );   
  //  helper.SetJetCorrector(corrector);
  
  // Get raw jets
  std::vector<pat::Jet> rawJets = helper.GetUncorrectedJets(pfjets);
  // Clean muons from jets
  std::vector<pat::Jet> jetsNoMu = helper.RemoveOverlaps(selectedMuonsLoose, rawJets);
  // Clean electrons from jets
  std::vector<pat::Jet> jetsNoEle = helper.RemoveOverlaps(selectedElectronsLoose, jetsNoMu);
  // Apply jet corrections
  //  std::vector<pat::Jet> correctedJets = helper.GetCorrectedJets(jetsNoEle, iEvent, iSetup);
  // Get jet Collection which pass selection
  std::vector<pat::Jet> selectedJets = helper.GetSelectedJets(jetsNoEle, 30., 2.4, jetID::jetLoose, '-' );
  // Get jet Collection which pass loose selection
  std::vector<pat::Jet> selectedJetsLoose = helper.GetSelectedJets(jetsNoEle, 20., 2.5, jetID::jetLoose, '-' );

  /**** GET MET ****/
  edm::Handle< std::vector<pat::MET> > h_pfmet;
  iEvent.getByToken( EDMMETsToken,h_pfmet );
  std::vector<pat::MET> const &pfMETs = *h_pfmet;

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
    if(genjets[i].pt()>30&&fabs(genjets[i].eta())<2.5)
      selectedGenJets.push_back(genjets[i]);
  }
  
  // Fill Boosted Event Object
  boosted::Event event = FillEvent(iEvent,h_geneventinfo,h_beamspot,h_hcalnoisesummary,h_puinfosummary);
  
  // FIGURE OUT SAMPLE
  SampleType sampleType;
  if(isData)
    sampleType = SampleType::data;
  else if(BoostedUtils::MCContainsTTbar(genParticles) && BoostedUtils::MCContainsHiggs(genParticles)){
    sampleType = SampleType::tth;
  }
  else if(BoostedUtils::MCContainsTTbar(genParticles)){
    sampleType = SampleType::tt;
  }
  else{
    sampleType = SampleType::nonttbkg;
  }

  // DO REWEIGHTING
  map<string,float> weights = GetWeights(event,selectedPVs,selectedJets,selectedElectrons,selectedMuons,genParticles);

  // DEFINE INPUT
  InputCollections input( event,
			  selectedTrigger,
			  triggerResults,
                          hlt_config_,
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
                          weights,
			  iSetup,
                          iEvent
			  );
  InputCollections unselected_input( event,
			  selectedTrigger,
			  triggerResults,
                          hlt_config_,
			  vtxs,
			  muons,
			  muons,
			  electrons,
                          electrons,
                          pfjets,
                          pfjets,
                          pfMETs,
                          heptopjets,
                          subfilterjets,
                          genParticles,
                          selectedGenJets,
                          sampleType,
                          weights,
			  iSetup,
                          iEvent
			  );
        
  
  // DO SELECTION
  cutflow.EventSurvivedStep("all");
  bool selected=true;
  for(size_t i=0; i<selections.size() && selected; i++){
    if(disableObjectSelections){
      if(!selections.at(i)->IsSelected(unselected_input,cutflow))
	selected=false;
    }
    else {
      if(!selections.at(i)->IsSelected(input,cutflow))
	selected=false;
    }
  }
  
  if(!selected) return;    

  // WRITE TREE
  if(disableObjectSelections)
    treewriter.Process(unselected_input);  
  else
    treewriter.Process(input);  
}


boosted::Event BoostedAnalyzer::FillEvent(const edm::Event& iEvent, const edm::Handle<GenEventInfoProduct>& genEvtInfo, const edm::Handle<reco::BeamSpot>& beamSpot, const edm::Handle<HcalNoiseSummary>& hcalNoiseSummary, const edm::Handle< std::vector<PileupSummaryInfo> >& puSummaryInfo){
 
  boosted::Event event = boosted::Event();
  
  event.evt         = iEvent.id().event();
  event.run         = iEvent.id().run();
  event.sample      = sampleID;
  event.lumiBlock   = iEvent.luminosityBlock();
  
  
  if(genEvtInfo.isValid()){
    std::vector<double> genWeights = genEvtInfo->weights();
    for(size_t i=0;i<genWeights.size();i++){
      event.weight *= genWeights[i];
    }

    event.qScale = genEvtInfo->qScale();
    event.alphaQCD = genEvtInfo->alphaQCD();
    event.alphaQED = genEvtInfo->alphaQED();
    event.pthat = ( genEvtInfo->hasBinningValues() ? (genEvtInfo->binningValues())[0] : 0.0);
    event.scalePDF = genEvtInfo->pdf()->scalePDF;
    event.x1 = genEvtInfo->pdf()->x.first;
    event.x2 = genEvtInfo->pdf()->x.second;
    event.xPDF1 = genEvtInfo->pdf()->xPDF.first;
    event.xPDF2 = genEvtInfo->pdf()->xPDF.second;
    event.id1 = genEvtInfo->pdf()->id.first;
    event.id2 = genEvtInfo->pdf()->id.second;
  }
  
  if(beamSpot.isValid()){
    event.BSx = beamSpot->x0();
    event.BSy = beamSpot->y0();
    event.BSz = beamSpot->z0();
  }
  
 
  if( hcalNoiseSummary.isValid() ){
    event.hcalnoiseLoose = hcalNoiseSummary->passLooseNoiseFilter();
    event.hcalnoiseTight = hcalNoiseSummary->passTightNoiseFilter();
  }
  
  if( puSummaryInfo.isValid() ){
    for(std::vector<PileupSummaryInfo>::const_iterator PVI = puSummaryInfo->begin(); PVI != puSummaryInfo->end(); ++PVI) {

      int BX = PVI->getBunchCrossing();

      event.sumNVtx  += float(PVI->getPU_NumInteractions());
      event.sumTrueNVtx += float(PVI->getTrueNumInteractions());

      if( BX==0 ){
	      event.numGenPV = PVI->getPU_NumInteractions();
	      event.numTruePV = PVI->getTrueNumInteractions();
      }

      if(BX == -1) { 
	      event.nm1 = PVI->getPU_NumInteractions();
	      event.nm1_true = PVI->getTrueNumInteractions();
      }
      else if(BX == 0) { 
	      event.n0 = PVI->getPU_NumInteractions();
	      event.n0_true = PVI->getTrueNumInteractions();
      }
      else if(BX == 1) { 
	      event.np1 = PVI->getPU_NumInteractions();
	      event.np1_true = PVI->getTrueNumInteractions();
      }
    }
  }
  
  return event;
}


map<string,float> BoostedAnalyzer::GetWeights(const boosted::Event& event, const reco::VertexCollection& selectedPVs, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon>& selectedMuons, const std::vector<reco::GenParticle>& genParticles){
  map<string,float> weights;
  
  if(isData){
    weights["Weight"] = 1.0;
    weights["Weight_XS"] = 1.0;
    weights["Weight_CSV"] = 1.0;
    weights["Weight_PU"] = 1.0;
    weights["Weight_TopPt"] = 1.0;
    return weights;
  }

  // not sure why the BNevent weight is !=+-1 but we dont want it that way
  float weight = event.weight;  
  float xsweight = xs*luminosity/totalMCevents;
  float csvweight = 1.;
  float puweight = 1.;
  float topptweight = 1.;
  //float csvweight = beanHelper.GetCSVweight(selectedJets,jsystype);
  //float puweight = beanHelper.GetPUweight(event[0].numTruePV);
  //float topptweight = beanHelper.GetTopPtweight(mcparticlesStatus3);
  //float q2scaleweight = beanHelper.GetQ2ScaleUp(const BNevent&);
  
  //NA, JERup, JERdown, JESup, JESdown, hfSFup, hfSFdown, lfSFdown, lfSFup, TESup, TESdown, 
  //CSVLFup, CSVLFdown, CSVHFup, CSVHFdown, CSVHFStats1up, CSVHFStats1down, CSVLFStats1up, CSVLFStats1down, CSVHFStats2up, CSVHFStats2down, CSVLFStats2up, CSVLFStats2down, CSVCErr1up, CSVCErr1down, CSVCErr2up, CSVCErr2down
  
  weight *= xsweight*csvweight*puweight*topptweight;
  weights["Weight"] = weight;
  weights["Weight_XS"] = xsweight;
  weights["Weight_CSV"] = csvweight;
  weights["Weight_PU"] = puweight;
  weights["Weight_TopPt"] = topptweight;
  
  /*
  if(doSystematics && jsystype != sysType::JESup && jsystype != sysType::JESup){
    weights["Weight_TopPtup"] = beanHelper.GetTopPtweightUp(mcparticlesStatus3)/topptweight;
    weights["Weight_TopPtdown"] = beanHelper.GetTopPtweightDown(mcparticlesStatus3)/topptweight;

    weights["Weight_CSVLFup"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVLFup)/csvweight;
    weights["Weight_CSVLFdown"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVLFdown)/csvweight;
    weights["Weight_CSVHFup"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVHFup)/csvweight;
    weights["Weight_CSVHFdown"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVHFdown)/csvweight;
    weights["Weight_CSVHFStats1up"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVHFStats1up)/csvweight;
    weights["Weight_CSVHFStats1down"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVHFStats1down)/csvweight;
    weights["Weight_CSVLFStats1up"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVLFStats1up)/csvweight;
    weights["Weight_CSVLFStats1down"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVLFStats1down)/csvweight;
    weights["Weight_CSVHFStats2up"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVHFStats2up)/csvweight;
    weights["Weight_CSVHFStats2down"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVHFStats2down)/csvweight;
    weights["Weight_CSVLFStats2up"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVLFStats2up)/csvweight;
    weights["Weight_CSVLFStats2down"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVLFStats2down)/csvweight;
    weights["Weight_CSVCErr1up"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVCErr1up)/csvweight;
    weights["Weight_CSVCErr1down"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVCErr1down)/csvweight;
    weights["Weight_CSVCErr2up"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVCErr2up)/csvweight;
    weights["Weight_CSVCErr2down"] = beanHelper.GetCSVweight(selectedJets,sysType::CSVCErr2down)/csvweight;
    weights["Weight_Q2up"] = beanHelper.GetQ2ScaleUp(event[0]);
    weights["Weight_Q2down"] = beanHelper.GetQ2ScaleDown(event[0]);

  }
  */
  
  return weights;
}


// ------------ method called once each job just before starting event loop  ------------
void 
BoostedAnalyzer::beginJob()
{
  eventcount=0;

  watch.Start();
}


// ------------ method called once each job just after ending the event loop  ------------
void 
BoostedAnalyzer::endJob() 
{
  cutflow.Print();
}
// ------------ method called when starting to processes a run ------------
// needed for the hlt_config_
void
BoostedAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
std::string hltTag="HLT";
bool hltchanged = true;
if (!hlt_config_.init(iRun, iSetup, hltTag, hltchanged)) {
std::cout << "Warning, didn't find trigger process HLT,\t" << hltTag << std::endl;
return;
}
}
 

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
