#include "BoostedTTH/BoostedAnalyzer/interface/BTagVetoSelection.hpp"

using namespace std;

BTagVetoSelection::BTagVetoSelection (){}
BTagVetoSelection::~BTagVetoSelection (){}

void BTagVetoSelection::InitCutflow(Cutflow& cutflow){

  cutflow.AddStep("No bjets");

  initialized=true;
}

bool BTagVetoSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "BTagVetoSelection not initialized" << endl;
  
  uint ntags = 0;
  for(auto& jet : input.selectedJetsLoose){
    if(BoostedUtils::PassesCSV(jet, 'M')){
      ntags++;
    }
  }

  if(ntags>0) {
    return false;
  }
  else{
    cutflow.EventSurvivedStep("No bjets",input.weights.at("Weight"));
    return true;    
  }

}