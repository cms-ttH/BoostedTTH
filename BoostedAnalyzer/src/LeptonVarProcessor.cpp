#include "BoostedTTH/BoostedAnalyzer/interface/LeptonVarProcessor.hpp"

using namespace std;

LeptonVarProcessor::LeptonVarProcessor() {}
LeptonVarProcessor::~LeptonVarProcessor() {}

void LeptonVarProcessor::Init(const InputCollections& input, VariableContainer& vars)
{
    vars.InitVar("N_TightElectrons", "I");
    vars.InitVar("N_LooseElectrons", "I");
    vars.InitVar("N_TightMuons", "I");
    vars.InitVar("N_LooseMuons", "I");
    // vars.InitVar("N_TightLeptons", "I");
    // vars.InitVar("N_LooseLeptons", "I");

    vars.InitVars("LooseMuon_E", "N_LooseMuons");
    vars.InitVars("LooseMuon_M", "N_LooseMuons");
    vars.InitVars("LooseMuon_Pt", "N_LooseMuons");
    vars.InitVars("LooseMuon_Eta", "N_LooseMuons");
    vars.InitVars("LooseMuon_Phi", "N_LooseMuons");
    vars.InitVars("LooseMuon_RelIso", "N_LooseMuons");
    vars.InitVars("LooseMuon_Charge", "N_LooseMuons");
    vars.InitVars("LooseMuon_Pt_BeForeRC", "N_LooseMuons");
    vars.InitVars("LooseMuon_roccorSF", "N_LooseMuons");
    vars.InitVars("LooseMuon_roccorSFUp", "N_LooseMuons");
    vars.InitVars("LooseMuon_roccorSFDown", "N_LooseMuons");
    vars.InitVars("LooseMuon_IdentificationSF", "N_LooseMuons");
    vars.InitVars("LooseMuon_IdentificationSFUp", "N_LooseMuons");
    vars.InitVars("LooseMuon_IdentificationSFDown", "N_LooseMuons");
    vars.InitVars("LooseMuon_IsolationSF", "N_LooseMuons");
    vars.InitVars("LooseMuon_IsolationSFUp", "N_LooseMuons");
    vars.InitVars("LooseMuon_IsolationSFDown", "N_LooseMuons");

    vars.InitVars("Muon_E", "N_TightMuons");
    vars.InitVars("Muon_M", "N_TightMuons");
    vars.InitVars("Muon_Pt", "N_TightMuons");
    vars.InitVars("Muon_Eta", "N_TightMuons");
    vars.InitVars("Muon_Phi", "N_TightMuons");
    vars.InitVars("Muon_RelIso", "N_TightMuons");
    vars.InitVars("Muon_Charge", "N_TightMuons");
    vars.InitVars("Muon_Pt_BeForeRC", "N_TightMuons");
    vars.InitVars("Muon_roccorSF", "N_TightMuons");
    vars.InitVars("Muon_roccorSFUp", "N_TightMuons");
    vars.InitVars("Muon_roccorSFDown", "N_TightMuons");
    vars.InitVars("Muon_IdentificationSF", "N_TightMuons");
    vars.InitVars("Muon_IdentificationSFUp", "N_TightMuons");
    vars.InitVars("Muon_IdentificationSFDown", "N_TightMuons");
    vars.InitVars("Muon_IsolationSF", "N_TightMuons");
    vars.InitVars("Muon_IsolationSFUp", "N_TightMuons");
    vars.InitVars("Muon_IsolationSFDown", "N_TightMuons");

    vars.InitVar("DiMuon_Pt");
    vars.InitVar("DiMuon_Phi");
    vars.InitVar("DiMuon_Eta");
    vars.InitVar("DiMuon_Energy");
    vars.InitVar("DiMuon_Mass");

    vars.InitVars("LooseElectron_E", "N_LooseElectrons");
    vars.InitVars("LooseElectron_M", "N_LooseElectrons");
    vars.InitVars("LooseElectron_Pt", "N_LooseElectrons");
    vars.InitVars("LooseElectron_Eta", "N_LooseElectrons");
    vars.InitVars("LooseElectron_Phi", "N_LooseElectrons");
    vars.InitVars("LooseElectron_RelIso", "N_LooseElectrons");
    vars.InitVars("LooseElectron_Charge", "N_LooseElectrons");
    vars.InitVars("LooseElectron_Pt_BeforeRun2Calibration", "N_LooseElectrons");
    vars.InitVars("LooseElectron_Eta_Supercluster", "N_LooseElectrons");
    // electron energy scale combined up/down
    vars.InitVars("LooseElectron_CorrFactor_ScaleUp", "N_LooseElectrons");
    vars.InitVars("LooseElectron_CorrFactor_ScaleDown", "N_LooseElectrons");
    // electron energy smearing combined up/down
    vars.InitVars("LooseElectron_CorrFactor_SigmaUp", "N_LooseElectrons");
    vars.InitVars("LooseElectron_CorrFactor_SigmaDown", "N_LooseElectrons");
    vars.InitVars("LooseElectron_IdentificationSF", "N_LooseElectrons");
    vars.InitVars("LooseElectron_IdentificationSFUp", "N_LooseElectrons");
    vars.InitVars("LooseElectron_IdentificationSFDown", "N_LooseElectrons");
    vars.InitVars("LooseElectron_ReconstructionSF", "N_LooseElectrons");
    vars.InitVars("LooseElectron_ReconstructionSFUp", "N_LooseElectrons");
    vars.InitVars("LooseElectron_ReconstructionSFDown", "N_LooseElectrons");

    vars.InitVars("Electron_E", "N_TightElectrons");
    vars.InitVars("Electron_M", "N_TightElectrons");
    vars.InitVars("Electron_Pt", "N_TightElectrons");
    vars.InitVars("Electron_Eta", "N_TightElectrons");
    vars.InitVars("Electron_Phi", "N_TightElectrons");
    vars.InitVars("Electron_RelIso", "N_TightElectrons");
    vars.InitVars("Electron_Charge", "N_TightElectrons");
    vars.InitVars("Electron_Pt_BeforeRun2Calibration", "N_TightElectrons");
    vars.InitVars("Electron_Eta_Supercluster", "N_TightElectrons");
    // electron energy scale combined up/down
    vars.InitVars("Electron_CorrFactor_ScaleUp", "N_TightElectrons");
    vars.InitVars("Electron_CorrFactor_ScaleDown", "N_TightElectrons");
    // electron energy smearing combined up/down
    vars.InitVars("Electron_CorrFactor_SigmaUp", "N_TightElectrons");
    vars.InitVars("Electron_CorrFactor_SigmaDown", "N_TightElectrons");
    vars.InitVars("Electron_IdentificationSF", "N_TightElectrons");
    vars.InitVars("Electron_IdentificationSFUp", "N_TightElectrons");
    vars.InitVars("Electron_IdentificationSFDown", "N_TightElectrons");
    vars.InitVars("Electron_ReconstructionSF", "N_TightElectrons");
    vars.InitVars("Electron_ReconstructionSFUp", "N_TightElectrons");
    vars.InitVars("Electron_ReconstructionSFDown", "N_TightElectrons");

    vars.InitVar("DiElectron_Pt");
    vars.InitVar("DiElectron_Phi");
    vars.InitVar("DiElectron_Eta");
    vars.InitVar("DiElectron_Energy");
    vars.InitVar("DiElectron_Mass");

    //     vars.InitVars("TightLepton_E", "N_TightLeptons");
    //     vars.InitVars("TightLepton_M", "N_TightLeptons");
    //     vars.InitVars("TightLepton_Pt", "N_TightLeptons");
    //     vars.InitVars("TightLepton_Eta", "N_TightLeptons");
    //     vars.InitVars("TightLepton_Phi", "N_TightLeptons");

    //     vars.InitVars("LooseLepton_E", "N_LooseLeptons");
    //     vars.InitVars("LooseLepton_M", "N_LooseLeptons");
    //     vars.InitVars("LooseLepton_Pt", "N_LooseLeptons");
    //     vars.InitVars("LooseLepton_Eta", "N_LooseLeptons");
    //     vars.InitVars("LooseLepton_Phi", "N_LooseLeptons");

    vars.InitVar("N_HEM_Electrons", "I");
    vars.InitVar("N_HEM_Muons", "I");

    initialized = true;
}

