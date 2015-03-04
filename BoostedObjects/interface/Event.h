#ifndef BOOSTEDTTH_BOOSTEDOBJECTS_EVENT_h
#define BOOSTEDTTH_BOOSTEDOBJECTS_EVENT_h

#include <vector>

namespace boosted {

  class Event {
    
    public:
    
      Event() :
		    weight(1.),
        evt(-1),
        run(-1),
        sample(-1),
        lumiBlock(-1),
        qScale(-1.),
        alphaQCD(-1.), alphaQED(-1.),
        pthat(-1.),
        scalePDF(-1.),
        x1(-1.), x2(-1.),
        xPDF1(-1.), xPDF2(-1.),
        id1(-99), id2(-99),
        BSx(-99.), BSy(-99.), BSz(-99.),
		      //        GoodVertex(false),
        hcalnoiseLoose(false), hcalnoiseTight(false),
        sumNVtx(0), numGenPV(-1), nm1(-1), n0(-1), np1(-1),
        sumTrueNVtx(0), numTruePV(-1), nm1_true(-1), n0_true(-1), np1_true(-1) {};
      
      // Event Weight
      float weight;
      
      // Event Information
      long evt;
      int run;
      int sample;
      int lumiBlock;
      
      // MC Generator Information
      float qScale;
      float alphaQCD, alphaQED;
      float pthat;
      float scalePDF;
      float x1, x2;
      float xPDF1, xPDF2;
      int   id1, id2;
      
      // Collision Point Information
      float BSx, BSy, BSz;
      
      // HCal Information
      bool hcalnoiseLoose, hcalnoiseTight;
      
      // Pile Up Information
      int sumNVtx, numGenPV, nm1, n0, np1;
      int sumTrueNVtx, numTruePV, nm1_true, n0_true, np1_true;
      
      /*
      int FilterOutScraping
      float FilterOutScrapingFraction;
      
      int HBHENoiseFilter;
      
      int CSCLooseHaloId, CSCTightHaloId;
      int EcalLooseHaloId, EcalTightHaloId;
      int HcalLooseHaloId, HcalTightHaloId;
      int GlobalLooseHaloId, GlobalTightHaloId;
      int LooseId, TightId;
      
      float bField;
      
      float Q2ScaleUpWgt, Q2ScaleDownWgt;
      
      float rho_kt6PFJets, rho_kt6PFJetsCentralChargedPileUp, rho_kt6PFJetsCentralNeutral, rho_kt6PFJetsCentralNeutralTight;
      
      int W0decay, W1decay, Z0decay, Z1decay, H0decay, H1decay;
      */
      
  };

  typedef std::vector<Event> EventCollection;
}

#endif
