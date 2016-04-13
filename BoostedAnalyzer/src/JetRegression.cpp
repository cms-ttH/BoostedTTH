#include "BoostedTTH/BoostedAnalyzer/interface/JetRegression.hpp"
using namespace std;



//PUBLIC
JetRegression::JetRegression(){
  //Read weightfile and stuff
  name = "BDTG";
 
  for (int i = 0; i < 17; i++){treevars.push_back(0);}
  for (int i = 0; i < 6; i++){treespec.push_back(0);}
  //TMVA Stuff
  reader = new TMVA::Reader();
  
  weightfile = BoostedUtils::GetAnalyzerPath()+"/data/bregweights/weights_breg.xml";  
  
  reader->AddVariable("Jet_Pt",&treevars[0]); 
  reader->AddVariable("Jet_corr",&treevars[1]);
  reader->AddVariable("N_PrimaryVertices",&treevars[2]);
  reader->AddVariable("Jet_Eta",&treevars[3]);
  reader->AddVariable("Jet_Mt",&treevars[4]); 
  reader->AddVariable("Jet_leadTrackPt",&treevars[5]); 
  reader->AddVariable("Jet_leptonPtRel",&treevars[6]);
  reader->AddVariable("Jet_leptonPt",&treevars[7]); 
  reader->AddVariable("Jet_leptonDeltaR",&treevars[8]);
  reader->AddVariable("Jet_totHEFrac",&treevars[9]); 
  reader->AddVariable("Jet_nEmEFrac",&treevars[10]);
  reader->AddVariable("Jet_vtxPt",&treevars[12]);
  reader->AddVariable("Jet_vtxMass",&treevars[13]);
  reader->AddVariable("Jet_vtx3DVal",&treevars[14]);
  reader->AddVariable("Jet_vtxNtracks",&treevars[15]);
  reader->AddVariable("Jet_vtx3DSig",&treevars[16]);
  

  //to be excluded in next training
  reader->AddSpectator("Jet_MatchedPartonPt", &treespec[0]);
  reader->AddSpectator("Jet_MatchedPartonFlav", &treespec[1]);
  reader->AddSpectator("Jet_PartonFlav", &treespec[2]);
  reader->AddSpectator("Jet_Flav" , &treespec[3]);
  reader->AddSpectator("Evt_Odd", &treespec[4]);
  reader->AddSpectator("Evt_Rho", &treespec[5]);
  
  reader->BookMVA(name,weightfile);
  
  //Set Cuts for very loose Electrons and Muons
  epTCut = 5.0;
  eetaCut = 2.5;
  edxyCut = 0.5;
  edzCut = 1.0;
  elostHits = 1.0;
  
  mupTCut = 3.0;
  muetaCut = 2.4;
  mudxyCut = 0.5;
  mudzCut = 1.0;

  deltaR2Max = 0.4*0.4;

  isDone = false;
}

