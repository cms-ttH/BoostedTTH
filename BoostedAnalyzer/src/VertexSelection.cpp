#include "BoostedTTH/BoostedAnalyzer/interface/VertexSelection.hpp"

using namespace std;

VertexSelection::VertexSelection (){}
VertexSelection::~VertexSelection (){}

void VertexSelection::Init(const edm::ParameterSet& iConfig, Cutflow& cutflow){

  cutflow.AddStep("First PV is good PV");

  initialized=true;
}

bool VertexSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "VertexSelection not initialized" << endl;

  if(input.primaryVertices.size() < 1) return false;
  if( !(input.primaryVertices[0].isFake()) &&
      (input.primaryVertices[0].ndof() >= 4.0) &&
      (abs(input.primaryVertices[0].z()) <= 24.0) &&
      (abs(input.primaryVertices[0].position().Rho()) <= 2.0 )) {

    cutflow.EventSurvivedStep("First PV is good PV");
    return true;    
  }
  else return false;

}
