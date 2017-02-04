#include "BoostedTTH/BoostedAnalyzer/interface/Synchronizer.hpp"

using namespace std;

Synchronizer::Synchronizer (const edm::ParameterSet& iConfig,edm::ConsumesCollector && iC){
    rawElToken = iC.consumes< std::vector<pat::Electron> > (edm::InputTag("slimmedElectrons"));
    rawMuToken = iC.consumes< std::vector<pat::Muon> > (edm::InputTag("slimmedMuons"));
}


Synchronizer::~Synchronizer (){
    cout << "Finishing Synch" << endl;
    for(auto f = dumpFiles.begin(); f!=dumpFiles.end(); f++){
	(*f)->close();
    }
    cout << "Systematics used: ";
    for(const auto & s : systematics){
	cout << s;
    }
    cout << endl;
    cout << "Cutflows SL: ";
    for(auto & c : cutflowsSL){
	c.Print(cout);
    }
    cout << endl;
    cout << "Cutflows DL: ";
    for(auto & c : cutflowsDL){
	c.Print(cout);
    }
    cout << endl;
}


void Synchronizer::DumpSyncExeHeader(std::ostream &out, bool addExtendedInfo){
    out << "run,lumi,event,is_e,is_mu,is_ee,is_emu,is_mumu,n_jets,n_btags,lep1_pt,lep1_iso,lep1_pdgId,lep2_pt,lep2_iso,lep2_pdgId,jet1_pt,jet1_eta,jet1_phi,jet1_jesSF,jet1_jesSF_up,jet1_jesSF_down,jet1_csv,jet2_pt,jet2_eta,jet2_phi,jet2_jesSF,jet2_jesSF_up,jet2_jesSF_down,jet2_csv,MET_pt,MET_phi,mll,ttHFCategory,n_interactions,puWeight,csvSF,csvSF_lf_up,csvSF_hf_down,csvSF_cErr1_down,pdf_up,pdf_down,me_up,me_down";
    if(addExtendedInfo){
	out << ",jet3_pt,jet3_eta,jet3_csv,jet4_pt,jet4_eta,jet4_csv,jet5_pt,jet5_eta,jet5_csv";
	out << ",trig_el,trig_mu,trig_elel,trig_elmu,trig_mumu";
	out << ",n_leps_tight,n_leps_dl,n_leps_loose";
	out << ",raw_el1_pt,raw_el1_eta,raw_el1_iso,raw_el1_pdgId,raw_el2_pt,raw_el2_eta,raw_el2_iso,raw_el2_pdgId";
	out << ",raw_mu1_pt,raw_mu1_eta,raw_mu1_iso,raw_mu1_pdgId,raw_mu2_pt,raw_mu2_eta,raw_mu2_iso,raw_mu2_pdgId";
	out << ",pass_FilterSelection,pass_VertexSelection,pass_LeptonSelection,pass_DiLeptonSelection";
	    
    }
    out << endl;
}

