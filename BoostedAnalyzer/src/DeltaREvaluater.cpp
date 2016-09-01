#include "BoostedTTH/BoostedAnalyzer/interface/DeltaREvaluater.hpp"

using namespace std;

DeltaREvaluater::DeltaREvaluater (){}
DeltaREvaluater::~DeltaREvaluater (){}

void DeltaREvaluater::Init(const InputCollections& input,VariableContainer& vars){
  /*
  vars.InitVar("dR_t_antit",-9.,"F");
  vars.InitVar("dR_b_antib",-9.,"F");
  vars.InitVar("dR_q_u_antiq_d",-9.,"F");
  vars.InitVar("dR_q_d_antiq_u",-9.,"F");
  
  vars.InitVar("dR_t_b",-9.,"F");
  vars.InitVar("dR_antit_antib",-9.,"F");
  vars.InitVar("dR_t_antib",-9.,"F");
  vars.InitVar("dR_antit_b",-9.,"F");
  
  vars.InitVar("dR_t_q_u",-9.,"F");
  vars.InitVar("dR_t_antiq_u",-9.,"F");
  vars.InitVar("dR_antit_q_u",-9.,"F");
  vars.InitVar("dR_antit_antiq_u",-9.,"F");
  
  vars.InitVar("dR_t_q_d",-9.,"F");
  vars.InitVar("dR_t_antiq_d",-9.,"F");
  vars.InitVar("dR_antit_q_d",-9.,"F");
  vars.InitVar("dR_antit_antiq_d",-9.,"F");
  
  vars.InitVar("dR_b_q_u",-9.,"F");
  vars.InitVar("dR_b_antiq_u",-9.,"F");
  vars.InitVar("dR_antib_q_u",-9.,"F");
  vars.InitVar("dR_antib_antiq_u",-9.,"F");
  
  vars.InitVar("dR_b_q_d",-9.,"F");
  vars.InitVar("dR_b_antiq_d",-9.,"F");
  vars.InitVar("dR_antib_q_d",-9.,"F");
  vars.InitVar("dR_antib_antiq_d",-9.,"F");
  */
  vars.InitVar("dR_combinations",19,"I");
  vars.InitVars("dRs_top_event","dR_combinations");
  vars.InitVar("lepton_flag",0.,"F");
  
  initialized=true;
}

