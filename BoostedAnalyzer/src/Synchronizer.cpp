#include "BoostedTTH/BoostedAnalyzer/interface/Synchronizer.hpp"

using namespace std;

Synchronizer::Synchronizer (){
    cutflowSL.Init();
    cutflowDL.Init();
}
Synchronizer::~Synchronizer (){
  for(auto f = dumpFiles1.begin(); f!=dumpFiles1.end(); f++){
    (*f)->close();
  }
  for(auto f = dumpFiles2.begin(); f!=dumpFiles2.end(); f++){
    (*f)->close();
  }
  for(auto f = dumpFiles2_jesup.begin(); f!=dumpFiles2_jesup.end(); f++){
    (*f)->close();
  }
  for(auto f = dumpFiles2_jesdown.begin(); f!=dumpFiles2_jesdown.end(); f++){
    (*f)->close();
  }
  for(auto f = dumpFiles2_raw.begin(); f!=dumpFiles2_raw.end(); f++){
    (*f)->close();
  }
  cutflowSL.Print(cout);
  cutflowDL.Print(cout);
}

void Synchronizer::DumpSyncExe1(int nfile,const InputCollections& input){
  DumpSyncExe1(input,*(dumpFiles1[nfile]));
}

void Synchronizer::DumpSyncExe1(const InputCollections& input, std::ostream &out){
  int run=input.eventInfo.run;
  int lumi=input.eventInfo.lumiBlock;  
  int event=input.eventInfo.evt;  
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
  
  for(std::vector<pat::Muon>::const_iterator iMuon = input.selectedMuons.begin(), ed = input.selectedMuons.end(); iMuon != ed; ++iMuon ){
    if(iMuon->pt()>lep1_pt){
      lep1_pt=iMuon->pt();
      lep1_eta=iMuon->eta();
      lep1_phi=iMuon->phi();}
  }
  for(std::vector<pat::Electron>::const_iterator iEle = input.selectedElectrons.begin(), ed = input.selectedElectrons.end(); iEle != ed; ++iEle ){
    if(iEle->pt()>lep1_pt){
      lep1_pt=iEle->pt();
      lep1_eta=iEle->eta();
      lep1_phi=iEle->phi();}
  }
  
  
  if(input.selectedJets.size()>0){
    jet1_pt=input.selectedJets.at(0).pt();
    jet1_CSVv2=input.selectedJets.at(0).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(input.selectedJets.size()>1){
    jet2_pt=input.selectedJets.at(1).pt();
    jet2_CSVv2=input.selectedJets.at(1).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(input.selectedJets.size()>2){
    jet3_pt=input.selectedJets.at(2).pt();
    jet3_CSVv2=input.selectedJets.at(2).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(input.selectedJets.size()>3){
    jet4_pt=input.selectedJets.at(3).pt();
    jet4_CSVv2=input.selectedJets.at(3).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  n_jets=int(input.selectedJets.size());
  for(auto jet=input.selectedJets.begin();jet!=input.selectedJets.end(); jet++){
    if(BoostedUtils::PassesCSV(*jet)) n_btags++;
  }
  
  for(auto topjet = input.selectedHEPTopJets.begin() ; topjet != input.selectedHEPTopJets.end(); topjet++ ){
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
  for( auto higgsJet = input.selectedSubFilterJets.begin() ; higgsJet != input.selectedSubFilterJets.end(); ++higgsJet ){
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

  
  MET=input.pfMET.pt();

  ttHFCategory=input.genTopEvt.GetTTxIdFromHelper();
  
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
void Synchronizer::DumpSyncExe2Header(std::ostream &out){
  out <<"run,lumi,event,is_SL,is_DL,lep1_pt,lep1_eta,lep1_phi,lep1_iso,lep1_pdgId,lep2_pt,lep2_eta,lep2_phi,lep2_iso,lep2_pdgId,jet1_pt,jet2_pt,jet3_pt,jet4_pt,jet1_CSVv2,jet2_CSVv2,jet3_CSVv2,jet4_CSVv2,MET_pt,MET_phi,n_jets,n_btags,bWeight,ttHFCategory\n";
}


void Synchronizer::DumpSyncExe2(const InputCollections& input, const MiniAODHelper helper, std::ostream &out){
    if(leptonSelections.size()==0){
	leptonSelections.push_back(new LeptonSelection());
	leptonSelections.push_back(new JetTagSelection(4,2));
	for(uint i=0; i<leptonSelections.size(); i++){
	    leptonSelections[i]->InitCutflow(cutflowSL);
	}
    }
    if(dileptonSelections.size()==0){
	dileptonSelections.push_back(new DiLeptonSelection());
	//	dileptonSelections.push_back(new DiLeptonMassSelection(20,99999));
	//	dileptonSelections.push_back(new DiLeptonMassSelection(76,106,true));
	//	dileptonSelections.push_back(new METSelection(40,99999));
	dileptonSelections.push_back(new JetTagSelection(2,1));
	for(uint i=0; i<dileptonSelections.size(); i++){
	    dileptonSelections[i]->InitCutflow(cutflowDL);
	}
    }

  int run=input.eventInfo.run;
  int lumi=input.eventInfo.lumiBlock;  
  int event=input.eventInfo.evt;  
  float bWeight=input.weights.at("Weight_CSV");
  float lep1_pt=0;
  float lep1_eta=0;
  float lep1_phi=0;
  float lep1_iso=0;
  float lep1_pdgId=0;
  float lep2_pt=0;
  float lep2_eta=0;
  float lep2_phi=0;
  float lep2_iso=0;
  float lep2_pdgId=0;
  float jet1_pt=0;
  float jet2_pt=0;
  float jet3_pt=0;
  float jet4_pt=0;
  float jet1_CSVv2=0;
  float jet2_CSVv2=0;
  float jet3_CSVv2=0;
  float jet4_CSVv2=0;
  float MET_pt=0;
  float MET_phi=0;
  int n_jets=0;
  int n_btags=0;
  int ttHFCategory=0;
 
  bool is_SL=true;
  bool is_DL=true;

  cutflowSL.EventSurvivedStep("all",input.weights.at("Weight"));
  for(uint i=0; i<leptonSelections.size(); i++){
      if(!leptonSelections[i]->IsSelected(input,cutflowSL)){
	  is_SL=false;
	  break;
      }
  }
  cutflowDL.EventSurvivedStep("all",input.weights.at("Weight"));
  for(uint i=0; i<dileptonSelections.size(); i++){
      if(!dileptonSelections[i]->IsSelected(input,cutflowDL)){
	  is_DL=false;
	  break;
      }
  }
  for(std::vector<pat::Muon>::const_iterator iMuon = input.selectedMuonsLoose.begin(); iMuon != input.selectedMuonsLoose.end(); ++iMuon ){
    if(iMuon->pt()>lep1_pt){
      lep2_pt=lep1_pt;
      lep2_eta=lep1_eta;
      lep2_phi=lep1_phi;
      lep2_iso=lep1_iso;
      lep2_pdgId=lep1_pdgId;

      lep1_pt=iMuon->pt();
      lep1_eta=iMuon->eta();
      lep1_phi=iMuon->phi();
      lep1_iso=helper.GetMuonRelIso(*iMuon,coneSize::R04, corrType::deltaBeta);
      lep1_pdgId=iMuon->pdgId();
    }
    else if(iMuon->pt()>lep2_pt){
      lep2_pt=iMuon->pt();
      lep2_eta=iMuon->eta();
      lep2_phi=iMuon->phi();
      lep2_iso=helper.GetMuonRelIso(*iMuon,coneSize::R04, corrType::deltaBeta);
      lep2_pdgId=iMuon->pdgId();
    }
  }
  for(std::vector<pat::Electron>::const_iterator iEle = input.selectedElectronsLoose.begin(); iEle != input.selectedElectronsLoose.end(); ++iEle ){
    if(iEle->pt()>lep1_pt){
      lep2_pt=lep1_pt;
      lep2_eta=lep1_eta;
      lep2_phi=lep1_phi;
      lep2_iso=lep1_iso;
      lep2_pdgId=lep1_pdgId;

      lep1_pt=iEle->pt();
      lep1_eta=iEle->eta();
      lep1_phi=iEle->phi();
      lep1_iso=helper.GetElectronRelIso(*iEle);
      lep1_pdgId=iEle->pdgId();
    }
    else if(iEle->pt()>lep2_pt){
      lep2_pt=iEle->pt();
      lep2_eta=iEle->eta();
      lep2_phi=iEle->phi();
      lep2_iso=helper.GetElectronRelIso(*iEle);
      lep2_pdgId=iEle->pdgId();
    }
  }
  
  
  if(input.selectedJets.size()>0){
    jet1_pt=input.selectedJets.at(0).pt();
    jet1_CSVv2=input.selectedJets.at(0).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(input.selectedJets.size()>1){
    jet2_pt=input.selectedJets.at(1).pt();
    jet2_CSVv2=input.selectedJets.at(1).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(input.selectedJets.size()>2){
    jet3_pt=input.selectedJets.at(2).pt();
    jet3_CSVv2=input.selectedJets.at(2).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(input.selectedJets.size()>3){
    jet4_pt=input.selectedJets.at(3).pt();
    jet4_CSVv2=input.selectedJets.at(3).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  n_jets=int(input.selectedJets.size());
  for(auto jet=input.selectedJets.begin();jet!=input.selectedJets.end(); jet++){
    if(BoostedUtils::PassesCSV(*jet)) n_btags++;
  }

  MET_pt=input.pfMET.pt();
  MET_phi=input.pfMET.phi();

  ttHFCategory=input.genTopEvt.GetTTxId();
  if(is_SL||is_DL){
      out <<run<<","<<lumi<<","<<event<<","<<is_SL<<","<<is_DL<<","
	  <<lep1_pt<<","<<lep1_eta<<","<<lep1_phi<<","<<lep1_iso<<","<<lep1_pdgId
	  <<","<<lep2_pt<<","<<lep2_eta<<","<<lep2_phi<<","<<lep2_iso<<","<<lep2_pdgId<<","
	  <<jet1_pt<<","<<jet2_pt<<","<<jet3_pt<<","<<jet4_pt<<","
	  <<jet1_CSVv2<<","<<jet2_CSVv2<<","<<jet3_CSVv2<<","<<jet4_CSVv2<<","
	  <<MET_pt<<","<<MET_phi<<","<<n_jets<<","<<n_btags<<","
	  <<bWeight<<","<<ttHFCategory<<"\n";
  }
}


void Synchronizer::DumpSyncExe2(int nfile,const InputCollections& input, const InputCollections& input_jesup, const InputCollections& input_jesdown, const InputCollections& input_raw, const MiniAODHelper helper){
  DumpSyncExe2(input,helper,*(dumpFiles2[nfile]));
  DumpSyncExe2(input_jesup,helper,*(dumpFiles2_jesup[nfile]));
  DumpSyncExe2(input_jesdown,helper,*(dumpFiles2_jesdown[nfile]));
  DumpSyncExe2(input_raw,helper,*(dumpFiles2_raw[nfile]));
}

void Synchronizer::InitDumpSyncFile1(std::string filename){
    dumpFiles1.push_back(new ofstream((filename+".csv").c_str()));
}

void Synchronizer::InitDumpSyncFile2(std::string filename){
    dumpFiles2.push_back(new ofstream((filename+".csv").c_str()));
    dumpFiles2_jesup.push_back(new ofstream((filename+"_JESup.csv").c_str()));
    dumpFiles2_jesdown.push_back(new ofstream((filename+"_JESdown.csv").c_str()));
    dumpFiles2_raw.push_back(new ofstream((filename+"_raw.csv").c_str()));
    DumpSyncExe2Header(*(dumpFiles2.back()));
    DumpSyncExe2Header(*(dumpFiles2_jesup.back()));
    DumpSyncExe2Header(*(dumpFiles2_jesdown.back()));
    DumpSyncExe2Header(*(dumpFiles2_raw.back()));
}
