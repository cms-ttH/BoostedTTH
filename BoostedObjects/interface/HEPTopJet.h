#ifndef BOOSTEDTTH_BOOSTEDOBJECTS_HEPTOPJET_h
#define BOOSTEDTTH_BOOSTEDOBJECTS_HEPTOPJET_h

#include <vector>

#include "DataFormats/PatCandidates/interface/Jet.h"

namespace boosted {

  class HEPTopJet {
    
    public:
    
      HEPTopJet() :
		    fatjet(pat::Jet()),
		    topjet(pat::Jet()),
		    nonW(pat::Jet()),
		    W(pat::Jet()),
		    W1(pat::Jet()),
		    W2(pat::Jet()),
		    toptag(false),
		    subjettiness1(-99),
		    subjettiness2(-99),
		    subjettiness3(-99),
		    subjettiness4(-99) {};

      pat::Jet fatjet;
	    pat::Jet topjet;
	    pat::Jet nonW;
	    pat::Jet W;
	    pat::Jet W1;
	    pat::Jet W2;

	    bool toptag;

	    double subjettiness1;
	    double subjettiness2;
	    double subjettiness3;
	    double subjettiness4;
  };

  typedef std::vector<HEPTopJet> HEPTopJetCollection;
  
}

#endif
