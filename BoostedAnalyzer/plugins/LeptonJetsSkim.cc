// -*- C++ -*-
//
// Package:    BoostedTTH/BoostedAnalyzer
// Class:      LeptonJetsSkim
// 
/**\class LeptonJetsSkim LeptonJetsSkim.cc BoostedTTH/BoostedProducer/plugins/LeptonJetsSkim.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Hannes Mildner
//         Created:  Sat, 17 Oct 2015 09:19:10 GMT
//
//


// system include files
#include <memory>
#include <exception>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"


#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

//
// class declaration
//

class LeptonJetsSkim : public edm::EDFilter {
   public:
      explicit LeptonJetsSkim(const edm::ParameterSet&);
      ~LeptonJetsSkim();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      bool setUpHelper(const edm::Event& iEvent);
      
      // ----------member data ---------------------------
    int minJetsAK4_;
    int minJetsAK8_;
    int maxJetsAK4_;
    int maxJetsAK8_;
    double AK4jetPtMin_;
    double AK4jetEtaMax_;
    double AK8jetPtMin_;
    double AK8jetEtaMax_;
    double muonPtMin_;
    double muonEtaMax_;
    double electronPtMin_;
    double electronEtaMax_;
    double photonPtMin_;
    double photonEtaMax_;
    double metPtMin_;

  
  // data access tokens
    edm::EDGetTokenT< double >                    EDMRhoToken; //  pileup density
    edm::EDGetTokenT< reco::VertexCollection >    EDMVertexToken; // vertex
    edm::EDGetTokenT< pat::MuonCollection >       EDMMuonsToken;  // muons
    edm::EDGetTokenT< pat::ElectronCollection >   EDMElectronsToken;  // electrons
    edm::EDGetTokenT< pat::PhotonCollection >     EDMPhotonsToken;     // photons
    edm::EDGetTokenT< pat::JetCollection >        EDMAK4JetsToken;  // AK4 jets
    edm::EDGetTokenT< pat::JetCollection >        EDMAK8JetsToken;  // AK8 jets
    edm::EDGetTokenT< std::vector<pat::MET> >        EDMMETToken; // MET


};

//
// constructors and destructor
//
LeptonJetsSkim::LeptonJetsSkim(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
  const std::string era = iConfig.getParameter<std::string>("era");
  
  EDMElectronsToken         = consumes <pat::ElectronCollection >  (iConfig.getParameter<edm::InputTag>("electrons"));
  EDMMuonsToken             = consumes< pat::MuonCollection >       (iConfig.getParameter<edm::InputTag>("muons"));
  EDMPhotonsToken           = consumes< std::vector<pat::Photon> >     (iConfig.getParameter<edm::InputTag>("photons"));
  EDMAK4JetsToken           = consumes< pat::JetCollection >        (iConfig.getParameter<edm::InputTag>("AK4jets"));
  EDMAK8JetsToken           = consumes< pat::JetCollection >        (iConfig.getParameter<edm::InputTag>("AK8jets"));
  EDMVertexToken            = consumes< reco::VertexCollection >    (iConfig.getParameter<edm::InputTag>("vertices"));
  EDMRhoToken               = consumes< double >                    (iConfig.getParameter<edm::InputTag>("rho"));
  EDMMETToken               = consumes< std::vector<pat::MET> > (iConfig.getParameter<edm::InputTag>("met"));

  minJetsAK4_           = iConfig.getParameter<int>("minJetsAK4");
  minJetsAK8_           = iConfig.getParameter<int>("minJetsAK8");
  maxJetsAK4_           = iConfig.getParameter<int>("maxJetsAK4");
  maxJetsAK8_           = iConfig.getParameter<int>("maxJetsAK8");
  AK4jetPtMin_          = iConfig.getParameter<double>("AK4jetPtMin");
  AK4jetEtaMax_         = iConfig.getParameter<double>("AK4jetEtaMax");
  AK8jetPtMin_          = iConfig.getParameter<double>("AK8jetPtMin");
  AK8jetEtaMax_         = iConfig.getParameter<double>("AK8jetEtaMax");
  
  muonPtMin_            = iConfig.getParameter<double>("muonPtMin");
  muonEtaMax_           = iConfig.getParameter<double>("muonEtaMax");
  electronPtMin_        = iConfig.getParameter<double>("electronPtMin");
  electronEtaMax_       = iConfig.getParameter<double>("electronEtaMax");
  photonPtMin_          = iConfig.getParameter<double>("photonPtMin");
  photonEtaMax_         = iConfig.getParameter<double>("photonEtaMax");
  
  metPtMin_             = iConfig.getParameter<double>("metPtMin");
  
  const bool isData     = iConfig.getParameter<bool>("isData");
  const int sampleID    = isData? -1 : 1;

}


LeptonJetsSkim::~LeptonJetsSkim()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
LeptonJetsSkim::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	// get slimmedElectrons
	edm::Handle< pat::ElectronCollection > h_electrons;
	iEvent.getByToken(EDMElectronsToken,h_electrons);
    
    // select those electrons satifsying pt and eta cuts
    std::vector<pat::Electron> selectedElectrons = *h_electrons;
    selectedElectrons.erase(std::remove_if(selectedElectrons.begin(),selectedElectrons.end(),[&](pat::Electron ele){return !(ele.pt()>=electronPtMin_ && fabs(ele.eta())<=electronEtaMax_);}),selectedElectrons.end());

    // get slimmedMuons
	edm::Handle<pat::MuonCollection> hMuons;
	iEvent.getByToken(EDMMuonsToken,hMuons);
    
    // select those muons satisfying pt and eta cuts
    std::vector<pat::Muon> selectedMuons = *hMuons;
    selectedMuons.erase(std::remove_if(selectedMuons.begin(),selectedMuons.end(),[&](pat::Muon mu){return !(mu.pt()>=muonPtMin_ && fabs(mu.eta())<=muonEtaMax_);}),selectedMuons.end());
    
    // get slimmedPhotons
	edm::Handle<pat::PhotonCollection> hPhotons;
	iEvent.getByToken(EDMPhotonsToken,hPhotons);
    
    // select those photons satisfying pt and eta cuts
    std::vector<pat::Photon> selectedPhotons = *hPhotons;
    selectedPhotons.erase(std::remove_if(selectedPhotons.begin(),selectedPhotons.end(),[&](pat::Photon ph){return !(ph.pt()>=photonPtMin_ && fabs(ph.eta())<=photonEtaMax_);}),selectedPhotons.end());
	
    // get AK4 jets
	edm::Handle<pat::JetCollection> ak4Jets;
	iEvent.getByToken(EDMAK4JetsToken,ak4Jets);
    
    // get AK8 jets
    edm::Handle<pat::JetCollection> ak8Jets;
	iEvent.getByToken(EDMAK8JetsToken,ak8Jets);
    
    // get slimmedMETs
    edm::Handle<std::vector<pat::MET>> hMETs;
	iEvent.getByToken(EDMMETToken,hMETs);
    
	int n_ak4jets = 0;
    int n_ak8jets = 0;
    
    // count ak4 and ak8 jets satisfying pt and eta cuts
	n_ak4jets = std::count_if(ak4Jets->begin(),ak4Jets->end(),[&](pat::Jet jet){return (jet.pt()>=AK4jetPtMin_ && fabs(jet.eta())<=AK4jetEtaMax_);});
    n_ak8jets = std::count_if(ak8Jets->begin(),ak8Jets->end(),[&](pat::Jet jet){return (jet.pt()>=AK8jetPtMin_ && fabs(jet.eta())<=AK8jetEtaMax_);});
    
    
    // calculate approximate hadronic recoil
    auto hadr_recoil = hMETs->at(0).p4();
    
    for(const auto& ele : selectedElectrons){
        hadr_recoil+=ele.p4();
    }
    for(const auto& mu : selectedMuons){
        hadr_recoil+=mu.p4();
    }
    for(const auto& ph : selectedPhotons){
        hadr_recoil+=ph.p4();
    }
    
    // apply skimming selection
    if(n_ak4jets<minJetsAK4_ && n_ak8jets<minJetsAK8_) return false;
    if(hMETs->at(0).pt()<metPtMin_ && hadr_recoil.pt()<metPtMin_) return false;
    if(n_ak4jets>maxJetsAK4_ || n_ak8jets > maxJetsAK8_) return false;
    
    std::cout << "Number of AK4 jets: " << n_ak4jets << std::endl;
    std::cout << "Number of AK8 jets: " << n_ak8jets << std::endl;
    std::cout << "MET: " << hMETs->at(0).pt() << std::endl;
    std::cout << "Hadronic recoil: " << hadr_recoil.pt() << std::endl;
    std::cout << "Number of selected electrons: " << selectedElectrons.size() << std::endl;
    std::cout << "Number of selected muons: " << selectedMuons.size() << std::endl;
    std::cout << "Number of selected photons: " << selectedPhotons.size() << std::endl;

	return true;
}



// ------------ method called once each job just before starting event loop  ------------
void 
LeptonJetsSkim::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
LeptonJetsSkim::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
LeptonJetsSkim::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
LeptonJetsSkim::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
LeptonJetsSkim::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
LeptonJetsSkim::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
LeptonJetsSkim::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(LeptonJetsSkim);
