#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TTEVENTRECOTRAINVARIABLESPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TTEVENTRECOTRAINVARIABLESPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class ttEventRecoTrainVariablesProcessor: public TreeProcessor {

public: 
    ttEventRecoTrainVariablesProcessor();
    ~ttEventRecoTrainVariablesProcessor();
    
    void Init(const InputCollections &input, VariableContainer &var);
    void Process(const InputCollections &input, VariableContainer &var);
private:
};

#endif
