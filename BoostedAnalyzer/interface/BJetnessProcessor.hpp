#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BJETNESSSPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BJETNESSSPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"


class BJetnessProcessor: public TreeProcessor{
  
public:
  
  // all configurations should be done in constructor
  BJetnessProcessor(edm::ConsumesCollector && iC);
  ~BJetnessProcessor();
  // you have to implement this to functions, you can add additionional (private) functions
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
private:
  // add all members needed, initialize in constructor

};
#endif
