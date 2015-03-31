#ifndef BOOSTEDTTH_BOOSTEDANALYZER_WEIGHTPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_WEIGHTPROCESSOR_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"


class WeightProcessor: public TreeProcessor{
  
  public:
  
    WeightProcessor();
    ~WeightProcessor();
    
    void Init(const InputCollections& input,VariableContainer& var);
    void Process(const InputCollections& input,VariableContainer& var);
   
};

#endif
