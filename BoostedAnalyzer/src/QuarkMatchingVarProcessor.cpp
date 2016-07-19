#include "BoostedTTH/BoostedAnalyzer/interface/QuarkMatchingVarProcessor.hpp"

using namespace std;

QuarkMatchingVarProcessor::QuarkMatchingVarProcessor(){

  DeltaRCut = 0.3;
  useregressedJets = false;

}


QuarkMatchingVarProcessor::QuarkMatchingVarProcessor( edm::ConsumesCollector && iC, std::vector<edm::InputTag> regJetCollections){

  DeltaRCut = 0.3;
  useregressedJets = true;

  for(auto &tag : regJetCollections){
      regressedJetsTokens.push_back(iC.consumes< std::vector<pat::Jet> >(tag));
  }

}


QuarkMatchingVarProcessor::~QuarkMatchingVarProcessor(){}

void QuarkMatchingVarProcessor::Init(const InputCollections& input, VariableContainer& vars){

  vars.InitVars("Jet_MatchedPartonPt","N_Jets");
  vars.InitVars("Jet_MatchedPartonDeltaR","N_Jets");
  vars.InitVars("Jet_MatchedPartonMotherId","N_Jets");
  vars.InitVars("Jet_MatchedPartonFlav","N_Jets");

  vars.InitVar("Evt_MCbbMass","F");

  vars.InitVar("Evt_MChadtopMass","F");

  vars.InitVars("Jet_GenParticleFlav","N_Jets");
  vars.InitVars("Jet_GenParticleMotherId", "N_Jets");
  vars.InitVars("Jet_GenParticlePt","N_Jets");
  vars.InitVars("Jet_GenParticleEta","N_Jets");

  vars.InitVars("Jet_isHiggsJet","N_Jets");
  vars.InitVars("Jet_ishadTopJet","N_Jets");
  vars.InitVars("Jet_isWJet","N_Jets");
  if(useregressedJets){


      vars.InitVars("RegJet_MatchedPartonPt","N_RegJets");
      vars.InitVars("RegJet_MatchedPartonDeltaR","N_RegJets");
      vars.InitVars("RegJet_MatchedPartonMotherId","N_RegJets");
      vars.InitVars("RegJet_MatchedPartonFlav","N_RegJets");

	  vars.InitVar("Evt_MCRegbbMass","F");

	  vars.InitVar("Evt_MCReghadtopMass","F");

      vars.InitVars("RegJet_GenParticleFlav","N_RegJets");
      vars.InitVars("RegJet_GenParticleMotherId", "N_RegJets");
      vars.InitVars("RegJet_GenParticlePt","N_RegJets");
      vars.InitVars("RegJet_GenParticleEta","N_RegJets");

      vars.InitVars("RegJet_isHiggsJet","N_RegJets");
      vars.InitVars("RegJet_ishadTopJet","N_RegJets");
      vars.InitVars("RegJet_isWJet","N_RegJets");


  }

  initialized = true;
}

