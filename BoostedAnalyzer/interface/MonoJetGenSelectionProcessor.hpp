#ifndef BOOSTEDTTH_BOOSTEDANALYZER_MONOJETGENSELECTIONPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_MONOJETGENSELECTIONPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class MonoJetGenSelectionProcessor: public TreeProcessor {

public:

  MonoJetGenSelectionProcessor();
  ~MonoJetGenSelectionProcessor();

  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input, VariableContainer& var);
  int GenVertexSelection(const InputCollections& input);
  int GenMETSelection(const InputCollections& input);
  int GenMonoJetSelection(const InputCollections& input);
  int GenLeptonVetoSelection(const InputCollections& input);
  int GenBTagVetoSelection(const InputCollections& input);
  int GenPhotonVetoSelection(const InputCollections& input);
  int GenmonoVselection(const InputCollections& input);

private:
  const float minMET = 200;
  const float maxMET = 100000;
  const float pt_min = 100;
  const float eta_max = 2.4;

  //Ak8Stuff
  const float minpt = 250;
  const float maxeta = 2.4;
  const float minMass = 65;
  const float maxMass = 105;
  bool monoVtagged;
};

#endif