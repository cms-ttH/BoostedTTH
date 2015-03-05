#ifndef SYNCHSELECTION_HPP
#define SYNCHSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include <stdio.h>
#include <string.h>



class SynchSelection: public Selection{
  
public:
    
  SynchSelection();
  ~SynchSelection();
  void Init(const edm::ParameterSet& iConfig, Cutflow& cutflow);
  bool IsSelected(const InputCollections& input,Cutflow& cutflow);

private:
  
  std::vector<std::string> muonTriggers;
  std::vector<std::string> electronTriggers;

};

#endif
