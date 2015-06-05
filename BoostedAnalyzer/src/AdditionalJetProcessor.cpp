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
  vars.InitVars( "AdditionalGenBJet_FromTopType",-9.,"N_AdditionalGenBJets" );
  vars.InitVars( "AdditionalGenBJet_HadronPt",-9.,"N_AdditionalGenBJets" );
  vars.InitVars( "AdditionalGenBJet_RecoJetPt",-9.,"N_AdditionalGenBJets" );
  vars.InitVars( "AdditionalGenBJet_RecoJetCSV",-9.,"N_AdditionalGenBJets" );
  vars.InitVars( "AdditionalGenBJet_HadronId",-9.,"N_AdditionalGenBJets" );
  vars.InitVars( "AdditionalGenBJet_Dr_BfromTTH",-9.,"N_AdditionalGenBJets" );
  vars.InitVars( "AdditionalGenBJet_Dr_QfromTTH",-9.,"N_AdditionalGenBJets" );
  vars.InitVars( "AdditionalGenBJet_NHadrons",-9.,"N_AdditionalGenBJets" );

  vars.InitVar( "N_AdditionalGenCJets",-1,"I" );
  vars.InitVars( "AdditionalGenCJet_Pt",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_Eta",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_Phi",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_E",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_FromTopType",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_HadronPt",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_RecoJetPt",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_RecoJetCSV",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_HadronId",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_Dr_CfromW",-9.,"N_AdditionalGenCJets" );
  vars.InitVars( "AdditionalGenCJet_NHadrons",-9.,"N_AdditionalGenCJets" );

  vars.InitVar( "N_AdditionalBHadrons",-1,"I" );
  vars.InitVars( "AdditionalBHadron_Pt",-9.,"N_AdditionalBHadrons" );
  vars.InitVars( "AdditionalBHadron_Eta",-9.,"N_AdditionalBHadrons" );
  vars.InitVars( "AdditionalBHadron_Phi",-9.,"N_AdditionalBHadrons" );
  vars.InitVars( "AdditionalBHadron_E",-9.,"N_AdditionalBHadrons" );
  vars.InitVars( "AdditionalBHadron_FromTopType",-9.,"N_AdditionalBHadrons" );
  vars.InitVars( "AdditionalBHadron_Mother",-9.,"N_AdditionalBHadrons" );
  vars.InitVars( "AdditionalBHadron_Dr_BfromTTH",-9.,"N_AdditionalBHadrons" );
  vars.InitVars( "AdditionalBHadron_Dr_QfromTTH",-9.,"N_AdditionalBHadrons" );

  vars.InitVar( "N_AdditionalCHadrons",-1,"I" );
  vars.InitVars( "AdditionalCHadron_Pt",-9.,"N_AdditionalCHadrons" );
  vars.InitVars( "AdditionalCHadron_Eta",-9.,"N_AdditionalCHadrons" );
  vars.InitVars( "AdditionalCHadron_Phi",-9.,"N_AdditionalCHadrons" );
  vars.InitVars( "AdditionalCHadron_E",-9.,"N_AdditionalCHadrons" );
  vars.InitVars( "AdditionalCHadron_FromTopType",-9.,"N_AdditionalCHadrons" );
  vars.InitVars( "AdditionalCHadron_Mother",-9.,"N_AdditionalBHadrons" );
  vars.InitVars( "AdditionalCHadron_Dr_CfromW",-9.,"N_AdditionalCHadrons" );

  vars.InitVar( "GenEvt_TTxId",-1,"I" );
  vars.InitVar( "GenEvt_TTxId_wo_PseudoAdditional",-1,"I" );
  vars.InitVar( "GenEvt_TTxId_w_PseudoAdditional",-1,"I" );

  initialized = true;
}

const pat::Jet* AdditionalJetProcessor::GetPatJet(const reco::GenJet& genjet,const std::vector<pat::Jet>& patjets){
  for(auto patjet=patjets.begin(); patjet!=patjets.end(); patjet++){
    if(patjet->pt()>0 && genjet.pt()>0 && BoostedUtils::DeltaR(patjet->p4(),genjet.p4())<0.2){
      return &(*patjet);
      break;
    }
  }
  return 0;
}


