#include "BoostedTTH/BoostedAnalyzer/interface/JetRegression.hpp"
using namespace std;



//PUBLIC

JetRegression::JetRegression(  ){

  //Set Cuts for soft Electrons and Muons
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

  //Initialize
  isDone = false;
  isInitialized = false;
  isEvaluated = false;
  tightLeptonssSet = false;
  returnsoftLeptons = false;

  //Settings
  excludetightLeptons = false; //Switch: Should the tight electron or muon be excluded from inclusive Leptons for b-Jet Regression
  debugmode = false;

  for (int i = 0; i < 16; i++){treevars.push_back(0);}

}

JetRegression::~JetRegression(  ){}

bool JetRegression::SetLeptonCuts(  vector< double > electronCuts,
                                    vector< double > muonCuts,
                                    double ljDr){

    epTCut = electronCuts[0];
    eetaCut = electronCuts[1];
    edxyCut = electronCuts[2];
    edzCut = electronCuts[3];
    elostHits = electronCuts[4];

    mupTCut = muonCuts[0];
    muetaCut = muonCuts[1];
    mudxyCut = muonCuts[2];
    mudzCut = muonCuts[3];

    deltaR2Max = ljDr*ljDr;

    return true;
}

bool JetRegression::init(  std::string weightname , double minpT ){
  if (  isRegressionInitialized()  ) { return false; }

  minpTs.push_back(minpT) ;

  string name  = "BDTG";

  //TMVA Stuff
  readermap[name] = new TMVA::Reader();

  string weightfile = BoostedUtils::GetAnalyzerPath()+"/data/bregweights/"+weightname;

  cout << "Weight for regression: " << weightfile << endl;

  readermap[name]->AddVariable("Jet_Pt",&treevars[0]);
  readermap[name]->AddVariable("Jet_corr",&treevars[1]);
  readermap[name]->AddVariable("N_PrimaryVertices",&treevars[2]);
  readermap[name]->AddVariable("Jet_Eta",&treevars[3]);
  readermap[name]->AddVariable("Jet_Mt",&treevars[4]);
  readermap[name]->AddVariable("Jet_leadTrackPt",&treevars[5]);
  readermap[name]->AddVariable("Jet_leptonPtRel",&treevars[6]);
  readermap[name]->AddVariable("Jet_leptonPt",&treevars[7]);
  readermap[name]->AddVariable("Jet_leptonDeltaR",&treevars[8]);
  readermap[name]->AddVariable("Jet_totHEFrac",&treevars[9]);
  readermap[name]->AddVariable("Jet_nEmEFrac",&treevars[10]);
  readermap[name]->AddVariable("Jet_vtxPt",&treevars[11]);
  readermap[name]->AddVariable("Jet_vtxMass",&treevars[12]);
  readermap[name]->AddVariable("Jet_vtx3DVal",&treevars[13]);
  readermap[name]->AddVariable("Jet_vtxNtracks",&treevars[14]);
  readermap[name]->AddVariable("Jet_vtx3DSig",&treevars[15]);

  readermap[name]->BookMVA("BDTG",weightfile);

  regressionnames.push_back(name);

  isInitialized = true;

  return true;
}



//TODO: Add flag, that extention will be used in in evaluation.
bool JetRegression::init(  std::string weightname, std::string extention, double minpT ){
  if (  isRegressionInitialized()  ) { return false; }

  minpTs.push_back(minpT) ;

  string name  = extention;

  //TMVA Stuff
  readermap[name] = new TMVA::Reader();

  string weightfile = BoostedUtils::GetAnalyzerPath()+"/data/bregweights/"+weightname;

  cout << "Weight for regression: " << weightfile << endl;

  readermap[name]->AddVariable("Jet_Pt",&treevars[0]);
  readermap[name]->AddVariable("Jet_corr",&treevars[1]);
  readermap[name]->AddVariable("N_PrimaryVertices",&treevars[2]);
  readermap[name]->AddVariable("Jet_Eta",&treevars[3]);
  readermap[name]->AddVariable("Jet_Mt",&treevars[4]);
  readermap[name]->AddVariable("Jet_leadTrackPt",&treevars[5]);
  readermap[name]->AddVariable("Jet_leptonPtRel",&treevars[6]);
  readermap[name]->AddVariable("Jet_leptonPt",&treevars[7]);
  readermap[name]->AddVariable("Jet_leptonDeltaR",&treevars[8]);
  readermap[name]->AddVariable("Jet_totHEFrac",&treevars[9]);
  readermap[name]->AddVariable("Jet_nEmEFrac",&treevars[10]);
  readermap[name]->AddVariable("Jet_vtxPt",&treevars[11]);
  readermap[name]->AddVariable("Jet_vtxMass",&treevars[12]);
  readermap[name]->AddVariable("Jet_vtx3DVal",&treevars[13]);
  readermap[name]->AddVariable("Jet_vtxNtracks",&treevars[14]);
  readermap[name]->AddVariable("Jet_vtx3DSig",&treevars[15]);

  readermap[name]->BookMVA("BDTG",weightfile);

  regressionnames.push_back(name);

  isInitialized = true;

  return true;
}


