#include "BoostedTTH/BoostedAnalyzer/interface/BoostedJetVarProcessor.hpp"

using namespace std;

BoostedJetVarProcessor::BoostedJetVarProcessor (){}
BoostedJetVarProcessor::~BoostedJetVarProcessor (){}


void BoostedJetVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
  vars.InitVar( "N_TopJets","I" );
  
  vars.InitVars( "HEPTopTag_TopJet","N_TopJets" );
  vars.InitVars( "Tag_TopJet","N_TopJets" );
  
  vars.InitVars( "E_TopJet","N_TopJets" );
  vars.InitVars( "Pt_TopJet","N_TopJets" );
  vars.InitVars( "Eta_TopJet","N_TopJets" );
  vars.InitVars( "Phi_TopJet","N_TopJets" );
  vars.InitVars( "M_TopJet","N_TopJets" );

  vars.InitVars( "E_B_TopJet","N_TopJets" );
  vars.InitVars( "Pt_B_TopJet","N_TopJets" );
  vars.InitVars( "Eta_B_TopJet","N_TopJets" );
  vars.InitVars( "Phi_B_TopJet","N_TopJets" );
  vars.InitVars( "M_B_TopJet","N_TopJets" );

  vars.InitVars( "E_W1_TopJet","N_TopJets" );
  vars.InitVars( "Pt_W1_TopJet","N_TopJets" );
  vars.InitVars( "Eta_W1_TopJet","N_TopJets" );
  vars.InitVars( "Phi_W1_TopJet","N_TopJets" );
  vars.InitVars( "M_W1_TopJet","N_TopJets" );

  vars.InitVars( "E_W2_TopJet","N_TopJets" );
  vars.InitVars( "Pt_W2_TopJet","N_TopJets" );
  vars.InitVars( "Eta_W2_TopJet","N_TopJets" );
  vars.InitVars( "Phi_W2_TopJet","N_TopJets" );
  vars.InitVars( "M_W2_TopJet","N_TopJets" );

  vars.InitVars( "E_W_TopJet","N_TopJets" );
  vars.InitVars( "Pt_W_TopJet","N_TopJets" );
  vars.InitVars( "Eta_W_TopJet","N_TopJets" );
  vars.InitVars( "Phi_W_TopJet","N_TopJets" );
  vars.InitVars( "M_W_TopJet","N_TopJets" );

  vars.InitVars( "E_Top_TopJet","N_TopJets" );
  vars.InitVars( "Pt_Top_TopJet","N_TopJets" );
  vars.InitVars( "Eta_Top_TopJet","N_TopJets" );
  vars.InitVars( "Phi_Top_TopJet","N_TopJets" );
  vars.InitVars( "M_Top_TopJet","N_TopJets" );

  vars.InitVars( "M12_TopJet","N_TopJets" );
  vars.InitVars( "M13_TopJet","N_TopJets" );
  vars.InitVars( "M23_TopJet","N_TopJets" );

  vars.InitVars( "CSV_B_TopJet","N_TopJets" );
  vars.InitVars( "CSV_W1_TopJet","N_TopJets" );
  vars.InitVars( "CSV_W2_TopJet","N_TopJets" );

  vars.InitVars( "Dr_B_Top_TopJet","N_TopJets" );
  vars.InitVars( "Dr_W1_Top_TopJet","N_TopJets" );
  vars.InitVars( "Dr_W2_Top_TopJet","N_TopJets" );
  vars.InitVars( "Dr_W_Top_TopJet","N_TopJets" );
  vars.InitVars( "Dr_W_B_TopJet","N_TopJets" );
  vars.InitVars( "Dr_W1_B_TopJet","N_TopJets" );
  vars.InitVars( "Dr_W2_B_TopJet","N_TopJets" );
  vars.InitVars( "Dr_W1_W_TopJet","N_TopJets" );
  vars.InitVars( "Dr_W2_W_TopJet","N_TopJets" );
  vars.InitVars( "Dr_W1_W2_TopJet","N_TopJets" );

  vars.InitVars( "ERatio_Top_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_B_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_W1_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_W2_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_W_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_B_Top_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_W1_Top_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_W2_Top_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_W_Top_TopJet","N_TopJets" );

  vars.InitVars( "PtRatio_Top_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_B_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_W1_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_W2_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_W_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_B_Top_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_W1_Top_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_W2_Top_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_W_Top_TopJet","N_TopJets" );

  vars.InitVars( "MRatio_Top_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_B_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_W1_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_W2_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_W_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_B_Top_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_W1_Top_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_W2_Top_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_W_Top_TopJet","N_TopJets" );

  vars.InitVars( "Subjetiness1_TopJet","N_TopJets" );
  vars.InitVars( "Subjetiness2_TopJet","N_TopJets" );
  vars.InitVars( "Subjetiness3_TopJet","N_TopJets" );
  vars.InitVars( "Subjetiness4_TopJet","N_TopJets" );

  vars.InitVars( "IdxAk5_W1_TopJet","N_TopJets" );
  vars.InitVars( "IdxAk5_W2_TopJet","N_TopJets" );
  vars.InitVars( "IdxAk5_B_TopJet","N_TopJets" );
  vars.InitVars( "Dr_Lepton_TopJet","N_TopJets" );
  vars.InitVars( "TaggedB_TopJet","N_TopJets" );

  vars.InitVars( "Pt_Bbtag_TopJet","N_TopJets" );
  vars.InitVars( "Pt_W1btag_TopJet","N_TopJets" );
  vars.InitVars( "Pt_W2btag_TopJet","N_TopJets" );
  vars.InitVars( "Eta_Bbtag_TopJet","N_TopJets" );
  vars.InitVars( "Eta_W1btag_TopJet","N_TopJets" );
  vars.InitVars( "Eta_W2btag_TopJet","N_TopJets" );
  vars.InitVars( "Phi_Bbtag_TopJet","N_TopJets" );
  vars.InitVars( "Phi_W1btag_TopJet","N_TopJets" );
  vars.InitVars( "Phi_W2btag_TopJet","N_TopJets" );
  vars.InitVars( "E_Bbtag_TopJet","N_TopJets" );
  vars.InitVars( "E_W1btag_TopJet","N_TopJets" );
  vars.InitVars( "E_W2btag_TopJet","N_TopJets" );
  vars.InitVars( "CSV_Bbtag_TopJet","N_TopJets" );
  vars.InitVars( "CSV_W1btag_TopJet","N_TopJets" );
  vars.InitVars( "CSV_W2btag_TopJet","N_TopJets" );
  vars.InitVars( "M_Wbtag_TopJet","N_TopJets" );
  vars.InitVars( "M_BW1btag_TopJet","N_TopJets" );
  vars.InitVars( "M_BW2btag_TopJet","N_TopJets" );

  vars.InitVars( "ERatio_Bbtag_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_W1btag_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_W2btag_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_Wbtag_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_Bbtag_Top_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_W1btag_Top_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_W2btag_Top_TopJet","N_TopJets" );
  vars.InitVars( "ERatio_Wbtag_Top_TopJet","N_TopJets" );

  vars.InitVars( "PtRatio_Bbtag_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_W1btag_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_W2btag_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_Wbtag_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_Bbtag_Top_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_W1btag_Top_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_W2btag_Top_TopJet","N_TopJets" );
  vars.InitVars( "PtRatio_Wbtag_Top_TopJet","N_TopJets" );

  vars.InitVars( "MRatio_Bbtag_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_W1btag_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_W2btag_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_Wbtag_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_Bbtag_Top_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_W1btag_Top_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_W2btag_Top_TopJet","N_TopJets" );
  vars.InitVars( "MRatio_Wbtag_Top_TopJet","N_TopJets" );

  vars.InitVars( "Dr_W1btag_Bbtag_TopJet","N_TopJets" );
  vars.InitVars( "Dr_W2btag_Bbtag_TopJet","N_TopJets" );
  vars.InitVars( "Dr_W1btag_W2btag_TopJet","N_TopJets" );


  vars.InitVar( "N_HiggsJets","I" );
  vars.InitVars( "Pt_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Eta_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Phi_HiggsJet","N_HiggsJets" );
  vars.InitVars( "CSV1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "CSV2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "CSV3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "CSV4_HiggsJet","N_HiggsJets" );
  vars.InitVars( "M2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "M3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "M2_SingleTag_HiggsJet","N_HiggsJets" );
  vars.InitVars( "M3_SingleTag_HiggsJet","N_HiggsJets" );
  vars.InitVars( "M2_DoubleTag_HiggsJet","N_HiggsJets" );
  vars.InitVars( "M3_DoubleTag_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Pt2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Pt3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Dr_TopJet1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Dr_TopJet2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Dr_TopJet3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Dr_TopJet4_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Subjetiness1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Subjetiness2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Subjetiness3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Subjetiness4_HiggsJet","N_HiggsJets" );
  
  vars.InitVars( "Pt_Filterjet1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Pt_Filterjet2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Pt_Filterjet3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Pt_Filterjet4_HiggsJet","N_HiggsJets" );
  vars.InitVars( "E_Filterjet1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "E_Filterjet2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "E_Filterjet3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "E_Filterjet4_HiggsJet","N_HiggsJets" );
  vars.InitVars( "M_Filterjet1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "M_Filterjet2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "M_Filterjet3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "M_Filterjet4_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Eta_Filterjet1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Eta_Filterjet2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Eta_Filterjet3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Eta_Filterjet4_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Phi_Filterjet1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Phi_Filterjet2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Phi_Filterjet3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Phi_Filterjet4_HiggsJet","N_HiggsJets" );
  vars.InitVars( "CSV_Filterjet1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "CSV_Filterjet2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "CSV_Filterjet3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "CSV_Filterjet4_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Dr_Filterjet1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Dr_Filterjet2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Dr_Filterjet3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Dr_Filterjet4_HiggsJet","N_HiggsJets" );
  vars.InitVars( "PtRatio_Filterjet1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "PtRatio_Filterjet2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "PtRatio_Filterjet3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "PtRatio_Filterjet4_HiggsJet","N_HiggsJets" );
  vars.InitVars( "ERatio_Filterjet1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "ERatio_Filterjet2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "ERatio_Filterjet3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "ERatio_Filterjet4_HiggsJet","N_HiggsJets" );
  
  vars.InitVars( "Dr_Filterjet12_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Dr_Filterjet13_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Dr_Filterjet23_HiggsJet","N_HiggsJets" );
  
  vars.InitVars( "E_Filterjet1_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Pt_Filterjet1_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Eta_Filterjet1_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Phi_Filterjet1_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "E_Filterjet2_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Pt_Filterjet2_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Eta_Filterjet2_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Phi_Filterjet2_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "E_Filterjet3_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Pt_Filterjet3_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Eta_Filterjet3_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Phi_Filterjet3_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "E_Filterjet4_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Pt_Filterjet4_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Eta_Filterjet4_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Phi_Filterjet4_RestFrame_HiggsJet","N_HiggsJets" );
  vars.InitVars( "CosThetaStar_Filterjet12_HiggsJet","N_HiggsJets" );
  vars.InitVars( "CosThetaStar_Filterjet13_HiggsJet","N_HiggsJets" );
  vars.InitVars( "CosThetaStar_Filterjet23_HiggsJet","N_HiggsJets" );
  vars.InitVars( "IdxAk5_Filterjet1_HiggsJet","N_HiggsJets" );
  vars.InitVars( "IdxAk5_Filterjet2_HiggsJet","N_HiggsJets" );
  vars.InitVars( "IdxAk5_Filterjet3_HiggsJet","N_HiggsJets" );
  vars.InitVars( "Dr_Lepton_HiggsJet","N_HiggsJets" );

  initialized=true;
}


void BoostedJetVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  const char* btagger="combinedInclusiveSecondaryVertexV2BJetTags";

  vars.FillVar("N_TopJets",input.selectedHEPTopJets.size());
  for(size_t i=0; i< input.selectedHEPTopJets.size(); i++){
    //vars.FillVars( "Tagged_TopJet",i,input.selectedHEPTopJets[i].toptag );
    
    vars.FillVars( "HEPTopTag_TopJet",i,input.selectedHEPTopJets[i].toptag);
    vars.FillVars( "Tag_TopJet",i,BoostedUtils::GetTopTag(input.selectedHEPTopJets[i],0.15,120.));
    
    vars.FillVars( "E_TopJet",i,input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "Pt_TopJet",i,input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "Eta_TopJet",i,input.selectedHEPTopJets[i].fatjet.eta() );
    vars.FillVars( "Phi_TopJet",i,input.selectedHEPTopJets[i].fatjet.phi() );
    vars.FillVars( "M_TopJet",i,input.selectedHEPTopJets[i].fatjet.mass() );

    vars.FillVars( "E_B_TopJet",i,input.selectedHEPTopJets[i].nonW.energy() );
    vars.FillVars( "Pt_B_TopJet",i,input.selectedHEPTopJets[i].nonW.pt() );
    vars.FillVars( "Eta_B_TopJet",i,input.selectedHEPTopJets[i].nonW.eta() );
    vars.FillVars( "Phi_B_TopJet",i,input.selectedHEPTopJets[i].nonW.phi() );
    vars.FillVars( "M_B_TopJet",i,input.selectedHEPTopJets[i].nonW.mass() );

    vars.FillVars( "E_W1_TopJet",i,input.selectedHEPTopJets[i].W1.energy() );
    vars.FillVars( "Pt_W1_TopJet",i,input.selectedHEPTopJets[i].W1.pt() );
    vars.FillVars( "Eta_W1_TopJet",i,input.selectedHEPTopJets[i].W1.eta() );
    vars.FillVars( "Phi_W1_TopJet",i,input.selectedHEPTopJets[i].W1.phi() );
    vars.FillVars( "M_W1_TopJet",i,input.selectedHEPTopJets[i].W1.mass() );

    vars.FillVars( "E_W2_TopJet",i,input.selectedHEPTopJets[i].W2.energy() );
    vars.FillVars( "Pt_W2_TopJet",i,input.selectedHEPTopJets[i].W2.pt() );
    vars.FillVars( "Eta_W2_TopJet",i,input.selectedHEPTopJets[i].W2.eta() );
    vars.FillVars( "Phi_W2_TopJet",i,input.selectedHEPTopJets[i].W2.phi() );
    vars.FillVars( "M_W2_TopJet",i,input.selectedHEPTopJets[i].W2.mass() );

    vars.FillVars( "E_W_TopJet",i,input.selectedHEPTopJets[i].W.energy() );
    vars.FillVars( "Pt_W_TopJet",i,input.selectedHEPTopJets[i].W.pt() );
    vars.FillVars( "Eta_W_TopJet",i,input.selectedHEPTopJets[i].W.eta() );
    vars.FillVars( "Phi_W_TopJet",i,input.selectedHEPTopJets[i].W.phi() );
    vars.FillVars( "M_W_TopJet",i,input.selectedHEPTopJets[i].W.mass() );

    vars.FillVars( "E_Top_TopJet",i,input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "Pt_Top_TopJet",i,input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "Eta_Top_TopJet",i,input.selectedHEPTopJets[i].topjet.eta() );
    vars.FillVars( "Phi_Top_TopJet",i,input.selectedHEPTopJets[i].topjet.phi() );
    vars.FillVars( "M_Top_TopJet",i,input.selectedHEPTopJets[i].topjet.mass() );

    vars.FillVars( "Dr_B_Top_TopJet",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].nonW,input.selectedHEPTopJets[i].topjet) );
    vars.FillVars( "Dr_W1_Top_TopJet",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W1,input.selectedHEPTopJets[i].topjet) );
    vars.FillVars( "Dr_W2_Top_TopJet",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W2,input.selectedHEPTopJets[i].topjet) );
    vars.FillVars( "Dr_W_Top_TopJet",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W,input.selectedHEPTopJets[i].topjet) );
    vars.FillVars( "Dr_W_B_TopJet",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W,input.selectedHEPTopJets[i].nonW) );
    vars.FillVars( "Dr_W1_B_TopJet",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W1,input.selectedHEPTopJets[i].nonW) );
    vars.FillVars( "Dr_W2_B_TopJet",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W2,input.selectedHEPTopJets[i].nonW) );
    vars.FillVars( "Dr_W1_W_TopJet",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W1,input.selectedHEPTopJets[i].W) );
    vars.FillVars( "Dr_W2_W_TopJet",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W2,input.selectedHEPTopJets[i].W) );
    vars.FillVars( "Dr_W1_W2_TopJet",i,BoostedUtils::DeltaR(input.selectedHEPTopJets[i].W1,input.selectedHEPTopJets[i].W2) );

    vars.FillVars( "ERatio_Top_TopJet",i,input.selectedHEPTopJets[i].topjet.energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "ERatio_B_TopJet",i,input.selectedHEPTopJets[i].nonW.energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "ERatio_W1_TopJet",i,input.selectedHEPTopJets[i].W1.energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "ERatio_W2_TopJet",i,input.selectedHEPTopJets[i].W2.energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "ERatio_W_TopJet",i,input.selectedHEPTopJets[i].W.energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "ERatio_B_Top_TopJet",i,input.selectedHEPTopJets[i].nonW.energy()/input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "ERatio_W1_Top_TopJet",i,input.selectedHEPTopJets[i].W1.energy()/input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "ERatio_W2_Top_TopJet",i,input.selectedHEPTopJets[i].W2.energy()/input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "ERatio_W_Top_TopJet",i,input.selectedHEPTopJets[i].W.energy()/input.selectedHEPTopJets[i].topjet.energy() );

    vars.FillVars( "PtRatio_Top_TopJet",i,input.selectedHEPTopJets[i].topjet.pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "PtRatio_B_TopJet",i,input.selectedHEPTopJets[i].nonW.pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "PtRatio_W1_TopJet",i,input.selectedHEPTopJets[i].W1.pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "PtRatio_W2_TopJet",i,input.selectedHEPTopJets[i].W2.pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "PtRatio_W_TopJet",i,input.selectedHEPTopJets[i].W.pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "PtRatio_B_Top_TopJet",i,input.selectedHEPTopJets[i].nonW.pt()/input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "PtRatio_W1_Top_TopJet",i,input.selectedHEPTopJets[i].W1.pt()/input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "PtRatio_W2_Top_TopJet",i,input.selectedHEPTopJets[i].W2.pt()/input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "PtRatio_W_Top_TopJet",i,input.selectedHEPTopJets[i].W.pt()/input.selectedHEPTopJets[i].topjet.pt() );

    vars.FillVars( "MRatio_Top_TopJet",i,input.selectedHEPTopJets[i].topjet.mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "MRatio_B_TopJet",i,input.selectedHEPTopJets[i].nonW.mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "MRatio_W1_TopJet",i,input.selectedHEPTopJets[i].W1.mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "MRatio_W2_TopJet",i,input.selectedHEPTopJets[i].W2.mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "MRatio_W_TopJet",i,input.selectedHEPTopJets[i].W.mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "MRatio_B_Top_TopJet",i,input.selectedHEPTopJets[i].nonW.mass()/input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "MRatio_W1_Top_TopJet",i,input.selectedHEPTopJets[i].W1.mass()/input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "MRatio_W2_Top_TopJet",i,input.selectedHEPTopJets[i].W2.mass()/input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "MRatio_W_Top_TopJet",i,input.selectedHEPTopJets[i].W.mass()/input.selectedHEPTopJets[i].topjet.mass() );

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
    vars.FillVars( "M12_TopJet",i,m12 );
    vars.FillVars( "M13_TopJet",i,m13 );
    vars.FillVars( "M23_TopJet",i,m23 );

    vars.FillVars( "CSV_B_TopJet",i,fmax(input.selectedHEPTopJets[i].nonW.bDiscriminator(btagger),-.1) );
    vars.FillVars( "CSV_W1_TopJet",i,fmax(input.selectedHEPTopJets[i].W1.bDiscriminator(btagger),-.1) );
    vars.FillVars( "CSV_W2_TopJet",i,fmax(input.selectedHEPTopJets[i].W2.bDiscriminator(btagger),-.1) );
    
    //Definition with b-jet == highest CSV
    vector<pat::Jet> subjets;
    subjets.push_back(input.selectedHEPTopJets[i].nonW);
    subjets.push_back(input.selectedHEPTopJets[i].W1);
    subjets.push_back(input.selectedHEPTopJets[i].W2);

    BoostedUtils::TopSubjetCSVDef(subjets);

    vector<math::XYZTLorentzVector> topvecs_bycsv = BoostedUtils::GetJetVecs(subjets);
    vars.FillVars( "TaggedB_TopJet",i,BoostedUtils::GetTopTag(input.selectedHEPTopJets[i],0.2,120,true) );
    vars.FillVars( "Pt_Bbtag_TopJet",i,subjets[0].pt() );
    vars.FillVars( "Pt_W1btag_TopJet",i,subjets[1].pt() );
    vars.FillVars( "Pt_W2btag_TopJet",i,subjets[2].pt() );
    vars.FillVars( "Eta_Bbtag_TopJet",i,subjets[0].eta() );
    vars.FillVars( "Eta_W1btag_TopJet",i,subjets[1].eta() );
    vars.FillVars( "Eta_W2btag_TopJet",i,subjets[2].eta() );
    vars.FillVars( "Phi_Bbtag_TopJet",i,subjets[0].phi() );
    vars.FillVars( "Phi_W1btag_TopJet",i,subjets[1].phi() );
    vars.FillVars( "Phi_W2btag_TopJet",i,subjets[2].phi() );
    vars.FillVars( "E_Bbtag_TopJet",i,subjets[0].energy() );
    vars.FillVars( "E_W1btag_TopJet",i,subjets[1].energy() );
    vars.FillVars( "E_W2btag_TopJet",i,subjets[2].energy() );
    vars.FillVars( "CSV_Bbtag_TopJet",i,fmax(subjets[0].bDiscriminator(btagger),-.1) );
    vars.FillVars( "CSV_W1btag_TopJet",i,fmax(subjets[1].bDiscriminator(btagger),-.1) );
    vars.FillVars( "CSV_W2btag_TopJet",i,fmax(subjets[2].bDiscriminator(btagger),-.1) );
    vars.FillVars( "M_Wbtag_TopJet",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M() );
    vars.FillVars( "M_BW1btag_TopJet",i,(topvecs_bycsv[0]+topvecs_bycsv[1]).M() );
    vars.FillVars( "M_BW2btag_TopJet",i,(topvecs_bycsv[0]+topvecs_bycsv[2]).M() );
    vars.FillVars( "Dr_W1btag_Bbtag_TopJet",i,BoostedUtils::DeltaR(subjets[1],subjets[0]));
    vars.FillVars( "Dr_W2btag_Bbtag_TopJet",i,BoostedUtils::DeltaR(subjets[2],subjets[0]));
    vars.FillVars( "Dr_W1btag_W2btag_TopJet",i,BoostedUtils::DeltaR(subjets[1],subjets[2]));

    vars.FillVars( "ERatio_Bbtag_TopJet",i,subjets[0].energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "ERatio_W1btag_TopJet",i,subjets[1].energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "ERatio_W2btag_TopJet",i,subjets[2].energy()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "ERatio_Wbtag_TopJet",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).E()/input.selectedHEPTopJets[i].fatjet.energy() );
    vars.FillVars( "ERatio_Bbtag_Top_TopJet",i,subjets[0].energy()/input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "ERatio_W1btag_Top_TopJet",i,subjets[1].energy()/input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "ERatio_W2btag_Top_TopJet",i,subjets[2].energy()/input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "ERatio_Wbtag_Top_TopJet",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).E()/input.selectedHEPTopJets[i].topjet.energy() );

    vars.FillVars( "PtRatio_Bbtag_TopJet",i,subjets[0].pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "PtRatio_W1btag_TopJet",i,subjets[1].pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "PtRatio_W2btag_TopJet",i,subjets[2].pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "PtRatio_Wbtag_TopJet",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).pt()/input.selectedHEPTopJets[i].fatjet.pt() );
    vars.FillVars( "PtRatio_Bbtag_Top_TopJet",i,subjets[0].pt()/input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "PtRatio_W1btag_Top_TopJet",i,subjets[1].pt()/input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "PtRatio_W2btag_Top_TopJet",i,subjets[2].pt()/input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "PtRatio_Wbtag_Top_TopJet",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).pt()/input.selectedHEPTopJets[i].topjet.pt() );

    vars.FillVars( "MRatio_Bbtag_TopJet",i,subjets[0].mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "MRatio_W1btag_TopJet",i,subjets[1].mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "MRatio_W2btag_TopJet",i,subjets[2].mass()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "MRatio_Wbtag_TopJet",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M()/input.selectedHEPTopJets[i].fatjet.mass() );
    vars.FillVars( "MRatio_Bbtag_Top_TopJet",i,subjets[0].mass()/input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "MRatio_W1btag_Top_TopJet",i,subjets[1].mass()/input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "MRatio_W2btag_Top_TopJet",i,subjets[2].mass()/input.selectedHEPTopJets[i].topjet.mass() );
    vars.FillVars( "MRatio_Wbtag_Top_TopJet",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M()/input.selectedHEPTopJets[i].topjet.mass() );

    vars.FillVars( "Subjetiness1_TopJet",i,input.selectedHEPTopJets[i].subjettiness1 );
    vars.FillVars( "Subjetiness2_TopJet",i,input.selectedHEPTopJets[i].subjettiness2 );
    vars.FillVars( "Subjetiness3_TopJet",i,input.selectedHEPTopJets[i].subjettiness3 );
    vars.FillVars( "Subjetiness4_TopJet",i,input.selectedHEPTopJets[i].subjettiness4 );
   
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


    vars.FillVars( "IdxAk5_W1_TopJet",i,idxW1 );
    vars.FillVars( "IdxAk5_W2_TopJet",i,idxW2 );
    vars.FillVars( "IdxAk5_B_TopJet",i,idxB );
    math::XYZTLorentzVector primlepvec=math::XYZTLorentzVector(0.,0.,0.,0.);
    if(input.selectedElectronsLoose.size()>0||input.selectedMuonsLoose.size()>0)
	  primlepvec = BoostedUtils::GetPrimLepVec(input.selectedElectronsLoose,input.selectedMuonsLoose);

    vars.FillVars("Dr_Lepton_TopJet",i,primlepvec.pt()>5 ? BoostedUtils::DeltaR(primlepvec,input.selectedHEPTopJets[i].fatjet.p4()) : -1);


  }

  
  vars.FillVar( "N_HiggsJets",input.selectedSubFilterJets.size() );
  for(size_t i=0; i< input.selectedSubFilterJets.size(); i++){
    vars.FillVars( "Pt_HiggsJet",i,input.selectedSubFilterJets[i].fatjet.pt() );
    vars.FillVars( "Eta_HiggsJet",i,input.selectedSubFilterJets[i].fatjet.eta() );
    vars.FillVars( "Phi_HiggsJet",i,input.selectedSubFilterJets[i].fatjet.phi() );
    
    TVector3 fatJetBoost = -(BoostedUtils::GetTLorentzVector(input.selectedSubFilterJets[i].fatjet.p4()).BoostVector());
    
    for(std::vector<pat::Jet>::const_iterator itFiltJet = input.selectedSubFilterJets[i].filterjets.begin(); itFiltJet != input.selectedSubFilterJets[i].filterjets.end() && itFiltJet-input.selectedSubFilterJets[i].filterjets.begin()<4; ++itFiltJet){
      
      TString FilterJetName = "Filterjet";
      FilterJetName += ((itFiltJet-input.selectedSubFilterJets[i].filterjets.begin())+1);
      
      vars.FillVars( "E_"+FilterJetName+"_HiggsJet",i,itFiltJet->energy() );
      vars.FillVars( "Pt_"+FilterJetName+"_HiggsJet",i,itFiltJet->pt() );
      vars.FillVars( "M_"+FilterJetName+"_HiggsJet",i,itFiltJet->mass() );
      vars.FillVars( "Eta_"+FilterJetName+"_HiggsJet",i,itFiltJet->eta() );
      vars.FillVars( "Phi_"+FilterJetName+"_HiggsJet",i,itFiltJet->phi() );
      vars.FillVars( "CSV_"+FilterJetName+"_HiggsJet",i,itFiltJet->bDiscriminator(btagger) );
      vars.FillVars( "Dr_"+FilterJetName+"_HiggsJet",i,BoostedUtils::DeltaR(*itFiltJet,input.selectedSubFilterJets[i].fatjet) );
      vars.FillVars( "PtRatio_"+FilterJetName+"_HiggsJet",i,itFiltJet->pt()/input.selectedSubFilterJets[i].fatjet.pt() );
      vars.FillVars( "ERatio_"+FilterJetName+"_HiggsJet",i,itFiltJet->energy()/input.selectedSubFilterJets[i].fatjet.energy() );

      TLorentzVector restframeFiltJet = BoostedUtils::GetTLorentzVector(itFiltJet->p4());
      restframeFiltJet.Boost(fatJetBoost);
      vars.FillVars( "Pt_"+FilterJetName+"_RestFrame_HiggsJet",i,restframeFiltJet.Pt());
      vars.FillVars( "Eta_"+FilterJetName+"_RestFrame_HiggsJet",i,restframeFiltJet.Eta());
      vars.FillVars( "Phi_"+FilterJetName+"_RestFrame_HiggsJet",i,restframeFiltJet.Phi()); 
    }
    
    if(input.selectedSubFilterJets[i].filterjets.size()>1){
      vars.FillVars( "Dr_Filterjet12_HiggsJet",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[0],input.selectedSubFilterJets[i].filterjets[1]) );
      vars.FillVars( "CosThetaStar_Filterjet12_HiggsJet",i,BoostedUtils::CosThetaStar(input.selectedSubFilterJets[i].filterjets[0].p4(),input.selectedSubFilterJets[i].filterjets[1].p4()) );
      vars.FillVars( "M2_HiggsJet",i,(input.selectedSubFilterJets[i].filterjets[0].p4()+input.selectedSubFilterJets[i].filterjets[1].p4()).M() );
      vars.FillVars( "Pt2_HiggsJet",i,(input.selectedSubFilterJets[i].filterjets[0].p4()+input.selectedSubFilterJets[i].filterjets[1].p4()).Pt() );
    }
    if(input.selectedSubFilterJets[i].filterjets.size()>2){
      vars.FillVars( "Dr_Filterjet23_HiggsJet",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[1],input.selectedSubFilterJets[i].filterjets[2]) );
      vars.FillVars( "Dr_Filterjet13_HiggsJet",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[0],input.selectedSubFilterJets[i].filterjets[2]) );
      vars.FillVars( "CosThetaStar_Filterjet23_HiggsJet",i,BoostedUtils::CosThetaStar(input.selectedSubFilterJets[i].filterjets[1].p4(),input.selectedSubFilterJets[i].filterjets[2].p4()) );
      vars.FillVars( "CosThetaStar_Filterjet13_HiggsJet",i,BoostedUtils::CosThetaStar(input.selectedSubFilterJets[i].filterjets[0].p4(),input.selectedSubFilterJets[i].filterjets[2].p4()) );
      vars.FillVars( "M3_HiggsJet",i,(input.selectedSubFilterJets[i].filterjets[0].p4()+input.selectedSubFilterJets[i].filterjets[1].p4()+input.selectedSubFilterJets[i].filterjets[2].p4()).M() );
      vars.FillVars( "Pt3_HiggsJet",i,(input.selectedSubFilterJets[i].filterjets[0].p4()+input.selectedSubFilterJets[i].filterjets[1].p4()+input.selectedSubFilterJets[i].filterjets[2].p4()).Pt() );
    }
    
    vars.FillVars( "M2_SingleTag_HiggsJet",i,BoostedUtils::GetHiggsMass(input.selectedSubFilterJets[i], 2, 1, 0.814) );
    vars.FillVars( "M3_SingleTag_HiggsJet",i,BoostedUtils::GetHiggsMass(input.selectedSubFilterJets[i], 3, 1, 0.814) );
    vars.FillVars( "M2_DoubleTag_HiggsJet",i,BoostedUtils::GetHiggsMass(input.selectedSubFilterJets[i], 2, 2, 0.814) );
    vars.FillVars( "M3_DoubleTag_HiggsJet",i,BoostedUtils::GetHiggsMass(input.selectedSubFilterJets[i], 3, 2, 0.814) );
    
    std::vector<pat::Jet> filterJets = BoostedUtils::GetHiggsFilterJets(input.selectedSubFilterJets[i], 4);
    if(filterJets.size()>0) vars.FillVars( "CSV1_HiggsJet",i,filterJets[0].bDiscriminator(btagger) );
    if(filterJets.size()>1) vars.FillVars( "CSV2_HiggsJet",i,filterJets[1].bDiscriminator(btagger) );
    if(filterJets.size()>2) vars.FillVars( "CSV3_HiggsJet",i,filterJets[2].bDiscriminator(btagger) );
    if(filterJets.size()>3) vars.FillVars( "CSV4_HiggsJet",i,filterJets[3].bDiscriminator(btagger) );
    
    if(input.selectedHEPTopJets.size()>0) vars.FillVars( "Dr_TopJet1_HiggsJet",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].fatjet,input.selectedHEPTopJets[0].fatjet) );
    if(input.selectedHEPTopJets.size()>1) vars.FillVars( "Dr_TopJet2_HiggsJet",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].fatjet,input.selectedHEPTopJets[1].fatjet) );
    if(input.selectedHEPTopJets.size()>2) vars.FillVars( "Dr_TopJet3_HiggsJet",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].fatjet,input.selectedHEPTopJets[2].fatjet) );
    if(input.selectedHEPTopJets.size()>3) vars.FillVars( "Dr_TopJet4_HiggsJet",i,BoostedUtils::DeltaR(input.selectedSubFilterJets[i].fatjet,input.selectedHEPTopJets[3].fatjet) );
    
    vars.FillVars( "Subjetiness1_HiggsJet",i,input.selectedSubFilterJets[i].subjettiness1 );
    vars.FillVars( "Subjetiness2_HiggsJet",i,input.selectedSubFilterJets[i].subjettiness2 );
    vars.FillVars( "Subjetiness3_HiggsJet",i,input.selectedSubFilterJets[i].subjettiness3 );
    vars.FillVars( "Subjetiness4_HiggsJet",i,input.selectedSubFilterJets[i].subjettiness4 );
    
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
    
    vars.FillVars( "IdxAk5_Filterjet1_HiggsJet",i,idx1);
    vars.FillVars( "IdxAk5_Filterjet2_HiggsJet",i,idx2);
    vars.FillVars( "IdxAk5_Filterjet3_HiggsJet",i,idx3);
    
    math::XYZTLorentzVector primlepvec = math::XYZTLorentzVector();
    if(input.selectedElectronsLoose.size()>0 || input.selectedMuonsLoose.size()>0)
	    primlepvec = BoostedUtils::GetPrimLepVec(input.selectedElectronsLoose,input.selectedMuonsLoose);
    vars.FillVars( "Dr_Lepton_HiggsJet",i,primlepvec.Pt()>5 ? BoostedUtils::DeltaR(primlepvec,input.selectedSubFilterJets[i].fatjet.p4()) : -1);
  }
}
