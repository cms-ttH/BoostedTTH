#include "BoostedTTH/BoostedAnalyzer/interface/Ak4Cluster.hpp"

boosted::Ak4ClusterCollection Ak4Cluster::GetSelectedAk4Cluster(const pat::JetCollection& inputAk4Jets, const double iMinClusterPt){

  // Cambridge Aachen radius
  double R = 1.5;

  boosted::Ak4ClusterCollection outputAk4Cluster;

  for(std::vector<pat::Jet>::const_iterator itJet=inputAk4Jets.begin();itJet!=inputAk4Jets.end();++itJet){
    int iJet = itJet - inputAk4Jets.begin();

    boosted::Ak4Cluster tempCluster;
    tempCluster.fatjet = inputAk4Jets[iJet].p4();
    tempCluster.ak4jets.push_back(inputAk4Jets[iJet]);

    outputAk4Cluster.push_back(tempCluster);
  }

  while(outputAk4Cluster.size() > 1){
    // get all dij
    double dij[outputAk4Cluster.size()][outputAk4Cluster.size()];
    for(unsigned iA=0; iA <outputAk4Cluster.size() ;++iA){
      for(unsigned iB=0; iB <outputAk4Cluster.size() ;++iB){
        if(iA <= iB) continue;

        // Cambridge Aachen definition:
        dij[iA][iB] = BoostedUtils::DeltaR(outputAk4Cluster[iA].fatjet, outputAk4Cluster[iB].fatjet) / (R*R);
      }
    }

    // get the minimal dij
    double mindij = 9.;
    unsigned int cluster_jet1_id = 99;
    unsigned int cluster_jet2_id = 99;
    for(unsigned iA=0; iA <outputAk4Cluster.size() ;++iA){
      for(unsigned iB=0; iB <outputAk4Cluster.size() ;++iB){
        if(iA <= iB) continue;
        if(dij[iA][iB]<mindij){
          mindij = dij[iA][iB];
          cluster_jet1_id = iA;
          cluster_jet2_id = iB;
        }
      }
    }

    //cout << "mindij = " << mindij << endl;
    if(mindij < 1){
      // cluster the second to the first chosen ak4 jet
      outputAk4Cluster[cluster_jet1_id].fatjet += outputAk4Cluster[cluster_jet2_id].fatjet;

      for (unsigned int iA =0; iA < outputAk4Cluster[cluster_jet2_id].ak4jets.size(); ++iA){
        outputAk4Cluster[cluster_jet1_id].ak4jets.push_back(outputAk4Cluster[cluster_jet2_id].ak4jets[iA]);
      }

      // discard added jet from cluster
      outputAk4Cluster.erase(outputAk4Cluster.begin()+cluster_jet2_id);
    }
    else return GetSelectedAk4Cluster(outputAk4Cluster,iMinClusterPt);
  }
  return GetSelectedAk4Cluster(outputAk4Cluster,iMinClusterPt);
}


boosted::Ak4ClusterCollection Ak4Cluster::GetSelectedAk4Cluster(const boosted::Ak4ClusterCollection& allAk4Clusters, const double iMinClusterPt){
  boosted::Ak4ClusterCollection selectedAk4Clusters;
  for(unsigned int iA=0; iA<allAk4Clusters.size(); ++iA){
    if(allAk4Clusters[iA].fatjet.Pt() > iMinClusterPt){
      selectedAk4Clusters.push_back(allAk4Clusters[iA]);
    }
  }
  return selectedAk4Clusters;
}
