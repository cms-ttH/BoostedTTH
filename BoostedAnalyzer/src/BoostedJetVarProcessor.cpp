#include "BoostedTTH/BoostedAnalyzer/interface/BoostedJetVarProcessor.hpp"

using namespace std;

BoostedJetVarProcessor::BoostedJetVarProcessor ():btagger("combinedSecondaryVertexBJetTags"){
  

}
BoostedJetVarProcessor::~BoostedJetVarProcessor (){}


void BoostedJetVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
  vars.InitVar( "N_TopJets","I" );
  
  vars.InitVars( "TopJet_HEPTopTag","N_TopJets" );
  vars.InitVars( "TopJet_Tag","N_TopJets" );
  
  vars.InitVars( "TopJet_E","N_TopJets" );
  vars.InitVars( "TopJet_Pt","N_TopJets" );
  vars.InitVars( "TopJet_Eta","N_TopJets" );
  vars.InitVars( "TopJet_Phi","N_TopJets" );
  vars.InitVars( "TopJet_M","N_TopJets" );

  vars.InitVars( "TopJet_B_E","N_TopJets" );
  vars.InitVars( "TopJet_B_Pt","N_TopJets" );
  vars.InitVars( "TopJet_B_Eta","N_TopJets" );
  vars.InitVars( "TopJet_B_Phi","N_TopJets" );
  vars.InitVars( "TopJet_B_M","N_TopJets" );
  vars.InitVars( "TopJet_B_Flav","N_TopJets" );
  vars.InitVars( "TopJet_B_Charge","N_TopJets" );
  vars.InitVars( "TopJet_B_CSV","N_TopJets" );
  
  vars.InitVars( "TopJet_W1_E","N_TopJets" );
  vars.InitVars( "TopJet_W1_Pt","N_TopJets" );
  vars.InitVars( "TopJet_W1_Eta","N_TopJets" );
  vars.InitVars( "TopJet_W1_Phi","N_TopJets" );
  vars.InitVars( "TopJet_W1_M","N_TopJets" );
  vars.InitVars( "TopJet_W1_Flav","N_TopJets" );
  vars.InitVars( "TopJet_W1_CSV","N_TopJets" );
  
  vars.InitVars( "TopJet_W2_E","N_TopJets" );
  vars.InitVars( "TopJet_W2_Pt","N_TopJets" );
  vars.InitVars( "TopJet_W2_Eta","N_TopJets" );
  vars.InitVars( "TopJet_W2_Phi","N_TopJets" );
  vars.InitVars( "TopJet_W2_M","N_TopJets" );
  vars.InitVars( "TopJet_W2_Flav","N_TopJets" );
  vars.InitVars( "TopJet_W2_CSV","N_TopJets" );
  
  vars.InitVars( "TopJet_W_E","N_TopJets" );
  vars.InitVars( "TopJet_W_Pt","N_TopJets" );
  vars.InitVars( "TopJet_W_Eta","N_TopJets" );
  vars.InitVars( "TopJet_W_Phi","N_TopJets" );
  vars.InitVars( "TopJet_W_M","N_TopJets" );
  vars.InitVars( "TopJet_W_Flav","N_TopJets" );
  vars.InitVars( "TopJet_W_Charge","N_TopJets" );

  vars.InitVars( "TopJet_Top_E","N_TopJets" );
  vars.InitVars( "TopJet_Top_Pt","N_TopJets" );
  vars.InitVars( "TopJet_Top_Eta","N_TopJets" );
  vars.InitVars( "TopJet_Top_Phi","N_TopJets" );
  vars.InitVars( "TopJet_Top_M","N_TopJets" );
  vars.InitVars( "TopJet_Top_Flav","N_TopJets" );
  vars.InitVars( "TopJet_Top_Charge","N_TopJets" );
  
  vars.InitVars( "TopJet_BW1_M","N_TopJets" );
  vars.InitVars( "TopJet_BW2_M","N_TopJets" );

  vars.InitVars( "TopJet_M12","N_TopJets" );
  vars.InitVars( "TopJet_M13","N_TopJets" );
  vars.InitVars( "TopJet_M23","N_TopJets" );

  vars.InitVars( "TopJet_Dr_B_Top","N_TopJets" );
  vars.InitVars( "TopJet_Dr_Top","N_TopJets" );
  vars.InitVars( "TopJet_Dr_W1_Top","N_TopJets" );
  vars.InitVars( "TopJet_Dr_W2_Top","N_TopJets" );
  vars.InitVars( "TopJet_Dr_W_Top","N_TopJets" );
  vars.InitVars( "TopJet_Dr_W_B","N_TopJets" );
  vars.InitVars( "TopJet_Dr_W1_B","N_TopJets" );
  vars.InitVars( "TopJet_Dr_W2_B","N_TopJets" );
  vars.InitVars( "TopJet_Dr_W1_W","N_TopJets" );
  vars.InitVars( "TopJet_Dr_W2_W","N_TopJets" );
  vars.InitVars( "TopJet_Dr_W1_W2","N_TopJets" );

  vars.InitVars( "TopJet_ERatio_Top","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_B","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W1","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W2","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_B_Top","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W1_Top","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W2_Top","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W_Top","N_TopJets" );

  vars.InitVars( "TopJet_PtRatio_Top","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_B","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W1","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W2","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_B_Top","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W1_Top","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W2_Top","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W_Top","N_TopJets" );

  vars.InitVars( "TopJet_MRatio_Top","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_B","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W1","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W2","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_B_Top","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W1_Top","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W2_Top","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W_Top","N_TopJets" );

  vars.InitVars( "TopJet_Subjetiness1","N_TopJets" );
  vars.InitVars( "TopJet_Subjetiness2","N_TopJets" );
  vars.InitVars( "TopJet_Subjetiness3","N_TopJets" );
  vars.InitVars( "TopJet_Subjetiness4","N_TopJets" );

  vars.InitVars( "TopJet_W1_IdxAk5","N_TopJets" );
  vars.InitVars( "TopJet_W2_IdxAk5","N_TopJets" );
  vars.InitVars( "TopJet_B_IdxAk5","N_TopJets" );
  vars.InitVars( "TopJet_Dr_Lepton","N_TopJets" );
  vars.InitVars( "TopJet_TaggedB","N_TopJets" );
  
  vars.InitVars( "TopJet_Bbtag_E","N_TopJets" );
  vars.InitVars( "TopJet_Bbtag_Pt","N_TopJets" );
  vars.InitVars( "TopJet_Bbtag_Eta","N_TopJets" );
  vars.InitVars( "TopJet_Bbtag_Phi","N_TopJets" );
  vars.InitVars( "TopJet_Bbtag_CSV","N_TopJets" );
  vars.InitVars( "TopJet_Bbtag_M","N_TopJets" );
  
  vars.InitVars( "TopJet_W1btag_E","N_TopJets" );
  vars.InitVars( "TopJet_W1btag_Pt","N_TopJets" );
  vars.InitVars( "TopJet_W1btag_Eta","N_TopJets" );
  vars.InitVars( "TopJet_W1btag_Phi","N_TopJets" );
  vars.InitVars( "TopJet_W1btag_CSV","N_TopJets" );
  vars.InitVars( "TopJet_W1btag_M","N_TopJets" );
  
  vars.InitVars( "TopJet_W2btag_E","N_TopJets" );
  vars.InitVars( "TopJet_W2btag_Pt","N_TopJets" );
  vars.InitVars( "TopJet_W2btag_Eta","N_TopJets" );
  vars.InitVars( "TopJet_W2btag_Phi","N_TopJets" );
  vars.InitVars( "TopJet_W2btag_CSV","N_TopJets" );
  vars.InitVars( "TopJet_W2btag_M","N_TopJets" );
  
  vars.InitVars( "TopJet_Wbtag_E","N_TopJets" );
  vars.InitVars( "TopJet_Wbtag_Pt","N_TopJets" );
  vars.InitVars( "TopJet_Wbtag_Eta","N_TopJets" );
  vars.InitVars( "TopJet_Wbtag_Phi","N_TopJets" );
  vars.InitVars( "TopJet_Wbtag_CSV","N_TopJets" );
  vars.InitVars( "TopJet_Wbtag_M","N_TopJets" );
  
  vars.InitVars( "TopJet_BW1btag_M","N_TopJets" );
  vars.InitVars( "TopJet_BW2btag_M","N_TopJets" );
