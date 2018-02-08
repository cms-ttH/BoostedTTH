#include "BoostedTTH/BoostedAnalyzer/interface/monoVselection.hpp"

using namespace std;

monoVselection::monoVselection (const edm::ParameterSet& iConfig): monoVselection(iConfig.getParameter<double>("minpt"), iConfig.getParameter<double>("maxeta"), iConfig.getParameter<double>("minPrunedMass"), iConfig.getParameter<double>("maxPrunedMass"), iConfig.getParameter<double>("maxtau21_chsPrun"), iConfig.getParameter<double>("minSoftDropMass"), iConfig.getParameter<double>("maxSoftDropMass"), iConfig.getParameter<double>("maxtau21_Puppi")) {}
monoVselection::monoVselection (double minpt_, double maxeta_, double minPrunedMass_, double maxPrunedMass_, double maxtau21_chsPrun_, double minSoftDropMass_, double maxSoftDropMass_, double maxtau21_Puppi_): minpt(minpt_), maxeta(maxeta_), minPrunedMass(minPrunedMass_), maxPrunedMass(maxPrunedMass_), maxtau21_chsPrun(maxtau21_chsPrun_), minSoftDropMass(minSoftDropMass_), maxSoftDropMass(maxSoftDropMass_), maxtau21_Puppi(maxtau21_Puppi_) {}
monoVselection::~monoVselection () {}

void monoVselection::InitCutflow(Cutflow& cutflow) {

  cutflow.AddStep("not monoVtagged");

  initialized = true;
}

bool monoVselection::IsSelected(const InputCollections& input, Cutflow& cutflow) {
  if (!initialized) cerr << "monoVselection not initialized" << endl;
  if (input.AK8Jets.size() >= 1) {
    pat::Jet leadingJet = input.AK8Jets.at(0);

    //CHs+Pruning+NSubjettiness Vtag
    float leadingJet_PrunedMass = leadingJet.userFloat("ak8PFJetsCHSPrunedMass");
    float leadingJet_eta = leadingJet.eta();
    float leadingJet_Pt = leadingJet.pt();
    float leadingJet_tau1 = leadingJet.userFloat("NjettinessAK8:tau1");
    float leadingJet_tau2 = leadingJet.userFloat("NjettinessAK8:tau2");

    float leadingJet_tau21 = leadingJet_tau2 / leadingJet_tau1;

    monoVtagged_ChsPrun = false;

    if (leadingJet_Pt > minpt && abs(leadingJet_eta) < maxeta && leadingJet_PrunedMass > minPrunedMass && leadingJet_PrunedMass < maxPrunedMass && leadingJet_tau21 < maxtau21_chsPrun ) {
      monoVtagged_ChsPrun = true;
    }

    if (monoVtagged_ChsPrun ) {
      return false;
    }
    else {
      cutflow.EventSurvivedStep("not monoVtagged", input.weights.at("Weight"));
      return true;
    }


    //Puppi+SoftDrop+NSubjettiness Vtag
    leadingJet_Pt             = leadingJet.userFloat("ak8PFJetsPuppiValueMap:pt");
    leadingJet_eta       = leadingJet.userFloat("ak8PFJetsPuppiValueMap:eta");
    leadingJet_tau1       = leadingJet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau1");
    leadingJet_tau2       = leadingJet.userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau2");

    leadingJet_tau21 = leadingJet_tau2 / leadingJet_tau1;

    TLorentzVector puppi_softdrop, puppi_softdrop_subjet;
    auto const & sdSubjetsPuppi = leadingJet.subjets("SoftDropPuppi");
    for ( auto const & it : sdSubjetsPuppi ) {
      puppi_softdrop_subjet.SetPtEtaPhiM(it->correctedP4(0).pt(), it->correctedP4(0).eta(), it->correctedP4(0).phi(), it->correctedP4(0).mass());
      puppi_softdrop += puppi_softdrop_subjet;
    }

    float leadingJet_softdrop_mass_puppi = puppi_softdrop.M();
    monoVtagged_PuppiSoftDrop = false;

    if (leadingJet_Pt > minpt && abs(leadingJet_eta) < maxeta && leadingJet_softdrop_mass_puppi > minSoftDropMass && leadingJet_softdrop_mass_puppi < maxSoftDropMass && leadingJet_tau21 < maxtau21_Puppi ) {
      monoVtagged_PuppiSoftDrop = true;
    }

    if (monoVtagged_PuppiSoftDrop ) {
      // return false;
    }
  }
  else {
    cutflow.EventSurvivedStep("not monoVtagged", input.weights.at("Weight"));
    return true;
  }


}