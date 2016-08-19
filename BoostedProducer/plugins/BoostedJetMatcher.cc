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
  recoFatJetsToken            = consumes< std::vector<reco::PFJet> >            (iConfig.getParameter<edm::InputTag>("recoFatJetsTag"));
  recoTopJetsToken            = consumes< std::vector<reco::BasicJet> >         (iConfig.getParameter<edm::InputTag>("recoTopJetsTag"));
  recoSFJetsToken             = consumes< std::vector<reco::BasicJet> >         (iConfig.getParameter<edm::InputTag>("recoSFJetsTag"));
  recoPrunedJetsToken         = consumes< std::vector<reco::BasicJet> >         (iConfig.getParameter<edm::InputTag>("recoPrunedJetsTag"));
  recoSDJetsToken             = consumes< std::vector<reco::BasicJet> >         (iConfig.getParameter<edm::InputTag>("recoSDJetsTag"));
  recoSDJetsforSToken         = consumes< std::vector<reco::PFJet> >            (iConfig.getParameter<edm::InputTag>("recoSDJetsForSubjettinessTag"));
  patFatJetsToken             = consumes< edm::View<pat::Jet> >                 (iConfig.getParameter<edm::InputTag>("patFatJetsTag"));
  patHTTTopJetsToken          = consumes< edm::View<pat::Jet> >                 (iConfig.getParameter<edm::InputTag>("patTopJetsTag"));
  patHTTSubjetsToken          = consumes< edm::View<pat::Jet> >                 (iConfig.getParameter<edm::InputTag>("patTopSubjetsTag"));
  httInfosToken               = consumes< std::vector<reco::HTTTopJetTagInfo> > (iConfig.getParameter<edm::InputTag>("httInfosTag"));
  patSFSubjetsToken           = consumes< edm::View<pat::Jet> >                 (iConfig.getParameter<edm::InputTag>("patSFSubjetsTag"));
  patSFFilterjetsToken        = consumes< edm::View<pat::Jet> >                 (iConfig.getParameter<edm::InputTag>("patSFFilterjetsTag"));
  patPrunedSubjetsToken       = consumes< edm::View<pat::Jet> >                 (iConfig.getParameter<edm::InputTag>("patPrunedSubjetsTag"));
  patSDSubjetsToken           = consumes< edm::View<pat::Jet> >                 (iConfig.getParameter<edm::InputTag>("patSDSubjetsTag"));
  softdropSubjettiness1Token  = consumes< edm::ValueMap<float> >                (iConfig.getParameter<edm::InputTag>("softdropSubjettiness1Tag"));
  softdropSubjettiness2Token  = consumes< edm::ValueMap<float> >                (iConfig.getParameter<edm::InputTag>("softdropSubjettiness2Tag"));
  softdropSubjettiness3Token  = consumes< edm::ValueMap<float> >                (iConfig.getParameter<edm::InputTag>("softdropSubjettiness3Tag"));


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
  edm::Handle< std::vector<reco::PFJet> > recoFatJetsHandle;
  iEvent.getByToken(recoFatJetsToken, recoFatJetsHandle);
  std::vector<reco::PFJet> recofatjets = *recoFatJetsHandle;

  edm::Handle< std::vector<reco::BasicJet> > recoTopJetsHandle;
  iEvent.getByToken(recoTopJetsToken, recoTopJetsHandle);
  std::vector<reco::BasicJet> recoTopJets = *recoTopJetsHandle;

  edm::Handle< std::vector<reco::BasicJet> > recoSFJetsHandle;
  iEvent.getByToken(recoSFJetsToken, recoSFJetsHandle);
  std::vector<reco::BasicJet> recosfjets = *recoSFJetsHandle;

  edm::Handle< std::vector<reco::BasicJet> > recoPrunedJetsHandle;
  iEvent.getByToken(recoPrunedJetsToken, recoPrunedJetsHandle);
  std::vector<reco::BasicJet> recoprunedjets = *recoPrunedJetsHandle;

  edm::Handle< std::vector<reco::BasicJet> > recoSDJetsHandle;
  iEvent.getByToken(recoSDJetsToken, recoSDJetsHandle);
  std::vector<reco::BasicJet> recosdjets = *recoSDJetsHandle;

  edm::Handle< std::vector<reco::PFJet> > recoSDJetsforSHandle;
  iEvent.getByToken(recoSDJetsforSToken, recoSDJetsforSHandle);
  std::vector<reco::PFJet> recosdjetsfors = *recoSDJetsforSHandle;

  edm::Handle<edm::View<pat::Jet> > patFatJetsHandle;
  iEvent.getByToken(patFatJetsToken, patFatJetsHandle);
  edm::View<pat::Jet> patfatjets = *patFatJetsHandle;

  edm::Handle<edm::View<pat::Jet> > patHTTTopJetsHandle;
  iEvent.getByToken(patHTTTopJetsToken, patHTTTopJetsHandle);
  edm::View<pat::Jet> pathtttopjets = *patHTTTopJetsHandle;

  edm::Handle<edm::View<pat::Jet> > patHTTSubjetsHandle;
  iEvent.getByToken(patHTTSubjetsToken, patHTTSubjetsHandle);
  edm::View<pat::Jet> pathttsubjets = *patHTTSubjetsHandle;

  edm::Handle<std::vector<reco::HTTTopJetTagInfo> > httInfosHandle;
  iEvent.getByToken(httInfosToken, httInfosHandle);
  std::vector<reco::HTTTopJetTagInfo> httinfos = *httInfosHandle;

  edm::Handle<edm::View<pat::Jet> > patSFSubjetsHandle;
  iEvent.getByToken(patSFSubjetsToken, patSFSubjetsHandle);
  edm::View<pat::Jet> patsfsubjets = *patSFSubjetsHandle;

  edm::Handle<edm::View<pat::Jet> > patSFFilterjetsHandle;
  iEvent.getByToken(patSFFilterjetsToken, patSFFilterjetsHandle);
  edm::View<pat::Jet> patsffilterjets = *patSFFilterjetsHandle;

  edm::Handle<edm::View<pat::Jet> > patPrunedSubjetsHandle;
  iEvent.getByToken(patPrunedSubjetsToken, patPrunedSubjetsHandle);
  edm::View<pat::Jet> patprunedsubjets = *patPrunedSubjetsHandle;

  edm::Handle<edm::View<pat::Jet> > patSDSubjetsHandle;
  iEvent.getByToken(patSDSubjetsToken, patSDSubjetsHandle);
  edm::View<pat::Jet> patsdsubjets = *patSDSubjetsHandle;

  edm::Handle<edm::ValueMap<float> > softdropSubjettiness1Handle;
  iEvent.getByToken(softdropSubjettiness1Token, softdropSubjettiness1Handle);
  edm::ValueMap<float> softdropSubjettiness1 = *softdropSubjettiness1Handle;

  edm::Handle<edm::ValueMap<float> > softdropSubjettiness2Handle;
  iEvent.getByToken(softdropSubjettiness2Token, softdropSubjettiness2Handle);
  edm::ValueMap<float> softdropSubjettiness2 = *softdropSubjettiness2Handle;

  edm::Handle<edm::ValueMap<float> > softdropSubjettiness3Handle;
  iEvent.getByToken(softdropSubjettiness3Token, softdropSubjettiness3Handle);
  edm::ValueMap<float> softdropSubjettiness3 = *softdropSubjettiness3Handle;

  std::multimap<double, int> patfatjetindex_by_eta;
  std::multimap<double, int> pathtttopjetindex_by_eta;
  std::multimap<double, int> pathttsubjetindex_by_eta;
  std::multimap<double, int> patsfsubjetindex_by_eta;
  std::multimap<double, int> patsffilterjetindex_by_eta;
  std::multimap<double, int> patprunedsubjetindex_by_eta;
  std::multimap<double, int> patsdsubjetindex_by_eta;

  for(size_t i=0; i<patfatjets.size(); ++i) patfatjetindex_by_eta.insert(std::pair<double,int>(patfatjets[i].eta(), i));
  for(size_t i=0; i<pathtttopjets.size(); ++i) pathtttopjetindex_by_eta.insert(std::pair<double,int>(pathtttopjets[i].eta(), i));
  for(size_t i=0; i<pathttsubjets.size(); ++i) pathttsubjetindex_by_eta.insert(std::pair<double,int>(pathttsubjets[i].eta(), i));
  for(size_t i=0; i<patsfsubjets.size(); ++i) patsfsubjetindex_by_eta.insert(std::pair<double,int>(patsfsubjets[i].eta(), i));
  for(size_t i=0; i<patsffilterjets.size(); ++i) patsffilterjetindex_by_eta.insert(std::pair<double,int>(patsffilterjets[i].eta(), i));
  for(size_t i=0; i<patprunedsubjets.size(); ++i) patprunedsubjetindex_by_eta.insert(std::pair<double,int>(patprunedsubjets[i].eta(), i));
  for(size_t i=0; i<patsdsubjets.size(); ++i) patsdsubjetindex_by_eta.insert(std::pair<double,int>(patsdsubjets[i].eta(), i));

  std::auto_ptr<boosted::BoostedJetCollection> BoostedJets(new boosted::BoostedJetCollection());

  for(typename std::vector<reco::PFJet>::const_iterator it=recofatjets.begin();it!=recofatjets.end();++it){

    BoostedJets->push_back(boosted::BoostedJet());

    BoostedJets->back().fatjet = patrecoJetMatching(patfatjets,patfatjetindex_by_eta,*it);

    // get HTT V2 information
    int httrecojetid = recorecoJetMatching(*it,recoTopJets,1.0);

    if(httrecojetid>=0){
      BoostedJets->back().topjet = patrecoJetMatching(pathtttopjets, pathtttopjetindex_by_eta, recoTopJets[httrecojetid]);

      std::vector<const reco::Candidate*> recohttsubjets = recoTopJets[httrecojetid].getJetConstituentsQuick();
      for(std::vector<const reco::Candidate*>::const_iterator itSub=recohttsubjets.begin();itSub!=recohttsubjets.end();++itSub){
        int iSub = itSub-recohttsubjets.begin();
        const pat::Jet & patsubjet = patrecoJetMatching(pathttsubjets, pathttsubjetindex_by_eta, **itSub);

        if(iSub==0) BoostedJets->back().W1    = patsubjet;
        if(iSub==1) BoostedJets->back().W2    = patsubjet;
        if(iSub==2) BoostedJets->back().nonW  = patsubjet;

        if(iSub>2) std::cout << "Error! More than 3 Subjets in reco::BasicJet" << std::endl;
      }

      reco::HTTTopJetProperties httproperties = httinfos[httrecojetid].properties();
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
    }

    // get Subjet Filterjet information
    int sfrecojetid = recorecoJetMatching(*it,recosfjets,1.0);

    if(sfrecojetid>=0){
      std::vector<const reco::Candidate*> recosfsubjets = recosfjets[sfrecojetid].getJetConstituentsQuick();

      for(std::vector<const reco::Candidate*>::const_iterator itSub=recosfsubjets.begin();itSub!=recosfsubjets.end();++itSub){
        int iSub = itSub-recosfsubjets.begin();

        if(iSub<2) BoostedJets->back().subjets.push_back(patrecoJetMatching(patsfsubjets, patsfsubjetindex_by_eta, **itSub));
        else BoostedJets->back().filterjets.push_back(patrecoJetMatching(patsffilterjets, patsffilterjetindex_by_eta, **itSub));
      }
    }

    // get pruned jets information
    int prunedrecojetid = recorecoJetMatching(*it,recoprunedjets,1.0);

    if(prunedrecojetid>=0){
      std::vector<const reco::Candidate*> recoprunedsubjets = recoprunedjets[prunedrecojetid].getJetConstituentsQuick();

      for(std::vector<const reco::Candidate*>::const_iterator itSub=recoprunedsubjets.begin();itSub!=recoprunedsubjets.end();++itSub){
        BoostedJets->back().prunedsubjets.push_back(patrecoJetMatching(patprunedsubjets, patprunedsubjetindex_by_eta, **itSub));
      }
    }
    // get soft drop jets information
    int sdrecojetid = recorecoJetMatching(*it,recosdjets,1.0);

    if(sdrecojetid>=0){
      std::vector<const reco::Candidate*> recosdsubjets = recosdjets[sdrecojetid].getJetConstituentsQuick();

      for(std::vector<const reco::Candidate*>::const_iterator itSub=recosdsubjets.begin();itSub!=recosdsubjets.end();++itSub){
        BoostedJets->back().sdsubjets.push_back(patrecoJetMatching(patsdsubjets, patsdsubjetindex_by_eta, **itSub));
      }

      BoostedJets->back().tau1Softdrop = softdropSubjettiness1.get(recoSDJetsforSHandle.id(),sdrecojetid);
      BoostedJets->back().tau2Softdrop = softdropSubjettiness2.get(recoSDJetsforSHandle.id(),sdrecojetid);
      BoostedJets->back().tau3Softdrop = softdropSubjettiness3.get(recoSDJetsforSHandle.id(),sdrecojetid);
    }
  }

  iEvent.put(BoostedJets,"boostedjets");
}


