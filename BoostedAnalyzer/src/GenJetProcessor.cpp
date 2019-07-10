#include "BoostedTTH/BoostedAnalyzer/interface/GenJetProcessor.hpp"

using namespace std;

GenJetProcessor::GenJetProcessor (){}
GenJetProcessor::~GenJetProcessor (){}

void GenJetProcessor::Init(const InputCollections& input,VariableContainer& vars){
    
    vars.InitVar( "N_GenJets",-1,"I" );
    vars.InitVars( "GenJet_Pt",-9.,"N_GenJets" );
    vars.InitVars( "GenJet_Eta",-9.,"N_GenJets" );
    vars.InitVars( "GenJet_Phi",-9.,"N_GenJets" );
    vars.InitVars( "GenJet_E",-9.,"N_GenJets" );
    vars.InitVars( "GenJet_RecoJetPt",-9.,"N_GenJets" );
    vars.InitVars( "GenJet_RecoJetEta",-9.,"N_GenJets" );
    vars.InitVars( "GenJet_RecoJetPhi",-9.,"N_GenJets" );
    vars.InitVars( "GenJet_RecoJetE",-9.,"N_GenJets" );
    vars.InitVars( "GenJet_RecoJetCSV",-9.,"N_GenJets" );
    vars.InitVars( "GenJet_NHadrons",-9.,"N_GenJets" );
    
    vars.InitVar("Evt_M_HardestGenJets");
    vars.InitVar("Evt_Dr_HardestGenJets");
    vars.InitVar("Evt_M_MinDeltaRGenJets");
    vars.InitVar("Evt_Dr_MinDeltaRGenJets");
    //vars.InitVar("Evt_Pt_MinDeltaRGenJets");
    vars.InitVar("Evt_M_GenJetsAverage");
    vars.InitVar("Evt_Deta_GenJetsAverage");
    vars.InitVar("Evt_Dr_GenJetsAverage");
    vars.InitVar("Evt_M_GenJetsClosestTo125");
    
    vars.InitVar("Evt_HT_GenJets");
    vars.InitVar("Evt_HT_Gen");
    
    initialized = true;
}

const pat::Jet* GenJetProcessor::GetPatJet(const reco::GenJet& genjet,const std::vector<pat::Jet>& patjets){
  
  for(auto patjet=patjets.begin(); patjet!=patjets.end(); patjet++){
      if(patjet->pt()>0 && genjet.pt()>0 && BoostedUtils::DeltaR(patjet->p4(),genjet.p4())<0.2){
          return &(*patjet);
          break;
        }
  }
  return 0;
}

