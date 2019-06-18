#include "BoostedTTH/BoostedAnalyzer/interface/GenBJetProcessor.hpp"

using namespace std;

GenBJetProcessor::GenBJetProcessor (){}
GenBJetProcessor::~GenBJetProcessor (){}

void GenBJetProcessor::Init(const InputCollections& input,VariableContainer& vars){
    
    vars.InitVar( "N_GenBJets",-1,"I" );
    vars.InitVars( "GenBJet_Pt",-9.,"N_GenBJets" );
    vars.InitVars( "GenBJet_Eta",-9.,"N_GenBJets" );
    vars.InitVars( "GenBJet_Phi",-9.,"N_GenBJets" );
    vars.InitVars( "GenBJet_E",-9.,"N_GenBJets" );
    vars.InitVars( "GenBJet_RecoJetPt",-9.,"N_GenBJets" );
    vars.InitVars( "GenBJet_RecoJetEta",-9.,"N_GenBJets" );
    vars.InitVars( "GenBJet_RecoJetPhi",-9.,"N_GenBJets" );
    vars.InitVars( "GenBJet_RecoJetE",-9.,"N_GenBJets" );
    vars.InitVars( "GenBJet_RecoJetCSV",-9.,"N_GenBJets" );
    vars.InitVars( "GenBJet_NHadrons",-9.,"N_GenBJets" );
    
    vars.InitVar("Evt_M_HardestGenBJets");
    vars.InitVar("Evt_Dr_HardestGenBJets");
    vars.InitVar("Evt_M_MinDeltaRGenBJets");
    vars.InitVar("Evt_Dr_MinDeltaRGenBJets");
    //vars.InitVar("Evt_Pt_MinDeltaRGenBJets");
    vars.InitVar("Evt_M_GenBJetsAverage");
    vars.InitVar("Evt_Deta_GenBJetsAverage");
    vars.InitVar("Evt_Dr_GenBJetsAverage");
    vars.InitVar("Evt_M_GenBJetsClosestTo125");
    
    vars.InitVar("Evt_HT_GenBJets");
    
    initialized = true;
}

const pat::Jet* GenBJetProcessor::GetPatJet(const reco::GenJet& genjet,const std::vector<pat::Jet>& patjets){
  
  for(auto patjet=patjets.begin(); patjet!=patjets.end(); patjet++){
      if(patjet->pt()>0 && genjet.pt()>0 && BoostedUtils::DeltaR(patjet->p4(),genjet.p4())<0.2){
          return &(*patjet);
          break;
        }
  }
  return 0;
}

