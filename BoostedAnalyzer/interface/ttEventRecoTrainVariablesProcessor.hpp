#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TTEVENTRECOTRAINVARIABLESPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TTEVENTRECOTRAINVARIABLESPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

class ttEventRecoTrainVariablesProcessor: public TreeProcessor {

public: 
    ttEventRecoTrainVariablesProcessor();
    ~ttEventRecoTrainVariablesProcessor();
    
    void Init(const InputCollections &input, VariableContainer &vars);
    void Process(const InputCollections &input, VariableContainer &vars);

    void FillTargetVariables(const reco::GenParticle &particle, const std::string &name, VariableContainer &vars);

private:
    std::string inputPrefix;
    std::string targetPrefix;
};

#endif
