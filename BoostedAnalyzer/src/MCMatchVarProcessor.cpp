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


  vars.InitVar("GenHiggsMassFromMatchedJets",-9.);	
  vars.InitVar("GenZMassFromMatchedJets",-9.);
  vars.InitVars("GenHadTopMassFromMatchedJets",-9.,"N_GenTopHad");
  vars.InitVars("GenHadWMassFromMatchedJets",-9.,"N_GenTopHad");

  vars.InitVar("N_AdditionalGenBJets",-1, "I");
  vars.InitVars("AdditionalGenBJet_Pt",-9.,"N_AdditionalGenBJets");
  vars.InitVars("AdditionalGenBJet_Eta",-9.,"N_AdditionalGenBJets");
  vars.InitVars("AdditionalGenBJet_Phi",-9.,"N_AdditionalGenBJets");
  vars.InitVars("AdditionalGenBJet_E",-9.,"N_AdditionalGenBJets");
  vars.InitVars("AdditionalGenBJet_M",-9.,"N_AdditionalGenBJets");

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
  std::vector<reco::GenJet> addBJet;
  std::vector<reco::GenJet> addCJet;
  std::vector<reco::GenJet> addLFJet;
  reco::GenParticle higgs;
  // for ttZ
  reco::GenParticle Z;

  std::vector<reco::GenJet> additional_b_genjets;

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
    addBJet=input.genTopEvt.GetAdditionalBGenJets();
    addCJet=input.genTopEvt.GetAdditionalCGenJets();
    addLFJet=input.genTopEvt.GetAdditionalLightGenJets();
    higgs=input.genTopEvt.GetHiggs();
    higgs_bs=input.genTopEvt.GetHiggsDecayProducts();
    Z_bs=input.genTopEvt.GetZDecayProducts();
    // for ttZ
    Z = input.genTopEvt.GetZ();

    additional_b_genjets = input.genTopEvt.GetAdditionalBGenJets();    
  }

  reco::GenParticle b1;
  reco::GenParticle b2;
  reco::GenParticle Zb1;
  reco::GenParticle Zb2;
  reco::GenParticle decProd1;
  reco::GenParticle decProd2;

  //create a TLorentzVector for the ttH system
  math::XYZTLorentzVector ttH;
  double ttH_HT=0.;
  double Gen_Jets_HT=0.;

//if(higgs_bs.size()>2)std:://cout<<"MORE THAN TWO HIGGS PRODUCTS"<<std::endl;
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
    math::XYZTLorentzVector gen_top=toplep[i].p4();
    ttH+=gen_top;
    ttH_HT+=toplep[i].pt();
    //cout<<"\n\t>>>>>\tadded leptnic top\t<<<<<\n";
    //cout<<gen_top.pt()<<"__"<<gen_top.px()<<"__"<<gen_top.py()<<"__"<<gen_top.pz()<<"__mass:_"<<gen_top.mass()<<endl;
    //cout<<ttH.pt()<<"__"<<ttH.px()<<"__"<<ttH.py()<<"__"<<ttH.pz()<<"__mass:_"<<ttH.mass()<<endl;
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
    math::XYZTLorentzVector gen_top=tophad[i].p4();
    ttH+=gen_top;
    ttH_HT+=tophad[i].pt();
    //cout<<"\n\t>>>>>\tadded hadronic top\t<<<<<\n";
    //cout<<gen_top.pt()<<"__"<<gen_top.px()<<"__"<<gen_top.py()<<"__"<<gen_top.pz()<<"__mass:_"<<gen_top.mass()<<endl;
    //cout<<ttH.pt()<<"__"<<ttH.px()<<"__"<<ttH.py()<<"__"<<ttH.pz()<<"__mass:_"<<ttH.mass()<<endl;
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
    math::XYZTLorentzVector gen_higgs=higgs.p4();
    ttH+=gen_higgs;
    ttH_HT+=gen_higgs.pt();
    //cout<<"\n\t>>>>>\tadded higgs\t<<<<<\n";
    //cout<<gen_higgs.pt()<<"__"<<gen_higgs.px()<<"__"<<gen_higgs.py()<<"__"<<gen_higgs.pz()<<"__mass:_"<<gen_higgs.mass()<<endl;
    //cout<<ttH.pt()<<"__"<<ttH.px()<<"__"<<ttH.py()<<"__"<<ttH.pz()<<"__mass:_"<<ttH.mass()<<endl;

  }

  // build HT from Jets and leptons
  for(std::vector<reco::GenJet>::const_iterator itJet = input.genJets.begin() ; itJet != input.genJets.end(); ++itJet){
      Gen_Jets_HT += itJet->pt();
      //cout<<Gen_Jets_HT<<endl;
  }
  // for(std::vector<reco::GenParticle>::const_iterator itEle = input.customGenElectrons.begin(); itEle != input.customGenElectrons.end(); ++itEle){
  //     Gen_Jets_HT += itEle->pt();
  //     //cout<<Gen_Jets_HT<<endl;
  // }
  // for(std::vector<reco::GenParticle>::const_iterator itMu = input.customGenMuons.begin(); itMu != input.customGenMuons.end(); ++itMu){
  //     Gen_Jets_HT += itMu->pt();
  //     //cout<<Gen_Jets_HT<<endl;
  // }
  // for(std::vector<reco::GenParticle>::const_iterator itGamma = input.customGenPhotons.begin(); itGamma != input.customGenPhotons.end(); ++itGamma){
  //     Gen_Jets_HT += itGamma->pt();
  //     //cout<<Gen_Jets_HT<<endl;
  // }


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
    int n_add_genjets = additional_b_genjets.size();
    //std::cout << n_add_genjets << std::endl;
    vars.FillVar("N_AdditionalGenBJets", n_add_genjets);
    for(uint i=0; i<additional_b_genjets.size(); i++)
    {
        vars.FillVars("AdditionalGenBJet_Pt",i,additional_b_genjets[i].pt());
        vars.FillVars("AdditionalGenBJet_Eta",i,additional_b_genjets[i].eta());
        vars.FillVars("AdditionalGenBJet_Phi",i,additional_b_genjets[i].phi());
        vars.FillVars("AdditionalGenBJet_M",i,additional_b_genjets[i].mass());
        vars.FillVars("AdditionalGenBJet_E",i,additional_b_genjets[i].energy());

    }
}
