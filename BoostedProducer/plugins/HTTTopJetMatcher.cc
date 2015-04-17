// -*- C++ -*-
//
// Package:    BoostedTTH/BoostedProducer/HTTTopJetMatcher
// Class:      SubjetFilterJetMatcher
// 
/**\class HTTTopJetMatcher HTTTopJetMatcher.cc BoostedTTH/BoostedProducer/plugins/HTTTopJetMatcher.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shawn Williamson
//         Created:  Fri, 23 Jan 2015 08:17:01 GMT
//
//

#include "BoostedTTH/BoostedProducer/plugins/HTTTopJetMatcher.h"

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
HTTTopJetMatcher::HTTTopJetMatcher(const edm::ParameterSet& iConfig)
{
  
  produces<boosted::HTTTopJetCollection>("htttopjets");
  
  recoFatJetsTag_=iConfig.getParameter<edm::InputTag>("recoFatJetsTag");
  patFatJetsTag_=iConfig.getParameter<edm::InputTag>("patFatJetsTag");
  patSubjetsTag_=iConfig.getParameter<edm::InputTag>("patSubjetsTag");
  httInfosTag_=iConfig.getParameter<edm::InputTag>("httInfosTag");
}


HTTTopJetMatcher::~HTTTopJetMatcher()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
HTTTopJetMatcher::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  
  edm::Handle< std::vector<reco::BasicJet> > recoFatJetsHandle;
  iEvent.getByLabel(recoFatJetsTag_, recoFatJetsHandle);
  std::vector<reco::BasicJet> recofatjets = *recoFatJetsHandle;
  
  edm::Handle<edm::View<pat::Jet> > patFatJetsHandle;
  iEvent.getByLabel(patFatJetsTag_, patFatJetsHandle);
  edm::View<pat::Jet> patfatjets = *patFatJetsHandle;
  
  edm::Handle<edm::View<pat::Jet> > patSubjetsHandle;
  iEvent.getByLabel(patSubjetsTag_, patSubjetsHandle);
  edm::View<pat::Jet> patsubjets = *patSubjetsHandle;
  
  edm::Handle<std::vector<reco::HTTTopJetTagInfo> > httInfosHandle;
  iEvent.getByLabel(httInfosTag_, httInfosHandle);
  std::vector<reco::HTTTopJetTagInfo> httinfos = *httInfosHandle;
  
  std::auto_ptr<boosted::HTTTopJetCollection> HTTTopJets(new boosted::HTTTopJetCollection());

  std::multimap<double, int> patfatjetindex_by_eta;
  std::multimap<double, int> patsubjetindex_by_eta;
  
  for(size_t i=0; i<patfatjets.size(); ++i) patfatjetindex_by_eta.insert(std::pair<double,int>(patfatjets[i].eta(), i));
  for(size_t i=0; i<patsubjets.size(); ++i) patsubjetindex_by_eta.insert(std::pair<double,int>(patsubjets[i].eta(), i));
  
  for(typename std::vector<reco::BasicJet>::const_iterator it=recofatjets.begin();it!=recofatjets.end();++it){
    
    HTTTopJets->push_back(boosted::HTTTopJet());
    HTTTopJets->back().fatjet 		      = deltarJetMatching(patfatjets, patfatjetindex_by_eta, *it);
    
    reco::HTTTopJetProperties httproperties = httinfos[it-recofatjets.begin()].properties();
    HTTTopJets->back().fatjetMass 		      = httproperties.fjMass;
    HTTTopJets->back().fatjetPt 		        = httproperties.fjPt;
    HTTTopJets->back().fatjetEta 		        = httproperties.fjEta;
    HTTTopJets->back().fatjetPhi 		        = httproperties.fjPhi;
    HTTTopJets->back().topMass 		          = httproperties.topMass;
    HTTTopJets->back().unfilteredMass	      = httproperties.unfilteredMass;
    HTTTopJets->back().prunedMass 		      = httproperties.prunedMass;
    HTTTopJets->back().fRec 		            = httproperties.fRec;
    HTTTopJets->back().massRatioPassed      = httproperties.massRatioPassed;
    HTTTopJets->back().Ropt 		            = httproperties.Ropt;
    HTTTopJets->back().RoptCalc 		        = httproperties.RoptCalc;
    HTTTopJets->back().ptForRoptCalc	      = httproperties.ptForRoptCalc;
    HTTTopJets->back().tau1Unfiltered 	    = httproperties.tau1Unfiltered;
    HTTTopJets->back().tau2Unfiltered 	    = httproperties.tau2Unfiltered;
    HTTTopJets->back().tau3Unfiltered 	    = httproperties.tau3Unfiltered;
    HTTTopJets->back().tau1Filtered 		    = httproperties.tau1Filtered;
    HTTTopJets->back().tau2Filtered 		    = httproperties.tau2Filtered;
    HTTTopJets->back().tau3Filtered 		    = httproperties.tau3Filtered;
    HTTTopJets->back().qWeight 		          = httproperties.QWeight;
    HTTTopJets->back().qEpsilon 		        = httproperties.QEpsilon;
    HTTTopJets->back().qSigmaM 		          = httproperties.QSigmaM;
    
    std::vector<const reco::Candidate*> recosubjets = it->getJetConstituentsQuick();
    
    for(size_t i=0;i<recosubjets.size(); ++i){
      const pat::Jet & patsubjet = deltarJetMatching(patsubjets, patsubjetindex_by_eta, *(recosubjets.at(i)));
      
      if(i==0) HTTTopJets->back().W1    = patsubjet;
      if(i==1) HTTTopJets->back().W2    = patsubjet;
      if(i==2) HTTTopJets->back().nonW  = patsubjet;
      
      if(i>2) std::cout << "Error! More than 3 Subjets in reco::BasicJet" << std::endl;
    }
  }
  
  iEvent.put(HTTTopJets,"htttopjets");
}


template<typename recojettype>
const pat::Jet & HTTTopJetMatcher::deltarJetMatching(const edm::View<pat::Jet> & patjets, const std::multimap<double, int> & patjetindex_by_eta, const recojettype & recojet){
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
HTTTopJetMatcher::beginJob()
{
}


// ------------ method called once each job just after ending the event loop  ------------
void 
HTTTopJetMatcher::endJob() {
}

 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HTTTopJetMatcher::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HTTTopJetMatcher);
