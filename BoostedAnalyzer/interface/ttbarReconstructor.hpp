#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TTBARRECONSTRUCTOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TTBARRECONSTRUCTOR_HPP

#include <vector>
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"
#include "THnSparse.h"

class ttbarReconstructor: public TreeProcessor{
  
public:
  
  ttbarReconstructor();
  ~ttbarReconstructor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
  void SetdRArray(math::XYZTLorentzVector vec_top,math::XYZTLorentzVector vec_antitop,math::XYZTLorentzVector vec_b,math::XYZTLorentzVector vec_antib,math::XYZTLorentzVector vec_q_u,math::XYZTLorentzVector vec_q_d,math::XYZTLorentzVector vec_antiq_u,math::XYZTLorentzVector vec_antiq_d,math::XYZTLorentzVector vec_lepton,math::XYZTLorentzVector vec_antilepton,math::XYZTLorentzVector vec_nu,math::XYZTLorentzVector vec_antinu,int leptonflag);
  double GetLikelihood(int leptonflag);
  void GetNuVecs(const TLorentzVector & lepvec, const TVector2 & metvec, TLorentzVector & nu1, TLorentzVector & nu2);
  
private:
  //std::vector<TString> variables;
  double dR_array[19]={0};
  THnSparseD* histo_lepton;
  THnSparseD* histo_antilepton;
  //std::map<TString,TH1D*> hists;
  //std::map<TString,double> likelihoods;
  //ReconstructionQuality quality;
  //InterpretationGenerator generator;
  //ReconstructionMCMatching mcmatcher;
};
  
#endif