#ifndef BOOSTEDTTH_BOOSTEDANALYZER_RAWVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_RAWVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class RawVarProcessor: public TreeProcessor{
  
public:
  
  RawVarProcessor();
  ~RawVarProcessor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
private:

};

#endif
