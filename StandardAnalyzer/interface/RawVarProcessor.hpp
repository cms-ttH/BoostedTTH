#ifndef BOOSTEDTTH_STANDARDANALYZER_RAWVARPROCESSOR_HPP
#define BOOSTEDTTH_STANDARDANALYZER_RAWVARPROCESSOR_HPP

#include "BoostedTTH/StandardAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/StandardAnalyzer/interface/StandardUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

class RawVarProcessor: public TreeProcessor{
  
public:
  
  RawVarProcessor();
  ~RawVarProcessor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
private:

};

#endif
