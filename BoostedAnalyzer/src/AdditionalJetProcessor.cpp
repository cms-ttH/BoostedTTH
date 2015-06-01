#include "BoostedTTH/BoostedAnalyzer/interface/AdditionalJetProcessor.hpp"

using namespace std;

AdditionalJetProcessor::AdditionalJetProcessor (){}
AdditionalJetProcessor::~AdditionalJetProcessor (){}


void AdditionalJetProcessor::Init(const InputCollections& input,VariableContainer& vars){

  vars.InitVar( "N_AdditionalGenBJets",-1,"I" );
  vars.InitVars( "AdditionalGenBJet_Pt",-9.,"N_AdditionalGenBJets" );
  vars.InitVars( "AdditionalGenBJet_Eta",-9.,"N_AdditionalGenBJets" );
  vars.InitVars( "AdditionalGenBJet_Phi",-9.,"N_AdditionalGenBJets" );
  vars.InitVars( "AdditionalGenBJet_E",-9.,"N_AdditionalGenBJets" );
  vars.InitVars( "AdditionalGenBJet_IsProper",-9.,"N_AdditionalGenBJets" );
  vars.InitVars( "AdditionalGenBJet_HadronPt",-9.,"N_AdditionalGenBJets" );

  vars.InitVar( "N_AdditionalGenBJetsProper",-1,"I" );
  vars.InitVars( "AdditionalGenBJetProper_Pt",-9.,"N_AdditionalGenBJetsProper" );
  vars.InitVars( "AdditionalGenBJetProper_Eta",-9.,"N_AdditionalGenBJetsProper" );
  vars.InitVars( "AdditionalGenBJetProper_Phi",-9.,"N_AdditionalGenBJetsProper" );
  vars.InitVars( "AdditionalGenBJetProper_E",-9.,"N_AdditionalGenBJetsProper" );

  vars.InitVar( "N_AdditionalGenBJetsPseudo",-1,"I" );
  vars.InitVars( "AdditionalGenBJetPseudo_Pt",-9.,"N_AdditionalGenBJetsPseudo" );
  vars.InitVars( "AdditionalGenBJetPseudo_Eta",-9.,"N_AdditionalGenBJetsPseudo" );
  vars.InitVars( "AdditionalGenBJetPseudo_Phi",-9.,"N_AdditionalGenBJetsPseudo" );
  vars.InitVars( "AdditionalGenBJetPseudo_E",-9.,"N_AdditionalGenBJetsPseudo" );

  vars.InitVar( "N_AdditionalGenCJets",-1,"I" );
  vars.InitVars( "AdditionalGenCJet_Pt",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_Eta",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_Phi",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_E",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_IsProper",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_HadronPt",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_Dr_CfromW",-9.,"N_AdditionalGenCJets" );

  vars.InitVar( "N_AdditionalGenCJetsProper",-1,"I" );
  vars.InitVars( "AdditionalGenCJetProper_Pt",-9.,"N_AdditionalGenCJetsProper" );
  vars.InitVars( "AdditionalGenCJetProper_Eta",-9.,"N_AdditionalGenCJetsProper" );
  vars.InitVars( "AdditionalGenCJetProper_Phi",-9.,"N_AdditionalGenCJetsProper" );
  vars.InitVars( "AdditionalGenCJetProper_E",-9.,"N_AdditionalGenCJetsProper" );

  vars.InitVar( "N_AdditionalGenCJetsPseudo",-1,"I" );
  vars.InitVars( "AdditionalGenCJetPseudo_Pt",-9.,"N_AdditionalGenCJetsPseudo" );
  vars.InitVars( "AdditionalGenCJetPseudo_Eta",-9.,"N_AdditionalGenCJetsPseudo" );
  vars.InitVars( "AdditionalGenCJetPseudo_Phi",-9.,"N_AdditionalGenCJetsPseudo" );
  vars.InitVars( "AdditionalGenCJetPseudo_E",-9.,"N_AdditionalGenCJetsPseudo" );

  vars.InitVar( "GenEvt_TTxId",-1,"I" );
  vars.InitVar( "GenEvt_TTxId_wo_PseudoAdditional",-1,"I" );
  vars.InitVar( "GenEvt_TTxId_w_PseudoAdditional",-1,"I" );

  initialized = true;
}


