#ifndef BOOSTEDTTH_BOOSTEDANALYZER_REGRESSIONVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_REGRESSIONVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenJetMatcher.hpp"

class RegressionVarProcessor: public TreeProcessor{

public:

  RegressionVarProcessor(edm::ConsumesCollector && iC, std::vector<edm::InputTag> regJetCollections);
  ~RegressionVarProcessor();

  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);

private:
  std::vector<edm::EDGetTokenT< std::vector<pat::Jet> > > regressedJetsTokens;
  edm::EDGetTokenT< std::vector<reco::GenJet> > genJetswNuToken;
  std::vector< std::string > extentions;
  std::vector< std::string > jecLevels;
};

#endif
