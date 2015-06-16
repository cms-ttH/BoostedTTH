#ifndef METSelection_HPP
#define METSelection_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class METSelection: public Selection{
  
  public:
    
    METSelection();
    ~METSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

};

#endif
