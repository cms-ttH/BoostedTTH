#include "BoostedTTH/BoostedAnalyzer/interface/VertexSelection.hpp"

using namespace std;

VertexSelection::VertexSelection() {}
VertexSelection::~VertexSelection() {}

void VertexSelection::InitCutflow(Cutflow& cutflow)
{
    cutflow.AddStep("First PV is good PV");

    initialized = true;
}

bool VertexSelection::IsSelected(const InputCollections& input, Cutflow& cutflow)
{
    if (!initialized) cerr << "VertexSelection not initialized" << endl;

    if (!input.eventInfo.firstVertexIsGood) { return false; }
    else {
        cutflow.EventSurvivedStep("First PV is good PV", input.weights.at("Weight"));
        return true;
    }
}
