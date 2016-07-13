#include "BoostedTTH/BoostedAnalyzer/interface/QuarkMatchingVarProcessor.hpp"

using namespace std;

QuarkMatchingVarProcessor::QuarkMatchingVarProcessor(){

  DeltaRCut = 0.3;

}

QuarkMatchingVarProcessor::~QuarkMatchingVarProcessor(){}

void QuarkMatchingVarProcessor::Init(const InputCollections& input, VariableContainer& vars){

  vars.InitVars("Jet_MatchedPartonPt","N_Jets");
  vars.InitVars("Jet_MatchedPartonDeltaR","N_Jets");
  vars.InitVars("Jet_MatchedPartonMotherId","N_Jets");
  vars.InitVars("Jet_MatchedPartonFlav","N_Jets");

  vars.InitVars("Jet_GenParticleFlav","N_Jets");
  vars.InitVars("Jet_GenParticleMotherId", "N_Jets");
  vars.InitVars("Jet_GenParticlePt","N_Jets");
  vars.InitVars("Jet_GenParticleEta","N_Jets");

  vars.InitVars("Jet_isHiggsJet","N_Jets");

  vars.InitVar("N_MatchedHiggsJets","F");

  bool stdreginit = false;
  bool addreginit = false;

  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
    //int iJet = itJet - input.selectedJets.begin();
    //cout << "cout: " << itJet->userFloatNames() << endl;

    for (  auto ituserfloat = (itJet->userFloatNames()).begin() ; ituserfloat != (itJet->userFloatNames()).end() ; ituserfloat++  ) {
      if (  (*ituserfloat).find("bregCorrection") != std::string::npos  ) {
	if(  (*ituserfloat) == "bregCorrection"  ) {

	  vars.InitVar("Evt_MCbbMass","F");
	  vars.InitVar("Evt_MCregbbMass","F");
	  vars.InitVar("Evt_MCbbMass2Lep","F");
	  vars.InitVar("Evt_MCregbbMass2Lep","F");
	  vars.InitVar("Evt_MCbbMass1Lep","F");
	  vars.InitVar("Evt_MCregbbMass1Lep","F");
	  vars.InitVar("Evt_MCbbMass0Lep","F");
	  vars.InitVar("Evt_MCregbbMass0Lep","F");

	  vars.InitVar("Evt_MChadtopMass","F");
	  vars.InitVar("Evt_MCreghadtopMass","F");

	  stdreginit = true;

	}
	else {
	  size_t found = (*ituserfloat).find("_");
	  string extention = (*ituserfloat).substr(found);

	  vars.InitVar("Evt_MCregbbMass"+extention,"F");
	  vars.InitVar("Evt_MCregbbMass2Lep"+extention,"F");
	  vars.InitVar("Evt_MCregbbMass1Lep"+extention,"F");
	  vars.InitVar("Evt_MCregbbMass0Lep"+extention,"F");

	  vars.InitVar("Evt_MCreghadtopMass"+extention,"F");

	  extentions.push_back(extention);

	  addreginit = true;
	}
      }//end: bregCorrectio* ?
    }//end: userfloat loop
    if (  stdreginit || addreginit  ) {  //only loop as long the first regressed jet is found
      break;
    }
  }//end: loop over jets





  initialized = true;
}

