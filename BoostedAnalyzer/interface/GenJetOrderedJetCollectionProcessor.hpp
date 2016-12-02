#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GENJETORDEREDJETCOLLECTIONPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GENJETORDEREDJETCOLLECTIONPROCESSOR_HPP

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"


class GenJetOrderedJetCollectionProcessor: public TreeProcessor {
public:
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);

private:
  bool getClosestJet(const reco::GenJet& genJet,
                     const pat::JetCollection& jets,
		     pat::Jet& closestJet,
		     double& deltaRMin) const;
  double deltaR(const reco::GenJet& genJet, const pat::Jet& jet) const;
};
#endif
