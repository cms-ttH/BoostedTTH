#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
using namespace std;

BDTVarProcessor::BDTVarProcessor():bdtohio1(BDTOhio_v1(BoostedUtils::GetAnalyzerPath()+"/data/bdtweights/ohio_weights_run2_v1/")),bdtohio2(BDTOhio_v2(BoostedUtils::GetAnalyzerPath()+"/data/bdtweights/ohio_weights_run2_v2/")){}
BDTVarProcessor::~BDTVarProcessor(){}


void BDTVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
  vars.InitVar("BDTOhio_v1_output");
  vars.InitVar("BDTOhio_v2_output");

  map<string,float> bdtinputs1=bdtohio1.GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs1.begin(); it!=bdtinputs1.end(); it++){
    vars.InitVar("BDTOhio_v1_input_"+it->first);
  }

  map<string,float> bdtinputs2=bdtohio2.GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs2.begin(); it!=bdtinputs2.end(); it++){
    vars.InitVar("BDTOhio_v2_input_"+it->first);
  }

  initialized=true;
}

void BDTVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  float bdtoutput1=bdtohio1.Evaluate(input.selectedMuons,input.selectedElectrons, input.selectedJets, input.selectedJetsLoose, input.pfMET);
  vars.FillVar("BDTOhio_v1_output",bdtoutput1);
  map<string,float> bdtinputs1=bdtohio1.GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs1.begin(); it!=bdtinputs1.end(); it++){
    vars.FillVar("BDTOhio_v1_input_"+it->first,it->second);
  }

  float bdtoutput2=bdtohio2.Evaluate(input.selectedMuons,input.selectedElectrons, input.selectedJets, input.selectedJetsLoose, input.pfMET);
  vars.FillVar("BDTOhio_v2_output",bdtoutput2);
  map<string,float> bdtinputs2=bdtohio2.GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs2.begin(); it!=bdtinputs2.end(); it++){
    vars.FillVar("BDTOhio_v2_input_"+it->first,it->second);
  }

}
