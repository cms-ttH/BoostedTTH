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
  
  vars.InitVars( "BoostedJet_Dr_GenQ1_Filterjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_Filterjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB1_Filterjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB2_Filterjet",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ1_CSV1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_CSV1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB_CSV1",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ1_CSV2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenQ2_CSV2",-9.,"N_BoostedJets" );
  vars.InitVars( "BoostedJet_Dr_GenB_CSV2",-9.,"N_BoostedJets" );

  vars.InitVars("BoostedJet_Dr_ZTop",-9.,"N_BoostedJets");
  vars.InitVars("BoostedJet_Dr_GenB_ZTop",-9.,"N_BoostedJets");
  vars.InitVars("BoostedJet_Dr_GenW_ZTop",-9.,"N_BoostedJets");
  vars.InitVars("BoostedJet_Dr_bfromTPrime",-9.,"N_BoostedJets");
  vars.InitVars("BoostedJet_Dr_GenZTop_bfromTPrime",-9.,"N_BoostedJets");
  vars.InitVars("BoostedJet_Dr_GenWfromTPrime_bfromTPrime",-9.,"N_BoostedJets");
  vars.InitVars("BoostedJet_Dr_WfromTPrime",-9.,"N_BoostedJets");
  vars.InitVars("BoostedJet_Dr_GenZTop_WfromTPrime",-9.,"N_BoostedJets");
  vars.InitVars("BoostedJet_Dr_GenbfromTPrime_WfromTPrime",-9.,"N_BoostedJets");  

  
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
  
  std::vector<reco::GenParticle> ZTop;
  std::vector<reco::GenParticle> TPrime;
  std::vector<reco::GenParticle> WfromTPrime;
  std::vector<reco::GenParticle> bfromTPrime;

  
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
  if(input.zprimetotprimeallhad.IsFilled()){
    ZTop=input.zprimetotprimeallhad.GetTopsandTopbars();
    TPrime=input.zprimetotprimeallhad.GetTPrimesandTPrimebars();
    WfromTPrime=input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars();
    bfromTPrime=input.zprimetotprimeallhad.GetBottom_fromTPrimesandTPrimebars();
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
    cout<<"ZPrime filled ?:  "<<input.zprimetotprimeallhad.IsFilled()<<endl;
    
    if(input.zprimetotprimeallhad.IsFilled()){
        float minDr_ZTop = 999;
        float minDr_GenB_ZTop = 999;
        float minDr_GenW_ZTop = 999;
        float minDr_bfromTPrime = 999;
        float minDr_GenZTop_bfromTPrime=999;
        float minDr_GenWfromTPrime_bfromTPrime=999;
        float minDr_WfromTPrime = 999;
        float minDr_GenZTop_WfromTPrime=999;
        float minDr_GenbfromTPrime_WfromTPrime=999;        
        
        cout<<"ZTopsize:  "<<ZTop.size()<<endl;
        for(size_t j=0;j<ZTop.size();j++){
            float Dr_ZTop_temp = BoostedUtils::DeltaR(ZTop[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
                if(Dr_ZTop_temp<minDr_ZTop){
                    minDr_ZTop = Dr_ZTop_temp;
                    cout<<"minDr_ZTop:  "<<minDr_ZTop<<endl;
//                    minDr_GenB_ZTop = BoostedUtils::DeltaR(bfromTPrime[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
//                    minDr_GenW_ZTop = BoostedUtils::DeltaR(WfromTPrime[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
//                    cout<<"minDr_GenW_ZTop:  "<<minDr_GenW_ZTop<<endl;
                }
        }
        for(size_t j=0;j<bfromTPrime.size();j++){   
            float Dr_B_temp = BoostedUtils::DeltaR(bfromTPrime[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
                if(Dr_B_temp<minDr_bfromTPrime){
                    minDr_bfromTPrime = Dr_B_temp;
                    cout<<"minDr_bfromTPrime:  "<<minDr_bfromTPrime<<endl;
//                    minDr_GenZTop_bfromTPrime = BoostedUtils::DeltaR(ZTop[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
//                    minDr_GenWfromTPrime_bfromTPrime = BoostedUtils::DeltaR(WfromTPrime[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
                }
        }        
        for(size_t j=0;j<WfromTPrime.size();j++){
            float Dr_W_temp = BoostedUtils::DeltaR(WfromTPrime[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
                if(Dr_W_temp<minDr_WfromTPrime){
                    minDr_WfromTPrime = Dr_W_temp;
                    cout<<"minDr_WfromTPrime:  "<<minDr_WfromTPrime<<endl;
//                    minDr_GenbfromTPrime_WfromTPrime = BoostedUtils::DeltaR(bfromTPrime[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
//                    minDr_GenZTop_WfromTPrime = BoostedUtils::DeltaR(ZTop[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
                }            
        
        }
           
        if(minDr_ZTop<999) vars.FillVars("BoostedJet_Dr_ZTop",i,minDr_ZTop);
        if(minDr_GenB_ZTop<999) vars.FillVars("BoostedJet_Dr_GenB_ZTop",i,minDr_GenB_ZTop);
        if(minDr_GenW_ZTop<999) vars.FillVars("BoostedJet_Dr_GenW_ZTop",i,minDr_GenW_ZTop);
        if(minDr_bfromTPrime<999) vars.FillVars("BoostedJet_Dr_bfromTPrime",i,minDr_bfromTPrime);
        if(minDr_GenZTop_bfromTPrime<999) vars.FillVars("BoostedJet_Dr_GenZTop_bfromTPrime",i,minDr_GenZTop_bfromTPrime);
        if(minDr_GenWfromTPrime_bfromTPrime<999) vars.FillVars("BoostedJet_Dr_GenWfromTPrime_bfromTPrime",i,minDr_GenWfromTPrime_bfromTPrime);
        if(minDr_WfromTPrime<999) vars.FillVars("BoostedJet_Dr_WfromTPrime",i,minDr_WfromTPrime);
        if(minDr_GenZTop_WfromTPrime<999) vars.FillVars("BoostedJet_Dr_GenZTop_WfromTPrime",i,minDr_GenZTop_WfromTPrime);
        if(minDr_GenbfromTPrime_WfromTPrime<999) vars.FillVars("BoostedJet_Dr_GenbfromTPrime_WfromTPrime",i,minDr_GenbfromTPrime_WfromTPrime);        



    }
    

    if(minDr_TopHad<999){
        vars.FillVars("BoostedJet_Dr_GenTopHad",i,minDr_TopHad);
        //cout<<"BoostedJet_Dr_GenTopHad:  "<<minDr_TopHad;
    }
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
      
      double minDrB1 = 999;
      double minDrB2 = 999;
      
      for(size_t j=0;j<input.selectedBoostedJets[i].filterjets.size();j++){
	
        if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[j].p4(),b1.p4())<minDrB1){
          minDrB1 = BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[j].p4(),b1.p4());
        }
        if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[j].p4(),b2.p4())<minDrB2){
          if(b2.pt()>0.) minDrB2 = BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[j].p4(),b2.p4());
        }
      }
      
      if(minDrB1<999) vars.FillVars("BoostedJet_Dr_GenB1_Filterjet",i,minDrB1);
      if(minDrB2<999) vars.FillVars("BoostedJet_Dr_GenB2_Filterjet",i,minDrB2); 
    }
    
    float minDr_WHad = 999;
    float minDr_Q1 = 999;
    float minDr_Q2 = 999;
    float minDr_Q1_FilterJet = 999;
    float minDr_Q2_FilterJet = 999;
   
    for(size_t j=0;j<whad.size();j++){
    
      float Dr_temp = BoostedUtils::DeltaR(whad[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
      
	    if(Dr_temp<minDr_WHad){
	  	  minDr_WHad = Dr_temp;
		  minDr_Q1 = BoostedUtils::DeltaR(q1[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
		  minDr_Q2 = BoostedUtils::DeltaR(q2[j].p4(),input.selectedBoostedJets[i].fatjet.p4());
        
        for(size_t k=0;k<input.selectedBoostedJets[i].filterjets.size();k++){
	      
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[k].p4(),q1[j].p4())<minDr_Q1_FilterJet){
            minDr_Q1_FilterJet = BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[k].p4(),q1[j].p4());
          }
          if(BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[k].p4(),q2[j].p4())<minDr_Q2_FilterJet){
            minDr_Q2_FilterJet = BoostedUtils::DeltaR(input.selectedBoostedJets[i].filterjets[k].p4(),q2[j].p4());
          }
        }
	    }
	  }

    
    if(minDr_WHad<999) vars.FillVars("BoostedJet_Dr_GenW",i,minDr_WHad);
    if(minDr_Q1<999) vars.FillVars("BoostedJet_Dr_GenQ1",i,minDr_Q1);
    if(minDr_Q2<999) vars.FillVars("BoostedJet_Dr_GenQ2",i,minDr_Q2);
    if(minDr_Q1_FilterJet<999) vars.FillVars("BoostedJet_Dr_GenQ1_Filterjet",i,minDr_Q1_FilterJet);
    if(minDr_Q2_FilterJet<999) vars.FillVars("BoostedJet_Dr_GenQ2_Filterjet",i,minDr_Q2_FilterJet);

    std::vector<pat::Jet> filterJets = BoostedUtils::GetHiggsFilterJets(input.selectedBoostedJets[i], 4);
    float dr_GenQ1_CSV1=999;
    float dr_GenQ2_CSV1=999;
    float dr_GenB_CSV1=999;
    float dr_GenQ1_CSV2=999;
    float dr_GenQ2_CSV2=999;
    float dr_GenB_CSV2=999;

    for(size_t j=0;j<tophad.size();j++){
	if(filterJets.size()>0){
	    dr_GenQ1_CSV1=fmin(BoostedUtils::DeltaR(filterJets[0].p4(),q1[j].p4()),dr_GenQ1_CSV1);
	    dr_GenQ2_CSV1=fmin(BoostedUtils::DeltaR(filterJets[0].p4(),q2[j].p4()),dr_GenQ2_CSV1);
	    dr_GenB_CSV1=fmin(BoostedUtils::DeltaR(filterJets[0].p4(),bhad[j].p4()),dr_GenB_CSV1);	    
	}
	if(filterJets.size()>1){
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
