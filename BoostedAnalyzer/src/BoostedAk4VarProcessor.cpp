#include "BoostedTTH/BoostedAnalyzer/interface/BoostedAk4VarProcessor.hpp"

using namespace std;

BoostedAk4VarProcessor::BoostedAk4VarProcessor() {}
BoostedAk4VarProcessor::~BoostedAk4VarProcessor() {}

void BoostedAk4VarProcessor::Init(const InputCollections& input,
                                  VariableContainer& vars) {
  vars.InitVars("BoostedAk4Cluster_E", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_M", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Pt", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Phi", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Eta", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_N_Ak4Jets", -9, "N_BoostedAk4Cluster");

  vars.InitVars("BoostedAk4Cluster_Dr_Ak4Cluster_BoostedJet1", -9,
                "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Dr_Ak4Cluster_BoostedJet2", -9,
                "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Dr_Ak4Cluster_BoostedJet3", -9,
                "N_BoostedAk4Cluster");

  vars.InitVars("BoostedAk4Cluster_Ak4Jet1_E", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet1_M", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet1_Pt", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet1_Phi", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet1_Eta", -9, "N_BoostedAk4Cluster");

  vars.InitVars("BoostedAk4Cluster_Ak4Jet2_E", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet2_M", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet2_Pt", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet2_Phi", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet2_Eta", -9, "N_BoostedAk4Cluster");

  vars.InitVars("BoostedAk4Cluster_Ak4Jet3_E", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet3_M", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet3_Pt", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet3_Phi", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet3_Eta", -9, "N_BoostedAk4Cluster");

  vars.InitVars("BoostedAk4Cluster_Ak4Jet4_E", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet4_M", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet4_Pt", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet4_Phi", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet4_Eta", -9, "N_BoostedAk4Cluster");

  vars.InitVars("BoostedAk4Cluster_Ak4Jet5_E", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet5_M", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet5_Pt", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet5_Phi", -9, "N_BoostedAk4Cluster");
  vars.InitVars("BoostedAk4Cluster_Ak4Jet5_Eta", -9, "N_BoostedAk4Cluster");

  initialized = true;
}

void BoostedAk4VarProcessor::Process(const InputCollections& input,
                                     VariableContainer& vars) {
  if (!initialized) cerr << "tree processor not initialized" << endl;

  for (int unsigned i = 0; i < input.selectedAk4Cluster.size(); ++i) {
    vars.FillVars("BoostedAk4Cluster_E", i,
                  input.selectedAk4Cluster[i].fatjet.E());
    vars.FillVars("BoostedAk4Cluster_Pt", i,
                  input.selectedAk4Cluster[i].fatjet.Pt());
    vars.FillVars("BoostedAk4Cluster_M", i,
                  input.selectedAk4Cluster[i].fatjet.M());
    vars.FillVars("BoostedAk4Cluster_Eta", i,
                  input.selectedAk4Cluster[i].fatjet.Eta());
    vars.FillVars("BoostedAk4Cluster_Phi", i,
                  input.selectedAk4Cluster[i].fatjet.Phi());
    vars.FillVars("BoostedAk4Cluster_N_Ak4Jets", i,
                  input.selectedAk4Cluster[i].ak4jets.size());

    for (std::vector<pat::Jet>::const_iterator itAk4Jet =
             input.selectedAk4Cluster[i].ak4jets.begin();
         itAk4Jet != input.selectedAk4Cluster[i].ak4jets.end() &&
         itAk4Jet - input.selectedAk4Cluster[i].ak4jets.begin() < 5;
         ++itAk4Jet) {
      string iAk4JetNumber = std::to_string(
          itAk4Jet - input.selectedAk4Cluster[i].ak4jets.begin() + 1);
      vars.FillVars("BoostedAk4Cluster_Ak4Jet" + iAk4JetNumber + "_E", i,
                    itAk4Jet->energy());
      vars.FillVars("BoostedAk4Cluster_Ak4Jet" + iAk4JetNumber + "_M", i,
                    itAk4Jet->mass());
      vars.FillVars("BoostedAk4Cluster_Ak4Jet" + iAk4JetNumber + "_Pt", i,
                    itAk4Jet->pt());
      vars.FillVars("BoostedAk4Cluster_Ak4Jet" + iAk4JetNumber + "_Phi", i,
                    itAk4Jet->phi());
      vars.FillVars("BoostedAk4Cluster_Ak4Jet" + iAk4JetNumber + "_Eta", i,
                    itAk4Jet->eta());
    }

    if (input.selectedBoostedJets.size() > 0)
      vars.FillVars(
          "BoostedAk4Cluster_Dr_Ak4Cluster_BoostedJet1", i,
          BoostedUtils::DeltaR(input.selectedAk4Cluster[i].fatjet,
                               input.selectedBoostedJets[0].fatjet.p4()));
    if (input.selectedBoostedJets.size() > 1)
      vars.FillVars(
          "BoostedAk4Cluster_Dr_Ak4Cluster_BoostedJet2", i,
          BoostedUtils::DeltaR(input.selectedAk4Cluster[i].fatjet,
                               input.selectedBoostedJets[1].fatjet.p4()));
    if (input.selectedBoostedJets.size() > 2)
      vars.FillVars(
          "BoostedAk4Cluster_Dr_Ak4Cluster_BoostedJet3", i,
          BoostedUtils::DeltaR(input.selectedAk4Cluster[i].fatjet,
                               input.selectedBoostedJets[2].fatjet.p4()));
  }
}
