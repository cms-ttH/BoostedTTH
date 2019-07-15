#ifndef GENTOPSLSELECTION_HPP
#define GENTOPSLSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class GenTopSLSelection : public Selection {
 public:
  GenTopSLSelection();
  ~GenTopSLSelection();
  void InitCutflow(Cutflow& cutflow);
  bool IsSelected(const InputCollections& input, Cutflow& cutflow);

 private:
};

#endif
