#include "BoostedTTH/BoostedAnalyzer/interface/DarkMatterProcessor.hpp"

using namespace std;

DarkMatterProcessor::DarkMatterProcessor(){}
DarkMatterProcessor::~DarkMatterProcessor(){}


void DarkMatterProcessor::Init(const InputCollections& input,VariableContainer& vars){
  
  vars.InitVar( "Evt_Pt_MET" );
  vars.InitVar( "Evt_Phi_MET" );
  vars.InitVar( "Evt_Pt_GenMET" );
  vars.InitVar( "Evt_Phi_GenMET" );
  vars.InitVar( "CaloMET" );
  vars.InitVar( "CaloMET_PFMET_ratio" );
  vars.InitVar( "NaiveMET" );
  
  vars.InitVars( "DeltaPhi_Jet_MET","N_Jets");
  
  vars.InitVar( "N_Neutralinos","I" );
  vars.InitVar( "N_Neutrinos","I" );
  
  vars.InitVar( "Mediator_Mass" );
  vars.InitVar( "Mediator_Pt" );
  vars.InitVar( "Mediator_Phi" );
  vars.InitVar( "Mediator_Eta" );
  vars.InitVar( "Mediator_Energy" );
  vars.InitVar( "Mediator_Px" );
  vars.InitVar( "Mediator_Py" );
  vars.InitVar( "Mediator_Pz" );
  
  vars.InitVars( "Neutralino_Mass","N_Neutralinos" );
  vars.InitVars( "Neutralino_Pt","N_Neutralinos" );
  vars.InitVars( "Neutralino_Phi","N_Neutralinos" );
  vars.InitVars( "Neutralino_Eta","N_Neutralinos" );
  vars.InitVars( "Neutralino_Energy","N_Neutralinos" );
  vars.InitVars( "Neutralino_Px","N_Neutralinos" );
  vars.InitVars( "Neutralino_Py","N_Neutralinos" );
  vars.InitVars( "Neutralino_Pz","N_Neutralinos" );
  
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
  
  vars.InitVars( "Neutrino_Mass","N_Neutrinos" );
  vars.InitVars( "Neutrino_Pt","N_Neutrinos" );
  vars.InitVars( "Neutrino_Phi","N_Neutrinos" );
  vars.InitVars( "Neutrino_Eta","N_Neutrinos" );
  vars.InitVars( "Neutrino_Energy","N_Neutrinos" );
  vars.InitVars( "Neutrino_Px","N_Neutrinos" );
  vars.InitVars( "Neutrino_Py","N_Neutrinos" );
  vars.InitVars( "Neutrino_Pz","N_Neutrinos" );

  initialized=true;
}

void DarkMatterProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  
  vars.FillVar( "Evt_Pt_MET",input.correctedMET.corPt(pat::MET::Type1XY) );
  vars.FillVar( "Evt_Phi_MET",input.correctedMET.corPhi(pat::MET::Type1XY) );
  vars.FillVar( "CaloMET",input.correctedMET.caloMETPt() );
  vars.FillVar( "CaloMET_PFMET_ratio",fabs(input.correctedMET.corPt(pat::MET::Type1XY)-input.correctedMET.caloMETPt())/input.correctedMET.corPt(pat::MET::Type1XY) );
  if(input.correctedMET.genMET()!=0){
      vars.FillVar( "Evt_Pt_GenMET",input.correctedMET.genMET()->pt() );
      vars.FillVar( "Evt_Phi_GenMET",input.correctedMET.genMET()->phi() );
  }
  for(size_t i=0;i<input.selectedJets.size();i++){
    vars.FillVars ( "DeltaPhi_Jet_MET",i,fabs(TVector2::Phi_mpi_pi(input.correctedMET.corPhi(pat::MET::Type1XY)-input.selectedJets.at(i).phi())));
  }
  
  if(input.genDarkMatterEvt.IsFilled()){
  
    const GenDarkMatterEvent& DM_Evt = input.genDarkMatterEvt;
    
    TLorentzVector Mediator_p4 = DM_Evt.ReturnMediator4Vector();
    std::vector<TLorentzVector> Neutralinos_p4 = DM_Evt.ReturnNeutralino4Vectors();
    std::vector<TLorentzVector> Neutrinos_p4 = DM_Evt.ReturnNeutrino4Vectors();
    
    vars.FillVar( "N_Neutralinos",Neutralinos_p4.size() );
    vars.FillVar( "N_Neutrinos",Neutrinos_p4.size() );
    
    vars.FillVar( "NaiveMET",DM_Evt.ReturnNaiveMET());
    
    vars.FillVar( "Mediator_Mass",Mediator_p4.M());
    vars.FillVar( "Mediator_Pt",Mediator_p4.Pt());
    vars.FillVar( "Mediator_Phi",Mediator_p4.Phi());
    vars.FillVar( "Mediator_Eta",Mediator_p4.Eta());
    vars.FillVar( "Mediator_Energy",Mediator_p4.E());
    vars.FillVar( "Mediator_Px",Mediator_p4.Px());
    vars.FillVar( "Mediator_Py",Mediator_p4.Py());
    vars.FillVar( "Mediator_Pz",Mediator_p4.Pz());
    
    for(std::vector<TLorentzVector>::const_iterator itNeutralino = Neutralinos_p4.begin() ; itNeutralino != Neutralinos_p4.end(); ++itNeutralino){
        int iNeutralino = itNeutralino - Neutralinos_p4.begin();
        vars.FillVars( "Neutralino_Mass",iNeutralino,itNeutralino->M() );
        vars.FillVars( "Neutralino_Pt",iNeutralino,itNeutralino->Pt() );
        vars.FillVars( "Neutralino_Phi",iNeutralino,itNeutralino->Phi() );
        vars.FillVars( "Neutralino_Eta",iNeutralino,itNeutralino->Eta() );
        vars.FillVars( "Neutralino_Energy",iNeutralino,itNeutralino->E() );
        vars.FillVars( "Neutralino_Px",iNeutralino,itNeutralino->Px() );
        vars.FillVars( "Neutralino_Py",iNeutralino,itNeutralino->Py() );
        vars.FillVars( "Neutralino_Pz",iNeutralino,itNeutralino->Pz() );
    }
    
    if(Neutralinos_p4.size()>=2){
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
    
    for(std::vector<TLorentzVector>::const_iterator itNeutrino = Neutrinos_p4.begin() ; itNeutrino != Neutrinos_p4.end(); ++itNeutrino){
        int iNeutrino = itNeutrino - Neutrinos_p4.begin();
        vars.FillVars( "Neutrino_Mass",iNeutrino,itNeutrino->M() );
        vars.FillVars( "Neutrino_Pt",iNeutrino,itNeutrino->Pt() );
        vars.FillVars( "Neutrino_Phi",iNeutrino,itNeutrino->Phi() );
        vars.FillVars( "Neutrino_Eta",iNeutrino,itNeutrino->Eta() );
        vars.FillVars( "Neutrino_Energy",iNeutrino,itNeutrino->E() );
        vars.FillVars( "Neutrino_Px",iNeutrino,itNeutrino->Px() );
        vars.FillVars( "Neutrino_Py",iNeutrino,itNeutrino->Py() );
        vars.FillVars( "Neutrino_Pz",iNeutrino,itNeutrino->Pz() );
    }
  
  }
}
