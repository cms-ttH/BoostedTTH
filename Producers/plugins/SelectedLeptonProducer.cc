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
    
    enum class LeptonType    {Electron, Muon};
    enum class ElectronID    {Veto, Loose, Medium, Tight};
    enum class MuonID        {Loose, Medium, Tight};
    enum class MuonIsoConeSize      {R03, R04};
    enum class MuonIsoCorrType      {rhoEA, deltaBeta};
    enum class MuonIsolation {Loose, Medium, Tight};
    
    
    // Function to sort leptons by pt
    template <typename T> T GetSortedByPt(const T&);
    
    // Functions to return an electron collection with the desired properties
    std::vector<pat::Electron> GetSelectedElectrons(const std::vector<pat::Electron>& inputElectrons, const double iMinPt = 10., const ElectronID = ElectronID::Loose, const double iMaxEta = 2.4);
    bool isGoodElectron(const pat::Electron& iElectron, const double iMinPt = 10., const double iMaxEta = 2.4, const ElectronID iElectronID = ElectronID::Loose) const;
    
    // Functions to return a muon collection with the desired properties
    std::vector<pat::Muon> GetSelectedMuons(const std::vector<pat::Muon>& inputMuons, const double iMinPt = 10., const MuonID = MuonID::Loose, const MuonIsoConeSize = MuonIsoConeSize::R04, const MuonIsoCorrType = MuonIsoCorrType::deltaBeta, const double iMaxEta = 2.4, const MuonIsolation = MuonIsolation::Loose);
    bool isGoodMuon(const pat::Muon&, const double iMinPt = 10., const double iMaxEta = 2.4, const MuonID = MuonID::Loose, const MuonIsoConeSize = MuonIsoConeSize::R04, const MuonIsoCorrType = MuonIsoCorrType::deltaBeta, const MuonIsolation = MuonIsolation::Loose) const;
    
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
    const std::vector<std::string> muonIsoConeSizes;
    const std::vector<std::string> muonIsoCorrTypes;
    const std::vector<std::string> muonIsoTypes;
    
    const bool isData;
    const bool useMuonRC;                                           // flag to enable or disable Rochester Correction
    const bool deterministicSeeds;                                  // flag to enable or disable deterministic seeds for RC
    
    std::vector<MuonID> muonIDs_;
    std::vector<ElectronID> electronIDs_;
    std::vector<MuonIsoConeSize> muonIsoConeSizes_;
    std::vector<MuonIsoCorrType> muonIsoCorrTypes_;
    std::vector<MuonIsolation> muonIsos_;
    
    // data access tokens
    // pileup density
    edm::EDGetTokenT< double >                  EDMRhoToken; 
    // vertex
    edm::EDGetTokenT< reco::VertexCollection >  EDMVertexToken;
    // muons
    edm::EDGetTokenT< pat::MuonCollection >     EDMMuonsToken;  
    // electrons
    edm::EDGetTokenT< edm::View<pat::Electron> >EDMElectronsToken;
    
    // use to get electron ID decisions, if electron IDs are recalculated by egamma VID tool
    //edm::EDGetTokenT<edm::ValueMap<bool> >          EDMeleCutBasedMediumIDmapToken;
    //edm::EDGetTokenT<edm::ValueMap<bool> >          EDMeleCutBasedLooseIDmapToken;
    //edm::EDGetTokenT<edm::ValueMap<bool> >          EDMeleCutBasedVetoIDmapToken;
    //edm::EDGetTokenT<edm::ValueMap<bool> >          EDMeleCutBasedTightIDmapToken;
    
    
    RoccoR rc;                                                // Object to calculate Rochester Correction
    // directory of text files used to calculate RC
    std::string roccor_dir=std::string(getenv("CMSSW_BASE"))+"/src/BoostedTTH/Producers/data/rcdata2017v1/RoccoR2017v1.txt";
    
    reco::Vertex vertex;
};


