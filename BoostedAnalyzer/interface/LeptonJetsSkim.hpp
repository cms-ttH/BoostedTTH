// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// #include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "BoostedTTH/Producers/plugins/SelectedLeptonProducer.cc"
#include "BoostedTTH/Producers/plugins/SelectedJetProducer.cc"

//
// class declaration
//
// // some enums to make things nicer (defined in SelectedLeptonProducer)
// enum class ElectronID    {None, Veto, Loose, Medium, Tight};
// enum class MuonID        {None, Loose, Medium, Tight};
// enum class IsoConeSize      {R03, R04};
// enum class IsoCorrType      {rhoEA, deltaBeta};
// enum class MuonIsolation {None, Loose, Medium, Tight}

class LeptonJetsSkim : public edm::EDFilter
{
public:
  explicit LeptonJetsSkim(const edm::ParameterSet &);
  ~LeptonJetsSkim();

  static void fillDescriptions(edm::ConfigurationDescriptions &descriptions);

private:
  virtual void beginJob() override;
  virtual bool filter(edm::Event &, const edm::EventSetup &) override;
  virtual void endJob() override;
  bool setUpHelper(const edm::Event &iEvent);

  std::vector<pat::Electron>
  GetSelectedElectrons(const std::vector<pat::Electron> &inputElectrons,
                       const double iMinPt, const SelectedLeptonProducer::ElectronID iElectronID,
                       const double iMaxEta) const;

  std::vector<pat::Muon>
  GetSelectedMuons(const std::vector<pat::Muon> &inputMuons, const double iMinPt,
                   const SelectedLeptonProducer::MuonID iMuonID, const SelectedLeptonProducer::IsoConeSize iconeSize,
                   const SelectedLeptonProducer::IsoCorrType icorrType,
                   const double iMaxEta, const SelectedLeptonProducer::MuonIsolation imuonIso) const;

  // function to return Jets, which fullfill all IDs
  std::vector<pat::Jet>
  GetSelectedJets(const std::vector<pat::Jet> &inputJets,
                  const float iMinPt, const float iMaxAbsEta,
                  const SelectedJetProducer::JetID iJetID, const SelectedJetProducer::PUJetIDWP wp) const;

  // ----------member data ---------------------------
  std::string era;
  int minJets_;
  double jetPtMin_;
  double jetEtaMax_;
  double muonPtMin_;
  double muonEtaMax_;
  double electronPtMin_;
  double electronEtaMax_;

  // primary vertex
  reco::Vertex vertex;
  // event-specific average pile-up energy density per unit area in the phi-eta plane
  double rho;

  SelectedLeptonProducer::ElectronID electronID_;
  SelectedLeptonProducer::MuonID muonID_;
  SelectedLeptonProducer::MuonIsolation muonIso_;
  SelectedLeptonProducer::IsoConeSize muonIsoConeSize_;
  SelectedLeptonProducer::IsoCorrType muonIsoCorrType_;

  // data access tokens
  edm::EDGetTokenT<double> EDMRhoToken;                        // pileup density
  edm::EDGetTokenT<reco::VertexCollection> EDMVertexToken;     // vertex
  edm::EDGetTokenT<pat::MuonCollection> EDMMuonsToken;         // muons
  edm::EDGetTokenT<pat::ElectronCollection> EDMElectronsToken; // electrons
  edm::EDGetTokenT<pat::JetCollection> EDMJetsToken;           // jets
};