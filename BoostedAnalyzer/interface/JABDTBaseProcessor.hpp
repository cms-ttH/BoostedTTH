#ifndef JABDTBASEPROCESSOR_HPP
#define JABDTBASEPROCESSOR_HPP
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "TTH/CommonClassifier/interface/HypothesisCombinatorics.h"

#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

class JABDTBaseProcessor: public TreeProcessor{
public:
  JABDTBaseProcessor();
  virtual ~JABDTBaseProcessor();
  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);

protected:
  std::string loadWeightPath(const edm::ParameterSet& jaoptions, const char* keyword) const;
  std::string loadVariables(const edm::ParameterSet& jaoptions, const char* keyword) const;
  std::string hypothesis;
  std::unique_ptr<HypothesisCombinatorics> pointerToEvenHypothesisCombinatorics = nullptr;
  std::unique_ptr<HypothesisCombinatorics> pointerToOddHypothesisCombinatorics = nullptr;

  bool initialized = false;
};

#endif
