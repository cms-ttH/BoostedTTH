#ifndef BOOSTEDTTH_BOOSTEDANALYZER_SPINCORRELATIONPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_SPINCORRELATIONPROCESSOR_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/TTHReconstruction/interface/ReconstructionQuality.hpp"
#include "BoostedTTH/TTHReconstruction/interface/InterpretationGenerator.hpp"
#include "BoostedTTH/TTHReconstruction/interface/Interpretation.hpp"
#include "BoostedTTH/TTHReconstruction/interface/ReconstructionMCMatching.hpp"

class SpinCorrelationProcessor: public TreeProcessor{
  
public:
  
  SpinCorrelationProcessor();
  ~SpinCorrelationProcessor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
  TLorentzVector Boost(TLorentzVector in_vec, Int_t frame_number, TLorentzVector vec_top_, TLorentzVector vec_antitop_);
  void SetAllVectors(TLorentzVector& vec_top_, TLorentzVector& vec_antitop_, TLorentzVector& vec_b_, TLorentzVector& vec_antib_, TLorentzVector& vec_lepton_, TLorentzVector& vec_antilepton_,TLorentzVector& vec_d_,TLorentzVector& vec_antid_, int identifier);
  double GetVars(TLorentzVector vec_top_, TLorentzVector vec_antitop_, TLorentzVector vec_b_,TLorentzVector vec_antib_, TLorentzVector vec_lepton_,TLorentzVector vec_antilepton_,TLorentzVector vec_d_,TLorentzVector vec_antid_, Int_t var_number);
private:
  ReconstructionQuality quality;
  InterpretationGenerator generator;
  //ReconstructionMCMatching mcmatcher;
};
  
#endif