#ifndef BOOSTEDTTH_BOOSTEDANALYZER_STDTOPVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_STDTOPVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class StdTopVarProcessor : public TreeProcessor {
   public:
    StdTopVarProcessor();
    ~StdTopVarProcessor();

    void Init(const InputCollections& input, VariableContainer& var);
    void Process(const InputCollections& input, VariableContainer& var);

   private:
};

#endif
