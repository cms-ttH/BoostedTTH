#include "BoostedTTH/BoostedAnalyzer/interface/BoostedMCMatchVarProcessor.hpp"

using namespace std;

BoostedMCMatchVarProcessor::BoostedMCMatchVarProcessor (){}
BoostedMCMatchVarProcessor::~BoostedMCMatchVarProcessor (){}


void BoostedMCMatchVarProcessor::Init(const InputCollections& input,VariableContainer& vars){

  
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


void BoostedMCMatchVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  
  if(!initialized) cerr << "tree processor not initialized" << endl;
  
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
  
  
  for(size_t i=0; i< input.selectedHEPTopJets.size(); i++){
    
    float minDr_TopLep_TopJet = 999;
    
    for(size_t j=0;j<toplep.size();j++){
      float Dr_temp = BoostedUtils::DeltaR(toplep[j].p4(),input.selectedHEPTopJets[i].fatjet.p4());
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
  
  for(size_t i=0; i< input.selectedHEPTopJets.size(); i++){
    
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
      
      float Dr_temp = BoostedUtils::DeltaR(tophad[j].p4(),input.selectedHEPTopJets[i].fatjet.p4());
      if(Dr_temp<minDr_TopHad_TopJet){
	minDr_TopHad_TopJet = Dr_temp;
	minDr_TopB_TopJet = BoostedUtils::DeltaR(bhad[j].p4(),input.selectedHEPTopJets[i].fatjet.p4());
	minDr_TopQ1_TopJet = BoostedUtils::DeltaR(q1[j].p4(),input.selectedHEPTopJets[i].fatjet.p4());
	minDr_TopQ2_TopJet = BoostedUtils::DeltaR(q2[j].p4(),input.selectedHEPTopJets[i].fatjet.p4());
	if(input.selectedHEPTopJets[i].nonW.pt()>0){
	  minDr_TopB_B_TopJet = BoostedUtils::DeltaR(bhad[j].p4(),input.selectedHEPTopJets[i].nonW.p4());
	  minDr_TopQ2_B_TopJet = BoostedUtils::DeltaR(q2[j].p4(),input.selectedHEPTopJets[i].nonW.p4());
	  minDr_TopQ1_B_TopJet = BoostedUtils::DeltaR(q1[j].p4(),input.selectedHEPTopJets[i].nonW.p4());
	}
	if(input.selectedHEPTopJets[i].W1.pt()>0){
	  minDr_TopB_W1_TopJet = BoostedUtils::DeltaR(bhad[j].p4(),input.selectedHEPTopJets[i].W1.p4());
	  minDr_TopQ1_W1_TopJet = BoostedUtils::DeltaR(q1[j].p4(),input.selectedHEPTopJets[i].W1.p4());
	  minDr_TopQ2_W1_TopJet = BoostedUtils::DeltaR(q2[j].p4(),input.selectedHEPTopJets[i].W1.p4());
	}
	if(input.selectedHEPTopJets[i].W2.pt()>0){
	  minDr_TopB_W2_TopJet = BoostedUtils::DeltaR(bhad[j].p4(),input.selectedHEPTopJets[i].W2.p4());
	  minDr_TopQ1_W2_TopJet = BoostedUtils::DeltaR(q1[j].p4(),input.selectedHEPTopJets[i].W2.p4());
	  minDr_TopQ2_W2_TopJet = BoostedUtils::DeltaR(q2[j].p4(),input.selectedHEPTopJets[i].W2.p4());
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
  
  for(size_t i=0; i<input.selectedHEPTopJets.size(); i++){
    if(higgs.pt()>0) vars.FillVars("TopJet_Dr_GenHiggs",i,BoostedUtils::DeltaR(higgs.p4(),input.selectedHEPTopJets[i].fatjet.p4()));
  }
}
