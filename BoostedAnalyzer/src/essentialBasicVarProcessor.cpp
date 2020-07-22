#include "BoostedTTH/BoostedAnalyzer/interface/essentialBasicVarProcessor.hpp"

using namespace std;

essentialBasicVarProcessor::essentialBasicVarProcessor() {}
essentialBasicVarProcessor::~essentialBasicVarProcessor() {}

void essentialBasicVarProcessor::Init(const InputCollections& input, VariableContainer& vars)
{
    // load dataEra
    era = input.era;

    vars.InitVar("Evt_ID", "L");
    vars.InitVar("Evt_Odd", "I");
    vars.InitVar("Evt_Run", "I");
    vars.InitVar("Evt_Lumi", "I");

    vars.InitVar("N_Jets", "I");
    vars.InitVar("N_LooseJets", "I");
    vars.InitVar("N_AK8Jets", "I");
    vars.InitVar("N_AK15Jets", "I");

    vars.InitVar("N_BTagsL", "I");
    vars.InitVar("N_BTagsM", "I");
    vars.InitVar("N_BTagsT", "I");
    vars.InitVar("N_NoTags", "I");
    vars.InitVar("N_PrimaryVertices", "I");
    vars.InitVar("N_GenPVs", "I");
    vars.InitVar("fixedGridRhoAll");
    vars.InitVar("fixedGridRhoFastjetAll");
    vars.InitVar("fixedGridRhoFastjetAllCalo");
    vars.InitVar("fixedGridRhoFastjetCentral");
    vars.InitVar("fixedGridRhoFastjetCentralCalo");
    vars.InitVar("fixedGridRhoFastjetCentralNeutral");
    vars.InitVar("fixedGridRhoFastjetCentralChargedPileUp");

    vars.InitVar("N_TightElectrons", "I");
    vars.InitVar("N_LooseElectrons", "I");
    vars.InitVar("N_TightMuons", "I");
    vars.InitVar("N_LooseMuons", "I");
    vars.InitVar("N_Taus", "I");

    vars.InitVars("LooseJet_E", "N_LooseJets");
    vars.InitVars("LooseJet_M", "N_LooseJets");
    vars.InitVars("LooseJet_Pt", "N_LooseJets");
    vars.InitVars("LooseJet_Phi", "N_LooseJets");
    vars.InitVars("LooseJet_Eta", "N_LooseJets");
    //     vars.InitVars("LooseJet_CSV", "N_LooseJets");
    vars.InitVars("LooseJet_Flav", "N_LooseJets");
    vars.InitVars("LooseJet_PartonFlav", "N_LooseJets");
    vars.InitVars("LooseJet_Charge", "N_LooseJets");
    //     vars.InitVars("LooseJet_PileUpID", "N_LooseJets");
    //     vars.InitVars("LooseJet_PileUpMVA", "N_LooseJets");
    //
    //     vars.InitVars("LooseJet_GenJet_Pt", "N_LooseJets");
    //     vars.InitVars("LooseJet_GenJet_Eta", "N_LooseJets");
    //
    //     vars.InitVars("LooseJet_DeepCSV_b", "N_LooseJets");
    //     vars.InitVars("LooseJet_DeepCSV_bb", "N_LooseJets");
    //     vars.InitVars("LooseJet_DeepCSV_c", "N_LooseJets");
    //     vars.InitVars("LooseJet_DeepCSV_udsg", "N_LooseJets");
    //
    //     vars.InitVars("LooseJet_DeepJetCSV", "N_LooseJets");
    //     vars.InitVars("LooseJet_DeepJet_b", "N_LooseJets");
    //     vars.InitVars("LooseJet_DeepJet_bb", "N_LooseJets");
    //     vars.InitVars("LooseJet_DeepJet_lepb", "N_LooseJets");
    //     vars.InitVars("LooseJet_DeepJet_c", "N_LooseJets");
    //     vars.InitVars("LooseJet_DeepJet_uds", "N_LooseJets");
    //     vars.InitVars("LooseJet_DeepJet_g", "N_LooseJets");

    vars.InitVars("Jet_E", "N_Jets");
    vars.InitVars("Jet_M", "N_Jets");
    vars.InitVars("Jet_Pt", "N_Jets");
    vars.InitVars("Jet_Phi", "N_Jets");
    vars.InitVars("Jet_Eta", "N_Jets");
    vars.InitVars("Jet_CSV", "N_Jets");
    vars.InitVars("Jet_Flav", "N_Jets");
    vars.InitVars("Jet_PartonFlav", "N_Jets");
    vars.InitVars("Jet_Charge", "N_Jets");
    vars.InitVars("Jet_PileUpID", "N_Jets");
    vars.InitVars("Jet_PileUpMVA", "N_Jets");
    vars.InitVars("Jet_CHF", "N_Jets");
    vars.InitVars("Jet_NHF", "N_Jets");
    vars.InitVars("Jet_NEMF", "N_Jets");
    vars.InitVars("Jet_CEMF", "N_Jets");
    vars.InitVars("Jet_MF", "N_Jets");
    vars.InitVars("Jet_Puppi_Multiplicity", "N_Jets");
    vars.InitVars("Jet_Puppi_NeutralMultiplicity", "N_Jets");
    vars.InitVars("Jet_Puppi_ChargedMultiplicity", "N_Jets");
    vars.InitVars("Jet_N_Daughters", "N_Jets");

    vars.InitVars("Jet_GenJet_Pt", "N_Jets");
    vars.InitVars("Jet_GenJet_Eta", "N_Jets");

    //vars.InitVars("Jet_DeepCSV_b", "N_Jets");
    //vars.InitVars("Jet_DeepCSV_bb", "N_Jets");
    //vars.InitVars("Jet_DeepCSV_c", "N_Jets");
    //vars.InitVars("Jet_DeepCSV_udsg", "N_Jets");

    vars.InitVars("Jet_DeepJetCSV", "N_Jets");
    vars.InitVars("Jet_DeepJet_b", "N_Jets");
    vars.InitVars("Jet_DeepJet_bb", "N_Jets");
    vars.InitVars("Jet_DeepJet_lepb", "N_Jets");
    vars.InitVars("Jet_DeepJet_c", "N_Jets");
    vars.InitVars("Jet_DeepJet_uds", "N_Jets");
    vars.InitVars("Jet_DeepJet_g", "N_Jets");

    vars.InitVars("TaggedJet_E", "N_BTagsM");
    vars.InitVars("TaggedJet_M", "N_BTagsM");
    vars.InitVars("TaggedJet_Pt", "N_BTagsM");
    vars.InitVars("TaggedJet_Phi", "N_BTagsM");
    vars.InitVars("TaggedJet_Eta", "N_BTagsM");
    vars.InitVars("TaggedJet_CSV", "N_BTagsM");
    vars.InitVars("TaggedJet_Flav", "N_BTagsM");
    vars.InitVars("TaggedJet_PartonFlav", "N_BTagsM");
    // vars.InitVars("TaggedJet_DeepJetCSV", "N_BTagsM");
    // vars.InitVars("TaggedJet_DeepJet_b", "N_BTagsM");
    // vars.InitVars("TaggedJet_DeepJet_bb", "N_BTagsM");
    // vars.InitVars("TaggedJet_DeepJet_lepb", "N_BTagsM");
    // vars.InitVars("TaggedJet_DeepJet_c", "N_BTagsM");
    // vars.InitVars("TaggedJet_DeepJet_uds", "N_BTagsM");
    // vars.InitVars("TaggedJet_DeepJet_g", "N_BTagsM");
    
    vars.InitVars("LooseTaggedJet_E", "N_BTagsL");
    vars.InitVars("LooseTaggedJet_M", "N_BTagsL");
    vars.InitVars("LooseTaggedJet_Pt", "N_BTagsL");
    vars.InitVars("LooseTaggedJet_Phi", "N_BTagsL");
    vars.InitVars("LooseTaggedJet_Eta", "N_BTagsL");
    vars.InitVars("LooseTaggedJet_CSV", "N_BTagsL");
    vars.InitVars("LooseTaggedJet_Flav", "N_BTagsL");
    vars.InitVars("LooseTaggedJet_PartonFlav", "N_BTagsL");

    vars.InitVars("UntaggedJet_E", "N_NoTags");
    vars.InitVars("UntaggedJet_M", "N_NoTags");
    vars.InitVars("UntaggedJet_Pt", "N_NoTags");
    vars.InitVars("UntaggedJet_Phi", "N_NoTags");
    vars.InitVars("UntaggedJet_Eta", "N_NoTags");
    vars.InitVars("UntaggedJet_CSV", "N_NoTags");
    vars.InitVars("UntaggedJet_Flav", "N_NoTags");
    vars.InitVars("UntaggedJet_PartonFlav", "N_NoTags");

    vars.InitVar("Evt_Pt_MET_Puppi");
    vars.InitVar("Evt_Phi_MET_Puppi");
    vars.InitVar("Gen_Pt_MET_Puppi");
    vars.InitVar("Gen_Phi_MET_Puppi");

    vars.InitVars("CSV", "N_Jets");

    vars.InitVar("N_HEM_Jets", "I");

    vars.InitVar("HT_GenAK4Jets");

    initialized = true;
}

