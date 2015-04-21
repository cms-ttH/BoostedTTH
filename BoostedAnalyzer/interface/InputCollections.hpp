#ifndef BOOSTEDTTH_BOOSTEDANALYZER_INPUTCOLLECTIONS_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_INPUTCOLLECTIONS_HPP

#include <vector>
#include <map>

#include "BoostedTTH/BoostedObjects/interface/Event.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "BoostedTTH/BoostedObjects/interface/SubFilterJet.h"
#include "BoostedTTH/BoostedObjects/interface/HTTTopJet.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

enum SampleType{data,tth,tt,nonttbkg};

struct InputCollections{
InputCollections(   const boosted::Event&                         event_,
                    const pat::TriggerObjectStandAloneCollection& selectedTrigger_,
                    const edm::TriggerResults&                    triggerResults_,
                    const HLTConfigProvider&                      hlt_config_,
                    const reco::VertexCollection&                 selectedPVs_,
                    const std::vector<pat::Muon>&                 selectedMuons_,
                    const std::vector<pat::Muon>&                 selectedMuonsLoose_,
                    const std::vector<pat::Electron>&             selectedElectrons_,
                    const std::vector<pat::Electron>&             selectedElectronsLoose_,
                    const std::vector<pat::Jet>&                  selectedJets_,
                    const std::vector<pat::Jet>&                  selectedJetsLoose_,
                    const std::vector<pat::MET>&                  pfMets_,
                    const boosted::HTTTopJetCollection&           selectedHTTTopJets_,
                    const boosted::SubFilterJetCollection&        selectedSubFilterJets_,
		    const GenTopEvent&                            genTopEvt_,
                    const std::vector<reco::GenJet>&              selectedGenJets_,
                    const SampleType                              sampleType_,
                    const std::map<std::string,float>&            weights_,
		    const edm::EventSetup&	                  setup_,
        	    const edm::Event&	                          edmevent_

                  ):
                    event(event_),
                    selectedTrigger(selectedTrigger_),
                    triggerResults(triggerResults_),
                    hlt_config(hlt_config_),
                    selectedPVs(selectedPVs_),
                    selectedMuons(selectedMuons_),
                    selectedMuonsLoose(selectedMuonsLoose_),
                    selectedElectrons(selectedElectrons_),
                    selectedElectronsLoose(selectedElectronsLoose_),
                    selectedJets(selectedJets_),
                    selectedJetsLoose(selectedJetsLoose_),
                    pfMets(pfMets_),
                    selectedHTTTopJets(selectedHTTTopJets_),
                    selectedSubFilterJets(selectedSubFilterJets_),
                    genTopEvt(genTopEvt_),
                    selectedGenJets(selectedGenJets_),
                    sampleType(sampleType_),
                    weights(weights_),
		    setup(setup_),
                    edmevent(edmevent_){}
  
  const boosted::Event&                         event;
  const pat::TriggerObjectStandAloneCollection& selectedTrigger;
  const edm::TriggerResults&                    triggerResults;
  const HLTConfigProvider&                       hlt_config;
  const reco::VertexCollection&                 selectedPVs;
  const std::vector<pat::Muon>&                 selectedMuons;
  const std::vector<pat::Muon>&                 selectedMuonsLoose;
  const std::vector<pat::Electron>&             selectedElectrons;
  const std::vector<pat::Electron>&             selectedElectronsLoose;
  const std::vector<pat::Jet>&                  selectedJets;
  const std::vector<pat::Jet>&                  selectedJetsLoose;
  const std::vector<pat::MET>&                  pfMets;
  const boosted::HTTTopJetCollection&           selectedHTTTopJets;
  const boosted::SubFilterJetCollection&        selectedSubFilterJets;
  const GenTopEvent&                            genTopEvt;
  const std::vector<reco::GenJet>&              selectedGenJets;
  const SampleType                              sampleType;
  const std::map<std::string,float>&            weights;
  const edm::EventSetup& 			setup;
  const edm::Event& 			        edmevent;

  void Dump();
};

#endif
