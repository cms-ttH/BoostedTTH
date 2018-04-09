#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BJETNESSSPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BJETNESSSPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include <vector>

class BJetnessProcessor : public TreeProcessor
{

public:
  BJetnessProcessor(edm::ConsumesCollector&& iC);
  ~BJetnessProcessor();

  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input, VariableContainer& var);

private:
  edm::EDGetTokenT<vector<float>> bjetness_;
};
#endif
