#ifndef BOOSTEDTTH_STANDARDANALYZER_MVAVARPROCESSOR_HPP
#define BOOSTEDTTH_STANDARDANALYZER_MVAVARPROCESSOR_HPP

#include "BoostedTTH/StandardAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "MiniAOD/MiniAODHelper/interface/BDTvars.h"

class MVAVarProcessor: public TreeProcessor{
  
public:
  
  MVAVarProcessor();
  ~MVAVarProcessor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
private:
  BDTvars bdtvar;
};

#endif
