#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonVarProcessor.hpp"

using namespace std;

DiLeptonVarProcessor::DiLeptonVarProcessor(){}
DiLeptonVarProcessor::~DiLeptonVarProcessor(){}


void DiLeptonVarProcessor::Init(const InputCollections& input,VariableContainer& vars){

  vars.InitVar( "DiMuon_E");
  vars.InitVar( "DiMuon_M");
  vars.InitVar( "DiMuon_Pt");
  vars.InitVar( "DiMuon_Eta");
  vars.InitVar( "DiMuon_Phi");

  initialized=true;

}


void DiLeptonVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  if(input.selectedMuonsLoose.size()>=2){
    std::vector<math::XYZTLorentzVector> leptonVecs;
    
    for(std::vector<pat::Muon>::const_iterator itMu = input.selectedMuonsLoose.begin(); itMu != input.selectedMuonsLoose.end(); ++itMu){
      leptonVecs.push_back(itMu->p4());
    }
    std::sort(leptonVecs.begin(), leptonVecs.end(),BoostedUtils::FirstIsHarder);
    
    math::XYZTLorentzVector DiMuonVec=leptonVecs.at(0);
    DiMuonVec+=leptonVecs.at(1);

    vars.FillVar( "DiMuon_E",DiMuonVec.E() );
    vars.FillVar( "DiMuon_M",DiMuonVec.M() );
    vars.FillVar( "DiMuon_Pt",DiMuonVec.Pt() );
    vars.FillVar( "DiMuon_Eta",DiMuonVec.Eta() );
    vars.FillVar( "DiMuon_Phi",DiMuonVec.Phi() );
  }



}
