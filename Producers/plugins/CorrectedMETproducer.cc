#include <memory>
#include <vector>

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

class CorrectedMETproducer : public edm::stream::EDProducer<> {
public:
    explicit CorrectedMETproducer(const edm::ParameterSet&);
    ~CorrectedMETproducer();
    
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    
private:
    virtual void beginStream(edm::StreamID) override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endStream() override;
    
    // ----------member data ---------------------------
    /** input jets data access token -- before (re-)correction **/
    edm::EDGetTokenT< std::vector<pat::Jet> > oldJetsToken;    
    /** input jets data access token -- after (re-)correction **/
    edm::EDGetTokenT< std::vector<pat::Jet> > newJetsToken;
    /** mets data access token **/
    edm::EDGetTokenT< std::vector<pat::MET> > metsToken;
    /** MiniAODHelper, used for jet correction and selection **/
    MiniAODHelper helper;
    /** names of output jet collections **/
    std::string collectionName;
    
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
CorrectedMETproducer::CorrectedMETproducer(const edm::ParameterSet& iConfig)
{
    oldJetsToken  = consumes< std::vector<pat::Jet> >(iConfig.getParameter<edm::InputTag>("oldJets"));
    newJetsToken  = consumes< std::vector<pat::Jet> >(iConfig.getParameter<edm::InputTag>("newJets"));
    metsToken  = consumes< std::vector<pat::MET> >(iConfig.getParameter<edm::InputTag>("mets"));
    collectionName = iConfig.getParameter< std::string>("collectionName");

    const bool isData = iConfig.getParameter<bool>("isData");
    analysisType::analysisType iAnalysisType = analysisType::LJ;
    const int sampleID = isData? -1 : 1;
    const std::string era = "2015_74x";
    helper.SetUp(era, sampleID, iAnalysisType, isData);

    produces<pat::METCollection>(collectionName);      
}


CorrectedMETproducer::~CorrectedMETproducer()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
CorrectedMETproducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle< pat::JetCollection > h_oldJets;
   iEvent.getByToken( oldJetsToken,h_oldJets );

   edm::Handle< pat::JetCollection > h_newJets;
   iEvent.getByToken( oldJetsToken,h_newJets );
  
   edm::Handle< pat::METCollection > h_inputMETs;
   iEvent.getByToken( metsToken,h_inputMETs );

   std::auto_ptr<pat::METCollection> correctedMETs( new pat::METCollection(helper.CorrectMET(*h_oldJets,*h_newJets,*h_inputMETs)) );
   iEvent.put(correctedMETs,collectionName);
   
   
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
CorrectedMETproducer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
CorrectedMETproducer::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
CorrectedMETproducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
CorrectedMETproducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
CorrectedMETproducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
CorrectedMETproducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CorrectedMETproducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CorrectedMETproducer);
