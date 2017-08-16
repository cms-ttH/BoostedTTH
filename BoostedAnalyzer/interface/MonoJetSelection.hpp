#ifndef MONOJETSELECTION_HPP
#define MONOJETSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class MonoJetSelection: public Selection{
  
  public:
  
    MonoJetSelection(const edm::ParameterSet& iConfig);
    MonoJetSelection(double pt_min_,double eta_max_);
    ~MonoJetSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

    double pt_min;
    double eta_max;
    std::string pt_str="";
    std::string eta_str="";

};

#endif
