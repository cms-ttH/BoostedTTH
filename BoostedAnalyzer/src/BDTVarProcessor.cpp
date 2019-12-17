#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
using namespace std;

BDTVarProcessor::BDTVarProcessor():
//     bdtohio2(BDTOhio_v2(BoostedUtils::GetAnalyzerPath()+"/data/bdtweights/ohio_weights_run2_v2/")),
//     bdt3(BDT_v3(BoostedUtils::GetAnalyzerPath()+"/data/bdtweights/weights_v3/")),
    commonBDT5(new BDTClassifier(string(getenv("CMSSW_BASE"))+"/src/TTH/CommonClassifier/data/lj_BDT_DeepCSV_Summer18_v1/")),
    recoLikelihoodVariables(new RecoLikelihoodVariables()) {needToDeleteBDTClassifier=true;}
BDTVarProcessor::~BDTVarProcessor(){
  if(needToDeleteBDTClassifier){
    delete commonBDT5;
  }
  delete recoLikelihoodVariables;
}

BDTVarProcessor::BDTVarProcessor(BDTClassifier* bdt_):commonBDT5(bdt_), recoLikelihoodVariables(new RecoLikelihoodVariables()){needToDeleteBDTClassifier=false;}



void BDTVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
//   vars.InitVar("BDTOhio_v2_output");
//   vars.InitVar("BDT_v3_output");
  vars.InitVar("BDT_common5_output");

//   map<string,float> bdtinputs2=bdtohio2.GetVariablesOfLastEvaluation();
//   for(auto it=bdtinputs2.begin(); it!=bdtinputs2.end(); it++){
//     vars.InitVar("BDTOhio_v2_input_"+it->first);
//   }
// 
//   map<string,float> bdtinputs3=bdt3.GetVariablesOfLastEvaluation();
//   for(auto it=bdtinputs3.begin(); it!=bdtinputs3.end(); it++){
//     vars.InitVar("BDT_v3_input_"+it->first);
//   }

  map<string,float> bdtinputs_common5=commonBDT5->GetVariablesOfLastEvaluation();
  for(auto it=bdtinputs_common5.begin(); it!=bdtinputs_common5.end(); it++){
    vars.InitVar("BDT_common5_input_"+it->first);
  }

//   map<TString,double> DNN_inputs = recoLikelihoodVariables->GetRecoLikelihoodVariables();
//   for(auto it=DNN_inputs.begin(); it!=DNN_inputs.end(); it++){
//     vars.InitVar("DNN_input_"+it->first);
//   }

  initialized=true;
}

void BDTVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  if(input.selectedMuons.size()+input.selectedElectrons.size()!=1) return;
//   float bdtoutput2=bdtohio2.Evaluate(input.selectedMuons,input.selectedElectrons, input.selectedJets, input.selectedJetsLoose, input.correctedMET);
//   vars.FillVar("BDTOhio_v2_output",bdtoutput2);
//   if(bdtohio2.GetCategory(input.selectedJets)!="none"){
//     map<string,float> bdtinputs2=bdtohio2.GetVariablesOfLastEvaluation();
//     for(auto it=bdtinputs2.begin(); it!=bdtinputs2.end(); it++){
//       vars.FillVar("BDTOhio_v2_input_"+it->first,it->second);
//     }
//   }
// 
//   float bdtoutput3=bdt3.Evaluate(input.selectedMuons,input.selectedElectrons, input.selectedJets, input.selectedJetsLoose, input.correctedMET);
//   vars.FillVar("BDT_v3_output",bdtoutput3);
//   if(bdt3.GetCategory(input.selectedJets)!="none"){
//     map<string,float> bdtinputs3=bdt3.GetVariablesOfLastEvaluation();
//     for(auto it=bdtinputs3.begin(); it!=bdtinputs3.end(); it++){
//       vars.FillVar("BDT_v3_input_"+it->first,it->second);
//     }
//   }
 
  vector<TLorentzVector> lepvecs=BoostedUtils::GetTLorentzVectors(BoostedUtils::GetLepVecs(input.selectedElectrons,input.selectedMuons));
  vector<TLorentzVector> jetvecs=BoostedUtils::GetTLorentzVectors(BoostedUtils::GetJetVecs(input.selectedJets));
  vector<TLorentzVector> loose_jetvecs=BoostedUtils::GetTLorentzVectors(BoostedUtils::GetJetVecs(input.selectedJetsLoose));
  TLorentzVector metP4=BoostedUtils::GetTLorentzVector(input.correctedMET.corP4(pat::MET::Type1XY));
  vector<double> jetcsvs;
  vector<double> loose_jetcsvs;
  for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++){
      jetcsvs.push_back(CSVHelper::GetJetCSV(*j,"DeepJet"));
  }
  for(auto j=input.selectedJetsLoose.begin(); j!=input.selectedJetsLoose.end(); j++){
      loose_jetcsvs.push_back(CSVHelper::GetJetCSV(*j,"DeepJet"));
  }

  float bdtoutput_common5=commonBDT5->GetBDTOutput(lepvecs, jetvecs, jetcsvs,metP4);
  vars.FillVar("BDT_common5_output",bdtoutput_common5);
  if(commonBDT5->GetCategoryOfLastEvaluation()!="none"){
      map<string,float> bdtinputs_common5=commonBDT5->GetVariablesOfLastEvaluation();
      for(auto it=bdtinputs_common5.begin(); it!=bdtinputs_common5.end(); it++){
	  vars.FillVar("BDT_common5_input_"+it->first,it->second);
      }
  }

//   recoLikelihoodVariables->CalculateRecoLikelihoodVariables(lepvecs, jetvecs, jetcsvs, metP4);
//   map<TString,double> DNN_inputs = recoLikelihoodVariables->GetRecoLikelihoodVariables();
//   for(auto it=DNN_inputs.begin(); it!=DNN_inputs.end(); it++){
//     vars.FillVar("DNN_input_"+it->first, it->second);
//   }
}
