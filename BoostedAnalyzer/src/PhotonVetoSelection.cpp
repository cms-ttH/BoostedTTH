#include "BoostedTTH/BoostedAnalyzer/interface/PhotonVetoSelection.hpp"

using namespace std;

PhotonVetoSelection::PhotonVetoSelection (){}
PhotonVetoSelection::~PhotonVetoSelection (){}

void PhotonVetoSelection::InitCutflow(Cutflow& cutflow){

  cutflow.AddStep("No veto photons");

  initialized=true;
}

bool PhotonVetoSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "PhotonVetoSelection not initialized" << endl;

  // veto the event if a loose photon is found
  if(input.selectedPhotonsLoose.size()>0) {
    return false;
  }
  else{
    cutflow.EventSurvivedStep("No veto photons",input.weights.at("Weight"));
    return true;    
  }

}