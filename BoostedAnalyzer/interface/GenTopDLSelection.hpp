#ifndef GENTOPDLSELECTION_HPP
#define GENTOPDLSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class GenTopDLSelection : public Selection {
   public:
    GenTopDLSelection();
    ~GenTopDLSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input, Cutflow& cutflow);

   private:
};

#endif
