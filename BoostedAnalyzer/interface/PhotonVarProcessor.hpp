#ifndef BOOSTEDTTH_BOOSTEDANALYZER_PHOTONVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_PHOTONVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"

class PhotonVarProcessor : public TreeProcessor {
 public:
  PhotonVarProcessor();
  ~PhotonVarProcessor();

  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input, VariableContainer& var);

 private:
  std::string era;
};

#endif