bool JetRegression::init(  std::vector< std::string > WeightFiles, std::vector<std::vector < bool > >  WeightInputs, std::vector < std::string > names , std::vector< double >  minpT){
  if (  isRegressionInitialized()  ) { return false; }

  for( size_t iw = 0 ; iw < WeightFiles.size() ; iw++ ) {
    minpTs.push_back(minpT[iw]) ;

    string name = names.at(iw);

    vector< bool > usevars = WeightInputs.at(iw);

    //TMVA Stuff
    readermap[name] = new TMVA::Reader();

    string weightfile = BoostedUtils::GetAnalyzerPath()+"/data/bregweights/"+WeightFiles.at(iw);

    cout << "Weight for regression: " <<  weightfile  << endl;


    if( usevars[0]  ) {   readermap[name]->AddVariable("Jet_Pt",&treevars[0]);  }
    if( usevars[1]  ) {   readermap[name]->AddVariable("Jet_corr",&treevars[1]);  }
    if( usevars[2]  ) {   readermap[name]->AddVariable("N_PrimaryVertices",&treevars[2]);  }
    if( usevars[3]  ) {   readermap[name]->AddVariable("Jet_Eta",&treevars[3]);  }
    if( usevars[4]  ) {   readermap[name]->AddVariable("Jet_Mt",&treevars[4]);  }
    if( usevars[5]  ) {   readermap[name]->AddVariable("Jet_leadTrackPt",&treevars[5]);  }
    if( usevars[6]  ) {   readermap[name]->AddVariable("Jet_leptonPtRel",&treevars[6]);  }
    if( usevars[7]  ) {   readermap[name]->AddVariable("Jet_leptonPt",&treevars[7]);  }
    if( usevars[8]  ) {   readermap[name]->AddVariable("Jet_leptonDeltaR",&treevars[8]);  }
    if( usevars[9]  ) {   readermap[name]->AddVariable("Jet_totHEFrac",&treevars[9]);  }
    if( usevars[10] ) {   readermap[name]->AddVariable("Jet_nEmEFrac",&treevars[10]);  }
    if( usevars[11] ) {   readermap[name]->AddVariable("Jet_vtxPt",&treevars[11]);  }
    if( usevars[12] ) {   readermap[name]->AddVariable("Jet_vtxMass",&treevars[12]);  }
    if( usevars[13] ) {   readermap[name]->AddVariable("Jet_vtx3DVal",&treevars[13]);  }
    if( usevars[14] ) {   readermap[name]->AddVariable("Jet_vtxNtracks",&treevars[14]);  }
    if( usevars[15] ) {   readermap[name]->AddVariable("Jet_vtx3DSig",&treevars[15]);  }

    readermap[name]->BookMVA("BDTG",weightfile);

    regressionnames.push_back(name);

  }




  isInitialized = true;

  return true;
}


