#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDMCMATCHVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDMCMATCHVARPROCESSOR_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

class BoostedMCMatchVarProcessor : public TreeProcessor {
 public:
  BoostedMCMatchVarProcessor();
  ~BoostedMCMatchVarProcessor();

  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input, VariableContainer& var);
};

#endif
