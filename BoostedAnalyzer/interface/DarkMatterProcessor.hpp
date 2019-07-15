#ifndef BOOSTEDTTH_BOOSTEDANALYZER_DARKMATTERPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_DARKMATTERPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class DarkMatterProcessor : public TreeProcessor {
 public:
  DarkMatterProcessor();
  ~DarkMatterProcessor();

  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input, VariableContainer& var);

 private:
};

#endif
