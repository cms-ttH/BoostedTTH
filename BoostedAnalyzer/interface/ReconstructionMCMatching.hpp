#ifndef RECONSTRUCTIONMCMATCHING
#define RECONSTRUCTIONMCMATCHING

#include "TFile.h"
#include "TLorentzVector.h"
#include "BoostedTTH/BoostedAnalyzer/interface/Interpretation.hpp"
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

  bool MatchTTHallQ(Interpretation& i);
  bool MatchTTallQ(Interpretation& i);
  bool MatchH(Interpretation& i);
  int MatchNH(Interpretation& i);
  bool MatchWHad(Interpretation& i);
  int MatchNWHad(Interpretation& i);
  bool MatchBLep(Interpretation& i);
  bool MatchBHad(Interpretation& i);
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

};

#endif
