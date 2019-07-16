#ifndef BOOSTEDTTH_BOOSTEDANALYZER_PROCESSORTEMPLATE_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_PROCESSORTEMPLATE_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"

class ProcessorTemplate : public TreeProcessor {
   public:
    // all configurations should be done in constructor
    ProcessorTemplate();
    ~ProcessorTemplate();
    // you have to implement this to functions, you can add additionional
    // (private) functions
    void Init(const InputCollections& input, VariableContainer& var);
    void Process(const InputCollections& input, VariableContainer& var);

   private:
    // add all members needed, initialize in constructor
};

#endif
