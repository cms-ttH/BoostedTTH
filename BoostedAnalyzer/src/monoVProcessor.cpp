#include "BoostedTTH/BoostedAnalyzer/interface/monoVProcessor.hpp"

using namespace std;

monoVProcessor::monoVProcessor() {}
monoVProcessor::~monoVProcessor() {}


void monoVProcessor::Init(const InputCollections& input, VariableContainer& vars) {

  vars.InitVar( "N_Jets_Ak8", "I" );

  vars.InitVars( "Jet_Pt_Ak8", "N_Jets_Ak8" );
  vars.InitVars( "Jet_Eta_Ak8", "N_Jets_Ak8" );

  vars.InitVars( "tau1_Ak8", "N_Jets_Ak8" );
  vars.InitVars( "tau2_Ak8", "N_Jets_Ak8" );
  vars.InitVars( "tau3_Ak8", "N_Jets_Ak8" );

  vars.InitVars( "PrunedMass_Ak8", "N_Jets_Ak8" );

  vars.InitVars( "Jet_Pt_puppi", "N_Jets_Ak8" );
  vars.InitVars( "mass_puppi", "N_Jets_Ak8" );
  vars.InitVars( "tau1_puppi", "N_Jets_Ak8" );
  vars.InitVars( "tau2_puppi", "N_Jets_Ak8" );
  vars.InitVars( "tau3_puppi", "N_Jets_Ak8" );
  vars.InitVars( "Jet_Eta_puppi",  "N_Jets_Ak8" );
  vars.InitVars( "softdrop_mass_puppi",  "N_Jets_Ak8" );
  vars.InitVars( "puppi_softdrop_subjet_Pt",  "N_Jets_Ak8" );

  vars.InitVar( "monoVtagged_ChsPrun", "I" );
  vars.InitVar( "monoVtagged_PuppiSoftDrop", "I" );


  pat::Jet leadingJet;


  initialized = true;
}

