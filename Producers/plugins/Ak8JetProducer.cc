// -*- C++ -*-
//
// Package:    BoostedTTH/BoostedJetProducer
// Class:      BoostedJetProducer
//
/**\class BoostedJetProducer BoostedJetProducer.cc BoostedTTH/BoostedJetProducer/plugins/BoostedJetProducer.cc

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
#include "FWCore/Utilities/interface/Exception.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/Systematics.h"
#include "MiniAOD/MiniAODHelper/interface/PUJetID.h"
//
// class declaration
//

class Ak8JetProducer : public edm::stream::EDProducer<> {
public:
  explicit Ak8JetProducer(const edm::ParameterSet&);
  ~Ak8JetProducer();

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
  edm::EDGetTokenT< pat::JetCollection > AK8PFCHSSoftDrop_Token;


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
Ak8JetProducer::Ak8JetProducer(const edm::ParameterSet& iConfig)
{
  AK8PFCHSSoftDrop_Token  = consumes< pat::JetCollection >(iConfig.getParameter<edm::InputTag>("jets"));

  ptMins = iConfig.getParameter< std::vector<double> >("ptMins");
  etaMaxs = iConfig.getParameter< std::vector<double> >("etaMaxs");
  leptonJetDr = iConfig.getParameter< double >("leptonJetDr");
  applyCorrection = iConfig.getParameter<bool>("applyCorrection");
  doJER = iConfig.getParameter<bool>("doJER");
  collectionNames = iConfig.getParameter< std::vector<std::string> >("collectionNames");
  PUJetIDMins = iConfig.getParameter<std::vector<std::string>> ("PUJetIDMins");
  JetID = iConfig.getParameter<std::string> ("JetID");

  assert(ptMins.size() == etaMaxs.size());
  assert(ptMins.size() == collectionNames.size());

  isData = iConfig.getParameter<bool>("isData");
  analysisType::analysisType iAnalysisType = analysisType::LJ;
  const int sampleID = isData ? -1 : 1;
  const std::string era = "2015_74x";
  const std::vector<std::string> s_systematics = iConfig.getParameter< std::vector<std::string> >("systematics");

  helper.SetUp(era, sampleID, iAnalysisType, isData);

  produces<pat::JetCollection>("rawK8PFCHSSoftDropJets");
  for (uint i = 0; i < collectionNames.size(); i++) {
    // for (uint j = 0; j < systematics.size(); j++) {
      // produces<pat::JetCollection>(systName(collectionNames[i], systematics[j]));
      produces<pat::JetCollection>(collectionNames[i]);

    // }
  }


}


Ak8JetProducer::~Ak8JetProducer()
{

  // do anything here that needs to be done at destruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
Ak8JetProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  helper.UpdateJetCorrectorUncertainties(iSetup);
  helper.SetAK8JetCorrectorUncertainty(iSetup);

  edm::Handle< pat::JetCollection > h_inputJets_AK8PFCHSSoftDrop;
  iEvent.getByToken( AK8PFCHSSoftDrop_Token, h_inputJets_AK8PFCHSSoftDrop );

  const std::vector<pat::Jet> idJets_AK8PFCHSSoftDropJets = helper.GetSelectedJets(*h_inputJets_AK8PFCHSSoftDrop, 0., 9999., MiniAODHelper::getjetID(JetID) , '-' );
  std::vector<pat::Jet> rawK8PFCHSSoftDropJets = helper.GetUncorrectedJets(idJets_AK8PFCHSSoftDropJets);
  std::auto_ptr<pat::JetCollection>rawK8PFCHSSoftDropJets_(new pat::JetCollection(rawK8PFCHSSoftDropJets));
  iEvent.put(rawK8PFCHSSoftDropJets_, collectionNames[0]);


}

std::string Ak8JetProducer::systName(std::string name, Systematics::Type sysType) {
  if ( sysType == Systematics::NA ) return name;
  else                         return name + Systematics::toString(sysType);
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
Ak8JetProducer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
Ak8JetProducer::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
Ak8JetProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void
Ak8JetProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void
Ak8JetProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
Ak8JetProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Ak8JetProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}


//define this as a plug-in
DEFINE_FWK_MODULE(Ak8JetProducer);