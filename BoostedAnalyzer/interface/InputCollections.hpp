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
#include "MiniAOD/BoostedObjects/interface/BoostedJet.h"
#include "MiniAOD/BoostedObjects/interface/Ak4Cluster.h"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/EventInfo.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TriggerInfo.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/FilterInfo.hpp"
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
        const FilterInfo&                             filterInfo_,
        const std::vector<reco::Vertex>&              selectedPVs_,

                    const std::vector<pat::Muon>&                 selectedMuons_,
                    const std::vector<pat::Muon>&                 selectedMuonsDL_,
                    const std::vector<pat::Muon>&                 selectedMuonsLoose_,
                    const std::vector<pat::Electron>&             selectedElectrons_,
                    const std::vector<pat::Electron>&             selectedElectronsDL_,
                    const std::vector<pat::Electron>&             selectedElectronsLoose_,
                    const std::vector<pat::Jet>&                  selectedJets_,
                    const std::vector<pat::Jet>&                  selectedJetsLoose_,
                    const std::vector<pat::Jet>&                  AK8Jets_,
                    const pat::MET&                               correctedMET_,
                    const boosted::BoostedJetCollection&          selectedBoostedJets_,
                    const boosted::Ak4ClusterCollection&          selectedAk4Cluster_,
                    const GenTopEvent&                            genTopEvt_,
                    const std::vector<reco::GenJet>&              genJets_,
                    const SampleType                              sampleType_,
                    const HiggsDecay::HiggsDecay                  higgsDecay_,
                    const std::map<std::string,float>&            weights_,
        const edm::Event&                             iEvent_,
        const edm::EventSetup&                        iSetup_,
                    const Systematics::Type&                      systematic_,
                    const std::map<std::string, int>&             selectionTags_
                    
          /**** bjetness code ****/
                ):
                    eventInfo(eventInfo_),
                    triggerInfo(triggerInfo_),
                    filterInfo(filterInfo_),
                    selectedPVs(selectedPVs_),
                    selectedMuons(selectedMuons_),
                    selectedMuonsDL(selectedMuonsDL_),
                    selectedMuonsLoose(selectedMuonsLoose_),
                    selectedElectrons(selectedElectrons_),
                    selectedElectronsDL(selectedElectronsDL_),
                    selectedElectronsLoose(selectedElectronsLoose_),
                    selectedJets(selectedJets_),
                    selectedJetsLoose(selectedJetsLoose_),
                    AK8Jets(AK8Jets_), 
                    correctedMET(correctedMET_),
                    selectedBoostedJets(selectedBoostedJets_),
                    selectedAk4Cluster(selectedAk4Cluster_),
                    genTopEvt(genTopEvt_),
                    genJets(genJets_),
                    sampleType(sampleType_),
                    higgsDecay(higgsDecay_),
                    weights(weights_),
        iEvent(iEvent_),
        iSetup(iSetup_),
        systematic(systematic_),
        selectionTags(selectionTags_)
                    {}

/**
   Constructor that replaces all variables related to jets and copies the remaining ones from a different input colection
 */
InputCollections(   const InputCollections&                       input,
                    const std::vector<pat::Jet>&                  rawJets_,
                    const std::vector<pat::Jet>&                  selectedJets_,
                    const std::vector<pat::Jet>&                  selectedJetsLoose_,
                    const pat::MET&                               correctedMET_,
                    const boosted::BoostedJetCollection&          selectedBoostedJets_,
                    const boosted::Ak4ClusterCollection&          selectedAk4Cluster_,
                    const std::map<std::string,float>&            weights_
                ): 
                    eventInfo(input.eventInfo),
                    triggerInfo(input.triggerInfo),
                    filterInfo(input.filterInfo),
                    selectedPVs(input.selectedPVs),
                    selectedMuons(input.selectedMuons),
                    selectedMuonsDL(input.selectedMuonsDL),
                    selectedMuonsLoose(input.selectedMuonsLoose),
                    selectedElectrons(input.selectedElectrons),
                    selectedElectronsDL(input.selectedElectronsDL),
                    selectedElectronsLoose(input.selectedElectronsLoose),
                    selectedJets(selectedJets_),
                    selectedJetsLoose(selectedJetsLoose_),
                    AK8Jets(input.AK8Jets), 
                    correctedMET(correctedMET_),
                    selectedBoostedJets(selectedBoostedJets_),
                    selectedAk4Cluster(selectedAk4Cluster_),
                    genTopEvt(input.genTopEvt),
                    genJets(input.genJets),
                    sampleType(input.sampleType),
                    higgsDecay(input.higgsDecay),
                    weights(weights_),
        iEvent(input.iEvent),
        iSetup(input.iSetup),
        systematic(input.systematic),
        selectionTags(input.selectionTags)
                    {}

  const EventInfo&                              eventInfo;
  const TriggerInfo&                            triggerInfo;
  const FilterInfo&                             filterInfo;
  const std::vector<reco::Vertex>&              selectedPVs;
  const std::vector<pat::Muon>&                 selectedMuons;
  const std::vector<pat::Muon>&                 selectedMuonsDL;
  const std::vector<pat::Muon>&                 selectedMuonsLoose;
  const std::vector<pat::Electron>&             selectedElectrons;
  const std::vector<pat::Electron>&             selectedElectronsDL;
  const std::vector<pat::Electron>&             selectedElectronsLoose;
  const std::vector<pat::Jet>&                  selectedJets;
  const std::vector<pat::Jet>&                  selectedJetsLoose;
  const std::vector<pat::Jet>&                  AK8Jets;
  const pat::MET&                               correctedMET;
  const boosted::BoostedJetCollection&          selectedBoostedJets;
  const boosted::Ak4ClusterCollection&          selectedAk4Cluster;
  const GenTopEvent&                            genTopEvt;
  const std::vector<reco::GenJet>&              genJets;
  const SampleType                              sampleType;
  const HiggsDecay::HiggsDecay                  higgsDecay;
  const std::map<std::string,float>             weights;
  const edm::Event &                            iEvent;
  const edm::EventSetup &                       iSetup;
  const Systematics::Type&                      systematic;
  const std::map<std::string, int>&              selectionTags;
};

#endif