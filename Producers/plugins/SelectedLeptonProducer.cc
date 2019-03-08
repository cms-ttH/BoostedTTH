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
    std::vector<std::string> collectionNames_;
    
    // lepton selection criteria
    const std::vector<double> ptMins_;
    const std::vector<double> etaMaxs_;    
    const std::vector<std::string > leptonIDs;
    const std::vector<std::string> isoConeSizes;
    const std::vector<std::string> isoCorrTypes;
    const std::vector<std::string> muonIsoTypes;
    
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
    
    
};



// constructor with initializer list for all inputs which are obtained from the config
SelectedLeptonProducer::SelectedLeptonProducer(const edm::ParameterSet& iConfig) :  leptonType{iConfig.getParameter<std::string>("leptonType")},
                                                                                    collectionNames_{iConfig.getParameter<std::vector< std::string> >("collectionNames")},
                                                                                    ptMins_{iConfig.getParameter< std::vector<double> >("ptMins")},
                                                                                    etaMaxs_{iConfig.getParameter< std::vector<double> >("etaMaxs")},
                                                                                    leptonIDs{iConfig.getParameter< std::vector<std::string> >("leptonIDs")},
                                                                                    isoConeSizes{iConfig.getParameter<std::vector<std::string> >("isoConeSizes")},
                                                                                    isoCorrTypes{iConfig.getParameter<std::vector<std::string> >("isoCorrTypes")},
                                                                                    muonIsoTypes{iConfig.getParameter<std::vector<std::string> >("muonIsoTypes")},
                                                                                    isData{iConfig.getParameter<bool>("isData")},
                                                                                    useMuonRC{iConfig.getParameter<bool>("useMuonRC")},
                                                                                    deterministicSeeds{iConfig.getParameter<bool>("useDeterministicSeeds")},
                                                                                    rc{std::string(getenv("CMSSW_BASE"))+"/src/"+iConfig.getParameter<std::string>("rc_dir")},
                                                                                    EA{std::string(getenv("CMSSW_BASE"))+"/src/"+iConfig.getParameter<std::string>("ea_dir")},

                                                                                    // inputs
                                                                                    EDMRhoToken{consumes< double >                  (iConfig.getParameter<edm::InputTag>("rho"))},
                                                                                    EDMVertexToken{consumes< reco::VertexCollection >  (iConfig.getParameter<edm::InputTag>("vertices"))},
                                                                                    EDMMuonsToken{consumes< pat::MuonCollection >     (iConfig.getParameter<edm::InputTag>("leptons"))},
                                                                                    EDMElectronsToken{consumes< pat::ElectronCollection >(iConfig.getParameter<edm::InputTag>("leptons"))}
                                                                                    
