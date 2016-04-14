#ifndef BOOSTEDTTH_BOOSTEDPRODUCERS_BOOSTEDJETMATCHER_H
#define BOOSTEDTTH_BOOSTEDPRODUCERS_BOOSTEDJETMATCHER_H 1

// -*- C++ -*-
//
// Package:    BoostedTTH/BoostedProducer/BoostedJetMatcher
// Class:      BoostedJetMatcher
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


// system include files
#include <memory>
#include <vector>
#include <map>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "MiniAOD/BoostedObjects/interface/BoostedJet.h"
#include "DataFormats/JetReco/interface/HTTTopJetTagInfo.h"
#include "DataFormats/Math/interface/deltaR.h"

//
// class declaration
//

class BoostedJetMatcher : public edm::EDProducer {
   
  public:

    explicit BoostedJetMatcher(const edm::ParameterSet&);
    ~BoostedJetMatcher();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


  private:

    virtual void beginJob() override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    template<typename recojettype>
    const pat::Jet & deltarJetMatching(const edm::View<pat::Jet> & patjets, const std::multimap<double, int> & patjetindex_by_eta, const recojettype & rjet);
    template<typename recojettype>
    const int deltarTopJetMatching(const recojettype & recofatjet, const std::vector<reco::BasicJet> & recotopjets);

    // ---------- member data ---------------------------
    
    /** Jet Collection Access Tokens **/
    edm::EDGetTokenT< std::vector<reco::BasicJet> >         recoFatJetsToken;
    edm::EDGetTokenT< std::vector<reco::BasicJet> >         recoTopJetsToken;
    edm::EDGetTokenT< edm::View<pat::Jet> >                 patFatJetsToken;
    edm::EDGetTokenT< edm::View<pat::Jet> >                 patTopJetsToken;
    edm::EDGetTokenT< edm::View<pat::Jet> >                 patTopSubjetsToken;
    edm::EDGetTokenT< std::vector<reco::HTTTopJetTagInfo> > httInfosToken;
    edm::EDGetTokenT< edm::View<pat::Jet> >                 patSFSubJetsToken;
    edm::EDGetTokenT< edm::View<pat::Jet> >                 patSFFilterJetsToken;
    edm::EDGetTokenT< edm::ValueMap<float> >                softdropSubjettiness1Token;
    edm::EDGetTokenT< edm::ValueMap<float> >                softdropSubjettiness2Token;
    edm::EDGetTokenT< edm::ValueMap<float> >                softdropSubjettiness3Token;
    edm::EDGetTokenT< std::vector<reco::BasicJet> >         recoSDZ2B1JetsToken;
    edm::EDGetTokenT< std::vector<reco::PFJet> >            recoSubJetsToken;
};

#endif
