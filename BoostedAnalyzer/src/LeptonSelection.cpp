#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"

using namespace std;

LeptonSelection::LeptonSelection (){}
LeptonSelection::~LeptonSelection (){}

void LeptonSelection::Init(const edm::ParameterSet& iConfig, Cutflow& cutflow){

  muonTriggers = iConfig.getParameter< std::vector<std::string> >("muonTriggers");
  electronTriggers = iConfig.getParameter< std::vector<std::string> >("electronTriggers");

  cutflow.AddStep("Has PV");
  cutflow.AddStep("Single lepton trigger");
  cutflow.AddStep("== 1 loose lepton");
  cutflow.AddStep("== 1 tight lepton same flavor");
  cutflow.AddStep("== 0 loose leptons different flavor");
  
  initialized=true;
}

bool LeptonSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "LeptonSelection not initialized" << endl;

  int npvs = input.selectedPVs.size();
  int nelectrons = input.selectedElectrons.size();
  int nmuons = input.selectedMuons.size();
  int nelectronsloose = input.selectedElectronsLoose.size();
  int nmuonsloose = input.selectedMuonsLoose.size();
  
  bool muonTriggered = BoostedUtils::IsAnyTriggerBitFired(muonTriggers,input.triggerResults,input.hlt_config);
  bool electronTriggered = BoostedUtils::IsAnyTriggerBitFired(electronTriggers,input.triggerResults,input.hlt_config);

  if(npvs<1) return false;
  else cutflow.EventSurvivedStep("Has PV");
  if(!muonTriggered && !electronTriggered) return false;
  else cutflow.EventSurvivedStep("Single lepton trigger");
  if(!( (muonTriggered&&nmuonsloose==1) || (electronTriggered&&nelectronsloose==1) ) ) return false;
  else cutflow.EventSurvivedStep("== 1 loose lepton");
  if(!( (muonTriggered&&nmuonsloose==1&&nmuons==1) || (electronTriggered&&nelectronsloose==1&&nelectrons==1) ) ) return false;
  else cutflow.EventSurvivedStep("== 1 tight lepton same flavor");
  if(!( (muonTriggered&&nmuonsloose==1&&nmuons==1&&nelectronsloose==0) || (electronTriggered&&nelectronsloose==1&&nelectrons==1&&nmuonsloose==0) ) ) return false;
  else cutflow.EventSurvivedStep("== 0 loose leptons different flavor");
  
  return true;
}
