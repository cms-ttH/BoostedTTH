#include "BoostedTTH/BoostedAnalyzer/interface/BoostedSynchronizer.hpp"

using namespace std;

BoostedSynchronizer::BoostedSynchronizer ():initializedCutflowsWithSelections(false){
  cutflow_nominal.Init();
  cutflow_jesup.Init();
  cutflow_jesdown.Init();
}


BoostedSynchronizer::~BoostedSynchronizer (){
  for(auto f = dumpFiles.begin(); f!=dumpFiles.end(); f++){
    (*f)->close();
  }
  for(auto f = dumpFiles_jesup.begin(); f!=dumpFiles_jesup.end(); f++){
    (*f)->close();
  }
  for(auto f = dumpFiles_jesdown.begin(); f!=dumpFiles_jesdown.end(); f++){
    (*f)->close();
  }
  if(cutflowFile!=0){
    cutflow_nominal.Print(*cutflowFile);
    cutflow_nominal.Print(cout);
  }
}


void BoostedSynchronizer::InitDumpSyncFile(std::string filename){
    cutflowFile = new ofstream((filename+"-cutflow.log").c_str());
    dumpFiles.push_back(new ofstream((filename+".csv").c_str()));
    dumpFiles_jesup.push_back(new ofstream((filename+"_JESup.csv").c_str()));
    dumpFiles_jesdown.push_back(new ofstream((filename+"_JESdown.csv").c_str()));
    DumpSyncExeHeader(*(dumpFiles.back()));
    DumpSyncExeHeader(*(dumpFiles_jesup.back()));
    DumpSyncExeHeader(*(dumpFiles_jesdown.back()));
}


void BoostedSynchronizer::DumpSyncExeHeader(std::ostream &out){
  out <<"run,lumi,event,"
  <<"is_SL,"
  <<"lep1_pt,lep1_eta,lep1_phi,lep1_iso,lep1_pdgId,"
  <<"n_jets,n_btags,"
  <<"jet1_pt,jet2_pt,jet3_pt,jet4_pt,"
  <<"jet1_CSVv2,jet2_CSVv2,jet3_CSVv2,jet4_CSVv2,"
  <<"n_fatjets,"
  <<"pt_fatjet_1,pt_fatjet_2,"
  <<"eta_fatjet_1,eta_fatjet_2,"
  <<"pt_nonW_1,pt_nonW_2,"
  <<"pt_W1_1,pt_W1_2,"
  <<"pt_W2_1,pt_W2_2,"
  <<"csv_nonW_1,csv_nonW_2,"
  <<"csv_W1_1,csv_W1_2,"
  <<"csv_W2_1,csv_W2_2,"
  <<"pt_top_1,pt_top_2,"
  <<"eta_top_1,eta_top_2,"
  <<"m_top_1,m_top_2,"
  <<"pt_sf_filterjet1_1,pt_sf_filterjet1_2,"
  <<"pt_sf_filterjet2_1,pt_sf_filterjet2_2,"
  <<"pt_sf_filterjet3_1,pt_sf_filterjet3_2,"
  <<"csv_sf_filterjet1_1,csv_sf_filterjet1_2,"
  <<"csv_sf_filterjet2_1,csv_sf_filterjet2_2,"
  <<"csv_sf_filterjet3_1,csv_sf_filterjet3_2,"
  <<"pt_pruned_subjet1_1,pt_pruned_subjet1_2,"
  <<"pt_pruned_subjet2_1,pt_pruned_subjet2_2,"
  <<"csv_pruned_subjet1_1,csv_pruned_subjet1_2,"
  <<"csv_pruned_subjet2_1,csv_pruned_subjet2_2,"
  <<"pt_sd_subjet1_1,pt_sd_subjet1_2,"
  <<"pt_sd_subjet2_1,pt_sd_subjet2_2,"
  <<"csv_sd_subjet1_1,csv_sd_subjet1_2,"
  <<"csv_sd_subjet2_1,csv_sd_subjet2_2,"
  <<"pt_sdz2b1_subjet1_1,pt_sdz2b1_subjet1_2,"
  <<"pt_sdz2b1_subjet2_1,pt_sdz2b1_subjet2_2,"
  <<"csv_sdz2b1_subjet1_1,csv_sdz2b1_subjet1_2,"
  <<"csv_sdz2b1_subjet2_1,csv_sdz2b1_subjet2_2"
  <<"\n";
}


