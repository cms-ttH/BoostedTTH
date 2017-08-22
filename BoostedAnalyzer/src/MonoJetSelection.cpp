#include "BoostedTTH/BoostedAnalyzer/interface/MonoJetSelection.hpp"

using namespace std;

MonoJetSelection::MonoJetSelection (const edm::ParameterSet& iConfig):MonoJetSelection(iConfig.getParameter<double>("MonoJet_Pt"),iConfig.getParameter<double>("MonoJet_Eta"),iConfig.getParameter<double>("MonoJet_Chf"),iConfig.getParameter<double>("MonoJet_Nhf")){}
MonoJetSelection::MonoJetSelection (double pt_min_,double eta_max_,double chf_min_,double nhf_max_):pt_min(pt_min_),eta_max(eta_max_),charged_hadron_fraction_min(chf_min_),neutral_hadron_fraction_max(nhf_max_){}
MonoJetSelection::~MonoJetSelection (){}

void MonoJetSelection::InitCutflow(Cutflow& cutflow){

  pt_str = std::to_string(pt_min); 
  eta_str = std::to_string(eta_max); 
  cutflow.AddStep("At least one jet with pt greater than "+pt_str+"and eta smaller than "+eta_str);

  initialized=true;
}

bool MonoJetSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "MonoJetSelection not initialized" << endl;
  uint njet=0;
  for(auto& jet : input.selectedJets) {
      if(jet.pt()>pt_min && abs(jet.eta())<eta_max && charged_hadron_fraction_min<jet.chargedHadronEnergyFraction() && neutral_hadron_fraction_max>jet.neutralHadronEnergyFraction()) {
          njet+=1;
      }
  }
  if(njet<1) {
    return false;
  }
  else{
    cutflow.EventSurvivedStep("At least one jet with pt greater than "+pt_str+"and eta smaller than "+eta_str,input.weights.at("Weight"));
    return true;    
  }

}