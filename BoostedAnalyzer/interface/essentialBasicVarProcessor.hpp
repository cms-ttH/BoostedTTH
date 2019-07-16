#ifndef BOOSTEDTTH_BOOSTEDANALYZER_ESSENTIALBASICVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_ESSENTIALBASICVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"

class essentialBasicVarProcessor : public TreeProcessor {
   public:
    essentialBasicVarProcessor();
    ~essentialBasicVarProcessor();

    void Init(const InputCollections& input, VariableContainer& var);
    void Process(const InputCollections& input, VariableContainer& var);

   private:
    std::string era;
};

#endif
