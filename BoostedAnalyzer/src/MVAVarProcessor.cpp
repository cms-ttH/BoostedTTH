#include "BoostedTTH/BoostedAnalyzer/interface/MVAVarProcessor.hpp"

using namespace std;

MVAVarProcessor::MVAVarProcessor(){}
MVAVarProcessor::~MVAVarProcessor(){}


void MVAVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
 
  vars.InitVar("Evt_ID","I");

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
  
  vars.InitVars( "Jet_E","N_Jets" );
  vars.InitVars( "Jet_M","N_Jets" );
  vars.InitVars( "Jet_Pt","N_Jets" );
  vars.InitVars( "Jet_Phi","N_Jets" );
  vars.InitVars( "Jet_Eta","N_Jets" );
  vars.InitVars( "Jet_CSV","N_Jets" );
  vars.InitVars( "Jet_Flav","N_Jets" );
  vars.InitVars( "Jet_Charge","N_Jets" );
  
  vars.InitVars( "TaggedJet_E","N_BTagsM" );
  vars.InitVars( "TaggedJet_M","N_BTagsM" );
  vars.InitVars( "TaggedJet_Pt","N_BTagsM" );
  vars.InitVars( "TaggedJet_Phi","N_BTagsM" );
  vars.InitVars( "TaggedJet_Eta","N_BTagsM" );
  
  vars.InitVar( "Evt_E_PrimaryLepton" );
  vars.InitVar( "Evt_M_PrimaryLepton" );
  vars.InitVar( "Evt_Pt_PrimaryLepton" );
  vars.InitVar( "Evt_Eta_PrimaryLepton" );
  vars.InitVar( "Evt_Phi_PrimaryLepton" );
  
  vars.InitVars( "LooseLepton_E","N_LooseLeptons" );
  vars.InitVars( "LooseLepton_M","N_LooseLeptons" );
  vars.InitVars( "LooseLepton_Pt","N_LooseLeptons" );
  vars.InitVars( "LooseLepton_Eta","N_LooseLeptons" );
  vars.InitVars( "LooseLepton_Phi","N_LooseLeptons" );
  
  vars.InitVars( "Muon_E","N_LooseMuons" );
  vars.InitVars( "Muon_M","N_LooseMuons" );
  vars.InitVars( "Muon_Pt","N_LooseMuons" );
  vars.InitVars( "Muon_Eta","N_LooseMuons" );
  vars.InitVars( "Muon_Phi","N_LooseMuons" );
  
  vars.InitVars( "Electron_E","N_LooseElectrons" );
  vars.InitVars( "Electron_M","N_LooseElectrons" );
  vars.InitVars( "Electron_Pt","N_LooseElectrons" );
  vars.InitVars( "Electron_Eta","N_LooseElectrons" );
  vars.InitVars( "Electron_Phi","N_LooseElectrons" );
  
  vars.InitVar( "Evt_Pt_MET" );
  vars.InitVar( "Evt_Phi_MET" );

  vars.InitVar("Evt_M3");
  vars.InitVar("Evt_M3_OneJetTagged");
  vars.InitVar("Evt_MTW");
  vars.InitVar("Evt_HT");
  vars.InitVar("Evt_HT_Jets");
  vars.InitVar("Evt_M_Total");
  vars.InitVar("Evt_MHT");
  
  vars.InitVars( "CSV","N_Jets" );
  vars.InitVar( "Evt_CSV_Average" );
  vars.InitVar( "Evt_CSV_Min" );
  vars.InitVar( "Evt_CSV_Dev" );
  vars.InitVar( "Evt_CSV_Average_Tagged" );
  vars.InitVar( "Evt_CSV_Min_Tagged" );
  vars.InitVar( "Evt_CSV_Dev_Tagged" );

  vars.InitVar( "Evt_M_MinDeltaRJets" );
  vars.InitVar( "Evt_M_MinDeltaRTaggedJets" );
  vars.InitVar( "Evt_M_MinDeltaRUntaggedJets" );
  vars.InitVar( "Evt_M_MinDeltaRLeptonTaggedJet" );
  vars.InitVar( "Evt_M_MinDeltaRLeptonJet" );

  vars.InitVar( "Evt_Dr_MinDeltaRJets" );
  vars.InitVar( "Evt_Dr_MinDeltaRTaggedJets" );
  vars.InitVar( "Evt_Dr_MinDeltaRUntaggedJets" );
  vars.InitVar( "Evt_Dr_MinDeltaRLeptonTaggedJet" );
  vars.InitVar( "Evt_Dr_MinDeltaRLeptonJet" );

  vars.InitVar( "Evt_Pt_MinDeltaRJets" );
  vars.InitVar( "Evt_Pt_MinDeltaRTaggedJets" );
  vars.InitVar( "Evt_Pt_MinDeltaRUntaggedJets" );

  vars.InitVar( "Evt_M_JetsAverage" );
  vars.InitVar( "Evt_M_TaggedJetsAverage" );
  vars.InitVar( "Evt_M_UntaggedJetsAverage" );
  
  vars.InitVar( "Evt_Eta_JetsAverage" );
  vars.InitVar( "Evt_Eta_TaggedJetsAverage" );
  vars.InitVar( "Evt_Eta_UntaggedJetsAverage" );
  
  vars.InitVar( "Evt_M2_JetsAverage" );
  vars.InitVar( "Evt_M2_TaggedJetsAverage" );
  vars.InitVar( "Evt_M2_UntaggedJetsAverage" );
  vars.InitVar( "Evt_M2_2JetsAverage" );
  vars.InitVar( "Evt_M2_3JetsAverage" );
  vars.InitVar( "Evt_M2_4JetsAverage" );
  vars.InitVar( "Evt_M2_5JetsAverage" );
  vars.InitVar( "Evt_M2_6JetsAverage" );
  vars.InitVar( "Evt_M2_2TaggedJetsAverage" );
  vars.InitVar( "Evt_M2_3TaggedJetsAverage" );
  vars.InitVar( "Evt_M2_4TaggedJetsAverage" );
  
  vars.InitVar( "Evt_Deta_JetsAverage" );
  vars.InitVar( "Evt_Deta_TaggedJetsAverage" );
  vars.InitVar( "Evt_Deta_UntaggedJetsAverage" );
  vars.InitVar( "Evt_Deta_2JetsAverage" );
  vars.InitVar( "Evt_Deta_3JetsAverage" );
  vars.InitVar( "Evt_Deta_4JetsAverage" );
  vars.InitVar( "Evt_Deta_5JetsAverage" );
  vars.InitVar( "Evt_Deta_6JetsAverage" );
  vars.InitVar( "Evt_Deta_2TaggedJetsAverage" );
  vars.InitVar( "Evt_Deta_3TaggedJetsAverage" );
  vars.InitVar( "Evt_Deta_4TaggedJetsAverage" );
  
  vars.InitVar( "Evt_Dr_JetsAverage" );
  vars.InitVar( "Evt_Dr_TaggedJetsAverage" );
  vars.InitVar( "Evt_Dr_UntaggedJetsAverage" );
  vars.InitVar( "Evt_Dr_2JetsAverage" );
  vars.InitVar( "Evt_Dr_3JetsAverage" );
  vars.InitVar( "Evt_Dr_4JetsAverage" );
  vars.InitVar( "Evt_Dr_5JetsAverage" );
  vars.InitVar( "Evt_Dr_6JetsAverage" );
  vars.InitVar( "Evt_Dr_2TaggedJetsAverage" );
  vars.InitVar( "Evt_Dr_3TaggedJetsAverage" );
  vars.InitVar( "Evt_Dr_4TaggedJetsAverage" );
  
  vars.InitVar( "Evt_Dkt_JetsAverage" );
  vars.InitVar( "Evt_Dkt_TaggedJetsAverage" );
  vars.InitVar( "Evt_Dkt_UntaggedJetsAverage" );
  vars.InitVar( "Evt_Dkt_2JetsAverage" );
  vars.InitVar( "Evt_Dkt_3JetsAverage" );
  vars.InitVar( "Evt_Dkt_4JetsAverage" );
  vars.InitVar( "Evt_Dkt_5JetsAverage" );
  vars.InitVar( "Evt_Dkt_6JetsAverage" );
  vars.InitVar( "Evt_Dkt_2TaggedJetsAverage" );
  vars.InitVar( "Evt_Dkt_3TaggedJetsAverage" );
  vars.InitVar( "Evt_Dkt_4TaggedJetsAverage" );
  
  vars.InitVar( "Evt_M_TaggedJetsClosestTo125" );
  
  vars.InitVar( "Evt_JetPtOverJetE" );
  
  vars.InitVar( "Evt_Jet_MaxDeta_Jets" );
  vars.InitVar( "Evt_TaggedJet_MaxDeta_Jets" );
  vars.InitVar( "Evt_TaggedJet_MaxDeta_TaggedJets" );

  vars.InitVar( "Evt_M_MedianTaggedJets" );
  
  vars.InitVar( "Evt_Jet_Drmax_Lepton" );
  vars.InitVar( "Evt_Jet_Detamax_Lepton" );
  
  vars.InitVars( "Jet_CosTheta_cm","N_Jets" );
  vars.InitVar( "Evt_Jet_CosThetamax_cm" );

  vars.InitVar( "Evt_Jet_Drmax_Jet1" );
    
  vars.InitVar( "Evt_Jet_Detamax_Jet1" );

  vars.InitVars("Jet_CosThetaStar_Lepton","N_Jets");
  vars.InitVars("Jet_CosThetaStar_Jet1","N_Jets");
  vars.InitVars("Jet_CosThetaStar_Jet2","N_Jets");
  vars.InitVars("Jet_CosThetaStar_Jet3","N_Jets");
  vars.InitVars("Jet_CosThetaStar_Jet4","N_Jets");

  vars.InitVars("Jet_Dr_Lepton","N_Jets");
  vars.InitVars("Jet_Dr_Jet1","N_Jets");
  vars.InitVars("Jet_Dr_Jet2","N_Jets");
  vars.InitVars("Jet_Dr_Jet3","N_Jets");
  vars.InitVars("Jet_Dr_Jet4","N_Jets");

  vars.InitVars("Jet_Dkt_Lepton","N_Jets");
  vars.InitVars("Jet_Dkt_Jet1","N_Jets");
  vars.InitVars("Jet_Dkt_Jet2","N_Jets");
  vars.InitVars("Jet_Dkt_Jet3","N_Jets");
  vars.InitVars("Jet_Dkt_Jet4","N_Jets");

  vars.InitVars("Jet_Deta_Lepton","N_Jets");
  vars.InitVars("Jet_Deta_Jet1","N_Jets");
  vars.InitVars("Jet_Deta_Jet2","N_Jets");
  vars.InitVars("Jet_Deta_Jet3","N_Jets");
  vars.InitVars("Jet_Deta_Jet4","N_Jets");

  vars.InitVar( "Evt_Aplanarity" );
  vars.InitVar( "Evt_Sphericity" );
    
  vars.InitVar( "Evt_H0" );
  vars.InitVar( "Evt_H1" );
  vars.InitVar( "Evt_H2" );
  vars.InitVar( "Evt_H3" );
  vars.InitVar( "Evt_H4" );

  
  vars.InitVar("Evt_Deta_TopLep_BB_Ohio");
  vars.InitVar("Evt_Deta_TopHad_BB_Ohio");
  vars.InitVar("Evt_Best_Higgs_Mass_Ohio");
  vars.InitVar("Evt_Deta_Fn_Ohio");
  vars.InitVar("Evt_Dr_BB_Ohio");

  initialized=true;
}

void MVAVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  //also write the event ID for splitting purposes
  long evt_id = input.eventInfo.evt;
  vars.FillVar("Evt_ID",evt_id);

  const char* btagger="pfCombinedInclusiveSecondaryVertexV2BJetTags";
  std::vector<pat::Jet> selectedTaggedJets;
  std::vector<pat::Jet> selectedTaggedJetsT;
  std::vector<pat::Jet> selectedTaggedJetsL;
  std::vector<pat::Jet> selectedUntaggedJets;
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet){
    if(BoostedUtils::PassesCSV(*itJet, 'M', btagger)){
      selectedTaggedJets.push_back(*itJet);
    }
    else{
      selectedUntaggedJets.push_back(*itJet);
    }
    if(BoostedUtils::PassesCSV(*itJet, 'L', btagger)){
      selectedTaggedJetsL.push_back(*itJet);
    }
    if(BoostedUtils::PassesCSV(*itJet, 'T', btagger)){
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
    vars.FillVars( "Jet_E",iJet,itJet->energy() );
    vars.FillVars( "Jet_M",iJet,itJet->mass() );
    vars.FillVars( "Jet_Pt",iJet,itJet->pt() );
    vars.FillVars( "Jet_Eta",iJet,itJet->eta() );
    vars.FillVars( "Jet_Phi",iJet,itJet->phi() );
    vars.FillVars( "Jet_CSV",iJet,fmax(itJet->bDiscriminator(btagger),-.1) );
    vars.FillVars( "Jet_Flav",iJet,itJet->partonFlavour() );
    vars.FillVars( "Jet_Charge",iJet,itJet->jetCharge() );
  }
  
  // Tagged Jets
  for(std::vector<pat::Jet>::iterator itTaggedJet = selectedTaggedJets.begin() ; itTaggedJet != selectedTaggedJets.end(); ++itTaggedJet){
    int iTaggedJet = itTaggedJet - selectedTaggedJets.begin();
    vars.FillVars( "TaggedJet_E",iTaggedJet,itTaggedJet->energy() );
    vars.FillVars( "TaggedJet_M",iTaggedJet,itTaggedJet->mass() );
    vars.FillVars( "TaggedJet_Pt",iTaggedJet,itTaggedJet->pt() );
    vars.FillVars( "TaggedJet_Eta",iTaggedJet,itTaggedJet->eta() );
    vars.FillVars( "TaggedJet_Phi",iTaggedJet,itTaggedJet->phi() );
  }
  
  // Fill Lepton Variables
  std::vector<math::XYZTLorentzVector> looseLeptonVecs = BoostedUtils::GetLepVecs(input.selectedElectronsLoose,input.selectedMuonsLoose);
  for(std::vector<math::XYZTLorentzVector>::iterator itLep = looseLeptonVecs.begin() ; itLep != looseLeptonVecs.end(); ++itLep){
    int iLep = itLep - looseLeptonVecs.begin();
    vars.FillVars( "LooseLepton_E",iLep,itLep->E() );
    vars.FillVars( "LooseLepton_M",iLep,itLep->M() );
    vars.FillVars( "LooseLepton_Pt",iLep,itLep->Pt() );
    vars.FillVars( "LooseLepton_Eta",iLep,itLep->Eta());
    vars.FillVars( "LooseLepton_Phi",iLep,itLep->Phi() );
  }
  
  math::XYZTLorentzVector primLepVec = math::XYZTLorentzVector();
  if(input.selectedElectrons.size()>0 || input.selectedMuons.size()>0){
    primLepVec = BoostedUtils::GetPrimLepVec(input.selectedElectrons,input.selectedMuons);
    vars.FillVar( "Evt_E_PrimaryLepton",primLepVec.E());
    vars.FillVar( "Evt_M_PrimaryLepton",primLepVec.M());
    vars.FillVar( "Evt_Pt_PrimaryLepton",primLepVec.Pt() );
    vars.FillVar( "Evt_Eta_PrimaryLepton",primLepVec.Eta());
    vars.FillVar( "Evt_Phi_PrimaryLepton",primLepVec.Phi());
  }
  
  for(std::vector<pat::Electron>::const_iterator itEle = input.selectedElectronsLoose.begin(); itEle != input.selectedElectronsLoose.end(); ++itEle){
    int iEle = itEle - input.selectedElectronsLoose.begin();
    vars.FillVars( "Electron_E",iEle,itEle->energy() );
    vars.FillVars( "Electron_M",iEle,itEle->mass() );
    vars.FillVars( "Electron_Pt",iEle,itEle->pt() );
    vars.FillVars( "Electron_Eta",iEle,itEle->eta() );
    vars.FillVars( "Electron_Phi",iEle,itEle->phi() ); 
  }
  for(std::vector<pat::Muon>::const_iterator itMu = input.selectedMuonsLoose.begin(); itMu != input.selectedMuonsLoose.end(); ++itMu){
    int iMu = itMu - input.selectedMuonsLoose.begin();
    vars.FillVars( "Muon_E",iMu,itMu->energy() );
    vars.FillVars( "Muon_M",iMu,itMu->mass() );
    vars.FillVars( "Muon_Pt",iMu,itMu->pt() );
    vars.FillVars( "Muon_Eta",iMu,itMu->eta() );
    vars.FillVars( "Muon_Phi",iMu,itMu->phi() );
  }
  
  vars.FillVar( "Evt_Pt_MET",input.pfMET.pt() );
  vars.FillVar( "Evt_Phi_MET",input.pfMET.phi() );
  
  std::vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);
  math::XYZTLorentzVector metvec = input.pfMET.p4();
  
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
  vars.FillVar("Evt_M3",m3);
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
  vars.FillVar("Evt_M3_OneJetTagged",m3tagged);
  
  // Fill MTW
  float mtw = -1.;
  if(input.selectedElectrons.size()>0 || input.selectedMuons.size()>0){
    mtw = sqrt(2*(primLepVec.Pt()*input.pfMET.pt() - primLepVec.Px()*input.pfMET.px() - primLepVec.Py()*input.pfMET.py()));
  }
  vars.FillVar("Evt_MTW",mtw);
  
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
  ht += input.pfMET.pt();
  
  vars.FillVar("Evt_HT",ht);
  vars.FillVar("Evt_MHT",sqrt( mht_px*mht_px + mht_py*mht_py ));
  vars.FillVar("Evt_HT_Jets",htjets);
  
  // Fill Event Mass
  math::XYZTLorentzVector p4all;
  for(std::vector<math::XYZTLorentzVector>::iterator itJetVec = jetvecs.begin() ; itJetVec != jetvecs.end(); ++itJetVec){
    p4all += *itJetVec;
  }
  for(std::vector<math::XYZTLorentzVector>::iterator itLep = looseLeptonVecs.begin() ; itLep != looseLeptonVecs.end(); ++itLep){
    p4all += *itLep;
  }
  p4all += metvec;
  vars.FillVar("Evt_M_Total",p4all.M());
  
  // Fill Number of b Tags
  vars.FillVar( "N_BTagsM",selectedTaggedJets.size() );
  vars.FillVar( "N_BTagsL",selectedTaggedJetsL.size() );
  vars.FillVar( "N_BTagsT",selectedTaggedJetsT.size() );
  
  // Fill CSV Variables
  // All Jets
  std::vector<double> csvJets;
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
    csvJets.push_back(fmax(itJet->bDiscriminator(btagger),-.1));
  }
  std::vector<double> csvJetsSorted=csvJets;
  std::sort(csvJetsSorted.begin(),csvJetsSorted.end(),std::greater<double>());
  vars.FillVar("Evt_CSV_Min",csvJetsSorted.size()>0 ? csvJetsSorted.back() : -.1);
  
  float averageCSV = 0;
  for(std::vector<double>::iterator itCSV = csvJetsSorted.begin() ; itCSV != csvJetsSorted.end(); ++itCSV){
    int iCSV = itCSV - csvJetsSorted.begin();
    vars.FillVars("CSV" ,iCSV,*itCSV);
    averageCSV += fmax(*itCSV,0);
  }
  averageCSV /= csvJetsSorted.size();
  vars.FillVar("Evt_CSV_Average" ,averageCSV );
  
  float csvDev = 0;
  for(std::vector<double>::iterator itCSV = csvJetsSorted.begin() ; itCSV != csvJetsSorted.end(); ++itCSV){
    csvDev += fabs(pow(*itCSV - averageCSV,2));
  }
  if(csvJetsSorted.size() > 0)
    csvDev /= csvJetsSorted.size();
  else
    csvDev=-1.;
  vars.FillVar("Evt_CSV_Dev",csvDev);
  
  // Tagged Jets
  vector<float> csvTaggedJets;
  for(std::vector<pat::Jet>::iterator itTaggedJet = selectedTaggedJets.begin() ; itTaggedJet != selectedTaggedJets.end(); ++itTaggedJet){
    csvTaggedJets.push_back(fmax(itTaggedJet->bDiscriminator( btagger),-.1));
  }
  sort(csvTaggedJets.begin(),csvTaggedJets.end(),std::greater<float>());
  vars.FillVar("Evt_CSV_Min_Tagged",csvTaggedJets.size()>0 ? csvTaggedJets.back() : -.1);
  
  float averageCSVTagged = 0;
  for(std::vector<float>::iterator itCSVTagged = csvTaggedJets.begin() ; itCSVTagged != csvTaggedJets.end(); ++itCSVTagged){
    averageCSVTagged += fmax(*itCSVTagged,0);
  }
  averageCSVTagged /= csvTaggedJets.size();
  vars.FillVar("Evt_CSV_Average_Tagged",averageCSVTagged);
  
  float csvDevTagged = 0;
  for(std::vector<float>::iterator itCSVTagged = csvTaggedJets.begin() ; itCSVTagged != csvTaggedJets.end(); ++itCSVTagged){
    csvDevTagged += fabs(pow(*itCSVTagged - averageCSVTagged,2));
  }
  if(csvTaggedJets.size() > 0)
    csvDevTagged /= csvTaggedJets.size();
  else
    csvDevTagged=-1.;
    
  vars.FillVar("Evt_CSV_Dev_Tagged",csvDevTagged);
  // Fill Variables for closest ak5 Jets
  // All Jets
  if(input.selectedJets.size()>1){
    int idClosestJet1 = -1;
    int idClosestJet2 = -1;
    float minDrJets = BoostedUtils::GetClosestJetIDs(idClosestJet1,idClosestJet2,input.selectedJets);
    math::XYZTLorentzVector closestJetVec1 = input.selectedJets[idClosestJet1].p4();
    math::XYZTLorentzVector closestJetVec2 = input.selectedJets[idClosestJet1].p4();
    vars.FillVar("Evt_M_MinDeltaRJets",(closestJetVec1+closestJetVec2).M());
    vars.FillVar("Evt_Dr_MinDeltaRJets",minDrJets);
    vars.FillVar("Evt_Pt_MinDeltaRJets",(closestJetVec1+closestJetVec2).Pt());
  }
  // Tagged Jets
  if(selectedTaggedJets.size()>1){
    int idClosestTaggedJet1 = -1;
    int idClosestTaggedJet2 = -1;
    float minDrTaggedJets = BoostedUtils::GetClosestJetIDs(idClosestTaggedJet1,idClosestTaggedJet2,selectedTaggedJets);
    math::XYZTLorentzVector closestTaggedJetVec1 = selectedTaggedJets[idClosestTaggedJet1].p4();
    math::XYZTLorentzVector closestTaggedJetVec2 = selectedTaggedJets[idClosestTaggedJet2].p4();
    vars.FillVar("Evt_M_MinDeltaRTaggedJets",(closestTaggedJetVec1+closestTaggedJetVec2).M());
    vars.FillVar("Evt_Dr_MinDeltaRTaggedJets",minDrTaggedJets);
    vars.FillVar("Evt_Pt_MinDeltaRTaggedJets",(closestTaggedJetVec1+closestTaggedJetVec2).Pt());
  }
  // Untagged Jets
  if(selectedUntaggedJets.size()>1){
    int idClosestUntaggedJet1 = -1;
    int idClosestUntaggedJet2 = -1;
    float minDrUntaggedJets = BoostedUtils::GetClosestJetIDs(idClosestUntaggedJet1,idClosestUntaggedJet2,selectedUntaggedJets);
    math::XYZTLorentzVector closestUntaggedJetVec1 = selectedUntaggedJets[idClosestUntaggedJet1].p4();
    math::XYZTLorentzVector closestUntaggedJetVec2 = selectedUntaggedJets[idClosestUntaggedJet2].p4();
    vars.FillVar("Evt_M_MinDeltaRUntaggedJets",(closestUntaggedJetVec1+closestUntaggedJetVec2).M());
    vars.FillVar("Evt_Dr_MinDeltaRUntaggedJets",minDrUntaggedJets);
    vars.FillVar("Evt_Pt_MinDeltaRUntaggedJets",(closestUntaggedJetVec1+closestUntaggedJetVec2).Pt());
  }
  // Jet and Lepton
  if(input.selectedJets.size()>1&&(input.selectedElectrons.size()>0||input.selectedMuons.size()>0)){
    int idClosestJet = -1;
    float minDrLepJet = BoostedUtils::GetClosestLepJetID(idClosestJet,primLepVec,input.selectedJets);
    math::XYZTLorentzVector closestJetVec = input.selectedJets[idClosestJet].p4();
    vars.FillVar("Evt_M_MinDeltaRLeptonJet",(primLepVec+closestJetVec).M());
    vars.FillVar("Evt_Dr_MinDeltaRLeptonJet",minDrLepJet);
  }
  
  // Tagged Jet and Lepton
  if(selectedTaggedJets.size()>1&&(input.selectedElectrons.size()>0||input.selectedMuons.size()>0)){
    int idClosestTaggedJet = -1;
    float minDrLepTaggedJet = BoostedUtils::GetClosestLepJetID(idClosestTaggedJet,primLepVec,selectedTaggedJets);
    math::XYZTLorentzVector closestTaggedJetVec = input.selectedJets[idClosestTaggedJet].p4();
    vars.FillVar("Evt_M_MinDeltaRLeptonTaggedJet",(primLepVec+closestTaggedJetVec).M());
    vars.FillVar("Evt_Dr_MinDeltaRLeptonTaggedJet",minDrLepTaggedJet);
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
  vars.FillVar("Evt_M_JetsAverage",mJetsAverage);
  vars.FillVar("Evt_Eta_JetsAverage",etaJetsAverage);
  vars.FillVar("Evt_M2_JetsAverage",m2JetsAverage);
  vars.FillVar("Evt_Deta_JetsAverage",detaJetsAverage);
  vars.FillVar("Evt_Dr_JetsAverage",drJetsAverage);
  vars.FillVar("Evt_Dkt_JetsAverage",dktJetsAverage);
  vars.FillVar("Evt_JetPtOverJetE", ptJetsAverage/eJetsAverage);
  
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
  sort(m2TaggedJets.begin(),m2TaggedJets.end(),std::greater<float>());
  
  vars.FillVar("Evt_M_TaggedJetsAverage",mTaggedJetsAverage);
  vars.FillVar("Evt_Eta_TaggedJetsAverage",etaTaggedJetsAverage);
  vars.FillVar("Evt_M2_TaggedJetsAverage",m2TaggedJetsAverage);
  if(m2TaggedJets.size()>0) vars.FillVar("Evt_M_MedianTaggedJets",m2TaggedJets.at(m2TaggedJets.size()/2));
  vars.FillVar("Evt_M_TaggedJetsClosestTo125",m2TaggedJetsClosestTo125);
  vars.FillVar("Evt_Deta_TaggedJetsAverage",detaTaggedJetsAverage);
  vars.FillVar("Evt_Dr_TaggedJetsAverage",drTaggedJetsAverage);
  vars.FillVar("Evt_Dkt_TaggedJetsAverage",dktTaggedJetsAverage);
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
  vars.FillVar( "Evt_M_UntaggedJetsAverage",mUntaggedJetsAverage );
  vars.FillVar( "Evt_Eta_UntaggedJetsAverage",etaUntaggedJetsAverage );
  vars.FillVar( "Evt_M2_UntaggedJetsAverage",m2UntaggedJetsAverage );
  vars.FillVar( "Evt_Deta_UntaggedJetsAverage",detaUntaggedJetsAverage );
  vars.FillVar( "Evt_Dr_UntaggedJetsAverage",drUntaggedJetsAverage );
  vars.FillVar( "Evt_Dkt_UntaggedJetsAverage",dktUntaggedJetsAverage );
  
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
    
    TString mName = "Evt_M2_";
    TString detaName = "Evt_Deta_";
    TString drName = "Evt_Dr_";
    TString dktName = "Evt_Dkt_";
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
    
    TString mName = "Evt_M2_";
    TString detaName = "Evt_Deta_";
    TString drName = "Evt_Dr_";
    TString dktName = "Evt_Dkt_";
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
  vars.FillVar("Evt_Jet_MaxDeta_Jets",BoostedUtils::GetJetAverageJetEtaMax(input.selectedJets,input.selectedJets));
  vars.FillVar("Evt_TaggedJet_MaxDeta_Jets",BoostedUtils::GetJetAverageJetEtaMax(input.selectedJets,selectedTaggedJets));
  vars.FillVar("Evt_TaggedJet_MaxDeta_TaggedJets",BoostedUtils::GetJetAverageJetEtaMax(selectedTaggedJets,selectedTaggedJets));
  
 
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
    
    vars.FillVars("Jet_Deta_Lepton",iJetVec,deta_lj);
    vars.FillVars("Jet_Deta_Jet1",iJetVec,deta_j1j);
    vars.FillVars("Jet_Deta_Jet2",iJetVec,deta_j2j);
    vars.FillVars("Jet_Deta_Jet3",iJetVec,deta_j3j);
    vars.FillVars("Jet_Deta_Jet4",iJetVec,deta_j4j);
    
    vars.FillVars("Jet_Dr_Lepton",iJetVec,dr_lj);
    vars.FillVars("Jet_Dr_Jet1",iJetVec,dr_j1j);
    vars.FillVars("Jet_Dr_Jet2",iJetVec,dr_j2j);
    vars.FillVars("Jet_Dr_Jet3",iJetVec,dr_j3j);
    vars.FillVars("Jet_Dr_Jet4",iJetVec,dr_j4j);
    
    vars.FillVars("Jet_Dkt_Lepton",iJetVec,dkt_lj);
    vars.FillVars("Jet_Dkt_Jet1",iJetVec,dkt_j1j);
    vars.FillVars("Jet_Dkt_Jet2",iJetVec,dkt_j2j);
    vars.FillVars("Jet_Dkt_Jet3",iJetVec,dkt_j3j);
    vars.FillVars("Jet_Dkt_Jet4",iJetVec,dkt_j4j);
    
    vars.FillVars("Jet_CosThetaStar_Lepton",iJetVec,c_lj);
    vars.FillVars("Jet_CosThetaStar_Jet1",iJetVec,c_j1j);
    vars.FillVars("Jet_CosThetaStar_Jet2",iJetVec,c_j2j);
    vars.FillVars("Jet_CosThetaStar_Jet3",iJetVec,c_j3j);
    vars.FillVars("Jet_CosThetaStar_Jet4",iJetVec,c_j4j);
    
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
    vars.FillVars("Jet_CosTheta_cm",iJetVec,costheta_jcm  );
    if(costhetamax_jcm<fabs(costheta_jcm)){
      costhetamax_jcm=fabs(costheta_jcm);
    }
  }
  vars.FillVar("Evt_Jet_Drmax_Lepton",drmax_lj);
  vars.FillVar("Evt_Jet_Detamax_Lepton",detamax_lj);
  vars.FillVar("Evt_Jet_Drmax_Jet1",drmax_j1j);
  vars.FillVar("Evt_Jet_Detamax_Jet1",detamax_j1j);
  vars.FillVar("Evt_Jet_CosThetamax_cm",costhetamax_jcm );
  
  // Ohio Variables
  std::vector<pat::Jet> selectedJetsLooseExclusive;
  vector<TLorentzVector> jet_loose_vecsTL;
  vector<double> jetCSV_loose;
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJetsLoose.begin() ; itJet != input.selectedJetsLoose.end(); ++itJet){
    if(itJet->pt() >= 30) continue;
    selectedJetsLooseExclusive.push_back(*itJet);
    jetCSV_loose.push_back(itJet->bDiscriminator(btagger));
    jet_loose_vecsTL.push_back(BoostedUtils::GetTLorentzVector(itJet->p4()));
  }
  vector<TLorentzVector> jetvecsTL=BoostedUtils::GetTLorentzVectors(jetvecs);
  // Event Shape Variables
  // Fox Wolfram Moments
  float h0,h1,h2,h3,h4;
  h0=-9;
  h1=-9;
  h2=-9;
  h3=-9;
  h4=-9;
  bdtvar.getFox(jetvecsTL, h0,h1,h2,h3,h4);
  vars.FillVar( "Evt_H0", h0 );
  vars.FillVar( "Evt_H1", h1 );
  vars.FillVar( "Evt_H2", h2 );
  vars.FillVar( "Evt_H3", h3 );
  vars.FillVar( "Evt_H4", h4 );
  
  // Aplanarity and Sphericity;
  float aplanarity=-1;
  float sphericity=-1;
  TLorentzVector primLepVecTL = BoostedUtils::GetTLorentzVector(primLepVec);
  TLorentzVector metvecTL = BoostedUtils::GetTLorentzVector(primLepVec);
  // workaround to avoid bdtvar crashing
  if(jetvecsTL.size()>0)
    bdtvar.getSp(primLepVecTL, metvecTL, jetvecsTL, aplanarity, sphericity) ;
  vars.FillVar( "Evt_Aplanarity", aplanarity );
  vars.FillVar( "Evt_Sphericity", sphericity );
  double minChi,dRbb;
  TLorentzVector bjet1,bjet2;
  float best_higgs_mass = bdtvar.getBestHiggsMass(primLepVecTL,metvecTL,jetvecsTL,csvJets,minChi,dRbb,bjet1,bjet2, jet_loose_vecsTL,jetCSV_loose);
  TLorentzVector dummy_metv;
  double minChiStudy, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, dRbbStudy, testquant1, testquant2, testquant3, testquant4, testquant5, testquant6, testquant7; 
  TLorentzVector b1,b2;
  vector< vector<double> > jets_vvdouble;
  for(auto jet=input.selectedJets.begin();jet!=input.selectedJets.end(); jet++){
    vector<double> pxpypzE;
    pxpypzE.push_back(jet->px());
    pxpypzE.push_back(jet->py());
    pxpypzE.push_back(jet->pz());
    pxpypzE.push_back(jet->energy());
    jets_vvdouble.push_back(pxpypzE);
  }
  bdtvar.study_tops_bb_syst (input.pfMET.pt(), input.pfMET.phi(), dummy_metv, primLepVecTL, jets_vvdouble, csvJets, minChiStudy, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, dRbbStudy, testquant1, testquant2, testquant3, testquant4, testquant5, testquant6, testquant7, b1, b2);
  float dEta_fn=testquant6;

  vars.FillVar("Evt_Best_Higgs_Mass_Ohio",best_higgs_mass);
  vars.FillVar("Evt_Deta_Fn_Ohio",dEta_fn);

  float abs_dEta_hadtop_bb=fabs(testquant2);
  float abs_dEta_leptop_bb=fabs(testquant2);


  vars.FillVar("Evt_Deta_TopLep_BB_Ohio",abs_dEta_leptop_bb);
  vars.FillVar("Evt_Deta_TopHad_BB_Ohio",abs_dEta_hadtop_bb);
  vars.FillVar("Evt_Dr_BB_Ohio",dRbbStudy);

}
