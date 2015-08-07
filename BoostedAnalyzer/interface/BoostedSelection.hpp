#ifndef BOOSTEDSELECTION_HPP
#define BOOSTEDSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"
#include "MiniAOD/MiniAODHelper/interface/HiggsTagger.h"

class BoostedSelection: public Selection{
  
  public:
    
    BoostedSelection(int minTopTags=1,int minHiggsTags=1);
    ~BoostedSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:
    TopTagger toptagger;
    int minTopTags;
    int minHiggsTags;
};

#endif
