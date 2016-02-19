#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TTHVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TTHVARPROCESSOR_HPP

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"
#include "MiniAOD/MiniAODHelper/interface/HiggsTagger.h"

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedttHEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

enum BoostedRecoType {BoostedTop,BoostedTopHiggs,BoostedHiggs};


class ttHVarProcessor: public TreeProcessor{
  
  public:
  
    ttHVarProcessor(BoostedRecoType recotype_, MiniAODHelper* helper_, TopTag::Mode topTaggerMode_, TopTag::SubjetAssign subjetAssign_, std::string topTaggerfilePath_, HiggsTag::Mode higgsTaggerMode_, std::string higgsTaggerFilePath_, std::string prefix="");
    ~ttHVarProcessor();
    
    void Init(const InputCollections& input,VariableContainer& var);
    void Process(const InputCollections& input,VariableContainer& var);
    
    void InitHiggsCandidateVars(VariableContainer& vars);
    void InitTopHadCandidateVars(VariableContainer& vars);
    void InitTopLepCandidateVars(VariableContainer& vars);
    void InitAk5JetsVars(VariableContainer& vars);
    void InitCombinationVars(VariableContainer& vars);
    void InitMCVars(VariableContainer& vars);
    void InitAk4JetsVars(VariableContainer& vars);
    
    void FillHiggsCandidateVars(VariableContainer& vars, BoostedttHEvent& ttHevent);
    void FillTopHadCandidateVars(VariableContainer& vars, BoostedttHEvent& ttHevent);
    void FillTopLepCandidateVars(VariableContainer& vars,BoostedttHEvent& ttHevent);
    void FillAk5JetsVars(VariableContainer& vars,BoostedttHEvent& ttHevent);
    void FillCombinationVars(VariableContainer& vars,BoostedttHEvent& ttHevent);
    void FillMCVars(VariableContainer& vars,BoostedttHEvent& ttHevent,const InputCollections& input);
  void FillAk4JetsVars(VariableContainer& vars,BoostedttHEvent& ttHEvent,const InputCollections& input);

  private:
  
    BoostedRecoType recotype;
    std::string   prefix;
    const char* btagger;
      
    TopTagger     toptagger;
    HiggsTagger   higgstagger;

    BoostedttHEvent ttHEvent;
};

#endif
