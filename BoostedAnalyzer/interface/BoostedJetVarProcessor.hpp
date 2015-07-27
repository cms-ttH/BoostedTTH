#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDJETVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDJETVARPROCESSOR_HPP

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"
#include "MiniAOD/MiniAODHelper/interface/HiggsTagger.h"

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetMatching.hpp"



#include <vector>
#include <map>

class BoostedJetVarProcessor: public TreeProcessor{
  
  public:
    
    BoostedJetVarProcessor(MiniAODHelper* helper_);
    ~BoostedJetVarProcessor();
    
    void Init(const InputCollections& input, VariableContainer& var);
    void Process(const InputCollections& input, VariableContainer& var);


  private:

    const char* btagger;
    std::map<std::string,TopTagger> toptagger;
    std::map<std::string,HiggsTagger> higgstagger;
  
};

#endif
