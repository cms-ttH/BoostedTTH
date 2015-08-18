// -*- C++ -*-
//
// Package:    BoostedTTH/BoostedProducer/BoostedJetMatcher
// Class:      SubjetFilterJetMatcher
// 
/**\class BoostedJetMatcher BoostedJetMatcher.cc BoostedTTH/BoostedProducer/plugins/BoostedJetMatcher.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shawn Williamson
//         Created:  Fri, 23 Jan 2015 08:17:01 GMT
//
//

#include "BoostedTTH/BoostedProducer/plugins/BoostedJetMatcher.h"

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
BoostedJetMatcher::BoostedJetMatcher(const edm::ParameterSet& iConfig):
  recoFatJetsTag_(iConfig.getParameter<edm::InputTag>("recoFatJetsTag")),
  patFatJetsTag_(iConfig.getParameter<edm::InputTag>("patFatJetsTag")),
  recoTopJetsTag_(iConfig.getParameter<edm::InputTag>("recoTopJetsTag")),
  patTopJetsTag_(iConfig.getParameter<edm::InputTag>("patTopJetsTag")),
  patTopSubjetsTag_(iConfig.getParameter<edm::InputTag>("patTopSubjetsTag")),
  httInfosTag_(iConfig.getParameter<edm::InputTag>("httInfosTag")),
  patSFSubJetsTag_(iConfig.getParameter<edm::InputTag>("patSFSubJetsTag")),
  patSFFilterJetsTag_(iConfig.getParameter<edm::InputTag>("patSFFilterJetsTag"))
{
  produces<boosted::BoostedJetCollection>("boostedjets");
}


BoostedJetMatcher::~BoostedJetMatcher()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
BoostedJetMatcher::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  edm::Handle< std::vector<reco::BasicJet> > recoFatJetsHandle;
  iEvent.getByLabel(recoFatJetsTag_, recoFatJetsHandle);
  std::vector<reco::BasicJet> recofatjets = *recoFatJetsHandle;
  
  edm::Handle< std::vector<reco::BasicJet> > recoTopJetsHandle;
  iEvent.getByLabel(recoTopJetsTag_, recoTopJetsHandle);
  std::vector<reco::BasicJet> recotopjets = *recoTopJetsHandle;
  
  edm::Handle<edm::View<pat::Jet> > patFatJetsHandle;
  iEvent.getByLabel(patFatJetsTag_, patFatJetsHandle);
  edm::View<pat::Jet> patfatjets = *patFatJetsHandle;
  
  edm::Handle<edm::View<pat::Jet> > patTopJetsHandle;
  iEvent.getByLabel(patTopJetsTag_, patTopJetsHandle);
  edm::View<pat::Jet> pattopjets = *patTopJetsHandle;
  
  edm::Handle<edm::View<pat::Jet> > patTopSubjetsHandle;
  iEvent.getByLabel(patTopSubjetsTag_, patTopSubjetsHandle);
  edm::View<pat::Jet> pattopsubjets = *patTopSubjetsHandle;
  
  edm::Handle<std::vector<reco::HTTTopJetTagInfo> > httInfosHandle;
  iEvent.getByLabel(httInfosTag_, httInfosHandle);
  std::vector<reco::HTTTopJetTagInfo> httinfos = *httInfosHandle;
  
  edm::Handle<edm::View<pat::Jet> > patSFSubJetsHandle;
  iEvent.getByLabel(patSFSubJetsTag_, patSFSubJetsHandle);
  edm::View<pat::Jet> patsfsubjets = *patSFSubJetsHandle;
	
  edm::Handle<edm::View<pat::Jet> > patSFFilterJetsHandle;
  iEvent.getByLabel(patSFFilterJetsTag_, patSFFilterJetsHandle);
  edm::View<pat::Jet> patsffilterjets = *patSFFilterJetsHandle;
  
  std::multimap<double, int> patfatjetindex_by_eta;
  std::multimap<double, int> pattopjetindex_by_eta;
  std::multimap<double, int> pattopsubjetindex_by_eta;
  std::multimap<double, int> patsfsubjetindex_by_eta;
  std::multimap<double, int> patsffilterjetindex_by_eta;
  
  for(size_t i=0; i<patfatjets.size(); ++i) patfatjetindex_by_eta.insert(std::pair<double,int>(patfatjets[i].eta(), i));
  for(size_t i=0; i<pattopjets.size(); ++i) pattopjetindex_by_eta.insert(std::pair<double,int>(pattopjets[i].eta(), i));
  for(size_t i=0; i<pattopsubjets.size(); ++i) pattopsubjetindex_by_eta.insert(std::pair<double,int>(pattopsubjets[i].eta(), i));
  for(size_t i=0; i<patsfsubjets.size(); ++i) patsfsubjetindex_by_eta.insert(std::pair<double,int>(patsfsubjets[i].eta(), i));
  for(size_t i=0; i<patsffilterjets.size(); ++i) patsffilterjetindex_by_eta.insert(std::pair<double,int>(patsffilterjets[i].eta(), i));
  
  std::auto_ptr<boosted::BoostedJetCollection> BoostedJets(new boosted::BoostedJetCollection());
  
  for(typename std::vector<reco::BasicJet>::const_iterator it=recofatjets.begin();it!=recofatjets.end();++it){
    
    BoostedJets->push_back(boosted::BoostedJet());
    
    BoostedJets->back().fatjet 		          = deltarJetMatching(patfatjets, patfatjetindex_by_eta, *it);
    
    std::vector<const reco::Candidate*> recosfsubjets = it->getJetConstituentsQuick();
    for(std::vector<const reco::Candidate*>::const_iterator itSub=recosfsubjets.begin();itSub!=recosfsubjets.end();++itSub){
      int iSub = itSub-recosfsubjets.begin();
      
      if(iSub<2) BoostedJets->back().subjets.push_back(deltarJetMatching(patsfsubjets, patsfsubjetindex_by_eta, **itSub));
      else BoostedJets->back().filterjets.push_back(deltarJetMatching(patsffilterjets, patsffilterjetindex_by_eta, **itSub));
    }
    
    int topSubstructureID = deltarTopJetMatching<reco::Jet>(*it,recotopjets);
    
    if(topSubstructureID<0) continue;
    
    BoostedJets->back().topjet 		          = deltarJetMatching(pattopjets, pattopjetindex_by_eta, recotopjets[topSubstructureID]);
    
    reco::HTTTopJetProperties httproperties = httinfos[topSubstructureID].properties();
    BoostedJets->back().fatjetMass 		      = httproperties.fjMass;
    BoostedJets->back().fatjetPt 		        = httproperties.fjPt;
    BoostedJets->back().fatjetEta 		      = httproperties.fjEta;
    BoostedJets->back().fatjetPhi 		      = httproperties.fjPhi;
    BoostedJets->back().topMass 		        = httproperties.topMass;
    BoostedJets->back().unfilteredMass	    = httproperties.unfilteredMass;
    BoostedJets->back().prunedMass 		      = httproperties.prunedMass;
    BoostedJets->back().fRec 		            = httproperties.fRec;
    BoostedJets->back().massRatioPassed     = httproperties.massRatioPassed;
    BoostedJets->back().Ropt 		            = httproperties.Ropt;
    BoostedJets->back().RoptCalc 		        = httproperties.RoptCalc;
    BoostedJets->back().ptForRoptCalc	      = httproperties.ptForRoptCalc;
    BoostedJets->back().tau1Unfiltered 	    = httproperties.tau1Unfiltered;
    BoostedJets->back().tau2Unfiltered 	    = httproperties.tau2Unfiltered;
    BoostedJets->back().tau3Unfiltered 	    = httproperties.tau3Unfiltered;
    BoostedJets->back().tau1Filtered 		    = httproperties.tau1Filtered;
    BoostedJets->back().tau2Filtered 		    = httproperties.tau2Filtered;
    BoostedJets->back().tau3Filtered 		    = httproperties.tau3Filtered;
    BoostedJets->back().qWeight 		        = httproperties.QWeight;
    BoostedJets->back().qEpsilon 		        = httproperties.QEpsilon;
    BoostedJets->back().qSigmaM 		        = httproperties.QSigmaM;
    
    std::vector<const reco::Candidate*> recotopsubjets = recotopjets[topSubstructureID].getJetConstituentsQuick();
    
    for(std::vector<const reco::Candidate*>::const_iterator itSub=recotopsubjets.begin();itSub!=recotopsubjets.end();++itSub){
      int iSub = itSub-recotopsubjets.begin();
      
      const pat::Jet & patsubjet = deltarJetMatching(pattopsubjets, pattopsubjetindex_by_eta, **itSub);
      
      if(iSub==0) BoostedJets->back().W1    = patsubjet;
      if(iSub==1) BoostedJets->back().W2    = patsubjet;
      if(iSub==2) BoostedJets->back().nonW  = patsubjet;
      
      if(iSub>2) std::cout << "Error! More than 3 Subjets in reco::BasicJet" << std::endl;
    }
  }
  
  iEvent.put(BoostedJets,"boostedjets");
}


template<typename recojettype>
const pat::Jet & BoostedJetMatcher::deltarJetMatching(const edm::View<pat::Jet> & patjets, const std::multimap<double, int> & patjetindex_by_eta, const recojettype & recojet){
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


template<typename recojettype>
const int BoostedJetMatcher::deltarTopJetMatching(const recojettype & recofatjet, const std::vector<reco::BasicJet> & recotopjets){
	
  std::vector<reco::BasicJet>::const_iterator lower = recotopjets.begin();
  std::vector<reco::BasicJet>::const_iterator upper = recotopjets.end();
  
  double delta_r = 9999;
	int best_match = -1;

  for(std::vector<reco::BasicJet>::const_iterator it=lower; it!=upper; ++it){

	  if(best_match == -1 || reco::deltaR(*it,recofatjet) < delta_r){
			best_match = it-lower;
			delta_r = reco::deltaR(*it,recofatjet);
		}
	}
  
  if(delta_r<1.5)
	  return best_match;
  else
    return -1;
}



// ------------ method called once each job just before starting event loop  ------------
void 
BoostedJetMatcher::beginJob()
{
}


// ------------ method called once each job just after ending the event loop  ------------
void 
BoostedJetMatcher::endJob() {
}

 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BoostedJetMatcher::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BoostedJetMatcher);
