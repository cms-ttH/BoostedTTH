#ifndef BOOSTEDTTH_BOOSTEDANALYZER_ESSENTIALRECOVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_ESSENTIALRECOVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"

#include "TTH/CommonClassifier/interface/ReconstructedVars.h"

class essentialRecoVarProcessor : public TreeProcessor
{

public:
    essentialRecoVarProcessor();

    ~essentialRecoVarProcessor();

    void Init(const InputCollections &input, VariableContainer &var);
    void Process(const InputCollections &input, VariableContainer &var);

private:
    std::map<std::string, double> varMap;
    std::string btagger;
    // RecoVars from CommonClassifier classifier for sl channel
    std::unique_ptr<ReconstructedVars> pointerToRecoVars = nullptr;
};

#endif
