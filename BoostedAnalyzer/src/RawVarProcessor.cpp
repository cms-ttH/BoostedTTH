#include "BoostedTTH/BoostedAnalyzer/interface/RawVarProcessor.hpp"

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

  vars.InitVars( "RawJet_ChargedEmE","N_RawJets" );
  vars.InitVars( "RawJet_ChargedEmE_Frac","N_RawJets" );
  vars.InitVars( "RawJet_ChargedHadE","N_RawJets" );
  vars.InitVars( "RawJet_ChargedHadE_Frac","N_RawJets" );
  vars.InitVars( "RawJet_ChargedHadMult","N_RawJets" );
  vars.InitVars( "RawJet_ChargedMult","N_RawJets" );

  vars.InitVars( "RawJet_NeutralEmE","N_RawJets" );
  vars.InitVars( "RawJet_NeutralEmE_Frac","N_RawJets" );
  vars.InitVars( "RawJet_NeutralHadE","N_RawJets" );
  vars.InitVars( "RawJet_NeutralHadE_Frac","N_RawJets" );
  vars.InitVars( "RawJet_NeutralHadMult","N_RawJets" );
  vars.InitVars( "RawJet_NeutralMult","N_RawJets" );
  
  vars.InitVars( "RawLepton_E","N_RawLeptons" );
  vars.InitVars( "RawLepton_M","N_RawLeptons" );
  vars.InitVars( "RawLepton_Pt","N_RawLeptons" );
  vars.InitVars( "RawLepton_Eta","N_RawLeptons" );
  vars.InitVars( "RawLepton_Phi","N_RawLeptons" );
  
  vars.InitVars( "RawMuon_E","N_RawMuons" );
  vars.InitVars( "RawMuon_M","N_RawMuons" );
  vars.InitVars( "RawMuon_Pt","N_RawMuons" );
  vars.InitVars( "RawMuon_Eta","N_RawMuons" );
  vars.InitVars( "RawMuon_Phi","N_RawMuons" );
  
  vars.InitVars( "RawElectron_E","N_RawElectrons" );
  vars.InitVars( "RawElectron_M","N_RawElectrons" );
  vars.InitVars( "RawElectron_Pt","N_RawElectrons" );
  vars.InitVars( "RawElectron_Eta","N_RawElectrons" );
  vars.InitVars( "RawElectron_Phi","N_RawElectrons" );


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
  // Corrected Jets
  for(std::vector<pat::Jet>::const_iterator itJet = input.rawJets.begin() ; itJet != input.rawJets.end(); ++itJet){
    int iJet = itJet - input.rawJets.begin();
    vars.FillVars( "RawJet_E",iJet,itJet->energy() );
    vars.FillVars( "RawJet_M",iJet,itJet->mass() );
    vars.FillVars( "RawJet_Pt",iJet,itJet->pt() );
    vars.FillVars( "RawJet_Eta",iJet,itJet->eta() );
    vars.FillVars( "RawJet_Phi",iJet,itJet->phi() );
    vars.FillVars( "RawJet_CSV",iJet,MiniAODHelper::GetJetCSV(*itJet,btagger) );
    vars.FillVars( "RawJet_Flav",iJet,itJet->partonFlavour() );
    vars.FillVars( "RawJet_Charge",iJet,itJet->jetCharge() );

    vars.FillVars( "RawJet_ChargedEmE",iJet,itJet->chargedEmEnergy() );
    vars.FillVars( "RawJet_ChargedEmE_Frac",iJet,itJet->chargedEmEnergyFraction() );
    vars.FillVars( "RawJet_ChargedHadE",iJet,itJet->chargedHadronEnergy() );
    vars.FillVars( "RawJet_ChargedHadE_Frac",iJet,itJet->chargedHadronEnergyFraction() );
    vars.FillVars( "RawJet_ChargedHadMult",iJet,itJet->chargedHadronMultiplicity() );
    vars.FillVars( "RawJet_ChargedMult",iJet,itJet->chargedMultiplicity() );

    vars.FillVars( "RawJet_NeutralEmE",iJet,itJet->neutralEmEnergy() );
    vars.FillVars( "RawJet_NeutralEmE_Frac",iJet,itJet->neutralEmEnergyFraction() );
    vars.FillVars( "RawJet_NeutralHadE",iJet,itJet->neutralHadronEnergy() );
    vars.FillVars( "RawJet_NeutralHadE_Frac",iJet,itJet->neutralHadronEnergyFraction() );
    vars.FillVars( "RawJet_NeutralHadMult",iJet,itJet->neutralHadronMultiplicity() );
    vars.FillVars( "RawJet_NeutralMult",iJet,itJet->neutralMultiplicity() );
  }

//   for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
//     int iJet = itJet - input.selectedJets.begin();
//     vars.FillVars( "Jet_ChargedEmE",iJet,itJet->chargedEmEnergy() );
//     vars.FillVars( "Jet_ChargedEmE_Frac",iJet,itJet->chargedEmEnergyFraction() );
//     vars.FillVars( "Jet_ChargedHadE",iJet,itJet->chargedHadronEnergy() );
//     vars.FillVars( "Jet_ChargedHadE_Frac",iJet,itJet->chargedHadronEnergyFraction() );
//     vars.FillVars( "Jet_ChargedHadMult",iJet,itJet->chargedHadronMultiplicity() );
//     vars.FillVars( "Jet_ChargedMult",iJet,itJet->chargedMultiplicity() );
// 
//     vars.FillVars( "Jet_NeutralEmE",iJet,itJet->neutralEmEnergy() );
//     vars.FillVars( "Jet_NeutralEmE_Frac",iJet,itJet->neutralEmEnergyFraction() );
//     vars.FillVars( "Jet_NeutralHadE",iJet,itJet->neutralHadronEnergy() );
//     vars.FillVars( "Jet_NeutralHadE_Frac",iJet,itJet->neutralHadronEnergyFraction() );
//     vars.FillVars( "Jet_NeutralHadMult",iJet,itJet->neutralHadronMultiplicity() );
//     vars.FillVars( "Jet_NeutralMult",iJet,itJet->neutralMultiplicity() );
//   }
  
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
  }

  for(std::vector<pat::Muon>::const_iterator itMu = input.rawMuons.begin(); itMu != input.rawMuons.end(); ++itMu){
    int iMu = itMu - input.rawMuons.begin();
    vars.FillVars( "RawMuon_E",iMu,itMu->energy() );
    vars.FillVars( "RawMuon_M",iMu,itMu->mass() );
    vars.FillVars( "RawMuon_Pt",iMu,itMu->pt() );
    vars.FillVars( "RawMuon_Eta",iMu,itMu->eta() );
    vars.FillVars( "RawMuon_Phi",iMu,itMu->phi() );
  }

}
