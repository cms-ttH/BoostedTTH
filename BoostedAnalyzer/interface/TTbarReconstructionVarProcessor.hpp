#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TTBARRECONSTRUCTIONVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TTBARRECONSTRUCTIONVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "TLorentzVector.h"
#include "TTH/RecoLikelihoodReconstruction/interface/Interpretation.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/InterpretationGenerator.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/ReconstructionMCMatching.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/ReconstructionQuality.hpp"

class TTbarReconstructionVarProcessor : public TreeProcessor
{

public:
  TTbarReconstructionVarProcessor();

  ~TTbarReconstructionVarProcessor();

  void Init(const InputCollections& input, VariableContainer& var);

  void Process(const InputCollections& input, VariableContainer& var);

private:
  ReconstructionQuality quality;
  InterpretationGenerator generator;
  ReconstructionMCMatching mcmatcher;
};

#endif
