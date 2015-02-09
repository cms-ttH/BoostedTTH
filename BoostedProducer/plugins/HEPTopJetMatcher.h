#ifndef BOOSTEDTTH_BOOSTEDPRODUCERS_HEPTOPJETMATCHER_H
#define BOOSTEDTTH_BOOSTEDPRODUCERS_HEPTOPJETMATCHER_H 1

// -*- C++ -*-
//
// Package:    BoostedTTH/BoostedProducer/HEPTopJetMatcher
// Class:      HEPTopJetMatcher
// 
/**\class SubjetFilterJetMatcher SubjetFilterJetMatcher.cc BoostedTTH/BoostedProducer/plugins/HEPTopJetMatcher.cc

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
#include "BoostedTTH/BoostedObjects/interface/HEPTopJet.h"
#include "DataFormats/Math/interface/deltaR.h"

//
// class declaration
//

class HEPTopJetMatcher : public edm::EDProducer {
   
  public:

    explicit HEPTopJetMatcher(const edm::ParameterSet&);
    ~HEPTopJetMatcher();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


  private:

    virtual void beginJob() override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    template<typename recojettype>
    const pat::Jet & deltarJetMatching(const edm::View<pat::Jet> & patjets, const std::multimap<double, int> & patjetindex_by_eta, const recojettype & rjet);
  
  
    // ----------member data ---------------------------
    double minJetPt; 
    
    edm::InputTag recofatjetsTag_;
    edm::InputTag patfatjetsTag_;
    edm::InputTag patsubjetsTag_;
    edm::InputTag toptagsTag_;
    edm::InputTag subjettiness1Tag_;
    edm::InputTag subjettiness2Tag_;
    edm::InputTag subjettiness3Tag_;
    edm::InputTag subjettiness4Tag_;
    
};

#endif
