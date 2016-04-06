// -*- C++ -*-
//
// Package:    BoostedTTH/JetMETproducer
// Class:      JetMETproducer
// 
/**\class JetMETproducer JetMETproducer.cc BoostedTTH/JetMETproducer/plugins/JetMETproducer.cc

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
#include "DataFormats/PatCandidates/interface/MET.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
//
// class declaration
//

class JetMETproducer : public edm::stream::EDProducer<> {
public:
    explicit JetMETproducer(const edm::ParameterSet&);
    ~JetMETproducer();
    
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
    /** jets data access token **/
    edm::EDGetTokenT< std::vector<pat::Jet> > EDMJetsToken;
    /** mets data access token **/
    edm::EDGetTokenT< std::vector<pat::MET> > EDMMETsToken;
    
    /** MiniAODHelper, used for jet correction and selection **/
    MiniAODHelper helper;
    
    bool recorrectMET;
    
    double jetPtCut; 
    double jetEtaCut; 
    double looseJetPtCut; 
    double looseJetEtaCut; 
    double metCorrectionJetEtaCut; 
    double leptonJetDr;
    sysType::sysType syst;
    
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
JetMETproducer::JetMETproducer(const edm::ParameterSet& iConfig)
{
    jetPtCut   = iConfig.getParameter<double>("jetPtCut");
    looseJetPtCut   = iConfig.getParameter<double>("looseJetPtCut");
    jetEtaCut   = iConfig.getParameter<double>("jetEtaCut");
    looseJetEtaCut   = iConfig.getParameter<double>("looseJetEtaCut");
    metCorrectionJetEtaCut   = iConfig.getParameter<double>("metCorrectionJetEtaCut");
    metCorrectionJetEtaCut   = iConfig.getParameter<double>("leptonJetDr");

    jetsToken  = consumes< std::vector<pat::Jet> >(iConfig.getParameter<edm::InputTag>("jets"));
    metsToken  = consumes< std::vector<pat::MET> >(iConfig.getParameter<edm::InputTag>("mets"));
    jetsToken  = consumes< std::vector<pat::Electron> >(iConfig.getParameter<edm::InputTag>("electrons"));
    metsToken  = consumes< std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("muons"));

   //register your products
/* Examples
   produces<ExampleData2>();

   //if do put with a label
   produces<ExampleData2>("label");
 
   //if you want to put into the Run
   produces<ExampleData2,InRun>();
*/
   //now do what ever other initialization is needed
    produces<pat::JetCollection>("selectedJets");
    produces<pat::JetCollection>("selectedLooseJets");
    produces<pat::METCollection>("correctedMETs");
  
}


JetMETproducer::~JetMETproducer()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
JetMETproducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
/* This is an event example
   //Read 'ExampleData' from the Event
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);

   //Use the ExampleData to create an ExampleData2 which 
   // is put into the Event
   std::unique_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
   iEvent.put(std::move(pOut));
*/
   
/* this is an EventSetup example
   //Read SetupData from the SetupRecord in the EventSetup
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
*/
   //
   const bool isData = iConfig.getParameter<bool>("isData");
   analysisType::analysisType iAnalysisType = analysisType::LJ;
   const int sampleID = isData? -1 : 1;
   const std::string era = "2015_74x";
   helper.SetUp(era, sampleID, iAnalysisType, isData);
   helper.SetJetCorrectorUncertainty();
   helper.SetBoostedJetCorrectorUncertainty();

   edm::Handle<double> h_rho;
   iEvent.getByToken(EDMRhoToken,h_rho);
   helper.SetRho(*h_rho);

   edm::Handle< pat::JetCollection > h_inputJets;
   iEvent.getByToken( jetsToken,h_inputJets );
  
   edm::Handle< pat::METCollection > h_inputMETs;
   iEvent.getByToken( jetsToken,h_inputMETs );

   edm::Handle< pat::ElectronCollection > h_inputElectrons;
   iEvent.getByToken( jetsToken,h_inputElectrons );

   edm::Handle< pat::MuonCollection > h_inputMuons;
   iEvent.getByToken( jetsToken,h_inputMuons );

   // initialize jetcorrector
   const JetCorrector* corrector = JetCorrector::getJetCorrector( "ak4PFchsL1L2L3", iSetup );
   helper.SetJetCorrector(corrector);
   
   // selected jets with jet ID cuts
   std::vector<pat::Jet> idJets = helper.GetSelectedJets(pfjets, 0., 9999., jetID::jetLoose, '-' );
   // Get the jets for MET correction
   std::vector<pat::Jet> idJetsForMET = helper.GetSelectedJets(pfjets, 0., metCorrectionJetEtaCut, jetID::jetMETcorrection, '-' );
   std::vector<pat::Jet> rawJetsForMET = helper.GetUncorrectedJets(idJetsForMET);
   std::vector<pat::Jet> correctedJetsForMET = helper.GetCorrectedJets(rawJetsForMET, iEvent, iSetup, syst, true, false);
   //correct MET 
   std::vector<pat::MET> correctedMETs = recorrectMET ? helper.CorrectMET(idJetsForMET,correctedJetsForMET,pfMETs) : pfMETs;
   // Get raw jets
   std::vector<pat::Jet> rawJets = helper.GetUncorrectedJets(idJets);
   // Clean muons and electrons from jets
   std::vector<pat::Jet> cleanJets = helper.GetDeltaRCleanedJets(rawJets,*h_inputMuons,*h_inputElectrons,leptonJetDr);
   // Apply jet corrections
   std::vector<pat::Jet> correctedJets_unsorted = helper.GetCorrectedJets(cleanJets, iEvent, iSetup, syst);
   //Get jet Collection which pass selection
   std::vector<pat::Jet> selectedJets_unsorted = helper.GetSelectedJets(correctedJets_unsorted, jetPtCut, jetEtaCut, jetID::none, '-' );
   // Sort jets
   std::vector<pat::Jet> selectedJets = helper.GetSortedByPt(selectedJets_unsorted);
   // Get jet Collection which pass loose selection
   std::vector<pat::Jet> selectedJetsLoose_unsorted = helper.GetSelectedJets(correctedJets_unsorted, looseJetPtCut,looseJetEtaCut, jetID::none, '-' ); 
   // Sort jets
   std::vector<pat::Jet> selectedJetsLoose = helper.GetSortedByPt(selectedJetsLoose_unsorted);
   // Get jet Collection which pass the forward selection
   
   iEvent.put(&selectedJets,"selectedJets");
   iEvent.put(&selectedJetsLoose,"selectedLooseJets");
   iEvent.put(&correctedMETs,"correctedMETs");
   
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
JetMETproducer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
JetMETproducer::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
JetMETproducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
JetMETproducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
JetMETproducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
JetMETproducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JetMETproducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetMETproducer);
