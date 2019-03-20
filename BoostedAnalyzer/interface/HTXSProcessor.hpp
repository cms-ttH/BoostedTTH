#ifndef BOOSTEDTTH_BOOSTEDANALYZER_HTXSPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_HTXSPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class HTXSProcessor: public TreeProcessor{

public:

    HTXSProcessor();
    ~HTXSProcessor();

    void Init(const InputCollections& input,VariableContainer& var);
    void Process(const InputCollections& input,VariableContainer& var);
private:
};

#endif

