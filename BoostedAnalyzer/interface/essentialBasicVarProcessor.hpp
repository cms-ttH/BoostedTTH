#ifndef BOOSTEDTTH_BOOSTEDANALYZER_ESSENTIALBASICVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_ESSENTIALBASICVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"

class essentialBasicVarProcessor : public TreeProcessor
{

public:
  essentialBasicVarProcessor();
  ~essentialBasicVarProcessor();

  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input, VariableContainer& var);

private:
};

#endif
