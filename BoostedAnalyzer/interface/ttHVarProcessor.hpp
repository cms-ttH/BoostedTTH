#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TTHVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TTHVARPROCESSOR_HPP

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"
#include "MiniAOD/MiniAODHelper/interface/HiggsTagger.h"

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedttHEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

#include "TTH/CommonClassifier/interface/MEMClassifier.h"

enum BoostedRecoType {BoostedTop,BoostedTopHiggs,BoostedHiggs,BoostedTopAk4Higgs,BoostedTopAk4HiggsFromAk4C};


class ttHVarProcessor: public TreeProcessor{

  public:

    ttHVarProcessor(BoostedRecoType recotype_, MiniAODHelper* helper_, TopTag::Mode topTaggerMode_, TopTag::SubjetAssign subjetAssign_, std::string topTaggerfilePath_, const boosted::SubjetType subjettype_, HiggsTag::Mode higgsTaggerMode_, std::string higgsTaggerFilePath_, std::string prefix="",bool doMEM=true);
    ~ttHVarProcessor();

    void Init(const InputCollections& input,VariableContainer& var);
    void Process(const InputCollections& input,VariableContainer& var);

    void InitHiggsCandidateVars(VariableContainer& vars);
    void InitTopHadCandidateVars(VariableContainer& vars);
    void InitTopLepCandidateVars(VariableContainer& vars);
    void InitAk5JetsVars(VariableContainer& vars);
    void InitCombinationVars(VariableContainer& vars);
    void InitMCVars(VariableContainer& vars);
    //void InitMEMVars(VariableContainer& vars);
    void InitHiggsCandidateAk4Vars(VariableContainer& vars);
    void InitTopHadCandidateAk4Vars(VariableContainer& vars);
    void InitTopLepCandidateAk4Vars(VariableContainer& vars);

    void FillHiggsCandidateVars(VariableContainer& vars, BoostedttHEvent& ttHevent);
    void FillTopHadCandidateVars(VariableContainer& vars, BoostedttHEvent& ttHevent);
    void FillTopLepCandidateVars(VariableContainer& vars,BoostedttHEvent& ttHevent);
    void FillHiggsCandidateAk4Vars(VariableContainer& vars, BoostedttHEvent& ttHevent);
    void FillTopHadCandidateAk4Vars(VariableContainer& vars, BoostedttHEvent& ttHevent);
    void FillTopLepCandidateAk4Vars(VariableContainer& vars,BoostedttHEvent& ttHevent);
    void FillAk5JetsVars(VariableContainer& vars,BoostedttHEvent& ttHevent);
    void FillCombinationVars(VariableContainer& vars,BoostedttHEvent& ttHevent);
    void FillMCVars(VariableContainer& vars,BoostedttHEvent& ttHevent,const InputCollections& input);
    //void FillMEMVars(VariableContainer& vars, BoostedttHEvent& ttHEvent, const InputCollections& input);

  private:

    BoostedRecoType     recotype;
    std::string         prefix;
    const char*         btagger;

    TopTagger           toptagger;
    boosted::SubjetType subjettype;
    HiggsTagger         higgstagger;

    BoostedttHEvent     ttHEvent;

    MEMClassifier       mem;
    bool                doMEM;
};

#endif
