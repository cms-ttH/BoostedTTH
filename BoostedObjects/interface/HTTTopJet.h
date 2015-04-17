#ifndef BOOSTEDTTH_BOOSTEDOBJECTS_HTTTOPJET_h
#define BOOSTEDTTH_BOOSTEDOBJECTS_HTTTOPJET_h

#include <vector>

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/HTTTopJetTagInfo.h"

namespace boosted {

  class HTTTopJet {
    
    public:
    
      HTTTopJet() :
		    fatjet(pat::Jet()),
		    nonW(pat::Jet()),
		    W1(pat::Jet()),
		    W2(pat::Jet()),
		    fatjetMass(-99),
        fatjetPt(-99),
        fatjetEta(-99),
        fatjetPhi(-99),
        topMass(-99),
        unfilteredMass(-99),
        prunedMass(-99),
        fRec(-99),
        massRatioPassed(-99),
        tau1Unfiltered(-99),
	      tau2Unfiltered(-99),
	      tau3Unfiltered(-99),
	      tau1Filtered(-99),
	      tau2Filtered(-99),
	      tau3Filtered(-99),
        qWeight(-99),
        qEpsilon(-99),
        qSigmaM(-99) {};

      pat::Jet fatjet;
	    pat::Jet nonW;
	    pat::Jet W1;
	    pat::Jet W2;

	    double fatjetMass;
      double fatjetPt;
      double fatjetEta;
      double fatjetPhi;
      
      double topMass;
      double unfilteredMass;
      double prunedMass;
      double fRec;
      double massRatioPassed;
      
      double Ropt;
      double RoptCalc;
      double ptForRoptCalc;
      
      double tau1Unfiltered;
	    double tau2Unfiltered;
	    double tau3Unfiltered;
	    double tau1Filtered;
	    double tau2Filtered;
	    double tau3Filtered;
      
      double qWeight;
      double qEpsilon;
      double qSigmaM;
  };

  typedef std::vector<HTTTopJet> HTTTopJetCollection;
  
}

#endif
