#include "BoostedTTH/BoostedAnalyzer/interface/essentialMVAVarProcessor.hpp"

using namespace std;

essentialMVAVarProcessor::essentialMVAVarProcessor()
{
  pointerToMVAvars.reset(new MVAvars());
}

essentialMVAVarProcessor::~essentialMVAVarProcessor()
{
}

void essentialMVAVarProcessor::Init(const InputCollections &input, VariableContainer &vars)
{
  pointerToMVAvars->SetWP(CSVHelper::GetWP(input.era, CSVHelper::CSVwp::Medium, "DeepJet"));
  // Vars from CommonClassifier:
  map<string, float> varMap = pointerToMVAvars->GetVariables();
  for (auto it = varMap.begin(); it != varMap.end(); it++)
  {
    vars.InitVar(it->first);
  }

  initialized = true;
}

void essentialMVAVarProcessor::Process(const InputCollections &input, VariableContainer &vars)
{
  if (!initialized)
    cerr << "tree processor not initialized" << endl;

  // which btagger to use
  std::string btagger = "DeepJet";

  // csv ordered jets
  std::vector<double> csvJets;
  for (std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet)
  {
    csvJets.push_back(CSVHelper::GetJetCSV(*itJet, btagger));
  }

  // jet vecs
  std::vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);

  // Ohio Variables
  std::vector<pat::Jet> selectedJetsLooseExclusive;
  vector<TLorentzVector> jet_loose_vecsTL;
  vector<double> jetCSV_loose;
  for (std::vector<pat::Jet>::const_iterator itJet = input.selectedJetsLoose.begin(); itJet != input.selectedJetsLoose.end(); ++itJet)
  {
    if (itJet->pt() >= 30)
      continue;
    selectedJetsLooseExclusive.push_back(*itJet);
    jetCSV_loose.push_back(CSVHelper::GetJetCSV(*itJet, btagger));
    jet_loose_vecsTL.push_back(BoostedUtils::GetTLorentzVector(itJet->p4()));
  }
  vector<TLorentzVector> jetvecsTL = BoostedUtils::GetTLorentzVectors(jetvecs);
  

  // Variables from CommonClassifier:
  vector<TLorentzVector> lepvecs = BoostedUtils::GetTLorentzVectors(BoostedUtils::GetLepVecs(input.selectedElectrons, input.selectedMuons));
  TLorentzVector metP4 = BoostedUtils::GetTLorentzVector(input.correctedMET.corP4(pat::MET::Type1XY));

  varMap = pointerToMVAvars->GetMVAvars(lepvecs, jetvecsTL, csvJets, metP4);
  for (auto it = varMap.begin(); it != varMap.end(); it++)
  {
    vars.FillVar(it->first, it->second);
  }
}