void JetRegression::evaluateRegression (const edm::Event& iEvent,
					const edm::EDGetTokenT< edm::View<pat::Electron> >& electronToken,
					const edm::EDGetTokenT< std::vector<pat::Muon> >& muonToken,
					const edm::EDGetTokenT< reco::VertexCollection>& vertexToken,
					const edm::EDGetTokenT< std::vector<pat::Jet> >& jetToken,
					std::vector<pat::Jet>& Jets){
  
  bool domatchingwithselectedJets = true; //Switch: Which jets should be used for lepton/jet matching  
  bool usejecfactor = true; //Switch: Use jec Factor stored in selected Jets, or caluculate ist from Jet_Pt/Jet_rawPt
  

  edm::Handle< edm::View<pat::Electron> > h_electrons;
  edm::Handle< vector<pat::Muon> > h_muons;
  edm::Handle< vector<pat::Jet> > h_pfjets;
  edm::Handle<reco::VertexCollection> h_vtxs;
  
  iEvent.getByToken(electronToken, h_electrons);
  iEvent.getByToken(muonToken, h_muons);
  iEvent.getByToken(jetToken,h_pfjets);
  iEvent.getByToken(vertexToken, h_vtxs);

  //Select Vertices
  reco::VertexCollection const &vtxs = *h_vtxs;
  reco::VertexCollection Vertices;
  if( h_vtxs.isValid() ){
    for( reco::VertexCollection::const_iterator itvtx = vtxs.begin(); itvtx!=vtxs.end(); ++itvtx ){
      bool isGood = ( !(itvtx->isFake()) &&
		      (itvtx->ndof() >= 4.0) &&
		      (abs(itvtx->z()) <= 24.0) &&
		      (abs(itvtx->position().Rho()) <= 2.0) 
		      );
      if( isGood ) Vertices.push_back(*itvtx);
    }
  }

  vector<pat::Electron> electrons;
  for (size_t i = 0; i < h_electrons->size(); ++i){
    electrons.push_back(h_electrons->at(i));
  }

  vector<pat::Muon> const &muons = *h_muons;
  vector<pat::Jet> const &pfjets = *h_pfjets;
  
  
  if(domatchingwithselectedJets){
    matchLeptonswithJets(electrons, muons, Jets, Vertices);
  }
  else {
    matchLeptonswithJets(electrons, muons, pfjets, Vertices);
  }

  
  //Set variables for regression evaluation
  treevars[2] = Vertices.size();
  for (size_t i = 0; i<Jets.size(); i++) {
    float jetleptoneta = 0;
    treevars[0] = Jets.at(i).pt();
    if(usejecfactor) { treevars[1] = 1.0/Jets.at(i).jecFactor("Uncorrected"); }
    else             { treevars[1] = Jets.at(i).pt()/Jets.at(i).userFloat("Jet_rawPt"); }
    treevars[3] = Jets.at(i).eta();
    treevars[4] = Jets.at(i).mt();
    treevars[5] = leadingTrackpT(Jets.at(i));
    
    //Matched Lepton variables
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
	if(JetMuons.size() > 0){
	  treevars[6] = BoostedUtils::GetTLorentzVector(JetMuons.at(0)->p4()).Perp(TVector3(Jets.at(i).p4().x(),Jets.at(i).p4().y(),Jets.at(i).p4().z()));
	  treevars[7] = JetMuons.at(0)->pt();
	  treevars[8] = BoostedUtils::DeltaR(JetMuons.at(0)->p4(), Jets.at(i).p4());
	  jetleptoneta = JetMuons.at(0)->eta();
	}
	else{
	  treevars[6] = BoostedUtils::GetTLorentzVector(JetElectrons.at(0)->p4()).Perp(TVector3(Jets.at(i).p4().x(),Jets.at(i).p4().y(),Jets.at(i).p4().z()));
	  treevars[7] = JetElectrons.at(0)->pt();
	  treevars[8] = BoostedUtils::DeltaR(JetElectrons.at(0)->p4(), Jets.at(i).p4());    
	  jetleptoneta = JetElectrons.at(0)->eta(); 
	}

      }
    }
    else {
      treevars[6] = -1;
      treevars[7] = -1;
      treevars[8] = -1;
      jetleptoneta = -99;
    }
    
    //Calorimeter variables
    float totHadrFrac = Jets.at(i).neutralHadronEnergyFraction() + Jets.at(i).chargedHadronEnergyFraction();
    if (totHadrFrac > 1) { treevars[9] = 1; }
    else                 { treevars[9] = totHadrFrac; }
    float nEmEFrac = Jets.at(i).neutralEmEnergyFraction();
    if ( nEmEFrac > 1 ) { treevars[10] = 1; }
    else                { treevars[10] = nEmEFrac; }
    
    //Vertex variables
    treevars[11] = sqrt(Jets.at(i).userFloat("vtxPx")*Jets.at(i).userFloat("vtxPx") + Jets.at(i).userFloat("vtxPy")*Jets.at(i).userFloat("vtxPy"));
    treevars[12] = Jets.at(i).userFloat("vtxMass");
    treevars[13] = Jets.at(i).userFloat("vtx3DVal");
    treevars[14] = Jets.at(i).userFloat("vtxNtracks");
    treevars[15] = Jets.at(i).userFloat("vtx3DSig");
    
    //Spectators -> to be removed
    treespec[0] = treespec[1] = treespec[2] =  treespec[3] = treespec[4] = treespec[5] =0;


    //Only do regression for jets, that pass medium CSV workingpoint
    if (BoostedUtils::PassesCSV(Jets.at(i), 'M')){
      float result = (reader->EvaluateRegression(name)).at(0);
      Jets.at(i).addUserFloat("bregCorrection", result);
    }
    //else{
    //  Jets.at(i).addUserFloat("bregCorrection", -99);
    //}
    

    Jets.at(i).addUserFloat("Jet_leadTrackPt",treevars[5]);
    Jets.at(i).addUserFloat("Jet_leptonPtRel",treevars[6]);
    Jets.at(i).addUserFloat("Jet_leptonPt",treevars[7]);
    Jets.at(i).addUserFloat("Jet_leptonDeltaR",treevars[8]);
    Jets.at(i).addUserFloat("Jet_leptonEta",jetleptoneta);

  }
  
  isDone = true;
  
  //Clear Members
  inclusiveElectrons.clear();
  inclusiveMuons.clear();
  ElectronJetPairs.clear();
  MuonJetPairs.clear();

}



