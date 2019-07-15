#ifndef BOOSTEDTTH_BOOSTEDANALYZER_ESSENTIALMVAVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_ESSENTIALMVAVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"

#include "TTH/CommonClassifier/interface/MVAvars.h"

class essentialMVAVarProcessor : public TreeProcessor {
 public:
  essentialMVAVarProcessor();

  ~essentialMVAVarProcessor();

  void Init(const InputCollections &input, VariableContainer &var);
  void Process(const InputCollections &input, VariableContainer &var);

 private:
  std::map<std::string, float> varMap;
  std::string btagger;
  // MVAvars from CommonClassifier classifier for sl channel
  std::unique_ptr<MVAvars> pointerToMVAvars = nullptr;
};

#endif
