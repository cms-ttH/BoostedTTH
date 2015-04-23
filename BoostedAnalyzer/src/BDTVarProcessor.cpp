#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
using namespace std;

BDTVarProcessor::BDTVarProcessor():bdtohio(BDTOhio_v1(BoostedUtils::GetAnalyzerPath()+"/data/bdtweights/ohio_weights_run2_v1/")){}
BDTVarProcessor::~BDTVarProcessor(){}


void BDTVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
  vars.InitVar("BDTOhio_v1_output");
  map<string,float> bdtinputs=bdtohio.GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs.begin(); it!=bdtinputs.end(); it++){
    vars.InitVar("BDTOhio_v1_input_"+it->first);
  }
  initialized=true;
}

void BDTVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  float bdtoutput=bdtohio.Evaluate(input.selectedMuons,input.selectedElectrons, input.selectedJets, input.selectedJetsLoose, input.pfMets[0]);
  vars.FillVar("BDTOhio_v1_output",bdtoutput);
  map<string,float> bdtinputs=bdtohio.GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs.begin(); it!=bdtinputs.end(); it++){
    vars.FillVar("BDTOhio_v1_input_"+it->first,it->second);
  }


}
