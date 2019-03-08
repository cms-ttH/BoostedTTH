#ifndef JETTAGSELECTION_HPP
#define JETTAGSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"
#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"

class JetTagSelection: public Selection{
  
  public:
  
    JetTagSelection(const edm::ParameterSet& iConfig);
    JetTagSelection(std::vector<int> minjets,std::vector<int> mintags);
    JetTagSelection(int minjets,int mintags);
    JetTagSelection(std::vector<int> minjets,std::vector<int> maxjets, std::vector<int> mintags, std::vector<int> maxtags);
    ~JetTagSelection();
    void InitCutflow(Cutflow& cutflow);
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