//   vars.InitVars( "TopJet_Wbtag_Charge","N_TopJets" );
//   vars.InitVars( "TopJet_BW1btag_Charge","N_TopJets" );
//   vars.InitVars( "TopJet_BW2btag_Charge","N_TopJets" );
  vars.InitVars( "TopJet_Bbtag_Flav","N_TopJets" );
  vars.InitVars( "TopJet_W1btag_Flav","N_TopJets" );
  vars.InitVars( "TopJet_W2btag_Flav","N_TopJets" );

  vars.InitVars( "TopJet_ERatio_Bbtag","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W1btag","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W2btag","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_Wbtag","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_Bbtag_Top","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W1btag_Top","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_W2btag_Top","N_TopJets" );
  vars.InitVars( "TopJet_ERatio_Wbtag_Top","N_TopJets" );

  vars.InitVars( "TopJet_PtRatio_Bbtag","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W1btag","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W2btag","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_Wbtag","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_Bbtag_Top","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W1btag_Top","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_W2btag_Top","N_TopJets" );
  vars.InitVars( "TopJet_PtRatio_Wbtag_Top","N_TopJets" );

  vars.InitVars( "TopJet_MRatio_Bbtag","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W1btag","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W2btag","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_Wbtag","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_Bbtag_Top","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W1btag_Top","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_W2btag_Top","N_TopJets" );
  vars.InitVars( "TopJet_MRatio_Wbtag_Top","N_TopJets" );

  vars.InitVars( "TopJet_Dr_W1btag_Bbtag","N_TopJets" );
  vars.InitVars( "TopJet_Dr_W2btag_Bbtag","N_TopJets" );
  vars.InitVars( "TopJet_Dr_W1btag_W2btag","N_TopJets" );

  vars.InitVar( "N_HiggsJets","I" );

  vars.InitVars( "HiggsJet_Pt","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Eta","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Phi","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CSV1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CSV2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CSV3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CSV4","N_HiggsJets" );
  vars.InitVars( "HiggsJet_M2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_M3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_M2_SingleTag","N_HiggsJets" );
  vars.InitVars( "HiggsJet_M3_SingleTag","N_HiggsJets" );
  vars.InitVars( "HiggsJet_M2_DoubleTag","N_HiggsJets" );
  vars.InitVars( "HiggsJet_M3_DoubleTag","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Pt2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Pt3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_TopJet1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_TopJet2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_TopJet3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_TopJet4","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Subjetiness1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Subjetiness2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Subjetiness3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Subjetiness4","N_HiggsJets" );
  
  vars.InitVars( "HiggsJet_Filterjet1_Pt","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Pt","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Pt","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Pt","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_E","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_E","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_E","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_E","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_M","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_M","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_M","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_M","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Eta","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Eta","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Eta","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Eta","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Phi","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Phi","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Phi","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Phi","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_CSV","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_CSV","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_CSV","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_CSV","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Dr","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Dr","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Dr","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Dr","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Flav","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Flav","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Flav","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Flav","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Charge","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Charge","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Charge","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Charge","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_PtRatio","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_PtRatio","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_PtRatio","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_PtRatio","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_ERatio","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_ERatio","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_ERatio","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_ERatio","N_HiggsJets" );
  
  vars.InitVars( "HiggsJet_Dr_Filterjet12","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Filterjet13","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Filterjet23","N_HiggsJets" );
  
  vars.InitVars( "HiggsJet_Filterjet1_E_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Pt_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Eta_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_Phi_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_E_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Pt_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Eta_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_Phi_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_E_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Pt_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Eta_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_Phi_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_E_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Pt_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Eta_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet4_Phi_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CosThetaStar_Filterjet12","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CosThetaStar_Filterjet13","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CosThetaStar_Filterjet23","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet1_IdxAk5","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet2_IdxAk5","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Filterjet3_IdxAk5","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Lepton","N_HiggsJets" );

  vars.InitVar( "N_MJDCA12_L","I" );
  vars.InitVars( "CA12MFJ_L_E","MJDCA12_L_N" );
  vars.InitVars( "CA12MFJ_L_Pt","MJDCA12_L_N" );
  vars.InitVars( "CA12MFJ_L_Eta","MJDCA12_L_N" );
  vars.InitVars( "CA12MFJ_L_Phi","MJDCA12_L_N" );
  vars.InitVars( "CA12MFJ_L_DCSV","MJDCA12_L_N" );
  vars.InitVars( "CA12MFJ_L_Dr","MJDCA12_L_N" );

  vars.InitVar( "N_MJDCA12_T","I" );
  vars.InitVars( "CA12MFJ_T_E","MJDCA12_T_N" );
  vars.InitVars( "CA12MFJ_T_Pt","MJDCA12_T_N" );
  vars.InitVars( "CA12MFJ_T_Eta","MJDCA12_T_N" );
  vars.InitVars( "CA12MFJ_T_Phi","MJDCA12_T_N" );
  vars.InitVars( "CA12MFJ_T_DCSV","MJDCA12_T_N" );
  vars.InitVars( "CA12MFJ_T_Dr","MJDCA12_T_N" );

  vars.InitVar( "N_MJDCA15_L","I" );
  vars.InitVars( "CA15MFJ_L_E","MJDCA15_L_N" );
  vars.InitVars( "CA15MFJ_L_Pt","MJDCA15_L_N" );
  vars.InitVars( "CA15MFJ_L_Eta","MJDCA15_L_N" );
  vars.InitVars( "CA15MFJ_L_Phi","MJDCA15_L_N" );
  vars.InitVars( "CA15MFJ_L_DCSV","MJDCA15_L_N" );
  vars.InitVars( "CA15MFJ_L_Dr","MJDCA15_L_N" );

  vars.InitVar( "N_MJDCA15_T","I" );
  vars.InitVars( "CA15MFJ_T_E","MJDCA15_T_N" );
  vars.InitVars( "CA15MFJ_T_Pt","MJDCA15_T_N" );
  vars.InitVars( "CA15MFJ_T_Eta","MJDCA15_T_N" );
  vars.InitVars( "CA15MFJ_T_Phi","MJDCA15_T_N" );
  vars.InitVars( "CA15MFJ_T_DCSV","MJDCA15_T_N" );
  vars.InitVars( "CA15MFJ_T_Dr","MJDCA15_T_N" );


  initialized=true;
}


void BoostedJetVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  
  if(!initialized) cerr << "tree processor not initialized" << endl;

  vars.FillVar("N_TopJets",input.selectedHEPTopJets.size());
  for(size_t i=0; i< input.selectedHEPTopJets.size(); i++){
    //vars.FillVars( "TopJet_Tagged",i,input.selectedHEPTopJets[i].toptag );
    
    vars.FillVars( "TopJet_HEPTopTag",i,input.selectedHEPTopJets[i].toptag);
    vars.FillVars( "TopJet_Tag",i,BoostedUtils::GetTopTag(input.selectedHEPTopJets[i],0.15,120.));
    
    vars.FillVars( "TopJet_E",i,input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "TopJet_Pt",i,input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "TopJet_Eta",i,input.selectedHEPTopJets[i].fatjet.eta() );
    vars.FillVars( "TopJet_Phi",i,input.selectedHEPTopJets[i].fatjet.phi() );
    vars.FillVars( "TopJet_M",i,input.selectedHEPTopJets[i].fatjet.mass() );

    vars.FillVars( "TopJet_B_E",i,input.selectedHEPTopJets[i].nonW.energy() );
    vars.FillVars( "TopJet_B_Pt",i,input.selectedHEPTopJets[i].nonW.pt() );
    vars.FillVars( "TopJet_B_Eta",i,input.selectedHEPTopJets[i].nonW.eta() );
    vars.FillVars( "TopJet_B_Phi",i,input.selectedHEPTopJets[i].nonW.phi() );
    vars.FillVars( "TopJet_B_M",i,input.selectedHEPTopJets[i].nonW.mass() );
    vars.FillVars( "TopJet_B_Flav",i,input.selectedHEPTopJets[i].nonW.partonFlavour() );
    vars.FillVars( "TopJet_B_Charge",i,input.selectedHEPTopJets[i].nonW.jetCharge() );

    vars.FillVars( "TopJet_W1_E",i,input.selectedHEPTopJets[i].W1.energy() );
    vars.FillVars( "TopJet_W1_Pt",i,input.selectedHEPTopJets[i].W1.pt() );
    vars.FillVars( "TopJet_W1_Eta",i,input.selectedHEPTopJets[i].W1.eta() );
    vars.FillVars( "TopJet_W1_Phi",i,input.selectedHEPTopJets[i].W1.phi() );
    vars.FillVars( "TopJet_W1_M",i,input.selectedHEPTopJets[i].W1.mass() );
    vars.FillVars( "TopJet_W1_Flav",i,input.selectedHEPTopJets[i].W1.partonFlavour() );

    vars.FillVars( "TopJet_W2_E",i,input.selectedHEPTopJets[i].W2.energy() );
    vars.FillVars( "TopJet_W2_Pt",i,input.selectedHEPTopJets[i].W2.pt() );
    vars.FillVars( "TopJet_W2_Eta",i,input.selectedHEPTopJets[i].W2.eta() );
    vars.FillVars( "TopJet_W2_Phi",i,input.selectedHEPTopJets[i].W2.phi() );
    vars.FillVars( "TopJet_W2_M",i,input.selectedHEPTopJets[i].W2.mass() );
    vars.FillVars( "TopJet_W2_Flav",i,input.selectedHEPTopJets[i].W2.partonFlavour() );

    vars.FillVars( "TopJet_W_E",i,input.selectedHEPTopJets[i].W.energy() );
    vars.FillVars( "TopJet_W_Pt",i,input.selectedHEPTopJets[i].W.pt() );
    vars.FillVars( "TopJet_W_Eta",i,input.selectedHEPTopJets[i].W.eta() );
    vars.FillVars( "TopJet_W_Phi",i,input.selectedHEPTopJets[i].W.phi() );
    vars.FillVars( "TopJet_W_M",i,input.selectedHEPTopJets[i].W.mass() );
    vars.FillVars( "TopJet_W_Flav",i,input.selectedHEPTopJets[i].W.partonFlavour() );
    vars.FillVars( "TopJet_W_Charge",i,input.selectedHEPTopJets[i].W.jetCharge() );

    vars.FillVars( "TopJet_Top_E",i,input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "TopJet_Top_Pt",i,input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "TopJet_Top_Eta",i,input.selectedHEPTopJets[i].topjet.eta() );
    vars.FillVars( "TopJet_Top_Phi",i,input.selectedHEPTopJets[i].topjet.phi() );
    vars.FillVars( "TopJet_Top_M",i,input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "TopJet_Top_Flav",i,input.selectedHEPTopJets[i].topjet.partonFlavour() );
    vars.FillVars( "TopJet_Top_Charge",i,input.selectedHEPTopJets[i].topjet.jetCharge() );

    vars.FillVars( "TopJet_BW1_M",i,(input.selectedHEPTopJets[i].nonW.p4()+input.selectedHEPTopJets[i].W1.p4()).M() );
    vars.FillVars( "TopJet_BW2_M",i,(input.selectedHEPTopJets[i].nonW.p4()+input.selectedHEPTopJets[i].W2.p4()).M() );
    
    vars.FillVars( "TopJet_Dr_B_Top",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].nonW,input.selectedHEPTopJets[i].topjet) );
    vars.FillVars( "TopJet_Dr_W1_Top",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W1,input.selectedHEPTopJets[i].topjet) );
    vars.FillVars( "TopJet_Dr_W2_Top",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W2,input.selectedHEPTopJets[i].topjet) );
    vars.FillVars( "TopJet_Dr_W_Top",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W,input.selectedHEPTopJets[i].topjet) );
    vars.FillVars( "TopJet_Dr_W_B",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W,input.selectedHEPTopJets[i].nonW) );
    vars.FillVars( "TopJet_Dr_W1_B",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W1,input.selectedHEPTopJets[i].nonW) );
    vars.FillVars( "TopJet_Dr_W2_B",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W2,input.selectedHEPTopJets[i].nonW) );
    vars.FillVars( "TopJet_Dr_W1_W",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W1,input.selectedHEPTopJets[i].W) );
    vars.FillVars( "TopJet_Dr_W2_W",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W2,input.selectedHEPTopJets[i].W) );
    vars.FillVars( "TopJet_Dr_W1_W2",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W1,input.selectedHEPTopJets[i].W2) );

    vars.FillVars( "TopJet_ERatio_Top",i,input.selectedHEPTopJets[i].topjet.energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "TopJet_ERatio_B",i,input.selectedHEPTopJets[i].nonW.energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "TopJet_ERatio_W1",i,input.selectedHEPTopJets[i].W1.energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "TopJet_ERatio_W2",i,input.selectedHEPTopJets[i].W2.energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "TopJet_ERatio_W",i,input.selectedHEPTopJets[i].W.energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "TopJet_ERatio_B_Top",i,input.selectedHEPTopJets[i].nonW.energy()/input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "TopJet_ERatio_W1_Top",i,input.selectedHEPTopJets[i].W1.energy()/input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "TopJet_ERatio_W2_Top",i,input.selectedHEPTopJets[i].W2.energy()/input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "TopJet_ERatio_W_Top",i,input.selectedHEPTopJets[i].W.energy()/input.selectedHEPTopJets[i].topjet.energy() );

    vars.FillVars( "TopJet_PtRatio_Top",i,input.selectedHEPTopJets[i].topjet.pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "TopJet_PtRatio_B",i,input.selectedHEPTopJets[i].nonW.pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "TopJet_PtRatio_W1",i,input.selectedHEPTopJets[i].W1.pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "TopJet_PtRatio_W2",i,input.selectedHEPTopJets[i].W2.pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "TopJet_PtRatio_W",i,input.selectedHEPTopJets[i].W.pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "TopJet_PtRatio_B_Top",i,input.selectedHEPTopJets[i].nonW.pt()/input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "TopJet_PtRatio_W1_Top",i,input.selectedHEPTopJets[i].W1.pt()/input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "TopJet_PtRatio_W2_Top",i,input.selectedHEPTopJets[i].W2.pt()/input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "TopJet_PtRatio_W_Top",i,input.selectedHEPTopJets[i].W.pt()/input.selectedHEPTopJets[i].topjet.pt() );

    vars.FillVars( "TopJet_MRatio_Top",i,input.selectedHEPTopJets[i].topjet.mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "TopJet_MRatio_B",i,input.selectedHEPTopJets[i].nonW.mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "TopJet_MRatio_W1",i,input.selectedHEPTopJets[i].W1.mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "TopJet_MRatio_W2",i,input.selectedHEPTopJets[i].W2.mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "TopJet_MRatio_W",i,input.selectedHEPTopJets[i].W.mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "TopJet_MRatio_B_Top",i,input.selectedHEPTopJets[i].nonW.mass()/input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "TopJet_MRatio_W1_Top",i,input.selectedHEPTopJets[i].W1.mass()/input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "TopJet_MRatio_W2_Top",i,input.selectedHEPTopJets[i].W2.mass()/input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "TopJet_MRatio_W_Top",i,input.selectedHEPTopJets[i].W.mass()/input.selectedHEPTopJets[i].topjet.mass() );

    vector<math::XYZTLorentzVector> topvecs;
    topvecs.push_back(input.selectedHEPTopJets[i].W1.p4());
    topvecs.push_back(input.selectedHEPTopJets[i].W2.p4());
    topvecs.push_back(input.selectedHEPTopJets[i].nonW.p4());
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

    vars.FillVars( "TopJet_B_CSV",i,fmax(input.selectedHEPTopJets[i].nonW.bDiscriminator(btagger),-.1) );
    vars.FillVars( "TopJet_W1_CSV",i,fmax(input.selectedHEPTopJets[i].W1.bDiscriminator(btagger),-.1) );
    vars.FillVars( "TopJet_W2_CSV",i,fmax(input.selectedHEPTopJets[i].W2.bDiscriminator(btagger),-.1) );
    
    //Definition with b-jet == highest CSV
    vector<pat::Jet> subjets;
    subjets.push_back(input.selectedHEPTopJets[i].nonW);
    subjets.push_back(input.selectedHEPTopJets[i].W1);
    subjets.push_back(input.selectedHEPTopJets[i].W2);

    BoostedUtils::TopSubjetCSVDef(subjets);

    vector<math::XYZTLorentzVector> topvecs_bycsv = BoostedUtils::GetJetVecs(subjets);
    vars.FillVars( "TopJet_TaggedB",i,BoostedUtils::GetTopTag(input.selectedHEPTopJets[i],0.2,120,true) );
    
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
    vars.FillVars( "TopJet_Bbtag_CSV",i,fmax(subjets[0].bDiscriminator(btagger),-.1) );
    
    vars.FillVars( "TopJet_W1btag_E",i,subjets[1].energy() );
    vars.FillVars( "TopJet_W1btag_Pt",i,subjets[1].pt() );
    vars.FillVars( "TopJet_W1btag_Eta",i,subjets[1].eta() );
    vars.FillVars( "TopJet_W1btag_Phi",i,subjets[1].phi() );
    vars.FillVars( "TopJet_W1btag_M",i,subjets[1].mass() );
    vars.FillVars( "TopJet_W1btag_CSV",i,fmax(subjets[1].bDiscriminator(btagger),-.1) );
    
    vars.FillVars( "TopJet_W2btag_E",i,subjets[2].energy() );
    vars.FillVars( "TopJet_W2btag_Pt",i,subjets[2].pt() );
    vars.FillVars( "TopJet_W2btag_Eta",i,subjets[2].eta() );
    vars.FillVars( "TopJet_W2btag_Phi",i,subjets[2].phi() );
    vars.FillVars( "TopJet_W2btag_M",i,subjets[2].mass() );
    vars.FillVars( "TopJet_W2btag_CSV",i,fmax(subjets[2].bDiscriminator(btagger),-.1) );
    
    vars.FillVars( "TopJet_Wbtag_E",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).E() );
    vars.FillVars( "TopJet_Wbtag_Pt",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).Pt() );
    vars.FillVars( "TopJet_Wbtag_Eta",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).Eta() );
    vars.FillVars( "TopJet_Wbtag_Phi",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).Phi() );
    vars.FillVars( "TopJet_Wbtag_M",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M() );
    
    vars.FillVars( "TopJet_BW1btag_M",i,(topvecs_bycsv[0]+topvecs_bycsv[1]).M() );
    vars.FillVars( "TopJet_BW2btag_M",i,(topvecs_bycsv[0]+topvecs_bycsv[2]).M() );

