#include "BoostedTTH/BoostedAnalyzer/interface/QuarkMatchingVarProcessor.hpp"

using namespace std;

QuarkMatchingVarProcessor::QuarkMatchingVarProcessor(){

  DeltaRCut = 0.3;

}

QuarkMatchingVarProcessor::~QuarkMatchingVarProcessor(){}

void QuarkMatchingVarProcessor::Init(const InputCollections& input, VariableContainer& vars){

  vars.InitVars("Jet_PartonPt","N_Jets");
  vars.InitVars("Jet_PartonDeltaR","N_Jets");
  vars.InitVars("Jet_PartonMotherId","N_Jets");
  vars.InitVars("Jet_PartonFlav","N_Jets");

  vars.InitVar("Evt_bbMass","F");
  vars.InitVar("Evt_regbbMass","F");
  vars.InitVar("Evt_bbMass2Lep","F");
  vars.InitVar("Evt_regbbMass2Lep","F");
  vars.InitVar("Evt_bbMass1Lep","F");
  vars.InitVar("Evt_regbbMass1Lep","F");
  vars.InitVar("Evt_bbMass0Lep","F");
  vars.InitVar("Evt_regbbMass0Lep","F");

  vars.InitVar("Evt_hadtopMass","F");
  vars.InitVar("Evt_reghadtopMass","F");


  initialized = true;
}

