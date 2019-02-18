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
    enum class ElectronID    {Veto, Loose, Medium, Tight};
    enum class MuonID        {Loose, Medium, Tight};
    enum class IsoConeSize      {R03, R04};
    enum class IsoCorrType      {rhoEA, deltaBeta};
    enum class MuonIsolation {Loose, Medium, Tight};
    
    
    // Function to sort leptons by pt
    template <typename T> T GetSortedByPt(const T&);
    
    // Functions to return an electron collection with the desired properties
    std::vector<pat::Electron> GetSelectedElectrons(const std::vector<pat::Electron>& inputElectrons, const double iMinPt = 10., const ElectronID = ElectronID::Loose, const double iMaxEta = 2.4);
    bool isGoodElectron(const pat::Electron& iElectron, const double iMinPt = 10., const double iMaxEta = 2.4, const ElectronID iElectronID = ElectronID::Loose) const;
    // Function to calculate electron relative isolation manually
    double GetEletronRelIsolation(const pat::Electron& inputElectron, const IsoCorrType, const IsoConeSize) const;
    
    // Functions to return a muon collection with the desired properties
    std::vector<pat::Muon> GetSelectedMuons(const std::vector<pat::Muon>& inputMuons, const double iMinPt = 10., const MuonID = MuonID::Loose, const IsoConeSize = IsoConeSize::R04, const IsoCorrType = IsoCorrType::deltaBeta, const double iMaxEta = 2.4, const MuonIsolation = MuonIsolation::Loose);
    bool isGoodMuon(const pat::Muon&, const double iMinPt = 10., const double iMaxEta = 2.4, const MuonID = MuonID::Loose, const IsoConeSize = IsoConeSize::R04, const IsoCorrType = IsoCorrType::deltaBeta, const MuonIsolation = MuonIsolation::Loose) const;
    
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
    
    // data access tokens
    // pileup density
    edm::EDGetTokenT< double >                  EDMRhoToken; 
    // vertex collection
    edm::EDGetTokenT< reco::VertexCollection >  EDMVertexToken;
    // muons
    edm::EDGetTokenT< pat::MuonCollection >     EDMMuonsToken;  
    // electrons
    edm::EDGetTokenT< edm::View<pat::Electron> >EDMElectronsToken;
    
    // primary vertex
    reco::Vertex vertex;
    
    // event-specific average pile-up energy density per unit area in the phi-eta plane
    double rho;
    
    // use to get electron ID decisions, if electron IDs are recalculated by egamma VID tool
    //edm::EDGetTokenT<edm::ValueMap<bool> >          EDMeleCutBasedMediumIDmapToken;
    //edm::EDGetTokenT<edm::ValueMap<bool> >          EDMeleCutBasedLooseIDmapToken;
    //edm::EDGetTokenT<edm::ValueMap<bool> >          EDMeleCutBasedVetoIDmapToken;
    //edm::EDGetTokenT<edm::ValueMap<bool> >          EDMeleCutBasedTightIDmapToken;
    
    // Object to calculate Rochester Correction
    RoccoR rc;
    // directory of text files used to calculate RC
    std::string roccor_dir=std::string(getenv("CMSSW_BASE"))+"/src/BoostedTTH/Producers/data/rcdata2017v1/RoccoR2017v1.txt";
    
    // Object to get electron effective areas
    EffectiveAreas EA;
    // txt file to calculate effective areas for electrons relative isolation
    const std::string ea_dir = std::string(getenv("CMSSW_BASE"))+"/src/BoostedTTH/Producers/data/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt";
    
};



// constructor
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

                                                                                    // inputs
                                                                                    EDMRhoToken{consumes< double >                  (iConfig.getParameter<edm::InputTag>("rho"))},
                                                                                    EDMVertexToken{consumes< reco::VertexCollection >  (iConfig.getParameter<edm::InputTag>("vertices"))},
                                                                                    EDMMuonsToken{consumes< pat::MuonCollection >     (iConfig.getParameter<edm::InputTag>("leptons"))},
                                                                                    EDMElectronsToken{consumes< edm::View<pat::Electron> >(iConfig.getParameter<edm::InputTag>("leptons"))},
                                                                                    EA{ea_dir}
                                                                                    
