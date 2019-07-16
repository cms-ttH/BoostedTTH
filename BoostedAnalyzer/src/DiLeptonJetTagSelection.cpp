#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonJetTagSelection.hpp"
using namespace std;

DiLeptonJetTagSelection::DiLeptonJetTagSelection(std::vector< int > minjets_, std::vector< int > mintags_) :
    DiLeptonJetTagSelection(minjets_, std::vector< int >(), mintags_, std::vector< int >())
{
}
DiLeptonJetTagSelection::DiLeptonJetTagSelection(int minjets_, int mintags_) :
    DiLeptonJetTagSelection(std::vector< int >(1, minjets_), std::vector< int >(1, mintags_))
{
}

DiLeptonJetTagSelection::DiLeptonJetTagSelection(std::vector< int > minjets_, std::vector< int > maxjets_, std::vector< int > mintags_,
                                                 std::vector< int > maxtags_) :
    minJets(minjets_),
    maxJets(maxjets_),
    minTags(mintags_),
    maxTags(maxtags_)
{
    selSize = max(max(minJets.size(), maxJets.size()), max(minTags.size(), maxTags.size()));
    for (size_t iSel = 0; iSel < selSize; ++iSel) {
        if (iSel != 0) selName += " or ";
        if (iSel < minJets.size() && minJets[iSel] >= 0) {
            selName += ">=";
            selName += std::to_string(minJets[iSel]);
            selName += " jets with at least pT > 30 ";
        }
        if (iSel < maxJets.size() && maxJets[iSel] >= 0) {
            selName += "<=";
            selName += std::to_string(maxJets[iSel]);
            selName += " jets with at least pT > 30 ";
        }
        if (iSel < minTags.size() && minTags[iSel] >= 0) {
            selName += ">=";
            selName += std::to_string(minTags[iSel]);
            selName += " tags";
        }
        if (iSel < maxTags.size() && maxTags[iSel] >= 0) {
            selName += "<=";
            selName += std::to_string(maxTags[iSel]);
            selName += " tags";
        }
    }
}

DiLeptonJetTagSelection::DiLeptonJetTagSelection(const edm::ParameterSet& iConfig) :
    DiLeptonJetTagSelection(iConfig.getParameter< std::vector< int > >("minJets"), iConfig.getParameter< std::vector< int > >("maxJets"),
                            iConfig.getParameter< std::vector< int > >("minTags"), iConfig.getParameter< std::vector< int > >("maxTags"))
{
}

DiLeptonJetTagSelection::~DiLeptonJetTagSelection() {}

void DiLeptonJetTagSelection::InitCutflow(Cutflow& cutflow)
{
    cutflow.AddStep(selName.c_str());

    initialized = true;
}

bool DiLeptonJetTagSelection::IsSelected(const InputCollections& input, Cutflow& cutflow)
{
    if (!initialized) cerr << "DiLeptonJetTagSelection not initialized" << endl;

    double ptCut = 30.0;
    int    njets = 0;
    int    ntags = 0;
    for (size_t i = 0; i < input.selectedJetsLoose.size(); i++) {
        if (CSVHelper::PassesCSV(input.selectedJetsLoose.at(i), "DeepJet", CSVHelper::CSVwp::Medium, input.era)) { ntags++; }
        if (input.selectedJetsLoose.at(i).pt() >= ptCut) { njets++; }
    }

    for (size_t iSel = 0; iSel < selSize; ++iSel) {
        bool selected = true;

        if (iSel < minJets.size() && minJets[iSel] >= 0 && njets < minJets[iSel]) selected = false;
        if (iSel < maxJets.size() && maxJets[iSel] >= 0 && njets > maxJets[iSel]) selected = false;
        if (iSel < minTags.size() && minTags[iSel] >= 0 && ntags < minTags[iSel]) selected = false;
        if (iSel < maxTags.size() && maxTags[iSel] >= 0 && ntags > maxTags[iSel]) selected = false;

        if (selected) break;

        if (iSel == selSize - 1) return false;
    }
    cutflow.EventSurvivedStep(selName.c_str(), input.weights.at("Weight"));

    return true;
}
