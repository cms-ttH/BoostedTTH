#include "BoostedTTH/BoostedAnalyzer/interface/LooseLeptonSelection.hpp"

using namespace std;

LooseLeptonSelection::LooseLeptonSelection(
  std::vector<std::string> electronTriggers_,
  std::vector<std::string> muonTriggers_,
  std::string channel_,
  int step_)
  : electronTriggers(electronTriggers_)
  , muonTriggers(muonTriggers_)
  , channel(channel_)
  , step(step_)
{
}

LooseLeptonSelection::LooseLeptonSelection(std::string electronTrigger,
                                           std::string muonTrigger,
                                           std::string channel_,
                                           int step_)
  : LooseLeptonSelection(std::vector<std::string>(1, (electronTrigger)),
                         std::vector<std::string>(1, muonTrigger),
                         channel_,
                         step_)
{
}

LooseLeptonSelection::LooseLeptonSelection(const edm::ParameterSet& iConfig,
                                           int step_)
  : LooseLeptonSelection(
      iConfig.getParameter<std::vector<std::string>>("electronTriggers"),
      iConfig.getParameter<std::vector<std::string>>("muonTriggers"),
      iConfig.getParameter<std::string>("channel"),
      step_)
{
}

LooseLeptonSelection::~LooseLeptonSelection()
{
}

void
LooseLeptonSelection::InitCutflow(Cutflow& cutflow)
{
  if (step < 0 || step == 1)
    cutflow.AddStep("Single lepton trigger");
  if (step < 0 || step == 2)
    cutflow.AddStep(">= 1 loose lepton same flavor");

  initialized = true;
}

bool
LooseLeptonSelection::IsSelected(const InputCollections& input,
                                 Cutflow& cutflow)
{
  if (!initialized)
    cerr << "LooseLeptonSelection not initialized" << endl;

  int nelectronsloose = input.selectedElectronsLoose.size();
  int nmuonsloose = input.selectedMuonsLoose.size();
  bool muonTriggered = input.triggerInfo.IsAnyTriggered(muonTriggers);
  bool electronTriggered = input.triggerInfo.IsAnyTriggered(electronTriggers);
  if (channel == "both") {
    if (step < 0 || step == 1) {
      if (!muonTriggered && !electronTriggered)
        return false;
      else
        cutflow.EventSurvivedStep("Single lepton trigger",
                                  input.weights.at("Weight"));
    }
    if (step < 0 || step == 2) {
      if (!((muonTriggered && nmuonsloose >= 1) ||
            (electronTriggered && nelectronsloose >= 1)))
        return false;
      else
        cutflow.EventSurvivedStep(">= 1 loose lepton same flavor",
                                  input.weights.at("Weight"));
    }
  } else if (channel == "el") {
    if (step < 0 || step == 1) {
      if (!electronTriggered)
        return false;
      else
        cutflow.EventSurvivedStep("Single lepton trigger",
                                  input.weights.at("Weight"));
    }
    if (step < 0 || step == 2) {
      if (nelectronsloose < 1)
        return false;
      else
        cutflow.EventSurvivedStep(">= 1 loose lepton same flavor",
                                  input.weights.at("Weight"));
    }
  } else if (channel == "mu") {
    if (step < 0 || step == 1) {
      if (!muonTriggered)
        return false;
      else
        cutflow.EventSurvivedStep("Single lepton trigger",
                                  input.weights.at("Weight"));
    }
    if (step < 0 || step == 2) {
      if (nmuonsloose < 1)
        return false;
      else
        cutflow.EventSurvivedStep(">= 1 loose lepton same flavor",
                                  input.weights.at("Weight"));
    }
  } else {
    std::cerr << "channel of lepton selection does not exist! " << std::endl;
    return false;
  }

  return true;
}
