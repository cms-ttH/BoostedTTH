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
  


  vars.InitVar( "GenHiggs_Pt",-9. );
  vars.InitVar( "GenHiggs_Eta",-9. );
  vars.InitVar( "GenHiggs_Phi",-9. );

   vars.InitVar( "GenHiggs_B1_Pt",-9. );
   vars.InitVar( "GenHiggs_B2_Pt",-9. );
   vars.InitVar( "GenHiggs_B1_Eta",-9. );
   vars.InitVar( "GenHiggs_B2_Eta",-9. );
   vars.InitVar( "GenHiggs_B1_Phi",-9. );
   vars.InitVar( "GenHiggs_B2_Phi",-9. );
   vars.InitVar( "GenHiggs_B1_E",-9. );
   vars.InitVar( "GenHiggs_B2_E",-9. );
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


  vars.InitVar( "GenHiggs_B1_GenJet_Pt",-9. );
   vars.InitVar( "GenHiggs_B2_GenJet_Pt",-9. );
   vars.InitVar( "GenHiggs_B1_GenJet_Eta",-9. );
   vars.InitVar( "GenHiggs_B2_GenJet_Eta",-9. );
   vars.InitVar( "GenHiggs_B1_GenJet_Phi",-9. );
   vars.InitVar( "GenHiggs_B2_GenJet_Phi",-9. );
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
//
  // match variables for AachenDNN pre-net on genParticle level
  vars.InitVar( "GenTopHad_B_inacceptance_part", 0, "I" ); // (has_bhad)
  vars.InitVar( "GenTopHad_Q_inacceptance_part", 0, "I" ); // (has_lj)
  vars.InitVar( "GenTopHad_QQ_inacceptance_part", 0, "I" ); // (has_Whad)
  vars.InitVar( "GenTopLep_B_inacceptance_part",0,"I" ); // (has_blep)
  vars.InitVar( "GenHiggs_B_inacceptance_part", 0, "I" ); // (has_bH)
  vars.InitVar( "GenHiggs_BB_inacceptance_part", 0, "I" ); // (has_H)
  vars.InitVar( "GenAdd_B_inacceptance_part", 0, "I" ); // (has_b)
  vars.InitVar( "GenAdd_BB_inacceptance_part", 0, "I" ); // (has_bb)

  // match variables for AachenDNN pre-net on genJet level
  vars.InitVar( "GenTopHad_B_inacceptance_jet", 0, "I" ); // (has_bhad)
  vars.InitVar( "GenTopHad_Q_inacceptance_jet", 0, "I" ); // (has_lj)
  vars.InitVar( "GenTopHad_QQ_inacceptance_jet", 0, "I" ); // (has_Whad)
  vars.InitVar( "GenTopLep_B_inacceptance_jet",0,"I" ); // (has_blep)
  vars.InitVar( "GenHiggs_B_inacceptance_jet", 0, "I" ); // (has_bH)
  vars.InitVar( "GenHiggs_BB_inacceptance_jet", 0, "I" ); // (has_H)
  vars.InitVar( "GenAdd_B_inacceptance_jet", 0, "I" ); // (has_b)
  vars.InitVar( "GenAdd_BB_inacceptance_jet", 0, "I" ); // (has_bb)



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
  std::vector<reco::GenParticle> bhiggs_quarkss;
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
    bhiggs_quarkss=input.genTopEvt.GetHiggsDecayProducts();
  }

  reco::GenParticle b1;
  reco::GenParticle b2;
  reco::GenParticle decProd1;
  reco::GenParticle decProd2;

