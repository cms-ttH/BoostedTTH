#include "BoostedTTH/BoostedAnalyzer/interface/PhotonVarProcessor.hpp"

using namespace std;

PhotonVarProcessor::PhotonVarProcessor() {}
PhotonVarProcessor::~PhotonVarProcessor() {}

void PhotonVarProcessor::Init(const InputCollections& input, VariableContainer& vars)
{
    // load dataEra
    era = input.era;

    vars.InitVar("N_Photons", "I");
    vars.InitVars("Photon_Pt", "N_Photons");
    vars.InitVars("Photon_Eta", "N_Photons");
    vars.InitVars("Photon_Phi", "N_Photons");
    vars.InitVars("Photon_E", "N_Photons");
    vars.InitVars("Photon_M", "N_Photons");
    vars.InitVars("Photon_IdentificationSF", "N_Photons");
    vars.InitVars("Photon_IdentificationSFUp", "N_Photons");
    vars.InitVars("Photon_IdentificationSFDown", "N_Photons");
    
    vars.InitVar("N_LoosePhotons", "I");
    vars.InitVars("LoosePhoton_Pt", "N_LoosePhotons");
    vars.InitVars("LoosePhoton_Eta", "N_LoosePhotons");
    vars.InitVars("LoosePhoton_Phi", "N_LoosePhotons");
    vars.InitVars("LoosePhoton_E", "N_LoosePhotons");
    vars.InitVars("LoosePhoton_M", "N_LoosePhotons");
    vars.InitVars("LoosePhoton_IdentificationSF", "N_LoosePhotons");
    vars.InitVars("LoosePhoton_IdentificationSFUp", "N_LoosePhotons");
    vars.InitVars("LoosePhoton_IdentificationSFDown", "N_LoosePhotons");

    initialized = true;
}

void PhotonVarProcessor::Process(const InputCollections& input, VariableContainer& vars)
{
    if (!initialized) cerr << "PhotonVarProcessor not initialized" << endl;

    vars.FillVar("N_Photons", input.selectedPhotons.size());
    for (size_t i = 0; i < input.selectedPhotons.size(); i++) {
        vars.FillVars("Photon_Pt", i, input.selectedPhotons.at(i).pt());
        vars.FillVars("Photon_Eta", i, input.selectedPhotons.at(i).eta());
        vars.FillVars("Photon_Phi", i, input.selectedPhotons.at(i).phi());
        vars.FillVars("Photon_E", i, input.selectedPhotons.at(i).energy());
        vars.FillVars("Photon_M", i, input.selectedPhotons.at(i).mass());
        if (input.selectedPhotons.at(i).hasUserFloat("IdentificationSF")) {
            vars.FillVars("Photon_IdentificationSF", i, input.selectedPhotons.at(i).userFloat("IdentificationSF"));
            vars.FillVars("Photon_IdentificationSFUp", i, input.selectedPhotons.at(i).userFloat("IdentificationSFUp"));
            vars.FillVars("Photon_IdentificationSFDown", i, input.selectedPhotons.at(i).userFloat("IdentificationSFDown"));
        }
    }
    
    vars.FillVar("N_LoosePhotons", input.selectedPhotonsLoose.size());
    for (size_t i = 0; i < input.selectedPhotonsLoose.size(); i++) {
        vars.FillVars("LoosePhoton_Pt", i, input.selectedPhotonsLoose.at(i).pt());
        vars.FillVars("LoosePhoton_Eta", i, input.selectedPhotonsLoose.at(i).eta());
        vars.FillVars("LoosePhoton_Phi", i, input.selectedPhotonsLoose.at(i).phi());
        vars.FillVars("LoosePhoton_E", i, input.selectedPhotonsLoose.at(i).energy());
        vars.FillVars("LoosePhoton_M", i, input.selectedPhotonsLoose.at(i).mass());
        if (input.selectedPhotonsLoose.at(i).hasUserFloat("IdentificationSF")) {
            vars.FillVars("LoosePhoton_IdentificationSF", i, input.selectedPhotonsLoose.at(i).userFloat("IdentificationSF"));
            vars.FillVars("LoosePhoton_IdentificationSFUp", i, input.selectedPhotonsLoose.at(i).userFloat("IdentificationSFUp"));
            vars.FillVars("LoosePhoton_IdentificationSFDown", i, input.selectedPhotonsLoose.at(i).userFloat("IdentificationSFDown"));
        }
    }
}
