#include "BoostedTTH/BoostedAnalyzer/interface/JetRegression.hpp"
using namespace std;



//PUBLIC
JetRegression::JetRegression(){
  //Read weightfile and stuff
  name = "BDTG";
  weightfile = "/afs/desy.de/user/h/hmildner/public/regression_weights/weights_ttbar_quark/TMVARegression_BDTG.weights.xml";
  for (int i = 0; i < 17; i++){treevars.push_back(0);}
  //TMVA Stuff
  reader = new TMVA::Reader();
 
  reader->AddVariable("Jet_pt",&treevars[0]); 
  reader->AddVariable("Jet_corr",&treevars[1]);
  reader->AddVariable("rho",&treevars[2]);
  reader->AddVariable("Jet_eta",&treevars[3]);
  reader->AddVariable("Jet_mt",&treevars[4]); 
  reader->AddVariable("Jet_leadTrackPt",&treevars[5]); 
  reader->AddVariable("Jet_leptonPtRel",&treevars[6]);
  reader->AddVariable("Jet_leptonPt",&treevars[7]); 
  reader->AddVariable("Jet_leptonDeltaR",&treevars[8]);
  reader->AddVariable("Jet_neHEF",&treevars[9]); 
  reader->AddVariable("Jet_neEmEF",&treevars[10]);
  reader->AddVariable("Jet_chMult",&treevars[11]);
  reader->AddVariable("Jet_vtxPt",&treevars[12]);
  reader->AddVariable("Jet_vtxMass",&treevars[13]);
  reader->AddVariable("Jet_vtx3dL",&treevars[14]);
  reader->AddVariable("Jet_vtxNtrk",&treevars[15]);
  reader->AddVariable("Jet_vtx3deL",&treevars[16]);
 
  reader->BookMVA(name,weightfile);
  
  //Set Cuts
  epTCut = 5.0;
  eetaCut = 2.5;
  edxyCut = 0.5;
  edzCut = 1.0;

  mupTCut = 3.0;
  muetaCut = 2.4;
  mudxyCut = 0.5;
  mudzCut = 1.0;

  deltaR2Max = 0.4*0.4;
}

