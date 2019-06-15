#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GENLEPTONPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GENLEPTONPROCESSOR_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class GenLeptonProcessor : public TreeProcessor{
  
  public:
    
    GenLeptonProcessor();
    ~GenLeptonProcessor();
    
    void Init(const InputCollections& input,VariableContainer& var);
    void Process(const InputCollections& input,VariableContainer& var);
    
  private: 
    
    const pat::Electron* GetPatElectron(const reco::GenParticle& genelectron,const std::vector<pat::Electron>& patelectrons);
    const pat::Muon* GetPatMuon(const reco::GenParticle& genmuon,const std::vector<pat::Muon>& patmuons);
    
};

#endif
