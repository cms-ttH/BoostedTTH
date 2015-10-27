#ifndef LOOSELEPTONSELECTION_HPP
#define LOOSELEPTONSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class LooseLeptonSelection: public Selection{
  
  public:
    
    LooseLeptonSelection(const edm::ParameterSet& iConfig, int step=-1);
    LooseLeptonSelection(std::vector<std::string> electronTriggers, std::vector<std::string> muonTriggers, std::string channel="both", int step=-1);
    LooseLeptonSelection(std::string electronTrigger="any", std::string muonTrigger="any", std::string channel="both", int step=-1);
    ~LooseLeptonSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

    std::vector<std::string> electronTriggers;
    std::vector<std::string> muonTriggers;
    std::string channel;
    int step;
};

#endif
