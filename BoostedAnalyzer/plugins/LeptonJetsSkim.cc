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
    bool         setUpHelper(const edm::Event& iEvent);

    // ----------member data ---------------------------

    // data access tokens
    edm::EDGetTokenT< pat::ElectronCollection > EDMElectronsToken;  // electrons
    edm::EDGetTokenT< pat::MuonCollection >     EDMMuonsToken;      // muons
    edm::EDGetTokenT< pat::PhotonCollection >   EDMPhotonsToken;    // photons
    edm::EDGetTokenT< pat::JetCollection >      EDMAK4JetsToken;    // AK4 jets
    edm::EDGetTokenT< pat::JetCollection >      EDMAK8JetsToken;    // AK8 jets
    edm::EDGetTokenT< std::vector< pat::MET > > EDMMETToken;        // MET
    edm::EDGetTokenT< std::vector< pat::MET > > EDMPuppiMETToken;
    edm::EDGetTokenT< reco::VertexCollection >  EDMVertexToken;  // vertex
    edm::EDGetTokenT< double >                  EDMRhoToken;     //  pileup density
    edm::EDGetTokenT< pat::JetCollection >      EDMAK15JetsToken_;

    const int    minJetsAK4_;
    const int    minJetsAK8_;
    const int    minJetsAK15_;
    const int    maxJetsAK4_;
    const int    maxJetsAK8_;
    const int    maxJetsAK15_;
    const double AK4jetPtMin_;
    const double AK4jetEtaMax_;
    const double AK8jetPtMin_;
    const double AK8jetEtaMax_;
    const double muonPtMin_;
    const double muonEtaMax_;
    const double electronPtMin_;
    const double electronEtaMax_;
    const double photonPtMin_;
    const double photonEtaMax_;
    const double metPtMin_;

    const bool isData;
};

//
// constructors and destructor
//
LeptonJetsSkim::LeptonJetsSkim(const edm::ParameterSet& iConfig) :
    // now do what ever initialization is needed

    EDMElectronsToken{consumes< pat::ElectronCollection >(iConfig.getParameter< edm::InputTag >("electrons"))},
    EDMMuonsToken{consumes< pat::MuonCollection >(iConfig.getParameter< edm::InputTag >("muons"))},
    EDMPhotonsToken{consumes< std::vector< pat::Photon > >(iConfig.getParameter< edm::InputTag >("photons"))},
    EDMAK4JetsToken{consumes< pat::JetCollection >(iConfig.getParameter< edm::InputTag >("AK4jets"))},
    EDMAK8JetsToken{consumes< pat::JetCollection >(iConfig.getParameter< edm::InputTag >("AK8jets"))},
    EDMMETToken{consumes< std::vector< pat::MET > >(iConfig.getParameter< edm::InputTag >("met"))},
    EDMPuppiMETToken{consumes< std::vector< pat::MET > >(iConfig.getParameter< edm::InputTag >("met_puppi"))},
    EDMVertexToken{consumes< reco::VertexCollection >(iConfig.getParameter< edm::InputTag >("vertices"))},
    EDMRhoToken{consumes< double >(iConfig.getParameter< edm::InputTag >("rho"))},
    EDMAK15JetsToken_{consumes< pat::JetCollection >(iConfig.getParameter< edm::InputTag >("AK15jets"))},

    minJetsAK4_{iConfig.getParameter< int >("minJetsAK4")},
    minJetsAK8_{iConfig.getParameter< int >("minJetsAK8")},
    minJetsAK15_{iConfig.getParameter< int >("minJetsAK15")},
    maxJetsAK4_{iConfig.getParameter< int >("maxJetsAK4")},
    maxJetsAK8_{iConfig.getParameter< int >("maxJetsAK8")},
    maxJetsAK15_{iConfig.getParameter< int >("maxJetsAK15")},
    AK4jetPtMin_{iConfig.getParameter< double >("AK4jetPtMin")},
    AK4jetEtaMax_{iConfig.getParameter< double >("AK4jetEtaMax")},
    AK8jetPtMin_{iConfig.getParameter< double >("AK8jetPtMin")},
    AK8jetEtaMax_{iConfig.getParameter< double >("AK8jetEtaMax")},

    muonPtMin_{iConfig.getParameter< double >("muonPtMin")},
    muonEtaMax_{iConfig.getParameter< double >("muonEtaMax")},
    electronPtMin_{iConfig.getParameter< double >("electronPtMin")},
    electronEtaMax_{iConfig.getParameter< double >("electronEtaMax")},
    photonPtMin_{iConfig.getParameter< double >("photonPtMin")},
    photonEtaMax_{iConfig.getParameter< double >("photonEtaMax")},

    metPtMin_{iConfig.getParameter< double >("metPtMin")},

    isData{iConfig.getParameter< bool >("isData")}

