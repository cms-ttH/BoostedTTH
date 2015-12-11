#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TTBARRECONSTRUCTIONVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TTBARRECONSTRUCTIONVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/TTHReconstruction/interface/ReconstructionQuality.hpp"
#include "BoostedTTH/TTHReconstruction/interface/InterpretationGenerator.hpp"
#include "BoostedTTH/TTHReconstruction/interface/Interpretation.hpp"
#include "BoostedTTH/TTHReconstruction/interface/ReconstructionMCMatching.hpp"
#include "TLorentzVector.h"

class TTbarReconstructionVarProcessor: public TreeProcessor{

public:

    TTbarReconstructionVarProcessor();

    ~TTbarReconstructionVarProcessor();
    
    void Init(const InputCollections& input,VariableContainer& var);
    
    void Process(const InputCollections& input,VariableContainer& var);

private:
    ReconstructionQuality quality;
    InterpretationGenerator generator;
    ReconstructionMCMatching mcmatcher;

};

#endif
