#ifndef RECONSTRUCTIONQUALITY
#define RECONSTRUCTIONQUALITY

#include "TFile.h"
#include "TLorentzVector.h"
#include "BoostedTTH/TTHReconstruction/interface/Interpretation.hpp"
#include "BoostedTTH/TTHReconstruction/interface/MECalculator.hpp"
#include "TH1F.h"
#include "TMath.h"
#include <iostream>
#include <algorithm> 

class ReconstructionQuality{
public:
    ReconstructionQuality(std::string filename="");
    
    float GetTag(std::string tag, Interpretation& i);
    // get chi2 containing 3 (4) terms: hadronic top-mass, leptonic top-mass, W-mass (, Higgs/BB-mass)
    float TTHChi2(Interpretation& i);
    float TTBBChi2(Interpretation& i);
    float TTChi2(Interpretation& i);
    
    // get likelihood for the masses of hadronic top, leptonic top, W (, Higgs/BB-mass) for a perfectly reconstructed tth-interpreatation
    float TTHLikelihood(Interpretation& i);
    float TTBBLikelihood(Interpretation& i);
    float TTLikelihood(Interpretation& i);
    // get likelihood for the masses of hadronic top, leptonic top, W (and Higgs/BB-mass) for combinatoric background
    float TTHLikelihood_comb(Interpretation& i);
    float TTBBLikelihood_comb(Interpretation& i);
    float TTLikelihood_comb(Interpretation& i);
    // get likelihood for the masses of hadronic top, leptonic top, W (and Higgs/BB-mass) for the best possible interpretation
    float TopAndWHadLikelihood(Interpretation& i);
    
    float TTHLikelihoodTimesME(Interpretation& i);
    float TTBBLikelihoodTimesME(Interpretation& i);


    // get the b-tagger likelihoods
    float BLikelihood(float csv);
    float LLikelihood(float csv);
    float NBLikelihood(uint ntagged, uint njets, float* csvs);
      
    // get matrix element squared
    float TTH_ME(Interpretation& i);
    // ttbb me, using bb-mass as it is
    float TTBB_OFF_ME(Interpretation& i);
    // ttbb me, scaling bb-mass to 125 GeV
    float TTBB_ON_ME(Interpretation& i);
    float TTHBB_ME(Interpretation& i);
    
   
private:
    float TTHChi2(float mthad, float mtlep, float mhiggs, float mwhad);
    float TTBBChi2(float mthad, float mtlep, float mhiggs, float mwhad);
    float TTChi2(float mthad, float mtlep, float mwhad);
    
    float TTHLikelihood(float mthad, float mtlep, float mhiggs, float mwhad);
    float TTBBLikelihood(float mthad, float mtlep, float mhiggs, float mwhad);
    float TTLikelihood(float mthad, float mtlep, float mwhad);
    
    float TTHLikelihood_comb(float mthad, float mtlep, float mhiggs, float mwhad);
    float TTBBLikelihood_comb(float mthad, float mtlep, float mhiggs, float mwhad);
    float TTLikelihood_comb(float mthad, float mtlep, float mwhad);
  
// get likelihoods for different masses
    float TopHadLikelihood(float m);
    float TopHadLikelihood_comb(float m);
    float TopAndWHadLikelihood(float mthad,float mwhad);
    float TopAndWHadLikelihood_comb(float mthad,float mwhad);
    float TopLepLikelihood(float m);
    float TopLepLikelihood_comb(float m);
    float WHadLikelihood(float m);
    float WHadLikelihood_comb(float m);
    float HiggsLikelihood(float m);
    float HiggsLikelihood_comb(float m);
    float BBLikelihood(float m);
    float BBLikelihood_comb(float m);
    float Interpolate(TH1F* histo, float value);
    void PCA_MW_MT(float mw, float mt, float& mw_new , float& mt_new);    
  
    
    TFile* file;
    TH1F* h_CSV_b;
    TH1F* h_CSV_l_w_c;
    TH1F* h_M_Higgs_reco;
    TH1F* h_M_BB_reco;
    TH1F* h_M_TopHad_reco;
    TH1F* h_M_TopHad_pca_reco;
    TH1F* h_M_TopLep_reco;
    TH1F* h_M_WHad_reco;
    TH1F* h_M_WHad_pca_reco;
    TH1F* h_M_Higgs_best;
    TH1F* h_M_TopHad_best;
    TH1F* h_M_TopLep_best;
    TH1F* h_M_WHad_best;
    TH1F* h_M_Higgs_all;
    TH1F* h_M_BB_all;
    TH1F* h_M_TopHad_all;
    TH1F* h_M_TopHad_pca_all;
    TH1F* h_M_TopLep_all;
    TH1F* h_M_WHad_all;
    TH1F* h_M_WHad_pca_all;
    
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
