#include "BoostedTTH/TTHReconstruction/interface/Interpretation.hpp"
#include <iostream>
using namespace std;

Interpretation::Interpretation(TLorentzVector b_had_, float csv_b_had_, TLorentzVector q1_, float csv_q1_, TLorentzVector q2_, float csv_q2_, TLorentzVector b_lep_, float csv_b_lep_, TLorentzVector lep_, TLorentzVector nu_, TLorentzVector b1_, float csv_b1_, TLorentzVector b2_, float csv_b2_){
  b1=b1_;
  b2=b2_;
  b_had=b_had_;
  q1=q1_;
  q2=q2_;
  b_lep=b_lep_;
  lep=lep_;
  nu=nu_;
  csv_b1=csv_b1_;
  csv_b2=csv_b2_;
  csv_b_had=csv_b_had_;
  csv_b_lep=csv_b_lep_;
  csv_q1=csv_q1_;
  csv_q2=csv_q2_;
  //dervived
  w_had=q1+q2;
  t_had=b_had+w_had;
  w_lep=lep+nu;
  t_lep=b_lep+w_lep;
  higgs=b1+b2;

}

Interpretation::Interpretation(TLorentzVector b_had_, float csv_b_had_, TLorentzVector q1_, float csv_q1_, TLorentzVector q2_, float csv_q2_, TLorentzVector b_lep_, float csv_b_lep_, TLorentzVector lep_, TLorentzVector nu_){
  b_had=b_had_;
  q1=q1_;
  q2=q2_;
  b_lep=b_lep_;
  lep=lep_;
  nu=nu_;
  csv_b1=-2;
  csv_b2=-2;
  csv_b_had=csv_b_had_;
  csv_b_lep=csv_b_lep_;
  csv_q1=csv_q1_;
  csv_q2=csv_q2_;
  //dervived
  w_had=q1+q2;
  t_had=b_had+w_had;
  w_lep=lep+nu;
  t_lep=b_lep+w_lep;
}


TLorentzVector Interpretation::BHad(){
  return b_had;
}
TLorentzVector Interpretation::Q1(){
  return q1;
}
TLorentzVector Interpretation::Q2(){
  return q2;
}
TLorentzVector Interpretation::BLep(){
  return b_lep;
}
TLorentzVector Interpretation::Lep(){
  return lep;
}
TLorentzVector Interpretation::Nu(){
  return nu;
}
TLorentzVector Interpretation::TopHad(){
  return t_had;
}
TLorentzVector Interpretation::WHad(){
  return w_had;
}
TLorentzVector Interpretation::TopLep(){
  return t_lep;
}
TLorentzVector Interpretation::B1(){
  return b1;
}
TLorentzVector Interpretation::B2(){
  return b2;
}
TLorentzVector Interpretation::Total(){
  return t_had+t_lep+higgs;
}


TLorentzVector Interpretation::Higgs(){
  return higgs;
}
float Interpretation::TopHad_M(){
  return t_had.M();
}
float Interpretation::TopLep_M(){
  return t_lep.M();
}
float Interpretation::WHad_M(){
  return w_had.M();
}
float Interpretation::WLep_M(){
  return w_lep.M();
}
float Interpretation::Higgs_M(){
  return higgs.M();
}
float Interpretation::BHad_CSV(){
  return csv_b_had;
}
float Interpretation::BLep_CSV(){
  return csv_b_lep;
}
float Interpretation::Q1_CSV(){
  return csv_q1;
}
float Interpretation::Q2_CSV(){
  return csv_q2;
}
float Interpretation::B1_CSV(){
  return csv_b1;
}
float Interpretation::B2_CSV(){
  return csv_b2;
}
void Interpretation::SetTag(std::string tag, float value){
  tags[tag]=value;
}
float Interpretation::GetTag(std::string tag){
  return tags[tag];
}

bool Interpretation::HasTag(std::string tag){
  return tags.count(tag)>0;
}

void Interpretation::GetNuVecs(const TLorentzVector & lepvec, const TVector2 & metvec, TLorentzVector & nu1, TLorentzVector & nu2){
  double metvec2 = metvec.Px()*metvec.Px() + metvec.Py()*metvec.Py();
  double mu = (80.4*80.4)/2 + metvec.Px()*lepvec.Px() + metvec.Py()*lepvec.Py();
  double a = (mu*lepvec.Pz())/(lepvec.E()*lepvec.E() - lepvec.Pz()*lepvec.Pz());
  double a2 = TMath::Power(a, 2);
  double b = (TMath::Power(lepvec.E(), 2.)*metvec2 - TMath::Power(mu, 2.)) / (TMath::Power(lepvec.E(), 2)- TMath::Power(lepvec.Pz(), 2));
  float pz1,pz2;
  if (a2-b < 0) { 
    pz1 = a;
    pz2 = a;
  } else {
    double root = sqrt(a2-b);
    pz1 = a + root;
    pz2 = a - root;
  }
  nu1.SetPxPyPzE(metvec.Px(),metvec.Py(),pz1,sqrt(metvec.Mod2()+pz1*pz1));
  nu2.SetPxPyPzE(metvec.Px(),metvec.Py(),pz2,sqrt(metvec.Mod2()+pz2*pz2));
}
