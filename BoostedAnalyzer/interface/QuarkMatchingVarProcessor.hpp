#ifndef BOOSTEDTTH_BOOSTEDANALYZER_QUARKMATCHINGVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_QUARKMATCHINGVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

#include "DataFormats/PatCandidates/interface/Jet.h"




class QuarkMatchingVarProcessor: public TreeProcessor{

public:
  QuarkMatchingVarProcessor();
  QuarkMatchingVarProcessor(edm::ConsumesCollector && iC, std::vector<edm::InputTag> regJetCollections);
  ~QuarkMatchingVarProcessor();

  void Init(const InputCollections& input, VariableContainer& vars);
  void Process(const InputCollections& input, VariableContainer& vars);

private:

  float GetDijetMass(const pat::Jet& firstjet,
		     const pat::Jet& secondjet);

  float GetTopHadMass(const pat::Jet& topJet,
		      const vector<pat::Jet>& WJets);

  reco::GenParticle MatchPartontoJet(const InputCollections& input,
                                     std::vector<reco::GenParticle>& Partons,
                                     pat::Jet& Jet);

  std::vector<reco::GenParticle> GetQuarksfromWDecay(const InputCollections& input);
  std::vector<reco::GenParticle> GetbQuarksfromTopDecay(const InputCollections& input);
  std::vector<reco::GenParticle> GetQuarksfromHiggsDecay(const InputCollections& input);
  float DeltaRCut;
  bool useregressedJets;

  void PrintTLorentz(TLorentzVector& vec);

  std::vector< std::string > extentions;

  std::vector<edm::EDGetTokenT< std::vector<pat::Jet> > > regressedJetsTokens;
  edm::EDGetTokenT< std::vector<reco::GenJet> > genJetswNuToken;
};

#endif