//
// constructors and destructor
//
SelectedLeptonProducer::SelectedLeptonProducer(const edm::ParameterSet& iConfig) :  leptonType{iConfig.getParameter<std::string>("leptonType")},
                                                                                    collectionNames_{iConfig.getParameter<std::vector< std::string> >("collectionNames")},
                                                                                    ptMins_{iConfig.getParameter< std::vector<double> >("ptMins")},
                                                                                    etaMaxs_{iConfig.getParameter< std::vector<double> >("etaMaxs")},
                                                                                    leptonIDs{iConfig.getParameter< std::vector<std::string> >("leptonIDs")},
                                                                                    muonIsoConeSizes{iConfig.getParameter<std::vector<std::string> >("muonIsoConeSizes")},
                                                                                    muonIsoCorrTypes{iConfig.getParameter<std::vector<std::string> >("muonIsoCorrTypes")},
                                                                                    muonIsoTypes{iConfig.getParameter<std::vector<std::string> >("muonIsoTypes")},
                                                                                    isData{iConfig.getParameter<bool>("isData")},
                                                                                    useMuonRC{iConfig.getParameter<bool>("useMuonRC")},
                                                                                    deterministicSeeds{iConfig.getParameter<bool>("useDeterministicSeeds")},

                                                                                    // inputs
                                                                                    EDMRhoToken{consumes< double >                  (iConfig.getParameter<edm::InputTag>("rho"))},
                                                                                    EDMVertexToken{consumes< reco::VertexCollection >  (iConfig.getParameter<edm::InputTag>("vertices"))},
                                                                                    EDMMuonsToken{consumes< pat::MuonCollection >     (iConfig.getParameter<edm::InputTag>("leptons"))},
                                                                                    EDMElectronsToken{consumes< edm::View<pat::Electron> >(iConfig.getParameter<edm::InputTag>("leptons"))}
                                                                                    
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
    
    electronIDs_ = std::vector<ElectronID>(leptonIDs.size(),ElectronID::Loose);
    muonIDs_ = std::vector<MuonID>(leptonIDs.size(),MuonID::Loose);
    muonIsoConeSizes_ = std::vector<MuonIsoConeSize>(leptonIDs.size(),MuonIsoConeSize::R04);
    muonIsoCorrTypes_ = std::vector<MuonIsoCorrType>(leptonIDs.size(),MuonIsoCorrType::deltaBeta);
    muonIsos_ = std::vector<MuonIsolation>(leptonIDs.size(), MuonIsolation::Loose);
    
    assert(ptMins_.size()==etaMaxs_.size());
    assert(leptonIDs.size()==etaMaxs_.size());
    assert(collectionNames_.size()==etaMaxs_.size());
    if(leptonType_==LeptonType::Muon) assert(muonIsoConeSizes.size()==etaMaxs_.size());
    if(leptonType_==LeptonType::Muon) assert(muonIsoCorrTypes.size()==etaMaxs_.size());
    if(leptonType_==LeptonType::Muon) assert(muonIsoTypes.size()==etaMaxs_.size());
    
    
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
            if(      muonIsoConeSizes[i] == "R03"  ) muonIsoConeSizes_[i] = MuonIsoConeSize::R03;
            else if( muonIsoConeSizes[i] == "R04"  ) muonIsoConeSizes_[i] = MuonIsoConeSize::R04;
            else {
                std::cerr << "\n\nERROR: No matching isolation cone size found for: " << muonIsoConeSizes[i] << std::endl;
                throw std::exception();
            }
            
            if(      muonIsoCorrTypes[i] == "deltaBeta" ) muonIsoCorrTypes_[i] = MuonIsoCorrType::deltaBeta;
            else if( muonIsoCorrTypes[i] == "rhoEA"     ) muonIsoCorrTypes_[i] = MuonIsoCorrType::rhoEA;
            else {
                std::cerr << "\n\nERROR: No matching isolation correction type found for: " << muonIsoCorrTypes[i] << std::endl;
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
        if( leptonType_ == LeptonType::Muon     ) produces<pat::MuonCollection>(collectionNames_[i]);
        
    }
    
    if(useMuonRC) {
        rc.init(roccor_dir);
    }
}


