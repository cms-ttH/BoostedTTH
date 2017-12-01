#ifndef BOOSTEDTTH_BOOSTEDANALYZER_MONOJETPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_MONOJETPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class MonoJetProcessor: public TreeProcessor{
  
public:
  
  MonoJetProcessor();
  ~MonoJetProcessor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
private:
};

#endif