{
    // setup of producer
    if(      leptonType == "electron" ) leptonType_ = LeptonType::Electron;
    else if( leptonType == "muon"     ) leptonType_ = LeptonType::Muon;
    else {
        std::cerr << "\n\nERROR: Unknown lepton type " << leptonType << std::endl;
        std::cerr << "Please select 'electron' or 'muon'\n" << std::endl;
        throw std::exception();
    }
    
    
    // use to get electron ID decisions, if electron IDs are recalculated by egamma VID tool
    //EDMeleCutBasedMediumIDmapToken = consumes< edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleMediumIdMap"));
    //EDMeleCutBasedLooseIDmapToken = consumes< edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleLooseIdMap"));
    //EDMeleCutBasedVetoIDmapToken = consumes< edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleVetoIdMap"));
    //EDMeleCutBasedTightIDmapToken = consumes< edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleTightIdMap"));
    
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
    if(leptonType_==LeptonType::Muon) assert(isoConeSizes.size()==etaMaxs_.size());
    if(leptonType_==LeptonType::Muon) assert(isoCorrTypes.size()==etaMaxs_.size());
    if(leptonType_==LeptonType::Muon) assert(muonIsoTypes.size()==etaMaxs_.size());
    
    // translate strings from config to nice C++ objects
    for(size_t i=0; i<ptMins_.size(); i++){
        if(leptonType_ == LeptonType::Electron){
            if(      leptonIDs[i] == "loose"   )         electronIDs_[i] = ElectronID::Loose;
            else if( leptonIDs[i] == "medium"  )         electronIDs_[i] = ElectronID::Medium;
            else if( leptonIDs[i] == "tight"   )         electronIDs_[i] = ElectronID::Tight;
            else if( leptonIDs[i] == "veto"   )          electronIDs_[i] = ElectronID::Veto;
            else {
                std::cerr << "\n\nERROR: No matching electron ID type found for: " << leptonIDs[i] << std::endl;
                throw std::exception();
            }
        }
        if(leptonType_ == LeptonType::Muon){
            if(      leptonIDs[i] == "loose"  )   muonIDs_[i] = MuonID::Loose;
            else if( leptonIDs[i] == "medium"  )   muonIDs_[i] = MuonID::Medium;
            else if( leptonIDs[i] == "tight"  )   muonIDs_[i] = MuonID::Tight;
            else{
                std::cerr << "\n\nERROR: No matching muon ID type found for: " << leptonIDs[i] << std::endl;
                throw std::exception();
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
            if(      muonIsoTypes[i] == "loose"  )   muonIsos_[i] = MuonIsolation::Loose;
            else if( muonIsoTypes[i] == "medium"  )   muonIsos_[i] = MuonIsolation::Medium;
            else if( muonIsoTypes[i] == "tight"  )   muonIsos_[i] = MuonIsolation::Tight;
            else{
                std::cerr << "\n\nERROR: No matching muon isolation type found for: " << muonIsoTypes[i] << std::endl;
                throw std::exception();
            }
        }
        if( leptonType_ == LeptonType::Electron ) produces<pat::ElectronCollection>(collectionNames_[i]);
        else if( leptonType_ == LeptonType::Muon     ) produces<pat::MuonCollection>(collectionNames_[i]);
        else {
            std::cerr << "\n\nERROR: Unknown lepton type " << leptonType << std::endl;
            std::cerr << "Please select 'electron' or 'muon'\n" << std::endl;
            throw std::exception();
        }
        
    }
    
    // if muon rochester corrections should be applied, init the corresponding module
    if(useMuonRC) {
        rc.init(roccor_dir);
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
    vertex = hVtxs->at(0);
    
    edm::Handle<double> hRho;
    iEvent.getByToken(EDMRhoToken,hRho);
    if(not hRho.isValid()) {
        std::cerr << "\n\nERROR: retrieved pile-up energy density is not valid" << std::endl;
        throw std::exception();
    }
    rho = *hRho;
    
    if( leptonType_ == LeptonType::Electron ) {
        // get input electron collection
        edm::Handle< edm::View<pat::Electron> > hElectrons;
        iEvent.getByToken(EDMElectronsToken,hElectrons);
        if(not hElectrons.isValid()) {
            std::cerr << "\n\nERROR: retrieved electron collection is not valid" << std::endl;
            throw std::exception();
        }
        
        std::vector<pat::Electron> updatedElectrons;
        
        // use to get electron ID decisions, if electron IDs are recalculated by egamma VID tool
        //edm::Handle<edm::ValueMap<bool> > loose_id_decisions;
        //edm::Handle<edm::ValueMap<bool> > medium_id_decisions;
        //edm::Handle<edm::ValueMap<bool> > tight_id_decisions;
        //edm::Handle<edm::ValueMap<bool> > veto_id_decisions;
        
        //iEvent.getByToken(EDMeleCutBasedLooseIDmapToken, loose_id_decisions);
        //iEvent.getByToken(EDMeleCutBasedMediumIDmapToken, medium_id_decisions);
        //iEvent.getByToken(EDMeleCutBasedTightIDmapToken, tight_id_decisions);
        //iEvent.getByToken(EDMeleCutBasedVetoIDmapToken, veto_id_decisions);
        //if(loose_id_decisions.isValid() && medium_id_decisions.isValid() && tight_id_decisions.isValid() && veto_id_decisions.isValid()){
        
        
        for(size_t i=0; i<ptMins_.size(); i++)
        {
            // check the electron IDs and only accept electrons fulfilling the requested ID
            for(size_t j=0; j< hElectrons->size(); j++){
                auto electron = hElectrons->ptrAt(j);
                if(electron.isNull()) continue;
                bool passesID = false;
                //(*loose_id_decisions)[electron];
                if(electronIDs_[i] == ElectronID::Loose) passesID = electron->electronID("cutBasedElectronID-Fall17-94X-V1-loose");
                //(*medium_id_decisions)[electron];
                else if(electronIDs_[i] == ElectronID::Medium) passesID = electron->electronID("cutBasedElectronID-Fall17-94X-V1-medium");
                else if(electronIDs_[i] == ElectronID::Tight) passesID = electron->electronID("cutBasedElectronID-Fall17-94X-V1-tight");
                //(*tight_id_decisions)[electron];
                //(*veto_id_decisions)[electron];
                else if(electronIDs_[i] == ElectronID::Veto) passesID = electron->electronID("cutBasedElectronID-Fall17-94X-V1-veto");  
                else{
                    std::cerr << "\n\nERROR: InvalidElectronID" <<  std::endl;
                    throw std::exception();
                }
                if( passesID ) updatedElectrons.push_back(hElectrons->at(j));
                
            }
            // apply energy corrections (scale & smearing)
            for(auto& ele : updatedElectrons){
                ele.addUserFloat("ptBeforeRun2Calibration",ele.pt());
                ele.setP4(ele.p4()*ele.userFloat("ecalTrkEnergyPostCorr")/ele.energy());
            }
            
            // produce the different electron collections            
            std::unique_ptr<pat::ElectronCollection> selectedLeptons =  std::make_unique<pat::ElectronCollection>(
                                                                        GetSortedByPt(
                                                                        GetSelectedElectrons(updatedElectrons,ptMins_[i],electronIDs_[i],etaMaxs_[i])));
            //for (auto & lep : *selectedLeptons){
                // TODO conesize and corr type should not be hardcoded
                //helper_.AddElectronRelIso(lep,coneSize::R03, CorrType::rhoEA,effAreaType::fall17,"relIso");
            //}
            iEvent.put(std::move(selectedLeptons),collectionNames_[i]);
            updatedElectrons.clear();
        }
        //}  
        //else{
        //throw cms::Exception("InvalidIDdecisions") << "ID decisions are corrupted!";
        //}
    }
    
    else if( leptonType_ == LeptonType::Muon ) {
        
        // get input muon collection
        edm::Handle<pat::MuonCollection> hMuons;
        iEvent.getByToken(EDMMuonsToken,hMuons);
        if(not hMuons.isValid()) {
            std::cerr << "\n\nERROR: retrieved muon collection is not valid" << std::endl;
            throw std::exception();
        }
        
        std::vector<pat::Muon> muons = *hMuons;
        
        // if the flag is set, apply the muon momentum correction (rochester correction)
        if(useMuonRC) {
            ApplyMuonMomentumCorrection(muons);
        }
        
        // produce the different muon collections
        for(size_t i=0; i<ptMins_.size();i++){
            // select muon collection
            std::unique_ptr<pat::MuonCollection> selectedLeptons =  std::make_unique<pat::MuonCollection>(
                                                                    GetSortedByPt( 
                                                                    GetSelectedMuons(muons,ptMins_[i],muonIDs_[i],IsoConeSizes_[i],IsoCorrTypes_[i],etaMaxs_[i],muonIsos_[i]))) ;
            //for (auto & lep : *selectedLeptons){
                //helper_.AddMuonRelIso(lep, IsoConeSizes_[i], IsoCorrTypes_[i],"relIso");
            //}
            iEvent.put(std::move(selectedLeptons),collectionNames_[i]);
        }
    }
    else {
        std::cerr << "\n\nERROR: Unknown lepton type " << leptonType << std::endl;
        std::cerr << "Please select 'electron' or 'muon'\n" << std::endl;
        throw std::exception();
    }
}

template <typename T> T SelectedLeptonProducer::GetSortedByPt(const T& collection){
    T result = collection;
    std::sort(result.begin(), result.end(), [] (typename T::value_type a, typename T::value_type b) { return a.pt() > b.pt();});
    return result;
}

std::vector<pat::Electron>
SelectedLeptonProducer::GetSelectedElectrons(const std::vector<pat::Electron>& inputElectrons, const double iMinPt, const ElectronID iElectronID, const double iMaxEta){
    
    std::vector<pat::Electron> selectedElectrons;
    
    for(const auto& ele : inputElectrons){
        if(isGoodElectron(ele,iMinPt,iMaxEta,iElectronID)) 
        {
            selectedElectrons.push_back(ele);
        }
    }
    
    return selectedElectrons;
}

bool
SelectedLeptonProducer::isGoodElectron(const pat::Electron& iElectron, const double iMinPt, const double iMaxEta,const ElectronID iElectronID) const{
    bool passesKinematics = (iMinPt<=iElectron.pt()) and (iMaxEta>=fabs(iElectron.eta()));
    bool inCrack = false;
    bool passesIPcuts = false;
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
    
    return passesKinematics and (not inCrack) and passesIPcuts;
}

double SelectedLeptonProducer::GetEletronRelIsolation(const pat::Electron& inputElectron, const IsoCorrType icorrType, const IsoConeSize iconeSize) const {
    double isoChargedHadrons = inputElectron.pfIsolationVariables().sumChargedHadronPt;
    double isoNeutralHadrons = inputElectron.pfIsolationVariables().sumNeutralHadronEt;
    double isoPhotons = inputElectron.pfIsolationVariables().sumPhotonEt;
    // The following line provides the isolation sum for particles from PU needed if deltaBeta pile-up correction is used
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

std::vector<pat::Muon>
SelectedLeptonProducer::GetSelectedMuons(const std::vector<pat::Muon>& inputMuons, const double iMinPt, const MuonID iMuonID, const IsoConeSize iconeSize, const IsoCorrType icorrType, const double iMaxEta, const MuonIsolation imuonIso){
    
    
    std::vector<pat::Muon> selectedMuons;
    
    for(const auto& mu : inputMuons){
        if(isGoodMuon(mu,iMinPt,iMaxEta,iMuonID,iconeSize,icorrType, imuonIso)) 
        {
            selectedMuons.push_back(mu);
        }
    }
    
    return selectedMuons;
}

bool
SelectedLeptonProducer::isGoodMuon(const pat::Muon& iMuon, const double iMinPt, const double iMaxEta, const MuonID iMuonID, const IsoConeSize iconeSize, const IsoCorrType icorrType, const MuonIsolation imuonIso) const{
    bool passesKinematics = (iMinPt<=iMuon.pt()) and (iMaxEta>=fabs(iMuon.eta()));
    bool passesID = false;
    bool passesIso = false;
    switch(iMuonID){
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
