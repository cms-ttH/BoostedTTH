#ifndef BOOSTEDTTH_BOOSTEDANALYZER_REGRESSIONVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_REGRESSIONVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class RegressionVarProcessor: public TreeProcessor{
  
public:
  
  RegressionVarProcessor();
  ~RegressionVarProcessor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);

private:
  
  std::vector< std::string > extentions;
  std::vector< std::string > jecLevels;
};

#endif
