#ifndef BOOSTEDTTH_BOOSTEDANALYZER_MICROMCMATCHVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_MICROMCMATCHVARPROCESSOR_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

class microMCMatchVarProcessor: public TreeProcessor{
  
  public:
  
    microMCMatchVarProcessor();
    ~microMCMatchVarProcessor();
    
    void Init(const InputCollections& input,VariableContainer& var);
    void Process(const InputCollections& input,VariableContainer& var);
  
};

#endif
