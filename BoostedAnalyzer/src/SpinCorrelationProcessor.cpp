#include "BoostedTTH/BoostedAnalyzer/interface/SpinCorrelationProcessor.hpp"

// function to do some basic boosts on a TLorentzVectors using the number of the corresponding frame and the top/antitop 4-vectors
TLorentzVector Boost(TLorentzVector in_vec, Int_t frame_number, TLorentzVector vec_top_, TLorentzVector vec_antitop_){
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
void SetAllVectors(TLorentzVector& vec_top_, TLorentzVector& vec_antitop_, TLorentzVector& vec_b_, TLorentzVector& vec_antib_, TLorentzVector& vec_lepton_, TLorentzVector& vec_antilepton_,TLorentzVector& vec_d_,TLorentzVector& vec_antid_, int identifier){
  
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
      vec_top_=Boost(vec_top_tmp,identifier,vec_top_tmp,vec_antitop_tmp);
      vec_antitop_=Boost(vec_antitop_tmp,identifier,vec_top_tmp,vec_antitop_tmp);
      vec_b_=Boost(vec_b_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost b quark in corresponding system
      vec_antib_=Boost(vec_antib_tmp,identifier,vec_top_tmp,vec_antitop_tmp);//boost anti b quark in corresponding system
      vec_d_=Boost(vec_d_tmp,identifier,vec_top_tmp,vec_antitop_tmp);
      vec_antid_=Boost(vec_antid_tmp,identifier,vec_top_tmp,vec_antitop_tmp);
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
double GetVars(TLorentzVector vec_top_, TLorentzVector vec_antitop_, TLorentzVector vec_b_,TLorentzVector vec_antib_, TLorentzVector vec_lepton_,TLorentzVector vec_antilepton_,TLorentzVector vec_d_,TLorentzVector vec_antid_, Int_t var_number) {
  double out=-1;
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
    default:
      cerr << "no identifier for used variable" << endl;
  }
  return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

SpinCorrelationProcessor::SpinCorrelationProcessor ():generator(InterpretationGenerator(IntType::tt,0,8,-99999,99999,0.8)){}
SpinCorrelationProcessor::~SpinCorrelationProcessor (){}

void SpinCorrelationProcessor::Init(const InputCollections& input,VariableContainer& vars){
  
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
  variables.push_back("cos_theta_l_x_cos_theta_lbar");
  variables.push_back("M_ttbar");
  variables.push_back("cos_theta_ldbar");
  variables.push_back("cos_theta_lbard");
  variables.push_back("M_l");
  variables.push_back("M_lbar");
  variables.push_back("M_t");
  variables.push_back("M_tbar");
  variables.push_back("M_b");
  variables.push_back("M_bbar");
  
  var_type.push_back("GEN");
  var_type.push_back("RECO");
  
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
  
  initialized=true;
  
}


void SpinCorrelationProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
 
  std::map<TString,int> frames;// map which contains the frames which are used and some number for later identification
  std::map<TString,int> variables;// map which contains the variables which are used and some number for later nidentification
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
  
  // first few variables which are present in SL and DL channel
  variables["cos_theta_bb"]=0;
  variables["Delta_Eta_bb"]=1;
  variables["Delta_Phi_bb"]=2;
  variables["M_ttbar"]=13;
  variables["M_t"]=16;
  variables["M_tbar"]=17;
  variables["M_b"]=18;
  variables["M_bbar"]=19;
  
  

  // if top event isnt filled or n_jets<4 then there is nothing to do ...
  if(!(input.genTopEvt.IsFilled()) && !(input.selectedJets.size()>=4)) {
    cerr << "Top Event isnt filled and reconstruction not possible! " << endl;
    return;
  }
  
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  // decalre Vectors, which are present in every ttbar event
  math::XYZTLorentzVector vec_top;
  math::XYZTLorentzVector vec_antitop;
  math::XYZTLorentzVector vec_b;
  math::XYZTLorentzVector vec_antib;
  math::XYZTLorentzVector vec_lepton;
  math::XYZTLorentzVector vec_antilepton;
  math::XYZTLorentzVector vec_d;
  math::XYZTLorentzVector vec_antid;
  math::XYZTLorentzVector vec_zero(0.,0.,0.,0.);
  // and some temp vectors for later
  math::XYZTLorentzVector vec_top_tmp;
  math::XYZTLorentzVector vec_antitop_tmp;
  math::XYZTLorentzVector vec_b_tmp;
  math::XYZTLorentzVector vec_antib_tmp;
  
  // some flags which help later
  bool isDL=false;
  bool isSL=false;
  bool gen_evt_filled=false;
  int leptonflag=0;
  bool no_tau_selection=1;
  
  // loop begins over var_type
  for(auto it_type=var_type.begin();it_type!=var_type.end();++it_type) {
    //cout << "GEN or RECO? " << *it_type << endl;
    TString dec_type=*it_type;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // if top evt is filled and the loop is at var_type GEN, then the reconstruction for GEN variables can begin
    if(input.genTopEvt.IsFilled() && dec_type.EqualTo("GEN")){
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
      if(tophad.size()==0 and toplep.size()==2) {
	isDL=true;
	isSL=false;
	//cout << "Dilepton Event! " << endl;
      }
      else if(tophad.size()==1 and toplep.size()==1) {
	isSL=true;
	isDL=false;
	//cout << "Single Lepton Event! " << endl;
      }
      else if(tophad.size()==2 and toplep.size()==0) {
	isSL=false;
	isDL=false;
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
      // in SL case, the lepton/antilepton which is not present will be assigned with a (0,0,0,0) 4-vector
      if(isSL) {
	if(lep[0].pdgId()>0) {
	  if(lep[0].pdgId()==15 && no_tau_selection) {return;}
	  vec_lepton=lep[0].p4();
	  vec_antilepton=vec_zero;
	  vec_antid=q2[0].p4();
	  vec_d=vec_zero;
	  leptonflag=1;
	  //cout << "Lepton! " << endl;
	}
	else if(lep[0].pdgId()<0) {
	  if(lep[0].pdgId()==-15 && no_tau_selection) {return;}
	  vec_antilepton=lep[0].p4();
	  vec_lepton=vec_zero;
	  vec_d=q1[0].p4();
	  vec_antid=vec_zero;
	  leptonflag=-1;
	  //cout << "Antilepton! " << endl;
	}   
      }
      // in DL case, the assignment is straight forward. pdgid>0 are leptons, pdgid<0 are antileptons
      if(isDL) {
	if(lep[0].pdgId()>0) {
	  if(lep[0].pdgId()==15 && no_tau_selection) {return;}
	  vec_lepton=lep[0].p4();
	}
	else if(lep[0].pdgId()<0) {
  	  if(lep[0].pdgId()==-15 && no_tau_selection) {return;}
	  vec_antilepton=lep[0].p4();
	}
	if(lep[1].pdgId()>0) {
 	  if(lep[1].pdgId()==15 && no_tau_selection) {return;}
	  vec_lepton=lep[1].p4();
	}
	else if(lep[1].pdgId()<0) {
	  if(lep[1].pdgId()==-15 && no_tau_selection) {return;}
	  vec_antilepton=lep[1].p4();
	}
      }
      // now save the top/antitop, b/antib vectors for later comparison with the RECO vectors
      vec_top_tmp=vec_top;
      vec_antitop_tmp=vec_antitop;
      vec_b_tmp=vec_b;
      vec_antib_tmp=vec_antib;
      gen_evt_filled=true;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // if the loop is in var_type RECO and the events satisfies the requirements, the recontruction of the RECO variables can begin
    else if(input.selectedJets.size()>=4 && dec_type.EqualTo("RECO") && ((input.selectedElectrons.size()+input.selectedMuons.size())==1)){
      //cout << "N_jets>=4 and decay type RECO and Electrons+Muons==1" << endl;
      isSL=true;
      isDL=false;
      // this is the code of Hannes ttbar reconstruction processor to create some likelihood interpretations of the event
      std::vector<TLorentzVector> jetvecs = BoostedUtils::GetTLorentzVectors(BoostedUtils::GetJetVecs(input.selectedJets));
      std::vector<float> jetcsvs;
      int ntags=0;
      for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++){
	jetcsvs.push_back(MiniAODHelper::GetJetCSV(*j));
	if(BoostedUtils::PassesCSV(*j)) ntags++;
      }
      TLorentzVector lepvec = BoostedUtils::GetTLorentzVector(BoostedUtils::GetPrimLepVec(input.selectedElectrons,input.selectedMuons));
      TVector2 metvec(input.pfMET.px(),input.pfMET.py());
      if(input.genTopEvt.IsFilled()&&input.genTopEvt.IsSemiLepton()){
	vector<TLorentzVector> bs_true= BoostedUtils::GetTLorentzVectors(input.genTopEvt.GetHiggsDecayProductVecs());
	vector<TLorentzVector> qs_true= BoostedUtils::GetTLorentzVectors(input.genTopEvt.GetWQuarksVecs());
	if(bs_true.size()==2){
	  TLorentzVector bhad_true = BoostedUtils::GetTLorentzVector(input.genTopEvt.GetTopHadDecayQuarkVec());
	  TLorentzVector blep_true = BoostedUtils::GetTLorentzVector(input.genTopEvt.GetTopLepDecayQuarkVec());
	  TLorentzVector lep_true = BoostedUtils::GetTLorentzVector(input.genTopEvt.GetLeptonVec());
	  TLorentzVector nu_true = BoostedUtils::GetTLorentzVector(input.genTopEvt.GetNeutrinoVec());
	  //mcmatcher.Setup(bhad_true,qs_true[0],qs_true[1],blep_true,lep_true,nu_true,bs_true[0],bs_true[1]);
	}
      }
      Interpretation** ints = generator.GenerateTTHInterpretations(jetvecs,jetcsvs,lepvec,metvec);
      uint nints = generator.GetNints();
      Interpretation* best_int_lr=0;
      float best_lr=-99999;
      //    float best_chi2=-99999;
      for(uint i=0; i<nints; i++){
	  // likelihood ratio good ttbar reco / combinatorial background
	  float lr=quality.TTLikelihood_comb(*(ints[i]));
	  // simple chi2 reconstruction using hadronic W and both to masses
	  /*	float chi2=quality.TTChi2(*(ints[i]));
	  if(chi2>best_chi2){
	      best_chi2=chi2;
	      best_int_chi2=ints[i];
	      }*/
	  if(lr>best_lr){
	      best_lr=lr;
	      best_int_lr=ints[i];
	  }
      }
      if(best_lr>0.) {
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
	if(input.selectedMuons.size()==1) {
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
	vars.FillVar("RECO_flag_before_match",1);
	// now do a Delta R Matching of the reconstructed 4-vectors with the saved GEN vectors
	float dR_max=0.4;
	float dR_top=dR_max+1;
	float dR_antitop=dR_max+1;
	float dR_b=dR_max+1;
	float dR_antib=dR_max+1;
	if(gen_evt_filled){
	  dR_top=BoostedUtils::DeltaR(vec_top,vec_top_tmp);
	  dR_antitop=BoostedUtils::DeltaR(vec_antitop,vec_antitop_tmp);
	  dR_b=BoostedUtils::DeltaR(vec_b,vec_b_tmp);
	  dR_antib=BoostedUtils::DeltaR(vec_antib,vec_antib_tmp);
	}
	// if the dR Matching is succesfull the processor proceeds otherwise the loop for reco ends here
	if(dR_top<=dR_max && dR_antitop<=dR_max && dR_b<=dR_max && dR_antib<=dR_max) {
	  //cout << endl;
	  //cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!reconstruction succesfull!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	  //cout << endl;
	  vars.FillVar("RECO_flag_after_match",1);
	}
	else {
	  //cout << endl;
	  //cout << "reconstruction not correct, abort!! " << endl;
	  //cout << endl;
	}
	
	
      }
      // if the interpretation is 0 the loop for reco ends here
      else {
	//cout << "Interpretation = 0, abort!! " << endl;
	continue;
      }
      
    }
    // if neither GEN nor RECO part worked the loop ends here
    else {
      //cout << *it_type << " reconstruction not possible, abort!! " << endl;
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
      //cout << dec_type << endl;
      //cout << "Lepton Mass: " << vec_lepton.M() << endl;
      //cout << "Antilepton Mass: " << vec_antilepton.M() << endl;
      //cout << "frame: " << it_frames->first << " " << it_frames->second << endl;
      
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
	if(leptonflag==1) {
	  variables["cos_theta_l"]=6;
	  variables["cos_theta_lb"]=8;
	  variables["Delta_Phi_lb"]=10;
	  variables["cos_theta_ldbar"]=14;
	  variables["M_l"]=20;
	}
	if(leptonflag==-1) {
	  variables["cos_theta_lbar"]=7;
	  variables["cos_theta_lbarbbar"]=9;
	  variables["Delta_Phi_lbarbbar"]=11;
	  variables["cos_theta_lbard"]=15;
	  variables["M_lbar"]=21;
	}
      }
      // same for DL events
      if(isDL) {
	variables["cos_theta_ll"]=3;
	variables["Delta_Phi_ll"]=4;
	variables["Delta_Eta_ll"]=5;
	variables["cos_theta_l"]=6;
	variables["cos_theta_lbar"]=7;
	variables["cos_theta_lb"]=8;
	variables["cos_theta_lbarbbar"]=9;
	variables["Delta_Phi_lb"]=10;
	variables["Delta_Phi_lbarbbar"]=11; 
	variables["cos_theta_l_x_cos_theta_lbar"]=12;
 	variables["M_l"]=20;
  	variables["M_lbar"]=21;
      }
      // now the GetVars function calculates the desired variable depending on the number of the variable using the 4-vectors of the event
      for(auto it_variables=variables.begin();it_variables!=variables.end();++it_variables) {
	  vars.FillVar(*it_type+"__"+it_frames->first+"__"+it_variables->first,GetVars(vec_top_,vec_antitop_,vec_b_,vec_antib_,vec_lepton_,vec_antilepton_,vec_d_,vec_antid_,it_variables->second));
	  //cout << *it_type+"__"+it_frames->first+"__"+it_variables->first << " filled with " << GetVars(vec_top_,vec_antitop_,vec_b_,vec_antib_,vec_lepton_,vec_antilepton_,vec_d_,vec_antid_,it_variables->second) << endl;
	
      }
    }
  }
  
  
}
