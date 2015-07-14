#include "BoostedTTH/BoostedAnalyzer/interface/TriggerVarProcessor.hpp"

using namespace std;

TriggerVarProcessor::TriggerVarProcessor(){}
TriggerVarProcessor::~TriggerVarProcessor(){}


void TriggerVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
    map<string,bool> triggers=input.triggerInfo.GetTriggers();
    for (auto it=triggers.begin(); it!=triggers.end(); ++it){
	vars.InitVar("Triggered_"+it->first,"I");  
    }

  initialized=true;
}

void TriggerVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  map<string,bool> triggers=input.triggerInfo.GetTriggers();
  for (auto it=triggers.begin(); it!=triggers.end(); ++it){
      vars.FillVar("Triggered_"+it->first,int(it->second));  
  }
}
