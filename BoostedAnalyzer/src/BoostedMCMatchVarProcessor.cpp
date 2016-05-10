#include "BoostedTTH/BoostedAnalyzer/interface/BoostedMCMatchVarProcessor.hpp"

using namespace std;

BoostedMCMatchVarProcessor::BoostedMCMatchVarProcessor (){}
BoostedMCMatchVarProcessor::~BoostedMCMatchVarProcessor (){}


void BoostedMCMatchVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
 
  vars.InitVars( "BoostedJet_Dr_GenTopHad",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenTopLep",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenHiggs",-9.,"N_BoostedJets" );
  
  vars.InitVars( "BoostedJet_Dr_GenW",-9.,"N_BoostedJets" );
  
  vars.InitVars( "BoostedJet_Dr_GenB",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB2",-9.,"N_BoostedJets" );
  
  vars.InitVars( "BoostedJet_Dr_GenB_B",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB_W1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB_W2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ1_B",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ1_W1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ1_W2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_B",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_W1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_W2",-9.,"N_BoostedJets" );
  
  vars.InitVars( "BoostedJet_Dr_GenQ1_Subjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_Subjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB1_Subjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB2_Subjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ1_Filterjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_Filterjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB1_Filterjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB2_Filterjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ1_PrunedSubjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_PrunedSubjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB1_PrunedSubjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB2_PrunedSubjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB1_SoftdropSubjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB2_SoftdropSubjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ1_SoftdropSubjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_SoftdropSubjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB1_Softdropz2b1Subjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB2_Softdropz2b1Subjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ1_Softdropz2b1Subjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_Softdropz2b1Subjet",-9.,"N_BoostedJets" );
  
  vars.InitVars( "BoostedJet_Dr_GenQ1_CSV1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_CSV1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB_CSV1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ1_CSV2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_CSV2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB_CSV2",-9.,"N_BoostedJets" );
  
  vars.InitVars( "BoostedJet_Dr_Subjet1_GenB1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Subjet2_GenB1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Subjet1_GenB2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Subjet2_GenB2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Filterjet1_GenB1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Filterjet2_GenB1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Filterjet3_GenB1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Filterjet1_GenB2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Filterjet2_GenB2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Filterjet3_GenB2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Filterjet1_Q",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Filterjet2_Q",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Filterjet3_Q",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_PrunedSubjet1_GenB1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_PrunedSubjet2_GenB1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_PrunedSubjet1_GenB2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_PrunedSubjet2_GenB2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_PrunedSubjet1_Q",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_PrunedSubjet2_Q",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_SoftdropSubjet1_GenB1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_SoftdropSubjet2_GenB1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_SoftdropSubjet1_GenB2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_SoftdropSubjet2_GenB2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_SoftdropSubjet1_Q",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_SoftdropSubjet2_Q",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Softdropz2b1Subjet1_GenB1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Softdropz2b1Subjet2_GenB1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Softdropz2b1Subjet1_GenB2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Softdropz2b1Subjet2_GenB2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Softdropz2b1Subjet1_Q",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_Softdropz2b1Subjet2_Q",-9.,"N_BoostedJets" );

  initialized = true;
}


void BoostedMCMatchVarProcessor::Process(const InputCollections& input,VariableContainer& vars){

  if(!initialized) std::cerr << "tree processor not initialized" << std::endl;
  
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
  if(input.genTopEvt.IsFilled()&&input.genTopEvt.TTxIsFilled()){
      std::vector<reco::GenParticle> additional_bs=input.genTopEvt.GetAdditionalBHadrons();
      if(additional_bs.size()>0)
	  b1=additional_bs[0];
      if(additional_bs.size()>1)
	  b2=additional_bs[1];

  }

  // Match TopLep jets
  for(size_t i=0; i< input.selectedBoostedJets.size(); i++){
	  
    float minDr_TopLep = 999;
    
    for(size_t j=0;j<toplep.size();j++){
	    float Dr_temp = BoostedUtils::DeltaR(toplep[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
	    if(Dr_temp<minDr_TopLep) minDr_TopLep = Dr_temp;
	  }
    
    if(minDr_TopLep<999){
	    vars.FillVars("BoostedJet_Dr_GenTopLep",i,minDr_TopLep);
    }
  }
  
  // Match TopHad jets
  for(size_t i=0; i< input.selectedBoostedJets.size(); i++){
	  
    float minDr_TopHad = 999;
    float minDr_TopB = 999;
    float minDr_TopQ1 = 999;
    float minDr_TopQ2 = 999;
    float minDr_TopB_B = 999;
    float minDr_TopB_W1 = 999;
    float minDr_TopB_W2 = 999;
    float minDr_TopQ1_B = 999;
    float minDr_TopQ1_W1 = 999;
    float minDr_TopQ1_W2 = 999;
    float minDr_TopQ2_B = 999;
    float minDr_TopQ2_W1 = 999;
    float minDr_TopQ2_W2 = 999;
    
    for(size_t j=0;j<tophad.size();j++){
      
      float Dr_temp = BoostedUtils::DeltaR(tophad[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
      if(Dr_temp<minDr_TopHad){
	      minDr_TopHad = Dr_temp;
	      minDr_TopB = BoostedUtils::DeltaR(bhad[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
	      minDr_TopQ1 = BoostedUtils::DeltaR(q1[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
	      minDr_TopQ2 = BoostedUtils::DeltaR(q2[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
	      if(input.selectedBoostedJets[i].nonW.pt()>0){
	        minDr_TopB_B = BoostedUtils::DeltaR(bhad[j].p4(),input.selectedBoostedJets[i].nonW.p4());
	        minDr_TopQ2_B = BoostedUtils::DeltaR(q2[j].p4(),input.selectedBoostedJets[i].nonW.p4());
	        minDr_TopQ1_B = BoostedUtils::DeltaR(q1[j].p4(),input.selectedBoostedJets[i].nonW.p4());
	      }
	      if(input.selectedBoostedJets[i].W1.pt()>0){
	        minDr_TopB_W1 = BoostedUtils::DeltaR(bhad[j].p4(),input.selectedBoostedJets[i].W1.p4());
	        minDr_TopQ1_W1 = BoostedUtils::DeltaR(q1[j].p4(),input.selectedBoostedJets[i].W1.p4());
	        minDr_TopQ2_W1 = BoostedUtils::DeltaR(q2[j].p4(),input.selectedBoostedJets[i].W1.p4());
	      }
	      if(input.selectedBoostedJets[i].W2.pt()>0){
	        minDr_TopB_W2 = BoostedUtils::DeltaR(bhad[j].p4(),input.selectedBoostedJets[i].W2.p4());
	        minDr_TopQ1_W2 = BoostedUtils::DeltaR(q1[j].p4(),input.selectedBoostedJets[i].W2.p4());
	        minDr_TopQ2_W2 = BoostedUtils::DeltaR(q2[j].p4(),input.selectedBoostedJets[i].W2.p4());
	      }
      }
    }

    if(minDr_TopHad<999) vars.FillVars("BoostedJet_Dr_GenTopHad",i,minDr_TopHad);
    if(minDr_TopB<999) vars.FillVars("BoostedJet_Dr_GenB",i,minDr_TopB);
    if(minDr_TopQ1<999) vars.FillVars("BoostedJet_Dr_GenQ1",i,minDr_TopQ1);
    if(minDr_TopQ2<999) vars.FillVars("BoostedJet_Dr_GenQ2",i,minDr_TopQ2);
    if(minDr_TopB_B<999) vars.FillVars("BoostedJet_Dr_GenB_B",i,minDr_TopB_B);
    if(minDr_TopB_W1<999) vars.FillVars("BoostedJet_Dr_GenB_W1",i,minDr_TopB_W1);
    if(minDr_TopB_W2<999) vars.FillVars("BoostedJet_Dr_GenB_W2",i,minDr_TopB_W2);
    if(minDr_TopQ1_B<999) vars.FillVars("BoostedJet_Dr_GenQ1_B",i,minDr_TopQ1_B);
    if(minDr_TopQ1_W1<999) vars.FillVars("BoostedJet_Dr_GenQ1_W1",i,minDr_TopQ1_W1);
    if(minDr_TopQ1_W2<999) vars.FillVars("BoostedJet_Dr_GenQ1_W2",i,minDr_TopQ1_W2);
    if(minDr_TopQ2_B<999) vars.FillVars("BoostedJet_Dr_GenQ2_B",i,minDr_TopQ2_B);
    if(minDr_TopQ2_W1<999) vars.FillVars("BoostedJet_Dr_GenQ2_W1",i,minDr_TopQ2_W1);
    if(minDr_TopQ2_W2<999) vars.FillVars("BoostedJet_Dr_GenQ2_W2",i,minDr_TopQ2_W2);
  }
  
  for(size_t i=0; i< input.selectedBoostedJets.size(); i++){
    if(higgs.pt()>0)
      vars.FillVars("BoostedJet_Dr_GenHiggs",i,BoostedUtils::DeltaR(higgs.p4(),input.selectedBoostedJets[i].fatjet.p4()));	  
    
    if(b1.pt()>0.){

      vars.FillVars("BoostedJet_Dr_GenB1",i,BoostedUtils::DeltaR(b1.p4(),input.selectedBoostedJets[i].fatjet.p4()));
      if(b2.pt()>0.) vars.FillVars("BoostedJet_Dr_GenB2",i,BoostedUtils::DeltaR(b2.p4(),input.selectedBoostedJets[i].fatjet.p4()));
      
      // Subjets
      double minDrB1_sub = 999;
      double minDrB2_sub = 999;
      for(size_t j=0;j<input.selectedBoostedJets[i].subjets.size();j++){
        if (j>2) break;
	      if (input.selectedBoostedJets[i].subjets[j].pt() == 0.) continue;
        
        if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].subjets[j].p4(),b1.p4())<minDrB1_sub){
          minDrB1_sub = BoostedUtils::DeltaR(input.selectedBoostedJets[i].subjets[j].p4(),b1.p4());
        }
        if(b2.pt()>0.){
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].subjets[j].p4(),b2.p4())<minDrB2_sub){
            minDrB2_sub = BoostedUtils::DeltaR(input.selectedBoostedJets[i].subjets[j].p4(),b2.p4());
          }
        }
        vars.FillVars("BoostedJet_Dr_Subjet"+to_string(j+1)+"_GenB1",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].subjets[j].p4(),b1.p4()));
        vars.FillVars("BoostedJet_Dr_Subjet"+to_string(j+1)+"_GenB2",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].subjets[j].p4(),b2.p4()));
      }

      if(minDrB1_sub<999) vars.FillVars("BoostedJet_Dr_GenB1_Subjet",i,minDrB1_sub);
      if(minDrB2_sub<999) vars.FillVars("BoostedJet_Dr_GenB2_Subjet",i,minDrB2_sub); 
      
      // Filterjets
      double minDrB1_filter = 999;
      double minDrB2_filter = 999;
      
      for(size_t j=0;j<input.selectedBoostedJets[i].filterjets.size();j++){
        if (j>2) break;
	      if (input.selectedBoostedJets[i].filterjets[j].pt() == 0.) continue;
        
        if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[j].p4(),b1.p4())<minDrB1_filter){
          minDrB1_filter = BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[j].p4(),b1.p4());
        }
        if(b2.pt()>0.){
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[j].p4(),b2.p4())<minDrB2_filter){
            minDrB2_filter = BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[j].p4(),b2.p4());
          }
        }
        
        vars.FillVars("BoostedJet_Dr_Filterjet"+to_string(j+1)+"_GenB1",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[j].p4(),b1.p4()));
        vars.FillVars("BoostedJet_Dr_Filterjet"+to_string(j+1)+"_GenB2",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[j].p4(),b2.p4()));
      }
      
      if(minDrB1_filter<999) vars.FillVars("BoostedJet_Dr_GenB1_Filterjet",i,minDrB1_filter);
      if(minDrB2_filter<999) vars.FillVars("BoostedJet_Dr_GenB2_Filterjet",i,minDrB2_filter); 
      
      // Pruned subjets
      double minDrB1_Pruned = 999;
      double minDrB2_Pruned = 999;
      
      for(size_t j=0;j<input.selectedBoostedJets[i].prunedsubjets.size();j++){
        if (j>2) break;
        if (input.selectedBoostedJets[i].prunedsubjets[j].pt() == 0.) continue;
      
        if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[j].p4(),b1.p4())<minDrB1_Pruned){
          minDrB1_Pruned = BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[j].p4(),b1.p4());
        }
        if(b2.pt()>0.){
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[j].p4(),b2.p4())<minDrB2_Pruned){
            minDrB2_Pruned = BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[j].p4(),b2.p4());
          }
        }
        
        vars.FillVars("BoostedJet_Dr_PrunedSubjet"+to_string(j+1)+"_GenB1",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[j].p4(),b1.p4()));
        vars.FillVars("BoostedJet_Dr_PrunedSubjet"+to_string(j+1)+"_GenB2",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[j].p4(),b2.p4()));
      }
      
      if(minDrB1_Pruned < 999) vars.FillVars("BoostedJet_Dr_GenB1_PrunedSubjet",i,minDrB1_Pruned);
      if(minDrB2_Pruned < 999) vars.FillVars("BoostedJet_Dr_GenB2_PrunedSubjet",i,minDrB2_Pruned); 
      
      
      // Soft drop jets
      double minDrB1_Softdrop = 999;
      double minDrB2_Softdrop = 999;
      
      for(size_t j=0;j<input.selectedBoostedJets[i].sdsubjets.size();j++){
        if (j>2) break;
        if (input.selectedBoostedJets[i].sdsubjets[j].pt() == 0.) continue;
        
        if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[j].p4(),b1.p4())<minDrB1_Softdrop){
          minDrB1_Softdrop = BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[j].p4(),b1.p4());
        }
        if(b2.pt()>0.){
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[j].p4(),b2.p4())<minDrB2_Softdrop){
            minDrB2_Softdrop = BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[j].p4(),b2.p4());
          }
        }
        
        vars.FillVars("BoostedJet_Dr_SoftdropSubjet"+to_string(j+1)+"_GenB1",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[j].p4(),b1.p4()));
        vars.FillVars("BoostedJet_Dr_SoftdropSubjet"+to_string(j+1)+"_GenB2",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[j].p4(),b2.p4()));
      }
      
      if(minDrB1_Softdrop < 999) vars.FillVars("BoostedJet_Dr_GenB1_SoftdropSubjet",i,minDrB1_Softdrop);
      if(minDrB2_Softdrop < 999) vars.FillVars("BoostedJet_Dr_GenB2_SoftdropSubjet",i,minDrB2_Softdrop); 
      
      
      // Soft drop z2 b1 jets
      double minDrB1_Softdropz2b1 = 999;
      double minDrB2_Softdropz2b1 = 999;
      
      for(size_t j=0;j<input.selectedBoostedJets[i].sdz2b1subjets.size();j++){
        if (j>2) break;
        if (input.selectedBoostedJets[i].sdz2b1subjets[j].pt() == 0.) continue;
        
        if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[j].p4(),b1.p4())<minDrB1_Softdropz2b1){
          minDrB1_Softdropz2b1 = BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[j].p4(),b1.p4());
        }
        if(b2.pt()>0.){
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[j].p4(),b2.p4())<minDrB2_Softdropz2b1){
            minDrB2_Softdropz2b1 = BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[j].p4(),b2.p4());
          }
        }
        
        vars.FillVars("BoostedJet_Dr_Softdropz2b1Subjet"+to_string(j+1)+"_GenB1",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[j].p4(),b1.p4()));
        vars.FillVars("BoostedJet_Dr_Softdropz2b1Subjet"+to_string(j+1)+"_GenB2",i,BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[j].p4(),b2.p4()));
      }
      
      if(minDrB1_Softdropz2b1 < 999) vars.FillVars("BoostedJet_Dr_GenB1_Softdropz2b1Subjet",i,minDrB1_Softdropz2b1);
      if(minDrB2_Softdropz2b1 < 999) vars.FillVars("BoostedJet_Dr_GenB2_Softdropz2b1Subjet",i,minDrB2_Softdropz2b1);
    }
    
    float minDr_WHad = 999;
    float minDr_Q1 = 999;
    float minDr_Q2 = 999;
    float minDr_Q1_FilterJet = 999;
    float minDr_Q2_FilterJet = 999;
    float minDr_Q1_PrunedSubjet = 999;
    float minDr_Q2_PrunedSubjet = 999;
    float minDr_Q1_SoftdropSubjet = 999;
    float minDr_Q2_SoftdropSubjet = 999;
    float minDr_Q1_Softdropz2b1Subjet = 999;
    float minDr_Q2_Softdropz2b1Subjet = 999;
    
    for(size_t j=0;j<whad.size();j++){
    
      float Dr_temp = BoostedUtils::DeltaR(whad[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
      
	    if(Dr_temp<minDr_WHad){
	  	  minDr_WHad = Dr_temp;
		    minDr_Q1 = BoostedUtils::DeltaR(q1[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
		    minDr_Q2 = BoostedUtils::DeltaR(q2[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
        
        // Filterjets
        float minDr_Filterjet_Q[input.selectedBoostedJets[i].filterjets.size()];
        for(size_t j=0;j<input.selectedBoostedJets[i].filterjets.size();j++) minDr_Filterjet_Q[j] = 999;
        
        for(size_t k=0;k<input.selectedBoostedJets[i].filterjets.size();k++){
          if (input.selectedBoostedJets[i].filterjets[k].pt() == 0.) continue;

          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[k].p4(),q1[j].p4())<minDr_Q1_FilterJet){
            minDr_Q1_FilterJet = BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[k].p4(),q1[j].p4());
          }
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[k].p4(),q2[j].p4())<minDr_Q2_FilterJet){
            minDr_Q2_FilterJet = BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[k].p4(),q2[j].p4());
          }
          
          if(k>2) break;
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[k].p4(),q1[j].p4())<minDr_Filterjet_Q[k]){
            minDr_Filterjet_Q[k] = BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[k].p4(),q1[j].p4());
          }
        
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[k].p4(),q2[j].p4())<minDr_Filterjet_Q[k]){
            minDr_Filterjet_Q[k] = BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[k].p4(),q2[j].p4());
          }
          if(minDr_Filterjet_Q[k] < 999) vars.FillVars("BoostedJet_Dr_Filterjet"+to_string(k+1)+"_Q",i,minDr_Filterjet_Q[k]);
        }
        
        // Pruned subjets
        float minDr_PrunedSubjet_Q[2] = {999.,999.};
        for(size_t k=0;k<input.selectedBoostedJets[i].prunedsubjets.size();k++){
          if (input.selectedBoostedJets[i].prunedsubjets[k].pt() == 0.) continue;
	      
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[k].p4(),q1[j].p4())<minDr_Q1_PrunedSubjet){
            minDr_Q1_PrunedSubjet = BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[k].p4(),q1[j].p4());
          }
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[k].p4(),q2[j].p4())<minDr_Q2_PrunedSubjet){
            minDr_Q2_PrunedSubjet = BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[k].p4(),q2[j].p4());
          }
          
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[k].p4(),q1[j].p4())<minDr_PrunedSubjet_Q[k]){
            minDr_PrunedSubjet_Q[k] = BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[k].p4(),q1[j].p4());
          }
        
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[k].p4(),q2[j].p4())<minDr_PrunedSubjet_Q[k]){
            minDr_PrunedSubjet_Q[k] = BoostedUtils::DeltaR(input.selectedBoostedJets[i].prunedsubjets[k].p4(),q2[j].p4());
          }
          if(minDr_PrunedSubjet_Q[k] < 999) vars.FillVars("BoostedJet_Dr_PrunedSubjet"+to_string(k+1)+"_Q",i,minDr_PrunedSubjet_Q[k]);
        }
        
        // Soft drop subjets
        float minDr_SoftdropSubjet_Q[2] = {999.,999.};
        for(size_t k=0;k<input.selectedBoostedJets[i].sdsubjets.size();k++){
          if (input.selectedBoostedJets[i].sdsubjets[k].pt() == 0) continue;
	      
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[k].p4(),q1[j].p4())<minDr_Q1_SoftdropSubjet){
            minDr_Q1_SoftdropSubjet = BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[k].p4(),q1[j].p4());
          }
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[k].p4(),q2[j].p4())<minDr_Q2_SoftdropSubjet){
            minDr_Q2_SoftdropSubjet = BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[k].p4(),q2[j].p4());
          }
                    
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[k].p4(),q1[j].p4())<minDr_SoftdropSubjet_Q[k]){
            minDr_SoftdropSubjet_Q[k] = BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[k].p4(),q1[j].p4());
          }
        
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[k].p4(),q2[j].p4())<minDr_SoftdropSubjet_Q[k]){
            minDr_SoftdropSubjet_Q[k] = BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdsubjets[k].p4(),q2[j].p4());
          }
          if(minDr_SoftdropSubjet_Q[k] < 999) vars.FillVars("BoostedJet_Dr_SoftdropSubjet"+to_string(k+1)+"_Q",i,minDr_SoftdropSubjet_Q[k]);
        }
        
        // Soft drop z2 b1 subjets
        float minDr_Softdropz2b1Subjet_Q[2] = {999.,999.};
        for(size_t k=0;k<input.selectedBoostedJets[i].sdz2b1subjets.size();k++){
          if (input.selectedBoostedJets[i].sdz2b1subjets[k].pt() == 0) continue;
	      
          if(q1[j].pt() > 0.){
            if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[k].p4(),q1[j].p4())<minDr_Q1_Softdropz2b1Subjet){
              minDr_Q1_Softdropz2b1Subjet = BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[k].p4(),q1[j].p4());
            }
          }
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[k].p4(),q2[j].p4())<minDr_Q2_Softdropz2b1Subjet){
            minDr_Q2_Softdropz2b1Subjet = BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[k].p4(),q2[j].p4());
          }
                              
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[k].p4(),q1[j].p4())<minDr_Softdropz2b1Subjet_Q[k]){
            minDr_Softdropz2b1Subjet_Q[k] = BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[k].p4(),q1[j].p4());
          }
        
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[k].p4(),q2[j].p4())<minDr_Softdropz2b1Subjet_Q[k]){
            minDr_Softdropz2b1Subjet_Q[k] = BoostedUtils::DeltaR(input.selectedBoostedJets[i].sdz2b1subjets[k].p4(),q2[j].p4());
          }
          if(minDr_Softdropz2b1Subjet_Q[k] < 999) vars.FillVars("BoostedJet_Dr_Softdropz2b1Subjet"+to_string(k+1)+"_Q",i,minDr_Softdropz2b1Subjet_Q[k]);
        }
	    }
	  }

    
    if(minDr_WHad<999) vars.FillVars("BoostedJet_Dr_GenW",i,minDr_WHad);
    if(minDr_Q1<999) vars.FillVars("BoostedJet_Dr_GenQ1",i,minDr_Q1);
    if(minDr_Q2<999) vars.FillVars("BoostedJet_Dr_GenQ2",i,minDr_Q2);
    if(minDr_Q1_FilterJet<999) vars.FillVars("BoostedJet_Dr_GenQ1_Filterjet",i,minDr_Q1_FilterJet);
    if(minDr_Q2_FilterJet<999) vars.FillVars("BoostedJet_Dr_GenQ2_Filterjet",i,minDr_Q2_FilterJet);
    if(minDr_Q1_PrunedSubjet<999) vars.FillVars("BoostedJet_Dr_GenQ1_PrunedSubjet",i,minDr_Q1_PrunedSubjet);
    if(minDr_Q2_PrunedSubjet<999) vars.FillVars("BoostedJet_Dr_GenQ2_PrunedSubjet",i,minDr_Q2_PrunedSubjet);
    if(minDr_Q1_SoftdropSubjet<999) vars.FillVars("BoostedJet_Dr_GenQ1_SoftdropSubjet",i,minDr_Q1_SoftdropSubjet);
    if(minDr_Q2_SoftdropSubjet<999) vars.FillVars("BoostedJet_Dr_GenQ2_SoftdropSubjet",i,minDr_Q2_SoftdropSubjet);
    if(minDr_Q1_Softdropz2b1Subjet<999) vars.FillVars("BoostedJet_Dr_GenQ1_Softdropz2b1Subjet",i,minDr_Q1_Softdropz2b1Subjet);
    if(minDr_Q2_Softdropz2b1Subjet<999) vars.FillVars("BoostedJet_Dr_GenQ2_Softdropz2b1Subjet",i,minDr_Q2_Softdropz2b1Subjet);

    std::vector<pat::Jet> filterJets = BoostedUtils::GetHiggsFilterJets(input.selectedBoostedJets[i], 4);
    float dr_GenQ1_CSV1=999;
    float dr_GenQ2_CSV1=999;
    float dr_GenB_CSV1=999;
    float dr_GenQ1_CSV2=999;
    float dr_GenQ2_CSV2=999;
    float dr_GenB_CSV2=999;
    for(size_t j=0;j<tophad.size();j++){
	    if(filterJets.size()>0 && filterJets[0].pt() > 0){
        dr_GenQ1_CSV1=fmin(BoostedUtils::DeltaR(filterJets[0].p4(),q1[j].p4()),dr_GenQ1_CSV1);
	      dr_GenQ2_CSV1=fmin(BoostedUtils::DeltaR(filterJets[0].p4(),q2[j].p4()),dr_GenQ2_CSV1);
	      dr_GenB_CSV1=fmin(BoostedUtils::DeltaR(filterJets[0].p4(),bhad[j].p4()),dr_GenB_CSV1); 
	    }
	    if(filterJets.size()>1 && filterJets[1].pt() > 0){
	      dr_GenQ1_CSV2=fmin(BoostedUtils::DeltaR(filterJets[1].p4(),q1[j].p4()),dr_GenQ1_CSV2);
	      dr_GenQ2_CSV2=fmin(BoostedUtils::DeltaR(filterJets[1].p4(),q2[j].p4()),dr_GenQ2_CSV2);
	      dr_GenB_CSV2=fmin(BoostedUtils::DeltaR(filterJets[1].p4(),bhad[j].p4()),dr_GenB_CSV2);
	    }
    }
    vars.FillVars( "BoostedJet_Dr_GenQ1_CSV1",i,dr_GenQ1_CSV1);
    vars.FillVars( "BoostedJet_Dr_GenQ2_CSV1",i,dr_GenQ2_CSV1);
    vars.FillVars( "BoostedJet_Dr_GenB_CSV1",i,dr_GenB_CSV1);
    vars.FillVars( "BoostedJet_Dr_GenQ1_CSV2",i,dr_GenQ1_CSV2);
    vars.FillVars( "BoostedJet_Dr_GenQ2_CSV2",i,dr_GenQ2_CSV2);
    vars.FillVars( "BoostedJet_Dr_GenB_CSV2",i,dr_GenB_CSV2);

  }
}
