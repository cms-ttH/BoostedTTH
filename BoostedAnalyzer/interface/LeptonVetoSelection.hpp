#ifndef LEPTONVETOSELECTION_HPP
#define LEPTONVETOSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class LeptonVetoSelection: public Selection{
  
  public:
    
    LeptonVetoSelection();
    ~LeptonVetoSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

};

#endif
