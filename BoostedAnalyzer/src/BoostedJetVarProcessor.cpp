#include "BoostedTTH/BoostedAnalyzer/interface/BoostedJetVarProcessor.hpp"

using namespace std;

BoostedJetVarProcessor::BoostedJetVarProcessor(MiniAODHelper* helper_):btagger("DeepJet"){
  toptagger.insert(map< string, TopTagger >::value_type("HEP", TopTagger(TopTag::HEP,TopTag::Pt,"")));
  toptagger.insert(map< string, TopTagger >::value_type("HEPCSV", TopTagger(TopTag::HEP,TopTag::CSV,"")));
  toptagger.insert(map< string, TopTagger >::value_type("Likelihood", TopTagger(TopTag::Likelihood,TopTag::CSV,"toplikelihoodtaggerhistos.root")));
  toptagger.insert(map< string, TopTagger >::value_type("BDT_Std", TopTagger(TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml")));
  toptagger.insert(map< string, TopTagger >::value_type("BDT_PSO", TopTagger(TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_PSO.weights.xml")));

  higgstagger.insert(map< string, HiggsTagger >::value_type("SecondCSV", HiggsTagger(HiggsTag::SecondCSV,"")));
  higgstagger.insert(map< string, HiggsTagger >::value_type("DoubleCSV", HiggsTagger(HiggsTag::DoubleCSV,"")));
}


BoostedJetVarProcessor::~BoostedJetVarProcessor(){
}


void BoostedJetVarProcessor::Init(const InputCollections& input,VariableContainer& vars){

  InitFatJetVars(vars);
  InitHTTJetVars(vars);
  InitTopTagVars(vars);
  InitSFJetVars(vars);
  InitPrunedJetVars(vars);
  InitSDJetVars(vars);
  InitHiggsTagVars(vars);

  initialized=true;
}

void BoostedJetVarProcessor::InitFatJetVars(VariableContainer& vars){

  vars.InitVar( "N_BoostedJets","I" );

  vars.InitVars( "BoostedJet_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_M",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Dr_Lepton",-9,"N_BoostedJets" );
}


void BoostedJetVarProcessor::InitHTTJetVars(VariableContainer& vars){

  vars.InitVars( "BoostedJet_B_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B_Charge",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_W1_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W1_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W1_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W1_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W1_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W1_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W1_Flav",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_W2_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2_Flav",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_W_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W_M",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Top_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Top_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Top_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Top_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Top_M",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_BW1_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_BW2_M",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_M12",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_M13",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_M23",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Dr_B_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_W1_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_W2_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_W_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_W_B",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_W1_B",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_W2_B",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_W1_W",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_W2_W",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_W1_W2",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_ERatio_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_B",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_W1",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_W2",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_W",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_B_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_W1_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_W2_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_W_Top",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_PtRatio_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_B",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_W1",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_W2",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_W",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_B_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_W1_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_W2_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_W_Top",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_MRatio_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_B",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_W1",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_W2",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_W",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_B_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_W1_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_W2_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_W_Top",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_FatJet_Mass",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_FatJet_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_FatJet_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_FatJet_Phi",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_TopMass",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_UnfilteredMass",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PrunedMass",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_fRec",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MassRatioPassed",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Ropt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_RoptCalc",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtForRoptCalc",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Tau1Unfiltered",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Tau2Unfiltered",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Tau3Unfiltered",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Tau1Filtered",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Tau2Filtered",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Tau3Filtered",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_QWeight",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_QEpsilon",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_QSigmaM",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_W1_IdxAk5",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2_IdxAk5",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B_IdxAk5",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Bbtag_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Bbtag_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Bbtag_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Bbtag_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Bbtag_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Bbtag_M",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_W1btag_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W1btag_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W1btag_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W1btag_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W1btag_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W1btag_M",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_W2btag_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2btag_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2btag_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2btag_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2btag_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2btag_M",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Wbtag_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Wbtag_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Wbtag_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Wbtag_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Wbtag_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Wbtag_M",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_BW1btag_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_BW2btag_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Bbtag_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W1btag_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_W2btag_Flav",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_ERatio_Bbtag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_W1btag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_W2btag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_Wbtag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_Bbtag_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_W1btag_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_W2btag_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_ERatio_Wbtag_Top",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_PtRatio_Bbtag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_W1btag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_W2btag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_Wbtag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_Bbtag_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_W1btag_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_W2btag_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_PtRatio_Wbtag_Top",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_MRatio_Bbtag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_W1btag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_W2btag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_Wbtag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_Bbtag_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_W1btag_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_W2btag_Top",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_MRatio_Wbtag_Top",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Dr_W1btag_Bbtag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_W2btag_Bbtag",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_W1btag_W2btag",-9,"N_BoostedJets" );
}


void BoostedJetVarProcessor::InitTopTagVars(VariableContainer& vars){
  vars.InitVars( "BoostedJet_TopTag_HEP",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_TopTag_HEPCSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_TopTag_Likelihood",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_TopTag_BDT_Std",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_TopTag_BDT_PSO",-9,"N_BoostedJets" );
}


void BoostedJetVarProcessor::InitSFJetVars(VariableContainer& vars){

  vars.InitVars( "N_BoostedJet_Subjets",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Subjet1_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet1_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet1_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet1_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet1_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet1_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet1_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet1_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet1_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet1_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet1_ERatio",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Subjet2_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet2_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet2_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet2_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet2_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet2_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet2_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet2_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet2_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet2_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet2_ERatio",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Subjet12_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet12_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet12_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet12_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Subjet12_Phi",-9,"N_BoostedJets" );

  vars.InitVars( "N_BoostedJet_Filterjets",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Filterjet1_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet1_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet1_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet1_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet1_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet1_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet1_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet1_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet1_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet1_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet1_ERatio",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Filterjet2_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet2_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet2_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet2_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet2_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet2_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet2_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet2_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet2_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet2_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet2_ERatio",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Filterjet3_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet3_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet3_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet3_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet3_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet3_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet3_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet3_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet3_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet3_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet3_ERatio",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_CSV1",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_CSV2",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_CSV3",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_CSV4",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_B1_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B1_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B1_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B1_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B1_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B1_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B1_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B1_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B1_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B1_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B1_ERatio",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_B2_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B2_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B2_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B2_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B2_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B2_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B2_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B2_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B2_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B2_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_B2_ERatio",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_G_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_G_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_G_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_G_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_G_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_G_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_G_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_G_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_G_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_G_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_G_ERatio",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Dr_Filterjet12",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Filterjet13",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Filterjet23",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_CosThetaStar_Filterjet12",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_CosThetaStar_Filterjet13",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_CosThetaStar_Filterjet23",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_IsGoodTopJet",false,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_IsGoodHiggsJet",false,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Filterjet1_IdxAk5",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet2_IdxAk5",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet3_IdxAk5",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Filterjet12_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet12_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet12_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet12_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet12_Phi",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Filterjet123_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet123_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet123_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet123_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Filterjet123_Phi",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_bb_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_bb_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_bb_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_bb_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_bb_Phi",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_bbg_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_bbg_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_bbg_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_bbg_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_bbg_Phi",-9,"N_BoostedJets" );
}


void BoostedJetVarProcessor::InitPrunedJetVars(VariableContainer& vars){

  vars.InitVars( "N_BoostedJet_Pruned_Subjets",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Pruned_Subjet1_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet2_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet1_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet2_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet1_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet2_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet1_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet2_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet1_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet2_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet1_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet2_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet1_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet2_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet1_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet2_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet1_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet2_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet1_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet2_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet1_ERatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Subjet2_ERatio",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Pruned_CSV1",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_CSV2",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Pruned_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Pruned_Phi",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Dr_Pruned_Subjet12",-9,"N_BoostedJets" );
}


void BoostedJetVarProcessor::InitSDJetVars(VariableContainer& vars){

  vars.InitVars( "N_BoostedJet_SD_Subjets",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_SD_Subjet1_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet2_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet3_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet1_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet2_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet3_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet1_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet2_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet3_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet1_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet2_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet3_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet1_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet2_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet3_Phi",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet1_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet2_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet3_CSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet1_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet2_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet3_Dr",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet1_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet2_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet3_Flav",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet1_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet2_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet3_Charge",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet1_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet2_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet3_PtRatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet1_ERatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet2_ERatio",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Subjet3_ERatio",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_SD_CSV1",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_CSV2",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_CSV3",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_SD_Pt",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_E",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_M",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Eta",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Phi",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_Dr_SD_Subjet12",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_SD_Subjet13",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_SD_Subjet23",-9,"N_BoostedJets" );

  vars.InitVars( "BoostedJet_SD_Tau1",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Tau2",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_SD_Tau3",-9,"N_BoostedJets" );
}


void BoostedJetVarProcessor::InitHiggsTagVars(VariableContainer& vars){
  vars.InitVars( "BoostedJet_HiggsTag_SecondCSV",-9,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_HiggsTag_DoubleCSV",-9,"N_BoostedJets" );
}


void BoostedJetVarProcessor::Process(const InputCollections& input,VariableContainer& vars){

  if(!initialized) cerr << "tree processor not initialized" << endl;

  FillFatJetVars(input,vars);
  FillHTTJetVars(input,vars);
  FillTopTagVars(input,vars);
  FillSFJetVars(input,vars);
  FillPrunedJetVars(input,vars);
  FillSDJetVars(input,vars);
  FillHiggsTagVars(input,vars);
}


void BoostedJetVarProcessor::FillFatJetVars(const InputCollections& input,VariableContainer& vars){

  // Get Objects
  math::XYZTLorentzVector primlepvec=math::XYZTLorentzVector(0.,0.,0.,0.);
  if(input.selectedElectronsLoose.size()>0||input.selectedMuonsLoose.size()>0)
	  primlepvec = BoostedUtils::GetPrimLepVec(input.selectedElectronsLoose,input.selectedMuonsLoose);

  vars.FillVar("N_BoostedJets",input.selectedBoostedJets.size());

  for(size_t i=0; i< input.selectedBoostedJets.size(); i++){

    // Get BoostedJet Objects
    pat::Jet fatjet = input.selectedBoostedJets[i].fatjet;

    vars.FillVars( "BoostedJet_E",i,fatjet.energy() );
    vars.FillVars( "BoostedJet_Pt",i,fatjet.pt() );
    vars.FillVars( "BoostedJet_Eta",i,fatjet.eta() );
    vars.FillVars( "BoostedJet_Phi",i,fatjet.phi() );
    vars.FillVars( "BoostedJet_M",i,fatjet.mass() );

    vars.FillVars("BoostedJet_Dr_Lepton",i,primlepvec.pt()>5 ? BoostedUtils::DeltaR(primlepvec,fatjet.p4()) : -1);
  }
}


void BoostedJetVarProcessor::FillHTTJetVars(const InputCollections& input,VariableContainer& vars){

  for(size_t i=0; i< input.selectedBoostedJets.size(); i++){

    // Get BoostedJet Objects
    pat::Jet fatjet = input.selectedBoostedJets[i].fatjet;
    pat::Jet nonW = input.selectedBoostedJets[i].nonW;
    pat::Jet W1 = input.selectedBoostedJets[i].W1;
    pat::Jet W2 = input.selectedBoostedJets[i].W2;
    const math::XYZTLorentzVector WVec = input.selectedBoostedJets[i].GetWJetVec();
    const math::XYZTLorentzVector topVec = input.selectedBoostedJets[i].GetTopJetVec();

    if(topVec.Pt()<=0.) continue;

    vars.FillVars( "BoostedJet_B_E",i,nonW.energy() );
    vars.FillVars( "BoostedJet_B_Pt",i,nonW.pt() );
    vars.FillVars( "BoostedJet_B_Eta",i,nonW.eta() );
    vars.FillVars( "BoostedJet_B_Phi",i,nonW.phi() );
    vars.FillVars( "BoostedJet_B_M",i,nonW.mass() );
    vars.FillVars( "BoostedJet_B_Flav",i,nonW.partonFlavour() );
    vars.FillVars( "BoostedJet_B_Charge",i,nonW.jetCharge() );

    vars.FillVars( "BoostedJet_W1_E",i,W1.energy() );
    vars.FillVars( "BoostedJet_W1_Pt",i,W1.pt() );
    vars.FillVars( "BoostedJet_W1_Eta",i,W1.eta() );
    vars.FillVars( "BoostedJet_W1_Phi",i,W1.phi() );
    vars.FillVars( "BoostedJet_W1_M",i,W1.mass() );
    vars.FillVars( "BoostedJet_W1_Flav",i,W1.partonFlavour() );

    vars.FillVars( "BoostedJet_W2_E",i,W2.energy() );
    vars.FillVars( "BoostedJet_W2_Pt",i,W2.pt() );
    vars.FillVars( "BoostedJet_W2_Eta",i,W2.eta() );
    vars.FillVars( "BoostedJet_W2_Phi",i,W2.phi() );
    vars.FillVars( "BoostedJet_W2_M",i,W2.mass() );
    vars.FillVars( "BoostedJet_W2_Flav",i,W2.partonFlavour() );

    vars.FillVars( "BoostedJet_W_E",i,WVec.E() );
    vars.FillVars( "BoostedJet_W_Pt",i,WVec.Pt() );
    vars.FillVars( "BoostedJet_W_Eta",i,WVec.Eta() );
    vars.FillVars( "BoostedJet_W_Phi",i,WVec.Phi() );
    vars.FillVars( "BoostedJet_W_M",i,WVec.M() );

    vars.FillVars( "BoostedJet_Top_E",i,topVec.E() );
    vars.FillVars( "BoostedJet_Top_Pt",i,topVec.Pt() );
    vars.FillVars( "BoostedJet_Top_Eta",i,topVec.Eta() );
    vars.FillVars( "BoostedJet_Top_Phi",i,topVec.Phi() );
    vars.FillVars( "BoostedJet_Top_M",i,topVec.M() );

    vars.FillVars( "BoostedJet_BW1_M",i,(nonW.p4()+W1.p4()).M() );
    vars.FillVars( "BoostedJet_BW2_M",i,(nonW.p4()+W2.p4()).M() );

    vars.FillVars( "BoostedJet_Dr_B_Top",i,BoostedUtils::DeltaR(nonW.p4(),topVec) );
    vars.FillVars( "BoostedJet_Dr_W1_Top",i,BoostedUtils::DeltaR(W1.p4(),topVec) );
    vars.FillVars( "BoostedJet_Dr_W2_Top",i,BoostedUtils::DeltaR(W2.p4(),topVec) );
    vars.FillVars( "BoostedJet_Dr_W_Top",i,BoostedUtils::DeltaR(WVec,topVec) );
    vars.FillVars( "BoostedJet_Dr_W_B",i,BoostedUtils::DeltaR(WVec,nonW.p4()) );
    vars.FillVars( "BoostedJet_Dr_W1_B",i,BoostedUtils::DeltaR(W1.p4(),nonW.p4()) );
    vars.FillVars( "BoostedJet_Dr_W2_B",i,BoostedUtils::DeltaR(W2.p4(),nonW.p4()) );
    vars.FillVars( "BoostedJet_Dr_W1_W",i,BoostedUtils::DeltaR(W1.p4(),WVec) );
    vars.FillVars( "BoostedJet_Dr_W2_W",i,BoostedUtils::DeltaR(W2.p4(),WVec) );
    vars.FillVars( "BoostedJet_Dr_W1_W2",i,BoostedUtils::DeltaR(W1.p4(),W2.p4()) );

    vars.FillVars( "BoostedJet_ERatio_Top",i,topVec.E()/fatjet.energy() );
    vars.FillVars( "BoostedJet_ERatio_B",i,nonW.energy()/fatjet.energy() );
    vars.FillVars( "BoostedJet_ERatio_W1",i,W1.energy()/fatjet.energy() );
    vars.FillVars( "BoostedJet_ERatio_W2",i,W2.energy()/fatjet.energy() );
    vars.FillVars( "BoostedJet_ERatio_W",i,WVec.E()/fatjet.energy() );
    vars.FillVars( "BoostedJet_ERatio_B_Top",i,nonW.energy()/topVec.E() );
    vars.FillVars( "BoostedJet_ERatio_W1_Top",i,W1.energy()/topVec.E() );
    vars.FillVars( "BoostedJet_ERatio_W2_Top",i,W2.energy()/topVec.E() );
    vars.FillVars( "BoostedJet_ERatio_W_Top",i,WVec.E()/topVec.E() );

    vars.FillVars( "BoostedJet_PtRatio_Top",i,topVec.Pt()/fatjet.pt() );
    vars.FillVars( "BoostedJet_PtRatio_B",i,nonW.pt()/fatjet.pt() );
    vars.FillVars( "BoostedJet_PtRatio_W1",i,W1.pt()/fatjet.pt() );
    vars.FillVars( "BoostedJet_PtRatio_W2",i,W2.pt()/fatjet.pt() );
    vars.FillVars( "BoostedJet_PtRatio_W",i,WVec.Pt()/fatjet.pt() );
    vars.FillVars( "BoostedJet_PtRatio_B_Top",i,nonW.pt()/topVec.Pt() );
    vars.FillVars( "BoostedJet_PtRatio_W1_Top",i,W1.pt()/topVec.Pt() );
    vars.FillVars( "BoostedJet_PtRatio_W2_Top",i,W2.pt()/topVec.Pt() );
    vars.FillVars( "BoostedJet_PtRatio_W_Top",i,WVec.Pt()/topVec.Pt() );

    vars.FillVars( "BoostedJet_MRatio_Top",i,topVec.M()/fatjet.mass() );
    vars.FillVars( "BoostedJet_MRatio_B",i,nonW.mass()/fatjet.mass() );
    vars.FillVars( "BoostedJet_MRatio_W1",i,W1.mass()/fatjet.mass() );
    vars.FillVars( "BoostedJet_MRatio_W2",i,W2.mass()/fatjet.mass() );
    vars.FillVars( "BoostedJet_MRatio_W",i,WVec.M()/fatjet.mass() );
    vars.FillVars( "BoostedJet_MRatio_B_Top",i,nonW.mass()/topVec.M() );
    vars.FillVars( "BoostedJet_MRatio_W1_Top",i,W1.mass()/topVec.M() );
    vars.FillVars( "BoostedJet_MRatio_W2_Top",i,W2.mass()/topVec.M() );
    vars.FillVars( "BoostedJet_MRatio_W_Top",i,WVec.M()/topVec.M() );

    vector<math::XYZTLorentzVector> topvecs;
    topvecs.push_back(W1.p4());
    topvecs.push_back(W2.p4());
    topvecs.push_back(nonW.p4());
    std::sort(topvecs.begin(), topvecs.end(),BoostedUtils::FirstIsHarder);
    float m12=-99;
    float m23=-99;
    float m13=-99;
    if(topvecs.size()==3){
      m12=(topvecs[0]+topvecs[1]).M();
      m13=(topvecs[0]+topvecs[2]).M();
      m23=(topvecs[1]+topvecs[2]).M();
    }
    vars.FillVars( "BoostedJet_M12",i,m12 );
    vars.FillVars( "BoostedJet_M13",i,m13 );
    vars.FillVars( "BoostedJet_M23",i,m23 );

    vars.FillVars( "BoostedJet_B_CSV",i,MiniAODHelper::GetJetCSV(nonW,btagger) );
    vars.FillVars( "BoostedJet_W1_CSV",i,MiniAODHelper::GetJetCSV(W1,btagger) );
    vars.FillVars( "BoostedJet_W2_CSV",i,MiniAODHelper::GetJetCSV(W2,btagger) );

    //Definition with b-jet == highest CSV
    vector<pat::Jet> subjets;
    subjets.push_back(nonW);
    subjets.push_back(W1);
    subjets.push_back(W2);

    BoostedUtils::TopSubjetCSVDef(subjets);

    vector<math::XYZTLorentzVector> topvecs_bycsv = BoostedUtils::GetJetVecs(subjets);

    vars.FillVars( "BoostedJet_Bbtag_E",i,subjets[0].energy() );
    vars.FillVars( "BoostedJet_Bbtag_Pt",i,subjets[0].pt() );
    vars.FillVars( "BoostedJet_Bbtag_Eta",i,subjets[0].eta() );
    vars.FillVars( "BoostedJet_Bbtag_Phi",i,subjets[0].phi() );

    vars.FillVars( "BoostedJet_W1btag_Phi",i,subjets[1].phi() );
    vars.FillVars( "BoostedJet_W2btag_Phi",i,subjets[2].phi() );
    vars.FillVars( "BoostedJet_Bbtag_E",i,subjets[0].energy() );
    vars.FillVars( "BoostedJet_W1btag_E",i,subjets[1].energy() );
    vars.FillVars( "BoostedJet_W2btag_E",i,subjets[2].energy() );
    vars.FillVars( "BoostedJet_Bbtag_Flav",i,subjets[0].partonFlavour() );
    vars.FillVars( "BoostedJet_W1btag_Flav",i,subjets[1].partonFlavour() );
    vars.FillVars( "BoostedJet_W2btag_Flav",i,subjets[2].partonFlavour() );
    vars.FillVars( "BoostedJet_Bbtag_M",i,subjets[0].mass() );
    vars.FillVars( "BoostedJet_Bbtag_CSV",i,MiniAODHelper::GetJetCSV(subjets[0],btagger) );

    vars.FillVars( "BoostedJet_W1btag_E",i,subjets[1].energy() );
    vars.FillVars( "BoostedJet_W1btag_Pt",i,subjets[1].pt() );
    vars.FillVars( "BoostedJet_W1btag_Eta",i,subjets[1].eta() );
    vars.FillVars( "BoostedJet_W1btag_Phi",i,subjets[1].phi() );
    vars.FillVars( "BoostedJet_W1btag_M",i,subjets[1].mass() );
    vars.FillVars( "BoostedJet_W1btag_CSV",i,MiniAODHelper::GetJetCSV(subjets[1],btagger) );

    vars.FillVars( "BoostedJet_W2btag_E",i,subjets[2].energy() );
    vars.FillVars( "BoostedJet_W2btag_Pt",i,subjets[2].pt() );
    vars.FillVars( "BoostedJet_W2btag_Eta",i,subjets[2].eta() );
    vars.FillVars( "BoostedJet_W2btag_Phi",i,subjets[2].phi() );
    vars.FillVars( "BoostedJet_W2btag_M",i,subjets[2].mass() );
    vars.FillVars( "BoostedJet_W2btag_CSV",i,MiniAODHelper::GetJetCSV(subjets[2],btagger) );

    vars.FillVars( "BoostedJet_Wbtag_E",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).E() );
    vars.FillVars( "BoostedJet_Wbtag_Pt",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).Pt() );
    vars.FillVars( "BoostedJet_Wbtag_Eta",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).Eta() );
    vars.FillVars( "BoostedJet_Wbtag_Phi",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).Phi() );
    vars.FillVars( "BoostedJet_Wbtag_M",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M() );

    vars.FillVars( "BoostedJet_BW1btag_M",i,(topvecs_bycsv[0]+topvecs_bycsv[1]).M() );
    vars.FillVars( "BoostedJet_BW2btag_M",i,(topvecs_bycsv[0]+topvecs_bycsv[2]).M() );

    vars.FillVars( "BoostedJet_Dr_W1btag_Bbtag",i,BoostedUtils::DeltaR(subjets[1],subjets[0]));
    vars.FillVars( "BoostedJet_Dr_W2btag_Bbtag",i,BoostedUtils::DeltaR(subjets[2],subjets[0]));
    vars.FillVars( "BoostedJet_Dr_W1btag_W2btag",i,BoostedUtils::DeltaR(subjets[1],subjets[2]));

    vars.FillVars( "BoostedJet_ERatio_Bbtag",i,subjets[0].energy()/fatjet.energy() );
    vars.FillVars( "BoostedJet_ERatio_W1btag",i,subjets[1].energy()/fatjet.energy() );
    vars.FillVars( "BoostedJet_ERatio_W2btag",i,subjets[2].energy()/fatjet.energy() );
    vars.FillVars( "BoostedJet_ERatio_Wbtag",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).E()/fatjet.energy() );
    vars.FillVars( "BoostedJet_ERatio_Bbtag_Top",i,subjets[0].energy()/topVec.E() );
    vars.FillVars( "BoostedJet_ERatio_W1btag_Top",i,subjets[1].energy()/topVec.E() );
    vars.FillVars( "BoostedJet_ERatio_W2btag_Top",i,subjets[2].energy()/topVec.E() );
    vars.FillVars( "BoostedJet_ERatio_Wbtag_Top",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).E()/topVec.E() );

    vars.FillVars( "BoostedJet_PtRatio_Bbtag",i,subjets[0].pt()/fatjet.pt() );
    vars.FillVars( "BoostedJet_PtRatio_W1btag",i,subjets[1].pt()/fatjet.pt() );
    vars.FillVars( "BoostedJet_PtRatio_W2btag",i,subjets[2].pt()/fatjet.pt() );
    vars.FillVars( "BoostedJet_PtRatio_Wbtag",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).pt()/fatjet.pt() );
    vars.FillVars( "BoostedJet_PtRatio_Bbtag_Top",i,subjets[0].pt()/topVec.Pt() );
    vars.FillVars( "BoostedJet_PtRatio_W1btag_Top",i,subjets[1].pt()/topVec.Pt() );
    vars.FillVars( "BoostedJet_PtRatio_W2btag_Top",i,subjets[2].pt()/topVec.Pt() );
    vars.FillVars( "BoostedJet_PtRatio_Wbtag_Top",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).pt()/topVec.Pt() );

    vars.FillVars( "BoostedJet_MRatio_Bbtag",i,subjets[0].mass()/fatjet.mass() );
    vars.FillVars( "BoostedJet_MRatio_W1btag",i,subjets[1].mass()/fatjet.mass() );
    vars.FillVars( "BoostedJet_MRatio_W2btag",i,subjets[2].mass()/fatjet.mass() );
    vars.FillVars( "BoostedJet_MRatio_Wbtag",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M()/fatjet.mass() );
    vars.FillVars( "BoostedJet_MRatio_Bbtag_Top",i,subjets[0].mass()/topVec.M() );
    vars.FillVars( "BoostedJet_MRatio_W1btag_Top",i,subjets[1].mass()/topVec.M() );
    vars.FillVars( "BoostedJet_MRatio_W2btag_Top",i,subjets[2].mass()/topVec.M() );
    vars.FillVars( "BoostedJet_MRatio_Wbtag_Top",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M()/topVec.M() );

    vars.FillVars( "BoostedJet_FatJet_Mass",i,input.selectedBoostedJets[i].fatjetMass );
    vars.FillVars( "BoostedJet_FatJet_Pt",i,input.selectedBoostedJets[i].fatjetPt );
    vars.FillVars( "BoostedJet_FatJet_Eta",i,input.selectedBoostedJets[i].fatjetEta );
    vars.FillVars( "BoostedJet_FatJet_Phi",i,input.selectedBoostedJets[i].fatjetPhi );

    vars.FillVars( "BoostedJet_TopMass",i,input.selectedBoostedJets[i].topMass );
    vars.FillVars( "BoostedJet_UnfilteredMass",i,input.selectedBoostedJets[i].unfilteredMass );
    vars.FillVars( "BoostedJet_PrunedMass",i,input.selectedBoostedJets[i].prunedMass );
    vars.FillVars( "BoostedJet_fRec",i,input.selectedBoostedJets[i].fRec );
    vars.FillVars( "BoostedJet_MassRatioPassed",i,input.selectedBoostedJets[i].massRatioPassed );

    vars.FillVars( "BoostedJet_Ropt",i,input.selectedBoostedJets[i].Ropt );
    vars.FillVars( "BoostedJet_RoptCalc",i,input.selectedBoostedJets[i].RoptCalc );
    vars.FillVars( "BoostedJet_PtForRoptCalc",i,input.selectedBoostedJets[i].ptForRoptCalc );

    vars.FillVars( "BoostedJet_Tau1Unfiltered",i,input.selectedBoostedJets[i].tau1Unfiltered );
    vars.FillVars( "BoostedJet_Tau2Unfiltered",i,input.selectedBoostedJets[i].tau2Unfiltered );
    vars.FillVars( "BoostedJet_Tau3Unfiltered",i,input.selectedBoostedJets[i].tau3Unfiltered );
    vars.FillVars( "BoostedJet_Tau1Filtered",i,input.selectedBoostedJets[i].tau1Filtered );
    vars.FillVars( "BoostedJet_Tau2Filtered",i,input.selectedBoostedJets[i].tau2Filtered );
    vars.FillVars( "BoostedJet_Tau3Filtered",i,input.selectedBoostedJets[i].tau3Filtered );

    vars.FillVars( "BoostedJet_QWeight",i,input.selectedBoostedJets[i].qWeight );
    vars.FillVars( "BoostedJet_QEpsilon",i,input.selectedBoostedJets[i].qEpsilon );
    vars.FillVars( "BoostedJet_QSigmaM",i,input.selectedBoostedJets[i].qSigmaM );

    vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);
    math::XYZTLorentzVector w1vec = W1.p4();
    math::XYZTLorentzVector w2vec = W2.p4();
    math::XYZTLorentzVector bvec = nonW.p4();

    int idxW1=-1;
    int idxW2=-1;
    int idxB=-1;
    for(size_t j=0; j<jetvecs.size()&&bvec.pt()>0;j++){
      if(BoostedUtils::DeltaR(jetvecs[j],bvec)<0.2){
	      idxB = j;
	      break;
      }
    }
    for(size_t j=0; j<jetvecs.size()&&w1vec.pt()>0;j++){
      if(((int)j)!=idxB && BoostedUtils::DeltaR(jetvecs[j],w1vec)<0.2){
	      idxW1 = j;
	      break;
      }
    }
    for(size_t j=0; j<jetvecs.size()&&w2vec.pt()>0;j++){
      if(((int)j)!=idxB && ((int)j)!=idxW1 && BoostedUtils::DeltaR(jetvecs[j],w2vec)<0.2){
	      idxW2 = j;
	      break;
      }
    }

    vars.FillVars( "BoostedJet_W1_IdxAk5",i,idxW1 );
    vars.FillVars( "BoostedJet_W2_IdxAk5",i,idxW2 );
    vars.FillVars( "BoostedJet_B_IdxAk5",i,idxB );
  }
}


void BoostedJetVarProcessor::FillTopTagVars(const InputCollections& input,VariableContainer& vars){

  for(size_t i=0; i< input.selectedBoostedJets.size(); i++){
    vars.FillVars( "BoostedJet_TopTag_HEP",i,toptagger.at("HEP").GetTopTaggerOutput(input.selectedBoostedJets[i]) );
    vars.FillVars( "BoostedJet_TopTag_HEPCSV",i,toptagger.at("HEPCSV").GetTopTaggerOutput(input.selectedBoostedJets[i]) );
    vars.FillVars( "BoostedJet_TopTag_Likelihood",i,toptagger.at("Likelihood").GetTopTaggerOutput(input.selectedBoostedJets[i]) );
    vars.FillVars( "BoostedJet_TopTag_BDT_Std",i,toptagger.at("BDT_Std").GetTopTaggerOutput(input.selectedBoostedJets[i]) );
    vars.FillVars( "BoostedJet_TopTag_BDT_PSO",i,toptagger.at("BDT_PSO").GetTopTaggerOutput(input.selectedBoostedJets[i]) );
  }
}


void BoostedJetVarProcessor::FillSFJetVars(const InputCollections& input,VariableContainer& vars){

  for(size_t i=0; i< input.selectedBoostedJets.size(); i++){

    vars.FillVars( "N_BoostedJet_Subjets",i,input.selectedBoostedJets[i].subjets.size() );

    for(std::vector<pat::Jet>::const_iterator itSub = input.selectedBoostedJets[i].subjets.begin(); itSub != input.selectedBoostedJets[i].subjets.end() && itSub-input.selectedBoostedJets[i].subjets.begin()<2; ++itSub){
      TString subjetName = "Subjet";
      subjetName += ((itSub-input.selectedBoostedJets[i].subjets.begin())+1);

      vars.FillVars( "BoostedJet_"+subjetName+"_E",i,itSub->energy() );
      vars.FillVars( "BoostedJet_"+subjetName+"_Pt",i,itSub->pt() );
      vars.FillVars( "BoostedJet_"+subjetName+"_M",i,itSub->mass() );
      vars.FillVars( "BoostedJet_"+subjetName+"_Eta",i,itSub->eta() );
      vars.FillVars( "BoostedJet_"+subjetName+"_Phi",i,itSub->phi() );
      vars.FillVars( "BoostedJet_"+subjetName+"_CSV",i,MiniAODHelper::GetJetCSV(*itSub,btagger) );
      vars.FillVars( "BoostedJet_"+subjetName+"_Dr",i,BoostedUtils::DeltaR(*itSub,input.selectedBoostedJets[i].fatjet) );
      vars.FillVars( "BoostedJet_"+subjetName+"_Flav",i,itSub->partonFlavour() );
      vars.FillVars( "BoostedJet_"+subjetName+"_Charge",i,itSub->jetCharge() );
      vars.FillVars( "BoostedJet_"+subjetName+"_PtRatio",i,itSub->pt()/input.selectedBoostedJets[i].fatjet.pt() );
      vars.FillVars( "BoostedJet_"+subjetName+"_ERatio",i,itSub->energy()/input.selectedBoostedJets[i].fatjet.energy() );
    }

    if(input.selectedBoostedJets[i].subjets.size()>1){
      math::XYZTLorentzVector subjet12 = input.selectedBoostedJets[i].subjets[0].p4()+input.selectedBoostedJets[i].subjets[1].p4();
      vars.FillVars( "BoostedJet_Subjet12_E",i,subjet12.E() );
      vars.FillVars( "BoostedJet_Subjet12_Pt",i,subjet12.Pt() );
      vars.FillVars( "BoostedJet_Subjet12_M",i,subjet12.M() );
      vars.FillVars( "BoostedJet_Subjet12_Eta",i,subjet12.Eta() );
      vars.FillVars( "BoostedJet_Subjet12_Phi",i,subjet12.Phi() );
    }

    vars.FillVars( "N_BoostedJet_Filterjets",i,input.selectedBoostedJets[i].filterjets.size() );

    for(std::vector<pat::Jet>::const_iterator itSub = input.selectedBoostedJets[i].filterjets.begin(); itSub != input.selectedBoostedJets[i].filterjets.end() && itSub-input.selectedBoostedJets[i].filterjets.begin()<3; ++itSub){

      TString subjetName = "Filterjet";
      subjetName += ((itSub-input.selectedBoostedJets[i].filterjets.begin())+1);

      vars.FillVars( "BoostedJet_"+subjetName+"_E",i,itSub->energy() );
      vars.FillVars( "BoostedJet_"+subjetName+"_Pt",i,itSub->pt() );
      vars.FillVars( "BoostedJet_"+subjetName+"_M",i,itSub->mass() );
      vars.FillVars( "BoostedJet_"+subjetName+"_Eta",i,itSub->eta() );
      vars.FillVars( "BoostedJet_"+subjetName+"_Phi",i,itSub->phi() );
      vars.FillVars( "BoostedJet_"+subjetName+"_CSV",i,MiniAODHelper::GetJetCSV(*itSub,btagger) );
      vars.FillVars( "BoostedJet_"+subjetName+"_Dr",i,BoostedUtils::DeltaR(*itSub,input.selectedBoostedJets[i].fatjet) );
      vars.FillVars( "BoostedJet_"+subjetName+"_Flav",i,itSub->partonFlavour() );
      vars.FillVars( "BoostedJet_"+subjetName+"_Charge",i,itSub->jetCharge() );
      vars.FillVars( "BoostedJet_"+subjetName+"_PtRatio",i,itSub->pt()/input.selectedBoostedJets[i].fatjet.pt() );
      vars.FillVars( "BoostedJet_"+subjetName+"_ERatio",i,itSub->energy()/input.selectedBoostedJets[i].fatjet.energy() );
    }

    if(input.selectedBoostedJets[i].filterjets.size()>1){
      math::XYZTLorentzVector filterjet12 = input.selectedBoostedJets[i].filterjets[0].p4()+input.selectedBoostedJets[i].filterjets[1].p4();
      vars.FillVars( "BoostedJet_Filterjet12_E",i,filterjet12.E() );
      vars.FillVars( "BoostedJet_Filterjet12_Pt",i,filterjet12.Pt() );
      vars.FillVars( "BoostedJet_Filterjet12_M",i,filterjet12.M() );
      vars.FillVars( "BoostedJet_Filterjet12_Eta",i,filterjet12.Eta() );
      vars.FillVars( "BoostedJet_Filterjet12_Phi",i,filterjet12.Phi() );

      vars.FillVars( "BoostedJet_Dr_Filterjet12",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[0],input.selectedBoostedJets[i].filterjets[1]) );
      vars.FillVars( "BoostedJet_CosThetaStar_Filterjet12",i,BoostedUtils::CosThetaStar(input.selectedBoostedJets[i].filterjets[0].p4(),input.selectedBoostedJets[i].filterjets[1].p4()) );
    }

    if(input.selectedBoostedJets[i].filterjets.size()>2){
      math::XYZTLorentzVector filterjet123 = input.selectedBoostedJets[i].filterjets[0].p4()+input.selectedBoostedJets[i].filterjets[1].p4()+input.selectedBoostedJets[i].filterjets[2].p4();
      vars.FillVars( "BoostedJet_Filterjet123_E",i,filterjet123.E() );
      vars.FillVars( "BoostedJet_Filterjet123_Pt",i,filterjet123.Pt() );
      vars.FillVars( "BoostedJet_Filterjet123_M",i,filterjet123.M() );
      vars.FillVars( "BoostedJet_Filterjet123_Eta",i,filterjet123.Eta() );
      vars.FillVars( "BoostedJet_Filterjet123_Phi",i,filterjet123.Phi() );

      vars.FillVars( "BoostedJet_Dr_Filterjet23",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[1],input.selectedBoostedJets[i].filterjets[2]) );
      vars.FillVars( "BoostedJet_Dr_Filterjet13",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[0],input.selectedBoostedJets[i].filterjets[2]) );
      vars.FillVars( "BoostedJet_CosThetaStar_Filterjet23",i,BoostedUtils::CosThetaStar(input.selectedBoostedJets[i].filterjets[1].p4(),input.selectedBoostedJets[i].filterjets[2].p4()) );
      vars.FillVars( "BoostedJet_CosThetaStar_Filterjet13",i,BoostedUtils::CosThetaStar(input.selectedBoostedJets[i].filterjets[0].p4(),input.selectedBoostedJets[i].filterjets[2].p4()) );
    }

    vars.FillVars( "BoostedJet_IsGoodTopJet", i, input.selectedBoostedJets[i].isGoodTopJet);
    vars.FillVars( "BoostedJet_IsGoodHiggsJet", i, input.selectedBoostedJets[i].isGoodHiggsJet);

    if(input.selectedBoostedJets[i].filterjets.size()>1){
      vector<pat::Jet> higgsjets = BoostedUtils::GetHiggsFilterJets(input.selectedBoostedJets[i],2,3);

      math::XYZTLorentzVector bbjet = higgsjets.at(0).p4()+higgsjets.at(1).p4();
      vars.FillVars( "BoostedJet_bb_E",i,bbjet.E() );
      vars.FillVars( "BoostedJet_bb_Pt",i,bbjet.Pt() );
      vars.FillVars( "BoostedJet_bb_M",i,bbjet.M() );
      vars.FillVars( "BoostedJet_bb_Eta",i,bbjet.Eta() );
      vars.FillVars( "BoostedJet_bb_Phi",i,bbjet.Phi() );

      math::XYZTLorentzVector bbgjet = bbjet;
      if(higgsjets.size()>2){
        bbgjet += higgsjets.at(2).p4();
      }
      vars.FillVars( "BoostedJet_bbg_E",i,bbgjet.E() );
      vars.FillVars( "BoostedJet_bbg_Pt",i,bbgjet.Pt() );
      vars.FillVars( "BoostedJet_bbg_M",i,bbgjet.M() );
      vars.FillVars( "BoostedJet_bbg_Eta",i,bbgjet.Eta() );
      vars.FillVars( "BoostedJet_bbg_Phi",i,bbgjet.Phi() );

      for(std::vector<pat::Jet>::const_iterator itSub = higgsjets.begin(); itSub != higgsjets.end() && itSub-higgsjets.begin()<3; ++itSub){

        int subjetIndex = itSub-higgsjets.begin();
        TString subjetName = "";

        if(subjetIndex==0)
          subjetName = "B1";
        else if(subjetIndex==1)
          subjetName = "B2";
        else if(subjetIndex==2)
          subjetName = "G";

        vars.FillVars( "BoostedJet_"+subjetName+"_E",i,itSub->energy() );
        vars.FillVars( "BoostedJet_"+subjetName+"_Pt",i,itSub->pt() );
        vars.FillVars( "BoostedJet_"+subjetName+"_M",i,itSub->mass() );
        vars.FillVars( "BoostedJet_"+subjetName+"_Eta",i,itSub->eta() );
        vars.FillVars( "BoostedJet_"+subjetName+"_Phi",i,itSub->phi() );
        vars.FillVars( "BoostedJet_"+subjetName+"_CSV",i,MiniAODHelper::GetJetCSV(*itSub,btagger) );
        vars.FillVars( "BoostedJet_"+subjetName+"_Dr",i,BoostedUtils::DeltaR(*itSub,input.selectedBoostedJets[i].fatjet) );
        vars.FillVars( "BoostedJet_"+subjetName+"_Flav",i,itSub->partonFlavour() );
        vars.FillVars( "BoostedJet_"+subjetName+"_Charge",i,itSub->jetCharge() );
        vars.FillVars( "BoostedJet_"+subjetName+"_PtRatio",i,itSub->pt()/input.selectedBoostedJets[i].fatjet.pt() );
        vars.FillVars( "BoostedJet_"+subjetName+"_ERatio",i,itSub->energy()/input.selectedBoostedJets[i].fatjet.energy() );
      }
    }

    std::vector<pat::Jet> filterJets = BoostedUtils::GetHiggsFilterJets(input.selectedBoostedJets[i],4,-1);
    if(filterJets.size()>0) vars.FillVars( "BoostedJet_CSV1",i,MiniAODHelper::GetJetCSV(filterJets[0],btagger) );
    if(filterJets.size()>1) vars.FillVars( "BoostedJet_CSV2",i,MiniAODHelper::GetJetCSV(filterJets[1],btagger) );
    if(filterJets.size()>2) vars.FillVars( "BoostedJet_CSV3",i,MiniAODHelper::GetJetCSV(filterJets[2],btagger) );
    if(filterJets.size()>3) vars.FillVars( "BoostedJet_CSV4",i,MiniAODHelper::GetJetCSV(filterJets[3],btagger) );

    vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);
    vector<math::XYZTLorentzVector> filtvecs = BoostedUtils::GetJetVecs(input.selectedBoostedJets[i].filterjets);
    int idx1 = -1;
    int idx2 = -1;
    int idx3 = -1;
    for(size_t j=0; j<jetvecs.size()&&filtvecs.size()>0;j++){
      if(BoostedUtils::DeltaR(jetvecs[j],filtvecs[0])<0.2){
	      idx1=j;
	      break;
      }
    }
    for(size_t j=0; j<jetvecs.size()&&filtvecs.size()>1;j++){
      if(idx1!=((int)j) && BoostedUtils::DeltaR(jetvecs[j],filtvecs[1])<0.2){
	      idx2=j;
	      break;
      }
    }
    for(size_t j=0; j<jetvecs.size()&&filtvecs.size()>2;j++){
      if(idx2!=((int)j) && idx1!=((int)j) && BoostedUtils::DeltaR(jetvecs[j],filtvecs[2])<0.2){
	      idx3=j;
	      break;
      }
    }

    vars.FillVars( "BoostedJet_Filterjet1_IdxAk5",i,idx1);
    vars.FillVars( "BoostedJet_Filterjet2_IdxAk5",i,idx2);
    vars.FillVars( "BoostedJet_Filterjet3_IdxAk5",i,idx3);
  }
}


void BoostedJetVarProcessor::FillPrunedJetVars(const InputCollections& input,VariableContainer& vars){

  for(size_t i=0; i< input.selectedBoostedJets.size(); i++){

    std::vector<pat::Jet> subjets = input.selectedBoostedJets.at(i).prunedsubjets;
    std::sort(subjets.begin(), subjets.end(),BoostedUtils::FirstJetIsHarder);

    vars.FillVars( "N_BoostedJet_Pruned_Subjets",i,subjets.size() );

    for(std::vector<pat::Jet>::const_iterator itSub = subjets.begin(); itSub != subjets.end() && itSub-subjets.begin()<2; ++itSub){

      TString SubjetName = "Subjet";
      SubjetName += ((itSub-subjets.begin())+1);

      vars.FillVars( "BoostedJet_Pruned_"+SubjetName+"_E",i,itSub->energy() );
      vars.FillVars( "BoostedJet_Pruned_"+SubjetName+"_Pt",i,itSub->pt() );
      vars.FillVars( "BoostedJet_Pruned_"+SubjetName+"_M",i,itSub->mass() );
      vars.FillVars( "BoostedJet_Pruned_"+SubjetName+"_Eta",i,itSub->eta() );
      vars.FillVars( "BoostedJet_Pruned_"+SubjetName+"_Phi",i,itSub->phi() );
      vars.FillVars( "BoostedJet_Pruned_"+SubjetName+"_CSV",i,MiniAODHelper::GetJetCSV(*itSub,btagger) );
      vars.FillVars( "BoostedJet_Pruned_"+SubjetName+"_Dr",i,BoostedUtils::DeltaR(*itSub,input.selectedBoostedJets[i].fatjet) );
      vars.FillVars( "BoostedJet_Pruned_"+SubjetName+"_Flav",i,itSub->partonFlavour() );
      vars.FillVars( "BoostedJet_Pruned_"+SubjetName+"_Charge",i,itSub->jetCharge() );
      vars.FillVars( "BoostedJet_Pruned_"+SubjetName+"_PtRatio",i,itSub->pt()/input.selectedBoostedJets[i].fatjet.pt() );
      vars.FillVars( "BoostedJet_Pruned_"+SubjetName+"_ERatio",i,itSub->energy()/input.selectedBoostedJets[i].fatjet.energy() );
    }

    if(subjets.size()>1){

      const math::XYZTLorentzVector compVec = subjets[0].p4()+subjets[1].p4();

      vars.FillVars( "BoostedJet_Pruned_Pt",i,compVec.Pt() );
      vars.FillVars( "BoostedJet_Pruned_E",i,compVec.E() );
      vars.FillVars( "BoostedJet_Pruned_M",i,compVec.M() );
      vars.FillVars( "BoostedJet_Pruned_Eta",i,compVec.Eta() );
      vars.FillVars( "BoostedJet_Pruned_Phi",i,compVec.Phi() );

      vars.FillVars( "BoostedJet_Dr_Pruned_Subjet12",i,BoostedUtils::DeltaR(subjets[0],subjets[1]) );
    }

    std::sort(subjets.begin(), subjets.end(),BoostedUtils::FirstHasHigherCSV);

    if(subjets.size()>0) vars.FillVars( "BoostedJet_Pruned_CSV1",i,MiniAODHelper::GetJetCSV(subjets.at(0),btagger) );
    if(subjets.size()>1) vars.FillVars( "BoostedJet_Pruned_CSV2",i,MiniAODHelper::GetJetCSV(subjets.at(1),btagger) );
  }
}


void BoostedJetVarProcessor::FillSDJetVars(const InputCollections& input,VariableContainer& vars){

  for(size_t i=0; i< input.selectedBoostedJets.size(); i++){

    std::vector<pat::Jet> subjets = input.selectedBoostedJets.at(i).sdsubjets;
    std::sort(subjets.begin(), subjets.end(),BoostedUtils::FirstJetIsHarder);

    vars.FillVars( "N_BoostedJet_SD_Subjets",i,subjets.size() );

    for(std::vector<pat::Jet>::const_iterator itSub = subjets.begin(); itSub != subjets.end() && itSub-subjets.begin()<3; ++itSub){

      TString SubjetName = "Subjet";
      SubjetName += ((itSub-subjets.begin())+1);

      vars.FillVars( "BoostedJet_SD_"+SubjetName+"_E",i,itSub->energy() );
      vars.FillVars( "BoostedJet_SD_"+SubjetName+"_Pt",i,itSub->pt() );
      vars.FillVars( "BoostedJet_SD_"+SubjetName+"_M",i,itSub->mass() );
      vars.FillVars( "BoostedJet_SD_"+SubjetName+"_Eta",i,itSub->eta() );
      vars.FillVars( "BoostedJet_SD_"+SubjetName+"_Phi",i,itSub->phi() );
      vars.FillVars( "BoostedJet_SD_"+SubjetName+"_CSV",i,MiniAODHelper::GetJetCSV(*itSub,btagger) );
      vars.FillVars( "BoostedJet_SD_"+SubjetName+"_Dr",i,BoostedUtils::DeltaR(*itSub,input.selectedBoostedJets[i].fatjet) );
      vars.FillVars( "BoostedJet_SD_"+SubjetName+"_Flav",i,itSub->partonFlavour() );
      vars.FillVars( "BoostedJet_SD_"+SubjetName+"_Charge",i,itSub->jetCharge() );
      vars.FillVars( "BoostedJet_SD_"+SubjetName+"_PtRatio",i,itSub->pt()/input.selectedBoostedJets[i].fatjet.pt() );
      vars.FillVars( "BoostedJet_SD_"+SubjetName+"_ERatio",i,itSub->energy()/input.selectedBoostedJets[i].fatjet.energy() );
    }

    if(subjets.size()>1){

      const math::XYZTLorentzVector compVec = subjets[0].p4()+subjets[1].p4();

      vars.FillVars( "BoostedJet_SD_Pt",i,compVec.Pt() );
      vars.FillVars( "BoostedJet_SD_E",i,compVec.E() );
      vars.FillVars( "BoostedJet_SD_M",i,compVec.M() );
      vars.FillVars( "BoostedJet_SD_Eta",i,compVec.Eta() );
      vars.FillVars( "BoostedJet_SD_Phi",i,compVec.Phi() );

      vars.FillVars( "BoostedJet_Dr_SD_Subjet12",i,BoostedUtils::DeltaR(subjets[0],subjets[1]) );
      if(subjets.size() > 2) {
        vars.FillVars( "BoostedJet_Dr_SD_Subjet13",i,BoostedUtils::DeltaR(subjets[0],subjets[2]) );
        vars.FillVars( "BoostedJet_Dr_SD_Subjet23",i,BoostedUtils::DeltaR(subjets[1],subjets[2]) );
      }
    }

    std::sort(subjets.begin(), subjets.end(),BoostedUtils::FirstHasHigherCSV);

    if(subjets.size()>0) vars.FillVars( "BoostedJet_SD_CSV1",i,MiniAODHelper::GetJetCSV(subjets.at(0),btagger) );
    if(subjets.size()>1) vars.FillVars( "BoostedJet_SD_CSV2",i,MiniAODHelper::GetJetCSV(subjets.at(1),btagger) );
    if(subjets.size()>2) vars.FillVars( "BoostedJet_SD_CSV3",i,MiniAODHelper::GetJetCSV(subjets.at(2),btagger) );

    vars.FillVars( "BoostedJet_SD_Tau1",i,input.selectedBoostedJets.at(i).tau1Softdrop );
    vars.FillVars( "BoostedJet_SD_Tau2",i,input.selectedBoostedJets.at(i).tau2Softdrop );
    vars.FillVars( "BoostedJet_SD_Tau3",i,input.selectedBoostedJets.at(i).tau3Softdrop );
  }
}


void BoostedJetVarProcessor::FillHiggsTagVars(const InputCollections& input,VariableContainer& vars){

  for(size_t i=0; i< input.selectedBoostedJets.size(); i++){
    vars.FillVars( "BoostedJet_HiggsTag_SecondCSV",i,higgstagger.at("SecondCSV").GetHiggsTaggerOutput(input.selectedBoostedJets[i]) );
    vars.FillVars( "BoostedJet_HiggsTag_DoubleCSV",i,higgstagger.at("DoubleCSV").GetHiggsTaggerOutput(input.selectedBoostedJets[i]) );
  }
}
