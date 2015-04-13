// -*- C++ -*-
//
// Package:    BoostedTTH/BoostedProducer/SubjetFilterJetMatcher
// Class:      SubjetFilterJetMatcher
// 
/**\class SubjetFilterJetMatcher SubjetFilterJetMatcher.cc BoostedTTH/BoostedProducer/SubjetFilterJetMatcher/plugins/SubjetFilterJetMatcher.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shawn Williamson
//         Created:  Fri, 23 Jan 2015 08:17:01 GMT
//
//

#include "BoostedTTH/BoostedProducer/plugins/SubjetFilterJetMatcher.h"

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
SubjetFilterJetMatcher::SubjetFilterJetMatcher(const edm::ParameterSet& iConfig):
  minJetPt(iConfig.getParameter<double>("minJetPt")),
  recofatjetsTag_(iConfig.getParameter<edm::InputTag>("recofatjetsTag")),
  patfatjetsTag_(iConfig.getParameter<edm::InputTag>("patfatjetsTag")),
  patsubjetsTag_(iConfig.getParameter<edm::InputTag>("patsubjetsTag")),
  patfilterjetsTag_(iConfig.getParameter<edm::InputTag>("patfilterjetsTag")),
  subjettiness1Tag_(iConfig.getParameter<edm::InputTag>("subjettiness1Tag")),
  subjettiness2Tag_(iConfig.getParameter<edm::InputTag>("subjettiness2Tag")),
  subjettiness3Tag_(iConfig.getParameter<edm::InputTag>("subjettiness3Tag")),
  subjettiness4Tag_(iConfig.getParameter<edm::InputTag>("subjettiness4Tag"))
{  
  produces<boosted::SubFilterJetCollection>("subfilterjets");  
}


SubjetFilterJetMatcher::~SubjetFilterJetMatcher()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
SubjetFilterJetMatcher::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  
  edm::Handle< std::vector<reco::BasicJet> > recofatjetsHandle;
  iEvent.getByLabel(recofatjetsTag_, recofatjetsHandle);
  std::vector<reco::BasicJet> recofatjets = *recofatjetsHandle;
  
  edm::Handle<edm::View<pat::Jet> > patfatjetsHandle;
  iEvent.getByLabel(patfatjetsTag_, patfatjetsHandle);
  edm::View<pat::Jet> patfatjets = *patfatjetsHandle;
  
  edm::Handle<edm::View<pat::Jet> > patsubjetsHandle;
  iEvent.getByLabel(patsubjetsTag_, patsubjetsHandle);
  edm::View<pat::Jet> patsubjets = *patsubjetsHandle;
	
  edm::Handle<edm::View<pat::Jet> > patfilterjetsHandle;
  iEvent.getByLabel(patfilterjetsTag_, patfilterjetsHandle);
  edm::View<pat::Jet> patfilterjets = *patfilterjetsHandle;
  
  edm::Handle<std::vector<double> > subjettiness1Handle;
  iEvent.getByLabel(subjettiness1Tag_, subjettiness1Handle);
  std::vector<double> subjettiness1 = *subjettiness1Handle;
  
  edm::Handle<std::vector<double> > subjettiness2Handle;
  iEvent.getByLabel(subjettiness2Tag_, subjettiness2Handle);
  std::vector<double> subjettiness2 = *subjettiness2Handle;
  
  edm::Handle<std::vector<double> > subjettiness3Handle;
  iEvent.getByLabel(subjettiness3Tag_, subjettiness3Handle);
  std::vector<double> subjettiness3 = *subjettiness3Handle;
  
  edm::Handle<std::vector<double> > subjettiness4Handle;
  iEvent.getByLabel(subjettiness4Tag_, subjettiness4Handle);
  std::vector<double> subjettiness4 = *subjettiness4Handle;
  
  std::auto_ptr<boosted::SubFilterJetCollection> subFilterJets(new boosted::SubFilterJetCollection());

  std::multimap<double, int> patfatjetindex_by_eta;
  std::multimap<double, int> patsubjetindex_by_eta;
  std::multimap<double, int> patfilterjetindex_by_eta;
  
  for(size_t i=0; i<patfatjets.size(); ++i) patfatjetindex_by_eta.insert(std::pair<double,int>(patfatjets[i].eta(), i));
  for(size_t i=0; i<patsubjets.size(); ++i) patsubjetindex_by_eta.insert(std::pair<double,int>(patsubjets[i].eta(), i));
  for(size_t i=0; i<patfilterjets.size(); ++i) patfilterjetindex_by_eta.insert(std::pair<double,int>(patfilterjets[i].eta(), i));
  
  for(typename std::vector<reco::BasicJet>::const_iterator it=recofatjets.begin();it!=recofatjets.end();++it){
    if(it->pt() < minJetPt) continue;
    
    subFilterJets->push_back(boosted::SubFilterJet());
    subFilterJets->back().fatjet = deltarJetMatching(patfatjets, patfatjetindex_by_eta, *it);
    subFilterJets->back().subjettiness1 = subjettiness1[it-recofatjets.begin()];
    subFilterJets->back().subjettiness2 = subjettiness2[it-recofatjets.begin()];
    subFilterJets->back().subjettiness3 = subjettiness3[it-recofatjets.begin()];
    subFilterJets->back().subjettiness4 = subjettiness4[it-recofatjets.begin()];
    
    std::vector<const reco::Candidate*> recosubjets = it->getJetConstituentsQuick();
    for(size_t i=0;i<recosubjets.size(); ++i){
      if(i<2) subFilterJets->back().subjets.push_back(deltarJetMatching(patsubjets, patsubjetindex_by_eta, *(recosubjets.at(i))));
      else subFilterJets->back().filterjets.push_back(deltarJetMatching(patfilterjets, patfilterjetindex_by_eta, *(recosubjets.at(i))));
    }
  }
  
  iEvent.put(subFilterJets,"subfilterjets");
}


template<typename recojettype>
const pat::Jet & SubjetFilterJetMatcher::deltarJetMatching(const edm::View<pat::Jet> & patjets, const std::multimap<double, int> & patjetindex_by_eta, const recojettype & recojet){
	std::multimap<double, int>::const_iterator lower = patjetindex_by_eta.lower_bound(recojet.eta() - 0.01);
	std::multimap<double, int>::const_iterator upper = patjetindex_by_eta.upper_bound(recojet.eta() + 0.01);

	double delta_r = 9999.0;
	int best_match = -1;

	for(std::multimap<double, int>::const_iterator it=lower; it!=upper; ++it){
		if(best_match == -1 || reco::deltaR(patjets[it->second], recojet) < delta_r){
			best_match = it->second;
			delta_r = reco::deltaR(patjets[best_match], recojet);
		}
	}

	if(best_match >= 0) return patjets[best_match];
	throw std::string("deltarJetMatching: could not find matching jet.");
}


// ------------ method called once each job just before starting event loop  ------------
void 
SubjetFilterJetMatcher::beginJob()
{
}


// ------------ method called once each job just after ending the event loop  ------------
void 
SubjetFilterJetMatcher::endJob() {
}

 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SubjetFilterJetMatcher::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SubjetFilterJetMatcher);