void QuarkMatchingVarProcessor::Process(const InputCollections& input, VariableContainer& vars){

  if(!initialized) cerr << "tree processor not initialized" << endl;
  
  //Get Quarks form W+/- and Top Decays
  vector<reco::GenParticle> quarks;
  quarks = GetQuarksfromTopDecay(input);
  if(input.genTopEvt.GetHiggs().pdgId() == 25) {
    vector<reco::GenParticle> higgsquarks = GetQuarksfromHiggsDecay(input);
    quarks.insert(end(quarks), begin(higgsquarks), end(higgsquarks));
  }

  //Loop over all Jet
  float DeltaRtmp;
  
  vector<pat::Jet> higgsjets; 
  pat::Jet hadtopjet;
  bool topjetfound = false;
  vector<pat::Jet> hadWjets;
  
  for(vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); itJet++){
    reco::GenParticle MatchedParton;
    int iJet = itJet - input.selectedJets.begin();
    float DeltaRMin = 9999999;
    bool foundquark = false;
    
    for(vector<reco::GenParticle>::const_iterator itq = quarks.begin(); itq != quarks.end(); itq++){
      DeltaRtmp = BoostedUtils::DeltaR(itJet->p4(),itq->p4());
      if(DeltaRtmp < DeltaRCut && DeltaRtmp < DeltaRMin){
	MatchedParton = *itq;
	DeltaRMin = DeltaRtmp;
	foundquark = true;
	if(MatchedParton.mother()->pdgId() == 25 &&  BoostedUtils::PassesCSV(*itJet, 'M')) {
	  higgsjets.push_back(*itJet);
	}
	if(input.genTopEvt.IsSemiLepton()){
	  //Get to b from hadronic Top matched Jet
	  if(MatchedParton.mother()->pdgId() == input.genTopEvt.GetTopHad().pdgId() &&  BoostedUtils::PassesCSV(*itJet, 'M')){
	    hadtopjet = *itJet;
	    topjetfound = true;
	  }
	  //Get to quarks from hadronic W matched Jets
	  if(MatchedParton.mother()->pdgId() ==  input.genTopEvt.GetWhad().pdgId()){
	    hadWjets.push_back(*itJet);
	  }
	}
      }
    }
    if(foundquark){
      vars.FillVars("Jet_PartonPt",iJet,MatchedParton.pt());
      vars.FillVars("Jet_PartonDeltaR",iJet,DeltaRMin);
      vars.FillVars("Jet_PartonMotherId",iJet,MatchedParton.mother()->pdgId());
      vars.FillVars("Jet_PartonFlav",iJet,MatchedParton.pdgId());
    }
    else {
      vars.FillVars("Jet_PartonPt",iJet,-99);
      vars.FillVars("Jet_PartonDeltaR",iJet,-99);
      vars.FillVars("Jet_PartonMotherId",iJet,-99);
      vars.FillVars("Jet_PartonFlav",iJet,-99);
    }
  }
  if(higgsjets.size() >= 2){
    if (higgsjets.size() > 2){
      vector<pat::Jet> jettmp;
      for( int y = 0; y < 2; y++){
	float pttmp = 0;
	int ztmp = 0;
	for(size_t z = 0; z < jettmp.size(); z++) {
	  if(higgsjets.at(z).pt() > pttmp) { pttmp = higgsjets.at(z).pt(); ztmp = z;  }
	}
	jettmp.push_back(higgsjets.at(ztmp));
      }
      higgsjets = jettmp;
    }

    //Split bbbar Mass by different multiplicities of matched Leptons
    //Write Mass for bbbar, if one of the jets has a matched Lepton
    if ((higgsjets.at(0).userFloat("Jet_leptonPt") > 0 && higgsjets.at(1).userFloat("Jet_leptonPt") <= 0) || (higgsjets.at(0).userFloat("Jet_leptonPt") <= 0 && higgsjets.at(1).userFloat("Jet_leptonPt") > 0)){
      vars.FillVar("Evt_bbMass1Lep",GetDijetMass(higgsjets.at(0),higgsjets.at(1),false));
      vars.FillVar("Evt_regbbMass1Lep",GetDijetMass(higgsjets.at(0),higgsjets.at(1),true));
      vars.FillVar("Evt_bbMass2Lep",-99);
      vars.FillVar("Evt_regbbMass2Lep",-99);
      vars.FillVar("Evt_bbMass0Lep",-99);
      vars.FillVar("Evt_regbbMass0Lep",-99);
    }
    //Write Mass for bbbar, if both of the jets hava a matched Lepton
    else if (higgsjets.at(0).userFloat("Jet_leptonPt") > 0 && higgsjets.at(1).userFloat("Jet_leptonPt") > 0) {
      vars.FillVar("Evt_bbMass2Lep",GetDijetMass(higgsjets.at(0),higgsjets.at(1),false));
      vars.FillVar("Evt_regbbMass2Lep",GetDijetMass(higgsjets.at(0),higgsjets.at(1),true));
      vars.FillVar("Evt_bbMass1Lep",-99);
      vars.FillVar("Evt_regbbMass1Lep",-99);
      vars.FillVar("Evt_bbMass0Lep",-99);
      vars.FillVar("Evt_regbbMass0Lep",-99);
    }
    //Write Mass for bbbar, if none of the jets habe a matched Lepton
    else {
      vars.FillVar("Evt_bbMass0Lep",GetDijetMass(higgsjets.at(0),higgsjets.at(1),false));
      vars.FillVar("Evt_regbbMass0Lep",GetDijetMass(higgsjets.at(0),higgsjets.at(1),true));
      vars.FillVar("Evt_bbMass1Lep",-99);
      vars.FillVar("Evt_regbbMass1Lep",-99);
      vars.FillVar("Evt_bbMass2Lep",-99);
      vars.FillVar("Evt_regbbMass2Lep",-99);
    }
    vars.FillVar("Evt_bbMass",GetDijetMass(higgsjets.at(0),higgsjets.at(1),false));
    vars.FillVar("Evt_regbbMass",GetDijetMass(higgsjets.at(0),higgsjets.at(1),true));
  }
  else {
    vars.FillVar("Evt_bbMass",-99);
    vars.FillVar("Evt_regbbMass",-99);
    //Splitted by lepton multiplicity
    vars.FillVar("Evt_bbMass2Lep",-99);
    vars.FillVar("Evt_regbbMass2Lep",-99);
    vars.FillVar("Evt_bbMass1Lep",-99);
    vars.FillVar("Evt_regbbMass1Lep",-99);
    vars.FillVar("Evt_bbMass0Lep",-99);
    vars.FillVar("Evt_regbbMass0Lep",-99);
  }
  if(hadWjets.size() == 2 && topjetfound) {
    vars.FillVar("Evt_hadtopMass",GetTopHadMass(hadtopjet,hadWjets, false));
    vars.FillVar("Evt_reghadtopMass",GetTopHadMass(hadtopjet,hadWjets, true));
  }
  else {
    vars.FillVar("Evt_hadtopMass",-99);
    vars.FillVar("Evt_reghadtopMass",-99);
  }
}


