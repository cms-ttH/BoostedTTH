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
	cutflow.AddStep(">= 2 opposite sign leptons");
    
    initialized=true;
}

bool DiLeptonSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
    if(!initialized) cerr << "DiLeptonSelection not initialized" << endl;
    int nelectrons_p=0;
    int nelectrons_n=0;
    int nelectrons=input.selectedElectronsDL.size();
    for(auto e=input.selectedElectronsDL.begin();e!=input.selectedElectronsDL.end();e++){
      if(e->charge()>0) nelectrons_p++;      
      else nelectrons_n++;
    }
    int nmuons_p=0;
    int nmuons_n=0;
    int nmuons=input.selectedMuonsDL.size();
    for(auto e=input.selectedMuonsDL.begin();e!=input.selectedMuonsDL.end();e++){
      if(e->charge()>0) nmuons_p++;
      else nmuons_n++;
    }
    int nleptons=nmuons+nelectrons;
    
    bool elelTriggered = input.triggerInfo.IsAnyTriggered(elelTriggers);
    bool mumuTriggered = input.triggerInfo.IsAnyTriggered(mumuTriggers);
    bool elmuTriggered = input.triggerInfo.IsAnyTriggered(elmuTriggers);

    bool elel_step2 = elelTriggered && nleptons>=2 && (nelectrons_p>=1&&nelectrons_n>=1);
    bool elmu_step2 = elmuTriggered && nleptons>=2 && ((nelectrons_p>=1&&nmuons_n>=1)||(nelectrons_n>=1&&nmuons_p>=1));
    bool mumu_step2 = mumuTriggered && nleptons>=2 && ((nmuons_p>=1&&nmuons_n>=1)||(nmuons_n>=1&&nmuons_p>=1));

    if(channel=="elel"){
	if(step<0||step==1){
	    if(!elelTriggered) return false;
	    else cutflow.EventSurvivedStep("Dilepton trigger",input.weights.at("Weight"));
	}
	if(step<0||step==2){
	    if( !elel_step2 ) return false;
	    else cutflow.EventSurvivedStep("== 2 opposite sign leptons",input.weights.at("Weight"));
	}
    }
    else  if(channel=="mumu"){
	if(step<0||step==1){
	    if(!mumuTriggered) return false;
	    else cutflow.EventSurvivedStep("Dilepton trigger",input.weights.at("Weight"));
	}
	if(step<0||step==2){
	    if( !mumu_step2 ) return false;
	    else cutflow.EventSurvivedStep("== 2 opposite sign leptons",input.weights.at("Weight"));
	}
    }
    else  if(channel=="elmu"){
	if(step<0||step==1){
	    if(!elmuTriggered) return false;
	    else cutflow.EventSurvivedStep("Dilepton trigger",input.weights.at("Weight"));
	}
	if(step<0||step==2){
	    if( !elmu_step2 ) return false;
	    else cutflow.EventSurvivedStep("== 2 opposite sign leptons",input.weights.at("Weight"));
	}
    }
    else  if(channel=="all"){
	if(step<0||step==1){
	    if(!elmuTriggered&&!elelTriggered&&!mumuTriggered) return false;
	    else cutflow.EventSurvivedStep("Dilepton trigger",input.weights.at("Weight"));
	}
	if(step<0||step==2){
	    if( !elmu_step2&&!elel_step2&&!mumu_step2 ) return false;
	    else cutflow.EventSurvivedStep("== 2 opposite sign leptons",input.weights.at("Weight"));
	}
    }
    else {
	std::cerr << "channel of lepton selection does not exist! " << std::endl;
	return false;
    }
    
    return true;
}
