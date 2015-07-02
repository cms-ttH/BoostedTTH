#ifndef DILEPTONSELECTION_HPP
#define DILEPTONSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class DiLeptonSelection: public Selection{
    
public:
    
    DiLeptonSelection(const edm::ParameterSet& iConfig, int step=-1);
    DiLeptonSelection(std::vector<std::string> elelTriggers, std::vector<std::string> mumuTriggers, std::vector<std::string> elmuTriggers, std::string channel="all", int step=-1);
    DiLeptonSelection(std::string elelTrigger="None", std::string mumuTrigger="None", std::string elmuTrigger="None", std::string channel="all", int step=-1);
    ~DiLeptonSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

    std::vector<std::string> elelTriggers;
    std::vector<std::string> mumuTriggers;
    std::vector<std::string> elmuTriggers;
    std::string channel;
    int step;
};

#endif