void JetRegression::evaluateRegression (const edm::Event& iEvent,
                    					const edm::EDGetTokenT< edm::View<pat::Electron> >& electronToken,
                    					const edm::EDGetTokenT< std::vector<pat::Muon> >& muonToken,
                    					const edm::EDGetTokenT< reco::VertexCollection>& vertexToken,
                    					std::vector<pat::Jet>& Jets){


  bool doevaluation = true;
  if ( !isRegressionInitialized() ) {
    cout << "Regression was not initialized. Only ínputvariables will be set" << endl;
    doevaluation = false;
  }

  bool usejecfactorfromHelper = true;

  edm::Handle< edm::View<pat::Electron> > h_electrons;
  edm::Handle< vector<pat::Muon> > h_muons;
  edm::Handle<reco::VertexCollection> h_vtxs;

  iEvent.getByToken(electronToken, h_electrons);
  iEvent.getByToken(muonToken, h_muons);
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





  matchLeptonswithJets(electrons, muons, Jets, Vertices);


  //Set variables for regression evaluation
  treevars[2] = Vertices.size();
  for (size_t i = 0; i<Jets.size(); i++) {
    float jetleptoneta = 0;
    treevars[0] = Jets.at(i).pt();
    if(usejecfactorfromHelper) {
      treevars[1] = ( Jets.at(i).userFloat("L3Correction") );
    }
    else {
      //Divide by L3Absolute, because Data has additional residual correction. For MC L3Absolute is 1.0, so no changes there
      treevars[1] = 1.0/( Jets.at(i).jecFactor("Uncorrected") / Jets.at(i).jecFactor("L3Absolute") );
    }
    treevars[3] = Jets.at(i).eta();
    treevars[4] = Jets.at(i).mt();
    treevars[5] = leadingTrackpT(Jets.at(i));

    int nmatchedleptons = 0;
    int nmatchedelectrons = 0;
    int nmatchedmuons = 0;
    //Matched Lepton variables
    //cout << ElectronJetPairs.empty() << " " << MuonJetPairs.empty() << endl;
    if (!(ElectronJetPairs.empty()) || !(MuonJetPairs.empty())) {

     if( debugmode ) {
       cout << endl << "#############################################################" << endl;
       for(auto t : ElectronJetPairs) {
	 std::cout << t.first << " " << t.second << "\n";
	 std::cout << t.first->pt()  << " " << t.second->pt() << "\n";
       }
       cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
       for(auto t : MuonJetPairs) {
	 std::cout << t.first << " " << t.second << "\n";
	 std::cout << t.first->pt() << " " << t.second->pt() << "\n";
       }
       cout << "#############################################################" << endl<< endl;
     }

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
       nmatchedleptons = JetElectrons.size() + JetMuons.size();
       nmatchedmuons = JetMuons.size();
       nmatchedelectrons = JetElectrons.size();
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
     else {
       treevars[6] = -1;
       treevars[7] = -1;
       treevars[8] = -1;
       jetleptoneta = -99;
     }
    }
    else {
      treevars[6] = -1;
      treevars[7] = -1;
      treevars[8] = -1;
      jetleptoneta = -99;
    }
    //Calorimeter variables
    float totHadrFrac = (Jets.at(i).neutralHadronEnergyFraction() + Jets.at(i).chargedHadronEnergyFraction());
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

    if( debugmode ) {
      cout << "Regression input variables" << endl;
      for (size_t v = 0 ; v < treevars.size() ; v++) { cout << " | " << treevars[v]; }
      cout << endl;
    }

    //Only do regression for jets, that pass medium CSV workingpoint
    if(  doevaluation  ) {
      if (BoostedUtils::PassesCSV(Jets.at(i), 'M')){
	for ( size_t nt = 0; nt < regressionnames.size(); nt++  ) {
	  // First regression in list, always gets unserfloat without extention
	  float_t result = 0;
	  if ( nt == 0 ) {
        if(Jets.at(i).pt() >= minpTs[nt]){
    	    result = readermap[regressionnames[nt]]->EvaluateRegression(0,"BDTG");
    	    if( debugmode ) { cout << "Regression " << nt << ": pt: " << treevars[0] << " regcorr: " << result  << endl; }
    	    Jets.at(i).addUserFloat("bregCorrection", result);
        }
	  }
	  else {
        if(Jets.at(i).pt() >= minpTs[nt]) {
    	    result = (readermap[regressionnames[nt]]->EvaluateRegression(0,"BDTG"));
    	    if( debugmode ) { cout << "Regression " << nt << "( " << regressionnames[nt] << " )"  << ": pt: " << treevars[0]<< " regcorr: " << result << endl; }
    	    Jets.at(i).addUserFloat("bregCorrection_"+regressionnames[nt], result); //append name of regression to userfloat
        }
	  }
	}
      }
      isEvaluated = true;
    }
    else {
      isEvaluated = false;
    }
    //else{
    //  Jets.at(i).addUserFloat("bregCorrection", -99);
    //}

    //cout << "setting userFloats"  << " " << nmatchedleptons << " " << nmatchedelectrons << " " << nmatchedmuons <<endl;
    Jets.at(i).addUserFloat("Jet_leadTrackPt",treevars[5]);
    Jets.at(i).addUserFloat("Jet_leptonPtRel",treevars[6]);
    Jets.at(i).addUserFloat("Jet_leptonPt",treevars[7]);
    Jets.at(i).addUserFloat("Jet_leptonDeltaR",treevars[8]);
    Jets.at(i).addUserFloat("Jet_leptonEta",jetleptoneta);
    Jets.at(i).addUserFloat("Jet_NmatchsoftLeptons",nmatchedleptons);
    Jets.at(i).addUserFloat("Jet_NmatchsoftElectrons",nmatchedelectrons);
    Jets.at(i).addUserFloat("Jet_NmatchsoftMuons",nmatchedmuons);
  }

  isDone = true;


  //Clear Members
  inclusiveElectrons.clear();
  inclusiveMuons.clear();
  ElectronJetPairs.clear();
  MuonJetPairs.clear();

}



