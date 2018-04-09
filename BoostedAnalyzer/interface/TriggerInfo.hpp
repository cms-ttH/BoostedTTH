#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERINFO_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERINFO_HPP

#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <iostream>
#include <map>
#include <vector>

class TriggerInfo
{

public:
  TriggerInfo(std::map<std::string, bool> triggers,
              std::map<std::string, int> prescales);
  bool IsTriggered(std::string triggername) const;
  bool Exists(std::string triggername) const;
  bool GetPrescale(std::string triggername) const;
  void Print() const;
  bool IsAnyTriggered(std::vector<std::string> triggers) const;
  std::map<std::string, bool> GetTriggers() const;

private:
  std::map<std::string, bool> triggers;
  std::map<std::string, int> prescales;
};

class TriggerInfoProducer
{

public:
  TriggerInfoProducer(const edm::ParameterSet& iConfig,
                      edm::ConsumesCollector&& iC);
  TriggerInfo Produce(const edm::Event& iEvent) const;

private:
  edm::EDGetTokenT<edm::TriggerResults> triggerBitsToken;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescalesToken;
};

#endif
