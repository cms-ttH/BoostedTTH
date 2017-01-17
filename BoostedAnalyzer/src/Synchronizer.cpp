#include "BoostedTTH/BoostedAnalyzer/interface/Synchronizer.hpp"

using namespace std;

Synchronizer::Synchronizer (){
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


void Synchronizer::DumpSyncExeHeader(std::ostream &out){
    out << "run,lumi,event,is_e,is_mu,is_ee,is_emu,is_mumu,n_jets,n_btags,lep1_pt,lep1_iso,lep1_pdgId,lep2_pt,lep2_iso,lep2_pdgId,jet1_pt,jet1_eta,jet1_phi,jet1_jesSF,jet1_jesSF_up,jet1_jesSF_down,jet1_csv,jet2_pt,jet2_eta,jet2_phi,jet2_jesSF,jet2_jesSF_up,jet2_jesSF_down,jet2_csv,MET_pt,MET_phi,mll,ttHFCategory,n_interactions,puWeight,csvSF,csvSF_lf_up,csvSF_hf_down,csvSF_cErr1_down,pdf_up,pdf_down,me_up,me_down" << endl;
}

void Synchronizer::DumpSyncExe(const InputCollections& input,
			       std::ostream &out,
			       Cutflow& cutflowSL,
			       Cutflow& cutflowDL){

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
    
    bool is_SL=true;
    cutflowSL.EventSurvivedStep("all",input.weights.at("Weight"));
    for(uint i=0; i<selectionsSL.size(); i++){
	if(!selectionsSL[i]->IsSelected(input,cutflowSL)){
	    is_SL=false;
	    break;
	}
    }
    cout << is_SL << endl;
    bool is_DL=true;
    cutflowDL.EventSurvivedStep("all",input.weights.at("Weight"));
    for(uint i=0; i<selectionsDL.size(); i++){
	if(!selectionsDL[i]->IsSelected(input,cutflowDL)){
	    is_DL=false;
	    break;
	}
    }

    cout << is_SL << endl;
    cout << is_DL << endl;

    for(std::vector<pat::Muon>::const_iterator iMuon = input.selectedMuonsLoose.begin(); iMuon != input.selectedMuonsLoose.end(); ++iMuon ){
	if(iMuon->pt()>lep1_pt){
	    lep2_pt=lep1_pt;
	    lep2_iso=lep1_iso;
	    lep2_pdgId=lep1_pdgId;
	    
	    lep1_pt=iMuon->pt();
	    lep1_iso=helper->GetMuonRelIso(*iMuon,coneSize::R04, corrType::deltaBeta);
	    lep1_pdgId=iMuon->pdgId();
	}
	else if(iMuon->pt()>lep2_pt){
	    lep2_pt=iMuon->pt();
	    lep2_iso=helper->GetMuonRelIso(*iMuon,coneSize::R04, corrType::deltaBeta);
	    lep2_pdgId=iMuon->pdgId();
	}
    }
    for(std::vector<pat::Electron>::const_iterator iEle = input.selectedElectronsLoose.begin(); iEle != input.selectedElectronsLoose.end(); ++iEle ){
	if(iEle->pt()>lep1_pt){
	    lep2_pt=lep1_pt;
	    lep2_iso=lep1_iso;
	    lep2_pdgId=lep1_pdgId;
	    
	    lep1_pt=iEle->pt();
	    lep1_iso=helper->GetElectronRelIso(*iEle, coneSize::R03, corrType::rhoEA,effAreaType::spring15);
	    lep1_pdgId=iEle->pdgId();
	}
	else if(iEle->pt()>lep2_pt){
	    lep2_pt=iEle->pt();
	    lep2_iso=helper->GetElectronRelIso(*iEle, coneSize::R03, corrType::rhoEA,effAreaType::spring15);
	    lep2_pdgId=iEle->pdgId();

	}
    }
    if(input.selectedJets.size()>0){
	jet1_pt=input.selectedJets.at(0).pt();
	jet1_csv=MiniAODHelper::GetJetCSV(input.selectedJets.at(0));
    }
    if(input.selectedJets.size()>1){
	jet2_pt=input.selectedJets.at(1).pt();
	jet2_csv=MiniAODHelper::GetJetCSV(input.selectedJets.at(1));
    }
    
    n_jets=int(input.selectedJets.size());
    for(auto jet=input.selectedJets.begin();jet!=input.selectedJets.end(); jet++){
	if(helper->PassesCSV(*jet,'M')) n_btags++;
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
    
    puWeight=input.weights.at("Weight_PU");
    ttHFCategory=input.genTopEvt.GetTTxIdFromProducer();
  
  
  
    out << boost::format("%i,%i,%i,\
%i,%i,%i,%i,%i,\
%i,%i,\
%.4f,%.4f,%i,\
%.4f,%.4f,%i,\
%.4f,%.4f,\
%.4f,%.4f,\
%.4f,%.4f,%.4f,\
%.4f,%.4f,%.4f,\
%i,%i,\
%.4f,\
%.4f,%.4f,%.4f,\
%.4f,%.4f,\
%.4f,%.4f\n")%
	run% lumi% event%
	is_e% is_mu% is_ee% is_emu% is_mumu%
	n_jets% n_btags%
	lep1_pt% lep1_iso% lep1_pdgId%
	lep2_pt% lep2_iso% lep2_pdgId%
	jet1_pt% jet2_pt%
	jet1_csv% jet2_csv%
	jet1_jesSF% jet1_jesSF_up% jet1_jesSF_down%
	MET_pt% MET_phi% mll%
	ttHFCategory% n_interactions%
	puWeight%
	csvSF_lf_up% csvSF_hf_down% csvSF_cErr1_down%
	pdf_up% pdf_down%
	me_up% me_down;
}


void Synchronizer::DumpSyncExe(const std::vector< InputCollections>& inputs){
    for(uint i=0; i<inputs.size(); i++){
	DumpSyncExe(inputs[i],
		    *(dumpFiles[i]),
		    cutflowsSL[i],
		    cutflowsDL[i]);
    }
}




void Synchronizer::Init(std::string filename, const std::vector<std::string>& jetSystematics,const edm::ParameterSet& iConfig,MiniAODHelper* helper_){
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
	DumpSyncExeHeader(*(dumpFiles.back()));
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

    datasetFlag = iConfig.getParameter<std::string>("datasetFlag");
}
