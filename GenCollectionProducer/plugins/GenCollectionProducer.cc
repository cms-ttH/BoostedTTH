// -*- C++ -*-
//
// Package:    BoostedTTH/GenCollectionProducer
// Class:      GenCollectionProducer
// 
/**\class GenCollectionProducer GenCollectionProducer.cc BoostedTTH/GenCollectionProducer/plugins/GenCollectionProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Michael Wassmer
//         Created:  Thu, 14 Dec 2017 13:41:41 GMT
//
//


// system include files
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
//
// class declaration
//

class GenCollectionProducer : public edm::stream::EDProducer<> {
   public:
      explicit GenCollectionProducer(const edm::ParameterSet&);
      ~GenCollectionProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      
      std::vector<reco::GenJet> ApplyPtEtaCuts(const std::vector<reco::GenJet>& GenJets_,const double& pt_min_,const double& eta_max_);
      std::vector<reco::GenParticle> ApplyPtEtaCuts(const std::vector<reco::GenParticle>& GenParticles_,const std::string& type_,const double& pt_min_,const double& eta_max_);
      std::vector<reco::GenJet> DeltaRCleaning(const std::vector<reco::GenJet>& GenJets_,const std::vector<reco::GenParticle>& Leptons,double R);

      // ----------member data ---------------------------
      // token for slimmed genjets collection
      edm::EDGetTokenT< std::vector<reco::GenJet> > GenJetsToken;
      // token for slimmed AK8genjets collection
      edm::EDGetTokenT< std::vector<reco::GenJet> > GenJetsAK8Token;
      // token for pruned gen particle collection
      edm::EDGetTokenT< std::vector<reco::GenParticle> > GenParticlesToken;
      
      // few needed containers
      std::vector<std::string> collection_name;
      std::vector<std::string> collection_type;
      std::vector<double> pt_min;
      std::vector<double> eta_max;
      std::map<std::string,int> pdgids;
      bool doDeltaRCleaning;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
GenCollectionProducer::GenCollectionProducer(const edm::ParameterSet& iConfig)
{
   //register your products
/* Examples
   produces<ExampleData2>();

   //if do put with a label
   produces<ExampleData2>("label");
 
   //if you want to put into the Run
   produces<ExampleData2,InRun>();
*/
    //now do what ever other initialization is needed
   
    // store pdgids of leptons for later
    pdgids["Electron"]=11;
    pdgids["Muon"]=13;
    pdgids["Tau"]=15;
    pdgids["Photon"]=22;
    // register data access
    GenJetsToken  = consumes< std::vector<reco::GenJet> >(iConfig.getParameter<edm::InputTag>("genJets"));
    GenJetsAK8Token  = consumes< std::vector<reco::GenJet> >(iConfig.getParameter<edm::InputTag>("genJetsAK8"));
    GenParticlesToken = consumes< std::vector<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("genParticles"));
    
    // read config
    collection_name = iConfig.getParameter< std::vector<std::string> >("collection_name");
    collection_type = iConfig.getParameter< std::vector<std::string> >("collection_type");
    pt_min = iConfig.getParameter< std::vector<double> >("pt_min");
    eta_max = iConfig.getParameter< std::vector<double> >("eta_max");
    doDeltaRCleaning = iConfig.getParameter< bool >("doDeltaRCleaning");
    
    // register the objects which will later be put into the edm::event instance
    for(size_t i=0;i<collection_name.size();i++){
        if(collection_type.at(i)=="AK4Jet"||collection_type.at(i)=="AK8Jet"){
            produces<std::vector<reco::GenJet>>(collection_name.at(i));
        }
        else if(collection_type.at(i)=="Electron"||collection_type.at(i)=="Muon"||collection_type.at(i)=="Tau"||collection_type.at(i)=="Photon"){
            produces<std::vector<reco::GenParticle>>(collection_name.at(i));
        }
        else {
            throw cms::Exception("GenCollectionProducer") << "Wrong collection type " << collection_type.at(i) <<"\n";
        }
    }
}


GenCollectionProducer::~GenCollectionProducer()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
GenCollectionProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
/* This is an event example
   //Read 'ExampleData' from the Event
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);

   //Use the ExampleData to create an ExampleData2 which 
   // is put into the Event
   std::unique_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
   iEvent.put(std::move(pOut));
*/