//     vars.FillVars( "TopJet_Wbtag_Charge",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).jetCharge() );
//     vars.FillVars( "TopJet_BW1btag_Charge",i,(topvecs_bycsv[0]+topvecs_bycsv[1]).jetCharge() );
//     vars.FillVars( "TopJet_BW2btag_Charge",i,(topvecs_bycsv[0]+topvecs_bycsv[2]).jetCharge() );
    
    vars.FillVars( "TopJet_Dr_W1btag_Bbtag",i,BoostedUtils::DeltaR(subjets[1],subjets[0]));
    vars.FillVars( "TopJet_Dr_W2btag_Bbtag",i,BoostedUtils::DeltaR(subjets[2],subjets[0]));
    vars.FillVars( "TopJet_Dr_W1btag_W2btag",i,BoostedUtils::DeltaR(subjets[1],subjets[2]));

    vars.FillVars( "TopJet_ERatio_Bbtag",i,subjets[0].energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "TopJet_ERatio_W1btag",i,subjets[1].energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "TopJet_ERatio_W2btag",i,subjets[2].energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "TopJet_ERatio_Wbtag",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).E()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "TopJet_ERatio_Bbtag_Top",i,subjets[0].energy()/input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "TopJet_ERatio_W1btag_Top",i,subjets[1].energy()/input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "TopJet_ERatio_W2btag_Top",i,subjets[2].energy()/input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "TopJet_ERatio_Wbtag_Top",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).E()/input.selectedHEPTopJets[i].topjet.energy() );

    vars.FillVars( "TopJet_PtRatio_Bbtag",i,subjets[0].pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "TopJet_PtRatio_W1btag",i,subjets[1].pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "TopJet_PtRatio_W2btag",i,subjets[2].pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "TopJet_PtRatio_Wbtag",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "TopJet_PtRatio_Bbtag_Top",i,subjets[0].pt()/input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "TopJet_PtRatio_W1btag_Top",i,subjets[1].pt()/input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "TopJet_PtRatio_W2btag_Top",i,subjets[2].pt()/input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "TopJet_PtRatio_Wbtag_Top",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).pt()/input.selectedHEPTopJets[i].topjet.pt() );

    vars.FillVars( "TopJet_MRatio_Bbtag",i,subjets[0].mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "TopJet_MRatio_W1btag",i,subjets[1].mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "TopJet_MRatio_W2btag",i,subjets[2].mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "TopJet_MRatio_Wbtag",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "TopJet_MRatio_Bbtag_Top",i,subjets[0].mass()/input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "TopJet_MRatio_W1btag_Top",i,subjets[1].mass()/input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "TopJet_MRatio_W2btag_Top",i,subjets[2].mass()/input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "TopJet_MRatio_Wbtag_Top",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M()/input.selectedHEPTopJets[i].topjet.mass() );

    vars.FillVars( "TopJet_Subjetiness1",i,input.selectedHEPTopJets[i].subjettiness1 );
    vars.FillVars( "TopJet_Subjetiness2",i,input.selectedHEPTopJets[i].subjettiness2 );
    vars.FillVars( "TopJet_Subjetiness3",i,input.selectedHEPTopJets[i].subjettiness3 );
    vars.FillVars( "TopJet_Subjetiness4",i,input.selectedHEPTopJets[i].subjettiness4 );
   
    vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);
    math::XYZTLorentzVector w1vec = input.selectedHEPTopJets[i].W1.p4();
    math::XYZTLorentzVector w2vec = input.selectedHEPTopJets[i].W2.p4();
    math::XYZTLorentzVector bvec = input.selectedHEPTopJets[i].nonW.p4();
    
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
    math::XYZTLorentzVector primlepvec=math::XYZTLorentzVector(0.,0.,0.,0.);
    if(input.selectedElectronsLoose.size()>0||input.selectedMuonsLoose.size()>0)
	  primlepvec = BoostedUtils::GetPrimLepVec(input.selectedElectronsLoose,input.selectedMuonsLoose);

    vars.FillVars("TopJet_Dr_Lepton",i,primlepvec.pt()>5 ? BoostedUtils::DeltaR(primlepvec,input.selectedHEPTopJets[i].fatjet.p4()) : -1);


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
      vars.FillVars( "HiggsJet_"+FilterJetName+"_CSV",i,itFiltJet->bDiscriminator(btagger) );
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
    
    vars.FillVars( "HiggsJet_M2_SingleTag",i,BoostedUtils::GetHiggsMass(input.selectedSubFilterJets[i], 2, 1, 0.814) );
    vars.FillVars( "HiggsJet_M3_SingleTag",i,BoostedUtils::GetHiggsMass(input.selectedSubFilterJets[i], 3, 1, 0.814) );
    vars.FillVars( "HiggsJet_M2_DoubleTag",i,BoostedUtils::GetHiggsMass(input.selectedSubFilterJets[i], 2, 2, 0.814) );
    vars.FillVars( "HiggsJet_M3_DoubleTag",i,BoostedUtils::GetHiggsMass(input.selectedSubFilterJets[i], 3, 2, 0.814) );
    
    std::vector<pat::Jet> filterJets = BoostedUtils::GetHiggsFilterJets(input.selectedSubFilterJets[i], 4);
    if(filterJets.size()>0) vars.FillVars( "HiggsJet_CSV1",i,filterJets[0].bDiscriminator(btagger) );
    if(filterJets.size()>1) vars.FillVars( "HiggsJet_CSV2",i,filterJets[1].bDiscriminator(btagger) );
    if(filterJets.size()>2) vars.FillVars( "HiggsJet_CSV3",i,filterJets[2].bDiscriminator(btagger) );
    if(filterJets.size()>3) vars.FillVars( "HiggsJet_CSV4",i,filterJets[3].bDiscriminator(btagger) );
    
    if(input.selectedHEPTopJets.size()>0) vars.FillVars( "HiggsJet_Dr_TopJet1",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].fatjet,input.selectedHEPTopJets[0].fatjet) );
    if(input.selectedHEPTopJets.size()>1) vars.FillVars( "HiggsJet_Dr_TopJet2",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].fatjet,input.selectedHEPTopJets[1].fatjet) );
    if(input.selectedHEPTopJets.size()>2) vars.FillVars( "HiggsJet_Dr_TopJet3",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].fatjet,input.selectedHEPTopJets[2].fatjet) );
    if(input.selectedHEPTopJets.size()>3) vars.FillVars( "HiggsJet_Dr_TopJet4",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].fatjet,input.selectedHEPTopJets[3].fatjet) );
    
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
  }

  vector<float> CA12MFJ_L_CSVR;
  vector<float> CA12MFJ_L_Dr;
  vector<TLorentzVector> CA12MFJ_L_p4 = BoostedUtils::GetCAMatchDiff(input.selectedSubFilterJets, input.selectedJets, CA12MFJ_L_CSVR, CA12MFJ_L_Dr);

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
  vector<TLorentzVector> CA12MFJ_T_p4 = BoostedUtils::GetCAMatchDiff(input.selectedSubFilterJets, input.selectedJets, CA12MFJ_T_CSVR, CA12MFJ_T_Dr);

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
  vector<TLorentzVector> CA15MFJ_L_p4 = BoostedUtils::GetCAMatchDiff(input.selectedSubFilterJets, input.selectedJets, CA15MFJ_L_CSVR, CA15MFJ_L_Dr);

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
  vector<TLorentzVector> CA15MFJ_T_p4 = BoostedUtils::GetCAMatchDiff(input.selectedSubFilterJets, input.selectedJets, CA15MFJ_T_CSVR, CA15MFJ_T_Dr);

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
