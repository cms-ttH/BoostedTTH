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
BoostedJetMatcher::BoostedJetMatcher(const edm::ParameterSet& iConfig)
{
  recoFatJetsToken      = consumes< std::vector<reco::BasicJet> >         (iConfig.getParameter<edm::InputTag>("recoFatJetsTag"));
  recoTopJetsToken      = consumes< std::vector<reco::BasicJet> >         (iConfig.getParameter<edm::InputTag>("recoTopJetsTag"));
  patFatJetsToken       = consumes< edm::View<pat::Jet> >                 (iConfig.getParameter<edm::InputTag>("patFatJetsTag"));
  patTopJetsToken       = consumes< edm::View<pat::Jet> >                 (iConfig.getParameter<edm::InputTag>("patTopJetsTag"));
  patTopSubjetsToken    = consumes< edm::View<pat::Jet> >                 (iConfig.getParameter<edm::InputTag>("patTopSubjetsTag"));
  httInfosToken         = consumes< std::vector<reco::HTTTopJetTagInfo> > (iConfig.getParameter<edm::InputTag>("httInfosTag"));
  patSFSubJetsToken     = consumes< edm::View<pat::Jet> >                 (iConfig.getParameter<edm::InputTag>("patSFSubJetsTag"));
  patSFFilterJetsToken  = consumes< edm::View<pat::Jet> >                 (iConfig.getParameter<edm::InputTag>("patSFFilterJetsTag"));

  softdropSubjettiness1Token = consumes< edm::ValueMap<float> >           (iConfig.getParameter<edm::InputTag>("softdropSubjettiness1Tag"));
  softdropSubjettiness2Token = consumes< edm::ValueMap<float> >           (iConfig.getParameter<edm::InputTag>("softdropSubjettiness2Tag"));
  softdropSubjettiness3Token = consumes< edm::ValueMap<float> >           (iConfig.getParameter<edm::InputTag>("softdropSubjettiness3Tag"));
  recoSDZ2B1JetsToken   = consumes< std::vector<reco::BasicJet> >         (iConfig.getParameter<edm::InputTag>("recoSDZ2B1JetsTag"));
  recoSubJetsToken      = consumes< std::vector<reco::PFJet> >            (iConfig.getParameter<edm::InputTag>("recoSubJetsTag"));
  
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
  iEvent.getByToken(recoFatJetsToken, recoFatJetsHandle);
  std::vector<reco::BasicJet> recofatjets = *recoFatJetsHandle;
  
  edm::Handle< std::vector<reco::BasicJet> > recoTopJetsHandle;
  iEvent.getByToken(recoTopJetsToken, recoTopJetsHandle);
  std::vector<reco::BasicJet> recotopjets = *recoTopJetsHandle;
  
  edm::Handle<edm::View<pat::Jet> > patFatJetsHandle;
  iEvent.getByToken(patFatJetsToken, patFatJetsHandle);
  edm::View<pat::Jet> patfatjets = *patFatJetsHandle;
  
  edm::Handle<edm::View<pat::Jet> > patTopJetsHandle;
  iEvent.getByToken(patTopJetsToken, patTopJetsHandle);
  edm::View<pat::Jet> pattopjets = *patTopJetsHandle;
  
  edm::Handle<edm::View<pat::Jet> > patTopSubjetsHandle;
  iEvent.getByToken(patTopSubjetsToken, patTopSubjetsHandle);
  edm::View<pat::Jet> pattopsubjets = *patTopSubjetsHandle;
  
  edm::Handle<std::vector<reco::HTTTopJetTagInfo> > httInfosHandle;
  iEvent.getByToken(httInfosToken, httInfosHandle);
  std::vector<reco::HTTTopJetTagInfo> httinfos = *httInfosHandle;
  
  edm::Handle<edm::View<pat::Jet> > patSFSubJetsHandle;
  iEvent.getByToken(patSFSubJetsToken, patSFSubJetsHandle);
  edm::View<pat::Jet> patsfsubjets = *patSFSubJetsHandle;
	
  edm::Handle<edm::View<pat::Jet> > patSFFilterJetsHandle;
  iEvent.getByToken(patSFFilterJetsToken, patSFFilterJetsHandle);
  edm::View<pat::Jet> patsffilterjets = *patSFFilterJetsHandle;
  
  edm::Handle<edm::ValueMap<float> > softdropSubjettiness1Handle;
  iEvent.getByToken(softdropSubjettiness1Token, softdropSubjettiness1Handle);
  edm::ValueMap<float> softdropSubjettiness1 = *softdropSubjettiness1Handle;
  
  edm::Handle<edm::ValueMap<float> > softdropSubjettiness2Handle;
  iEvent.getByToken(softdropSubjettiness2Token, softdropSubjettiness2Handle);
  edm::ValueMap<float> softdropSubjettiness2 = *softdropSubjettiness2Handle;
  
  edm::Handle<edm::ValueMap<float> > softdropSubjettiness3Handle;
  iEvent.getByToken(softdropSubjettiness3Token, softdropSubjettiness3Handle);
  edm::ValueMap<float> softdropSubjettiness3 = *softdropSubjettiness3Handle;
  
  edm::Handle< std::vector<reco::BasicJet> > recoSDZ2B1JetsHandle;
  iEvent.getByToken(recoSDZ2B1JetsToken, recoSDZ2B1JetsHandle);
  std::vector<reco::BasicJet> recosdz2b1jets = *recoSDZ2B1JetsHandle;
  
  edm::Handle< std::vector<reco::PFJet> > recoSubJetsHandle;
  iEvent.getByToken(recoSubJetsToken, recoSubJetsHandle);
  std::vector<reco::PFJet> recosubjets = *recoSubJetsHandle;
  
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
  
  int nrecofatjet = -1;
  
  for(typename std::vector<reco::BasicJet>::const_iterator it=recofatjets.begin();it!=recofatjets.end();++it){
    ++nrecofatjet;
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
    
    BoostedJets->back().tau1Softdrop 		    = softdropSubjettiness1.get(nrecofatjet);
    BoostedJets->back().tau2Softdrop  		    = softdropSubjettiness2.get(nrecofatjet);
    BoostedJets->back().tau3Softdrop  		    = softdropSubjettiness3.get(nrecofatjet); 
    
    std::cout << softdropSubjettiness1.get(recoSubJetsHandle.id(),nrecofatjet) <<
    std::endl<< softdropSubjettiness2.get(recoSubJetsHandle.id(),nrecofatjet) <<
    std::endl<< softdropSubjettiness3.get(recoSubJetsHandle.id(),nrecofatjet) <<
    std::endl << "---" << std::endl;
    
    /*for (unsigned int it =0; it <= 10; it++)
    {
      std::cout << softdropSubjettiness3.get(it) <<" " << std:: endl;
    }*/
    
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
