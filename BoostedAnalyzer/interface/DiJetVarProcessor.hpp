#ifndef BOOSTEDTTH_BOOSTEDANALYZER_DIJETVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_DIJETVARPROCESSOR_HPP

#include <string>

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"

class DiJetVarProcessor: public TreeProcessor {
public:
  explicit DiJetVarProcessor(const edm::ParameterSet& cfg);
  ~DiJetVarProcessor() {}
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);


private:
  std::string bTagger_;
  std::string jetTagInfoSV_;
  double minSVFlightDistSig_;
  std::string puJetIDDiscr_;

  void fillSecondaryVertexInfo(VariableContainer& vars, const pat::Jet& jet, const size_t iJet) const;
};
#endif
