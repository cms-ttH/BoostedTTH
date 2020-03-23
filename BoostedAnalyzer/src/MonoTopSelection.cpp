#include "BoostedTTH/BoostedAnalyzer/interface/MonoTopSelection.hpp"

using namespace std;

MonoTopSelection::MonoTopSelection(const edm::ParameterSet& iConfig) :
    MonoTopSelection(iConfig.getParameter< double >("AK15Jet_Pt"), iConfig.getParameter< double >("AK15Jet_Eta"), iConfig.getParameter< double >("AK15Jet_Chf"),
                     iConfig.getParameter< double >("AK15Jet_Nhf"), iConfig.getParameter< double >("minMET"), iConfig.getParameter< double >("minRecoil"),
                     iConfig.getParameter< double >("AK15Jet_Min_SoftDrop_Mass"), iConfig.getParameter< double >("AK15Jet_Max_SoftDrop_Mass"))
{
}
MonoTopSelection::MonoTopSelection(double pt_min_, double eta_max_, double chf_min_, double nhf_max_, double min_MET_, double min_Recoil_,
                                   double minSoftDropMass_, double maxSoftDropMass_) :
    pt_min(pt_min_),
    eta_max(eta_max_),
    charged_hadron_fraction_min(chf_min_),
    neutral_hadron_fraction_max(nhf_max_),
    minMET(min_MET_),
    minRecoil(min_Recoil_),
    minSoftDropMass(minSoftDropMass_),
    maxSoftDropMass(maxSoftDropMass_)
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
    // else if(input.systematic==Systematics::METUnclENup) {
    // met_p4 =
    // input.correctedMETPuppi.shiftedP4(pat::MET::UnclusteredEnUp,pat::MET::Type1);
    //}
    // else if(input.systematic==Systematics::METUnclENdown) {
    // met_p4 =
    // input.correctedMETPuppi.shiftedP4(pat::MET::UnclusteredEnDown,pat::MET::Type1);
    //}
    else {
        met_p4 = input.correctedMETPuppi.corP4(pat::MET::Type1);
    }
    // catch possible error where JER corrected MET has nan values
    // use nominal MET instead as temporary solution
    if (std::isnan(met_p4.pt())) { met_p4 = input.correctedMETPuppi.corP4(pat::MET::Type1); }

    // calculate hadronic recoil starting from MET
    hadr_recoil_p4 = met_p4;
    for (const auto& el : input.selectedElectronsLoose) { hadr_recoil_p4 += el.p4(); }
    for (const auto& mu : input.selectedMuonsLoose) { hadr_recoil_p4 += mu.p4(); }
    for (const auto& ph : input.selectedPhotons) { hadr_recoil_p4 += ph.p4(); }

    // hadronic tau criterium
    // bool hadronic_tau_criterium = input.selectedTaus.size() == 0;

    // for softdrop mass criterium
    // std::vector< math::XYZTLorentzVector > ak15_softdrop_jets_from_subjets;
    // std::vector< float >                   ak15_softdrop_masses;
    // for (const auto& ak15jet : input.selectedJetsAK15) {
    // if (not ak15jet.hasSubjets("SoftDropWithBtagInfoCorrected")) continue;
    // math::XYZTLorentzVector ak15_softdrop_jet{0., 0., 0., 0.};
    // for (const auto& ak15_softdrop_subjet : ak15jet.subjets("SoftDropWithBtagInfoCorrected")) { ak15_softdrop_jet += ak15_softdrop_subjet->p4(); }
    // ak15_softdrop_jets_from_subjets.push_back(ak15_softdrop_jet);
    // ak15_softdrop_masses.push_back(ak15jet.hasUserFloat("ak15PFJetsPuppiSoftDropMass") ? ak15jet.userFloat("ak15PFJetsPuppiSoftDropMass") : -9.);
    //}

    // sort starting with highest softdrop pt
    // std::sort(ak15_softdrop_jets_from_subjets.begin(), ak15_softdrop_jets_from_subjets.end(), [](auto& a, auto& b) { return a.pt() > b.pt(); });
    // check if hardest ak15 jet or softdrop jet satisfies minimum pt

    // sort starting with highest softdrop mass
    // std::sort(ak15_softdrop_jets_from_subjets.begin(), ak15_softdrop_jets_from_subjets.end(), [](auto& a, auto& b) { return a.mass() > b.mass(); });
    // std::sort(ak15_softdrop_masses.begin(), ak15_softdrop_masses.end(), [](auto& a, auto& b) { return a > b; });
    // bool softdrop_mass_criterium = ak15_softdrop_jets_from_subjets.size() > 0
    //? ((ak15_softdrop_jets_from_subjets.at(0).mass() > minSoftDropMass || ak15_softdrop_masses.at(0) > minSoftDropMass) &&
    //   (ak15_softdrop_jets_from_subjets.back().mass() < maxSoftDropMass || ak15_softdrop_masses.back() < maxSoftDropMass))
    //: false;

    // criteria for number of ak15 jets, MET, highest softdrop mass, and hadronic recoil in hadronic monotop channel
    // bool n_ak15_jets_criterium =
    //(std::count_if(input.selectedJetsAK15.begin(), input.selectedJetsAK15.end(), [&](auto& jet) { return jet.pt() > pt_min; }) == 1) ||
    //(std::count_if(ak15_softdrop_jets_from_subjets.begin(), ak15_softdrop_jets_from_subjets.end(), [&](auto& jet) { return jet.pt() > pt_min; }) == 1);

    // bool softdrop_mass_criterium = (input.selectedJetsAK15.size() > 0 && input.selectedJetsAK15.at(0).hasUserFloat("ak15PFJetsPuppiSoftDropMass"))
    //                                   ? (input.selectedJetsAK15.at(0).userFloat("ak15PFJetsPuppiSoftDropMass") > minSoftDropMass)
    //                                   : true;

    bool met_recoil_criterium         = (met_p4.pt() >= minRecoil) || (hadr_recoil_p4.pt() >= minRecoil);
    bool n_ak15_jets_criterium        = (input.selectedJetsAK15.size() == 1);
    bool leading_ak15jet_pt_criterium = (input.selectedJetsAK15.size() > 0 ? (input.selectedJetsAK15.at(0).pt() > pt_min) : false);
    bool n_max_leptons_criterium      = (input.selectedElectronsLoose.size() + input.selectedMuonsLoose.size()) <= 2;
    bool hadronic_criterium           = met_recoil_criterium && n_ak15_jets_criterium && n_max_leptons_criterium && leading_ak15jet_pt_criterium;

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
    float m_transverse = 0.;
    if ((input.selectedElectrons.size() + input.selectedMuons.size()) == 1) {
        auto lepton_p4 = input.selectedElectrons.size() > 0 ? input.selectedElectrons.at(0).p4() : input.selectedMuons.at(0).p4();
        auto dphi      = fabs(TVector2::Phi_mpi_pi(met_p4.phi() - lepton_p4.phi()));
        auto cos_dphi  = TMath::Cos(dphi);
        m_transverse   = TMath::Sqrt(2 * lepton_p4.pt() * met_p4.pt() * (1 - cos_dphi));
    }

    bool n_ak4_jets_criterium   = (input.selectedJets.size() >= 1) && (input.selectedJets.size() <= 3);
    bool n_lepton_criterium     = (input.selectedElectrons.size() + input.selectedMuons.size()) == 1;
    bool met_criterium          = met_p4.pt() >= minMET;
    bool m_transverse_criterium = m_transverse >= 40.;
    bool leptonic_criterium     = n_ak4_jets_criterium && n_lepton_criterium && met_criterium && m_transverse_criterium;

    // event is compatible with leptonic monotop selection
    if (leptonic_criterium) {
        cutflow.EventSurvivedStep("MonoTopSelection", input.weights.at("Weight"));
        return true;
    }

    // event is not compatible with either hadronic or leptonic monotop selection
    return false;
}