void JetRegression::evaluateRegression (const edm::Event& iEvent,
                    					const edm::EDGetTokenT< edm::View<pat::Electron> >& electronToken,
                    					const edm::EDGetTokenT< std::vector<pat::Muon> >& muonToken,
                    					const edm::EDGetTokenT< reco::VertexCollection>& vertexToken,
                    					std::vector<pat::Jet>& Jets,
                    					const std::string prefix,
                    					const bool isadditionaltraining){


  bool doevaluation = true;
  if ( !isRegressionInitialized() ) {
    cout << "Regression was not initialized. Only ínputvariables will be set" << endl;
    doevaluation = false;
  }
  bool usejecfactorfromHelper = true;

  edm::Handle< edm::View<pat::Electron> > h_electrons;
  edm::Handle< vector<pat::Muon> > h_muons;
  edm::Handle<reco::VertexCollection> h_vtxs;

  iEvent.getByToken(electronToken, h_electrons);
  iEvent.getByToken(muonToken, h_muons);
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




  matchLeptonswithJets(electrons, muons, Jets, Vertices);


  //Set variables for regression evaluation
  treevars[2] = Vertices.size();
  for (size_t i = 0; i<Jets.size(); i++) {
    float jetleptoneta = 0;
    treevars[0] = Jets.at(i).pt();
    if (usejecfactorfromHelper){
      treevars[1] = ( Jets.at(i).userFloat("L3Correction") );
    }
    else {
      //Divide by L3Absolute, because Data has additional residual correction. For MC L3Absolute is 1.0, so no changes there
      treevars[1] = 1.0/( Jets.at(i).jecFactor("Uncorrected") / Jets.at(i).jecFactor("L3Absolute") );
    }
    treevars[3] = Jets.at(i).eta();
    treevars[4] = Jets.at(i).mt();
    treevars[5] = leadingTrackpT(Jets.at(i));

    int nmatchedleptons = 0;
    int nmatchedelectrons = 0;
    int nmatchedmuons = 0;
    //Matched Lepton variables
    //cout << ElectronJetPairs.empty() << " " << MuonJetPairs.empty() << endl;
    if (!(ElectronJetPairs.empty()) || !(MuonJetPairs.empty())) {

     if( debugmode ) {
       cout << endl << "#############################################################" << endl;
       for(auto t : ElectronJetPairs) {
	 std::cout << t.first << " " << t.second << "\n";
	 std::cout << t.first->pt()  << " " << t.second->pt() << "\n";
       }
       cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
       for(auto t : MuonJetPairs) {
	 std::cout << t.first << " " << t.second << "\n";
	 std::cout << t.first->pt() << " " << t.second->pt() << "\n";
       }
       cout << "#############################################################" << endl<< endl;
     }

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
       nmatchedleptons = JetElectrons.size() + JetMuons.size();
       nmatchedmuons = JetMuons.size();
       nmatchedelectrons = JetElectrons.size();
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
     else {
       treevars[6] = -1;
       treevars[7] = -1;
       treevars[8] = -1;
       jetleptoneta = -4;
     }
    }
    else {
      treevars[6] = -1;
      treevars[7] = -1;
      treevars[8] = -1;
      jetleptoneta = -4;
    }
    //Calorimeter variables
    float totHadrFrac = 0;
    float nEmEFrac = 0;

    if (prefix == ""){
      totHadrFrac = (Jets.at(i).neutralHadronEnergyFraction() + Jets.at(i).chargedHadronEnergyFraction());
      nEmEFrac = Jets.at(i).neutralEmEnergyFraction();
    }
    else if (prefix == "id"){
      totHadrFrac = ( Jets.at(i).userFloat("idJetnhadEfrac") + Jets.at(i).userFloat("idJetchhadEfrac") );
      nEmEFrac = Jets.at(i).userFloat("idJetnemEfrac") ;
    }
    treevars[9] = totHadrFrac;
    treevars[10] = nEmEFrac;
    if ( totHadrFrac > 1 ) { treevars[9] = 1; }
    if (    nEmEFrac > 1 ) { treevars[10] = 1; }

    //Vertex variables
    treevars[11] = sqrt(Jets.at(i).userFloat("vtxPx")*Jets.at(i).userFloat("vtxPx") + Jets.at(i).userFloat("vtxPy")*Jets.at(i).userFloat("vtxPy"));
    treevars[12] = Jets.at(i).userFloat("vtxMass");
    treevars[13] = Jets.at(i).userFloat("vtx3DVal");
    treevars[14] = Jets.at(i).userFloat("vtxNtracks");
    treevars[15] = Jets.at(i).userFloat("vtx3DSig");

    if( debugmode ) {
      cout << "Regression input variables" << endl;
      for (size_t v = 0 ; v < treevars.size() ; v++) { cout << " | " << treevars[v]; }
      cout << endl;
    }

    //Only do regression for jets, that pass medium CSV workingpoint
    if(  doevaluation  ) {
      if (BoostedUtils::PassesCSV(Jets.at(i), 'M')){
	for ( size_t nt = 0; nt < regressionnames.size(); nt++  ) {
	  // First regression in list, always gets unserfloat without extention
	  float_t result = 0;
	  if ( nt == 0 && !isadditionaltraining) {
	    result = readermap[regressionnames[nt]]->EvaluateRegression(0,"BDTG");
	    if( debugmode ) { cout << "Regression " << nt << ": pt: " << treevars[0] << " regcorr: " << result  << endl; }
	    Jets.at(i).addUserFloat("bregCorrection", result);
	  }
	  else {
	    result = (readermap[regressionnames[nt]]->EvaluateRegression(0,"BDTG"));
	    if( debugmode ) { cout << "Regression " << nt << "( " << regressionnames[nt] << " )"  << ": pt: " << treevars[0]<< " regcorr: " << result << endl; }
	    Jets.at(i).addUserFloat("bregCorrection_"+regressionnames[nt], result); //append name of regression to userfloat
	  }
	}
      }
      isEvaluated = true;
    }
    else {
      isEvaluated = false;
    }

    if (!isadditionaltraining){
      Jets.at(i).addUserFloat("Jet_leadTrackPt",treevars[5]);
      Jets.at(i).addUserFloat("Jet_leptonPtRel",treevars[6]);
      Jets.at(i).addUserFloat("Jet_leptonPt",treevars[7]);
      Jets.at(i).addUserFloat("Jet_leptonDeltaR",treevars[8]);
      Jets.at(i).addUserFloat("Jet_leptonEta",jetleptoneta);
      Jets.at(i).addUserFloat("Jet_NmatchsoftLeptons",nmatchedleptons);
      Jets.at(i).addUserFloat("Jet_NmatchsoftElectrons",nmatchedelectrons);
      Jets.at(i).addUserFloat("Jet_NmatchsoftMuons",nmatchedmuons);
    }
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
    if ( jet.hasUserFloat("bregCorrection") ) {
    jet.addUserFloat("unregressedpT", jet.pt());
        jet.scaleEnergy(jet.userFloat("bregCorrection"));
    }
    correctedJets.push_back(jet);
  }
  return correctedJets;
}

