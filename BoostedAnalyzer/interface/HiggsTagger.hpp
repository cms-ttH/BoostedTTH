#ifndef BOOSTEDTTH_BOOSTEDANALYZER_HIGGSTAGGER_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_HIGGSTAGGER_HPP

#include <map>

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "BoostedTTH/BoostedObjects/interface/SubFilterJet.h"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "TH1F.h"
#include "TFile.h"
#include "TMVA/Reader.h"

class HiggsTagger{
  
public:
  
  HiggsTagger();
  HiggsTagger(std::string name);
  HiggsTagger(std::string name, std::vector<std::string> BDTVarNames, std::string weightsPath);
  float GetHiggsTag(const boosted::SubFilterJet& higgsJet, bool verbose = false);
  bool FirstHasHigherHiggsTaggerOutput(boosted::SubFilterJet jet1, boosted::SubFilterJet jet2);
  boosted::SubFilterJetCollection GetSortedByHiggsTaggerOutput(const boosted::SubFilterJetCollection& higgsJets, bool verbose = false);
  float GetHiggsCand(boosted::SubFilterJetCollection& higgsJets, boosted::SubFilterJet& higgsCand, bool verbose = false);

private:
  std::string name;
  
  bool secondcsv;
  bool tmva;
  
  TMVA::Reader* BDTReader;
  std::map<std::string,float> BDTVars;
  
  void ResetBDTVars();  
  
  float GetSecondCSV(const boosted::SubFilterJet& topjet, bool verbose);
  float GetBDTOutput(const boosted::SubFilterJet& topjet, bool verbose); 
};


struct HiggsTaggerOutputComparison{

  HiggsTagger* higgsTagger;

  HiggsTaggerOutputComparison(HiggsTagger* higgsTagger_): higgsTagger(higgsTagger_){};

  bool operator()(boosted::SubFilterJet jet1, boosted::SubFilterJet jet2){
    return higgsTagger->GetHiggsTag(jet1) > higgsTagger->GetHiggsTag(jet2);
  };
};

#endif
