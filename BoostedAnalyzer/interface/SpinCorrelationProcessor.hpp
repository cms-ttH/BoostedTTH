#ifndef BOOSTEDTTH_BOOSTEDANALYZER_SPINCORRELATIONPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_SPINCORRELATIONPROCESSOR_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/TTHReconstruction/interface/ReconstructionQuality.hpp"
#include "BoostedTTH/TTHReconstruction/interface/InterpretationGenerator.hpp"
#include "BoostedTTH/TTHReconstruction/interface/Interpretation.hpp"
#include "BoostedTTH/TTHReconstruction/interface/ReconstructionMCMatching.hpp"

class SpinCorrelationProcessor: public TreeProcessor{
  
public:
  
  SpinCorrelationProcessor();
  ~SpinCorrelationProcessor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
  
private:
  ReconstructionQuality quality;
  InterpretationGenerator generator;
  //ReconstructionMCMatching mcmatcher;
};
  
#endif