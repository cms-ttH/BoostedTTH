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
    // which btagger to use
    btagger = "DeepJet";

    // set CSVWp 
    pointerToMVAvars->SetWP(CSVHelper::GetWP(input.era, CSVHelper::CSVwp::Medium, btagger));

    // initialize vars from common classifier
    map<string, float> varMap = pointerToMVAvars->GetVariables();
    for (auto it = varMap.begin(); it != varMap.end(); it++)
        vars.InitVar(it->first);

    initialized = true;
}



void essentialMVAVarProcessor::Process(const InputCollections &input, VariableContainer &vars)
{
    if (!initialized) cerr << "tree processor not initialized" << endl;

    // btag values of jets
    std::vector<double> csvJets;
    for (std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet)
        csvJets.push_back(CSVHelper::GetJetCSV(*itJet, btagger));

    // jet vecs
    std::vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);
    vector<TLorentzVector> jetvecsTL = BoostedUtils::GetTLorentzVectors(jetvecs);

    // lep vecs
    vector<TLorentzVector> lepvecs = BoostedUtils::GetTLorentzVectors(BoostedUtils::GetLepVecs(input.selectedElectrons, input.selectedMuons));

    // met vec
    TLorentzVector metP4 = BoostedUtils::GetTLorentzVector(input.correctedMET.corP4(pat::MET::Type1XY));
  
    // fill variables from common classifier
    varMap = pointerToMVAvars->GetMVAvars(lepvecs, jetvecsTL, csvJets, metP4);
    for (auto it = varMap.begin(); it != varMap.end(); it++)
        vars.FillVar(it->first, it->second);
}
