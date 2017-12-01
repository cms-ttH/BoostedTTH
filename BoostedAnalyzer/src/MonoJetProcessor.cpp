#include "BoostedTTH/BoostedAnalyzer/interface/MonoJetProcessor.hpp"

using namespace std;

MonoJetProcessor::MonoJetProcessor(){}
MonoJetProcessor::~MonoJetProcessor(){}


void MonoJetProcessor::Init(const InputCollections& input,VariableContainer& vars){
 
  
  initialized=true;
}

void MonoJetProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;


}