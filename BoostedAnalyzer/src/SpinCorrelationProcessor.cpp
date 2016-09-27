#include "BoostedTTH/BoostedAnalyzer/interface/SpinCorrelationProcessor.hpp"

// function to do some basic boosts on a TLorentzVectors using the number of the corresponding frame and the top/antitop 4-vectors
TLorentzVector SpinCorrelationProcessor::Boost(TLorentzVector in_vec, Int_t frame_number, TLorentzVector vec_top_, TLorentzVector vec_antitop_){
  TLorentzVector out_vec=in_vec;
  //cout << "out_vec pt before boost: " << out_vec.Pt() << endl;
  //cout << "boost frame_number: " << frame_number << endl;
  switch(frame_number){
    case 0:
      // no boost, so stay in lab frame
      break;
    case 1:
      // boost in ttbar cm frame
      out_vec.Boost(- (vec_top_+vec_antitop_).BoostVector() );
      break;
    case 2:
      // boost in top rest frame
      out_vec.Boost(- vec_top_.BoostVector() );
      break;
    case 3:
      // boost in antitop rest frame
      out_vec.Boost(- vec_antitop_.BoostVector() );
      break;
  }
  //cout << "out_vec pt after boost: " << out_vec.Pt() << endl;
  return out_vec;
}

