#ifndef BOOSTEDTTH_BOOSTEDANALYZER_SPINCORRELATIONPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_SPINCORRELATIONPROCESSOR_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/ReconstructionQuality.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/InterpretationGenerator.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/Interpretation.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/ReconstructionMCMatching.hpp"

class SpinCorrelationProcessor : public TreeProcessor {
 public:
  SpinCorrelationProcessor();
  ~SpinCorrelationProcessor();

  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input, VariableContainer& var);
  TLorentzVector Boost(const TLorentzVector in_vec, Int_t frame_number,
                       const TLorentzVector vec_top_,
                       const TLorentzVector vec_antitop_);
  void SetAllVectors(TLorentzVector& vec_top_, TLorentzVector& vec_antitop_,
                     TLorentzVector& vec_b_, TLorentzVector& vec_antib_,
                     TLorentzVector& vec_lepton_,
                     TLorentzVector& vec_antilepton_, TLorentzVector& vec_d_,
                     TLorentzVector& vec_antid_, int identifier);
  double GetVars(const TLorentzVector vec_top_,
                 const TLorentzVector vec_antitop_, const TLorentzVector vec_b_,
                 const TLorentzVector vec_antib_,
                 const TLorentzVector vec_lepton_,
                 const TLorentzVector vec_antilepton_,
                 const TLorentzVector vec_d_, const TLorentzVector vec_antid_,
                 Int_t var_number);
  Interpretation* GetBestLR(int& njets, int& ntags,
                            std::vector<TLorentzVector>& jetvecs,
                            std::vector<float>& jetcsvs, TLorentzVector& lepvec,
                            TVector2& metvec, bool& flag, float& best_lr);
  reco::GenParticle MatchPartontoJet(vector<reco::GenParticle>& Partons,
                                     pat::Jet& Jet);

 private:
  ReconstructionQuality quality;
  InterpretationGenerator generator;
  // ReconstructionMCMatching mcmatcher;
};

#endif