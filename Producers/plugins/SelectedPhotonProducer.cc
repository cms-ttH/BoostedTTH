// system include files
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

#include "DataFormats/PatCandidates/interface/Photon.h"

class SelectedPhotonProducer : public edm::EDProducer {
public:
  explicit SelectedPhotonProducer(const edm::ParameterSet&);
  ~SelectedPhotonProducer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:

  virtual void beginJob() override;
  virtual void produce(edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  std::vector<pat::Photon> GetSelectedPhotons(const std::vector<pat::Photon>& inputPhotons, const float iMinPt, const float iMaxEta);
  bool isGoodPhoton(const pat::Photon& iPhoton, const float iMinPt, const float iMaxEta);
  // ----------member data ---------------------------
  std::vector<double> ptMins_;
  std::vector<double> etaMaxs_;
  std::vector<std::string> collectionNames_;
  std::vector<std::string> ids_;
  
  //std::vector<pat::Photon> photons_;
  edm::EDGetTokenT< edm::View<pat::Photon> > edmPhotonsToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > phoLooseIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > phoMediumIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > phoTightIdMapToken_;
  
};

SelectedPhotonProducer::SelectedPhotonProducer(const edm::ParameterSet& iConfig)
{
    ptMins_ = iConfig.getParameter< std::vector<double> >("ptMins");
    etaMaxs_ = iConfig.getParameter< std::vector<double> >("etaMaxs");
    collectionNames_ = iConfig.getParameter< std::vector<std::string> >("collectionNames");
    ids_ = iConfig.getParameter< std::vector<std::string> >("IDs");
    
    edmPhotonsToken_         = consumes< edm::View<pat::Photon> > (iConfig.getParameter<edm::InputTag>("photons"));
    phoLooseIdMapToken_     = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoLooseIdMap"));
    phoMediumIdMapToken_    = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoMediumIdMap"));
    phoTightIdMapToken_     = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoTightIdMap"));
    
    for(size_t i=0;i<ptMins_.size();i++){
        produces<pat::PhotonCollection>(collectionNames_[i]);
    }
}

SelectedPhotonProducer::~SelectedPhotonProducer() {}

void
SelectedPhotonProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    edm::Handle<edm::View<pat::Photon>> photons;
    edm::Handle<edm::ValueMap<bool> > loose_id_decisions;
    edm::Handle<edm::ValueMap<bool> > medium_id_decisions;
    edm::Handle<edm::ValueMap<bool> > tight_id_decisions;
    
    iEvent.getByToken(edmPhotonsToken_,photons);
    iEvent.getByToken(phoLooseIdMapToken_ ,loose_id_decisions);
    iEvent.getByToken(phoMediumIdMapToken_,medium_id_decisions);
    iEvent.getByToken(phoTightIdMapToken_ ,tight_id_decisions);
    
    for(size_t i=0;i<ptMins_.size();i++){
        std::vector<pat::Photon> IDphotons;
        for (size_t j = 0; j < photons->size(); j++){
            auto pho = photons->ptrAt(j);
            //std::cout << "Photon " << j << std::endl;
            bool passesID = false;
            if(ids_[i]=="loose") passesID = (*loose_id_decisions)[pho];
            else if(ids_[i]=="medium") passesID =  (*medium_id_decisions)[pho];
            else if(ids_[i]=="tight") passesID =  (*tight_id_decisions)[pho];
            else {
                std::cerr << "\n\nERROR: No matching Photon ID type found for: " << ids_[i] << std::endl;
                throw std::exception();
            }
            if(passesID) {
            	//std::cout << "Photon ID passed " << std::endl;
            	IDphotons.push_back(photons->at(j));
            }
        }
        std::auto_ptr<pat::PhotonCollection> selectedPhotons(new pat::PhotonCollection(GetSelectedPhotons(IDphotons,ptMins_[i],etaMaxs_[i])));
        iEvent.put(selectedPhotons,collectionNames_[i]);
    }
    
}

// ------------ method called once each job just before starting event loop  ------------
void
SelectedPhotonProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
SelectedPhotonProducer::endJob() {
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SelectedPhotonProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

std::vector<pat::Photon> SelectedPhotonProducer::GetSelectedPhotons(const std::vector<pat::Photon>& inputPhotons, const float iMinPt, const float iMaxEta)
{
    std::vector<pat::Photon> selectedPhotons;

    for( std::vector<pat::Photon>::const_iterator it = inputPhotons.begin(), ed = inputPhotons.end(); it != ed; ++it ){
        if( isGoodPhoton(*it,iMinPt,iMaxEta) ) selectedPhotons.push_back(*it);
    }

    return selectedPhotons;
}

bool SelectedPhotonProducer::isGoodPhoton(const pat::Photon& iPhoton, const float iMinPt, const float iMaxEta)
{
    bool passesKinematics = ((iPhoton.pt() >= iMinPt) && (fabs(iPhoton.eta()) <= iMaxEta));
    //bool isEB =  fabs(SCeta) < 1.479 ;
    //double full5x5_sigmaIetaIeta = iPhoton.full5x5_sigmaIetaIeta();
    //double HoverE = iPhoton.hadronicOverEm();
  
    return passesKinematics;
}

//define this as a plug-in
DEFINE_FWK_MODULE(SelectedPhotonProducer);
