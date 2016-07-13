#include "BoostedTTH/BoostedAnalyzer/interface/GenJetMatcher.hpp"
using namespace std;


//PUBLIC


GenJetMatcher::GenJetMatcher(  ){





}


void GenJetMatcher::init( double DeltaRMatch ){

  maxDeltaRforMatch = DeltaRMatch;

}

map< pat::Jet* , reco::GenJet* > GenJetMatcher::match(  vector< pat::Jet >& Jets,
						                               vector< reco::GenJet >& GenJets){


  jetMatches = matchGenJetstoJet( Jets , GenJets );
  /*
  for (auto& Jet: Jets) {
    for (size_t i = 0; i < jetMatches[&Jet].size(); i++) {
      cout <<"Jet with " << Jet.pt() << " is matched to GenJet " << jetMatches[&Jet].at(i)->pt() << " with DR of " << BoostedUtils::DeltaR(Jet.p4(), jetMatches[&Jet].at(i)->p4()) << endl;
    }
  }
  */
  //std::map< reco::GenJet* , vector< pat::Jet* > >  genJetMatches;

  genJetMatches = matchJetstoGenJet( Jets , GenJets );





  map< pat::Jet* , reco::GenJet* > finalmatches;

  for ( auto& Jet: Jets ){
    vector< reco::GenJet* > currentGenJets = jetMatches[&Jet];
    // Loop over all GenJets, that are matched to current jet. After that, the DeltaR between this current GenJet
    // and the Jet are compared to the DeltaR between the curren GenJet and all to this GenJet matched Jet.
    for ( auto& currentGenJet: currentGenJets ) {
      bool bestgenjet = true;
      //vector< pat::Jet* > currentJets = getAllJetsforGenJet( *currentGenJet );
      vector< pat::Jet* > currentJets = genJetMatches[currentGenJet];
      for ( auto& currentJet: currentJets ){
	bool isnotsame = ( currentJet != &Jet );
	if ( ( BoostedUtils::DeltaR(Jet.p4(), currentGenJet->p4()) > BoostedUtils::DeltaR(currentJet->p4(),currentGenJet->p4()) ) && isnotsame){
	  bestgenjet = false;
	  break;
	}
      }
      if ( bestgenjet ) {
	finalmatches[&Jet] = currentGenJet;
	cleanMaps(Jet, *currentGenJet);

      }
    }
  }


  return finalmatches;


}


//PRIVATE


map< pat::Jet* , vector<reco::GenJet* > >  GenJetMatcher::matchGenJetstoJet (  vector<  pat::Jet >& Jets,
									      vector< reco::GenJet >& GenJets){

  map <  pat::Jet* , vector< reco::GenJet* > > matches;


  for(size_t i = 0 ; i < Jets.size(); i++) {
    vector< reco::GenJet* > matchedgenjets;
    for(size_t j = 0 ; j < GenJets.size() ; j++) {
      float dRjgj = BoostedUtils::DeltaR(Jets.at(i).p4(), GenJets.at(j).p4());
      if ( dRjgj < maxDeltaRforMatch ){
	matchedgenjets.push_back(&GenJets.at(j));
      }
    }
    matches[&Jets.at(i)] = matchedgenjets;
  }

  return matches;

}

map< reco::GenJet* ,  vector< pat::Jet* > >  GenJetMatcher::matchJetstoGenJet (  vector<  pat::Jet >& Jets,
									       vector< reco::GenJet >& GenJets){
  map < reco::GenJet* ,  vector < pat::Jet* > > matches;

  for(size_t j = 0 ; j < GenJets.size() ; j++) {
    vector<  pat::Jet* > matchedjets;
    for(size_t i = 0 ; i < Jets.size(); i++) {
      float dRjgj = BoostedUtils::DeltaR(Jets.at(i).p4(), GenJets.at(j).p4());
      if ( dRjgj < maxDeltaRforMatch ){
	matchedjets.push_back(&Jets.at(i));
      }
    }
    genJetMatches[&GenJets.at(j)] = matchedjets;
  }

  return matches;

}

vector< reco::GenJet* > GenJetMatcher::getAllGenJetsforJet(  pat::Jet& Jet ){

  return jetMatches[&Jet];
  /*bool nothingfound = true;

  for ( auto it_jets = jetMatches.begin() ; it_jets != jetMatches.end() ; it_jets++ ) {
    if ( it_jets->first == &Jet ){
      return it_jets->second;
    }
  }
  if (nothingfound){
    vector< reco::GenJet* > emptyvector;
    return emptyvector;
    }*/

}
vector< pat::Jet* > GenJetMatcher::getAllJetsforGenJet( reco::GenJet& GenJet ){

  return genJetMatches[&GenJet];
    /*
  bool nothingfound = true;

  for ( auto it_genJets = genJetMatches.begin() ; it_genJets != genJetMatches.end(); it_genJets++){
    if( it_genJets->first == &GenJet ) {
      return it_genJets->second;
      nothingfound = false;
    }
  }
  if (nothingfound){
    vector< pat::Jet* > emptyvector;
    return emptyvector;
  }
    */
}

void GenJetMatcher::cleanMaps(  pat::Jet& Jet, reco::GenJet& GenJet ){

  int ngj = 0;
  for ( auto& genJet: jetMatches[&Jet] ){
    if ( genJet == &GenJet ){
      jetMatches[&Jet].erase(jetMatches[&Jet].begin()+ngj);
    }
    ngj++;
  }

  genJetMatches.erase(&GenJet);


}


void GenJetMatcher::resetMaps( ){
    jetMatches.clear();
    genJetMatches.clear();
}