void QuarkMatchingVarProcessor::Process(const InputCollections& input, VariableContainer& vars){

  if(!initialized) cerr << "tree processor not initialized" << endl;
  if(!input.genTopEvt.IsFilled()) { return; } //Only continue, if genTopEvt is filled


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
  vector<int> iHiggsJet;


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
	  iHiggsJet.push_back(iJet);
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
      vars.FillVars("Jet_MatchedPartonPt",iJet,MatchedParton.pt());
      vars.FillVars("Jet_MatchedPartonDeltaR",iJet,DeltaRMin);
      vars.FillVars("Jet_MatchedPartonMotherId",iJet,MatchedParton.mother()->pdgId());
      vars.FillVars("Jet_MatchedPartonFlav",iJet,MatchedParton.pdgId());
    }
    else {
      vars.FillVars("Jet_MatchedPartonPt",iJet,-99);
      vars.FillVars("Jet_MatchedPartonDeltaR",iJet,-99);
      vars.FillVars("Jet_MatchedPartonMotherId",iJet,-99);
      vars.FillVars("Jet_MatchedPartonFlav",iJet,-99);
    }
  }
  vars.FillVar("N_MatchedHiggsJets",higgsjets.size());

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
      vars.FillVar("Evt_MCbbMass1Lep",GetDijetMass(higgsjets.at(0),higgsjets.at(1),false));
      vars.FillVar("Evt_MCregbbMass1Lep",GetDijetMass(higgsjets.at(0),higgsjets.at(1),true));
      vars.FillVar("Evt_MCbbMass2Lep",-99);
      vars.FillVar("Evt_MCregbbMass2Lep",-99);
      vars.FillVar("Evt_MCbbMass0Lep",-99);
      vars.FillVar("Evt_MCregbbMass0Lep",-99);
      for(  auto itextentions = extentions.begin() ; itextentions != extentions.end(); itextentions++  ) {
	vars.FillVar("Evt_MCregbbMass1Lep"+(*itextentions),GetDijetMass(higgsjets.at(0),higgsjets.at(1),(*itextentions)));
	vars.FillVar("Evt_MCregbbMass2Lep"+(*itextentions),-99);
	vars.FillVar("Evt_MCregbbMass0Lep"+(*itextentions),-99);
      }
    }
    //Write Mass for bbbar, if both of the jets hava a matched Lepton
    else if (higgsjets.at(0).userFloat("Jet_leptonPt") > 0 && higgsjets.at(1).userFloat("Jet_leptonPt") > 0) {
      vars.FillVar("Evt_MCbbMass2Lep",GetDijetMass(higgsjets.at(0),higgsjets.at(1),false));
      vars.FillVar("Evt_MCregbbMass2Lep",GetDijetMass(higgsjets.at(0),higgsjets.at(1),true));
      vars.FillVar("Evt_MCbbMass1Lep",-99);
      vars.FillVar("Evt_MCregbbMass1Lep",-99);
      vars.FillVar("Evt_MCbbMass0Lep",-99);
      vars.FillVar("Evt_MCregbbMass0Lep",-99);
      for(  auto itextentions = extentions.begin() ; itextentions != extentions.end(); itextentions++  ) {
	vars.FillVar("Evt_MCregbbMass2Lep"+(*itextentions),GetDijetMass(higgsjets.at(0),higgsjets.at(1),(*itextentions)));
	vars.FillVar("Evt_MCregbbMass1Lep"+(*itextentions),-99);
	vars.FillVar("Evt_MCregbbMass0Lep"+(*itextentions),-99);
      }
    }
    //Write Mass for bbbar, if none of the jets habe a matched Lepton
    else {
      vars.FillVar("Evt_MCbbMass0Lep",GetDijetMass(higgsjets.at(0),higgsjets.at(1),false));
      vars.FillVar("Evt_MCregbbMass0Lep",GetDijetMass(higgsjets.at(0),higgsjets.at(1),true));
      vars.FillVar("Evt_MCbbMass1Lep",-99);
      vars.FillVar("Evt_MCregbbMass1Lep",-99);
      vars.FillVar("Evt_MCbbMass2Lep",-99);
      vars.FillVar("Evt_MCregbbMass2Lep",-99);
      for(  auto itextentions = extentions.begin() ; itextentions != extentions.end(); itextentions++  ) {
	vars.FillVar("Evt_MCregbbMass0Lep"+(*itextentions),GetDijetMass(higgsjets.at(0),higgsjets.at(1),(*itextentions)));
	vars.FillVar("Evt_MCregbbMass1Lep"+(*itextentions),-99);
	vars.FillVar("Evt_MCregbbMass2Lep"+(*itextentions),-99);
      }
    }
    vars.FillVar("Evt_MCbbMass",GetDijetMass(higgsjets.at(0),higgsjets.at(1),false));
    vars.FillVar("Evt_MCregbbMass",GetDijetMass(higgsjets.at(0),higgsjets.at(1),true));
    for(  auto itextentions = extentions.begin() ; itextentions != extentions.end(); itextentions++  ) {
      vars.FillVar("Evt_MCregbbMass"+(*itextentions),GetDijetMass(higgsjets.at(0),higgsjets.at(1),(*itextentions)));
    }
  }
  else {
    vars.FillVar("Evt_MCbbMass",-99);
    vars.FillVar("Evt_MCregbbMass",-99);
    //Splitted by lepton multiplicity
    vars.FillVar("Evt_MCbbMass2Lep",-99);
    vars.FillVar("Evt_MCregbbMass2Lep",-99);
    vars.FillVar("Evt_MCbbMass1Lep",-99);
    vars.FillVar("Evt_MCregbbMass1Lep",-99);
    vars.FillVar("Evt_MCbbMass0Lep",-99);
    vars.FillVar("Evt_MCregbbMass0Lep",-99);
    for(  auto itextentions = extentions.begin() ; itextentions != extentions.end(); itextentions++  ) {
      vars.FillVar("Evt_MCregbbMass"+(*itextentions),-99);
      //Splitted by lepton multiplicity
      vars.FillVar("Evt_MCregbbMass2Lep"+(*itextentions),-99);
      vars.FillVar("Evt_MCregbbMass1Lep"+(*itextentions),-99);
      vars.FillVar("Evt_MCregbbMass0Lep"+(*itextentions),-99);
    }
  }
  if(hadWjets.size() == 2 && topjetfound) {
    vars.FillVar("Evt_MChadtopMass",GetTopHadMass(hadtopjet,hadWjets, false));
    vars.FillVar("Evt_MCreghadtopMass",GetTopHadMass(hadtopjet,hadWjets, true));
    for(  auto itextentions = extentions.begin() ; itextentions != extentions.end(); itextentions++  ) {
      vars.FillVar("Evt_MCreghadtopMass"+(*itextentions),GetTopHadMass(hadtopjet,hadWjets,(*itextentions)));
    }

  }
  else {
    vars.FillVar("Evt_MChadtopMass",-99);
    vars.FillVar("Evt_MCreghadtopMass",-99);
    for(  auto itextentions = extentions.begin() ; itextentions != extentions.end(); itextentions++  ) {
      vars.FillVar("Evt_MCreghadtopMass"+(*itextentions),-99);
    }
  }


  //Save if Jet was used for MC Higgs Mass
  int nh = 0;
  for (std::vector<pat::Jet>::const_iterator it = input.selectedJets.begin(), ed = input.selectedJets.end(); it != ed; ++it ) {
    int iJet = it - input.selectedJets.begin();
    bool jetset = false;
    if (iHiggsJet.size() > 1) {
      for (size_t ih = 0; ih < iHiggsJet.size(); ih++) {
	if (iHiggsJet.at(ih) == iJet) {
	  vars.FillVars("Jet_isHiggsJet",iJet,1);
	  jetset = true;
	  nh += 1;
	}
      }
    }
    if (jetset == false) {
      vars.FillVars("Jet_isHiggsJet",iJet,0);
    }

  }
  //GenParticle Code:
  for(vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); itJet++){
    int iJet = itJet - input.selectedJets.begin();

    const reco::GenParticle *genparticle = itJet->genParticle();

    if ( genparticle ) {


      const reco::Candidate *mother  = genparticle->mother();

      vars.FillVars(  "Jet_GenParticleFlav" , iJet, genparticle->pdgId()  );
      vars.FillVars(  "Jet_GenParticleMotherId" , iJet , mother->pdgId()   );
      vars.FillVars(  "Jet_GenParticlePt" , iJet , genparticle->pt()  );
      vars.FillVars(  "Jet_GenParticleEta" , iJet , genparticle->eta()  );
    }

    else {

      vars.FillVars(  "Jet_GenParticleFlav" , iJet, -99  );
      vars.FillVars(  "Jet_GenParticleMotherId" , iJet , -99 );
      vars.FillVars(  "Jet_GenParticlePt" , iJet , -1  );
      vars.FillVars(  "Jet_GenParticleEta" , iJet , -11  );
    }



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
    float correction = 1;
    if (jet1.hasUserFloat("bregCorrection")){  correction = jet1.userFloat("bregCorrection");  }
    jet1.scaleEnergy( correction );
    jet1vec.SetPtEtaPhiM(  jet1.pt() , jet1.eta() , jet1.phi() , jet1.mass()  );
  }
  else {
    jet1vec.SetPtEtaPhiM(  jet1.pt() , jet1.eta() , jet1.phi() , jet1.mass()  );
  }
  jet2vec.SetPtEtaPhiM(  jet2.pt() , jet2.eta() , jet2.phi() , jet2.mass()  );
  jet3vec.SetPtEtaPhiM(  jet3.pt() , jet3.eta() , jet3.phi() , jet3.mass()  );

  mass = (jet1vec+jet2vec+jet3vec).M();

  return mass;

}


