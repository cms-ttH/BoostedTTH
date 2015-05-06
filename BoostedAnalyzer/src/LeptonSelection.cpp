#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"

using namespace std;

LeptonSelection::LeptonSelection (){}
LeptonSelection::~LeptonSelection (){}

void LeptonSelection::Init(const edm::ParameterSet& iConfig, Cutflow& cutflow){

  muonTriggers = iConfig.getParameter< std::vector<std::string> >("muonTriggers");
  electronTriggers = iConfig.getParameter< std::vector<std::string> >("electronTriggers");
  channel = iConfig.getParameter<std::string>("channel");
  cutflow.AddStep("Single lepton trigger");
  cutflow.AddStep("== 1 loose lepton");
  cutflow.AddStep("== 1 tight lepton same flavor");
  cutflow.AddStep("== 0 loose leptons different flavor");
//for testing

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
    if(!muonTriggered && !electronTriggered) return false;
    else cutflow.EventSurvivedStep("Single lepton trigger");
    if(!( (muonTriggered&&nmuonsloose==1) || (electronTriggered&&nelectronsloose==1) ) ) return false;
    else cutflow.EventSurvivedStep("== 1 loose lepton");
    if(!( (muonTriggered&&nmuonsloose==1&&nmuons==1) || (electronTriggered&&nelectronsloose==1&&nelectrons==1) ) ) return false;
    else cutflow.EventSurvivedStep("== 1 tight lepton same flavor");
    if(!( (muonTriggered&&nmuonsloose==1&&nmuons==1&&nelectronsloose==0) || (electronTriggered&&nelectronsloose==1&&nelectrons==1&&nmuonsloose==0) ) ) return false;
    else cutflow.EventSurvivedStep("== 0 loose leptons different flavor");
  }
  else if(channel=="el"){
    if(!electronTriggered) return false;
    else cutflow.EventSurvivedStep("Single lepton trigger");
    if(! (electronTriggered&&nelectronsloose==1 ) ) return false;
    else cutflow.EventSurvivedStep("== 1 loose lepton");
    if(!( electronTriggered&&nelectronsloose==1&&nelectrons==1 ) ) return false;
    else cutflow.EventSurvivedStep("== 1 tight lepton same flavor");
    if(!( electronTriggered&&nelectronsloose==1&&nelectrons==1&&nmuonsloose==0 ) ) return false;
    else cutflow.EventSurvivedStep("== 0 loose leptons different flavor");
  }
  else if(channel=="mu"){
    if(!muonTriggered) return false;
    else cutflow.EventSurvivedStep("Single lepton trigger");
    if(!( muonTriggered&&nmuonsloose==1 ) ) return false;
    else cutflow.EventSurvivedStep("== 1 loose lepton");
    if(!( muonTriggered&&nmuonsloose==1&&nmuons==1 ) ) return false;
    else cutflow.EventSurvivedStep("== 1 tight lepton same flavor");
    if(!( muonTriggered&&nmuonsloose==1&&nmuons==1&&nelectronsloose==0 ) ) return false;
    else cutflow.EventSurvivedStep("== 0 loose leptons different flavor");
  }
  else {
    std::cerr << "channel of lepton selection does not exist! " << std::endl;
    return false;
  }

  return true;
}
