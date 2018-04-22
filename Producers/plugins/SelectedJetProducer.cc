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
#include "FWCore/Utilities/interface/Exception.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/Systematics.h"
#include "MiniAOD/MiniAODHelper/interface/PUJetID.h"
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
    std::string systName(std::string name, Systematics::Type);
    
    //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    
    // ----------member data ---------------------------
    /** input jets data access token **/
    edm::EDGetTokenT< pat::JetCollection > jetsToken;
    /** genjets data access token (for getcorrected jets) **/
    edm::EDGetTokenT< reco::GenJetCollection> genjetsToken;
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
    /** pileupjetid for collections **/
    std::vector<std::string> PUJetIDMins;
    std::string JetID;
    std::string JetType;
    /** systematics used **/
    std::vector<Systematics::Type> systematics;
    /** apply jet energy correciton? **/
    bool applyCorrection;
    bool doJER;
    bool isData;
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
SelectedJetProducer::SelectedJetProducer(const edm::ParameterSet& iConfig) : helper(iConfig.getParameter<std::string> ("JetType"))
{
    jetsToken  = consumes< pat::JetCollection >(iConfig.getParameter<edm::InputTag>("jets"));
    genjetsToken = consumes< reco::GenJetCollection >(iConfig.getParameter<edm::InputTag>("miniAODGenJets"));
    electronsToken  = consumes< pat::ElectronCollection >(iConfig.getParameter<edm::InputTag>("electrons"));
    muonsToken  = consumes< pat::MuonCollection >(iConfig.getParameter<edm::InputTag>("muons"));
    rhoToken  = consumes<double> (iConfig.getParameter<edm::InputTag>("rho") );
    ptMins = iConfig.getParameter< std::vector<double> >("ptMins");
    etaMaxs = iConfig.getParameter< std::vector<double> >("etaMaxs");    
    leptonJetDr = iConfig.getParameter< double >("leptonJetDr");
    applyCorrection = iConfig.getParameter<bool>("applyCorrection");
    doJER = iConfig.getParameter<bool>("doJER");
    collectionNames = iConfig.getParameter< std::vector<std::string> >("collectionNames");
    PUJetIDMins = iConfig.getParameter<std::vector<std::string>> ("PUJetIDMins");
    JetID = iConfig.getParameter<std::string> ("JetID");
    JetType = iConfig.getParameter<std::string> ("JetType");
    JetType.replace(JetType.begin(),JetType.begin()+2,"ak");// do this for getJetCorrector call with JetType as argument, because it needs ak4... or ak8 ... instead of AK4... or AK8...
    
    assert(ptMins.size()==etaMaxs.size());
    assert(ptMins.size()==collectionNames.size());

    isData = iConfig.getParameter<bool>("isData");
    analysisType::analysisType iAnalysisType = analysisType::LJ;
    const int sampleID = isData? -1 : 1;
    const std::string era = "2015_74x";
    const std::vector<std::string> s_systematics = iConfig.getParameter< std::vector<std::string> >("systematics");
    for(uint i=0; i<s_systematics.size(); i++){
      try {
	systematics.push_back(Systematics::get(s_systematics[i]));
      } catch(cms::Exception& e) {
	throw cms::Exception("InvalidUncertaintyName") << "SelectedJetProducer: systematic name " << s_systematics[i] << " not recognized" << std::endl;
      }
    }
    helper.SetUp(era, sampleID, iAnalysisType, isData);

    produces<pat::JetCollection>("rawJets");

    for(uint i=0; i<collectionNames.size();i++){
	for(uint j=0; j<systematics.size();j++){
	    produces<pat::JetCollection>(systName(collectionNames[i],systematics[j]));
	}
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

   helper.UpdateJetCorrectorUncertainties(iSetup);
   //helper.SetAK8JetCorrectorUncertainty(iSetup);

   edm::Handle<double> h_rho;
   iEvent.getByToken(rhoToken,h_rho);
   helper.SetRho(*h_rho);

   edm::Handle< pat::JetCollection > h_inputJets;
   iEvent.getByToken( jetsToken,h_inputJets );
   edm::Handle< reco::GenJetCollection > h_genJets;
   if (!isData) {iEvent.getByToken( genjetsToken, h_genJets );}

   edm::Handle< pat::ElectronCollection > h_inputElectrons;
   iEvent.getByToken( electronsToken,h_inputElectrons );

   edm::Handle< pat::MuonCollection > h_inputMuons;
   iEvent.getByToken( muonsToken,h_inputMuons );

   
   // selected jets with jet ID cuts ( do this before jet energy correction !!! )
   std::vector<pat::Jet> idJets = helper.GetSelectedJets(*h_inputJets, 0., 9999., MiniAODHelper::getjetID(JetID) , '-' );
   for(auto& jet : idJets){
   	if(!jet.hasUserFloat("neutralHadronEnergyFraction") && !jet.hasUserFloat("chargedHadronEnergyFraction")){
   	jet.addUserFloat("neutralHadronEnergyFraction",jet.neutralHadronEnergyFraction());
        jet.addUserFloat("chargedHadronEnergyFraction",jet.chargedHadronEnergyFraction());
        }
   }
   std::vector<std::vector<pat::Jet> > unsortedJets;
   if(applyCorrection){
       // initialize jetcorrector
       // std::cout << "getting JetCorrector: " << JetType+"L1L2L3" << std::endl;
       const JetCorrector* corrector = JetCorrector::getJetCorrector( JetType+"L1L2L3", iSetup );
       helper.SetJetCorrector(corrector);

       // Get raw jets
       std::vector<pat::Jet> rawJets = helper.GetUncorrectedJets(idJets);
       std::auto_ptr<pat::JetCollection>rawJets_(new pat::JetCollection(rawJets));
       iEvent.put(rawJets_, "rawJets");
       // Clean muons and electrons from jets
       std::vector<pat::Jet> cleanJets = helper.GetDeltaRCleanedJets(rawJets,*h_inputMuons,*h_inputElectrons,leptonJetDr);
       // Apply jet corrections
       //   Get genjets for new JER recommendation ( JER is done in extra producer SmearedJetProducer, the manual JER application is therefore disabled doJER=false)
       for(uint i=0; i<systematics.size(); i++){
	   unsortedJets.push_back(helper.GetCorrectedJets(cleanJets, iEvent, iSetup, h_genJets, systematics[i],true,doJER));
       }

   }

   // if no correction is to be applied, still remove jets close to a lepton
   else{
       for(uint i=0; i<systematics.size(); i++){
	   unsortedJets.push_back(helper.GetDeltaRCleanedJets(idJets,*h_inputMuons,*h_inputElectrons,leptonJetDr));
       }
   }
   // loop over all jetcollections and each systematic and apply pt,eta as well as pujetid cut on them
   for(uint i=0; i<ptMins.size(); i++ ){
       for(uint j=0; j<systematics.size(); j++){
	   //Get jet Collection which pass selections
	   std::vector<pat::Jet> selectedJets_unsorted = helper.GetSelectedJets(unsortedJets[j], ptMins[i], etaMaxs[i], jetID::none, '-',PUJetID::get(PUJetIDMins[i]) );
	   // sort the selected jets with respect to pt
	   std::auto_ptr<pat::JetCollection> selectedJets(new pat::JetCollection(helper.GetSortedByPt(selectedJets_unsorted)));

	   iEvent.put(selectedJets,systName(collectionNames[i],systematics[j]));
       }
   }
   
}

std::string SelectedJetProducer::systName(std::string name,Systematics::Type sysType){
  if( sysType == Systematics::NA ) return name;
  else                         return name + Systematics::toString(sysType);
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
