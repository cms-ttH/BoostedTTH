#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"

using namespace std;

LeptonSelection::LeptonSelection (const edm::ParameterSet& iConfig, int step_){
  muonTriggers = iConfig.getParameter< std::vector<std::string> >("muonTriggers");
  electronTriggers = iConfig.getParameter< std::vector<std::string> >("electronTriggers");
  channel = iConfig.getParameter<std::string>("channel");
  step=step_;
}

LeptonSelection::~LeptonSelection (){}

void LeptonSelection::InitCutflow(Cutflow& cutflow){
  if(step<0||step==1)
    cutflow.AddStep("Single lepton trigger");
  if(step<0||step==2)
    cutflow.AddStep("== 1 loose lepton");
  if(step<0||step==3)
    cutflow.AddStep("== 1 tight lepton same flavor");
  if(step<0||step==4)
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
  // what needs to be fixed here exactly?
  bool muonTriggered = input.triggerInfo.IsAnyTriggered(muonTriggers);
  bool electronTriggered = input.triggerInfo.IsAnyTriggered(electronTriggers);
  if(channel=="both"){
    if(step<0||step==1){
      if(!muonTriggered && !electronTriggered) return false;
      else cutflow.EventSurvivedStep("Single lepton trigger");
    }
    if(step<0||step==2){
      if(!( (muonTriggered&&nmuonsloose==1) || (electronTriggered&&nelectronsloose==1) ) ) return false;
      else cutflow.EventSurvivedStep("== 1 loose lepton");
    }
    if(step<0||step==3){
      if(!( (muonTriggered&&nmuonsloose==1&&nmuons==1) || (electronTriggered&&nelectronsloose==1&&nelectrons==1) ) ) return false;
      else cutflow.EventSurvivedStep("== 1 tight lepton same flavor");
    }
    if(step<0||step==4){
      if(!( (muonTriggered&&nmuonsloose==1&&nmuons==1&&nelectronsloose==0) || (electronTriggered&&nelectronsloose==1&&nelectrons==1&&nmuonsloose==0) ) ) return false;
      else cutflow.EventSurvivedStep("== 0 loose leptons different flavor");
    }
  }
  else if(channel=="el"){
    if(step<0||step==1){
      if(!electronTriggered) return false;
      else cutflow.EventSurvivedStep("Single lepton trigger");
    }
    if(step<0||step==2){
      if(! (electronTriggered&&nelectronsloose==1 ) ) return false;
      else cutflow.EventSurvivedStep("== 1 loose lepton");
    }
    if(step<0||step==3){
      if(!( electronTriggered&&nelectronsloose==1&&nelectrons==1 ) ) return false;
      else cutflow.EventSurvivedStep("== 1 tight lepton same flavor");
    }
    if(step<0||step==4){
      if(!( electronTriggered&&nelectronsloose==1&&nelectrons==1&&nmuonsloose==0 ) ) return false;
      else cutflow.EventSurvivedStep("== 0 loose leptons different flavor");
    }
  }
  else if(channel=="mu"){
    if(step<0||step==1){
      if(!muonTriggered) return false;
      else cutflow.EventSurvivedStep("Single lepton trigger");
    }
    if(step<0||step==2){
      if(!( muonTriggered&&nmuonsloose==1 ) ) return false;
      else cutflow.EventSurvivedStep("== 1 loose lepton");
    }
    if(step<0||step==3){
      if(!( muonTriggered&&nmuonsloose==1&&nmuons==1 ) ) return false;
      else cutflow.EventSurvivedStep("== 1 tight lepton same flavor");
    }
    if(step<0||step==4){
      if(!( muonTriggered&&nmuonsloose==1&&nmuons==1&&nelectronsloose==0 ) ) return false;
      else cutflow.EventSurvivedStep("== 0 loose leptons different flavor");
    }
  }
  else {
    std::cerr << "channel of lepton selection does not exist! " << std::endl;
    return false;
  }

  return true;
}
