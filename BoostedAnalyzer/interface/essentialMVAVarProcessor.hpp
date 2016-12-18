#ifndef BOOSTEDTTH_BOOSTEDANALYZER_ESSENTIALMVAVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_ESSENTIALMVAVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "MiniAOD/MiniAODHelper/interface/BDTvars.h"
#include "BoostedTTH/TTHReconstruction/interface/ReconstructionQuality.hpp"
#include "TTH/CommonClassifier/interface/MEMClassifier.h"

class essentialMVAVarProcessor: public TreeProcessor{
  
public:
  
  essentialMVAVarProcessor();
  ~essentialMVAVarProcessor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
private:
  BDTvars bdtvar;
//   ReconstructionQuality quality;
  MEMClassifier mem;
};

#endif