float QuarkMatchingVarProcessor::GetTopHadMass(const pat::Jet& topJet, const vector<pat::Jet>& WJets, std::string regextention) {

  float mass = 0;

  pat::Jet jet1 = topJet;
  pat::Jet jet2 = WJets.at(0);
  pat::Jet jet3 = WJets.at(1);

  TLorentzVector jet1vec;
  TLorentzVector jet2vec;
  TLorentzVector jet3vec;

  if(jet1.hasUserFloat("bregCorrection"+regextention)){
    float correction = 1;
    correction = jet1.userFloat("bregCorrection"+regextention);
    jet1.scaleEnergy( correction );
    jet1vec.SetPtEtaPhiM(  jet1.pt() , jet1.eta() , jet1.phi() , jet1.mass()  );

    jet2vec.SetPtEtaPhiM(  jet2.pt() , jet2.eta() , jet2.phi() , jet2.mass()  );
    jet3vec.SetPtEtaPhiM(  jet3.pt() , jet3.eta() , jet3.phi() , jet3.mass()  );


    mass = (jet1vec+jet2vec+jet3vec).M();

    return mass;


  }
  else {
    return -10;
  }

}

float QuarkMatchingVarProcessor::GetDijetMass(const pat::Jet& firstjet, const pat::Jet& secondjet, const bool docorrection) {

  float dijetmass = 0;

  TLorentzVector jet1vec;
  TLorentzVector jet2vec;

  pat::Jet jet1 = firstjet;
  pat::Jet jet2 = secondjet;


  if(docorrection){
    float correction1 = 1;
    float correction2 = 1;
    if (jet1.hasUserFloat("bregCorrection")) {  correction1 = jet1.userFloat("bregCorrection");  }
    if (jet2.hasUserFloat("bregCorrection")) {  correction2 = jet2.userFloat("bregCorrection");  }


    jet1.scaleEnergy(correction1);
    jet2.scaleEnergy(correction2);

    jet1vec.SetPtEtaPhiM(  jet1.pt() , jet1.eta() , jet1.phi() , jet1.mass()  );
    jet2vec.SetPtEtaPhiM(  jet2.pt() , jet2.eta() , jet2.phi() , jet2.mass()  );
  }
  else {
    jet1vec.SetPtEtaPhiM(  jet1.pt() , jet1.eta() , jet1.phi() , jet1.mass()  );
    jet2vec.SetPtEtaPhiM(  jet2.pt() , jet2.eta() , jet2.phi() , jet2.mass()  );
  }

  dijetmass = (jet1vec+jet2vec).M();

  return dijetmass;

}



