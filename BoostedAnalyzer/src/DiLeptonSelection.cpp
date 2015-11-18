#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonSelection.hpp"

using namespace std;

DiLeptonSelection::DiLeptonSelection(std::vector<std::string> elelTriggers_, std::vector<std::string> mumuTriggers_, std::vector<std::string> elmuTriggers_, std::string channel_, int step_):elelTriggers(elelTriggers_),mumuTriggers(mumuTriggers_),elmuTriggers(elmuTriggers_),channel(channel_),step(step_){
}

DiLeptonSelection::DiLeptonSelection(std::string elelTrigger, std::string mumuTrigger, std::string elmuTrigger, std::string channel_, int step_):DiLeptonSelection(std::vector<std::string> (1,elelTrigger),std::vector<std::string> (1,mumuTrigger),std::vector<std::string> (1,elmuTrigger),channel_,step_){
}

DiLeptonSelection::DiLeptonSelection(const edm::ParameterSet& iConfig, int step_):DiLeptonSelection(iConfig.getParameter< std::vector<std::string> >("elelTriggers"),
												    iConfig.getParameter< std::vector<std::string> >("mumuTriggers"),
												    iConfig.getParameter< std::vector<std::string> >("elmuTriggers"),
												    iConfig.getParameter<std::string>("dlchannel"),
												    step_){
}

DiLeptonSelection::~DiLeptonSelection (){}

void DiLeptonSelection::InitCutflow(Cutflow& cutflow){
  if(step<0||step==1)
    cutflow.AddStep("Dilepton trigger");
  if(step<0||step==2)
    cutflow.AddStep("== 2 opposite sign leptons");
    
  initialized=true;
}

