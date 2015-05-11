#ifndef LEPTONSELECTION_HPP
#define LEPTONSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class LeptonSelection: public Selection{
  
  public:
    
    LeptonSelection(const edm::ParameterSet& iConfig, int step=-1);
    ~LeptonSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

    std::vector<std::string> muonTriggers;
    std::vector<std::string> electronTriggers;
    std::string channel;
    int step;
};

#endif
