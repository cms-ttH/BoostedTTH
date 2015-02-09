#ifndef BOOSTEDTTH_BOOSTEDOBJECTS_SUBFILTERJET_h
#define BOOSTEDTTH_BOOSTEDOBJECTS_SUBFILTERJET_h

#include <vector>

#include "DataFormats/PatCandidates/interface/Jet.h"

namespace boosted {

  class SubFilterJet {

    public:

      SubFilterJet() :
	      fatjet(pat::Jet()),
	      subjettiness1(-99),
	      subjettiness2(-99),
	      subjettiness3(-99),
	      subjettiness4(-99) {};

      pat::Jet fatjet;
      std::vector<pat::Jet> subjets;
      std::vector<pat::Jet> filterjets;

      double subjettiness1;
      double subjettiness2;
      double subjettiness3;
      double subjettiness4;
      
  };

  typedef std::vector<SubFilterJet> SubFilterJetCollection;

}

#endif