void JetRegression::setTightLeptons(const std::vector< pat::Muon >& muons,
		     const std::vector< pat::Electron >& electrons){

  tightElectrons = electrons;
  tightMuons = muons;

  tightLeptonssSet = true;

}

void JetRegression::getSoftLeptons(std::vector< pat:: Muon >& muons,
				   std::vector< pat:: Electron>& electrons) {

  //cout <<"inreg"  << &muons << " " << &returnMuons << endl;

  muons = returnMuons;
  electrons = returnElectrons;

  returnMuons.clear();
  returnElectrons.clear();


  returnsoftLeptons = true;

}


bool JetRegression::isRegressionDone(){

  return isDone;

}


bool JetRegression::isRegressionInitialized(){

  return isInitialized;

}

bool JetRegression::isRegressionEvaluated(){

  return isEvaluated;

}

void JetRegression::activateDebugMode() {

  cout << "Debug mode for regression activated" << endl;

  debugmode = true;

}

void JetRegression::matchGenJetstoJets( vector< pat::Jet >& Jets,
					vector< reco::GenJet >& GenJets ){

  GenJetMatcher matcher;
  matcher.init( 0.4 );

  map< pat::Jet* , reco::GenJet* > matches = matcher.match( Jets, GenJets );

  for( auto& Jet: Jets) {
    if ( matches.find(&Jet) != matches.end() ){
      Jet.addUserFloat("matchedGenJetwNuPt", matches[&Jet]->pt() );
      Jet.addUserFloat("matchedGenJetwNuEta", matches[&Jet]->eta() );
      Jet.addUserFloat("matchedGenJetwNuPhi", matches[&Jet]->phi() );
      Jet.addUserFloat("matchedGenJetwNuM", matches[&Jet]->mass() );
      //cout << "matching " <<Jet.pt() << " to"<<  endl;
      //cout << matches[&Jet]->pt() <<  " with DR of " << BoostedUtils::DeltaR(Jet.p4(), matches[&Jet]->p4()) << endl;
    }
  }
}

