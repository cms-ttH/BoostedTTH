#ifndef BOOSTEDTTH_BOOSTEDANALYZER_AK8JETPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_AK8JETPROCESSOR_HPP

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

class AK8JetProcessor : public TreeProcessor {
 public:
  AK8JetProcessor(MiniAODHelper* helper_);
  ~AK8JetProcessor();

  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input, VariableContainer& var);

 private:
  float tau1, tau2, tau3;
  float b1N2, b2N2, b1N3, b2N3;
  const char* btagger;
};

#endif