void QuarkMatchingVarProcessor::Process(const InputCollections& input, VariableContainer& vars){

  if(!initialized) cerr << "tree processor not initialized" << endl;
  if(!input.genTopEvt.IsFilled() || !input.genTopEvt.IsSemiLepton() ) { return; } //Only continue, if genTopEvt is filled
  std::vector<pat::Jet> regressedJets;
  if (useregressedJets){
      edm::Handle < std::vector< pat::Jet > > h_regressedJets;
      input.iEvent.getByToken( regressedJetsTokens[input.isys], h_regressedJets );
      regressedJets = *h_regressedJets;
  }
  /*
  //Get Quarks form W+/- and Top Decays
  vector<reco::GenParticle> quarks;
  quarks = GetQuarksfromTopDecay(input);
  if(input.genTopEvt.GetHiggs().pdgId() == 25) {
    vector<reco::GenParticle> higgsquarks = GetQuarksfromHiggsDecay(input);
    quarks.insert(end(quarks), begin(higgsquarks), end(higgsquarks));
}*/

    vector< vector< reco::GenParticle > > DecayProducts;
    DecayProducts.push_back( GetQuarksfromWDecay(input) );
    DecayProducts.push_back( { input.genTopEvt.GetTopLepDecayQuark() } );
    DecayProducts.push_back( { input.genTopEvt.GetTopHadDecayQuark() } );
    DecayProducts.push_back( GetQuarksfromHiggsDecay(input) );

    //cout << "DecayProducts " << DecayProducts[0].size() << " | " << DecayProducts[1].size() << " | " << DecayProducts[2].size() << " | " << DecayProducts[3].size()  << endl;
    //cout << "NJets is: " << input.selectedJets.size() << endl;

  //Loop over all Jet
  vector< vector < pat::Jet > > VJets = { input.selectedJets};
  vector< bool > isregressed = { false };
  if( useregressedJets ){
    VJets.push_back(regressedJets);
    isregressed.push_back(true);
  }

  for( size_t ijv = 0 ; ijv < VJets.size() ; ijv++ ){
      //cout << "Processing: " << ijv << endl;
      vector< pat::Jet > Jets =  VJets[ijv];

      vector< pat::Jet > higgsjets;
      pat::Jet hadtopjet;
      bool topjetfound = false;
      vector< pat::Jet > hadWjets;
      vector< int > iHiggsJet;

      string prefix = "";

      if( isregressed[ijv] ){
          prefix = "Reg";
      }



      int iJet = 0;
      for( auto& Jet: Jets ){
        reco::GenParticle MatchedParton;
        bool foundquark = false;


        vector< reco::GenParticle > MatchingQuarks;
        for(auto& Quarks: DecayProducts){

            MatchingQuarks.push_back( MatchPartontoJet( input, Quarks, Jet) );

        }

        //Find best matching quark -> usually no problem, but better save than sorry
        size_t iQ = 0;
        int decayfrom = -1;
        float DeltaRtmp = 999;
        for( auto& Quark: MatchingQuarks ){

            if (Quark.pdgId() != 0){
                if ( BoostedUtils::DeltaR( Jet.p4() , Quark.p4() ) < DeltaRtmp ){
                    DeltaRtmp = BoostedUtils::DeltaR( Jet.p4() , Quark.p4() );
                    MatchedParton = Quark;
                    decayfrom = iQ;
                    foundquark = true;
                }
            }
            iQ++;
        }
        //Fill Jets from W-Decay vector
        if( decayfrom == 0){
            //cout << Jet << endl << "is WJet" << endl;
            hadWjets.push_back(Jet);
            vars.FillVars(prefix+"Jet_isHiggsJet",iJet,0);
            vars.FillVars(prefix+"Jet_isWJet",iJet,1);
            vars.FillVars(prefix+"Jet_ishadTopJet",iJet,0);

        }
        //Fill Jet from leptonic Top-Decay vector
        else if (decayfrom == 1){
            //cout << Jet << endl << "is lepTJet" << endl;
            vars.FillVars(prefix+"Jet_isHiggsJet",iJet,0);
            vars.FillVars(prefix+"Jet_isWJet",iJet,0);
            vars.FillVars(prefix+"Jet_ishadTopJet",iJet,0);
            topjetfound = false;
        }
        //Fill Jet from hadronic Top-Decay vector
        else if (decayfrom == 2){
            //cout << Jet << endl << "is hadTJet" << endl;
            hadtopjet = Jet;
            vars.FillVars(prefix+"Jet_isHiggsJet",iJet,0);
            vars.FillVars(prefix+"Jet_isWJet",iJet,0);
            vars.FillVars(prefix+"Jet_ishadTopJet",iJet,1);
            topjetfound = true;
        }
        //Fill Jets from H-Decay vector
        else if (decayfrom == 3){
            //cout << Jet << endl << "is HJet" << endl;
            higgsjets.push_back(Jet);
            vars.FillVars(prefix+"Jet_isHiggsJet",iJet,1);
            vars.FillVars(prefix+"Jet_isWJet",iJet,0);
            vars.FillVars(prefix+"Jet_ishadTopJet",iJet,0);
        }

        if(foundquark){
            vars.FillVars(prefix+"Jet_MatchedPartonPt",iJet,MatchedParton.pt());
            vars.FillVars(prefix+"Jet_MatchedPartonDeltaR",iJet,BoostedUtils::DeltaR(Jet.p4(),MatchedParton.p4()));
            vars.FillVars(prefix+"Jet_MatchedPartonMotherId",iJet,MatchedParton.mother()->pdgId());
            vars.FillVars(prefix+"Jet_MatchedPartonFlav",iJet,MatchedParton.pdgId());
        }
        else {
            vars.FillVars(prefix+"Jet_MatchedPartonPt",iJet,-5);
            vars.FillVars(prefix+"Jet_MatchedPartonDeltaR",iJet,-5);
            vars.FillVars(prefix+"Jet_MatchedPartonMotherId",iJet,-5);
            vars.FillVars(prefix+"Jet_MatchedPartonFlav",iJet,-5);
        }
        iJet++;
      }

    //cout << "                                             Len whadjets: " << hadWjets.size() << endl;

      /**************************************************************/
      /*            Compute the MC Higgs mass variables             */
      /*                                                            */
      /*   Lepton multiplicity dependent variables now need to be   */
      /*   computed in external plotscripts -> use isHiggsJet var   */
      /**************************************************************/
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
        vars.FillVar("Evt_MC"+prefix+"bbMass",GetDijetMass(higgsjets.at(0),higgsjets.at(1)));
      }
      else {
        vars.FillVar("Evt_MC"+prefix+"bbMass",-99);
      }
      /**************************************************************/
      /**************************************************************/
      /**************************************************************/




      /**************************************************************/
      /*            Compute the MC Had Top mass variables           */
      /**************************************************************/
      if( hadWjets.size() == 2 && topjetfound ) {
        vars.FillVar("Evt_MC"+prefix+"hadtopMass",GetTopHadMass(hadtopjet,hadWjets));
      }
      else {
        vars.FillVar("Evt_MC"+prefix+"hadtopMass",-99);
      }
      /**************************************************************/
      /**************************************************************/
      /**************************************************************/




      /**************************************************************/
      /*                         GenParticle                        */
      /**************************************************************/
      int jJet = 0;
      for(auto& Jet: Jets){

        const reco::GenParticle *genparticle = Jet.genParticle();

        if ( genparticle ) {


          const reco::Candidate *mother  = genparticle->mother();

          vars.FillVars(  prefix+"Jet_GenParticleFlav" , jJet, genparticle->pdgId()  );
          vars.FillVars(  prefix+"Jet_GenParticleMotherId" , jJet , mother->pdgId()   );
          vars.FillVars(  prefix+"Jet_GenParticlePt" , jJet , genparticle->pt()  );
          vars.FillVars(  prefix+"Jet_GenParticleEta" , jJet , genparticle->eta()  );
        }

        else {

          vars.FillVars(  prefix+"Jet_GenParticleFlav" , jJet, -99  );
          vars.FillVars(  prefix+"Jet_GenParticleMotherId" , jJet , -99 );
          vars.FillVars(  prefix+"Jet_GenParticlePt" , jJet , -1  );
          vars.FillVars(  prefix+"Jet_GenParticleEta" , jJet , -11  );
        }
        jJet++;
      }
      /**************************************************************/
      /**************************************************************/
      /**************************************************************/

    }

}


