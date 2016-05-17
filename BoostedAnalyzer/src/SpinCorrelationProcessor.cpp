#include "BoostedTTH/BoostedAnalyzer/interface/SpinCorrelationProcessor.hpp"

TLorentzVector Boost(TLorentzVector in_vec, Int_t frame_number, TLorentzVector vec_top_, TLorentzVector vec_antitop_){
  TLorentzVector out_vec;
  switch(frame_number){
    case 0:
      out_vec=in_vec;
      break;
    case 1:
      out_vec.Boost(- (vec_top_+vec_antitop_).BoostVector() );
      break;
    case 2:
      out_vec.Boost(- vec_top_.BoostVector() );
      break;
    case 3:
      out_vec.Boost(- vec_antitop_.BoostVector() );
      break;
  }
  return out_vec;
}

void SetAllVectors(TLorentzVector& vec_top_, TLorentzVector& vec_antitop_, TLorentzVector& vec_b_, TLorentzVector& vec_antib_, TLorentzVector& vec_lepton_, TLorentzVector& vec_antilepton_, int identifier){
  TLorentzVector vec_lepton_tmp=vec_lepton_;
  TLorentzVector vec_antilepton_tmp=vec_antilepton_;
  TLorentzVector vec_b_tmp=vec_b_;
  TLorentzVector vec_antib_tmp=vec_antib_;
  TLorentzVector vec_top_tmp=vec_top_;
  TLorentzVector vec_antitop_tmp=vec_antitop_;
  
  switch(identifier) {
    case 4:
      vec_lepton_=Boost(vec_lepton_tmp,1,vec_top_tmp,vec_antitop_tmp);//boost lepton in ttbar cm system
      vec_antilepton_=Boost(vec_antilepton_tmp,1,vec_top_tmp,vec_antitop_tmp);//boost antilepton in ttbar cm system
      vec_lepton_=Boost(vec_lepton_,3,Boost(vec_top_tmp,1,vec_top_tmp,vec_antitop_tmp),Boost(vec_antitop_tmp,1,vec_top_tmp,vec_antitop_tmp));//boost lepton in antitop rest frame
      vec_antilepton_=Boost(vec_antilepton_,2,Boost(vec_top_tmp,1,vec_top_tmp,vec_antitop_tmp),Boost(vec_antitop_tmp,1,vec_top_tmp,vec_antitop_tmp));//boost antilepton in top rest frame
      vec_b_=Boost(vec_b_tmp,1,vec_top_tmp,vec_antitop_tmp);//boost b quark in ttbar cm system
      vec_antib_=Boost(vec_antib_tmp,1,vec_top_tmp,vec_antitop_tmp);//boost anti b quark in ttbar cm system
      vec_b_=Boost(vec_b_,2,Boost(vec_top_tmp,1,vec_top_tmp,vec_antitop_tmp),Boost(vec_antitop_tmp,1,vec_top_tmp,vec_antitop_tmp));//boost b quark in top rest frame
      vec_antib_=Boost(vec_antib_,3,Boost(vec_top_tmp,1,vec_top_tmp,vec_antitop_tmp),Boost(vec_antitop_tmp,1,vec_top_tmp,vec_antitop_tmp));//boost anti b quark in antitop rest frame
      vec_top_=Boost(vec_top_tmp,1,vec_top_tmp,vec_antitop_tmp);
      vec_antitop_=Boost(vec_antitop_tmp,1,vec_top_tmp,vec_antitop_tmp);
      vec_top_=Boost(vec_top_,2,Boost(vec_top_tmp,1,vec_top_tmp,vec_antitop_tmp),Boost(vec_antitop_tmp,1,vec_top_tmp,vec_antitop_tmp));
      vec_antitop_=Boost(vec_antitop_,3,Boost(vec_top_tmp,1,vec_top_tmp,vec_antitop_tmp),Boost(vec_antitop_tmp,1,vec_top_tmp,vec_antitop_tmp));
      break;
    default:
      vec_lepton_=Boost(vec_lepton_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost lepton in corresponding system
      vec_antilepton_=Boost(vec_antilepton_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost antilepton in corresponding system
      vec_top_=Boost(vec_top_tmp,identifier,vec_top_tmp,vec_antitop_tmp);
      vec_antitop_=Boost(vec_antitop_tmp,identifier,vec_top_tmp,vec_antitop_tmp);
      vec_b_=Boost(vec_b_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost b quark in corresponding system
      vec_antib_=Boost(vec_antib_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost anti b quark in corresponding system
      break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

SpinCorrelationProcessor::SpinCorrelationProcessor (){}
SpinCorrelationProcessor::~SpinCorrelationProcessor (){}

void SpinCorrelationProcessor::Init(const InputCollections& input,VariableContainer& vars){
  
  std::vector<TString> frames;
  std::vector<TString> variables;
  
  frames.push_back("lab");
  frames.push_back("ttbar_cm");
  //frames.push_back("top_rest");
  //frames.push_back("antitop_rest");
  frames.push_back("special");
  
  variables.push_back("cos(theta_ll)");
  variables.push_back("cos(theta_bb)");
  variables.push_back("cos(theta_l*)");
  variables.push_back("cos(theta_lbar*)");
  variables.push_back("cos(theta_lb)");
  variables.push_back("cos(theta_lbarbbar)");
  variables.push_back("Delta_Phi_lb");
  variables.push_back("Delta_Phi_lbarbbar");
  variables.push_back("Delta_Phi_ll");
  //variables.push_back("Delta_Phi_bb");
  variables.push_back("Delta_Eta_ll");
  variables.push_back("Delta_Eta_bb");
  
  for(auto it_frames=frames.begin();it_frames!=frames.end();++it_frames) {
    for(auto it_variables=variables.begin();it_variables!=variables.end();++it_variables) {
      vars.InitVar((*it_frames)+"|"+(*it_variables),-9.,"F");
    }
  }
  
  initialized=true;
  
}


void SpinCorrelationProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
 
  std::map<TString,int> frames;
  frames["lab"]=0;
  frames["ttbar_cm"]=1;
  //frames["top_rest"]=2;
  //frames["antitop_rest"]=3;
  frames["special"]=4;
  
  if(!(input.genTopEvt.IsFilled())) return;
  
  std::vector<reco::GenParticle> tophad;
  std::vector<reco::GenParticle> bhad;
  std::vector<reco::GenParticle> toplep;
  std::vector<reco::GenParticle> blep;
  std::vector<reco::GenParticle> lep;
  
  if(input.genTopEvt.IsFilled()){
    tophad=input.genTopEvt.GetAllTopHads();
    bhad=input.genTopEvt.GetAllTopHadDecayQuarks();
    toplep=input.genTopEvt.GetAllTopLeps();
    blep=input.genTopEvt.GetAllTopLepDecayQuarks();
    lep=input.genTopEvt.GetAllLeptons();
    //additional_bs=input.genTopEvt.GetAdditionalBGenJets();
  }

  bool isDL;
  bool isSL;
  
  if(tophad.size()==0 and toplep.size()==2) {
    isDL=true;
    isSL=false;
  }
  if(tophad.size()==1 and toplep.size()==1) {
    isSL=true;
    isDL=false;
  }
  if(tophad.size()==2 and toplep.size()==0) {
    isSL=false;
    isDL=false;
    return;
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  // Set Vectors, which are present in every ttbar event
  math::XYZTLorentzVector vec_top;
  math::XYZTLorentzVector vec_antitop;
  math::XYZTLorentzVector vec_b;
  math::XYZTLorentzVector vec_antib;
  
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
  ///////////////////////////////////////////////////////////////////////////////////////////
  
  math::XYZTLorentzVector vec_lepton;
  math::XYZTLorentzVector vec_antilepton;
  math::XYZTLorentzVector vec_zero(0.,0.,0.,0.);
  
  
  if(isSL) {
    if(toplep[0].pdgId()>0) {
      vec_lepton=toplep[0].p4();
      vec_antilepton=vec_zero;
    }
    else if(toplep[0].pdgId()<0) {
      vec_antilepton=toplep[0].p4();
      vec_lepton=vec_zero;
    }   
  }
  
  if(isDL) {
    if(toplep[0].pdgId()>0) {
      vec_lepton=toplep[0].p4();
    }
    else if(toplep[1].pdgId()>0) {
      vec_lepton=toplep[1].p4();
    }
    if(toplep[0].pdgId()<0) {
      vec_antilepton=toplep[0].p4();
    }
    else if(toplep[1].pdgId()<0) {
      vec_antilepton=toplep[1].p4();
    }
  }
  
  TLorentzVector vec_lepton_=BoostedUtils::GetTLorentzVector(vec_lepton);
  TLorentzVector vec_antilepton_=BoostedUtils::GetTLorentzVector(vec_antilepton);
  TLorentzVector vec_top_=BoostedUtils::GetTLorentzVector(vec_top);
  TLorentzVector vec_antitop_=BoostedUtils::GetTLorentzVector(vec_antitop);
  TLorentzVector vec_b_=BoostedUtils::GetTLorentzVector(vec_b);
  TLorentzVector vec_antib_=BoostedUtils::GetTLorentzVector(vec_antib);
  
  for(auto it_frames=frames.begin();it_frames!=frames.end();++it_frames) {
    SetAllVectors(vec_top_,vec_antitop_,vec_b_,vec_antib_,vec_lepton_,vec_antilepton_,it_frames->second);
  
    
    
  }
  
}