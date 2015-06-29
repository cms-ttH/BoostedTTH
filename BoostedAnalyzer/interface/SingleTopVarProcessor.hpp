#ifndef BOOSTEDTTH_BOOSTEDANALYZER_SINGLETOPVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_SINGLETOPVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "MiniAOD/MiniAODHelper/interface/BDTvars.h"

class SingleTopVarProcessor: public TreeProcessor{
  
public:
  
  SingleTopVarProcessor();
  ~SingleTopVarProcessor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
private:

};

#endif
