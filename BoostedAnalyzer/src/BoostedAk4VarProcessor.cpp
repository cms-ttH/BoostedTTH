#include "BoostedTTH/BoostedAnalyzer/interface/BoostedAk4VarProcessor.hpp"

using namespace std;

BoostedAk4VarProcessor::BoostedAk4VarProcessor(){}
BoostedAk4VarProcessor::~BoostedAk4VarProcessor(){}


void BoostedAk4VarProcessor::Init(const InputCollections& input,VariableContainer& vars){

  vars.InitVars( "BoostedAk4Cluster_E","N_BoostedAk4Cluster" );
  vars.InitVars( "BoostedAk4Cluster_M","N_BoostedAk4Cluster" );
  vars.InitVars( "BoostedAk4Cluster_Pt","N_BoostedAk4Cluster" );
  vars.InitVars( "BoostedAk4Cluster_Phi","N_BoostedAk4Cluster" );
  vars.InitVars( "BoostedAk4Cluster_Eta","N_BoostedAk4Cluster" );

  vars.InitVars( "BoostedAk4Cluster_Dr_Ak4Cluster_BoostedJet1","N_BoostedAk4Cluster" );
  vars.InitVars( "BoostedAk4Cluster_Dr_Ak4Cluster_BoostedJet2","N_BoostedAk4Cluster" );
  vars.InitVars( "BoostedAk4Cluster_Dr_Ak4Cluster_BoostedJet3","N_BoostedAk4Cluster" );

  initialized=true;
}

void BoostedAk4VarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  for(int unsigned i = 0; i< input.selectedAk4Cluster.size(); ++i){
    vars.FillVars( "BoostedAk4Cluster_E",i,input.selectedAk4Cluster[i].fatjet.E() );
    vars.FillVars( "BoostedAk4Cluster_Pt",i,input.selectedAk4Cluster[i].fatjet.Pt() );
    vars.FillVars( "BoostedAk4Cluster_M",i,input.selectedAk4Cluster[i].fatjet.M() );
    vars.FillVars( "BoostedAk4Cluster_Eta",i,input.selectedAk4Cluster[i].fatjet.Eta() );
    vars.FillVars( "BoostedAk4Cluster_Phi",i,input.selectedAk4Cluster[i].fatjet.Phi() );

    if(input.selectedBoostedJets.size()>0)
      vars.FillVars( "BoostedAk4Cluster_Dr_Ak4Cluster_BoostedJet1",i, BoostedUtils::DeltaR(input.selectedAk4Cluster[i].fatjet, input.selectedBoostedJets[0].fatjet.p4()));
    if(input.selectedBoostedJets.size()>1)
      vars.FillVars( "BoostedAk4Cluster_Dr_Ak4Cluster_BoostedJet2",i, BoostedUtils::DeltaR(input.selectedAk4Cluster[i].fatjet, input.selectedBoostedJets[1].fatjet.p4()));
    if(input.selectedBoostedJets.size()>2)
      vars.FillVars( "BoostedAk4Cluster_Dr_Ak4Cluster_BoostedJet3",i, BoostedUtils::DeltaR(input.selectedAk4Cluster[i].fatjet, input.selectedBoostedJets[2].fatjet.p4()));
  }
}
