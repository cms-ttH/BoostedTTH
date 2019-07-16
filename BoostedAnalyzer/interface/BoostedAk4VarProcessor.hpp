#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDAK4VARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDAK4VARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class BoostedAk4VarProcessor : public TreeProcessor {
   public:
    BoostedAk4VarProcessor();
    ~BoostedAk4VarProcessor();

    void Init(const InputCollections& input, VariableContainer& var);
    void Process(const InputCollections& input, VariableContainer& var);

   private:
};

#endif
