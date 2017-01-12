#ifndef FILTERSELECTION_HPP
#define FILTERSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class FilterSelection: public Selection{
  
  public:
    
    FilterSelection(const edm::ParameterSet& iConfig);
    ~FilterSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:
    std::vector<std::string> filters;
};

#endif
