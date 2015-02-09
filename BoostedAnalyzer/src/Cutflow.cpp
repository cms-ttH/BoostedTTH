#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"

using namespace std;

// ------ Cutflow Object

Cutflow::Cutflow(){
}


Cutflow::~Cutflow(){
  cutflowfile.close();
}


void Cutflow::AddStep(string name){
  eventsAfterSelectionSteps.push_back(0);
  selectionStepNames.push_back(name);
}

void Cutflow::Init(const char* filename){
  cutflowfile.open(filename);
}


void Cutflow::Print(){
  for(size_t i=0; i<selectionStepNames.size();i++){
    cutflowfile << i << " : " << selectionStepNames[i] << " : " << eventsAfterSelectionSteps[i] << endl;
  }
}


void Cutflow::EventSurvivedStep(string name){
  auto it = find(selectionStepNames.begin(), selectionStepNames.end(), name);
  if(it != selectionStepNames.end()) {
    int step=it-selectionStepNames.begin();
    eventsAfterSelectionSteps.at(step)++;
  }
  else{
    cerr<< "selection step " << name << " does not exist " << endl;
  }
   
}


