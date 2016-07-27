#ifndef BOOSTEDTTH_BOOSTEDANALYZER_REGRESSIONVALIDATIONVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_REGRESSIONVALIDATIONVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenJetMatcher.hpp"

class RegressionValidationVarProcessor: public TreeProcessor{

public:

  RegressionValidationVarProcessor(edm::ConsumesCollector && iC, std::vector<edm::InputTag> regJetCollections);
  ~RegressionValidationVarProcessor();

  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);

private:
  std::vector<edm::EDGetTokenT< std::vector<pat::Jet> > > regressedJetsTokens;
  std::vector< std::string > extentions;
};

#endif
