#include "BoostedTTH/BoostedAnalyzer/interface/MVAVarProcessor.hpp"

using namespace std;

MVAVarProcessor::MVAVarProcessor(){}
MVAVarProcessor::~MVAVarProcessor(){}


void MVAVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
 
  vars.InitVar( "N_Jets","I" );
  vars.InitVar( "N_LooseJets","I" );
  vars.InitVar( "N_TightLeptons","I" );
  vars.InitVar( "N_LooseLeptons" ,"I");
  vars.InitVar( "N_TightElectrons" ,"I");
  vars.InitVar( "N_LooseElectrons","I" );
  vars.InitVar( "N_TightMuons" ,"I");
  vars.InitVar( "N_LooseMuons" ,"I");
  vars.InitVar( "N_BTagsM" ,"I");
  vars.InitVar( "N_BTagsT","I" );
  vars.InitVar( "N_BTagsL" ,"I");
  vars.InitVar( "N_PrimaryVertices","I" );
  
  vars.InitVars( "E_Jet","N_Jets" );
  vars.InitVars( "M_Jet","N_Jets" );
  vars.InitVars( "Pt_Jet","N_Jets" );
  vars.InitVars( "Phi_Jet","N_Jets" );
  vars.InitVars( "Eta_Jet","N_Jets" );
  vars.InitVars( "CSV_Jet","N_Jets" );
  vars.InitVars( "Flav_Jet","N_Jets" );
  
  vars.InitVars( "E_TaggedJet","N_BTagsM" );
  vars.InitVars( "M_TaggedJet","N_BTagsM" );
  vars.InitVars( "Pt_TaggedJet","N_BTagsM" );
  vars.InitVars( "Phi_TaggedJet","N_BTagsM" );
  vars.InitVars( "Eta_TaggedJet","N_BTagsM" );
  
  vars.InitVar( "E_PrimaryLepton" );
  vars.InitVar( "M_PrimaryLepton" );
  vars.InitVar( "Pt_PrimaryLepton" );
  vars.InitVar( "Eta_PrimaryLepton" );
  vars.InitVar( "Phi_PrimaryLepton" );
  
  vars.InitVars( "E_LooseLepton","N_LooseLeptons" );
  vars.InitVars( "M_LooseLepton","N_LooseLeptons" );
  vars.InitVars( "Pt_LooseLepton","N_LooseLeptons" );
  vars.InitVars( "Eta_LooseLepton","N_LooseLeptons" );
  vars.InitVars( "Phi_LooseLepton","N_LooseLeptons" );
  
  vars.InitVars( "E_Muon","N_LooseMuons" );
  vars.InitVars( "M_Muon","N_LooseMuons" );
  vars.InitVars( "Pt_Muon","N_LooseMuons" );
  vars.InitVars( "Eta_Muon","N_LooseMuons" );
  vars.InitVars( "Phi_Muon","N_LooseMuons" );
  
  vars.InitVars( "E_Electron","N_LooseElectrons" );
  vars.InitVars( "M_Electron","N_LooseElectrons" );
  vars.InitVars( "Pt_Electron","N_LooseElectrons" );
  vars.InitVars( "Eta_Electron","N_LooseElectrons" );
  vars.InitVars( "Phi_Electron","N_LooseElectrons" );
  
  vars.InitVar( "Pt_MET" );
  vars.InitVar( "Phi_MET" );

  vars.InitVar("M3");
  vars.InitVar("M3_OneJetTagged");
  vars.InitVar("MTW");
  vars.InitVar("HT");
  vars.InitVar("HT_Jets");
  vars.InitVar("M_Total");
  vars.InitVar("MHT");
  
  vars.InitVars( "CSV","N_Jets" );
  vars.InitVar( "CSV_Average" );
  vars.InitVar( "CSV_Min" );
  vars.InitVar( "CSV_Dev" );
  vars.InitVar( "CSV_Average_Tagged" );
  vars.InitVar( "CSV_Min_Tagged" );
  vars.InitVar( "CSV_Dev_Tagged" );

  vars.InitVar( "M_MinDeltaRJets" );    
  vars.InitVar( "M_MinDeltaRTaggedJets" );
  vars.InitVar( "M_MinDeltaRUntaggedJets" );
  vars.InitVar( "M_MinDeltaRLeptonTaggedJet" );
  vars.InitVar( "M_MinDeltaRLeptonJet" );

  vars.InitVar( "Dr_MinDeltaRJets" );    
  vars.InitVar( "Dr_MinDeltaRTaggedJets" );
  vars.InitVar( "Dr_MinDeltaRUntaggedJets" );
  vars.InitVar( "Dr_MinDeltaRLeptonTaggedJet" );
  vars.InitVar( "Dr_MinDeltaRLeptonJet" );

  vars.InitVar( "Pt_MinDeltaRJets" );    
  vars.InitVar( "Pt_MinDeltaRTaggedJets" );
  vars.InitVar( "Pt_MinDeltaRUntaggedJets" );

  vars.InitVar( "M_JetsAverage" );
  vars.InitVar( "M_TaggedJetsAverage" );
  vars.InitVar( "M_UntaggedJetsAverage" );
  
  vars.InitVar( "Eta_JetsAverage" );
  vars.InitVar( "Eta_TaggedJetsAverage" );
  vars.InitVar( "Eta_UntaggedJetsAverage" );
  
  vars.InitVar( "M2_JetsAverage" );
  vars.InitVar( "M2_TaggedJetsAverage" );
  vars.InitVar( "M2_UntaggedJetsAverage" );
  vars.InitVar( "M2_2JetsAverage" );
  vars.InitVar( "M2_3JetsAverage" );
  vars.InitVar( "M2_4JetsAverage" );
  vars.InitVar( "M2_5JetsAverage" );
  vars.InitVar( "M2_6JetsAverage" );
  vars.InitVar( "M2_2TaggedJetsAverage" );
  vars.InitVar( "M2_3TaggedJetsAverage" );
  vars.InitVar( "M2_4TaggedJetsAverage" );
  
  vars.InitVar( "Deta_JetsAverage" );
  vars.InitVar( "Deta_TaggedJetsAverage" );
  vars.InitVar( "Deta_UntaggedJetsAverage" );
  vars.InitVar( "Deta_2JetsAverage" );
  vars.InitVar( "Deta_3JetsAverage" );
  vars.InitVar( "Deta_4JetsAverage" );
  vars.InitVar( "Deta_5JetsAverage" );
  vars.InitVar( "Deta_6JetsAverage" );
  vars.InitVar( "Deta_2TaggedJetsAverage" );
  vars.InitVar( "Deta_3TaggedJetsAverage" );
  vars.InitVar( "Deta_4TaggedJetsAverage" );
  
  vars.InitVar( "Dr_JetsAverage" );
  vars.InitVar( "Dr_TaggedJetsAverage" );
  vars.InitVar( "Dr_UntaggedJetsAverage" );
  vars.InitVar( "Dr_2JetsAverage" );
  vars.InitVar( "Dr_3JetsAverage" );
  vars.InitVar( "Dr_4JetsAverage" );
  vars.InitVar( "Dr_5JetsAverage" );
  vars.InitVar( "Dr_6JetsAverage" );
  vars.InitVar( "Dr_2TaggedJetsAverage" );
  vars.InitVar( "Dr_3TaggedJetsAverage" );
  vars.InitVar( "Dr_4TaggedJetsAverage" );
  
  vars.InitVar( "Dkt_JetsAverage" );
  vars.InitVar( "Dkt_TaggedJetsAverage" );
  vars.InitVar( "Dkt_UntaggedJetsAverage" );
  vars.InitVar( "Dkt_2JetsAverage" );
  vars.InitVar( "Dkt_3JetsAverage" );
  vars.InitVar( "Dkt_4JetsAverage" );
  vars.InitVar( "Dkt_5JetsAverage" );
  vars.InitVar( "Dkt_6JetsAverage" );
  vars.InitVar( "Dkt_2TaggedJetsAverage" );
  vars.InitVar( "Dkt_3TaggedJetsAverage" );
  vars.InitVar( "Dkt_4TaggedJetsAverage" );
  
  vars.InitVar( "M_TaggedJetsClosestTo125" );
  
  vars.InitVar( "JetPtOverJetE" );
  
  vars.InitVar( "Aplanarity" );
  vars.InitVar( "Sphericity" );
    
  vars.InitVar( "H0" );
  vars.InitVar( "H1" );
  vars.InitVar( "H2" );
  vars.InitVar( "H3" );
  vars.InitVar( "H4" );

  vars.InitVar( "MaxDeta_Jets_Jet" );
  vars.InitVar( "MaxDeta_Jets_TaggedJet" );
  vars.InitVar( "MaxDeta_TaggedJets_TaggedJet" );

  vars.InitVar( "M_MedianTaggedJets" );
  
  vars.InitVar( "Drmax_Lepton_Jet" );
  vars.InitVar( "Detamax_Lepton_Jet" );
  
  vars.InitVars( "CosTheta_cm_Jet","N_Jets" );
  vars.InitVar( "CosThetamax_cm_Jet" );

  vars.InitVar( "Drmax_Jet1_Jet" );
    
  vars.InitVar( "Detamax_Jet1_Jet" );

  vars.InitVars("CosThetaStar_Lepton_Jet","N_Jets");
  vars.InitVars("CosThetaStar_Jet1_Jet","N_Jets");
  vars.InitVars("CosThetaStar_Jet2_Jet","N_Jets");
  vars.InitVars("CosThetaStar_Jet3_Jet","N_Jets");
  vars.InitVars("CosThetaStar_Jet4_Jet","N_Jets");

  vars.InitVars("Dr_Lepton_Jet","N_Jets");
  vars.InitVars("Dr_Jet1_Jet","N_Jets");
  vars.InitVars("Dr_Jet2_Jet","N_Jets");
  vars.InitVars("Dr_Jet3_Jet","N_Jets");
  vars.InitVars("Dr_Jet4_Jet","N_Jets");

  vars.InitVars("Dkt_Lepton_Jet","N_Jets");
  vars.InitVars("Dkt_Jet1_Jet","N_Jets");
  vars.InitVars("Dkt_Jet2_Jet","N_Jets");
  vars.InitVars("Dkt_Jet3_Jet","N_Jets");
  vars.InitVars("Dkt_Jet4_Jet","N_Jets");

  vars.InitVars("Deta_Lepton_Jet","N_Jets");
  vars.InitVars("Deta_Jet1_Jet","N_Jets");
  vars.InitVars("Deta_Jet2_Jet","N_Jets");
  vars.InitVars("Deta_Jet3_Jet","N_Jets");
  vars.InitVars("Deta_Jet4_Jet","N_Jets");
  
  vars.InitVar("Deta_TopLep_BB_Ohio");
  vars.InitVar("Deta_TopHad_BB_Ohio");
  vars.InitVar("Best_Higgs_Mass_Ohio");
  vars.InitVar("Deta_Fn_Ohio");
  vars.InitVar("Dr_BB_Ohio");

  initialized=true;
}

void MVAVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  const char* btagger="combinedInclusiveSecondaryVertexV2BJetTags";
  std::vector<pat::Jet> selectedTaggedJets;
  std::vector<pat::Jet> selectedTaggedJetsT;
  std::vector<pat::Jet> selectedTaggedJetsL;
  std::vector<pat::Jet> selectedUntaggedJets;
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet){
    if(BoostedUtils::PassesCSV(*itJet, 'M')){
      selectedTaggedJets.push_back(*itJet);
    }
    else{
      selectedUntaggedJets.push_back(*itJet);
    }
    if(BoostedUtils::PassesCSV(*itJet, 'L')){
      selectedTaggedJetsL.push_back(*itJet);
    }
    if(BoostedUtils::PassesCSV(*itJet, 'T')){
      selectedTaggedJetsT.push_back(*itJet);
    }
  }
  
  // Fill Multiplicity Variables
  vars.FillVar( "N_PrimaryVertices",input.selectedPVs.size());  
  vars.FillVar( "N_Jets",input.selectedJets.size());
  vars.FillVar( "N_LooseJets",input.selectedJetsLoose.size());
  vars.FillVar( "N_TightLeptons",input.selectedElectrons.size()+ input.selectedMuons.size());  
  vars.FillVar( "N_LooseLeptons",input.selectedElectronsLoose.size()+ input.selectedMuonsLoose.size());  
  vars.FillVar( "N_TightElectrons",input.selectedElectrons.size());  
  vars.FillVar( "N_LooseElectrons",input.selectedElectronsLoose.size());  
  vars.FillVar( "N_TightMuons",input.selectedMuons.size());  
  vars.FillVar( "N_LooseMuons",input.selectedMuonsLoose.size());  
  
  // Fill Jet Variables
  // All Jets
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
    int iJet = itJet - input.selectedJets.begin();
    vars.FillVars( "E_Jet",iJet,itJet->energy() );
    vars.FillVars( "M_Jet",iJet,itJet->mass() );
    vars.FillVars( "Pt_Jet",iJet,itJet->pt() );
    vars.FillVars( "Eta_Jet",iJet,itJet->eta() );
    vars.FillVars( "Phi_Jet",iJet,itJet->phi() );
    vars.FillVars( "CSV_Jet",iJet,fmax(itJet->bDiscriminator(btagger),-.1) );        
    vars.FillVars( "Flav_Jet",iJet,itJet->partonFlavour() );        
  }
  
  // Tagged Jets
  for(std::vector<pat::Jet>::iterator itTaggedJet = selectedTaggedJets.begin() ; itTaggedJet != selectedTaggedJets.end(); ++itTaggedJet){
    int iTaggedJet = itTaggedJet - selectedTaggedJets.begin();
    vars.FillVars( "E_TaggedJet",iTaggedJet,itTaggedJet->energy() );
    vars.FillVars( "M_TaggedJet",iTaggedJet,itTaggedJet->mass() );
    vars.FillVars( "Pt_TaggedJet",iTaggedJet,itTaggedJet->pt() );
    vars.FillVars( "Eta_TaggedJet",iTaggedJet,itTaggedJet->eta() );
    vars.FillVars( "Phi_TaggedJet",iTaggedJet,itTaggedJet->phi() );
  }
  
  // Fill Lepton Variables
  std::vector<math::XYZTLorentzVector> looseLeptonVecs = BoostedUtils::GetLepVecs(input.selectedElectronsLoose,input.selectedMuonsLoose);
  for(std::vector<math::XYZTLorentzVector>::iterator itLep = looseLeptonVecs.begin() ; itLep != looseLeptonVecs.end(); ++itLep){
    int iLep = itLep - looseLeptonVecs.begin();
    vars.FillVars( "E_LooseLepton",iLep,itLep->E() );
    vars.FillVars( "M_LooseLepton",iLep,itLep->M() );
    vars.FillVars( "Pt_LooseLepton",iLep,itLep->Pt() );
    vars.FillVars( "Eta_LooseLepton",iLep,itLep->Eta());
    vars.FillVars( "Phi_LooseLepton",iLep,itLep->Phi() );
  }
  
  math::XYZTLorentzVector primLepVec = math::XYZTLorentzVector();
  if(input.selectedElectrons.size()>0 || input.selectedMuons.size()>0){
    primLepVec = BoostedUtils::GetPrimLepVec(input.selectedElectrons,input.selectedMuons);
    vars.FillVar( "E_PrimaryLepton",primLepVec.E());
    vars.FillVar( "M_PrimaryLepton",primLepVec.M());
    vars.FillVar( "Pt_PrimaryLepton",primLepVec.Pt() );
    vars.FillVar( "Eta_PrimaryLepton",primLepVec.Eta());
    vars.FillVar( "Phi_PrimaryLepton",primLepVec.Phi());    
  }
  
  for(std::vector<pat::Electron>::const_iterator itEle = input.selectedElectronsLoose.begin(); itEle != input.selectedElectronsLoose.end(); ++itEle){
    int iEle = itEle - input.selectedElectronsLoose.begin();
    vars.FillVars( "E_Electron",iEle,itEle->energy() );
    vars.FillVars( "M_Electron",iEle,itEle->mass() );
    vars.FillVars( "Pt_Electron",iEle,itEle->pt() );
    vars.FillVars( "Eta_Electron",iEle,itEle->eta() );
    vars.FillVars( "Phi_Electron",iEle,itEle->phi() ); 
  }
  for(std::vector<pat::Muon>::const_iterator itMu = input.selectedMuonsLoose.begin(); itMu != input.selectedMuonsLoose.end(); ++itMu){
    int iMu = itMu - input.selectedMuonsLoose.begin();
    vars.FillVars( "E_Muon",iMu,itMu->energy() );
    vars.FillVars( "M_Muon",iMu,itMu->mass() );
    vars.FillVars( "Pt_Muon",iMu,itMu->pt() );
    vars.FillVars( "Eta_Muon",iMu,itMu->eta() );
    vars.FillVars( "Phi_Muon",iMu,itMu->phi() );
  }
  
  vars.FillVar( "Pt_MET",input.pfMets[0].pt() );
  vars.FillVar( "Phi_MET",input.pfMets[0].phi() );
  
  std::vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);
  math::XYZTLorentzVector metvec = input.pfMets[0].p4();
  
  // Fill M3 Variables
  float m3 = -1.;
  float maxpt=-1;
  for(std::vector<math::XYZTLorentzVector>::iterator itJetVec1 = jetvecs.begin() ; itJetVec1 != jetvecs.end(); ++itJetVec1){
    for(std::vector<math::XYZTLorentzVector>::iterator itJetVec2 = itJetVec1+1 ; itJetVec2 != jetvecs.end(); ++itJetVec2){
      for(std::vector<math::XYZTLorentzVector>::iterator itJetVec3 = itJetVec2+1 ; itJetVec3 != jetvecs.end(); ++itJetVec3){
    
        math::XYZTLorentzVector m3vec = *itJetVec1 + *itJetVec2 + *itJetVec3;
        
	      if(m3vec.Pt() > maxpt){
	        maxpt = m3vec.Pt();
	        m3 = m3vec.M();
	      }
      } 
    }
  }
  vars.FillVar("M3",m3);
  float m3tagged = -1.;
  float maxpttagged=-1.;
  for(std::vector<pat::Jet>::iterator itJetUntagged1 = selectedUntaggedJets.begin() ; itJetUntagged1 != selectedUntaggedJets.end(); ++itJetUntagged1){
    for(std::vector<pat::Jet>::iterator itJetUntagged2 = itJetUntagged1+1 ; itJetUntagged2 != selectedUntaggedJets.end(); ++itJetUntagged2){
      for(std::vector<pat::Jet>::iterator itJetTagged = selectedTaggedJets.begin() ; itJetTagged != selectedTaggedJets.end(); ++itJetTagged){
        
        math::XYZTLorentzVector m3vec = itJetUntagged1->p4() + itJetUntagged2->p4() + itJetTagged->p4();
	      
        if(m3vec.Pt() > maxpttagged){
	        maxpttagged = m3vec.Pt();
	        m3tagged = m3vec.M();
	      }
      } 
    }
  }
  vars.FillVar("M3_OneJetTagged",m3tagged);
  
  // Fill MTW
  float mtw = -1.;
  if(input.selectedElectrons.size()>0 || input.selectedMuons.size()>0){
    mtw = sqrt(2*(primLepVec.Pt()*input.pfMets[0].pt() - primLepVec.Px()*input.pfMets[0].px() - primLepVec.Py()*input.pfMets[0].py()));
  }
  vars.FillVar("MTW",mtw);
  
  // Fill Ht Variables
  float ht = 0.;
  float htjets = 0.;
  float mht_px = 0.;
  float mht_py = 0.;
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
    ht += itJet->pt();
    htjets += itJet->pt();
    mht_px += itJet->px();
    mht_py += itJet->py();
  }
  for(std::vector<pat::Electron>::const_iterator itEle = input.selectedElectronsLoose.begin(); itEle != input.selectedElectronsLoose.end(); ++itEle){
    ht += itEle->pt();
    mht_px += itEle->px();
    mht_py += itEle->py();
    
  }
  for(std::vector<pat::Muon>::const_iterator itMu = input.selectedMuonsLoose.begin(); itMu != input.selectedMuonsLoose.end(); ++itMu){
    ht += itMu->pt();
    mht_px += itMu->px();
    mht_py += itMu->py();
    
  }
  ht += input.pfMets[0].pt();
  
  vars.FillVar("HT",ht);
  vars.FillVar("MHT",sqrt( mht_px*mht_px + mht_py*mht_py ));
  vars.FillVar("HT_Jets",htjets);
  
  // Fill Event Mass
  math::XYZTLorentzVector p4all;
  for(std::vector<math::XYZTLorentzVector>::iterator itJetVec = jetvecs.begin() ; itJetVec != jetvecs.end(); ++itJetVec){
    p4all += *itJetVec;
  }
  for(std::vector<math::XYZTLorentzVector>::iterator itLep = looseLeptonVecs.begin() ; itLep != looseLeptonVecs.end(); ++itLep){
    p4all += *itLep;
  }
  p4all += metvec;
  vars.FillVar("M_Total",p4all.M());
  
  // Fill Number of b Tags
  vars.FillVar( "N_BTagsM",selectedTaggedJets.size() );  
  vars.FillVar( "N_BTagsL",selectedTaggedJetsL.size() );  
  vars.FillVar( "N_BTagsT",selectedTaggedJetsT.size() );
  
  // Fill CSV Variables
  // All Jets
  std::vector<float> csvJets;
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
    csvJets.push_back(fmax(itJet->bDiscriminator(btagger),-.1));
  }
  
  std::sort(csvJets.begin(),csvJets.end(),BoostedUtils::FirstIsLarger);
  vars.FillVar("CSV_Min",csvJets.size()>0 ? csvJets.back() : -.1);
  
  float averageCSV = 0;
  for(std::vector<float>::iterator itCSV = csvJets.begin() ; itCSV != csvJets.end(); ++itCSV){
    int iCSV = itCSV - csvJets.begin();
    vars.FillVars("CSV" ,iCSV,*itCSV);
    averageCSV += fmax(*itCSV,0);
  }
  averageCSV /= csvJets.size();
  vars.FillVar("CSV_Average" ,averageCSV );
  
  float csvDev = 0;
  for(std::vector<float>::iterator itCSV = csvJets.begin() ; itCSV != csvJets.end(); ++itCSV){
    csvDev += fabs(pow(*itCSV - averageCSV,2));
  }
  if(csvJets.size() > 0)
    csvDev /= csvJets.size();
  else
    csvDev=-1.;
  vars.FillVar("CSV_Dev",csvDev);
  
  // Tagged Jets
  vector<float> csvTaggedJets;
  for(std::vector<pat::Jet>::iterator itTaggedJet = selectedTaggedJets.begin() ; itTaggedJet != selectedTaggedJets.end(); ++itTaggedJet){
    csvTaggedJets.push_back(fmax(itTaggedJet->bDiscriminator( btagger),-.1));
  }
  sort(csvTaggedJets.begin(),csvTaggedJets.end(),BoostedUtils::FirstIsLarger);
  vars.FillVar("CSV_Min_Tagged",csvTaggedJets.size()>0 ? csvTaggedJets.back() : -.1);
  
  float averageCSVTagged = 0;
  for(std::vector<float>::iterator itCSVTagged = csvTaggedJets.begin() ; itCSVTagged != csvTaggedJets.end(); ++itCSVTagged){
    averageCSVTagged += fmax(*itCSVTagged,0);
  }
  averageCSVTagged /= csvTaggedJets.size();
  vars.FillVar("CSV_Average_Tagged",averageCSVTagged);
  
  float csvDevTagged = 0;
  for(std::vector<float>::iterator itCSVTagged = csvTaggedJets.begin() ; itCSVTagged != csvTaggedJets.end(); ++itCSVTagged){
    csvDevTagged += fabs(pow(*itCSVTagged - averageCSVTagged,2));
  }
  if(csvTaggedJets.size() > 0)
    csvDevTagged /= csvTaggedJets.size();
  else
    csvDevTagged=-1.;
    
  vars.FillVar("CSV_Dev_Tagged",csvDevTagged);
  // Fill Variables for closest ak5 Jets
  // All Jets
  if(input.selectedJets.size()>1){
    int idClosestJet1 = -1;
    int idClosestJet2 = -1;
    float minDrJets = BoostedUtils::GetClosestJetIDs(idClosestJet1,idClosestJet2,input.selectedJets);
    math::XYZTLorentzVector closestJetVec1 = input.selectedJets[idClosestJet1].p4();
    math::XYZTLorentzVector closestJetVec2 = input.selectedJets[idClosestJet1].p4();
    vars.FillVar("M_MinDeltaRJets",(closestJetVec1+closestJetVec2).M());
    vars.FillVar("Dr_MinDeltaRJets",minDrJets);
    vars.FillVar("Pt_MinDeltaRJets",(closestJetVec1+closestJetVec2).Pt());
  }
  // Tagged Jets
  if(selectedTaggedJets.size()>1){
    int idClosestTaggedJet1 = -1;
    int idClosestTaggedJet2 = -1;
    float minDrTaggedJets = BoostedUtils::GetClosestJetIDs(idClosestTaggedJet1,idClosestTaggedJet2,selectedTaggedJets);
    math::XYZTLorentzVector closestTaggedJetVec1 = selectedTaggedJets[idClosestTaggedJet1].p4();
    math::XYZTLorentzVector closestTaggedJetVec2 = selectedTaggedJets[idClosestTaggedJet2].p4();
    vars.FillVar("M_MinDeltaRTaggedJets",(closestTaggedJetVec1+closestTaggedJetVec2).M());
    vars.FillVar("Dr_MinDeltaRTaggedJets",minDrTaggedJets);
    vars.FillVar("Pt_MinDeltaRTaggedJets",(closestTaggedJetVec1+closestTaggedJetVec2).Pt());
  }
  // Untagged Jets
  if(selectedUntaggedJets.size()>1){
    int idClosestUntaggedJet1 = -1;
    int idClosestUntaggedJet2 = -1;
    float minDrUntaggedJets = BoostedUtils::GetClosestJetIDs(idClosestUntaggedJet1,idClosestUntaggedJet2,selectedUntaggedJets);
    math::XYZTLorentzVector closestUntaggedJetVec1 = selectedUntaggedJets[idClosestUntaggedJet1].p4();
    math::XYZTLorentzVector closestUntaggedJetVec2 = selectedUntaggedJets[idClosestUntaggedJet2].p4();
    vars.FillVar("M_MinDeltaRUntaggedJets",(closestUntaggedJetVec1+closestUntaggedJetVec2).M());
    vars.FillVar("Dr_MinDeltaRUntaggedJets",minDrUntaggedJets);
    vars.FillVar("Pt_MinDeltaRUntaggedJets",(closestUntaggedJetVec1+closestUntaggedJetVec2).Pt());
  }
  // Jet and Lepton
  if(input.selectedJets.size()>1&&(input.selectedElectrons.size()>0||input.selectedMuons.size()>0)){
    int idClosestJet = -1;
    float minDrLepJet = BoostedUtils::GetClosestLepJetID(idClosestJet,primLepVec,input.selectedJets);
    math::XYZTLorentzVector closestJetVec = input.selectedJets[idClosestJet].p4();
    vars.FillVar("M_MinDeltaRLeptonJet",(primLepVec+closestJetVec).M());
    vars.FillVar("Dr_MinDeltaRLeptonJet",minDrLepJet);
  }
  
  // Tagged Jet and Lepton
  if(selectedTaggedJets.size()>1&&(input.selectedElectrons.size()>0||input.selectedMuons.size()>0)){
    int idClosestTaggedJet = -1;
    float minDrLepTaggedJet = BoostedUtils::GetClosestLepJetID(idClosestTaggedJet,primLepVec,selectedTaggedJets);
    math::XYZTLorentzVector closestTaggedJetVec = input.selectedJets[idClosestTaggedJet].p4();
    vars.FillVar("M_MinDeltaRLeptonTaggedJet",(primLepVec+closestTaggedJetVec).M());
    vars.FillVar("Dr_MinDeltaRLeptonTaggedJet",minDrLepTaggedJet);
  }
  
  // JetRelation Variables
  // All Jets
  float mJetsAverage = 0;
  float eJetsAverage = 0;
  float ptJetsAverage = 0;
  float etaJetsAverage = 0;
  float m2JetsAverage = 0;
  float detaJetsAverage = 0;
  float drJetsAverage = 0;
  float dktJetsAverage = 0;
  
  int nPairsJets = 0;
  for(std::vector<math::XYZTLorentzVector>::iterator itJetVec1 = jetvecs.begin();itJetVec1 != jetvecs.end();++itJetVec1){
    mJetsAverage += itJetVec1->M();
    eJetsAverage += itJetVec1->E();
    ptJetsAverage += itJetVec1->Pt();
    etaJetsAverage += itJetVec1->Eta();
    
    for(std::vector<math::XYZTLorentzVector>::iterator itJetVec2 = itJetVec1+1;itJetVec2 != jetvecs.end();++itJetVec2){
      m2JetsAverage += (*itJetVec1+*itJetVec2).M();
      detaJetsAverage += fabs(itJetVec1->Eta()-itJetVec2->Eta());
      drJetsAverage += BoostedUtils::DeltaR(*itJetVec1,*itJetVec2);
      dktJetsAverage += BoostedUtils::DeltaKt(*itJetVec1,*itJetVec2);
      
      nPairsJets++;
    }
  }
  if(jetvecs.size() > 0){
    mJetsAverage /= (float) nPairsJets;
    etaJetsAverage /= (float) jetvecs.size();
  }
  if(nPairsJets > 0){
    m2JetsAverage /= (float) nPairsJets;
    detaJetsAverage /= (float) nPairsJets;
    drJetsAverage /= (float) nPairsJets;
    dktJetsAverage /= (float) nPairsJets;
  }
  vars.FillVar("M_JetsAverage",mJetsAverage);
  vars.FillVar("Eta_JetsAverage",etaJetsAverage);
  vars.FillVar("M2_JetsAverage",m2JetsAverage);
  vars.FillVar("Deta_JetsAverage",detaJetsAverage);
  vars.FillVar("Dr_JetsAverage",drJetsAverage);
  vars.FillVar("Dkt_JetsAverage",dktJetsAverage);
  vars.FillVar("JetPtOverJetE", ptJetsAverage/eJetsAverage);  
  
  // Tagged Jets
  float mTaggedJetsAverage = 0;
  float etaTaggedJetsAverage = 0;
  float m2TaggedJetsAverage = 0;
  vector<float> m2TaggedJets;
  float m2TaggedJetsClosestTo125 = -999;
  float detaTaggedJetsAverage = 0;
  float drTaggedJetsAverage = 0;
  float dktTaggedJetsAverage = 0;
  
  int nPairsTaggedJets=0;
  for(std::vector<pat::Jet>::iterator itTaggedJet1 = selectedTaggedJets.begin();itTaggedJet1 != selectedTaggedJets.end();++itTaggedJet1){
    math::XYZTLorentzVector taggedJetVec1 = itTaggedJet1->p4();
    
    mTaggedJetsAverage += taggedJetVec1.M();
    etaTaggedJetsAverage += taggedJetVec1.Eta();
    
    for(std::vector<pat::Jet>::iterator itTaggedJet2 = itTaggedJet1+1;itTaggedJet2 != selectedTaggedJets.end();++itTaggedJet2){
      math::XYZTLorentzVector taggedJetVec2 = itTaggedJet2->p4();
      
      m2TaggedJets.push_back((taggedJetVec1+taggedJetVec2).M());
      m2TaggedJetsAverage += m2TaggedJets.back();
      if(fabs(m2TaggedJets.back()-125)<fabs(m2TaggedJetsClosestTo125-125)) m2TaggedJetsClosestTo125 = m2TaggedJets.back();
      detaTaggedJetsAverage += fabs(taggedJetVec1.Eta()-taggedJetVec2.Eta());
      drTaggedJetsAverage += BoostedUtils::DeltaR(taggedJetVec1,taggedJetVec2);
      dktTaggedJetsAverage += BoostedUtils::DeltaKt(taggedJetVec1,taggedJetVec2);
      
      nPairsTaggedJets++;
    }
  }
  if(selectedTaggedJets.size() > 0){
    mTaggedJetsAverage /= (float) selectedTaggedJets.size();
    etaTaggedJetsAverage /= (float) selectedTaggedJets.size();
  }
  if(nPairsTaggedJets > 0){
    m2TaggedJetsAverage /= (float) nPairsTaggedJets;
    detaTaggedJetsAverage /= (float) nPairsTaggedJets;
    drTaggedJetsAverage /= (float) nPairsTaggedJets;
    dktTaggedJetsAverage /= (float) nPairsTaggedJets;
  }
  sort(m2TaggedJets.begin(),m2TaggedJets.end(),BoostedUtils::FirstIsLarger);
  
  vars.FillVar("M_TaggedJetsAverage",mTaggedJetsAverage);
  vars.FillVar("Eta_TaggedJetsAverage",etaTaggedJetsAverage);
  vars.FillVar("M2_TaggedJetsAverage",m2TaggedJetsAverage);
  if(m2TaggedJets.size()>0) vars.FillVar("M_MedianTaggedJets",m2TaggedJets.at(m2TaggedJets.size()/2));
  vars.FillVar("M_TaggedJetsClosestTo125",m2TaggedJetsClosestTo125);
  vars.FillVar("Deta_TaggedJetsAverage",detaTaggedJetsAverage);
  vars.FillVar("Dr_TaggedJetsAverage",drTaggedJetsAverage);
  vars.FillVar("Dkt_TaggedJetsAverage",dktTaggedJetsAverage);
  // Untagged Jets
  float mUntaggedJetsAverage = 0;
  float etaUntaggedJetsAverage = 0;
  float m2UntaggedJetsAverage=0;
  float detaUntaggedJetsAverage = 0;
  float drUntaggedJetsAverage=0;
  float dktUntaggedJetsAverage=0;
  int nPairsUntaggedJets=0;
  for(std::vector<pat::Jet>::iterator itUntaggedJet1 = selectedUntaggedJets.begin();itUntaggedJet1 != selectedUntaggedJets.end();++itUntaggedJet1){
    math::XYZTLorentzVector untaggedJetVec1 = itUntaggedJet1->p4();
    
    mUntaggedJetsAverage += untaggedJetVec1.M();
    etaUntaggedJetsAverage += untaggedJetVec1.Eta();
    
    for(std::vector<pat::Jet>::iterator itUntaggedJet2 = itUntaggedJet1+1;itUntaggedJet2 != selectedUntaggedJets.end();++itUntaggedJet2){
      math::XYZTLorentzVector untaggedJetVec2 = itUntaggedJet2->p4();
      m2UntaggedJetsAverage += (untaggedJetVec1+untaggedJetVec2).M();
      detaUntaggedJetsAverage += fabs(untaggedJetVec1.Eta()-untaggedJetVec2.Eta());
      drUntaggedJetsAverage += BoostedUtils::DeltaR(untaggedJetVec1,untaggedJetVec2);
      dktUntaggedJetsAverage += BoostedUtils::DeltaKt(untaggedJetVec1,untaggedJetVec2);
      nPairsUntaggedJets++;
    }
  }
  if(selectedUntaggedJets.size() > 0){
    mUntaggedJetsAverage /= (float) selectedUntaggedJets.size();
    etaUntaggedJetsAverage /= (float) selectedUntaggedJets.size();
  }
  if(nPairsUntaggedJets > 0){
    m2UntaggedJetsAverage /= nPairsUntaggedJets;
    detaUntaggedJetsAverage /= nPairsUntaggedJets;
    drUntaggedJetsAverage /= nPairsUntaggedJets;
    dktUntaggedJetsAverage /= nPairsUntaggedJets;
  }
  vars.FillVar( "M_UntaggedJetsAverage",mUntaggedJetsAverage );
  vars.FillVar( "Eta_UntaggedJetsAverage",etaUntaggedJetsAverage );
  vars.FillVar( "M2_UntaggedJetsAverage",m2UntaggedJetsAverage );
  vars.FillVar( "Deta_UntaggedJetsAverage",detaUntaggedJetsAverage );
  vars.FillVar( "Dr_UntaggedJetsAverage",drUntaggedJetsAverage );
  vars.FillVar( "Dkt_UntaggedJetsAverage",dktUntaggedJetsAverage );
  
  // Hardest N Jets
  for(int maxjets=2;maxjets<=6;maxjets++){
    
    float m2JetsAverage=0;
    float drJetsAverage=0;
    float dktJetsAverage=0;
    int nPairsJets=0;
    
    for(std::vector<math::XYZTLorentzVector>::iterator itJetVec1 = jetvecs.begin();itJetVec1 != jetvecs.end() && itJetVec1-jetvecs.begin() < maxjets;++itJetVec1){
      for(std::vector<math::XYZTLorentzVector>::iterator itJetVec2 = itJetVec1+1;itJetVec2 != jetvecs.end() && itJetVec2-jetvecs.begin() < maxjets;++itJetVec2){
        m2JetsAverage += (*itJetVec1+*itJetVec2).M();
        drJetsAverage += BoostedUtils::DeltaR(*itJetVec1,*itJetVec2);
        dktJetsAverage += BoostedUtils::DeltaKt(*itJetVec1,*itJetVec2);
        nPairsJets++;
      }
    }
    if(nPairsJets > 0){
      m2JetsAverage/=nPairsJets;
      drJetsAverage/=nPairsJets;
      dktJetsAverage/=nPairsJets;
    }
    
    TString mName = "M2_";
    TString detaName = "Deta_";
    TString drName = "Dr_";
    TString dktName = "Dkt_";
    mName += maxjets;
    detaName += maxjets;
    drName += maxjets;
    dktName += maxjets;
    mName+="JetsAverage";
    detaName += "JetsAverage";
    drName+="JetsAverage";
    dktName+="JetsAverage";
    
    vars.FillVar(mName.Data(),m2JetsAverage);
    vars.FillVar(detaName.Data(),drJetsAverage);
    vars.FillVar(drName.Data(),drJetsAverage);
    vars.FillVar(dktName.Data(),dktJetsAverage);
  }
  
  // N Jets with highest CSV
  std::vector<pat::Jet> jetsByCSV = input.selectedJets;
  std::sort(jetsByCSV.begin(), jetsByCSV.end(),BoostedUtils::FirstHasHigherCSV);
  for(int maxjets=2;maxjets<=4;maxjets++){
    float m2JetsAverage=0;
    float detaJetsAverage=0;
    float drJetsAverage=0;
    float dktJetsAverage=0;
    int nPairsJets=0;
    
    for(std::vector<pat::Jet>::iterator itJet1 = jetsByCSV.begin();itJet1 != jetsByCSV.end() && itJet1-jetsByCSV.begin() < maxjets;++itJet1){
      math::XYZTLorentzVector jetVec1 = itJet1->p4();
      
      for(std::vector<pat::Jet>::iterator itJet2 = itJet1+1;itJet2 != jetsByCSV.end() && itJet2-jetsByCSV.begin() < maxjets;++itJet2){
        math::XYZTLorentzVector jetVec2 = itJet2->p4();
        m2JetsAverage += (jetVec1+jetVec2).M();
        detaJetsAverage += fabs(jetVec1.Eta()-jetVec2.Eta());
        drJetsAverage += BoostedUtils::DeltaR(jetVec1,jetVec2);
        dktJetsAverage += BoostedUtils::DeltaKt(jetVec1,jetVec2);
        nPairsJets++;
      }
    }
    if(nPairsJets > 0){
      m2JetsAverage /= nPairsJets;
      detaJetsAverage /= nPairsJets;
      drJetsAverage /= nPairsJets;
      dktJetsAverage /= nPairsJets;
    }
    
    TString mName = "M2_";
    TString detaName = "Deta_";
    TString drName = "Dr_";
    TString dktName = "Dkt_";
    mName += maxjets;
    detaName += maxjets;
    drName += maxjets;
    dktName += maxjets;
    mName += "TaggedJetsAverage";
    detaName += "TaggedJetsAverage";
    drName += "TaggedJetsAverage";
    dktName += "TaggedJetsAverage";
    
    vars.FillVar(mName.Data(),m2JetsAverage);
    vars.FillVar(detaName.Data(),drJetsAverage);
    vars.FillVar(drName.Data(),drJetsAverage);
    vars.FillVar(dktName.Data(),dktJetsAverage);
  }
  
  // DeltaEta of Jets
  vars.FillVar("MaxDeta_Jets_Jet",BoostedUtils::GetJetAverageJetEtaMax(input.selectedJets,input.selectedJets));
  vars.FillVar("MaxDeta_Jets_TaggedJet",BoostedUtils::GetJetAverageJetEtaMax(input.selectedJets,selectedTaggedJets));
  vars.FillVar("MaxDeta_TaggedJets_TaggedJet",BoostedUtils::GetJetAverageJetEtaMax(selectedTaggedJets,selectedTaggedJets));
  
  // Event Shape Variables
  // Fox Wolfram Moments
  float h0,h1,h2,h3,h4;
  BoostedUtils::GetFoxWolframMoments(jetvecs, h0,h1,h2,h3,h4);
  vars.FillVar( "H0", h0 );
  vars.FillVar( "H1", h1 );
  vars.FillVar( "H2", h2 );
  vars.FillVar( "H3", h3 );
  vars.FillVar( "H4", h4 );
  
  // Aplanarity and Sphericity;
  float aplanarity,sphericity;
  BoostedUtils::GetAplanaritySphericity(primLepVec, metvec, jetvecs, aplanarity, sphericity) ;
  vars.FillVar( "Aplanarity", aplanarity );
  vars.FillVar( "Sphericity", sphericity );
  
  // Event Angle Variables 
  float drmax_lj=-1;
  float detamax_lj=-1;
  float drmax_j1j=-1;
  float drmax_j2j=-1;
  float drmax_j3j=-1;
  float drmax_j4j=-1;
  float detamax_j1j=-1;
  float detamax_j2j=-1;
  float detamax_j3j=-1;
  float detamax_j4j=-1;
  float costhetamax_jcm=-1;
  for(std::vector<math::XYZTLorentzVector>::iterator itJetVec = jetvecs.begin();itJetVec != jetvecs.end();++itJetVec){
    int iJetVec = itJetVec - jetvecs.begin();
    
    float c_lj=-1.5;
    float c_j1j=-1.5;
    float c_j2j=-1.5;
    float c_j3j=-1.5;
    float c_j4j=-1.5;
    float deta_lj=-1.;
    float deta_j1j=-1.;
    float deta_j2j=-1.;
    float deta_j3j=-1.;
    float deta_j4j=-1.;
    float dr_lj=-1.;
    float dr_j1j=-1.;
    float dr_j2j=-1.;
    float dr_j3j=-1.;
    float dr_j4j=-1.;
    float dkt_lj=-50.;
    float dkt_j1j=-50.;
    float dkt_j2j=-50.;
    float dkt_j3j=-50.;
    float dkt_j4j=-50.;
    
    if(primLepVec.Pt()>1){
      deta_lj = BoostedUtils::DeltaEta(*itJetVec,primLepVec);
      dr_lj = BoostedUtils::DeltaR(*itJetVec,primLepVec);
      dkt_lj = BoostedUtils::DeltaKt(*itJetVec,primLepVec);
      c_lj = BoostedUtils::CosThetaStar(*itJetVec,primLepVec);
    }
    if(jetvecs.size()>0){
      deta_j1j = BoostedUtils::DeltaEta(*itJetVec,jetvecs[0]);
      dr_j1j = BoostedUtils::DeltaR(*itJetVec,jetvecs[0]);
      dkt_j1j = BoostedUtils::DeltaKt(*itJetVec,jetvecs[0]);
      c_j1j = BoostedUtils::CosThetaStar(*itJetVec,jetvecs[0]);
    }
    if(jetvecs.size()>1){
      deta_j2j = BoostedUtils::DeltaEta(*itJetVec,jetvecs[1]);
      dr_j2j = BoostedUtils::DeltaR(*itJetVec,jetvecs[1]);
      dkt_j2j = BoostedUtils::DeltaKt(*itJetVec,jetvecs[1]);
      c_j2j = BoostedUtils::CosThetaStar(*itJetVec,jetvecs[1]);
    }
    if(jetvecs.size()>2){
      deta_j3j = BoostedUtils::DeltaEta(*itJetVec,jetvecs[2]);
      dr_j3j = BoostedUtils::DeltaR(*itJetVec,jetvecs[2]);
      dkt_j3j = BoostedUtils::DeltaKt(*itJetVec,jetvecs[2]);
      c_j3j = BoostedUtils::CosThetaStar(*itJetVec,jetvecs[2]);
    }
    if(jetvecs.size()>3){
      deta_j4j = BoostedUtils::DeltaEta(*itJetVec,jetvecs[3]);
      dr_j4j = BoostedUtils::DeltaR(*itJetVec,jetvecs[3]);
      dkt_j4j = BoostedUtils::DeltaKt(*itJetVec,jetvecs[3]);
      c_j4j = BoostedUtils::CosThetaStar(*itJetVec,jetvecs[3]);
    }
    
    vars.FillVars("Deta_Lepton_Jet",iJetVec,deta_lj);
    vars.FillVars("Deta_Jet1_Jet",iJetVec,deta_j1j);
    vars.FillVars("Deta_Jet2_Jet",iJetVec,deta_j2j);
    vars.FillVars("Deta_Jet3_Jet",iJetVec,deta_j3j);
    vars.FillVars("Deta_Jet4_Jet",iJetVec,deta_j4j);
    
    vars.FillVars("Dr_Lepton_Jet",iJetVec,dr_lj);
    vars.FillVars("Dr_Jet1_Jet",iJetVec,dr_j1j);
    vars.FillVars("Dr_Jet2_Jet",iJetVec,dr_j2j);
    vars.FillVars("Dr_Jet3_Jet",iJetVec,dr_j3j);
    vars.FillVars("Dr_Jet4_Jet",iJetVec,dr_j4j);
    
    vars.FillVars("Dkt_Lepton_Jet",iJetVec,dkt_lj);
    vars.FillVars("Dkt_Jet1_Jet",iJetVec,dkt_j1j);
    vars.FillVars("Dkt_Jet2_Jet",iJetVec,dkt_j2j);
    vars.FillVars("Dkt_Jet3_Jet",iJetVec,dkt_j3j);
    vars.FillVars("Dkt_Jet4_Jet",iJetVec,dkt_j4j);
    
    vars.FillVars("CosThetaStar_Lepton_Jet",iJetVec,c_lj);
    vars.FillVars("CosThetaStar_Jet1_Jet",iJetVec,c_j1j);
    vars.FillVars("CosThetaStar_Jet2_Jet",iJetVec,c_j2j);
    vars.FillVars("CosThetaStar_Jet3_Jet",iJetVec,c_j3j);
    vars.FillVars("CosThetaStar_Jet4_Jet",iJetVec,c_j4j);
    
    if(drmax_lj < dr_lj){
      drmax_lj = dr_lj;
    }
    if(detamax_lj < deta_lj){
      detamax_lj = deta_lj;
    }
    if(drmax_j1j < dr_j1j){
      drmax_j1j = dr_j1j;
    }
    if(drmax_j2j < dr_j2j){
      drmax_j2j = dr_j2j;
    }
    if(drmax_j3j < dr_j3j){
      drmax_j3j = dr_j3j;
    }
    if(drmax_j4j < dr_j4j){
      drmax_j4j = dr_j4j;
    }
    if(detamax_j1j < deta_j1j){
      detamax_j1j = deta_j1j;
    }
    if(detamax_j2j < deta_j2j){
      detamax_j2j = deta_j2j;
    }
    if(detamax_j3j < deta_j3j){
      detamax_j3j = deta_j3j;
    }
    if(detamax_j4j < deta_j4j){
      detamax_j4j = deta_j4j;
    }
    
    float costheta_jcm= BoostedUtils::CosThetaCM(*itJetVec,p4all);
    vars.FillVars("CosTheta_cm_Jet",iJetVec,costheta_jcm  );
    if(costhetamax_jcm<fabs(costheta_jcm)){
      costhetamax_jcm=fabs(costheta_jcm);
    }
  }
  vars.FillVar("Drmax_Lepton_Jet",drmax_lj);
  vars.FillVar("Detamax_Lepton_Jet",detamax_lj);
  vars.FillVar("Drmax_Jet1_Jet",drmax_j1j);
  vars.FillVar("Detamax_Jet1_Jet",detamax_j1j);
  vars.FillVar("CosThetamax_cm_Jet",costhetamax_jcm );
  
  // Ohio Variables
  std::vector<pat::Jet> selectedJetsLooseExclusive;
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJetsLoose.begin() ; itJet != input.selectedJetsLoose.end(); ++itJet){
    if(itJet->pt() >= 30) continue;
    selectedJetsLooseExclusive.push_back(*itJet);
  }
  
  float best_higgs_mass;
  float dRbb;
  float abs_dEta_hadtop_bb;
  float abs_dEta_leptop_bb;
  float dEta_fn;
  BoostedUtils::TTHRecoVarsOhio(input.selectedJets,selectedJetsLooseExclusive, input.pfMets[0], primLepVec, best_higgs_mass, dRbb,abs_dEta_hadtop_bb,abs_dEta_leptop_bb, dEta_fn);
  vars.FillVar("Deta_TopLep_BB_Ohio",abs_dEta_leptop_bb);
  vars.FillVar("Deta_TopHad_BB_Ohio",abs_dEta_hadtop_bb);
  vars.FillVar("Best_Higgs_Mass_Ohio",best_higgs_mass);
  vars.FillVar("Deta_Fn_Ohio",dEta_fn);
  vars.FillVar("Dr_BB_Ohio",dRbb);

}