void Synchronizer::DumpSyncExe(const InputCollections& input,
			       std::ostream &out,
			       Cutflow& cutflowSL,
			       Cutflow& cutflowDL,
			       bool addExtendedInfo,
			       std::vector<int> dumpAlwaysEvents){

    edm::Handle< std::vector<pat::Muon> > h_rawMu;
    input.iEvent.getByToken( rawMuToken,h_rawMu );
    edm::Handle< std::vector<pat::Electron> > h_rawEl;
    input.iEvent.getByToken( rawElToken,h_rawEl );

    int run=input.eventInfo.run;
    int lumi=input.eventInfo.lumiBlock;
    long event=input.eventInfo.evt;
    
    int is_e=-1;
    int is_mu=-1;
    int is_ee=-1;
    int is_emu=-1;
    int is_mumu=-1;
    
    int n_jets=-1;
    int n_btags=-1;
    
    float lep1_pt=-1;
    float lep1_iso=-1;
    int lep1_pdgId=-1;
    
    float lep2_pt=-1;
    float lep2_iso=-1;
    int lep2_pdgId=-1;
    
    float jet1_pt=-1;
    float jet1_eta=-1;
    float jet1_phi=-1;
    float jet1_jesSF=-1;
    float jet1_jesSF_up=-1;
    float jet1_jesSF_down=-1;
    float jet1_csv=-1;
    
    float jet2_pt=-1;
    float jet2_eta=-1;
    float jet2_phi=-1;
    float jet2_jesSF=-1;
    float jet2_jesSF_up=-1;
    float jet2_jesSF_down=-1;
    float jet2_csv=-1;
    
    float MET_pt=-1;
    float MET_phi=-1;
    
    float mll=-1;
    
    int ttHFCategory=-1;
    
    int n_interactions=-1;
    
    float puWeight=-1;
    
    float csvSF=-1;
    float csvSF_lf_up=-1;
    float csvSF_hf_down=-1;
    float csvSF_cErr1_down=-1;
    
    float pdf_up=-1;
    float pdf_down=-1;
    
    float me_up=-1;
    float me_down=-1;

    float jet3_pt=-1;
    float jet3_eta=-1;
    float jet3_csv=-1;
    float jet4_pt=-1;
    float jet4_eta=-1;
    float jet4_csv=-1;
    float jet5_pt=-1;
    float jet5_eta=-1;
    float jet5_csv=-1;
    int n_leps_tight=-1;
    int n_leps_dl=-1;
    int n_leps_loose=-1;

    float raw_mu1_pt=-1;
    float raw_mu1_eta=-1;
    float raw_mu1_iso=-1;
    float raw_mu1_pdgId=-1;
    float raw_mu2_pt=-1;
    float raw_mu2_eta=-1;
    float raw_mu2_iso=-1;
    float raw_mu2_pdgId=-1;
    float raw_el1_pt=-1;
    float raw_el1_eta=-1;
    float raw_el1_iso=-1;
    float raw_el1_pdgId=-1;
    float raw_el2_pt=-1;
    float raw_el2_eta=-1;
    float raw_el2_iso=-1;
    float raw_el2_pdgId=-1;
    int trig_el=-1;
    int trig_mu=-1;
    int trig_elel=-1;
    int trig_elmu=-1;
    int trig_mumu=-1;
    int pass_FilterSelection=-1;
    int pass_VertexSelection=-1;
    int pass_LeptonSelection=-1;
    int pass_DiLeptonSelection=-1;

    //=================================================
    for(std::vector<pat::Muon>::const_iterator iMuon = input.selectedMuonsLoose.begin(); iMuon != input.selectedMuonsLoose.end(); ++iMuon ){
	if(iMuon->pt()>lep1_pt){
	    lep2_pt=lep1_pt;
	    lep2_iso=lep1_iso;
	    lep2_pdgId=lep1_pdgId;
	    
	    lep1_pt=iMuon->pt();
	    if(iMuon->hasUserFloat("relIso")) lep1_iso= iMuon->userFloat("relIso");
	    lep1_pdgId=iMuon->pdgId();
	}
	else if(iMuon->pt()>lep2_pt){
	    lep2_pt=iMuon->pt();
	    if(iMuon->hasUserFloat("relIso")) lep2_iso= iMuon->userFloat("relIso");
	    lep2_pdgId=iMuon->pdgId();
	}
    }
    for(std::vector<pat::Electron>::const_iterator iEle = input.selectedElectronsLoose.begin(); iEle != input.selectedElectronsLoose.end(); ++iEle ){
	if(iEle->pt()>lep1_pt){
	    lep2_pt=lep1_pt;
	    lep2_iso=lep1_iso;
	    lep2_pdgId=lep1_pdgId;
	    
	    lep1_pt=iEle->pt();
	    if(iEle->hasUserFloat("relIso")) lep1_iso= iEle->userFloat("relIso");
	    lep1_pdgId=iEle->pdgId();
	}
	else if(iEle->pt()>lep2_pt){
	    lep2_pt=iEle->pt();
	    if(iEle->hasUserFloat("relIso")) lep2_iso= iEle->userFloat("relIso");
	    lep2_pdgId=iEle->pdgId();

	}
    }


    bool is_SL=true;
    cutflowSL.EventSurvivedStep("all",input.weights.at("Weight"));
    for(uint i=0; i<selectionsSL.size(); i++){
	if(!selectionsSL[i]->IsSelected(input,cutflowSL)){
	    is_SL=false;
	    if(i==0) pass_FilterSelection=0;
	    if(i==1) pass_VertexSelection=0;
	    if(i==2) pass_LeptonSelection=0;

	    break;
	}
	else{
	    if(i==0) pass_FilterSelection=1;
	    if(i==1) pass_VertexSelection=1;
	    if(i==2) pass_LeptonSelection=1;
	}
    }
    if(is_SL){
	if(abs(lep1_pdgId)==11) {
	    is_e=1;
	    is_mu=0;
	}
	else if(abs(lep1_pdgId)==13){
	    is_mu=1;
	    is_e=0;
	}
    }
    else{
	is_e=0;
	is_mu=0;
    }

    bool is_DL=true;
    cutflowDL.EventSurvivedStep("all",input.weights.at("Weight"));
    for(uint i=0; i<selectionsDL.size(); i++){
	if(!selectionsDL[i]->IsSelected(input,cutflowDL)){
	    is_DL=false;
	    if(i==2) pass_DiLeptonSelection=0;
	    break;
	}
	else{
	    if(i==2) pass_DiLeptonSelection=1;
	}
    }
    if(is_DL){
	if(abs(lep1_pdgId)==11&&abs(lep2_pdgId)==11) {
	    is_ee=1;
	    is_emu=0;
	    is_mumu=0;
	}
	else if( (abs(lep1_pdgId)==11&&abs(lep2_pdgId)==13) || (abs(lep1_pdgId)==13&&abs(lep2_pdgId)==11) ){
	    is_ee=0;
	    is_emu=1;
	    is_mumu=0;
	}
	if(abs(lep1_pdgId)==13&&abs(lep2_pdgId)==13) {
	    is_ee=0;
	    is_emu=0;
	    is_mumu=1;
	}

    }
    else{
	    is_ee=0;
	    is_emu=0;
	    is_mumu=0;
    }

    if(input.selectedJets.size()>0){
	jet1_pt=input.selectedJets.at(0).pt();
	jet1_eta=input.selectedJets.at(0).eta();
	jet1_phi=input.selectedJets.at(0).phi();
	jet1_csv=MiniAODHelper::GetJetCSV(input.selectedJets.at(0));
	if(input.selectedJets.at(0).hasUserFloat("HelperJES")) jet1_jesSF=input.selectedJets.at(0).userFloat("HelperJES");
	if(input.selectedJets.at(0).hasUserFloat("HelperJESUp")) jet1_jesSF_up=input.selectedJets.at(0).userFloat("HelperJESUp");
	if(input.selectedJets.at(0).hasUserFloat("HelperJESDown")) jet1_jesSF_down=input.selectedJets.at(0).userFloat("HelperJESDown");

    }

    if(input.selectedJets.size()>1){
	jet2_pt=input.selectedJets.at(1).pt();
	jet2_eta=input.selectedJets.at(1).eta();
	jet2_phi=input.selectedJets.at(1).phi();
	jet2_csv=MiniAODHelper::GetJetCSV(input.selectedJets.at(1));
	if(input.selectedJets.at(1).hasUserFloat("HelperJES")) jet2_jesSF=input.selectedJets.at(1).userFloat("HelperJES");
	if(input.selectedJets.at(1).hasUserFloat("HelperJESUp")) jet2_jesSF_up=input.selectedJets.at(1).userFloat("HelperJESUp");
	if(input.selectedJets.at(1).hasUserFloat("HelperJESDown")) jet2_jesSF_down=input.selectedJets.at(1).userFloat("HelperJESDown");
    }
    if(input.selectedJetsLoose.size()>2){
	jet3_pt=input.selectedJetsLoose.at(2).pt();
	jet3_eta=input.selectedJetsLoose.at(2).eta();
	jet3_csv=MiniAODHelper::GetJetCSV(input.selectedJetsLoose.at(2));
    }
    if(input.selectedJetsLoose.size()>3){
	jet4_pt=input.selectedJetsLoose.at(3).pt();
	jet4_eta=input.selectedJetsLoose.at(3).eta();
	jet4_csv=MiniAODHelper::GetJetCSV(input.selectedJetsLoose.at(3));
    }
    if(input.selectedJetsLoose.size()>4){
	jet5_pt=input.selectedJetsLoose.at(4).pt();
	jet5_eta=input.selectedJetsLoose.at(4).eta();
	jet5_csv=MiniAODHelper::GetJetCSV(input.selectedJetsLoose.at(4));
    }
    n_leps_tight=input.selectedMuons.size()+input.selectedElectrons.size();
    n_leps_dl=input.selectedMuonsDL.size()+input.selectedElectronsDL.size();
    n_leps_loose=input.selectedMuonsLoose.size()+input.selectedElectronsLoose.size();
    if(h_rawMu->size()>0){
	raw_mu1_pt=h_rawMu->at(0).pt();
	raw_mu1_eta=h_rawMu->at(0).eta();
	raw_mu1_iso=helper->GetMuonRelIso(h_rawMu->at(0),coneSize::R04,corrType::deltaBeta);
	raw_mu1_pdgId=h_rawMu->at(0).pdgId();
    }
    if(h_rawMu->size()>1){
	raw_mu2_pt=h_rawMu->at(1).pt();
	raw_mu2_eta=h_rawMu->at(1).eta();
	raw_mu2_iso=helper->GetMuonRelIso(h_rawMu->at(1),coneSize::R04,corrType::deltaBeta);
	raw_mu2_pdgId=h_rawMu->at(1).pdgId();
    }
    if(h_rawEl->size()>0){
	raw_el1_pt=h_rawEl->at(0).pt();
	raw_el1_eta=h_rawEl->at(0).eta();
	raw_el1_iso=helper->GetElectronRelIso(h_rawEl->at(0), coneSize::R03, corrType::rhoEA,effAreaType::spring16);
	raw_el1_pdgId=h_rawEl->at(0).pdgId();
    }
    if(h_rawEl->size()>1){
	raw_el2_pt=h_rawEl->at(1).pt();
	raw_el2_eta=h_rawEl->at(1).eta();
	raw_el2_iso=helper->GetElectronRelIso(h_rawEl->at(1), coneSize::R03, corrType::rhoEA,effAreaType::spring16);
	raw_el2_pdgId=h_rawEl->at(1).pdgId();
    }


    trig_el=input.triggerInfo.IsTriggered("HLT_IsoMu24_v*")||input.triggerInfo.IsTriggered("HLT_IsoTkMu24_v*");
    trig_mu=input.triggerInfo.IsTriggered("HLT_Ele27_eta2p1_WPTight_Gsf_v*");
    trig_elel=input.triggerInfo.IsTriggered("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*");
    trig_elmu=input.triggerInfo.IsTriggered("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*")
	|| input.triggerInfo.IsTriggered("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*")
	|| input.triggerInfo.IsTriggered("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*")
	|| input.triggerInfo.IsTriggered("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*");
    trig_mumu=input.triggerInfo.IsTriggered("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v*")
	|| input.triggerInfo.IsTriggered("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v*")
	|| input.triggerInfo.IsTriggered("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*")
	|| input.triggerInfo.IsTriggered("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*");


    
    if(is_DL) {
	n_jets=int(input.selectedJetsLoose.size());
	n_btags=0;
	for(auto jet=input.selectedJetsLoose.begin();jet!=input.selectedJetsLoose.end(); jet++){
	    if(helper->PassesCSV(*jet,'M')) n_btags++;
	}
    }
    else{
	n_jets=int(input.selectedJets.size());
	n_btags=0;
	for(auto jet=input.selectedJets.begin();jet!=input.selectedJets.end(); jet++){
	    if(helper->PassesCSV(*jet,'M')) n_btags++;
	}
    }
    //calculate mll
    if(is_DL){
	math::XYZTLorentzVector vec1;
	math::XYZTLorentzVector vec2;
	bool calculateMll=false;
	if(input.selectedMuonsLoose.size()==2 && input.selectedElectronsLoose.size()==0){
	    vec1=input.selectedMuonsLoose[0].p4();
	    vec2=input.selectedMuonsLoose[1].p4();
	    calculateMll=true;
	}
	else if(input.selectedMuonsLoose.size()==0 && input.selectedElectronsLoose.size()==2){
	    vec1=input.selectedElectronsLoose[0].p4();
	    vec2=input.selectedElectronsLoose[1].p4();
	    calculateMll=true;
	}
	else if(input.selectedMuonsLoose.size()==1 && input.selectedElectronsLoose.size()==1){
	    vec1=input.selectedMuonsLoose[0].p4();
	    vec2=input.selectedElectronsLoose[0].p4();
	    calculateMll=true;
	}
	else {
	    std::cout<<"PROBLEM we have !=2 leptons in DiLeptonSelection"<<std::endl;
      }
	
	if(calculateMll){
	    mll=(vec1+vec2).M();
	}
    }
    
    MET_pt=input.correctedMET.pt();
    MET_phi=input.correctedMET.phi();
    
    if(input.weights.count("Weight_PU")>0) puWeight=input.weights.at("Weight_PU");
    ttHFCategory=input.genTopEvt.GetTTxIdFromProducerLong();
    n_interactions=input.eventInfo.numTruePV;
      
    if(input.weights.count("Weight_CSV")>0)    csvSF=input.weights.at("Weight_CSV");
    if(input.weights.count("Weight_CSVLFup")>0) csvSF_lf_up=input.weights.at("Weight_CSV")*input.weights.at("Weight_CSVLFup");
    if(input.weights.count("Weight_CSVHFdown")>0) csvSF_hf_down=input.weights.at("Weight_CSV")*input.weights.at("Weight_CSVHFdown");
    if(input.weights.count("Weight_CSVCErr1down")>0) csvSF_cErr1_down=input.weights.at("Weight_CSV")*input.weights.at("Weight_CSVCErr1down");

    if(input.weights.count("Weight_muRupmuFup")>0) me_up =input.weights.at("Weight_muRupmuFup");
    if(input.weights.count("Weight_muRdownmuFdown")>0) me_down =input.weights.at("Weight_muRdownmuFdown");

    bool print=false;
    if (dataset=="NA" && (is_SL || is_DL)) print =true;
    if (dataset=="el"&&is_e) print =true;
    if (dataset=="mu"&&is_mu) print =true;
    if (dataset=="elel"&&is_ee) print =true;
    if (dataset=="elmu"&&is_emu) print =true;
    if (dataset=="mumu"&&is_mumu) print =true;

    for(uint i=0; i<dumpAlwaysEvents.size(); i++){
	if (dumpAlwaysEvents[i]==event){
	    print=true;
	    break;
	}       
    }
    if(print){ out << boost::format("%i,%i,%i,\
%i,%i,%i,%i,%i,\
%i,%i,\
%.4f,%.4f,%i,\
%.4f,%.4f,%i,\
%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,\
%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,\
%.4f,%.4f,%.4f,\
%i,%i,\
%.4f,\
%.4f,%.4f,%.4f,%.4f,\
%.4f,%.4f,\
%.4f,%.4f")%
	run% lumi% event%
	is_e% is_mu% is_ee% is_emu% is_mumu%
	n_jets% n_btags%
	lep1_pt% lep1_iso% lep1_pdgId%
	lep2_pt% lep2_iso% lep2_pdgId%
	jet1_pt% jet1_eta% jet1_phi% jet1_jesSF% jet1_jesSF_up% jet1_jesSF_down% jet1_csv% 
	jet2_pt% jet2_eta% jet2_phi% jet2_jesSF% jet2_jesSF_up% jet2_jesSF_down% jet2_csv% 	
	MET_pt% MET_phi% mll%
	ttHFCategory% n_interactions%
	puWeight%
	csvSF% csvSF_lf_up% csvSF_hf_down% csvSF_cErr1_down%
	pdf_up% pdf_down%
	me_up% me_down;
	if(addExtendedInfo){
	    out << boost::format(",%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f")%jet3_pt%jet3_eta%jet3_csv%jet4_pt%jet4_eta%jet4_csv%jet5_pt%jet5_eta%jet5_csv;
	    out << boost::format(",%i,%i,%i,%i,%i")%trig_el%trig_mu%trig_elel%trig_elmu%trig_mumu;
	    out << boost::format(",%i,%i,%i")%n_leps_tight%n_leps_dl%n_leps_loose;
	    out << boost::format(",%.4f,%.4f,%.4f,%i,%.4f,%.4f,%.4f,%i")%raw_el1_pt%raw_el1_eta%raw_el1_iso%raw_el1_pdgId%raw_el2_pt%raw_el2_eta%raw_el2_iso%raw_el2_pdgId;
	    out << boost::format(",%.4f,%.4f,%.4f,%i,%.4f,%.4f,%.4f,%i")%raw_mu1_pt%raw_mu1_eta%raw_mu1_iso%raw_mu1_pdgId%raw_mu2_pt%raw_mu2_eta%raw_mu2_iso%raw_mu2_pdgId;
	    out << boost::format(",%i,%i,%i,%i")%pass_FilterSelection%pass_VertexSelection%pass_LeptonSelection%pass_DiLeptonSelection;
	}
	out<<"\n";
    }
}