void DeltaREvaluater::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  
  
  std::vector<TString> variables;
  std::map<TString,double> values;
  
  math::XYZTLorentzVector vec_top;
  math::XYZTLorentzVector vec_antitop;
  math::XYZTLorentzVector vec_b;
  math::XYZTLorentzVector vec_antib;
  math::XYZTLorentzVector vec_lepton;
  math::XYZTLorentzVector vec_antilepton;
  math::XYZTLorentzVector vec_q_u;
  math::XYZTLorentzVector vec_antiq_u;
  math::XYZTLorentzVector vec_antiq_d;
  math::XYZTLorentzVector vec_q_d;
  math::XYZTLorentzVector vec_nu;
  math::XYZTLorentzVector vec_antinu;
  math::XYZTLorentzVector vec_zero(0.,0.,0.,0.);
  
  bool gen_evt_filled=input.genTopEvt.IsFilled();
  bool no_tau_selection=true;
  
  // some flags which help later
  bool isSL=false;
  
  int leptonflag=0;// flag for lepton=1, for antilepton=-1

  
  if(gen_evt_filled){
    //cout << "GenTopEvt is filled " << endl;
    std::vector<reco::GenParticle> tophad;
    std::vector<reco::GenParticle> bhad;
    std::vector<reco::GenParticle> toplep;
    std::vector<reco::GenParticle> blep;
    std::vector<reco::GenParticle> lep;
    std::vector<reco::GenParticle> q1;
    std::vector<reco::GenParticle> q2;
    std::vector<reco::GenParticle> nu;
    tophad=input.genTopEvt.GetAllTopHads();
    bhad=input.genTopEvt.GetAllTopHadDecayQuarks();
    toplep=input.genTopEvt.GetAllTopLeps();
    blep=input.genTopEvt.GetAllTopLepDecayQuarks();
    lep=input.genTopEvt.GetAllLeptons();
    q1=input.genTopEvt.GetAllWQuarks();
    q2=input.genTopEvt.GetAllWAntiQuarks();
    nu=input.genTopEvt.GetAllNeutrinos();
    //additional_bs=input.genTopEvt.GetAdditionalBGenJets();
    
  
    // identify the kind of decay
    if(tophad.size()==0 and toplep.size()==2) {
      isSL=false;
      //cout << "Dilepton Event! " << endl;
      return;
    }
    else if(tophad.size()==1 and toplep.size()==1 and q1.size()>=1 and q2.size()>=1) {
      isSL=true;
      //cout << "Single Lepton Event! " << endl;
    }
    else if(tophad.size()==2 and toplep.size()==0) {
      isSL=false;
      //cout << "Fully hadronic Event! " << endl;
      return;
    }
    else {
      return;
    }
    
    
    // make the correct assignment of the top/antitop b/antib 4-vectors
    for(auto it=tophad.begin();it!=tophad.end();++it) {
      if(it->pdgId()>0) { vec_top=it->p4(); }
      else if(it->pdgId()<0) { vec_antitop=it->p4(); }
    }
    for(auto it=toplep.begin();it!=toplep.end();++it) {
      if(it->pdgId()>0) { vec_top=it->p4(); }
      else if(it->pdgId()<0) { vec_antitop=it->p4(); }
    }
    for(auto it=bhad.begin();it!=bhad.end();++it) {
      if(it->pdgId()>0) { vec_b=it->p4(); }
      else if(it->pdgId()<0) { vec_antib=it->p4(); }
    }
    for(auto it=blep.begin();it!=blep.end();++it) {
      if(it->pdgId()>0) { vec_b=it->p4(); }
      else if(it->pdgId()<0) { vec_antib=it->p4(); }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // now identify the correct lepton/antilepton 4 vectors
    // in SL case, the lepton/antilepton which is not present will be assigned with a (0,0,0,0) 4-vector, pdgid>0 ->leptons pdgid<0 antileptons
    if(isSL) {
      if(lep[0].pdgId()>0) {
	if(lep[0].pdgId()==15 && no_tau_selection) {return;}
	vec_lepton=lep[0].p4();
	vec_antilepton=vec_zero;
	leptonflag=1;
	//cout << "Lepton! " << endl;
      }
      else if(lep[0].pdgId()<0) {
	if(lep[0].pdgId()==-15 && no_tau_selection) {return;}
	vec_antilepton=lep[0].p4();
	vec_lepton=vec_zero;
	leptonflag=-1;
	//cout << "Antilepton! " << endl;
      }   
    }
    //cout << "Leptonflag: " << leptonflag << endl;
    if(leptonflag==1) {
      vec_q_u=q1[0].p4();
      vec_antiq_d=q2[0].p4();
      vec_antinu=nu[0].p4();
      vec_nu=vec_zero;
    }
    else if(leptonflag==-1) {
      vec_q_d=q1[0].p4();
      vec_antiq_u=q2[0].p4();
      vec_nu=nu[0].p4();
      vec_antinu=vec_zero;
    }
    
    
    
    values["dR_t_antit"]=BoostedUtils::DeltaR(vec_top,vec_antitop);
    values["dR_b_antib"]=BoostedUtils::DeltaR(vec_b,vec_antib);
    values["dR_t_b"]=BoostedUtils::DeltaR(vec_top,vec_b);
    values["dR_t_antib"]=BoostedUtils::DeltaR(vec_top,vec_antib);
    values["dR_antit_antib"]=BoostedUtils::DeltaR(vec_antitop,vec_antib);
    values["dR_antit_b"]=BoostedUtils::DeltaR(vec_antitop,vec_b);
    
    variables.push_back("dR_t_antit");
    variables.push_back("dR_b_antib");
    variables.push_back("dR_t_b");
    variables.push_back("dR_t_antib");
    variables.push_back("dR_antit_antib");
    variables.push_back("dR_antit_b");
    
    if(leptonflag==1) {
      //cout << "negative charge lepton" << endl;
    
      values["dR_t_q_u"]=BoostedUtils::DeltaR(vec_top,vec_q_u);
      values["dR_t_antiq_d"]=BoostedUtils::DeltaR(vec_top,vec_antiq_d);
      values["dR_antit_q_u"]=BoostedUtils::DeltaR(vec_antitop,vec_q_u);
      values["dR_antit_antiq_d"]=BoostedUtils::DeltaR(vec_antitop,vec_antiq_d);
      
      values["dR_b_q_u"]=BoostedUtils::DeltaR(vec_b,vec_q_u);
      values["dR_b_antiq_d"]=BoostedUtils::DeltaR(vec_b,vec_antiq_d);
      values["dR_antib_q_u"]=BoostedUtils::DeltaR(vec_antib,vec_q_u);
      values["dR_antib_antiq_d"]=BoostedUtils::DeltaR(vec_antib,vec_antiq_d);
      
      values["dR_q_u_antiq_d"]=BoostedUtils::DeltaR(vec_q_u,vec_antiq_d);
      
      values["dR_t_lep"]=BoostedUtils::DeltaR(vec_top,vec_lepton);
      values["dR_b_lep"]=BoostedUtils::DeltaR(vec_b,vec_lepton);
      values["dR_antit_lep"]=BoostedUtils::DeltaR(vec_antitop,vec_lepton);
      values["dR_antib_lep"]=BoostedUtils::DeltaR(vec_antib,vec_lepton);
      
      values["m_antib_lep_antinu"]=(vec_antib+vec_lepton+vec_antinu).mass();
      values["m_b_q_u_antiq_d"]=(vec_b+vec_q_u+vec_antiq_d).mass();
      values["m_lep_antinu"]=(vec_lepton+vec_antinu).mass();
      values["m_q_u_antiq_d"]=(vec_q_u+vec_antiq_d).mass();
      
      variables.push_back("dR_t_q_u");
      variables.push_back("dR_t_antiq_d");
      variables.push_back("dR_antit_q_u");
      variables.push_back("dR_antit_antiq_d");
      
      variables.push_back("dR_b_q_u");
      variables.push_back("dR_b_antiq_d");
      variables.push_back("dR_antib_q_u");
      variables.push_back("dR_antib_antiq_d");
      
      variables.push_back("dR_q_u_antiq_d");
      
      variables.push_back("dR_t_lep");
      variables.push_back("dR_b_lep");
      variables.push_back("dR_antit_lep");
      variables.push_back("dR_antib_lep");
      
      //variables.push_back("m_antib_lep_antinu");
      //variables.push_back("m_b_q_u_antiq_d");
      //variables.push_back("m_lep_antinu");
      //variables.push_back("m_q_u_antiq_d");
      
    }
    else if(leptonflag==-1) {
      //cout << "positive charge lepton" << endl;
    
      values["dR_t_antiq_u"]=BoostedUtils::DeltaR(vec_top,vec_antiq_u);
      values["dR_t_q_d"]=BoostedUtils::DeltaR(vec_top,vec_q_d);
      values["dR_antit_antiq_u"]=BoostedUtils::DeltaR(vec_antitop,vec_antiq_u);
      values["dR_antit_q_d"]=BoostedUtils::DeltaR(vec_antitop,vec_q_d);
      
      values["dR_b_antiq_u"]=BoostedUtils::DeltaR(vec_b,vec_antiq_u);
      values["dR_b_q_d"]=BoostedUtils::DeltaR(vec_b,vec_q_d);
      values["dR_antib_antiq_u"]=BoostedUtils::DeltaR(vec_antib,vec_antiq_u);
      values["dR_antib_q_d"]=BoostedUtils::DeltaR(vec_antib,vec_q_d);
      
      values["dR_q_d_antiq_u"]=BoostedUtils::DeltaR(vec_q_d,vec_antiq_u);
      
      values["dR_t_antilep"]=BoostedUtils::DeltaR(vec_top,vec_antilepton);
      values["dR_b_antilep"]=BoostedUtils::DeltaR(vec_b,vec_antilepton);
      values["dR_antit_antilep"]=BoostedUtils::DeltaR(vec_antitop,vec_antilepton);
      values["dR_antib_antilep"]=BoostedUtils::DeltaR(vec_antib,vec_antilepton);
      
      values["m_b_antilep_nu"]=(vec_b+vec_antilepton+vec_nu).mass();
      values["m_antib_q_d_antiq_u"]=(vec_antib+vec_q_d+vec_antiq_u).mass();
      values["m_antilep_nu"]=(vec_antilepton+vec_nu).mass();
      values["m_q_d_antiq_u"]=(vec_q_d+vec_antiq_u).mass();
      
      variables.push_back("dR_t_antiq_u");
      variables.push_back("dR_t_q_d");
      variables.push_back("dR_antit_antiq_u");
      variables.push_back("dR_antit_q_d");
      
      variables.push_back("dR_b_antiq_u");
      variables.push_back("dR_b_q_d");
      variables.push_back("dR_antib_antiq_u");
      variables.push_back("dR_antib_q_d");
      
      variables.push_back("dR_q_d_antiq_u");
      
      variables.push_back("dR_t_antilep");
      variables.push_back("dR_b_antilep");
      variables.push_back("dR_antit_antilep");
      variables.push_back("dR_antib_antilep");
      
      //variables.push_back("m_b_antilep_nu");
      //variables.push_back("m_antib_q_d_antiq_u");
      //variables.push_back("m_antilep_nu");
      //variables.push_back("m_q_d_antiq_u");
    }
    
    int array_size=variables.size();
    
    //cout << "Array size " << array_size << endl;
    
    for(int i=0;i<array_size;i++) {
      //cout << i << "   " << values[variables[i]] << endl;
      vars.FillVars("dRs_top_event",i,values[variables[i]]);
    }
    vars.FillVar("lepton_flag",leptonflag);
    
  }
  
  else {return;}
  
  
  
  
}