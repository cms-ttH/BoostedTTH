#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"
using namespace std;

JetTagSelection::JetTagSelection(std::vector<int> minjets_,std::vector<int> mintags_):JetTagSelection(minjets_,std::vector<int>(),mintags_,std::vector<int>()) {  
}
JetTagSelection::JetTagSelection(int minjets_,int mintags_):JetTagSelection(std::vector<int>(1,minjets_),std::vector<int>(1,mintags_)) {  
}


JetTagSelection::JetTagSelection(std::vector<int> minjets_,std::vector<int> maxjets_, std::vector<int> mintags_, std::vector<int> maxtags_):minJets(minjets_), maxJets(maxjets_), minTags(mintags_), maxTags(maxtags_){

  selSize = max(max(minJets.size(),maxJets.size()),max(minTags.size(),maxTags.size()));
  for(size_t iSel=0;iSel<selSize;++iSel){
    if(iSel!=0) selName+=" or ";
    if(iSel<minJets.size() && minJets[iSel] >= 0){
      selName += ">=";
      selName += std::to_string(minJets[iSel]);
      selName += " jets ";
    }
    if(iSel<maxJets.size() && maxJets[iSel] >= 0){
      selName += "<=";
      selName += std::to_string(maxJets[iSel]);
      selName += " jets ";
    }
    if(iSel<minTags.size() && minTags[iSel] >= 0){
      selName += ">=";
      selName += std::to_string(minTags[iSel]);
      selName += " tags";
    }
    if(iSel<maxTags.size() && maxTags[iSel] >= 0){
      selName += "<=";
      selName += std::to_string(maxTags[iSel]);
      selName += " tags";
    }
  }

}

JetTagSelection::JetTagSelection(const edm::ParameterSet& iConfig):JetTagSelection(iConfig.getParameter< std::vector<int> >("minJets"),
										   iConfig.getParameter< std::vector<int> >("maxJets"),
										   iConfig.getParameter< std::vector<int> >("minTags"),
										   iConfig.getParameter< std::vector<int> >("maxTags")){
}


JetTagSelection::~JetTagSelection (){}


void JetTagSelection::InitCutflow(Cutflow& cutflow){
  cutflow.AddStep(selName.c_str());

  initialized=true;
}

bool JetTagSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "JetTagSelection not initialized" << endl;

  int njets = input.selectedJetsLoose.size();
  int ntags = 0;
  for(size_t i=0; i<input.selectedJets.size();i++){
    if(CSVHelper::PassesCSV(input.selectedJets.at(i), "DeepJet", CSVHelper::CSVwp::Medium, input.era)){
      ntags++;
    }
  }

  for(size_t iSel=0;iSel<selSize;++iSel){
    bool selected = true;
    
    if(iSel < minJets.size() && minJets[iSel] >= 0  && njets < minJets[iSel]) selected = false;
    if(iSel < maxJets.size() && maxJets[iSel] >= 0  && njets > maxJets[iSel]) selected = false;
    if(iSel < minTags.size() && minTags[iSel] >= 0  && ntags < minTags[iSel]) selected = false;
    if(iSel < maxTags.size() && maxTags[iSel] >= 0  && ntags > maxTags[iSel]) selected = false;
    
    if(selected) break;
    
    if(iSel == selSize-1) return false;
  } 
  cutflow.EventSurvivedStep(selName.c_str(),input.weights.at("Weight"));

  return true;
}