void AdditionalJetProcessor::Process(const InputCollections& input,VariableContainer& vars){
  
  if(!initialized) cerr << "tree processor not initialized" << endl;

  const char* btagger="combinedInclusiveSecondaryVertexV2BJetTags";

  if(input.genTopEvt.TTxIsFilled()){
    std::vector<reco::GenJet> additional_b_genjets = input.genTopEvt.GetAdditionalBGenJets();
    std::vector<reco::GenJet> additional_c_genjets = input.genTopEvt.GetAdditionalCGenJets();
    std::vector<const pat::Jet*> additional_b_genjets_recojets;
    std::vector<const pat::Jet*> additional_c_genjets_recojets;
    for(auto genbjet = additional_b_genjets.begin(); genbjet != additional_b_genjets.end(); genbjet++){
      additional_b_genjets_recojets.push_back(GetPatJet(*genbjet,input.selectedJets));
    }
    for(auto gencjet = additional_c_genjets.begin(); gencjet != additional_c_genjets.end(); gencjet++){
      additional_c_genjets_recojets.push_back(GetPatJet(*gencjet,input.selectedJets));
    }


    std::vector<int>         additional_b_genjets_fromtop = input.genTopEvt.GetAdditionalBGenJetsFromTopType();
    std::vector<int>         additional_c_genjets_fromtop = input.genTopEvt.GetAdditionalCGenJetsFromTopType();
    std::vector<int>         additional_b_genjets_nhadrons = input.genTopEvt.GetAdditionalBGenJetsNHadrons();
    std::vector<int>         additional_c_genjets_nhadrons = input.genTopEvt.GetAdditionalCGenJetsNHadrons();

    std::vector<reco::GenParticle> additional_b_genjets_hadron = input.genTopEvt.GetAdditionalBGenJetsHadron();
    std::vector<reco::GenParticle> additional_c_genjets_hadron = input.genTopEvt.GetAdditionalCGenJetsHadron();
    std::vector<reco::GenParticle> q1;
    std::vector<reco::GenParticle> q2;
    std::vector<reco::GenParticle> btth;
    std::vector<reco::GenParticle> qtth;
    if(input.genTopEvt.IsFilled()){
      q1=input.genTopEvt.GetAllWQuarks();
      q2=input.genTopEvt.GetAllWAntiQuarks();
      std::vector<reco::GenParticle>  bhads=input.genTopEvt.GetAllTopHadDecayQuarks();
      std::vector<reco::GenParticle> bleps=input.genTopEvt.GetAllTopLepDecayQuarks();
      std::vector<reco::GenParticle> bhiggs=input.genTopEvt.GetHiggsDecayProducts();
      btth.reserve(bhads.size()+bleps.size()+bhiggs.size()) ;
      btth.insert(btth.end(),bhads.begin(),bhads.end());
      btth.insert(btth.end(),bleps.begin(),bleps.end());
      btth.insert(btth.end(),bhiggs.begin(),bhiggs.end());
      qtth.reserve(btth.size()+q1.size()+q2.size()) ;
      qtth.insert(qtth.end(),btth.begin(),btth.end());
      qtth.insert(qtth.end(),q1.begin(),q1.end());
      qtth.insert(qtth.end(),q2.begin(),q2.end());
    
    }
    
    vars.FillVar( "N_AdditionalGenBJets", additional_b_genjets.size());
    for(uint i=0; i<additional_b_genjets.size(); i++){
      vars.FillVars( "AdditionalGenBJet_Pt", i, additional_b_genjets[i].pt());
      vars.FillVars( "AdditionalGenBJet_Eta", i, additional_b_genjets[i].eta());
      vars.FillVars( "AdditionalGenBJet_Phi", i, additional_b_genjets[i].phi());
      vars.FillVars( "AdditionalGenBJet_E", i, additional_b_genjets[i].energy());
      vars.FillVars( "AdditionalGenBJet_FromTopType", i, additional_b_genjets_fromtop[i]);
      vars.FillVars( "AdditionalGenBJet_NHadrons", i, additional_b_genjets_nhadrons[i]);
      vars.FillVars( "AdditionalGenBJet_HadronPt", i, additional_b_genjets_hadron[i].pt());
      vars.FillVars( "AdditionalGenBJet_RecoJetPt", i, additional_b_genjets_recojets[i]!=0 ? additional_b_genjets_recojets[i]->pt() : -1);
      vars.FillVars( "AdditionalGenBJet_RecoJetCSV", i, additional_b_genjets_recojets[i]!=0 ? additional_b_genjets_recojets[i]->bDiscriminator(btagger) : -2);
      vars.FillVars( "AdditionalGenBJet_HadronId", i, additional_b_genjets_hadron[i].pdgId());
      float drB=5;
      for(uint k=0; k<btth.size(); k++){
	if(abs(btth[k].pdgId())==5&&btth[k].pt()>1&&additional_b_genjets[i].pt()>1){
	  float dr=BoostedUtils::DeltaR(btth[k].p4(),additional_b_genjets[i].p4());
	  if(dr>0&&dr<drB){
	    drB=dr;
	  }
	}
      }
      float drQ=5;
      for(uint k=0; k<qtth.size(); k++){
	if(qtth[k].pt()>1&&additional_b_genjets[i].pt()>1){
	  float dr = BoostedUtils::DeltaR(qtth[k].p4(),additional_b_genjets[i].p4());
	  if(dr>0&&dr<drQ){
	    drQ=dr;
	  }
	}
      }

      vars.FillVars( "AdditionalGenBJet_Dr_BfromTTH", i, drB);
      vars.FillVars( "AdditionalGenBJet_Dr_QfromTTH", i, drQ);

    }
    
    
    vars.FillVar( "N_AdditionalGenCJets",additional_c_genjets.size());
    for(uint i=0; i<additional_c_genjets.size(); i++){
      vars.FillVars( "AdditionalGenCJet_Pt", i, additional_c_genjets[i].pt());
      vars.FillVars( "AdditionalGenCJet_Eta", i, additional_c_genjets[i].eta());
      vars.FillVars( "AdditionalGenCJet_Phi", i, additional_c_genjets[i].phi());
      vars.FillVars( "AdditionalGenCJet_E", i, additional_c_genjets[i].energy());
      vars.FillVars( "AdditionalGenCJet_FromTopType", i, additional_c_genjets_fromtop[i]);
      vars.FillVars( "AdditionalGenCJet_NHadrons", i, additional_c_genjets_nhadrons[i]);
      vars.FillVars( "AdditionalGenCJet_HadronPt", i, additional_c_genjets_hadron[i].pt());
      vars.FillVars( "AdditionalGenCJet_RecoJetPt", i, additional_c_genjets_recojets[i]!=0 ? additional_c_genjets_recojets[i]->pt() : -1);
      vars.FillVars( "AdditionalGenCJet_RecoJetCSV", i, additional_c_genjets_recojets[i]!=0 ? additional_c_genjets_recojets[i]->bDiscriminator(btagger) : -2);
      vars.FillVars( "AdditionalGenCJet_HadronId", i, additional_c_genjets_hadron[i].pdgId());
      float drQ=5;
      for(uint k=0; k<q1.size(); k++){
	if(abs(q1[k].pdgId())==4&&q1[k].pt()>1&&additional_c_genjets[i].pt()>0){
	  float dr = BoostedUtils::DeltaR(q1[k].p4(),additional_c_genjets[i].p4());
	  if(dr>0&&dr<drQ){
	    drQ=dr;
	  }

	}
      }
      for(uint k=0; k<q2.size(); k++){
	if(abs(q2[k].pdgId())==4&&q2[k].pt()>1&&additional_c_genjets[i].pt()>0){
	  float dr=BoostedUtils::DeltaR(q2[k].p4(),additional_c_genjets[i].p4());
	  if(dr>0&&dr<drQ){
	    drQ=dr;
	  }
	}
      }    
      vars.FillVars( "AdditionalGenCJet_Dr_CfromW", i, drQ);
    }
    
    vars.FillVar( "GenEvt_TTxId",input.genTopEvt.GetTTxId());
    vars.FillVar( "GenEvt_TTxId_w_PseudoAdditional",input.genTopEvt.GetTTxId(true));
    vars.FillVar( "GenEvt_TTxId_wo_PseudoAdditional",input.genTopEvt.GetTTxId(false));
  

    std::vector<reco::GenParticle>bhadrons=input.genTopEvt.GetAdditionalBHadrons();
    std::vector<int> bmothers=input.genTopEvt.GetAdditionalBHadronMothers();
    std::vector<int> btopdecaytype=input.genTopEvt.GetAdditionalBHadronAfterTopType();
    vars.FillVar( "N_AdditionalBHadrons",bhadrons.size() );
    for(uint i=0; i<bhadrons.size(); i++){
      vars.FillVars( "AdditionalBHadron_Pt",i, bhadrons[i].pt());
      vars.FillVars( "AdditionalBHadron_Eta",i,bhadrons[i].eta() );
      vars.FillVars( "AdditionalBHadron_Phi",i,bhadrons[i].phi() );
      vars.FillVars( "AdditionalBHadron_E",i, bhadrons[i].energy());
      vars.FillVars( "AdditionalBHadron_FromTopType",i, btopdecaytype[i]);
      vars.FillVars( "AdditionalBHadron_Mother",i, bmothers[i]);
      float drB=5;
      for(uint k=0; k<btth.size(); k++){
	if(abs(btth[k].pdgId())==5&&btth[k].pt()>1&&bhadrons[i].pt()>1){
	  float dr =BoostedUtils::DeltaR(btth[k].p4(),bhadrons[i].p4());
	  drB=dr;
	}
      }
      float drQ=5;
      for(uint k=0; k<qtth.size(); k++){
	if(qtth[k].pt()>1&&bhadrons[i].pt()>1){
	  float dr = BoostedUtils::DeltaR(qtth[k].p4(),bhadrons[i].p4());
	  drQ=dr;
	}
      }

      vars.FillVars( "AdditionalBHadron_Dr_BfromTTH", i, drB);
      vars.FillVars( "AdditionalBHadron_Dr_QfromTTH", i, drQ);

    }
    std::vector<reco::GenParticle>chadrons=input.genTopEvt.GetAdditionalCHadrons();
    std::vector<int> cmothers=input.genTopEvt.GetAdditionalCHadronMothers();
    std::vector<int> ctopdecaytype=input.genTopEvt.GetAdditionalCHadronAfterTopType();
    vars.FillVar( "N_AdditionalCHadrons",chadrons.size() );
    for(uint i=0; i<chadrons.size(); i++){
      vars.FillVars( "AdditionalCHadron_Pt",i, chadrons[i].pt());
      vars.FillVars( "AdditionalCHadron_Eta",i,chadrons[i].eta() );
      vars.FillVars( "AdditionalCHadron_Phi",i,chadrons[i].phi() );
      vars.FillVars( "AdditionalCHadron_E",i, chadrons[i].energy());
      vars.FillVars( "AdditionalCHadron_FromTopType",i, ctopdecaytype[i]);
      vars.FillVars( "AdditionalCHadron_Mother",i, cmothers[i]);
      float drQ=5;
      for(uint k=0; k<q1.size(); k++){
	if(abs(q1[k].pdgId())==4&&q1[k].pt()>1&&chadrons[k].pt()>1){
	  float dr = BoostedUtils::DeltaR(q1[k].p4(),chadrons[i].p4());
	  if(dr>0&&dr<drQ){
	    drQ=dr;
	  }
	}
      }
      for(uint k=0; k<q2.size(); k++){
	if(abs(q2[k].pdgId())==4&&q2[k].pt()>1&&chadrons[i].pt()>1){
	  float dr =BoostedUtils::DeltaR(q2[k].p4(),chadrons[i].p4());
	  if(dr>0&&dr<drQ){
	    drQ=dr;
	  }
	}
      }    
      vars.FillVars( "AdditionalCHadron_Dr_CfromW", i, drQ);     
    }
    
  }

}
