// -*- C++ -*-
//
// Package:    BoostedTTH/BoostedAnalyzer
// Class:      LeptonJetsSkim
//
/**\class LeptonJetsSkim LeptonJetsSkim.cc
 BoostedTTH/BoostedProducer/plugins/LeptonJetsSkim.cc

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
#include <exception>
#include <iostream>
#include <memory>

// user include files
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

//
// class declaration
//

class LeptonJetsSkim : public edm::EDFilter
{
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
  MiniAODHelper helper_;
  int minJets_;
  double jetPtMin_;
  double jetEtaMax_;
  double muonPtMin_;
  double muonEtaMax_;
  double electronPtMin_;
  double electronEtaMax_;
  muonID::muonID muonID_;
  electronID::electronID electronID_;
  coneSize::coneSize muonIsoConeSize_;
  corrType::corrType muonIsoCorrType_;

  // data access tokens
  edm::EDGetTokenT<double> EDMRhoToken;                    //  pileup density
  edm::EDGetTokenT<reco::VertexCollection> EDMVertexToken; // vertex
  edm::EDGetTokenT<pat::MuonCollection> EDMMuonsToken;     // muons
  edm::EDGetTokenT<pat::ElectronCollection> EDMElectronsToken; // electrons
  edm::EDGetTokenT<pat::JetCollection> EDMJetsToken;           // jets
};

//
// constructors and destructor
//
LeptonJetsSkim::LeptonJetsSkim(const edm::ParameterSet& iConfig)
{
  // now do what ever initialization is needed
  const std::string era = iConfig.getParameter<std::string>("era");
  analysisType::analysisType iAnalysisType = analysisType::LJ;

  EDMElectronsToken = consumes<pat::ElectronCollection>(
    iConfig.getParameter<edm::InputTag>("electrons"));
  EDMMuonsToken =
    consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"));
  EDMJetsToken =
    consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets"));
  EDMVertexToken = consumes<reco::VertexCollection>(
    iConfig.getParameter<edm::InputTag>("vertices"));
  EDMRhoToken = consumes<double>(iConfig.getParameter<edm::InputTag>("rho"));

  minJets_ = iConfig.getParameter<int>("minJets");
  jetPtMin_ = iConfig.getParameter<double>("jetPtMin");
  jetEtaMax_ = iConfig.getParameter<double>("jetEtaMax");
  muonPtMin_ = iConfig.getParameter<double>("muonPtMin");
  muonEtaMax_ = iConfig.getParameter<double>("muonEtaMax");
  electronPtMin_ = iConfig.getParameter<double>("electronPtMin");
  electronEtaMax_ = iConfig.getParameter<double>("electronEtaMax");
  electronID_ = electronID::electron80XCutBasedM;
  muonID_ = muonID::muonTight;

  muonIsoConeSize_ = coneSize::R04;
  muonIsoCorrType_ = corrType::deltaBeta;
  const bool isData = iConfig.getParameter<bool>("isData");
  const int sampleID = isData ? -1 : 1;
  helper_.SetUp(era, sampleID, iAnalysisType, isData);
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
  if (setUpHelper(iEvent)) {

    edm::Handle<pat::ElectronCollection> h_electrons;
    iEvent.getByToken(EDMElectronsToken, h_electrons);
    // select electrons
    pat::ElectronCollection selectedElectrons = helper_.GetSelectedElectrons(
      *h_electrons, electronPtMin_, electronID_, electronEtaMax_);

    edm::Handle<pat::MuonCollection> hMuons;
    iEvent.getByToken(EDMMuonsToken, hMuons);
    pat::MuonCollection selectedMuons =
      helper_.GetSelectedMuons(*hMuons,
                               muonPtMin_,
                               muonID_,
                               muonIsoConeSize_,
                               muonIsoCorrType_,
                               muonEtaMax_);

    edm::Handle<pat::JetCollection> hJets;
    iEvent.getByToken(EDMJetsToken, hJets);
    pat::JetCollection selectedJets = helper_.GetSelectedJets(
      *hJets, jetPtMin_, jetEtaMax_, jetID::jetLoose, '-');
    // TODO: correct jets (maybe even with JESUP) to make sure the jetcuts are
    // loose enough

    if ((selectedMuons.size() + selectedElectrons.size()) >= 1 &&
        int(selectedJets.size()) > minJets_) {
      return true;
    }
  }
  return false;
}

// Do event-wise setup of MiniAODHelper
// Return true if successful, false otherwise
bool
LeptonJetsSkim::setUpHelper(const edm::Event& iEvent)
{
  // get RHO
  edm::Handle<double> hRho;
  iEvent.getByToken(EDMRhoToken, hRho);
  if (hRho.isValid()) {
    helper_.SetRho(*hRho);
  } else {
    cout << "could not find rho" << endl;
    return false;
  }

  // get PRIMARY VERTICES
  edm::Handle<reco::VertexCollection> hVtxs;
  iEvent.getByToken(EDMVertexToken, hVtxs);
  if (hVtxs->size() > 0) {
    helper_.SetVertex(hVtxs->at(0));
  } else {
    cout << "could not find vertices" << endl;
    return false;
  }
  return true;
}

// ------------ method called once each job just before starting event loop
// ------------
void
LeptonJetsSkim::beginJob()
{
}

// ------------ method called once each job just after ending the event loop
// ------------
void
LeptonJetsSkim::endJob()
{
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

// ------------ method called when starting to processes a luminosity block
// ------------
/*
void
LeptonJetsSkim::beginLuminosityBlock(edm::LuminosityBlock const&,
edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block
// ------------
/*
void
LeptonJetsSkim::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup
const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the
// module  ------------
void
LeptonJetsSkim::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
  // The following says we do not know what parameters are allowed so do no
  // validation
  // Please change this to state exactly what you do use, even if it is no
  // parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
// define this as a plug-in
DEFINE_FWK_MODULE(LeptonJetsSkim);
