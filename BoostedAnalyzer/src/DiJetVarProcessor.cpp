#include <vector>

#include "FWCore/Utilities/interface/Exception.h"

#include "BoostedTTH/BoostedAnalyzer/interface/DiJetVarProcessor.hpp"


void DiJetVarProcessor::Init(const InputCollections& input, VariableContainer& vars) {
 
  vars.InitVar("Evt_ID","I"); // Possible conflict because of same-name variables in BasicVarProcessor

  vars.InitVar( "N_PrimaryVertices","I" );

  vars.InitVar( "N_LooseJets","I" );
  vars.InitVars( "LooseJet_E","N_LooseJets" );
  vars.InitVars( "LooseJet_M","N_LooseJets" );
  vars.InitVars( "LooseJet_Pt","N_LooseJets" );
  vars.InitVars( "LooseJet_Phi","N_LooseJets" );
  vars.InitVars( "LooseJet_Eta","N_LooseJets" );
  vars.InitVars( "LooseJet_CSV","N_LooseJets" );
  vars.InitVars( "LooseJet_Flav","N_LooseJets" );
  vars.InitVars( "LooseJet_Charge","N_LooseJets" );
  vars.InitVars( "LooseJet_PileUpID","N_LooseJets" );
  vars.InitVars( "LooseJet_GenJet_Pt","N_LooseJets" );
  vars.InitVars( "LooseJet_GenJet_Eta","N_LooseJets" );
  vars.InitVars( "LooseJet_GenJet_Phi","N_LooseJets" );

  bTagger_ = "pfCombinedInclusiveSecondaryVertexV2BJetTags";
  puJetIDDiscr_ = "pileupJetId:fullDiscriminant";

  initialized=true;
}


void DiJetVarProcessor::Process(const InputCollections& input, VariableContainer& vars) {
  if( !initialized ) throw cms::Exception("BadProcessor") << "DiJetVarProcessor not initialized";

  // event variables
  vars.FillIntVar( "Evt_ID", input.eventInfo.evt );
  vars.FillVar( "N_PrimaryVertices",input.selectedPVs.size());  

  // jet variables
  // use "selectedJetsLoose" --> pt>20 GeV  
  const std::vector<pat::Jet>& jets = input.selectedJetsLoose;
  vars.FillVar( "N_LooseJets", jets.size());
  for( std::vector<pat::Jet>::const_iterator itJet = jets.begin(); itJet != jets.end(); ++itJet) {
    const size_t iJet = itJet - jets.begin();
    vars.FillVars( "LooseJet_E",iJet,itJet->energy() );
    vars.FillVars( "LooseJet_M",iJet,itJet->mass() );
    vars.FillVars( "LooseJet_Pt",iJet,itJet->pt() );
    vars.FillVars( "LooseJet_Eta",iJet,itJet->eta() );
    vars.FillVars( "LooseJet_Phi",iJet,itJet->phi() );
    vars.FillVars( "LooseJet_CSV",iJet,BoostedUtils::GetJetCSV(*itJet,bTagger_) );
    vars.FillVars( "LooseJet_Flav",iJet,itJet->partonFlavour() );
    vars.FillVars( "LooseJet_Charge",iJet,itJet->jetCharge() );
    vars.FillVars( "LooseJet_PileUpID",iJet,itJet->userFloat(puJetIDDiscr_));
    if( itJet->genJet() != 0 ) {
      vars.FillVars( "LooseJet_GenJet_Pt",iJet,itJet->genJet()->pt());
      vars.FillVars( "LooseJet_GenJet_Eta",iJet,itJet->genJet()->eta());
      vars.FillVars( "LooseJet_GenJet_Phi",iJet,itJet->genJet()->phi());
    } else {
      vars.FillVars( "LooseJet_GenJet_Pt",iJet,-9.0);
      vars.FillVars( "LooseJet_GenJet_Eta",iJet,-9.0);
      vars.FillVars( "LooseJet_GenJet_Phi",iJet,-9.0);
    }
  }
}