{
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
bool LeptonJetsSkim::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    // get slimmedElectrons
    edm::Handle< pat::ElectronCollection > hElectrons;
    iEvent.getByToken(EDMElectronsToken, hElectrons);

    // select those electrons satifsying pt and eta cuts
    std::vector< pat::Electron > selectedElectrons = *hElectrons;
    selectedElectrons.erase(std::remove_if(selectedElectrons.begin(), selectedElectrons.end(),
                                           [&](pat::Electron ele) {
                                               return !(ele.pt() >= electronPtMin_ && fabs(ele.eta()) <= electronEtaMax_ &&
                                                        ele.electronID("cutBasedElectronID-Fall17-94X-V2-loose"));
                                           }),
                            selectedElectrons.end());

    // get slimmedMuons
    edm::Handle< pat::MuonCollection > hMuons;
    iEvent.getByToken(EDMMuonsToken, hMuons);

    // select those muons satisfying pt and eta cuts
    std::vector< pat::Muon > selectedMuons = *hMuons;
    selectedMuons.erase(
        std::remove_if(selectedMuons.begin(), selectedMuons.end(),
                       [&](pat::Muon mu) {
                           return !(mu.pt() >= muonPtMin_ && fabs(mu.eta()) <= muonEtaMax_ && muon::isLooseMuon(mu) && mu.passed(pat::Muon::PFIsoLoose));
                       }),
        selectedMuons.end());

    // get slimmedPhotons
    edm::Handle< pat::PhotonCollection > hPhotons;
    iEvent.getByToken(EDMPhotonsToken, hPhotons);

    // select those photons satisfying pt and eta cuts
    std::vector< pat::Photon > selectedPhotons = *hPhotons;
    selectedPhotons.erase(
        std::remove_if(selectedPhotons.begin(), selectedPhotons.end(),
                       [&](pat::Photon ph) {
                           return !(ph.pt() >= photonPtMin_ && fabs(ph.eta()) <= photonEtaMax_ && ph.photonID("cutBasedPhotonID-Fall17-94X-V2-loose"));
                       }),
        selectedPhotons.end());

    // get AK4 jets
    edm::Handle< pat::JetCollection > ak4Jets;
    iEvent.getByToken(EDMAK4JetsToken, ak4Jets);

    // get AK8 jets
    edm::Handle< pat::JetCollection > ak8Jets;
    iEvent.getByToken(EDMAK8JetsToken, ak8Jets);

    // get AK15 jets
    edm::Handle< pat::JetCollection > ak15Jets;
    iEvent.getByToken(EDMAK15JetsToken_, ak15Jets);

    // get slimmedMETs CHS
    edm::Handle< std::vector< pat::MET > > hMETs;
    iEvent.getByToken(EDMMETToken, hMETs);

    // get slimmedMETs Puppi
    edm::Handle< std::vector< pat::MET > > hPuppiMETs;
    iEvent.getByToken(EDMPuppiMETToken, hPuppiMETs);

    int n_ak4jets  = 0;
    int n_ak8jets  = 0;
    int n_ak15jets = 0;

    // count ak4 and ak8 jets satisfying pt and eta cuts
    // n_ak4jets = std::count_if(ak4Jets->begin(),ak4Jets->end(),[&](pat::Jet
    // jet){return (jet.pt()>=AK4jetPtMin_ && fabs(jet.eta())<=AK4jetEtaMax_);});
    n_ak4jets = ak4Jets->size();
    // n_ak8jets = std::count_if(ak8Jets->begin(),ak8Jets->end(),[&](pat::Jet
    // jet){return (jet.pt()>=AK8jetPtMin_ && fabs(jet.eta())<=AK8jetEtaMax_);});
    n_ak8jets  = ak8Jets->size();
    n_ak15jets = ak15Jets->size();

    bool jet_veto_criterium = n_ak4jets < minJetsAK4_ && n_ak8jets < minJetsAK8_ && n_ak15jets < minJetsAK15_;

    // apply skimming selection
    if (jet_veto_criterium) return false;

    // number of leptons (electrons and muons)
    int n_electrons = selectedElectrons.size();
    int n_muons     = selectedMuons.size();
    int n_leptons   = n_electrons + n_muons;

    // leading lepton pts
    auto leading_ele_pt    = n_electrons > 0 ? selectedElectrons.at(0).pt() : 0.;
    auto leading_muon_pt   = n_muons > 0 ? selectedMuons.at(0).pt() : 0.;
    auto leading_lepton_pt = leading_ele_pt > leading_muon_pt ? leading_ele_pt : leading_muon_pt;
    auto leading_jet_pt    = n_ak4jets > 0 ? ak4Jets->at(0).pt() : 0.;

    // calculate approximate hadronic recoil
    auto hadr_recoil = hMETs->at(0).p4();

    auto hadr_recoil_puppi = hPuppiMETs->at(0).p4();

    for (const auto& ele : selectedElectrons) {
        hadr_recoil += ele.p4();
        hadr_recoil_puppi += ele.p4();
    }
    for (const auto& mu : selectedMuons) {
        hadr_recoil += mu.p4();
        hadr_recoil_puppi += mu.p4();
    }
    for (const auto& ph : selectedPhotons) {
        hadr_recoil += ph.p4();
        hadr_recoil_puppi += ph.p4();
    }

    // veto criterium for hadronic channel which can only be circumvented by leptonic events, see next criterium
    bool met_recoil_veto_criterium =
        (hMETs->at(0).pt() < metPtMin_) && (hPuppiMETs->at(0).pt() < metPtMin_) && (hadr_recoil.pt() < metPtMin_) && (hadr_recoil_puppi.pt() < metPtMin_);

    // criterium which lowers requested MET value for events in the leptonic channel
    bool lepton_jet_met_criterium =
        (n_leptons == 1) && (n_ak4jets > 0) && (leading_jet_pt > 50.) && (leading_lepton_pt > 20.) && (hMETs->at(0).pt() > 50. || hPuppiMETs->at(0).pt() > 50.);

    // if (n_ak4jets > maxJetsAK4_ || n_ak8jets > maxJetsAK8_ || n_ak15jets > maxJetsAK15_) return false;
    // met selection in general
    if (met_recoil_veto_criterium && !lepton_jet_met_criterium) return false;

    //     std::cout << "Number of AK4 jets: " << n_ak4jets << std::endl;
    //     std::cout << "Number of AK8 jets: " << n_ak8jets << std::endl;
    //     std::cout << "Number of AK15 jets: " << n_ak15jets << std::endl;
    //     std::cout << "MET: " << hMETs->at(0).pt() << std::endl;
    //     std::cout << "Puppi MET: " << hPuppiMETs->at(0).pt() << std::endl;
    //     std::cout << "Hadronic recoil: " << hadr_recoil.pt() << std::endl;
    //     std::cout << "Puppi Hadronic recoil: " << hadr_recoil_puppi.pt() <<
    //     std::endl; std::cout << "Number of selected electrons: " <<
    //     selectedElectrons.size() << std::endl; std::cout << "Number of selected
    //     muons: " << selectedMuons.size() << std::endl; std::cout << "Number of
    //     selected photons: " << selectedPhotons.size() << std::endl;

    return true;
}

// ------------ method called once each job just before starting event loop
// ------------
void LeptonJetsSkim::beginJob() {}

// ------------ method called once each job just after ending the event loop
// ------------
void LeptonJetsSkim::endJob() {}

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
void LeptonJetsSkim::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
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
