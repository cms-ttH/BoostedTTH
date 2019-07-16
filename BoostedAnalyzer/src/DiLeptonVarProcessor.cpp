#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonVarProcessor.hpp"

using namespace std;

DiLeptonVarProcessor::DiLeptonVarProcessor() {}
DiLeptonVarProcessor::~DiLeptonVarProcessor() {}

void DiLeptonVarProcessor::Init(const InputCollections& input, VariableContainer& vars)
{
    vars.InitVar("DiMuon_E");
    vars.InitVar("DiMuon_M");
    vars.InitVar("DiMuon_Pt");
    vars.InitVar("DiMuon_Eta");
    vars.InitVar("DiMuon_Phi");
    vars.InitVar("DiMuon_SS");

    vars.InitVar("DiElectron_E");
    vars.InitVar("DiElectron_M");
    vars.InitVar("DiElectron_Pt");
    vars.InitVar("DiElectron_Eta");
    vars.InitVar("DiElectron_Phi");
    vars.InitVar("DiElectron_SS");

    vars.InitVar("ElMu_E");
    vars.InitVar("ElMu_M");
    vars.InitVar("ElMu_Pt");
    vars.InitVar("ElMu_Eta");
    vars.InitVar("ElMu_Phi");
    vars.InitVar("ElMu_SS");

    initialized = true;
}

void DiLeptonVarProcessor::Process(const InputCollections& input, VariableContainer& vars)
{
    if (!initialized) cerr << "tree processor not initialized" << endl;

    if (input.selectedMuonsDL.size() >= 2) {
        math::XYZTLorentzVector DiMuonVec = input.selectedMuonsDL[0].p4() + input.selectedMuonsDL[1].p4();

        vars.FillVar("DiMuon_E", DiMuonVec.E());
        vars.FillVar("DiMuon_M", DiMuonVec.M());
        vars.FillVar("DiMuon_Pt", DiMuonVec.Pt());
        vars.FillVar("DiMuon_Eta", DiMuonVec.Eta());
        vars.FillVar("DiMuon_Phi", DiMuonVec.Phi());
        vars.FillVar("DiMuon_SS", input.selectedMuonsDL[0].charge() * input.selectedMuonsDL[1].charge() > 0);
    }

    if (input.selectedElectronsDL.size() >= 2) {
        math::XYZTLorentzVector DiElectronVec = input.selectedElectronsDL[0].p4() + input.selectedElectronsDL[1].p4();

        vars.FillVar("DiElectron_E", DiElectronVec.E());
        vars.FillVar("DiElectron_M", DiElectronVec.M());
        vars.FillVar("DiElectron_Pt", DiElectronVec.Pt());
        vars.FillVar("DiElectron_Eta", DiElectronVec.Eta());
        vars.FillVar("DiElectron_Phi", DiElectronVec.Phi());

        vars.FillVar("DiElectron_SS", input.selectedElectronsDL[0].charge() * input.selectedElectronsDL[1].charge() > 0);
    }

    if (input.selectedElectronsDL.size() >= 1 && input.selectedMuonsDL.size() >= 1) {
        math::XYZTLorentzVector ElMuVec = input.selectedElectronsDL[0].p4() + input.selectedMuonsDL[0].p4();

        vars.FillVar("ElMu_E", ElMuVec.E());
        vars.FillVar("ElMu_M", ElMuVec.M());
        vars.FillVar("ElMu_Pt", ElMuVec.Pt());
        vars.FillVar("ElMu_Eta", ElMuVec.Eta());
        vars.FillVar("ElMu_Phi", ElMuVec.Phi());
        vars.FillVar("ElMu_SS", input.selectedElectronsDL[0].charge() * input.selectedMuonsDL[1].charge() > 0);
    }
}
