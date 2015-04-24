#ifndef BOOSTEDTTH_BOOSTEDANALYZER_EVENTINFO_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_EVENTINFO_HPP

#include <vector>


class EventInfo {
  
public:
  
  EventInfo(const edm::Event& iEvent, const edm::Handle<reco::BeamSpot>& beamSpot, const edm::Handle<HcalNoiseSummary>& hcalNoiseSummary, const edm::Handle< std::vector<PileupSummaryInfo> >& puSummaryInfo);

  // Event Information
  long evt;
  int run;
  int sample;
  int lumiBlock;
  
  // Collision Point Information
  float BSx, BSy, BSz;
  
  // HCal Information
  bool hcalnoiseLoose, hcalnoiseTight;
  
  // Pile Up Information
  int sumNVtx, numGenPV, nm1, n0, np1;
  int sumTrueNVtx, numTruePV, nm1_true, n0_true, np1_true;

  const reco::VertexVertexCollection& primaryVertices;
  
};

#endif
