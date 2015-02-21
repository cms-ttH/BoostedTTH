#include "BoostedTTH/BoostedAnalyzer/interface/BoostedJetVarProcessor.hpp"

using namespace std;

BoostedJetVarProcessor::BoostedJetVarProcessor (){}
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

  vars.InitVars( "TopJet_E_B","N_TopJets" );
  vars.InitVars( "TopJet_Pt_B","N_TopJets" );
  vars.InitVars( "TopJet_Eta_B","N_TopJets" );
  vars.InitVars( "TopJet_Phi_B","N_TopJets" );
  vars.InitVars( "TopJet_M_B","N_TopJets" );

  vars.InitVars( "TopJet_E_W1","N_TopJets" );
  vars.InitVars( "TopJet_Pt_W1","N_TopJets" );
  vars.InitVars( "TopJet_Eta_W1","N_TopJets" );
  vars.InitVars( "TopJet_Phi_W1","N_TopJets" );
  vars.InitVars( "TopJet_M_W1","N_TopJets" );

  vars.InitVars( "TopJet_E_W2","N_TopJets" );
  vars.InitVars( "TopJet_Pt_W2","N_TopJets" );
  vars.InitVars( "TopJet_Eta_W2","N_TopJets" );
  vars.InitVars( "TopJet_Phi_W2","N_TopJets" );
  vars.InitVars( "TopJet_M_W2","N_TopJets" );

  vars.InitVars( "TopJet_E_W","N_TopJets" );
  vars.InitVars( "TopJet_Pt_W","N_TopJets" );
  vars.InitVars( "TopJet_Eta_W","N_TopJets" );
  vars.InitVars( "TopJet_Phi_W","N_TopJets" );
  vars.InitVars( "TopJet_M_W","N_TopJets" );

  vars.InitVars( "TopJet_E_Top","N_TopJets" );
  vars.InitVars( "TopJet_Pt_Top","N_TopJets" );
  vars.InitVars( "TopJet_Eta_Top","N_TopJets" );
  vars.InitVars( "TopJet_Phi_Top","N_TopJets" );
  vars.InitVars( "TopJet_M_Top","N_TopJets" );

  vars.InitVars( "TopJet_M12","N_TopJets" );
  vars.InitVars( "TopJet_M13","N_TopJets" );
  vars.InitVars( "TopJet_M23","N_TopJets" );

  vars.InitVars( "TopJet_CSV_B","N_TopJets" );
  vars.InitVars( "TopJet_CSV_W1","N_TopJets" );
  vars.InitVars( "TopJet_CSV_W2","N_TopJets" );

  vars.InitVars( "TopJet_Dr_B_Top","N_TopJets" );
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

  vars.InitVars( "TopJet_IdxAk5_W1","N_TopJets" );
  vars.InitVars( "TopJet_IdxAk5_W2","N_TopJets" );
  vars.InitVars( "TopJet_IdxAk5_B","N_TopJets" );
  vars.InitVars( "TopJet_Dr_Lepton","N_TopJets" );
  vars.InitVars( "TopJet_TaggedB","N_TopJets" );

  vars.InitVars( "TopJet_Pt_Bbtag","N_TopJets" );
  vars.InitVars( "TopJet_Pt_W1btag","N_TopJets" );
  vars.InitVars( "TopJet_Pt_W2btag","N_TopJets" );
  vars.InitVars( "TopJet_Eta_Bbtag","N_TopJets" );
  vars.InitVars( "TopJet_Eta_W1btag","N_TopJets" );
  vars.InitVars( "TopJet_Eta_W2btag","N_TopJets" );
  vars.InitVars( "TopJet_Phi_Bbtag","N_TopJets" );
  vars.InitVars( "TopJet_Phi_W1btag","N_TopJets" );
  vars.InitVars( "TopJet_Phi_W2btag","N_TopJets" );
  vars.InitVars( "TopJet_E_Bbtag","N_TopJets" );
  vars.InitVars( "TopJet_E_W1btag","N_TopJets" );
  vars.InitVars( "TopJet_E_W2btag","N_TopJets" );
  vars.InitVars( "TopJet_CSV_Bbtag","N_TopJets" );
  vars.InitVars( "TopJet_CSV_W1btag","N_TopJets" );
  vars.InitVars( "TopJet_CSV_W2btag","N_TopJets" );
  vars.InitVars( "TopJet_M_Wbtag","N_TopJets" );
  vars.InitVars( "TopJet_M_BW1btag","N_TopJets" );
  vars.InitVars( "TopJet_M_BW2btag","N_TopJets" );

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
  
  vars.InitVars( "HiggsJet_Pt_Filterjet1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Pt_Filterjet2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Pt_Filterjet3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Pt_Filterjet4","N_HiggsJets" );
  vars.InitVars( "HiggsJet_E_Filterjet1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_E_Filterjet2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_E_Filterjet3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_E_Filterjet4","N_HiggsJets" );
  vars.InitVars( "HiggsJet_M_Filterjet1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_M_Filterjet2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_M_Filterjet3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_M_Filterjet4","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Eta_Filterjet1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Eta_Filterjet2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Eta_Filterjet3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Eta_Filterjet4","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Phi_Filterjet1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Phi_Filterjet2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Phi_Filterjet3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Phi_Filterjet4","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CSV_Filterjet1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CSV_Filterjet2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CSV_Filterjet3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CSV_Filterjet4","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Filterjet1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Filterjet2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Filterjet3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Filterjet4","N_HiggsJets" );
  vars.InitVars( "HiggsJet_PtRatio_Filterjet1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_PtRatio_Filterjet2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_PtRatio_Filterjet3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_PtRatio_Filterjet4","N_HiggsJets" );
  vars.InitVars( "HiggsJet_ERatio_Filterjet1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_ERatio_Filterjet2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_ERatio_Filterjet3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_ERatio_Filterjet4","N_HiggsJets" );
  
  vars.InitVars( "HiggsJet_Dr_Filterjet12","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Filterjet13","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Filterjet23","N_HiggsJets" );
  
  vars.InitVars( "HiggsJet_E_Filterjet1_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Pt_Filterjet1_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Eta_Filterjet1_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Phi_Filterjet1_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_E_Filterjet2_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Pt_Filterjet2_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Eta_Filterjet2_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Phi_Filterjet2_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_E_Filterjet3_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Pt_Filterjet3_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Eta_Filterjet3_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Phi_Filterjet3_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_E_Filterjet4_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Pt_Filterjet4_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Eta_Filterjet4_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Phi_Filterjet4_RestFrame","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CosThetaStar_Filterjet12","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CosThetaStar_Filterjet13","N_HiggsJets" );
  vars.InitVars( "HiggsJet_CosThetaStar_Filterjet23","N_HiggsJets" );
  vars.InitVars( "HiggsJet_IdxAk5_Filterjet1","N_HiggsJets" );
  vars.InitVars( "HiggsJet_IdxAk5_Filterjet2","N_HiggsJets" );
  vars.InitVars( "HiggsJet_IdxAk5_Filterjet3","N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_Lepton","N_HiggsJets" );

  initialized=true;
}


void BoostedJetVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  const char* btagger="combinedInclusiveSecondaryVertexV2BJetTags";

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

    vars.FillVars( "TopJet_E_B",i,input.selectedHEPTopJets[i].nonW.energy() );
    vars.FillVars( "TopJet_Pt_B",i,input.selectedHEPTopJets[i].nonW.pt() );
    vars.FillVars( "TopJet_Eta_B",i,input.selectedHEPTopJets[i].nonW.eta() );
    vars.FillVars( "TopJet_Phi_B",i,input.selectedHEPTopJets[i].nonW.phi() );
    vars.FillVars( "TopJet_M_B",i,input.selectedHEPTopJets[i].nonW.mass() );

    vars.FillVars( "TopJet_E_W1",i,input.selectedHEPTopJets[i].W1.energy() );
    vars.FillVars( "TopJet_Pt_W1",i,input.selectedHEPTopJets[i].W1.pt() );
    vars.FillVars( "TopJet_Eta_W1",i,input.selectedHEPTopJets[i].W1.eta() );
    vars.FillVars( "TopJet_Phi_W1",i,input.selectedHEPTopJets[i].W1.phi() );
    vars.FillVars( "TopJet_M_W1",i,input.selectedHEPTopJets[i].W1.mass() );

    vars.FillVars( "TopJet_E_W2",i,input.selectedHEPTopJets[i].W2.energy() );
    vars.FillVars( "TopJet_Pt_W2",i,input.selectedHEPTopJets[i].W2.pt() );
    vars.FillVars( "TopJet_Eta_W2",i,input.selectedHEPTopJets[i].W2.eta() );
    vars.FillVars( "TopJet_Phi_W2",i,input.selectedHEPTopJets[i].W2.phi() );
    vars.FillVars( "TopJet_M_W2",i,input.selectedHEPTopJets[i].W2.mass() );

    vars.FillVars( "TopJet_E_W",i,input.selectedHEPTopJets[i].W.energy() );
    vars.FillVars( "TopJet_Pt_W",i,input.selectedHEPTopJets[i].W.pt() );
    vars.FillVars( "TopJet_Eta_W",i,input.selectedHEPTopJets[i].W.eta() );
    vars.FillVars( "TopJet_Phi_W",i,input.selectedHEPTopJets[i].W.phi() );
    vars.FillVars( "TopJet_M_W",i,input.selectedHEPTopJets[i].W.mass() );

    vars.FillVars( "TopJet_E_Top",i,input.selectedHEPTopJets[i].topjet.energy() );
    vars.FillVars( "TopJet_Pt_Top",i,input.selectedHEPTopJets[i].topjet.pt() );
    vars.FillVars( "TopJet_Eta_Top",i,input.selectedHEPTopJets[i].topjet.eta() );
    vars.FillVars( "TopJet_Phi_Top",i,input.selectedHEPTopJets[i].topjet.phi() );
    vars.FillVars( "TopJet_M_Top",i,input.selectedHEPTopJets[i].topjet.mass() );

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

    vars.FillVars( "TopJet_CSV_B",i,fmax(input.selectedHEPTopJets[i].nonW.bDiscriminator(btagger),-.1) );
    vars.FillVars( "TopJet_CSV_W1",i,fmax(input.selectedHEPTopJets[i].W1.bDiscriminator(btagger),-.1) );
    vars.FillVars( "TopJet_CSV_W2",i,fmax(input.selectedHEPTopJets[i].W2.bDiscriminator(btagger),-.1) );
    
    //Definition with b-jet == highest CSV
    vector<pat::Jet> subjets;
    subjets.push_back(input.selectedHEPTopJets[i].nonW);
    subjets.push_back(input.selectedHEPTopJets[i].W1);
    subjets.push_back(input.selectedHEPTopJets[i].W2);

    BoostedUtils::TopSubjetCSVDef(subjets);

    vector<math::XYZTLorentzVector> topvecs_bycsv = BoostedUtils::GetJetVecs(subjets);
    vars.FillVars( "TopJet_TaggedB",i,BoostedUtils::GetTopTag(input.selectedHEPTopJets[i],0.2,120,true) );
    vars.FillVars( "TopJet_Pt_Bbtag",i,subjets[0].pt() );
    vars.FillVars( "TopJet_Pt_W1btag",i,subjets[1].pt() );
    vars.FillVars( "TopJet_Pt_W2btag",i,subjets[2].pt() );
    vars.FillVars( "TopJet_Eta_Bbtag",i,subjets[0].eta() );
    vars.FillVars( "TopJet_Eta_W1btag",i,subjets[1].eta() );
    vars.FillVars( "TopJet_Eta_W2btag",i,subjets[2].eta() );
    vars.FillVars( "TopJet_Phi_Bbtag",i,subjets[0].phi() );
    vars.FillVars( "TopJet_Phi_W1btag",i,subjets[1].phi() );
    vars.FillVars( "TopJet_Phi_W2btag",i,subjets[2].phi() );
    vars.FillVars( "TopJet_E_Bbtag",i,subjets[0].energy() );
    vars.FillVars( "TopJet_E_W1btag",i,subjets[1].energy() );
    vars.FillVars( "TopJet_E_W2btag",i,subjets[2].energy() );
    vars.FillVars( "TopJet_CSV_Bbtag",i,fmax(subjets[0].bDiscriminator(btagger),-.1) );
    vars.FillVars( "TopJet_CSV_W1btag",i,fmax(subjets[1].bDiscriminator(btagger),-.1) );
    vars.FillVars( "TopJet_CSV_W2btag",i,fmax(subjets[2].bDiscriminator(btagger),-.1) );
    vars.FillVars( "TopJet_M_Wbtag",i,(topvecs_bycsv[1]+topvecs_bycsv[2]).M() );
    vars.FillVars( "TopJet_M_BW1btag",i,(topvecs_bycsv[0]+topvecs_bycsv[1]).M() );
    vars.FillVars( "TopJet_M_BW2btag",i,(topvecs_bycsv[0]+topvecs_bycsv[2]).M() );
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


    vars.FillVars( "TopJet_IdxAk5_W1",i,idxW1 );
    vars.FillVars( "TopJet_IdxAk5_W2",i,idxW2 );
    vars.FillVars( "TopJet_IdxAk5_B",i,idxB );
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
      
      vars.FillVars( "HiggsJet_E_"+FilterJetName+"",i,itFiltJet->energy() );
      vars.FillVars( "HiggsJet_Pt_"+FilterJetName+"",i,itFiltJet->pt() );
      vars.FillVars( "HiggsJet_M_"+FilterJetName+"",i,itFiltJet->mass() );
      vars.FillVars( "HiggsJet_Eta_"+FilterJetName+"",i,itFiltJet->eta() );
      vars.FillVars( "HiggsJet_Phi_"+FilterJetName+"",i,itFiltJet->phi() );
      vars.FillVars( "HiggsJet_CSV_"+FilterJetName+"",i,itFiltJet->bDiscriminator(btagger) );
      vars.FillVars( "HiggsJet_Dr_"+FilterJetName+"",i,BoostedUtils::DeltaR(*itFiltJet,input.selectedSubFilterJets[i].fatjet) );
      vars.FillVars( "HiggsJet_PtRatio_"+FilterJetName+"",i,itFiltJet->pt()/input.selectedSubFilterJets[i].fatjet.pt() );
      vars.FillVars( "HiggsJet_ERatio_"+FilterJetName+"",i,itFiltJet->energy()/input.selectedSubFilterJets[i].fatjet.energy() );

      TLorentzVector restframeFiltJet = BoostedUtils::GetTLorentzVector(itFiltJet->p4());
      restframeFiltJet.Boost(fatJetBoost);
      vars.FillVars( "HiggsJet_Pt_"+FilterJetName+"_RestFrame",i,restframeFiltJet.Pt());
      vars.FillVars( "HiggsJet_Eta_"+FilterJetName+"_RestFrame",i,restframeFiltJet.Eta());
      vars.FillVars( "HiggsJet_Phi_"+FilterJetName+"_RestFrame",i,restframeFiltJet.Phi()); 
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
    
    vars.FillVars( "HiggsJet_IdxAk5_Filterjet1",i,idx1);
    vars.FillVars( "HiggsJet_IdxAk5_Filterjet2",i,idx2);
    vars.FillVars( "HiggsJet_IdxAk5_Filterjet3",i,idx3);
    
    math::XYZTLorentzVector primlepvec = math::XYZTLorentzVector();
    if(input.selectedElectronsLoose.size()>0 || input.selectedMuonsLoose.size()>0)
	    primlepvec = BoostedUtils::GetPrimLepVec(input.selectedElectronsLoose,input.selectedMuonsLoose);
    vars.FillVars( "HiggsJet_Dr_Lepton",i,primlepvec.Pt()>5 ? BoostedUtils::DeltaR(primlepvec,input.selectedSubFilterJets[i].fatjet.p4()) : -1);
  }
}