void Synchronizer::DumpSyncExe(const std::vector< InputCollections>& inputs, bool addExtendedInfo,  std::vector<int> dumpAlwaysEvents){
    for(uint i=0; i<inputs.size(); i++){
	DumpSyncExe(inputs[i],
		    *(dumpFiles[i]),
		    cutflowsSL[i],
		    cutflowsDL[i],
		    addExtendedInfo,
		    dumpAlwaysEvents);
    }
}




void Synchronizer::Init(std::string filename, const std::vector<std::string>& jetSystematics,const edm::ParameterSet& iConfig,MiniAODHelper* helper_,bool dumpExtended){
    systematics=jetSystematics;
    helper=helper_;
    for(const auto & s : systematics){
	cutflowsSL.push_back(Cutflow());
	cutflowsSL.back().Init();
	//	cutflowFilesSL.push_back(new ofstream((filename+"_"+s+"_cutflowSL.log").c_str()));
	cutflowsDL.push_back(Cutflow());
	cutflowsDL.back().Init();
	//	cutflowFilesDL.push_back(new ofstream((filename+"_"+s+"_cutflowDL.log").c_str()));
	dumpFiles.push_back(new ofstream((filename+"_"+s+".csv").c_str()));
	DumpSyncExeHeader(*(dumpFiles.back()),dumpExtended);
    }
    selectionsDL.push_back(new FilterSelection(iConfig));
    selectionsDL.push_back(new VertexSelection());
    selectionsDL.push_back(new DiLeptonSelection(iConfig));
    selectionsDL.push_back(new DiLeptonMassSelection(20,99999,false,true));
    selectionsDL.push_back(new DiLeptonMassSelection(76,106,true,false));
    selectionsDL.push_back(new DiLeptonMETSelection(40,99999));
    selectionsDL.push_back(new DiLeptonJetTagSelection(2,1));
    for (auto &c : cutflowsDL){
	for (auto &s : selectionsDL){
	    s->InitCutflow(c);
	}
    }

    selectionsSL.push_back(new FilterSelection(iConfig));
    selectionsSL.push_back(new VertexSelection());
    selectionsSL.push_back(new LeptonSelection(iConfig));
    selectionsSL.push_back(new JetTagSelection(4,2));
    for (auto &c : cutflowsSL){
	for (auto &s : selectionsSL){
	    s->InitCutflow(c);
	}
    }

    dataset = iConfig.getParameter<std::string>("dataset");
    isData = iConfig.getParameter<bool>("isData");
}
