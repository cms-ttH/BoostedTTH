#include "FWCore/Utilities/interface/Exception.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "TVector2.h"

#include "BoostedTTH/BoostedAnalyzer/interface/GenJetOrderedJetCollectionProcessor.hpp"

void GenJetOrderedJetCollectionProcessor::Init(const InputCollections& input, VariableContainer& vars)
{
    vars.InitVar("Evt_ID", "I");  // Possible conflict because of same-name
                                  // variables in BasicVarProcessor

    // the GEN jets
    vars.InitVar("N_GenJets", "I");
    vars.InitVars("GenJet_E", "N_GenJets");
    vars.InitVars("GenJet_Pt", "N_GenJets");
    vars.InitVars("GenJet_Phi", "N_GenJets");
    vars.InitVars("GenJet_Eta", "N_GenJets");

    // RECO jets matched to GEN jets
    vars.InitVars("GenJet_Jet_E", "N_GenJets");
    vars.InitVars("GenJet_Jet_Pt", "N_GenJets");
    vars.InitVars("GenJet_Jet_Eta", "N_GenJets");
    vars.InitVars("GenJet_Jet_Phi", "N_GenJets");
    vars.InitVars("GenJet_Jet_DeltaR", "N_GenJets");

    initialized = true;
}

void GenJetOrderedJetCollectionProcessor::Process(const InputCollections& input, VariableContainer& vars)
{
    if (!initialized) throw cms::Exception("BadProcessor") << "GenJetOrderedJetCollectionProcessor not initialized";

    // event variables
    vars.FillIntVar("Evt_ID", input.eventInfo.evt);

    // jet variables
    vars.FillVar("N_GenJets", input.genJets.size());
    size_t iGenJet = 0;
    for (auto& genJet : input.genJets) {
        vars.FillVars("GenJet_E", iGenJet, genJet.energy());
        vars.FillVars("GenJet_Pt", iGenJet, genJet.pt());
        vars.FillVars("GenJet_Eta", iGenJet, genJet.eta());
        vars.FillVars("GenJet_Phi", iGenJet, genJet.phi());

        pat::Jet closestJet;
        double   deltaRMin = 1000.;
        if (getClosestJet(genJet, input.selectedJets, closestJet, deltaRMin)) {
            vars.FillVars("GenJet_Jet_E", iGenJet, closestJet.energy());
            vars.FillVars("GenJet_Jet_Pt", iGenJet, closestJet.pt());
            vars.FillVars("GenJet_Jet_Eta", iGenJet, closestJet.eta());
            vars.FillVars("GenJet_Jet_Phi", iGenJet, closestJet.phi());
            vars.FillVars("GenJet_Jet_DeltaR", iGenJet, deltaRMin);
        }
        else {
            vars.FillVars("GenJet_Jet_E", iGenJet, -1.);
            vars.FillVars("GenJet_Jet_Pt", iGenJet, -1.);
            vars.FillVars("GenJet_Jet_Eta", iGenJet, 0.);
            vars.FillVars("GenJet_Jet_Phi", iGenJet, 0.);
            vars.FillVars("GenJet_Jet_DeltaR", iGenJet, deltaRMin);
        }

        ++iGenJet;
    }
}

bool GenJetOrderedJetCollectionProcessor::getClosestJet(const reco::GenJet& genJet, const pat::JetCollection& jets, pat::Jet& closestJet,
                                                        double& deltaRMin) const
{
    double dRMin  = 1000;
    int    idxMin = -1;
    for (size_t i = 0; i < jets.size(); ++i) {
        const double dR = deltaR(genJet, jets.at(i));
        if (dR < dRMin) {
            idxMin = i;
            dRMin  = dR;
        }
    }

    if (idxMin < 0) { return false; }
    else {
        closestJet = jets.at(idxMin);
        deltaRMin  = dRMin;
        return true;
    }
}

double GenJetOrderedJetCollectionProcessor::deltaR(const reco::GenJet& genJet, const pat::Jet& jet) const
{
    const double dEta = genJet.eta() - jet.eta();
    const double dPhi = TVector2::Phi_mpi_pi(genJet.phi() - jet.phi());

    return sqrt(dEta * dEta + dPhi * dPhi);
}
