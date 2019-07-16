#include "BoostedTTH/BoostedAnalyzer/interface/GenTopSLSelection.hpp"

using namespace std;

GenTopSLSelection::GenTopSLSelection() {}
GenTopSLSelection::~GenTopSLSelection() {}

void GenTopSLSelection::InitCutflow(Cutflow& cutflow)
{
    cutflow.AddStep("Event is SL ttbar");

    initialized = true;
}

bool GenTopSLSelection::IsSelected(const InputCollections& input, Cutflow& cutflow)
{
    if (!initialized) cerr << "GenTopSLSelection not initialized" << endl;

    std::vector< reco::GenParticle > tophad;
    std::vector< reco::GenParticle > toplep;

    if (input.genTopEvt.IsFilled()) {
        tophad = input.genTopEvt.GetAllTopHads();
        toplep = input.genTopEvt.GetAllTopLeps();
    }

    if (!(tophad.size() == 1 and toplep.size() == 1)) { return false; }
    else {
        cutflow.EventSurvivedStep("Event is SL ttbar", input.weights.at("Weight"));
        return true;
    }
}
