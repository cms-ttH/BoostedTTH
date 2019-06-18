#include "BoostedTTH/BoostedAnalyzer/interface/JABDTBaseProcessor.hpp"
using namespace std;

JABDTBaseProcessor::JABDTBaseProcessor()
{
}
JABDTBaseProcessor::~JABDTBaseProcessor(){

}

std::string JABDTBaseProcessor::loadVariables(const edm::ParameterSet& jaoptions, const char* keyword) const{
  std::string returnstring = "";
  TString helper;
  if (jaoptions.existsAs<std::string>(keyword, true)){
    helper = jaoptions.getParameter<std::string>(keyword);
    if(helper.EndsWith(".csv")) returnstring = std::string(getenv("CMSSW_BASE")) + "/src/" + helper.Data();
    else returnstring = helper.Data();
  }
  else{
    std::cerr << "ERROR: Could not load keyword '" << keyword << "'\n";
  }
  return returnstring;
}
std::string JABDTBaseProcessor::loadWeightPath(const edm::ParameterSet& jaoptions, const char* keyword) const{
  std::string weightpath = "";
  try{
        weightpath = std::string(getenv("CMSSW_BASE")) + "/src/" +jaoptions.getParameter<std::string>(keyword);
      }
  catch(const std::exception& e){
      std::cerr << "ERROR: variable '"<<keyword <<"' does not exist in ParameterSet 'JetAssignentOptions'\n";
      std::cerr << e.what() << std::endl;
  }
  return weightpath;
}

void JABDTBaseProcessor::Init(const InputCollections& input,VariableContainer& vars){
  if( pointerToEvenHypothesisCombinatorics != nullptr and pointerToOddHypothesisCombinatorics != nullptr )
  {
    std::vector<std::string> BDT_variables = pointerToEvenHypothesisCombinatorics->GetVariableNames();
    for(auto varname : BDT_variables)
    {
      std::cout << "booking variable " << varname << std::endl;
      vars.InitVar( varname.c_str() );
      initialized=true;
    }
  }
  else{
    std::cerr << "ERROR: Could not find hyptothesis combinatorics! ";
    std::cerr << "Will not save any results for this hypothesis: " << hypothesis << std::endl;
    initialized = false;
  }
}

void JABDTBaseProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) 
  {
    cerr << "tree processor not initialized" << endl;
    return;
  }
  if(input.selectedMuons.size()+input.selectedElectrons.size()!=1) return;

  pointerToEvenHypothesisCombinatorics->SetBtagWP( CSVHelper::GetWP(input.era, CSVHelper::CSVwp::Medium, "DeepJet"));
  pointerToOddHypothesisCombinatorics->SetBtagWP( CSVHelper::GetWP(input.era, CSVHelper::CSVwp::Medium, "DeepJet"));

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
  //do cross evaluation
  std::map<std::string, float> bestestimate;
  long evt_id = input.eventInfo.evt;
  if(evt_id % 2 == 0){
   bestestimate= pointerToOddHypothesisCombinatorics->GetBestPermutation(lepvecs, loose_jetvecs, loose_jetcsvs, metP4);
  }
  else{
    bestestimate= pointerToEvenHypothesisCombinatorics->GetBestPermutation(lepvecs, loose_jetvecs, loose_jetcsvs, metP4);
  }
  for(auto it=bestestimate.begin(); it!=bestestimate.end(); it++){
    vars.FillVar(it->first,it->second);
  }
  
}

