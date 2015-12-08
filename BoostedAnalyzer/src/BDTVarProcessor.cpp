#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
using namespace std;

BDTVarProcessor::BDTVarProcessor():
    bdtohio2(BDTOhio_v2(BoostedUtils::GetAnalyzerPath()+"/data/bdtweights/ohio_weights_run2_v2/")),
    bdt3(BDT_v3(BoostedUtils::GetAnalyzerPath()+"/data/bdtweights/weights_v3/")),
    bdt4(LJ_BDT_v4(string(getenv("CMSSW_BASE"))+"/src/MiniAOD/MiniAODHelper/data/bdtweights/V4weights"))
{}
BDTVarProcessor::~BDTVarProcessor(){}


void BDTVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
  vars.InitVar("BDTOhio_v2_output");
  vars.InitVar("BDT_v3_output");
  vars.InitVar("BDT_v4_output");
  vars.InitVar("BDT_common");

  map<string,float> bdtinputs2=bdtohio2.GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs2.begin(); it!=bdtinputs2.end(); it++){
    vars.InitVar("BDTOhio_v2_input_"+it->first);
  }

  map<string,float> bdtinputs3=bdt3.GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs3.begin(); it!=bdtinputs3.end(); it++){
    vars.InitVar("BDT_v3_input_"+it->first);
  }

  map<string,float> bdtinputs4=bdt4.GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs4.begin(); it!=bdtinputs4.end(); it++){
    vars.InitVar("BDT_v4_input_"+it->first);
  }

  map<string,float> bdtinputs_common=bdt4.GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs_common.begin(); it!=bdtinputs_common.end(); it++){
    vars.InitVar("BDT_common_"+it->first);
  }

  initialized=true;
}

void BDTVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  if(input.selectedMuons.size()+input.selectedElectrons.size()!=1) return;
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

  float bdtoutput4=bdt4.Evaluate(input.selectedMuons,input.selectedElectrons, input.selectedJets, input.selectedJetsLoose, input.pfMET);
  vars.FillVar("BDT_v4_output",bdtoutput4);
  if(bdt4.GetCategory(input.selectedJets)!="none"){
    map<string,float> bdtinputs4=bdt4.GetVariablesOfLastEvaluation();
    for(auto it=bdtinputs4.begin(); it!=bdtinputs4.end(); it++){
      vars.FillVar("BDT_v4_input_"+it->first,it->second);
    }
  }
  
  vector<TLorentzVector> lepvecs=BoostedUtils::GetTLorentzVectors(BoostedUtils::GetLepVecs(input.selectedElectrons,input.selectedMuons));
  vector<TLorentzVector> jetvecs=BoostedUtils::GetTLorentzVectors(BoostedUtils::GetJetVecs(input.selectedJets));
  vector<TLorentzVector> loose_jetvecs=BoostedUtils::GetTLorentzVectors(BoostedUtils::GetJetVecs(input.selectedJetsLoose));
  TLorentzVector metP4=BoostedUtils::GetTLorentzVector(input.pfMET.p4());
  vector<double> jetcsvs;
  vector<double> loose_jetcsvs;
  for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++){
      jetcsvs.push_back(BoostedUtils::GetJetCSV(*j));
  }
  for(auto j=input.selectedJetsLoose.begin(); j!=input.selectedJetsLoose.end(); j++){
      loose_jetcsvs.push_back(BoostedUtils::GetJetCSV(*j));
  }

  float bdtoutput_common=commonBDT.GetBDTOutput(lepvecs, jetvecs, jetcsvs,loose_jetvecs,loose_jetcsvs,metP4);
  vars.FillVar("BDT_v_common_output",bdtoutput_common);
  if(commonBDT.GetCategoryOfLastEvaluation()!="none"){
      map<string,float> bdtinputs_common=commonBDT.GetVariablesOfLastEvaluation();
      for(auto it=bdtinputs_common.begin(); it!=bdtinputs_common.end(); it++){
	  vars.FillVar("BDT_v_common_input_"+it->first,it->second);
      }
  }


}
