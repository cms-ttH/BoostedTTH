/* -*- C++ -*- */
//
// Package:    BoostedTTH/RegressedJetProducer
// Class:      RegressedJetProducer
//
/**\class RegressedJetProducer RegressedJetProducer.cc BoostedTTH/RegressedJetProducer/plugins/RegressedJetProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/


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

#include "BoostedTTH/BoostedAnalyzer/interface/JetRegression.hpp"

//
// class declaration
//

class RegressedJetProducer : public edm::stream::EDProducer<> {
public:
  explicit RegressedJetProducer(const edm::ParameterSet&);
  ~RegressedJetProducer();

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
    std::vector <edm::InputTag> jetInputTags;
    std::vector <edm::EDGetTokenT< std::vector<pat::Jet> > > inputJetsToken;
    edm::EDGetTokenT < std::vector<pat::Muon> > muonsToken;
    edm::EDGetTokenT < edm::View<pat::Electron> > electronsToken;
    edm::EDGetTokenT < reco::VertexCollection > primaryVerticesToken;
    edm::EDGetTokenT< std::vector<reco::GenJet> > genJetswNuToken;
    std::vector < double > electronCuts;
    std::vector < double > muonCuts;
    double ljDr;

    std::string outputprefix;
    std::vector< std::string > collectionpostfix;

    bool isData;
    bool doGenJetMatching;
    std::vector< std::string > outputcollections;


    std::string outputname;

    /** register Regression as member **/
    JetRegression bjetRegression;
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
RegressedJetProducer::RegressedJetProducer(const edm::ParameterSet& iConfig) {

    jetInputTags             = iConfig.getParameter< std::vector < edm::InputTag > >("inputjets");
    for (auto& tag: jetInputTags){
        inputJetsToken.push_back(consumes< pat::JetCollection >(tag));
    }
    //jetsToken            = consumes< pat::JetCollection >(iConfig.getParameter<edm::InputTag>("jets"));
    electronsToken        = consumes< edm::View<pat::Electron> >(iConfig.getParameter<edm::InputTag>("electrons"));
    muonsToken            = consumes< std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("muons"));
    primaryVerticesToken  = consumes< reco::VertexCollection > (iConfig.getParameter<edm::InputTag>("pVs"));
    genJetswNuToken       = consumes< std::vector< reco::GenJet > >(iConfig.getParameter<edm::InputTag>("genjets"));

    electronCuts          = iConfig.getParameter< std::vector<double> >("electroncuts");
    muonCuts              = iConfig.getParameter< std::vector<double> >("muoncuts");
    ljDr                  = iConfig.getParameter< double >("softleptonJetDr");

    outputprefix          = iConfig.getParameter< std::string >("outputprefix");
    collectionpostfix     = iConfig.getParameter< std::vector < std::string > >("collectionpostfix");

    isData                = iConfig.getParameter<bool>("isData");
    doGenJetMatching      = iConfig.getParameter<bool>("doGenJetMatchingforRegression");

    assert(jetInputTags.size() == collectionpostfix.size());

    //Init outputcollections
    for(auto postfix: collectionpostfix){
        outputcollections.push_back(outputprefix+postfix);
        produces<pat::JetCollection>(outputprefix+postfix);
    }

    // Initialize b-Jet Regression
    bjetRegression.init(iConfig.getParameter< std::string >("weightfile"));
    bjetRegression.SetLeptonCuts(electronCuts, muonCuts, ljDr);

}



RegressedJetProducer::~RegressedJetProducer(){

   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
RegressedJetProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {


    for(size_t icollection = 0; icollection < outputcollections.size(); icollection++){
        //Get Inputjets
        edm::Handle< pat::JetCollection > h_inputJets;
        iEvent.getByToken( inputJetsToken[icollection],h_inputJets );

        edm::Handle< std::vector< reco::GenJet > > h_genjetswNu;
        std::vector< reco::GenJet > genJetswNu;
        if(!isData){
          iEvent.getByToken( genJetswNuToken, h_genjetswNu );
          std::vector< reco::GenJet > const &genjetswNu = *h_genjetswNu;
          for( size_t i = 0 ; i < genjetswNu.size() ; i++ ){
            if( genjetswNu[i].pt() > 15 && fabs( genjetswNu[i].eta()) < 2.4 ){
      	        genJetswNu.push_back(genjetswNu[i]);
            }
          }
        }


        std::vector < pat::Jet > inputjets = *h_inputJets;
        std::vector < pat::Jet > outputjets;

        bjetRegression.matchGenJetstoJets(inputjets,genJetswNu);
        bjetRegression.evaluateRegression(iEvent, electronsToken, muonsToken, primaryVerticesToken, inputjets,"",false);

        outputjets = bjetRegression.GetRegressedJets(inputjets);


        std::auto_ptr<pat::JetCollection>regJets(new pat::JetCollection(outputjets));
        iEvent.put(regJets, outputcollections[icollection]);
    }
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
RegressedJetProducer::beginStream(edm::StreamID) {

}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
RegressedJetProducer::endStream() {

}

// ------------ method called when starting to processes a run  ------------
/*
void
RegressedJetProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void
RegressedJetProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void
RegressedJetProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
RegressedJetProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RegressedJetProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(RegressedJetProducer);
