#include "BoostedTTH/BoostedAnalyzer/interface/essentialMCMatchVarProcessor.hpp"

using namespace std;

essentialMCMatchVarProcessor::essentialMCMatchVarProcessor (){}
essentialMCMatchVarProcessor::~essentialMCMatchVarProcessor (){}


void essentialMCMatchVarProcessor::Init(const InputCollections& input,VariableContainer& vars){

 
  vars.InitVar( "GenEvt_I_TTPlusCC",-1,"I" );
  vars.InitVar( "GenEvt_I_TTPlusBB",-1,"I" );
  vars.InitVar( "GenEvt_TTxId_FromProducer",-1,"I" );
  vars.InitVar( "N_GoodTagsM",-1,"I" );
  vars.InitVar( "N_MisTagsM",-1,"I" );
  
  vars.InitVar( "N_GenTopHad", -1, "I" );
  vars.InitVar( "GenTopHad_B_inacceptance", 0, "I" ); // (has_bhad) is there a jet with gen-tophad-b in it
  vars.InitVar( "GenTopHad_Q_inacceptance", 0, "I" ); // (has_lj) is there a jet with at least one gen-tophad w-decay quark in it
  vars.InitVar( "GenTopHad_QQ_inacceptance", 0, "I" ); // (has_Whad) are there jets with both gen-tophad w-decay quarks in them

  vars.InitVars( "GenTopHad_Pt",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Eta",-9.,"N_GenTopHad" );
  vars.InitVars( "GenTopHad_Phi",-9.,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_W_Pt",-9.,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_B_Pt",-9.,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_Q1_Pt",-9.,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_Q2_Pt",-9.,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_W_Eta",-9.,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_B_Eta",-9.,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_Q1_Eta",-9.,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_Q2_Eta",-9.,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_W_Phi",-9.,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_B_Phi",-9.,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_Q1_Phi",-9.,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_Q2_Phi",-9.,"N_GenTopHad" );
 
  vars.InitVar( "N_GenTopLep",-1,"I" );
  vars.InitVar( "GenTopLep_B_inacceptance",0,"I" ); // (has_blep) is there a jet with gen-lephad-b in it

  vars.InitVars( "GenTopLep_Pt",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Eta",-9.,"N_GenTopLep" );
  vars.InitVars( "GenTopLep_Phi",-9.,"N_GenTopLep" );
//   vars.InitVars( "GenTopLep_W_Pt",-9.,"N_GenTopLep" );
//   vars.InitVars( "GenTopLep_B_Pt",-9.,"N_GenTopLep" );
//   vars.InitVars( "GenTopLep_Lep_Pt",-9.,"N_GenTopLep" );
//   vars.InitVars( "GenTopLep_Nu_Pt",-9.,"N_GenTopLep" );
//   vars.InitVars( "GenTopLep_W_Eta",-9.,"N_GenTopLep" );
//   vars.InitVars( "GenTopLep_B_Eta",-9.,"N_GenTopLep" );
//   vars.InitVars( "GenTopLep_Lep_Eta",-9.,"N_GenTopLep" );
//   vars.InitVars( "GenTopLep_Nu_Eta",-9.,"N_GenTopLep" );
//   vars.InitVars( "GenTopLep_W_Phi",-9.,"N_GenTopLep" );
//   vars.InitVars( "GenTopLep_B_Phi",-9.,"N_GenTopLep" );
//   vars.InitVars( "GenTopLep_Lep_Phi",-9.,"N_GenTopLep" );
//   vars.InitVars( "GenTopLep_Nu_Phi",-9.,"N_GenTopLep" );
  

  vars.InitVar( "GenHiggs_B_inacceptance", 0, "I" ); // (has_bH) is there a jet with at least one genhiggs-b in it
  vars.InitVar( "GenHiggs_BB_inacceptance", 0, "I" ); // (has_H) are there jets with both genhiggs-bs in them

  vars.InitVar( "GenHiggs_Pt",-9. );
  vars.InitVar( "GenHiggs_Eta",-9. );
  vars.InitVar( "GenHiggs_Phi",-9. );
//   vars.InitVar( "GenHiggs_B1_Pt",-9. );
//   vars.InitVar( "GenHiggs_B2_Pt",-9. );
//   vars.InitVar( "GenHiggs_B1_Eta",-9. );
//   vars.InitVar( "GenHiggs_B2_Eta",-9. );
//   vars.InitVar( "GenHiggs_B1_Phi",-9. );
//   vars.InitVar( "GenHiggs_B2_Phi",-9. );
//   vars.InitVar( "GenHiggs_B1_E",-9. );
//   vars.InitVar( "GenHiggs_B2_E",-9. );
//   
//   vars.InitVars( "GenTopHad_B_Idx",-1,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_Q1_Idx",-1,"N_GenTopHad" );
//   vars.InitVars( "GenTopHad_Q2_Idx",-1,"N_GenTopHad" );
//   vars.InitVars( "GenTopLep_B_Idx",-1,"N_GenTopLep" );
//   vars.InitVar( "GenHiggs_B1_Idx",-1 );
//   vars.InitVar( "GenHiggs_B2_Idx",-1 );
  
  vars.InitVar( "GenHiggs_DecProd1_Pt",-9. );
  vars.InitVar( "GenHiggs_DecProd1_Eta",-9. );
  vars.InitVar( "GenHiggs_DecProd1_PDGID",-999 );
  vars.InitVar( "GenHiggs_DecProd2_Pt",-9. );
  vars.InitVar( "GenHiggs_DecProd2_Eta",-9. );
  vars.InitVar( "GenHiggs_DecProd2_PDGID",-999 );

//  vars.InitVar( "GenHiggs_B1_GenJet_Pt",-9. );
//   vars.InitVar( "GenHiggs_B2_GenJet_Pt",-9. );
//   vars.InitVar( "GenHiggs_B1_GenJet_Eta",-9. );
//   vars.InitVar( "GenHiggs_B2_GenJet_Eta",-9. );
//   vars.InitVar( "GenHiggs_B1_GenJet_Phi",-9. );
//   vars.InitVar( "GenHiggs_B2_GenJet_Phi",-9. );
// 
//   vars.InitVars( "GenTopLep_B_GenJet_Pt",-9., "N_GenTopLep" );
//   vars.InitVars( "GenTopHad_B_GenJet_Pt",-9., "N_GenTopHad");
//   vars.InitVars( "GenTopLep_B_GenJet_Eta",-9., "N_GenTopLep" );
//   vars.InitVars( "GenTopHad_B_GenJet_Eta",-9., "N_GenTopHad");
//   vars.InitVars( "GenTopLep_B_GenJet_Phi",-9., "N_GenTopLep" );
//   vars.InitVars( "GenTopHad_B_GenJet_Phi",-9., "N_GenTopHad");
// 
// 
//   vars.InitVar( "GenHiggs_B1_Hadron_Pt",-9. );
//   vars.InitVar( "GenHiggs_B2_Hadron_Pt",-9. );
//   vars.InitVar( "GenHiggs_B1_Hadron_Eta",-9. );
//   vars.InitVar( "GenHiggs_B2_Hadron_Eta",-9. );
//   vars.InitVar( "GenHiggs_B1_Hadron_Phi",-9. );
//   vars.InitVar( "GenHiggs_B2_Hadron_Phi",-9. );
// 
//   vars.InitVars( "GenTopLep_B_Hadron_Pt",-9., "N_GenTopLep" );
//   vars.InitVars( "GenTopHad_B_Hadron_Pt",-9., "N_GenTopHad");
//   vars.InitVars( "GenTopLep_B_Hadron_Eta",-9., "N_GenTopLep" );
//   vars.InitVars( "GenTopHad_B_Hadron_Eta",-9., "N_GenTopHad");
//   vars.InitVars( "GenTopLep_B_Hadron_Phi",-9., "N_GenTopLep" );
//   vars.InitVars( "GenTopHad_B_Hadron_Phi",-9., "N_GenTopHad");

  vars.InitVar( "GenAdd_B_inacceptance", 0, "I" ); // (has_b) is there a jet with an additional gen-b in it
  vars.InitVar( "GenAdd_BB_inacceptance", 0, "I" ); // (has_bb) are there two jets with additional gen-bs in them,


  initialized = true;
}


void essentialMCMatchVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  
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
      if (!(BoostedUtils::PassesCSV(*j, 'M'))) continue;
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
  std::vector<reco::GenParticle> higgs_bs;
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
  }

  reco::GenParticle b1;
  reco::GenParticle b2;
  reco::GenParticle decProd1;
  reco::GenParticle decProd2;

//if(higgs_bs.size()>2)std::cout<<"MORE THAN TWO HIGGS PRODUCTS"<<std::endl;
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
  
  if(decProd1.pt()>0.){
    vars.FillVar("GenHiggs_DecProd1_Pt",decProd1.pt());
    vars.FillVar("GenHiggs_DecProd2_Pt",decProd2.pt());
    vars.FillVar("GenHiggs_DecProd1_Eta",decProd1.eta());
    vars.FillVar("GenHiggs_DecProd2_Eta",decProd2.eta());
    vars.FillVar("GenHiggs_DecProd1_PDGID",decProd1.pdgId());
    vars.FillVar("GenHiggs_DecProd2_PDGID",decProd2.pdgId());
  }

  //std::cout<<decProd1.pdgId()<<" "<<decProd2.pdgId()<<std::endl;




  
  vars.FillVar( "N_GenTopLep", toplep.size());
  vars.FillVar( "N_GenTopHad", tophad.size());
  
  vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);
  
  for(size_t i=0;i<toplep.size();i++){
    vars.FillVars( "GenTopLep_Pt",i,toplep[i].pt());
    vars.FillVars( "GenTopLep_Eta",i,toplep[i].eta());
    vars.FillVars( "GenTopLep_Phi",i,toplep[i].phi());
//     vars.FillVars( "GenTopLep_W_Pt",i,wlep[i].pt());
//     vars.FillVars( "GenTopLep_B_Pt",i,blep[i].pt());
//     vars.FillVars( "GenTopLep_Lep_Pt",i,lep[i].pt());
//     vars.FillVars( "GenTopLep_Nu_Pt",i,nu[i].pt());
//     vars.FillVars( "GenTopLep_W_Eta",i,wlep[i].eta());
//     vars.FillVars( "GenTopLep_B_Eta",i,blep[i].eta());
//     vars.FillVars( "GenTopLep_Lep_Eta",i,lep[i].eta());
//     vars.FillVars( "GenTopLep_Nu_Eta",i,nu[i].eta());
//     vars.FillVars( "GenTopLep_W_Phi",i,wlep[i].phi());
//     vars.FillVars( "GenTopLep_B_Phi",i,blep[i].phi());
//     vars.FillVars( "GenTopLep_Lep_Phi",i,lep[i].phi());
//     vars.FillVars( "GenTopLep_Nu_Phi",i,nu[i].phi());
    
//     int idxblep = -1;
    double minDrTopLep = 999;
    for(std::vector<math::XYZTLorentzVector>::iterator itJetVec = jetvecs.begin() ; itJetVec != jetvecs.end(); ++itJetVec){
      if(BoostedUtils::DeltaR(*itJetVec,blep[i].p4())<minDrTopLep){
//         idxblep = itJetVec-jetvecs.begin();
        minDrTopLep = BoostedUtils::DeltaR(*itJetVec,blep[i].p4());
      }
    }
    
    if(minDrTopLep<.25){
//       vars.FillVars( "GenTopLep_B_Idx",i,idxblep);
    }
  }
  
  for(size_t i=0;i<tophad.size();i++){
    vars.FillVars( "GenTopHad_Pt",i,tophad[i].pt());
    vars.FillVars( "GenTopHad_Eta",i,tophad[i].eta());
    vars.FillVars( "GenTopHad_Phi",i,tophad[i].phi());
//     vars.FillVars( "GenTopHad_W_Pt",i,whad[i].pt());
//     vars.FillVars( "GenTopHad_B_Pt",i,bhad[i].pt());
//     vars.FillVars( "GenTopHad_Q1_Pt",i,q1[i].pt());
//     vars.FillVars( "GenTopHad_Q2_Pt",i,q2[i].pt());
//     vars.FillVars( "GenTopHad_W_Eta",i,whad[i].eta());
//     vars.FillVars( "GenTopHad_B_Eta",i,bhad[i].eta());
//     vars.FillVars( "GenTopHad_Q1_Eta",i,q1[i].eta());
//     vars.FillVars( "GenTopHad_Q2_Eta",i,q2[i].eta());
//     vars.FillVars( "GenTopHad_W_Phi",i,whad[i].phi());
//     vars.FillVars( "GenTopHad_B_Phi",i,bhad[i].phi());
//     vars.FillVars( "GenTopHad_Q1_Phi",i,q1[i].phi());
//     vars.FillVars( "GenTopHad_Q2_Phi",i,q2[i].phi());
//     int idxbhad=-1;
//     int idxq1=-1;
//     int idxq2=-1;
//     double minDrTopHadB = 999;
//     double minDrTopHadQ1 = 999;
//     double minDrTopHadQ2 = 999;
    
//     for(size_t j=0; j<jetvecs.size(); j++){
// 	    if(BoostedUtils::DeltaR(jetvecs[j],bhad[i].p4())<minDrTopHadB){
//         idxbhad = j;
//         minDrTopHadB = BoostedUtils::DeltaR(jetvecs[j],bhad[i].p4());
//       }
//       if(BoostedUtils::DeltaR(jetvecs[j],q1[i].p4())<minDrTopHadQ1){
//         idxq1 = j;
//         minDrTopHadQ1 = BoostedUtils::DeltaR(jetvecs[j],q1[i].p4());
//       }
//       if(BoostedUtils::DeltaR(jetvecs[j],q2[i].p4())<minDrTopHadQ2){
//         idxq2 = j;
//         minDrTopHadQ2 = BoostedUtils::DeltaR(jetvecs[j],q2[i].p4());
//       }
//     }
//     
//     if(minDrTopHadB<.25){
//       vars.FillVars( "GenTopHad_B_Idx",i,idxbhad);
//     }
//     if(minDrTopHadQ1<.25){
//       vars.FillVars( "GenTopHad_Q1_Idx",i,idxq1);
//     }
//     if(minDrTopHadQ2<.25){
//       vars.FillVars( "GenTopHad_Q2_Idx",i,idxq2);
//     }
  }

  if(higgs.pt()>0.){
    vars.FillVar( "GenHiggs_Pt",higgs.pt());
    vars.FillVar( "GenHiggs_Eta",higgs.eta());
    vars.FillVar( "GenHiggs_Phi",higgs.phi());
  }