template<typename recojettype>
const pat::Jet & BoostedJetMatcher::patrecoJetMatching(const edm::View<pat::Jet> & patjets, const std::multimap<double, int> & patjetindex_by_eta, const recojettype & recojet){
	std::multimap<double, int>::const_iterator lower = patjetindex_by_eta.lower_bound(recojet.eta() - 0.01);
	std::multimap<double, int>::const_iterator upper = patjetindex_by_eta.upper_bound(recojet.eta() + 0.01);

	double delta_r = 9999.0;
	int best_match = -1;

  int counter = 0;

	for(std::multimap<double, int>::const_iterator it=lower; it!=upper; ++it,++counter){

    double delta_r_temp = reco::deltaR(patjets[it->second], recojet);

    if(best_match == -1 || delta_r_temp < delta_r){
			best_match = it->second;
			delta_r = delta_r_temp;
		}
	}

	if(best_match >= 0) return patjets[best_match];
	throw std::string("patrecoJetMatching: could not find matching jet.");
}


template<typename recojettype1, typename recojettype2>
const int BoostedJetMatcher::recorecoJetMatching(const recojettype1 & recojet, const std::vector<recojettype2> & recojets, const float & matchingdistance){
	typename std::vector<recojettype2>::const_iterator lower = recojets.begin();
  typename std::vector<recojettype2>::const_iterator upper = recojets.end();

  double delta_r = 9999;
	int best_match = -1;

  for(typename std::vector<recojettype2>::const_iterator it=lower; it!=upper; ++it){

    float delta_r_temp = reco::deltaR(*it,recojet);

	  if( delta_r_temp < matchingdistance && (best_match == -1 || delta_r_temp < delta_r)){
			best_match = it-lower;
			delta_r = delta_r_temp;
		}
	}

  return best_match;
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