void monoVProcessor::Process(const InputCollections& input, VariableContainer& vars) {
  if (!initialized) cerr << "tree processor not initialized" << endl;
  vars.FillVar( "N_Jets_Ak8", input.AK8Jets.size());

  for (std::vector<pat::Jet>::const_iterator itJet = input.AK8Jets.begin() ; itJet != input.AK8Jets.end(); ++itJet) {
    int iJet = itJet - input.AK8Jets.begin();
    // cout << "Filling AK8Jet " << iJet << endl;

    vars.FillVars( "Jet_Pt_Ak8", iJet, itJet->pt());
    vars.FillVars( "PrunedMass_Ak8", iJet, itJet->userFloat("ak8PFJetsCHSPrunedMass"));

    if ( itJet->hasUserFloat("NjettinessAK8:tau1") ) {
      tau1 = itJet->userFloat("NjettinessAK8:tau1");
      vars.FillVars( "tau1_Ak8", iJet, tau1 );
    }
    // else cout << " Ak8Jet doesnt have tau1" << endl;


    if ( itJet->hasUserFloat("NjettinessAK8:tau2") ) {
      tau2 = itJet->userFloat("NjettinessAK8:tau2");
      vars.FillVars( "tau2_Ak8", iJet, tau2 );
    }
    // else cout << " AK8Jet doesnt have tau2" << endl;


    if ( itJet->hasUserFloat("NjettinessAK8:tau3") ) {
      tau3 = itJet->userFloat("NjettinessAK8:tau3");
      vars.FillVars( "tau3_Ak8", iJet, tau3 );
    }
    // else cout << " AK8Jet doesnt have tau3" << endl;

    vars.FillVars( "Jet_Eta_Ak8", iJet, itJet->eta() );


    //Puppi
    double puppi_pt             = itJet->userFloat("ak8PFJetsPuppiValueMap:pt");
    vars.FillVars( "Jet_Pt_puppi", iJet, puppi_pt );

    double puppi_mass       = itJet->userFloat("ak8PFJetsPuppiValueMap:mass");
    vars.FillVars( "mass_puppi", iJet, puppi_mass );

    double puppi_eta       = itJet->userFloat("ak8PFJetsPuppiValueMap:eta");
    vars.FillVars( "Jet_Eta_puppi", iJet, puppi_eta );

    double puppi_tau1       = itJet->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau1");
    vars.FillVars( "tau1_puppi", iJet, puppi_tau1);

    double puppi_tau2       = itJet->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau2");
    vars.FillVars( "tau2_puppi", iJet, puppi_tau2);

    double puppi_tau3       = itJet->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau3");
    vars.FillVars( "tau3_puppi", iJet, puppi_tau3);

    TLorentzVector puppi_softdrop, puppi_softdrop_subjet;
    auto const & sdSubjetsPuppi = itJet->subjets("SoftDropPuppi");
    for ( auto const & it : sdSubjetsPuppi ) {
      puppi_softdrop_subjet.SetPtEtaPhiM(it->correctedP4(0).pt(), it->correctedP4(0).eta(), it->correctedP4(0).phi(), it->correctedP4(0).mass());
      puppi_softdrop += puppi_softdrop_subjet;
      vars.FillVars( "puppi_softdrop_subjet_Pt", iJet, puppi_softdrop_subjet.Pt());

    }
    float softdrop_mass_puppi = puppi_softdrop.M();
    vars.FillVars( "softdrop_mass_puppi", iJet, softdrop_mass_puppi);


  }


  pat::Jet *leadingJet = new pat::Jet;
  leadingJet = input.AK8Jets.at(0).clone();

  //CHs+Pruning+NSubjettiness Vtag
  float leadingJet_PrunedMass = leadingJet->userFloat("ak8PFJetsCHSPrunedMass");
  float leadingJet_eta = leadingJet->eta();
  float leadingJet_Pt = leadingJet->pt();
  float leadingJet_tau1 = leadingJet->userFloat("NjettinessAK8:tau1");
  float leadingJet_tau2 = leadingJet->userFloat("NjettinessAK8:tau2");

  float leadingJet_tau21 = leadingJet_tau2 / leadingJet_tau1;

  monoVtagged_ChsPrun = false;
  if (leadingJet_Pt > 250 && abs(leadingJet_eta) < 2.4 && leadingJet_PrunedMass > 65 && leadingJet_PrunedMass < 105 && leadingJet_tau21 < 0.6 ) {
    monoVtagged_ChsPrun = true;
    // cout << "tagged ChsPrun" << endl;
  }

  vars.FillVar( "monoVtagged_ChsPrun", monoVtagged_ChsPrun);

  //Puppi+SoftDrop+NSubjettiness Vtag
  monoVtagged_PuppiSoftDrop = false;

  leadingJet_Pt             = leadingJet->userFloat("ak8PFJetsPuppiValueMap:pt");
  leadingJet_eta       = leadingJet->userFloat("ak8PFJetsPuppiValueMap:eta");
  leadingJet_tau1       = leadingJet->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau1");
  leadingJet_tau2       = leadingJet->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau2");
  leadingJet_tau21 = leadingJet_tau2 / leadingJet_tau1;

  TLorentzVector puppi_softdrop, puppi_softdrop_subjet;
  auto const & sdSubjetsPuppi = leadingJet->subjets("SoftDropPuppi");
  for ( auto const & it : sdSubjetsPuppi ) {
    puppi_softdrop_subjet.SetPtEtaPhiM(it->correctedP4(0).pt(), it->correctedP4(0).eta(), it->correctedP4(0).phi(), it->correctedP4(0).mass());
    puppi_softdrop += puppi_softdrop_subjet;
  }

  float leadingJet_softdrop_mass_puppi = puppi_softdrop.M();


  if (leadingJet_Pt > 250 && abs(leadingJet_eta) < 2.4 && leadingJet_softdrop_mass_puppi > 65 && leadingJet_softdrop_mass_puppi < 105 && leadingJet_tau21 < 0.4 ) {
    monoVtagged_PuppiSoftDrop = true;
    // cout << "tagged Puppi" << endl;
  }
  vars.FillVar( "monoVtagged_PuppiSoftDrop", monoVtagged_PuppiSoftDrop);

  delete leadingJet;



}
