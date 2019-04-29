#ifndef JABDTBASEPROCESSOR_HPP
#define JABDTBASEPROCESSOR_HPP
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "TTH/CommonClassifier/interface/HypothesisCombinatorics.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class JABDTBaseProcessor: public TreeProcessor{
public:
  JABDTBaseProcessor();
  virtual ~JABDTBaseProcessor();
  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);

protected:
  std::string hypothesis;
  std::unique_ptr<HypothesisCombinatorics> pointerToHypothesisCombinatorics = nullptr;
  bool initialized = false;
};

#endif
