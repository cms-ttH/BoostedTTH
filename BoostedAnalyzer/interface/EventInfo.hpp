#ifndef BOOSTEDTTH_BOOSTEDANALYZER_EVENTINFO_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_EVENTINFO_HPP

#include <vector>


class EventInfo {
  
public:
  
  EventInfo();
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

#endif
