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
  
  float GetDijetMass(const pat::Jet& firstjet, 
		     const pat::Jet& secondjet, 
		     const bool docorrection);

  float GetDijetMass(const pat::Jet& firstjet, 
		     const pat::Jet& secondjet, 
		     std::string regextention);

  float GetTopHadMass(const pat::Jet& topJet,
		      const vector<pat::Jet>& WJets, 
		      const bool docorrection );

  float GetTopHadMass(const pat::Jet& topJet,
		      const vector<pat::Jet>& WJets, 
		      std::string regextention);

  std::vector<reco::GenParticle> GetQuarksfromTopDecay(const InputCollections& input);
  std::vector<reco::GenParticle> GetQuarksfromHiggsDecay(const InputCollections& input);
  float DeltaRCut; 
  void PrintTLorentz(TLorentzVector& vec); 

  std::vector< std::string > extentions;

};

#endif

