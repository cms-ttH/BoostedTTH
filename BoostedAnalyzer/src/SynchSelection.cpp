#include "BoostedTTH/BoostedAnalyzer/interface/SynchSelection.hpp"

using namespace std;

SynchSelection::SynchSelection (){}
SynchSelection::~SynchSelection (){}

void SynchSelection::Init(const edm::ParameterSet& iConfig, Cutflow& cutflow){
  vector<std::string> muonTriggers;
  muonTriggers.push_back("HLT_IsoMu24_eta2p1_IterTrk02_v1");
  vector<std::string> electronTriggers;
  electronTriggers.push_back("HLT_Ele27_eta2p1_WP85_Gsf_v1");

  cutflow.AddStep("vertex selection");
  cutflow.AddStep("single ele trigger");
  cutflow.AddStep("== 1 electron");
  cutflow.AddStep("== 0 muons");
  cutflow.AddStep(">= 4 jets");
  cutflow.AddStep(">= 2 b-tags");
  cutflow.AddStep(">= 1 top tagged jet");
  cutflow.AddStep(">= 1 Higgs jet");
  
  initialized=true;
}

bool SynchSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "SynchSelection not initialized" << endl;
  
  // For this selection, do object selections first
  // This is an exception, usually object selections should be done in BoostedAnalyzer.cc with the help of the miniAODhelper
  reco::Vertex vtx= input.selectedPVs[0];
  bool hasGoodVertex = !vtx.isFake() 
    && vtx.ndof() >= 4.0 
    && abs(vtx.z()) <= 24.0 
    && abs(vtx.position().Rho()) <= 2.0;

  //  std::vector<pat::Electron> selectedElectrons;
  // ...

  
  // now write the numbers that should be dumped
 
  int run=-999;
  int lumi=-999;
  int event=-999;
  float lep1_pt=-999;
  float lep1_eta=-999;
  float lep1_phi=-999;
  float jet1_pt=-999;
  float jet2_pt=-999;
  float jet3_pt=-999; 
  float jet4_pt=-999;
  float jet1_CSVv2=-999;
  float jet2_CSVv2=-999;
  float jet3_CSVv2=-999;
  float jet4_CSVv2=-999;
  int n_jets=-999;
  int n_btags=-999;
  int n_toptags=-999; 
  int n_higgstags=-999;
    

  // dump
  printf("%6d %8d %10d   %6.2f %+4.2f %+4.2f   %6.2f %6.2f %6.2f %6.2f   %+7.3f %+7.3f %+7.3f %+7.3f   %2d  %2d   %2d  %2d\n",
	 run, lumi, event,
	 lep1_pt, lep1_eta, lep1_phi,
	 jet1_pt, jet2_pt, jet3_pt, jet4_pt,
	 jet1_CSVv2, jet2_CSVv2, jet3_CSVv2, jet4_CSVv2,
	 n_jets, n_btags,
	 n_toptags, n_higgstags);


  // make event selection
  if(!hasGoodVertex) return false;
  else cutflow.EventSurvivedStep("vertex selection");
  if(false) return false;
  else cutflow.EventSurvivedStep("single ele trigger");
  if(false) return false;
  else cutflow.EventSurvivedStep("== 1 electron");
  if(false) return false;
  else cutflow.EventSurvivedStep("== 0 muons");
  if(false) return false;
  else cutflow.EventSurvivedStep(">= 4 jets");
  if(false) return false;
  else cutflow.EventSurvivedStep(">= 2 b-tags");
  if(false) return false;
  else cutflow.EventSurvivedStep(">= 1 top tagged jet");
  if(false) return false;
  else cutflow.EventSurvivedStep(">= 1 Higgs jet");
  
  return true;
  
}


