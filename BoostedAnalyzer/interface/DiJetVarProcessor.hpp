#ifndef BOOSTEDTTH_BOOSTEDANALYZER_DIJETVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_DIJETVARPROCESSOR_HPP

#include <string>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"

class DiJetVarProcessor: public TreeProcessor {
public:
  DiJetVarProcessor() {}
  ~DiJetVarProcessor() {}
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);


private:
  std::string bTagger_;
  std::string puJetIDDiscr_;
};
#endif