void JetRegression::evaluateRegression (const edm::Event& iEvent,
					const edm::EDGetTokenT< edm::View<pat::Electron> >& electronToken,
					const edm::EDGetTokenT< std::vector<pat::Muon> >& muonToken,
					const edm::EDGetTokenT <double>& rhoToken,
					const edm::EDGetTokenT< std::vector<pat::Jet> >& jetToken,
					std::vector<pat::Jet>& Jets){


  bool domatchingwithselectedJets = true;   //Switch: Which jets should be used for lepton/jet matching  

  edm::Handle< edm::View<pat::Electron> > h_electrons;
  edm::Handle< vector<pat::Muon> > h_muons;
  edm::Handle< vector<pat::Jet> > h_pfjets;
  edm::Handle<double> h_rho;
  
  iEvent.getByToken(electronToken, h_electrons);
  iEvent.getByToken(muonToken, h_muons);
  iEvent.getByToken(jetToken,h_pfjets);
  iEvent.getByToken(rhoToken,h_rho);

  vector<pat::Electron> electrons;
  for (size_t i = 0; i < h_electrons->size(); ++i){
    electrons.push_back(h_electrons->at(i));
  }

  vector<pat::Muon> const &muons = *h_muons;
  vector<pat::Jet> const &pfjets = *h_pfjets;


  if(domatchingwithselectedJets){
    matchLeptonswithJets(electrons, muons, Jets); 
  }
  else {
    matchLeptonswithJets(electrons, muons, pfjets);
  }
  //Set variables for regression evaluation
  //cout << endl << "run/event " << iEvent.eventAuxiliary().run() << " / " << iEvent.eventAuxiliary().event() << endl;
  treevars[2] = (float)(*h_rho);
  for (size_t i = 0; i<Jets.size(); i++) {
    //if (abs(Jets.at(i).hadronFlavour()) == 5){
    if (true){
      //cout << "Jet: " << i << endl;
      //cout << "jet pT: " <<  Jets.at(i).pt() << endl;

      treevars[0] = Jets.at(i).pt();
      treevars[1] = 1.0/Jets.at(i).jecFactor("Uncorrected");
      treevars[3] = Jets.at(i).eta();
      treevars[4] = Jets.at(i).mt();
      treevars[5] = leadingTrackpT(Jets.at(i));
      if (!(ElectronJetPairs.empty()) || !(MuonJetPairs.empty())) {	
	vector<pat::Electron*> JetElectrons; 
	vector<pat::Muon*> JetMuons;
	float jeta = Jets.at(i).eta();
	float jphi = Jets.at(i).phi();
	float jcharge = Jets.at(i).charge();
	float jflav = Jets.at(i).hadronFlavour();
	for(map<pat::Electron*, const pat::Jet*>::iterator eit= ElectronJetPairs.begin(); eit != ElectronJetPairs.end(); eit++) {
	  float eeta = eit->second->eta();
	  float ephi = eit->second->phi();
	  float echarge = eit->second->charge();
	  float eflav = eit->second->hadronFlavour();
	  if( eeta == jeta  && ephi == jphi && 
	      echarge == jcharge && eflav == jflav ){
	    JetElectrons.push_back(eit->first);
	  }
	}
	for(map<pat::Muon*, const pat::Jet*>::iterator mit= MuonJetPairs.begin(); mit != MuonJetPairs.end(); mit++) {
	  float meta = mit->second->eta();
	  float mphi = mit->second->phi();
	  float mcharge = mit->second->charge();
	  float mflav = mit->second->hadronFlavour();
	  if( meta == jeta  && mphi == jphi && 
	      mcharge == jcharge && mflav == jflav ){
	    JetMuons.push_back(mit->first);
	  }
	}
	if(JetElectrons.size() > 0 || JetMuons.size() > 0){
	  if(JetElectrons.size() > 0){
	    treevars[6] = BoostedUtils::GetTLorentzVector(JetElectrons.at(0)->p4()).Perp(TVector3(Jets.at(i).p4().x(),Jets.at(i).p4().y(),Jets.at(i).p4().z()));
	    treevars[7] = JetElectrons.at(0)->pt();
	    treevars[8] = BoostedUtils::DeltaR(JetElectrons.at(0)->p4(), Jets.at(i).p4());
	  }
	  else{
	    treevars[6] = BoostedUtils::GetTLorentzVector(JetMuons.at(0)->p4()).Perp(TVector3(Jets.at(i).p4().x(),Jets.at(i).p4().y(),Jets.at(i).p4().z()));
	    treevars[7] = JetMuons.at(0)->pt();
	    treevars[8] = BoostedUtils::DeltaR(JetMuons.at(0)->p4(), Jets.at(i).p4());
	  }

	}
      }
      else {
	treevars[6] = -99;
	treevars[7] = -99;
	treevars[8] = -99;
      }
      
      treevars[9] = Jets.at(i).neutralHadronEnergyFraction();
      treevars[10] = Jets.at(i).neutralEmEnergyFraction();
      treevars[11] = Jets.at(i).chargedMultiplicity();
      treevars[12] = sqrt(Jets.at(i).userFloat("vtxPx")*Jets.at(i).userFloat("vtxPx") + Jets.at(i).userFloat("vtxPy")*Jets.at(i).userFloat("vtxPy"));
      treevars[13] = Jets.at(i).userFloat("vtxMass");
      treevars[14] = Jets.at(i).userFloat("vtx3DVal");
      treevars[15] = Jets.at(i).userFloat("vtxNtracks");
      treevars[16] = Jets.at(i).userFloat("vtx3DSig");

      //Only do regression for b-jets
      if (abs(Jets.at(i).hadronFlavour()) == 5){
	float result = (reader->EvaluateRegression(name)).at(0);
	Jets.at(i).addUserFloat("jetregressionPT", result);
      }
      else{
	Jets.at(i).addUserFloat("jetregressionPT", -99);
      }
      Jets.at(i).addUserFloat("Jet_leadTrackPt",treevars[5]);
      Jets.at(i).addUserFloat("Jet_leptonPtRel",treevars[6]);
      Jets.at(i).addUserFloat("Jet_leptonPt",treevars[7]);
      Jets.at(i).addUserFloat("Jet_leptonDeltaR",treevars[8]);

    }
  }

  //Clear Members
  inclusiveElectrons.clear();
  inclusiveMuons.clear();
  ElectronJetPairs.clear();
  MuonJetPairs.clear();
}




