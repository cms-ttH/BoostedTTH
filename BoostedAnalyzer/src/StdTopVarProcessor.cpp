#include "BoostedTTH/BoostedAnalyzer/interface/StdTopVarProcessor.hpp"

using namespace std;

StdTopVarProcessor::StdTopVarProcessor(){}
StdTopVarProcessor::~StdTopVarProcessor(){}


void StdTopVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
 
  vars.InitVar( "HadTop_Pt","F" );
  vars.InitVar( "HadTop_E","F" );
  vars.InitVar( "HadTop_Eta","F" );
  vars.InitVar( "HadTop_Phi","F" );
  vars.InitVar( "HadTop_M","F" );

  vars.InitVar( "HadTop_B_Pt","F" );
  vars.InitVar( "HadTop_B_E","F" );
  vars.InitVar( "HadTop_B_Eta","F" );
  vars.InitVar( "HadTop_B_Phi","F" );
  vars.InitVar( "HadTop_B_M","F" );
//   vars.InitVar( "HadTop_B_CSV","F" );
//   vars.InitVar( "HadTop_B_Flav","F" );

  vars.InitVar( "HadTop_W_Pt","F" );
  vars.InitVar( "HadTop_W_E","F" );
  vars.InitVar( "HadTop_W_Eta","F" );
  vars.InitVar( "HadTop_W_Phi","F" );
  vars.InitVar( "HadTop_W_M","F" );

  vars.InitVar( "HadTop_W1_Pt","F" );
  vars.InitVar( "HadTop_W1_E","F" );
  vars.InitVar( "HadTop_W1_Eta","F" );
  vars.InitVar( "HadTop_W1_Phi","F" );
  vars.InitVar( "HadTop_W1_M","F" );

  vars.InitVar( "HadTop_W2_Pt","F" );
  vars.InitVar( "HadTop_W2_E","F" );
  vars.InitVar( "HadTop_W2_Eta","F" );
  vars.InitVar( "HadTop_W2_Phi","F" );
  vars.InitVar( "HadTop_W2_M","F" );

  vars.InitVar( "LepTop_Pt","F" );
  vars.InitVar( "LepTop_E","F" );
  vars.InitVar( "LepTop_Eta","F" );
  vars.InitVar( "LepTop_Phi","F" );
  vars.InitVar( "LepTop_M","F" );

  vars.InitVar( "LepTop_B_Pt","F" );
  vars.InitVar( "LepTop_B_E","F" );
  vars.InitVar( "LepTop_B_Eta","F" );
  vars.InitVar( "LepTop_B_Phi","F" );
  vars.InitVar( "LepTop_B_M","F" );
//   vars.InitVar( "LepTop_B_CSV","F" );
//   vars.InitVar( "LepTop_B_Flav","F" );

  vars.InitVar( "LepTop_W_Pt","F" );
  vars.InitVar( "LepTop_W_E","F" );
  vars.InitVar( "LepTop_W_Eta","F" );
  vars.InitVar( "LepTop_W_Phi","F" );
  vars.InitVar( "LepTop_W_M","F" );

  initialized=true;
}

void StdTopVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  std::vector<pat::Jet> selectedTaggedJets;
  std::vector<pat::Jet> selectedUntaggedJets;
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet){
    if(BoostedUtils::PassesCSV(*itJet, 'M')) selectedTaggedJets.push_back(*itJet);
    else selectedUntaggedJets.push_back(*itJet);
  }

  math::XYZTLorentzVector HadW;
  math::XYZTLorentzVector HadW1;
  math::XYZTLorentzVector HadW2;

  for(std::vector<pat::Jet>::const_iterator it1Jet = selectedUntaggedJets.begin(); it1Jet != selectedUntaggedJets.end(); ++it1Jet){
    for(std::vector<pat::Jet>::const_iterator it2Jet = selectedUntaggedJets.begin(); it2Jet != selectedUntaggedJets.end(); ++it2Jet){
      if(abs(80.4-(it1Jet->p4()+it2Jet->p4()).M())<abs(80.4-(HadW1+HadW2).M())){
        HadW1 = it1Jet->p4();
        HadW2 = it2Jet->p4();
        HadW = HadW1+HadW2;
      }
    }
  }

  vars.FillVar( "HadTop_W_Pt",HadW.Pt() );
  vars.FillVar( "HadTop_W_E",HadW.E() );
  vars.FillVar( "HadTop_W_Eta",HadW.Eta() );
  vars.FillVar( "HadTop_W_Phi",HadW.Phi() );
  vars.FillVar( "HadTop_W_M",HadW.M() );

  vars.FillVar( "HadTop_W1_Pt",HadW1.Pt() );
  vars.FillVar( "HadTop_W1_E",HadW1.E() );
  vars.FillVar( "HadTop_W1_Eta",HadW1.Eta() );
  vars.FillVar( "HadTop_W1_Phi",HadW1.Phi() );
  vars.FillVar( "HadTop_W1_M",HadW1.M() );

  vars.FillVar( "HadTop_W2_Pt",HadW2.Pt() );
  vars.FillVar( "HadTop_W2_E",HadW2.E() );
  vars.FillVar( "HadTop_W2_Eta",HadW2.Eta() );
  vars.FillVar( "HadTop_W2_Phi",HadW2.Phi() );
  vars.FillVar( "HadTop_W2_M",HadW2.M() );

  math::XYZTLorentzVector HadB;
  math::XYZTLorentzVector HadTop;

  for(std::vector<pat::Jet>::const_iterator itJet = selectedTaggedJets.begin(); itJet != selectedTaggedJets.end(); ++itJet){
    if(HadTop.M()==0 || abs(172.4-(HadW+itJet->p4()).M())<abs(172.4-HadTop.M())){
      HadB = itJet->p4();
      HadTop = HadB+HadW;
    }
    else{
      cout << "HadTop_W_Pt: " << HadW.Pt() << ", HadTop_B_Pt: " << itJet->pt() << ", Top mass: " << (HadW+itJet->p4()).M() << endl;
    }
  }

  vars.FillVar( "HadTop_B_Pt",HadB.Pt() );
  vars.FillVar( "HadTop_B_E",HadB.E() );
  vars.FillVar( "HadTop_B_Eta",HadB.Eta() );
  vars.FillVar( "HadTop_B_Phi",HadB.Phi() );
  vars.FillVar( "HadTop_B_M",HadB.M() );
//   vars.FillVar( "HadTop_B_CSV",BoostedUtils::GetJetCSV(HadB,btagger) );
//   vars.FillVar( "HadTop_B_Flav",HadB.flavour() );

  vars.FillVar( "HadTop_Pt",HadTop.Pt() );
  vars.FillVar( "HadTop_E",HadTop.E() );
  vars.FillVar( "HadTop_Eta",HadTop.Eta() );
  vars.FillVar( "HadTop_Phi",HadTop.Phi() );
  vars.FillVar( "HadTop_M",HadTop.M() );

  math::XYZTLorentzVector nu1;
  math::XYZTLorentzVector nu2;
  TVector2 MET;
  MET.Set(input.pfMET.px(),input.pfMET.py());
  math::XYZTLorentzVector PrimLep = BoostedUtils::GetPrimLepVec(input.selectedElectrons, input.selectedMuons);
  BoostedUtils::GetNuVecs(PrimLep, MET, nu1, nu2);

  math::XYZTLorentzVector LepW;

  if(abs(80.4-(nu1+PrimLep).M())<abs(80.4-(nu2+PrimLep).M())) LepW = nu1+PrimLep;
  else LepW = nu2+PrimLep;

  vars.FillVar( "LepTop_W_Pt",LepW.Pt() );
  vars.FillVar( "LepTop_W_E",LepW.E() );
  vars.FillVar( "LepTop_W_Eta",LepW.Eta() );
  vars.FillVar( "LepTop_W_Phi",LepW.Phi() );
  vars.FillVar( "LepTop_W_M",LepW.M() );

  math::XYZTLorentzVector LepB;
  math::XYZTLorentzVector LepTop;

  for(std::vector<pat::Jet>::const_iterator itJet = selectedTaggedJets.begin(); itJet != selectedTaggedJets.end(); ++itJet){
    if(LepTop.M()==0 || abs(172.4-(LepW+itJet->p4()).M())<abs(172.4-LepTop.M())){
      LepB = itJet->p4();
      LepTop = LepW+LepB;
    }
  }

  vars.FillVar( "LepTop_B_Pt",LepB.Pt() );
  vars.FillVar( "LepTop_B_E",LepB.E() );
  vars.FillVar( "LepTop_B_Eta",LepB.Eta() );
  vars.FillVar( "LepTop_B_Phi",LepB.Phi() );
  vars.FillVar( "LepTop_B_M",LepB.M() );
//   vars.FillVar( "LepTop_B_CSV",BoostedUtils::GetJetCSV(LepB,btagger) );
//   vars.FillVar( "LepTop_B_Flav",LepB.flavour() );

  vars.FillVar( "LepTop_Pt",LepTop.Pt() );
  vars.FillVar( "LepTop_E",LepTop.E() );
  vars.FillVar( "LepTop_Eta",LepTop.Eta() );
  vars.FillVar( "LepTop_Phi",LepTop.Phi() );
  vars.FillVar( "LepTop_M",LepTop.M() );

}

