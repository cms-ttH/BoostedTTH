#ifndef LEPTONSELECTION_HPP
#define LEPTONSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class LeptonSelection : public Selection
{

public:
  LeptonSelection(const edm::ParameterSet& iConfig, int step = -1);
  LeptonSelection(std::vector<std::string> electronTriggers,
                  std::vector<std::string> muonTriggers,
                  std::string channel = "both",
                  int step = -1);
  LeptonSelection(std::string electronTrigger = "any",
                  std::string muonTrigger = "any",
                  std::string channel = "both",
                  int step = -1);
  ~LeptonSelection();
  void InitCutflow(Cutflow& cutflow);
  bool IsSelected(const InputCollections& input, Cutflow& cutflow);

private:
  std::vector<std::string> electronTriggers;
  std::vector<std::string> muonTriggers;
  std::string channel;
  int step;
};

#endif