// function which sets all the 4-vectors of the event according to the desired frame
void SpinCorrelationProcessor::SetAllVectors(TLorentzVector& vec_top_, TLorentzVector& vec_antitop_, TLorentzVector& vec_b_, TLorentzVector& vec_antib_, TLorentzVector& vec_lepton_, TLorentzVector& vec_antilepton_,TLorentzVector& vec_d_,TLorentzVector& vec_antid_, int identifier){
  
  //cout << "frame identifier: " << identifier << endl;
  
  TLorentzVector vec_lepton_tmp=vec_lepton_;
  TLorentzVector vec_antilepton_tmp=vec_antilepton_;
  TLorentzVector vec_b_tmp=vec_b_;
  TLorentzVector vec_antib_tmp=vec_antib_;
  TLorentzVector vec_top_tmp=vec_top_;
  TLorentzVector vec_antitop_tmp=vec_antitop_;
  TLorentzVector vec_d_tmp=vec_d_;
  TLorentzVector vec_antid_tmp=vec_antid_;
  
    /*cout << "top pt before: " << vec_top_.Pt() << endl;
    cout << "antitop pt before: " << vec_antitop_.Pt() << endl;
    cout << "b pt before: " << vec_b_.Pt() << endl;
    cout << "antib pt before: " << vec_antib_.Pt() << endl;
    cout << "lepton pt before: " << vec_lepton_.Pt() << endl;
    cout << "antilepton pt before: " << vec_antilepton_.Pt() << endl;*/
  
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
      vec_d_=Boost(vec_d_tmp,1,vec_top_tmp,vec_antitop_tmp);
      vec_antid_=Boost(vec_antid_tmp,1,vec_top_tmp,vec_antitop_tmp);
      vec_d_=Boost(vec_d_,2,Boost(vec_top_tmp,1,vec_top_tmp,vec_antitop_tmp),Boost(vec_antitop_tmp,1,vec_top_tmp,vec_antitop_tmp));
      vec_antid_=Boost(vec_antid_,3,Boost(vec_top_tmp,1,vec_top_tmp,vec_antitop_tmp),Boost(vec_antitop_tmp,1,vec_top_tmp,vec_antitop_tmp));
      //vec_top_=Boost(vec_top_,2,Boost(vec_top_tmp,1,vec_top_tmp,vec_antitop_tmp),Boost(vec_antitop_tmp,1,vec_top_tmp,vec_antitop_tmp));
      //vec_antitop_=Boost(vec_antitop_,3,Boost(vec_top_tmp,1,vec_top_tmp,vec_antitop_tmp),Boost(vec_antitop_tmp,1,vec_top_tmp,vec_antitop_tmp));
      break;
    default:
      vec_lepton_=Boost(vec_lepton_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost lepton in corresponding system
      vec_antilepton_=Boost(vec_antilepton_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost antilepton in corresponding system
      vec_top_=Boost(vec_top_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost top in corresponding system
      vec_antitop_=Boost(vec_antitop_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost antitop in corresponding system
      vec_b_=Boost(vec_b_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost b quark in corresponding system
      vec_antib_=Boost(vec_antib_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost anti b quark in corresponding system
      vec_d_=Boost(vec_d_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//bost downtype quark in corresponding system
      vec_antid_=Boost(vec_antid_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost downtype antiquark in corresponding system
      break;
  }
  
    /*cout << "top pt after: " << vec_top_.Pt() << endl;
    cout << "antitop pt after: " << vec_antitop_.Pt() << endl;
    cout << "b pt after: " << vec_b_.Pt() << endl;
    cout << "antib pt after: " << vec_antib_.Pt() << endl;
    cout << "lepton pt after: " << vec_lepton_.Pt() << endl;
    cout << "antilepton pt after: " << vec_antilepton_.Pt() << endl;*/
}

// this function calculates all desired variables using their identification number
double SpinCorrelationProcessor::GetVars(TLorentzVector vec_top_, TLorentzVector vec_antitop_, TLorentzVector vec_b_,TLorentzVector vec_antib_, TLorentzVector vec_lepton_,TLorentzVector vec_antilepton_,TLorentzVector vec_d_,TLorentzVector vec_antid_, Int_t var_number) {
  double out=-1.;
  //cout << "var number 2: " << var_number << endl;
  switch(var_number) {
  
    case 0:
      // cos(b bbar)
      out=TMath::Cos((vec_b_.Vect()).Angle(vec_antib_.Vect()));
      break;
    case 1:
      // eta(b bbar)
      out=TMath::Abs(vec_b_.Eta()-vec_antib_.Eta());
      break;
    case 2:
      // phi(b bbar)
      out=TMath::Abs(vec_b_.Phi()-vec_antib_.Phi());
      if(out>TMath::Pi()){
 	out=2*TMath::Pi()-out;
      }
      break;
    case 3:
      // cos(l lbar)
      out=TMath::Cos((vec_lepton_.Vect()).Angle(vec_antilepton_.Vect()));
      break;
    case 4:
      // phi(l lbar)
      out=TMath::Abs(vec_lepton_.Phi()-vec_antilepton_.Phi());
      if(out>TMath::Pi()){
 	out=2*TMath::Pi()-out;
      }
      break;
    case 5:
      // eta(l lbar)
      out=TMath::Abs(vec_lepton_.Eta()-vec_antilepton_.Eta());
      break;
    case 6:
      // cos(l tbar)
      out=TMath::Cos((vec_lepton_.Vect()).Angle(vec_antitop_.Vect()));
      break;
    case 7:
      // cos(lbar t)
      out=TMath::Cos((vec_antilepton_.Vect()).Angle(vec_top_.Vect()));
      break;
    case 8:
      // cos(l b)
      out=TMath::Cos((vec_lepton_.Vect()).Angle(vec_b_.Vect()));
      break;
    case 9:
      // cos(lbar bbar)
      out=TMath::Cos((vec_antilepton_.Vect()).Angle(vec_antib_.Vect()));
      break;
    case 10:
      // phi(l b)
      out=TMath::Abs(vec_lepton_.Phi()-vec_b_.Phi());
      if(out>TMath::Pi()){
 	out=2*TMath::Pi()-out;
      }
      break;
    case 11:
      // phi(lbar bbar)
      out=TMath::Abs(vec_antilepton_.Phi()-vec_antib_.Phi());
      if(out>TMath::Pi()){
 	out=2*TMath::Pi()-out;
      }
      break; 
    case 12:
      // cos(l tbar)*cos(lbar t)
      out=TMath::Cos((vec_lepton_.Vect()).Angle(vec_antitop_.Vect()))*TMath::Cos((vec_antilepton_.Vect()).Angle(vec_top_.Vect()));
      break;
    case 13:
      // inv. mass of ttbar system
      out=(vec_top_+vec_antitop_).M();
      break;
    case 14:
      out=TMath::Cos((vec_lepton_.Vect()).Angle(vec_antid_.Vect()));
      break;
    case 15:
      out=TMath::Cos((vec_antilepton_.Vect()).Angle(vec_d_.Vect()));
      break; 
    case 16:
      out=vec_top_.M();
      break; 
    case 17:
      out=vec_antitop_.M();
      break;
    case 18:
      out=vec_b_.M();
      break;
    case 19:
      out=vec_antib_.M();
      break;
    case 20:
      out=vec_lepton_.M();
      break;
    case 21:
      out=vec_antilepton_.M();
      break;
    case 22:
      out=TMath::Abs(vec_lepton_.Eta()-vec_b_.Eta());
      break;
    case 23:
      out=TMath::Abs(vec_antilepton_.Eta()-vec_antib_.Eta());
      break;
    case 24:
      out=((vec_b_.Vect()).Cross(vec_antib_.Vect())).Dot(vec_lepton_.Vect())/10000.;
      break;
    case 25:
      out=((vec_b_.Vect()).Cross(vec_antib_.Vect())).Dot(vec_antilepton_.Vect())/10000.;
      break;
    case 26:
      out=TMath::Cos((vec_d_.Vect()).Angle(vec_antid_.Vect()));
      break;
    default:
      cerr << "no identifier for used variable" << endl;
  }
  return out;
}

Interpretation* SpinCorrelationProcessor::GetBestLR(int& njets,int& ntags,std::vector<TLorentzVector>& jetvecs,std::vector<float>& jetcsvs,TLorentzVector& lepvec,TVector2& metvec, bool& flag,float& best_lr) {
  bool use_chi2=true;
  if(flag) {
    if(ntags<4) {
      if(njets>5) {
	generator.SetVars(IntType::tth,10);
      }
      else {
	generator.SetVars(IntType::tt,8);
      }
    }
    else {
	generator.SetVars(IntType::tth,10);
    }
  }
  else {
    if(ntags<4) {
      if(njets>5) {
	generator.SetVars(IntType::tt,8);
      }
      else {
	generator.SetVars(IntType::tth,10);
      }
    }
    else {
	generator.SetVars(IntType::tt,8);
    }
  }
  Interpretation** ints = generator.GenerateTTHInterpretations(jetvecs,jetcsvs,lepvec,metvec);
  uint nints = generator.GetNints();
  Interpretation* best_int_lr=0;
  //float best_lr=-99999.;
  //    float best_chi2=-99999;
  for(uint i=0; i<nints; i++){
    // likelihood ratio good ttbar reco / combinatorial background
    float lr=0.;
    /*
    if(njets>5 && ntags>2) {
      lr=quality.TTHLikelihood_comb(*(ints[i]));
    }
    else {
      lr=quality.TTLikelihood_comb(*(ints[i]));
    }
    */
    if(flag){
      if(ntags<4) {
	if(njets>5) {
	  if(!use_chi2){
	    lr=quality.TTHLikelihood_comb(*(ints[i]));
	  }
	  else if(use_chi2) {
	    lr=quality.TTHChi2(*(ints[i]));
	  }
	}
	else {
	  if(!use_chi2){
	    lr=quality.TTLikelihood_comb(*(ints[i]));
	  }
	  else if(use_chi2) {
	    lr=quality.TTChi2(*(ints[i]));
	  }
	}
      }
      else {
	if(!use_chi2){
	  lr=quality.TTHLikelihood_comb(*(ints[i]));
	}
	else if(use_chi2) {
	  lr=quality.TTHChi2(*(ints[i]));
	}
      }
    }
    else {
      if(ntags<4) {
	if(njets>5) {
	  if(!use_chi2){
	    lr=quality.TTLikelihood_comb(*(ints[i]));
	  }
	  else if(use_chi2) {
	    lr=quality.TTChi2(*(ints[i]));
	  }
	}
	else {
	  if(!use_chi2){
	    lr=quality.TTHLikelihood_comb(*(ints[i]));
	  }
	  else if(use_chi2) {
	    lr=quality.TTHChi2(*(ints[i]));
	  }
	}
      }
      else {
	if(!use_chi2){
	  lr=quality.TTLikelihood_comb(*(ints[i]));
	}
	else if(use_chi2) {
	  lr=quality.TTChi2(*(ints[i]));
	}
      }
    }
    // simple chi2 reconstruction using hadronic W and both top masses
    /*	
    float chi2=quality.TTChi2(*(ints[i]));
    if(chi2>best_chi2){
	best_chi2=chi2;
	best_int_chi2=ints[i];
	}
    */
    if(lr>best_lr){
	best_lr=lr;
	best_int_lr=ints[i];
    }
  }
  return best_int_lr;
}

reco::GenParticle SpinCorrelationProcessor::MatchPartontoJet (vector<reco::GenParticle>& Partons,pat::Jet& Jet){
    float DeltaRtmp;
    float DeltaRMin = 9999999;
    float DeltaRCut = 0.4;
    reco::GenParticle matchedParton;

    for( auto& Parton: Partons ){
        DeltaRtmp = BoostedUtils::DeltaR(Jet.p4(),Parton.p4());
        if(DeltaRtmp < DeltaRCut && DeltaRtmp < DeltaRMin){
            matchedParton = Parton;
            DeltaRMin = DeltaRtmp;
        }
    }

    return matchedParton;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

SpinCorrelationProcessor::SpinCorrelationProcessor ():generator(InterpretationGenerator(IntType::tt,0,8,-9999,9999,0.8)){}
SpinCorrelationProcessor::~SpinCorrelationProcessor (){}

void SpinCorrelationProcessor::Init(const InputCollections& input,VariableContainer& vars){
  
  //cout << "Spin Correlaton Processor initialized" << endl;
  std::vector<TString> frames;
  std::vector<TString> variables;
  std::vector<TString> var_type;
  
  frames.push_back("lab");
  frames.push_back("ttbar_cm");
  //frames.push_back("top_rest");
  //frames.push_back("antitop_rest");
  frames.push_back("special");
  
  variables.push_back("cos_theta_ll");
  variables.push_back("cos_theta_bb");
  variables.push_back("cos_theta_l");
  variables.push_back("cos_theta_lbar");
  variables.push_back("cos_theta_lb");
  variables.push_back("cos_theta_lbarbbar");
  variables.push_back("Delta_Phi_lb");
  variables.push_back("Delta_Phi_lbarbbar");
  variables.push_back("Delta_Phi_ll");
  variables.push_back("Delta_Phi_bb");
  variables.push_back("Delta_Eta_ll");
  variables.push_back("Delta_Eta_bb");
  variables.push_back("Delta_Eta_lb");
  variables.push_back("Delta_Eta_lbarbbar");
  variables.push_back("cos_theta_l_x_cos_theta_lbar");
  //variables.push_back("M_ttbar");
  variables.push_back("cos_theta_ldbar");
  variables.push_back("cos_theta_lbard");
  variables.push_back("cos_theta_dd");
  /*
  variables.push_back("M_l");
  variables.push_back("M_lbar");
  variables.push_back("M_t");
  variables.push_back("M_tbar");
  variables.push_back("M_b");
  variables.push_back("M_bbar");
  */
  variables.push_back("triple_product_l");
  variables.push_back("triple_product_lbar");
  
  var_type.push_back("GEN");
  var_type.push_back("RECO");
  var_type.push_back("HALFRECO");
  
  for(auto it_frames=frames.begin();it_frames!=frames.end();++it_frames) {
    for(auto it_variables=variables.begin();it_variables!=variables.end();++it_variables) {
      for(auto it_type=var_type.begin();it_type!=var_type.end();++it_type) {
	vars.InitVar((*it_type)+"__"+(*it_frames)+"__"+(*it_variables),-9.,"F");
      }
      //cout << (*it_frames)+"|"+(*it_variables) << " initialized " << endl;
    }
  }
  
  vars.InitVar("RECO_flag_before_match",0,"I");
  vars.InitVar("RECO_flag_after_match",0,"I");
  /*
  vars.InitVar("RECO_switch_flag_after_match_1",0,"I");
  vars.InitVar("RECO_switch_flag_after_match_2",0,"I");
  vars.InitVar("RECO_bb_flag_after_match",0,"I");
  vars.InitVar("RECO_tt_flag_after_match",0,"I");
  vars.InitVar("RECO_bb_switch_flag_after_match",0,"I");
  vars.InitVar("RECO_tt_switch_flag_after_match",0,"I");
  vars.InitVar("RECO_t_flag_after_match",0,"I");
  vars.InitVar("RECO_t_switch_flag_after_match",0,"I");
  vars.InitVar("RECO_antit_flag_after_match",0,"I");
  vars.InitVar("RECO_antit_switch_flag_after_match",0,"I");
  vars.InitVar("RECO_b_flag_after_match",0,"I");
  vars.InitVar("RECO_b_switch_flag_after_match",0,"I");
  vars.InitVar("RECO_antib_flag_after_match",0,"I");
  vars.InitVar("RECO_antib_switch_flag_after_match",0,"I");
  */
  vars.InitVar("GenTopEvt_filled",0,"I");
  vars.InitVar("RECO_likelihood",-9.,"F");
  
  initialized=true;
  
}


void SpinCorrelationProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  //cout << "Spin Correlation Processor process started " << endl;
  
  std::map<TString,int> frames;// map which contains the frames which are used and some number for later identification  
  std::vector<TString> var_type;// just string vector which contains GEN and RECO to use it in loop 
  
  // frames which are used
  frames["lab"]=0;
  frames["ttbar_cm"]=1;
  //frames["top_rest"]=2;
  //frames["antitop_rest"]=3;
  frames["special"]=4;
  
  // variable type GEN or RECO
  var_type.push_back("GEN");
  var_type.push_back("RECO");
  var_type.push_back("HALFRECO");
  

  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // decalre Vectors, which are present in every ttbar event
  math::XYZTLorentzVector vec_zero(0.,0.,0.,0.);
  math::XYZTLorentzVector vec_top=vec_zero;
  math::XYZTLorentzVector vec_antitop=vec_zero;
  math::XYZTLorentzVector vec_b=vec_zero;
  math::XYZTLorentzVector vec_antib=vec_zero;
  math::XYZTLorentzVector vec_lepton=vec_zero;
  math::XYZTLorentzVector vec_antilepton=vec_zero;
  math::XYZTLorentzVector vec_d=vec_zero;
  math::XYZTLorentzVector vec_antid=vec_zero;
  // and some temp vectors for later
  math::XYZTLorentzVector vec_top_tmp=vec_zero;
  math::XYZTLorentzVector vec_antitop_tmp=vec_zero;
  math::XYZTLorentzVector vec_b_tmp=vec_zero;
  math::XYZTLorentzVector vec_antib_tmp=vec_zero;
  
  bool no_tau_selection=false;
  bool gen_evt_filled=input.genTopEvt.IsFilled();
  
  // loop begins over var_type
  for(auto it_type=var_type.begin();it_type!=var_type.end();++it_type) {
    
    //cout << "GEN or RECO? " << *it_type << endl;
    
    TString dec_type=*it_type;
    
    std::map<TString,int> variables;// map which later contains the variables which are used in the event and some number for later identification
    
    // some flags which help later
    bool isDL=false;
    bool isSL=false;
    bool isAH=false;
    int leptonflag=0;// flag for lepton=1, for antilepton=-1
    bool dilepton_reco_flag=false;// flag to signalize that for this event at least the dilepton variables in the lab frame could be used, which is of course possible even without top-event reconstruction
    
    //cout << "Gen Top Event is filled? " << gen_evt_filled << endl;
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // if top evt is filled and the loop is at var_type GEN, then the reconstruction for GEN variables can begin
    if(gen_evt_filled && dec_type.EqualTo("GEN")){
      //cout << "GenTopEvt is filled and decay type GEN " << endl;
      std::vector<reco::GenParticle> tophad;
      std::vector<reco::GenParticle> bhad;
      std::vector<reco::GenParticle> toplep;
      std::vector<reco::GenParticle> blep;
      std::vector<reco::GenParticle> lep;
      std::vector<reco::GenParticle> q1;
      std::vector<reco::GenParticle> q2;
      tophad=input.genTopEvt.GetAllTopHads();
      bhad=input.genTopEvt.GetAllTopHadDecayQuarks();
      toplep=input.genTopEvt.GetAllTopLeps();
      blep=input.genTopEvt.GetAllTopLepDecayQuarks();
      lep=input.genTopEvt.GetAllLeptons();
      q1=input.genTopEvt.GetAllWQuarks();
      q2=input.genTopEvt.GetAllWAntiQuarks();
      //additional_bs=input.genTopEvt.GetAdditionalBGenJets();
    
      // identify the kind of decay
      if(input.genTopEvt.IsDiLepton()) {
	isDL=true;
	isSL=false;
	isAH=false;
	//cout << "Dilepton Event! " << endl;
      }
      else if(input.genTopEvt.IsSemiLepton()) {
	isSL=true;
	isDL=false;
	isAH=false;
	//cout << "Single Lepton Event! " << endl;
      }
      else if(input.genTopEvt.IsAllHadron()) {
	isSL=false;
	isDL=false;
	isAH=true;
	//cout << "------------------------------" << endl;
	//cout << "Fully hadronic Event! " << endl;
	//cout << "------------------------------" << endl;
      }
      else {
	//cout << "strange event ... " << endl;
	continue;
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
	  if(lep[0].pdgId()==15 && no_tau_selection) {continue;}
	  vec_lepton=lep[0].p4();
	  vec_antilepton=vec_zero;
	  vec_antid=q2[0].p4();
	  vec_d=vec_zero;
	  leptonflag=1;
	  //cout << "Lepton! " << endl;
	}
	else if(lep[0].pdgId()<0) {
	  if(lep[0].pdgId()==-15 && no_tau_selection) {continue;}
	  vec_antilepton=lep[0].p4();
	  vec_lepton=vec_zero;
	  vec_d=q1[0].p4();
	  vec_antid=vec_zero;
	  leptonflag=-1;
	  //cout << "Antilepton! " << endl;
	}   
      }
      // in DL case, the assignment is straight forward. pdgid>0 are leptons, pdgid<0 are antileptons
      else if(isDL) {
	if(lep[0].pdgId()>0) {
	  if(lep[0].pdgId()==15 && no_tau_selection) {continue;}
	  vec_lepton=lep[0].p4();
	}
	else if(lep[0].pdgId()<0) {
  	  if(lep[0].pdgId()==-15 && no_tau_selection) {continue;}
	  vec_antilepton=lep[0].p4();
	}
	if(lep[1].pdgId()>0) {
 	  if(lep[1].pdgId()==15 && no_tau_selection) {continue;}
	  vec_lepton=lep[1].p4();
	}
	else if(lep[1].pdgId()<0) {
	  if(lep[1].pdgId()==-15 && no_tau_selection) {continue;}
	  vec_antilepton=lep[1].p4();
	}
      }
      else if(isAH) {
	for(auto it=q1.begin();it!=q1.end();++it) {
	  if(abs(it->pdgId())==1 || abs(it->pdgId())==3 || abs(it->pdgId())==5) { vec_d=it->p4(); }
	}
	for(auto it=q2.begin();it!=q2.end();++it) {
	  if(abs(it->pdgId())==1 || abs(it->pdgId())==3 || abs(it->pdgId())==5) { vec_antid=it->p4(); }
	}
      }
      // now save the top/antitop, b/antib vectors for later comparison with the RECO vectors
      vec_top_tmp=vec_top;
      vec_antitop_tmp=vec_antitop;
      vec_b_tmp=vec_b;
      vec_antib_tmp=vec_antib;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // if the loop is in var_type RECO and the events satisfies the requirements, the recontruction of the RECO variables can begin
    else if(input.selectedJets.size()>=4 && dec_type.EqualTo("RECO") && (input.selectedElectrons.size()+input.selectedMuons.size())==1 && !((input.selectedElectronsLoose.size()+input.selectedMuonsLoose.size())==2)){
      //cout << "N_jets>=4 and decay type RECO and Electrons+Muons==1" << endl;
      // this is the code of Hannes ttbar reconstruction processor to create some likelihood/chi2 interpretations of the event
      std::vector<TLorentzVector> jetvecs = BoostedUtils::GetTLorentzVectors(BoostedUtils::GetJetVecs(input.selectedJets));
      std::vector<float> jetcsvs;
      int ntags=0;
      int njets=input.selectedJets.size();
      for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++){
	jetcsvs.push_back(MiniAODHelper::GetJetCSV(*j));
	if(BoostedUtils::PassesCSV(*j)) ntags++;
      }
      TLorentzVector lepvec = BoostedUtils::GetTLorentzVector(BoostedUtils::GetPrimLepVec(input.selectedElectrons,input.selectedMuons));
      TVector2 metvec(input.correctedMET.px(),input.correctedMET.py());
      float best_lr=-9999.;
      bool flag=true;
      Interpretation* best_int_lr=GetBestLR(njets,ntags,jetvecs,jetcsvs,lepvec,metvec,flag,best_lr);
      if(!(best_lr>-9998.)){
	best_lr=-9999.;
	flag=false;
	best_int_lr=GetBestLR(njets,ntags,jetvecs,jetcsvs,lepvec,metvec,flag,best_lr);
      }
      //cout << " chi 2 " << best_lr << endl;
      /*
      if(ntags<4) {
	if(njets>5) {
	  generator.SetVars(IntType::tth,10);
	}
	else {
	  generator.SetVars(IntType::tt,8);
	}
      }
      else {
	  generator.SetVars(IntType::tth,10);
      }
      Interpretation** ints = generator.GenerateTTHInterpretations(jetvecs,jetcsvs,lepvec,metvec);
      uint nints = generator.GetNints();
      Interpretation* best_int_lr=0;
      float best_lr=-99999.;
      //    float best_chi2=-99999;
      for(uint i=0; i<nints; i++){
	  // likelihood ratio good ttbar reco / combinatorial background
	  float lr=0.;
	 
	  if(ntags<4) {
	    if(njets>5) {
	      lr=quality.TTHLikelihood_comb(*(ints[i]));
	    }
	    else {
	      lr=quality.TTLikelihood_comb(*(ints[i]));
	    }
	  }
	  else {
	    lr=quality.TTHLikelihood_comb(*(ints[i]));
	  }
	  if(lr>best_lr){
	      best_lr=lr;
	      best_int_lr=ints[i];
	  }
      }
      */
      if(best_lr>-9998.) {
	//cout << "Hypothese with LR>0 available" << endl;
	vars.FillVar("RECO_likelihood",best_lr);
	isSL=true;
	isDL=false;
        isAH=false;
	// the likelihood ratio of the interpretation isnt allowed to be 0
	// now check if the SL event has an electron- or muon-lepton and whether it is a lepton or antilepton
	if(input.selectedElectrons.size()==1){
	  leptonflag=-input.selectedElectrons[0].charge();
	  if(leptonflag>0) {
	    //cout << "Electron! " << endl;
	    vec_lepton.SetPxPyPzE(input.selectedElectrons[0].px(),input.selectedElectrons[0].py(),input.selectedElectrons[0].pz(),input.selectedElectrons[0].energy());
	    vec_antilepton=vec_zero;
	  }
	  else if(leptonflag<0) {
	    //cout << "Positron! " << endl;
	    vec_antilepton.SetPxPyPzE(input.selectedElectrons[0].px(),input.selectedElectrons[0].py(),input.selectedElectrons[0].pz(),input.selectedElectrons[0].energy());
	    vec_lepton=vec_zero;
	  }
	}
	else if(input.selectedMuons.size()==1) {
	  leptonflag=-input.selectedMuons[0].charge();
	  if(leptonflag>0) {
	    //cout << "Muon! " << endl;
	    vec_lepton.SetPxPyPzE(input.selectedMuons[0].px(),input.selectedMuons[0].py(),input.selectedMuons[0].pz(),input.selectedMuons[0].energy());
	    vec_antilepton=vec_zero;
	  }
	  else if(leptonflag<0) {
	    //cout << "AntiMuon! " << endl;
	    vec_antilepton.SetPxPyPzE(input.selectedMuons[0].px(),input.selectedMuons[0].py(),input.selectedMuons[0].pz(),input.selectedMuons[0].energy());
	    vec_lepton=vec_zero;
	  }
	}
	else {continue;}
	// depending on the outcome of the SL event classification, the corresponding 4-vectors are set
	if(leptonflag>0) {
	  vec_antitop.SetPxPyPzE(best_int_lr->TopLep().Px(),best_int_lr->TopLep().Py(),best_int_lr->TopLep().Pz(),best_int_lr->TopLep().E());
	  vec_top.SetPxPyPzE(best_int_lr->TopHad().Px(),best_int_lr->TopHad().Py(),best_int_lr->TopHad().Pz(),best_int_lr->TopHad().E());
	  vec_antib.SetPxPyPzE(best_int_lr->BLep().Px(),best_int_lr->BLep().Py(),best_int_lr->BLep().Pz(),best_int_lr->BLep().E());
	  vec_b.SetPxPyPzE(best_int_lr->BHad().Px(),best_int_lr->BHad().Py(),best_int_lr->BHad().Pz(),best_int_lr->BHad().E()); 
	}
	else if(leptonflag<0) {
	  vec_antitop.SetPxPyPzE(best_int_lr->TopHad().Px(),best_int_lr->TopHad().Py(),best_int_lr->TopHad().Pz(),best_int_lr->TopHad().E());
	  vec_top.SetPxPyPzE(best_int_lr->TopLep().Px(),best_int_lr->TopLep().Py(),best_int_lr->TopLep().Pz(),best_int_lr->TopLep().E());
	  vec_antib.SetPxPyPzE(best_int_lr->BHad().Px(),best_int_lr->BHad().Py(),best_int_lr->BHad().Pz(),best_int_lr->BHad().E());
	  vec_b.SetPxPyPzE(best_int_lr->BLep().Px(),best_int_lr->BLep().Py(),best_int_lr->BLep().Pz(),best_int_lr->BLep().E()); 
	}
	else {continue;}
	
	vars.FillVar("RECO_flag_before_match",1);
	
	// now do a Delta R Matching of the reconstructed 4-vectors with the saved GEN vectors
	float dR_max=0.4;
	float dR_top=dR_max+1.;
	float dR_antitop=dR_max+1.;
	float dR_b=dR_max+1.;
	float dR_antib=dR_max+1.;
	//float dR_top_switch=dR_max+1.;
	//float dR_antitop_switch=dR_max+1.;
	//float dR_b_switch=dR_max+1.;
	//float dR_antib_switch=dR_max+1.;
	if(gen_evt_filled){
	  vars.FillVar("GenTopEvt_filled",1);
	  //cout << "Gen Top Event is filled " << endl;
	  dR_top=BoostedUtils::DeltaR(vec_top,vec_top_tmp);
	  dR_antitop=BoostedUtils::DeltaR(vec_antitop,vec_antitop_tmp);
	  dR_b=BoostedUtils::DeltaR(vec_b,vec_b_tmp);
	  dR_antib=BoostedUtils::DeltaR(vec_antib,vec_antib_tmp);
	  //dR_top_switch=BoostedUtils::DeltaR(vec_top,vec_antitop_tmp);
	  //dR_antitop_switch=BoostedUtils::DeltaR(vec_antitop,vec_top_tmp);
	  //dR_b_switch=BoostedUtils::DeltaR(vec_b,vec_antib_tmp);
	  //dR_antib_switch=BoostedUtils::DeltaR(vec_antib,vec_b_tmp);
	}
	/*
	// set some flags which are of interest for the reconstruction -> maybe some dedicated processor would be better for this
	if(dR_top<dR_max) {
	  vars.FillVar("RECO_t_flag_after_match",1);
	}
	if(dR_antitop<dR_max) {
	  vars.FillVar("RECO_antit_flag_after_match",1);
	}
	if(dR_b<dR_max) {
	  vars.FillVar("RECO_b_flag_after_match",1);
	}
	if(dR_antib<dR_max) {
	  vars.FillVar("RECO_antib_flag_after_match",1);
	}
	if(dR_top_switch<dR_max) {
	  vars.FillVar("RECO_t_switch_flag_after_match",1);
	}
	if(dR_antitop_switch<dR_max) {
	  vars.FillVar("RECO_antit_switch_flag_after_match",1);
	}
	if(dR_b_switch<dR_max) {
	  vars.FillVar("RECO_b_switch_flag_after_match",1);
	}
	if(dR_antib_switch<dR_max) {
	  vars.FillVar("RECO_antib_switch_flag_after_match",1);
	}
	if(dR_top<dR_max && dR_antitop<dR_max) {
	  vars.FillVar("RECO_tt_flag_after_match",1);
	}
	else if(dR_top_switch<dR_max && dR_antitop_switch<dR_max) {
	  vars.FillVar("RECO_tt_switch_flag_after_match",1);
	}
	if(dR_b<dR_max && dR_antib<dR_max) {
	  vars.FillVar("RECO_bb_flag_after_match",1);
	}
	else if(dR_b_switch<dR_max && dR_antib_switch<dR_max) {
	  vars.FillVar("RECO_bb_switch_flag_after_match",1);
	}
	*/
	if(dR_top<dR_max && dR_antitop<dR_max && dR_b<dR_max && dR_antib<dR_max) {
	  //cout << "every particle is matched correctly" << endl;
	  vars.FillVar("RECO_flag_after_match",1);
	}
	/*
	else if(dR_top<dR_max && dR_antitop<dR_max && dR_b_switch<dR_max && dR_antib_switch<dR_max) {
	  vars.FillVar("RECO_switch_flag_after_match_1",1);
	}
	else if(dR_top_switch<dR_max && dR_antitop_switch<dR_max && dR_b_switch<dR_max && dR_antib_switch<dR_max) {
	  vars.FillVar("RECO_switch_flag_after_match_2",1);
	}*/	
      }
      // if the interpretation is 0 the loop for reco ends here
      else {
	//cout << "Interpretation = 0, abort!! " << endl;
	continue;
      }
      
    }
    
    else if(input.selectedJetsDL.size()>=2 && dec_type.EqualTo("RECO") && ((input.selectedElectronsLoose.size()+input.selectedMuonsLoose.size())==2) && !((input.selectedElectrons.size()+input.selectedMuons.size())==1)) {
      isSL=false;
      isDL=true;
      isAH=false;
      //cout << "DiLepton Reconstruction ! " << endl;
      dilepton_reco_flag=true;
      //now check if there are 2 electrons or 2 muons or one of both and assign the correct 4 vectors
      if(input.selectedElectronsLoose.size()==2) {
	if(input.selectedElectronsLoose[0].charge()<0) {
	  vec_lepton.SetPxPyPzE(input.selectedElectronsLoose[0].px(),input.selectedElectronsLoose[0].py(),input.selectedElectronsLoose[0].pz(),input.selectedElectronsLoose[0].energy());
	}
	else if(input.selectedElectronsLoose[0].charge()>0) {
	  vec_antilepton.SetPxPyPzE(input.selectedElectronsLoose[0].px(),input.selectedElectronsLoose[0].py(),input.selectedElectronsLoose[0].pz(),input.selectedElectronsLoose[0].energy());
	}
	if(input.selectedElectronsLoose[1].charge()<0) {
	  vec_lepton.SetPxPyPzE(input.selectedElectronsLoose[1].px(),input.selectedElectronsLoose[1].py(),input.selectedElectronsLoose[1].pz(),input.selectedElectronsLoose[1].energy());
	}
	else if(input.selectedElectronsLoose[1].charge()>0) {
	  vec_antilepton.SetPxPyPzE(input.selectedElectronsLoose[1].px(),input.selectedElectronsLoose[1].py(),input.selectedElectronsLoose[1].pz(),input.selectedElectronsLoose[1].energy());
	}
      }
      else if(input.selectedMuonsLoose.size()==2) {
	if(input.selectedMuonsLoose[0].charge()<0) {
	  vec_lepton.SetPxPyPzE(input.selectedMuonsLoose[0].px(),input.selectedMuonsLoose[0].py(),input.selectedMuonsLoose[0].pz(),input.selectedMuonsLoose[0].energy());
	}
	else if(input.selectedMuonsLoose[0].charge()>0) {
	  vec_antilepton.SetPxPyPzE(input.selectedMuonsLoose[0].px(),input.selectedMuonsLoose[0].py(),input.selectedMuonsLoose[0].pz(),input.selectedMuonsLoose[0].energy());
	}
	if(input.selectedMuonsLoose[1].charge()<0) {
	  vec_lepton.SetPxPyPzE(input.selectedMuonsLoose[1].px(),input.selectedMuonsLoose[1].py(),input.selectedMuonsLoose[1].pz(),input.selectedMuonsLoose[1].energy());
	}
	else if(input.selectedMuonsLoose[1].charge()>0) {
	  vec_antilepton.SetPxPyPzE(input.selectedMuonsLoose[1].px(),input.selectedMuonsLoose[1].py(),input.selectedMuonsLoose[1].pz(),input.selectedMuonsLoose[1].energy());
	}
      }
      else {
	if(input.selectedElectronsLoose[0].charge()<0) {
	  vec_lepton.SetPxPyPzE(input.selectedElectronsLoose[0].px(),input.selectedElectronsLoose[0].py(),input.selectedElectronsLoose[0].pz(),input.selectedElectronsLoose[0].energy());
	}
	else if(input.selectedElectronsLoose[0].charge()>0) {
	  vec_antilepton.SetPxPyPzE(input.selectedElectronsLoose[0].px(),input.selectedElectronsLoose[0].py(),input.selectedElectronsLoose[0].pz(),input.selectedElectronsLoose[0].energy());
	}
	if(input.selectedMuonsLoose[0].charge()<0) {
	  vec_lepton.SetPxPyPzE(input.selectedMuonsLoose[0].px(),input.selectedMuonsLoose[0].py(),input.selectedMuonsLoose[0].pz(),input.selectedMuonsLoose[0].energy());
	}
	else if(input.selectedMuonsLoose[0].charge()>0) {
	  vec_antilepton.SetPxPyPzE(input.selectedMuonsLoose[0].px(),input.selectedMuonsLoose[0].py(),input.selectedMuonsLoose[0].pz(),input.selectedMuonsLoose[0].energy());
	}
      }
    }
    
    else if(gen_evt_filled && dec_type.EqualTo("HALFRECO")){
      if(input.genTopEvt.IsSemiLepton()){
	//cout << "event is not semileptonic on gen level " << endl;
	isSL=true;
	isDL=false;
        isAH=false;
      }
      else if(input.genTopEvt.IsDiLepton()) {
	isSL=false;
	isDL=true;
        isAH=false;
      }
      else {continue;}
      //cout << "gen event is semileptonic " << endl;
      
      // some gen info used, because only the effect of wrong permutations shall be examined
      std::vector<reco::GenParticle> nu;
      std::vector<reco::GenParticle> lep;
      nu=input.genTopEvt.GetAllNeutrinos();
      lep=input.genTopEvt.GetAllLeptons();
      math::XYZTLorentzVector vec_nu;
      math::XYZTLorentzVector vec_antinu;
      /////////////// Quark Jet Matching ////////////////
      vector< vector< reco::GenParticle > > DecayProducts;
      
      
      DecayProducts.push_back( input.genTopEvt.GetWQuarks() ); 
      //cout << "getWquarks vector size = " << DecayProducts[0].size() << endl;
      DecayProducts.push_back( input.genTopEvt.GetAllTopLepDecayQuarks() );
      DecayProducts.push_back( input.genTopEvt.GetAllTopHadDecayQuarks() );
      //cout << "decay products vector size = " << DecayProducts.size() << endl;
      vector < pat::Jet >  Jets = input.selectedJets;
     
      vector< pat::Jet > hadtopjets;
      vector< pat::Jet > leptopjets;
      vector< pat::Jet > hadWjets;
      vector< int > pdgids;
      int nwhadjets = 0;
      int nleptopjets =0;
      int nhadtopjets =0;
      //int iJet = 0;
      //cout << "trying to match the jets to the gen quarks " << endl;
      for( auto& Jet: Jets ){
        reco::GenParticle MatchedParton;	
        vector< reco::GenParticle > MatchingQuarks;
        for(auto& Quarks: DecayProducts){

            MatchingQuarks.push_back( MatchPartontoJet(Quarks,Jet) );

	}
	size_t iQ = 0;
        int decayfrom = -1;
        float DeltaRtmp = 999;
        for( auto& Quark: MatchingQuarks ){

            if (Quark.pdgId() != 0){
                if ( BoostedUtils::DeltaR( Jet.p4() , Quark.p4() ) < DeltaRtmp ){
                    DeltaRtmp = BoostedUtils::DeltaR( Jet.p4() , Quark.p4() );
                    MatchedParton = Quark;
                    decayfrom = iQ;
                }
            }
            iQ++;
	}

	if( decayfrom == 0){
	  //cout << "W jet found " << endl;
	  hadWjets.push_back(Jet);
	  nwhadjets+=1;
	}
	else if (decayfrom == 1){
	  //cout << "leptonic b jet found " << endl;
	  leptopjets.push_back(Jet);
	  nleptopjets+=1;
	  pdgids.push_back(MatchedParton.pdgId());
	}
	else if (decayfrom == 2){
	  //cout << "hadtronic b jet found " << endl;
	  hadtopjets.push_back(Jet);
	  nhadtopjets+=1;
	}
		    
      }
      //////////////////////////////////////////////////////
      //after gen quark jet matching use the gen info for the rest, leptons and neutrinos
      if(isSL) {
	if(!(nleptopjets==1 && nhadtopjets==1 && nwhadjets>=1)) {
	  //cout << "jets could not be assigned to quarks" << endl;
	  continue;
	}
	//cout << "SL matching was succesfull" << endl;
	if(lep[0].pdgId()>0) {
	  if(lep[0].pdgId()==15 && no_tau_selection) {continue;}
	  vec_lepton=lep[0].p4();
	  vec_antilepton=vec_zero;
	  leptonflag=1;
	}
	else if(lep[0].pdgId()<0) {
	  if(lep[0].pdgId()==-15 && no_tau_selection) {continue;}
	  vec_antilepton=lep[0].p4();
	  vec_lepton=vec_zero;
	  leptonflag=-1;
	  //cout << "Antilepton! " << endl;
	} 
	if(leptonflag==1) {
          if(nwhadjets>1) {  
            vec_top=hadtopjets[0].p4()+hadWjets[0].p4()+hadWjets[1].p4();
          }
          else if(nwhadjets==1) {
            vec_top=hadtopjets[0].p4()+hadWjets[0].p4();
          }
	  vec_antitop=leptopjets[0].p4()+vec_lepton+nu[0].p4();
	  vec_b=hadtopjets[0].p4();
	  vec_antib=leptopjets[0].p4();
	}
	else if(leptonflag==-1) {
          if(nwhadjets>1) {  
            vec_antitop=hadtopjets[0].p4()+hadWjets[0].p4()+hadWjets[1].p4();
          }
          else if(nwhadjets==1) {
            vec_antitop=hadtopjets[0].p4()+hadWjets[0].p4();
          }
	  vec_top=leptopjets[0].p4()+vec_antilepton+nu[0].p4();
	  vec_antib=hadtopjets[0].p4();
	  vec_b=leptopjets[0].p4();
	}
      }
      else if(isDL) {
	if(!(nleptopjets==2 && nhadtopjets==0 && nwhadjets==0)) {
	  continue;
	}
	//cout << "DL matching was succesfull" << endl;
	if(lep[0].pdgId()>0) {
	  if(lep[0].pdgId()==15 && no_tau_selection) {continue;}
	  vec_lepton=lep[0].p4();
	}
	else if(lep[0].pdgId()<0) {
  	  if(lep[0].pdgId()==-15 && no_tau_selection) {continue;}
	  vec_antilepton=lep[0].p4();
	}
	if(lep[1].pdgId()>0) {
 	  if(lep[1].pdgId()==15 && no_tau_selection) {continue;}
	  vec_lepton=lep[1].p4();
	}
	else if(lep[1].pdgId()<0) {
	  if(lep[1].pdgId()==-15 && no_tau_selection) {continue;}
	  vec_antilepton=lep[1].p4();
	}
	if(nu[0].pdgId()>0) {
	  vec_nu=nu[0].p4();
	}
	else if(nu[0].pdgId()<0) {
	  vec_antinu=nu[0].p4();
	}
	if(nu[1].pdgId()>0) {
	  vec_nu=nu[1].p4();
	}
	else if(nu[1].pdgId()<0) {
	  vec_antinu=nu[1].p4();
	}
	if(pdgids[0]>0) {
	  vec_b=leptopjets[0].p4();
	}
	else if(pdgids[0]<0) {
	  vec_antib=leptopjets[0].p4();
	}
	if(pdgids[1]>0) {
	  vec_b=leptopjets[1].p4();
	}
	else if(pdgids[1]<0) {
	  vec_antib=leptopjets[1].p4();
	}
	vec_top=vec_b+vec_antilepton+vec_nu;
	vec_antitop=vec_antib+vec_lepton+vec_antinu;
      }
      else {continue;}
	
    }
    
    // if neither GEN nor RECO part worked the loop ends here
    else {
      //cout << *it_type << " nothing could be done in this round of the loop!! " << endl;
      continue;
    }
    
    // now with the reconstructed 4-vectors the calculation of the variables starts
    for(auto it_frames=frames.begin();it_frames!=frames.end();++it_frames) {
      TLorentzVector vec_lepton_=BoostedUtils::GetTLorentzVector(vec_lepton);
      TLorentzVector vec_antilepton_=BoostedUtils::GetTLorentzVector(vec_antilepton);
      TLorentzVector vec_top_=BoostedUtils::GetTLorentzVector(vec_top);
      TLorentzVector vec_antitop_=BoostedUtils::GetTLorentzVector(vec_antitop);
      TLorentzVector vec_b_=BoostedUtils::GetTLorentzVector(vec_b);
      TLorentzVector vec_antib_=BoostedUtils::GetTLorentzVector(vec_antib);
      TLorentzVector vec_d_=BoostedUtils::GetTLorentzVector(vec_d);
      TLorentzVector vec_antid_=BoostedUtils::GetTLorentzVector(vec_antid);
      /*
      cout << dec_type << endl;
      cout << "Lepton Mass: " << vec_lepton.M() << endl;
      cout << "Antilepton Mass: " << vec_antilepton.M() << endl;
      cout << "frame: " << it_frames->first << " " << it_frames->second << endl;
      */
      
      // the SetAllVectors function uses the reconstructed 4-vectors and changes them according to the desired frame/boost using the number of the frame
      SetAllVectors(vec_top_,vec_antitop_,vec_b_,vec_antib_,vec_lepton_,vec_antilepton_,vec_d_,vec_antid_,it_frames->second);
      /*cout << "top m: " << vec_top_.M() << endl;
      cout << "antitop m: " << vec_antitop_.M() << endl;
      cout << "b m: " << vec_b_.M() << endl;
      cout << "antib m: " << vec_antib_.M() << endl;
      cout << "lepton m: " << vec_lepton_.M() << endl;
      cout << "antilepton m: " << vec_antilepton_.M() << endl;*/

      
      // if SL event: depending on lepton or antilepton, the variables which make sense are defined for the event
      if(isSL) {
	// first few variables which are present in SL channel
	variables["cos_theta_bb"]=0;
	variables["Delta_Eta_bb"]=1;
	variables["Delta_Phi_bb"]=2;
	/*
	variables["M_ttbar"]=13;
	variables["M_t"]=16;
	variables["M_tbar"]=17;
	variables["M_b"]=18;
	variables["M_bbar"]=19;
	*/
	// depend on lepton or antilepton the variables are filled
	if(leptonflag==1) {
	  variables["cos_theta_l"]=6;
	  variables["cos_theta_lb"]=8;
	  variables["Delta_Phi_lb"]=10;
	  variables["cos_theta_ldbar"]=14;
	  //variables["M_l"]=20;
	  variables["Delta_Eta_lb"]=22;
	  variables["triple_product_l"]=24;
	}
	else if(leptonflag==-1) {
	  variables["cos_theta_lbar"]=7;
	  variables["cos_theta_lbarbbar"]=9;
	  variables["Delta_Phi_lbarbbar"]=11;
	  variables["cos_theta_lbard"]=15;
	  //variables["M_lbar"]=21;
	  variables["Delta_Eta_lbarbbar"]=23;
	  variables["triple_product_lbar"]=25;
	}
      }
      // same for DL events
      else if(isDL) {
	// if DL flag is set, then these variables can be filled 
	variables["cos_theta_ll"]=3;
	variables["Delta_Phi_ll"]=4;
	variables["Delta_Eta_ll"]=5;
	//variables["M_l"]=20;
  	//variables["M_lbar"]=21;
	// these variables will only be filled if the dilepton reco flag isnt set, because they can only be filled if the whole event is reconstructed which cannot be done in DL case 
	if(!dilepton_reco_flag) {
	  variables["cos_theta_bb"]=0;
	  variables["Delta_Eta_bb"]=1;
	  variables["Delta_Phi_bb"]=2;
	  /*
	  variables["M_ttbar"]=13;
	  variables["M_t"]=16;
	  variables["M_tbar"]=17;
	  variables["M_b"]=18;
	  variables["M_bbar"]=19;
	  */
	  variables["cos_theta_l"]=6;
	  variables["cos_theta_lbar"]=7;
	  variables["cos_theta_lb"]=8;
	  variables["cos_theta_lbarbbar"]=9;
	  variables["Delta_Phi_lb"]=10;
	  variables["Delta_Phi_lbarbbar"]=11; 
	  variables["cos_theta_l_x_cos_theta_lbar"]=12;
	  variables["Delta_Eta_lb"]=22;
	  variables["Delta_Eta_lbarbbar"]=23;
	}
      }
      else if(isAH) {
	//cout << "all hadronic event recognized" << endl;
	variables["cos_theta_bb"]=0;
	variables["Delta_Eta_bb"]=1;
	variables["Delta_Phi_bb"]=2;
	variables["cos_theta_dd"]=26;
      }
      // now the GetVars function calculates the desired variable depending on the number of the variable using the 4-vectors of the event
      for(auto it_variables=variables.begin();it_variables!=variables.end();++it_variables) {
	  if(dilepton_reco_flag) {
	    if((it_frames->second)==0) {
	      vars.FillVar(*it_type+"__"+it_frames->first+"__"+it_variables->first,GetVars(vec_top_,vec_antitop_,vec_b_,vec_antib_,vec_lepton_,vec_antilepton_,vec_d_,vec_antid_,it_variables->second));
	    }
	  }
	  else {
	    vars.FillVar(*it_type+"__"+it_frames->first+"__"+it_variables->first,GetVars(vec_top_,vec_antitop_,vec_b_,vec_antib_,vec_lepton_,vec_antilepton_,vec_d_,vec_antid_,it_variables->second));
	    //cout << *it_type+"__"+it_frames->first+"__"+it_variables->first << " filled with " << GetVars(vec_top_,vec_antitop_,vec_b_,vec_antib_,vec_lepton_,vec_antilepton_,vec_d_,vec_antid_,it_variables->second) << endl;
	  }
      }
    }
  }
}
