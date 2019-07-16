#ifndef GENTOPFHSELECTION_HPP
#define GENTOPFHSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class GenTopFHSelection : public Selection {
   public:
    GenTopFHSelection();
    ~GenTopFHSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input, Cutflow& cutflow);

   private:
};

#endif
