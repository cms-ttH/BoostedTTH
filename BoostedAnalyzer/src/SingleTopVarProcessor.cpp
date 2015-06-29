#include "BoostedTTH/BoostedAnalyzer/interface/SingleTopVarProcessor.hpp"

using namespace std;

SingleTopVarProcessor::SingleTopVarProcessor(){}
SingleTopVarProcessor::~SingleTopVarProcessor(){}


void SingleTopVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
  
  vars.InitVar( "Evt_LooseJet_MaxEta");

  initialized=true;
}

void SingleTopVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  float maxeta=0;
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJetsLoose.begin() ; itJet != input.selectedJetsLoose.end(); ++itJet){
    maxeta=max(fabs(itJet->eta()),maxeta);
  }
  vars.FillVar( "Evt_LooseJet_MaxEta",maxeta);
}
