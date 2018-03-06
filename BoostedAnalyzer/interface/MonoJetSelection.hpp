#ifndef MONOJETSELECTION_HPP
#define MONOJETSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class MonoJetSelection: public Selection{
  
  public:
  
    MonoJetSelection(const edm::ParameterSet& iConfig);
    MonoJetSelection(double pt_min_,double eta_max_,double chf_min_,double nhf_max_);
    ~MonoJetSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);
    double DeltaPhi(const double& phi1, const double& phi2);

  private:

    double pt_min;
    double eta_max;
    double charged_hadron_fraction_min;
    double neutral_hadron_fraction_max;
    std::string pt_str="";
    std::string eta_str="";

};

#endif
