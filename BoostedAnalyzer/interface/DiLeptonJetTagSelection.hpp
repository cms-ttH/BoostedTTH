#ifndef DILEPTONJETTAGSELECTION_HPP
#define DILEPTONJETTAGSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class DiLeptonJetTagSelection: public Selection{
  
  public:
  
    DiLeptonJetTagSelection(const edm::ParameterSet& iConfig);
    DiLeptonJetTagSelection(std::vector<int> minjets,std::vector<int> mintags);
    DiLeptonJetTagSelection(int minjets,int mintags);
    DiLeptonJetTagSelection(std::vector<int> minjets,std::vector<int> maxjets, std::vector<int> mintags, std::vector<int> maxtags);
    ~DiLeptonJetTagSelection();
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
