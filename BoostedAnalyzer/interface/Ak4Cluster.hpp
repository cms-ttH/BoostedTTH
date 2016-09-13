#ifndef BOOSTEDTTH_BOOSTEDANALYZER_AK4CLUSTER_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_AK4CLUSTER_HPP

#include <vector>
#include "TLorentzVector.h"
#include "TVector.h"
#include "TMath.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "MiniAOD/BoostedObjects/interface/Ak4Cluster.h"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
//#include "DataFormats/Math/interface/LorentzVector.h"
//#include "Math/GenVector/LorentzVector.h"

class Ak4Cluster{

  public:

    static boosted::Ak4ClusterCollection GetSelectedAk4Cluster(const pat::JetCollection& inputAk4Jets, const double iMinClusterPt);
    static boosted::Ak4ClusterCollection GetSelectedAk4Cluster(const boosted::Ak4ClusterCollection& allAk4Clusters, const double iMinClusterPt);

  private:

};

#endif
