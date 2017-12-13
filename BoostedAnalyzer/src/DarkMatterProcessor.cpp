#include "BoostedTTH/BoostedAnalyzer/interface/DarkMatterProcessor.hpp"

using namespace std;

DarkMatterProcessor::DarkMatterProcessor(){}
DarkMatterProcessor::~DarkMatterProcessor(){}


void DarkMatterProcessor::Init(const InputCollections& input,VariableContainer& vars){
  
  vars.InitVar( "Evt_Pt_MET" );
  vars.InitVar( "Evt_Phi_MET" );
  vars.InitVar( "Evt_Pt_GenMET" );
  vars.InitVar( "Evt_Phi_GenMET" );
  
  vars.InitVar( "NaiveMET" );
  
  vars.InitVar( "Mediator_Mass" );
  vars.InitVar( "Mediator_Pt" );
  vars.InitVar( "Mediator_Phi" );
  vars.InitVar( "Mediator_Eta" );
  
  vars.InitVar( "Neutralino1_Mass" );
  vars.InitVar( "Neutralino2_Mass" );
  vars.InitVar( "Neutralino1_Pt" );
  vars.InitVar( "Neutralino2_Pt" );
  vars.InitVar( "Neutralino1_Phi" );
  vars.InitVar( "Neutralino2_Phi" );
  vars.InitVar( "Neutralino1_Eta" );
  vars.InitVar( "Neutralino2_Eta" );

  initialized=true;
}

void DarkMatterProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  
  vars.FillVar( "Evt_Pt_MET",input.correctedMET.corPt(pat::MET::Type1XY) );
  vars.FillVar( "Evt_Phi_MET",input.correctedMET.corPhi(pat::MET::Type1XY) );
  if(input.correctedMET.genMET()!=0){
      vars.FillVar( "Evt_Pt_GenMET",input.correctedMET.genMET()->pt() );
      vars.FillVar( "Evt_Phi_GenMET",input.correctedMET.genMET()->phi() );
  }
  
  if(input.genDarkMatterEvt.IsFilled()){
  
  const GenDarkMatterEvent& DM_Evt = input.genDarkMatterEvt;
  
  TLorentzVector Mediator_p4 = DM_Evt.ReturnMediator4Vector();
  std::vector<TLorentzVector> Neutralinos_p4 = DM_Evt.ReturnNeutralino4Vectors();
  
  vars.FillVar( "NaiveMET",DM_Evt.ReturnNaiveMET());
  
  vars.FillVar( "Mediator_Mass",Mediator_p4.M());
  vars.FillVar( "Mediator_Pt",Mediator_p4.Pt());
  vars.FillVar( "Mediator_Phi",Mediator_p4.Phi());
  vars.FillVar( "Mediator_Eta",Mediator_p4.Eta());
  
  vars.FillVar( "Neutralino1_Mass",Neutralinos_p4[0].M());
  vars.FillVar( "Neutralino2_Mass",Neutralinos_p4[1].M());
  vars.FillVar( "Neutralino1_Pt",Neutralinos_p4[0].Pt());
  vars.FillVar( "Neutralino2_Pt",Neutralinos_p4[1].Pt());
  vars.FillVar( "Neutralino1_Phi",Neutralinos_p4[0].Phi());
  vars.FillVar( "Neutralino2_Phi",Neutralinos_p4[1].Phi());
  vars.FillVar( "Neutralino1_Eta",Neutralinos_p4[0].Eta());
  vars.FillVar( "Neutralino2_Eta",Neutralinos_p4[1].Eta());
  
  }
}