SelectedLeptonProducer::~SelectedLeptonProducer() {}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
SelectedLeptonProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    
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
                    throw cms::Exception("InvalidElectronID") << "Could not match the electron ID with a ID decision map!";
                }
                if( passesID ) updatedElectrons.push_back(hElectrons->at(j));
                
            }
            // apply energy corrections (scale & smearing)
            for(auto& ele : updatedElectrons){
                ele.addUserFloat("ptBeforeRun2Calibration",ele.pt());
                ele.setP4(ele.p4()*ele.userFloat("ecalTrkEnergyPostCorr")/ele.energy());
            }
            
            // produce the different electron collections
            
            std::unique_ptr<pat::ElectronCollection> selectedLeptons = std::make_unique<pat::ElectronCollection>(GetSortedByPt(GetSelectedElectrons(updatedElectrons,ptMins_[i],electronIDs_[i],etaMaxs_[i])));
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
        
        if(useMuonRC) {
            double momentum_sf;
            TRandom3 rnd;
            for(uint i=0;i<muons.size();i++) {
                momentum_sf=1.;
                if(deterministicSeeds) {
                    int32_t seed = muons[i].userInt("deterministicSeed");
                    rnd.SetSeed((uint32_t)seed);
                }
                double r1 = rnd.Rndm();
                int trackerLayersWithMeasurement=0;
                if(!muons[i].innerTrack().isNull()) {
                    trackerLayersWithMeasurement = muons[i].innerTrack()->hitPattern().trackerLayersWithMeasurement();
                }
                if(isData) {
                    momentum_sf = rc.kScaleDT(muons[i].charge(), muons[i].pt(), muons[i].eta(), muons[i].phi(), 0, 0);
                }
                else {
                    if(muons[i].genLepton()) {
                        momentum_sf = rc.kSpreadMC(muons[i].charge(), muons[i].pt(), muons[i].eta(), muons[i].phi(), muons[i].genLepton()->pt(), 0, 0);
                    }
                    else {
                        momentum_sf = rc.kSmearMC(muons[i].charge(), muons[i].pt(), muons[i].eta(), muons[i].phi(), trackerLayersWithMeasurement, r1, 0, 0);
                    }
                }
                auto tmp_vector = muons[i].p4();
                muons[i].addUserFloat( "PtbeforeRC", tmp_vector.Pt());
                tmp_vector.SetPxPyPzE(momentum_sf*tmp_vector.Px(),momentum_sf*tmp_vector.Py(),momentum_sf*tmp_vector.Pz(),TMath::Sqrt((1+(tmp_vector.P2()/(tmp_vector.E()*tmp_vector.E())*(momentum_sf*momentum_sf-1))))*tmp_vector.E());
                muons[i].setP4(tmp_vector);            
            }
        }
        
        // produce the different muon collections
        for(uint i=0; i<ptMins_.size();i++){
            // select muon collection
            std::unique_ptr<pat::MuonCollection> selectedLeptons = std::make_unique<pat::MuonCollection>(GetSortedByPt(GetSelectedMuons(muons,ptMins_[i],muonIDs_[i],muonIsoConeSizes_[i],muonIsoCorrTypes_[i],etaMaxs_[i],muonIsos_[i]))) ;
            //for (auto & lep : *selectedLeptons){
                //helper_.AddMuonRelIso(lep, muonIsoConeSizes_[i], muonIsoCorrTypes_[i],"relIso");
            //}
            iEvent.put(std::move(selectedLeptons),collectionNames_[i]);
        }
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

std::vector<pat::Muon>
SelectedLeptonProducer::GetSelectedMuons(const std::vector<pat::Muon>& inputMuons, const double iMinPt, const MuonID iMuonID, const MuonIsoConeSize iconeSize, const MuonIsoCorrType icorrType, const double iMaxEta, const MuonIsolation imuonIso){
    
    
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
SelectedLeptonProducer::isGoodMuon(const pat::Muon& iMuon, const double iMinPt, const double iMaxEta, const MuonID iMuonID, const MuonIsoConeSize iconeSize, const MuonIsoCorrType icorrType, const MuonIsolation imuonIso) const{
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
            throw cms::Exception("InvalidMuonID") << "No matching muon ID found!";

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
            throw cms::Exception("InvalidMuonIso") << "No matching muon Isolation found!";

    }
    return passesKinematics and passesID and passesIso;
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
