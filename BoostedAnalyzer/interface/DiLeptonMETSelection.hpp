#ifndef DILEPTONMETSelection_HPP
#define DILEPTONMETSelection_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class DiLeptonMETSelection: public Selection{
  
  public:
    
    DiLeptonMETSelection(const edm::ParameterSet& iConfig);
    DiLeptonMETSelection(float minMET=-1, float maxMET=999999);
    ~DiLeptonMETSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:
    float minMET;
    float maxMET;
    std::string selectionName;

};

#endif
