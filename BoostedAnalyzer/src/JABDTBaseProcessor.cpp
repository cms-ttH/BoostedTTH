#include "BoostedTTH/BoostedAnalyzer/interface/JABDTBaseProcessor.hpp"
using namespace std;

JABDTBaseProcessor::JABDTBaseProcessor()
{
}
JABDTBaseProcessor::~JABDTBaseProcessor(){

}

void JABDTBaseProcessor::Init(const InputCollections& input,VariableContainer& vars){
  if( pointerToHypothesisCombinatorics != nullptr )
  {
    std::vector<std::string> BDT_variables = pointerToHypothesisCombinatorics->GetVariableNames();
    for(auto varname : BDT_variables)
    {
      vars.InitVar( (hypothesis + "_" + varname).c_str() );
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

  pointerToHypothesisCombinatorics->SetBtagWP(CSVHelper::GetWP(input.era, CSVHelper::CSVwp::Medium, "DeepJet"));

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

  std::map<std::string, float> bestestimate = pointerToHypothesisCombinatorics->GetBestPermutation(lepvecs, jetvecs, jetcsvs, metP4);
  
  for(auto it=bestestimate.begin(); it!=bestestimate.end(); it++){
    vars.FillVar(hypothesis + "_" +it->first,it->second);
  }
  
}
