#ifndef SelectedJetProducer_h
#define SelectedJetProducer_h

#include <memory>
#include <vector>
#include <utility>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
//
// class declaration
//

class CorrectedMETproducer : public edm::stream::EDProducer<> {
public:
    explicit CorrectedMETproducer(const edm::ParameterSet&);
    ~CorrectedMETproducer();
    
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    
    std::vector<pat::MET> CorrectMET(const std::vector<pat::Jet>& oldJetsForMET, const std::vector<pat::Jet>& newJetsForMET, const std::vector<pat::Electron>& oldElectronsForMET, const std::vector<pat::Electron>& newElectronsForMET, const std::vector<pat::Muon>& oldMuonsForMET, const std::vector<pat::Muon>& newMuonsForMET, const std::vector<pat::MET>& pfMETs) const;
    
private:
    virtual void beginStream(edm::StreamID) override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endStream() override;
    
    // ----------member data ---------------------------
    /** input jets data access token -- before (re-)correction **/
    edm::EDGetTokenT< std::vector<pat::Jet> > oldJetsToken;    
    /** input jets data access token -- after (re-)correction **/
    edm::EDGetTokenT< std::vector<pat::Jet> > newJetsToken;
    /** input electrons data access token -- before (re-)correction **/
    edm::EDGetTokenT< std::vector<pat::Electron> > oldElectronsToken;    
    /** input electrons data access token -- after (re-)correction **/
    edm::EDGetTokenT< std::vector<pat::Electron> > newElectronsToken;    
    /** input muons data access token -- before (re-)correction **/
    edm::EDGetTokenT< std::vector<pat::Muon> > oldMuonsToken;    
    /** input muons data access token -- after (re-)correction **/
    edm::EDGetTokenT< std::vector<pat::Muon> > newMuonsToken;    
    /** mets data access token **/
    edm::EDGetTokenT< std::vector<pat::MET> > metsToken;
    /** names of output jet collections **/
    const std::string collectionName;
    
};

#endif