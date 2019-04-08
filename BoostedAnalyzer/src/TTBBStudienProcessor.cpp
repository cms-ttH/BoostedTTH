/** Processor for ttbb studies
 *
 * @author Marco A. Harrendorf
 */

#include "BoostedTTH/BoostedAnalyzer/interface/TTBBStudienProcessor.hpp"

using namespace std;

// all configurations should be done in constructor
TTBBStudienProcessor::TTBBStudienProcessor(){}
TTBBStudienProcessor::~TTBBStudienProcessor(){}


void TTBBStudienProcessor::Init(const InputCollections& input,VariableContainer& vars){

  initTopDR(input, vars);
  initEventType(input, vars);
  initAmountTags(input, vars);

  initialized=true;
}

void TTBBStudienProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl; // complain if not initialized but keep running
  
  processTopDR(input, vars);
  processEventType(input, vars);
  processAmountTags(input, vars);

}

void TTBBStudienProcessor::initTopDR(const InputCollections& input, VariableContainer& vars) {
    vars.InitVar( "N_additionalUntaggedJets", "I" );
    vars.InitVar( "N_additionalTaggedJets", "I" );

    vars.InitVar( "HadTop_LepTop_DR","F" );
    vars.InitVar( "HadTop_LepTop_B_DR","F" );
    vars.InitVar( "HadTop_LepTop_W_DR","F" );
    vars.InitVar( "HadTop_LepTop_W1_DR","F" );
    vars.InitVar( "HadTop_LepTop_W2_DR","F" );
    vars.InitVars( "HadTop_additionalUntaggedJets", "N_additionalUntaggedJets" );
    vars.InitVars( "HadTop_additionalTaggedJets", "N_additionalTaggedJets" );

    vars.InitVar( "HadTop_B_LepTop_DR","F" );
    vars.InitVar( "HadTop_B_LepTop_B_DR","F" );
    vars.InitVar( "HadTop_B_LepTop_W_DR","F" );
    vars.InitVar( "HadTop_B_LepTop_W1_DR","F" );
    vars.InitVar( "HadTop_B_LepTop_W2_DR","F" );
    vars.InitVars( "HadTop_B_additionalUntaggedJets", "N_additionalUntaggedJets" );
    vars.InitVars( "HadTop_B_additionalTaggedJets", "N_additionalTaggedJets" );

    vars.InitVar( "HadTop_W_LepTop_DR","F" );
    vars.InitVar( "HadTop_W_LepTop_B_DR","F" );
    vars.InitVar( "HadTop_W_LepTop_W_DR","F" );
    vars.InitVar( "HadTop_W_LepTop_W1_DR","F" );
    vars.InitVar( "HadTop_W_LepTop_W2_DR","F" );
    vars.InitVars( "HadTop_W_additionalUntaggedJets", "N_additionalUntaggedJets" );
    vars.InitVars( "HadTop_W_additionalTaggedJets", "N_additionalTaggedJets" );

    vars.InitVar( "HadTop_W1_LepTop_DR","F" );
    vars.InitVar( "HadTop_W1_LepTop_B_DR","F" );
    vars.InitVar( "HadTop_W1_LepTop_W_DR","F" );
    vars.InitVar( "HadTop_W1_LepTop_W1_DR","F" );
    vars.InitVar( "HadTop_W1_LepTop_W2_DR","F" );
    vars.InitVars( "HadTop_W1_additionalUntaggedJets", "N_additionalUntaggedJets" );
    vars.InitVars( "HadTop_W1_additionalTaggedJets", "N_additionalTaggedJets" );

    vars.InitVar( "HadTop_W2_LepTop_DR","F" );
    vars.InitVar( "HadTop_W2_LepTop_B_DR","F" );
    vars.InitVar( "HadTop_W2_LepTop_W_DR","F" );
    vars.InitVar( "HadTop_W2_LepTop_W1_DR","F" );
    vars.InitVar( "HadTop_W2_LepTop_W2_DR","F" );
    vars.InitVars( "HadTop_W2_additionalUntaggedJets", "N_additionalUntaggedJets" );
    vars.InitVars( "HadTop_W2_additionalTaggedJets", "N_additionalTaggedJets" );

    vars.InitVars( "LepTop_additionalUntaggedJets", "N_additionalUntaggedJets" );
    vars.InitVars( "LepTop_B_additionalUntaggedJets", "N_additionalUntaggedJets" );
    vars.InitVars( "LepTop_W_additionalUntaggedJets", "N_additionalUntaggedJets" );
    vars.InitVars( "LepTop_W1_additionalUntaggedJets", "N_additionalUntaggedJets" );
    vars.InitVars( "LepTop_W2_additionalUntaggedJets", "N_additionalUntaggedJets" );

    vars.InitVars( "LepTop_additionalTaggedJets", "N_additionalTaggedJets" );
    vars.InitVars( "LepTop_B_additionalTaggedJets", "N_additionalTaggedJets" );
    vars.InitVars( "LepTop_W_additionalTaggedJets", "N_additionalTaggedJets" );
    vars.InitVars( "LepTop_W1_additionalTaggedJets", "N_additionalTaggedJets" );
    vars.InitVars( "LepTop_W2_additionalTaggedJets", "N_additionalTaggedJets" );
}