void essentialBasicVarProcessor::Process(const InputCollections& input, VariableContainer& vars)
{
    if (!initialized) cerr << "tree processor not initialized" << endl;

    // also write the event ID for splitting purposes
    long evt_id       = input.eventInfo.evt;
    long run_id       = input.eventInfo.run;
    long lumi_section = input.eventInfo.lumiBlock;

    vars.FillIntVar("Evt_ID", evt_id);
    vars.FillIntVar("Evt_Odd", evt_id % 2);
    vars.FillIntVar("Evt_Run", run_id);
    vars.FillIntVar("Evt_Lumi", lumi_section);
    vars.FillVar("fixedGridRhoAll", input.eventInfo.rhoAll);
    vars.FillVar("fixedGridRhoFastjetAll", input.eventInfo.rhoFastjetAll);
    vars.FillVar("fixedGridRhoFastjetAllCalo", input.eventInfo.rhoFastjetAllCalo);
    vars.FillVar("fixedGridRhoFastjetCentral", input.eventInfo.rhoFastjetCentral);
    vars.FillVar("fixedGridRhoFastjetCentralCalo", input.eventInfo.rhoFastjetCentralCalo);
    vars.FillVar("fixedGridRhoFastjetCentralNeutral", input.eventInfo.rhoFastjetCentralNeutral);
    vars.FillVar("fixedGridRhoFastjetCentralChargedPileUp", input.eventInfo.rhoFastjetCentralChargedPileUp);

    const char*             btagger = "DeepJet";
    std::vector< pat::Jet > selectedTaggedJets;
    std::vector< pat::Jet > selectedTaggedJetsT;
    std::vector< pat::Jet > selectedTaggedJetsL;
    std::vector< pat::Jet > selectedUntaggedJets;
    for (std::vector< pat::Jet >::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet) {
        if (CSVHelper::PassesCSV(*itJet, btagger, CSVHelper::CSVwp::Medium, era))
            selectedTaggedJets.push_back(*itJet);
        else
            selectedUntaggedJets.push_back(*itJet);

        if (CSVHelper::PassesCSV(*itJet, btagger, CSVHelper::CSVwp::Loose, era)) selectedTaggedJetsL.push_back(*itJet);
        if (CSVHelper::PassesCSV(*itJet, btagger, CSVHelper::CSVwp::Tight, era)) selectedTaggedJetsT.push_back(*itJet);
    }

    // Fill Multiplicity Variables
    vars.FillVar("N_GenPVs", input.eventInfo.numTruePV);
    vars.FillVar("N_PrimaryVertices", input.selectedPVs.size());
    vars.FillVar("N_Jets", input.selectedJets.size());
    vars.FillVar("N_LooseJets", input.selectedJetsLoose.size());
    vars.FillVar("N_AK8Jets", input.selectedJetsAK8.size());
    vars.FillVar("N_AK15Jets", input.selectedJetsAK15.size());
    vars.FillVar("N_TightElectrons", input.selectedElectrons.size());
    vars.FillVar("N_LooseElectrons", input.selectedElectronsLoose.size());
    vars.FillVar("N_TightMuons", input.selectedMuons.size());
    vars.FillVar("N_LooseMuons", input.selectedMuonsLoose.size());
    vars.FillVar("N_Taus", input.selectedTaus.size());
    
     // Fill Number of b Tags
    vars.FillVar("N_BTagsM", selectedTaggedJets.size());
    vars.FillVar("N_BTagsL", selectedTaggedJetsL.size());
    vars.FillVar("N_BTagsT", selectedTaggedJetsT.size());
    vars.FillVar("N_NoTags", selectedUntaggedJets.size());

    int N_HEM_Jets = 0;

    // Fill Jet Variables
    // All Jets
    for (std::vector< pat::Jet >::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet) {
        int iJet = itJet - input.selectedJets.begin();
        vars.FillVars("Jet_E", iJet, itJet->energy());
        vars.FillVars("Jet_M", iJet, itJet->mass());
        vars.FillVars("Jet_Pt", iJet, itJet->pt());
        vars.FillVars("Jet_Eta", iJet, itJet->eta());
        vars.FillVars("Jet_Phi", iJet, itJet->phi());
        vars.FillVars("Jet_CSV", iJet, CSVHelper::GetJetCSV(*itJet, btagger));
        vars.FillVars("Jet_Flav", iJet, itJet->hadronFlavour());
        vars.FillVars("Jet_PartonFlav", iJet, itJet->partonFlavour());
        vars.FillVars("Jet_Charge", iJet, itJet->jetCharge());
        vars.FillVars("Jet_N_Daughters", iJet, itJet->numberOfDaughters());

        if (itJet->hasUserFloat("chargedHadronEnergyFraction")) { vars.FillVars("Jet_CHF", iJet, itJet->userFloat("chargedHadronEnergyFraction")); }
        if (itJet->hasUserFloat("neutralHadronEnergyFraction")) { vars.FillVars("Jet_NHF", iJet, itJet->userFloat("neutralHadronEnergyFraction")); }
        if (itJet->hasUserFloat("chargedElectromagneticEnergyFraction")) {
            vars.FillVars("Jet_CEMF", iJet, itJet->userFloat("chargedElectromagneticEnergyFraction"));
        }
        if (itJet->hasUserFloat("neutralElectromagneticEnergyFraction")) {
            vars.FillVars("Jet_NEMF", iJet, itJet->userFloat("neutralElectromagneticEnergyFraction"));
        }
        if (itJet->hasUserFloat("muonEnergyFraction")) { vars.FillVars("Jet_MF", iJet, itJet->userFloat("muonEnergyFraction")); }

        if (itJet->hasUserFloat("patPuppiJetSpecificProducer:puppiMultiplicity")) {
            vars.FillVars("Jet_Puppi_Multiplicity", iJet, itJet->userFloat("patPuppiJetSpecificProducer:puppiMultiplicity"));
        }
        if (itJet->hasUserFloat("patPuppiJetSpecificProducer:neutralPuppiMultiplicity")) {
            vars.FillVars("Jet_Puppi_NeutralMultiplicity", iJet, itJet->userFloat("patPuppiJetSpecificProducer:neutralPuppiMultiplicity"));
        }
        if (itJet->hasUserFloat("patPuppiJetSpecificProducer:puppiMultiplicity") &&
            itJet->hasUserFloat("patPuppiJetSpecificProducer:neutralPuppiMultiplicity")) {
            vars.FillVars(
                "Jet_Puppi_ChargedMultiplicity", iJet,
                itJet->userFloat("patPuppiJetSpecificProducer:puppiMultiplicity") - itJet->userFloat("patPuppiJetSpecificProducer:neutralPuppiMultiplicity"));
        }

        if (itJet->hasUserInt("pileupJetId:fullId")) vars.FillVars("Jet_PileUpID", iJet, itJet->userInt("pileupJetId:fullId"));
        if (itJet->hasUserFloat("pileupJetId:fullDiscriminant"))
            vars.FillVars("Jet_PileUpMVA", iJet, itJet->userFloat("pileupJetId:fullDiscriminant"));

        if (itJet->genJet() != NULL) {
            vars.FillVars("Jet_GenJet_Pt", iJet, itJet->genJet()->pt());
            vars.FillVars("Jet_GenJet_Eta", iJet, itJet->genJet()->eta());
        }
        else {
            vars.FillVars("Jet_GenJet_Pt", iJet, -9.0);
            vars.FillVars("Jet_GenJet_Eta", iJet, -9.0);
        }

        //vars.FillVars("Jet_DeepCSV_b", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probb"));
        //vars.FillVars("Jet_DeepCSV_bb", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probbb"));
        //vars.FillVars("Jet_DeepCSV_c", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probc"));
        //vars.FillVars("Jet_DeepCSV_udsg", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probudsg"));

        vars.FillVars("Jet_DeepJetCSV", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "DeepJet"));
        vars.FillVars("Jet_DeepJet_b", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probb"));
        vars.FillVars("Jet_DeepJet_bb", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probbb"));
        vars.FillVars("Jet_DeepJet_lepb", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:problepb"));
        vars.FillVars("Jet_DeepJet_c", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probc"));
        vars.FillVars("Jet_DeepJet_uds", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probuds"));
        vars.FillVars("Jet_DeepJet_g", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probg"));

        // if (itJet->eta() < -1.4 && itJet->eta() > -3.0 && itJet->phi() < -0.87 && itJet->phi() > -1.57) N_HEM_Jets += 1;
    }

    for (std::vector< pat::Jet >::const_iterator itJet = input.selectedJetsLoose.begin(); itJet != input.selectedJetsLoose.end(); ++itJet) {
        int iJet = itJet - input.selectedJetsLoose.begin();
        vars.FillVars("LooseJet_E", iJet, itJet->energy());
        vars.FillVars("LooseJet_M", iJet, itJet->mass());
        vars.FillVars("LooseJet_Pt", iJet, itJet->pt());
        vars.FillVars("LooseJet_Eta", iJet, itJet->eta());
        vars.FillVars("LooseJet_Phi", iJet, itJet->phi());
        vars.FillVars("LooseJet_Flav", iJet, itJet->hadronFlavour());
        vars.FillVars("LooseJet_PartonFlav", iJet, itJet->partonFlavour());
        vars.FillVars("LooseJet_Charge", iJet, itJet->jetCharge());
        if (itJet->pt() > 30. && itJet->eta() < -1.3 && itJet->eta() > -3.0 && itJet->phi() < -0.87 && itJet->phi() > -1.57) N_HEM_Jets += 1;
    }
    //         vars.FillVars("LooseJet_CSV", iJet, CSVHelper::GetJetCSV(*itJet, btagger));
    //         // vars.FillVars(
    //         // "LooseJet_CSV_DNN",iJet,CSVHelper::GetJetCSV_DNN(*itJet,btagger) );
    //         if (itJet->hasUserInt("pileupJetIdUpdated:fullId")) vars.FillVars("LooseJet_PileUpID", iJet, itJet->userInt("pileupJetIdUpdated:fullId"));
    //         if (itJet->hasUserFloat("pileupJetIdUpdated:fullDiscriminant"))
    //             vars.FillVars("LooseJet_PileUpMVA", iJet, itJet->userFloat("pileupJetIdUpdated:fullDiscriminant"));
    //
    //         if (itJet->genJet() != NULL) {
    //             vars.FillVars("LooseJet_GenJet_Pt", iJet, itJet->genJet()->pt());
    //             vars.FillVars("LooseJet_GenJet_Eta", iJet, itJet->genJet()->eta());
    //         }
    //         else {
    //             vars.FillVars("LooseJet_GenJet_Pt", iJet, -9.0);
    //             vars.FillVars("LooseJet_GenJet_Eta", iJet, -9.0);
    //         }
    //
    //         vars.FillVars("LooseJet_DeepCSV_b", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probb"));
    //         vars.FillVars("LooseJet_DeepCSV_bb", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probbb"));
    //         vars.FillVars("LooseJet_DeepCSV_c", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probc"));
    //         vars.FillVars("LooseJet_DeepCSV_udsg", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probudsg"));
    //
    //         vars.FillVars("LooseJet_DeepJetCSV", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "DeepJet"));
    //         vars.FillVars("LooseJet_DeepJet_b", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probb"));
    //         vars.FillVars("LooseJet_DeepJet_bb", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probbb"));
    //         vars.FillVars("LooseJet_DeepJet_lepb", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:problepb"));
    //         vars.FillVars("LooseJet_DeepJet_c", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probc"));
    //         vars.FillVars("LooseJet_DeepJet_uds", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probuds"));
    //         vars.FillVars("LooseJet_DeepJet_g", iJet, CSVHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probg"));
    //     }

    // Tagged Jets
    for (std::vector< pat::Jet >::iterator itTaggedJet = selectedTaggedJets.begin(); itTaggedJet != selectedTaggedJets.end(); ++itTaggedJet) {
        int iTaggedJet = itTaggedJet - selectedTaggedJets.begin();
        vars.FillVars("TaggedJet_E", iTaggedJet, itTaggedJet->energy());
        vars.FillVars("TaggedJet_M", iTaggedJet, itTaggedJet->mass());
        vars.FillVars("TaggedJet_Pt", iTaggedJet, itTaggedJet->pt());
        vars.FillVars("TaggedJet_Eta", iTaggedJet, itTaggedJet->eta());
        vars.FillVars("TaggedJet_Phi", iTaggedJet, itTaggedJet->phi());
        vars.FillVars("TaggedJet_CSV", iTaggedJet, CSVHelper::GetJetCSV(*itTaggedJet, btagger));
        vars.FillVars("TaggedJet_Flav", iTaggedJet, itTaggedJet->hadronFlavour());
        vars.FillVars("TaggedJet_PartonFlav", iTaggedJet, itTaggedJet->partonFlavour());
        // vars.FillVars("TaggedJet_DeepJetCSV", iTaggedJet, CSVHelper::GetJetCSV_DNN(*itTaggedJet, "DeepJet"));
        // vars.FillVars("TaggedJet_DeepJet_b", iTaggedJet, CSVHelper::GetJetCSV_DNN(*itTaggedJet, "pfDeepFlavourJetTags:probb"));
        // vars.FillVars("TaggedJet_DeepJet_bb", iTaggedJet, CSVHelper::GetJetCSV_DNN(*itTaggedJet, "pfDeepFlavourJetTags:probbb"));
        // vars.FillVars("TaggedJet_DeepJet_lepb", iTaggedJet, CSVHelper::GetJetCSV_DNN(*itTaggedJet, "pfDeepFlavourJetTags:problepb"));
        // vars.FillVars("TaggedJet_DeepJet_c", iTaggedJet, CSVHelper::GetJetCSV_DNN(*itTaggedJet, "pfDeepFlavourJetTags:probc"));
        // vars.FillVars("TaggedJet_DeepJet_uds", iTaggedJet, CSVHelper::GetJetCSV_DNN(*itTaggedJet, "pfDeepFlavourJetTags:probuds"));
        // vars.FillVars("TaggedJet_DeepJet_g", iTaggedJet, CSVHelper::GetJetCSV_DNN(*itTaggedJet, "pfDeepFlavourJetTags:probg"));
    }
    
    for (std::vector< pat::Jet >::iterator itLooseTaggedJet = selectedTaggedJetsL.begin(); itLooseTaggedJet != selectedTaggedJetsL.end(); ++itLooseTaggedJet) {
        int iLooseTaggedJet = itLooseTaggedJet - selectedTaggedJetsL.begin();
        vars.FillVars("LooseTaggedJet_E", iLooseTaggedJet, itLooseTaggedJet->energy());
        vars.FillVars("LooseTaggedJet_M", iLooseTaggedJet, itLooseTaggedJet->mass());
        vars.FillVars("LooseTaggedJet_Pt", iLooseTaggedJet, itLooseTaggedJet->pt());
        vars.FillVars("LooseTaggedJet_Eta", iLooseTaggedJet, itLooseTaggedJet->eta());
        vars.FillVars("LooseTaggedJet_Phi", iLooseTaggedJet, itLooseTaggedJet->phi());
        vars.FillVars("LooseTaggedJet_CSV", iLooseTaggedJet, CSVHelper::GetJetCSV(*itLooseTaggedJet, btagger));
        vars.FillVars("LooseTaggedJet_Flav", iLooseTaggedJet, itLooseTaggedJet->hadronFlavour());
        vars.FillVars("LooseTaggedJet_PartonFlav", iLooseTaggedJet, itLooseTaggedJet->partonFlavour());
    }
    
    for (std::vector< pat::Jet >::iterator itUntaggedJet = selectedUntaggedJets.begin(); itUntaggedJet != selectedUntaggedJets.end(); ++itUntaggedJet) {
        int iUntaggedJet = itUntaggedJet - selectedUntaggedJets.begin();
        vars.FillVars("UntaggedJet_E", iUntaggedJet, itUntaggedJet->energy());
        vars.FillVars("UntaggedJet_M", iUntaggedJet, itUntaggedJet->mass());
        vars.FillVars("UntaggedJet_Pt", iUntaggedJet, itUntaggedJet->pt());
        vars.FillVars("UntaggedJet_Eta", iUntaggedJet, itUntaggedJet->eta());
        vars.FillVars("UntaggedJet_Phi", iUntaggedJet, itUntaggedJet->phi());
        vars.FillVars("UntaggedJet_CSV", iUntaggedJet, CSVHelper::GetJetCSV(*itUntaggedJet, btagger));
        vars.FillVars("UntaggedJet_Flav", iUntaggedJet, itUntaggedJet->hadronFlavour());
        vars.FillVars("UntaggedJet_PartonFlav", iUntaggedJet, itUntaggedJet->partonFlavour());
    }

    vars.FillVar("Evt_Pt_MET_Puppi", input.correctedMETPuppi.corPt(pat::MET::Type1));
    vars.FillVar("Evt_Phi_MET_Puppi", input.correctedMETPuppi.corPhi(pat::MET::Type1));

    if (input.correctedMETPuppi.genMET() != 0) {
        vars.FillVar("Gen_Pt_MET_Puppi", input.correctedMETPuppi.genMET()->pt());
        vars.FillVar("Gen_Phi_MET_Puppi", input.correctedMETPuppi.genMET()->phi());
    }

    // std::vector<math::XYZTLorentzVector> jetvecs =
    // BoostedUtils::GetJetVecs(input.selectedJets); math::XYZTLorentzVector metvec
    // = input.correctedMET.corP4(pat::MET::Type1);

    // Fill CSV Variables
    std::vector< double > csvJets;
    for (std::vector< pat::Jet >::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet)
        csvJets.push_back(CSVHelper::GetJetCSV(*itJet, btagger));

    std::vector< double > csvJetsSorted = csvJets;
    std::sort(csvJetsSorted.begin(), csvJetsSorted.end(), std::greater< double >());

    for (std::vector< double >::iterator itCSV = csvJetsSorted.begin(); itCSV != csvJetsSorted.end(); ++itCSV) {
        int iCSV = itCSV - csvJetsSorted.begin();
        vars.FillVars("CSV", iCSV, *itCSV);
    }

    vars.FillVar("N_HEM_Jets", N_HEM_Jets);

    if (not input.iEvent.isRealData()) {
        float HT_GenAK4Jets = 0.0;
        for (const auto& genjet : input.genJets) { HT_GenAK4Jets += genjet.pt(); }
        vars.FillVar("HT_GenAK4Jets", HT_GenAK4Jets);
    }
}
