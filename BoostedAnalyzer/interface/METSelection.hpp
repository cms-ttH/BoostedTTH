#ifndef METSelection_HPP
#define METSelection_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class METSelection: public Selection{
  
  public:
    
    METSelection(const edm::ParameterSet& iConfig);
    ~METSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:
    float minMET;
    float maxMET;
    std::string selectionName;

};

#endif
