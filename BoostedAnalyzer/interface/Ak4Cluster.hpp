#ifndef BOOSTEDTTH_BOOSTEDANALYZER_AK4CLUSTER_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_AK4CLUSTER_HPP

#include "TLorentzVector.h"
#include "TMath.h"
#include "TVector.h"
#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "MiniAOD/BoostedObjects/interface/Ak4Cluster.h"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

class Ak4Cluster
{

public:
  static boosted::Ak4ClusterCollection GetAk4Cluster(
    const pat::JetCollection& inputAk4Jets,
    const int algo);
  static boosted::Ak4ClusterCollection GetSelectedAk4Cluster(
    const boosted::Ak4ClusterCollection& allAk4Clusters,
    const double iMinClusterPt,
    const string mode);
  static bool FirstFatjetInAk4ClusterIsHarder(boosted::Ak4Cluster clu1,
                                              boosted::Ak4Cluster clu2);

private:
};

#endif