//Get Jets, that are scaled with correction factor from b-Regression
vector<pat::Jet> JetRegression::GetRegressedJets(const vector<pat::Jet>& Jets){
  
  vector<pat::Jet> correctedJets;
  for (std::vector<pat::Jet>::const_iterator it = Jets.begin(), ed = Jets.end(); it != ed; ++it ) {
    pat::Jet jet = (*it);
    if ( jet.hasUserFloat("bregCorrection") ) {  jet.scaleEnergy(jet.userFloat("bregCorrection"));  }
    correctedJets.push_back(jet);
  }
  return correctedJets;
}

bool JetRegression::IsRegressionDone(){

  return isDone;

}

//PRIVATE

bool JetRegression::setInclusiveLeptons(const vector<pat::Electron>& electrons, 
					const vector<pat::Muon>& muons,
					const reco::VertexCollection& Vertices){


  float dxy = 0;
  float dz = 0;
  double expectedMissingInnerHits = -999;
  
  
  bool PassesTrack; //Track requirements  
  bool PassesVertex; //Vertex distance cuts
  bool PassesCuts ; //Kinematic cuts
  bool PassesBaseline; //Baseline selections for particel identification
  
  reco::Vertex vtx;

  if(Vertices.size() > 0) { vtx = Vertices.at(0); }
  else { return false; }

  //Electrons
  for(size_t i = 0; i<electrons.size(); i++) {
    
    PassesTrack = false;
    PassesVertex = false;
    PassesCuts = false; 
    PassesBaseline = true; //no special Baseline selection
    
    //Electron selection
    if( electrons[i].gsfTrack().isNonnull()){
      dxy = electrons[i].gsfTrack()->dxy( vtx.position() );
      dz = electrons[i].gsfTrack()->dz( vtx.position() );
      PassesVertex = abs(dxy) < edxyCut && abs(dz) < edzCut;
      expectedMissingInnerHits = electrons[i].gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
      PassesTrack = PassesVertex && expectedMissingInnerHits <= elostHits;						     
    }
    PassesCuts = electrons[i].pt() > epTCut && abs(electrons[i].eta()) < eetaCut;

    if(PassesTrack && PassesCuts && PassesBaseline){  
      inclusiveElectrons.push_back(electrons[i]);  
    }
  } //end loop over electrons
  //Muons
  for (size_t i = 0; i<muons.size(); i++) {
    
    PassesTrack = false;
    PassesVertex = false;
    PassesCuts = false;
    PassesBaseline = false;
    

    //Muon selection
    PassesBaseline = muons[i].isPFMuon() && ( muons[i].isGlobalMuon() || muons[i].isTrackerMuon() );
    
    if(muons[i].muonBestTrack().isAvailable()){
      dxy = muons[i].muonBestTrack()->dxy( vtx.position() );
      dz = muons[i].muonBestTrack()->dz( vtx.position() );
      PassesVertex =  abs(dxy) < mudxyCut && abs(dz) < mudzCut;
      PassesTrack = PassesVertex; //no further track requirements
    }
    
    PassesCuts = muons[i].pt() > mupTCut && abs(muons[i].eta()) < muetaCut;
      
    if( PassesTrack && PassesCuts && PassesBaseline ){  
      inclusiveMuons.push_back(muons[i]); 
    }
  }//end loop over muons
  
  return true;
}

bool JetRegression::matchLeptonswithJets(const vector<pat::Electron>& electrons, 
					 const vector<pat::Muon>& muons,
					 const vector<pat::Jet>& jets,
					 const reco::VertexCollection& Vertices){
  
  if (!setInclusiveLeptons(electrons, muons, Vertices)) { return false; }
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

  return true;
  
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

