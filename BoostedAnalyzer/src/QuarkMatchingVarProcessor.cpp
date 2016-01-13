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

  initialized = true;
}

void QuarkMatchingVarProcessor::Process(const InputCollections& input, VariableContainer& vars){

  if(!initialized) cerr << "tree processor not initialized" << endl;
  
  //Get Quarks form W+/- and Top Decays
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
  //Loop over all Jet

  float DeltaRtmp;

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
}
