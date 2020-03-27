#include "BoostedTTH/BoostedAnalyzer/interface/DarkMatterProcessor.hpp"

using namespace std;

DarkMatterProcessor::DarkMatterProcessor() {}
DarkMatterProcessor::~DarkMatterProcessor() {}

void DarkMatterProcessor::Init(const InputCollections& input, VariableContainer& vars)
{
    era = input.era;
    
    vars.InitVar("Evt_Pt_MET");
    vars.InitVar("Evt_Phi_MET");
    vars.InitVar("Evt_Pt_MET_T1XY");
    vars.InitVar("Evt_Phi_MET_T1XY");
    vars.InitVar("Evt_Pt_MET_UnclEnUp");
    vars.InitVar("Evt_Pt_MET_UnclEnDown");
    vars.InitVar("Evt_Pt_GenMET");
    vars.InitVar("Evt_Phi_GenMET");
    vars.InitVar("CaloMET");
    vars.InitVar("CaloMET_PFMET_ratio");
    vars.InitVar("CaloMET_PFMET_vec_ratio");
    vars.InitVar("CaloMET_PFMET_Recoil_ratio");
    vars.InitVar("CaloMET_PFMET_Recoil_vec_ratio");
    vars.InitVar("NaiveMET");
    vars.InitVar("Hadr_Recoil_Pt");
    vars.InitVar("Hadr_Recoil_Phi");
    vars.InitVar("Gen_Hadr_Recoil_Pt");
    vars.InitVar("Gen_Hadr_Recoil_Phi");
    vars.InitVar("CaloMET_Hadr_Recoil_ratio");

    vars.InitVar("HT_AK4Jets");

    vars.InitVar("N_LooseLeptons", "I");
    vars.InitVars("M_W_transverse", "N_LooseLeptons");

    vars.InitVars("DeltaPhi_LooseElectron_MET", "N_LooseElectrons");
    vars.InitVars("DeltaPhi_LooseMuon_MET", "N_LooseMuons");

    vars.InitVars("DeltaPhi_AK4Jet_MET", "N_Jets");
    vars.InitVars("DeltaPhi_AK4Jet_Hadr_Recoil", "N_Jets");
    vars.InitVars("DeltaPhi_AK8Jet_MET", "N_AK8Jets");
    vars.InitVars("DeltaPhi_AK8Jet_Hadr_Recoil", "N_AK8Jets");
    vars.InitVars("DeltaPhi_AK15Jet_MET", "N_AK15Jets");
    vars.InitVars("DeltaPhi_AK15Jet_Hadr_Recoil", "N_AK15Jets");

    vars.InitVar("N_AK15Jets_x_N_LooseElectrons", "I");
    vars.InitVar("N_AK8Jets_x_N_LooseElectrons", "I");
    vars.InitVar("N_AK4Jets_x_N_LooseElectrons", "I");
    vars.InitVar("N_AK15Jets_x_N_LooseMuons", "I");
    vars.InitVar("N_AK8Jets_x_N_LooseMuons", "I");
    vars.InitVar("N_AK4Jets_x_N_LooseMuons", "I");
    vars.InitVar("N_AK15Jets_x_N_LoosePhotons", "I");
    vars.InitVar("N_AK8Jets_x_N_LoosePhotons", "I");
    vars.InitVar("N_AK4Jets_x_N_LoosePhotons", "I");

    vars.InitVars("DeltaR_AK15Jet_LooseElectron", "N_AK15Jets_x_N_LooseElectrons");
    vars.InitVars("DeltaR_AK8Jet_LooseElectron", "N_AK8Jets_x_N_LooseElectrons");
    vars.InitVars("DeltaR_AK4Jet_LooseElectron", "N_AK4Jets_x_N_LooseElectrons");
    vars.InitVars("DeltaR_AK15Jet_LooseMuon", "N_AK15Jets_x_N_LooseMuons");
    vars.InitVars("DeltaR_AK8Jet_LooseMuon", "N_AK8Jets_x_N_LooseMuons");
    vars.InitVars("DeltaR_AK4Jet_LooseMuon", "N_AK4Jets_x_N_LooseMuons");
    vars.InitVars("DeltaR_AK4Jet_LoosePhoton", "N_AK4Jets_x_N_LoosePhotons");
    vars.InitVars("DeltaR_AK8Jet_LoosePhoton", "N_AK8Jets_x_N_LoosePhotons");
    vars.InitVars("DeltaR_AK15Jet_LoosePhoton", "N_AK15Jets_x_N_LoosePhotons");
    
    vars.InitVar("N_AK4JetsTagged_x_N_LooseElectrons", "I");
    vars.InitVar("N_AK4JetsUntagged_x_N_LooseElectrons", "I");
    vars.InitVar("N_AK4JetsTagged_x_N_LooseMuons", "I");
    vars.InitVar("N_AK4JetsUntagged_x_N_LooseMuons", "I");
    
    vars.InitVars("DeltaPhi_AK4JetTagged_MET", "N_BTagsM");
    vars.InitVars("DeltaPhi_AK4JetUntagged_MET", "N_NoTags");
    vars.InitVars("DeltaR_AK4JetTagged_LooseElectron", "N_AK4JetsTagged_x_N_LooseElectrons");
    vars.InitVars("DeltaR_AK4JetUntagged_LooseElectron", "N_AK4JetsUntagged_x_N_LooseElectrons");
    vars.InitVars("DeltaR_AK4JetTagged_LooseMuon", "N_AK4JetsTagged_x_N_LooseMuons");
    vars.InitVars("DeltaR_AK4JetUntagged_LooseMuon", "N_AK4JetsUntagged_x_N_LooseMuons");

    vars.InitVar("N_Neutralinos", "I");
    vars.InitVar("N_Neutrinos", "I");

    vars.InitVar("Mediator_Mass");
    vars.InitVar("Mediator_Pt");
    vars.InitVar("Mediator_Phi");
    vars.InitVar("Mediator_Eta");
    vars.InitVar("Mediator_Energy");
    vars.InitVar("Mediator_Px");
    vars.InitVar("Mediator_Py");
    vars.InitVar("Mediator_Pz");

    vars.InitVars("Neutralino_Mass", "N_Neutralinos");
    vars.InitVars("Neutralino_Pt", "N_Neutralinos");
    vars.InitVars("Neutralino_Phi", "N_Neutralinos");
    vars.InitVars("Neutralino_Eta", "N_Neutralinos");
    vars.InitVars("Neutralino_Energy", "N_Neutralinos");
    vars.InitVars("Neutralino_Px", "N_Neutralinos");
    vars.InitVars("Neutralino_Py", "N_Neutralinos");
    vars.InitVars("Neutralino_Pz", "N_Neutralinos");

    vars.InitVar("N1_N2_Mass");
    vars.InitVar("N1_N2_Pt");
    vars.InitVar("N1_N2_Phi");
    vars.InitVar("N1_N2_Eta");
    vars.InitVar("N1_N2_Energy");
    vars.InitVar("N1_N2_Px");
    vars.InitVar("N1_N2_Py");
    vars.InitVar("N1_N2_Pz");

    vars.InitVar("cos_theta_N1_N2");
    vars.InitVar("cos_theta_Med_N1");
    vars.InitVar("cos_theta_Med_N2");

    vars.InitVar("delta_phi_N1_N2");
    vars.InitVar("delta_phi_Med_N1");
    vars.InitVar("delta_phi_Med_N2");

    vars.InitVar("delta_R_N1_N2");
    vars.InitVar("delta_R_Med_N1");
    vars.InitVar("delta_R_Med_N2");

    vars.InitVars("Neutrino_Mass", "N_Neutrinos");
    vars.InitVars("Neutrino_Pt", "N_Neutrinos");
    vars.InitVars("Neutrino_Phi", "N_Neutrinos");
    vars.InitVars("Neutrino_Eta", "N_Neutrinos");
    vars.InitVars("Neutrino_Energy", "N_Neutrinos");
    vars.InitVars("Neutrino_Px", "N_Neutrinos");
    vars.InitVars("Neutrino_Py", "N_Neutrinos");
    vars.InitVars("Neutrino_Pz", "N_Neutrinos");

    // particle-level quantities!
    vars.InitVar("W_Pt");
    vars.InitVar("W_Phi");
    vars.InitVar("W_Eta");
    vars.InitVar("W_Mass");
    vars.InitVar("W_Energy");
    vars.InitVar("Z_Pt");
    vars.InitVar("Z_Phi");
    vars.InitVar("Z_Eta");
    vars.InitVar("Z_Mass");
    vars.InitVar("Z_Energy");
    vars.InitVar("Gamma_Pt");
    vars.InitVar("Gamma_Phi");
    vars.InitVar("Gamma_Eta");
    vars.InitVar("Gamma_Mass");
    vars.InitVar("Gamma_Energy");

    //     vars.InitVar("Zmumu_Pt_Hadr_Recoil_Pt_ratio");

    vars.InitVar("Problematic_MET", "I");

    vars.InitVar("N_HEM_METS", "I");

    initialized = true;
}

