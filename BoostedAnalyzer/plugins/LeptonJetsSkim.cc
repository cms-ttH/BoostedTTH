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

#include "../interface/LeptonJetsSkim.hpp"

//
// constructors and destructor
//
LeptonJetsSkim::LeptonJetsSkim(const edm::ParameterSet &iConfig)
{
    //now do what ever initialization is needed
    era = iConfig.getParameter<std::string>("era");
    EDMElectronsToken = consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"));
    EDMMuonsToken = consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"));
    EDMJetsToken = consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets"));
    EDMVertexToken = consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"));
    EDMRhoToken = consumes<double>(iConfig.getParameter<edm::InputTag>("rho"));

    minJets_ = iConfig.getParameter<int>("minJets");
    jetPtMin_ = iConfig.getParameter<double>("jetPtMin");
    jetEtaMax_ = iConfig.getParameter<double>("jetEtaMax");
    muonPtMin_ = iConfig.getParameter<double>("muonPtMin");
    muonEtaMax_ = iConfig.getParameter<double>("muonEtaMax");
    electronPtMin_ = iConfig.getParameter<double>("electronPtMin");
    electronEtaMax_ = iConfig.getParameter<double>("electronEtaMax");

    electronID_ = SelectedLeptonProducer::ElectronID::None;
    muonID_ = SelectedLeptonProducer::MuonID::Loose;
    muonIso_ = SelectedLeptonProducer::MuonIsolation::Loose;
    muonIsoConeSize_ = SelectedLeptonProducer::IsoConeSize::R04;
    muonIsoCorrType_ = SelectedLeptonProducer::IsoCorrType::deltaBeta;
}

LeptonJetsSkim::~LeptonJetsSkim()
{

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)
}

//
// member functions
//

// function to select electrons with several properties and return a collection
std::vector<pat::Electron> LeptonJetsSkim::GetSelectedElectrons(const std::vector<pat::Electron> &inputElectrons,
                                                                const double iMinPt, const SelectedLeptonProducer::ElectronID iElectronID,
                                                                const double iMaxEta) const
{
    std::vector<pat::Electron> selectedElectrons;
    for (const auto &ele : inputElectrons)
    {
        if (SelectedLeptonProducer::isGoodElectron(ele, vertex, iMinPt, iMaxEta, iElectronID))
        {
            selectedElectrons.push_back(ele);
        }
    }
    return selectedElectrons;
}

// function to select muons with several properties and return a collection
std::vector<pat::Muon> LeptonJetsSkim::GetSelectedMuons(const std::vector<pat::Muon> &inputMuons, const double iMinPt,
                                                        const SelectedLeptonProducer::MuonID iMuonID,
                                                        const SelectedLeptonProducer::IsoConeSize iconeSize,
                                                        const SelectedLeptonProducer::IsoCorrType icorrType,
                                                        const double iMaxEta, const SelectedLeptonProducer::MuonIsolation imuonIso) const
{
    std::vector<pat::Muon> selectedMuons;
    for (const auto &mu : inputMuons)
    {
        if (SelectedLeptonProducer::isGoodMuon(mu, iMinPt, iMaxEta, iMuonID, iconeSize, icorrType, imuonIso, vertex))
        {
            selectedMuons.push_back(mu);
        }
    }
    return selectedMuons;
}

// function to return Jets, which fullfill all IDs
std::vector<pat::Jet> LeptonJetsSkim::GetSelectedJets(const std::vector<pat::Jet> &inputJets,
                                                      const float iMinPt, const float iMaxAbsEta,
                                                      const SelectedJetProducer::JetID iJetID,
                                                      const SelectedJetProducer::PUJetIDWP wp) const
{
    // iterate through inputjets and find good Jets
    std::vector<pat::Jet> selectedJets;
    for (auto &jet : inputJets)
    {
        if (SelectedJetProducer::isGoodJet(jet, iMinPt, iMaxAbsEta, iJetID, wp, era))
        {
            selectedJets.push_back(jet);
        }
    }
    return selectedJets;
}

// ------------ method called on each new Event  ------------
bool LeptonJetsSkim::filter(edm::Event &iEvent, const edm::EventSetup &iSetup)
{
    // get the vertices
    edm::Handle<reco::VertexCollection> hVtxs;
    iEvent.getByToken(EDMVertexToken, hVtxs);
    if (not hVtxs.isValid())
    {
        std::cerr << "\n\nERROR: retrieved vertex collection is not valid" << std::endl;
        throw std::exception();
    }
    else if (not(hVtxs->size() > 0))
    {
        std::cerr << "\n\nERROR: retrieved vertex collection is empty" << std::endl;
        throw std::exception();
    }
    // primary vertex
    vertex = hVtxs->at(0);

    // get rho (average pile-up energy density per unit area in the phi-eta plane)
    edm::Handle<double> hRho;
    iEvent.getByToken(EDMRhoToken, hRho);
    if (not hRho.isValid())
    {
        std::cerr << "\n\nERROR: retrieved pile-up energy density is not valid" << std::endl;
        throw std::exception();
    }
    //pile-up density
    rho = *hRho;

    // get input electron collection
    edm::Handle<pat::ElectronCollection> inputElectrons;
    iEvent.getByToken(EDMElectronsToken, inputElectrons);
    if (not inputElectrons.isValid())
    {
        std::cerr << "\n\nERROR: retrieved electron collection is not valid" << std::endl;
        throw std::exception();
    }
    // select electrons
    pat::ElectronCollection selectedElectrons = GetSelectedElectrons(*inputElectrons, electronPtMin_, electronID_, electronEtaMax_);

    // get input muon collection
    edm::Handle<pat::MuonCollection> inputMuons;
    iEvent.getByToken(EDMMuonsToken, inputMuons);
    if (not inputMuons.isValid())
    {
        std::cerr << "\n\nERROR: retrieved muon collection is not valid" << std::endl;
        throw std::exception();
    }
    pat::MuonCollection selectedMuons = GetSelectedMuons(*inputMuons, muonPtMin_, muonID_, muonIsoConeSize_, muonIsoCorrType_, muonEtaMax_, muonIso_);

    edm::Handle<pat::JetCollection> inputJets;
    iEvent.getByToken(EDMJetsToken, inputJets);
    if (not inputJets.isValid())
    {
        std::cerr << "\n\nERROR: retrieved jet collection is not valid" << std::endl;
        throw std::exception();
    }
    pat::JetCollection selectedJets = GetSelectedJets(*inputJets, jetPtMin_, jetEtaMax_, SelectedJetProducer::JetID::Tight, SelectedJetProducer::PUJetIDWP::none);
    // TODO: correct jets (maybe even with JESUP) to make sure the jetcuts are loose enough

    if ((selectedMuons.size() + selectedElectrons.size()) >= 1 && int(selectedJets.size()) > minJets_)
    {
        return true;
    }

    return false;
}

// ------------ method called once each job just before starting event loop  ------------
void LeptonJetsSkim::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void LeptonJetsSkim::endJob()
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
void LeptonJetsSkim::fillDescriptions(edm::ConfigurationDescriptions &descriptions)
{
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(LeptonJetsSkim);
