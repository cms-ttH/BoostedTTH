#include "BoostedTTH/BoostedAnalyzer/interface/MCMatchVarProcessor.hpp"

using namespace std;

MCMatchVarProcessor::MCMatchVarProcessor (){}
MCMatchVarProcessor::~MCMatchVarProcessor (){}


void MCMatchVarProcessor::Init(const InputCollections& input,VariableContainer& vars){

 
  vars.InitVar( "GenEvt_I_TTPlusCC",-1,"I" );
  vars.InitVar( "GenEvt_I_TTPlusBB",-1,"I" );
  vars.InitVar( "GenEvt_TTxId_FromProducer",-1,"I" );
  vars.InitVar( "N_GoodTagsM",-1,"I" );
  vars.InitVar( "N_MisTagsM",-1,"I" );
  
  vars.InitVar( "N_GenTopHad", -1, "I" );
  vars.InitVars( "GenTopHad_Pt",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Eta",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Phi",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_E",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_W_Pt",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_B_Pt",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q1_Pt",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q2_Pt",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_W_Eta",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_B_Eta",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q1_Eta",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q2_Eta",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_W_Phi",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_B_Phi",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q1_Phi",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q2_Phi",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_W_E",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_B_E",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q1_E",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q2_E",-9.,"N_GenTopHad" );
 
  vars.InitVar( "N_GenTopLep",-1,"I" );
  vars.InitVars( "GenTopLep_Pt",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Eta",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Phi",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_E",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_W_Pt",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_B_Pt",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Lep_Pt",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Nu_Pt",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_W_Eta",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_B_Eta",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Lep_Eta",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Nu_Eta",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_W_Phi",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_B_Phi",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Lep_Phi",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Nu_Phi",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_W_E",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_B_E",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Lep_E",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Nu_E",-9.,"N_GenTopLep" );
  
  vars.InitVar( "GenHiggs_Pt",-9. );
  vars.InitVar( "GenHiggs_Eta",-9. );
  vars.InitVar( "GenHiggs_Phi",-9. );
  vars.InitVar( "GenHiggs_E",-9. );
  vars.InitVar( "GenHiggs_Y",-9. );
  vars.InitVar( "GenHiggs_B1_Pt",-9. );
  vars.InitVar( "GenHiggs_B2_Pt",-9. );
  vars.InitVar( "GenHiggs_B1_Eta",-9. );
  vars.InitVar( "GenHiggs_B2_Eta",-9. );
  vars.InitVar( "GenHiggs_B1_Phi",-9. );
  vars.InitVar( "GenHiggs_B2_Phi",-9. );
  vars.InitVar( "GenHiggs_B1_E",-9. );
  vars.InitVar( "GenHiggs_B2_E",-9. );
  
  vars.InitVar( "GenZ_Pt",-9. );
  vars.InitVar( "GenZ_Eta",-9. );
  vars.InitVar( "GenZ_Phi",-9. );
  vars.InitVar( "GenZ_E",-9. );
  vars.InitVar( "GenZ_Y",-9. );
  vars.InitVar( "GenZ_B1_Pt",-9. );
  vars.InitVar( "GenZ_B2_Pt",-9. );
  vars.InitVar( "GenZ_B1_Eta",-9. );
  vars.InitVar( "GenZ_B2_Eta",-9. );
  vars.InitVar( "GenZ_B1_Phi",-9. );
  vars.InitVar( "GenZ_B2_Phi",-9. );
  vars.InitVar( "GenZ_B1_E",-9. );
  vars.InitVar( "GenZ_B2_E",-9. );



  vars.InitVars( "GenTopHad_B_Idx",-1,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q1_Idx",-1,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Q2_Idx",-1,"N_GenTopHad" );
  vars.InitVars( "GenTopLep_B_Idx",-1,"N_GenTopLep" );
  vars.InitVar( "GenHiggs_B1_Idx",-1 );
  vars.InitVar( "GenHiggs_B2_Idx",-1 );
  vars.InitVar( "GenZ_B1_Idx",-1 );
  vars.InitVar( "GenZ_B2_Idx",-1 );
  
  vars.InitVar( "GenHiggs_DecProd1_Pt",-9. );
  vars.InitVar( "GenHiggs_DecProd1_Eta",-9. );
  vars.InitVar( "GenHiggs_DecProd1_E",-9. );
  vars.InitVar( "GenHiggs_DecProd1_PDGID",-999 );
  vars.InitVar( "GenHiggs_DecProd2_Pt",-9. );
  vars.InitVar( "GenHiggs_DecProd2_Eta",-9. );
  vars.InitVar( "GenHiggs_DecProd2_E",-9. );
  vars.InitVar( "GenHiggs_DecProd2_PDGID",-999 );

  vars.InitVar( "GenHiggs_B1_GenJet_Pt",-9. );
  vars.InitVar( "GenHiggs_B2_GenJet_Pt",-9. );
  vars.InitVar( "GenHiggs_B1_GenJet_Eta",-9. );
  vars.InitVar( "GenHiggs_B2_GenJet_Eta",-9. );
  vars.InitVar( "GenHiggs_B1_GenJet_Phi",-9. );
  vars.InitVar( "GenHiggs_B2_GenJet_Phi",-9. );
  vars.InitVar( "GenHiggs_B1_GenJet_E",-9. );
  vars.InitVar( "GenHiggs_B2_GenJet_E",-9. );

  vars.InitVars( "GenTopLep_B_GenJet_Pt",-9., "N_GenTopLep" );
  vars.InitVars( "GenTopHad_B_GenJet_Pt",-9., "N_GenTopHad");
  vars.InitVars( "GenTopLep_B_GenJet_Eta",-9., "N_GenTopLep" );
  vars.InitVars( "GenTopHad_B_GenJet_Eta",-9., "N_GenTopHad");
  vars.InitVars( "GenTopLep_B_GenJet_Phi",-9., "N_GenTopLep" );
  vars.InitVars( "GenTopHad_B_GenJet_Phi",-9., "N_GenTopHad");
  vars.InitVars( "GenTopLep_B_GenJet_E",-9., "N_GenTopLep" );
  vars.InitVars( "GenTopHad_B_GenJet_E",-9., "N_GenTopHad");


  vars.InitVar( "GenHiggs_B1_Hadron_Pt",-9. );
  vars.InitVar( "GenHiggs_B2_Hadron_Pt",-9. );
  vars.InitVar( "GenHiggs_B1_Hadron_Eta",-9. );
  vars.InitVar( "GenHiggs_B2_Hadron_Eta",-9. );
  vars.InitVar( "GenHiggs_B1_Hadron_Phi",-9. );
  vars.InitVar( "GenHiggs_B2_Hadron_Phi",-9. );
  vars.InitVar( "GenHiggs_B1_Hadron_E",-9. );
  vars.InitVar( "GenHiggs_B2_Hadron_E",-9. );

  vars.InitVars( "GenTopLep_B_Hadron_Pt",-9., "N_GenTopLep" );
  vars.InitVars( "GenTopHad_B_Hadron_Pt",-9., "N_GenTopHad");
  vars.InitVars( "GenTopLep_B_Hadron_Eta",-9., "N_GenTopLep" );
  vars.InitVars( "GenTopHad_B_Hadron_Eta",-9., "N_GenTopHad");
  vars.InitVars( "GenTopLep_B_Hadron_Phi",-9., "N_GenTopLep" );
  vars.InitVars( "GenTopHad_B_Hadron_Phi",-9., "N_GenTopHad");
  vars.InitVars( "GenTopLep_B_Hadron_E",-9., "N_GenTopLep" );
  vars.InitVars( "GenTopHad_B_Hadron_E",-9., "N_GenTopHad");
  
  //// for THW
  //vars.InitVar( "GenW_NotFromTop_Pt",-9. );
  //vars.InitVar( "GenW_NotFromTop_Eta",-9. );
  //vars.InitVar( "GenW_NotFromTop_Phi",-9. );
  //vars.InitVar( "GenW_NotFromTop_E",-9. );
  //vars.InitVar( "N_GenW_NotFromTop_DecProds",-1,"I" );
  //vars.InitVars( "GenW_NotFromTop_DecProd_Pt",-9., "N_GenW_NotFromTop_DecProds" );
  //vars.InitVars( "GenW_NotFromTop_DecProd_Eta",-9., "N_GenW_NotFromTop_DecProds" );
  //vars.InitVars( "GenW_NotFromTop_DecProd_Phi",-9., "N_GenW_NotFromTop_DecProds" );
  //vars.InitVars( "GenW_NotFromTop_DecProd_E",-9., "N_GenW_NotFromTop_DecProds" );
  //vars.InitVars( "GenW_NotFromTop_DecProd_PDGID",-999, "N_GenW_NotFromTop_DecProds" );
  //
  //// for THQ
  //vars.InitVar( "GenForwardQuark_Pt",-9. );
  //vars.InitVar( "GenForwardQuark_Eta",-9. );
  //vars.InitVar( "GenForwardQuark_Phi",-9. );
  //vars.InitVar( "GenForwardQuark_E",-9. );
  //vars.InitVar( "GenForwardQuark_PDGID",-999 );


  //// for ttbar dR matching
  vars.InitVar("Gen_ttbar_matched", 0, "I");
  vars.InitVar("Gen_ttH_matched", 0, "I");
  vars.InitVar("GenHiggsMassFromMatchedJets",-9.);
  vars.InitVar("GenZMassFromMatchedJets",-9.);
  vars.InitVars("GenHadTopMassFromMatchedJets",-9.,"N_GenTopHad");
  vars.InitVars("GenHadWMassFromMatchedJets",-9.,"N_GenTopHad");
  initialized = true;
}


void MCMatchVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  
  if(!initialized) cerr << "tree processor not initialized" << endl;
  
  int iBB = 0;
  int iCC = 0;
  
  if(input.sampleType == SampleType::ttbb) iBB = 3;
  if(input.sampleType == SampleType::ttb) iBB = 1;
  if(input.sampleType == SampleType::tt2b) iBB = 2;
  if(input.sampleType == SampleType::ttcc) iCC = 1;
  
  vars.FillVar( "GenEvt_I_TTPlusCC",iCC );
  vars.FillVar( "GenEvt_I_TTPlusBB",iBB );
  if(input.genTopEvt.IsFilled()){
      vars.FillVar( "GenEvt_TTxId_FromProducer",input.genTopEvt.GetTTxIdFromProducer());
  }
  int nGoodTagsM=0;
  int nMisTagsM=0;
  for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++){
      if (!(CSVHelper::PassesCSV(*j, "DeepJet", CSVHelper::CSVwp::Medium,input.era))) continue;
      if(abs(j->hadronFlavour())==5) nGoodTagsM++;
      if(abs(j->hadronFlavour())!=5) nMisTagsM++;
  }  
  vars.FillVar( "N_GoodTagsM",nGoodTagsM);
  vars.FillVar( "N_MisTagsM",nMisTagsM);


  std::vector<reco::GenParticle> tophad;
  std::vector<reco::GenParticle> whad;
  std::vector<reco::GenParticle> bhad;
  std::vector<reco::GenParticle> q1;
  std::vector<reco::GenParticle> q2;
  std::vector<reco::GenParticle> toplep;
  std::vector<reco::GenParticle> wlep;
  std::vector<reco::GenParticle> blep;
  std::vector<reco::GenParticle> lep;
  std::vector<reco::GenParticle> nu;
  reco::GenParticle higgs;
  // for ttZ
  reco::GenParticle Z;
  // for THW
  reco::GenParticle w_not_from_top;
  std::vector<reco::GenParticle> w_not_from_top_decay_products;
  // for THQ
  reco::GenParticle forward_quark;
  std::vector<reco::GenParticle> higgs_bs;
  std::vector<reco::GenParticle> Z_bs;
  if(input.genTopEvt.IsFilled()){
    tophad=input.genTopEvt.GetAllTopHads();
    whad=input.genTopEvt.GetAllWhads();
    bhad=input.genTopEvt.GetAllTopHadDecayQuarks();
    q1=input.genTopEvt.GetAllWQuarks();
    q2=input.genTopEvt.GetAllWAntiQuarks();
    toplep=input.genTopEvt.GetAllTopLeps();
    wlep=input.genTopEvt.GetAllWleps();
    blep=input.genTopEvt.GetAllTopLepDecayQuarks();
    lep=input.genTopEvt.GetAllLeptons();
    nu=input.genTopEvt.GetAllNeutrinos();
    higgs=input.genTopEvt.GetHiggs();
    higgs_bs=input.genTopEvt.GetHiggsDecayProducts();
    Z_bs=input.genTopEvt.GetZDecayProducts();
    // for ttZ
    Z = input.genTopEvt.GetZ();
    // for THW
    w_not_from_top = input.genTopEvt.GetWNotFromTop();
    w_not_from_top_decay_products = input.genTopEvt.GetWNotFromTopDecayProducts();
    // for THQ
    forward_quark = input.genTopEvt.GetForwardQuark();
  }

  reco::GenParticle b1;
  reco::GenParticle b2;
  reco::GenParticle Zb1;
  reco::GenParticle Zb2;
  reco::GenParticle decProd1;
  reco::GenParticle decProd2;

  // find Higgs decay products
  bool dfirst=true;
  for(auto p =higgs_bs.begin(); p!=higgs_bs.end(); p++){
    if(p->pdgId()==5) b1=*p;
    if(p->pdgId()==-5) b2=*p;
    if(dfirst){
      decProd1=*p;
      dfirst=false;
    }
    else{
      decProd2=*p;
    }
  }
  
  // fill Higgs decay products
  if(decProd1.pt()>0.){
    vars.FillVar("GenHiggs_DecProd1_Pt",decProd1.pt());
    vars.FillVar("GenHiggs_DecProd2_Pt",decProd2.pt());
    vars.FillVar("GenHiggs_DecProd1_Eta",decProd1.eta());
    vars.FillVar("GenHiggs_DecProd2_Eta",decProd2.eta());
    vars.FillVar("GenHiggs_DecProd1_E",decProd1.energy());
    vars.FillVar("GenHiggs_DecProd2_E",decProd2.energy());
    vars.FillVar("GenHiggs_DecProd1_PDGID",decProd1.pdgId());
    vars.FillVar("GenHiggs_DecProd2_PDGID",decProd2.pdgId());
  }
 
  // find Z decay products
  for(auto p = Z_bs.begin(); p!=Z_bs.end(); p++) {
    if(p->pdgId()==5) Zb1=*p;
    if(p->pdgId()==-5) Zb2=*p;
  }
  
  vars.FillVar( "N_GenTopLep", toplep.size());
  vars.FillVar( "N_GenTopHad", tophad.size());
  
  vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);
  
  // fill leptonic Top system
  for(size_t i=0;i<toplep.size();i++){
    vars.FillVars( "GenTopLep_Pt",i,toplep[i].pt());
    vars.FillVars( "GenTopLep_Eta",i,toplep[i].eta());
    vars.FillVars( "GenTopLep_Phi",i,toplep[i].phi());
    vars.FillVars( "GenTopLep_E",i,toplep[i].energy());
    vars.FillVars( "GenTopLep_W_Pt",i,wlep[i].pt());
    vars.FillVars( "GenTopLep_B_Pt",i,blep[i].pt());
    vars.FillVars( "GenTopLep_Lep_Pt",i,lep[i].pt());
    vars.FillVars( "GenTopLep_Nu_Pt",i,nu[i].pt());
    vars.FillVars( "GenTopLep_W_Eta",i,wlep[i].eta());
    vars.FillVars( "GenTopLep_B_Eta",i,blep[i].eta());
    vars.FillVars( "GenTopLep_Lep_Eta",i,lep[i].eta());
    vars.FillVars( "GenTopLep_Nu_Eta",i,nu[i].eta());
    vars.FillVars( "GenTopLep_W_Phi",i,wlep[i].phi());
    vars.FillVars( "GenTopLep_B_Phi",i,blep[i].phi());
    vars.FillVars( "GenTopLep_Lep_Phi",i,lep[i].phi());
    vars.FillVars( "GenTopLep_Nu_Phi",i,nu[i].phi());
    vars.FillVars( "GenTopLep_W_E",i,wlep[i].energy());
    vars.FillVars( "GenTopLep_B_E",i,blep[i].energy());
    vars.FillVars( "GenTopLep_Lep_E",i,lep[i].energy());
    vars.FillVars( "GenTopLep_Nu_E",i,nu[i].energy());
    
    int idxblep = -1;
    double minDrTopLep = 999;
    for(std::vector<math::XYZTLorentzVector>::iterator itJetVec = jetvecs.begin() ; itJetVec != jetvecs.end(); ++itJetVec){
      if(BoostedUtils::DeltaR(*itJetVec,blep[i].p4())<minDrTopLep){
        idxblep = itJetVec-jetvecs.begin();
        minDrTopLep = BoostedUtils::DeltaR(*itJetVec,blep[i].p4());
      }
    }
    
    if(minDrTopLep<.25){
      vars.FillVars( "GenTopLep_B_Idx",i,idxblep);
    }
  }
  

  // fill hadronic top system
  for(size_t i=0;i<tophad.size();i++){
    vars.FillVars( "GenTopHad_Pt",i,tophad[i].pt());
    vars.FillVars( "GenTopHad_Eta",i,tophad[i].eta());
    vars.FillVars( "GenTopHad_Phi",i,tophad[i].phi());
    vars.FillVars( "GenTopHad_E",i,tophad[i].energy());
    vars.FillVars( "GenTopHad_W_Pt",i,whad[i].pt());
    vars.FillVars( "GenTopHad_B_Pt",i,bhad[i].pt());
    vars.FillVars( "GenTopHad_Q1_Pt",i,q1[i].pt());
    vars.FillVars( "GenTopHad_Q2_Pt",i,q2[i].pt());
    vars.FillVars( "GenTopHad_W_Eta",i,whad[i].eta());
    vars.FillVars( "GenTopHad_B_Eta",i,bhad[i].eta());
    vars.FillVars( "GenTopHad_Q1_Eta",i,q1[i].eta());
    vars.FillVars( "GenTopHad_Q2_Eta",i,q2[i].eta());
    vars.FillVars( "GenTopHad_W_Phi",i,whad[i].phi());
    vars.FillVars( "GenTopHad_B_Phi",i,bhad[i].phi());
    vars.FillVars( "GenTopHad_Q1_Phi",i,q1[i].phi());
    vars.FillVars( "GenTopHad_Q2_Phi",i,q2[i].phi());
    vars.FillVars( "GenTopHad_W_E",i,whad[i].energy());
    vars.FillVars( "GenTopHad_B_E",i,bhad[i].energy());
    vars.FillVars( "GenTopHad_Q1_E",i,q1[i].energy());
    vars.FillVars( "GenTopHad_Q2_E",i,q2[i].energy());
    int idxbhad=-1;
    int idxq1=-1;
    int idxq2=-1;
    double minDrTopHadB = 999;
    double minDrTopHadQ1 = 999;
    double minDrTopHadQ2 = 999;
    
    for(size_t j=0; j<jetvecs.size(); j++){
            if(BoostedUtils::DeltaR(jetvecs[j],bhad[i].p4())<minDrTopHadB){
        idxbhad = j;
        minDrTopHadB = BoostedUtils::DeltaR(jetvecs[j],bhad[i].p4());
      }
      if(BoostedUtils::DeltaR(jetvecs[j],q1[i].p4())<minDrTopHadQ1){
        idxq1 = j;
        minDrTopHadQ1 = BoostedUtils::DeltaR(jetvecs[j],q1[i].p4());
      }
      if(BoostedUtils::DeltaR(jetvecs[j],q2[i].p4())<minDrTopHadQ2){
        idxq2 = j;
        minDrTopHadQ2 = BoostedUtils::DeltaR(jetvecs[j],q2[i].p4());
      }
    }
    
    if(minDrTopHadB<.25){
      vars.FillVars( "GenTopHad_B_Idx",i,idxbhad);
    }
    if(minDrTopHadQ1<.25){
      vars.FillVars( "GenTopHad_Q1_Idx",i,idxq1);
    }
    if(minDrTopHadQ2<.25){
      vars.FillVars( "GenTopHad_Q2_Idx",i,idxq2);
    }

    // get mass of dijet Whad system if quark indices were found
    if(minDrTopHadQ1<.25 && minDrTopHadQ2<.25)
    {
        // get tri
        math::XYZTLorentzVector hadw_vec = jetvecs[idxq1]+jetvecs[idxq2];
        vars.FillVars("GenHadWMassFromMatchedJets",i,hadw_vec.M());
    }

    // get mass of trijet hadtop system if quark indices were found
    if( minDrTopHadB<.25 && minDrTopHadQ1<.25 && minDrTopHadQ2<.25)
    {
        // get tri
        math::XYZTLorentzVector hadtop_vec = jetvecs[idxbhad]+jetvecs[idxq1]+jetvecs[idxq2];
        vars.FillVars("GenHadTopMassFromMatchedJets",i,hadtop_vec.M());
    }
    
  }


  // fill higgs system
  if(higgs.pt()>0.){
    vars.FillVar( "GenHiggs_Pt",higgs.pt());
    vars.FillVar( "GenHiggs_Eta",higgs.eta());
    vars.FillVar( "GenHiggs_Phi",higgs.phi());
    vars.FillVar( "GenHiggs_E",higgs.energy());
    vars.FillVar( "GenHiggs_Y",higgs.rapidity());
  }
  if(b1.pt()>0.){
    vars.FillVar("GenHiggs_B1_Pt",b1.pt());
    vars.FillVar("GenHiggs_B2_Pt",b2.pt());
    vars.FillVar("GenHiggs_B1_Eta",b1.eta());
    vars.FillVar("GenHiggs_B2_Eta",b2.eta());
    vars.FillVar("GenHiggs_B1_Phi",b1.phi());
    vars.FillVar("GenHiggs_B2_Phi",b2.phi());
    vars.FillVar("GenHiggs_B1_E",b1.energy());
    vars.FillVar("GenHiggs_B2_E",b2.energy());
    
    int idxb1=-1;
    int idxb2=-1;
    
    double minDrB1 = 999;
    double minDrB2 = 999;
    
    for(std::vector<math::XYZTLorentzVector>::iterator itJetVec = jetvecs.begin() ; itJetVec != jetvecs.end(); ++itJetVec){
      assert(itJetVec->pt()>0);
      assert(b1.pt()>0);
      assert(b2.pt()>0);
      if(BoostedUtils::DeltaR(*itJetVec,b1.p4())<minDrB1){
        idxb1 = itJetVec-jetvecs.begin();
        minDrB1 = BoostedUtils::DeltaR(*itJetVec,b1.p4());
      }
      if(BoostedUtils::DeltaR(*itJetVec,b2.p4())<minDrB2){
        idxb2 = itJetVec-jetvecs.begin();
        minDrB2 = BoostedUtils::DeltaR(*itJetVec,b2.p4());
      }
    }
    
    if(minDrB1<.25){
      vars.FillVar( "GenHiggs_B1_Idx",idxb1);
    }
    if(minDrB2<.25){
      vars.FillVar( "GenHiggs_B2_Idx",idxb2);
    }

    // get mass of dijet system of B indices were found
    if( minDrB1<.25 && minDrB2<.25 )
    {
        // get dijet
        math::XYZTLorentzVector higgs_vec = jetvecs[idxb1]+jetvecs[idxb2];
        vars.FillVar("GenHiggsMassFromMatchedJets", higgs_vec.M());
    }

  }


  // fill Z system
  if(Z.pt()>0.){
    vars.FillVar( "GenZ_Pt",Z.pt());
    vars.FillVar( "GenZ_Eta",Z.eta());
    vars.FillVar( "GenZ_Phi",Z.phi());
    vars.FillVar( "GenZ_E",Z.energy());
    vars.FillVar( "GenZ_Y",Z.rapidity());
  }
  if(Zb1.pt()>0.){
    vars.FillVar("GenZ_B1_Pt",Zb1.pt());
    vars.FillVar("GenZ_B2_Pt",Zb2.pt());
    vars.FillVar("GenZ_B1_Eta",Zb1.eta());
    vars.FillVar("GenZ_B2_Eta",Zb2.eta());
    vars.FillVar("GenZ_B1_Phi",Zb1.phi());
    vars.FillVar("GenZ_B2_Phi",Zb2.phi());
    vars.FillVar("GenZ_B1_E",Zb1.energy());
    vars.FillVar("GenZ_B2_E",Zb2.energy());
    
    int idxb1=-1;
    int idxb2=-1;
    
    double minDrB1 = 999;
    double minDrB2 = 999;
    
    for(std::vector<math::XYZTLorentzVector>::iterator itJetVec = jetvecs.begin() ; itJetVec != jetvecs.end(); ++itJetVec){
      assert(itJetVec->pt()>0);
      assert(Zb1.pt()>0);
      assert(Zb2.pt()>0);
      if(BoostedUtils::DeltaR(*itJetVec,Zb1.p4())<minDrB1){
        idxb1 = itJetVec-jetvecs.begin();
        minDrB1 = BoostedUtils::DeltaR(*itJetVec,Zb1.p4());
      }
      if(BoostedUtils::DeltaR(*itJetVec,Zb2.p4())<minDrB2){
        idxb2 = itJetVec-jetvecs.begin();
        minDrB2 = BoostedUtils::DeltaR(*itJetVec,Zb2.p4());
      }
    }
    
    if(minDrB1<.25){
      vars.FillVar( "GenZ_B1_Idx",idxb1);
    }
    if(minDrB2<.25){
      vars.FillVar( "GenZ_B2_Idx",idxb2);
    }

    // get mass of dijet system of B indices were found
    if( minDrB1<.25 && minDrB2<.25 )
    {
        // get dijet
        math::XYZTLorentzVector Z_vec = jetvecs[idxb1]+jetvecs[idxb2];
        vars.FillVar("GenZMassFromMatchedJets", Z_vec.M());
    }

  }


  // fill semileptonic gen top event stuff
  if(input.genTopEvt.IsFilled()&&input.genTopEvt.TTxIsFilled()&&input.genTopEvt.IsSemiLepton()){
    std::vector<reco::GenJet> bhad_genjet=input.genTopEvt.GetAllTopHadBGenJets();
    std::vector<reco::GenJet> blep_genjet=input.genTopEvt.GetAllTopLepBGenJets();
    reco::GenJet b1_genjet=input.genTopEvt.GetHiggsBBarGenJet();
    reco::GenJet b2_genjet=input.genTopEvt.GetHiggsBGenJet();

    std::vector<reco::GenParticle> bhad_hadron=input.genTopEvt.GetAllTopHadBHadrons();
    std::vector<reco::GenParticle> blep_hadron=input.genTopEvt.GetAllTopLepBHadrons();
    reco::GenParticle b1_hadron=input.genTopEvt.GetHiggsBBarHadron();
    reco::GenParticle b2_hadron=input.genTopEvt.GetHiggsBHadron();

    vars.FillVar( "GenHiggs_B1_GenJet_Pt",b1_genjet.pt() );
    vars.FillVar( "GenHiggs_B2_GenJet_Pt",b2_genjet.pt() );
    vars.FillVar( "GenHiggs_B1_GenJet_Eta",b1_genjet.eta() );
    vars.FillVar( "GenHiggs_B2_GenJet_Eta",b2_genjet.eta() );
    vars.FillVar( "GenHiggs_B1_GenJet_Phi",b1_genjet.phi() );
    vars.FillVar( "GenHiggs_B2_GenJet_Phi",b2_genjet.phi() );
    vars.FillVar( "GenHiggs_B1_GenJet_E",b1_genjet.energy() );
    vars.FillVar( "GenHiggs_B2_GenJet_E",b2_genjet.energy() );

    vars.FillVar( "GenHiggs_B1_Hadron_Pt",b1_hadron.pt() );
    vars.FillVar( "GenHiggs_B2_Hadron_Pt",b2_hadron.pt() );
    vars.FillVar( "GenHiggs_B1_Hadron_Eta",b1_hadron.eta() );
    vars.FillVar( "GenHiggs_B2_Hadron_Eta",b2_hadron.eta() );
    vars.FillVar( "GenHiggs_B1_Hadron_Phi",b1_hadron.phi() );
    vars.FillVar( "GenHiggs_B2_Hadron_Phi",b2_hadron.phi() );
    vars.FillVar( "GenHiggs_B1_Hadron_E",b1_hadron.energy() );
    vars.FillVar( "GenHiggs_B2_Hadron_E",b2_hadron.energy() );
    
    for(uint i=0;i<bhad_genjet.size();i++){
      if(bhad_genjet[i].pt()>1){
              vars.FillVars( "GenTopHad_B_GenJet_Pt",i,bhad_genjet[i].pt() );
              vars.FillVars( "GenTopHad_B_GenJet_Eta",i,bhad_genjet[i].eta() );
              vars.FillVars( "GenTopHad_B_GenJet_Phi",i,bhad_genjet[i].phi());
              vars.FillVars( "GenTopHad_B_GenJet_E",i,bhad_genjet[i].energy());
      }
      if(bhad_hadron[i].pt()>1){
              vars.FillVars( "GenTopHad_B_Hadron_Pt",i,bhad_hadron[i].pt() );
              vars.FillVars( "GenTopHad_B_Hadron_Eta",i,bhad_hadron[i].eta() );
              vars.FillVars( "GenTopHad_B_Hadron_Phi",i,bhad_hadron[i].phi());
              vars.FillVars( "GenTopHad_B_Hadron_E",i,bhad_hadron[i].energy());
      }
          }
    
    for(uint i=0;i<blep_genjet.size();i++){
      if(blep_genjet[i].pt()>1){
              vars.FillVars( "GenTopLep_B_GenJet_Pt",i,blep_genjet[i].pt() );
              vars.FillVars( "GenTopLep_B_GenJet_Eta",i,blep_genjet[i].eta());
              vars.FillVars( "GenTopLep_B_GenJet_Phi",i,blep_genjet[i].phi());
              vars.FillVars( "GenTopLep_B_GenJet_E",i,blep_genjet[i].energy());
      }
      if(blep_hadron[i].pt()>1){
              vars.FillVars( "GenTopLep_B_Hadron_Pt",i,blep_hadron[i].pt() );
              vars.FillVars( "GenTopLep_B_Hadron_Eta",i,blep_hadron[i].eta());
              vars.FillVars( "GenTopLep_B_Hadron_Phi",i,blep_hadron[i].phi());
              vars.FillVars( "GenTopLep_B_Hadron_E",i,blep_hadron[i].energy());
      }
    }
  }
  
  //// for THW
  //if(w_not_from_top.pt()>0.){
  //  vars.FillVar( "GenW_NotFromTop_Pt",w_not_from_top.pt());
  //  vars.FillVar( "GenW_NotFromTop_Eta",w_not_from_top.eta());
  //  vars.FillVar( "GenW_NotFromTop_Phi",w_not_from_top.phi());
  //  vars.FillVar( "GenW_NotFromTop_E",w_not_from_top.energy());
  //}
  //vars.FillVar( "N_GenW_NotFromTop_DecProds",w_not_from_top_decay_products.size() );
  //for(size_t i=0;i<w_not_from_top_decay_products.size();i++){
  //  vars.FillVars("GenW_NotFromTop_DecProd_Pt",i,w_not_from_top_decay_products.at(i).pt() );
  //  vars.FillVars("GenW_NotFromTop_DecProd_Eta",i,w_not_from_top_decay_products.at(i).eta() );
  //  vars.FillVars("GenW_NotFromTop_DecProd_Phi",i,w_not_from_top_decay_products.at(i).phi() );
  //  vars.FillVars("GenW_NotFromTop_DecProd_E",i,w_not_from_top_decay_products.at(i).energy() );
  //  vars.FillVars("GenW_NotFromTop_DecProd_PDGID",i,w_not_from_top_decay_products.at(i).pdgId() );
  //}
  //
  //// for THQ
  //if(forward_quark.pt()>0.){
  //  vars.FillVar( "GenForwardQuark_Pt",forward_quark.pt());
  //  vars.FillVar( "GenForwardQuark_Eta",forward_quark.eta());
  //  vars.FillVar( "GenForwardQuark_Phi",forward_quark.phi());
  //  vars.FillVar( "GenForwardQuark_E",forward_quark.energy());
  //  vars.FillVar( "GenForwardQuark_PDGID",forward_quark.pdgId());
  //}

    if(input.genTopEvt.IsFilled()&&input.genTopEvt.TTxIsFilled()&&input.genTopEvt.IsSemiLepton()) {

        double dR_bhad;
        double dR_blep;
        double dR_q1;
        double dR_q2;

        double dR_b1;
        double dR_b2;
        bool found_ttbar = false;
        bool found_ttH = false;
        double dR_threshold_match = 0.5;
        int it_i, it_j, it_k, it_l, it_m, it_n;

        it_i = 0;
        for( auto i = input.selectedJets.begin(); i!=input.selectedJets.end(); i++ )
        {   
            if(found_ttH) break;
            it_i++;

            if (!CSVHelper::PassesCSV(*i, "DeepJet", CSVHelper::CSVwp::Medium,input.era)) continue;
            // search for a dR that matches the hadronic b
            dR_bhad = std::abs(BoostedUtils::DeltaR(i->p4(), bhad[0].p4()));
            if (dR_bhad > dR_threshold_match) continue;

            it_j = 0;
            for( auto j = input.selectedJets.begin(); j!=input.selectedJets.end(); j++ )
            {
                if(found_ttH) break;
                it_j++;
                if(it_i==it_j) continue;

                if (!CSVHelper::PassesCSV(*j, "DeepJet", CSVHelper::CSVwp::Medium,input.era)) continue;
                // search for a dR that matches the leptonic b
                dR_blep = std::abs(BoostedUtils::DeltaR(j->p4(), blep[0].p4()));
                if( dR_blep > dR_threshold_match) continue;

                it_k = 0;
                for( auto k = input.selectedJets.begin(); k!=input.selectedJets.end(); k++ )
                {
                    if(found_ttH) break;
                    it_k++;
                    if(it_k==it_i || it_k==it_j) continue;

                    // search for first hadronic W jet
                    dR_q1 = std::abs(BoostedUtils::DeltaR(k->p4(), q1[0].p4()));
                    if( dR_q1 > dR_threshold_match) continue;

                    it_l = 0;
                    for( auto l = input.selectedJets.begin(); l!=input.selectedJets.end(); l++ )
                    {
                        if(found_ttH) break;
                        it_l++;
                        if(it_l==it_i||it_l==it_j||it_l==it_k) continue;

                        // search for second hadronic W jet
                        dR_q2 = std::abs(BoostedUtils::DeltaR(l->p4(), q2[0].p4()));
                        if( dR_q2 > dR_threshold_match) continue;

                        // successfully found ttbar config
                        found_ttbar = true;

                        it_m = 0;
                        for( auto m = input.selectedJets.begin(); m!=input.selectedJets.end(); m++ )
                        {
                            if(found_ttH) break;
                            it_m++;
                            if(it_m==it_i||it_m==it_j||it_m==it_k||it_m==it_l) continue;

                            //if (!CSVHelper::PassesCSV(*m, "DeepJet", CSVHelper::CSVwp::Medium,input.era)) continue;
                            // search for first higgs b
                            dR_b1 = std::abs(BoostedUtils::DeltaR(m->p4(), b1.p4()));
                            if( dR_b1 > dR_threshold_match) continue;

                            it_n = 0;
                            for( auto n = input.selectedJets.begin(); n!=input.selectedJets.end(); n++ )
                            {
                                if(found_ttH) break;
                                it_n++;
                                if(it_n==it_i||it_n==it_j||it_n==it_k||it_n==it_l||it_n==it_m) continue;

                                //if (!CSVHelper::PassesCSV(*n, "DeepJet", CSVHelper::CSVwp::Medium,input.era)) continue;
                                // search for first higgs b
                                dR_b2 = std::abs(BoostedUtils::DeltaR(n->p4(), b2.p4()));
                                if( dR_b2 > dR_threshold_match) continue;

                                // successfully found ttH config
                                found_ttH = true;
                            }
                        }
                    }
                }
            }
        }
        if (found_ttbar) 
            vars.FillVar("Gen_ttbar_matched", 1);
        if (found_ttH)   
            vars.FillVar("Gen_ttH_matched", 1);

    }

}
