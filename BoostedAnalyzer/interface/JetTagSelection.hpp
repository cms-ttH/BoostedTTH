#ifndef JETTAGSELECTION_HPP
#define JETTAGSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class JetTagSelection: public Selection{
  
  public:
  
    JetTagSelection();
    ~JetTagSelection();
    void Init(const edm::ParameterSet& iConfig, Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

    

    std::string selName;

    size_t selSize;

    std::vector<int> minJets;
    std::vector<int> maxJets;
    std::vector<int> minTags;
    std::vector<int> maxTags;

};

#endif