bool DiLeptonSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "DiLeptonSelection not initialized" << endl;
  
  int nleadelectrons_p = 0;
  int nleadelectrons_n = 0;
  
  for(auto e=input.selectedElectronsDL.begin();e!=input.selectedElectronsDL.end();e++){
    if(e->charge()>0) {
    	nleadelectrons_p++;      
    }
    else{ 
    	nleadelectrons_n++;
    }
  }
  
  int nleadelectrons = nleadelectrons_p+nleadelectrons_n;
  
  int nsubleadelectrons_p = 0;
  int nsubleadelectrons_n = 0;
  
  for(auto e=input.selectedElectronsLoose.begin();e!=input.selectedElectronsLoose.end();e++){
  
    bool leadID = false;
    
    for(auto le=input.selectedElectronsDL.begin();le!=input.selectedElectronsDL.end();le++){
      if(BoostedUtils::DeltaR(le->p4(),e->p4())<0.001){
        leadID = true;
        break;
      }
    }
    
    if(leadID) continue;
    
    if(e->charge()>0) { 
    	nsubleadelectrons_p++;      
    }
    else {
    	nsubleadelectrons_n++;
    }
  }
  
  int nelectrons_p = nleadelectrons_p + nsubleadelectrons_p;
  int nelectrons_n = nleadelectrons_n + nsubleadelectrons_n;
  
  int nleadmuons_p = 0;
  int nleadmuons_n = 0;
  
  for(auto e=input.selectedMuonsDL.begin();e!=input.selectedMuonsDL.end();e++){
    if(e->charge()>0) {
    	nleadmuons_p++;      
    }
    else { 
    	nleadmuons_n++;
    }
  }
  
  int nleadmuons = nleadmuons_p+nleadmuons_n;
  
  int nsubleadmuons_p = 0;
  int nsubleadmuons_n = 0;
  
  for(auto mu=input.selectedMuonsLoose.begin();mu!=input.selectedMuonsLoose.end();mu++){
  
    bool leadID = false;
    
    for(auto lmu=input.selectedMuonsDL.begin();lmu!=input.selectedMuonsDL.end();lmu++){
      if(BoostedUtils::DeltaR(lmu->p4(),mu->p4())<0.001){
        leadID = true;
        break;
      }
    }
    
    if(leadID) continue;
    
    if(mu->charge()>0) {
    	nsubleadmuons_p++;      
    }
    else {
    	nsubleadmuons_n++;
    }
  }
  
  int nmuons_p = nleadmuons_p + nsubleadmuons_p;
  int nmuons_n = nleadmuons_n + nsubleadmuons_n;
  
  int nleadleptons = nleadelectrons+nleadmuons;

  bool elelTriggered = input.triggerInfo.IsAnyTriggered(elelTriggers);
  bool mumuTriggered = input.triggerInfo.IsAnyTriggered(mumuTriggers);
  bool elmuTriggered = input.triggerInfo.IsAnyTriggered(elmuTriggers);

  bool elel_step2 = elelTriggered && nleadelectrons>=1 && (nelectrons_p==1&&nelectrons_n==1 && nmuons_p==0&&nmuons_n==0);
  bool elmu_step2 = elmuTriggered && nleadleptons>=1 && ((nelectrons_p==1&&nmuons_n==1 && nelectrons_n==0&&nmuons_p==0)||(nelectrons_n==1&&nmuons_p==1 && nelectrons_p==0&&nmuons_n==0));
  bool mumu_step2 = mumuTriggered && nleadmuons>=1 && (nmuons_p==1&&nmuons_n==1 && nelectrons_p==0 && nelectrons_n==0);

  /*
  std::cout << "elelTriggered: " << elelTriggered << "   mumuTriggered: " << mumuTriggered << "   elmuTriggered: " << elmuTriggered << std::endl;
  std::cout << "nleadelectrons: " << nleadelectrons << "   nelectrons_p: " << nelectrons_p << "   nelectrons_n: " << nelectrons_n << std::endl;
  std::cout << "nleadmuons: " << nleadmuons << "   nmuons_p: " << nmuons_p << "   nmuons_n: " << nmuons_n << std::endl;
  */
  
  if(channel=="elel"){
    if(step<0||step==1){
      if(!elelTriggered) {
      	return false;
      }
      else {
      	cutflow.EventSurvivedStep("Dilepton trigger",input.weights.at("Weight"));
      }
    }
    if(step<0||step==2){
      if( !elel_step2 ) {
      	return false;
      }
      else {
      	cutflow.EventSurvivedStep("== 2 opposite sign leptons",input.weights.at("Weight"));
      }
    }
  }
  else  if(channel=="mumu"){
    if(step<0||step==1){
      if(!mumuTriggered) {
      	return false;
      }
      else {
      	cutflow.EventSurvivedStep("Dilepton trigger",input.weights.at("Weight"));
      }
    }
    if(step<0||step==2){
      if( !mumu_step2 ) {
      	return false;
      }
      else {
      	cutflow.EventSurvivedStep("== 2 opposite sign leptons",input.weights.at("Weight"));
      }
    }
  }
  else  if(channel=="elmu"){
    if(step<0||step==1){
      if(!elmuTriggered) {
      	return false;
      }
      else {
      	cutflow.EventSurvivedStep("Dilepton trigger",input.weights.at("Weight"));
      }
    }
    if(step<0||step==2){
      if( !elmu_step2 ) {
      	return false;
      }
      else {
      	cutflow.EventSurvivedStep("== 2 opposite sign leptons",input.weights.at("Weight"));
      }
    }
  }
  else  if(channel=="all"){
    if(step<0||step==1){
      if(!elmuTriggered&&!elelTriggered&&!mumuTriggered) {
      	return false;
      }
      else {
      	cutflow.EventSurvivedStep("Dilepton trigger",input.weights.at("Weight"));
      }
    }
    if(step<0||step==2){
      if( !elmu_step2&&!elel_step2&&!mumu_step2 ) {
      	return false;
      }
      else {
      	cutflow.EventSurvivedStep("== 2 opposite sign leptons",input.weights.at("Weight"));
      }
    }
  }
  else {
    std::cerr << "channel of lepton selection does not exist! " << std::endl;
    return false;
  }

  return true;
}
