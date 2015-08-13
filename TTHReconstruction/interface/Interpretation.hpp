#ifndef INTERPRETATION
#define INTERPRETATION


#include "TLorentzVector.h"
#include "TVector2.h"
#include <map>
#include <vector>

class Interpretation{
public:
    Interpretation(TLorentzVector b_had, float csv_b_had, TLorentzVector q1, float csv_q1, TLorentzVector q2, float csv_q2, TLorentzVector b_lep, float csv_b_lep, TLorentzVector lep, TLorentzVector nu, TLorentzVector b1, float csv_b1, TLorentzVector b2, float csv_b2);

    Interpretation(TLorentzVector b_had, float csv_b_had, TLorentzVector q1, float csv_q1, TLorentzVector q2, float csv_q2, TLorentzVector b_lep, float csv_b_lep, TLorentzVector lep, TLorentzVector nu, TLorentzVector b1, float csv_b1, TLorentzVector b2, float csv_b2, std::vector<TLorentzVector> additional_jets, std::vector<float> additional_jetcsvs);

  Interpretation(TLorentzVector b_had_, float csv_b_had_, TLorentzVector q1_, float csv_q1_, TLorentzVector q2_, float csv_q2_, TLorentzVector b_lep_, float csv_b_lep_, TLorentzVector lep_, TLorentzVector nu_, std::vector<TLorentzVector> additional_jets, std::vector<float> additional_jetcsvs);

  Interpretation(TLorentzVector b_had_, float csv_b_had_, TLorentzVector q1_, float csv_q1_, TLorentzVector q2_, float csv_q2_, TLorentzVector b_lep_, float csv_b_lep_, TLorentzVector lep_, TLorentzVector nu_);

  TLorentzVector BHad();
  TLorentzVector Q1();
  TLorentzVector Q2();
  TLorentzVector B1();
  TLorentzVector B2();
  TLorentzVector BLep();
  TLorentzVector Lep();
  TLorentzVector Nu();
  TLorentzVector TopHad();
  TLorentzVector WHad();
  TLorentzVector TopLep();
  TLorentzVector Higgs();
  TLorentzVector Total();
  std::vector<TLorentzVector> AdditionalJets();
  float TopHad_M();
  float TopLep_M();
  float WHad_M();
  float WLep_M();
  float Higgs_M();
  float BHad_CSV();
  float BLep_CSV();
  float Q1_CSV();
  float Q2_CSV();
  float B1_CSV();
  float B2_CSV();
  void SetTag(std::string tag, float value);
  float GetTag(std::string tag);
  bool HasTag(std::string tag);
  
  static void GetNuVecs(const TLorentzVector & lepvec, const TVector2 & metvec, TLorentzVector & nu1, TLorentzVector & nu2);

private:
    TLorentzVector b1, b2, b_had, q1, q2, b_lep, lep, nu, w_had, t_had, w_lep, t_lep, higgs;
    float csv_b1, csv_b2, csv_b_had, csv_b_lep, csv_q1, csv_q2;
    std::vector<TLorentzVector> additional_jets;
    std::vector<float> additional_jetcsvs;
    std::map<std::string,float> tags;
 
};

#endif