void BoostedSynchronizer::DumpSyncExe(const InputCollections& input, MiniAODHelper& helper, std::ostream &out,Cutflow& cutflowSL){
  
  bool runOverData = true;

  // Setup Selections
  // Single Lepton Selection
  if(selections.size()==0){
    selections.push_back(new VertexSelection());
    if(runOverData) {
	    selections.push_back(new LeptonSelection("HLT_Ele27_eta2p1_WPLoose_Gsf_v*","HLT_IsoMu18_v*"));
    } else {
	    selections.push_back(new LeptonSelection("HLT_Ele27_WP85_Gsf_v*","HLT_IsoMu17_eta2p1_v*"));
    }
    selections.push_back(new JetTagSelection(4,2));
    
    cout << "SL Selection Step 0: VertexSelection" << endl;
    cout << "SL Selection Step 1: LeptonSelection" << endl;
    cout << "SL Selection Step 2: JetTagSelection" << endl;
  }
  if(!initializedCutflowsWithSelections){
    for(uint i=0; i<selections.size(); i++){
      selections[i]->InitCutflow(cutflowSL);
    }
  }

  // Declare Variables
  int run=input.eventInfo.run;
  int lumi=input.eventInfo.lumiBlock;  
  int event=input.eventInfo.evt;  

  bool is_SL=true;

  float lep1_pt=0;
  float lep1_eta=0;
  float lep1_phi=0;
  float lep1_iso=0;
  float lep1_pdgId=0;
  
  int n_jets=0;
  int n_btags=0;

  float jet1_pt=0;
  float jet2_pt=0;
  float jet3_pt=0;
  float jet4_pt=0;

  float jet1_CSVv2=0;
  float jet2_CSVv2=0;
  float jet3_CSVv2=0;
  float jet4_CSVv2=0;

  int n_fatjets=0;
  
  float pt_fatjet_1=0;
  float pt_fatjet_2=0;
  float eta_fatjet_1=0;
  float eta_fatjet_2=0;
  
  float pt_nonW_1=0;
  float pt_nonW_2=0;
  float pt_W1_1=0;
  float pt_W1_2=0;
  float pt_W2_1=0;
  float pt_W2_2=0;
  float csv_nonW_1=0;
  float csv_nonW_2=0;
  float csv_W1_1=0;
  float csv_W1_2=0;
  float csv_W2_1=0;
  float csv_W2_2=0;
  
  float pt_top_1=0;
  float pt_top_2=0;
  float eta_top_1=0;
  float eta_top_2=0;
  float m_top_1=0;
  float m_top_2=0;
  
  float pt_sf_filterjet1_1=0;
  float pt_sf_filterjet1_2=0;
  float pt_sf_filterjet2_1=0;
  float pt_sf_filterjet2_2=0;
  float pt_sf_filterjet3_1=0;
  float pt_sf_filterjet3_2=0;
  float csv_sf_filterjet1_1=0;
  float csv_sf_filterjet1_2=0;
  float csv_sf_filterjet2_1=0;
  float csv_sf_filterjet2_2=0;
  float csv_sf_filterjet3_1=0;
  float csv_sf_filterjet3_2=0;
  
  float pt_pruned_subjet1_1=0;
  float pt_pruned_subjet1_2=0;
  float pt_pruned_subjet2_1=0;
  float pt_pruned_subjet2_2=0;
  float csv_pruned_subjet1_1=0;
  float csv_pruned_subjet1_2=0;
  float csv_pruned_subjet2_1=0;
  float csv_pruned_subjet2_2=0;
  
  float pt_sd_subjet1_1=0;
  float pt_sd_subjet1_2=0;
  float pt_sd_subjet2_1=0;
  float pt_sd_subjet2_2=0;
  float csv_sd_subjet1_1=0;
  float csv_sd_subjet1_2=0;
  float csv_sd_subjet2_1=0;
  float csv_sd_subjet2_2=0;
  
  float pt_sdz2b1_subjet1_1=0;
  float pt_sdz2b1_subjet1_2=0;
  float pt_sdz2b1_subjet2_1=0;
  float pt_sdz2b1_subjet2_2=0;
  float csv_sdz2b1_subjet1_1=0;
  float csv_sdz2b1_subjet1_2=0;
  float csv_sdz2b1_subjet2_1=0;
  float csv_sdz2b1_subjet2_2=0;
      
  bool compare = false;
  
  /*               
  const int nEntries = 6;
  int comparisonList[] = {324990, 904458,2259390, 2844708,277215,1059298}; 

  for(int i = 0;i<nEntries;i++){
    if(event == comparisonList[i]){
      compare = true;
      break;
    }
  }
  */
  
  if(compare) std::cout << "Event: " << event << std::endl;
  
  cutflowSL.EventSurvivedStep("all",input.weights.at("Weight"));
  for(uint i=0; i<selections.size(); i++){
    if(!selections[i]->IsSelected(input,cutflowSL)){
      if(compare) cout << "Event failed SL Selection at step " << i << endl;
	    is_SL=false;
	    break;
    }
  }
   
  //if(!is_SL) return;
  
  if(compare) std::cout << "is_SL: " << is_SL << std::endl;
  
  // leptons
  for(std::vector<pat::Muon>::const_iterator iMuon = input.selectedMuonsLoose.begin(); iMuon != input.selectedMuonsLoose.end(); ++iMuon ){
    if(iMuon->pt()>lep1_pt){
      lep1_pt=iMuon->pt();
      lep1_eta=iMuon->eta();
      lep1_phi=iMuon->phi();
      lep1_iso=helper.GetMuonRelIso(*iMuon,coneSize::R04, corrType::deltaBeta);
      lep1_pdgId=iMuon->pdgId();
    }
  }
  for(std::vector<pat::Electron>::const_iterator iEle = input.selectedElectronsLoose.begin(); iEle != input.selectedElectronsLoose.end(); ++iEle ){
    if(iEle->pt()>lep1_pt){      
      lep1_pt=iEle->pt();
      lep1_eta=iEle->eta();
      lep1_phi=iEle->phi();
      lep1_iso=helper.GetElectronRelIso(*iEle, coneSize::R03, corrType::rhoEA,effAreaType::spring15);
      lep1_pdgId=iEle->pdgId();
    }
  }
  
  // jets
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
  
  // boosted jets
  n_fatjets = int(input.selectedBoostedJets.size());
  if(input.selectedBoostedJets.size()>0){
    pt_fatjet_1=input.selectedBoostedJets.at(0).fatjet.pt();
    eta_fatjet_1=input.selectedBoostedJets.at(0).fatjet.eta();
    
    if(input.selectedBoostedJets.at(0).topjet.pt()>0){
      pt_nonW_1=input.selectedBoostedJets.at(0).nonW.pt();
      pt_W1_1=input.selectedBoostedJets.at(0).W1.pt();
      pt_W2_1=input.selectedBoostedJets.at(0).W2.pt();
      csv_nonW_1=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(0).nonW);
      csv_W1_1=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(0).W1);
      csv_W2_1=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(0).W2);

      pt_top_1=input.selectedBoostedJets.at(0).topjet.pt();
      eta_top_1=input.selectedBoostedJets.at(0).topjet.eta();
      m_top_1=input.selectedBoostedJets.at(0).topjet.mass();
    }
    
    if(input.selectedBoostedJets.at(0).filterjets.size()>0){
      pt_sf_filterjet1_1=input.selectedBoostedJets.at(0).filterjets.at(0).pt();
      csv_sf_filterjet1_1=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(0).filterjets.at(0));
    }
    if(input.selectedBoostedJets.at(0).filterjets.size()>1){
      pt_sf_filterjet2_1=input.selectedBoostedJets.at(0).filterjets.at(1).pt();
      csv_sf_filterjet2_1=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(0).filterjets.at(1));
    }
    if(input.selectedBoostedJets.at(0).filterjets.size()>2){
      pt_sf_filterjet3_1=input.selectedBoostedJets.at(0).filterjets.at(2).pt();
      csv_sf_filterjet3_1=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(0).filterjets.at(2));
    }
    
    if(input.selectedBoostedJets.at(0).prunedsubjets.size()>0){
      pt_pruned_subjet1_1=input.selectedBoostedJets.at(0).prunedsubjets.at(0).pt();
      csv_pruned_subjet1_1=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(0).prunedsubjets.at(0));
    }
    if(input.selectedBoostedJets.at(0).prunedsubjets.size()>1){
      pt_pruned_subjet2_1=input.selectedBoostedJets.at(0).prunedsubjets.at(1).pt();
      csv_pruned_subjet2_1=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(0).prunedsubjets.at(1));
    }

    if(input.selectedBoostedJets.at(0).sdsubjets.size()>0){
      pt_sd_subjet1_1=input.selectedBoostedJets.at(0).sdsubjets.at(0).pt();
      csv_sd_subjet1_1=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(0).sdsubjets.at(0));
    }
    if(input.selectedBoostedJets.at(0).sdsubjets.size()>1){
      pt_sd_subjet2_1=input.selectedBoostedJets.at(0).sdsubjets.at(1).pt();
      csv_sd_subjet2_1=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(0).sdsubjets.at(1));
    }

    if(input.selectedBoostedJets.at(0).sdz2b1subjets.size()>0){
      pt_sdz2b1_subjet1_1=input.selectedBoostedJets.at(0).sdz2b1subjets.at(0).pt();
      csv_sdz2b1_subjet1_1=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(0).sdz2b1subjets.at(0));
    }
    if(input.selectedBoostedJets.at(0).sdz2b1subjets.size()>1){
      pt_sdz2b1_subjet2_1=input.selectedBoostedJets.at(0).sdz2b1subjets.at(1).pt();
      csv_sdz2b1_subjet2_1=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(0).sdz2b1subjets.at(1));
    }   
  }
  
  if(input.selectedBoostedJets.size()>1){
    pt_fatjet_2=input.selectedBoostedJets.at(1).fatjet.pt();
    eta_fatjet_2=input.selectedBoostedJets.at(1).fatjet.eta();
    
    if(input.selectedBoostedJets.at(1).topjet.pt()>0){
      pt_nonW_2=input.selectedBoostedJets.at(1).nonW.pt();
      pt_W1_2=input.selectedBoostedJets.at(1).W1.pt();
      pt_W2_2=input.selectedBoostedJets.at(1).W2.pt();
      csv_nonW_2=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(1).nonW);
      csv_W1_2=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(1).W1);
      csv_W2_2=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(1).W2);

      pt_top_2=input.selectedBoostedJets.at(1).topjet.pt();
      eta_top_2=input.selectedBoostedJets.at(1).topjet.eta();
      m_top_2=input.selectedBoostedJets.at(1).topjet.mass();
    }
    
    if(input.selectedBoostedJets.at(1).filterjets.size()>0){
      pt_sf_filterjet1_2=input.selectedBoostedJets.at(1).filterjets.at(0).pt();
      csv_sf_filterjet1_2=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(1).filterjets.at(0));
    }
    if(input.selectedBoostedJets.at(1).filterjets.size()>1){
      pt_sf_filterjet2_2=input.selectedBoostedJets.at(1).filterjets.at(1).pt();
      csv_sf_filterjet2_2=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(1).filterjets.at(1));
    }
    if(input.selectedBoostedJets.at(1).filterjets.size()>2){
      pt_sf_filterjet3_2=input.selectedBoostedJets.at(1).filterjets.at(2).pt();
      csv_sf_filterjet3_2=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(1).filterjets.at(2));
    }
    
    if(input.selectedBoostedJets.at(1).prunedsubjets.size()>0){
      pt_pruned_subjet1_2=input.selectedBoostedJets.at(1).prunedsubjets.at(0).pt();
      csv_pruned_subjet1_2=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(1).prunedsubjets.at(0));
    }
    if(input.selectedBoostedJets.at(1).prunedsubjets.size()>1){
      pt_pruned_subjet2_2=input.selectedBoostedJets.at(1).prunedsubjets.at(1).pt();
      csv_pruned_subjet2_2=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(1).prunedsubjets.at(1));
    }

    if(input.selectedBoostedJets.at(1).sdsubjets.size()>0){
      pt_sd_subjet1_2=input.selectedBoostedJets.at(1).sdsubjets.at(0).pt();
      csv_sd_subjet1_2=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(1).sdsubjets.at(0));
    }
    if(input.selectedBoostedJets.at(1).sdsubjets.size()>1){
      pt_sd_subjet2_2=input.selectedBoostedJets.at(1).sdsubjets.at(1).pt();
      csv_sd_subjet2_2=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(1).sdsubjets.at(1));
    }

    if(input.selectedBoostedJets.at(1).sdz2b1subjets.size()>0){
      pt_sdz2b1_subjet1_2=input.selectedBoostedJets.at(1).sdz2b1subjets.at(0).pt();
      csv_sdz2b1_subjet1_2=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(1).sdz2b1subjets.at(0));
    }
    if(input.selectedBoostedJets.at(1).sdz2b1subjets.size()>1){
      pt_sdz2b1_subjet2_2=input.selectedBoostedJets.at(1).sdz2b1subjets.at(1).pt();
      csv_sdz2b1_subjet2_2=MiniAODHelper::GetJetCSV(input.selectedBoostedJets.at(1).sdz2b1subjets.at(1));
    }   
  }
    
  if(compare) cout <<run<<","<<lumi<<","<<event<<","
    <<is_SL<<","
	  <<boost::format("%.4f") % lep1_pt<<","<<boost::format("%.4f") % lep1_eta<<","<<boost::format("%.4f") % lep1_phi<<","<<boost::format("%.4f") % lep1_iso<<","<<lep1_pdgId<<","
    <<n_jets<<","<<n_btags<<","
	  <<boost::format("%.4f") % jet1_pt<<","<<boost::format("%.4f") % jet2_pt<<","<<boost::format("%.4f") % jet3_pt<<","<<boost::format("%.4f") % jet4_pt<<","
	  <<boost::format("%.4f") % jet1_CSVv2<<","<<boost::format("%.4f") % jet2_CSVv2<<","<<boost::format("%.4f") % jet3_CSVv2<<","<<boost::format("%.4f") % jet4_CSVv2<<","
	  <<n_fatjets<<","
    <<boost::format("%.4f") % pt_fatjet_1<<","<<boost::format("%.4f") % pt_fatjet_2<<","
	  <<boost::format("%.4f") % eta_fatjet_1<<","<<boost::format("%.4f") % eta_fatjet_2<<","
	  <<boost::format("%.4f") % pt_nonW_1<<","<<boost::format("%.4f") % pt_nonW_2<<","
	  <<boost::format("%.4f") % pt_W1_1<<","<<boost::format("%.4f") % pt_W1_2<<","
	  <<boost::format("%.4f") % pt_W2_1<<","<<boost::format("%.4f") % pt_W2_2<<","
	  <<boost::format("%.4f") % csv_nonW_1<<","<<boost::format("%.4f") % csv_nonW_2<<","
	  <<boost::format("%.4f") % csv_W1_1<<","<<boost::format("%.4f") % csv_W1_2<<","
	  <<boost::format("%.4f") % csv_W2_1<<","<<boost::format("%.4f") % csv_W2_2<<","
	  <<boost::format("%.4f") % pt_top_1<<","<<boost::format("%.4f") % pt_top_2<<","
	  <<boost::format("%.4f") % eta_top_1<<","<<boost::format("%.4f") % eta_top_2<<","
	  <<boost::format("%.4f") % m_top_1<<","<<boost::format("%.4f") % m_top_2<<","
	  <<boost::format("%.4f") % pt_sf_filterjet1_1<<","<<boost::format("%.4f") % pt_sf_filterjet1_2<<","
	  <<boost::format("%.4f") % pt_sf_filterjet2_1<<","<<boost::format("%.4f") % pt_sf_filterjet2_2<<","
	  <<boost::format("%.4f") % pt_sf_filterjet3_1<<","<<boost::format("%.4f") % pt_sf_filterjet3_2<<","
	  <<boost::format("%.4f") % csv_sf_filterjet1_1<<","<<boost::format("%.4f") % csv_sf_filterjet1_2<<","
	  <<boost::format("%.4f") % csv_sf_filterjet2_1<<","<<boost::format("%.4f") % csv_sf_filterjet2_2<<","
	  <<boost::format("%.4f") % csv_sf_filterjet3_1<<","<<boost::format("%.4f") % csv_sf_filterjet3_2<<","
	  <<boost::format("%.4f") % pt_pruned_subjet1_1<<","<<boost::format("%.4f") % pt_pruned_subjet1_2<<","
	  <<boost::format("%.4f") % pt_pruned_subjet2_1<<","<<boost::format("%.4f") % pt_pruned_subjet2_2<<","
	  <<boost::format("%.4f") % csv_pruned_subjet1_1<<","<<boost::format("%.4f") % csv_pruned_subjet1_2<<","
	  <<boost::format("%.4f") % csv_pruned_subjet2_1<<","<<boost::format("%.4f") % csv_pruned_subjet2_2<<","
	  <<boost::format("%.4f") % pt_sd_subjet1_1<<","<<boost::format("%.4f") % pt_sd_subjet1_2<<","
	  <<boost::format("%.4f") % pt_sd_subjet2_1<<","<<boost::format("%.4f") % pt_sd_subjet2_2<<","
	  <<boost::format("%.4f") % csv_sd_subjet1_1<<","<<boost::format("%.4f") % csv_sd_subjet1_2<<","
	  <<boost::format("%.4f") % csv_sd_subjet2_1<<","<<boost::format("%.4f") % csv_sd_subjet2_2<<","
	  <<boost::format("%.4f") % pt_sdz2b1_subjet1_1<<","<<boost::format("%.4f") % pt_sdz2b1_subjet1_2<<","
	  <<boost::format("%.4f") % pt_sdz2b1_subjet2_1<<","<<boost::format("%.4f") % pt_sdz2b1_subjet2_2<<","
	  <<boost::format("%.4f") % csv_sdz2b1_subjet1_1<<","<<boost::format("%.4f") % csv_sdz2b1_subjet1_2<<","
	  <<boost::format("%.4f") % csv_sdz2b1_subjet2_1<<","<<boost::format("%.4f") % csv_sdz2b1_subjet2_2<<"\n";
  
  out <<run<<","<<lumi<<","<<event<<","
  <<is_SL<<","
	<<boost::format("%.4f") % lep1_pt<<","<<boost::format("%.4f") % lep1_eta<<","<<boost::format("%.4f") % lep1_phi<<","<<boost::format("%.4f") % lep1_iso<<","<<lep1_pdgId<<","
  <<n_jets<<","<<n_btags<<","
	<<boost::format("%.4f") % jet1_pt<<","<<boost::format("%.4f") % jet2_pt<<","<<boost::format("%.4f") % jet3_pt<<","<<boost::format("%.4f") % jet4_pt<<","
	<<boost::format("%.4f") % jet1_CSVv2<<","<<boost::format("%.4f") % jet2_CSVv2<<","<<boost::format("%.4f") % jet3_CSVv2<<","<<boost::format("%.4f") % jet4_CSVv2<<","
	<<n_fatjets<<","
  <<boost::format("%.4f") % pt_fatjet_1<<","<<boost::format("%.4f") % pt_fatjet_2<<","
	<<boost::format("%.4f") % eta_fatjet_1<<","<<boost::format("%.4f") % eta_fatjet_2<<","
	<<boost::format("%.4f") % pt_nonW_1<<","<<boost::format("%.4f") % pt_nonW_2<<","
	<<boost::format("%.4f") % pt_W1_1<<","<<boost::format("%.4f") % pt_W1_2<<","
	<<boost::format("%.4f") % pt_W2_1<<","<<boost::format("%.4f") % pt_W2_2<<","
	<<boost::format("%.4f") % csv_nonW_1<<","<<boost::format("%.4f") % csv_nonW_2<<","
	<<boost::format("%.4f") % csv_W1_1<<","<<boost::format("%.4f") % csv_W1_2<<","
	<<boost::format("%.4f") % csv_W2_1<<","<<boost::format("%.4f") % csv_W2_2<<","
  <<boost::format("%.4f") % pt_top_1<<","<<boost::format("%.4f") % pt_top_2<<","
	<<boost::format("%.4f") % eta_top_1<<","<<boost::format("%.4f") % eta_top_2<<","
	<<boost::format("%.4f") % m_top_1<<","<<boost::format("%.4f") % m_top_2<<","
	<<boost::format("%.4f") % pt_sf_filterjet1_1<<","<<boost::format("%.4f") % pt_sf_filterjet1_2<<","
	<<boost::format("%.4f") % pt_sf_filterjet2_1<<","<<boost::format("%.4f") % pt_sf_filterjet2_2<<","
	<<boost::format("%.4f") % pt_sf_filterjet3_1<<","<<boost::format("%.4f") % pt_sf_filterjet3_2<<","
	<<boost::format("%.4f") % csv_sf_filterjet1_1<<","<<boost::format("%.4f") % csv_sf_filterjet1_2<<","
	<<boost::format("%.4f") % csv_sf_filterjet2_1<<","<<boost::format("%.4f") % csv_sf_filterjet2_2<<","
	<<boost::format("%.4f") % csv_sf_filterjet3_1<<","<<boost::format("%.4f") % csv_sf_filterjet3_2<<","
	<<boost::format("%.4f") % pt_pruned_subjet1_1<<","<<boost::format("%.4f") % pt_pruned_subjet1_2<<","
	<<boost::format("%.4f") % pt_pruned_subjet2_1<<","<<boost::format("%.4f") % pt_pruned_subjet2_2<<","
	<<boost::format("%.4f") % csv_pruned_subjet1_1<<","<<boost::format("%.4f") % csv_pruned_subjet1_2<<","
	<<boost::format("%.4f") % csv_pruned_subjet2_1<<","<<boost::format("%.4f") % csv_pruned_subjet2_2<<","
	<<boost::format("%.4f") % pt_sd_subjet1_1<<","<<boost::format("%.4f") % pt_sd_subjet1_2<<","
	<<boost::format("%.4f") % pt_sd_subjet2_1<<","<<boost::format("%.4f") % pt_sd_subjet2_2<<","
	<<boost::format("%.4f") % csv_sd_subjet1_1<<","<<boost::format("%.4f") % csv_sd_subjet1_2<<","
	<<boost::format("%.4f") % csv_sd_subjet2_1<<","<<boost::format("%.4f") % csv_sd_subjet2_2<<","
	<<boost::format("%.4f") % pt_sdz2b1_subjet1_1<<","<<boost::format("%.4f") % pt_sdz2b1_subjet1_2<<","
	<<boost::format("%.4f") % pt_sdz2b1_subjet2_1<<","<<boost::format("%.4f") % pt_sdz2b1_subjet2_2<<","
	<<boost::format("%.4f") % csv_sdz2b1_subjet1_1<<","<<boost::format("%.4f") % csv_sdz2b1_subjet1_2<<","
	<<boost::format("%.4f") % csv_sdz2b1_subjet2_1<<","<<boost::format("%.4f") % csv_sdz2b1_subjet2_2<<"\n";
}


void BoostedSynchronizer::DumpSyncExe(int nfile,const InputCollections& input, const InputCollections& input_jesup, const InputCollections& input_jesdown, MiniAODHelper& helper){
  DumpSyncExe(input,helper,*(dumpFiles[nfile]),cutflow_nominal);
  DumpSyncExe(input_jesup,helper,*(dumpFiles_jesup[nfile]),cutflow_jesup);
  DumpSyncExe(input_jesdown,helper,*(dumpFiles_jesdown[nfile]),cutflow_jesdown);
  initializedCutflowsWithSelections=true;
}
