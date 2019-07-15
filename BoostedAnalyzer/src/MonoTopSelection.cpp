#include "BoostedTTH/BoostedAnalyzer/interface/MonoTopSelection.hpp"

using namespace std;

MonoTopSelection::MonoTopSelection(const edm::ParameterSet& iConfig)
    : MonoTopSelection(iConfig.getParameter<double>("AK15Jet_Pt"),
                       iConfig.getParameter<double>("AK15Jet_Eta"),
                       iConfig.getParameter<double>("AK15Jet_Chf"),
                       iConfig.getParameter<double>("AK15Jet_Nhf")) {}
MonoTopSelection::MonoTopSelection(double pt_min_, double eta_max_,
                                   double chf_min_, double nhf_max_)
    : pt_min(pt_min_),
      eta_max(eta_max_),
      charged_hadron_fraction_min(chf_min_),
      neutral_hadron_fraction_max(nhf_max_) {}
MonoTopSelection::~MonoTopSelection() {}

void MonoTopSelection::InitCutflow(Cutflow& cutflow) {
  // create string for cutflow
  pt_str = std::to_string(pt_min);
  eta_str = std::to_string(eta_max);
  cutflow.AddStep("Exactly one AK15 jet with pt greater than " + pt_str +
                  " and eta smaller than " + eta_str);

  initialized = true;
}

bool MonoTopSelection::IsSelected(const InputCollections& input,
                                  Cutflow& cutflow) {
  if (!initialized) cerr << "MonoTopSelection not initialized" << endl;

  // do not use the event if there is not exactly one AK15 jet
  if (input.selectedJetsAK15.size() != 1) return false;

  // AK15 jet has to fulfill pt,eta and several quality criteria
  bool leading_jet_criterium =
      input.selectedJetsAK15.at(0).pt() > pt_min &&
      fabs(input.selectedJetsAK15.at(0).eta()) < eta_max &&
      charged_hadron_fraction_min < input.selectedJetsAK15.at(0).userFloat(
                                        "chargedHadronEnergyFraction") &&
      neutral_hadron_fraction_max >
          input.selectedJetsAK15.at(0).userFloat("neutralHadronEnergyFraction");

  if (!leading_jet_criterium) return false;

  // get correct MET/hadronic recoil from events, see METSelection.cpp for
  // explanation
  math::XYZTLorentzVector met_p4(0., 0., 0., 0.);
  math::XYZTLorentzVector hadr_recoil_p4(0., 0., 0., 0.);

  if (input.systematic == Systematics::JESup) {
    met_p4 = input.correctedMET.shiftedP4(pat::MET::JetEnUp, pat::MET::Type1XY);
  } else if (input.systematic == Systematics::JESdown) {
    met_p4 =
        input.correctedMET.shiftedP4(pat::MET::JetEnDown, pat::MET::Type1XY);
  } else if (input.systematic == Systematics::JERup) {
    met_p4 =
        input.correctedMET.shiftedP4(pat::MET::JetResUp, pat::MET::Type1XY);
  } else if (input.systematic == Systematics::JERdown) {
    met_p4 =
        input.correctedMET.shiftedP4(pat::MET::JetResDown, pat::MET::Type1XY);
  }
  //     else if(input.systematic==Systematics::METUnclENup) {
  //       met_p4 =
  //       input.correctedMET.shiftedP4(pat::MET::UnclusteredEnUp,pat::MET::Type1XY);
  //     }
  //     else if(input.systematic==Systematics::METUnclENdown) {
  //         met_p4 =
  //         input.correctedMET.shiftedP4(pat::MET::UnclusteredEnDown,pat::MET::Type1XY);
  //     }
  else {
    met_p4 = input.correctedMET.corP4(pat::MET::Type1XY);
  }

  hadr_recoil_p4 = met_p4;
  for (const auto& el : input.selectedElectronsLoose) {
    hadr_recoil_p4 += el.p4();
  }
  for (const auto& mu : input.selectedMuonsLoose) {
    hadr_recoil_p4 += mu.p4();
  }
  //     for(const auto& ph : input.selectedPhotonsLoose){
  //         hadr_recoil_p4 += ph.p4();
  //     }

  // deltaphi criteria between jets and MET to suppress mismeasured QCD events
  // bool dPhi_jet_met_criterium = true;
  // for(size_t i=0;i<input.selectedJets.size()&&i<4;i++) {
  //    dPhi_jet_met_criterium =
  //    fabs(TVector2::Phi_mpi_pi(met_p4.phi()-input.selectedJets.at(i).phi()))>0.5;
  //    if(!dPhi_jet_met_criterium) return false;
  //}

  // Delta phi criterium between AK15 jet and MET
  if (fabs(TVector2::Phi_mpi_pi(met_p4.phi() -
                                input.selectedJetsAK15.at(0).phi())) < 1.5)
    return false;

  cutflow.EventSurvivedStep("Exactly one AK15 jet with pt greater than " +
                                pt_str + " and eta smaller than " + eta_str,
                            input.weights.at("Weight"));
  return true;
}
