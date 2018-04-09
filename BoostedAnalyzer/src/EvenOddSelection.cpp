#include "BoostedTTH/BoostedAnalyzer/interface/EvenOddSelection.hpp"

using namespace std;

EvenOddSelection::EvenOddSelection(bool selEven_)
  : selEven(selEven_)
{
}
EvenOddSelection::~EvenOddSelection()
{
}

void
EvenOddSelection::InitCutflow(Cutflow& cutflow)
{
  if (selEven)
    cutflow.AddStep("Evt ID is even");
  else
    cutflow.AddStep("Evt ID is odd");

  initialized = true;
}

bool
EvenOddSelection::IsSelected(const InputCollections& input, Cutflow& cutflow)
{
  if (!initialized)
    cerr << "EvenOddSelection not initialized" << endl;

  if ((input.eventInfo.evt % 2 == 0 && !selEven) ||
      (input.eventInfo.evt % 2 == 1 && selEven)) {
    return false;
  } else {
    if (selEven)
      cutflow.EventSurvivedStep("Evt ID is even", input.weights.at("Weight"));
    else
      cutflow.EventSurvivedStep("Evt ID is odd", input.weights.at("Weight"));
    return true;
  }
}
