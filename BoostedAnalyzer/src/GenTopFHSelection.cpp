#include "BoostedTTH/BoostedAnalyzer/interface/GenTopFHSelection.hpp"

using namespace std;

GenTopFHSelection::GenTopFHSelection() {}
GenTopFHSelection::~GenTopFHSelection() {}

void GenTopFHSelection::InitCutflow(Cutflow& cutflow) {
  cutflow.AddStep("Event is FullHadronic ttbar");

  initialized = true;
}

bool GenTopFHSelection::IsSelected(const InputCollections& input,
                                   Cutflow& cutflow) {
  if (!initialized) cerr << "GenTopFHSelection not initialized" << endl;

  std::vector<reco::GenParticle> tophad;
  std::vector<reco::GenParticle> toplep;

  if (input.genTopEvt.IsFilled()) {
    tophad = input.genTopEvt.GetAllTopHads();
    toplep = input.genTopEvt.GetAllTopLeps();
  }

  if (!(tophad.size() == 2 and toplep.size() == 0)) {
    return false;
  } else {
    cutflow.EventSurvivedStep("Event is FullHadronic ttbar",
                              input.weights.at("Weight"));
    return true;
  }
}
