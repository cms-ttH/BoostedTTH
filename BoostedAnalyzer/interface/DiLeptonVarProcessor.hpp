#ifndef BOOSTEDTTH_BOOSTEDANALYZER_DILEPTONVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_DILEPTONVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"

class DiLeptonVarProcessor : public TreeProcessor
{

public:
  DiLeptonVarProcessor();
  ~DiLeptonVarProcessor();

  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input, VariableContainer& var);

private:
};

#endif
