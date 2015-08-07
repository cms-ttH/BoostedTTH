#ifndef RECONSTRUCTIONQUALITY
#define RECONSTRUCTIONQUALITY

#include "TFile.h"
#include "TLorentzVector.h"
#include "BoostedTTH/BoostedAnalyzer/interface/Interpretation.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MECalculator.hpp"
#include "TH1F.h"
#include "TMath.h"
#include <iostream>
#include <algorithm> 

class ReconstructionQuality{
public:
  ReconstructionQuality(std::string filename="data/likelihoodhistos.root");

  float GetTag(std::string tag, Interpretation& i);
  // get chi2 containing 3 (4) terms: hadronic top-mass, leptonic top-mass, W-mass (, Higgs/BB-mass)
  float TTWHChi2(Interpretation& i);
  float TTWBBChi2(Interpretation& i);
  float TTWChi2(Interpretation& i);

  // get likelihood for the masses of hadronic top, leptonic top, W (, Higgs/BB-mass) for a perfectly reconstructed tth-interpreatation
  float TTWHLikelihood(Interpretation& i);
  float TTWBBLikelihood(Interpretation& i);
  float TTWLikelihood(Interpretation& i);
  // get likelihood for the masses of hadronic top, leptonic top, W (and Higgs/BB-mass) for combinatoric background
  float TTWHLikelihood_comb(Interpretation& i);
  float TTWBBLikelihood_comb(Interpretation& i);
  float TTWLikelihood_comb(Interpretation& i);
  // get likelihood for the masses of hadronic top, leptonic top, W (and Higgs/BB-mass) for the best possible interpretation
  float TTWHishLikelihood(Interpretation& i);
  float TTWishLikelihood(Interpretation& i);

  // get the b-tagger likelihoods
  float BLikelihood(float csv);
  float LLikelihood(float csv);
  float NBLikelihood(uint ntagged, uint njets, float* csvs);

  // get likelihoods for different masses
  float TopHadLikelihood(float m);
  float TopHadLikelihood_comb(float m);
  float TopHadishLikelihood(float m);
  float TopLepLikelihood(float m);
  float TopLepLikelihood_comb(float m);
  float TopLepishLikelihood(float m);
  float WHadLikelihood(float m);
  float WHadLikelihood_comb(float m);
  float WHadishLikelihood(float m);
  float HiggsLikelihood(float m);
  float HiggsLikelihood_comb(float m);
  float HiggsishLikelihood(float m);
  float BBLikelihood(float m);
  float BBLikelihood_comb(float m);

  // get matrix element squared
  float TTH_ME(Interpretation& i);
  // ttbb me, using bb-mass as it is
  float TTBB_OFF_ME(Interpretation& i);
  // ttbb me, scaling bb-mass to 125 GeV
  float TTBB_ON_ME(Interpretation& i);
  float TTHBB_ME(Interpretation& i);
  
  float Interpolate(TH1F* histo, float value);

 
private:
  float TTWHChi2(float mthad, float mtlep, float mhiggs, float mwhad);
  float TTWBBChi2(float mthad, float mtlep, float mhiggs, float mwhad);
  float TTWChi2(float mthad, float mtlep, float mwhad);

  float TTWHLikelihood(float mthad, float mtlep, float mhiggs, float mwhad);
  float TTWBBLikelihood(float mthad, float mtlep, float mhiggs, float mwhad);
  float TTWLikelihood(float mthad, float mtlep, float mwhad);

  float TTWHLikelihood_comb(float mthad, float mtlep, float mhiggs, float mwhad);
  float TTWBBLikelihood_comb(float mthad, float mtlep, float mhiggs, float mwhad);
  float TTWLikelihood_comb(float mthad, float mtlep, float mwhad);

  float TTWHishLikelihood(float mthad, float mtlep, float mhiggs, float mwhad);
  float TTWishLikelihood(float mthad, float mtlep, float mwhad);


  TFile* file;
  TH1F* h_CSV_b;
  TH1F* h_CSV_l_w_c;
  TH1F* h_M_Higgs_reco;
  TH1F* h_M_BB_reco;
  TH1F* h_M_TopHad_reco;
  TH1F* h_M_TopLep_reco;
  TH1F* h_M_WHad_reco;
  TH1F* h_M_Higgs_best;
  TH1F* h_M_TopHad_best;
  TH1F* h_M_TopLep_best;
  TH1F* h_M_WHad_best;
  TH1F* h_M_Higgs_all;
  TH1F* h_M_BB_all;
  TH1F* h_M_TopHad_all;
  TH1F* h_M_TopLep_all;
  TH1F* h_M_WHad_all;

  float higgs_mean;
  float tophad_mean;
  float toplep_mean;
  float whad_mean;
  float higgs_sigma;
  float tophad_sigma;
  float toplep_sigma;
  float whad_sigma;
  
  float bb_slope;

  float tiny_likelihood;

  MECalculator me;
};

#endif