void AdditionalJetProcessor::Process(const InputCollections& input,VariableContainer& vars){
  
  if(!initialized) cerr << "tree processor not initialized" << endl;
  if(input.genTopEvt.TTxIsFilled()){
    std::vector<reco::GenJet> additional_b_genjets = input.genTopEvt.GetAdditionalBGenJets();
    std::vector<reco::GenJet> additional_c_genjets = input.genTopEvt.GetAdditionalCGenJets();
    std::vector<bool>         additional_b_genjets_fromtop = input.genTopEvt.AreAdditionalBGenJetsFromTop();
    std::vector<bool>         additional_c_genjets_fromtop = input.genTopEvt.AreAdditionalCGenJetsFromTop();
    std::vector<reco::GenParticle> additional_b_genjets_hadron = input.genTopEvt.GetAdditionalBGenJetsHadron();
    std::vector<reco::GenParticle> additional_c_genjets_hadron = input.genTopEvt.GetAdditionalCGenJetsHadron();
    std::vector<reco::GenJet> additional_b_pseudogenjets = input.genTopEvt.GetPseudoAdditionalBGenJets();
    std::vector<reco::GenJet> additional_c_pseudogenjets = input.genTopEvt.GetPseudoAdditionalCGenJets();
    std::vector<reco::GenJet> additional_b_propergenjets = input.genTopEvt.GetProperAdditionalBGenJets();
    std::vector<reco::GenJet> additional_c_propergenjets = input.genTopEvt.GetProperAdditionalCGenJets();
    std::vector<reco::GenParticle> q1;
    std::vector<reco::GenParticle> q2;
    
    if(input.genTopEvt.IsFilled()){
      q1=input.genTopEvt.GetAllWQuarks();
      q2=input.genTopEvt.GetAllWAntiQuarks();
    }
    
    vars.FillVar( "N_AdditionalGenBJets", additional_b_genjets.size());
    for(uint i=0; i<additional_b_genjets.size(); i++){
      vars.FillVars( "AdditionalGenBJet_Pt", i, additional_b_genjets[i].pt());
      vars.FillVars( "AdditionalGenBJet_Eta", i, additional_b_genjets[i].eta());
      vars.FillVars( "AdditionalGenBJet_Phi", i, additional_b_genjets[i].phi());
      vars.FillVars( "AdditionalGenBJet_E", i, additional_b_genjets[i].energy());
      vars.FillVars( "AdditionalGenBJet_IsProper", i, !(additional_b_genjets_fromtop[i]));
      vars.FillVars( "AdditionalGenBJet_HadronPt", i, additional_b_genjets_hadron[i].pt());
    }
    
    vars.FillVar( "N_AdditionalGenBJetsProper",additional_b_propergenjets.size());
    for(uint i=0; i<additional_b_propergenjets.size(); i++){
      vars.FillVars( "AdditionalGenBJetProper_Pt", i, additional_b_propergenjets[i].pt());
      vars.FillVars( "AdditionalGenBJetProper_Eta", i, additional_b_propergenjets[i].eta());
      vars.FillVars( "AdditionalGenBJetProper_Phi", i, additional_b_propergenjets[i].phi());
      vars.FillVars( "AdditionalGenBJetProper_E", i, additional_b_propergenjets[i].energy());
    }
    
    vars.FillVar( "N_AdditionalGenBJetsPseudo",additional_b_pseudogenjets.size());
    for(uint i=0; i<additional_b_pseudogenjets.size(); i++){
      vars.FillVars( "AdditionalGenBJetPseudo_Pt", i, additional_b_pseudogenjets[i].pt());
      vars.FillVars( "AdditionalGenBJetPseudo_Eta", i, additional_b_pseudogenjets[i].eta());
      vars.FillVars( "AdditionalGenBJetPseudo_Phi", i, additional_b_pseudogenjets[i].phi());
      vars.FillVars( "AdditionalGenBJetPseudo_E", i, additional_b_pseudogenjets[i].energy());
    }
    
    vars.FillVar( "N_AdditionalGenCJets",additional_c_genjets.size());
    for(uint i=0; i<additional_c_genjets.size(); i++){
      vars.FillVars( "AdditionalGenCJet_Pt", i, additional_c_genjets[i].pt());
      vars.FillVars( "AdditionalGenCJet_Eta", i, additional_c_genjets[i].eta());
      vars.FillVars( "AdditionalGenCJet_Phi", i, additional_c_genjets[i].phi());
      vars.FillVars( "AdditionalGenCJet_E", i, additional_c_genjets[i].energy());
      vars.FillVars( "AdditionalGenCJet_IsProper", i, !(additional_c_genjets_fromtop[i]));
      vars.FillVars( "AdditionalGenCJet_HadronPt", i, additional_c_genjets_hadron[i].pt());
      float drQ=5;
      for(uint i=0; i<q1.size(); i++){
	if(abs(q1[i].pdgId())==4){
	  drQ=fmin(drQ,BoostedUtils::DeltaR(q1[i].p4(),additional_c_genjets_hadron[i].p4()));
	}
      }
      for(uint i=0; i<q2.size(); i++){
	if(abs(q2[i].pdgId())==4){
	  drQ=fmin(drQ,BoostedUtils::DeltaR(q2[i].p4(),additional_c_genjets_hadron[i].p4()));
	}
      }    
      vars.FillVars( "AdditionalGenCJet_Dr_CfromW", i, drQ);
    }
    
    vars.FillVar( "N_AdditionalGenCJetsProper",additional_c_propergenjets.size());
    for(uint i=0; i<additional_c_propergenjets.size(); i++){
      vars.FillVars( "AdditionalGenCJetProper_Pt", i, additional_c_propergenjets[i].pt());
      vars.FillVars( "AdditionalGenCJetProper_Eta", i, additional_c_propergenjets[i].eta());
      vars.FillVars( "AdditionalGenCJetProper_Phi", i, additional_c_propergenjets[i].phi());
      vars.FillVars( "AdditionalGenCJetProper_E", i, additional_c_propergenjets[i].energy());
    }
    
    vars.FillVar( "N_AdditionalGenCJetsPseudo", additional_c_pseudogenjets.size());
    for(uint i=0; i<additional_c_pseudogenjets.size(); i++){
      vars.FillVars( "AdditionalGenCJetPseudo_Pt", i, additional_c_pseudogenjets[i].pt());
      vars.FillVars( "AdditionalGenCJetPseudo_Eta", i, additional_c_pseudogenjets[i].eta());
      vars.FillVars( "AdditionalGenCJetPseudo_Phi", i, additional_c_pseudogenjets[i].phi());
      vars.FillVars( "AdditionalGenCJetPseudo_E", i, additional_c_pseudogenjets[i].energy());
    }
    vars.FillVar( "GenEvt_TTxId",input.genTopEvt.GetTTxId());
    vars.FillVar( "GenEvt_TTxId_w_PseudoAdditional",input.genTopEvt.GetTTxId(true));
    vars.FillVar( "GenEvt_TTxId_wo_PseudoAdditional",input.genTopEvt.GetTTxId(false));
  }
}