void GenJetProcessor::Process(const InputCollections& input,VariableContainer& vars){

    if(!initialized) cerr << "tree processor not initialized" << endl;

    const char* btagger="DeepCSV";

    if(input.genTopEvt.TTxIsFilled()){
      
      std::vector<reco::GenJet> all_genjets = input.genTopEvt.GetAllGenJets();
      
      vars.FillVar( "N_GenJets", all_genjets.size());
      
      if(all_genjets.size()>0){
        
        std::vector<const pat::Jet*> all_genjets_recojets;
        for(auto genalljet = all_genjets.begin(); genalljet != all_genjets.end(); genalljet++){
          all_genjets_recojets.push_back(GetPatJet(*genalljet,input.selectedJets));
        }
        
        
        // B-genjets kinematic variables
        reco::GenJet leadingalljet = all_genjets.at(0);
        reco::GenJet subleadingalljet = all_genjets.at(0);
        for(uint i=0; i<all_genjets.size(); i++){
          if(all_genjets[i].pt() > leadingalljet.pt()){
            leadingalljet = all_genjets[i];
            subleadingalljet = leadingalljet;
          }
          vars.FillVars( "GenJet_Pt", i, all_genjets[i].pt());
          vars.FillVars( "GenJet_Eta", i, all_genjets[i].eta());
          vars.FillVars( "GenJet_Phi", i, all_genjets[i].phi());
          vars.FillVars( "GenJet_E", i, all_genjets[i].energy());
          vars.FillVars( "GenJet_RecoJetPt", i, all_genjets_recojets[i]!=0 ? all_genjets_recojets[i]->pt() : -1);
          vars.FillVars( "GenJet_RecoJetEta", i, all_genjets_recojets[i]!=0 ? all_genjets_recojets[i]->eta() : -1);
          vars.FillVars( "GenJet_RecoJetPhi", i, all_genjets_recojets[i]!=0 ? all_genjets_recojets[i]->phi() : -1);
          vars.FillVars( "GenJet_RecoJetE", i, all_genjets_recojets[i]!=0 ? all_genjets_recojets[i]->energy() : -1);
          vars.FillVars( "GenJet_RecoJetCSV", i, all_genjets_recojets[i]!=0 ? MiniAODHelper::GetJetCSV(*all_genjets_recojets[i],btagger) : -2);
        }
        
        
        if(all_genjets.size()>1){
          // Fill Variables for hardest GenJets
          math::XYZTLorentzVector leadingJetVec = leadingalljet.p4();
          math::XYZTLorentzVector subleadingJetVec = subleadingalljet.p4();
          float DrHardest = BoostedUtils::DeltaR(all_genjets[0].p4(),all_genjets[1].p4());
          vars.FillVar("Evt_M_HardestGenJets",(leadingJetVec+subleadingJetVec).M());
          vars.FillVar("Evt_Dr_HardestGenJets",DrHardest);
          // Fill Variables for closest GenJets
          int idClosestJet1 = -1;
          int idClosestJet2 = -1;
          float minDrJets = BoostedUtils::GetClosestJetIDs(idClosestJet1,idClosestJet2,all_genjets);
          math::XYZTLorentzVector closestJetVec1 = all_genjets[idClosestJet1].p4();
          math::XYZTLorentzVector closestJetVec2 = all_genjets[idClosestJet2].p4();
          vars.FillVar("Evt_M_MinDeltaRGenJets",(closestJetVec1+closestJetVec2).M());
          vars.FillVar("Evt_Dr_MinDeltaRGenJets",minDrJets);
          //vars.FillVar("Evt_Pt_MinDeltaRGenJets",(closestJetVec1+closestJetVec2).Pt());
        }
        
        
        // JetRelation Variables
        float mJetsAverage = 0;
        float detaJetsAverage = 0;
        float drJetsAverage = 0;
        float mGenJetsClosestTo125 = -999;
        vector<float> mGenJets;
        
        int nPairsJets = 0;
        std::vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(all_genjets);
        for(std::vector<math::XYZTLorentzVector>::iterator itJetVec1 = jetvecs.begin();itJetVec1 != jetvecs.end();++itJetVec1){        
          for(std::vector<math::XYZTLorentzVector>::iterator itJetVec2 = itJetVec1+1;itJetVec2 != jetvecs.end();++itJetVec2){
            
            mGenJets.push_back((*itJetVec1+*itJetVec2).M());
            mJetsAverage += mGenJets.back();
            if(fabs(mGenJets.back()-125)<fabs(mGenJetsClosestTo125-125)) mGenJetsClosestTo125 = mGenJets.back();
            
            detaJetsAverage += fabs(itJetVec1->Eta()-itJetVec2->Eta());
            drJetsAverage += BoostedUtils::DeltaR(*itJetVec1,*itJetVec2);
            
            nPairsJets++;
          }
        }
         
        if(nPairsJets > 0){
          mJetsAverage /= (float) nPairsJets;
          detaJetsAverage /= (float) nPairsJets;
          drJetsAverage /= (float) nPairsJets;
        }
        
        vars.FillVar("Evt_M_GenJetsAverage",mJetsAverage);
        vars.FillVar("Evt_Deta_GenJetsAverage",detaJetsAverage);
        vars.FillVar("Evt_Dr_GenJetsAverage",drJetsAverage);
        vars.FillVar("Evt_M_GenJetsClosestTo125",mGenJetsClosestTo125);
        
        // Fill Ht Variables
        float htalljets = 0.;
        float ht_gen = 0.;
        for(std::vector<reco::GenJet>::const_iterator itJet = all_genjets.begin() ; itJet != all_genjets.end(); ++itJet){
          ht_gen += itJet->pt();
          htalljets += itJet->pt();
        }
        for(std::vector<reco::GenParticle>::const_iterator itEle = input.customGenElectrons.begin(); itEle != input.customGenElectrons.end(); ++itEle){
            ht_gen += itEle->pt();
        }
        for(std::vector<reco::GenParticle>::const_iterator itMu = input.customGenMuons.begin(); itMu != input.customGenMuons.end(); ++itMu){
            ht_gen += itMu->pt();
        }
        ht_gen += input.correctedMET.genMET()->pt();
        
        vars.FillVar("Evt_HT_GenJets",htalljets);
        vars.FillVar("Evt_HT_Gen",ht_gen);
      }
    }
}
