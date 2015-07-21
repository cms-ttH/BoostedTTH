#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TOPTAGGER_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TOPTAGGER_HPP

#include <map>

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "BoostedTTH/BoostedObjects/interface/HTTTopJet.h"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "TH1F.h"
#include "TFile.h"
#include "TMVA/Reader.h"

class TopTagger{
  
public:
  
  TopTagger();
  TopTagger(std::string name, std::string histosPath = "toplikelihoodtaggerhistos.root");
  TopTagger(std::string name, std::vector<std::string> BDTVarNames, std::string weightsPath = "");
  float GetTopTag(const boosted::HTTTopJet& topJet, bool verbose = false);
  bool FirstHasHigherTopTaggerOutput(boosted::HTTTopJet jet1, boosted::HTTTopJet jet2);
  boosted::HTTTopJetCollection GetSortedByTopTaggerOutput(const boosted::HTTTopJetCollection& topJets, bool verbose = false);
  float GetTopHad(boosted::HTTTopJetCollection& topJets, boosted::HTTTopJet& topHadCand, bool verbose = false);

private:
  std::string name;
  
  bool toplikelihood;
  bool tmva;
  
  TFile* file;
  TH1F* mtop_top_histo;
  TH1F* mtop_nottop_histo;
  TH1F* mratio_top_histo;
  TH1F* mratio_nottop_histo;
  TH1F* atan_top_histo;
  TH1F* atan_nottop_histo;
  
  TMVA::Reader* BDTReader;
  std::map<std::string,float> BDTVars;
  
  void ResetBDTVars();  
  
  float GetTopLikelihood(const boosted::HTTTopJet& topjet, bool verbose);
  float GetBDTOutput(const boosted::HTTTopJet& topjet, bool verbose); 
};


struct TopTaggerOutputComparison{

  TopTagger* topTagger;

  TopTaggerOutputComparison(TopTagger* topTagger_): topTagger(topTagger_){};

  bool operator()(boosted::HTTTopJet jet1, boosted::HTTTopJet jet2){
    return topTagger->GetTopTag(jet1)>topTagger->GetTopTag(jet2);
  };
};

#endif
