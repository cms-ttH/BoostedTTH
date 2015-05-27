#include "BoostedTTH/BoostedAnalyzer/interface/HbbSelection.hpp"

using namespace std;

HbbSelection::HbbSelection (){}
HbbSelection::~HbbSelection (){}

void HbbSelection::InitCutflow(Cutflow& cutflow){

  cutflow.AddStep("Higgs to bb");

  initialized=true;
}

bool HbbSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "HbbSelection not initialized" << endl;
  std::vector<reco::GenParticle> decayProds= input.genTopEvt.GetHiggsDecayProducts();
  if(decayProds.size()==0) {
    cutflow.EventSurvivedStep("Higgs to bb",input);
    return true; // do nothing if there is no Higgs
  }
  for(auto p = decayProds.begin(); p != decayProds.end(); p++){
    if(abs(p->pdgId())==5) {
      cutflow.EventSurvivedStep("Higgs to bb",input);
      return true;
    }
  }

  return false;   

}
