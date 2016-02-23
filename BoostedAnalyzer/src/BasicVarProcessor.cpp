#include "BoostedTTH/BoostedAnalyzer/interface/BasicVarProcessor.hpp"

using namespace std;

BasicVarProcessor::BasicVarProcessor(){}
BasicVarProcessor::~BasicVarProcessor(){}


void BasicVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
 
  vars.InitVar("Evt_ID","I");
  vars.InitVar("Evt_Odd","I");
  vars.InitVar("Evt_Rho","F");
  vars.InitVar("Evt_Run","I");
  vars.InitVar("Evt_Lumi","I");

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
  vars.InitVars( "Jet_Mt","N_Jets" );
  vars.InitVars( "Jet_Pt","N_Jets" );
  vars.InitVars( "Jet_Phi","N_Jets" );
  vars.InitVars( "Jet_Eta","N_Jets" );
  vars.InitVars( "Jet_CSV","N_Jets" );
  vars.InitVars( "Jet_Flav","N_Jets" );
  vars.InitVars( "Jet_PartonFlav","N_Jets" );
  vars.InitVars( "Jet_Charge","N_Jets" );
  vars.InitVars( "Jet_PileUpID","N_Jets" );
  vars.InitVars( "Jet_vtxMass","N_Jets" );
  vars.InitVars( "Jet_vtx3DVal","N_Jets" );
  vars.InitVars( "Jet_vtxNtracks","N_Jets" );
  vars.InitVars( "Jet_vtx3DSig","N_Jets" );
  vars.InitVars( "Jet_vtxPt","N_Jets" );
  vars.InitVars( "Jet_nHEFrac","N_Jets" );
  vars.InitVars( "Jet_nEmEFrac","N_Jets" );
  vars.InitVars( "Jet_chargedMult","N_Jets" );
  vars.InitVars( "Jet_leadTrackPt","N_Jets" );
  vars.InitVars( "Jet_leptonPtRel","N_Jets" );
  vars.InitVars( "Jet_leptonPt","N_Jets" );
  vars.InitVars( "Jet_leptonDeltaR","N_Jets" );
  vars.InitVars( "Jet_corr","N_Jets" );
  vars.InitVars( "Jet_rawPt","N_Jets" );
  vars.InitVars( "Jet_corr_rawJet","N_Jets" );
  vars.InitVars( "Jet_regPt","N_Jets" );
  vars.InitVars( "Jet_regcorr","N_Jets" );

  vars.InitVars( "Jet_GenJet_Pt","N_Jets" );
  vars.InitVars( "Jet_GenJet_Eta","N_Jets" );

  vars.InitVars( "LooseJet_E","N_LooseJets" );
  vars.InitVars( "LooseJet_M","N_LooseJets" );
  vars.InitVars( "LooseJet_Pt","N_LooseJets" );
  vars.InitVars( "LooseJet_Phi","N_LooseJets" );
  vars.InitVars( "LooseJet_Eta","N_LooseJets" );
  vars.InitVars( "LooseJet_CSV","N_LooseJets" );
  vars.InitVars( "LooseJet_Flav","N_LooseJets" );
  vars.InitVars( "LooseJet_PartonFlav","N_LooseJets" );
  vars.InitVars( "LooseJet_Charge","N_LooseJets" );
  vars.InitVars( "LooseJet_PileUpID","N_LooseJets" );
  vars.InitVars( "LooseJet_GenJet_Pt","N_LooseJets" );
  vars.InitVars( "LooseJet_GenJet_Eta","N_LooseJets" );

  
  vars.InitVars( "TaggedJet_E","N_BTagsM" );
  vars.InitVars( "TaggedJet_M","N_BTagsM" );
  vars.InitVars( "TaggedJet_Pt","N_BTagsM" );
  vars.InitVars( "TaggedJet_Phi","N_BTagsM" );
  vars.InitVars( "TaggedJet_Eta","N_BTagsM" );
  
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
  vars.InitVars( "Muon_RelIso","N_LooseMuons" );
  vars.InitVars( "Muon_Charge","N_LooseMuons" );
  
  vars.InitVars( "Electron_E","N_LooseElectrons" );
  vars.InitVars( "Electron_M","N_LooseElectrons" );
  vars.InitVars( "Electron_Pt","N_LooseElectrons" );
  vars.InitVars( "Electron_Eta","N_LooseElectrons" );
  vars.InitVars( "Electron_Phi","N_LooseElectrons" );
  vars.InitVars( "Electron_RelIso","N_LooseElectrons" );
  vars.InitVars( "Electron_Charge","N_LooseElectrons" );
  
  vars.InitVar( "Evt_Pt_MET" );
  vars.InitVar( "Evt_Phi_MET" );
  vars.InitVar( "Evt_Pt_GenMET" );
  vars.InitVar( "Evt_Phi_GenMET" );

  vars.InitVar("Evt_M3");
  vars.InitVar("Evt_M3_OneJetTagged");
  vars.InitVar("Evt_MTW");
  vars.InitVar("Evt_HT");
  vars.InitVar("Evt_HT_Jets");
  vars.InitVar("Evt_M_Total");
  vars.InitVar("Evt_MHT");
  
  vars.InitVars( "CSV","N_Jets" );

  initialized=true;
}

void BasicVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  //also write the event ID for splitting purposes
  long evt_id = input.eventInfo.evt;
  long run_id = input.eventInfo.run;
  long lumi_section = input.eventInfo.lumiBlock;

  vars.FillIntVar("Evt_ID",evt_id);
  vars.FillIntVar("Evt_Odd",evt_id%2);
  vars.FillFloatVar("Evt_Rho",input.eventInfo.rho);
  vars.FillIntVar("Evt_Run",run_id);
  vars.FillIntVar("Evt_Lumi",lumi_section);


  const char* btagger="pfCombinedInclusiveSecondaryVertexV2BJetTags";
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
    vars.FillVars( "Jet_E",iJet,itJet->energy() );
    vars.FillVars( "Jet_M",iJet,itJet->mass() );
    vars.FillVars( "Jet_Mt",iJet,itJet->mt() );
    vars.FillVars( "Jet_Pt",iJet,itJet->pt() );
    vars.FillVars( "Jet_Eta",iJet,itJet->eta() );
    vars.FillVars( "Jet_Phi",iJet,itJet->phi() );
    vars.FillVars( "Jet_CSV",iJet,MiniAODHelper::GetJetCSV(*itJet,btagger) );
    vars.FillVars( "Jet_Flav",iJet,itJet->hadronFlavour() );
    vars.FillVars( "Jet_PartonFlav",iJet,itJet->partonFlavour() );
    vars.FillVars( "Jet_Charge",iJet,itJet->jetCharge() );
    vars.FillVars( "Jet_PileUpID",iJet,itJet->userFloat("pileupJetId:fullDiscriminant"));
    vars.FillVars( "Jet_vtxMass",iJet,itJet->userFloat("vtxMass"));
    vars.FillVars( "Jet_vtx3DVal",iJet,itJet->userFloat("vtx3DVal"));
    vars.FillVars( "Jet_vtxNtracks",iJet,itJet->userFloat("vtxNtracks"));
    vars.FillVars( "Jet_vtx3DSig",iJet,itJet->userFloat("vtx3DSig"));
    vars.FillVars( "Jet_vtxPt",iJet,sqrt(itJet->userFloat("vtxPx")*itJet->userFloat("vtxPx") + itJet->userFloat("vtxPy")*itJet->userFloat("vtxPy")));
    vars.FillVars( "Jet_nHEFrac",iJet, itJet->neutralHadronEnergyFraction());
    vars.FillVars( "Jet_nEmEFrac",iJet, itJet->neutralEmEnergyFraction());
    vars.FillVars( "Jet_chargedMult",iJet, itJet->chargedMultiplicity());
    vars.FillVars( "Jet_leadTrackPt",iJet,itJet->userFloat("Jet_leadTrackPt"));
    vars.FillVars( "Jet_leptonPtRel",iJet,itJet->userFloat("Jet_leptonPtRel"));
    vars.FillVars( "Jet_leptonPt",iJet,itJet->userFloat("Jet_leptonPt"));
    vars.FillVars( "Jet_leptonDeltaR",iJet,itJet->userFloat("Jet_leptonDeltaR"));
    vars.FillVars( "Jet_corr",iJet,1/itJet->jecFactor("Uncorrected"));
    vars.FillVars( "Jet_rawPt",iJet,itJet->userFloat("Jet_rawPt"));
    vars.FillVars( "Jet_corr_rawJet",iJet,itJet->pt()/itJet->userFloat("Jet_rawPt"));
    vars.FillVars( "Jet_regPt",iJet,itJet->userFloat("jetregressionPT"));
    vars.FillVars( "Jet_regcorr",iJet,itJet->userFloat("jetregressionPT")/itJet->pt());
    if(itJet->genJet()!=NULL){
      vars.FillVars( "Jet_GenJet_Pt",iJet,itJet->genJet()->pt());
      vars.FillVars( "Jet_GenJet_Eta",iJet,itJet->genJet()->eta());
    }
    else {
      vars.FillVars( "Jet_GenJet_Pt",iJet,-9.0);
      vars.FillVars( "Jet_GenJet_Eta",iJet,-9.0);
    }
  }
  // Loose Jets
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJetsLoose.begin() ; itJet != input.selectedJetsLoose.end(); ++itJet){
    int iJet = itJet - input.selectedJetsLoose.begin();
    vars.FillVars( "LooseJet_E",iJet,itJet->energy() );
    vars.FillVars( "LooseJet_M",iJet,itJet->mass() );
    vars.FillVars( "LooseJet_Pt",iJet,itJet->pt() );
    vars.FillVars( "LooseJet_Eta",iJet,itJet->eta() );
    vars.FillVars( "LooseJet_Phi",iJet,itJet->phi() );
    vars.FillVars( "LooseJet_CSV",iJet,MiniAODHelper::GetJetCSV(*itJet,btagger) );
    vars.FillVars( "LooseJet_PartonFlav",iJet,itJet->partonFlavour() );
    vars.FillVars( "LooseJet_Flav",iJet,itJet->hadronFlavour() );
    vars.FillVars( "LooseJet_Charge",iJet,itJet->jetCharge() );
    vars.FillVars( "LooseJet_PileUpID",iJet,itJet->userFloat("pileupJetId:fullDiscriminant"));
    if(itJet->genJet()!=NULL){
      vars.FillVars( "LooseJet_GenJet_Pt",iJet,itJet->genJet()->pt());
      vars.FillVars( "LooseJet_GenJet_Eta",iJet,itJet->genJet()->eta());
    }
    else {
      vars.FillVars( "LooseJet_GenJet_Pt",iJet,-9.0);
      vars.FillVars( "LooseJet_GenJet_Eta",iJet,-9.0);
    }
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
   
  for(std::vector<pat::Electron>::const_iterator itEle = input.selectedElectronsLoose.begin(); itEle != input.selectedElectronsLoose.end(); ++itEle){
    int iEle = itEle - input.selectedElectronsLoose.begin();
    vars.FillVars( "Electron_E",iEle,itEle->energy() );
    vars.FillVars( "Electron_M",iEle,itEle->mass() );
    vars.FillVars( "Electron_Pt",iEle,itEle->pt() );
    vars.FillVars( "Electron_Eta",iEle,itEle->eta() );
    vars.FillVars( "Electron_Phi",iEle,itEle->phi() ); 
    if(itEle->hasUserFloat("relIso")){
	vars.FillVars( "Electron_RelIso",iEle,itEle->userFloat("relIso") );
    }
    vars.FillVars( "Electron_Charge",iEle,itEle->charge() ); 
  }
  for(std::vector<pat::Muon>::const_iterator itMu = input.selectedMuonsLoose.begin(); itMu != input.selectedMuonsLoose.end(); ++itMu){
    int iMu = itMu - input.selectedMuonsLoose.begin();
    vars.FillVars( "Muon_E",iMu,itMu->energy() );
    vars.FillVars( "Muon_M",iMu,itMu->mass() );
    vars.FillVars( "Muon_Pt",iMu,itMu->pt() );
    vars.FillVars( "Muon_Eta",iMu,itMu->eta() );
    vars.FillVars( "Muon_Phi",iMu,itMu->phi() );
    if(itMu->hasUserFloat("relIso")){
	vars.FillVars( "Muon_RelIso",iMu,itMu->userFloat("relIso") );
    }
    vars.FillVars( "Muon_Charge",iMu,itMu->charge() );
  }
  
  vars.FillVar( "Evt_Pt_MET",input.pfMET.pt() );
  vars.FillVar( "Evt_Phi_MET",input.pfMET.phi() );
  if(input.pfMET.genMET()!=0){
      vars.FillVar( "Evt_Pt_GenMET",input.pfMET.genMET()->pt() );
      vars.FillVar( "Evt_Phi_GenMET",input.pfMET.genMET()->phi() );
  }
  
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
  math::XYZTLorentzVector primLepVec = math::XYZTLorentzVector();
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
    csvJets.push_back(MiniAODHelper::GetJetCSV(*itJet,btagger));
  }
  std::vector<double> csvJetsSorted=csvJets;
  std::sort(csvJetsSorted.begin(),csvJetsSorted.end(),std::greater<double>());
  
  for(std::vector<double>::iterator itCSV = csvJetsSorted.begin() ; itCSV != csvJetsSorted.end(); ++itCSV){
    int iCSV = itCSV - csvJetsSorted.begin();
    vars.FillVars("CSV" ,iCSV,*itCSV);
  }

}
