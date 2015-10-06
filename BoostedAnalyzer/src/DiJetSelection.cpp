#include <vector>

#include "DataFormats/PatCandidates/interface/Jet.h"

#include "BoostedTTH/BoostedAnalyzer/interface/DiJetSelection.hpp"


DiJetSelection::DiJetSelection()
  : selectionStep1_("2 jets with pt>20 GeV"), minPt_(20.) {}


void DiJetSelection::InitCutflow(Cutflow& cutflow) {
  cutflow.AddStep(selectionStep1_);
  initialized=true;
}


bool DiJetSelection::IsSelected(const InputCollections& input, Cutflow& cutflow) {
  checkIfIsInit("DiJetSelection");

  const std::vector<pat::Jet>& jets = input.idJets;

  if( jets.size()     < 2      ) return false;
  if( jets.at(0).pt() < minPt_ ) return false;
  if( jets.at(1).pt() < minPt_ ) return false;

  cutflow.EventSurvivedStep(selectionStep1_,input.weights.at("Weight"));
  return true;
}
