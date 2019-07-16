#ifndef DILEPTONMASSSELECTION_HPP
#define DILEPTONMASSSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class DiLeptonMassSelection : public Selection {
   public:
    DiLeptonMassSelection(float minMass, float maxMass, bool invertCut = false, bool cutForDifferentFlavors = true);
    ~DiLeptonMassSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input, Cutflow& cutflow);

   private:
    float       minMass;
    float       maxMass;
    bool        invertCut;
    std::string selectionName;
    bool        cutForDifferentFlavors;
};

#endif
