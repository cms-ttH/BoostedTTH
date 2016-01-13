#ifndef BOOSTEDTTH_BOOSTEDANALYZER_QUARKMATCHINGVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_QUARKMATCHINGVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

class QuarkMatchingVarProcessor: public TreeProcessor{
  
public:
  QuarkMatchingVarProcessor();
  ~QuarkMatchingVarProcessor();

  void Init(const InputCollections& input, VariableContainer& vars);
  void Process(const InputCollections& input, VariableContainer& vars);

private:

  float DeltaRCut; 

};

#endif

