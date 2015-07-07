#include "BoostedTTH/BoostedAnalyzer/interface/THQJetSelection.hpp"

using namespace std;

THQJetSelection::THQJetSelection (){}
THQJetSelection::~THQJetSelection (){}

void THQJetSelection::InitCutflow(Cutflow& cutflow){

    cutflow.AddStep(">= 4 single top jets >= 30 GeV");
    cutflow.AddStep(">= 3 b-tagged single top jets");
    cutflow.AddStep(">= 1 untagged single top jet");
    
    initialized=true;
}

bool THQJetSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
    if(!initialized) cerr << "THQJetSelection not initialized" << endl;
    int njets30=0;
    int ntags=0;
    int nuntagged=0;
    for(auto j=input.selectedJetsSingleTop.begin(); j!=input.selectedJetsSingleTop.begin(); j++){
	if(j->pt()>30) njets30++;
	if(fabs(j->eta())<2.4&&BoostedUtils::PassesCSV(*j,'T')) ntags++;
	else nuntagged++;
    }
    
    if(njets30<4){
	cutflow.EventSurvivedStep(">= 4 single top jets >= 30 GeV",input.weights.at("Weight"));   	
    }
    else{
	return false;
    }
    if(ntags<3){
	cutflow.EventSurvivedStep(">= 3 b-tagged single top jets",input.weights.at("Weight"));   	
    }
    else{
	return false;
    }
    if(nuntagged<1){
	cutflow.EventSurvivedStep(">= 1 untagged single top jet",input.weights.at("Weight"));   	
    }
    else{
	return false;
    }
  
    return true;   

}
