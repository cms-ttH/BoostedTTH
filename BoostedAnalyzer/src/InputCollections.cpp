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

  for(auto topjet = selectedHEPTopJets.begin() ; topjet != selectedHEPTopJets.end(); topjet++ ){
    // pt and eta requirements on top jet
    if( !(topjet->fatjet.pt() > 250. && abs(topjet->fatjet.eta()) < 1.8) ) continue;
    std::cout << "fat top jet pt: " << topjet->fatjet.pt()<<std::endl;
    pat::Jet W = topjet->W;
    pat::Jet W1 = topjet->W1;
    pat::Jet top = topjet->topjet;
    printf("\t\t W %2d:\t pT = %.1f,\t M = %.1f,\t eta = %.2f,\t phi = %.2f,\t CSVv2 = %+5.3f,\t CSVv1 = %+5.3f \n",
	   0, W.pt() , W.mass(), W.eta(), W.phi(), 
	   W.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"),
	   W.bDiscriminator("combinedSecondaryVertexBJetTags"));
    printf("\t\t top %2d:\t pT = %.1f,\t M = %.1f,\t eta = %.2f,\t phi = %.2f,\t CSVv2 = %+5.3f,\t CSVv1 = %+5.3f \n",
	   0, top.pt() , top.mass(), top.eta(), top.phi(), 
	   top.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"),
	   top.bDiscriminator("combinedSecondaryVertexBJetTags"));
    printf("\t\t W1 %2d:\t pT = %.1f,\t M = %.1f,\t eta = %.2f,\t phi = %.2f,\t CSVv2 = %+5.3f,\t CSVv1 = %+5.3f \n",
	   0, W1.pt() , W1.mass(), W1.eta(), W1.phi(), 
	   W1.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"),
	   W1.bDiscriminator("combinedSecondaryVertexBJetTags"));
    
  }

}
