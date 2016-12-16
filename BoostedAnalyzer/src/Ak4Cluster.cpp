#include "BoostedTTH/BoostedAnalyzer/interface/Ak4Cluster.hpp"

boosted::Ak4ClusterCollection Ak4Cluster::GetAk4Cluster(const pat::JetCollection& inputAk4Jets, const int algo=0){

  double clusterRadius = 1.5;

  boosted::Ak4ClusterCollection outputAk4Cluster;
  
  // get all ak4jets and create ak4cluster for each ak4jet
  for(std::vector<pat::Jet>::const_iterator itJet=inputAk4Jets.begin();itJet!=inputAk4Jets.end();++itJet){
    int iJet = itJet - inputAk4Jets.begin();

    boosted::Ak4Cluster tempCluster;
    tempCluster.fatjet = inputAk4Jets[iJet].p4();
    tempCluster.ak4jets.push_back(inputAk4Jets[iJet]);

    outputAk4Cluster.push_back(tempCluster);
  }
  
  // cluster ak4jets and delete redundant ak4cluster after clustering step
  while(outputAk4Cluster.size() > 1){
    // Calculate two d-parameters:
    //    - dij is the distance-parameter between jet i and j with different
    //      exponents (1 = kt, 0 = CA, -1 = Anti-kt)
    //    - diB is the distance-parameter between jet i and the beam

    double dij[outputAk4Cluster.size()][outputAk4Cluster.size()];
    double diB[outputAk4Cluster.size()];
    double mindij = 9.;
    unsigned int cluster_jet1_id = 99;
    unsigned int cluster_jet2_id = 99;
    double mindiB = 9.;
    for(unsigned iA=0; iA <outputAk4Cluster.size() ;++iA){
      for(unsigned iB=0; iB <outputAk4Cluster.size() ;++iB){
        if(iA <= iB) continue;

        // get the dij
        dij[iA][iB] = min(pow(outputAk4Cluster[iA].fatjet.Pt(),2*algo),pow(outputAk4Cluster[iA].fatjet.Pt(),2*algo))*BoostedUtils::DeltaR(outputAk4Cluster[iA].fatjet, outputAk4Cluster[iB].fatjet) / (clusterRadius*clusterRadius);

        if(dij[iA][iB]<mindij){
          mindij = dij[iA][iB];
          cluster_jet1_id = iA;
          cluster_jet2_id = iB;
        }
      }
      // get the diB (distance from jet i to the beam)
      diB[iA] = pow(outputAk4Cluster[iA].fatjet.Pt(),2*algo);
      if(diB[iA] < mindiB) mindiB = diB[iA];
    }

    //cout << "mindij = " << mindij << endl;
    if(mindij < mindiB){
      // cluster the second to the first chosen ak4 jet
      outputAk4Cluster[cluster_jet1_id].fatjet += outputAk4Cluster[cluster_jet2_id].fatjet;

      for (unsigned int iA =0; iA < outputAk4Cluster[cluster_jet2_id].ak4jets.size(); ++iA){
        outputAk4Cluster[cluster_jet1_id].ak4jets.push_back(outputAk4Cluster[cluster_jet2_id].ak4jets[iA]);
      }

      // discard added jet from cluster
      outputAk4Cluster.erase(outputAk4Cluster.begin()+cluster_jet2_id);
    }
    //else return outputAk4Cluster;
    else break;
  }
  
  // sort ak4jets in ak4cluster by pT
  for(unsigned iAk4Cluster=0; iAk4Cluster <outputAk4Cluster.size() ;++iAk4Cluster){ 
    std::sort(outputAk4Cluster[iAk4Cluster].ak4jets.begin(), outputAk4Cluster[iAk4Cluster].ak4jets.end(),BoostedUtils::FirstJetIsHarder);
  }
  
  return outputAk4Cluster;
}


boosted::Ak4ClusterCollection Ak4Cluster::GetSelectedAk4Cluster(const boosted::Ak4ClusterCollection& allAk4Clusters, const double iMinClusterPt, const string mode="C"){
  boosted::Ak4ClusterCollection selectedAk4Clusters;

  for(unsigned int iA=0; iA<allAk4Clusters.size(); ++iA){
    boosted::Ak4Cluster tempCluster = allAk4Clusters[iA];

    tempCluster.isGoodHiggsCluster = false;
    tempCluster.isGoodTopCluster = false;

    if(mode=="C"){
      // mode C: pT cut on cluster pT

      if(tempCluster.fatjet.Pt() > iMinClusterPt){
        if(tempCluster.ak4jets.size()<2){
          tempCluster.isGoodHiggsCluster = false;
        }
        else tempCluster.isGoodHiggsCluster = true;

        if(tempCluster.ak4jets.size()<3) tempCluster.isGoodTopCluster = false;
        else tempCluster.isGoodTopCluster = true;

        selectedAk4Clusters.push_back(tempCluster);
      }
    }
    else if(mode == "A" || mode == "B"){
      // mode A: pT cut on two filterjets with best CSV out of the three hardest subjets
      // mode B: pT cut on three hardest filterjets
      if(tempCluster.ak4jets.size()<3) tempCluster.isGoodTopCluster = false;
      else{
        std::vector<pat::Jet> sortedAk4TopJets = tempCluster.ak4jets;
        BoostedUtils::TopSubjetCSVDef(sortedAk4TopJets);
        if((sortedAk4TopJets[0].p4() + sortedAk4TopJets[1].p4() + sortedAk4TopJets[2].p4()).pt() > iMinClusterPt){
          tempCluster.isGoodTopCluster = true;
        }
        else tempCluster.isGoodTopCluster = false;
      }

      if(tempCluster.ak4jets.size()<2){
        tempCluster.isGoodHiggsCluster = false;
      }
      else {
        // get three hardest ak4 jets
        std::vector<pat::Jet> sortedPtAk4Jets = tempCluster.ak4jets;
        std::sort(sortedPtAk4Jets.begin(), sortedPtAk4Jets.end(),BoostedUtils::FirstJetIsHarder);
        std::vector<pat::Jet> threeHardestAk4Jets;
        for ( std::vector<pat::Jet>::const_iterator itFilt2 = sortedPtAk4Jets.begin(), edFilt2 = sortedPtAk4Jets.end(); itFilt2 != edFilt2; ++itFilt2 ){
          int iFilt2 = itFilt2 - sortedPtAk4Jets.begin();
          if (iFilt2 > 2) continue;
          threeHardestAk4Jets.push_back(*itFilt2);
        }

        // selection
        if(mode=="A"){
          std::vector<pat::Jet> sortedAk4Jets = threeHardestAk4Jets;
          std::sort(sortedAk4Jets.begin(), sortedAk4Jets.end(),BoostedUtils::FirstHasHigherCSV);
          if ((sortedAk4Jets[0].p4() + sortedAk4Jets[1].p4()).pt() > iMinClusterPt) tempCluster.isGoodHiggsCluster = true;
          else tempCluster.isGoodHiggsCluster = false;
        }
        else if(mode=="B"){
          if ((threeHardestAk4Jets[0].p4() + threeHardestAk4Jets[1].p4() + threeHardestAk4Jets[2].p4()).pt() > iMinClusterPt) tempCluster.isGoodHiggsCluster = true;
          else tempCluster.isGoodHiggsCluster = false;
        }
      }
    }
    else cout << "Error in GetSelectedAk4Cluster: No valid selection mode.";

    if(tempCluster.isGoodHiggsCluster || tempCluster.isGoodTopCluster) selectedAk4Clusters.push_back(tempCluster);
  }
  return selectedAk4Clusters;
}
