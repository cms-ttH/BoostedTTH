#include "BoostedTTH/BoostedAnalyzer/interface/BoostedSelection.hpp"

using namespace std;

BoostedSelection::BoostedSelection (int minTopTags_,int minHiggsTags_):toptagger(TopTag::Likelihood,TopTag::CSV,"toplikelihoodtaggerhistos.root"),minTopTags(minTopTags_),minHiggsTags(minHiggsTags_){}
BoostedSelection::~BoostedSelection (){}

void BoostedSelection::InitCutflow(Cutflow& cutflow){

  cutflow.AddStep(">= "+to_string(minTopTags)+" top-tag");
  cutflow.AddStep(">= "+to_string(minHiggsTags)+" non-overlapping jet with higgs-tag");

    
  initialized=true;
}

bool BoostedSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "BoostedSelection not initialized" << endl;
    
  int n_toptags=0;  
  int n_higgstags=0;  

  vector<boosted::HTTTopJet> syncTopJets;
  for(auto topjet = input.selectedHTTTopJets.begin() ; topjet != input.selectedHTTTopJets.end(); topjet++ ){
    // pt and eta requirements on top jet
    if( !(topjet->fatjet.pt() > 200. && abs(topjet->fatjet.eta()) < 2.) ) continue;
    std::vector<pat::Jet> subjets;
    subjets.push_back(topjet->W1);
    subjets.push_back(topjet->W2);
    subjets.push_back(topjet->nonW);
    bool subjetcuts=true;
    for(auto j = subjets.begin(); j!=subjets.end();j++){
      if(j->pt()<20 || fabs(j->eta())>2.4) {
	subjetcuts=false;
	break;
      }
    }
    if(!subjetcuts) continue;
    if(toptagger.GetTopTaggerOutput(*topjet)>-1){
      n_toptags++;
      syncTopJets.push_back(*topjet);
    }
  }

  if(n_toptags>=minTopTags){
    cutflow.EventSurvivedStep(">= "+to_string(minTopTags)+" top-tag",input.weights.at("Weight"));   	
  }
  else{
    return false;
  }


  for( auto higgsJet = input.selectedSubFilterJets.begin() ; higgsJet != input.selectedSubFilterJets.end(); ++higgsJet ){
    // pt and eta requirements on higgs jet
    if( !(higgsJet->fatjet.pt() > 200. && abs(higgsJet->fatjet.eta()) < 2) ) continue;
    bool overlapping=false;
    for(auto tj=syncTopJets.begin(); tj!=syncTopJets.end(); tj++){
      if(BoostedUtils::DeltaR(tj->fatjet,higgsJet->fatjet)<1.5){
	overlapping=true;
	break;
      }
    }
    if(overlapping) continue;
    std::vector<pat::Jet> filterjets = higgsJet->filterjets;
    int subjettags=0;
    for(auto j=filterjets.begin(); j!=filterjets.end(); j++ ){
      if(j->pt()<20 || fabs(j->eta())>2.4) continue;
      if(BoostedUtils::PassesCSV(*j)){
	subjettags++;
      }	
    }
    if(subjettags>=2) n_higgstags++;
  }
  if(n_higgstags>=minHiggsTags){
    cutflow.EventSurvivedStep(">= "+to_string(minHiggsTags)+" non-overlapping jet with higgs-tag",input.weights.at("Weight"));
  }
  else{
    return false;
  }
  
  return true;   
  
}