//PRIVATE

bool JetRegression::setInclusiveLeptons(  const vector<pat::Electron>& electrons,
					  const vector<pat::Muon>& muons,
					  const reco::VertexCollection& Vertices  ){


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
  //cout << "All electrons: " << electrons.size() << endl;

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
  //cout << "All muons: " << muons.size() << endl;
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

    //cout << "Muon " << i << " " << PassesTrack << " " << PassesCuts << " " <<  PassesBaseline << endl;

    if( PassesTrack && PassesCuts && PassesBaseline ){
      inclusiveMuons.push_back(muons[i]);
    }
  }//end loop over muons

  return true;
}

bool JetRegression::matchLeptonswithJets(const vector<pat::Electron>& raw_electrons,
					 const vector<pat::Muon>& raw_muons,
					 const vector<pat::Jet>& jets,
					 const reco::VertexCollection& Vertices){

  vector< pat::Electron > electrons;
  vector< pat::Muon > muons;


  //cout << raw_electrons.size() << " | " << raw_muons.size() << " | " << jets.size() << endl;

  //Exclude tight leptons form inclusive Leptons:
  if( tightLeptonssSet ){
    vector< pat::Electron > electrons_;
    vector< pat::Muon > muons_;

    //Electrons
    if (  tightElectrons.size() > 0  ){
      for (  size_t j = 0 ; j  < raw_electrons.size() ; j++  ) {
	for (  size_t i = 0 ; i  < tightElectrons.size() ; i++  ) {
	  if (  tightElectrons.at(i).eta() != raw_electrons.at(j).eta() || tightElectrons.at(i).phi() !=  raw_electrons.at(j).phi()  ) {
	    electrons_.push_back(raw_electrons.at(j));
	  }
	}// end tight electron loop
      }//end inlc. electron loop
    }
    else {
      for (  size_t j = 0 ; j  < raw_electrons.size() ; j++  ) {
	electrons_.push_back(raw_electrons.at(j));
      }// end incl electron loop
    }
    //Muons
    if (  tightMuons.size() > 0  ) {
      for (  size_t j = 0 ; j  < raw_muons.size() ; j++  ) {
	for (  size_t i = 0 ; i  < tightMuons.size() ; i++  ) {
	  if (  tightMuons.at(i).eta() != raw_muons.at(j).eta() || tightMuons.at(i).phi() !=  raw_muons.at(j).phi()  ) {
	    muons_.push_back(raw_muons.at(j));
	  }
	}// end tight muon loop
      }//end inlc. muon loop
    }
    else {
      for (  size_t j = 0 ; j  < raw_muons.size() ; j++  ) {
	muons_.push_back(raw_muons.at(j));
      }//end inlc. muon loop
    }
    //Save soft Leptons for extraction in Analyzer
    if (returnsoftLeptons){
      returnElectrons = electrons_;
      returnMuons = muons_;

    }
    //if tght leptons should be excluded from leptons for matching save only soft leptons as leptons
    if( excludetightLeptons ){

      muons = muons_;
      electrons = electrons_;

    }
  }
  if(!excludetightLeptons || !tightLeptonssSet ) {

    muons = raw_muons;
    electrons = raw_electrons;

  }

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
