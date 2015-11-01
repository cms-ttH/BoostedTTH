#ifndef BOOSTEDTTH_BOOSTEDANALYZER_EVENTINFO_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_EVENTINFO_HPP

#include <vector>
#include "DataFormats/METReco/interface/HcalNoiseSummary.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
class EventInfo {
  
public:
  
  EventInfo(const edm::Event& iEvent, const edm::Handle<reco::BeamSpot>& beamSpot, const edm::Handle<HcalNoiseSummary>& hcalNoiseSummary, const edm::Handle< std::vector<PileupSummaryInfo> >& puSummaryInfo, bool firstVertexIsGood_, float rho_);

  // Event Information
  long evt;
  int run;
  int lumiBlock;
  
  // Collision Point Information
  float BSx, BSy, BSz;
  
  // HCal Information
  bool hcalnoiseLoose, hcalnoiseTight;
  
  // Pile Up Information
  float numGenPV, numTruePV;
  int sumNVtx, nm1, n0, np1;
  int sumTrueNVtx, nm1_true, n0_true, np1_true;

  bool firstVertexIsGood;

  float rho;
  
};

#endif
