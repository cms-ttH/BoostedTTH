#ifndef BOOSTEDTTH_BOOSTEDANALYZER_QUARKMATCHINGVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_QUARKMATCHINGVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

#include "DataFormats/PatCandidates/interface/Jet.h"




class QuarkMatchingVarProcessor: public TreeProcessor{
  
public:
  QuarkMatchingVarProcessor();
  ~QuarkMatchingVarProcessor();
  
  void Init(const InputCollections& input, VariableContainer& vars);
  void Process(const InputCollections& input, VariableContainer& vars);
  
private:
  
  float GetDijetMass(const pat::Jet& jet1, 
		     const pat::Jet& jet2, 
		     const bool docorrection);

  float GetTopHadMass(const pat::Jet& topJet,
		      const vector<pat::Jet>& WJets, 
		      const bool docorrection );
  
  std::vector<reco::GenParticle> GetQuarksfromTopDecay(const InputCollections& input);
  std::vector<reco::GenParticle> GetQuarksfromHiggsDecay(const InputCollections& input);
  float DeltaRCut; 
  void PrintTLorentz(TLorentzVector& vec); 
  

};

#endif

