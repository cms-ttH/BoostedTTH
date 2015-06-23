#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"

using namespace std;

// ------ Cutflow Object

Cutflow::Cutflow(){
  initialized=false;
}


Cutflow::~Cutflow(){
  cutflowfile.close();
}

void Cutflow::Init(const char* filename){
  cutflowfile.open(filename);
  AddStep("all");
}

void Cutflow::AddStep(string name){
  if(std::find(selectionStepNames.begin(), selectionStepNames.end(), name) != selectionStepNames.end()){
    std::cerr<< "Selection step " << name << " does already exist" << std::endl;
    return;
  }
  eventsAfterSelectionSteps.push_back(0);
  yieldsAfterSelectionSteps.push_back(0);
  selectionStepNames.push_back(name);
}

void Cutflow::Print(){
  for(size_t i=0; i<selectionStepNames.size();i++){
    cutflowfile << i << " : " << selectionStepNames[i] << " : " << eventsAfterSelectionSteps[i] << " : " << yieldsAfterSelectionSteps[i] <<endl;
  }
}


void Cutflow::EventSurvivedStep(string name, const InputCollections& input){
  auto it = find(selectionStepNames.begin(), selectionStepNames.end(), name);
  if(it != selectionStepNames.end()) {
    int step=it-selectionStepNames.begin();
    float w = input.weights.at("Weight");
    eventsAfterSelectionSteps.at(step)++;
    yieldsAfterSelectionSteps.at(step)+=w;
  }
  else{
    cerr<< "selection step " << name << " does not exist " << endl;
  }
   
}
