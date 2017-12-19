#ifndef LEPTONSELECTION_QCDCONTROLREGION_HPP
#define LEPTONSELECTION_QCDCONTROLREGION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class LeptonSelection_QCDControlregion: public Selection{
  
  public:
    
    LeptonSelection_QCDControlregion(const edm::ParameterSet& iConfig, int step=-1);
    LeptonSelection_QCDControlregion(std::vector<std::string> electronTriggers, std::vector<std::string> muonTriggers, std::string channel="both", int step=-1);
    LeptonSelection_QCDControlregion(std::string electronTrigger="any", std::string muonTrigger="any", std::string channel="both", int step=-1);
    ~LeptonSelection_QCDControlregion();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

    std::vector<std::string> electronTriggers;
    std::vector<std::string> muonTriggers;
    std::string channel;
    int step;
};

#endif