{
    // setup of producer
    if(      leptonType == "electron" ) leptonType_ = LeptonType::Electron;
    else if( leptonType == "muon"     ) leptonType_ = LeptonType::Muon;
    else {
        std::cerr << "\n\nERROR: Unknown lepton type " << leptonType << std::endl;
        std::cerr << "Please select 'electron' or 'muon'\n" << std::endl;
        throw std::exception();
    }
    
    
    
    // fill lepton selection criteria with default values
    electronIDs_        = std::vector<ElectronID>(leptonIDs.size(),ElectronID::Loose);
    muonIDs_            = std::vector<MuonID>(leptonIDs.size(),MuonID::Loose);
    IsoConeSizes_       = std::vector<IsoConeSize>(leptonIDs.size(),IsoConeSize::R03);
    IsoCorrTypes_       = std::vector<IsoCorrType>(leptonIDs.size(),IsoCorrType::rhoEA);
    muonIsos_           = std::vector<MuonIsolation>(leptonIDs.size(), MuonIsolation::Loose);
    
    // some safety guards
    assert(ptMins_.size()==etaMaxs_.size());
    assert(leptonIDs.size()==etaMaxs_.size());
    assert(collectionNames_.size()==etaMaxs_.size());
    assert(isoConeSizes.size()==etaMaxs_.size());
    assert(isoCorrTypes.size()==etaMaxs_.size());
    if(leptonType_==LeptonType::Muon) assert(muonIsoTypes.size()==etaMaxs_.size());
    
    // translate strings from config to nice C++ objects
    for(size_t i=0; i<ptMins_.size(); i++){
        if(leptonType_ == LeptonType::Electron){
            if(      leptonIDs[i] == "loose"   )         electronIDs_[i] = ElectronID::Loose;
            else if( leptonIDs[i] == "medium"  )         electronIDs_[i] = ElectronID::Medium;
            else if( leptonIDs[i] == "tight"   )         electronIDs_[i] = ElectronID::Tight;
            else if( leptonIDs[i] == "veto"   )          electronIDs_[i] = ElectronID::Veto;
            else if( leptonIDs[i] == "none"   )          electronIDs_[i] = ElectronID::None;
            else {
                std::cerr << "\n\nERROR: No matching electron ID type found for: " << leptonIDs[i] << std::endl;
                throw std::exception();
            }
        }
        if(leptonType_ == LeptonType::Muon){
            if(      leptonIDs[i] == "loose"  )   muonIDs_[i] = MuonID::Loose;
            else if( leptonIDs[i] == "medium"  )   muonIDs_[i] = MuonID::Medium;
            else if( leptonIDs[i] == "tight"  )   muonIDs_[i] = MuonID::Tight;
            else if( leptonIDs[i] == "none"  )   muonIDs_[i] = MuonID::None;
            else{
                std::cerr << "\n\nERROR: No matching muon ID type found for: " << leptonIDs[i] << std::endl;
                throw std::exception();
            }
           
            if(      muonIsoTypes[i] == "loose"  )   muonIsos_[i] = MuonIsolation::Loose;
            else if( muonIsoTypes[i] == "medium"  )   muonIsos_[i] = MuonIsolation::Medium;
            else if( muonIsoTypes[i] == "tight"  )   muonIsos_[i] = MuonIsolation::Tight;
            else if( muonIsoTypes[i] == "none"  )   muonIsos_[i] = MuonIsolation::None;
            else{
                std::cerr << "\n\nERROR: No matching muon isolation type found for: " << muonIsoTypes[i] << std::endl;
                throw std::exception();
            }
        }
        
        if(      isoConeSizes[i] == "R03"  ) IsoConeSizes_[i] = IsoConeSize::R03;
        else if( isoConeSizes[i] == "R04"  ) IsoConeSizes_[i] = IsoConeSize::R04;
        else {
            std::cerr << "\n\nERROR: No matching isolation cone size found for: " << isoConeSizes[i] << std::endl;
            throw std::exception();
        }
        
        if(      isoCorrTypes[i] == "deltaBeta" ) IsoCorrTypes_[i] = IsoCorrType::deltaBeta;
        else if( isoCorrTypes[i] == "rhoEA"     ) IsoCorrTypes_[i] = IsoCorrType::rhoEA;
        else {
            std::cerr << "\n\nERROR: No matching isolation correction type found for: " << isoCorrTypes[i] << std::endl;
            throw std::exception();
        }
        
        if( leptonType_ == LeptonType::Electron ) produces<pat::ElectronCollection>(collectionNames_[i]);
        else if( leptonType_ == LeptonType::Muon     ) produces<pat::MuonCollection>(collectionNames_[i]);
        else {
            std::cerr << "\n\nERROR: Unknown lepton type " << leptonType << std::endl;
            std::cerr << "Please select 'electron' or 'muon'\n" << std::endl;
            throw std::exception();
        }
        
    }
}

