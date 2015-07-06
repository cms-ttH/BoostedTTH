#ifndef DILEPTONMASSSELECTION_HPP
#define DILEPTONMASSSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class DiLeptonMassSelection: public Selection{
    
public:
    
    DiLeptonMassSelection(float minMass,float maxMass,bool invertCut=false);
    ~DiLeptonMassSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


private:

    float minMass;
    float maxMass;
    bool invertCut;
    std::string selectionName;
};

#endif
