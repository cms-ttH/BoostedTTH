#ifndef LEPTONSELECTION_HPP
#define LEPTONSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class LeptonSelection: public Selection{
  
  public:
    
    LeptonSelection();
    ~LeptonSelection();
    void Init(const edm::ParameterSet& iConfig, Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

    std::vector<std::string> muonTriggers;
    std::vector<std::string> electronTriggers;

};

#endif
