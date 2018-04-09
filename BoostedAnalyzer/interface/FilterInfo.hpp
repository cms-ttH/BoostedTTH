#ifndef BOOSTEDTTH_BOOSTEDANALYZER_FILTERINFO_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_FILTERINFO_HPP

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <iostream>
#include <map>
#include <vector>

class FilterInfo
{

public:
  FilterInfo(std::map<std::string, bool> filters);
  bool Pass(std::string triggername) const;
  bool Exists(std::string triggername) const;
  void Print() const;
  bool PassAll(std::vector<std::string> triggers) const;
  std::map<std::string, bool> GetFilters() const;

private:
  std::map<std::string, bool> filters;
};

class FilterInfoProducer
{

public:
  FilterInfoProducer(const edm::ParameterSet& iConfig,
                     edm::ConsumesCollector&& iC);
  FilterInfo Produce(const edm::Event& iEvent) const;

private:
  /** filter results data access token **/
  edm::EDGetTokenT<edm::TriggerResults> filterBitsToken;
  /** additional filter bools **/
  std::vector<edm::EDGetTokenT<bool>> additionalFiltersTokens;
  std::vector<std::string> additionalFiltersNames;
};

#endif
