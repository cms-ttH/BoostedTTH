#ifndef DILEPTONSELECTION_HPP
#define DILEPTONSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class DiLeptonSelection: public Selection{
    
public:
    
    DiLeptonSelection(const edm::ParameterSet& iConfig, int step=-1);
    DiLeptonSelection(std::vector<std::string> elelTriggers, std::vector<std::string> mumuTriggers, std::vector<std::string> elmuTriggers,std::vector<std::string> elTriggers,std::vector<std::string> muTriggers, std::string channel="all", int step=-1,std::string dataset="NA");
    DiLeptonSelection(std::string elelTrigger="None", std::string mumuTrigger="None", std::string elmuTrigger="None",std::string elTrigger="None",std::string muTrigger="None", std::string channel="all", int step=-1,std::string dataset="NA");
    ~DiLeptonSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

    std::vector<std::string> elelTriggers;
    std::vector<std::string> mumuTriggers;
    std::vector<std::string> elmuTriggers;
    std::vector<std::string> elTriggers;
    std::vector<std::string> muTriggers;
    std::string channel;
    int step;
    std::string dataset;
};

#endif
