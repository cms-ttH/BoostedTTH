#include "FWCore/Utilities/interface/Exception.h"

#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection_QCDControlregion.hpp"

using namespace std;

LeptonSelection_QCDControlregion::LeptonSelection_QCDControlregion(std::vector<std::string> electronTriggers_, std::vector<std::string> muonTriggers_, std::string channel_, int step_):electronTriggers(electronTriggers_),muonTriggers(muonTriggers_),channel(channel_),step(step_){
}

LeptonSelection_QCDControlregion::LeptonSelection_QCDControlregion(std::string electronTrigger, std::string muonTrigger, std::string channel_, int step_):LeptonSelection_QCDControlregion(std::vector<std::string> (1,(electronTrigger)),std::vector<std::string> (1,muonTrigger),channel_,step_){
}

LeptonSelection_QCDControlregion::LeptonSelection_QCDControlregion(const edm::ParameterSet& iConfig, int step_):LeptonSelection_QCDControlregion(iConfig.getParameter< std::vector<std::string> >("electronTriggers"),
											      iConfig.getParameter< std::vector<std::string> >("muonTriggers"),
											      iConfig.getParameter<std::string>("channel"),
											      step_){
}

LeptonSelection_QCDControlregion::~LeptonSelection_QCDControlregion (){}

void LeptonSelection_QCDControlregion::InitCutflow(Cutflow& cutflow){
  if(step<0||step==1)
    cutflow.AddStep("Single lepton trigger");
  if(step<0||step==2)
    cutflow.AddStep("== 1 loose lepton same flavor");
  if(step<0||step==3)
    cutflow.AddStep("== 1 tight lepton same flavor");
  if(step<0||step==4)
    cutflow.AddStep("== 0 loose leptons different flavor");

  initialized=true;
}

bool LeptonSelection_QCDControlregion::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "LeptonSelection_QCDControlregion not initialized" << endl;

  int nelectrons_iso_inverted = input.selectedElectronsDL.size();
  int nmuons_iso_inverted = input.selectedMuonsDL.size();
  int nelectronsloose_with_iso = input.selectedElectronsLoose.size();
  int nmuonsloose_with_iso = input.selectedMuonsLoose.size();
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
      if(!( (muonTriggered&&nmuonsloose_with_iso==0) || (electronTriggered&&nelectronsloose_with_iso==0) ) ) return false;
      else cutflow.EventSurvivedStep("== 1 loose lepton same flavor",input.weights.at("Weight"));
    }
    if(step<0||step==3){
      if(!( (muonTriggered&&nmuonsloose_with_iso==0&&nmuons_iso_inverted==1) || (electronTriggered&&nelectronsloose_with_iso==0&&nelectrons_iso_inverted==1) ) ) return false;
      else cutflow.EventSurvivedStep("== 1 tight lepton same flavor",input.weights.at("Weight"));
    }
    if(step<0||step==4){
      if(!( (muonTriggered&&nmuonsloose_with_iso==0&&nmuons_iso_inverted==1&&nelectronsloose_with_iso==0&&nelectrons_iso_inverted==0) || (electronTriggered&&nelectronsloose_with_iso==0&&nelectrons_iso_inverted==1&&nmuonsloose_with_iso==0&&nmuons_iso_inverted==0) ) ) return false;
      else cutflow.EventSurvivedStep("== 0 loose leptons different flavor",input.weights.at("Weight"));
    }
  }
  else if(channel=="el"){
    if(step<0||step==1){
      if(!electronTriggered) return false;
      else cutflow.EventSurvivedStep("Single lepton trigger",input.weights.at("Weight"));
    }
    if(step<0||step==2){
      if( nelectronsloose_with_iso!=0 ) return false;
      else cutflow.EventSurvivedStep("== 1 loose lepton same flavor",input.weights.at("Weight"));
    }
    if(step<0||step==3){
      if( nelectrons_iso_inverted!=1 ) return false;
      else cutflow.EventSurvivedStep("== 1 tight lepton same flavor",input.weights.at("Weight"));
    }
    if(step<0||step==4){
      if( nmuonsloose_with_iso!=0 || nmuons_iso_inverted!=0 ) return false;
      else cutflow.EventSurvivedStep("== 0 loose leptons different flavor",input.weights.at("Weight"));
    }
  }
  else if(channel=="mu"){
    if(step<0||step==1){
      if(!muonTriggered) return false;
      else cutflow.EventSurvivedStep("Single lepton trigger",input.weights.at("Weight"));
    }
    if(step<0||step==2){
      if( nmuonsloose_with_iso!=0 ) return false;
      else cutflow.EventSurvivedStep("== 1 loose lepton same flavor",input.weights.at("Weight"));
    }
    if(step<0||step==3){
      if( nmuons_iso_inverted!=1 ) return false;
      else cutflow.EventSurvivedStep("== 1 tight lepton same flavor",input.weights.at("Weight"));
    }
    if(step<0||step==4){
      if( nelectronsloose_with_iso!=0 || nelectrons_iso_inverted!=0 ) return false;
      else cutflow.EventSurvivedStep("== 0 loose leptons different flavor",input.weights.at("Weight"));
    }
  }
  else {
    throw cms::Exception("BadSelection")
      << "channel '" << channel << "' of lepton selection does not exist!\n"
      << "Please fix BoostedAnalyzer.channel parameter\n"
      << "Values are 'el', 'mu', or 'both'";      
    return false;
  }
  //std::cout << "IsSelected=true" << std::endl;
  return true;
}
