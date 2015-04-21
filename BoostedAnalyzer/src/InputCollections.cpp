#include "../interface/InputCollections.hpp"
void InputCollections::Dump(){

  for( auto higgsJet = selectedSubFilterJets.begin() ; higgsJet != selectedSubFilterJets.end(); ++higgsJet ){
    // pt and eta requirements on top jet
    if( !(higgsJet->fatjet.pt() > 250. && abs(higgsJet->fatjet.eta()) < 1.8) ) continue;
    std::cout << "fat jet pt: " << higgsJet->fatjet.pt()<<std::endl;
    std::vector<pat::Jet> filterjets = higgsJet->filterjets;
    for( uint ijet=0; ijet<filterjets.size(); ijet++ ){
      printf("\t\t filt jet %2d:\t pT = %.1f,\t eta = %.2f,\t phi = %.2f,\t CSVv2 = %+5.3f,\t CSVv1 = %+5.3f \n",
	     ijet, filterjets[ijet].pt(), filterjets[ijet].eta(), filterjets[ijet].phi(), 
	     filterjets[ijet].bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"),
	     filterjets[ijet].bDiscriminator("combinedSecondaryVertexBJetTags"));
    }
  }

  for(auto topjet = selectedHTTTopJets.begin() ; topjet != selectedHTTTopJets.end(); topjet++ ){
    // pt and eta requirements on top jet
    if( !(topjet->fatjet.pt() > 250. && abs(topjet->fatjet.eta()) < 1.8) ) continue;
    std::cout << "fat top jet pt: " << topjet->fatjet.pt()<<std::endl;
    math::XYZTLorentzVector W = topjet->GetWJetVec();
    pat::Jet W1 = topjet->W1;
    math::XYZTLorentzVector top = topjet->GetTopJetVec();
    printf("\t\t W %2d:\t pT = %.1f,\t M = %.1f,\t eta = %.2f,\t phi = %.2f \n",
	   0, W.Pt() , W.M(), W.Eta(), W.Phi());
    printf("\t\t top %2d:\t pT = %.1f,\t M = %.1f,\t eta = %.2f,\t phi = %.2f \n",
	   0, top.Pt() , top.M(), top.Eta(), top.Phi());
    printf("\t\t W1 %2d:\t pT = %.1f,\t M = %.1f,\t eta = %.2f,\t phi = %.2f,\t CSVv2 = %+5.3f,\t CSVv1 = %+5.3f \n",
	   0, W1.pt() , W1.mass(), W1.eta(), W1.phi(), 
	   W1.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"),
	   W1.bDiscriminator("combinedSecondaryVertexBJetTags"));
    
  }

}
