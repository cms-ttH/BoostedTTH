#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERVARPROCESSOR_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"


class TriggerVarProcessor: public TreeProcessor{
  
  public:
  
    TriggerVarProcessor(std::vector<std::string> relevantTriggers);
    ~TriggerVarProcessor();
    
    void Init(const InputCollections& input,VariableContainer& var);
    void Process(const InputCollections& input,VariableContainer& var);

  private:
    const std::vector<std::string> relevantTriggers;
    std::string replaceAsterix(std::string triggername);
};

#endif
