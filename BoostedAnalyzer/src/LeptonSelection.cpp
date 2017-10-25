#include "FWCore/Utilities/interface/Exception.h"

#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"

using namespace std;

LeptonSelection::LeptonSelection(std::vector<std::string> electronTriggers_, std::vector<std::string> muonTriggers_, std::string channel_, int step_):electronTriggers(electronTriggers_),muonTriggers(muonTriggers_),channel(channel_),step(step_){
}

LeptonSelection::LeptonSelection(std::string electronTrigger, std::string muonTrigger, std::string channel_, int step_):LeptonSelection(std::vector<std::string> (1,(electronTrigger)),std::vector<std::string> (1,muonTrigger),channel_,step_){
}

LeptonSelection::LeptonSelection(const edm::ParameterSet& iConfig, int step_):LeptonSelection(iConfig.getParameter< std::vector<std::string> >("electronTriggers"),
											      iConfig.getParameter< std::vector<std::string> >("muonTriggers"),
											      iConfig.getParameter<std::string>("channel"),
											      step_){
}

LeptonSelection::~LeptonSelection (){}

void LeptonSelection::InitCutflow(Cutflow& cutflow){
  if(step<0||step==1)
    cutflow.AddStep("Single lepton trigger");
  if(step<0||step==2)
    cutflow.AddStep("== 1 loose lepton same flavor");
  if(step<0||step==3)
    cutflow.AddStep("== 1 tight lepton same flavor");
  if(step<0||step==4)
    cutflow.AddStep("== 0 loose leptons different flavor");
  if(step<0||step==5)
    cutflow.AddStep("== No leptons");
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
  
  //std::cout << "muonTriggered " << muonTriggered << " electronTriggered " << electronTriggered << std::endl;
  //std::cout << channel << std::endl;
  if(channel=="both"){
    if(step<0||step==1){
      if(!muonTriggered && !electronTriggered) return false;
      else cutflow.EventSurvivedStep("Single lepton trigger",input.weights.at("Weight"));
    }
    if(step<0||step==2){
      if(!( (muonTriggered&&nmuonsloose==1) || (electronTriggered&&nelectronsloose==1) ) ) return false;
      else cutflow.EventSurvivedStep("== 1 loose lepton same flavor",input.weights.at("Weight"));
    }
    if(step<0||step==3){
      if(!( (muonTriggered&&nmuonsloose==1&&nmuons==1) || (electronTriggered&&nelectronsloose==1&&nelectrons==1) ) ) return false;
      else cutflow.EventSurvivedStep("== 1 tight lepton same flavor",input.weights.at("Weight"));
    }
    if(step<0||step==4){
      if(!( (muonTriggered&&nmuonsloose==1&&nmuons==1&&nelectronsloose==0) || (electronTriggered&&nelectronsloose==1&&nelectrons==1&&nmuonsloose==0) ) ) return false;
      else cutflow.EventSurvivedStep("== 0 loose leptons different flavor",input.weights.at("Weight"));
    }
  }
  else if(channel=="el"){
    if(step<0||step==1){
      if(!electronTriggered) return false;
      else cutflow.EventSurvivedStep("Single lepton trigger",input.weights.at("Weight"));
    }
    if(step<0||step==2){
      if( nelectronsloose!=1 ) return false;
      else cutflow.EventSurvivedStep("== 1 loose lepton same flavor",input.weights.at("Weight"));
    }
    if(step<0||step==3){
      if( nelectrons!=1 ) return false;
      else cutflow.EventSurvivedStep("== 1 tight lepton same flavor",input.weights.at("Weight"));
    }
    if(step<0||step==4){
      if( nmuonsloose!=0 ) return false;
      else cutflow.EventSurvivedStep("== 0 loose leptons different flavor",input.weights.at("Weight"));
    }
  }
  else if(channel=="mu"){
    if(step<0||step==1){
      if(!muonTriggered) return false;
      else cutflow.EventSurvivedStep("Single lepton trigger",input.weights.at("Weight"));
    }
    if(step<0||step==2){
      if( nmuonsloose!=1 ) return false;
      else cutflow.EventSurvivedStep("== 1 loose lepton same flavor",input.weights.at("Weight"));
    }
    if(step<0||step==3){
      if( nmuons!=1 ) return false;
      else cutflow.EventSurvivedStep("== 1 tight lepton same flavor",input.weights.at("Weight"));
    }
    if(step<0||step==4){
      if( nelectronsloose!=0 ) return false;
      else cutflow.EventSurvivedStep("== 0 loose leptons different flavor",input.weights.at("Weight"));
    }
  }
  else if(channel=="veto"){
//    if(step<0||step==1){
//      if(muonTriggered || electronTriggered) return false;
//      else cutflow.EventSurvivedStep("lepton VETO trigger",input.weights.at("Weight"));
//    }
    if(step<0||step==5){
      if( nmuons==0 && nelectrons==0 && !(muonTriggered || electronTriggered)) cutflow.EventSurvivedStep("== No leptons",input.weights.at("Weight"));
      else return false;
    }
  }  else {
    throw cms::Exception("BadSelection")
      << "channel '" << channel << "' of lepton selection does not exist!\n"
      << "Please fix BoostedAnalyzer.channel parameter\n"
      << "Values are 'el', 'mu', or 'both'";      
    return false;
  }
  //std::cout << "IsSelected=true" << std::endl;
  return true;
}
