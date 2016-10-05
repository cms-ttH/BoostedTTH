// -*- C++ -*-
//
// Package:    BoostedTTH/SelectedBoostedJetProducer
// Class:      SelectedBoostedJetProducer
//

//
// Original Author:  Sebastian Wieland
//         Created:  Thu, 22 Sep 2016
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

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/src/BoostedUtils.cpp"
//
// class declaration
//

class SelectedBoostedJetProducer : public edm::stream::EDProducer<> {
public:
    explicit SelectedBoostedJetProducer(const edm::ParameterSet&); //constructor
    ~SelectedBoostedJetProducer();  //destructor

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
    virtual void beginStream(edm::StreamID) override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endStream() override;
    std::string systName(std::string name, sysType::sysType);

    //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

    // ----------member data ---------------------------
    /** input jets data access token **/
    // edm::EDGetTokenT< pat::JetCollection > jetsToken;
    /** genjets data access token (for getcorrected jets) **/
    edm::EDGetTokenT< reco::GenJetCollection> genjetsToken;
    /** muons data access token (for jet cleaning)**/
    // edm::EDGetTokenT< pat::MuonCollection >     muonsToken;
    /** electrons data access token (for jet cleaning)**/
    // edm::EDGetTokenT< pat::ElectronCollection >electronsToken;
    /** boosted jets data access token **/
    edm::EDGetTokenT< boosted::BoostedJetCollection > boostedJetsToken;
    /** rho data access token (for jet cleaning)**/
    edm::EDGetTokenT< double >rhoToken;