/* this is an EventSetup example
   //Read SetupData from the SetupRecord in the EventSetup
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
*/
    // handle to manage the objects to be accessed
    edm::Handle<std::vector<reco::GenJet>> GenJets;
    edm::Handle<std::vector<reco::GenJet>> GenJetsAK8;
    edm::Handle<std::vector<reco::GenParticle>> GenParticles;
    // get the objects
    iEvent.getByToken(GenJetsToken,GenJets);
    iEvent.getByToken(GenJetsAK8Token,GenJetsAK8);
    iEvent.getByToken(GenParticlesToken,GenParticles);
    
    std::vector<reco::GenParticle> electrons = ApplyPtEtaCuts(*GenParticles,"Electron",10.,2.4);
    std::vector<reco::GenParticle> muons = ApplyPtEtaCuts(*GenParticles,"Muon",10.,2.4);
    std::vector<reco::GenParticle> leptons;
    leptons.insert(leptons.end(),electrons.begin(),electrons.end());
    leptons.insert(leptons.end(),muons.begin(),muons.end());
    
    // get basic collections of the gen particles/jets with pt and eta cuts applied
    for(size_t i=0;i<collection_name.size();i++){
        if(collection_type.at(i)=="AK4Jet"){
            std::vector<reco::GenJet> collection = ApplyPtEtaCuts(*GenJets,pt_min.at(i),eta_max.at(i));
            if(doDeltaRCleaning){
                std::vector<reco::GenJet> collection_cleaned = DeltaRCleaning(collection,leptons,0.4);
                collection = collection_cleaned;
            }
            std::unique_ptr<std::vector<reco::GenJet>> pOut(new std::vector<reco::GenJet>(collection));
            std::sort(pOut->begin(),pOut->end(),[](const auto& a, const auto& b){return a.pt()>b.pt();});
            iEvent.put(std::move(pOut),collection_name.at(i));
        }
        else if(collection_type.at(i)=="AK8Jet"){
            std::vector<reco::GenJet> collection = ApplyPtEtaCuts(*GenJetsAK8,pt_min.at(i),eta_max.at(i));
            if(doDeltaRCleaning){
                std::vector<reco::GenJet> collection_cleaned = DeltaRCleaning(collection,leptons,0.8);
                collection = collection_cleaned;
            }
            std::unique_ptr<std::vector<reco::GenJet>> pOut(new std::vector<reco::GenJet>(collection));
            std::sort(pOut->begin(),pOut->end(),[](const auto& a, const auto& b){return a.pt()>b.pt();});
            iEvent.put(std::move(pOut),collection_name.at(i));
        }
        else {
            std::vector<reco::GenParticle> collection = ApplyPtEtaCuts(*GenParticles,collection_type.at(i),pt_min.at(i),eta_max.at(i));
            std::unique_ptr<std::vector<reco::GenParticle>> pOut(new std::vector<reco::GenParticle>(collection));
            std::sort(pOut->begin(),pOut->end(),[](const auto& a, const auto& b){return a.pt()>b.pt();});
            iEvent.put(std::move(pOut),collection_name.at(i));
        }
    }
        
 
}

// get collection of genjets with pt and eta cuts
std::vector<reco::GenJet> GenCollectionProducer::ApplyPtEtaCuts(const std::vector<reco::GenJet>& GenJets_,const double& pt_min_,const double& eta_max_){
 
    std::vector<reco::GenJet> mod_GenJets;
    for(size_t i=0;i<GenJets_.size();i++){
        if(GenJets_.at(i).pt()>=pt_min_ && GenJets_.at(i).eta()<=eta_max_) {
            mod_GenJets.push_back(GenJets_.at(i));
        }
    }
    return mod_GenJets;
}

// get collection of specified genparticles with pt and eta cuts and in addition calculate dressed leptons
std::vector<reco::GenParticle> GenCollectionProducer::ApplyPtEtaCuts(const std::vector<reco::GenParticle>& GenParticles_,const std::string& type_,const double& pt_min_,const double& eta_max_){
    // look for prompt gen particles
    std::vector<reco::GenParticle> mod_GenParticles;
    for(size_t i=0;i<GenParticles_.size();i++){
        if(abs(GenParticles_.at(i).pdgId())==pdgids[type_]) {
            // prompt electrons, muons or photons
            if(type_!="Tau") {
                if(GenParticles_.at(i).isPromptFinalState()){
                    mod_GenParticles.push_back(GenParticles_.at(i));
                }
            }
            // prompt taus (is this correct?)
            else {
                if(GenParticles_.at(i).isPromptDecayed()){
                    mod_GenParticles.push_back(GenParticles_.at(i));
                }
            }
            
        }
    }
    // add collinear photons to electrons and muons to obtain dressed leptons
    if(type_=="Electron"||type_=="Muon"){
        for(size_t i=0;i<GenParticles_.size();i++){
            for(size_t j=0;j<mod_GenParticles.size();j++){
                if(abs(GenParticles_.at(i).pdgId())==pdgids["Photon"] && GenParticles_.at(i).status()==1 && !GenParticles_.at(i).statusFlags().isPrompt() && reco::deltaR(GenParticles_.at(i),mod_GenParticles.at(j))<0.1) {
                    mod_GenParticles.at(j).setP4(mod_GenParticles.at(j).p4()+GenParticles_.at(i).p4());
                }
            }
        }
    }
    // do pt and eta cuts
    std::vector<reco::GenParticle> mod_GenParticles_pt_eta;
    for(size_t i=0;i<mod_GenParticles.size();i++){
        if(mod_GenParticles.at(i).pt()>=pt_min_ && mod_GenParticles.at(i).eta()<=eta_max_) {
            mod_GenParticles_pt_eta.push_back(mod_GenParticles.at(i));
        }
    }
    //
    return mod_GenParticles_pt_eta;
}

// do a lepton deltaR cleaning with jets
std::vector<reco::GenJet> GenCollectionProducer::DeltaRCleaning(const std::vector<reco::GenJet>& GenJets_,const std::vector<reco::GenParticle>& Leptons,double R) {
    std::vector<reco::GenJet> cleaned_jets;
    for(size_t i=0;i<GenJets_.size();i++){
        bool isolated = true;
        for(size_t j=0;j<Leptons.size();j++){
            isolated = isolated && reco::deltaR(GenJets_.at(i),Leptons.at(j))<R;
        }
        if(isolated) {
            cleaned_jets.push_back(GenJets_.at(i));
        }
    }
    return cleaned_jets;
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
GenCollectionProducer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
GenCollectionProducer::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
GenCollectionProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
GenCollectionProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
GenCollectionProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
GenCollectionProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GenCollectionProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenCollectionProducer);
