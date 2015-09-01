#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
using namespace std;

BDTVarProcessor::BDTVarProcessor():
    bdtohio2(BDTOhio_v2(BoostedUtils::GetAnalyzerPath()+"/data/bdtweights/ohio_weights_run2_v2/")),
    bdt3(BDT_v3(BoostedUtils::GetAnalyzerPath()+"/data/bdtweights/weights_v3/"))
{}
BDTVarProcessor::~BDTVarProcessor(){}


void BDTVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
  vars.InitVar("BDTOhio_v2_output");
  vars.InitVar("BDT_v3_output");

  map<string,float> bdtinputs2=bdtohio2.GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs2.begin(); it!=bdtinputs2.end(); it++){
    vars.InitVar("BDTOhio_v2_input_"+it->first);
  }

  map<string,float> bdtinputs3=bdt3.GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs3.begin(); it!=bdtinputs3.end(); it++){
    vars.InitVar("BDT_v3_input_"+it->first);
  }

  initialized=true;
}

void BDTVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  float bdtoutput2=bdtohio2.Evaluate(input.selectedMuons,input.selectedElectrons, input.selectedJets, input.selectedJetsLoose, input.pfMET);
  vars.FillVar("BDTOhio_v2_output",bdtoutput2);
  if(bdtohio2.GetCategory(input.selectedJets)!="none"){
    map<string,float> bdtinputs2=bdtohio2.GetVariablesOfLastEvaluation();
    for(auto it=bdtinputs2.begin(); it!=bdtinputs2.end(); it++){
      vars.FillVar("BDTOhio_v2_input_"+it->first,it->second);
    }
  }

  float bdtoutput3=bdt3.Evaluate(input.selectedMuons,input.selectedElectrons, input.selectedJets, input.selectedJetsLoose, input.pfMET);
  vars.FillVar("BDT_v3_output",bdtoutput3);
  if(bdt3.GetCategory(input.selectedJets)!="none"){
    map<string,float> bdtinputs3=bdt3.GetVariablesOfLastEvaluation();
    for(auto it=bdtinputs3.begin(); it!=bdtinputs3.end(); it++){
      vars.FillVar("BDT_v3_input_"+it->first,it->second);
    }
  }

}
