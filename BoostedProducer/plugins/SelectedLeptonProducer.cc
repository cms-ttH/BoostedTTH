// -*- C++ -*-
//
// Package:    BoostedTTH/BoostedProducer
// Class:      SelectedLeptonProducer
// 
/**\class SelectedLeptonProducer SelectedLeptonProducer.cc BoostedTTH/BoostedProducer/plugins/SelectedLeptonProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Matthias Schroeder
//         Created:  Tue, 15 Sep 2015 11:58:04 GMT
//
//


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

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

//
// class declaration
//

class SelectedLeptonProducer : public edm::EDProducer {
public:
  explicit SelectedLeptonProducer(const edm::ParameterSet&);
  ~SelectedLeptonProducer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
private:
  enum LeptonType { Electron, Muon };

  virtual void beginJob() override;
  virtual void produce(edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  bool setUpHelper(const edm::Event& iEvent);
  
  // ----------member data ---------------------------
  MiniAODHelper helper_;
  LeptonType leptonType_;  

  // lepton selection criteria
  double ptMin_;
  double etaMax_;
  muonID::muonID muonID_;
  electronID::electronID electronID_;
  coneSize::coneSize isoConeSize_;
  corrType::corrType isoCorrType_;
  
  // data access tokens
  edm::EDGetTokenT< double >                  EDMRhoToken; //  pileup density
  edm::EDGetTokenT< reco::VertexCollection >  EDMVertexToken; // vertex
  edm::EDGetTokenT< pat::MuonCollection >     EDMMuonsToken;  // muons
  edm::EDGetTokenT< pat::ElectronCollection > EDMElectronsToken;  // electrons
};


//
// constructors and destructor
//
SelectedLeptonProducer::SelectedLeptonProducer(const edm::ParameterSet& iConfig)
{
  const std::string leptonType = iConfig.getParameter<std::string>("leptonType");
  if(      leptonType == "electron" ) leptonType_ = Electron;
  else if( leptonType == "muon"     ) leptonType_ = Muon;
  else {
    std::cerr << "\n\nERROR: Unknown lepton type '" << leptonType << "'" << std::endl;
    std::cerr << "Please select 'electron' or 'muon'\n" << std::endl;
    throw std::exception();
  }

  const std::string era = iConfig.getParameter<std::string>("era");
  const std::string analysisType = iConfig.getParameter<std::string>("analysisType");
  analysisType::analysisType iAnalysisType = analysisType::LJ;
  if(      analysisType == "LJ"     ) iAnalysisType = analysisType::LJ;
  else if( analysisType == "DIL"    ) iAnalysisType = analysisType::DIL;
  else if( analysisType == "TauLJ"  ) iAnalysisType = analysisType::TauLJ;
  else if( analysisType == "TauDIL" ) iAnalysisType = analysisType::TauDIL;
  else {
    std::cerr << "\n\nERROR: No matching analysis type found for: " << analysisType << std::endl;
    throw std::exception();
  }
  
  EDMElectronsToken  = consumes< pat::ElectronCollection >  (iConfig.getParameter<edm::InputTag>("leptons"));
  EDMMuonsToken      = consumes< pat::MuonCollection >      (iConfig.getParameter<edm::InputTag>("leptons"));
  EDMVertexToken = consumes< reco::VertexCollection >       (iConfig.getParameter<edm::InputTag>("vertices"));
  EDMRhoToken    = consumes< double >                       (iConfig.getParameter<edm::InputTag>("rho"));
  
  ptMin_ = iConfig.getParameter<double>("ptMin");
  etaMax_ = iConfig.getParameter<double>("etaMax");
  
  const std::string leptonID = iConfig.getParameter<std::string>("leptonID");
  electronID_ = electronID::electronLoose;
  muonID_ = muonID::muonLoose;
  if(leptonType_ == Electron){
    if(      leptonID == "loose"        ) electronID_ = electronID::electronLoose;
    else if( leptonID == "tight"        ) electronID_ = electronID::electronTight;
    else if( leptonID == "loosePhys14"  ) electronID_ = electronID::electronPhys14L;
    else if( leptonID == "tightPhys14"  ) electronID_ = electronID::electronPhys14T;
    else {
      std::cerr << "\n\nERROR: No matching electron ID type found for: " << leptonID << std::endl;
      throw std::exception();
    }
  }
  if(leptonType_ == Muon){
    if(      leptonID == "loose"  ) muonID_ = muonID::muonLoose;
    else if( leptonID == "tight"  ) muonID_ = muonID::muonTight;
    else {
      std::cerr << "\n\nERROR: No matching muon ID type found for: " << leptonID << std::endl;
      throw std::exception();
    }
  }
  
  const std::string isoConeSize = iConfig.getParameter<std::string>("isoConeSize");
  isoConeSize_ = coneSize::R04;
  if(      isoConeSize == "R03"  ) isoConeSize_ = coneSize::R03;
  else if( isoConeSize == "R04"  ) isoConeSize_ = coneSize::R04;
  else {
    std::cerr << "\n\nERROR: No matching isolation cone size found for: " << isoConeSize << std::endl;
    throw std::exception();
  }
  
  const std::string isoCorrType = iConfig.getParameter<std::string>("isoCorrType");
  isoCorrType_ = corrType::deltaBeta;
  if(      isoCorrType == "deltaBeta" ) isoCorrType_ = corrType::deltaBeta;
  else if( isoCorrType == "rhoEA"     ) isoCorrType_ = corrType::rhoEA;
  else {
    std::cerr << "\n\nERROR: No matching isolation correction type found for: " << isoCorrType << std::endl;
    throw std::exception();
  }
  
  // Set up MiniAODHelper
  const bool isData = iConfig.getParameter<bool>("isData");
  const int sampleID = -1;
  helper_.SetUp(era,sampleID,iAnalysisType,isData);

  if( leptonType_ == Electron ) produces<pat::ElectronCollection>();
  if( leptonType_ == Muon     ) produces<pat::MuonCollection>();
}


SelectedLeptonProducer::~SelectedLeptonProducer() {}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
SelectedLeptonProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  if( setUpHelper(iEvent) ) {
    
    if( leptonType_ == Electron ) {
      // select and produce electron collection

      edm::Handle<pat::ElectronCollection> hElectrons;
      iEvent.getByToken(EDMElectronsToken,hElectrons);
      
      std::auto_ptr<pat::ElectronCollection> selectedLeptons( new pat::ElectronCollection(helper_.GetSelectedElectrons(*hElectrons,ptMin_,electronID_,etaMax_)) );
      
      std::cout << ">>>>> SELECTED Electrons: " << selectedLeptons->size() << " electrons" << std::endl;
      for(pat::ElectronCollection::const_iterator iObj = selectedLeptons->begin(); iObj != selectedLeptons->end(); ++iObj) {
	      std::cout << "  pt = " << iObj->pt() << std::endl;
      }
      
      iEvent.put(selectedLeptons);
    }
    else if( leptonType_ == Muon ) {
      // select and produce muon collection

      edm::Handle<pat::MuonCollection> hMuons;
      iEvent.getByToken(EDMMuonsToken,hMuons);
      
      std::auto_ptr<pat::MuonCollection> selectedLeptons( new pat::MuonCollection(helper_.GetSelectedMuons(*hMuons,ptMin_,muonID_,isoConeSize_,isoCorrType_,etaMax_)) );
      
      std::cout << ">>>>> SELECTED MUONS: " << selectedLeptons->size() << " muons" << std::endl;
      for(pat::MuonCollection::const_iterator iObj = selectedLeptons->begin(); iObj != selectedLeptons->end(); ++iObj) {
	      std::cout << "  pt = " << iObj->pt() << std::endl;
      }
      
      iEvent.put(selectedLeptons);
    }
  }
}

// Do event-wise setup of MiniAODHelper
// Return true if successful, false otherwise
bool
SelectedLeptonProducer::setUpHelper(const edm::Event& iEvent)
{
  // get RHO
  edm::Handle<double> hRho;
  iEvent.getByToken(EDMRhoToken,hRho);
  if( hRho.isValid() ) {
    helper_.SetRho(*hRho);
  } else {
    return false;
  }

  // get PRIMARY VERTICES
  edm::Handle<reco::VertexCollection> hVtxs;
  iEvent.getByToken(EDMVertexToken,hVtxs);
  if( hVtxs->size()>0 ) {
    helper_.SetVertex( hVtxs->at(0) );
  } else {
    return false;
  }

  return true;
}


// ------------ method called once each job just before starting event loop  ------------
void 
SelectedLeptonProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SelectedLeptonProducer::endJob() {
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SelectedLeptonProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SelectedLeptonProducer);
