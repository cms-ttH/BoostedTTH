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
  vars.InitVar( "DiMuon_SS");

  vars.InitVar( "DiElectron_E");
  vars.InitVar( "DiElectron_M");
  vars.InitVar( "DiElectron_Pt");
  vars.InitVar( "DiElectron_Eta");
  vars.InitVar( "DiElectron_Phi");
  vars.InitVar( "DiElectron_SS");

  vars.InitVar( "ElMu_E");
  vars.InitVar( "ElMu_M");
  vars.InitVar( "ElMu_Pt");
  vars.InitVar( "ElMu_Eta");
  vars.InitVar( "ElMu_Phi");
  vars.InitVar( "ElMu_SS");

  
  //vars.InitVar( "LeptonLepton_Opening_Angle" );
  
  
  initialized=true;

}


void DiLeptonVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  if(input.selectedMuonsLoose.size()>=2){
    
    math::XYZTLorentzVector DiMuonVec=input.selectedMuonsLoose[0].p4()+input.selectedMuonsLoose[1].p4();
    
    //TLorentzVector v1(input.selectedMuonsLoose[0].p4().Px(),input.selectedMuonsLoose[0].p4().Py(),input.selectedMuonsLoose[0].p4().Pz(),input.selectedMuonsLoose[0].p4().E());
    //TLorentzVector v2(input.selectedMuonsLoose[1].p4().Px(),input.selectedMuonsLoose[1].p4().Py(),input.selectedMuonsLoose[1].p4().Pz(),input.selectedMuonsLoose[1].p4().E());
    //TVector3 p1 = v1.Vect();
    //TVector3 p2 = v2.Vect();
    //Double_t di_op_ang = 360./(2*TMath::Pi())*p1.Angle(p2);
    //if(di_op_ang<0){di_op_ang=360./(2*TMath::Pi())*p2.Angle(p1);}
    //vars.FillVar( "LeptonLepton_Opening_Angle",di_op_ang );
    
    vars.FillVar( "DiMuon_E",DiMuonVec.E() );
    vars.FillVar( "DiMuon_M",DiMuonVec.M() );
    vars.FillVar( "DiMuon_Pt",DiMuonVec.Pt() );
    vars.FillVar( "DiMuon_Eta",DiMuonVec.Eta() );
    vars.FillVar( "DiMuon_Phi",DiMuonVec.Phi() );
    vars.FillVar( "DiMuon_SS",input.selectedMuonsLoose[0].charge()*input.selectedMuonsLoose[1].charge()>0 );
    
  }

  if(input.selectedElectronsLoose.size()>=2){

    math::XYZTLorentzVector DiElectronVec=input.selectedElectronsLoose[0].p4()+input.selectedElectronsLoose[1].p4();
    
    /*TLorentzVector v1(input.selectedElectronsLoose[0].p4().Px(),input.selectedElectronsLoose[0].p4().Py(),input.selectedElectronsLoose[0].p4().Pz(),input.selectedElectronsLoose[0].p4().E());
    TLorentzVector v2(input.selectedElectronsLoose[1].p4().Px(),input.selectedElectronsLoose[1].p4().Py(),input.selectedElectronsLoose[1].p4().Pz(),input.selectedElectronsLoose[1].p4().E());
    TVector3 p1 = v1.Vect();
    TVector3 p2 = v2.Vect();
    Double_t di_op_ang = 360./(2*TMath::Pi())*p1.Angle(p2);
    if(di_op_ang<0){di_op_ang=360./(2*TMath::Pi())*p2.Angle(p1);}
    vars.FillVar( "LeptonLepton_Opening_Angle",di_op_ang );*/
    
    vars.FillVar( "DiElectron_E",DiElectronVec.E() );
    vars.FillVar( "DiElectron_M",DiElectronVec.M() );
    vars.FillVar( "DiElectron_Pt",DiElectronVec.Pt() );
    vars.FillVar( "DiElectron_Eta",DiElectronVec.Eta() );
    vars.FillVar( "DiElectron_Phi",DiElectronVec.Phi() );

    vars.FillVar( "DiElectron_SS",input.selectedElectronsLoose[0].charge()*input.selectedElectronsLoose[1].charge()>0 );
  }

  if(input.selectedElectronsLoose.size()>=1&&input.selectedMuonsLoose.size()>=1){
    
    math::XYZTLorentzVector ElMuVec=input.selectedElectronsLoose[0].p4()+input.selectedMuonsLoose[0].p4();
    
    /*TLorentzVector v1(input.selectedElectronsLoose[0].p4().Px(),input.selectedElectronsLoose[0].p4().Py(),input.selectedElectronsLoose[0].p4().Pz(),input.selectedElectronsLoose[0].p4().E());
    TLorentzVector v2(input.selectedMuonsLoose[0].p4().Px(),input.selectedMuonsLoose[0].p4().Py(),input.selectedMuonsLoose[0].p4().Pz(),input.selectedMuonsLoose[0].p4().E());
    TVector3 p1 = v1.Vect();
    TVector3 p2 = v2.Vect();
    Double_t di_op_ang = 360./(2*TMath::Pi())*p1.Angle(p2);
    if(di_op_ang<0){di_op_ang=360./(2*TMath::Pi())*p2.Angle(p1);}
    vars.FillVar( "LeptonLepton_Opening_Angle",di_op_ang );*/

    vars.FillVar( "ElMu_E",ElMuVec.E() );
    vars.FillVar( "ElMu_M",ElMuVec.M() );
    vars.FillVar( "ElMu_Pt",ElMuVec.Pt() );
    vars.FillVar( "ElMu_Eta",ElMuVec.Eta() );
    vars.FillVar( "ElMu_Phi",ElMuVec.Phi() );
    vars.FillVar( "ElMu_SS",input.selectedElectronsLoose[0].charge()*input.selectedMuonsLoose[1].charge()>0 );
  }



}
