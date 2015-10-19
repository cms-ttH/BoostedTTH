#include "BoostedTTH/BoostedAnalyzer/interface/TriggerVarProcessor.hpp"

using namespace std;

TriggerVarProcessor::TriggerVarProcessor(const std::vector<std::string> relevantTriggers_):relevantTriggers(relevantTriggers_){}
TriggerVarProcessor::~TriggerVarProcessor(){}


void TriggerVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
    for (auto it=relevantTriggers.begin(); it!=relevantTriggers.end(); ++it){
	vars.InitVar("Triggered_"+replaceAsterix(*it),"I");  
    }

    initialized=true;
}

void TriggerVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  for (auto it=relevantTriggers.begin(); it!=relevantTriggers.end(); ++it){
      vars.FillVar("Triggered_"+replaceAsterix(*it),int(input.triggerInfo.IsTriggered(*it)));  
  }
}

std::string TriggerVarProcessor::replaceAsterix(std::string triggername){
    int asterix = triggername.find("*");
    if(triggername.find("*")==std::string::npos){	    
	return triggername;
    }
    else{
	return triggername.replace(asterix,1,"X");
    }
}
