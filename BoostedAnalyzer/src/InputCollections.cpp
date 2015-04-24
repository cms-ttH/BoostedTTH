#include "../interface/InputCollections.hpp"
void InputCollections::DumpFatJets(){

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
void InputCollections::DumpSyncExe(){
  /*  int run=-99;
  int lumi=-99;  
  int event=-99;  
  float lep1_pt=-99;
  float lep1_eta=-99;
  float lep1_phi=-99;
  float lep1_pt=-99;
  float lep2_pt=-99;
  float lep3_pt=-99;
  float lep4_pt=-99;
  float lep1_CSVv2=-99;
  float lep2_CSVv2=-99;
  float lep3_CSVv2=-99;
  float lep4_CSVv2=-99;
  int njets=0;
  int nbtags=0;
  int n_toptags=0;
  int n_higgstags=0;
  
  printf("%6d %8d %10d   %6.2f %+4.2f %+4.2f   %6.2f %6.2f %6.2f %6.2f   %+7.3f %+7.3f %+7.3f %+7.3f   %2d  %2d   %2d  %2d\n",
	 run, lumi, event,
	 lep1_pt, lep1_eta, lep1_phi,
	 jet1_pt, jet2_pt, jet3_pt, jet4_pt,
	 jet1_CSVv2, jet2_CSVv2, jet3_CSVv2, jet4_CSVv2,
	 n_jets, n_btags,
	 n_toptags, n_higgstags);*/
}
