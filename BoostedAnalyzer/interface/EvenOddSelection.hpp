#ifndef EVENODDSELECTION_HPP
#define EVENODDSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class EvenOddSelection : public Selection {
 public:
  EvenOddSelection(bool selEven_);
  ~EvenOddSelection();
  void InitCutflow(Cutflow& cutflow);
  bool IsSelected(const InputCollections& input, Cutflow& cutflow);

 private:
  bool selEven;
};

#endif
