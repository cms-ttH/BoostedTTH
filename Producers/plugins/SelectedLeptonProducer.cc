// -*- C++ -*-
//
// Package:    BoostedTTH/ObjectSelectors
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

#include "BoostedTTH/Producers/src/RoccoR.cc" // this is needed to calculate the correction factors of the rochester correction
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
  std::vector<double> ptMins_;
  std::vector<double> etaMaxs_;

  std::vector<muonID::muonID> muonIDs_;
  std::vector<electronID::electronID> electronIDs_;
  std::vector<coneSize::coneSize> muonIsoConeSizes_;
  std::vector<corrType::corrType> muonIsoCorrTypes_;
  std::vector<std::string> collectionNames_;

  // data access tokens
  edm::EDGetTokenT< double >                  EDMRhoToken; //  pileup density
  edm::EDGetTokenT< reco::VertexCollection >  EDMVertexToken; // vertex
  edm::EDGetTokenT< pat::MuonCollection >     EDMMuonsToken;  // muons
  edm::EDGetTokenT< edm::View<pat::Electron> >EDMElectronsToken;  // electrons
  edm::EDGetTokenT< edm::ValueMap<float> >    EDMeleMVAvaluesToken; // values of electron mva
  edm::EDGetTokenT< edm::ValueMap<int> >      EDMeleMVAcategoriesToken;  // category of electron mva
  
  bool isData;
  bool useMuonRC; // flag to enable or disable Rochester Correction
  bool deterministicSeeds; // flag to enable or disable deterministic seeds for RC
  RoccoR rc; // Object to calculate Rochester Correction
  std::string roccor_dir=string(getenv("CMSSW_BASE"))+"/src/BoostedTTH/Producers/data/rcdata2016v3"; // directory of text files used to calculate RC
};


