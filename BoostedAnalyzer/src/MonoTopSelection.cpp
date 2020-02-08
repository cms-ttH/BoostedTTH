#include "BoostedTTH/BoostedAnalyzer/interface/MonoTopSelection.hpp"

using namespace std;

MonoTopSelection::MonoTopSelection(const edm::ParameterSet& iConfig) :
    MonoTopSelection(iConfig.getParameter< double >("AK15Jet_Pt"), iConfig.getParameter< double >("AK15Jet_Eta"), iConfig.getParameter< double >("AK15Jet_Chf"),
                     iConfig.getParameter< double >("AK15Jet_Nhf"), iConfig.getParameter< double >("minMET"), iConfig.getParameter< double >("minRecoil"))
{
}
MonoTopSelection::MonoTopSelection(double pt_min_, double eta_max_, double chf_min_, double nhf_max_, double min_MET_, double min_Recoil_) :
    pt_min(pt_min_),
    eta_max(eta_max_),
    charged_hadron_fraction_min(chf_min_),
    neutral_hadron_fraction_max(nhf_max_),
    minMET(min_MET_),
    minRecoil(min_Recoil_)
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

    // get correct MET/hadronic recoil from events, see METSelection.cpp for explanation
    math::XYZTLorentzVector met_p4(0., 0., 0., 0.);
    math::XYZTLorentzVector hadr_recoil_p4(0., 0., 0., 0.);

    if (input.systematic == Systematics::JESup) { met_p4 = input.correctedMETPuppi.shiftedP4(pat::MET::JetEnUp, pat::MET::Type1); }
    else if (input.systematic == Systematics::JESdown) {
        met_p4 = input.correctedMETPuppi.shiftedP4(pat::MET::JetEnDown, pat::MET::Type1);
    }
    else if (input.systematic == Systematics::JERup) {
        met_p4 = input.correctedMETPuppi.shiftedP4(pat::MET::JetResUp, pat::MET::Type1);
    }
    else if (input.systematic == Systematics::JERdown) {
        met_p4 = input.correctedMETPuppi.shiftedP4(pat::MET::JetResDown, pat::MET::Type1);
    }
    //     else if(input.systematic==Systematics::METUnclENup) {
    //       met_p4 =
    //       input.correctedMETPuppi.shiftedP4(pat::MET::UnclusteredEnUp,pat::MET::Type1);
    //     }
    //     else if(input.systematic==Systematics::METUnclENdown) {
    //         met_p4 =
    //         input.correctedMETPuppi.shiftedP4(pat::MET::UnclusteredEnDown,pat::MET::Type1);
    //     }
    else {
        met_p4 = input.correctedMETPuppi.corP4(pat::MET::Type1);
    }

    // calculate hadronic recoil starting from MET
    hadr_recoil_p4 = met_p4;
    for (const auto& el : input.selectedElectronsLoose) { hadr_recoil_p4 += el.p4(); }
    for (const auto& mu : input.selectedMuonsLoose) { hadr_recoil_p4 += mu.p4(); }
    for (const auto& ph : input.selectedPhotons) { hadr_recoil_p4 += ph.p4(); }

    // for softdrop mass criterium
    std::vector< math::XYZTLorentzVector > ak15_softdrop_jets_from_subjets;
    std::vector< float >                   ak15_softdrop_masses;
    for (const auto& ak15jet : input.selectedJetsAK15) {
        math::XYZTLorentzVector ak15_softdrop_jet{0., 0., 0., 0.};
        for (const auto& ak15_softdrop_subjet : ak15jet.subjets("SoftDropWithBtagInfoCorrected")) { ak15_softdrop_jet += ak15_softdrop_subjet->p4(); }
        ak15_softdrop_jets_from_subjets.push_back(ak15_softdrop_jet);
        ak15_softdrop_masses.push_back(ak15jet.userFloat("ak15PFJetsPuppiSoftDropMass"));
    }

    // sort starting with highest softdrop pt
    std::sort(ak15_softdrop_jets_from_subjets.begin(), ak15_softdrop_jets_from_subjets.end(), [](auto& a, auto& b) { return a.pt() > b.pt(); });
    // check if hardest ak15 jet or softdrop jet satisfies minimum pt
    bool leading_ak15jet_pt_criterium = (input.selectedJetsAK15.size() > 0 ? (input.selectedJetsAK15.at(0).pt() > pt_min) : false) ||
                                        (ak15_softdrop_jets_from_subjets.size() > 0 ? (ak15_softdrop_jets_from_subjets.at(0).pt() > pt_min) : false);

    // sort starting with highest softdrop mass
    std::sort(ak15_softdrop_jets_from_subjets.begin(), ak15_softdrop_jets_from_subjets.end(), [](auto& a, auto& b) { return a.mass() > b.mass(); });
    std::sort(ak15_softdrop_masses.begin(), ak15_softdrop_masses.end(), [](auto& a, auto& b) { return a > b; });
    bool softdrop_mass_criterium = (ak15_softdrop_jets_from_subjets.size() > 0 ? (ak15_softdrop_jets_from_subjets.at(0).mass() > 30.) : false) ||
                                   (ak15_softdrop_masses.size() > 0 ? (ak15_softdrop_masses.at(0) > 30.) : false);

    // criteria for number of ak15 jets, MET, highest softdrop mass, and hadronic recoil in hadronic monotop channel
    bool n_ak15_jets_criterium = (input.selectedJetsAK15.size() >= 1) && (input.selectedJetsAK15.size() <= 2);
    bool met_recoil_criterium  = (met_p4.pt() >= minRecoil) || (hadr_recoil_p4.pt() >= minRecoil);
    bool hadronic_criterium    = met_recoil_criterium && n_ak15_jets_criterium && leading_ak15jet_pt_criterium && softdrop_mass_criterium;

    // event is compatible with hadronic monotop selection
    if (hadronic_criterium) {
        cutflow.EventSurvivedStep("MonoTopSelection", input.weights.at("Weight"));
        return true;
    }
    // deltaphi criteria between jets and MET to suppress mismeasured QCD events
    // bool dPhi_jet_met_criterium = true;
    // for(size_t i=0;i<input.selectedJets.size()&&i<4;i++) {
    //    dPhi_jet_met_criterium =
    //    fabs(TVector2::Phi_mpi_pi(met_p4.phi()-input.selectedJets.at(i).phi()))>0.5;
    //    if(!dPhi_jet_met_criterium) return false;
    //}

    // Delta phi criterium between AK15 jet and MET
    // if (fabs(TVector2::Phi_mpi_pi(met_p4.phi() - input.selectedJetsAK15.at(0).phi())) < deltaR_MET_AK15Jet) return false;

    // criteria for number of AK4 jets, number of well reconstructed leptons, and MET for leptonic monotop channel
    bool n_ak4_jets_criterium = (input.selectedJets.size() >= 1) && (input.selectedJets.size() <= 3);
    bool n_lepton_criterium   = (input.selectedElectrons.size() + input.selectedMuons.size()) == 1;
    bool met_criterium        = met_p4.pt() >= minMET;
    bool leptonic_criterium   = n_ak4_jets_criterium && n_lepton_criterium && met_criterium;

    // event is compatible with leptonic monotop selection
    if (leptonic_criterium) {
        cutflow.EventSurvivedStep("MonoTopSelection", input.weights.at("Weight"));
        return true;
    }

    // event is not compatible with either hadronic or leptonic monotop selection
    return false;
}
