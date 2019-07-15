#ifndef BOOSTEDTTH_BOOSTEDANALYZER_SLIMMEDNTUPLES_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_SLIMMEDNTUPLES_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"

class SlimmedNtuples : public TreeProcessor {
 public:
  SlimmedNtuples();
  ~SlimmedNtuples();

  void Init(const std::vector<InputCollections>& input, VariableContainer& var);
  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const std::vector<InputCollections>& input,
               VariableContainer& var);
  void Process(const InputCollections& input, VariableContainer& var);
  template <typename T>
  T GetSortedBySeed(const T&);

 private:
  std::string base_string = "SN_";
};

#endif
