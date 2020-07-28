#ifndef BOOSTEDTTH_BOOSTEDANALYZER_MICROBASICVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_MICROBASICVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"

class microBasicVarProcessor: public TreeProcessor{
  
public:
  
  microBasicVarProcessor();
  ~microBasicVarProcessor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
private:
  std::string era;
};

#endif