void DarkMatterProcessor::Process(const InputCollections& input, VariableContainer& vars)
{
    if (!initialized) cerr << "tree processor not initialized" << endl;

    // 4-vector for hadronic recoil on gen level
    math::XYZTLorentzVector gen_hadr_recoil_p4(0., 0., 0., 0.);

    // GenMET
    if (input.correctedMETPuppi.genMET() != 0) {
        if (input.correctedMETPuppi.genMET()->pt() < 1) {  // fix for broken GenMET in MadGraphMonoJetSamples
            if (input.genDarkMatterEvt.IsFilled()) {
                const GenDarkMatterEvent& DM_Evt = input.genDarkMatterEvt;
                vars.FillVar("Evt_Pt_GenMET", DM_Evt.ReturnNaiveMET4Vector().Pt());
                vars.FillVar("Evt_Phi_GenMET", DM_Evt.ReturnNaiveMET4Vector().Phi());
                gen_hadr_recoil_p4 = BoostedUtils::GetXYZTLorentzVector(DM_Evt.ReturnNaiveMET4Vector());
            }
        }
        else {
            vars.FillVar("Evt_Pt_GenMET", input.correctedMETPuppi.genMET()->pt());
            vars.FillVar("Evt_Phi_GenMET", input.correctedMETPuppi.genMET()->phi());
            gen_hadr_recoil_p4 = input.correctedMETPuppi.genMET()->p4();
        }

        // calculate gen hadronic recoil from gen MET
        //         for (const auto& el : input.customGenElectrons) { gen_hadr_recoil_p4 += el.p4(); }
        //         for (const auto& mu : input.customGenMuons) { gen_hadr_recoil_p4 += mu.p4(); }
        //         for (const auto& ph : input.customGenPhotons) { gen_hadr_recoil_p4 += ph.p4(); }
    }

    // fill hadronic recoil pt and phi on gen level
    vars.FillVar("Gen_Hadr_Recoil_Pt", gen_hadr_recoil_p4.pt());
    vars.FillVar("Gen_Hadr_Recoil_Phi", gen_hadr_recoil_p4.phi());

    // 4-vectors to contain MET and hadronic recoil
    math::XYZTLorentzVector met_p4(0., 0., 0., 0.);
    math::XYZTLorentzVector hadr_recoil_p4(0., 0., 0., 0.);

    // get reco MET
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
    //     else if (input.systematic == Systematics::METUnclENup) {
    //         met_p4 = input.correctedMETPuppi.shiftedP4(pat::MET::UnclusteredEnUp, pat::MET::Type1);
    //     }
    //     else if (input.systematic == Systematics::METUnclENdown) {
    //         met_p4 = input.correctedMETPuppi.shiftedP4(pat::MET::UnclusteredEnDown, pat::MET::Type1);
    //     }
    else {
        met_p4 = input.correctedMETPuppi.corP4(pat::MET::Type1);
    }

    if (std::isnan(met_p4.pt())) {
        vars.FillVar("Problematic_MET", 1);
        met_p4 = input.correctedMETPuppi.corP4(pat::MET::Type1);
    }
    else {
        vars.FillVar("Problematic_MET", 0);
    }

    math::XYZTLorentzVector calomet_p4(input.correctedMETPuppi.caloMETP2().px, input.correctedMETPuppi.caloMETP2().py, 0., 0.);

    vars.FillVar("Evt_Pt_MET", met_p4.pt());
    vars.FillVar("Evt_Phi_MET", met_p4.phi());
    vars.FillVar("Evt_Pt_MET_T1XY", input.correctedMETPuppi.corPt(pat::MET::Type1XY));
    vars.FillVar("Evt_Phi_MET_T1XY", input.correctedMETPuppi.corPhi(pat::MET::Type1XY));
    vars.FillVar("Evt_Pt_MET_UnclEnUp", input.correctedMETPuppi.shiftedPt(pat::MET::UnclusteredEnUp, pat::MET::Type1));
    vars.FillVar("Evt_Pt_MET_UnclEnDown", input.correctedMETPuppi.shiftedPt(pat::MET::UnclusteredEnDown, pat::MET::Type1));
    vars.FillVar("CaloMET", input.correctedMETPuppi.caloMETPt());
    vars.FillVar("CaloMET_PFMET_ratio", fabs(met_p4.pt() - input.correctedMETPuppi.caloMETPt()) / input.correctedMETPuppi.caloMETPt());
    vars.FillVar("CaloMET_PFMET_vec_ratio", (met_p4 - calomet_p4).pt() / calomet_p4.pt());

    // transverse W mass
    std::vector< double > v_M_W_transverse;
    vars.FillVar("N_LooseLeptons", input.selectedElectronsLoose.size() + input.selectedMuonsLoose.size());

    for (size_t i = 0; i < input.selectedElectronsLoose.size(); i++) {
        double dphi = fabs(TVector2::Phi_mpi_pi(met_p4.phi() - input.selectedElectronsLoose.at(i).phi()));
        vars.FillVars("DeltaPhi_LooseElectron_MET", i, dphi);
        double cos_dphi = TMath::Cos(dphi);
        v_M_W_transverse.push_back(TMath::Sqrt(2 * input.selectedElectronsLoose.at(i).pt() * met_p4.pt() * (1 - cos_dphi)));
    }
    for (size_t i = 0; i < input.selectedMuonsLoose.size(); i++) {
        double dphi = fabs(TVector2::Phi_mpi_pi(met_p4.phi() - input.selectedMuonsLoose.at(i).phi()));
        vars.FillVars("DeltaPhi_LooseMuon_MET", i, dphi);
        double cos_dphi = TMath::Cos(dphi);
        v_M_W_transverse.push_back(TMath::Sqrt(2 * input.selectedMuonsLoose.at(i).pt() * met_p4.pt() * (1 - cos_dphi)));
    }

    for (size_t i = 0; i < v_M_W_transverse.size(); i++) { vars.FillVars("M_W_transverse", i, v_M_W_transverse.at(i)); }

    double ht_ak4jets = 0.0;
    for (size_t i = 0; i < input.selectedJets.size(); i++) {
        vars.FillVars("DeltaPhi_AK4Jet_MET", i, fabs(TVector2::Phi_mpi_pi(met_p4.phi() - input.selectedJets.at(i).phi())));
        ht_ak4jets += input.selectedJets.at(i).pt();
    }
    for (size_t i = 0; i < input.selectedJetsAK8.size(); i++) {
        vars.FillVars("DeltaPhi_AK8Jet_MET", i, fabs(TVector2::Phi_mpi_pi(met_p4.phi() - input.selectedJetsAK8.at(i).phi())));
    }
    for (size_t i = 0; i < input.selectedJetsAK15.size(); i++) {
        vars.FillVars("DeltaPhi_AK15Jet_MET", i, fabs(TVector2::Phi_mpi_pi(met_p4.phi() - input.selectedJetsAK15.at(i).phi())));
    }

    // calculate hadronic recoil from reco MET
    hadr_recoil_p4 = met_p4;
    for (const auto& el : input.selectedElectronsLoose) { hadr_recoil_p4 += el.p4(); }
    for (const auto& mu : input.selectedMuonsLoose) { hadr_recoil_p4 += mu.p4(); }
    for (const auto& ph : input.selectedPhotons) { hadr_recoil_p4 += ph.p4(); }

    vars.FillVar("Hadr_Recoil_Pt", hadr_recoil_p4.pt());
    vars.FillVar("Hadr_Recoil_Phi", hadr_recoil_p4.phi());
    vars.FillVar("CaloMET_Hadr_Recoil_ratio", fabs(hadr_recoil_p4.pt() - input.correctedMETPuppi.caloMETPt()) / input.correctedMETPuppi.caloMETPt());
    vars.FillVar("CaloMET_PFMET_Recoil_ratio", fabs(met_p4.pt() - input.correctedMETPuppi.caloMETPt()) / hadr_recoil_p4.pt());
    vars.FillVar("CaloMET_PFMET_Recoil_vec_ratio", (met_p4 - calomet_p4).pt() / hadr_recoil_p4.pt());

    vars.FillVar("N_AK15Jets_x_N_LooseElectrons", input.selectedJetsAK15.size() * input.selectedElectronsLoose.size());
    vars.FillVar("N_AK8Jets_x_N_LooseElectrons", input.selectedJetsAK8.size() * input.selectedElectronsLoose.size());
    vars.FillVar("N_AK4Jets_x_N_LooseElectrons", input.selectedJets.size() * input.selectedElectronsLoose.size());
    vars.FillVar("N_AK15Jets_x_N_LooseMuons", input.selectedJetsAK15.size() * input.selectedMuonsLoose.size());
    vars.FillVar("N_AK8Jets_x_N_LooseMuons", input.selectedJetsAK8.size() * input.selectedMuonsLoose.size());
    vars.FillVar("N_AK4Jets_x_N_LooseMuons", input.selectedJets.size() * input.selectedMuonsLoose.size());
    vars.FillVar("N_AK15Jets_x_N_LoosePhotons", input.selectedJetsAK15.size() * input.selectedPhotonsLoose.size());
    vars.FillVar("N_AK8Jets_x_N_LoosePhotons", input.selectedJetsAK8.size() * input.selectedPhotonsLoose.size());
    vars.FillVar("N_AK4Jets_x_N_LoosePhotons", input.selectedJets.size() * input.selectedPhotonsLoose.size());

    for (size_t i = 0; i < input.selectedJets.size(); i++) {
        vars.FillVars("DeltaPhi_AK4Jet_Hadr_Recoil", i, fabs(TVector2::Phi_mpi_pi(hadr_recoil_p4.phi() - input.selectedJets.at(i).phi())));
        for (size_t j = 0; j < input.selectedElectronsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK4Jet_LooseElectron", i * input.selectedElectronsLoose.size() + j,
                          BoostedUtils::DeltaR(input.selectedJets.at(i).p4(), input.selectedElectronsLoose.at(j).p4()));
        }
        for (size_t j = 0; j < input.selectedMuonsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK4Jet_LooseMuon", i * input.selectedMuonsLoose.size() + j,
                          BoostedUtils::DeltaR(input.selectedJets.at(i).p4(), input.selectedMuonsLoose.at(j).p4()));
        }
        for (size_t j = 0; j < input.selectedPhotonsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK4Jet_LoosePhoton", i * input.selectedPhotonsLoose.size() + j,
                          BoostedUtils::DeltaR(input.selectedJets.at(i).p4(), input.selectedPhotonsLoose.at(j).p4()));
        }
    }
    for (size_t i = 0; i < input.selectedJetsAK8.size(); i++) {
        vars.FillVars("DeltaPhi_AK8Jet_Hadr_Recoil", i, fabs(TVector2::Phi_mpi_pi(hadr_recoil_p4.phi() - input.selectedJetsAK8.at(i).phi())));
        for (size_t j = 0; j < input.selectedElectronsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK8Jet_LooseElectron", i * input.selectedElectronsLoose.size() + j,
                          BoostedUtils::DeltaR(input.selectedJetsAK8.at(i).p4(), input.selectedElectronsLoose.at(j).p4()));
        }
        for (size_t j = 0; j < input.selectedMuonsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK8Jet_LooseMuon", i * input.selectedMuonsLoose.size() + j,
                          BoostedUtils::DeltaR(input.selectedJetsAK8.at(i).p4(), input.selectedMuonsLoose.at(j).p4()));
        }
        for (size_t j = 0; j < input.selectedPhotonsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK8Jet_LoosePhoton", i * input.selectedPhotonsLoose.size() + j,
                          BoostedUtils::DeltaR(input.selectedJetsAK8.at(i).p4(), input.selectedPhotonsLoose.at(j).p4()));
        }
    }
    for (size_t i = 0; i < input.selectedJetsAK15.size(); i++) {
        vars.FillVars("DeltaPhi_AK15Jet_Hadr_Recoil", i, fabs(TVector2::Phi_mpi_pi(hadr_recoil_p4.phi() - input.selectedJetsAK15.at(i).phi())));
        for (size_t j = 0; j < input.selectedElectronsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK15Jet_LooseElectron", i * input.selectedElectronsLoose.size() + j,
                          BoostedUtils::DeltaR(input.selectedJetsAK15.at(i).p4(), input.selectedElectronsLoose.at(j).p4()));
        }
        for (size_t j = 0; j < input.selectedMuonsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK15Jet_LooseMuon", i * input.selectedMuonsLoose.size() + j,
                          BoostedUtils::DeltaR(input.selectedJetsAK15.at(i).p4(), input.selectedMuonsLoose.at(j).p4()));
        }
        for (size_t j = 0; j < input.selectedPhotonsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK15Jet_LoosePhoton", i * input.selectedPhotonsLoose.size() + j,
                          BoostedUtils::DeltaR(input.selectedJetsAK15.at(i).p4(), input.selectedPhotonsLoose.at(j).p4()));
        }
    }

    int n_hem_mets = 0;
    for (const auto& loose_jet : input.selectedJetsLoose) {
        if (met_p4.phi() < -0.87 && met_p4.phi() > -1.57 && loose_jet.eta() < -1.3 && loose_jet.eta() > -3.2) n_hem_mets += 1;
    }
    vars.FillVar("N_HEM_METS", n_hem_mets);
    vars.FillVar("HT_AK4Jets", ht_ak4jets);
    
    const char*             btagger = "DeepJet";
    std::vector< pat::Jet > selectedTaggedJets;
    std::vector< pat::Jet > selectedUntaggedJets;
    for (std::vector< pat::Jet >::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet) {
        if (CSVHelper::PassesCSV(*itJet, btagger, CSVHelper::CSVwp::Medium, era))
            selectedTaggedJets.push_back(*itJet);
        else
            selectedUntaggedJets.push_back(*itJet);
    }
    
    vars.FillVar("N_AK4JetsTagged_x_N_LooseElectrons", selectedTaggedJets.size()*input.selectedElectronsLoose.size());
    vars.FillVar("N_AK4JetsUntagged_x_N_LooseElectrons", selectedUntaggedJets.size()*input.selectedElectronsLoose.size());
    vars.FillVar("N_AK4JetsTagged_x_N_LooseMuons", selectedTaggedJets.size()*input.selectedMuonsLoose.size());
    vars.FillVar("N_AK4JetsUntagged_x_N_LooseMuons", selectedUntaggedJets.size()*input.selectedMuonsLoose.size());
    
    for (size_t i = 0; i < selectedTaggedJets.size(); i++) {
        vars.FillVars("DeltaPhi_AK4JetTagged_MET", i, fabs(TVector2::Phi_mpi_pi(met_p4.phi() - selectedTaggedJets.at(i).phi())));
        for (size_t j = 0; j < input.selectedElectronsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK4JetTagged_LooseElectron", i * input.selectedElectronsLoose.size() + j,
                          BoostedUtils::DeltaR(selectedTaggedJets.at(i).p4(), input.selectedElectronsLoose.at(j).p4()));
        }
        for (size_t j = 0; j < input.selectedMuonsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK4JetTagged_LooseMuon", i * input.selectedMuonsLoose.size() + j,
                          BoostedUtils::DeltaR(selectedTaggedJets.at(i).p4(), input.selectedMuonsLoose.at(j).p4()));
        }
    }
    for (size_t i = 0; i < selectedUntaggedJets.size(); i++) {
        vars.FillVars("DeltaPhi_AK4JetUntagged_MET", i, fabs(TVector2::Phi_mpi_pi(met_p4.phi() - selectedUntaggedJets.at(i).phi())));
        for (size_t j = 0; j < input.selectedElectronsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK4JetUntagged_LooseElectron", i * input.selectedElectronsLoose.size() + j,
                          BoostedUtils::DeltaR(selectedUntaggedJets.at(i).p4(), input.selectedElectronsLoose.at(j).p4()));
        }
        for (size_t j = 0; j < input.selectedMuonsLoose.size(); j++) {
            vars.FillVars("DeltaR_AK4JetUntagged_LooseMuon", i * input.selectedMuonsLoose.size() + j,
                          BoostedUtils::DeltaR(selectedUntaggedJets.at(i).p4(), input.selectedMuonsLoose.at(j).p4()));
        }
    }

    // get particle-level W/Z pt for later usage in V boson reweighting
    if (input.genDarkMatterEvt.WBosonIsFilled()) {
        // std::cout << "W boson!" << std::endl;
        const GenDarkMatterEvent& DM_Evt = input.genDarkMatterEvt;
        math::XYZTLorentzVector   WBoson = DM_Evt.ReturnWBoson();
        vars.FillVar("W_Pt", WBoson.Pt());
        vars.FillVar("W_Phi", WBoson.Phi());
        vars.FillVar("W_Eta", WBoson.Eta());
        vars.FillVar("W_Energy", WBoson.E());
        vars.FillVar("W_Mass", WBoson.M());
    }

    if (input.genDarkMatterEvt.ZBosonIsFilled()) {
        // std::cout << "Z boson!" << std::endl;
        const GenDarkMatterEvent& DM_Evt = input.genDarkMatterEvt;
        math::XYZTLorentzVector   ZBoson = DM_Evt.ReturnZBoson();
        vars.FillVar("Z_Pt", ZBoson.Pt());
        vars.FillVar("Z_Phi", ZBoson.Phi());
        vars.FillVar("Z_Eta", ZBoson.Eta());
        vars.FillVar("Z_Energy", ZBoson.E());
        vars.FillVar("Z_Mass", ZBoson.M());
    }

    if (input.genDarkMatterEvt.PhotonIsFilled()) {
        const GenDarkMatterEvent& DM_Evt = input.genDarkMatterEvt;
        math::XYZTLorentzVector   Gamma  = DM_Evt.ReturnPhoton();
        vars.FillVar("Gamma_Pt", Gamma.Pt());
        vars.FillVar("Gamma_Phi", Gamma.Phi());
        vars.FillVar("Gamma_Eta", Gamma.Eta());
        vars.FillVar("Gamma_Energy", Gamma.E());
        vars.FillVar("Gamma_Mass", Gamma.M());
    }

    //         vars.FillVar("Zmumu_Pt_Hadr_Recoil_Pt_ratio", fabs(Zmumu.Pt() - hadr_recoil_p4.pt()) / hadr_recoil_p4.pt());

    // get and fill some gen level information
    if (input.genDarkMatterEvt.IsFilled()) {
        const GenDarkMatterEvent& DM_Evt = input.genDarkMatterEvt;

        TLorentzVector                Mediator_p4    = DM_Evt.ReturnMediator4Vector();
        TLorentzVector                NaiveMET_p4    = DM_Evt.ReturnNaiveMET4Vector();
        std::vector< TLorentzVector > Neutralinos_p4 = DM_Evt.ReturnNeutralino4Vectors();
        std::vector< TLorentzVector > Neutrinos_p4   = DM_Evt.ReturnNeutrino4Vectors();

        vars.FillVar("N_Neutralinos", Neutralinos_p4.size());
        vars.FillVar("N_Neutrinos", Neutrinos_p4.size());

        vars.FillVar("NaiveMET", DM_Evt.ReturnNaiveMET());

        vars.FillVar("Mediator_Mass", Mediator_p4.M());
        vars.FillVar("Mediator_Pt", Mediator_p4.Pt());
        vars.FillVar("Mediator_Phi", Mediator_p4.Phi());
        vars.FillVar("Mediator_Eta", Mediator_p4.Eta());
        vars.FillVar("Mediator_Energy", Mediator_p4.E());
        vars.FillVar("Mediator_Px", Mediator_p4.Px());
        vars.FillVar("Mediator_Py", Mediator_p4.Py());
        vars.FillVar("Mediator_Pz", Mediator_p4.Pz());

        for (std::vector< TLorentzVector >::const_iterator itNeutralino = Neutralinos_p4.begin(); itNeutralino != Neutralinos_p4.end(); ++itNeutralino) {
            int iNeutralino = itNeutralino - Neutralinos_p4.begin();
            vars.FillVars("Neutralino_Mass", iNeutralino, itNeutralino->M());
            vars.FillVars("Neutralino_Pt", iNeutralino, itNeutralino->Pt());
            vars.FillVars("Neutralino_Phi", iNeutralino, itNeutralino->Phi());
            vars.FillVars("Neutralino_Eta", iNeutralino, itNeutralino->Eta());
            vars.FillVars("Neutralino_Energy", iNeutralino, itNeutralino->E());
            vars.FillVars("Neutralino_Px", iNeutralino, itNeutralino->Px());
            vars.FillVars("Neutralino_Py", iNeutralino, itNeutralino->Py());
            vars.FillVars("Neutralino_Pz", iNeutralino, itNeutralino->Pz());
        }

        if (Neutralinos_p4.size() >= 2) {
            vars.FillVar("N1_N2_Mass", (Neutralinos_p4[0] + Neutralinos_p4[1]).M());
            vars.FillVar("N1_N2_Pt", (Neutralinos_p4[0] + Neutralinos_p4[1]).Pt());
            vars.FillVar("N1_N2_Phi", (Neutralinos_p4[0] + Neutralinos_p4[1]).Phi());
            vars.FillVar("N1_N2_Eta", (Neutralinos_p4[0] + Neutralinos_p4[1]).Eta());
            vars.FillVar("N1_N2_Energy", (Neutralinos_p4[0] + Neutralinos_p4[1]).E());
            vars.FillVar("N1_N2_Px", (Neutralinos_p4[0] + Neutralinos_p4[1]).Px());
            vars.FillVar("N1_N2_Py", (Neutralinos_p4[0] + Neutralinos_p4[1]).Py());
            vars.FillVar("N1_N2_Pz", (Neutralinos_p4[0] + Neutralinos_p4[1]).Pz());

            vars.FillVar("cos_theta_N1_N2", TMath::Cos((Neutralinos_p4[0].Vect()).Angle(Neutralinos_p4[1].Vect())));
            vars.FillVar("cos_theta_Med_N1", TMath::Cos((Neutralinos_p4[0].Vect()).Angle(Mediator_p4.Vect())));
            vars.FillVar("cos_theta_Med_N2", TMath::Cos((Neutralinos_p4[1].Vect()).Angle(Mediator_p4.Vect())));

            vars.FillVar("delta_phi_N1_N2", Neutralinos_p4[0].DeltaPhi(Neutralinos_p4[1]));
            vars.FillVar("delta_phi_Med_N1", Mediator_p4.DeltaPhi(Neutralinos_p4[0]));
            vars.FillVar("delta_phi_Med_N2", Mediator_p4.DeltaPhi(Neutralinos_p4[1]));

            vars.FillVar("delta_R_N1_N2", Neutralinos_p4[0].DeltaR(Neutralinos_p4[1]));
            vars.FillVar("delta_R_Med_N1", Mediator_p4.DeltaR(Neutralinos_p4[0]));
            vars.FillVar("delta_R_Med_N2", Mediator_p4.DeltaR(Neutralinos_p4[1]));
        }

        for (std::vector< TLorentzVector >::const_iterator itNeutrino = Neutrinos_p4.begin(); itNeutrino != Neutrinos_p4.end(); ++itNeutrino) {
            int iNeutrino = itNeutrino - Neutrinos_p4.begin();
            vars.FillVars("Neutrino_Mass", iNeutrino, itNeutrino->M());
            vars.FillVars("Neutrino_Pt", iNeutrino, itNeutrino->Pt());
            vars.FillVars("Neutrino_Phi", iNeutrino, itNeutrino->Phi());
            vars.FillVars("Neutrino_Eta", iNeutrino, itNeutrino->Eta());
            vars.FillVars("Neutrino_Energy", iNeutrino, itNeutrino->E());
            vars.FillVars("Neutrino_Px", iNeutrino, itNeutrino->Px());
            vars.FillVars("Neutrino_Py", iNeutrino, itNeutrino->Py());
            vars.FillVars("Neutrino_Pz", iNeutrino, itNeutrino->Pz());
        }
    }
}
