#ifndef BOOSTEDTTH_BOOSTEDANALYZER_MCMATCHVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_MCMATCHVARPROCESSOR_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

class MCMatchVarProcessor: public TreeProcessor{
  
  public:
  
    MCMatchVarProcessor();
    ~MCMatchVarProcessor();
    
    void Init(const InputCollections& input,VariableContainer& var);
    void Process(const InputCollections& input,VariableContainer& var);
  
};

#endif
