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
  
  for(auto& jet : input.selectedJetsLoose){
    if(BoostedUtils::PassesCSV(jet, 'M')) return false;
  }

  cutflow.EventSurvivedStep("No bjets",input.weights.at("Weight"));
  return true;    

}