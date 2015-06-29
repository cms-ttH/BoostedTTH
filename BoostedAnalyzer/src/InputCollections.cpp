#include "../interface/InputCollections.hpp"
/*void InputCollections::DumpSampleType(){
  
  }*/


void InputCollections::DumpLeptons(std::ostream &out){
  out << "loose electrons" << std::endl;
  for(auto el=selectedElectronsLoose.begin(); el!=selectedElectronsLoose.end(); el++){
    out << " pT "  << el->pt() << " eta " << el->eta() << " phi "  << el->phi() << std::endl;
  }
  out << "tight electrons" << std::endl;
  for(auto el=selectedElectrons.begin(); el!=selectedElectrons.end(); el++){
    out << " pT "  << el->pt() << " eta " << el->eta() << " phi "  << el->phi() << std::endl;
  }
  out << "loose muons" << std::endl;
  for(auto el=selectedMuonsLoose.begin(); el!=selectedMuonsLoose.end(); el++){
    out << " pT "  << el->pt() << " eta " << el->eta() << " phi "  << el->phi() << std::endl;
  }
  out << "tight muons" << std::endl;
  for(auto el=selectedMuons.begin(); el!=selectedMuons.end(); el++){
    out << " pT "  << el->pt() << " eta " << el->eta() << " phi "  << el->phi() << std::endl;
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
  
  out << boost::format("%6d %8d %10d   %6.2f %+4.2f %+4.2f   %6.2f %6.2f %6.2f %6.2f   %+7.3f %+7.3f %+7.3f %+7.3f   %+7.3f   %2d  %2d   %2d   %2d  %2d\n")%
	 run% lumi% event%
	 lep1_pt% lep1_eta% lep1_phi%
	 jet1_pt% jet2_pt% jet3_pt% jet4_pt%
	 jet1_CSVv2% jet2_CSVv2% jet3_CSVv2% jet4_CSVv2%
	 MET%
	 n_jets% n_btags%
	 ttHFCategory%
	 n_toptags% n_higgstags;

}
void InputCollections::DumpSyncExe2(const MiniAODHelper& helper, std::ostream &out){
  /*  int run=eventInfo.run;
  int lumi=eventInfo.lumiBlock;  
  int event=eventInfo.evt;  
  float bWeight=input.weights.at("Weight_CSV")
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
  float MET_pt=-99;
  float MET_phi=-99;
  int n_jets=0;
  int n_btags=0;
  int ttHFCategory=0;

  //GetMuonRelIso(const pat::Muon& iMuon,const coneSize::coneSize iconeSize, const corrType::corrType icorrType) const
  float lep1_iso=-99;
  float lep1_pdgid=-99;
  float lep2_pt=-99;
  float lep2_eta=-99;
  float lep2_phi=-99;
  float lep2_iso=-99;
  float lep2_pdgid=-99;



  for(std::vector<pat::Muon>::const_iterator iMuon = selectedMuonsLoose.begin(), iMuon != selectedMuonsLoose.end(); ++iMuon ){
    if(iMuon->pt()>lep1_pt){
      lep1_pt=iMuon->pt();
      lep1_eta=iMuon->eta();
      lep1_phi=iMuon->phi();
      lep1_iso=helper.GetMuonRelIso(iMuon,coneSize::R04, const corrType::deltaBeta);
      lep1_pdgid=iMuon->pdgId();
    }
  }
  for(std::vector<pat::Electron>::const_iterator iEle = selectedElectronsLoose.begin(), iEle != selectedElectronsLoose.end(); ++iEle ){
    if(iEle->pt()>lep1_pt){
      lep1_pt=iEle->pt();
      lep1_eta=iEle->eta();
      lep1_phi=iEle->phi();
      lep1_iso=helper.GetElectronRelIso(iElectron,coneSize::R04, const corrType::deltaBeta);
      lep1_pdgid=iMuon->pdgId();
    }
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

  MET_pt=pfMET.pt();
  MET_phi=pfMET.phi();

  ttHFCategory=genTopEvt.GetTTxId();


  
run,lumi,event,\
is_SL,is_DL,\
lep1_pt,lep1_eta,lep1_phi,lep1_iso,lep1_pdgId,\
lep2_pt,lep2_eta,lep2_phi,lep2_iso,lep2_pdgId,\
jet1_pt,jet2_pt,jet3_pt,jet4_pt,\
jet1_CSVv2,jet2_CSVv2,jet3_CSVv2,jet4_CSVv2,\
jet1_corr,jet2_corr,jet3_corr,jet4_corr,\
jet1_corrUp,jet2_corrUp,jet3_corrUp,jet4_corrUp,\
jet1_corrDown,jet2_corrDown,jet3_corrDown,jet4_corrDown,\
MET_pt,MET_phi,\
n_jets,n_btags,\
bWeight,bWeightLFUp,bWeightLFDown,\
ttHFCategory"
*/
}
