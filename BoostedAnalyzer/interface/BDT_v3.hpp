#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BDT_V3_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BDT_V3_HPP
#include <vector>
#include <map>
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "MiniAOD/MiniAODHelper/interface/BDTvars.h"
#include "TMVA/Reader.h"

// class to evaluate retrained run I BDT
class BDT_v3{
  
public:
  // constructor takes path to weights as argument
  BDT_v3(TString weightPath);
  ~BDT_v3();

  // Evaluate function takes all selected objects as input, figures out category and returns bdt output
  float Evaluate(const std::vector<pat::Muon>& selectedMuons, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Jet>& selectedJetsLoose, const pat::MET& pfMET);
  // returns map with all input variable names and values (e.g. for control plots)
  std::map<std::string,float> GetVariablesOfLastEvaluation() const;
  // return all BDT outputs, need to call evaluate first
  std::map<std::string,float> GetAllOutputsOfLastEvaluation() const;

  // Can be used to categorize events
  std::vector<std::string> GetAllCategories() const;
  std::string GetCategory(const std::vector<pat::Jet>& selectedJets) const;


private:  
  float Evaluate(std::string categoryLabel,const std::vector<pat::Muon>& selectedMuons, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Jet>& selectedJetsLoose, const pat::MET& pfMET);
  std::map<std::string,TMVA::Reader*> readerMap;
  std::map<std::string,float> variableMap;
  BDTvars bdtvar;
  const double btagMcut;

};

#endif
