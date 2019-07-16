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
}
