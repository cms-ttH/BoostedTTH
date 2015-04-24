#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BDTOHIOV1_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BDTOHIOV1_HPP
#include <vector>
#include <map>
#include "MiniAOD/MiniAODHelper/interface/BDTvars.h"
#include "TMVA/Reader.h"

// class to evaluate retrained run I BDT
class BDTOhio_v1{
  
public:
  // constructor takes path to weights as argument
  BDTOhio_v1(TString weightPath);
  ~BDTOhio_v1();
  // Evaluate function takes all selected objects as input, figures out category and returns bdt output
  float Evaluate(const std::vector<pat::Muon>& selectedMuons, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Jet>& selectedJetsLoose, const pat::MET& pfMET);
  // Can be used to categorize events
  bool EventIsInCategory(std::string categoryLabel, const std::vector<pat::Jet>& selectedJets) const;
  // returns map with all input variable names and values (e.g. for control plots)
  std::map<std::string,float> GetVariablesOfLastEvaluation() const;

private:  
  float Evaluate(std::string categoryLabel,const std::vector<pat::Muon>& selectedMuons, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Jet>& selectedJetsLoose, const pat::MET& pfMET);
  std::map<std::string,TMVA::Reader*> readerMap;
  std::map<std::string,float> variableMap;
  BDTvars bdtvar;
  const double btagMcut;
  const char* btagger;

};

#endif
