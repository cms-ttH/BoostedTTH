#include "BoostedTTH/BoostedAnalyzer/interface/ttbarReconstructor.hpp"

using namespace std;

ttbarReconstructor::ttbarReconstructor (){
  TFile* file=new TFile("/nfs/dust/cms/user/mwassmer/Reco_Tests_plots/Reco_Tests.root","READ");
  histo_lepton=(THnSparseD*)file->Get("histo_lepton");
  histo_antilepton=(THnSparseD*)file->Get("histo_antilepton");
}
ttbarReconstructor::~ttbarReconstructor (){}

void ttbarReconstructor::SetdRArray(math::XYZTLorentzVector vec_top,math::XYZTLorentzVector vec_antitop,math::XYZTLorentzVector vec_b,math::XYZTLorentzVector vec_antib,math::XYZTLorentzVector vec_q_u,math::XYZTLorentzVector vec_q_d,math::XYZTLorentzVector vec_antiq_u,math::XYZTLorentzVector vec_antiq_d,math::XYZTLorentzVector vec_lepton,math::XYZTLorentzVector vec_antilepton,math::XYZTLorentzVector vec_nu,math::XYZTLorentzVector vec_antinu,int leptonflag) {
  std::map<TString,double> dR_map;
  std::vector<TString> variables;
  
  dR_map["dR_t_antit"]=BoostedUtils::DeltaR(vec_top,vec_antitop);
  dR_map["dR_b_antib"]=BoostedUtils::DeltaR(vec_b,vec_antib);
  
  dR_map["dR_t_b"]=BoostedUtils::DeltaR(vec_top,vec_b);
  dR_map["dR_t_antib"]=BoostedUtils::DeltaR(vec_top,vec_antib);
  dR_map["dR_antit_antib"]=BoostedUtils::DeltaR(vec_antitop,vec_antib);
  dR_map["dR_antit_b"]=BoostedUtils::DeltaR(vec_antitop,vec_b);
  
  variables.push_back("dR_t_antit");
  variables.push_back("dR_b_antib");
  variables.push_back("dR_t_b");
  variables.push_back("dR_t_antib");
  variables.push_back("dR_antit_antib");
  variables.push_back("dR_antit_b");
  
  if(leptonflag==1) {
    //cout << "negative charge lepton" << endl;
    dR_map["dR_q_u_antiq_d"]=BoostedUtils::DeltaR(vec_q_u,vec_antiq_d);
    
    dR_map["dR_t_q_u"]=BoostedUtils::DeltaR(vec_top,vec_q_u);
    dR_map["dR_t_antiq_d"]=BoostedUtils::DeltaR(vec_top,vec_antiq_d);
    dR_map["dR_antit_q_u"]=BoostedUtils::DeltaR(vec_antitop,vec_q_u);
    dR_map["dR_antit_antiq_d"]=BoostedUtils::DeltaR(vec_antitop,vec_antiq_d);
    
    dR_map["dR_b_q_u"]=BoostedUtils::DeltaR(vec_b,vec_q_u);
    dR_map["dR_b_antiq_d"]=BoostedUtils::DeltaR(vec_b,vec_antiq_d);
    dR_map["dR_antib_q_u"]=BoostedUtils::DeltaR(vec_antib,vec_q_u);
    dR_map["dR_antib_antiq_d"]=BoostedUtils::DeltaR(vec_antib,vec_antiq_d);
    
    dR_map["dR_t_lep"]=BoostedUtils::DeltaR(vec_top,vec_lepton);
    dR_map["dR_b_lep"]=BoostedUtils::DeltaR(vec_b,vec_lepton);
    dR_map["dR_antit_lep"]=BoostedUtils::DeltaR(vec_antitop,vec_lepton);
    dR_map["dR_antib_lep"]=BoostedUtils::DeltaR(vec_antib,vec_lepton);
    
    dR_map["m_antib_lep_antinu"]=(vec_antib+vec_lepton+vec_antinu).mass();
    dR_map["m_b_q_u_antiq_d"]=(vec_b+vec_q_u+vec_antiq_d).mass();
    dR_map["m_lep_antinu"]=(vec_lepton+vec_antinu).mass();
    dR_map["m_q_u_antiq_d"]=(vec_q_u+vec_antiq_d).mass();
    
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
    dR_map["dR_q_d_antiq_u"]=BoostedUtils::DeltaR(vec_q_d,vec_antiq_u);
    
    dR_map["dR_t_antiq_u"]=BoostedUtils::DeltaR(vec_top,vec_antiq_u);
    dR_map["dR_t_q_d"]=BoostedUtils::DeltaR(vec_top,vec_q_d);
    dR_map["dR_antit_antiq_u"]=BoostedUtils::DeltaR(vec_antitop,vec_antiq_u);
    dR_map["dR_antit_q_d"]=BoostedUtils::DeltaR(vec_antitop,vec_q_d);
    
    dR_map["dR_b_antiq_u"]=BoostedUtils::DeltaR(vec_b,vec_antiq_u);
    dR_map["dR_b_q_d"]=BoostedUtils::DeltaR(vec_b,vec_q_d);
    dR_map["dR_antib_antiq_u"]=BoostedUtils::DeltaR(vec_antib,vec_antiq_u);
    dR_map["dR_antib_q_d"]=BoostedUtils::DeltaR(vec_antib,vec_q_d);
    
    dR_map["dR_t_antilep"]=BoostedUtils::DeltaR(vec_top,vec_antilepton);
    dR_map["dR_b_antilep"]=BoostedUtils::DeltaR(vec_b,vec_antilepton);
    dR_map["dR_antit_antilep"]=BoostedUtils::DeltaR(vec_antitop,vec_antilepton);
    dR_map["dR_antib_antilep"]=BoostedUtils::DeltaR(vec_antib,vec_antilepton);
    
    dR_map["m_b_antilep_nu"]=(vec_b+vec_antilepton+vec_nu).mass();
    dR_map["m_antib_q_d_antiq_u"]=(vec_antib+vec_q_d+vec_antiq_u).mass();
    dR_map["m_antilep_nu"]=(vec_antilepton+vec_nu).mass();
    dR_map["m_q_d_antiq_u"]=(vec_q_d+vec_antiq_u).mass();
    
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
  for(int i=0;i<array_size;i++) {
      dR_array[i]=dR_map[variables[i]];
  }
}

double ttbarReconstructor::GetLikelihood(int leptonflag) {
  double likelihood=1.;
  int pos[19]={0};
  cout << "Leptonflag " << leptonflag << endl;
  cout << "dr array " << dR_array[0] << "   " << dR_array[10] << endl;
  Long64_t n_bin=0;
  if(leptonflag==1) {
    n_bin=histo_lepton->GetBin(dR_array);
    likelihood=histo_lepton->GetBinContent(n_bin,pos);
    cout << "lepton" << endl;
  }
  else if(leptonflag==-1) {
    n_bin=histo_antilepton->GetBin(dR_array);
    likelihood=histo_antilepton->GetBinContent(n_bin,pos);
    cout << "antilepton" << endl;
  }
  else {likelihood=0.;}
  cout << "nbin " << n_bin << endl;
  cout << "bin position first" << pos[0] << " " << pos[1] << " " << pos[2] << " " << pos[3] << " " << pos[4] << " " << pos[5] << endl;
  cout << "bin position second" << pos[6] << " " << pos[7] << " " << pos[8] << " " << pos[9] << " " << pos[10] << endl; 
  cout << "likelihood " << likelihood << endl;
  return likelihood;
}

void ttbarReconstructor::GetNuVecs(const TLorentzVector & lepvec, const TVector2 & metvec, TLorentzVector & nu1, TLorentzVector & nu2){
    double metvec2 = metvec.Px()*metvec.Px() + metvec.Py()*metvec.Py();
    double mu = (80.4*80.4)/2 + metvec.Px()*lepvec.Px() + metvec.Py()*lepvec.Py();
    double a = (mu*lepvec.Pz())/(lepvec.E()*lepvec.E() - lepvec.Pz()*lepvec.Pz());
    double a2 = TMath::Power(a, 2);
    double b = (TMath::Power(lepvec.E(), 2.)*metvec2 - TMath::Power(mu, 2.)) / (TMath::Power(lepvec.E(), 2)- TMath::Power(lepvec.Pz(), 2));
    float pz1,pz2;
    if (a2-b < 0) { 
	pz1 = a;
	pz2 = a;
    } else {
	double root = sqrt(a2-b);
	pz1 = a + root;
	pz2 = a - root;
    }
    nu1.SetPxPyPzE(metvec.Px(),metvec.Py(),pz1,sqrt(metvec.Mod2()+pz1*pz1));
    nu2.SetPxPyPzE(metvec.Px(),metvec.Py(),pz2,sqrt(metvec.Mod2()+pz2*pz2));
}

void ttbarReconstructor::Init(const InputCollections& input,VariableContainer& vars){
  
  vars.InitVar("bs_matched",0,"I");
  vars.InitVar("lfs_matched",0,"I");
  vars.InitVar("t_matched",0,"I");
  vars.InitVar("antit_matched",0,"I");
  vars.InitVar("ts_matched",0,"I");
  vars.InitVar("all_matched",0,"I");
  vars.InitVar("bslf_matched",0,"I");
  
  cout << "test test test " << endl;
  
  initialized=true;
}

void ttbarReconstructor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
 
//////////////////////////////////////////////////////////////////////////////////////////  
  // GEN INFOS
  
  math::XYZTLorentzVector vec_top_gen;
  math::XYZTLorentzVector vec_antitop_gen;
  math::XYZTLorentzVector vec_b_gen;
  math::XYZTLorentzVector vec_antib_gen;
  //math::XYZTLorentzVector vec_lepton_gen;
  //math::XYZTLorentzVector vec_antilepton_gen;
  math::XYZTLorentzVector vec_q_u_gen;
  math::XYZTLorentzVector vec_antiq_u_gen;
  math::XYZTLorentzVector vec_antiq_d_gen;
  math::XYZTLorentzVector vec_q_d_gen;
  math::XYZTLorentzVector vec_nu_gen;
  math::XYZTLorentzVector vec_antinu_gen;
  
  int leptonflag=0;
  
  if(input.genTopEvt.IsFilled()){
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
      //cout << "Dilepton Event! " << endl;
      return;
    }
    else if(tophad.size()==1 and toplep.size()==1 and q1.size()>=1 and q2.size()>=1) {
      //cout << "Single Lepton Event! " << endl;
    }
    else if(tophad.size()==2 and toplep.size()==0) {
      //cout << "Fully hadronic Event! " << endl;
      return;
    }
    else {
      return;
    }
    
    
    // make the correct assignment of the top/antitop b/antib 4-vectors
    for(auto it=tophad.begin();it!=tophad.end();++it) {
      if(it->pdgId()>0) { vec_top_gen=it->p4(); }
      else if(it->pdgId()<0) { vec_antitop_gen=it->p4(); }
    }
    for(auto it=toplep.begin();it!=toplep.end();++it) {
      if(it->pdgId()>0) { vec_top_gen=it->p4(); }
      else if(it->pdgId()<0) { vec_antitop_gen=it->p4(); }
    }
    for(auto it=bhad.begin();it!=bhad.end();++it) {
      if(it->pdgId()>0) { vec_b_gen=it->p4(); }
      else if(it->pdgId()<0) { vec_antib_gen=it->p4(); }
    }
    for(auto it=blep.begin();it!=blep.end();++it) {
      if(it->pdgId()>0) { vec_b_gen=it->p4(); }
      else if(it->pdgId()<0) { vec_antib_gen=it->p4(); }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // now identify the correct lepton/antilepton 4 vectors
    // in SL case, the lepton/antilepton which is not present will be assigned with a (0,0,0,0) 4-vector, pdgid>0 ->leptons pdgid<0 antileptons
    
    if(lep[0].pdgId()>0) {
      leptonflag=1;
      //cout << "Lepton! " << endl;
    }
    else if(lep[0].pdgId()<0) {
      leptonflag=-1;
      //cout << "Antilepton! " << endl;
    }
    
    //cout << "Leptonflag: " << leptonflag << endl;
    if(leptonflag==1) {
      vec_q_u_gen=q1[0].p4();
      vec_antiq_d_gen=q2[0].p4();
      vec_antinu_gen=nu[0].p4();
    }
    else if(leptonflag==-1) {
      vec_q_d_gen=q1[0].p4();
      vec_antiq_u_gen=q2[0].p4();
      vec_nu_gen=nu[0].p4();
    }  
  }
  
  else {return;}
  
  ////////////////////////////////////////////////////////////////////////////////////////// 
  // RECO CODE
  
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
  
  std::vector<pat::Jet> jets=input.selectedJets;
  std::vector<pat::Jet> jets_btag;
  std::vector<pat::Jet> jets_no_btag;
  for(auto j=jets.begin(); j!=jets.end(); j++){
    if(BoostedUtils::PassesCSV(*j)) {
      jets_btag.push_back(*j);
    }
    else {
      jets_no_btag.push_back(*j);
    }
  }
  std::vector<pat::Jet> jets_no_btag_tmp;
  std::vector<pat::Jet> jets_no_btag_max;
  int n_jets=jets.size();
  int n_btags=jets_btag.size();
  int n_no_btags=jets_no_btag.size();
  
  cout << "-----------------------------------------------------------" << endl;
  cout << "N_Jets: " << n_jets << " N_Btags: " << n_btags << " N_no_Btags: " << n_no_btags << endl;
  cout << "-----------------------------------------------------------" << endl;
  // if number of jets without btag is below 2 then use the jets of the btag jet collection with the smallest csv value as a second non_btag jet
  /*if(n_no_btags>0) {
    int max_csv_index=0;
    float max_csv=0.;
    for(int i=0;i<n_no_btags; i++){
      if(MiniAODHelper::GetJetCSV(jets_no_btag[i])>max_csv) {
	max_csv=MiniAODHelper::GetJetCSV(jets_no_btag[i]);
	max_csv_index=i;
      }
    }
    jets_btag.push_back(jets_no_btag[max_csv_index]);
    jets_no_btag.erase(jets_no_btag.begin()+max_csv_index);  
    n_no_btags-=1;
    n_btags+=1;
  }*/
  
  
  //int n_expected_btags=2;
  
  std::vector<pat::Electron> electrons=input.selectedElectrons;
  std::vector<pat::Muon> muons=input.selectedMuons;
  pat::MET MET=input.correctedMET;
  
  TLorentzVector nu1;
  TLorentzVector nu2;
  TLorentzVector lepvec;
  TVector2 metvec(MET.px(),MET.py());
  
  if(electrons.size()+muons.size()==1) {
    if(electrons.size()==1) {
      leptonflag=-electrons[0].charge();
      if(leptonflag==1) {
	vec_lepton=electrons[0].p4();
      }
      else if(leptonflag==-1) {
	vec_antilepton=electrons[0].p4();
      }
    }
    else if(muons.size()==1) {
      leptonflag=-muons[0].charge();
      if(leptonflag==1) {
	vec_lepton=muons[0].p4();
      }
      else if(leptonflag==-1) {
	vec_antilepton=muons[0].p4();
      }
    }
  }
  else {
    return;
  }
  
  
  if(leptonflag==1) {
    lepvec=BoostedUtils::GetTLorentzVector(vec_lepton);
  }
  else if(leptonflag==-1) {
    lepvec=BoostedUtils::GetTLorentzVector(vec_antilepton);
  }/*
  cout << "MET: Px: " << MET.px() << " Py: " << MET.py() << " Pz: " << MET.pz()<< endl;
  cout << "MET: Px: " << metvec1.Px() << " Py: " << metvec1.Py() << " Pz: " << metvec1.Pz()<< endl;
  cout << "MET: Px: " << metvec2.Px() << " Py: " << metvec2.Py() << " Pz: " << metvec2.Pz()<< endl;
  if(leptonflag==-1) {
    cout << "MET: Px: " << vec_nu_gen.Px() << " Py: " << vec_nu_gen.Py() << " Pz: " << vec_nu_gen.Pz()<< endl;
  }
  else if(leptonflag==1) {
    cout << "MET: Px: " << vec_antinu_gen.Px() << " Py: " << vec_antinu_gen.Py() << " Pz: " << vec_antinu_gen.Pz()<< endl;
  }*/
  GetNuVecs(lepvec,metvec,nu1,nu2);
  std::vector<math::XYZTLorentzVector> nu_vec;
  nu_vec.push_back(BoostedUtils::GetXYZTLorentzVector(nu1));
  nu_vec.push_back(BoostedUtils::GetXYZTLorentzVector(nu2));
  
  cout << "MET: Px: " << nu1.Px() << " Py: " << nu1.Py() << " Pz: " << nu1.Pz()<< endl;
  cout << "MET: Px: " << nu2.Px() << " Py: " << nu2.Py() << " Pz: " << nu2.Pz()<< endl;
  
  double likelihood_max=0.;
  int i_b_max=0;
  int i_antib_max=0;
  int i_q1_max=0;
  int i_q2_max=0;
  int n_max=0;
  for(int n=0;n<2;n++) {
    for(int i_b=0;i_b<n_btags;i_b++) {
      //cout << i << endl;
      for(int i_antib=0;(i_antib<n_btags);i_antib++) {
	jets_no_btag_tmp=jets_no_btag;
	if(i_b==i_antib) {continue;}
	for(int j=0;j<n_btags;j++){
	  if(j!=i_b && j!=i_antib) {
	    jets_no_btag_tmp.push_back(jets_btag[j]);
	  }
	}
	n_no_btags=jets_no_btag_tmp.size();
	for(int i_q1=0;i_q1<n_no_btags;i_q1++) {	
	  for(int i_q2=0;i_q2<n_no_btags;i_q2++) {
	    if(i_q2==i_q1) {continue;}  
	    //cout << i_b << "  " << i_antib  << "  " << i_q1 << "  " << i_q2 << endl;
	    vec_b=jets_btag[i_b].p4();
	    vec_antib=jets_btag[i_antib].p4();
	    if(leptonflag==1) {
	      vec_q_u=jets_no_btag_tmp[i_q1].p4();
	      vec_antiq_d=jets_no_btag_tmp[i_q2].p4();
	      vec_antinu=nu_vec[n];
	      vec_top=vec_b+vec_q_u+vec_antiq_d;
	      vec_antitop=vec_antib+vec_lepton+vec_antinu;
	    }
	    else if(leptonflag==-1) {
	      vec_q_d=jets_no_btag_tmp[i_q1].p4();
	      vec_antiq_u=jets_no_btag_tmp[i_q2].p4();
	      vec_nu=nu_vec[n];
	      vec_antitop=vec_antib+vec_q_d+vec_antiq_u;
	      vec_top=vec_b+vec_antilepton+vec_nu;
	    }
	    else {
	      return;
	    }
	    SetdRArray(vec_top,vec_antitop,vec_b,vec_antib,vec_q_u,vec_q_d,vec_antiq_u,vec_antiq_d,vec_lepton,vec_antilepton,vec_nu,vec_antinu,leptonflag);
	    double likelihood = ttbarReconstructor::GetLikelihood(leptonflag);
	    //cout << "likelihood " << likelihood << endl;
	    if(likelihood>likelihood_max) {
	      likelihood_max=likelihood;
	      i_b_max=i_b;
	      i_antib_max=i_antib;
	      i_q1_max=i_q1;
	      i_q2_max=i_q2;
	      n_max=n;
	      jets_no_btag_max=jets_no_btag_tmp;
	    }
	  }
	}
      }
    }
  }
  if(likelihood_max==0.) {
    return;
  }
  
  //std::map<TString,double> dR_map = ttbarReconstructor::GetdRMap(vec_top,vec_antitop,vec_b,vec_antib,vec_q_u,vec_q_d,vec_antiq_u,vec_antiq_d,leptonflag);
  //double likelihood = ttbarReconstructor::GetLikelihood(dR_map);
  
  cout << "############################################" << endl;
  cout << "Likelihood Max: " << likelihood_max << endl;
  cout << "i_b: " << i_b_max << " i_antib: " << i_antib_max << endl;
  if(leptonflag==1) {
    cout << "i_q_u: " << i_q1_max << " i_antiq_d: " << i_q2_max << endl;
  }
  else if(leptonflag==-1) {
    cout << "i_q_d: " << i_q1_max << " i_antiq_u: " << i_q2_max << endl;
  }
  cout << "############################################" << endl;
  
  math::XYZTLorentzVector vec_b_max=jets_btag[i_b_max].p4();
  math::XYZTLorentzVector vec_antib_max=jets_btag[i_antib_max].p4();
  math::XYZTLorentzVector vec_q_u_max=jets_no_btag_max[i_q1_max].p4();
  math::XYZTLorentzVector vec_q_d_max=jets_no_btag_max[i_q1_max].p4();
  math::XYZTLorentzVector vec_antiq_u_max=jets_no_btag_max[i_q2_max].p4();
  math::XYZTLorentzVector vec_antiq_d_max=jets_no_btag_max[i_q2_max].p4();
  math::XYZTLorentzVector vec_top_max;
  math::XYZTLorentzVector vec_antitop_max;
  if(leptonflag==1) {
    vec_top_max=vec_b_max+vec_q_u_max+vec_antiq_d_max;
    vec_antitop_max=vec_antib_max+vec_lepton+nu_vec[n_max];//ttbarReconstructor::GetNuSol(vec_lepton,metvec1,n_max);
  }
  if(leptonflag==-1) {
    vec_antitop_max=vec_antib_max+vec_q_d_max+vec_antiq_u_max;
    vec_top_max=vec_b_max+vec_antilepton+nu_vec[n_max];//ttbarReconstructor::GetNuSol(vec_antilepton,metvec1,n_max);
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////
  // matching of gen stuff with reco
  
  bool b_matched = BoostedUtils::DeltaR(vec_b_gen,vec_b_max)<0.4;
  bool antib_matched = BoostedUtils::DeltaR(vec_antib_gen,vec_antib_max)<0.4;
  bool q_u_matched = BoostedUtils::DeltaR(vec_q_u_gen,vec_q_u_max)<0.4;
  bool q_d_matched = BoostedUtils::DeltaR(vec_q_d_gen,vec_q_d_max)<0.4;
  bool antiq_u_matched = BoostedUtils::DeltaR(vec_antiq_u_gen,vec_antiq_u_max)<0.4;
  bool antiq_d_matched = BoostedUtils::DeltaR(vec_antiq_d_gen,vec_antiq_d_max)<0.4;
  bool top_matched = BoostedUtils::DeltaR(vec_top_gen,vec_top_max)<0.4;
  bool antitop_matched = BoostedUtils::DeltaR(vec_antitop_gen,vec_antitop_max)<0.4;
  
  
  if(b_matched && antib_matched) {
    cout << "bs are matched !!!!" << endl;
    vars.FillVar("bs_matched",1);
  }
  if(leptonflag==1) {
    if(q_u_matched && antiq_d_matched) {
      cout << "lf quarks are matched !!!! " << endl;
      vars.FillVar("lfs_matched",1);
    }
    if(q_u_matched && antiq_d_matched && b_matched && antib_matched) {
      cout << "lf and bs matched" << endl;
      vars.FillVar("bslf_matched",1);
    }
    if(top_matched) {
      vars.FillVar("t_matched",1);
      cout << "top matched !!!!" << endl;
    }
    if(antitop_matched) {
      vars.FillVar("antit_matched",1);
      cout << "antitop matched !!!!" << endl;
    }
    if(top_matched && antitop_matched) {
      vars.FillVar("ts_matched",1);
      cout << "top quarks are matched !!!! " << endl;
    }
    if(top_matched && antitop_matched && b_matched && antib_matched) {
      vars.FillVar("all_matched",1);
      cout << "all quarks are matched !!!! " << endl;
    }
  }
  else if(leptonflag==-1) {
    if(q_d_matched && antiq_u_matched) {
      cout << "lf quarks are matched !!!! " << endl;
      vars.FillVar("lfs_matched",1);
    }
    if(q_d_matched && antiq_u_matched && b_matched && antib_matched) {
      cout << "lf and bs matched" << endl;
      vars.FillVar("bslf_matched",1);
    }
    if(top_matched) {
      vars.FillVar("t_matched",1);
      cout << "top matched !!!!" << endl;
    }
    if(antitop_matched) {
      vars.FillVar("antit_matched",1);
      cout << "antitop matched !!!!" << endl;
    }
    if(top_matched && antitop_matched) {
      vars.FillVar("ts_matched",1);
      cout << "top quarks are matched !!!! " << endl;
    }
    if(top_matched && antitop_matched && b_matched && antib_matched) {
      vars.FillVar("all_matched",1);
      cout << "all quarks are matched !!!! " << endl;
    }
  }
    
  
}