void TTBBStudienProcessor::processTopDR(const InputCollections& input, VariableContainer& vars) {

    // Group into tagged and untagged jets for hadronic top reconstruction
    std::vector<pat::Jet> selectedTaggedJets;
    std::vector<pat::Jet> selectedUntaggedJets;
    for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet){
        if(CSVHelper::PassesCSV(*itJet, "DeepJet", CSVHelper::CSVwp::Medium,input.era)) selectedTaggedJets.push_back(*itJet);
        else selectedUntaggedJets.push_back(*itJet);
    }

      // W reconstruction for hadronic top
      math::XYZTLorentzVector HadW;
      math::XYZTLorentzVector HadW1;
      math::XYZTLorentzVector HadW2;
      pat::Jet savedW1Jet;
      pat::Jet savedW2Jet;

      // Create vector for additional untagged jets which are not used for the W
      std::vector<pat::Jet> additionalUntaggedJets;
      // Copy contents of selectedUntaggedJets to new vector
      additionalUntaggedJets = selectedUntaggedJets;

      for(std::vector<pat::Jet>::const_iterator it1Jet = selectedUntaggedJets.begin(); it1Jet != selectedUntaggedJets.end(); ++it1Jet){
        for(std::vector<pat::Jet>::const_iterator it2Jet = selectedUntaggedJets.begin(); it2Jet != selectedUntaggedJets.end(); ++it2Jet){
          if(HadW1.M() == 0 || HadW2.M() || abs(80.4-(it1Jet->p4()+it2Jet->p4()).M())<abs(80.4-(HadW1+HadW2).M())){
            HadW1 = it1Jet->p4();
            HadW2 = it2Jet->p4();
            HadW = HadW1+HadW2;
            savedW1Jet = *it1Jet;
            savedW2Jet = *it2Jet;
          }
        }
      }

      // Remove from vector already used jets to keep only additional jets
      additionalUntaggedJets.erase(
        std::remove_if(additionalUntaggedJets.begin(),
                       additionalUntaggedJets.end(),
                       [&savedW1Jet, &savedW2Jet](pat::Jet x){return (x.p4() == savedW1Jet.p4() || x.p4() == savedW2Jet.p4());}),
        additionalUntaggedJets.end()
      );

      // b and top reconstruction in hadronic case
      math::XYZTLorentzVector HadB;
      math::XYZTLorentzVector HadTop;
      pat::Jet savedBJet;

      for(std::vector<pat::Jet>::const_iterator itJet = selectedTaggedJets.begin(); itJet != selectedTaggedJets.end(); ++itJet){
        if(HadTop.M()==0 || abs(172.4-(HadW+itJet->p4()).M())<abs(172.4-HadTop.M())){
          HadB = itJet->p4();
          HadTop = HadB+HadW;
          savedBJet = *itJet;
        }
      }

      // Create vector for additional tagged jets which are not used as b for the top
      std::vector<pat::Jet> additionalTaggedJets;
      // Copy contents of selectedTaggedJets to new vector
      additionalTaggedJets = selectedTaggedJets;

      // Remove from vector already used jets to keep only additional b jets
      additionalTaggedJets.erase(
        std::remove_if(additionalTaggedJets.begin(),
                       additionalTaggedJets.end(),
                       [&savedBJet](pat::Jet x){return (x.p4() == savedBJet.p4());}),
        additionalTaggedJets.end()
      );


      // Select leptons for leptonic top reconstruction
      math::XYZTLorentzVector nu1;
      math::XYZTLorentzVector nu2;
      TVector2 MET;
      MET.Set(input.correctedMET.corP4(pat::MET::Type1XY).px(),input.correctedMET.corP4(pat::MET::Type1XY).py());
      math::XYZTLorentzVector PrimLep = BoostedUtils::GetPrimLepVec(input.selectedElectrons, input.selectedMuons);
      BoostedUtils::GetNuVecs(PrimLep, MET, nu1, nu2);

      // W reconstruction for leptonic top
      math::XYZTLorentzVector LepW;
      math::XYZTLorentzVector LepW1;
      math::XYZTLorentzVector LepW2;

      LepW1 = nu1+PrimLep;
      LepW2 = nu2+PrimLep;
      if(abs(80.4-LepW1.M()) < abs(80.4-LepW2.M())) LepW = LepW1;
      else LepW = LepW2;

      // b and top reconstruction in leptonic case
      math::XYZTLorentzVector LepB;
      math::XYZTLorentzVector LepTop;

      for(std::vector<pat::Jet>::const_iterator itJet = selectedTaggedJets.begin(); itJet != selectedTaggedJets.end(); ++itJet){
        if(LepTop.M()==0 || abs(172.4-(LepW+itJet->p4()).M())<abs(172.4-LepTop.M())){
          LepB = itJet->p4();
          LepTop = LepW+LepB;
        }
      }


      vars.FillVar( "HadTop_LepTop_DR",BoostedUtils::DeltaR(HadTop,LepTop));
      vars.FillVar( "HadTop_LepTop_B_DR",BoostedUtils::DeltaR(HadTop,LepB));
      vars.FillVar( "HadTop_LepTop_W_DR",BoostedUtils::DeltaR(HadTop,LepW));
      vars.FillVar( "HadTop_LepTop_W1_DR",BoostedUtils::DeltaR(HadTop,LepW1));
      vars.FillVar( "HadTop_LepTop_W2_DR",BoostedUtils::DeltaR(HadTop,LepW2));

      vars.FillVar( "HadTop_B_LepTop_DR",BoostedUtils::DeltaR(HadB,LepTop));
      vars.FillVar( "HadTop_B_LepTop_B_DR",BoostedUtils::DeltaR(HadB,LepB));
      vars.FillVar( "HadTop_B_LepTop_W_DR",BoostedUtils::DeltaR(HadB,LepW));
      vars.FillVar( "HadTop_B_LepTop_W1_DR",BoostedUtils::DeltaR(HadB,LepW1));
      vars.FillVar( "HadTop_B_LepTop_W2_DR",BoostedUtils::DeltaR(HadB,LepW2));

      vars.FillVar( "HadTop_W_LepTop_DR",BoostedUtils::DeltaR(HadW,LepTop));
      vars.FillVar( "HadTop_W_LepTop_B_DR",BoostedUtils::DeltaR(HadW,LepB));
      vars.FillVar( "HadTop_W_LepTop_W_DR",BoostedUtils::DeltaR(HadW,LepW));
      vars.FillVar( "HadTop_W_LepTop_W1_DR",BoostedUtils::DeltaR(HadW,LepW1));
      vars.FillVar( "HadTop_W_LepTop_W2_DR",BoostedUtils::DeltaR(HadW,LepW2));

      vars.FillVar( "HadTop_W1_LepTop_DR",BoostedUtils::DeltaR(HadW1,LepTop));
      vars.FillVar( "HadTop_W1_LepTop_B_DR",BoostedUtils::DeltaR(HadW1,LepB));
      vars.FillVar( "HadTop_W1_LepTop_W_DR",BoostedUtils::DeltaR(HadW1,LepW));
      vars.FillVar( "HadTop_W1_LepTop_W1_DR",BoostedUtils::DeltaR(HadW1,LepW1));
      vars.FillVar( "HadTop_W1_LepTop_W2_DR",BoostedUtils::DeltaR(HadW1,LepW2));

      vars.FillVar( "HadTop_W2_LepTop_DR",BoostedUtils::DeltaR(HadW2,LepTop));
      vars.FillVar( "HadTop_W2_LepTop_B_DR",BoostedUtils::DeltaR(HadW2,LepB));
      vars.FillVar( "HadTop_W2_LepTop_W_DR",BoostedUtils::DeltaR(HadW2,LepW));
      vars.FillVar( "HadTop_W2_LepTop_W1_DR",BoostedUtils::DeltaR(HadW2,LepW1));
      vars.FillVar( "HadTop_W2_LepTop_W2_DR",BoostedUtils::DeltaR(HadW2,LepW2));

      // Fill quantities for additionalUntaggedJets and additionalTaggedJets
      vars.FillVar("N_additionalUntaggedJets", additionalUntaggedJets.size());
      vars.FillVar("N_additionalTaggedJets", additionalTaggedJets.size());

      for(std::vector<pat::Jet>::const_iterator itJet = additionalUntaggedJets.begin() ; itJet != additionalUntaggedJets.end(); ++itJet){
          int iJet = itJet - additionalUntaggedJets.begin();
          vars.FillVars("HadTop_additionalUntaggedJets",iJet,BoostedUtils::DeltaR(HadTop,itJet->p4()));
          vars.FillVars("HadTop_B_additionalUntaggedJets",iJet,BoostedUtils::DeltaR(HadB,itJet->p4()));
          vars.FillVars("HadTop_W_additionalUntaggedJets",iJet,BoostedUtils::DeltaR(HadW,itJet->p4()));
          vars.FillVars("HadTop_W1_additionalUntaggedJets",iJet,BoostedUtils::DeltaR(HadW1,itJet->p4()));
          vars.FillVars("HadTop_W2_additionalUntaggedJets",iJet,BoostedUtils::DeltaR(HadW2,itJet->p4()));

          vars.FillVars("LepTop_additionalUntaggedJets",iJet,BoostedUtils::DeltaR(LepTop,itJet->p4()));
          vars.FillVars("LepTop_B_additionalUntaggedJets",iJet,BoostedUtils::DeltaR(LepB,itJet->p4()));
          vars.FillVars("LepTop_W_additionalUntaggedJets",iJet,BoostedUtils::DeltaR(LepW,itJet->p4()));
          vars.FillVars("LepTop_W1_additionalUntaggedJets",iJet,BoostedUtils::DeltaR(LepW1,itJet->p4()));
          vars.FillVars("LepTop_W2_additionalUntaggedJets",iJet,BoostedUtils::DeltaR(LepW2,itJet->p4()));
      }

      for(std::vector<pat::Jet>::const_iterator itJet = additionalTaggedJets.begin() ; itJet != additionalTaggedJets.end(); ++itJet){
          int iJet = itJet - additionalTaggedJets.begin();
          vars.FillVars("HadTop_additionalTaggedJets",iJet,BoostedUtils::DeltaR(HadTop,itJet->p4()));
          vars.FillVars("HadTop_B_additionalTaggedJets",iJet,BoostedUtils::DeltaR(HadB,itJet->p4()));
          vars.FillVars("HadTop_W_additionalTaggedJets",iJet,BoostedUtils::DeltaR(HadW,itJet->p4()));
          vars.FillVars("HadTop_W1_additionalTaggedJets",iJet,BoostedUtils::DeltaR(HadW1,itJet->p4()));
          vars.FillVars("HadTop_W2_additionalTaggedJets",iJet,BoostedUtils::DeltaR(HadW2,itJet->p4()));

          vars.FillVars("LepTop_additionalTaggedJets",iJet,BoostedUtils::DeltaR(LepTop,itJet->p4()));
          vars.FillVars("LepTop_B_additionalTaggedJets",iJet,BoostedUtils::DeltaR(LepB,itJet->p4()));
          vars.FillVars("LepTop_W_additionalTaggedJets",iJet,BoostedUtils::DeltaR(LepW,itJet->p4()));
          vars.FillVars("LepTop_W1_additionalTaggedJets",iJet,BoostedUtils::DeltaR(LepW1,itJet->p4()));
          vars.FillVars("LepTop_W2_additionalTaggedJets",iJet,BoostedUtils::DeltaR(LepW2,itJet->p4()));
      }
}