float QuarkMatchingVarProcessor::GetDijetMass(const pat::Jet& firstjet, const pat::Jet& secondjet, std::string regextention) {

  float dijetmass = 0;

  TLorentzVector jet1vec;
  TLorentzVector jet2vec;

  pat::Jet jet1 = firstjet;
  pat::Jet jet2 = secondjet;


  if(jet1.hasUserFloat("bregCorrection"+regextention) && jet2.hasUserFloat("bregCorrection"+regextention)){
    float correction1 = 1;
    float correction2 = 1;
    correction1 = jet1.userFloat("bregCorrection"+regextention);
    correction2 = jet2.userFloat("bregCorrection"+regextention);

    jet1.scaleEnergy(correction1);
    jet2.scaleEnergy(correction2);

    jet1vec.SetPtEtaPhiM(  jet1.pt() , jet1.eta() , jet1.phi() , jet1.mass()  );
    jet2vec.SetPtEtaPhiM(  jet2.pt() , jet2.eta() , jet2.phi() , jet2.mass()  );

    dijetmass = (jet1vec+jet2vec).M();

    return dijetmass;
  }
  else {
    return -10;
  }

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

// For debugging purposes
void QuarkMatchingVarProcessor::PrintTLorentz(TLorentzVector& vec) {

  cout << "pT : " << vec.Pt() << " ";
  cout << "eta: " << vec.Eta() << " ";
  cout << "phi: " << vec.Phi() << " ";
  cout << "M  : " << vec.M() << " ";
  cout << "E  : " << vec.E() << " ";
  cout << endl;

}
