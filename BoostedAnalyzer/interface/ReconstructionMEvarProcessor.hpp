#ifndef BOOSTEDTTH_BOOSTEDANALYZER_RECONSTRUCTIONMEVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_RECONSTRUCTIONMEVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/ReconstructionQuality.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/InterpretationGenerator.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/Interpretation.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/ReconstructionMCMatching.hpp"
#include "TLorentzVector.h"
#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"

class ReconstructionMEvarProcessor: public TreeProcessor{

public:

    ReconstructionMEvarProcessor();

    ~ReconstructionMEvarProcessor();
    
    void Init(const InputCollections& input,VariableContainer& var);
    
    void Process(const InputCollections& input,VariableContainer& var);

private:
    ReconstructionQuality quality;
    InterpretationGenerator generator;
    ReconstructionMCMatching mcmatcher;
    std::vector<std::string> tags_tt;
    std::vector<std::string> tags_ttbb;
    std::vector<std::string> tags_tth;
    std::vector<std::string> alltags;
    std::vector<std::string> ratiotags_name;
    std::vector<std::string> ratiotags_tth;
    std::vector<std::string> ratiotags_ttbb;

};

#endif