    /** MiniAODHelper, used for jet correction and selection **/
    MiniAODHelper helper;
    /** min pt of jet collections **/
    // std::vector<double> ptMins;
    /** max eta of jet collections **/
    // std::vector<double> etaMaxs;
    /** min dir to lepton for jets **/
    // double leptonJetDr;
    /** names of output jet collections **/
    std::vector<std::string> collectionNames;
    /** systematics used **/
    // std::vector<sysType::sysType> systematics;
    /** systematics */
    std::vector<sysType::sysType> jetSystematics;
    /** apply jet energy correciton? **/
    bool applyCorrection;
    bool isData;
    /** use fat jets? this is only possible if the miniAOD contains them */
    bool useFatJets;
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
SelectedBoostedJetProducer::SelectedBoostedJetProducer(const edm::ParameterSet& iConfig)
{
    // jetsToken  = consumes< pat::JetCollection >(iConfig.getParameter<edm::InputTag>("jets"));
    // genjetsToken = consumes< reco::GenJetCollection >(iConfig.getParameter<edm::InputTag>("miniAODGenJets"));
    // electronsToken  = consumes< pat::ElectronCollection >(iConfig.getParameter<edm::InputTag>("electrons"));
    // muonsToken  = consumes< pat::MuonCollection >(iConfig.getParameter<edm::InputTag>("muons"));
    boostedJetsToken        = consumes< boosted::BoostedJetCollection >(iConfig.getParameter<edm::InputTag>("boostedjets"));
    rhoToken  = consumes<double> (iConfig.getParameter<edm::InputTag>("rho") );
    // ptMins = iConfig.getParameter< std::vector<double> >("ptMins");
    // etaMaxs = iConfig.getParameter< std::vector<double> >("etaMaxs");
    // leptonJetDr = iConfig.getParameter< double >("leptonJetDr");
    // applyCorrection = iConfig.getParameter<bool>("applyCorrection");
    collectionNames = iConfig.getParameter< std::vector<std::string> >("collectionNames");
    useFatJets = iConfig.getParameter<bool>("useFatJets");

    // assert(ptMins.size()==etaMaxs.size());
    // assert(ptMins.size()==collectionNames.size());

    isData = iConfig.getParameter<bool>("isData");
    analysisType::analysisType iAnalysisType = analysisType::LJ;
    const int sampleID = isData? -1 : 1;
    const std::string era = "2015_74x";
    const std::vector<std::string> s_systematics = iConfig.getParameter< std::vector<std::string> >("systematics");
    for(uint i=0; i<s_systematics.size(); i++){
	  if(s_systematics[i]=="") jetSystematics.push_back(sysType::NA);
 	  else if(s_systematics[i]=="jesup") jetSystematics.push_back(sysType::JESup);
	  else if(s_systematics[i]=="jesdown") jetSystematics.push_back(sysType::JESdown);
	  else if(s_systematics[i]=="jerup") jetSystematics.push_back(sysType::JERup);
	  else if(s_systematics[i]=="jerdown") jetSystematics.push_back(sysType::JERdown);
	  else{
	    std::cerr << "SelectedboostedJetProducer: systematic name " << s_systematics[i] << " not recognized" << std::endl;
	    throw std::exception();
	   }

    helper.SetUp(era, sampleID, iAnalysisType, isData);

    produces<pat::JetCollection>("rawJets");

    for(uint i=0; i<collectionNames.size();i++){
	for(uint j=0; j<s_systematics.size();j++){
	    produces<pat::JetCollection>(systName(collectionNames[i],jetSystematics[j]));
	}
    }
  }
}


SelectedBoostedJetProducer::~SelectedBoostedJetProducer()
{

   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
SelectedBoostedJetProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;




 // notwendig?!?!
  //  helper.SetJetCorrectorUncertainty(iSetup);
  //  helper.SetBoostedJetCorrectorUncertainty(iSetup);
  //
  //  edm::Handle<double> h_rho;
  //  iEvent.getByToken(rhoToken,h_rho);
  //  helper.SetRho(*h_rho);
  //
  //  edm::Handle< pat::JetCollection > h_inputJets;
  //  iEvent.getByToken( jetsToken,h_inputJets );
  //  edm::Handle< reco::GenJetCollection > h_genJets;
  //  if (!isData) {iEvent.getByToken( genjetsToken, h_genJets );}
  //
  //  edm::Handle< pat::ElectronCollection > h_inputElectrons;
  //  iEvent.getByToken( electronsToken,h_inputElectrons );
  //
  //  edm::Handle< pat::MuonCollection > h_inputMuons;
  //  iEvent.getByToken( muonsToken,h_inputMuons );


  /**** GET BOOSTEDJETS*****/
   edm::Handle<double> h_rho;
   iEvent.getByToken(rhoToken,h_rho);
   helper.SetRho(*h_rho);

   edm::Handle< reco::GenJetCollection > h_genJets;
   if (!isData) {iEvent.getByToken( genjetsToken, h_genJets );}
   // initialize jetcorrector
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
     boosted::BoostedJetCollection idBoostedJets = helper.GetSelectedBoostedJets(boostedjets, 0., 9999., 0., 9999., jetID::jetLoose);
     for(auto syst : jetSystematics){
         boosted::BoostedJetCollection correctedBoostedJets = helper.GetCorrectedBoostedJets(idBoostedJets, iEvent, iSetup, h_genJets, syst, true, true);
         selectedBoostedJets.push_back(helper.GetSelectedBoostedJets(correctedBoostedJets, 200., 2.0, 20., 2.4, jetID::none));
     }
   }
   else{
     for(uint i =0; i<jetSystematics.size();i++){
         selectedBoostedJets.push_back(boosted::BoostedJetCollection());
     }
   }



}

std::string SelectedBoostedJetProducer::systName(std::string name,sysType::sysType sysType){
    if(sysType==sysType::NA) return name;
    if(sysType==sysType::JESup) return name+"jesup";
    if(sysType==sysType::JESdown) return name+"jesdown";
    if(sysType==sysType::JERup) return name+"jerup";
    if(sysType==sysType::JERdown) return name+"jerdown";
    std::cerr << "SelectedBoostedJetProducer: systematic #"<< sysType<< " not implemented" << std::endl;
    throw std::exception();
    return name;
  }


// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
SelectedBoostedJetProducer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
SelectedBoostedJetProducer::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
SelectedBoostedJetProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void
SelectedBoostedJetProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void
SelectedBoostedJetProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
SelectedBoostedJetProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SelectedBoostedJetProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SelectedBoostedJetProducer);