//   if(b1.pt()>0.){
//     vars.FillVar("GenHiggs_B1_Pt",b1.pt());
//     vars.FillVar("GenHiggs_B2_Pt",b2.pt());
//     vars.FillVar("GenHiggs_B1_Eta",b1.eta());
//     vars.FillVar("GenHiggs_B2_Eta",b2.eta());
//     vars.FillVar("GenHiggs_B1_Phi",b1.phi());
//     vars.FillVar("GenHiggs_B2_Phi",b2.phi());
//     vars.FillVar("GenHiggs_B1_E",b1.energy());
//     vars.FillVar("GenHiggs_B2_E",b2.energy());
//     
//     int idxb1=-1;
//     int idxb2=-1;
//     
//     double minDrB1 = 999;
//     double minDrB2 = 999;
//     
//     for(std::vector<math::XYZTLorentzVector>::iterator itJetVec = jetvecs.begin() ; itJetVec != jetvecs.end(); ++itJetVec){
//       assert(itJetVec->pt()>0);
//       assert(b1.pt()>0);
//       assert(b2.pt()>0);
//       if(BoostedUtils::DeltaR(*itJetVec,b1.p4())<minDrB1){
//         idxb1 = itJetVec-jetvecs.begin();
//         minDrB1 = BoostedUtils::DeltaR(*itJetVec,b1.p4());
//       }
//       if(BoostedUtils::DeltaR(*itJetVec,b2.p4())<minDrB2){
//         idxb2 = itJetVec-jetvecs.begin();
//         minDrB2 = BoostedUtils::DeltaR(*itJetVec,b2.p4());
//       }
//     }
//     
//     if(minDrB1<.25){
//       vars.FillVar( "GenHiggs_B1_Idx",idxb1);
//     }
//     if(minDrB2<.25){
//       vars.FillVar( "GenHiggs_B2_Idx",idxb2);
//     }
//   }
  if(input.genTopEvt.IsFilled()&&input.genTopEvt.TTxIsFilled()&&input.genTopEvt.IsSemiLepton()){
    // b jets from had top
    std::vector<reco::GenJet> bhad_genjet=input.genTopEvt.GetAllTopHadBGenJets();
    if(bhad_genjet.size() > 1){ std::cout<<"MORE THAN ONE B FROM HADTOP"<<std::endl; }

    // b jets from lep top
    std::vector<reco::GenJet> blep_genjet=input.genTopEvt.GetAllTopLepBGenJets();
    if(bhad_genjet.size() > 1){ std::cout<<"MORE THAN ONE B FROM LEPTOP"<<std::endl; }

    // b jets from higgs
    reco::GenJet b1_genjet=input.genTopEvt.GetHiggsBBarGenJet();
    reco::GenJet b2_genjet=input.genTopEvt.GetHiggsBGenJet();
    // jets from W decay
    std::vector<reco::GenJet> w_genjet=input.genTopEvt.GetWGenJets();
    // additional b jets
    std::vector<reco::GenJet> b_add_genjet=input.genTopEvt.GetAdditionalBGenJets();

    std::vector<reco::GenParticle> bhad_hadron=input.genTopEvt.GetAllTopHadBHadrons();
    std::vector<reco::GenParticle> blep_hadron=input.genTopEvt.GetAllTopLepBHadrons();
    reco::GenParticle b1_hadron=input.genTopEvt.GetHiggsBBarHadron();
    reco::GenParticle b2_hadron=input.genTopEvt.GetHiggsBHadron();

//     vars.FillVar( "GenHiggs_B1_GenJet_Pt",b1_genjet.pt() );
//     vars.FillVar( "GenHiggs_B2_GenJet_Pt",b2_genjet.pt() );
//     vars.FillVar( "GenHiggs_B1_GenJet_Eta",b1_genjet.eta() );
//     vars.FillVar( "GenHiggs_B2_GenJet_Eta",b2_genjet.eta());
//     vars.FillVar( "GenHiggs_B1_GenJet_Phi",b1_genjet.phi());
//     vars.FillVar( "GenHiggs_B2_GenJet_Phi",b2_genjet.phi() );
// 
//     vars.FillVar( "GenHiggs_B1_Hadron_Pt",b1_hadron.pt() );
//     vars.FillVar( "GenHiggs_B2_Hadron_Pt",b2_hadron.pt() );
//     vars.FillVar( "GenHiggs_B1_Hadron_Eta",b1_hadron.eta() );
//     vars.FillVar( "GenHiggs_B2_Hadron_Eta",b2_hadron.eta());
//     vars.FillVar( "GenHiggs_B1_Hadron_Phi",b1_hadron.phi());
//     vars.FillVar( "GenHiggs_B2_Hadron_Phi",b2_hadron.phi() );
    
//     for(uint i=0;i<bhad_genjet.size();i++){
//       if(bhad_genjet[i].pt()>1){
// 	      vars.FillVars( "GenTopHad_B_GenJet_Pt",i,bhad_genjet[i].pt() );
// 	      vars.FillVars( "GenTopHad_B_GenJet_Eta",i,bhad_genjet[i].eta() );
// 	      vars.FillVars( "GenTopHad_B_GenJet_Phi",i,bhad_genjet[i].phi());
//       }
//       if(bhad_hadron[i].pt()>1){
// 	      vars.FillVars( "GenTopHad_B_Hadron_Pt",i,bhad_hadron[i].pt() );
// 	      vars.FillVars( "GenTopHad_B_Hadron_Eta",i,bhad_hadron[i].eta() );
// 	      vars.FillVars( "GenTopHad_B_Hadron_Phi",i,bhad_hadron[i].phi());
//       }
// 	  }
    
//     for(uint i=0;i<blep_genjet.size();i++){
//       if(blep_genjet[i].pt()>1){
// 	      vars.FillVars( "GenTopLep_B_GenJet_Phi",i,blep_genjet[i].phi());
// 	      vars.FillVars( "GenTopLep_B_GenJet_Pt",i,blep_genjet[i].pt() );
// 	      vars.FillVars( "GenTopLep_B_GenJet_Eta",i,blep_genjet[i].eta());
//       }
//       if(blep_hadron[i].pt()>1){
// 	      vars.FillVars( "GenTopLep_B_Hadron_Pt",i,blep_hadron[i].pt() );
// 	      vars.FillVars( "GenTopLep_B_Hadron_Eta",i,blep_hadron[i].eta());
// 	      vars.FillVars( "GenTopLep_B_Hadron_Phi",i,blep_hadron[i].phi());
//       }
//     }

    bool first_higgs_b = true;
    bool first_W_jet = true;
    bool first_add_jet = true;
    double dR_threshold = 0.05;

    // init all 'inacceptance' variables with 'false'
    vars.FillVar("GenTopHad_B_inacceptance",0);
    vars.FillVar("GenTopLep_B_inacceptance",0);
    vars.FillVar("GenTopHad_Q_inacceptance",0);
    vars.FillVar("GenTopHad_QQ_inacceptance",0);
    vars.FillVar("GenHiggs_B_inacceptance",0);
    vars.FillVar("GenHiggs_BB_inacceptance",0);
    vars.FillVar("GenAdd_B_inacceptance",0);
    vars.FillVar("GenAdd_BB_inacceptance",0);   

    // loop over reco jets, get GenJet perform dR Matching with GenParticle Objects
    for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++) {
      reco::GenJet genj = j.genJet();
 
      // search for b jet from hadronic top
      for(uint i=0; i<bhad_genjet.size(); i++){     
        if( BoostedUtils::DeltaR(genj.p4(), bhad_genjet[i].p4()) < dR_threshold ){
          // has_bhad
          vars.FillVar("GenTopHad_B_inacceptance",1);
          }
        }

      // search for b jet from leptonic top
      for(uint i=0; i<blep_genjet.size(); i++){
        if( BoostedUtils::DeltaR(genj.p4(), blep_genjet[i].p4()) < dR_threshold ){
          // has_blep
          vars.FillVar("GenTopLep_B_inacceptance",1);
          }
        }

      // search for quark jets from hadronic W
      for(uint i=0; i<w_genjet.size(); i++){
        if( BoostedUtils::DeltaR(genj.p4(), w_genjet[i].p4()) < dR_threshold ){
          if( first_W_jet ){
            // has_lj
            vars.FillVar("GenTopHad_Q_inacceptance",1);
            first_W_jet = false;
            }
          else{
            // has_Whad
            vars.FillVar("GenTopHad_QQ_inacceptance",1);
            }   
          }
        }

      // search for b jets from higgs
      if( BoostedUtils::DeltaR(genj.p4(), b1_genjet.p4()) < dR_threshold or BoostedUtils::DeltaR(genj.p4(), b2_genjet.p4()) < dR_threshold) {
        if( first_higgs_b ){
          // has_bH
          vars.FillVar("GenHiggs_B_inacceptance",1);
          first_higgs_b = false;
          }
        else {
          // has_H
          vars.FillVar("GenHiggs_BB_inacceptance",1);
          }
        }

      // search for additional b jets
      for(uint i=0; i<b_add_genjet.size(); i++){
        if( BoostedUtils::DeltaR(genj.p4(), b_add_genjet[i].p4()) < dR_threshold ){
          if( first_add_jet ){
            // has_b
            vars.FillVar("GenAdd_B_inacceptance",1);
            first_add_jet = false;
            }
          else {
            // has_bb
            vars.FillVar("GenAdd_BB_inacceptance",1);
            }
          }
        }

      } // end of selectedJets loop

    } // end of isSemiLep
    
  }
}
