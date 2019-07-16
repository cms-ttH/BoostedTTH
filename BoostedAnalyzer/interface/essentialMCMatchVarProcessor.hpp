#ifndef BOOSTEDTTH_BOOSTEDANALYZER_ESSENTIALMCMATCHVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_ESSENTIALMCMATCHVARPROCESSOR_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

class essentialMCMatchVarProcessor : public TreeProcessor {
   public:
    essentialMCMatchVarProcessor();
    ~essentialMCMatchVarProcessor();

    void Init(const InputCollections& input, VariableContainer& var);
    void Process(const InputCollections& input, VariableContainer& var);
};

#endif
