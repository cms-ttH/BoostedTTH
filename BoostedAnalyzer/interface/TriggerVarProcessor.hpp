#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERVARPROCESSOR_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"


class TriggerVarProcessor: public TreeProcessor{
  
  public:
  
    TriggerVarProcessor();
    ~TriggerVarProcessor();
    
    void Init(const InputCollections& input,VariableContainer& var);
    void Process(const InputCollections& input,VariableContainer& var);
   
};

#endif
