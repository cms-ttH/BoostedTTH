#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BASICVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BASICVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"

class BasicVarProcessor : public TreeProcessor
{

public:
  BasicVarProcessor();
  ~BasicVarProcessor();

  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input, VariableContainer& var);

private:
};

#endif
