#include "BoostedTTH/BoostedAnalyzer/interface/JetVarProcessor.hpp"

using namespace std;

JetVarProcessor::JetVarProcessor() {}
JetVarProcessor::~JetVarProcessor() {}

void JetVarProcessor::Init(const InputCollections& input, VariableContainer& vars)
{
    // load dataEra
    era = input.era;

    /*
    vars.InitVar("N_AK8Jets", "I");

    vars.InitVars("AK8Jet_Pt", "N_AK8Jets");
    vars.InitVars("AK8Jet_Eta", "N_AK8Jets");
    vars.InitVars("AK8Jet_Phi", "N_AK8Jets");
    vars.InitVars("AK8Jet_E", "N_AK8Jets");
    vars.InitVars("AK8Jet_M", "N_AK8Jets");

    vars.InitVars("AK8Jet_CHF", "N_AK8Jets");
    vars.InitVars("AK8Jet_NHF", "N_AK8Jets");
    vars.InitVars("AK8Jet_NEMF", "N_AK8Jets");
    vars.InitVars("AK8Jet_CEMF", "N_AK8Jets");
    vars.InitVars("AK8Jet_MF", "N_AK8Jets");

    vars.InitVars("AK8Jet_Njettiness_tau1", "N_AK8Jets");
    vars.InitVars("AK8Jet_Njettiness_tau2", "N_AK8Jets");
    vars.InitVars("AK8Jet_Njettiness_tau3", "N_AK8Jets");
    vars.InitVars("AK8Jet_Njettiness_tau4", "N_AK8Jets");
    vars.InitVars("AK8Jet_PuppiSoftDropMass", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_TvsQCD", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probTbcq", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probTbqq", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probTbc", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probTbq", "N_AK8Jets");

    vars.InitVars("AK8Jet_DeepAK8_probWcq", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probWqq", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probZbb", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probZcc", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probZqq", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probQCDbb", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probQCDb", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probQCDcc", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probQCDc", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_probQCDothers", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_WvsQCD", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_ZvsQCD", "N_AK8Jets");

    vars.InitVar("N_AK8Jets_SoftDrop", "I");
    vars.InitVars("AK8Jet_N_SoftDropSubjets", "N_AK8Jets");
    vars.InitVars("AK8Jet_N_BTaggedSoftDropSubjets", "N_AK8Jets");
    vars.InitVars("AK8Jet_N_LooseBTaggedSoftDropSubjets", "N_AK8Jets");
    vars.InitVars("AK8Jet_N_TightBTaggedSoftDropSubjets", "N_AK8Jets");

    vars.InitVars("AK8Jet_SoftDropJet1_Pt", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet1_Eta", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet1_Phi", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet1_E", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet1_M", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet1_DeepJetCSV", "N_AK8Jets");

    vars.InitVars("AK8Jet_SoftDropJet2_Pt", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet2_Eta", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet2_Phi", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet2_E", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet2_M", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet2_DeepJetCSV", "N_AK8Jets");

    vars.InitVars("AK8Jet_SoftDropJet3_Pt", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet3_Eta", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet3_Phi", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet3_E", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet3_M", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDropJet3_DeepJetCSV", "N_AK8Jets");

    vars.InitVars("AK8Jet_SoftDrop_Pt", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDrop_Eta", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDrop_Phi", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDrop_E", "N_AK8Jets");
    vars.InitVars("AK8Jet_SoftDrop_M", "N_AK8Jets");

    vars.InitVar("N_AK8Jets_x_N_Jets", "I");
    vars.InitVar("N_AK8Jets_x_N_JetsTagged", "I");
    vars.InitVar("N_AK8Jets_x_N_JetsLooseTagged", "I");
    vars.InitVar("N_AK8Jets_x_N_JetsTightTagged", "I");
    vars.InitVar("N_AK4JetsTagged_outside_AK8Jets", "I");
    vars.InitVar("N_AK4JetsLooseTagged_outside_AK8Jets", "I");
    vars.InitVar("N_AK4JetsTightTagged_outside_AK8Jets", "I");
    vars.InitVar("N_AK4JetsTagged_inside_AK8Jets", "I");
    vars.InitVar("N_AK4JetsLooseTagged_inside_AK8Jets", "I");
    vars.InitVar("N_AK4JetsTightTagged_inside_AK8Jets", "I");
    vars.InitVars("DeltaR_AK8Jet_AK4Jet", "N_AK8Jets_x_N_Jets");
    vars.InitVars("DeltaR_AK8Jet_AK4JetTagged", "N_AK8Jets_x_N_JetsTagged");
    vars.InitVars("DeltaR_AK8Jet_AK4JetLooseTagged", "N_AK8Jets_x_N_JetsLooseTagged");
    vars.InitVars("DeltaR_AK8Jet_AK4JetTightTagged", "N_AK8Jets_x_N_JetsTightTagged");

    vars.InitVar("N_HEM_AK8Jets", "I");
    */

    // vars.InitVar("N_AK15Jets", "I");
    vars.InitVars("AK15Jet_Pt", "N_AK15Jets");
    vars.InitVars("AK15Jet_Eta", "N_AK15Jets");
    vars.InitVars("AK15Jet_Phi", "N_AK15Jets");
    vars.InitVars("AK15Jet_E", "N_AK15Jets");
    vars.InitVars("AK15Jet_M", "N_AK15Jets");

    vars.InitVars("AK15Jet_CHF", "N_AK15Jets");
    vars.InitVars("AK15Jet_NHF", "N_AK15Jets");
    vars.InitVars("AK15Jet_NEMF", "N_AK15Jets");
    vars.InitVars("AK15Jet_CEMF", "N_AK15Jets");
    vars.InitVars("AK15Jet_MF", "N_AK15Jets");
    vars.InitVars("AK15Jet_Puppi_Multiplicity", "N_AK15Jets");
    vars.InitVars("AK15Jet_Puppi_NeutralMultiplicity", "N_AK15Jets");

    vars.InitVars("AK15Jet_Njettiness_tau1", "N_AK15Jets");
    vars.InitVars("AK15Jet_Njettiness_tau2", "N_AK15Jets");
    vars.InitVars("AK15Jet_Njettiness_tau3", "N_AK15Jets");
    vars.InitVars("AK15Jet_Njettiness_tau4", "N_AK15Jets");
    vars.InitVars("AK15Jet_PuppiSoftDropMass", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_TvsQCD", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probTbcq", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probTbqq", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probTbc", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probTbq", "N_AK15Jets");

    vars.InitVars("AK15Jet_DeepAK15_probWcq", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probWqq", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probZbb", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probZcc", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probZqq", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probQCDbb", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probQCDcc", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probQCDc", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probQCDb", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_probQCDothers", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_WvsQCD", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_ZvsQCD", "N_AK15Jets");

    vars.InitVar("N_AK15Jets_SoftDrop", "I");
    vars.InitVars("AK15Jet_N_SoftDropSubjets", "N_AK15Jets");
    vars.InitVars("AK15Jet_N_BTaggedSoftDropSubjets", "N_AK15Jets");
    vars.InitVars("AK15Jet_N_LooseBTaggedSoftDropSubjets", "N_AK15Jets");
    vars.InitVars("AK15Jet_N_TightBTaggedSoftDropSubjets", "N_AK15Jets");

    vars.InitVars("AK15Jet_SoftDropJet1_Pt", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet1_Eta", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet1_Phi", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet1_E", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet1_M", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet1_DeepJetCSV", "N_AK15Jets");

    vars.InitVars("AK15Jet_SoftDropJet2_Pt", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet2_Eta", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet2_Phi", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet2_E", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet2_M", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet2_DeepJetCSV", "N_AK15Jets");

    vars.InitVars("AK15Jet_SoftDrop_Pt", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDrop_Eta", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDrop_Phi", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDrop_E", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDrop_M", "N_AK15Jets");

    vars.InitVars("AK15Jet_SoftDropJet3_Pt", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet3_Eta", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet3_Phi", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet3_E", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet3_M", "N_AK15Jets");
    vars.InitVars("AK15Jet_SoftDropJet3_DeepJetCSV", "N_AK15Jets");

    vars.InitVar("N_AK15Jets_x_N_Jets", "I");
    vars.InitVar("N_AK15Jets_x_N_JetsTagged", "I");
    vars.InitVar("N_AK15Jets_x_N_JetsLooseTagged", "I");
    vars.InitVar("N_AK15Jets_x_N_JetsTightTagged", "I");
    vars.InitVar("N_AK4JetsTagged_outside_AK15Jets", "I");
    vars.InitVar("N_AK4JetsLooseTagged_outside_AK15Jets", "I");
    vars.InitVar("N_AK4JetsTightTagged_outside_AK15Jets", "I");
    vars.InitVar("N_AK4JetsTagged_inside_AK15Jets", "I");
    vars.InitVar("N_AK4JetsLooseTagged_inside_AK15Jets", "I");
    vars.InitVar("N_AK4JetsTightTagged_inside_AK15Jets", "I");
    vars.InitVars("DeltaR_AK15Jet_AK4Jet", "N_AK15Jets_x_N_Jets");
    vars.InitVars("DeltaR_AK15Jet_AK4JetTagged", "N_AK15Jets_x_N_JetsTagged");
    vars.InitVars("DeltaR_AK15Jet_AK4JetLooseTagged", "N_AK15Jets_x_N_JetsLooseTagged");
    vars.InitVars("DeltaR_AK15Jet_AK4JetTightTagged", "N_AK15Jets_x_N_JetsTightTagged");

    vars.InitVars("AK15Jet_TopMatched", "N_AK15Jets");
    vars.InitVars("Min_DeltaR_AK15Jet_GenTopHad", "N_AK15Jets");

    vars.InitVar("N_HEM_AK15Jets", "I");

    initialized = true;
}

void JetVarProcessor::Process(const InputCollections& input, VariableContainer& vars)
{
    if (!initialized) cerr << "JetVarProcessor not initialized" << endl;

    const auto& ak4jets = input.selectedJets;

    std::vector< pat::Jet > ak4jets_tagged;
    std::vector< pat::Jet > ak4jets_loose_tagged;
    std::vector< pat::Jet > ak4jets_tight_tagged;
    for (const auto& ak4jet : ak4jets) {
        if (CSVHelper::PassesCSV(ak4jet, "DeepJet", CSVHelper::CSVwp::Medium, era)) ak4jets_tagged.push_back(ak4jet);
        if (CSVHelper::PassesCSV(ak4jet, "DeepJet", CSVHelper::CSVwp::Loose, era)) ak4jets_loose_tagged.push_back(ak4jet);
        if (CSVHelper::PassesCSV(ak4jet, "DeepJet", CSVHelper::CSVwp::Tight, era)) ak4jets_tight_tagged.push_back(ak4jet);
    }

    /*
    int n_AK4JetsTagged_outside_AK8Jets      = 0;
    int n_AK4JetsLooseTagged_outside_AK8Jets = 0;
    int n_AK4JetsTightTagged_outside_AK8Jets = 0;
    int n_AK4JetsTagged_inside_AK8Jets       = 0;
    int n_AK4JetsLooseTagged_inside_AK8Jets  = 0;
    int n_AK4JetsTightTagged_inside_AK8Jets  = 0;
    int N_HEM_AK8Jets                        = 0;
    int n_AK8_SoftDrop_Jets                  = 0;

    const auto& ak8jets = input.selectedJetsAK8;

    // vars.FillVar("N_AK8Jets", ak8jets.size());
    vars.FillVar("N_AK8Jets_x_N_Jets", ak8jets.size() * ak4jets.size());
    vars.FillVar("N_AK8Jets_x_N_JetsTagged", ak8jets.size() * ak4jets_tagged.size());
    vars.FillVar("N_AK8Jets_x_N_JetsLooseTagged", ak8jets.size() * ak4jets_loose_tagged.size());
    vars.FillVar("N_AK8Jets_x_N_JetsTightTagged", ak8jets.size() * ak4jets_tight_tagged.size());
    for (size_t i = 0; i < ak8jets.size(); i++) {
        const auto& ak8jet = ak8jets.at(i);
        vars.FillVars("AK8Jet_Pt", i, ak8jet.pt());
        vars.FillVars("AK8Jet_Eta", i, ak8jet.eta());
        vars.FillVars("AK8Jet_Phi", i, ak8jet.phi());
        vars.FillVars("AK8Jet_E", i, ak8jet.energy());
        vars.FillVars("AK8Jet_M", i, ak8jet.mass());
        if (ak8jet.hasUserFloat("chargedHadronEnergyFraction")) { vars.FillVars("AK8Jet_CHF", i, ak8jet.userFloat("chargedHadronEnergyFraction")); }
        if (ak8jet.hasUserFloat("neutralHadronEnergyFraction")) { vars.FillVars("AK8Jet_NHF", i, ak8jet.userFloat("neutralHadronEnergyFraction")); }
        if (ak8jet.hasUserFloat("neutralElectromagneticEnergyFraction")) {
            vars.FillVars("AK8Jet_NEMF", i, ak8jet.userFloat("neutralElectromagneticEnergyFraction"));
        }
        if (ak8jet.hasUserFloat("chargedElectromagneticEnergyFraction")) {
            vars.FillVars("AK8Jet_CEMF", i, ak8jet.userFloat("chargedElectromagneticEnergyFraction"));
        }
        if (ak8jet.hasUserFloat("muonEnergyFraction")) { vars.FillVars("AK8Jet_MF", i, ak8jet.userFloat("muonEnergyFraction")); }
        if (ak8jet.hasUserFloat("NjettinessAK8Puppi:tau1")) { vars.FillVars("AK8Jet_Njettiness_tau1", i, ak8jet.userFloat("NjettinessAK8Puppi:tau1")); }
        if (ak8jet.hasUserFloat("NjettinessAK8Puppi:tau2")) { vars.FillVars("AK8Jet_Njettiness_tau2", i, ak8jet.userFloat("NjettinessAK8Puppi:tau2")); }
        if (ak8jet.hasUserFloat("NjettinessAK8Puppi:tau3")) { vars.FillVars("AK8Jet_Njettiness_tau3", i, ak8jet.userFloat("NjettinessAK8Puppi:tau3")); }
        if (ak8jet.hasUserFloat("NjettinessAK8Puppi:tau4")) { vars.FillVars("AK8Jet_Njettiness_tau4", i, ak8jet.userFloat("NjettinessAK8Puppi:tau4")); }
        if (ak8jet.hasUserFloat("ak8PFJetsPuppiSoftDropMass")) { vars.FillVars("AK8Jet_PuppiSoftDropMass", i, ak8jet.userFloat("ak8PFJetsPuppiSoftDropMass")); }
        vars.FillVars("AK8Jet_DeepAK8_TvsQCD", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:TvsQCD"));
        vars.FillVars("AK8Jet_DeepAK8_probTbcq", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probTbcq"));
        vars.FillVars("AK8Jet_DeepAK8_probTbqq", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probTbqq"));
        vars.FillVars("AK8Jet_DeepAK8_probTbc", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probTbc"));
        vars.FillVars("AK8Jet_DeepAK8_probTbq", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probTbq"));

        vars.FillVars("AK8Jet_DeepAK8_probWcq", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probWcq"));
        vars.FillVars("AK8Jet_DeepAK8_probWqq", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probWqq"));
        vars.FillVars("AK8Jet_DeepAK8_probZbb", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probZbb"));
        vars.FillVars("AK8Jet_DeepAK8_probZcc", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probZcc"));
        vars.FillVars("AK8Jet_DeepAK8_probZqq", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:propZqq"));
        vars.FillVars("AK8Jet_DeepAK8_probQCDbb", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probQCDbb"));
        vars.FillVars("AK8Jet_DeepAK8_probQCDb", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probQCDb"));
        vars.FillVars("AK8Jet_DeepAK8_probQCDcc", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probQCDcc"));
        vars.FillVars("AK8Jet_DeepAK8_probQCDc", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probQCDc"));
        vars.FillVars("AK8Jet_DeepAK8_probQCDothers", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probQCDothers"));
        vars.FillVars("AK8Jet_DeepAK8_WvsQCD", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:WvsQCD"));
        vars.FillVars("AK8Jet_DeepAK8_ZvsQCD", i, ak8jet.bDiscriminator("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:ZvsQCD"));

        if (ak8jet.hasSubjets("SoftDropWithBtagInfo")) {
            const auto& ak8jet_subjets = ak8jet.subjets("SoftDropWithBtagInfo");

            vars.FillVars("AK8Jet_N_SoftDropSubjets", i, ak8jet_subjets.size());

            if (ak8jet_subjets.size() > 0) n_AK8_SoftDrop_Jets += 1;

            int n_btagged_softdropsubjets      = 0;
            int n_loosebtagged_softdropsubjets = 0;
            int n_tightbtagged_softdropsubjets = 0;

            math::XYZTLorentzVector ak8jet_softdrop(0., 0., 0., 0.);

            for (size_t j = 0; j < ak8jet_subjets.size() && j < 3; j++) {
                const auto& ak8jet_subjet = *ak8jet_subjets.at(j);
                vars.FillVars("AK8Jet_SoftDropJet" + std::to_string(j + 1) + "_Pt", i, ak8jet_subjet.pt());
                vars.FillVars("AK8Jet_SoftDropJet" + std::to_string(j + 1) + "_Eta", i, ak8jet_subjet.eta());
                vars.FillVars("AK8Jet_SoftDropJet" + std::to_string(j + 1) + "_Phi", i, ak8jet_subjet.phi());
                vars.FillVars("AK8Jet_SoftDropJet" + std::to_string(j + 1) + "_E", i, ak8jet_subjet.energy());
                vars.FillVars("AK8Jet_SoftDropJet" + std::to_string(j + 1) + "_M", i, ak8jet_subjet.mass());
                vars.FillVars("AK8Jet_SoftDropJet" + std::to_string(j + 1) + "_DeepJetCSV", i, CSVHelper::GetJetCSV_DNN(ak8jet_subjet, "DeepJet"));
                if (CSVHelper::PassesCSV(ak8jet_subjet, "DeepJet", CSVHelper::CSVwp::Medium, era)) n_btagged_softdropsubjets += 1;
                if (CSVHelper::PassesCSV(ak8jet_subjet, "DeepJet", CSVHelper::CSVwp::Loose, era)) n_loosebtagged_softdropsubjets += 1;
                if (CSVHelper::PassesCSV(ak8jet_subjet, "DeepJet", CSVHelper::CSVwp::Tight, era)) n_tightbtagged_softdropsubjets += 1;
                ak8jet_softdrop += ak8jet_subjet.p4();
            }

            vars.FillVars("AK8Jet_N_BTaggedSoftDropSubjets", i, n_btagged_softdropsubjets);
            vars.FillVars("AK8Jet_N_LooseBTaggedSoftDropSubjets", i, n_loosebtagged_softdropsubjets);
            vars.FillVars("AK8Jet_N_TightBTaggedSoftDropSubjets", i, n_tightbtagged_softdropsubjets);

            vars.FillVars("AK8Jet_SoftDrop_Pt", i, ak8jet_softdrop.pt());
            vars.FillVars("AK8Jet_SoftDrop_Eta", i, ak8jet_softdrop.eta());
            vars.FillVars("AK8Jet_SoftDrop_Phi", i, ak8jet_softdrop.phi());
            vars.FillVars("AK8Jet_SoftDrop_E", i, ak8jet_softdrop.energy());
            vars.FillVars("AK8Jet_SoftDrop_M", i, ak8jet_softdrop.mass());
        }

        for (size_t k = 0; k < ak4jets.size(); k++) {
            const auto& ak4jet = ak4jets.at(k);
            vars.FillVars("DeltaR_AK8Jet_AK4Jet", i * ak4jets.size() + k, BoostedUtils::DeltaR(ak8jet.p4(), ak4jet.p4()));
        }

        for (size_t k = 0; k < ak4jets_tagged.size(); k++) {
            const auto& ak4jet_tagged           = ak4jets_tagged.at(k);
            const auto  dR_ak8jet_ak4jet_tagged = BoostedUtils::DeltaR(ak8jet.p4(), ak4jet_tagged.p4());
            vars.FillVars("DeltaR_AK8Jet_AK4JetTagged", i * ak4jets_tagged.size() + k, BoostedUtils::DeltaR(ak8jet.p4(), ak4jet_tagged.p4()));
            if (dR_ak8jet_ak4jet_tagged > 0.8)
                n_AK4JetsTagged_outside_AK8Jets += 1;
            else
                n_AK4JetsTagged_inside_AK8Jets += 1;
        }
        for (size_t k = 0; k < ak4jets_loose_tagged.size(); k++) {
            const auto& ak4jet_loose_tagged           = ak4jets_loose_tagged.at(k);
            const auto  dR_ak8jet_ak4jet_loose_tagged = BoostedUtils::DeltaR(ak8jet.p4(), ak4jet_loose_tagged.p4());
            vars.FillVars("DeltaR_AK8Jet_AK4JetLooseTagged", i * ak4jets_loose_tagged.size() + k, BoostedUtils::DeltaR(ak8jet.p4(), ak4jet_loose_tagged.p4()));
            if (dR_ak8jet_ak4jet_loose_tagged > 0.8)
                n_AK4JetsLooseTagged_outside_AK8Jets += 1;
            else
                n_AK4JetsLooseTagged_inside_AK8Jets += 1;
        }
        for (size_t k = 0; k < ak4jets_tight_tagged.size(); k++) {
            const auto& ak4jet_tight_tagged           = ak4jets_tight_tagged.at(k);
            const auto  dR_ak8jet_ak4jet_tight_tagged = BoostedUtils::DeltaR(ak8jet.p4(), ak4jet_tight_tagged.p4());
            vars.FillVars("DeltaR_AK8Jet_AK4JetTightTagged", i * ak4jets_tight_tagged.size() + k, BoostedUtils::DeltaR(ak8jet.p4(), ak4jet_tight_tagged.p4()));
            if (dR_ak8jet_ak4jet_tight_tagged > 0.8)
                n_AK4JetsTightTagged_outside_AK8Jets += 1;
            else
                n_AK4JetsTightTagged_inside_AK8Jets += 1;
        }

        if (ak8jet.eta() < -1.4 && ak8jet.eta() > -3.0 && ak8jet.phi() < -0.87 && ak8jet.phi() > -1.57) N_HEM_AK8Jets += 1;
    }
    vars.FillVar("N_AK4JetsTagged_outside_AK8Jets", n_AK4JetsTagged_outside_AK8Jets);
    vars.FillVar("N_AK4JetsLooseTagged_outside_AK8Jets", n_AK4JetsLooseTagged_outside_AK8Jets);
    vars.FillVar("N_AK4JetsTightTagged_outside_AK8Jets", n_AK4JetsTightTagged_outside_AK8Jets);
    vars.FillVar("N_AK4JetsTagged_inside_AK8Jets", n_AK4JetsTagged_inside_AK8Jets);
    vars.FillVar("N_AK4JetsLooseTagged_inside_AK8Jets", n_AK4JetsLooseTagged_inside_AK8Jets);
    vars.FillVar("N_AK4JetsTightTagged_inside_AK8Jets", n_AK4JetsTightTagged_inside_AK8Jets);
    vars.FillVar("N_AK8Jets_SoftDrop", n_AK8_SoftDrop_Jets);
    vars.FillVar("N_HEM_AK8Jets", N_HEM_AK8Jets);
    */

    int n_AK4JetsTagged_outside_AK15Jets      = 0;
    int n_AK4JetsLooseTagged_outside_AK15Jets = 0;
    int n_AK4JetsTightTagged_outside_AK15Jets = 0;
    int n_AK4JetsTagged_inside_AK15Jets       = 0;
    int n_AK4JetsLooseTagged_inside_AK15Jets  = 0;
    int n_AK4JetsTightTagged_inside_AK15Jets  = 0;
    int N_HEM_AK15Jets                        = 0;
    int n_AK15_SoftDrop_Jets                  = 0;

    const auto& ak15jets = input.selectedJetsAK15;

    // vars.FillVar("N_AK15Jets", ak15jets.size());
    vars.FillVar("N_AK15Jets_x_N_Jets", ak15jets.size() * ak4jets.size());
    vars.FillVar("N_AK15Jets_x_N_JetsTagged", ak15jets.size() * ak4jets_tagged.size());
    vars.FillVar("N_AK15Jets_x_N_JetsLooseTagged", ak15jets.size() * ak4jets_loose_tagged.size());
    vars.FillVar("N_AK15Jets_x_N_JetsTightTagged", ak15jets.size() * ak4jets_tight_tagged.size());
    for (size_t i = 0; i < ak15jets.size(); i++) {
        const auto& ak15jet = ak15jets.at(i);
        vars.FillVars("AK15Jet_Pt", i, ak15jet.pt());
        vars.FillVars("AK15Jet_Eta", i, ak15jet.eta());
        vars.FillVars("AK15Jet_Phi", i, ak15jet.phi());
        vars.FillVars("AK15Jet_E", i, ak15jet.energy());
        vars.FillVars("AK15Jet_M", i, ak15jet.mass());
        if (ak15jet.hasUserFloat("chargedHadronEnergyFraction")) { vars.FillVars("AK15Jet_CHF", i, ak15jet.userFloat("chargedHadronEnergyFraction")); }
        if (ak15jet.hasUserFloat("neutralHadronEnergyFraction")) { vars.FillVars("AK15Jet_NHF", i, ak15jet.userFloat("neutralHadronEnergyFraction")); }
        if (ak15jet.hasUserFloat("neutralElectromagneticEnergyFraction")) {
            vars.FillVars("AK15Jet_NEMF", i, ak15jet.userFloat("neutralElectromagneticEnergyFraction"));
        }
        if (ak15jet.hasUserFloat("chargedElectromagneticEnergyFraction")) {
            vars.FillVars("AK15Jet_CEMF", i, ak15jet.userFloat("chargedElectromagneticEnergyFraction"));
        }
        if (ak15jet.hasUserFloat("muonEnergyFraction")) { vars.FillVars("AK15Jet_MF", i, ak15jet.userFloat("muonEnergyFraction")); }
        if (ak15jet.hasUserFloat("patPuppiJetSpecificProducer:puppiMultiplicity")) {
            vars.FillVars("AK15Jet_Puppi_Multiplicity", i, ak15jet.userFloat("patPuppiJetSpecificProducer:puppiMultiplicity"));
        }
        if (ak15jet.hasUserFloat("patPuppiJetSpecificProducer:neutralPuppiMultiplicity")) {
            vars.FillVars("AK15Jet_Puppi_NeutralMultiplicity", i, ak15jet.userFloat("patPuppiJetSpecificProducer:neutralPuppiMultiplicity"));
        }

        if (ak15jet.hasUserFloat("NjettinessAK15Puppi:tau1")) { vars.FillVars("AK15Jet_Njettiness_tau1", i, ak15jet.userFloat("NjettinessAK15Puppi:tau1")); }
        if (ak15jet.hasUserFloat("NjettinessAK15Puppi:tau2")) { vars.FillVars("AK15Jet_Njettiness_tau2", i, ak15jet.userFloat("NjettinessAK15Puppi:tau2")); }
        if (ak15jet.hasUserFloat("NjettinessAK15Puppi:tau3")) { vars.FillVars("AK15Jet_Njettiness_tau3", i, ak15jet.userFloat("NjettinessAK15Puppi:tau3")); }
        if (ak15jet.hasUserFloat("NjettinessAK15Puppi:tau4")) { vars.FillVars("AK15Jet_Njettiness_tau4", i, ak15jet.userFloat("NjettinessAK15Puppi:tau4")); }
        if (ak15jet.hasUserFloat("ak15PFJetsPuppiSoftDropMass")) {
            vars.FillVars("AK15Jet_PuppiSoftDropMass", i, ak15jet.userFloat("ak15PFJetsPuppiSoftDropMass"));
        }
        vars.FillVars("AK15Jet_DeepAK15_TvsQCD", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:TvsQCD"));
        vars.FillVars("AK15Jet_DeepAK15_probTbcq", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probTbcq"));
        vars.FillVars("AK15Jet_DeepAK15_probTbqq", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probTbqq"));
        vars.FillVars("AK15Jet_DeepAK15_probTbc", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probTbc"));
        vars.FillVars("AK15Jet_DeepAK15_probTbq", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probTbq"));

        vars.FillVars("AK15Jet_DeepAK15_probWcq", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probWcq"));
        vars.FillVars("AK15Jet_DeepAK15_probWqq", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probWqq"));
        vars.FillVars("AK15Jet_DeepAK15_probZbb", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probZbb"));
        vars.FillVars("AK15Jet_DeepAK15_probZcc", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probZcc"));
        vars.FillVars("AK15Jet_DeepAK15_probZqq", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:propZqq"));
        vars.FillVars("AK15Jet_DeepAK15_probQCDbb", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probQCDbb"));
        vars.FillVars("AK15Jet_DeepAK15_probQCDcc", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probQCDcc"));
        vars.FillVars("AK15Jet_DeepAK15_probQCDc", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probQCDc"));
        vars.FillVars("AK15Jet_DeepAK15_probQCDb", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probQCDb"));
        vars.FillVars("AK15Jet_DeepAK15_probQCDothers", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedJetTags:probQCDothers"));
        vars.FillVars("AK15Jet_DeepAK15_WvsQCD", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:WvsQCD"));
        vars.FillVars("AK15Jet_DeepAK15_ZvsQCD", i, ak15jet.bDiscriminator("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:ZvsQCD"));

        if (ak15jet.hasSubjets("SoftDropWithBtagInfoCorrected")) {
            const auto& ak15jet_subjets = ak15jet.subjets("SoftDropWithBtagInfoCorrected");

            vars.FillVars("AK15Jet_N_SoftDropSubjets", i, ak15jet_subjets.size());

            if (ak15jet_subjets.size() > 0) n_AK15_SoftDrop_Jets += 1;

            int n_btagged_softdropsubjets      = 0;
            int n_loosebtagged_softdropsubjets = 0;
            int n_tightbtagged_softdropsubjets = 0;

            math::XYZTLorentzVector ak15jet_softdrop(0., 0., 0., 0.);

            for (size_t j = 0; j < ak15jet_subjets.size() && j < 3; j++) {
                const auto& ak15jet_subjet = *ak15jet_subjets.at(j);
                vars.FillVars("AK15Jet_SoftDropJet" + std::to_string(j + 1) + "_Pt", i, ak15jet_subjet.pt());
                vars.FillVars("AK15Jet_SoftDropJet" + std::to_string(j + 1) + "_Eta", i, ak15jet_subjet.eta());
                vars.FillVars("AK15Jet_SoftDropJet" + std::to_string(j + 1) + "_Phi", i, ak15jet_subjet.phi());
                vars.FillVars("AK15Jet_SoftDropJet" + std::to_string(j + 1) + "_E", i, ak15jet_subjet.energy());
                vars.FillVars("AK15Jet_SoftDropJet" + std::to_string(j + 1) + "_M", i, ak15jet_subjet.mass());
                vars.FillVars("AK15Jet_SoftDropJet" + std::to_string(j + 1) + "_DeepJetCSV", i, CSVHelper::GetJetCSV_DNN(ak15jet_subjet, "DeepJet"));
                if (CSVHelper::PassesCSV(ak15jet_subjet, "DeepJet", CSVHelper::CSVwp::Medium, era)) n_btagged_softdropsubjets += 1;
                if (CSVHelper::PassesCSV(ak15jet_subjet, "DeepJet", CSVHelper::CSVwp::Loose, era)) n_loosebtagged_softdropsubjets += 1;
                if (CSVHelper::PassesCSV(ak15jet_subjet, "DeepJet", CSVHelper::CSVwp::Tight, era)) n_tightbtagged_softdropsubjets += 1;
                ak15jet_softdrop += ak15jet_subjet.p4();
            }

            vars.FillVars("AK15Jet_N_BTaggedSoftDropSubjets", i, n_btagged_softdropsubjets);
            vars.FillVars("AK15Jet_N_LooseBTaggedSoftDropSubjets", i, n_loosebtagged_softdropsubjets);
            vars.FillVars("AK15Jet_N_TightBTaggedSoftDropSubjets", i, n_tightbtagged_softdropsubjets);

            vars.FillVars("AK15Jet_SoftDrop_Pt", i, ak15jet_softdrop.pt());
            vars.FillVars("AK15Jet_SoftDrop_Eta", i, ak15jet_softdrop.eta());
            vars.FillVars("AK15Jet_SoftDrop_Phi", i, ak15jet_softdrop.phi());
            vars.FillVars("AK15Jet_SoftDrop_E", i, ak15jet_softdrop.energy());
            vars.FillVars("AK15Jet_SoftDrop_M", i, ak15jet_softdrop.mass());
        }

        for (size_t k = 0; k < ak4jets.size(); k++) {
            const auto& ak4jet = ak4jets.at(k);
            vars.FillVars("DeltaR_AK15Jet_AK4Jet", i * ak4jets.size() + k, BoostedUtils::DeltaR(ak15jet.p4(), ak4jet.p4()));
        }

        for (size_t k = 0; k < ak4jets_tagged.size(); k++) {
            const auto& ak4jet_tagged            = ak4jets_tagged.at(k);
            const auto  dR_ak15jet_ak4jet_tagged = BoostedUtils::DeltaR(ak15jet.p4(), ak4jet_tagged.p4());
            vars.FillVars("DeltaR_AK15Jet_AK4JetTagged", i * ak4jets_tagged.size() + k, dR_ak15jet_ak4jet_tagged);
            if (dR_ak15jet_ak4jet_tagged > 1.5)
                n_AK4JetsTagged_outside_AK15Jets += 1;
            else
                n_AK4JetsTagged_inside_AK15Jets += 1;
        }
        for (size_t k = 0; k < ak4jets_loose_tagged.size(); k++) {
            const auto& ak4jet_loose_tagged            = ak4jets_loose_tagged.at(k);
            const auto  dR_ak15jet_ak4jet_loose_tagged = BoostedUtils::DeltaR(ak15jet.p4(), ak4jet_loose_tagged.p4());
            vars.FillVars("DeltaR_AK15Jet_AK4JetLooseTagged", i * ak4jets_loose_tagged.size() + k, dR_ak15jet_ak4jet_loose_tagged);
            if (dR_ak15jet_ak4jet_loose_tagged > 1.5)
                n_AK4JetsLooseTagged_outside_AK15Jets += 1;
            else
                n_AK4JetsLooseTagged_inside_AK15Jets += 1;
        }
        for (size_t k = 0; k < ak4jets_tight_tagged.size(); k++) {
            const auto& ak4jet_tight_tagged            = ak4jets_tight_tagged.at(k);
            const auto  dR_ak15jet_ak4jet_tight_tagged = BoostedUtils::DeltaR(ak15jet.p4(), ak4jet_tight_tagged.p4());
            vars.FillVars("DeltaR_AK15Jet_AK4JetTightTagged", i * ak4jets_tight_tagged.size() + k, dR_ak15jet_ak4jet_tight_tagged);
            if (dR_ak15jet_ak4jet_tight_tagged > 1.5)
                n_AK4JetsTightTagged_outside_AK15Jets += 1;
            else
                n_AK4JetsTightTagged_inside_AK15Jets += 1;
        }

        if (ak15jet.eta() < -1.4 && ak15jet.eta() > -3.0 && ak15jet.phi() < -0.87 && ak15jet.phi() > -1.57) N_HEM_AK15Jets += 1;

        if (input.genTopEvt.IsFilled()) {
            const auto& tophad  = input.genTopEvt.GetAllTopHads();
            bool        matched = false;
            float       min_dr  = 999.;
            for (size_t j = 0; j < tophad.size(); j++) {
                const auto& bhad   = input.genTopEvt.GetAllTopHadDecayQuarks().at(j);
                const auto& q1     = input.genTopEvt.GetAllWQuarks().at(j);
                const auto& q2     = input.genTopEvt.GetAllWAntiQuarks().at(j);
                const auto  max_dr = std::max(
                    {BoostedUtils::DeltaR(bhad.p4(), ak15jet.p4()), BoostedUtils::DeltaR(q1.p4(), ak15jet.p4()), BoostedUtils::DeltaR(q2.p4(), ak15jet.p4())});
                min_dr = std::min(BoostedUtils::DeltaR(tophad.at(j).p4(), ak15jet.p4()), min_dr);
                if (max_dr < 1.5) { matched = true; }
            }
            if (matched) { vars.FillVars("AK15Jet_TopMatched", i, 1); }
            else {
                vars.FillVars("AK15Jet_TopMatched", i, 0);
            }
            vars.FillVars("Min_DeltaR_AK15Jet_GenTopHad", i, min_dr);
        }
    }
    vars.FillVar("N_AK4JetsTagged_outside_AK15Jets", n_AK4JetsTagged_outside_AK15Jets);
    vars.FillVar("N_AK4JetsLooseTagged_outside_AK15Jets", n_AK4JetsLooseTagged_outside_AK15Jets);
    vars.FillVar("N_AK4JetsTightTagged_outside_AK15Jets", n_AK4JetsTightTagged_outside_AK15Jets);
    vars.FillVar("N_AK4JetsTagged_inside_AK15Jets", n_AK4JetsTagged_inside_AK15Jets);
    vars.FillVar("N_AK4JetsLooseTagged_inside_AK15Jets", n_AK4JetsLooseTagged_inside_AK15Jets);
    vars.FillVar("N_AK4JetsTightTagged_inside_AK15Jets", n_AK4JetsTightTagged_inside_AK15Jets);
    vars.FillVar("N_AK15Jets_SoftDrop", n_AK15_SoftDrop_Jets);
    vars.FillVar("N_HEM_AK15Jets", N_HEM_AK15Jets);
}
