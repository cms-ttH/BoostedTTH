#ifndef RECONSTRUCTIONMCMATCHING
#define RECONSTRUCTIONMCMATCHING

#include "TFile.h"
#include "TLorentzVector.h"
#include "BoostedTTH/TTHReconstruction/interface/Interpretation.hpp"
#include "TH1F.h"
#include "TMath.h"
#include <iostream>
#include <algorithm> 

class ReconstructionMCMatching{
public:
  ReconstructionMCMatching();

  void Setup(TLorentzVector b_had, TLorentzVector q1, TLorentzVector q2, TLorentzVector b_lep, TLorentzVector lep, TLorentzVector nu, TLorentzVector b1, TLorentzVector b2);
  void Setup(TLorentzVector b_had, TLorentzVector q1, TLorentzVector q2, TLorentzVector b_lep, TLorentzVector lep, TLorentzVector nu);
  float GetTag(std::string tag, Interpretation& i);
  int GetState();

  bool MatchTTHallQ(Interpretation& i);
  bool MatchTTallQ(Interpretation& i);
  bool MatchH(Interpretation& i);
  int MatchNH(Interpretation& i);
  float DrH(Interpretation& i);
  float DrB1(Interpretation& i);
  float DrB2(Interpretation& i);
  bool MatchWHad(Interpretation& i);
  int MatchNWHad(Interpretation& i);
  float DrWHad(Interpretation& i);
  float DrQ1(Interpretation& i);
  float DrQ2(Interpretation& i);
  float DrWLep(Interpretation& i);
  float DrLep(Interpretation& i);
  float DrNu(Interpretation& i);
  bool MatchBLep(Interpretation& i);
  float DrBLep(Interpretation& i);
  bool MatchBHad(Interpretation& i);
  float DrBHad(Interpretation& i);
  float DrTopHad(Interpretation& i);
  float DrTopLep(Interpretation& i);
  int MatchNTTH(Interpretation& i);
  float SumDrTTH(Interpretation& i);
  int MatchNTTHResonances(Interpretation& i);
  
 
private:
  float maxdr;
  int setupMC;
  TLorentzVector b_had;
  TLorentzVector q1;
  TLorentzVector q2;
  TLorentzVector b_lep;
  TLorentzVector lep;
  TLorentzVector nu;
  TLorentzVector b1;
  TLorentzVector b2;
  TLorentzVector top_had;
  TLorentzVector w_had;
  TLorentzVector w_lep;
  TLorentzVector top_lep;
  TLorentzVector higgs;

};

#endif
