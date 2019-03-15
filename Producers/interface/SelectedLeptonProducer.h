// -*- C++ -*-
//
// Package:    BoostedTTH/ObjectSelectors
// Class:      SelectedLeptonProducer
//
/**\class SelectedLeptonProducer SelectedLeptonProducer.cc BoostedTTH/BoostedProducer/plugins/SelectedLeptonProducer.cc
 * 
 * Description: [one line class summary]
 * 
 * Implementation:
 *     [Notes on implementation]
 */
//
// Original Author:  Matthias Schroeder
//         Created:  Tue, 15 Sep 2015 11:58:04 GMT
//
//

#ifndef SelectedLeptonProducer_h
#define SelectedLeptonProducer_h

// system include files
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "TRandom3.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"
//#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "TH2F.h"
#include "TFile.h"

#include "BoostedTTH/Producers/src/RoccoR.cc" // this is needed to calculate the correction factors of the rochester correction
//
// class declaration
//

class SelectedLeptonProducer : public edm::EDProducer {
public:
    explicit SelectedLeptonProducer(const edm::ParameterSet&);
    ~SelectedLeptonProducer();
    
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    
    // some enums to make things nicer
    enum class LeptonType    {Electron, Muon};
    enum class ElectronID    {None, Veto, Loose, Medium, Tight};
    enum class MuonID        {None, Loose, Medium, Tight};
    enum class IsoConeSize      {R03, R04};
    enum class IsoCorrType      {rhoEA, deltaBeta};
    enum class MuonIsolation {None, Loose, Medium, Tight};
    
    
    // Function to sort leptons by pt
    template <typename T> T GetSortedByPt(const T&);
    
    // Functions to return an electron collection with the desired properties
    std::vector<pat::Electron> GetSelectedElectrons(const std::vector<pat::Electron>& inputElectrons, const double iMinPt = 10., const ElectronID = ElectronID::Loose, const double iMaxEta = 2.4) const;
    bool isGoodElectron(const pat::Electron& iElectron, const double iMinPt = 10., const double iMaxEta = 2.4, const ElectronID iElectronID = ElectronID::Loose) const;
    
    // Function to calculate electron relative isolation manually, for sync exercises
    double GetEletronRelIsolation(const pat::Electron& inputElectron, const IsoCorrType icorrType = IsoCorrType::rhoEA, const IsoConeSize iconeSize = IsoConeSize::R03) const;
    void AddElectronRelIsolation(std::vector<pat::Electron>& inputElectrons, const IsoCorrType icorrType = IsoCorrType::rhoEA, const IsoConeSize iconeSize = IsoConeSize::R03);
    
    // Functions to add object scale factors to electrons meaning reconstruction and identification scale factors
    void AddElectronSFs(std::vector<pat::Electron>& inputElectrons, const ElectronID iElectronID) const;
    std::vector<float> GetElectronIDSF(const pat::Electron& iElectron, const ElectronID iElectronID) const;
    std::vector<float> GetElectronRecoSF(const pat::Electron& iElectron) const;
    
    // Functions to return a muon collection with the desired properties
    std::vector<pat::Muon> GetSelectedMuons(const std::vector<pat::Muon>& inputMuons, const double iMinPt = 10., const MuonID = MuonID::Loose, const IsoConeSize = IsoConeSize::R04, const IsoCorrType = IsoCorrType::deltaBeta, const double iMaxEta = 2.4, const MuonIsolation = MuonIsolation::Loose) const;
    bool isGoodMuon(const pat::Muon&, const double iMinPt = 10., const double iMaxEta = 2.4, const MuonID = MuonID::Loose, const IsoConeSize = IsoConeSize::R04, const IsoCorrType = IsoCorrType::deltaBeta, const MuonIsolation = MuonIsolation::Loose) const;
    
    // Function to calculate muon relative isolation manually, for sync exercises
    double GetMuonRelIsolation(const pat::Muon& inputMuon, const IsoCorrType icorrType = IsoCorrType::deltaBeta, const IsoConeSize iconeSize = IsoConeSize::R04) const;
    void AddMuonRelIsolation(std::vector<pat::Muon>& inputMuons, const IsoCorrType icorrType = IsoCorrType::deltaBeta, const IsoConeSize iconeSize = IsoConeSize::R04);
    
    // Function to apply the muon rochester correction to a given muon collection
    void ApplyMuonMomentumCorrection(std::vector<pat::Muon>& inputMuons);
    
private:
    
    virtual void beginJob() override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    
    // ----------member data ---------------------------
    // type of lepton (electron or muon) and names of the collections to create
    const std::string leptonType;
    LeptonType leptonType_;
    const std::vector<std::string> collectionNames_;
    
    // lepton selection criteria
    const std::vector<double> ptMins_;
    const std::vector<double> etaMaxs_;    
    const std::vector<std::string> leptonIDs;
    const std::vector<std::string> isoConeSizes;
    const std::vector<std::string> isoCorrTypes;
    const std::vector<std::string> muonIsoTypes;
    
    const std::string era;
    
    // flags used for muon Rochester correction
    const bool isData;
    const bool useMuonRC;                                           // flag to enable or disable Rochester Correction
    const bool deterministicSeeds;                                  // flag to enable or disable deterministic seeds for RC
    
    // lepton selection criteria
    std::vector<MuonID> muonIDs_;
    std::vector<ElectronID> electronIDs_;
    std::vector<IsoConeSize> IsoConeSizes_;
    std::vector<IsoCorrType> IsoCorrTypes_;
    std::vector<MuonIsolation> muonIsos_;
    
    // Object to calculate Rochester Correction
    RoccoR rc;
    
    // Object to get electron effective areas
    EffectiveAreas EA;
    
    // data access tokens
    // pileup density
    edm::EDGetTokenT< double >                  EDMRhoToken; 
    // vertex collection
    edm::EDGetTokenT< reco::VertexCollection >  EDMVertexToken;
    // muons
    edm::EDGetTokenT< pat::MuonCollection >     EDMMuonsToken;  
    // electrons
    edm::EDGetTokenT< pat::ElectronCollection >EDMElectronsToken;
    
    // primary vertex
    reco::Vertex vertex;
    
    // event-specific average pile-up energy density per unit area in the phi-eta plane
    double rho;
    
    // ptrs to 2D histograms which contain the electron scale factors for reconstruction and identification
    TH2F* EleID_SF_Loose = nullptr;
    TH2F* EleID_SF_Medium = nullptr;
    TH2F* EleID_SF_Tight = nullptr;
    TH2F* EleReco_SF_highPt = nullptr;
    TH2F* EleReco_SF_lowPt = nullptr;
    
    
};
#endif
