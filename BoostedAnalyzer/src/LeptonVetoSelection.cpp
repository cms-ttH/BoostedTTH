#include "BoostedTTH/BoostedAnalyzer/interface/LeptonVetoSelection.hpp"

using namespace std;

LeptonVetoSelection::LeptonVetoSelection (){}
LeptonVetoSelection::~LeptonVetoSelection (){}

void LeptonVetoSelection::InitCutflow(Cutflow& cutflow){

  cutflow.AddStep("No veto leptons");

  initialized=true;
}

bool LeptonVetoSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "LeptonVetoSelection not initialized" << endl;

  // veto the event if there is any loose lepton
  if(input.selectedElectronsLoose.size()>0 || input.selectedMuonsLoose.size()>0 || input.selectedTaus.size()>0) {
    return false;
  }
  else{
    cutflow.EventSurvivedStep("No veto leptons",input.weights.at("Weight"));
    return true;    
  }

}