// destructor
SelectedLeptonProducer::~SelectedLeptonProducer() {}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
SelectedLeptonProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    // get the vertices and the rho (average pile-up energy density per unit area in the phi-eta plane)
    edm::Handle<reco::VertexCollection> hVtxs;
    iEvent.getByToken(EDMVertexToken,hVtxs);
    if(not hVtxs.isValid()) {
        std::cerr << "\n\nERROR: retrieved vertex collection is not valid" << std::endl;
        throw std::exception();
    }
    else if(not (hVtxs->size()>0)) {
        std::cerr << "\n\nERROR: retrieved vertex collection is empty" << std::endl;
        throw std::exception();
    }
    // primary vertex
    vertex = hVtxs->at(0);
    
    edm::Handle<double> hRho;
    iEvent.getByToken(EDMRhoToken,hRho);
    if(not hRho.isValid()) {
        std::cerr << "\n\nERROR: retrieved pile-up energy density is not valid" << std::endl;
        throw std::exception();
    }
    //pile-up density
    rho = *hRho;
    
    if( leptonType_ == LeptonType::Electron ) {
        // get input electron collection
        edm::Handle< pat::ElectronCollection > inputElectrons;
        iEvent.getByToken(EDMElectronsToken,inputElectrons);
        if(not inputElectrons.isValid()) {
            std::cerr << "\n\nERROR: retrieved electron collection is not valid" << std::endl;
            throw std::exception();
        }
        
        
        for(size_t i=0; i<ptMins_.size(); i++)
        {
            std::vector<pat::Electron> updatedElectrons = *inputElectrons;
            
            // add the electron relative isolation as a userfloat, mainly for sync by now
            AddElectronRelIsolation(updatedElectrons,IsoCorrTypes_[i],IsoConeSizes_[i]);
            
            // apply energy corrections (scale & smearing)
            for(auto& ele : updatedElectrons){
                ele.addUserFloat("ptBeforeRun2Calibration",ele.pt());
                ele.setP4(ele.p4()*ele.userFloat("ecalTrkEnergyPostCorr")/ele.energy());
                // only use combined systematics for scaling and smearing since we should not be very sensitive to electron energy scale
                // as recommended by e/gamma pog only for MC
                if(not isData){
                    ele.addUserFloat("CorrFactor_ScaleUp",ele.userFloat("energyScaleUp")/ele.userFloat("ecalTrkEnergyPostCorr"));
                    ele.addUserFloat("CorrFactor_ScaleDown",ele.userFloat("energyScaleDown")/ele.userFloat("ecalTrkEnergyPostCorr"));
                    ele.addUserFloat("CorrFactor_SigmaUp",ele.userFloat("energySigmaUp")/ele.userFloat("ecalTrkEnergyPostCorr"));
                    ele.addUserFloat("CorrFactor_SigmaDown",ele.userFloat("energySigmaDown")/ele.userFloat("ecalTrkEnergyPostCorr"));
                }
            }
            
            // produce the different electron collections and create a unique ptr to it      
            std::unique_ptr<pat::ElectronCollection> selectedLeptons =  std::make_unique<pat::ElectronCollection>(
                                                                        GetSortedByPt(
                                                                        GetSelectedElectrons(updatedElectrons,ptMins_[i],electronIDs_[i],etaMaxs_[i])));
            // put the collection into the event with help of the unique ptr
            iEvent.put(std::move(selectedLeptons),collectionNames_[i]);
        }

    }
    
    else if( leptonType_ == LeptonType::Muon ) {
        
        // get input muon collection
        edm::Handle<pat::MuonCollection> inputMuons;
        iEvent.getByToken(EDMMuonsToken,inputMuons);
        if(not inputMuons.isValid()) {
            std::cerr << "\n\nERROR: retrieved muon collection is not valid" << std::endl;
            throw std::exception();
        }
        std::vector<pat::Muon> correctedMuons = *inputMuons;        
        // if the flag is set, apply the muon momentum correction (rochester correction)
        if(useMuonRC) {
            ApplyMuonMomentumCorrection(correctedMuons);
        }
        
        
        // produce the different muon collections
        for(size_t i=0; i<ptMins_.size();i++){
            std::vector<pat::Muon> updatedMuons = correctedMuons;
            // add the muon relative isolation as a userfloat, mainly for sync by now
            AddMuonRelIsolation(updatedMuons,IsoCorrTypes_[i],IsoConeSizes_[i]);
            // produce the different muon collections and create a unique ptr to it      
            std::unique_ptr<pat::MuonCollection> selectedLeptons =  std::make_unique<pat::MuonCollection>(
                                                                    GetSortedByPt( 
                                                                    GetSelectedMuons(updatedMuons,ptMins_[i],muonIDs_[i],IsoConeSizes_[i],IsoCorrTypes_[i],etaMaxs_[i],muonIsos_[i]))) ;
            // put the collection into the event with help of the unique ptr
            iEvent.put(std::move(selectedLeptons),collectionNames_[i]);
        }
    }
    else {
        std::cerr << "\n\nERROR: Unknown lepton type " << leptonType << std::endl;
        std::cerr << "Please select 'electron' or 'muon'\n" << std::endl;
        throw std::exception();
    }
}
// template function to sort a collection by pt and return the sorted collection, should work with pat::Muon and pat::Electron collections and probably more
template <typename T> T SelectedLeptonProducer::GetSortedByPt(const T& collection){
    T result = collection;
    std::sort(result.begin(), result.end(), [] (typename T::value_type a, typename T::value_type b) { return a.pt() > b.pt();});
    return result;
}
// function to select electrons with several properties and return a collection
std::vector<pat::Electron>
SelectedLeptonProducer::GetSelectedElectrons(const std::vector<pat::Electron>& inputElectrons, const double iMinPt, const ElectronID iElectronID, const double iMaxEta) const{
    
    std::vector<pat::Electron> selectedElectrons;
    
    for(const auto& ele : inputElectrons){
        if(isGoodElectron(ele,iMinPt,iMaxEta,iElectronID)) 
        {
            selectedElectrons.push_back(ele);
        }
    }
    
    return selectedElectrons;
}
// function to check whether an electron fulfills several requirements
bool
SelectedLeptonProducer::isGoodElectron(const pat::Electron& iElectron, const double iMinPt, const double iMaxEta,const ElectronID iElectronID) const{
    bool passesKinematics = (iMinPt<=iElectron.pt()) and (iMaxEta>=fabs(iElectron.eta()));
    bool inCrack = false;
    bool passesIPcuts = false;
    bool passesID = false;
    
    double absSCeta = 999; 
    if( iElectron.superCluster().isAvailable() ){
        absSCeta = fabs(iElectron.superCluster()->position().eta());
        inCrack = (absSCeta>1.4442 and absSCeta<1.5660 );
    }
    double IP_d0 = 999;
    double IP_dZ = 999;

    bool isEB = absSCeta < 1.479; //check if electron is in barrel region
    if( iElectron.gsfTrack().isAvailable() ){
        IP_d0 = fabs(iElectron.gsfTrack()->dxy(vertex.position()));
        IP_dZ = fabs(iElectron.gsfTrack()->dz(vertex.position()));
    }
    
    //if impact parameter cuts are not met, set passesIPcuts = false
    if( isEB ) passesIPcuts = (IP_d0 < 0.05 and IP_dZ < 0.1);
    else passesIPcuts = (IP_d0 < 0.1 and IP_dZ < 0.2);
    
    switch(iElectronID){
        case ElectronID::None:
            passesID = true;
            break;
        case ElectronID::Veto:
            passesID = iElectron.electronID("cutBasedElectronID-Fall17-94X-V2-veto");
            break;
        case ElectronID::Loose:
            passesID = iElectron.electronID("cutBasedElectronID-Fall17-94X-V2-loose");
            break;
        case ElectronID::Medium:
            passesID = iElectron.electronID("cutBasedElectronID-Fall17-94X-V2-medium");
            break;
        case ElectronID::Tight:
            passesID = iElectron.electronID("cutBasedElectronID-Fall17-94X-V2-tight");
            break;
        default:
            std::cerr << "\n\nERROR: InvalidElectronID" <<  std::endl;
            throw std::exception();
    }
    
    return passesKinematics and (not inCrack) and passesIPcuts and passesID;
}
// function to calculate electron relative isolation by hand. Mainly needed for sync purposes since isolations are part of other provided electron properties like ID
double SelectedLeptonProducer::GetEletronRelIsolation(const pat::Electron& inputElectron, const IsoCorrType icorrType, const IsoConeSize iconeSize) const {
    double isoChargedHadrons = inputElectron.pfIsolationVariables().sumChargedHadronPt;
    double isoNeutralHadrons = inputElectron.pfIsolationVariables().sumNeutralHadronEt;
    double isoPhotons = inputElectron.pfIsolationVariables().sumPhotonEt;
    double pileup = 0;
    if(iconeSize == IsoConeSize::R03) {
        if(icorrType == IsoCorrType::deltaBeta) pileup = 0.5*inputElectron.pfIsolationVariables().sumPUPt;
        else if(icorrType == IsoCorrType::rhoEA) {
            double eta = 0.;
            if( inputElectron.superCluster().isAvailable() ){
                eta = fabs(inputElectron.superCluster()->position().eta());
            }
            else {
                eta = fabs(inputElectron.eta());
            }
            pileup = rho*EA.getEffectiveArea(eta);
        }
        else {
            std::cerr << "\n\nERROR: invalid electron isolation correction type" << std::endl;
            throw std::exception();
        }
    }
    else {
        std::cerr << "\n\nERROR: electron isolation is not implemeted for conesizes other than 0.3" << std::endl;
        throw std::exception();
    }
    return (isoChargedHadrons+std::max(0.,isoNeutralHadrons+isoPhotons-pileup))/inputElectron.pt();
}
// function to add the calculate electron relative isolation to the electron as a userfloat
void SelectedLeptonProducer::AddElectronRelIsolation(std::vector<pat::Electron>& inputElectrons, const IsoCorrType icorrType, const IsoConeSize iconeSize) {
    for(auto& ele : inputElectrons){
        ele.addUserFloat("relIso",GetEletronRelIsolation(ele, icorrType, iconeSize));
    }
}
// function to select muons with several properties and return a collection
std::vector<pat::Muon>
SelectedLeptonProducer::GetSelectedMuons(const std::vector<pat::Muon>& inputMuons, const double iMinPt, const MuonID iMuonID, const IsoConeSize iconeSize, const IsoCorrType icorrType, const double iMaxEta, const MuonIsolation imuonIso) const{
    
    
    std::vector<pat::Muon> selectedMuons;
    
    for(const auto& mu : inputMuons){
        if(isGoodMuon(mu,iMinPt,iMaxEta,iMuonID,iconeSize,icorrType, imuonIso)) 
        {
            selectedMuons.push_back(mu);
        }
    }
    
    return selectedMuons;
}
// function to check whether a muon fulfills several requirements
bool
SelectedLeptonProducer::isGoodMuon(const pat::Muon& iMuon, const double iMinPt, const double iMaxEta, const MuonID iMuonID, const IsoConeSize iconeSize, const IsoCorrType icorrType, const MuonIsolation imuonIso) const{
    bool passesKinematics = (iMinPt<=iMuon.pt()) and (iMaxEta>=fabs(iMuon.eta()));
    bool passesID = false;
    bool passesIso = false;
    switch(iMuonID){
        case MuonID::None:
            passesID         = true;
            break;
        case MuonID::Loose:
            passesID         = muon::isLooseMuon(iMuon);
            break;
        case MuonID::Medium:
            passesID         = muon::isMediumMuon(iMuon);
            break;
        case MuonID::Tight:
            passesID         = muon::isTightMuon(iMuon, vertex);
            break;
        default:
            std::cerr << "\n\nERROR: InvalidMuonID" <<  std::endl;
            throw std::exception();

    }
    switch(imuonIso){
        case MuonIsolation::None:
            passesIso         = true;
            break;
        case MuonIsolation::Loose:
            passesIso         = iMuon.passed(pat::Muon::PFIsoLoose);
            break;
        case MuonIsolation::Medium:
            passesIso         = iMuon.passed(pat::Muon::PFIsoMedium);
            break;
        case MuonIsolation::Tight:
            passesIso         = iMuon.passed(pat::Muon::PFIsoTight);
            break;
        default:
            std::cerr << "\n\nERROR: InvalidMuonIso" <<  std::endl;
            throw std::exception();

    }
    return passesKinematics and passesID and passesIso;
}
// function to apply muon momentum correction (rochester correction)
void SelectedLeptonProducer::ApplyMuonMomentumCorrection(std::vector<pat::Muon>& inputMuons){
    double momentum_sf;
    TRandom3 rnd;
    for(size_t i=0;i<inputMuons.size();i++) {
        momentum_sf=1.;
        if(deterministicSeeds) {
            int32_t seed = inputMuons[i].userInt("deterministicSeed");
            rnd.SetSeed((uint32_t)seed);
        }
        double r1 = rnd.Rndm();
        int trackerLayersWithMeasurement=0;
        if(!inputMuons[i].innerTrack().isNull()) {
            trackerLayersWithMeasurement = inputMuons[i].innerTrack()->hitPattern().trackerLayersWithMeasurement();
        }
        if(isData) {
            momentum_sf = rc.kScaleDT(inputMuons[i].charge(), inputMuons[i].pt(), inputMuons[i].eta(), inputMuons[i].phi(), 0, 0);
        }
        else {
            if(inputMuons[i].genLepton()) {
                momentum_sf = rc.kSpreadMC(inputMuons[i].charge(), inputMuons[i].pt(), inputMuons[i].eta(), inputMuons[i].phi(), inputMuons[i].genLepton()->pt(), 0, 0);
            }
            else {
                momentum_sf = rc.kSmearMC(inputMuons[i].charge(), inputMuons[i].pt(), inputMuons[i].eta(), inputMuons[i].phi(), trackerLayersWithMeasurement, r1, 0, 0);
            }
        }
        auto tmp_vector = inputMuons[i].p4();
        inputMuons[i].addUserFloat( "PtbeforeRC", tmp_vector.Pt());
        tmp_vector.SetPxPyPzE(momentum_sf*tmp_vector.Px(),momentum_sf*tmp_vector.Py(),momentum_sf*tmp_vector.Pz(),TMath::Sqrt((1+(tmp_vector.P2()/(tmp_vector.E()*tmp_vector.E())*(momentum_sf*momentum_sf-1))))*tmp_vector.E());
        inputMuons[i].setP4(tmp_vector);
    }
}
// function to calculate muon relative isolation by hand. Mainly needed for sync purposes since isolation-checks are provided centrally
double SelectedLeptonProducer::GetMuonRelIsolation(const pat::Muon& inputMuon, const IsoCorrType icorrType, const IsoConeSize iconeSize) const {
    double isoChargedHadrons = inputMuon.pfIsolationR04().sumChargedHadronPt;
    double isoNeutralHadrons = inputMuon.pfIsolationR04().sumNeutralHadronEt;
    double isoPhotons = inputMuon.pfIsolationR04().sumPhotonEt;
    double pileup = 0;
    if(iconeSize == IsoConeSize::R04) {
        if(icorrType == IsoCorrType::deltaBeta) pileup = 0.5*inputMuon.pfIsolationR04().sumPUPt;
        else {
            std::cerr << "\n\nERROR: muon isolation is not implemeted for pileup corrections other than deltaBeta" << std::endl;
            throw std::exception();
        }
    }
    else {
        std::cerr << "\n\nERROR: muon isolation is not implemeted for conesizes other than 0.4" << std::endl;
        throw std::exception();
    }
    return (isoChargedHadrons+std::max(0.,isoNeutralHadrons+isoPhotons-pileup))/inputMuon.pt();
}
// function to add the calculate muon relative isolation to the muon as a userfloat
void SelectedLeptonProducer::AddMuonRelIsolation(std::vector<pat::Muon>& inputMuons, const IsoCorrType icorrType, const IsoConeSize iconeSize) {
    for(auto& mu : inputMuons){
        mu.addUserFloat("relIso",GetMuonRelIsolation(mu, icorrType, iconeSize));
    }
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
