#ifndef BTAGVETOSELECTION_HPP
#define BTAGVETOSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class BTagVetoSelection: public Selection{
  
  public:
    
    BTagVetoSelection();
    ~BTagVetoSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

};

#endif