#include "BoostedTTH/BoostedAnalyzer/interface/WeightProcessor.hpp"

using namespace std;

WeightProcessor::WeightProcessor(){}
WeightProcessor::~WeightProcessor(){}


void WeightProcessor::Init(const InputCollections& input,VariableContainer& vars){
    
  for (auto it=input.weights.begin(); it!=input.weights.end(); ++it){
    vars.InitVar(it->first);  
  }

  initialized=true;
}

void WeightProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  for (auto it=input.weights.begin(); it!=input.weights.end(); ++it){
    vars.FillVar( it->first,it->second);  
  }
}