//PRIVATE

void JetRegression::setInclusiveLeptons(const vector<pat::Electron>& electrons, 
					const vector<pat::Muon>& muons){
  float dxy;
  float dz;
  //Electrons
  for(size_t i = 0; i<electrons.size(); i++) {
    if(electrons[i].gsfTrack().isNonnull()){
      dxy = electrons[i].gsfTrack()->dxy();
      dz = electrons[i].gsfTrack()->dz();
      if(electrons[i].pt() > epTCut && electrons[i].eta() < eetaCut && abs(dxy) < edxyCut && abs(dz) < edzCut){
	inclusiveElectrons.push_back(electrons[i]);
      }
    }
  }
  //Muons
  for (size_t i = 0; i<muons.size(); i++) {
    if(muons[i].track().isNonnull()){
      dxy = muons[i].track()->dxy();
      dz = muons[i].track()->dz();
      if(muons[i].pt() > mupTCut && muons[i].eta() < muetaCut && abs(dxy) < mudxyCut && abs(dz) < mudzCut){
	inclusiveMuons.push_back(muons[i]);
      }
    }
  }
}

void JetRegression::matchLeptonswithJets(const vector<pat::Electron>& electrons, 
					 const vector<pat::Muon>& muons,
					 const vector<pat::Jet>& jets){
  setInclusiveLeptons(electrons, muons);
  //Match Electrons with Jets  
  for (size_t i = 0; i < inclusiveElectrons.size(); i++) {
    float deltaR2Min = 10000000;
    int jmatch = -1;
    for(size_t j = 0; j < jets.size(); j++) {
      float dRlj = BoostedUtils::DeltaR(inclusiveElectrons[i].p4(), jets[j].p4());
      float dR2lj = dRlj*dRlj;
      if (dR2lj < deltaR2Min){
	deltaR2Min = dR2lj;
	jmatch = j;
      }
    }
    if (deltaR2Min < deltaR2Max && jmatch != -1){
      ElectronJetPairs[&(inclusiveElectrons[i])] = &(jets[jmatch]);
    }
  }
  //Match Muons with Jets
  for (size_t i = 0; i < inclusiveMuons.size(); i++) {
    float deltaR2Min = 10000000;
    int jmatch = -1;
    for(size_t j = 0; j < jets.size(); j++) {
      float dRlj = BoostedUtils::DeltaR(inclusiveMuons[i].p4(), jets[j].p4());
      float dR2lj = dRlj*dRlj;
      if (dR2lj < deltaR2Min){
	deltaR2Min = dR2lj;
	jmatch = j;
      }
    }
    if (deltaR2Min < deltaR2Max && jmatch != -1){
      MuonJetPairs[&(inclusiveMuons[i])] = &(jets[jmatch]);
    }
  }
}


float JetRegression::leadingTrackpT(const pat::Jet& jet) {
  float maxpt = 0;
  for(size_t i = 0; i < jet.daughterPtrVector().size(); i++) {
    if(jet.daughterPtrVector().at(i).get()->pt() > maxpt && jet.daughterPtrVector().at(i).get()->charge() != 0){
      maxpt = jet.daughterPtrVector().at(i).get()->pt();
    }
  }
  return maxpt;
}

