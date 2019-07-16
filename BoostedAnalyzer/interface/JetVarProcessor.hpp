#ifndef BOOSTEDTTH_BOOSTEDANALYZER_JETVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_JETVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"

class JetVarProcessor : public TreeProcessor {
   public:
    JetVarProcessor();
    ~JetVarProcessor();

    void Init(const InputCollections& input, VariableContainer& var);
    void Process(const InputCollections& input, VariableContainer& var);

   private:
    std::string era;
};

#endif
