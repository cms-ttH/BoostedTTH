#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GENJETPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GENJETPROCESSOR_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

class GenJetProcessor: public TreeProcessor{
  
  public:
  
    GenJetProcessor();
    ~GenJetProcessor();
    
    void Init(const InputCollections& input,VariableContainer& var);
    void Process(const InputCollections& input,VariableContainer& var);

  private:
    const pat::Jet* GetPatJet(const reco::GenJet& genjet,const std::vector<pat::Jet>& patjets);
  
};

#endif
