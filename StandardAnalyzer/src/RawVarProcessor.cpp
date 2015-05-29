#include "BoostedTTH/StandardAnalyzer/interface/RawVarProcessor.hpp"

using namespace std;

RawVarProcessor::RawVarProcessor(){}
RawVarProcessor::~RawVarProcessor(){}


void RawVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
 
  vars.InitVar( "N_RawJets","I" );
  vars.InitVar( "N_RawLeptons","I" );
  vars.InitVar( "N_RawElectrons","I" );
  vars.InitVar( "N_RawMuons","I" );
  
  vars.InitVars( "RawJet_E","N_RawJets" );
  vars.InitVars( "RawJet_M","N_RawJets" );
  vars.InitVars( "RawJet_Pt","N_RawJets" );
  vars.InitVars( "RawJet_Phi","N_RawJets" );
  vars.InitVars( "RawJet_Eta","N_RawJets" );
  vars.InitVars( "RawJet_CSV","N_RawJets" );
  vars.InitVars( "RawJet_Flav","N_RawJets" );
  vars.InitVars( "RawJet_Charge","N_RawJets" );
  
  vars.InitVars( "RawLepton_E","N_RawLeptons" );
  vars.InitVars( "RawLepton_M","N_RawLeptons" );
  vars.InitVars( "RawLepton_Pt","N_RawLeptons" );
  vars.InitVars( "RawLepton_Eta","N_RawLeptons" );
  vars.InitVars( "RawLepton_Phi","N_RawLeptons" );
//   vars.InitVars( "RawLepton_Iso","N_RawLeptons" );
  
  vars.InitVars( "RawMuon_E","N_RawMuons" );
  vars.InitVars( "RawMuon_M","N_RawMuons" );
  vars.InitVars( "RawMuon_Pt","N_RawMuons" );
  vars.InitVars( "RawMuon_Eta","N_RawMuons" );
  vars.InitVars( "RawMuon_Phi","N_RawMuons" );
  vars.InitVars( "RawMuon_Iso","N_RawMuons" );
  
  vars.InitVars( "RawElectron_E","N_RawElectrons" );
  vars.InitVars( "RawElectron_M","N_RawElectrons" );
  vars.InitVars( "RawElectron_Pt","N_RawElectrons" );
  vars.InitVars( "RawElectron_Eta","N_RawElectrons" );
  vars.InitVars( "RawElectron_Phi","N_RawElectrons" );
  vars.InitVars( "RawElectron_Iso","N_RawElectrons" );

  initialized=true;
}

void RawVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  const char* btagger="pfCombinedInclusiveSecondaryVertexV2BJetTags";
  

  // Fill Multiplicity Variables
  vars.FillVar( "N_RawJets",input.rawJets.size());
  vars.FillVar( "N_RawLeptons",input.rawElectrons.size() + input.rawMuons.size());
  vars.FillVar( "N_RawElectrons",input.rawElectrons.size());
  vars.FillVar( "N_RawMuons",input.rawMuons.size());
  
  // Fill Jet Variables
  // Raw Jets
  for(std::vector<pat::Jet>::const_iterator itJet = input.rawJets.begin() ; itJet != input.rawJets.end(); ++itJet){
    int iJet = itJet - input.selectedJets.begin();
    vars.FillVars( "RawJet_E",iJet,itJet->energy() );
    vars.FillVars( "RawJet_M",iJet,itJet->mass() );
    vars.FillVars( "RawJet_Pt",iJet,itJet->pt() );
    vars.FillVars( "RawJet_Eta",iJet,itJet->eta() );
    vars.FillVars( "RawJet_Phi",iJet,itJet->phi() );
    vars.FillVars( "RawJet_CSV",iJet,fmax(itJet->bDiscriminator(btagger),-.1) );
    vars.FillVars( "RawJet_Flav",iJet,itJet->partonFlavour() );
    vars.FillVars( "RawJet_Charge",iJet,itJet->jetCharge() );

  }
  
  // Fill Lepton Variables
  std::vector<math::XYZTLorentzVector> rawLeptonVecs = BoostedUtils::GetLepVecs(input.rawElectrons,input.rawMuons);
  for(std::vector<math::XYZTLorentzVector>::iterator itLep = rawLeptonVecs.begin() ; itLep != rawLeptonVecs.end(); ++itLep){
    int iLep = itLep - rawLeptonVecs.begin();
    vars.FillVars( "RawLepton_E",iLep,itLep->E() );
    vars.FillVars( "RawLepton_M",iLep,itLep->M() );
    vars.FillVars( "RawLepton_Pt",iLep,itLep->Pt() );
    vars.FillVars( "RawLepton_Eta",iLep,itLep->Eta() );
    vars.FillVars( "RawLepton_Phi",iLep,itLep->Phi() );
  }
  
  for(std::vector<pat::Electron>::const_iterator itEle = input.rawElectrons.begin(); itEle != input.rawElectrons.end(); ++itEle){
    int iEle = itEle - input.rawElectrons.begin();
    vars.FillVars( "RawElectron_E",iEle,itEle->energy() );
    vars.FillVars( "RawElectron_M",iEle,itEle->mass() );
    vars.FillVars( "RawElectron_Pt",iEle,itEle->pt() );
    vars.FillVars( "RawElectron_Eta",iEle,itEle->eta() );
    vars.FillVars( "RawElectron_Phi",iEle,itEle->phi() );
    float RawElectron_Iso = StandardUtils::GetElectronRelIso(*itEle);
    vars.FillVars( "RawElectron_Iso",iEle,RawElectron_Iso );
//     vars.FillVars( "RawLepton_Iso",iEle,MiniAODHelper::GetElectronRelIso(*itEle) );
  }

  for(std::vector<pat::Muon>::const_iterator itMu = input.rawMuons.begin(); itMu != input.rawMuons.end(); ++itMu){
    int iMu = itMu - input.rawMuons.begin();
    vars.FillVars( "RawMuon_E",iMu,itMu->energy() );
    vars.FillVars( "RawMuon_M",iMu,itMu->mass() );
    vars.FillVars( "RawMuon_Pt",iMu,itMu->pt() );
    vars.FillVars( "RawMuon_Eta",iMu,itMu->eta() );
    vars.FillVars( "RawMuon_Phi",iMu,itMu->phi() );
    float RawMuon_Iso = StandardUtils::GetMuonRelIso(*itMu);
    vars.FillVars( "RawMuon_Iso",iMu,RawMuon_Iso );
//     vars.FillVars( "RawLepton_Iso",iMu+input.rawElectrons.size(),MiniAODHelper::GetMuonRelIso(*itMu, coneSize::R04, corrType::deltaBeta) );
  }

}
