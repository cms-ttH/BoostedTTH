#ifndef BOOSTEDTTH_BOOSTEDANALYZER_RECONSTRUCTIONVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_RECONSTRUCTIONVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/TTHReconstruction/interface/ReconstructionQuality.hpp"
#include "BoostedTTH/TTHReconstruction/interface/InterpretationGenerator.hpp"
#include "BoostedTTH/TTHReconstruction/interface/Interpretation.hpp"
#include "TLorentzVector.h"

class ReconstructionVarProcessor: public TreeProcessor{

public:

    ReconstructionVarProcessor();

    ~ReconstructionVarProcessor();
    
    void Init(const InputCollections& input,VariableContainer& var);
    
    void Process(const InputCollections& input,VariableContainer& var);

private:
    ReconstructionQuality quality;
    InterpretationGenerator generator;
    std::vector<std::string> tags;


};

#endif
