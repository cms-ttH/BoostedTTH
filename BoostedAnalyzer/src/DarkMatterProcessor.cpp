#include "BoostedTTH/BoostedAnalyzer/interface/DarkMatterProcessor.hpp"

using namespace std;

DarkMatterProcessor::DarkMatterProcessor() {}
DarkMatterProcessor::~DarkMatterProcessor() {}

void DarkMatterProcessor::Init(const InputCollections& input, VariableContainer& vars)
{
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
    vars.InitVar("NaiveMET");
    vars.InitVar("Hadr_Recoil_Pt");
    vars.InitVar("Hadr_Recoil_Phi");
    vars.InitVar("Gen_Hadr_Recoil_Pt");
    vars.InitVar("Gen_Hadr_Recoil_Phi");
    vars.InitVar("CaloMET_Hadr_Recoil_ratio");

    vars.InitVars("DeltaPhi_AK4Jet_MET", "N_Jets");
    vars.InitVars("DeltaPhi_AK4Jet_Hadr_Recoil", "N_Jets");
    vars.InitVars("DeltaPhi_AK8Jet_MET", "N_AK8Jets");
    vars.InitVars("DeltaPhi_AK8Jet_Hadr_Recoil", "N_AK8Jets");
    vars.InitVars("DeltaPhi_AK15Jet_MET", "N_AK15Jets");
    vars.InitVars("DeltaPhi_AK15Jet_Hadr_Recoil", "N_AK15Jets");

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

    //     vars.InitVar("Zmumu_Pt_Hadr_Recoil_Pt_ratio");

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

    vars.FillVar("Evt_Pt_MET", met_p4.pt());
    vars.FillVar("Evt_Phi_MET", met_p4.phi());
    vars.FillVar("Evt_Pt_MET_T1XY", input.correctedMETPuppi.corPt(pat::MET::Type1XY));
    vars.FillVar("Evt_Phi_MET_T1XY", input.correctedMETPuppi.corPhi(pat::MET::Type1XY));
    vars.FillVar("Evt_Pt_MET_UnclEnUp", input.correctedMETPuppi.shiftedPt(pat::MET::UnclusteredEnUp, pat::MET::Type1));
    vars.FillVar("Evt_Pt_MET_UnclEnDown", input.correctedMETPuppi.shiftedPt(pat::MET::UnclusteredEnDown, pat::MET::Type1));
    vars.FillVar("CaloMET", input.correctedMETPuppi.caloMETPt());
    vars.FillVar("CaloMET_PFMET_ratio", fabs(met_p4.pt() - input.correctedMETPuppi.caloMETPt()) / input.correctedMETPuppi.caloMETPt());

    for (size_t i = 0; i < input.selectedJets.size(); i++) {
        vars.FillVars("DeltaPhi_AK4Jet_MET", i, fabs(TVector2::Phi_mpi_pi(met_p4.phi() - input.selectedJets.at(i).phi())));
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

    for (size_t i = 0; i < input.selectedJets.size(); i++) {
        vars.FillVars("DeltaPhi_AK4Jet_Hadr_Recoil", i, fabs(TVector2::Phi_mpi_pi(hadr_recoil_p4.phi() - input.selectedJets.at(i).phi())));
    }
    for (size_t i = 0; i < input.selectedJetsAK8.size(); i++) {
        vars.FillVars("DeltaPhi_AK8Jet_Hadr_Recoil", i, fabs(TVector2::Phi_mpi_pi(hadr_recoil_p4.phi() - input.selectedJetsAK8.at(i).phi())));
    }
    for (size_t i = 0; i < input.selectedJetsAK15.size(); i++) {
        vars.FillVars("DeltaPhi_AK15Jet_Hadr_Recoil", i, fabs(TVector2::Phi_mpi_pi(hadr_recoil_p4.phi() - input.selectedJetsAK15.at(i).phi())));
    }

    // get particle-level W/Z pt for later usage in V boson reweighting
    if (input.genDarkMatterEvt.WBosonIsFilled()) {
        const GenDarkMatterEvent& DM_Evt = input.genDarkMatterEvt;
        math::XYZTLorentzVector   WBoson = DM_Evt.ReturnWBoson();
        vars.FillVar("W_Pt", WBoson.Pt());
        vars.FillVar("W_Phi", WBoson.Phi());
        vars.FillVar("W_Eta", WBoson.Eta());
        vars.FillVar("W_Energy", WBoson.E());
        vars.FillVar("W_Mass", WBoson.M());
    }

    if (input.genDarkMatterEvt.ZBosonIsFilled()) {
        const GenDarkMatterEvent& DM_Evt = input.genDarkMatterEvt;
        math::XYZTLorentzVector   ZBoson = DM_Evt.ReturnZBoson();
        vars.FillVar("Z_Pt", ZBoson.Pt());
        vars.FillVar("Z_Phi", ZBoson.Phi());
        vars.FillVar("Z_Eta", ZBoson.Eta());
        vars.FillVar("Z_Energy", ZBoson.E());
        vars.FillVar("Z_Mass", ZBoson.M());
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
