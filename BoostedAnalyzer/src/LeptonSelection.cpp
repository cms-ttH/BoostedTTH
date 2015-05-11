#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"

using namespace std;

LeptonSelection::LeptonSelection (const edm::ParameterSet& iConfig, int steps_){
  muonTriggers = iConfig.getParameter< std::vector<std::string> >("muonTriggers");
  electronTriggers = iConfig.getParameter< std::vector<std::string> >("electronTriggers");
  channel = iConfig.getParameter<std::string>("channel");
  steps=steps_;
}

LeptonSelection::~LeptonSelection (){}

void LeptonSelection::InitCutflow(Cutflow& cutflow){
  if(steps>0)
    cutflow.AddStep("Single lepton trigger");
  if(steps>1)
    cutflow.AddStep("== 1 loose lepton");
  if(steps>2)
    cutflow.AddStep("== 1 tight lepton same flavor");
  if(steps>3)
    cutflow.AddStep("== 0 loose leptons different flavor");

  initialized=true;
}

bool LeptonSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "LeptonSelection not initialized" << endl;

  int nelectrons = input.selectedElectrons.size();
  int nmuons = input.selectedMuons.size();
  int nelectronsloose = input.selectedElectronsLoose.size();
  int nmuonsloose = input.selectedMuonsLoose.size();
  // todo: fix triggers
  bool muonTriggered = input.triggerInfo.IsAnyTriggered(muonTriggers);
  bool electronTriggered = input.triggerInfo.IsAnyTriggered(electronTriggers);
  if(channel=="both"){
    if(steps<1) return true;
    if(!muonTriggered && !electronTriggered) return false;
    else cutflow.EventSurvivedStep("Single lepton trigger");

    if(steps<2) return true;
    if(!( (muonTriggered&&nmuonsloose==1) || (electronTriggered&&nelectronsloose==1) ) ) return false;
    else cutflow.EventSurvivedStep("== 1 loose lepton");

    if(steps<3) return true;
    if(!( (muonTriggered&&nmuonsloose==1&&nmuons==1) || (electronTriggered&&nelectronsloose==1&&nelectrons==1) ) ) return false;
    else cutflow.EventSurvivedStep("== 1 tight lepton same flavor");

    if(steps<4) return true;
    if(!( (muonTriggered&&nmuonsloose==1&&nmuons==1&&nelectronsloose==0) || (electronTriggered&&nelectronsloose==1&&nelectrons==1&&nmuonsloose==0) ) ) return false;
    else cutflow.EventSurvivedStep("== 0 loose leptons different flavor");
  }
  else if(channel=="el"){
    if(steps<1) return true;
    if(!electronTriggered) return false;
    else cutflow.EventSurvivedStep("Single lepton trigger");

    if(steps<2) return true;
    if(! (electronTriggered&&nelectronsloose==1 ) ) return false;
    else cutflow.EventSurvivedStep("== 1 loose lepton");

    if(steps<3) return true;
    if(!( electronTriggered&&nelectronsloose==1&&nelectrons==1 ) ) return false;
    else cutflow.EventSurvivedStep("== 1 tight lepton same flavor");

    if(steps<4) return true;
    if(!( electronTriggered&&nelectronsloose==1&&nelectrons==1&&nmuonsloose==0 ) ) return false;
    else cutflow.EventSurvivedStep("== 0 loose leptons different flavor");
  }
  else if(channel=="mu"){
    if(steps<1) return true;
    if(!muonTriggered) return false;
    else cutflow.EventSurvivedStep("Single lepton trigger");

    if(steps<2) return true;
    if(!( muonTriggered&&nmuonsloose==1 ) ) return false;
    else cutflow.EventSurvivedStep("== 1 loose lepton");

    if(steps<3) return true;
    if(!( muonTriggered&&nmuonsloose==1&&nmuons==1 ) ) return false;
    else cutflow.EventSurvivedStep("== 1 tight lepton same flavor");

    if(steps<4) return true;
    if(!( muonTriggered&&nmuonsloose==1&&nmuons==1&&nelectronsloose==0 ) ) return false;
    else cutflow.EventSurvivedStep("== 0 loose leptons different flavor");
  }
  else {
    std::cerr << "channel of lepton selection does not exist! " << std::endl;
    return false;
  }

  return true;
}
