#include "BoostedTTH/BoostedAnalyzer/interface/THQJetSelection.hpp"

using namespace std;

THQJetSelection::THQJetSelection (){}
THQJetSelection::~THQJetSelection (){}

void THQJetSelection::InitCutflow(Cutflow& cutflow){

  cutflow.AddStep(">= 3 b-tagged single top jets");
  cutflow.AddStep(">= 1 untagged single top jet");
  cutflow.AddStep(">= 4 single top jets >= 30 GeV");

  initialized=true;
}

bool THQJetSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "THQJetSelection not initialized" << endl;
  return true;
  //  if(){
  //    cutflow.EventSurvivedStep(">= 3 b-tagged single top jets",input.weights.at("Weight"));   

    //  }
    //  return false;   

}