void TTBBStudienProcessor::initEventType(const InputCollections& input, VariableContainer& vars) {
    vars.InitVar( "TTBB_GenEvt_I_TTPlusCC",-1,"I" );
    vars.InitVar( "TTBB_GenEvt_I_TTPlusBB",-1,"I" );
    vars.InitVar( "TTBB_GenEvt_TTxId_FromProducer",-1,"I" );
}

void TTBBStudienProcessor::processEventType(const InputCollections& input, VariableContainer& vars) {
    int iBB = 0;
    int iCC = 0;

    if(input.sampleType == SampleType::ttbb) iBB = 3;
    if(input.sampleType == SampleType::ttb) iBB = 1;
    if(input.sampleType == SampleType::tt2b) iBB = 2;
    if(input.sampleType == SampleType::ttcc) iCC = 1;

    vars.FillVar( "TTBB_GenEvt_I_TTPlusCC",iCC );
    vars.FillVar( "TTBB_GenEvt_I_TTPlusBB",iBB );
    if(input.genTopEvt.IsFilled()){
      vars.FillVar( "TTBB_GenEvt_TTxId_FromProducer",input.genTopEvt.GetTTxIdFromProducer());
    }
}

void TTBBStudienProcessor::initAmountTags(const InputCollections& input, VariableContainer& vars) {
    vars.InitVar( "N_TotalTags",-1,"I" );
    vars.InitVar( "N_GoodTags",-1,"I" );
    vars.InitVar( "N_MisTags",-1,"I" );
}

void TTBBStudienProcessor::processAmountTags(const InputCollections& input, VariableContainer& vars) {
    int nTotalTags = 0, nGoodTags=0, nMisTags=0;
    for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++){
      if (!(CSVHelper::PassesCSV(*j, "DeepJet", CSVHelper::CSVwp::Medium,input.era))) continue;
      nTotalTags++;
      if(abs(j->hadronFlavour())==5) nGoodTags++;
      if(abs(j->hadronFlavour())!=5) nMisTags++;
    }

    vars.FillVar( "N_TotalTags",nTotalTags);
    vars.FillVar( "N_GoodTags",nGoodTags);
    vars.FillVar( "N_MisTags",nMisTags);
}
