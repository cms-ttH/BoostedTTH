// -*- C++ -*-
//
// Package:    BoostedTTH/SelectedJetProducer
// Class:      SelectedJetProducer
// 
/**\class SelectedJetProducer SelectedJetProducer.cc BoostedTTH/SelectedJetProducer/plugins/SelectedJetProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Hannes Mildner
//         Created:  Tue, 05 Apr 2016 09:53:41 GMT
//
//


// system include files
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
//
// class declaration
//

class SelectedJetProducer : public edm::stream::EDProducer<> {
public:
    explicit SelectedJetProducer(const edm::ParameterSet&);
    ~SelectedJetProducer();
    
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    
private:
    virtual void beginStream(edm::StreamID) override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endStream() override;
    
    //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    
    // ----------member data ---------------------------
    /** input jets data access token **/
    edm::EDGetTokenT< pat::JetCollection > jetsToken;
    /** muons data access token (for jet cleaning)**/
    edm::EDGetTokenT< pat::MuonCollection >     muonsToken;  
    /** electrons data access token (for jet cleaning)**/
    edm::EDGetTokenT< pat::ElectronCollection >electronsToken;
    /** rho data access token (for jet cleaning)**/
    edm::EDGetTokenT< double >rhoToken;
    
    /** MiniAODHelper, used for jet correction and selection **/
    MiniAODHelper helper;
    /** min pt of jet collections **/
    std::vector<double> ptMins;
    /** max eta of jet collections **/
    std::vector<double> etaMaxs;
    /** min dir to lepton for jets **/
    double leptonJetDr;
    /** names of output jet collections **/
    std::vector<std::string> collectionNames;
    /** systematic type **/
    sysType::sysType syst;
    /** apply jet energy correciton? **/
    bool applyCorrection;
    
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
SelectedJetProducer::SelectedJetProducer(const edm::ParameterSet& iConfig)
{
    jetsToken  = consumes< pat::JetCollection >(iConfig.getParameter<edm::InputTag>("jets"));
    electronsToken  = consumes< pat::ElectronCollection >(iConfig.getParameter<edm::InputTag>("electrons"));
    muonsToken  = consumes< pat::MuonCollection >(iConfig.getParameter<edm::InputTag>("muons"));
    ptMins = iConfig.getParameter< std::vector<double> >("ptMins");
    etaMaxs = iConfig.getParameter< std::vector<double> >("etaMaxs");    
    applyCorrection = iConfig.getParameter<bool>("applyCorrection");
    collectionNames = iConfig.getParameter< std::vector<std::string> >("collectionNames");

    assert(ptMins.size()==etaMaxs.size());
    assert(ptMins.size()==collectionNames.size());

    const bool isData = iConfig.getParameter<bool>("isData");
    analysisType::analysisType iAnalysisType = analysisType::LJ;
    const int sampleID = isData? -1 : 1;
    const std::string era = "2015_74x";
    helper.SetUp(era, sampleID, iAnalysisType, isData);
    helper.SetJetCorrectorUncertainty();
    helper.SetBoostedJetCorrectorUncertainty();

    for(uint i=0; i<collectionNames.size();i++){
	produces<pat::JetCollection>(collectionNames[i]);
    }  
}


SelectedJetProducer::~SelectedJetProducer()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
SelectedJetProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<double> h_rho;
   iEvent.getByToken(rhoToken,h_rho);
   helper.SetRho(*h_rho);

   edm::Handle< pat::JetCollection > h_inputJets;
   iEvent.getByToken( jetsToken,h_inputJets );
  
   edm::Handle< pat::ElectronCollection > h_inputElectrons;
   iEvent.getByToken( jetsToken,h_inputElectrons );

   edm::Handle< pat::MuonCollection > h_inputMuons;
   iEvent.getByToken( jetsToken,h_inputMuons );

   // initialize jetcorrector
   const JetCorrector* corrector = JetCorrector::getJetCorrector( "ak4PFchsL1L2L3", iSetup );
   helper.SetJetCorrector(corrector);
   
   // selected jets with jet ID cuts
   const std::vector<pat::Jet> idJets = helper.GetSelectedJets(*h_inputJets, 0., 9999., jetID::jetLoose, '-' );
   std::vector<pat::Jet> *unsortedJets=0;
   if(applyCorrection){
       // Get raw jets
       std::vector<pat::Jet> rawJets = helper.GetUncorrectedJets(idJets);
       // Clean muons and electrons from jets
       std::vector<pat::Jet> cleanJets = helper.GetDeltaRCleanedJets(rawJets,*h_inputMuons,*h_inputElectrons,leptonJetDr);
   // Apply jet corrections
       std::vector<pat::Jet> correctedJets_unsorted = helper.GetCorrectedJets(cleanJets, iEvent, iSetup, syst);
       unsortedJets=&correctedJets_unsorted;
   }
   else{
       std::vector<pat::Jet> cleanJets = helper.GetDeltaRCleanedJets(idJets,*h_inputMuons,*h_inputElectrons,leptonJetDr);
       unsortedJets=&cleanJets;
   }
   for(uint i=0; i<ptMins.size(); i++ ){
       //Get jet Collection which pass selections
       std::vector<pat::Jet> selectedJets_unsorted = helper.GetSelectedJets(*unsortedJets, ptMins[i], etaMaxs[i], jetID::none, '-' );
       // Get jet Collection which pass loose selection
       std::auto_ptr<pat::JetCollection> selectedJets(new pat::JetCollection(helper.GetSortedByPt(selectedJets_unsorted)));
       iEvent.put(selectedJets,collectionNames[i]);
   }
   
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
SelectedJetProducer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
SelectedJetProducer::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
SelectedJetProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
SelectedJetProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
SelectedJetProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
SelectedJetProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SelectedJetProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SelectedJetProducer);
