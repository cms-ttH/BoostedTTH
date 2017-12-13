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
  vars.InitVar( "Mediator_Energy" );
  vars.InitVar( "Mediator_Px" );
  vars.InitVar( "Mediator_Py" );
  vars.InitVar( "Mediator_Pz" );
  
  vars.InitVar( "Neutralino1_Mass" );
  vars.InitVar( "Neutralino2_Mass" );
  vars.InitVar( "Neutralino1_Pt" );
  vars.InitVar( "Neutralino2_Pt" );
  vars.InitVar( "Neutralino1_Phi" );
  vars.InitVar( "Neutralino2_Phi" );
  vars.InitVar( "Neutralino1_Eta" );
  vars.InitVar( "Neutralino2_Eta" );
  vars.InitVar( "Neutralino1_Energy" );
  vars.InitVar( "Neutralino2_Energy" );
  vars.InitVar( "Neutralino1_Px" );
  vars.InitVar( "Neutralino2_Px" );
  vars.InitVar( "Neutralino1_Py" );
  vars.InitVar( "Neutralino2_Py" );
  vars.InitVar( "Neutralino1_Pz" );
  vars.InitVar( "Neutralino2_Pz" );
  
  vars.InitVar( "N1_N2_Mass" );
  vars.InitVar( "N1_N2_Pt" );
  vars.InitVar( "N1_N2_Phi" );
  vars.InitVar( "N1_N2_Eta" );
  vars.InitVar( "N1_N2_Energy" );
  vars.InitVar( "N1_N2_Px" );
  vars.InitVar( "N1_N2_Py" );
  vars.InitVar( "N1_N2_Pz" );
  
  vars.InitVar( "cos_theta_N1_N2" );
  vars.InitVar( "cos_theta_Med_N1" );
  vars.InitVar( "cos_theta_Med_N2" );
  
  vars.InitVar( "delta_phi_N1_N2" );
  vars.InitVar( "delta_phi_Med_N1" );
  vars.InitVar( "delta_phi_Med_N2" );
  
  vars.InitVar( "delta_R_N1_N2" );
  vars.InitVar( "delta_R_Med_N1" );
  vars.InitVar( "delta_R_Med_N2" );

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
  vars.FillVar( "Mediator_Energy",Mediator_p4.E());
  vars.FillVar( "Mediator_Px",Mediator_p4.Px());
  vars.FillVar( "Mediator_Py",Mediator_p4.Py());
  vars.FillVar( "Mediator_Pz",Mediator_p4.Pz());
  
  vars.FillVar( "Neutralino1_Mass",Neutralinos_p4[0].M());
  vars.FillVar( "Neutralino2_Mass",Neutralinos_p4[1].M());
  vars.FillVar( "Neutralino1_Pt",Neutralinos_p4[0].Pt());
  vars.FillVar( "Neutralino2_Pt",Neutralinos_p4[1].Pt());
  vars.FillVar( "Neutralino1_Phi",Neutralinos_p4[0].Phi());
  vars.FillVar( "Neutralino2_Phi",Neutralinos_p4[1].Phi());
  vars.FillVar( "Neutralino1_Eta",Neutralinos_p4[0].Eta());
  vars.FillVar( "Neutralino2_Eta",Neutralinos_p4[1].Eta());
  vars.FillVar( "Neutralino1_Energy",Neutralinos_p4[0].E());
  vars.FillVar( "Neutralino2_Energy",Neutralinos_p4[1].E());
  vars.FillVar( "Neutralino1_Px",Neutralinos_p4[0].Px());
  vars.FillVar( "Neutralino2_Px",Neutralinos_p4[1].Px());
  vars.FillVar( "Neutralino1_Py",Neutralinos_p4[0].Py());
  vars.FillVar( "Neutralino2_Py",Neutralinos_p4[1].Py());
  vars.FillVar( "Neutralino1_Pz",Neutralinos_p4[0].Pz());
  vars.FillVar( "Neutralino2_Pz",Neutralinos_p4[1].Pz());
  
  vars.FillVar( "N1_N2_Mass",(Neutralinos_p4[0]+Neutralinos_p4[1]).M());
  vars.FillVar( "N1_N2_Pt",(Neutralinos_p4[0]+Neutralinos_p4[1]).Pt());
  vars.FillVar( "N1_N2_Phi",(Neutralinos_p4[0]+Neutralinos_p4[1]).Phi());
  vars.FillVar( "N1_N2_Eta",(Neutralinos_p4[0]+Neutralinos_p4[1]).Eta());
  vars.FillVar( "N1_N2_Energy",(Neutralinos_p4[0]+Neutralinos_p4[1]).E());
  vars.FillVar( "N1_N2_Px",(Neutralinos_p4[0]+Neutralinos_p4[1]).Px());
  vars.FillVar( "N1_N2_Py",(Neutralinos_p4[0]+Neutralinos_p4[1]).Py());
  vars.FillVar( "N1_N2_Pz",(Neutralinos_p4[0]+Neutralinos_p4[1]).Pz());
  
  vars.FillVar( "cos_theta_N1_N2",TMath::Cos((Neutralinos_p4[0].Vect()).Angle(Neutralinos_p4[1].Vect())));
  vars.FillVar( "cos_theta_Med_N1",TMath::Cos((Neutralinos_p4[0].Vect()).Angle(Mediator_p4.Vect())));
  vars.FillVar( "cos_theta_Med_N2",TMath::Cos((Neutralinos_p4[1].Vect()).Angle(Mediator_p4.Vect())));
  
  vars.FillVar( "delta_phi_N1_N2",Neutralinos_p4[0].DeltaPhi(Neutralinos_p4[1]));
  vars.FillVar( "delta_phi_Med_N1",Mediator_p4.DeltaPhi(Neutralinos_p4[0]));
  vars.FillVar( "delta_phi_Med_N2",Mediator_p4.DeltaPhi(Neutralinos_p4[1]));
  
  vars.FillVar( "delta_R_N1_N2",Neutralinos_p4[0].DeltaR(Neutralinos_p4[1]));
  vars.FillVar( "delta_R_Med_N1",Mediator_p4.DeltaR(Neutralinos_p4[0]));
  vars.FillVar( "delta_R_Med_N2",Mediator_p4.DeltaR(Neutralinos_p4[1]));
  
  }
}
