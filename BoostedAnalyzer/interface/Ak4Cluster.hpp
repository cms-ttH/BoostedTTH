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

class Ak4Cluster{

  public:

    static boosted::Ak4ClusterCollection GetAk4Cluster(const pat::JetCollection& inputAk4Jets, const int algo);
    static boosted::Ak4ClusterCollection GetSelectedAk4Cluster(const boosted::Ak4ClusterCollection& allAk4Clusters, const double iMinClusterPt);
    static void StudyMatchingAk4ClusterAndFatjets(const boosted::Ak4ClusterCollection& ak4Clusters, std::vector<boosted::BoostedJet> fatjets, const double iMaxDeltaR);

  private:

};

#endif
