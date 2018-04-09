#include "BoostedTTH/BoostedAnalyzer/interface/GenTopDLSelection.hpp"

using namespace std;

GenTopDLSelection::GenTopDLSelection()
{
}
GenTopDLSelection::~GenTopDLSelection()
{
}

void
GenTopDLSelection::InitCutflow(Cutflow& cutflow)
{

  cutflow.AddStep("Event is DL ttbar");

  initialized = true;
}

bool
GenTopDLSelection::IsSelected(const InputCollections& input, Cutflow& cutflow)
{
  if (!initialized)
    cerr << "GenTopDLSelection not initialized" << endl;

  std::vector<reco::GenParticle> tophad;
  std::vector<reco::GenParticle> toplep;

  if (input.genTopEvt.IsFilled()) {
    tophad = input.genTopEvt.GetAllTopHads();
    toplep = input.genTopEvt.GetAllTopLeps();
  }

  if (!(tophad.size() == 0 and toplep.size() == 2)) {
    return false;
  } else {
    cutflow.EventSurvivedStep("Event is DL ttbar", input.weights.at("Weight"));
    return true;
  }
}