float QuarkMatchingVarProcessor::GetTopHadMass(const pat::Jet& topJet, const vector<pat::Jet>& WJets, const bool docorrection ) {
  
  float mass = 0;

  pat::Jet jet1 = topJet;
  pat::Jet jet2 = WJets.at(0);
  pat::Jet jet3 = WJets.at(1);

  TLorentzVector jet1vec;
  TLorentzVector jet2vec;
  TLorentzVector jet3vec;

  if(docorrection){
    jet1vec.SetPtEtaPhiM(jet1.userFloat("jetregressionPT"),jet1.eta(),jet1.phi(),jet1.mass());
  }
  else {
    jet1vec.SetPtEtaPhiM(jet1.pt(),jet1.eta(),jet1.phi(),jet1.mass());
  }
  jet2vec.SetPtEtaPhiM(jet2.pt(),jet2.eta(),jet2.phi(),jet2.mass());
  jet3vec.SetPtEtaPhiM(jet3.pt(),jet3.eta(),jet3.phi(),jet3.mass());
  
  mass = (jet1vec+jet2vec+jet3vec).M();

  return mass;
  
} 

float QuarkMatchingVarProcessor::GetDijetMass(const pat::Jet& jet1, const pat::Jet& jet2, const bool docorrection) {
  
  float dijetmass = 0;

  TLorentzVector jet1vec;
  TLorentzVector jet2vec;
  

  if(docorrection){
    jet1vec.SetPtEtaPhiM(jet1.userFloat("jetregressionPT"),jet1.eta(),jet1.phi(),jet1.mass());
    jet2vec.SetPtEtaPhiM(jet2.userFloat("jetregressionPT"),jet2.eta(),jet2.phi(),jet2.mass());
  }
  else {
    jet1vec.SetPtEtaPhiM(jet1.pt(),jet1.eta(),jet1.phi(),jet1.mass());
    jet2vec.SetPtEtaPhiM(jet2.pt(),jet2.eta(),jet2.phi(),jet2.mass());
  }
  //cout << "Higgsvec 1: " << endl;
  //PrintTLorentz(jet1vec);
  //cout << "Higgsvec 2: " << endl;
  //PrintTLorentz(jet2vec);
    
  dijetmass = (jet1vec+jet2vec).M();
  

  return dijetmass;
  
}


vector<reco::GenParticle> QuarkMatchingVarProcessor::GetQuarksfromTopDecay(const InputCollections& input) {

  vector<reco::GenParticle> quarks;

  quarks.push_back(input.genTopEvt.GetTopDecayQuark());
  quarks.push_back(input.genTopEvt.GetTopBarDecayQuark());
  vector<reco::GenParticle> wplusdecayproducts = input.genTopEvt.GetWplusDecayProducts();
  vector<reco::GenParticle> wminusdecayproducts = input.genTopEvt.GetWminusDecayProducts();
  for(auto p=wplusdecayproducts.begin(); p!=wplusdecayproducts.end(); p++){
    if(abs(p->pdgId()) == 1 ||abs(p->pdgId()) ==  2 || abs(p->pdgId()) == 3 || abs(p->pdgId()) == 4 || abs(p->pdgId()) == 5 || abs(p->pdgId()) == 6){
      quarks.push_back(*p);
    }
  }
  for(auto p=wminusdecayproducts.begin(); p!=wminusdecayproducts.end(); p++){
    if(abs(p->pdgId()) == 1 ||abs(p->pdgId()) ==  2 || abs(p->pdgId()) == 3 || abs(p->pdgId()) == 4 || abs(p->pdgId()) == 5 || abs(p->pdgId()) == 6){
      quarks.push_back(*p);
    }
  }
  
  return quarks;

}


vector<reco::GenParticle> QuarkMatchingVarProcessor::GetQuarksfromHiggsDecay(const InputCollections& input) {

  vector<reco::GenParticle> quarks = input.genTopEvt.GetHiggsDecayProducts();

  return quarks;

}


void QuarkMatchingVarProcessor::PrintTLorentz(TLorentzVector& vec) {
  
  cout << "pT : " << vec.Pt() << " ";
  cout << "eta: " << vec.Eta() << " ";
  cout << "phi: " << vec.Phi() << " ";
  cout << "M  : " << vec.M() << " ";
  cout << "E  : " << vec.E() << " ";
  cout << endl;

}
