#ifndef BOOSTEDTTH_BOOSTEDANALYZER_MONOJETGENSELECTIONPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_MONOJETGENSELECTIONPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class MonoJetGenSelectionProcessor: public TreeProcessor{
  
public:
  
  MonoJetGenSelectionProcessor();
  ~MonoJetGenSelectionProcessor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
  int GenVertexSelection(const InputCollections& input);
  int GenMETSelection(const InputCollections& input);
  int GenMonoJetSelection(const InputCollections& input);
  int GenLeptonVetoSelection(const InputCollections& input);
  int GenBTagVetoSelection(const InputCollections& input);
  int GenPhotonVetoSelection(const InputCollections& input);
private:
  const float minMET = 250;
  const float maxMET = 100000;
  const float pt_min = 100;
  const float eta_max = 2.5;
  const float charged_hadron_fraction_min = 0.1;
  const float neutral_hadron_fraction_max = 0.8;
};

#endif