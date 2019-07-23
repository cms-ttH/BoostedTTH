#include "BoostedTTH/BoostedAnalyzer/interface/MonoTopSelection.hpp"

using namespace std;

MonoTopSelection::MonoTopSelection(const edm::ParameterSet& iConfig) :
    MonoTopSelection(iConfig.getParameter< double >("AK15Jet_Pt"), iConfig.getParameter< double >("AK15Jet_Eta"), iConfig.getParameter< double >("AK15Jet_Chf"),
                     iConfig.getParameter< double >("AK15Jet_Nhf"), iConfig.getParameter< double >("minMET"), iConfig.getParameter< double >("maxMET"),
                     iConfig.getParameter< double >("DeltaR_MET_AK15Jet"))
{
}
MonoTopSelection::MonoTopSelection(double pt_min_, double eta_max_, double chf_min_, double nhf_max_, double min_MET_, double max_MET_,
                                   double deltaR_MET_AK15Jet_) :
    pt_min(pt_min_),
    eta_max(eta_max_),
    charged_hadron_fraction_min(chf_min_),
    neutral_hadron_fraction_max(nhf_max_),
    minMET(min_MET_),
    maxMET(max_MET_),
    deltaR_MET_AK15Jet(deltaR_MET_AK15Jet_)
{
}
MonoTopSelection::~MonoTopSelection() {}

void MonoTopSelection::InitCutflow(Cutflow& cutflow)
{
    cutflow.AddStep("MonoTopSelection");

    initialized = true;
}

bool MonoTopSelection::IsSelected(const InputCollections& input, Cutflow& cutflow)
{
    if (!initialized) cerr << "MonoTopSelection not initialized" << endl;

    // do not use the event if there is not exactly one AK15 jet
    if (input.selectedJetsAK15.size() != 1) return false;

    // AK15 jet has to fulfill pt,eta and several quality criteria
    bool leading_jet_criterium = input.selectedJetsAK15.at(0).pt() > pt_min && fabs(input.selectedJetsAK15.at(0).eta()) < eta_max;  //&&
    //                                  charged_hadron_fraction_min < input.selectedJetsAK15.at(0).userFloat("chargedHadronEnergyFraction") &&
    //                                  neutral_hadron_fraction_max > input.selectedJetsAK15.at(0).userFloat("neutralHadronEnergyFraction");

    if (!leading_jet_criterium) return false;

    // get correct MET/hadronic recoil from events, see METSelection.cpp for
    // explanation
    math::XYZTLorentzVector met_p4(0., 0., 0., 0.);
    math::XYZTLorentzVector hadr_recoil_p4(0., 0., 0., 0.);

    if (input.systematic == Systematics::JESup) { met_p4 = input.correctedMET.shiftedP4(pat::MET::JetEnUp, pat::MET::Type1XY); }
    else if (input.systematic == Systematics::JESdown) {
        met_p4 = input.correctedMET.shiftedP4(pat::MET::JetEnDown, pat::MET::Type1XY);
    }
    else if (input.systematic == Systematics::JERup) {
        met_p4 = input.correctedMET.shiftedP4(pat::MET::JetResUp, pat::MET::Type1XY);
    }
    else if (input.systematic == Systematics::JERdown) {
        met_p4 = input.correctedMET.shiftedP4(pat::MET::JetResDown, pat::MET::Type1XY);
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
    for (const auto& el : input.selectedElectrons) { hadr_recoil_p4 += el.p4(); }
    for (const auto& mu : input.selectedMuons) { hadr_recoil_p4 += mu.p4(); }
    for (const auto& ph : input.selectedPhotons) { hadr_recoil_p4 += ph.p4(); }

    if (met_p4.pt() < minMET && hadr_recoil_p4.pt() < minMET) return false;
    // deltaphi criteria between jets and MET to suppress mismeasured QCD events
    // bool dPhi_jet_met_criterium = true;
    // for(size_t i=0;i<input.selectedJets.size()&&i<4;i++) {
    //    dPhi_jet_met_criterium =
    //    fabs(TVector2::Phi_mpi_pi(met_p4.phi()-input.selectedJets.at(i).phi()))>0.5;
    //    if(!dPhi_jet_met_criterium) return false;
    //}

    // Delta phi criterium between AK15 jet and MET
    if (fabs(TVector2::Phi_mpi_pi(met_p4.phi() - input.selectedJetsAK15.at(0).phi())) < deltaR_MET_AK15Jet) return false;

    cutflow.EventSurvivedStep("MonoTopSelection", input.weights.at("Weight"));
    return true;
}
