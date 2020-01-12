// -*- C++ -*-
//
// Package:    BoostedTTH/Ele32DoubleL1ToSingleL1
// Class:      Ele32DoubleL1ToSingleL1
//
/**\class Ele32DoubleL1ToSingleL1 Ele32DoubleL1ToSingleL1.cc BoostedTTH/Ele32DoubleL1ToSingleL1/plugins/Ele32DoubleL1ToSingleL1.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Michael Wassmer
//         Created:  Sun, 12 Jan 2020 14:14:42 GMT
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Common/interface/View.h"
//
// class declaration
//

class Ele32DoubleL1ToSingleL1 : public edm::stream::EDFilter<> {
   public:
    explicit Ele32DoubleL1ToSingleL1(const edm::ParameterSet&);
    ~Ele32DoubleL1ToSingleL1();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
    virtual void                                       beginStream(edm::StreamID) override;
    virtual bool                                       filter(edm::Event&, const edm::EventSetup&) override;
    virtual void                                       endStream() override;
    std::vector< const pat::TriggerObjectStandAlone* > getMatchedObjs(const float eta, const float phi,
                                                                      const std::vector< pat::TriggerObjectStandAlone >& trigObjs, const float maxDeltaR);

    // virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    // virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    // virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    // virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

    // ----------member data ---------------------------
    edm::EDGetTokenT< edm::TriggerResults >                         trigResultsToken_;
    edm::EDGetTokenT< std::vector< pat::TriggerObjectStandAlone > > trigObjsToken_;
    edm::EDGetTokenT< edm::View< pat::Electron > >                  elesToken_;
    bool                                                            tagging_mode_;
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
Ele32DoubleL1ToSingleL1::Ele32DoubleL1ToSingleL1(const edm::ParameterSet& iConfig) :
    trigResultsToken_{consumes< edm::TriggerResults >(iConfig.getParameter< edm::InputTag >("trigResults"))},
    trigObjsToken_{consumes< std::vector< pat::TriggerObjectStandAlone > >(iConfig.getParameter< edm::InputTag >("trigObjs"))},
    elesToken_{consumes< edm::View< pat::Electron > >(iConfig.getParameter< edm::InputTag >("eles"))},
    tagging_mode_{iConfig.getParameter< bool >("tagging_mode")}
{
    // now do what ever initialization is needed
    produces< bool >("Ele32DoubleL1ToSingleL1");
}

Ele32DoubleL1ToSingleL1::~Ele32DoubleL1ToSingleL1()
{
    // do anything here that needs to be done at destruction time
    // (e.g. close files, deallocate resources etc.)
}

//
// member functions
//

// ------------ method called on each new Event  ------------
bool Ele32DoubleL1ToSingleL1::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    edm::Handle< edm::TriggerResults > trigResults;
    iEvent.getByToken(trigResultsToken_, trigResults);
    edm::Handle< std::vector< pat::TriggerObjectStandAlone > > trigObjs;
    iEvent.getByToken(trigObjsToken_, trigObjs);
    edm::Handle< edm::View< pat::Electron > > eles;
    iEvent.getByToken(elesToken_, eles);

    bool found = false;

    std::vector< pat::TriggerObjectStandAlone > unpackedTrigObjs;
    for (auto& trigObj : *trigObjs) {
        unpackedTrigObjs.push_back(trigObj);
        unpackedTrigObjs.back().unpackFilterLabels(iEvent, *trigResults);
    }

    for (auto& ele : *eles) {
        // std::cout << "found: " << found << std::endl;
        // the eta/phi of e/gamma trigger objects is the supercluster eta/phi
        const float eta = ele.superCluster()->eta();
        const float phi = ele.superCluster()->phi();
        // std::cout << "ele eta: " << eta << std::endl;
        // std::cout << "ele phi: " << phi << std::endl;
        // now match ALL objects in a cone of DR<0.1
        // it is important to match all objects as there are different ways to reconstruct the same electron
        // eg, L1 seeded, unseeded, as a jet etc
        // and so you want to be sure you get all possible objects
        std::vector< const pat::TriggerObjectStandAlone* > matchedTrigObjs = getMatchedObjs(eta, phi, unpackedTrigObjs, 0.1);
        for (const auto trigObj : matchedTrigObjs) {
            // now just check if it passes the two filters
            if (trigObj->hasFilterLabel("hltEle32L1DoubleEGWPTightGsfTrackIsoFilter") && trigObj->hasFilterLabel("hltEGL1SingleEGOrFilter")) {
                found = true;
                // std::cout << " ele " << ele.et() << " " << eta << " " << phi << " passes HLT_Ele32_WPTight_Gsf" << std::endl;
                if (tagging_mode_) iEvent.put(std::unique_ptr< bool >(new bool(found)), "Ele32DoubleL1ToSingleL1");
                return true;
            }
        }
    }
    if (tagging_mode_) iEvent.put(std::unique_ptr< bool >(new bool(found)), "Ele32DoubleL1ToSingleL1");
    return tagging_mode_ || found;
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void Ele32DoubleL1ToSingleL1::beginStream(edm::StreamID) {}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void Ele32DoubleL1ToSingleL1::endStream() {}

// ------------ method called when starting to processes a run  ------------
/*
void
Ele32DoubleL1ToSingleL1::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void
Ele32DoubleL1ToSingleL1::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void
Ele32DoubleL1ToSingleL1::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
Ele32DoubleL1ToSingleL1::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void Ele32DoubleL1ToSingleL1::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
    // The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}
std::vector< const pat::TriggerObjectStandAlone* > Ele32DoubleL1ToSingleL1::getMatchedObjs(const float eta, const float phi,
                                                                                           const std::vector< pat::TriggerObjectStandAlone >& trigObjs,
                                                                                           const float                                        maxDeltaR = 0.1)
{
    std::vector< const pat::TriggerObjectStandAlone* > matchedObjs;
    const float                                        maxDR2 = maxDeltaR * maxDeltaR;
    for (auto& trigObj : trigObjs) {
        const float dR2 = reco::deltaR2(eta, phi, trigObj.eta(), trigObj.phi());
        if (dR2 < maxDR2) matchedObjs.push_back(&trigObj);
    }
    return matchedObjs;
}
// define this as a plug-in
DEFINE_FWK_MODULE(Ele32DoubleL1ToSingleL1);