//
// constructors and destructor
//
SelectedLeptonProducer::SelectedLeptonProducer(const edm::ParameterSet& iConfig)
{
    // setup of producer
  const std::string leptonType = iConfig.getParameter<std::string>("leptonType");
  if(      leptonType == "electron" ) leptonType_ = Electron;
  else if( leptonType == "muon"     ) leptonType_ = Muon;
  else {
    std::cerr << "\n\nERROR: Unknown lepton type '" << leptonType << "'" << std::endl;
    std::cerr << "Please select 'electron' or 'muon'\n" << std::endl;
    throw std::exception();
  }

  // setup for miniaodhelper
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

  // inputs
  EDMElectronsToken         = consumes< edm::View<pat::Electron> >(iConfig.getParameter<edm::InputTag>("leptons"));
  EDMMuonsToken             = consumes< pat::MuonCollection >     (iConfig.getParameter<edm::InputTag>("leptons"));
  EDMVertexToken            = consumes< reco::VertexCollection >  (iConfig.getParameter<edm::InputTag>("vertices"));
  EDMRhoToken               = consumes< double >                  (iConfig.getParameter<edm::InputTag>("rho"));
  EDMeleMVAvaluesToken      = consumes<edm::ValueMap<float> >     (iConfig.getParameter<edm::InputTag>("electronMVAvalues"));
  EDMeleMVAcategoriesToken  = consumes<edm::ValueMap<int> >       (iConfig.getParameter<edm::InputTag>("electronMVAcategories"));
  
  // setup of outputs
  ptMins_ = iConfig.getParameter< std::vector<double> >("ptMins");
  etaMaxs_ = iConfig.getParameter< std::vector<double> >("etaMaxs");
  const std::vector<std::string > leptonIDs= iConfig.getParameter< std::vector<std::string> >("leptonIDs");
  electronIDs_ = std::vector<electronID::electronID>(leptonIDs.size(),electronID::electronLoose);
  muonIDs_ = std::vector<muonID::muonID>(leptonIDs.size(),muonID::muonLoose);
  const std::vector<std::string> muonIsoConeSizes = iConfig.getParameter<std::vector<std::string> >("muonIsoConeSizes");
  muonIsoConeSizes_ = std::vector<coneSize::coneSize>(leptonIDs.size(),coneSize::R04);
  const vector<std::string> muonIsoCorrTypes = iConfig.getParameter<std::vector<std::string> >("muonIsoCorrTypes");
  muonIsoCorrTypes_ = std::vector<corrType::corrType>(leptonIDs.size(),corrType::deltaBeta);
  collectionNames_= iConfig.getParameter<std::vector< std::string> >("collectionNames");

  assert(ptMins_.size()==etaMaxs_.size());
  assert(leptonIDs.size()==etaMaxs_.size());
  if(leptonType_==Muon) assert(muonIsoConeSizes.size()==etaMaxs_.size());
  if(leptonType_==Muon) assert(muonIsoCorrTypes.size()==etaMaxs_.size());
  assert(collectionNames_.size()==etaMaxs_.size());

  for(uint i=0; i<ptMins_.size(); i++){
      if(leptonType_ == Electron){
	  if(      leptonIDs[i] == "loose"        )         electronIDs_[i] = electronID::electronLoose;
	  else if( leptonIDs[i] == "tight"        )         electronIDs_[i] = electronID::electronTight;
	  else if( leptonIDs[i] == "loosePhys14"  )         electronIDs_[i] = electronID::electronPhys14L;
	  else if( leptonIDs[i] == "tightPhys14"  )         electronIDs_[i] = electronID::electronPhys14T;
	  else if( leptonIDs[i] == "tightSpring15"  )       electronIDs_[i] = electronID::electronSpring15T;
	  else if( leptonIDs[i] == "mediumSpring15"  )      electronIDs_[i] = electronID::electronSpring15M;
	  else if( leptonIDs[i] == "looseSpring15"  )       electronIDs_[i] = electronID::electronSpring15L;
	  else if( leptonIDs[i] == "EndOf15MVA80"  )        electronIDs_[i] = electronID::electronEndOf15MVA80;
	  else if( leptonIDs[i] == "EndOf15MVA90"  )        electronIDs_[i] = electronID::electronEndOf15MVA90;
	  else if( leptonIDs[i] == "EndOf15MVA80iso0p1"  )  electronIDs_[i] = electronID::electronEndOf15MVA80iso0p1;
	  else if( leptonIDs[i] == "EndOf15MVA90iso0p1"  )  electronIDs_[i] = electronID::electronEndOf15MVA90iso0p1;
	  else if( leptonIDs[i] == "EndOf15MVA80iso0p15"  ) electronIDs_[i] = electronID::electronEndOf15MVA80iso0p15;
	  else if( leptonIDs[i] == "EndOf15MVA90iso0p15"  ) electronIDs_[i] = electronID::electronEndOf15MVA90iso0p15;
 	  else if( leptonIDs[i] == "electron80XCutBasedL"  ) electronIDs_[i] = electronID::electron80XCutBasedL;
	  else if( leptonIDs[i] == "electron80XCutBasedM"  ) electronIDs_[i] = electronID::electron80XCutBasedM;
	  else if( leptonIDs[i] == "electron80XCutBasedT"  ) electronIDs_[i] = electronID::electron80XCutBasedT;
          else if( leptonIDs[i] == "electron80XCutBasedT_IsoInverted"  ) electronIDs_[i] = electronID::electron80XCutBasedT_IsoInverted;
	  else if( leptonIDs[i] == "electronNonTrigMVAid90"  ) electronIDs_[i] = electronID::electronNonTrigMVAid90;
	  else if( leptonIDs[i] == "electronNonTrigMVAid80"  ) electronIDs_[i] = electronID::electronNonTrigMVAid80;
	  else if( leptonIDs[i] == "electronGeneralPurposeMVA2016WP80"  ) electronIDs_[i] = electronID::electronGeneralPurposeMVA2016WP80;
	  else if( leptonIDs[i] == "electronGeneralPurposeMVA2016WP90"  ) electronIDs_[i] = electronID::electronGeneralPurposeMVA2016WP90;

	  else {
	      std::cerr << "\n\nERROR: No matching electron ID type found for: " << leptonIDs[i] << std::endl;
	      throw std::exception();
	  }
      }
      if(leptonType_ == Muon){
	  if(      leptonIDs[i] == "loose"  )   muonIDs_[i] = muonID::muonLoose;
	  else if( leptonIDs[i] == "tight"  )   muonIDs_[i] = muonID::muonTight;
          else if( leptonIDs[i] == "tight_IsoInverted"  )   muonIDs_[i] = muonID::muonTight_IsoInverted;
	  else if( leptonIDs[i] == "tightDL"  ) muonIDs_[i] = muonID::muonTightDL;
          else if( leptonIDs[i] == "tightDL_IsoInverted"  )   muonIDs_[i] = muonID::muonTightDL_IsoInverted;
	  else if( leptonIDs[i] == "muonMediumICHEP"  ) muonIDs_[i] = muonID::muonMediumICHEP;

	  else {
	      std::cerr << "\n\nERROR: No matching muon ID type found for: " << leptonIDs[i] << std::endl;
	      throw std::exception();
	  }


	  if(      muonIsoConeSizes[i] == "R03"  ) muonIsoConeSizes_[i] = coneSize::R03;
	  else if( muonIsoConeSizes[i] == "R04"  ) muonIsoConeSizes_[i] = coneSize::R04;
	  else {
	      std::cerr << "\n\nERROR: No matching isolation cone size found for: " << muonIsoConeSizes_[i] << std::endl;
	      throw std::exception();
	  }

	  if(      muonIsoCorrTypes[i] == "deltaBeta" ) muonIsoCorrTypes_[i] = corrType::deltaBeta;
	  else if( muonIsoCorrTypes[i] == "rhoEA"     ) muonIsoCorrTypes_[i] = corrType::rhoEA;
	  else {
	      std::cerr << "\n\nERROR: No matching isolation correction type found for: " << muonIsoCorrTypes_[i] << std::endl;
	      throw std::exception();
	  }
      }
      if( leptonType_ == Electron ) produces<pat::ElectronCollection>(collectionNames_[i]);
      if( leptonType_ == Muon     ) produces<pat::MuonCollection>(collectionNames_[i]);

  }
  // Set up MiniAODHelper
  isData = iConfig.getParameter<bool>("isData");
  useMuonRC = iConfig.getParameter<bool>("useMuonRC");
  deterministicSeeds = iConfig.getParameter<bool>("useDeterministicSeeds");
  const int sampleID = -1;
  helper_.SetUp(era,sampleID,iAnalysisType,isData);
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
    if( !setUpHelper(iEvent) ) return;


    if( leptonType_ == Electron ) {
	// get input electron collection
	edm::Handle< edm::View<pat::Electron> > hElectrons;
	iEvent.getByToken(EDMElectronsToken,hElectrons);


	std::vector<pat::Electron> updatedElectrons;
	// get electron mva info
	edm::Handle<edm::ValueMap<float> > h_mvaValues;
	iEvent.getByToken(EDMeleMVAvaluesToken,h_mvaValues);
	if (h_mvaValues.isValid()){
	    edm::Handle<edm::ValueMap<int> > h_mvaCategories;
	    iEvent.getByToken(EDMeleMVAcategoriesToken,h_mvaCategories);

	    // add electron mva info to electrons
	    updatedElectrons = helper_.GetElectronsWithMVAid(hElectrons,h_mvaValues,h_mvaCategories);
	}
	else{
	    for (size_t i = 0; i < hElectrons->size(); ++i){
		updatedElectrons.push_back(hElectrons->at(i));
	    }
	}

	// produce the different electron collections
	for(uint i=0; i<ptMins_.size();i++){
	    // select electron collection
	    std::unique_ptr<pat::ElectronCollection> selectedLeptons = std::make_unique<pat::ElectronCollection>( helper_.GetSortedByPt(helper_.GetSelectedElectrons(updatedElectrons,ptMins_[i],electronIDs_[i],etaMaxs_[i])));
	    for (auto & lep : *selectedLeptons){
		// TODO conesize and corr type should not be hardcoded
		helper_.AddElectronRelIso(lep,coneSize::R03, corrType::rhoEA,effAreaType::spring16,"relIso");
	    }
	    iEvent.put(std::move(selectedLeptons),collectionNames_[i]);
	}
    }

    else if( leptonType_ == Muon ) {

	// get input muon collection
	edm::Handle<pat::MuonCollection> hMuons;
	iEvent.getByToken(EDMMuonsToken,hMuons);
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
                        momentum_sf = rc.kScaleFromGenMC(muons[i].charge(), muons[i].pt(), muons[i].eta(), muons[i].phi(), trackerLayersWithMeasurement, muons[i].genLepton()->pt(), r1, 0, 0);
                    }
                    else {
                        double r2=r1;
                        if(!deterministicSeeds) {r2=rnd.Rndm();}
                        momentum_sf = rc.kScaleAndSmearMC(muons[i].charge(), muons[i].pt(), muons[i].eta(), muons[i].phi(), trackerLayersWithMeasurement, r1, r2, 0, 0);
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
	    std::unique_ptr<pat::MuonCollection> selectedLeptons = std::make_unique<pat::MuonCollection>(helper_.GetSortedByPt(helper_.GetSelectedMuons(muons,ptMins_[i],muonIDs_[i],muonIsoConeSizes_[i],muonIsoCorrTypes_[i],etaMaxs_[i]))) ;
	    for (auto & lep : *selectedLeptons){
		helper_.AddMuonRelIso(lep, muonIsoConeSizes_[i], muonIsoCorrTypes_[i],"relIso");
	    }
	    iEvent.put(std::move(selectedLeptons),collectionNames_[i]);
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
