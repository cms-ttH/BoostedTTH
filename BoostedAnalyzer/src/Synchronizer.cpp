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
    for(auto &sel : selectionsSL) {
        delete sel;
    }
    for(auto &sel : selectionsDL) {
        delete sel;
    }
}


void Synchronizer::DumpSyncExeHeader(std::ostream &out, bool addExtendedInfo){
    out << "run,lumi,event,is_e,is_mu,is_ee,is_emu,is_mumu,n_jets,n_btags,lep1_pt,lep1_eta,lep1_iso,lep1_pdgId,lep1_idSF,lep1_isoSF,lep1_seed,lep2_pt,lep2_eta,lep2_iso,lep2_pdgId,lep2_idSF,lep2_isoSF,lep2_seed,jet1_pt,jet1_eta,jet1_phi,jet1_jesSF,jet1_jesSF_up,jet1_jesSF_down,jet1_jesSF_PileUpDataMC_down,jet1_jesSF_RelativeFSR_up,jet1_jerSF_nominal,jet1_csv,jet1_PUJetId,jet1_PUJetDiscriminant,jet1_seed,jet2_pt,jet2_eta,jet2_phi,jet2_jesSF,jet2_jesSF_up,jet2_jesSF_down,jet2_jesSF_PileUpDataMC_down,jet2_jesSF_RelativeFSR_up,jet2_jerSF_nominal,jet2_csv,jet2_PUJetId,jet2_PUJetDiscriminant,jet2_seed,MET_pt,MET_phi,mll,ttHFCategory,ttHFGenFilterTag,n_interactions,puWeight,csvSF,csvSF_lf_up,csvSF_hf_down,csvSF_cErr1_down,pdf_up,pdf_down,me_up,me_down,isr_up,isr_down,fsr_up,fsr_down,triggerSF,top_pt_weight,bdt_output,dnn_ttH_output,dnn_ttbb_output";
    if(addExtendedInfo){
	out << ",jet3_pt,jet3_eta,jet3_csv,jet4_pt,jet4_eta,jet4_csv,jet5_pt,jet5_eta,jet5_csv,jet6_pt,jet6_eta,jet6_csv,jet7_pt,jet7_eta,jet7_csv";
	out << ",trig_el,trig_mu,trig_elel,trig_elmu,trig_mumu";
	out << ",n_leps_tight,n_leps_dl,n_leps_loose,rho";
	out << ",raw_el1_pt,raw_el1_eta,raw_el1_iso,raw_el1_pdgId,raw_el2_pt,raw_el2_eta,raw_el2_iso,raw_el2_pdgId";
	out << ",raw_mu1_pt,raw_mu1_eta,raw_mu1_iso,raw_mu1_pdgId,raw_mu2_pt,raw_mu2_eta,raw_mu2_iso,raw_mu2_pdgId";
	out << ",pass_FilterSelection,pass_VertexSelection,pass_LeptonSelection,pass_DiLeptonSelection,pass_METSelection";
	    
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
    float rho = input.eventInfo.rho;
    
    int is_e=-1;
    int is_mu=-1;
    int is_ee=-1;
    int is_emu=-1;
    int is_mumu=-1;
    
    int n_jets=-1;
    int n_btags=-1;
    
    float lep1_pt=-1;
    float lep1_iso=-1;
    float lep1_eta=-1;
    int lep1_pdgId=-1;
    float lep1_idSF=-1;
    float lep1_isoSF=-1;
    uint32_t lep1_seed=0;
    
    float lep2_pt=-1;
    float lep2_iso=-1;
    float lep2_eta=-1;
    int lep2_pdgId=-1;
    float lep2_idSF=-1;
    float lep2_isoSF=-1;
    uint32_t lep2_seed=0;
    
    float jet1_pt=-1;
    float jet1_eta=-1;
    float jet1_phi=-1;
    float jet1_jesSF=-1;
    float jet1_jesSF_up=-1;
    float jet1_jesSF_down=-1;
    float jet1_jesSF_PileUpDataMC_down=-1;
    float jet1_jesSF_RelativeFSR_up=-1;
    float jet1_jerSF_nominal=-1;
    //float jet1_jerSF_up=-1;
    //float jet1_jerSF_down=-1;
    float jet1_csv=-1;
    int jet1_PUJetId=-1;
    float jet1_PUJetDiscriminant=-1;
    uint32_t jet1_seed=0;
    
    float jet2_pt=-1;
    float jet2_eta=-1;
    float jet2_phi=-1;
    float jet2_jesSF=-1;
    float jet2_jesSF_up=-1;
    float jet2_jesSF_down=-1;
    float jet2_jesSF_PileUpDataMC_down=-1;
    float jet2_jesSF_RelativeFSR_up=-1;
    float jet2_jerSF_nominal=-1;
    //float jet2_jerSF_up=-1;
    //float jet2_jerSF_down=-1;
    float jet2_csv=-1;
    int jet2_PUJetId=-1;
    float jet2_PUJetDiscriminant=-1;
    uint32_t jet2_seed=0;
    
    float MET_pt=-1;
    float MET_phi=-1;
    
    float mll=-1;
    
    int ttHFCategory=-1;
    int ttHFGenFilterTag=-1;
    
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
    
    float isr_up=-1;
    float isr_down=-1;
    float fsr_up=-1;
    float fsr_down=-1;
    
    float triggerSF=-1;
    float top_pt_weight=-1;
    float bdt_output=-1;
    float dnn_ttH_output=-1;
    float dnn_ttbb_output=-1;

    float jet3_pt=-1;
    float jet3_eta=-1;
    float jet3_csv=-1;
    float jet4_pt=-1;
    float jet4_eta=-1;
    float jet4_csv=-1;
    float jet5_pt=-1;
    float jet5_eta=-1;
    float jet5_csv=-1;
    float jet6_pt=-1;
    float jet6_eta=-1;
    float jet6_csv=-1;
    float jet7_pt=-1;
    float jet7_eta=-1;
    float jet7_csv=-1;
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
    int pass_METSelection=-1;
    
    // hack to use loose isolation scale factors for muons in case of dilepton channel
    if(int(input.selectedElectronsLoose.size()+input.selectedMuonsLoose.size())>1) {
        leptonsfhelper->ChangeMuIsoHistos(true);
    }
    else {
        leptonsfhelper->ChangeMuIsoHistos(false);
    }
    
    std::map< std::string, float > leptonsfs = leptonsfhelper->GetLeptonSF(input.selectedElectronsLoose,input.selectedMuonsLoose);

    //=================================================
    for(std::vector<pat::Muon>::const_iterator iMuon = input.selectedMuonsLoose.begin(); iMuon != input.selectedMuonsLoose.end(); ++iMuon ){
        std::vector<pat::Muon> muon_tmp(1, *iMuon);
        std::vector<pat::Electron> ele_tmp;
        std::map<std::string,float> leptonsfs_tmp = leptonsfhelper->GetLeptonSF(ele_tmp,muon_tmp);
	if(iMuon->pt()>lep1_pt){
	    lep2_pt=lep1_pt;
	    lep2_eta=lep1_eta;
	    lep2_iso=lep1_iso;
	    lep2_pdgId=lep1_pdgId;
	    lep2_seed=lep1_seed;
	    lep2_idSF=lep1_idSF;
            lep2_isoSF=lep1_isoSF;
            
	    lep1_pt=iMuon->pt();
	    lep1_eta=iMuon->eta();
	    if(iMuon->hasUserFloat("relIso")) lep1_iso= iMuon->userFloat("relIso");
	    lep1_pdgId=iMuon->pdgId();
	    if(iMuon->hasUserInt("deterministicSeed")) lep1_seed=(uint32_t)iMuon->userInt("deterministicSeed");
            lep1_idSF=leptonsfs_tmp["MuonSFID"];//leptonsfhelper->GetMuonSF(iMuon->pt(),iMuon->eta(),0,"ID");
            lep1_isoSF=leptonsfs_tmp["MuonSFIso"];//leptonsfhelper->GetMuonSF(iMuon->pt(),iMuon->eta(),0,"ISO");
	}
	else if(iMuon->pt()>lep2_pt){
	    lep2_pt=iMuon->pt();
	    lep2_eta=iMuon->eta();
	    if(iMuon->hasUserFloat("relIso")) lep2_iso= iMuon->userFloat("relIso");
	    lep2_pdgId=iMuon->pdgId();
	    if(iMuon->hasUserInt("deterministicSeed")) lep2_seed=(uint32_t)iMuon->userInt("deterministicSeed");
            lep2_idSF=leptonsfs_tmp["MuonSFID"];//leptonsfhelper->GetMuonSF(iMuon->pt(),iMuon->eta(),0,"ID");
            lep2_isoSF=leptonsfs_tmp["MuonSFIso"];//leptonsfhelper->GetMuonSF(iMuon->pt(),iMuon->eta(),0,"ISO");
	}
    }
    for(std::vector<pat::Electron>::const_iterator iEle = input.selectedElectronsLoose.begin(); iEle != input.selectedElectronsLoose.end(); ++iEle ){
        std::vector<pat::Electron> ele_tmp(1, *iEle);
        std::vector<pat::Muon> muon_tmp;
        std::map<std::string,float> leptonsfs_tmp = leptonsfhelper->GetLeptonSF(ele_tmp,muon_tmp);
	if(iEle->pt()>lep1_pt){
	    lep2_pt=lep1_pt;
	    lep2_eta=lep1_eta;
	    lep2_iso=lep1_iso;
	    lep2_pdgId=lep1_pdgId;
	    lep2_seed=lep1_seed;
            lep2_idSF=lep1_idSF;
            lep2_isoSF=lep1_isoSF;
	    
	    lep1_pt=iEle->pt();
	    lep1_eta=iEle->eta();
	    if(iEle->hasUserFloat("relIso")) lep1_iso= iEle->userFloat("relIso");
	    lep1_pdgId=iEle->pdgId();
	    if(iEle->hasUserInt("deterministicSeed")) lep1_seed=(uint32_t)iEle->userInt("deterministicSeed");
            lep1_idSF=leptonsfs_tmp["ElectronSFID"];//leptonsfhelper->GetElectronSF(iEle->pt(),iEle->eta(),0,"ID");
            lep1_isoSF=leptonsfs_tmp["ElectronSFIso"];//leptonsfhelper->GetElectronSF(iEle->pt(),iEle->eta(),0,"ISO");
	}
	else if(iEle->pt()>lep2_pt){
	    lep2_pt=iEle->pt();
	    lep2_eta=iEle->eta();
	    if(iEle->hasUserFloat("relIso")) lep2_iso= iEle->userFloat("relIso");
	    lep2_pdgId=iEle->pdgId();
	    if(iEle->hasUserInt("deterministicSeed")) lep2_seed=(uint32_t)iEle->userInt("deterministicSeed");
            lep2_idSF=leptonsfs_tmp["ElectronSFID"];//leptonsfhelper->GetElectronSF(iEle->pt(),iEle->eta(),0,"ID");
            lep2_isoSF=leptonsfs_tmp["ElectronSFIso"];//leptonsfhelper->GetElectronSF(iEle->pt(),iEle->eta(),0,"ISO");

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
            if(i==3) pass_METSelection=0;

	    break;
	}
	else{
	    if(i==0) pass_FilterSelection=1;
	    if(i==1) pass_VertexSelection=1;
	    if(i==2) pass_LeptonSelection=1;
            if(i==3) pass_METSelection=1;
	}
    }
    if(is_SL){
	if(abs(lep1_pdgId)==11) {
	    is_e=1;
	    is_mu=0;
            triggerSF=leptonsfs["ElectronSFTrigger"];
	}
	else if(abs(lep1_pdgId)==13){
	    is_mu=1;
	    is_e=0;
            triggerSF=leptonsfs["MuonSFTrigger"];
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
            triggerSF=leptonsfs["ElectronElectronTriggerSF"];
	}
	else if( (abs(lep1_pdgId)==11&&abs(lep2_pdgId)==13) || (abs(lep1_pdgId)==13&&abs(lep2_pdgId)==11) ){
	    is_ee=0;
	    is_emu=1;
	    is_mumu=0;
            triggerSF=leptonsfs["ElectronMuonTriggerSF"];
	}
	if(abs(lep1_pdgId)==13&&abs(lep2_pdgId)==13) {
	    is_ee=0;
	    is_emu=0;
	    is_mumu=1;
            triggerSF=leptonsfs["MuonMuonTriggerSF"];
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
	if(input.selectedJets.at(0).hasUserInt("deterministicSeed")) jet1_seed=(uint32_t)input.selectedJets.at(0).userInt("deterministicSeed");
	if(input.selectedJets.at(0).hasUserInt("pileupJetId:fullId")) jet1_PUJetId=input.selectedJets.at(0).userInt("pileupJetId:fullId");
	if(input.selectedJets.at(0).hasUserFloat("pileupJetId:fullDiscriminant")) { jet1_PUJetDiscriminant=input.selectedJets.at(0).userFloat("pileupJetId:fullDiscriminant");}
	if(input.selectedJets.at(0).hasUserFloat("HelperJES")) jet1_jesSF=input.selectedJets.at(0).userFloat("HelperJES");
	if(input.selectedJets.at(0).hasUserFloat("HelperJESup")) jet1_jesSF_up=input.selectedJets.at(0).userFloat("HelperJESup");
	if(input.selectedJets.at(0).hasUserFloat("HelperJESdown")) jet1_jesSF_down=input.selectedJets.at(0).userFloat("HelperJESdown");
        if(input.selectedJets.at(0).hasUserFloat("HelperJER")) jet1_jerSF_nominal=input.selectedJets.at(0).userFloat("HelperJER");
	//if(input.selectedJets.at(0).hasUserFloat("HelperJERUp")) jet1_jerSF_up=input.selectedJets.at(0).userFloat("HelperJERUp");
	//if(input.selectedJets.at(0).hasUserFloat("HelperJERDown")) jet1_jerSF_down=input.selectedJets.at(0).userFloat("HelperJERDown");
        if(input.selectedJets.at(0).hasUserFloat("HelperJESPileUpDataMCdown")) jet1_jesSF_PileUpDataMC_down=input.selectedJets.at(0).userFloat("HelperJESPileUpDataMCdown");
        if(input.selectedJets.at(0).hasUserFloat("HelperJESRelativeFSRup")) jet1_jesSF_RelativeFSR_up=input.selectedJets.at(0).userFloat("HelperJESRelativeFSRup");
    }

    if(input.selectedJets.size()>1){
	jet2_pt=input.selectedJets.at(1).pt();
	jet2_eta=input.selectedJets.at(1).eta();
	jet2_phi=input.selectedJets.at(1).phi();
	jet2_csv=MiniAODHelper::GetJetCSV(input.selectedJets.at(1));
	if(input.selectedJets.at(1).hasUserInt("deterministicSeed")) jet2_seed=(uint32_t)input.selectedJets.at(1).userInt("deterministicSeed");
	if(input.selectedJets.at(1).hasUserInt("pileupJetId:fullId")) jet2_PUJetId=input.selectedJets.at(1).userInt("pileupJetId:fullId");
	if(input.selectedJets.at(1).hasUserFloat("pileupJetId:fullDiscriminant")){ jet2_PUJetDiscriminant=input.selectedJets.at(1).userFloat("pileupJetId:fullDiscriminant");}
	if(input.selectedJets.at(1).hasUserFloat("HelperJES")) jet2_jesSF=input.selectedJets.at(1).userFloat("HelperJES");
	if(input.selectedJets.at(1).hasUserFloat("HelperJESup")) jet2_jesSF_up=input.selectedJets.at(1).userFloat("HelperJESup");
	if(input.selectedJets.at(1).hasUserFloat("HelperJESdown")) jet2_jesSF_down=input.selectedJets.at(1).userFloat("HelperJESdown");
        if(input.selectedJets.at(1).hasUserFloat("HelperJER")) jet2_jerSF_nominal=input.selectedJets.at(1).userFloat("HelperJER");
	//if(input.selectedJets.at(1).hasUserFloat("HelperJERUp")) jet2_jerSF_up=input.selectedJets.at(1).userFloat("HelperJERUp");
	//if(input.selectedJets.at(1).hasUserFloat("HelperJERDown")) jet2_jerSF_down=input.selectedJets.at(1).userFloat("HelperJERDown");
        if(input.selectedJets.at(1).hasUserFloat("HelperJESPileUpDataMCdown")) jet2_jesSF_PileUpDataMC_down=input.selectedJets.at(1).userFloat("HelperJESPileUpDataMCdown");
        if(input.selectedJets.at(1).hasUserFloat("HelperJESRelativeFSRup")) jet2_jesSF_RelativeFSR_up=input.selectedJets.at(1).userFloat("HelperJESRelativeFSRup");
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
    if(input.selectedJetsLoose.size()>5){
	jet6_pt=input.selectedJetsLoose.at(5).pt();
	jet6_eta=input.selectedJetsLoose.at(5).eta();
	jet6_csv=MiniAODHelper::GetJetCSV(input.selectedJetsLoose.at(5));
    }
    if(input.selectedJetsLoose.size()>6){
	jet7_pt=input.selectedJetsLoose.at(6).pt();
	jet7_eta=input.selectedJetsLoose.at(6).eta();
	jet7_csv=MiniAODHelper::GetJetCSV(input.selectedJetsLoose.at(6));
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


    trig_mu=input.triggerInfo.IsTriggered("HLT_IsoMu24_eta2p1_v*")||input.triggerInfo.IsTriggered("HLT_IsoMu27_v*");
    trig_el=input.triggerInfo.IsTriggered("HLT_Ele35_WPTight_Gsf_v*")||input.triggerInfo.IsTriggered("HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v*");
    trig_elel=input.triggerInfo.IsTriggered("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*")||input.triggerInfo.IsTriggered("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*");
    trig_elmu=input.triggerInfo.IsTriggered("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*")
	|| input.triggerInfo.IsTriggered("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*")
	|| input.triggerInfo.IsTriggered("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*")
	|| input.triggerInfo.IsTriggered("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*");
    trig_mumu=input.triggerInfo.IsTriggered("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*")
	|| input.triggerInfo.IsTriggered("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*")
	|| input.triggerInfo.IsTriggered("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*");


    
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
	    if(BoostedUtils::PassesCSV(*jet,'M')) n_btags++;
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
    
    MET_pt=input.correctedMET.corPt(pat::MET::Type1XY);
    MET_phi=input.correctedMET.corPhi(pat::MET::Type1XY);
    
    if(input.weights.count("Weight_PU")>0) puWeight=input.weights.at("Weight_PU");
    ttHFCategory=input.genTopEvt.GetTTxIdFromProducerLong();
    n_interactions=input.eventInfo.numTruePV;
      
    if(input.weights.count("Weight_CSV")>0)    csvSF=input.weights.at("Weight_CSV");
    if(input.weights.count("Weight_CSVLFup")>0) csvSF_lf_up=input.weights.at("Weight_CSV")*input.weights.at("Weight_CSVLFup");
    if(input.weights.count("Weight_CSVHFdown")>0) csvSF_hf_down=input.weights.at("Weight_CSV")*input.weights.at("Weight_CSVHFdown");
    if(input.weights.count("Weight_CSVCErr1down")>0) csvSF_cErr1_down=input.weights.at("Weight_CSV")*input.weights.at("Weight_CSVCErr1down");

    if(input.weights.count("Weight_scale_variation_muR_2p0_muF_2p0")>0) me_up =input.weights.at("Weight_scale_variation_muR_2p0_muF_2p0");
    if(input.weights.count("Weight_scale_variation_muR_0p5_muF_0p5")>0) me_down =input.weights.at("Weight_scale_variation_muR_0p5_muF_0p5");
    if(input.weights.count("Weight_TopPt")>0) top_pt_weight=input.weights.at("Weight_TopPt");
    if(input.weights.count("Weight_LHA_306000_up")>0) pdf_up=input.weights.at("Weight_LHA_306000_up");
    if(input.weights.count("Weight_LHA_306000_down")>0) pdf_down=input.weights.at("Weight_LHA_306000_down");
    if(input.weights.count("GenWeight_6")>0) isr_up=input.weights.at("GenWeight_6");
    if(input.weights.count("GenWeight_7")>0) fsr_up=input.weights.at("GenWeight_7");
    if(input.weights.count("GenWeight_8")>0) isr_down=input.weights.at("GenWeight_8");
    if(input.weights.count("GenWeight_9")>0) fsr_down=input.weights.at("GenWeight_9");
    
    if(is_SL) {
        std::vector<TLorentzVector> lepvecs=BoostedUtils::GetTLorentzVectors(BoostedUtils::GetLepVecs(input.selectedElectrons,input.selectedMuons));
        std::vector<TLorentzVector> jetvecs=BoostedUtils::GetTLorentzVectors(BoostedUtils::GetJetVecs(input.selectedJets));
        std::vector<TLorentzVector> loose_jetvecs=BoostedUtils::GetTLorentzVectors(BoostedUtils::GetJetVecs(input.selectedJetsLoose));
        TLorentzVector metP4=BoostedUtils::GetTLorentzVector(input.correctedMET.corP4(pat::MET::Type1XY));
        std::vector<double> jetcsvs;
        std::vector<double> jetcsvs_dnn;
        std::vector<double> loose_jetcsvs;
        std::vector<double> add_features;
        std::vector<unsigned int> out_best_perm;
        for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++){
            jetcsvs.push_back(MiniAODHelper::GetJetCSV(*j));
            jetcsvs_dnn.push_back(MiniAODHelper::GetJetCSV_DNN(*j));
        }
        for(auto j=input.selectedJetsLoose.begin(); j!=input.selectedJetsLoose.end(); j++){
            loose_jetcsvs.push_back(MiniAODHelper::GetJetCSV(*j));
        }
        double out_P_4b=-1;
        double out_P_2b=-1;
        double eth_blr=-1;
        double eth_blr_trans=-1;
        if(jetvecs.size()>3){
            eth_blr=memclassifier->GetBTagLikelihoodRatio(jetvecs,jetcsvs,out_best_perm,out_P_4b,out_P_2b);
        }
        eth_blr_trans=log(eth_blr/(1-eth_blr));
        add_features.push_back(eth_blr);
        add_features.push_back(eth_blr_trans);
        add_features.push_back(0.);
        bdt_output=bdtclassifier->GetBDTOutput(lepvecs, jetvecs, jetcsvs,metP4);
        //DNNOutput dnn_output = sldnnclassifier->evaluate(jetvecs,jetcsvs_dnn,lepvecs[0],metP4,add_features);
        //dnn_ttbb_output = dnn_output.ttbb();
        //dnn_ttH_output = dnn_output.ttH();
    }
    
    else if(is_DL) {
        std::vector<TLorentzVector> lepvecs;
        std::vector<double> lepcharges;
        for(int i=0;i<int(input.selectedElectronsLoose.size());i++) {
            lepvecs.push_back(BoostedUtils::GetTLorentzVector(input.selectedElectronsLoose[i].p4()));
            lepcharges.push_back(input.selectedElectronsLoose[i].charge());
        }
        for(int i=0;i<int(input.selectedMuonsLoose.size());i++) {
            lepvecs.push_back(BoostedUtils::GetTLorentzVector(input.selectedMuonsLoose[i].p4()));
            lepcharges.push_back(input.selectedMuonsLoose[i].charge());
        }
        if(lepvecs[0].Pt()<lepvecs[1].Pt()) {
            std::swap(lepvecs[0],lepvecs[1]);
            std::swap(lepcharges[0],lepcharges[1]);
        }
        std::vector<TLorentzVector> jetvecs=BoostedUtils::GetTLorentzVectors(BoostedUtils::GetJetVecs(input.selectedJetsLoose));
        std::vector<double> jetcsvs;
        std::vector<double> jetcsvs_dnn;
        std::vector<double> add_features;
        std::vector<unsigned int> out_best_perm;
        TLorentzVector metP4=BoostedUtils::GetTLorentzVector(input.correctedMET.corP4(pat::MET::Type1XY));
        for(auto j=input.selectedJetsLoose.begin(); j!=input.selectedJetsLoose.end(); j++){
            jetcsvs.push_back(MiniAODHelper::GetJetCSV(*j));
            jetcsvs_dnn.push_back(MiniAODHelper::GetJetCSV_DNN(*j));
        }
        double out_P_4b=-1;
        double out_P_2b=-1;
        double eth_blr=-1;
        double eth_blr_trans=-1;
        if(jetvecs.size()>3){
            eth_blr=memclassifier->GetBTagLikelihoodRatio(jetvecs,jetcsvs,out_best_perm,out_P_4b,out_P_2b);
        }
        eth_blr_trans=log(eth_blr/(1-eth_blr));
        add_features.push_back(eth_blr);
        add_features.push_back(eth_blr_trans);
        add_features.push_back(0.);
        bdt_output=dlbdtclassifier->GetBDTOutput(lepvecs,lepcharges,jetvecs,jetcsvs,metP4);
        //DNNOutput dnn_output = dldnnclassifier->evaluate(jetvecs,jetcsvs_dnn,lepvecs,metP4,add_features);
        //dnn_ttbb_output = dnn_output.ttbb();
        //dnn_ttH_output = dnn_output.ttH();
    }
    

    bool print=false;
    if (dataset=="NA" && (is_SL || is_DL)) print =true;
    if (dataset=="el"&&is_e) print =true;
    if (dataset=="mu"&&is_mu) print =true;
    if ((dataset=="elel"||dataset=="el")&&is_ee) print =true;
    if ((dataset=="elmu"||dataset=="el"||dataset=="mu")&&is_emu) print =true;
    if ((dataset=="mumu"||dataset=="mu")&&is_mumu) print =true;

    for(uint i=0; i<dumpAlwaysEvents.size(); i++){
	if (dumpAlwaysEvents[i]==event){
	    print=true;
	    break;
	}       
    }
    if(print){ out << boost::format("%i,%i,%i,\
%i,%i,%i,%i,%i,\
%i,%i,\
%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%i,\
%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%i,\
%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%i,\
%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%i,\
%.4f,%.4f,%.4f,\
%i,%i,%i,\
%.4f,\
%.4f,%.4f,%.4f,%.4f,\
%.4f,%.4f,\
%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f")%
	run% lumi% event%
	is_e% is_mu% is_ee% is_emu% is_mumu%
	n_jets% n_btags%
	lep1_pt% lep1_eta% lep1_iso% lep1_pdgId% lep1_idSF% lep1_isoSF% lep1_seed%
	lep2_pt% lep2_eta% lep2_iso% lep2_pdgId% lep2_idSF% lep2_isoSF% lep2_seed%
	jet1_pt% jet1_eta% jet1_phi% jet1_jesSF% jet1_jesSF_up% jet1_jesSF_down% jet1_jesSF_PileUpDataMC_down% jet1_jesSF_RelativeFSR_up% jet1_jerSF_nominal% jet1_csv% jet1_PUJetId% jet1_PUJetDiscriminant% jet1_seed%
	jet2_pt% jet2_eta% jet2_phi% jet2_jesSF% jet2_jesSF_up% jet2_jesSF_down% jet2_jesSF_PileUpDataMC_down% jet2_jesSF_RelativeFSR_up% jet2_jerSF_nominal% jet2_csv% jet2_PUJetId% jet2_PUJetDiscriminant% jet2_seed%	
	MET_pt% MET_phi% mll%
	ttHFCategory% ttHFGenFilterTag% n_interactions%
	puWeight%
	csvSF% csvSF_lf_up% csvSF_hf_down% csvSF_cErr1_down%
	pdf_up% pdf_down%
	me_up% me_down% isr_up% isr_down% fsr_up% fsr_down% triggerSF% top_pt_weight% bdt_output% dnn_ttH_output% dnn_ttbb_output;
	if(addExtendedInfo){
	    out << boost::format(",%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f")%jet3_pt%jet3_eta%jet3_csv%jet4_pt%jet4_eta%jet4_csv%jet5_pt%jet5_eta%jet5_csv%jet6_pt%jet6_eta%jet6_csv%jet7_pt%jet7_eta%jet7_csv;
	    out << boost::format(",%i,%i,%i,%i,%i")%trig_el%trig_mu%trig_elel%trig_elmu%trig_mumu;
	    out << boost::format(",%i,%i,%i,%.4f")%n_leps_tight%n_leps_dl%n_leps_loose%rho;
	    out << boost::format(",%.4f,%.4f,%.4f,%i,%.4f,%.4f,%.4f,%i")%raw_el1_pt%raw_el1_eta%raw_el1_iso%raw_el1_pdgId%raw_el2_pt%raw_el2_eta%raw_el2_iso%raw_el2_pdgId;
	    out << boost::format(",%.4f,%.4f,%.4f,%i,%.4f,%.4f,%.4f,%i")%raw_mu1_pt%raw_mu1_eta%raw_mu1_iso%raw_mu1_pdgId%raw_mu2_pt%raw_mu2_eta%raw_mu2_iso%raw_mu2_pdgId;
	    out << boost::format(",%i,%i,%i,%i,%i")%pass_FilterSelection%pass_VertexSelection%pass_LeptonSelection%pass_DiLeptonSelection%pass_METSelection;
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




void Synchronizer::Init(std::string filename, const std::vector<std::string>& jetSystematics,const edm::ParameterSet& iConfig,MiniAODHelper* helper_,LeptonSFHelper* leptonsfhelper_,BDTClassifier* bdtclassifier_,DLBDTClassifier* dlbdtclassifier_,DNNClassifier_SL* sldnnclassifier_,DNNClassifier_DL* dldnnclassifier_,MEMClassifier* memclassifier_,bool dumpExtended){
    systematics=jetSystematics;
    helper=helper_;
    leptonsfhelper=leptonsfhelper_;
    bdtclassifier=bdtclassifier_;
    dlbdtclassifier=dlbdtclassifier_;
    sldnnclassifier=sldnnclassifier_;
    dldnnclassifier=dldnnclassifier_;
    memclassifier=memclassifier_;
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
    selectionsSL.push_back(new METSelection(20.,99999.));
    selectionsSL.push_back(new JetTagSelection(4,2));
    for (auto &c : cutflowsSL){
	for (auto &s : selectionsSL){
	    s->InitCutflow(c);
	}
    }

    dataset = iConfig.getParameter<std::string>("dataset");
    isData = iConfig.getParameter<bool>("isData");
}

/*
        if(event==625102) {
            cout << "Lepton: " << "pt: " << lepvecs[0].Pt() << " eta: " << lepvecs[0].Eta() << " phi: " << lepvecs[0].Phi() << " e: " << lepvecs[0].E() << endl;
            for(int i=0;i<int(jetvecs.size());i++) {
                cout << "Jet " << i << " pt: " << jetvecs[i].Pt() << " eta: " << jetvecs[i].Eta() << " phi: " << jetvecs[i].Phi() << " e: " << jetvecs[i].E() << " csv: " << jetcsvs[i] << endl;
            }
            cout << "METpt: " << metP4.Pt() << "METphi: " << metP4.Phi() << endl;
}*/
