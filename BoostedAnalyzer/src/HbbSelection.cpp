#include "BoostedTTH/BoostedAnalyzer/interface/HbbSelection.hpp"

using namespace std;

HbbSelection::HbbSelection() {}
HbbSelection::~HbbSelection() {}

void HbbSelection::InitCutflow(Cutflow& cutflow)
{
    cutflow.AddStep("Higgs to bb");

    initialized = true;
}

bool HbbSelection::IsSelected(const InputCollections& input, Cutflow& cutflow)
{
    if (!initialized) cerr << "HbbSelection not initialized" << endl;

    if (input.higgsDecay == HiggsDecay::bb || input.higgsDecay == HiggsDecay::NA) {
        cutflow.EventSurvivedStep("Higgs to bb", input.weights.at("Weight"));
        return true;
    }
    return false;
}