reco::GenParticle QuarkMatchingVarProcessor::MatchPartontoJet ( const InputCollections& input,
                                                                vector<reco::GenParticle>& Partons,
                                                                pat::Jet& Jet){
    float DeltaRtmp;
    float DeltaRMin = 9999999;
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



/*
bool QuarkMatchingVarProcessor::MatchPartontoJet( const InputCollections& input,
                                                vector<reco::GenParticle>& Partons,
                                                pat::Jet& Jet ,
                                                pat::Jet& hadTopJet,
                                                vector<pat::Jet>& hadWJets,
                                                vector<pat::Jet>& HiggsJets,
                                                reco::GenParticle& matchedParton){
    float DeltaRtmp;
    float DeltaRMin = 9999999;
    bool foundquark = false;

    for( auto& Parton: Partons ){
        DeltaRtmp = BoostedUtils::DeltaR(Jet.p4(),Parton.p4());
        if(DeltaRtmp < DeltaRCut && DeltaRtmp < DeltaRMin){
            matchedParton = Parton;
            DeltaRMin = DeltaRtmp;
        	foundquark = true;
        }
        if (matchedParton.mother() != 0){
            if ( abs(matchedParton.pdgId()) == 5 ) {
                cout << matchedParton << endl;
                cout << "Here is a parton without a mother.. :(" << endl;
            }
            if(matchedParton.mother()->pdgId() == 25 &&  BoostedUtils::PassesCSV(Jet, 'M')) {
        	  HiggsJets.push_back(Jet);
        	}
            if(input.genTopEvt.IsSemiLepton()){
                //Get to b from hadronic Top matched Jet
                if(matchedParton.mother()->pdgId() == input.genTopEvt.GetTopHad().pdgId() &&  BoostedUtils::PassesCSV(Jet, 'M')){
                    hadTopJet = Jet;
                }
                //Get to quarks from hadronic W matched Jets
                if(matchedParton.mother()->pdgId() ==  input.genTopEvt.GetWhad().pdgId()){
                    hadWJets.push_back(Jet);
                }

            }

        }

    }

    return foundquark;

}
*/


float QuarkMatchingVarProcessor::GetTopHadMass(const pat::Jet& topJet, const vector<pat::Jet>& WJets) {

    float mass = 0;

    pat::Jet jet1 = topJet;
    pat::Jet jet2 = WJets.at(0);
    pat::Jet jet3 = WJets.at(1);

    TLorentzVector jet1vec;
    TLorentzVector jet2vec;
    TLorentzVector jet3vec;

    jet1vec.SetPtEtaPhiM(  jet1.pt() , jet1.eta() , jet1.phi() , jet1.mass()  );
    jet2vec.SetPtEtaPhiM(  jet2.pt() , jet2.eta() , jet2.phi() , jet2.mass()  );
    jet3vec.SetPtEtaPhiM(  jet3.pt() , jet3.eta() , jet3.phi() , jet3.mass()  );

    mass = (jet1vec+jet2vec+jet3vec).M();

    return mass;

}



float QuarkMatchingVarProcessor::GetDijetMass(const pat::Jet& firstjet, const pat::Jet& secondjet) {

    float dijetmass = 0;

    TLorentzVector jet1vec;
    TLorentzVector jet2vec;

    pat::Jet jet1 = firstjet;
    pat::Jet jet2 = secondjet;

    jet1vec.SetPtEtaPhiM(  jet1.pt() , jet1.eta() , jet1.phi() , jet1.mass()  );
    jet2vec.SetPtEtaPhiM(  jet2.pt() , jet2.eta() , jet2.phi() , jet2.mass()  );

    dijetmass = (jet1vec+jet2vec).M();

    return dijetmass;

}


std::vector<reco::GenParticle> QuarkMatchingVarProcessor::GetQuarksfromWDecay(const InputCollections& input) {

    vector<reco::GenParticle> quarks;

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

vector<reco::GenParticle> QuarkMatchingVarProcessor::GetbQuarksfromTopDecay(const InputCollections& input) {

  vector<reco::GenParticle> quarks;

  quarks.push_back(input.genTopEvt.GetTopDecayQuark());
  quarks.push_back(input.genTopEvt.GetTopBarDecayQuark());

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
