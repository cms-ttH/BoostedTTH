#include "BoostedTTH/BoostedAnalyzer/interface/MCMatchVarProcessor.hpp"

using namespace std;

MCMatchVarProcessor::MCMatchVarProcessor (){}
MCMatchVarProcessor::~MCMatchVarProcessor (){}


void MCMatchVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
  
  vars.InitVar( "GenEvt_I_TTPlusCC",-1,"I" );
  vars.InitVar( "GenEvt_I_TTPlusBB",-1,"I" );
  
  vars.InitVar( "N_GenTopHad", -1, "I" );
  vars.InitVars( "GenTopHad_Pt",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Eta",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Phi",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_W_Pt",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_B_Pt",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q1_Pt",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q2_Pt",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_W_Eta",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_B_Eta",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q1_Eta",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q2_Eta",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_W_Phi",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_B_Phi",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q1_Phi",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q2_Phi",-9.,"N_GenTopHad" );
  
  vars.InitVar( "N_GenTopLep",-1,"I" );
  vars.InitVars( "GenTopLep_Pt",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Eta",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Phi",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_W_Pt",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_B_Pt",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Lep_Pt",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Nu_Pt",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_W_Eta",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_B_Eta",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Lep_Eta",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Nu_Eta",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_W_Phi",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_B_Phi",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Lep_Phi",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Nu_Phi",-9.,"N_GenTopLep" );
  
  vars.InitVar( "GenHiggs_Pt",-9. );
  vars.InitVar( "GenHiggs_Eta",-9. );
  vars.InitVar( "GenHiggs_Phi",-9. );
  vars.InitVar( "GenHiggs_B1_Pt",-9. );
  vars.InitVar( "GenHiggs_B2_Pt",-9. );
  vars.InitVar( "GenHiggs_B1_Eta",-9. );
  vars.InitVar( "GenHiggs_B2_Eta",-9. );
  vars.InitVar( "GenHiggs_B1_Phi",-9. );
  vars.InitVar( "GenHiggs_B2_Phi",-9. );
  
  vars.InitVars( "GenTopHad_B_Idx",-1,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q1_Idx",-1,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q2_Idx",-1,"N_GenTopHad" );
  vars.InitVars( "GenTopLep_B_Idx",-1,"N_GenTopLep" );
  vars.InitVar( "GenHiggs_B1_Idx",-1 );
  vars.InitVar( "GenHiggs_B2_Idx",-1 );
  
  vars.InitVars( "TopJet_Dr_GenTopHad",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenTopLep",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenHiggs",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenB",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenQ1",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenQ2",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenB_B",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenB_W1",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenB_W2",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenQ1_B",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenQ1_W1",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenQ1_W2",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenQ2_B",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenQ2_W1",-9.,"N_TopJets" );
  vars.InitVars( "TopJet_Dr_GenQ2_W2",-9.,"N_TopJets" );
  
  vars.InitVars( "HiggsJet_Dr_GenHiggs",-9.,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_GenTopHad",-9.,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_GenTopLep",-9.,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_GenB1",-9.,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_GenB2",-9.,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_GenB1_Filterjet",-9.,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_GenB2_Filterjet",-9.,"N_HiggsJets" );
  
  vars.InitVars( "HiggsJet_Dr_GenW",-9.,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_GenQ1",-9.,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_GenQ2",-9.,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_GenQ1_Filterjet",-9.,"N_HiggsJets" );
  vars.InitVars( "HiggsJet_Dr_GenQ2_Filterjet",-9.,"N_HiggsJets" );

  initialized = true;
}


void MCMatchVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  
  if(!initialized) cerr << "tree processor not initialized" << endl;
  
  int iBB = 0;
  int iCC = 0;
  
  /*
    if(input.sampleType == SampleType::ttbb) iBB = 3;
    if(input.sampleType == SampleType::ttb) iBB = 1;
    if(input.sampleType == SampleType::ttcc) iCC = 1;
  */
  vars.FillVar( "GenEvt_I_TTPlusCC",iCC );
  vars.FillVar( "GenEvt_I_TTPlusBB",iBB );
  std::vector<reco::GenParticle> tophad;
  std::vector<reco::GenParticle> whad;
  std::vector<reco::GenParticle> bhad;
  std::vector<reco::GenParticle> q1;
  std::vector<reco::GenParticle> q2;
  std::vector<reco::GenParticle> toplep;
  std::vector<reco::GenParticle> wlep;
  std::vector<reco::GenParticle> blep;
  std::vector<reco::GenParticle> lep;
  std::vector<reco::GenParticle> nu;
  reco::GenParticle higgs;
  std::vector<reco::GenParticle> higgs_bs;
  if(input.genTopEvt.IsFilled()){
    tophad=input.genTopEvt.GetAllTopHads();
    whad=input.genTopEvt.GetAllWhads();
    bhad=input.genTopEvt.GetAllTopHadDecayQuarks();
    q1=input.genTopEvt.GetAllWQuarks();
    q2=input.genTopEvt.GetAllWAntiQuarks();
    toplep=input.genTopEvt.GetAllTopLeps();
    wlep=input.genTopEvt.GetAllWleps();
    blep=input.genTopEvt.GetAllTopLepDecayQuarks();
    lep=input.genTopEvt.GetAllLeptons();
    nu=input.genTopEvt.GetAllNeutrinos();
    higgs=input.genTopEvt.GetHiggs();
    higgs_bs=input.genTopEvt.GetHiggsDecayProducts();
  }

  reco::GenParticle b1;
  reco::GenParticle b2;

  for(auto p =higgs_bs.begin(); p!=higgs_bs.end(); p++){
    if(p->pdgId()==5) b1=*p;
    if(p->pdgId()==-5) b2=*p;
  }
  
  vars.FillVar( "N_GenTopLep", toplep.size());
  vars.FillVar( "N_GenTopHad", tophad.size());
  
  vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);
  
  for(size_t i=0;i<toplep.size();i++){
    vars.FillVars( "GenTopLep_Pt",i,toplep[i].pt());
    vars.FillVars( "GenTopLep_Eta",i,toplep[i].eta());
    vars.FillVars( "GenTopLep_Phi",i,toplep[i].phi());
    vars.FillVars( "GenTopLep_W_Pt",i,wlep[i].pt());
    vars.FillVars( "GenTopLep_B_Pt",i,blep[i].pt());
    vars.FillVars( "GenTopLep_Lep_Pt",i,lep[i].pt());
    vars.FillVars( "GenTopLep_Nu_Pt",i,nu[i].pt());
    vars.FillVars( "GenTopLep_W_Eta",i,wlep[i].eta());
    vars.FillVars( "GenTopLep_B_Eta",i,blep[i].eta());
    vars.FillVars( "GenTopLep_Lep_Eta",i,lep[i].eta());
    vars.FillVars( "GenTopLep_Nu_Eta",i,nu[i].eta());
    vars.FillVars( "GenTopLep_W_Phi",i,wlep[i].phi());
    vars.FillVars( "GenTopLep_B_Phi",i,blep[i].phi());
    vars.FillVars( "GenTopLep_Lep_Phi",i,lep[i].phi());
    vars.FillVars( "GenTopLep_Nu_Phi",i,nu[i].phi());
    
    int idxblep = -1;
    double minDrTopLep = 999;
    for(std::vector<math::XYZTLorentzVector>::iterator itJetVec = jetvecs.begin() ; itJetVec != jetvecs.end(); ++itJetVec){
      if(BoostedUtils::DeltaR(*itJetVec,blep[i].p4())<minDrTopLep){
        idxblep = itJetVec-jetvecs.begin();
        minDrTopLep = BoostedUtils::DeltaR(*itJetVec,blep[i].p4());
      }
    }
    
    if(minDrTopLep<.25){
      vars.FillVars( "GenTopLep_B_Idx",i,idxblep);
    }
  }
  
  for(size_t i=0; i< input.selectedHTTTopJets.size(); i++){
	  
    float minDr_TopLep_TopJet = 999;
    
    for(size_t j=0;j<toplep.size();j++){
	    float Dr_temp = BoostedUtils::DeltaR(toplep[j].p4(),input.selectedHTTTopJets[i].fatjet.p4());
	    if(Dr_temp<minDr_TopLep_TopJet) minDr_TopLep_TopJet = Dr_temp;
	  }
    
    if(minDr_TopLep_TopJet<999){
	    vars.FillVars("TopJet_Dr_GenTopLep",i,minDr_TopLep_TopJet);
    }
  }
  
  for(size_t i=0; i< input.selectedSubFilterJets.size(); i++){
    
    float minDr_TopLep_HiggsJet = 999;
    
    for(size_t j=0;j<toplep.size();j++){
	    float Dr_temp = BoostedUtils::DeltaR(toplep[j].p4(),input.selectedSubFilterJets[i].fatjet.p4());
	    if(Dr_temp<minDr_TopLep_HiggsJet) minDr_TopLep_HiggsJet = Dr_temp;
	  }
    
    if(minDr_TopLep_HiggsJet<999){
      vars.FillVars("HiggsJet_Dr_GenTopLep",i,minDr_TopLep_HiggsJet);
    }
  }
  
  for(size_t i=0;i<tophad.size();i++){
    vars.FillVars( "GenTopHad_Pt",i,tophad[i].pt());
    vars.FillVars( "GenTopHad_Eta",i,tophad[i].eta());
    vars.FillVars( "GenTopHad_Phi",i,tophad[i].phi());
    vars.FillVars( "GenTopHad_W_Pt",i,whad[i].pt());
    vars.FillVars( "GenTopHad_B_Pt",i,bhad[i].pt());
    vars.FillVars( "GenTopHad_Q1_Pt",i,q1[i].pt());
    vars.FillVars( "GenTopHad_Q2_Pt",i,q2[i].pt());
    vars.FillVars( "GenTopHad_W_Eta",i,whad[i].eta());
    vars.FillVars( "GenTopHad_B_Eta",i,bhad[i].eta());
    vars.FillVars( "GenTopHad_Q1_Eta",i,q1[i].eta());
    vars.FillVars( "GenTopHad_Q2_Eta",i,q2[i].eta());
    vars.FillVars( "GenTopHad_W_Phi",i,whad[i].phi());
    vars.FillVars( "GenTopHad_B_Phi",i,bhad[i].phi());
    vars.FillVars( "GenTopHad_Q1_Phi",i,q1[i].phi());
    vars.FillVars( "GenTopHad_Q2_Phi",i,q2[i].phi());
    int idxbhad=-1;
    int idxq1=-1;
    int idxq2=-1;
    double minDrTopHadB = 999;
    double minDrTopHadQ1 = 999;
    double minDrTopHadQ2 = 999;
    
    for(size_t j=0; j<jetvecs.size(); j++){
	    if(BoostedUtils::DeltaR(jetvecs[j],bhad[i].p4())<minDrTopHadB){
        idxbhad = j;
        minDrTopHadB = BoostedUtils::DeltaR(jetvecs[j],bhad[i].p4());
      }
      if(BoostedUtils::DeltaR(jetvecs[j],q1[i].p4())<minDrTopHadQ1){
        idxq1 = j;
        minDrTopHadQ1 = BoostedUtils::DeltaR(jetvecs[j],q1[i].p4());
      }
      if(BoostedUtils::DeltaR(jetvecs[j],q2[i].p4())<minDrTopHadQ2){
        idxq2 = j;
        minDrTopHadQ2 = BoostedUtils::DeltaR(jetvecs[j],q2[i].p4());
      }
    }
    
    if(minDrTopHadB<.25){
      vars.FillVars( "GenTopHad_B_Idx",i,idxbhad);
    }
    if(minDrTopHadQ1<.25){
      vars.FillVars( "GenTopHad_Q1_Idx",i,idxq1);
    }
    if(minDrTopHadQ2<.25){
      vars.FillVars( "GenTopHad_Q2_Idx",i,idxq2);
    }
  }
  for(size_t i=0; i< input.selectedHTTTopJets.size(); i++){
	  
    float minDr_TopHad_TopJet = 999;
    float minDr_TopB_TopJet = 999;
    float minDr_TopQ1_TopJet = 999;
    float minDr_TopQ2_TopJet = 999;
    float minDr_TopB_B_TopJet = 999;
    float minDr_TopB_W1_TopJet = 999;
    float minDr_TopB_W2_TopJet = 999;
    float minDr_TopQ1_B_TopJet = 999;
    float minDr_TopQ1_W1_TopJet = 999;
    float minDr_TopQ1_W2_TopJet = 999;
    float minDr_TopQ2_B_TopJet = 999;
    float minDr_TopQ2_W1_TopJet = 999;
    float minDr_TopQ2_W2_TopJet = 999;
    
    for(size_t j=0;j<tophad.size();j++){
      
      float Dr_temp = BoostedUtils::DeltaR(tophad[j].p4(),input.selectedHTTTopJets[i].fatjet.p4());
      if(Dr_temp<minDr_TopHad_TopJet){
	      minDr_TopHad_TopJet = Dr_temp;
	      minDr_TopB_TopJet = BoostedUtils::DeltaR(bhad[j].p4(),input.selectedHTTTopJets[i].fatjet.p4());
	      minDr_TopQ1_TopJet = BoostedUtils::DeltaR(q1[j].p4(),input.selectedHTTTopJets[i].fatjet.p4());
	      minDr_TopQ2_TopJet = BoostedUtils::DeltaR(q2[j].p4(),input.selectedHTTTopJets[i].fatjet.p4());
	      if(input.selectedHTTTopJets[i].nonW.pt()>0){
	        minDr_TopB_B_TopJet = BoostedUtils::DeltaR(bhad[j].p4(),input.selectedHTTTopJets[i].nonW.p4());
	        minDr_TopQ2_B_TopJet = BoostedUtils::DeltaR(q2[j].p4(),input.selectedHTTTopJets[i].nonW.p4());
	        minDr_TopQ1_B_TopJet = BoostedUtils::DeltaR(q1[j].p4(),input.selectedHTTTopJets[i].nonW.p4());
	      }
	      if(input.selectedHTTTopJets[i].W1.pt()>0){
	        minDr_TopB_W1_TopJet = BoostedUtils::DeltaR(bhad[j].p4(),input.selectedHTTTopJets[i].W1.p4());
	        minDr_TopQ1_W1_TopJet = BoostedUtils::DeltaR(q1[j].p4(),input.selectedHTTTopJets[i].W1.p4());
	        minDr_TopQ2_W1_TopJet = BoostedUtils::DeltaR(q2[j].p4(),input.selectedHTTTopJets[i].W1.p4());
	      }
	      if(input.selectedHTTTopJets[i].W2.pt()>0){
	        minDr_TopB_W2_TopJet = BoostedUtils::DeltaR(bhad[j].p4(),input.selectedHTTTopJets[i].W2.p4());
	        minDr_TopQ1_W2_TopJet = BoostedUtils::DeltaR(q1[j].p4(),input.selectedHTTTopJets[i].W2.p4());
	        minDr_TopQ2_W2_TopJet = BoostedUtils::DeltaR(q2[j].p4(),input.selectedHTTTopJets[i].W2.p4());
	      }
      }
    }

    if(minDr_TopHad_TopJet<999) vars.FillVars("TopJet_Dr_GenTopHad",i,minDr_TopHad_TopJet);
    if(minDr_TopB_TopJet<999) vars.FillVars("TopJet_Dr_GenB",i,minDr_TopB_TopJet);
    if(minDr_TopQ1_TopJet<999) vars.FillVars("TopJet_Dr_GenQ1",i,minDr_TopQ1_TopJet);
    if(minDr_TopQ2_TopJet<999) vars.FillVars("TopJet_Dr_GenQ2",i,minDr_TopQ2_TopJet);
    if(minDr_TopB_B_TopJet<999) vars.FillVars("TopJet_Dr_GenB_B",i,minDr_TopB_B_TopJet);
    if(minDr_TopB_W1_TopJet<999) vars.FillVars("TopJet_Dr_GenB_W1",i,minDr_TopB_W1_TopJet);
    if(minDr_TopB_W2_TopJet<999) vars.FillVars("TopJet_Dr_GenB_W2",i,minDr_TopB_W2_TopJet);
    if(minDr_TopQ1_B_TopJet<999) vars.FillVars("TopJet_Dr_GenQ1_B",i,minDr_TopQ1_B_TopJet);
    if(minDr_TopQ1_W1_TopJet<999) vars.FillVars("TopJet_Dr_GenQ1_W1",i,minDr_TopQ1_W1_TopJet);
    if(minDr_TopQ1_W2_TopJet<999) vars.FillVars("TopJet_Dr_GenQ1_W2",i,minDr_TopQ1_W2_TopJet);
    if(minDr_TopQ2_B_TopJet<999) vars.FillVars("TopJet_Dr_GenQ2_B",i,minDr_TopQ2_B_TopJet);
    if(minDr_TopQ2_W1_TopJet<999) vars.FillVars("TopJet_Dr_GenQ2_W1",i,minDr_TopQ2_W1_TopJet);
    if(minDr_TopQ2_W2_TopJet<999) vars.FillVars("TopJet_Dr_GenQ2_W2",i,minDr_TopQ2_W2_TopJet);
  }
  for(size_t i=0; i< input.selectedSubFilterJets.size(); i++){
    
    float minDr_TopHad_HiggsJet = 9;
    
    for(size_t j=0;j<tophad.size();j++){
      float Dr_temp = BoostedUtils::DeltaR(tophad[j].p4(),input.selectedSubFilterJets[i].fatjet.p4());
      if(Dr_temp<minDr_TopHad_HiggsJet) minDr_TopHad_HiggsJet = Dr_temp;
    }
    vars.FillVars("HiggsJet_Dr_GenTopHad",i,minDr_TopHad_HiggsJet);
  }
  if(higgs.pt()>0.){
    vars.FillVar( "GenHiggs_Pt",higgs.pt());
    vars.FillVar( "GenHiggs_Eta",higgs.eta());
    vars.FillVar( "GenHiggs_Phi",higgs.phi());
  }
  if(b1.pt()>0.){
    vars.FillVar("GenHiggs_B1_Pt",b1.pt());
    vars.FillVar("GenHiggs_B2_Pt",b2.pt());
    vars.FillVar("GenHiggs_B1_Eta",b1.eta());
    vars.FillVar("GenHiggs_B2_Eta",b2.eta());
    vars.FillVar("GenHiggs_B1_Phi",b1.phi());
    vars.FillVar("GenHiggs_B2_Phi",b2.phi());
    
    int idxb1=-1;
    int idxb2=-1;
    double minDrB1 = 999;
    double minDrB2 = 999;
    
    for(std::vector<math::XYZTLorentzVector>::iterator itJetVec = jetvecs.begin() ; itJetVec != jetvecs.end(); ++itJetVec){
      assert(itJetVec->pt()>0);
      assert(b1.pt()>0);
      assert(b2.pt()>0);
      if(BoostedUtils::DeltaR(*itJetVec,b1.p4())<minDrB1){
        idxb1 = itJetVec-jetvecs.begin();
        minDrB1 = BoostedUtils::DeltaR(*itJetVec,b1.p4());
      }
      if(BoostedUtils::DeltaR(*itJetVec,b2.p4())<minDrB2){
        idxb2 = itJetVec-jetvecs.begin();
        minDrB2 = BoostedUtils::DeltaR(*itJetVec,b2.p4());
      }
    }
    
    if(minDrB1<.25){
      vars.FillVar( "GenHiggs_B1_Idx",idxb1);
    }
    if(minDrB2<.25){
      vars.FillVar( "GenHiggs_B2_Idx",idxb2);
    }
  }
  for(size_t i=0; i< input.selectedSubFilterJets.size(); i++){
    if(higgs.pt()>0)
      vars.FillVars("HiggsJet_Dr_GenHiggs",i,BoostedUtils::DeltaR(higgs.p4(),input.selectedSubFilterJets[i].fatjet.p4()));	  
	  
	  if(b1.pt()>0.){
    
	    vars.FillVars("HiggsJet_Dr_GenB1",i,BoostedUtils::DeltaR(b1.p4(),input.selectedSubFilterJets[i].fatjet.p4()));
	    vars.FillVars("HiggsJet_Dr_GenB2",i,BoostedUtils::DeltaR(b2.p4(),input.selectedSubFilterJets[i].fatjet.p4()));
      
      double minDrB1 = 999;
      double minDrB2 = 999;
      
      for(size_t j=0;j<input.selectedSubFilterJets[i].filterjets.size();j++){
	      
        if(BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[j].p4(),b1.p4())<minDrB1){
          minDrB1 = BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[j].p4(),b1.p4());
        }
        if(BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[j].p4(),b2.p4())<minDrB2){
          minDrB2 = BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[j].p4(),b2.p4());
        }
      }
      
      if(minDrB1<999) vars.FillVars("HiggsJet_Dr_GenB1_Filterjet",i,minDrB1);
	  	if(minDrB2<999) vars.FillVars("HiggsJet_Dr_GenB2_Filterjet",i,minDrB2); 
	  }
    
    float minDr_WHad_HiggsJet = 999;
	  float minDr_Q1_HiggsJet = 999;
	  float minDr_Q2_HiggsJet = 999;
    float minDr_Q1_FilterJet = 999;
    float minDr_Q2_FilterJet = 999;
    
    for(size_t j=0;j<whad.size();j++){
    
      float Dr_temp = BoostedUtils::DeltaR(whad[j].p4(),input.selectedSubFilterJets[i].fatjet.p4());
      
	    if(Dr_temp<minDr_WHad_HiggsJet){
	  	  minDr_WHad_HiggsJet = Dr_temp;
		    minDr_Q1_HiggsJet = BoostedUtils::DeltaR(q1[j].p4(),input.selectedSubFilterJets[i].fatjet.p4());
		    minDr_Q2_HiggsJet = BoostedUtils::DeltaR(q2[j].p4(),input.selectedSubFilterJets[i].fatjet.p4());
        
        for(size_t k=0;k<input.selectedSubFilterJets[i].filterjets.size();k++){
	      
          if(BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[k].p4(),q1[j].p4())<minDr_Q1_FilterJet){
            minDr_Q1_FilterJet = BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[k].p4(),q1[j].p4());
          }
          if(BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[k].p4(),q2[j].p4())<minDr_Q2_FilterJet){
            minDr_Q2_FilterJet = BoostedUtils::DeltaR(input.selectedSubFilterJets[i].filterjets[k].p4(),q2[j].p4());
          }
        }
	    }
	  }
    
    if(minDr_WHad_HiggsJet<999) vars.FillVars("HiggsJet_Dr_GenW",i,minDr_WHad_HiggsJet);
    if(minDr_Q1_HiggsJet<999) vars.FillVars("HiggsJet_Dr_GenQ1",i,minDr_Q1_HiggsJet);
    if(minDr_Q2_HiggsJet<999) vars.FillVars("HiggsJet_Dr_GenQ2",i,minDr_Q2_HiggsJet);
    if(minDr_Q1_FilterJet<999) vars.FillVars("HiggsJet_Dr_GenQ1_Filterjet",i,minDr_Q1_FilterJet);
    if(minDr_Q2_FilterJet<999) vars.FillVars("HiggsJet_Dr_GenQ2_Filterjet",i,minDr_Q2_FilterJet);
  }
  
  for(size_t i=0; i<input.selectedHTTTopJets.size(); i++){
  	if(higgs.pt()>0) vars.FillVars("TopJet_Dr_GenHiggs",i,BoostedUtils::DeltaR(higgs.p4(),input.selectedHTTTopJets[i].fatjet.p4()));
  }
}
