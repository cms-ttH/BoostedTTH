#include "BoostedTTH/BoostedAnalyzer/interface/JetVarProcessor.hpp"

using namespace std;

JetVarProcessor::JetVarProcessor() {}
JetVarProcessor::~JetVarProcessor() {}

void JetVarProcessor::Init(const InputCollections& input, VariableContainer& vars)
{
    // load dataEra
    era = input.era;

    vars.InitVar("N_AK8Jets", "I");
    vars.InitVars("AK8Jet_Pt", "N_AK8Jets");
    vars.InitVars("AK8Jet_Eta", "N_AK8Jets");
    vars.InitVars("AK8Jet_Phi", "N_AK8Jets");
    vars.InitVars("AK8Jet_E", "N_AK8Jets");
    vars.InitVars("AK8Jet_M", "N_AK8Jets");
    vars.InitVars("AK8Jet_Njettiness_tau1", "N_AK8Jets");
    vars.InitVars("AK8Jet_Njettiness_tau2", "N_AK8Jets");
    vars.InitVars("AK8Jet_Njettiness_tau3", "N_AK8Jets");
    vars.InitVars("AK8Jet_Njettiness_tau4", "N_AK8Jets");
    vars.InitVars("AK8Jet_PuppiSoftDropMass", "N_AK8Jets");
    vars.InitVars("AK8Jet_DeepAK8_TvsQCD", "N_AK8Jets");

    vars.InitVar("N_AK15Jets", "I");
    vars.InitVars("AK15Jet_Pt", "N_AK15Jets");
    vars.InitVars("AK15Jet_Eta", "N_AK15Jets");
    vars.InitVars("AK15Jet_Phi", "N_AK15Jets");
    vars.InitVars("AK15Jet_E", "N_AK15Jets");
    vars.InitVars("AK15Jet_M", "N_AK15Jets");
    vars.InitVars("AK15Jet_Njettiness_tau1", "N_AK15Jets");
    vars.InitVars("AK15Jet_Njettiness_tau2", "N_AK15Jets");
    vars.InitVars("AK15Jet_Njettiness_tau3", "N_AK15Jets");
    vars.InitVars("AK15Jet_Njettiness_tau4", "N_AK15Jets");
    vars.InitVars("AK15Jet_PuppiSoftDropMass", "N_AK15Jets");
    vars.InitVars("AK15Jet_DeepAK15_TvsQCD", "N_AK15Jets");

    initialized = true;
}

void JetVarProcessor::Process(const InputCollections& input, VariableContainer& vars)
{
    if (!initialized) cerr << "JetVarProcessor not initialized" << endl;

    vars.FillVar("N_AK8Jets", input.selectedJetsAK8.size());
    for (size_t i = 0; i < input.selectedJetsAK8.size(); i++) {
        vars.FillVars("AK8Jet_Pt", i, input.selectedJetsAK8.at(i).pt());
        vars.FillVars("AK8Jet_Eta", i, input.selectedJetsAK8.at(i).eta());
        vars.FillVars("AK8Jet_Phi", i, input.selectedJetsAK8.at(i).phi());
        vars.FillVars("AK8Jet_E", i, input.selectedJetsAK8.at(i).energy());
        vars.FillVars("AK8Jet_M", i, input.selectedJetsAK8.at(i).mass());
        if (input.selectedJetsAK8.at(i).hasUserFloat("NjettinessAK8Puppi:tau1")) {
            vars.FillVars("AK8Jet_Njettiness_tau1", i, input.selectedJetsAK8.at(i).userFloat("NjettinessAK8Puppi:tau1"));
        }
        if (input.selectedJetsAK8.at(i).hasUserFloat("NjettinessAK8Puppi:tau2")) {
            vars.FillVars("AK8Jet_Njettiness_tau2", i, input.selectedJetsAK8.at(i).userFloat("NjettinessAK8Puppi:tau2"));
        }
        if (input.selectedJetsAK8.at(i).hasUserFloat("NjettinessAK8Puppi:tau3")) {
            vars.FillVars("AK8Jet_Njettiness_tau3", i, input.selectedJetsAK8.at(i).userFloat("NjettinessAK8Puppi:tau3"));
        }
        if (input.selectedJetsAK8.at(i).hasUserFloat("NjettinessAK8Puppi:tau4")) {
            vars.FillVars("AK8Jet_Njettiness_tau4", i, input.selectedJetsAK8.at(i).userFloat("NjettinessAK8Puppi:tau4"));
        }
        if (input.selectedJetsAK8.at(i).hasUserFloat("ak8PFJetsPuppiSoftDropMass")) {
            vars.FillVars("AK8Jet_PuppiSoftDropMass", i, input.selectedJetsAK8.at(i).userFloat("ak8PFJetsPuppiSoftDropMass"));
        }
        vars.FillVars("AK8Jet_DeepAK8_TvsQCD", i, input.selectedJetsAK8.at(i).bDiscriminator("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:TvsQCD"));
    }

    vars.FillVar("N_AK15Jets", input.selectedJetsAK15.size());
    for (size_t i = 0; i < input.selectedJetsAK15.size(); i++) {
        vars.FillVars("AK15Jet_Pt", i, input.selectedJetsAK15.at(i).pt());
        vars.FillVars("AK15Jet_Eta", i, input.selectedJetsAK15.at(i).eta());
        vars.FillVars("AK15Jet_Phi", i, input.selectedJetsAK15.at(i).phi());
        vars.FillVars("AK15Jet_E", i, input.selectedJetsAK15.at(i).energy());
        vars.FillVars("AK15Jet_M", i, input.selectedJetsAK15.at(i).mass());
        if (input.selectedJetsAK15.at(i).hasUserFloat("NjettinessAK15Puppi:tau1")) {
            vars.FillVars("AK15Jet_Njettiness_tau1", i, input.selectedJetsAK15.at(i).userFloat("NjettinessAK15Puppi:tau1"));
        }
        if (input.selectedJetsAK15.at(i).hasUserFloat("NjettinessAK15Puppi:tau2")) {
            vars.FillVars("AK15Jet_Njettiness_tau2", i, input.selectedJetsAK15.at(i).userFloat("NjettinessAK15Puppi:tau2"));
        }
        if (input.selectedJetsAK15.at(i).hasUserFloat("NjettinessAK15Puppi:tau3")) {
            vars.FillVars("AK15Jet_Njettiness_tau3", i, input.selectedJetsAK15.at(i).userFloat("NjettinessAK15Puppi:tau3"));
        }
        if (input.selectedJetsAK15.at(i).hasUserFloat("NjettinessAK15Puppi:tau4")) {
            vars.FillVars("AK15Jet_Njettiness_tau4", i, input.selectedJetsAK15.at(i).userFloat("NjettinessAK15Puppi:tau4"));
        }
        if (input.selectedJetsAK15.at(i).hasUserFloat("ak15PFJetsPuppiSoftDropMass")) {
            vars.FillVars("AK15Jet_PuppiSoftDropMass", i, input.selectedJetsAK15.at(i).userFloat("ak15PFJetsPuppiSoftDropMass"));
        }
        vars.FillVars("AK15Jet_DeepAK15_TvsQCD", i, input.selectedJetsAK15.at(i).bDiscriminator("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:TvsQCD"));
    }
}
