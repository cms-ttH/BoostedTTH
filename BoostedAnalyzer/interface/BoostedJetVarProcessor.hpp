#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDJETVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDJETVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

#include <vector>

class BoostedJetVarProcessor: public TreeProcessor{
  
  public:
    
    BoostedJetVarProcessor();
    ~BoostedJetVarProcessor();
    
    void Init(const InputCollections& input, VariableContainer& var);
    void Process(const InputCollections& input, VariableContainer& var);


  private:

    const char* btagger;

  
};

#endif
