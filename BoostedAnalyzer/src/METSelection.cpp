#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"

using namespace std;

METSelection::METSelection (){}
METSelection::~METSelection (){}

void METSelection::InitCutflow(Cutflow& cutflow){

  cutflow.AddStep("MET <= 800 for FastSim");

  initialized=true;
}

bool METSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "METSelection not initialized" << endl;
  double met=input.pfMET.pt();
  if(met<=800){
    cutflow.EventSurvivedStep("MET <= 800 for FastSim" ,input.weights.at("Weight"));
    return true;
  }

  return false;   

} 
