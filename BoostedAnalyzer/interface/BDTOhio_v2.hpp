#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BDTOHIOV2_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BDTOHIOV2_HPP
#include <vector>
#include <map>
#include "MiniAOD/MiniAODHelper/interface/BDTvars.h"
#include "TMVA/Reader.h"

// class to evaluate retrained run I BDT
class BDTOhio_v2{
  
public:
  // constructor takes path to weights as argument
  BDTOhio_v2(TString weightPath);
  ~BDTOhio_v2();

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
  const char* btagger;

};

#endif
