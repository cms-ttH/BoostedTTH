#ifndef THQJETSELECTION_HPP
#define THQJETSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class THQJetSelection: public Selection{
  
  public:
    
    THQJetSelection();
    ~THQJetSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

};

#endif