void LeptonVarProcessor::Process(const InputCollections& input, VariableContainer& vars)
{
    if (!initialized) cerr << "LeptonVarProcessor not initialized" << endl;

    vars.FillVar("N_TightElectrons", input.selectedElectrons.size());
    vars.FillVar("N_LooseElectrons", input.selectedElectronsLoose.size());
    vars.FillVar("N_TightMuons", input.selectedMuons.size());
    vars.FillVar("N_LooseMuons", input.selectedMuonsLoose.size());
    // vars.FillVar("N_TightLeptons", input.selectedElectrons.size() + input.selectedMuons.size());
    // vars.FillVar("N_LooseLeptons", input.selectedElectronsLoose.size() + input.selectedMuonsLoose.size());
    
    int N_HEM_Electrons = 0;
    int N_HEM_Muons = 0;

    for (std::vector< pat::Electron >::const_iterator itEle = input.selectedElectronsLoose.begin(); itEle != input.selectedElectronsLoose.end(); ++itEle) {
        int iEle = itEle - input.selectedElectronsLoose.begin();
        vars.FillVars("LooseElectron_E", iEle, itEle->energy());
        vars.FillVars("LooseElectron_M", iEle, itEle->mass());
        vars.FillVars("LooseElectron_Pt", iEle, itEle->pt());
        vars.FillVars("LooseElectron_Eta", iEle, itEle->eta());
        vars.FillVars("LooseElectron_Phi", iEle, itEle->phi());
        if (itEle->hasUserFloat("relIso")) vars.FillVars("LooseElectron_RelIso", iEle, itEle->userFloat("relIso"));

        vars.FillVars("LooseElectron_Charge", iEle, itEle->charge());
        if (itEle->hasUserFloat("ptBeforeRun2Calibration"))
            vars.FillVars("LooseElectron_Pt_BeforeRun2Calibration", iEle, itEle->userFloat("ptBeforeRun2Calibration"));

        vars.FillVars("LooseElectron_Eta_Supercluster", iEle, itEle->superCluster()->eta());
        if (itEle->hasUserFloat("CorrFactor_ScaleUp")) {
            // electron energy scale combined up/down
            vars.FillVars("LooseElectron_CorrFactor_ScaleUp", iEle, itEle->userFloat("CorrFactor_ScaleUp"));
            vars.FillVars("LooseElectron_CorrFactor_ScaleDown", iEle, itEle->userFloat("CorrFactor_ScaleDown"));
            // electron energy smearing combined up/down
            vars.FillVars("LooseElectron_CorrFactor_SigmaUp", iEle, itEle->userFloat("CorrFactor_SigmaUp"));
            vars.FillVars("LooseElectron_CorrFactor_SigmaDown", iEle, itEle->userFloat("CorrFactor_SigmaDown"));
        }
        if (itEle->hasUserFloat("IdentificationSF")) {
            vars.FillVars("LooseElectron_IdentificationSF", iEle, itEle->userFloat("IdentificationSF"));
            vars.FillVars("LooseElectron_IdentificationSFUp", iEle, itEle->userFloat("IdentificationSFUp"));
            vars.FillVars("LooseElectron_IdentificationSFDown", iEle, itEle->userFloat("IdentificationSFDown"));
            vars.FillVars("LooseElectron_ReconstructionSF", iEle, itEle->userFloat("ReconstructionSF"));
            vars.FillVars("LooseElectron_ReconstructionSFUp", iEle, itEle->userFloat("ReconstructionSFUp"));
            vars.FillVars("LooseElectron_ReconstructionSFDown", iEle, itEle->userFloat("ReconstructionSFDown"));
        }
        if(itEle->eta()<-1.4 && itEle->eta()>-3.0 && itEle->phi()<-0.87 && itEle->phi()>-1.57) N_HEM_Electrons+=1;
    }
    for (std::vector< pat::Electron >::const_iterator itEle = input.selectedElectrons.begin(); itEle != input.selectedElectrons.end(); ++itEle) {
        int iEle = itEle - input.selectedElectrons.begin();
        vars.FillVars("Electron_E", iEle, itEle->energy());
        vars.FillVars("Electron_M", iEle, itEle->mass());
        vars.FillVars("Electron_Pt", iEle, itEle->pt());
        vars.FillVars("Electron_Eta", iEle, itEle->eta());
        vars.FillVars("Electron_Phi", iEle, itEle->phi());
        if (itEle->hasUserFloat("relIso")) vars.FillVars("Electron_RelIso", iEle, itEle->userFloat("relIso"));

        vars.FillVars("Electron_Charge", iEle, itEle->charge());
        if (itEle->hasUserFloat("ptBeforeRun2Calibration"))
            vars.FillVars("Electron_Pt_BeforeRun2Calibration", iEle, itEle->userFloat("ptBeforeRun2Calibration"));

        vars.FillVars("Electron_Eta_Supercluster", iEle, itEle->superCluster()->eta());
        if (itEle->hasUserFloat("CorrFactor_ScaleUp")) {
            // electron energy scale combined up/down
            vars.FillVars("Electron_CorrFactor_ScaleUp", iEle, itEle->userFloat("CorrFactor_ScaleUp"));
            vars.FillVars("Electron_CorrFactor_ScaleDown", iEle, itEle->userFloat("CorrFactor_ScaleDown"));
            // electron energy smearing combined up/down
            vars.FillVars("Electron_CorrFactor_SigmaUp", iEle, itEle->userFloat("CorrFactor_SigmaUp"));
            vars.FillVars("Electron_CorrFactor_SigmaDown", iEle, itEle->userFloat("CorrFactor_SigmaDown"));
        }
        if (itEle->hasUserFloat("IdentificationSF")) {
            vars.FillVars("Electron_IdentificationSF", iEle, itEle->userFloat("IdentificationSF"));
            vars.FillVars("Electron_IdentificationSFUp", iEle, itEle->userFloat("IdentificationSFUp"));
            vars.FillVars("Electron_IdentificationSFDown", iEle, itEle->userFloat("IdentificationSFDown"));
            vars.FillVars("Electron_ReconstructionSF", iEle, itEle->userFloat("ReconstructionSF"));
            vars.FillVars("Electron_ReconstructionSFUp", iEle, itEle->userFloat("ReconstructionSFUp"));
            vars.FillVars("Electron_ReconstructionSFDown", iEle, itEle->userFloat("ReconstructionSFDown"));
        }
    }

    if (input.selectedElectronsLoose.size() >= 2) {
        auto dielectron = input.selectedElectronsLoose.at(0).p4() + input.selectedElectronsLoose.at(1).p4();
        vars.FillVar("DiElectron_Pt", dielectron.pt());
        vars.FillVar("DiElectron_Phi", dielectron.phi());
        vars.FillVar("DiElectron_Eta", dielectron.eta());
        vars.FillVar("DiElectron_Energy", dielectron.energy());
        vars.FillVar("DiElectron_Mass", dielectron.mass());
    }

    for (std::vector< pat::Muon >::const_iterator itMu = input.selectedMuonsLoose.begin(); itMu != input.selectedMuonsLoose.end(); ++itMu) {
        int iMu = itMu - input.selectedMuonsLoose.begin();
        vars.FillVars("LooseMuon_E", iMu, itMu->energy());
        vars.FillVars("LooseMuon_M", iMu, itMu->mass());
        vars.FillVars("LooseMuon_Pt", iMu, itMu->pt());
        vars.FillVars("LooseMuon_Eta", iMu, itMu->eta());
        vars.FillVars("LooseMuon_Phi", iMu, itMu->phi());
        if (itMu->hasUserFloat("relIso")) vars.FillVars("LooseMuon_RelIso", iMu, itMu->userFloat("relIso"));

        vars.FillVars("LooseMuon_Charge", iMu, itMu->charge());
        if (itMu->hasUserFloat("PtbeforeRC")) vars.FillVars("LooseMuon_Pt_BeForeRC", iMu, itMu->userFloat("PtbeforeRC"));

        if (itMu->hasUserFloat("roccorSF")) vars.FillVars("LooseMuon_roccorSF", iMu, itMu->userFloat("roccorSF"));

        if (itMu->hasUserFloat("roccorSFUp")) vars.FillVars("LooseMuon_roccorSFUp", iMu, itMu->userFloat("roccorSFUp"));

        if (itMu->hasUserFloat("roccorSFDown")) vars.FillVars("LooseMuon_roccorSFDown", iMu, itMu->userFloat("roccorSFDown"));

        if (itMu->hasUserFloat("IdentificationSF")) {
            vars.FillVars("LooseMuon_IdentificationSF", iMu, itMu->userFloat("IdentificationSF"));
            vars.FillVars("LooseMuon_IdentificationSFUp", iMu, itMu->userFloat("IdentificationSFUp"));
            vars.FillVars("LooseMuon_IdentificationSFDown", iMu, itMu->userFloat("IdentificationSFDown"));
        }
        if (itMu->hasUserFloat("IsolationSF")) {
            vars.FillVars("LooseMuon_IsolationSF", iMu, itMu->userFloat("IsolationSF"));
            vars.FillVars("LooseMuon_IsolationSFUp", iMu, itMu->userFloat("IsolationSFUp"));
            vars.FillVars("LooseMuon_IsolationSFDown", iMu, itMu->userFloat("IsolationSFDown"));
        }
        if(itMu->eta()<-1.4 && itMu->eta()>-3.0 && itMu->phi()<-0.87 && itMu->phi()>-1.57) N_HEM_Muons+=1;
    }
    for (std::vector< pat::Muon >::const_iterator itMu = input.selectedMuons.begin(); itMu != input.selectedMuons.end(); ++itMu) {
        int iMu = itMu - input.selectedMuons.begin();
        vars.FillVars("Muon_E", iMu, itMu->energy());
        vars.FillVars("Muon_M", iMu, itMu->mass());
        vars.FillVars("Muon_Pt", iMu, itMu->pt());
        vars.FillVars("Muon_Eta", iMu, itMu->eta());
        vars.FillVars("Muon_Phi", iMu, itMu->phi());
        if (itMu->hasUserFloat("relIso")) vars.FillVars("Muon_RelIso", iMu, itMu->userFloat("relIso"));

        vars.FillVars("Muon_Charge", iMu, itMu->charge());
        if (itMu->hasUserFloat("PtbeforeRC")) vars.FillVars("Muon_Pt_BeForeRC", iMu, itMu->userFloat("PtbeforeRC"));

        if (itMu->hasUserFloat("roccorSF")) vars.FillVars("Muon_roccorSF", iMu, itMu->userFloat("roccorSF"));

        if (itMu->hasUserFloat("roccorSFUp")) vars.FillVars("Muon_roccorSFUp", iMu, itMu->userFloat("roccorSFUp"));

        if (itMu->hasUserFloat("roccorSFDown")) vars.FillVars("Muon_roccorSFDown", iMu, itMu->userFloat("roccorSFDown"));

        if (itMu->hasUserFloat("IdentificationSF")) {
            vars.FillVars("Muon_IdentificationSF", iMu, itMu->userFloat("IdentificationSF"));
            vars.FillVars("Muon_IdentificationSFUp", iMu, itMu->userFloat("IdentificationSFUp"));
            vars.FillVars("Muon_IdentificationSFDown", iMu, itMu->userFloat("IdentificationSFDown"));
        }
        if (itMu->hasUserFloat("IsolationSF")) {
            vars.FillVars("Muon_IsolationSF", iMu, itMu->userFloat("IsolationSF"));
            vars.FillVars("Muon_IsolationSFUp", iMu, itMu->userFloat("IsolationSFUp"));
            vars.FillVars("Muon_IsolationSFDown", iMu, itMu->userFloat("IsolationSFDown"));
        }
    }

    if (input.selectedMuonsLoose.size() >= 2) {
        auto dimuon = input.selectedMuonsLoose.at(0).p4() + input.selectedMuonsLoose.at(1).p4();
        vars.FillVar("DiMuon_Pt", dimuon.pt());
        vars.FillVar("DiMuon_Phi", dimuon.phi());
        vars.FillVar("DiMuon_Eta", dimuon.eta());
        vars.FillVar("DiMuon_Energy", dimuon.energy());
        vars.FillVar("DiMuon_Mass", dimuon.mass());
    }

    // Fill Lepton Variables
    //     std::vector< math::XYZTLorentzVector > tightLeptonVecs = BoostedUtils::GetLepVecs(input.selectedElectrons, input.selectedMuons);
    //     for (auto itLep = tightLeptonVecs.begin(); itLep != tightLeptonVecs.end(); ++itLep) {
    //         int iLep = itLep - tightLeptonVecs.begin();
    //         vars.FillVars("TightLepton_E", iLep, itLep->E());
    //         vars.FillVars("TightLepton_M", iLep, itLep->M());
    //         vars.FillVars("TightLepton_Pt", iLep, itLep->Pt());
    //         vars.FillVars("TightLepton_Eta", iLep, itLep->Eta());
    //         vars.FillVars("TightLepton_Phi", iLep, itLep->Phi());
    //     }
    //     std::vector< math::XYZTLorentzVector > looseLeptonVecs = BoostedUtils::GetLepVecs(input.selectedElectronsLoose, input.selectedMuonsLoose);
    //     for (std::vector< math::XYZTLorentzVector >::iterator itLep = looseLeptonVecs.begin(); itLep != looseLeptonVecs.end(); ++itLep) {
    //         int iLep = itLep - looseLeptonVecs.begin();
    //         vars.FillVars("LooseLepton_E", iLep, itLep->E());
    //         vars.FillVars("LooseLepton_M", iLep, itLep->M());
    //         vars.FillVars("LooseLepton_Pt", iLep, itLep->Pt());
    //         vars.FillVars("LooseLepton_Eta", iLep, itLep->Eta());
    //         vars.FillVars("LooseLepton_Phi", iLep, itLep->Phi());
    //     }
    
    vars.FillVar("N_HEM_Electrons",N_HEM_Electrons);
    vars.FillVar("N_HEM_Muons",N_HEM_Muons);
}