void GenBJetProcessor::Process(const InputCollections& input,VariableContainer& vars){

    if(!initialized) cerr << "tree processor not initialized" << endl;

    const char* btagger="DeepCSV";

    if(input.genTopEvt.TTxIsFilled()){
      
      std::vector<reco::GenJet> b_genjets = input.genTopEvt.GetBGenJets();
      
      if(b_genjets.size()>0){
        
        std::vector<const pat::Jet*> b_genjets_recojets;
        for(auto genbjet = b_genjets.begin(); genbjet != b_genjets.end(); genbjet++){
          b_genjets_recojets.push_back(GetPatJet(*genbjet,input.selectedJets));
        }
        std::vector<int> b_genjets_nbhadrons = input.genTopEvt.GetBGenJetsNHadrons();
        
        
        // B-genjets kinematic variables
        vars.FillVar( "N_GenBJets", b_genjets.size());
        reco::GenJet leadingbjet = b_genjets.at(0);
        reco::GenJet subleadingbjet = b_genjets.at(0);
        for(uint i=0; i<b_genjets.size(); i++){
          if(b_genjets[i].pt() > leadingbjet.pt()){
            leadingbjet = b_genjets[i];
            subleadingbjet = leadingbjet;
          }
          vars.FillVars( "GenBJet_Pt", i, b_genjets[i].pt());
          vars.FillVars( "GenBJet_Eta", i, b_genjets[i].eta());
          vars.FillVars( "GenBJet_Phi", i, b_genjets[i].phi());
          vars.FillVars( "GenBJet_E", i, b_genjets[i].energy());
          vars.FillVars( "GenBJet_NHadrons", i, b_genjets_nbhadrons[i]);
          vars.FillVars( "GenBJet_RecoJetPt", i, b_genjets_recojets[i]!=0 ? b_genjets_recojets[i]->pt() : -1);
          vars.FillVars( "GenBJet_RecoJetEta", i, b_genjets_recojets[i]!=0 ? b_genjets_recojets[i]->eta() : -1);
          vars.FillVars( "GenBJet_RecoJetPhi", i, b_genjets_recojets[i]!=0 ? b_genjets_recojets[i]->phi() : -1);
          vars.FillVars( "GenBJet_RecoJetE", i, b_genjets_recojets[i]!=0 ? b_genjets_recojets[i]->energy() : -1);
          vars.FillVars( "GenBJet_RecoJetCSV", i, b_genjets_recojets[i]!=0 ? MiniAODHelper::GetJetCSV(*b_genjets_recojets[i],btagger) : -2);
        }
        
        
        if(b_genjets.size()>1){
          // Fill Variables for hardest GenBJets
          math::XYZTLorentzVector leadingJetVec = leadingbjet.p4();
          math::XYZTLorentzVector subleadingJetVec = subleadingbjet.p4();
          float DrHardest = BoostedUtils::DeltaR(leadingJetVec,subleadingJetVec);
          vars.FillVar("Evt_M_HardestGenBJets",(leadingJetVec+subleadingJetVec).M());
          vars.FillVar("Evt_Dr_HardestGenBJets",DrHardest);
          // Fill Variables for closest GenBJets
          int idClosestJet1 = -1;
          int idClosestJet2 = -1;
          float minDrJets = BoostedUtils::GetClosestJetIDs(idClosestJet1,idClosestJet2,b_genjets);
          math::XYZTLorentzVector closestJetVec1 = b_genjets[idClosestJet1].p4();
          math::XYZTLorentzVector closestJetVec2 = b_genjets[idClosestJet2].p4();
          vars.FillVar("Evt_M_MinDeltaRGenBJets",(closestJetVec1+closestJetVec2).M());
          vars.FillVar("Evt_Dr_MinDeltaRGenBJets",minDrJets);
          //vars.FillVar("Evt_Pt_MinDeltaRGenBJets",(closestJetVec1+closestJetVec2).Pt());
        }
        
        
        // JetRelation Variables
        float mJetsAverage = 0;
        float detaJetsAverage = 0;
        float drJetsAverage = 0;
        float mGenBJetsClosestTo125 = -999;
        vector<float> mGenBJets;
        
        int nPairsJets = 0;
        std::vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(b_genjets);
        for(std::vector<math::XYZTLorentzVector>::iterator itJetVec1 = jetvecs.begin();itJetVec1 != jetvecs.end();++itJetVec1){        
          for(std::vector<math::XYZTLorentzVector>::iterator itJetVec2 = itJetVec1+1;itJetVec2 != jetvecs.end();++itJetVec2){
            
            mGenBJets.push_back((*itJetVec1+*itJetVec2).M());
            mJetsAverage += mGenBJets.back();
            if(fabs(mGenBJets.back()-125)<fabs(mGenBJetsClosestTo125-125)) mGenBJetsClosestTo125 = mGenBJets.back();
            
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
        
        vars.FillVar("Evt_M_GenBJetsAverage",mJetsAverage);
        vars.FillVar("Evt_Deta_GenBJetsAverage",detaJetsAverage);
        vars.FillVar("Evt_Dr_GenBJetsAverage",drJetsAverage);
        vars.FillVar("Evt_M_GenBJetsClosestTo125",mGenBJetsClosestTo125);
        
        // Fill Ht Variables
        float htbjets = 0.;
        for(std::vector<reco::GenJet>::const_iterator itJet = b_genjets.begin() ; itJet != b_genjets.end(); ++itJet){
          htbjets += itJet->pt();
        }
        vars.FillVar("Evt_HT_GenBJets",htbjets);
      }
    }
}
