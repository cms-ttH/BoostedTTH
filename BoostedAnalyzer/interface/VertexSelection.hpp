#ifndef VERTEXSELECTION_HPP
#define VERTEXSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class VertexSelection : public Selection {
 public:
  VertexSelection();
  ~VertexSelection();
  void InitCutflow(Cutflow& cutflow);
  bool IsSelected(const InputCollections& input, Cutflow& cutflow);

 private:
};

#endif
