#ifndef BOOSTEDTTH_BOOSTEDANALYZER_LEPTONVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_LEPTONVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class LeptonVarProcessor : public TreeProcessor {
   public:
    LeptonVarProcessor();
    ~LeptonVarProcessor();

    void Init(const InputCollections& input, VariableContainer& var);
    void Process(const InputCollections& input, VariableContainer& var);
};

#endif
