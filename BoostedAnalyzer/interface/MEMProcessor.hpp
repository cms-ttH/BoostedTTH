#ifndef MEMPROCESSOR_HPP
#define MEMPROCESSOR_HPP
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "TTH/CommonClassifier/interface/MEMClassifier.h"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "TMVA/Reader.h"

class MEMProcessor: public TreeProcessor{
public:
    MEMProcessor(int minJets=6, int maxJets=8, int minTags=4);
    MEMProcessor(const edm::ParameterSet& iConfig);
    ~MEMProcessor();
    void Init(const InputCollections& input, VariableContainer& var);
    void Process(const InputCollections& input,VariableContainer& var);

private:
    int minJets;
    int maxJets;
    int minTags;
    MEMClassifier mem;
    const double btagMcut=0.89;
  
};

#endif