//if(bhiggs_quarkss.size()>2)std::cout<<"MORE THAN TWO HIGGS PRODUCTS"<<std::endl;
bool dfirst=true;
  for(auto p =bhiggs_quarkss.begin(); p!=bhiggs_quarkss.end(); p++){
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

     vars.FillVar("GenHiggs_B1_Pt",b1.pt());
     vars.FillVar("GenHiggs_B2_Pt",b2.pt());
     vars.FillVar("GenHiggs_B1_Eta",b1.eta());
     vars.FillVar("GenHiggs_B2_Eta",b2.eta());
     vars.FillVar("GenHiggs_B1_Phi",b1.phi());
     vars.FillVar("GenHiggs_B2_Phi",b2.phi());
     vars.FillVar("GenHiggs_B1_E",b1.energy());
     vars.FillVar("GenHiggs_B2_E",b2.energy());
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


    // get gen particles
    // b quark from had top
    std::vector<reco::GenParticle> bhad_quark=input.genTopEvt.GetAllTopHadDecayQuarks();
    if(bhad_quark.size() > 1){ std::cout<<"MORE THAN ONE B FROM HADTOP"<<std::endl; }

    // b quark from lep top    
    std::vector<reco::GenParticle> blep_quark=input.genTopEvt.GetAllTopLepDecayQuarks();
    if(blep_quark.size() > 1){ std::cout<<"MORE THAN ONE B FROM LEPTOP"<<std::endl; }

    //b quarks from higgs
    std::vector<reco::GenParticle> bhiggs_quarks = input.genTopEvt.GetHiggsDecayProducts();
    if(!(bhiggs_quarks.size() == 2) && !(bhiggs_quarks.size() == 0))
      {std::cout<<"NOT ZERO OR TWO B QUARKS FROM HIGGS"<<std::endl; }
    
    // quarks from W decay

    std::vector<reco::GenParticle> hadw_quarks=input.genTopEvt.GetWQuarks();
    if(!(hadw_quarks.size() == 2)){ std::cout<<"UNEQUAL TWO QUARKS FROM HADRONIC W"<<std::endl; }


    // get gen jets
    // b jet from had top
    std::vector<reco::GenJet> bhad_genjet=input.genTopEvt.GetAllTopHadBGenJets();
    if(bhad_genjet.size() > 1){ std::cout<<"MORE THAN ONE bJET FROM HADTOP"<<std::endl; }

    // b jet from lep top
    std::vector<reco::GenJet> blep_genjet=input.genTopEvt.GetAllTopLepBGenJets();
    if(blep_genjet.size() > 1){ std::cout<<"MORE THAN ONE bJET FROM HADTOP"<<std::endl; }

    // b jets from higgs
    reco::GenJet bhiggs_genjet1 = input.genTopEvt.GetHiggsBBarGenJet();
    reco::GenJet bhiggs_genjet2 = input.genTopEvt.GetHiggsBGenJet();

    // jets from W decay
    std::vector<reco::GenJet> hadw_genjets=input.genTopEvt.GetWGenJets();
    if(!(hadw_genjets.size() == 2)){ std::cout<<"UNEQUAL TWO JETS FROM HADRONIC W"<<std::endl; }

     vars.FillVar( "GenHiggs_B1_GenJet_Pt",bhiggs_genjet1.pt() );
     vars.FillVar( "GenHiggs_B2_GenJet_Pt",bhiggs_genjet2.pt() );
     vars.FillVar( "GenHiggs_B1_GenJet_Eta",bhiggs_genjet1.eta() );
     vars.FillVar( "GenHiggs_B2_GenJet_Eta",bhiggs_genjet2.eta());
     vars.FillVar( "GenHiggs_B1_GenJet_Phi",bhiggs_genjet1.phi());
     vars.FillVar( "GenHiggs_B2_GenJet_Phi",bhiggs_genjet2.phi() );
 
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
//       if(bhad_quark[i].pt()>1){
// 	      vars.FillVars( "GenTopHad_B_Hadron_Pt",i,bhad_quark[i].pt() );
// 	      vars.FillVars( "GenTopHad_B_Hadron_Eta",i,bhad_quark[i].eta() );
// 	      vars.FillVars( "GenTopHad_B_Hadron_Phi",i,bhad_quark[i].phi());
//       }
// 	  }
    
//     for(uint i=0;i<blep_genjet.size();i++){
//       if(blep_genjet[i].pt()>1){
// 	      vars.FillVars( "GenTopLep_B_GenJet_Phi",i,blep_genjet[i].phi());
// 	      vars.FillVars( "GenTopLep_B_GenJet_Pt",i,blep_genjet[i].pt() );
// 	      vars.FillVars( "GenTopLep_B_GenJet_Eta",i,blep_genjet[i].eta());
//       }
//       if(blep_quark[i].pt()>1){
// 	      vars.FillVars( "GenTopLep_B_Hadron_Pt",i,blep_quark[i].pt() );
// 	      vars.FillVars( "GenTopLep_B_Hadron_Eta",i,blep_quark[i].eta());
// 	      vars.FillVars( "GenTopLep_B_Hadron_Phi",i,blep_quark[i].phi());
//       }
//     }

    // --------------------------------------------------------------------------------------------
    // matching on genParticle level (analogue to AachenDNN)
    double dR_threshold = 0.05;
    bool first_higgs_to_b = true;
    bool first_W_to_q = true;
    bool first_add_jet = true;
    bool jet_was_matched = false;

    //bool found_both_w_q = false;    
    //bool found_both_higgs_b = false;
    // ---------------------------------------------------------------------------------------------------
    // loop over reco jets, get GenParticle, perform dR Matching with GenParticle Objects from genTopEvent
    for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++) {
      jet_was_matched = false;

      const reco::GenParticle *genp = j->genParticle();
      // check if genparticle exists
      if(!genp){ continue; }

      // search for b quark from hadronic top
      for(uint i=0; i<bhad_quark.size(); i++){     
        if( std::abs(BoostedUtils::DeltaR(genp->p4(), bhad_quark[i].p4())) < dR_threshold ){
          // has_bhad
          vars.FillVar("GenTopHad_B_inacceptance_part",1);
          jet_was_matched = true;
          }
        }

      // search for b quark from leptonic top
      for(uint i=0; i<blep_quark.size(); i++){
        if( std::abs(BoostedUtils::DeltaR(genp->p4(), blep_quark[i].p4())) < dR_threshold ){
          // has_blep
          vars.FillVar("GenTopLep_B_inacceptance_part",1);
          jet_was_matched = true;
          }
        }

      // search for quark from hadronic W
      for(uint i=0; i<hadw_quarks.size(); i++){
        if( std::abs(BoostedUtils::DeltaR(genp->p4(), hadw_quarks[i].p4())) < dR_threshold ){
          if( first_W_to_q ){
            // has_lj
            vars.FillVar("GenTopHad_Q_inacceptance_part",1);
            first_W_to_q = false;
            jet_was_matched = true;
            }
          else{
            // has_Whad
            vars.FillVar("GenTopHad_QQ_inacceptance_part",1);
            jet_was_matched = true;
            //found_both_w_q = true;
            }   
          }
        }

      // search for b quark from higgs
      for(uint i=0; i<bhiggs_quarks.size(); i++){
        if( std::abs(BoostedUtils::DeltaR(genp->p4(), bhiggs_quarks[i].p4())) < dR_threshold ){
          if( first_higgs_to_b ){
            // has_bH
            vars.FillVar("GenHiggs_B_inacceptance_part",1);
            first_higgs_to_b = false;
            jet_was_matched = true;
            }
          else {
            // has_H
            vars.FillVar("GenHiggs_BB_inacceptance_part",1);
            jet_was_matched = true;
            //found_both_higgs_b = true;
            }
          }
        }

      if(!(jet_was_matched) && std::abs(genp->pdgId())==5 && iBB > 0) {
        // variable can only be set true if eventtype == ttbb/tt2b/ttb
        // additional unmatched b quarks
        if( first_add_jet ) {
          // has_b
          vars.FillVar("GenAdd_B_inacceptance_part",1);
          first_add_jet = false;
          }
        else {
          if( iBB > 2 ){
            // variable can only be set true if eventtype == ttbb
            // has_bb
            vars.FillVar("GenAdd_BB_inacceptance_part",1);
            }
          }
        }
      } // end of selectedJets loop

    reco::GenParticle whad_particle = input.genTopEvt.GetWhad();
    //math::XYZTLorentzVector w_vec = hadw_quarks[0].p4() + hadw_quarks[1].p4();
    //float inv_w_mass = w_vec.M();

    bool first_higgs_jet = true;
    bool first_Wjet = true;
    first_add_jet = true;
    jet_was_matched = false;
    // ---------------------------------------------------------------------------------------------------
    // loop over reco jets, get GenJet, perform dR Matching with GenJet Objects from genTopEvent
    for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++) {
      jet_was_matched = false;

      const reco::GenJet *genj = j->genJet();
      // check if genjet exists
      if(!genj){ continue; }

      // search for b jet from hadronic top
      for(uint i=0; i<bhad_genjet.size(); i++){     
        if( std::abs(BoostedUtils::DeltaR(genj->p4(), bhad_genjet[i].p4())) < dR_threshold ){
          // has_bhad
          vars.FillVar("GenTopHad_B_inacceptance_jet",1);
          jet_was_matched = true;
          }
        }

      // search for b jet from leptonic top
      for(uint i=0; i<blep_genjet.size(); i++){
        if( std::abs(BoostedUtils::DeltaR(genj->p4(), blep_genjet[i].p4())) < dR_threshold ){
          // has_blep
          vars.FillVar("GenTopLep_B_inacceptance_jet",1);
          jet_was_matched = true;
          }
        }

      // search for quark jets from hadronic W
      for(uint i=0; i<hadw_genjets.size(); i++){
        if( std::abs(BoostedUtils::DeltaR(genj->p4(), hadw_genjets[i].p4())) < dR_threshold ){
          if( first_Wjet ){
            // has_lj
            vars.FillVar("GenTopHad_Q_inacceptance_jet",1);
            first_Wjet = false;
            jet_was_matched = true;
            }
          else{
            // has_Whad
            vars.FillVar("GenTopHad_QQ_inacceptance_jet",1);
            jet_was_matched = true;
            }   
          }
        }

      // search for b jets from higgs
      if( std::abs(BoostedUtils::DeltaR(genj->p4(), bhiggs_genjet1.p4())) < dR_threshold || std::abs(BoostedUtils::DeltaR(genj->p4(), bhiggs_genjet2.p4())) < dR_threshold ){
        if( first_higgs_jet ){
          // has_bH
          vars.FillVar("GenHiggs_B_inacceptance_jet",1);
          first_higgs_jet = false;
          jet_was_matched = true;
          }
        else {
          // has_H
          vars.FillVar("GenHiggs_BB_inacceptance_jet",1);
          jet_was_matched = true;
          }
        }

      const char *workingPoint = "M";
      if(!(jet_was_matched) && BoostedUtils::PassesCSV(*genj,*workingPoint) && iBB > 0) {
        // additional unmatched b-jets
        if( first_add_jet ) {
          // has_b
          vars.FillVar("GenAdd_B_inacceptance_jet",1);
          first_add_jet = false;
          }
        else {
          if(iBB>2){
            // has_bb
            vars.FillVar("GenAdd_BB_inacceptance_jet",1);
            }
          }
        }
      } // end of selectedJets loop
    // ---------------------------------------------------------------------------------------------------
    


    } // end of isSemiLep
    
  }
