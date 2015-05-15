#include "../interface/InputCollections.hpp"
/*void InputCollections::DumpSampleType(){
  
  }*/

void InputCollections::DumpFatJets(std::ostream &out){

  for( auto higgsJet = selectedSubFilterJets.begin() ; higgsJet != selectedSubFilterJets.end(); ++higgsJet ){
    // pt and eta requirements on top jet
    if( !(higgsJet->fatjet.pt() > 250. && abs(higgsJet->fatjet.eta()) < 1.8) ) continue;
    out << "fat jet pt: " << higgsJet->fatjet.pt()<<std::endl;
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
    out << "fat top jet pt: " << topjet->fatjet.pt()<<std::endl;
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
void InputCollections::DumpSyncExe(std::ostream &out){
  int run=eventInfo.run;
  int lumi=eventInfo.lumiBlock;  
  int event=eventInfo.evt;  
  float lep1_pt=-99;
  float lep1_eta=-99;
  float lep1_phi=-99;
  float jet1_pt=-99;
  float jet2_pt=-99;
  float jet3_pt=-99;
  float jet4_pt=-99;
  float jet1_CSVv2=-99;
  float jet2_CSVv2=-99;
  float jet3_CSVv2=-99;
  float jet4_CSVv2=-99;
  float MET=-99;
  int n_jets=0;
  int n_btags=0;
  int ttHFCategory=0;
  int n_toptags=0;
  int n_higgstags=0;

  for(std::vector<pat::Muon>::const_iterator iMuon = selectedMuons.begin(), ed = selectedMuons.end(); iMuon != ed; ++iMuon ){
    if(iMuon->pt()>lep1_pt){
      lep1_pt=iMuon->pt();
      lep1_eta=iMuon->eta();
      lep1_phi=iMuon->phi();}
  }
  for(std::vector<pat::Electron>::const_iterator iEle = selectedElectrons.begin(), ed = selectedElectrons.end(); iEle != ed; ++iEle ){
    if(iEle->pt()>lep1_pt){
      lep1_pt=iEle->pt();
      lep1_eta=iEle->eta();
      lep1_phi=iEle->phi();}
  }
  
  
  if(selectedJets.size()>0){
    jet1_pt=selectedJets.at(0).pt();
    jet1_CSVv2=selectedJets.at(0).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(selectedJets.size()>1){
    jet2_pt=selectedJets.at(1).pt();
    jet2_CSVv2=selectedJets.at(1).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(selectedJets.size()>2){
    jet3_pt=selectedJets.at(2).pt();
    jet3_CSVv2=selectedJets.at(2).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(selectedJets.size()>3){
    jet4_pt=selectedJets.at(3).pt();
    jet4_CSVv2=selectedJets.at(3).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  n_jets=int(selectedJets.size());
  for(auto jet=selectedJets.begin();jet!=selectedJets.end(); jet++){
    if(BoostedUtils::PassesCSV(*jet)) n_btags++;
  }
  
  for(auto topjet = selectedHEPTopJets.begin() ; topjet != selectedHEPTopJets.end(); topjet++ ){
    // pt and eta requirements on top jet
    if( !(topjet->fatjet.pt() > 250. && abs(topjet->fatjet.eta()) < 1.8) ) continue;
    std::vector<pat::Jet> subjets;
    subjets.push_back(topjet->W1);
    subjets.push_back(topjet->W2);
    subjets.push_back(topjet->nonW);
    bool subjetcuts=true;
    for(auto j = subjets.begin(); j!=subjets.end();j++){
      if(j->pt()<20 || fabs(j->eta())>2.5) {
	subjetcuts=false;
	break;
      }
    }
    if(!subjetcuts) continue;
    if(BoostedUtils::GetTopTag(*topjet)) n_toptags++;
  }
  for( auto higgsJet = selectedSubFilterJets.begin() ; higgsJet != selectedSubFilterJets.end(); ++higgsJet ){
    // pt and eta requirements on higgs jet
    if( !(higgsJet->fatjet.pt() > 250. && abs(higgsJet->fatjet.eta()) < 1.8) ) continue;
    std::vector<pat::Jet> filterjets = higgsJet->filterjets;
    int subjettags=0;
    for(auto j=filterjets.begin(); j!=filterjets.end(); j++ ){
      if(j->pt()<20 || fabs(j->eta())>2.5) continue;
      if(BoostedUtils::PassesCSV(*j)){
	subjettags++;
      }	
    }
    if(subjettags>=2) n_higgstags++;
    
  }

  
  MET=pfMET.pt();

  ttHFCategory=genTopEvt.GetTTxId();
  
  out << boost::format("%6d %8d %10d   %6.2f %+4.2f %+4.2f   %6.2f %6.2f %6.2f %6.2f   %+7.3f %+7.3f %+7.3f %+7.3f %+7.3f   %2d  %2d  %2d  %2d  %2d\n")%
	 run% lumi% event%
	 lep1_pt% lep1_eta% lep1_phi%
	 jet1_pt% jet2_pt% jet3_pt% jet4_pt%
	 jet1_CSVv2% jet2_CSVv2% jet3_CSVv2% jet4_CSVv2%
	 MET%
	 n_jets% n_btags%
	 ttHFCategory%
	 n_toptags% n_higgstags;

}
