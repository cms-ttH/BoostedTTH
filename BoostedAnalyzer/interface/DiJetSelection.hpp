#ifndef DIJET_SELECTION_HPP
#define DIJET_SELECTION_HPP

#include <string>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"


class DiJetSelection : public Selection {
public:
  DiJetSelection();
  ~DiJetSelection() {}

  void InitCutflow(Cutflow& cutflow);
  bool IsSelected(const InputCollections& input,Cutflow& cutflow);


private:
  std::string selectionStep1_;
  double minPt_;
};
#endif
