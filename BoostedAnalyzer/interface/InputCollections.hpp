#ifndef BOOSTEDTTH_BOOSTEDANALYZER_INPUTCOLLECTIONS_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_INPUTCOLLECTIONS_HPP

#include <vector>
#include <map>
#include <stdio.h>
#include <boost/format.hpp>

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "MiniAOD/BoostedObjects/interface/SubFilterJet.h"
#include "MiniAOD/BoostedObjects/interface/HTTTopJet.h"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/EventInfo.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TriggerInfo.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"


enum SampleType{data,tth,ttl,ttbb,ttb,tt2b,ttcc,ttc,nonttbkg,thq};
namespace HiggsDecay{enum HiggsDecay{NA,bb,nonbb};};



/*
  References to the selected physics objects as well as some general event information, some generator information, and event weights (nominal and for systematics) are stored in InputCollections. Only from these inputs the variables in the trees are calculated. There are multiple InputCollections for different systematics (e.g. in one the default jets are exchanged with JES shifted jets). 
 */
struct InputCollections{
/**
   Constructor in which all references to the objects that are analyzed are set
 */
InputCollections(   const EventInfo&                              eventInfo_,
		    const TriggerInfo&                            triggerInfo_,
		    const std::vector<reco::Vertex>&              selectedPVs_,
                    const std::vector<pat::Muon>&                 rawMuons_,
                    const std::vector<pat::Muon>&                 selectedMuons_,
                    const std::vector<pat::Muon>&                 selectedMuonsDL_,
                    const std::vector<pat::Muon>&                 selectedMuonsLoose_,
                    const std::vector<pat::Electron>&             rawElectrons_,
                    const std::vector<pat::Electron>&             selectedElectrons_,
                    const std::vector<pat::Electron>&             selectedElectronsDL_,
                    const std::vector<pat::Electron>&             selectedElectronsLoose_,
                    const std::vector<pat::Jet>&                  rawJets_,
                    const std::vector<pat::Jet>&                  selectedJets_,
                    const std::vector<pat::Jet>&                  selectedJetsLoose_,
                    const std::vector<pat::Jet>&                  selectedJetsSingleTop_,
                    const pat::MET&                               pfMET_,
                    const boosted::HTTTopJetCollection&           selectedHTTTopJets_,
                    const boosted::SubFilterJetCollection&        selectedSubFilterJets_,
            		    const GenTopEvent&                            genTopEvt_,
                    const std::vector<reco::GenJet>&              selectedGenJets_,
                    const SampleType                              sampleType_,
            		    const HiggsDecay::HiggsDecay                  higgsDecay_,
                    const std::map<std::string,float>&            weights_
		            ): 
                    eventInfo(eventInfo_),
                    triggerInfo(triggerInfo_),
                    selectedPVs(selectedPVs_),
                    rawMuons(rawMuons_),
                    selectedMuons(selectedMuons_),
                    selectedMuonsDL(selectedMuonsDL_),
                    selectedMuonsLoose(selectedMuonsLoose_),
                    rawElectrons(rawElectrons_),
                    selectedElectrons(selectedElectrons_),
                    selectedElectronsDL(selectedElectronsDL_),
                    selectedElectronsLoose(selectedElectronsLoose_),
                    rawJets(rawJets_),
                    selectedJets(selectedJets_),
                    selectedJetsLoose(selectedJetsLoose_),
                    selectedJetsSingleTop(selectedJetsSingleTop_),
                    pfMET(pfMET_),
                    selectedHTTTopJets(selectedHTTTopJets_),
                    selectedSubFilterJets(selectedSubFilterJets_),
                    genTopEvt(genTopEvt_),
                    selectedGenJets(selectedGenJets_),
                    sampleType(sampleType_),
                    higgsDecay(higgsDecay_),
                    weights(weights_)
                    {}

/**
   Constructor that replaces all variables related to jets and copies the remaining ones from a different input colection
 */
InputCollections(   const InputCollections&                       input,
                    const std::vector<pat::Jet>&                  selectedJets_,
                    const std::vector<pat::Jet>&                  selectedJetsLoose_,
                    const std::vector<pat::Jet>&                  selectedJetsSingleTop_,
                    const pat::MET&                               pfMET_,
                    const std::map<std::string,float>&            weights_
        		    ): 
                    eventInfo(input.eventInfo),
                    triggerInfo(input.triggerInfo),
                    selectedPVs(input.selectedPVs),
                    rawMuons(input.rawMuons),
                    selectedMuons(input.selectedMuons),
                    selectedMuonsDL(input.selectedMuonsDL),
                    selectedMuonsLoose(input.selectedMuonsLoose),
                    rawElectrons(input.rawElectrons),
                    selectedElectrons(input.selectedElectrons),
                    selectedElectronsDL(input.selectedElectronsDL),
                    selectedElectronsLoose(input.selectedElectronsLoose),
                    rawJets(input.rawJets),
                    selectedJets(selectedJets_),
                    selectedJetsLoose(selectedJetsLoose_),
                    selectedJetsSingleTop(selectedJetsSingleTop_),
                    pfMET(pfMET_),
                    selectedHTTTopJets(input.selectedHTTTopJets),
                    selectedSubFilterJets(input.selectedSubFilterJets),
                    genTopEvt(input.genTopEvt),
                    selectedGenJets(input.selectedGenJets),
                    sampleType(input.sampleType),
                    higgsDecay(input.higgsDecay),
                    weights(weights_)
                    {}

  const EventInfo&                              eventInfo;
  const TriggerInfo&                            triggerInfo;
  const std::vector<reco::Vertex>&              selectedPVs;
  const std::vector<pat::Muon>&                 rawMuons;
  const std::vector<pat::Muon>&                 selectedMuons;
  const std::vector<pat::Muon>&                 selectedMuonsDL;
  const std::vector<pat::Muon>&                 selectedMuonsLoose;
  const std::vector<pat::Electron>&             rawElectrons;
  const std::vector<pat::Electron>&             selectedElectrons;
  const std::vector<pat::Electron>&             selectedElectronsDL;
  const std::vector<pat::Electron>&             selectedElectronsLoose;
  const std::vector<pat::Jet>&                  rawJets;
  const std::vector<pat::Jet>&                  selectedJets;
  const std::vector<pat::Jet>&                  selectedJetsLoose;
  const std::vector<pat::Jet>&                  selectedJetsSingleTop;
  const pat::MET&                               pfMET;
  const boosted::HTTTopJetCollection&           selectedHTTTopJets;
  const boosted::SubFilterJetCollection&        selectedSubFilterJets;
  const GenTopEvent&                            genTopEvt;
  const std::vector<reco::GenJet>&              selectedGenJets;
  const SampleType                              sampleType;
  const HiggsDecay::HiggsDecay                  higgsDecay;
  const std::map<std::string,float>&            weights;

};

#endif
