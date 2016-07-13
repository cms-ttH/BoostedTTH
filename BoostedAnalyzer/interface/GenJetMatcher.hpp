#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GENJETMATCHER_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GENJETMATCHER_HPP

#include <map>
#include <vector>
#include <cmath>

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/GenJet.h"

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"


class GenJetMatcher {

public:
  GenJetMatcher();

  void init( double DeltaRMatch );

  std::map< pat::Jet* , reco::GenJet* > match( std::vector< pat::Jet >& Jets,
					       std::vector< reco::GenJet > & GenJets);

  void resetMaps( );

private:

  //Member Functions
  std::map<  pat::Jet* , std::vector<reco::GenJet* > > matchGenJetstoJet( std::vector<  pat::Jet >& Jets,
									  std::vector< reco::GenJet >& GenJets);

  std::map< reco::GenJet* ,  std::vector< pat::Jet* > > matchJetstoGenJet ( std::vector<  pat::Jet >& Jets,
									   std::vector< reco::GenJet >& GenJets);

  std::vector< reco::GenJet* > getAllGenJetsforJet( pat::Jet& Jet );
  std::vector< pat::Jet* > getAllJetsforGenJet( reco::GenJet& GenJet );

  void cleanMaps( pat::Jet& Jet, reco::GenJet& GenJet );

  //Member variables
  double maxDeltaRforMatch;

  std::map< pat::Jet* , vector<reco::GenJet* > > jetMatches;
  std::map< reco::GenJet* , vector< pat::Jet* > >  genJetMatches;



};

#endif
