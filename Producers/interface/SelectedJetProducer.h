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


#ifndef SelectedJetProducer_h
#define SelectedJetProducer_h

// system include files
#include <memory>
#include <vector>
#include <utility>
#include <fstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "../interface/SystematicsHelper.h"

// correction stuff
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

//To use when the object is either a reference or a pointer
template <typename T>
T *ptr(T &obj) { return &obj; } //turn reference into pointer!
template <typename T>
T *ptr(T *obj) { return obj; } //obj is already pointer, return it!

//
// class declaration
//

class SelectedJetProducer : public edm::stream::EDProducer<>
{
public:
  explicit SelectedJetProducer(const edm::ParameterSet &);
  ~SelectedJetProducer();

  static void fillDescriptions(edm::ConfigurationDescriptions &descriptions);

private:
  // some enums to make things nicer
  enum class JetID
  {
    Loose,
    Tight,
    none,
    jetMETcorrection,
    jetLooseAOD,
    jetMinimal,
    jetPU
  };
  enum class PUJetIDWP
  {
    none,
    Loose,
    Medium,
    Tight
  };

  // member functions
  virtual void beginStream(edm::StreamID) override;
  virtual void produce(edm::Event &, const edm::EventSetup &) override;
  virtual void endStream() override;
  std::string systName(std::string name, SystematicsHelper::Type) const;
  bool fileExists(const std::string &fileName) const;
  void UpdateJetCorrectorUncertainties(const edm::EventSetup &iSetup);
  JetCorrectionUncertainty *CreateJetCorrectorUncertainty(const edm::EventSetup &iSetup, const std::string &jetTypeLabel, const std::string &uncertaintyLabel) const;
  std::vector<pat::Jet> GetSelectedJets(const std::vector<pat::Jet> &, const float iMinPt, const float iMaxAbsEta, const JetID, const PUJetIDWP = PUJetIDWP::none) const;
  bool isGoodJet(const pat::Jet &iJet, const float iMinPt, const float iMaxAbsEta, const JetID, const PUJetIDWP wp) const;
  std::vector<pat::Jet> GetUncorrectedJets(const std::vector<pat::Jet> &inputJets) const;
  std::vector<pat::Jet> GetDeltaRCleanedJets(const std::vector<pat::Jet> &inputJets, const std::vector<pat::Muon> &inputMuons, const std::vector<pat::Electron> &inputElectrons, const double deltaRCut) const;
  std::vector<pat::Jet> GetCorrectedJets(const std::vector<pat::Jet> &, const edm::Event &, const edm::EventSetup &, const edm::Handle<reco::GenJetCollection> &, const SystematicsHelper::Type iSysType = SystematicsHelper::NA, const bool &doJES = true, const bool &doJER = true, const float &corrFactor = 1, const float &uncFactor = 1);
  pat::Jet GetCorrectedJet(const pat::Jet &, const edm::Event &, const edm::EventSetup &, const edm::Handle<reco::GenJetCollection> &, const SystematicsHelper::Type iSysType = SystematicsHelper::NA, const bool doJES = true, const bool doJER = true, const float corrFactor = 1, const float uncFactor = 1);
  void ApplyJetEnergyCorrection(pat::Jet &jet, double &totalCorrFactor, const edm::Event &event, const edm::EventSetup &setup, const edm::Handle<reco::GenJetCollection> &genjets, const SystematicsHelper::Type iSysType, const bool doJES, const bool doJER, const bool addUserFloats, const float corrFactor, const float uncFactor);
  double GetJECUncertainty(const pat::Jet &jet, const edm::EventSetup &iSetup, const SystematicsHelper::Type iSysType);
  void AddJetCorrectorUncertainty(const edm::EventSetup &iSetup, const std::string &uncertaintyLabel);
  template <typename T> T GetSortedByPt(const T &) const;
  int TranslateJetPUIDtoInt(PUJetIDWP wp) const;

  //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

  std::string JetType;
  const bool isData;
  /** min pt of jet collections **/
  std::vector<double> ptMins;
  /** max eta of jet collections **/
  std::vector<double> etaMaxs;
  /** min dir to lepton for jets **/
  double leptonJetDr;

  /** apply jet energy correciton? **/
  const bool applyCorrection;
  const bool doJER;

  /** names of output jet collections **/
  std::vector<std::string> collectionNames;
  /** pileupjetid for collections **/
  std::vector<std::string> PUJetIDMins;
  /** jetid **/
  const std::string JetID_;
  /** Systematics used **/
  const std::vector<std::string> systematics_config;
  std::vector<SystematicsHelper::Type> systematics;

  // ----------member data ---------------------------
  /** input jets data access token **/
  edm::EDGetTokenT<pat::JetCollection> jetsToken;
  /** genjets data access token (for getcorrected jets) **/
  edm::EDGetTokenT<reco::GenJetCollection> genjetsToken;
  /** muons data access token (for jet cleaning)**/
  edm::EDGetTokenT<pat::MuonCollection> muonsToken;
  /** electrons data access token (for jet cleaning)**/
  edm::EDGetTokenT<pat::ElectronCollection> electronsToken;
  /** rho data access token (for jet cleaning)**/
  edm::EDGetTokenT<double> rhoToken;

  //JEC files
  const std::string jecFileAK4_2016;
  const std::string jecFileAK8_2016;
  const std::string jecFileAK4_2017;
  const std::string jecFileAK8_2017;

  const std::string era;


  // selection criterias
  JetID Jet_ID;
  std::vector<PUJetIDWP> PUJetID_WP;

  // some variables neccessary for systematics
  std::string jetTypeLabelForJECUncertainty;
  std::string jecUncertaintyTxtFileName;
  std::map<std::string, std::unique_ptr<JetCorrectionUncertainty>> jecUncertainties_;
  const JetCorrector *corrector;
  const bool doJES = true;

};

#endif
