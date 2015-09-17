#include "BoostedTTH/BoostedAnalyzer/interface/Synchronizer.hpp"

using namespace std;

Synchronizer::Synchronizer ():toptagger(TopTag::Likelihood,TopTag::CSV,"toplikelihoodtaggerhistos.root"),bdt3(BDT_v3(BoostedUtils::GetAnalyzerPath()+"/data/bdtweights/weights_v3/")),initializedCutflowsWithSelections(false){
    cutflowSL_nominal.Init();
    cutflowSL_jesup.Init();
    cutflowSL_jesdown.Init();
    cutflowSL_raw.Init();
    cutflowDL_nominal.Init();
    cutflowDL_jesup.Init();
    cutflowDL_jesdown.Init();
    cutflowDL_raw.Init();

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
  cutflowSL_nominal.Print(cout);
  cutflowDL_nominal.Print(cout);
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
    jet1_CSVv2=MiniAODHelper::GetJetCSV(input.selectedJets.at(0),"pfCombinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(input.selectedJets.size()>1){
    jet2_pt=input.selectedJets.at(1).pt();
    jet2_CSVv2=MiniAODHelper::GetJetCSV(input.selectedJets.at(1),"pfCombinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(input.selectedJets.size()>2){
    jet3_pt=input.selectedJets.at(2).pt();
    jet3_CSVv2=MiniAODHelper::GetJetCSV(input.selectedJets.at(2),"pfCombinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(input.selectedJets.size()>3){
    jet4_pt=input.selectedJets.at(3).pt();
    jet4_CSVv2=MiniAODHelper::GetJetCSV(input.selectedJets.at(3),"pfCombinedInclusiveSecondaryVertexV2BJetTags");
  }
  n_jets=int(input.selectedJets.size());
  for(auto jet=input.selectedJets.begin();jet!=input.selectedJets.end(); jet++){
    if(BoostedUtils::PassesCSV(*jet)) n_btags++;
  }
  
  vector<boosted::BoostedJet> syncTopJets;
  for(auto topjet = input.selectedBoostedJets.begin() ; topjet != input.selectedBoostedJets.end(); topjet++ ){
    // pt and eta requirements on top jet
    if( !(topjet->fatjet.pt() > 200. && abs(topjet->fatjet.eta()) < 2.) ) continue;
    std::vector<pat::Jet> subjets;
    subjets.push_back(topjet->W1);
    subjets.push_back(topjet->W2);
    subjets.push_back(topjet->nonW);
    bool subjetcuts=true;
    for(auto j = subjets.begin(); j!=subjets.end();j++){
      if(j->pt()<20 || fabs(j->eta())>2.4) {
	subjetcuts=false;
	break;
      }
    }
    if(!subjetcuts) continue;
    if(toptagger.GetTopTaggerOutput(*topjet)>-1){
      n_toptags++;
      syncTopJets.push_back(*topjet);
    }
  }
  for( auto higgsJet = input.selectedBoostedJets.begin() ; higgsJet != input.selectedBoostedJets.end(); ++higgsJet ){
    // pt and eta requirements on higgs jet
    if( !(higgsJet->fatjet.pt() > 200. && abs(higgsJet->fatjet.eta()) < 2) ) continue;
    bool overlapping=false;
    for(auto tj=syncTopJets.begin(); tj!=syncTopJets.end(); tj++){
      if(BoostedUtils::DeltaR(tj->fatjet,higgsJet->fatjet)<1.5){
	overlapping=true;
	break;
      }
    }
    if(overlapping) continue;
    std::vector<pat::Jet> filterjets = higgsJet->filterjets;
    int subjettags=0;
    for(auto j=filterjets.begin(); j!=filterjets.end(); j++ ){
      if(j->pt()<20 || fabs(j->eta())>2.4) continue;
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
  out <<"run,lumi,event,is_SL,is_DL,lep1_pt,lep1_eta,lep1_phi,lep1_iso,lep1_pdgId,lep2_pt,lep2_eta,lep2_phi,lep2_iso,lep2_pdgId,jet1_pt,jet2_pt,jet3_pt,jet4_pt,jet1_CSVv2,jet2_CSVv2,jet3_CSVv2,jet4_CSVv2,MET_pt,MET_phi,n_jets,n_btags,bWeight,ttHFCategory,final_discriminant1,final_discriminant2,n_fatjets,pt_fatjet_1,pt_fatjet_2,pt_nonW_1,pt_nonW_2,pt_W1_1,pt_W1_2,pt_W2_1,pt_W2_2,m_top_1,m_top_2,higgstag_fatjet_1,higgstag_fatjet_2\n";
}


void Synchronizer::DumpSyncExe2(const InputCollections& input,const InputCollections& input_DL, MiniAODHelper& helper, std::ostream &out,Cutflow& cutflowSL,Cutflow& cutflowDL){
  
  // Setup Selections
  // Single Lepton Selection
  if(leptonSelections.size()==0){
    leptonSelections.push_back(new VertexSelection());
    leptonSelections.push_back(new LeptonSelection("HLT_Ele27_eta2p1_WP85_Gsf_HT200_v1","HLT_IsoMu24_eta2p1_v1"));
    leptonSelections.push_back(new JetTagSelection(4,2));
  }
  if(!initializedCutflowsWithSelections){
    for(uint i=0; i<leptonSelections.size(); i++){
      leptonSelections[i]->InitCutflow(cutflowSL);
    }
  }
  
  // Dilepton Selection
  if(dileptonSelections.size()==0){
    vector<string> elel_triggers;
    vector<string> mumu_triggers;
    vector<string> elmu_triggers;
    elel_triggers.push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1");
    mumu_triggers.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1");
    mumu_triggers.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v1");
    elmu_triggers.push_back("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1");
    elmu_triggers.push_back("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v1");

    dileptonSelections.push_back(new VertexSelection());
    dileptonSelections.push_back(new DiLeptonSelection(elel_triggers,mumu_triggers,elmu_triggers));
    dileptonSelections.push_back(new DiLeptonMassSelection(20,99999,false,true));
    dileptonSelections.push_back(new DiLeptonMassSelection(76,106,true));
    dileptonSelections.push_back(new DiLeptonMETSelection(40,99999));
    dileptonSelections.push_back(new DiLeptonJetTagSelection(2,1));
  }
  if(!initializedCutflowsWithSelections){
    for(uint i=0; i<dileptonSelections.size(); i++){
      dileptonSelections[i]->InitCutflow(cutflowDL);
    }
  }


  // Declare Variables
  int run=input.eventInfo.run;
  int lumi=input.eventInfo.lumiBlock;  
  int event=input.eventInfo.evt;  

  bool is_SL=true;
  bool is_DL=true;

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

  float bWeight=0;

  int ttHFCategory=0;

  float final_discriminant1=0;
  float final_discriminant2=0;

  int n_fatjets=0;
  float pt_fatjet_1=0;
  float pt_fatjet_2=0;
  
  float pt_nonW_1=0;
  float pt_nonW_2=0;
  float pt_W1_1=0;
  float pt_W1_2=0;
  float pt_W2_1=0;
  float pt_W2_2=0;
  float m_top_1=0;
  float m_top_2=0;
  
  float higgstag_fatjet_1=0;
  float higgstag_fatjet_2=0;
  
  cutflowSL.EventSurvivedStep("all",input.weights.at("Weight"));
  for(uint i=0; i<leptonSelections.size(); i++){
      if(!leptonSelections[i]->IsSelected(input,cutflowSL)){
	  is_SL=false;
	  break;
      }
  }
  cutflowDL.EventSurvivedStep("all",input_DL.weights.at("Weight"));
  for(uint i=0; i<dileptonSelections.size(); i++){
      if(!dileptonSelections[i]->IsSelected(input_DL,cutflowDL)){
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
      lep1_iso=helper.GetElectronRelIso(*iEle, coneSize::R03, corrType::rhoEA);
      lep1_pdgId=iEle->pdgId();
    }
    else if(iEle->pt()>lep2_pt){
      lep2_pt=iEle->pt();
      lep2_eta=iEle->eta();
      lep2_phi=iEle->phi();
      lep2_iso=helper.GetElectronRelIso(*iEle, coneSize::R03, corrType::rhoEA);
      lep2_pdgId=iEle->pdgId();
    }
  }
  
  if(is_DL){
  if(input_DL.selectedJets.size()>0){
    jet1_pt=input_DL.selectedJets.at(0).pt();
    jet1_CSVv2=MiniAODHelper::GetJetCSV(input_DL.selectedJets.at(0));
  }
  
  if(input_DL.selectedJets.size()>1){
    jet2_pt=input_DL.selectedJets.at(1).pt();
    jet2_CSVv2=MiniAODHelper::GetJetCSV(input_DL.selectedJets.at(1));
  }
  
  if(input_DL.selectedJets.size()>2){
    jet3_pt=input_DL.selectedJets.at(2).pt();
    jet3_CSVv2=MiniAODHelper::GetJetCSV(input_DL.selectedJets.at(2));
  }
  
  if(input_DL.selectedJets.size()>3){
    jet4_pt=input_DL.selectedJets.at(3).pt();
    jet4_CSVv2=MiniAODHelper::GetJetCSV(input_DL.selectedJets.at(3));
  }
  n_jets=int(input_DL.selectedJets.size());
  for(auto jet=input_DL.selectedJets.begin();jet!=input_DL.selectedJets.end(); jet++){
    if(helper.PassesCSV(*jet,'M')) n_btags++;
  }
  }
  else{
  if(input.selectedJets.size()>0){
    jet1_pt=input.selectedJets.at(0).pt();
    jet1_CSVv2=MiniAODHelper::GetJetCSV(input.selectedJets.at(0));
  }
  
  if(input.selectedJets.size()>1){
    jet2_pt=input.selectedJets.at(1).pt();
    jet2_CSVv2=MiniAODHelper::GetJetCSV(input.selectedJets.at(1));
  }
  
  if(input.selectedJets.size()>2){
    jet3_pt=input.selectedJets.at(2).pt();
    jet3_CSVv2=MiniAODHelper::GetJetCSV(input.selectedJets.at(2));
  }
  
  if(input.selectedJets.size()>3){
    jet4_pt=input.selectedJets.at(3).pt();
    jet4_CSVv2=MiniAODHelper::GetJetCSV(input.selectedJets.at(3));
  }
  n_jets=int(input.selectedJets.size());
  for(auto jet=input.selectedJets.begin();jet!=input.selectedJets.end(); jet++){
    if(helper.PassesCSV(*jet,'M')) n_btags++;
  }
  }

  MET_pt=input.pfMET.pt();
  MET_phi=input.pfMET.phi();
  if(is_SL&&( (n_jets>=4&&n_btags>=3) || (n_jets>=6&&n_btags>=2))){
    final_discriminant1=bdt3.Evaluate(input.selectedMuons,input.selectedElectrons, input.selectedJets, input.selectedJetsLoose, input.pfMET);
  }
   
  n_fatjets = int(input.selectedBoostedJets.size());
  if(input.selectedBoostedJets.size()>0){
    pt_fatjet_1=input.selectedBoostedJets.at(0).fatjet.pt();
    pt_nonW_1=input.selectedBoostedJets.at(0).nonW.pt();
    pt_W1_1=input.selectedBoostedJets.at(0).W1.pt();
    pt_W2_1=input.selectedBoostedJets.at(0).W2.pt();
    m_top_1=input.selectedBoostedJets.at(0).topjet.mass();
  }
  
  if(input.selectedBoostedJets.size()>1){
    pt_fatjet_2=input.selectedBoostedJets.at(1).fatjet.pt();
    pt_nonW_2=input.selectedBoostedJets.at(1).nonW.pt();
    pt_W1_2=input.selectedBoostedJets.at(1).W1.pt();
    pt_W2_2=input.selectedBoostedJets.at(1).W2.pt();
    m_top_2=input.selectedBoostedJets.at(1).topjet.mass();
  }
  
  if(input.selectedBoostedJets.size()>0){
    if(input.selectedBoostedJets.at(0).filterjets.size()>1){
      std::vector<pat::Jet> filterjets = BoostedUtils::GetHiggsFilterJets(input.selectedBoostedJets.at(0));
      higgstag_fatjet_1 = MiniAODHelper::GetJetCSV(filterjets.at(1));
    }
  }
  
  if(input.selectedBoostedJets.size()>1){
    if(input.selectedBoostedJets.at(1).filterjets.size()>1){
      std::vector<pat::Jet> filterjets = BoostedUtils::GetHiggsFilterJets(input.selectedBoostedJets.at(1));
      higgstag_fatjet_2 = MiniAODHelper::GetJetCSV(filterjets.at(1));
    }
  }

  if(is_DL){
    bWeight=input_DL.weights.at("Weight_CSV");
    ttHFCategory=input_DL.genTopEvt.GetTTxIdFromHelper();
  }
  else{
    bWeight=input.weights.at("Weight_CSV");
    ttHFCategory=input.genTopEvt.GetTTxIdFromHelper();
  }

  if(is_SL||is_DL){
      out <<run<<","<<lumi<<","<<event<<","<<is_SL<<","<<is_DL<<","
	  <<lep1_pt<<","<<lep1_eta<<","<<lep1_phi<<","<<lep1_iso<<","<<lep1_pdgId
	  <<","<<lep2_pt<<","<<lep2_eta<<","<<lep2_phi<<","<<lep2_iso<<","<<lep2_pdgId<<","
	  <<jet1_pt<<","<<jet2_pt<<","<<jet3_pt<<","<<jet4_pt<<","
	  <<jet1_CSVv2<<","<<jet2_CSVv2<<","<<jet3_CSVv2<<","<<jet4_CSVv2<<","
	  <<MET_pt<<","<<MET_phi<<","<<n_jets<<","<<n_btags<<","
	  <<bWeight<<","<<ttHFCategory<<","
	  <<final_discriminant1<<","<< final_discriminant2<<","
	  <<n_fatjets<<","<< pt_fatjet_1<<","<< pt_fatjet_2<<","
	  << pt_nonW_1<<","<< pt_nonW_2<<","
	  <<pt_W1_1<<","<< pt_W1_2<<","
	  <<pt_W2_1<<","<< pt_W2_2<<","
	  <<m_top_1<<","<< m_top_2<<","
	  <<higgstag_fatjet_1<<","<< higgstag_fatjet_2 << "\n";
  }
}


void Synchronizer::DumpSyncExe2(int nfile,const InputCollections& input, const InputCollections& input_jesup, const InputCollections& input_jesdown, const InputCollections& input_raw,const InputCollections& input_DL, const InputCollections& input_DL_jesup, const InputCollections& input_DL_jesdown, const InputCollections& input_DL_raw, MiniAODHelper& helper){
  DumpSyncExe2(input,input_DL,helper,*(dumpFiles2[nfile]),cutflowSL_nominal,cutflowDL_nominal);
  DumpSyncExe2(input_jesup,input_DL_jesup,helper,*(dumpFiles2_jesup[nfile]),cutflowSL_jesup,cutflowDL_jesup);
  DumpSyncExe2(input_jesdown,input_DL_jesdown,helper,*(dumpFiles2_jesdown[nfile]),cutflowSL_jesdown,cutflowDL_jesdown);
  DumpSyncExe2(input_raw,input_DL_raw,helper,*(dumpFiles2_raw[nfile]),cutflowSL_raw,cutflowDL_raw);
  initializedCutflowsWithSelections=true;
}

void Synchronizer::InitDumpSyncFile1(std::string filename){
    dumpFiles1.push_back(new ofstream((filename+".txt").c_str()));
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
