#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TTHVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TTHVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TopTagger.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/HiggsTagger.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedttHEvent.hpp"

enum BoostedRecoType {BoostedTop,BoostedTopHiggs,BoostedHiggs};


class ttHVarProcessor: public TreeProcessor{
  
public:
  
  ttHVarProcessor(BoostedRecoType recotype=BoostedRecoType::BoostedTopHiggs,std::string taggername="TopLikelihood",std::string higgstaggername="HiggsCSV", std::string prefix="BoostedttHReco");
    ~ttHVarProcessor();
    
    void Init(const InputCollections& input,VariableContainer& var);
    void Process(const InputCollections& input,VariableContainer& var);
    
    void InitTopTagger(std::string taggername);
    void InitHiggsTagger(std::string higgstaggername);
    
    void InitHiggsCandidateVars(VariableContainer& vars);
    void InitTopHadCandidateVars(VariableContainer& vars);
    void InitTopLepCandidateVars(VariableContainer& vars);
    void InitAk5JetsVars(VariableContainer& vars);
    void InitCombinationVars(VariableContainer& vars);
    void InitMCVars(VariableContainer& vars);
    
    void FillHiggsCandidateVars(VariableContainer& vars, BoostedttHEvent& ttHevent);
    void FillTopHadCandidateVars(VariableContainer& vars, BoostedttHEvent& ttHevent);
    void FillTopLepCandidateVars(VariableContainer& vars,BoostedttHEvent& ttHevent);
    void FillAk5JetsVars(VariableContainer& vars,BoostedttHEvent& ttHevent);
    void FillCombinationVars(VariableContainer& vars,BoostedttHEvent& ttHevent);
    void FillMCVars(VariableContainer& vars,BoostedttHEvent& ttHevent);
    
private:
    const char* btagger;
    BoostedRecoType recotype;
    std::string   prefix;   
    TopTagger     toptagger;
    HiggsTagger* higgstagger;
};

#endif
