#ifndef HBBSELECTION_HPP
#define HBBSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class HbbSelection : public Selection {
 public:
  HbbSelection();
  ~HbbSelection();
  void InitCutflow(Cutflow& cutflow);
  bool IsSelected(const InputCollections& input, Cutflow& cutflow);

 private:
};

#endif
