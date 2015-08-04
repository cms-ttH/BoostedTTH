#include "BoostedTTH/BoostedAnalyzer/interface/BoostedJetVarProcessor.hpp"

using namespace std;

BoostedJetVarProcessor::BoostedJetVarProcessor(MiniAODHelper* helper_):btagger("pfCombinedInclusiveSecondaryVertexV2BJetTags"){
  
  toptagger["HEP"] = TopTagger(helper_,TopTag::HEP,TopTag::Pt,"");
  toptagger["HEPCSV"] = TopTagger(helper_,TopTag::HEP,TopTag::CSV,"");
  toptagger["Likelihood"] = TopTagger(helper_,TopTag::Likelihood,TopTag::CSV,"toplikelihoodtaggerhistos.root");
  toptagger["BDT"] = TopTagger(helper_,TopTag::TMVA,TopTag::CSV,"BDTTopTagger_BDTG_Std.weights.xml");
  
  higgstagger["SecondCSV"] = HiggsTagger(helper_,HiggsTag::SecondCSV,"");
}


BoostedJetVarProcessor::~BoostedJetVarProcessor(){
}


void BoostedJetVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
  
  vars.InitVar( "N_TopJets","I" );
  
  vars.InitVars( "TopJet_E",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Pt",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Eta",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Phi",-9,"N_TopJets" );
  vars.InitVars( "TopJet_M",-9,"N_TopJets" );

  vars.InitVars( "TopJet_B_E",-9,"N_TopJets" );
  vars.InitVars( "TopJet_B_Pt",-9,"N_TopJets" );
  vars.InitVars( "TopJet_B_Eta",-9,"N_TopJets" );
  vars.InitVars( "TopJet_B_Phi",-9,"N_TopJets" );
  vars.InitVars( "TopJet_B_M",-9,"N_TopJets" );
  vars.InitVars( "TopJet_B_CSV",-9,"N_TopJets" );
  vars.InitVars( "TopJet_B_Flav",-9,"N_TopJets" );
  vars.InitVars( "TopJet_B_Charge",-9,"N_TopJets" );
  
  vars.InitVars( "TopJet_W1_E",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W1_Pt",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W1_Eta",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W1_Phi",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W1_M",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W1_CSV",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W1_Flav",-9,"N_TopJets" );
  
  vars.InitVars( "TopJet_W2_E",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2_Pt",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2_Eta",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2_Phi",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2_M",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2_CSV",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2_Flav",-9,"N_TopJets" );
  
  vars.InitVars( "TopJet_W_E",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W_Pt",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W_Eta",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W_Phi",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W_M",-9,"N_TopJets" );
  
  vars.InitVars( "TopJet_Top_E",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Top_Pt",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Top_Eta",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Top_Phi",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Top_M",-9,"N_TopJets" );
  
  vars.InitVars( "TopJet_BW1_M",-9,"N_TopJets" );
  vars.InitVars( "TopJet_BW2_M",-9,"N_TopJets" );

  vars.InitVars( "TopJet_M12",-9,"N_TopJets" );
  vars.InitVars( "TopJet_M13",-9,"N_TopJets" );
  vars.InitVars( "TopJet_M23",-9,"N_TopJets" );

  vars.InitVars( "TopJet_Dr_B_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_W1_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_W2_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_W_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_W_B",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_W1_B",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_W2_B",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_W1_W",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_W2_W",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_W1_W2",-9,"N_TopJets" );

  vars.InitVars( "TopJet_ERatio_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_B",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W1",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W2",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_B_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W1_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W2_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W_Top",-9,"N_TopJets" );

  vars.InitVars( "TopJet_PtRatio_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_B",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W1",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W2",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_B_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W1_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W2_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W_Top",-9,"N_TopJets" );

  vars.InitVars( "TopJet_MRatio_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_B",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W1",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W2",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_B_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W1_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W2_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W_Top",-9,"N_TopJets" );

  vars.InitVars( "TopJet_FatJet_Mass",-9,"N_TopJets" );
  vars.InitVars( "TopJet_FatJet_Pt",-9,"N_TopJets" );
  vars.InitVars( "TopJet_FatJet_Eta",-9,"N_TopJets" );
  vars.InitVars( "TopJet_FatJet_Phi",-9,"N_TopJets" );

  vars.InitVars( "TopJet_TopMass",-9,"N_TopJets" );
  vars.InitVars( "TopJet_UnfilteredMass",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PrunedMass",-9,"N_TopJets" );
  vars.InitVars( "TopJet_fRec",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MassRatioPassed",-9,"N_TopJets" );

  vars.InitVars( "TopJet_Ropt",-9,"N_TopJets" );
  vars.InitVars( "TopJet_RoptCalc",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtForRoptCalc",-9,"N_TopJets" );

  vars.InitVars( "TopJet_Tau1Unfiltered",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Tau2Unfiltered",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Tau3Unfiltered",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Tau1Filtered",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Tau2Filtered",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Tau3Filtered",-9,"N_TopJets" );

  vars.InitVars( "TopJet_QWeight",-9,"N_TopJets" );
  vars.InitVars( "TopJet_QEpsilon",-9,"N_TopJets" );
  vars.InitVars( "TopJet_QSigmaM",-9,"N_TopJets" );
    
  vars.InitVars( "TopJet_W1_IdxAk5",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2_IdxAk5",-9,"N_TopJets" );
  vars.InitVars( "TopJet_B_IdxAk5",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_Lepton",-9,"N_TopJets" );
  vars.InitVars( "TopJet_TaggedB",-9,"N_TopJets" );
  
  vars.InitVars( "TopJet_Bbtag_E",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Bbtag_Pt",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Bbtag_Eta",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Bbtag_Phi",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Bbtag_CSV",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Bbtag_M",-9,"N_TopJets" );
  
  vars.InitVars( "TopJet_W1btag_E",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W1btag_Pt",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W1btag_Eta",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W1btag_Phi",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W1btag_CSV",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W1btag_M",-9,"N_TopJets" );
  
  vars.InitVars( "TopJet_W2btag_E",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2btag_Pt",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2btag_Eta",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2btag_Phi",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2btag_CSV",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2btag_M",-9,"N_TopJets" );
  
  vars.InitVars( "TopJet_Wbtag_E",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Wbtag_Pt",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Wbtag_Eta",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Wbtag_Phi",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Wbtag_CSV",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Wbtag_M",-9,"N_TopJets" );
  
  vars.InitVars( "TopJet_BW1btag_M",-9,"N_TopJets" );
  vars.InitVars( "TopJet_BW2btag_M",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Bbtag_Flav",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W1btag_Flav",-9,"N_TopJets" );
  vars.InitVars( "TopJet_W2btag_Flav",-9,"N_TopJets" );

  vars.InitVars( "TopJet_ERatio_Bbtag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W1btag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W2btag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_Wbtag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_Bbtag_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W1btag_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W2btag_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_ERatio_Wbtag_Top",-9,"N_TopJets" );

  vars.InitVars( "TopJet_PtRatio_Bbtag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W1btag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W2btag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_Wbtag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_Bbtag_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W1btag_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W2btag_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_Wbtag_Top",-9,"N_TopJets" );

  vars.InitVars( "TopJet_MRatio_Bbtag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W1btag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W2btag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_Wbtag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_Bbtag_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W1btag_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W2btag_Top",-9,"N_TopJets" );
  vars.InitVars( "TopJet_MRatio_Wbtag_Top",-9,"N_TopJets" );

  vars.InitVars( "TopJet_Dr_W1btag_Bbtag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_W2btag_Bbtag",-9,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_W1btag_W2btag",-9,"N_TopJets" );
  
  vars.InitVars( "TopJet_TopTag_HEP",-9,"N_TopJets" );
  vars.InitVars( "TopJet_TopTag_HEPCSV",-9,"N_TopJets" );
  vars.InitVars( "TopJet_TopTag_Likelihood",-9,"N_TopJets" );
  vars.InitVars( "TopJet_TopTag_BDT",-9,"N_TopJets" );
  
  vars.InitVar( "N_HiggsJets","I" );

  vars.InitVars( "HiggsJet_Pt",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Eta",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Phi",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_CSV1",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_CSV2",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_CSV3",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_CSV4",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_M2",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_M3",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_M2_SingleTag",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_M3_SingleTag",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_M2_DoubleTag",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_M3_DoubleTag",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Pt2",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Pt3",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_TopJet1",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_TopJet2",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_TopJet3",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_TopJet4",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Subjetiness1",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Subjetiness2",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Subjetiness3",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Subjetiness4",-9,"N_HiggsJets" );
  
  vars.InitVars( "HiggsJet_Filterjet1_Pt",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Pt",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Pt",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Pt",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_E",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_E",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_E",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_E",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_M",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_M",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_M",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_M",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Eta",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Eta",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Eta",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Eta",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Phi",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Phi",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Phi",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Phi",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_CSV",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_CSV",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_CSV",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_CSV",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Dr",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Dr",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Dr",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Dr",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Flav",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Flav",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Flav",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Flav",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Charge",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Charge",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Charge",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Charge",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_PtRatio",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_PtRatio",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_PtRatio",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_PtRatio",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_ERatio",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_ERatio",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_ERatio",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_ERatio",-9,"N_HiggsJets" );
  
  vars.InitVars( "HiggsJet_Dr_Filterjet12",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Filterjet13",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Filterjet23",-9,"N_HiggsJets" );
  
  vars.InitVars( "HiggsJet_Filterjet1_E_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Pt_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Eta_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Phi_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_E_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Pt_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Eta_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Phi_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_E_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Pt_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Eta_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Phi_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_E_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Pt_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Eta_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Phi_RestFrame",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_CosThetaStar_Filterjet12",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_CosThetaStar_Filterjet13",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_CosThetaStar_Filterjet23",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_IdxAk5",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_IdxAk5",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_IdxAk5",-9,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Lepton",-9,"N_HiggsJets" );
  
  vars.InitVars( "HiggsJet_HiggsTag_SecondCSV",-9,"N_HiggsJets" );

  vars.InitVar( "N_MJDCA12_L",-9,"I" );
  vars.InitVars( "CA12MFJ_L_E",-9,"N_MJDCA12_L" );
  vars.InitVars( "CA12MFJ_L_Pt",-9,"N_MJDCA12_L" );
  vars.InitVars( "CA12MFJ_L_Eta",-9,"N_MJDCA12_L" );
  vars.InitVars( "CA12MFJ_L_Phi",-9,"N_MJDCA12_L" );
  vars.InitVars( "CA12MFJ_L_DCSV",-9,"N_MJDCA12_L" );
  vars.InitVars( "CA12MFJ_L_Dr",-9,"N_MJDCA12_L" );

  vars.InitVar( "N_MJDCA12_T",-9,"I" );
  vars.InitVars( "CA12MFJ_T_E",-9,"N_MJDCA12_T" );
  vars.InitVars( "CA12MFJ_T_Pt",-9,"N_MJDCA12_T" );
  vars.InitVars( "CA12MFJ_T_Eta",-9,"N_MJDCA12_T" );
  vars.InitVars( "CA12MFJ_T_Phi",-9,"N_MJDCA12_T" );
  vars.InitVars( "CA12MFJ_T_DCSV",-9,"N_MJDCA12_T" );
  vars.InitVars( "CA12MFJ_T_Dr",-9,"N_MJDCA12_T" );

  vars.InitVar( "N_MJDCA15_L",-9,"I" );
  vars.InitVars( "CA15MFJ_L_E",-9,"N_MJDCA15_L" );
  vars.InitVars( "CA15MFJ_L_Pt",-9,"N_MJDCA15_L" );
  vars.InitVars( "CA15MFJ_L_Eta",-9,"N_MJDCA15_L" );
  vars.InitVars( "CA15MFJ_L_Phi",-9,"N_MJDCA15_L" );
  vars.InitVars( "CA15MFJ_L_DCSV",-9,"N_MJDCA15_L" );
  vars.InitVars( "CA15MFJ_L_Dr",-9,"N_MJDCA15_L" );

  vars.InitVar( "N_MJDCA15_T",-9,"I" );
  vars.InitVars( "CA15MFJ_T_E",-9,"N_MJDCA15_T" );
  vars.InitVars( "CA15MFJ_T_Pt",-9,"N_MJDCA15_T" );
  vars.InitVars( "CA15MFJ_T_Eta",-9,"N_MJDCA15_T" );
  vars.InitVars( "CA15MFJ_T_Phi",-9,"N_MJDCA15_T" );
  vars.InitVars( "CA15MFJ_T_DCSV",-9,"N_MJDCA15_T" );
  vars.InitVars( "CA15MFJ_T_Dr",-9,"N_MJDCA15_T" );


  initialized=true;
}


void BoostedJetVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  
  if(!initialized) cerr << "tree processor not initialized" << endl;

  vars.FillVar("N_TopJets",input.selectedHTTTopJets.size());
  for(size_t i=0; i< input.selectedHTTTopJets.size(); i++){
    
    pat::Jet fatjet = input.selectedHTTTopJets[i].fatjet;
    pat::Jet nonW = input.selectedHTTTopJets[i].nonW;
    pat::Jet W1 = input.selectedHTTTopJets[i].W1;
    pat::Jet W2 = input.selectedHTTTopJets[i].W2;
    const math::XYZTLorentzVector WVec = input.selectedHTTTopJets[i].GetWJetVec();
    const math::XYZTLorentzVector topVec = input.selectedHTTTopJets[i].GetTopJetVec();
    
    vars.FillVars( "TopJet_E",i,fatjet.energy() );
    vars.FillVars( "TopJet_Pt",i,fatjet.pt() );
    vars.FillVars( "TopJet_Eta",i,fatjet.eta() );
    vars.FillVars( "TopJet_Phi",i,fatjet.phi() );
    vars.FillVars( "TopJet_M",i,fatjet.mass() );
    
    if(topVec.Pt()>0.){
      vars.FillVars( "TopJet_B_E",i,nonW.energy() );
      vars.FillVars( "TopJet_B_Pt",i,nonW.pt() );
      vars.FillVars( "TopJet_B_Eta",i,nonW.eta() );
      vars.FillVars( "TopJet_B_Phi",i,nonW.phi() );
      vars.FillVars( "TopJet_B_M",i,nonW.mass() );
      vars.FillVars( "TopJet_B_Flav",i,nonW.partonFlavour() );
      vars.FillVars( "TopJet_B_Charge",i,nonW.jetCharge() );

      vars.FillVars( "TopJet_W1_E",i,W1.energy() );
      vars.FillVars( "TopJet_W1_Pt",i,W1.pt() );
      vars.FillVars( "TopJet_W1_Eta",i,W1.eta() );
      vars.FillVars( "TopJet_W1_Phi",i,W1.phi() );
      vars.FillVars( "TopJet_W1_M",i,W1.mass() );
      vars.FillVars( "TopJet_W1_Flav",i,W1.partonFlavour() );

      vars.FillVars( "TopJet_W2_E",i,W2.energy() );
      vars.FillVars( "TopJet_W2_Pt",i,W2.pt() );
      vars.FillVars( "TopJet_W2_Eta",i,W2.eta() );
      vars.FillVars( "TopJet_W2_Phi",i,W2.phi() );
      vars.FillVars( "TopJet_W2_M",i,W2.mass() );
      vars.FillVars( "TopJet_W2_Flav",i,W2.partonFlavour() );

      vars.FillVars( "TopJet_W_E",i,WVec.E() );
      vars.FillVars( "TopJet_W_Pt",i,WVec.Pt() );
      vars.FillVars( "TopJet_W_Eta",i,WVec.Eta() );
      vars.FillVars( "TopJet_W_Phi",i,WVec.Phi() );
      vars.FillVars( "TopJet_W_M",i,WVec.M() );

      vars.FillVars( "TopJet_Top_E",i,topVec.E() );
      vars.FillVars( "TopJet_Top_Pt",i,topVec.Pt() );
      vars.FillVars( "TopJet_Top_Eta",i,topVec.Eta() );
      vars.FillVars( "TopJet_Top_Phi",i,topVec.Phi() );
      vars.FillVars( "TopJet_Top_M",i,topVec.M() );

      vars.FillVars( "TopJet_BW1_M",i,(nonW.p4()+W1.p4()).M() );
      vars.FillVars( "TopJet_BW2_M",i,(nonW.p4()+W2.p4()).M() );
         
      vars.FillVars( "TopJet_Dr_B_Top",i,BoostedUtils::DeltaR(nonW.p4(),topVec) );
      vars.FillVars( "TopJet_Dr_W1_Top",i,BoostedUtils::DeltaR(W1.p4(),topVec) );
      vars.FillVars( "TopJet_Dr_W2_Top",i,BoostedUtils::DeltaR(W2.p4(),topVec) );
      vars.FillVars( "TopJet_Dr_W_Top",i,BoostedUtils::DeltaR(WVec,topVec) );
      vars.FillVars( "TopJet_Dr_W_B",i,BoostedUtils::DeltaR(WVec,nonW.p4()) );
      vars.FillVars( "TopJet_Dr_W1_B",i,BoostedUtils::DeltaR(W1.p4(),nonW.p4()) );
      vars.FillVars( "TopJet_Dr_W2_B",i,BoostedUtils::DeltaR(W2.p4(),nonW.p4()) );
      vars.FillVars( "TopJet_Dr_W1_W",i,BoostedUtils::DeltaR(W1.p4(),WVec) );
      vars.FillVars( "TopJet_Dr_W2_W",i,BoostedUtils::DeltaR(W2.p4(),WVec) );
      vars.FillVars( "TopJet_Dr_W1_W2",i,BoostedUtils::DeltaR(W1.p4(),W2.p4()) );
    
      vars.FillVars( "TopJet_ERatio_Top",i,topVec.E()/fatjet.energy() );
      vars.FillVars( "TopJet_ERatio_B",i,nonW.energy()/fatjet.energy() );
      vars.FillVars( "TopJet_ERatio_W1",i,W1.energy()/fatjet.energy() );
      vars.FillVars( "TopJet_ERatio_W2",i,W2.energy()/fatjet.energy() );
      vars.FillVars( "TopJet_ERatio_W",i,WVec.E()/fatjet.energy() );
      vars.FillVars( "TopJet_ERatio_B_Top",i,nonW.energy()/topVec.E() );
      vars.FillVars( "TopJet_ERatio_W1_Top",i,W1.energy()/topVec.E() );
      vars.FillVars( "TopJet_ERatio_W2_Top",i,W2.energy()/topVec.E() );
      vars.FillVars( "TopJet_ERatio_W_Top",i,WVec.E()/topVec.E() );

      vars.FillVars( "TopJet_PtRatio_Top",i,topVec.Pt()/fatjet.pt() );
      vars.FillVars( "TopJet_PtRatio_B",i,nonW.pt()/fatjet.pt() );
      vars.FillVars( "TopJet_PtRatio_W1",i,W1.pt()/fatjet.pt() );
      vars.FillVars( "TopJet_PtRatio_W2",i,W2.pt()/fatjet.pt() );
      vars.FillVars( "TopJet_PtRatio_W",i,WVec.Pt()/fatjet.pt() );
      vars.FillVars( "TopJet_PtRatio_B_Top",i,nonW.pt()/topVec.Pt() );
      vars.FillVars( "TopJet_PtRatio_W1_Top",i,W1.pt()/topVec.Pt() );
      vars.FillVars( "TopJet_PtRatio_W2_Top",i,W2.pt()/topVec.Pt() );
      vars.FillVars( "TopJet_PtRatio_W_Top",i,WVec.Pt()/topVec.Pt() );

      vars.FillVars( "TopJet_MRatio_Top",i,topVec.M()/fatjet.mass() );
      vars.FillVars( "TopJet_MRatio_B",i,nonW.mass()/fatjet.mass() );
      vars.FillVars( "TopJet_MRatio_W1",i,W1.mass()/fatjet.mass() );
      vars.FillVars( "TopJet_MRatio_W2",i,W2.mass()/fatjet.mass() );
      vars.FillVars( "TopJet_MRatio_W",i,WVec.M()/fatjet.mass() );
      vars.FillVars( "TopJet_MRatio_B_Top",i,nonW.mass()/topVec.M() );
      vars.FillVars( "TopJet_MRatio_W1_Top",i,W1.mass()/topVec.M() );
      vars.FillVars( "TopJet_MRatio_W2_Top",i,W2.mass()/topVec.M() );
      vars.FillVars( "TopJet_MRatio_W_Top",i,WVec.M()/topVec.M() );

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
      vars.FillVars( "TopJet_M12",i,m12 );
      vars.FillVars( "TopJet_M13",i,m13 );
      vars.FillVars( "TopJet_M23",i,m23 );

      vars.FillVars( "TopJet_B_CSV",i,BoostedUtils::GetJetCSV(nonW,btagger) );
      vars.FillVars( "TopJet_W1_CSV",i,BoostedUtils::GetJetCSV(W1,btagger) );
      vars.FillVars( "TopJet_W2_CSV",i,BoostedUtils::GetJetCSV(W2,btagger) );

      //Definition with b-jet == highest CSV
      vector<pat::Jet> subjets;
      subjets.push_back(nonW);
      subjets.push_back(W1);
      subjets.push_back(W2);

      BoostedUtils::TopSubjetCSVDef(subjets);

      vector<math::XYZTLorentzVector> topvecs_bycsv = BoostedUtils::GetJetVecs(subjets);
      vars.FillVars( "TopJet_TaggedB",i,BoostedUtils::GetTopTag(input.selectedHTTTopJets[i],0.2,120,true) );

      vars.FillVars( "TopJet_Bbtag_E",i,subjets[0].energy() );
      vars.FillVars( "TopJet_Bbtag_Pt",i,subjets[0].pt() );
      vars.FillVars( "TopJet_Bbtag_Eta",i,subjets[0].eta() );
      vars.FillVars( "TopJet_Bbtag_Phi",i,subjets[0].phi() );

      vars.FillVars( "TopJet_W1btag_Phi",i,subjets[1].phi() );
      vars.FillVars( "TopJet_W2btag_Phi",i,subjets[2].phi() );
      vars.FillVars( "TopJet_Bbtag_E",i,subjets[0].energy() );
      vars.FillVars( "TopJet_W1btag_E",i,subjets[1].energy() );
      vars.FillVars( "TopJet_W2btag_E",i,subjets[2].energy() );
      vars.FillVars( "TopJet_Bbtag_Flav",i,subjets[0].partonFlavour() );
      vars.FillVars( "TopJet_W1btag_Flav",i,subjets[1].partonFlavour() );
      vars.FillVars( "TopJet_W2btag_Flav",i,subjets[2].partonFlavour() );
      vars.FillVars( "TopJet_Bbtag_M",i,subjets[0].mass() );
      vars.FillVars( "TopJet_Bbtag_CSV",i,BoostedUtils::GetJetCSV(subjets[0],btagger) );

      vars.FillVars( "TopJet_W1btag_E",i,subjets[1].energy() );
      vars.FillVars( "TopJet_W1btag_Pt",i,subjets[1].pt() );
      vars.FillVars( "TopJet_W1btag_Eta",i,subjets[1].eta() );
      vars.FillVars( "TopJet_W1btag_Phi",i,subjets[1].phi() );
      vars.FillVars( "TopJet_W1btag_M",i,subjets[1].mass() );
      vars.FillVars( "TopJet_W1btag_CSV",i,BoostedUtils::GetJetCSV(subjets[1],btagger) );

      vars.FillVars( "TopJet_W2btag_E",i,subjets[2].energy() );
      vars.FillVars( "TopJet_W2btag_Pt",i,subjets[2].pt() );
      vars.FillVars( "TopJet_W2btag_Eta",i,subjets[2].eta() );
      vars.FillVars( "TopJet_W2btag_Phi",i,subjets[2].phi() );
      vars.FillVars( "TopJet_W2btag_M",i,subjets[2].mass() );
      vars.FillVars( "TopJet_W2btag_CSV",i,BoostedUtils::GetJetCSV(subjets[2],btagger) );

      vars.FillVars( "TopJet_Wbtag_E",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).E() );
      vars.FillVars( "TopJet_Wbtag_Pt",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).Pt() );
      vars.FillVars( "TopJet_Wbtag_Eta",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).Eta() );
      vars.FillVars( "TopJet_Wbtag_Phi",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).Phi() );
      vars.FillVars( "TopJet_Wbtag_M",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M() );

      vars.FillVars( "TopJet_BW1btag_M",i,(topvecs_bycsv[0]+topvecs_bycsv[1]).M() );
      vars.FillVars( "TopJet_BW2btag_M",i,(topvecs_bycsv[0]+topvecs_bycsv[2]).M() );

      vars.FillVars( "TopJet_Dr_W1btag_Bbtag",i,BoostedUtils::DeltaR(subjets[1],subjets[0]));
      vars.FillVars( "TopJet_Dr_W2btag_Bbtag",i,BoostedUtils::DeltaR(subjets[2],subjets[0]));
      vars.FillVars( "TopJet_Dr_W1btag_W2btag",i,BoostedUtils::DeltaR(subjets[1],subjets[2]));

      vars.FillVars( "TopJet_ERatio_Bbtag",i,subjets[0].energy()/fatjet.energy() );
      vars.FillVars( "TopJet_ERatio_W1btag",i,subjets[1].energy()/fatjet.energy() );
      vars.FillVars( "TopJet_ERatio_W2btag",i,subjets[2].energy()/fatjet.energy() );
      vars.FillVars( "TopJet_ERatio_Wbtag",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).E()/fatjet.energy() );
      vars.FillVars( "TopJet_ERatio_Bbtag_Top",i,subjets[0].energy()/topVec.E() );
      vars.FillVars( "TopJet_ERatio_W1btag_Top",i,subjets[1].energy()/topVec.E() );
      vars.FillVars( "TopJet_ERatio_W2btag_Top",i,subjets[2].energy()/topVec.E() );
      vars.FillVars( "TopJet_ERatio_Wbtag_Top",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).E()/topVec.E() );

      vars.FillVars( "TopJet_PtRatio_Bbtag",i,subjets[0].pt()/fatjet.pt() );
      vars.FillVars( "TopJet_PtRatio_W1btag",i,subjets[1].pt()/fatjet.pt() );
      vars.FillVars( "TopJet_PtRatio_W2btag",i,subjets[2].pt()/fatjet.pt() );
      vars.FillVars( "TopJet_PtRatio_Wbtag",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).pt()/fatjet.pt() );
      vars.FillVars( "TopJet_PtRatio_Bbtag_Top",i,subjets[0].pt()/topVec.Pt() );
      vars.FillVars( "TopJet_PtRatio_W1btag_Top",i,subjets[1].pt()/topVec.Pt() );
      vars.FillVars( "TopJet_PtRatio_W2btag_Top",i,subjets[2].pt()/topVec.Pt() );
      vars.FillVars( "TopJet_PtRatio_Wbtag_Top",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).pt()/topVec.Pt() );

      vars.FillVars( "TopJet_MRatio_Bbtag",i,subjets[0].mass()/fatjet.mass() );
      vars.FillVars( "TopJet_MRatio_W1btag",i,subjets[1].mass()/fatjet.mass() );
      vars.FillVars( "TopJet_MRatio_W2btag",i,subjets[2].mass()/fatjet.mass() );
      vars.FillVars( "TopJet_MRatio_Wbtag",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M()/fatjet.mass() );
      vars.FillVars( "TopJet_MRatio_Bbtag_Top",i,subjets[0].mass()/topVec.M() );
      vars.FillVars( "TopJet_MRatio_W1btag_Top",i,subjets[1].mass()/topVec.M() );
      vars.FillVars( "TopJet_MRatio_W2btag_Top",i,subjets[2].mass()/topVec.M() );
      vars.FillVars( "TopJet_MRatio_Wbtag_Top",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M()/topVec.M() );

      vars.FillVars( "TopJet_FatJet_Mass",i,input.selectedHTTTopJets[i].fatjetMass );
      vars.FillVars( "TopJet_FatJet_Pt",i,input.selectedHTTTopJets[i].fatjetPt );
      vars.FillVars( "TopJet_FatJet_Eta",i,input.selectedHTTTopJets[i].fatjetEta );
      vars.FillVars( "TopJet_FatJet_Phi",i,input.selectedHTTTopJets[i].fatjetPhi );

      vars.FillVars( "TopJet_TopMass",i,input.selectedHTTTopJets[i].topMass );
      vars.FillVars( "TopJet_UnfilteredMass",i,input.selectedHTTTopJets[i].unfilteredMass );
      vars.FillVars( "TopJet_PrunedMass",i,input.selectedHTTTopJets[i].prunedMass );
      vars.FillVars( "TopJet_fRec",i,input.selectedHTTTopJets[i].fRec );
      vars.FillVars( "TopJet_MassRatioPassed",i,input.selectedHTTTopJets[i].massRatioPassed );

      vars.FillVars( "TopJet_Ropt",i,input.selectedHTTTopJets[i].Ropt );
      vars.FillVars( "TopJet_RoptCalc",i,input.selectedHTTTopJets[i].RoptCalc );
      vars.FillVars( "TopJet_PtForRoptCalc",i,input.selectedHTTTopJets[i].ptForRoptCalc );

      vars.FillVars( "TopJet_Tau1Unfiltered",i,input.selectedHTTTopJets[i].tau1Unfiltered );
      vars.FillVars( "TopJet_Tau2Unfiltered",i,input.selectedHTTTopJets[i].tau2Unfiltered );
      vars.FillVars( "TopJet_Tau3Unfiltered",i,input.selectedHTTTopJets[i].tau3Unfiltered );
      vars.FillVars( "TopJet_Tau1Filtered",i,input.selectedHTTTopJets[i].tau1Filtered );
      vars.FillVars( "TopJet_Tau2Filtered",i,input.selectedHTTTopJets[i].tau2Filtered );
      vars.FillVars( "TopJet_Tau3Filtered",i,input.selectedHTTTopJets[i].tau3Filtered );

      vars.FillVars( "TopJet_QWeight",i,input.selectedHTTTopJets[i].qWeight );
      vars.FillVars( "TopJet_QEpsilon",i,input.selectedHTTTopJets[i].qEpsilon );
      vars.FillVars( "TopJet_QSigmaM",i,input.selectedHTTTopJets[i].qSigmaM );

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


      vars.FillVars( "TopJet_W1_IdxAk5",i,idxW1 );
      vars.FillVars( "TopJet_W2_IdxAk5",i,idxW2 );
      vars.FillVars( "TopJet_B_IdxAk5",i,idxB );
      
      
    }
      
    math::XYZTLorentzVector primlepvec=math::XYZTLorentzVector(0.,0.,0.,0.);
    if(input.selectedElectronsLoose.size()>0||input.selectedMuonsLoose.size()>0)
	  primlepvec = BoostedUtils::GetPrimLepVec(input.selectedElectronsLoose,input.selectedMuonsLoose);

    vars.FillVars("TopJet_Dr_Lepton",i,primlepvec.pt()>5 ? BoostedUtils::DeltaR(primlepvec,fatjet.p4()) : -1);
    
    vars.FillVars( "TopJet_TopTag_HEP",i,toptagger["HEP"].GetTopTaggerOutput(input.selectedHTTTopJets[i]) );
    vars.FillVars( "TopJet_TopTag_HEPCSV",i,toptagger["HEPCSV"].GetTopTaggerOutput(input.selectedHTTTopJets[i]) );
    vars.FillVars( "TopJet_TopTag_Likelihood",i,toptagger["Likelihood"].GetTopTaggerOutput(input.selectedHTTTopJets[i]) );
    vars.FillVars( "TopJet_TopTag_BDT",i,toptagger["BDT"].GetTopTaggerOutput(input.selectedHTTTopJets[i]) );
  }
  
  
  vars.FillVar( "N_HiggsJets",input.selectedSubFilterJets.size() );
  
  for(size_t i=0; i< input.selectedSubFilterJets.size(); i++){
    vars.FillVars( "HiggsJet_Pt",i,input.selectedSubFilterJets[i].fatjet.pt() );
    vars.FillVars( "HiggsJet_Eta",i,input.selectedSubFilterJets[i].fatjet.eta() );
    vars.FillVars( "HiggsJet_Phi",i,input.selectedSubFilterJets[i].fatjet.phi() );
    
    TVector3 fatJetBoost = -(BoostedUtils::GetTLorentzVector(input.selectedSubFilterJets[i].fatjet.p4()).BoostVector());
    
    for(std::vector<pat::Jet>::const_iterator itFiltJet = input.selectedSubFilterJets[i].filterjets.begin(); itFiltJet != input.selectedSubFilterJets[i].filterjets.end() && itFiltJet-input.selectedSubFilterJets[i].filterjets.begin()<4; ++itFiltJet){
      
      TString FilterJetName = "Filterjet";
      FilterJetName += ((itFiltJet-input.selectedSubFilterJets[i].filterjets.begin())+1);
      
      vars.FillVars( "HiggsJet_"+FilterJetName+"_E",i,itFiltJet->energy() );
      vars.FillVars( "HiggsJet_"+FilterJetName+"_Pt",i,itFiltJet->pt() );
      vars.FillVars( "HiggsJet_"+FilterJetName+"_M",i,itFiltJet->mass() );
      vars.FillVars( "HiggsJet_"+FilterJetName+"_Eta",i,itFiltJet->eta() );
      vars.FillVars( "HiggsJet_"+FilterJetName+"_Phi",i,itFiltJet->phi() );
      vars.FillVars( "HiggsJet_"+FilterJetName+"_CSV",i,BoostedUtils::GetJetCSV(*itFiltJet,btagger) );
      vars.FillVars( "HiggsJet_"+FilterJetName+"_Dr",i,BoostedUtils::DeltaR(*itFiltJet,input.selectedSubFilterJets[i].fatjet) );
      vars.FillVars( "HiggsJet_"+FilterJetName+"_Flav",i,itFiltJet->partonFlavour() );
      vars.FillVars( "HiggsJet_"+FilterJetName+"_Charge",i,itFiltJet->jetCharge() );
      vars.FillVars( "HiggsJet_"+FilterJetName+"_PtRatio",i,itFiltJet->pt()/input.selectedSubFilterJets[i].fatjet.pt() );
      vars.FillVars( "HiggsJet_"+FilterJetName+"_ERatio",i,itFiltJet->energy()/input.selectedSubFilterJets[i].fatjet.energy() );

      TLorentzVector restframeFiltJet = BoostedUtils::GetTLorentzVector(itFiltJet->p4());
      restframeFiltJet.Boost(fatJetBoost);
      vars.FillVars( "HiggsJet_"+FilterJetName+"_Pt_RestFrame",i,restframeFiltJet.Pt());
      vars.FillVars( "HiggsJet_"+FilterJetName+"_Eta_RestFrame",i,restframeFiltJet.Eta());
      vars.FillVars( "HiggsJet_"+FilterJetName+"_Phi_RestFrame",i,restframeFiltJet.Phi()); 
    }
    
    if(input.selectedSubFilterJets[i].filterjets.size()>1){
      vars.FillVars( "HiggsJet_Dr_Filterjet12",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[0],input.selectedSubFilterJets[i].filterjets[1]) );
      vars.FillVars( "HiggsJet_CosThetaStar_Filterjet12",i,BoostedUtils::CosThetaStar(input.selectedSubFilterJets[i].filterjets[0].p4(),input.selectedSubFilterJets[i].filterjets[1].p4()) );
      vars.FillVars( "HiggsJet_M2",i,(input.selectedSubFilterJets[i].filterjets[0].p4()+input.selectedSubFilterJets[i].filterjets[1].p4()).M() );
      vars.FillVars( "HiggsJet_Pt2",i,(input.selectedSubFilterJets[i].filterjets[0].p4()+input.selectedSubFilterJets[i].filterjets[1].p4()).Pt() );
    }
    if(input.selectedSubFilterJets[i].filterjets.size()>2){
      vars.FillVars( "HiggsJet_Dr_Filterjet23",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[1],input.selectedSubFilterJets[i].filterjets[2]) );
      vars.FillVars( "HiggsJet_Dr_Filterjet13",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[0],input.selectedSubFilterJets[i].filterjets[2]) );
      vars.FillVars( "HiggsJet_CosThetaStar_Filterjet23",i,BoostedUtils::CosThetaStar(input.selectedSubFilterJets[i].filterjets[1].p4(),input.selectedSubFilterJets[i].filterjets[2].p4()) );
      vars.FillVars( "HiggsJet_CosThetaStar_Filterjet13",i,BoostedUtils::CosThetaStar(input.selectedSubFilterJets[i].filterjets[0].p4(),input.selectedSubFilterJets[i].filterjets[2].p4()) );
      vars.FillVars( "HiggsJet_M3",i,(input.selectedSubFilterJets[i].filterjets[0].p4()+input.selectedSubFilterJets[i].filterjets[1].p4()+input.selectedSubFilterJets[i].filterjets[2].p4()).M() );
      vars.FillVars( "HiggsJet_Pt3",i,(input.selectedSubFilterJets[i].filterjets[0].p4()+input.selectedSubFilterJets[i].filterjets[1].p4()+input.selectedSubFilterJets[i].filterjets[2].p4()).Pt() );
    }
    
    vars.FillVars( "HiggsJet_M2_SingleTag",i,BoostedUtils::GetHiggsMass(input.selectedSubFilterJets[i], 2, 1, 0.89) );
    vars.FillVars( "HiggsJet_M3_SingleTag",i,BoostedUtils::GetHiggsMass(input.selectedSubFilterJets[i], 3, 1, 0.89) );
    vars.FillVars( "HiggsJet_M2_DoubleTag",i,BoostedUtils::GetHiggsMass(input.selectedSubFilterJets[i], 2, 2, 0.89) );
    vars.FillVars( "HiggsJet_M3_DoubleTag",i,BoostedUtils::GetHiggsMass(input.selectedSubFilterJets[i], 3, 2, 0.89) );
    
    std::vector<pat::Jet> filterJets = BoostedUtils::GetHiggsFilterJets(input.selectedSubFilterJets[i], 4);
    if(filterJets.size()>0) vars.FillVars( "HiggsJet_CSV1",i,BoostedUtils::GetJetCSV(filterJets[0],btagger) );
    if(filterJets.size()>1) vars.FillVars( "HiggsJet_CSV2",i,BoostedUtils::GetJetCSV(filterJets[1],btagger) );
    if(filterJets.size()>2) vars.FillVars( "HiggsJet_CSV3",i,BoostedUtils::GetJetCSV(filterJets[2],btagger) );
    if(filterJets.size()>3) vars.FillVars( "HiggsJet_CSV4",i,BoostedUtils::GetJetCSV(filterJets[3],btagger) );
    
    if(input.selectedHTTTopJets.size()>0) vars.FillVars( "HiggsJet_Dr_TopJet1",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].fatjet,input.selectedHTTTopJets[0].fatjet) );
    if(input.selectedHTTTopJets.size()>1) vars.FillVars( "HiggsJet_Dr_TopJet2",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].fatjet,input.selectedHTTTopJets[1].fatjet) );
    if(input.selectedHTTTopJets.size()>2) vars.FillVars( "HiggsJet_Dr_TopJet3",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].fatjet,input.selectedHTTTopJets[2].fatjet) );
    if(input.selectedHTTTopJets.size()>3) vars.FillVars( "HiggsJet_Dr_TopJet4",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].fatjet,input.selectedHTTTopJets[3].fatjet) );
    
    vars.FillVars( "HiggsJet_Subjetiness1",i,input.selectedSubFilterJets[i].subjettiness1 );
    vars.FillVars( "HiggsJet_Subjetiness2",i,input.selectedSubFilterJets[i].subjettiness2 );
    vars.FillVars( "HiggsJet_Subjetiness3",i,input.selectedSubFilterJets[i].subjettiness3 );
    vars.FillVars( "HiggsJet_Subjetiness4",i,input.selectedSubFilterJets[i].subjettiness4 );
    
    vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);
    vector<math::XYZTLorentzVector> filtvecs = BoostedUtils::GetJetVecs(input.selectedSubFilterJets[i].filterjets);
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
    
    vars.FillVars( "HiggsJet_Filterjet1_IdxAk5",i,idx1);
    vars.FillVars( "HiggsJet_Filterjet2_IdxAk5",i,idx2);
    vars.FillVars( "HiggsJet_Filterjet3_IdxAk5",i,idx3);
    
    math::XYZTLorentzVector primlepvec = math::XYZTLorentzVector();
    if(input.selectedElectronsLoose.size()>0 || input.selectedMuonsLoose.size()>0)
	    primlepvec = BoostedUtils::GetPrimLepVec(input.selectedElectronsLoose,input.selectedMuonsLoose);
    vars.FillVars( "HiggsJet_Dr_Lepton",i,primlepvec.Pt()>5 ? BoostedUtils::DeltaR(primlepvec,input.selectedSubFilterJets[i].fatjet.p4()) : -1);
    
    vars.FillVars( "HiggsJet_HiggsTag_SecondCSV",i,higgstagger["SecondCSV"].GetHiggsTaggerOutput(input.selectedSubFilterJets[i]) );
  }
  
  vector<float> CA12MFJ_L_CSVR;
  vector<float> CA12MFJ_L_Dr;
  std::vector<pat::Jet> CA12filterjets_L = JetMatching::GetFilterjets(input.selectedSubFilterJets);
  vector<TLorentzVector> CA12MFJ_L_p4 = JetMatching::GetMatchedVecs(CA12filterjets_L, input.selectedJets, CA12MFJ_L_CSVR, CA12MFJ_L_Dr);

  vars.FillVar( "N_MJDCA12_L",CA12MFJ_L_p4.size() );
  for(size_t i=0; i<CA12MFJ_L_p4.size();i++)
  {
    vars.FillVars( "CA12MFJ_L_E",i,CA12MFJ_L_p4[i].E() );
    vars.FillVars( "CA12MFJ_L_Pt",i,CA12MFJ_L_p4[i].Pt() );
    vars.FillVars( "CA12MFJ_L_Eta",i,CA12MFJ_L_p4[i].Eta() );
    vars.FillVars( "CA12MFJ_L_Phi",i,CA12MFJ_L_p4[i].Phi() );
    vars.FillVars( "CA12MFJ_L_DCSV",i,CA12MFJ_L_CSVR[i] );
    vars.FillVars( "CA12MFJ_L_Dr",i,CA12MFJ_L_Dr[i] );
  }

  vector<float> CA12MFJ_T_CSVR;
  vector<float> CA12MFJ_T_Dr;
  std::vector<pat::Jet> CA12filterjets_T = JetMatching::GetFilterjets(input.selectedSubFilterJets, 30, 2.41);
  vector<TLorentzVector> CA12MFJ_T_p4 = JetMatching::GetMatchedVecs(CA12filterjets_T, input.selectedJets, CA12MFJ_T_CSVR, CA12MFJ_T_Dr);

  vars.FillVar( "N_MJDCA12_T",CA12MFJ_T_p4.size() );
  for(size_t i=0; i<CA12MFJ_T_p4.size();i++)
  {
    vars.FillVars( "CA12MFJ_T_E",i,CA12MFJ_T_p4[i].E() );
    vars.FillVars( "CA12MFJ_T_Pt",i,CA12MFJ_T_p4[i].Pt() );
    vars.FillVars( "CA12MFJ_T_Eta",i,CA12MFJ_T_p4[i].Eta() );
    vars.FillVars( "CA12MFJ_T_Phi",i,CA12MFJ_T_p4[i].Phi() );
    vars.FillVars( "CA12MFJ_T_DCSV",i,CA12MFJ_T_CSVR[i] );
    vars.FillVars( "CA12MFJ_T_Dr",i,CA12MFJ_T_Dr[i] );
  }

  vector<float> CA15MFJ_L_CSVR;
  vector<float> CA15MFJ_L_Dr;
  std::vector<pat::Jet> CA15filterjets_L = JetMatching::GetFilterjets(input.selectedHTTTopJets);
  vector<TLorentzVector> CA15MFJ_L_p4 = JetMatching::GetMatchedVecs(CA15filterjets_L, input.selectedJets, CA15MFJ_L_CSVR, CA15MFJ_L_Dr);

  vars.FillVar( "N_MJDCA15_L",CA15MFJ_L_p4.size() );
  for(size_t i=0; i<CA15MFJ_L_p4.size();i++)
  {
    vars.FillVars( "CA15MFJ_L_E",i,CA15MFJ_L_p4[i].E() );
    vars.FillVars( "CA15MFJ_L_Pt",i,CA15MFJ_L_p4[i].Pt() );
    vars.FillVars( "CA15MFJ_L_Eta",i,CA15MFJ_L_p4[i].Eta() );
    vars.FillVars( "CA15MFJ_L_Phi",i,CA15MFJ_L_p4[i].Phi() );
    vars.FillVars( "CA15MFJ_L_DCSV",i,CA15MFJ_L_CSVR[i] );
    vars.FillVars( "CA15MFJ_L_Dr",i,CA15MFJ_L_Dr[i] );
  }

  vector<float> CA15MFJ_T_CSVR;
  vector<float> CA15MFJ_T_Dr;
  std::vector<pat::Jet> CA15filterjets_T = JetMatching::GetFilterjets(input.selectedHTTTopJets, 30, 2.41);
  vector<TLorentzVector> CA15MFJ_T_p4 = JetMatching::GetMatchedVecs(CA15filterjets_T, input.selectedJets, CA15MFJ_T_CSVR, CA15MFJ_T_Dr);

  vars.FillVar( "N_MJDCA15_T",CA15MFJ_T_p4.size() );
  for(size_t i=0; i<CA15MFJ_T_p4.size();i++)
  {
    vars.FillVars( "CA15MFJ_T_E",i,CA15MFJ_T_p4[i].E() );
    vars.FillVars( "CA15MFJ_T_Pt",i,CA15MFJ_T_p4[i].Pt() );
    vars.FillVars( "CA15MFJ_T_Eta",i,CA15MFJ_T_p4[i].Eta() );
    vars.FillVars( "CA15MFJ_T_Phi",i,CA15MFJ_T_p4[i].Phi() );
    vars.FillVars( "CA15MFJ_T_DCSV",i,CA15MFJ_T_CSVR[i] );
    vars.FillVars( "CA15MFJ_T_Dr",i,CA15MFJ_T_Dr[i] );
  }
}
