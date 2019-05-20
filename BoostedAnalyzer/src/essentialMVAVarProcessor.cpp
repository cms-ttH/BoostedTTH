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

  vars.InitVar("Evt_E_PrimaryLepton");
  vars.InitVar("Evt_M_PrimaryLepton");
  vars.InitVar("Evt_Pt_PrimaryLepton");
  vars.InitVar("Evt_Eta_PrimaryLepton");
  vars.InitVar("Evt_Phi_PrimaryLepton");

  vars.InitVar("Evt_M_MinDeltaRJets");
  vars.InitVar("Evt_M_MinDeltaRTaggedJets");
  vars.InitVar("Evt_M_MinDeltaRUntaggedJets");
  vars.InitVar("Evt_M_MinDeltaRLeptonTaggedJet");
  vars.InitVar("Evt_M_MinDeltaRLeptonJet");

  vars.InitVar("Evt_Dr_MinDeltaRJets");
  vars.InitVar("Evt_Dr_MinDeltaRTaggedJets");
  vars.InitVar("Evt_Dr_MinDeltaRUntaggedJets");
  vars.InitVar("Evt_Dr_MinDeltaRLeptonTaggedJet");
  vars.InitVar("Evt_Dr_MinDeltaRLeptonJet");

  vars.InitVar("Evt_Pt_MinDeltaRJets");
  vars.InitVar("Evt_Pt_MinDeltaRTaggedJets");
  vars.InitVar("Evt_Pt_MinDeltaRUntaggedJets");

  vars.InitVar("Evt_M_JetsAverage");
  vars.InitVar("Evt_M_TaggedJetsAverage");
  vars.InitVar("Evt_M_UntaggedJetsAverage");

  vars.InitVar("Evt_Eta_JetsAverage");
  vars.InitVar("Evt_Eta_TaggedJetsAverage");
  vars.InitVar("Evt_Eta_UntaggedJetsAverage");

  vars.InitVar("Evt_M2_JetsAverage");
  vars.InitVar("Evt_M2_TaggedJetsAverage");
  vars.InitVar("Evt_M2_UntaggedJetsAverage");

  vars.InitVar("Evt_Deta_JetsAverage");
  vars.InitVar("Evt_Deta_TaggedJetsAverage");
  vars.InitVar("Evt_Deta_UntaggedJetsAverage");

  vars.InitVar("Evt_Dr_JetsAverage");
  vars.InitVar("Evt_Dr_TaggedJetsAverage");
  vars.InitVar("Evt_Dr_UntaggedJetsAverage");

  vars.InitVar("Evt_M_TaggedJetsClosestTo125");

  vars.InitVar("Evt_JetPtOverJetE");

  vars.InitVar("Evt_Jet_MaxDeta_Jets");
  vars.InitVar("Evt_TaggedJet_MaxDeta_Jets");
  vars.InitVar("Evt_TaggedJet_MaxDeta_TaggedJets");

  vars.InitVar("Evt_M_MedianTaggedJets");

   // Vars from CommonClassifier:
  map<string, float> varMap = pointerToMVAvars->GetVariables();
  for (auto it = varMap.begin(); it != varMap.end(); it++)
  {
    vars.InitVar("MVA_" + it->first);
  }

  initialized = true;
}

void essentialMVAVarProcessor::Process(const InputCollections &input, VariableContainer &vars)
{
  if (!initialized)
    cerr << "tree processor not initialized" << endl;

  std::string btagger = "DeepJet";
  std::vector<pat::Jet> selectedTaggedJets;
  std::vector<pat::Jet> selectedTaggedJetsT;
  std::vector<pat::Jet> selectedTaggedJetsL;
  std::vector<pat::Jet> selectedUntaggedJets;
  for (std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet)
  {
    if (CSVHelper::PassesCSV(*itJet, btagger, CSVHelper::CSVwp::Medium, input.era))
    {
      selectedTaggedJets.push_back(*itJet);
    }
    else
    {
      selectedUntaggedJets.push_back(*itJet);
    }
    if (CSVHelper::PassesCSV(*itJet, btagger, CSVHelper::CSVwp::Loose, input.era))
    {
      selectedTaggedJetsL.push_back(*itJet);
    }
    if (CSVHelper::PassesCSV(*itJet, btagger, CSVHelper::CSVwp::Tight, input.era))
    {
      selectedTaggedJetsT.push_back(*itJet);
    }
  }

  math::XYZTLorentzVector primLepVec = math::XYZTLorentzVector();
  if (input.selectedElectrons.size() > 0 || input.selectedMuons.size() > 0)
  {
    primLepVec = BoostedUtils::GetPrimLepVec(input.selectedElectrons, input.selectedMuons);
    vars.FillVar("Evt_E_PrimaryLepton", primLepVec.E());
    vars.FillVar("Evt_M_PrimaryLepton", primLepVec.M());
    vars.FillVar("Evt_Pt_PrimaryLepton", primLepVec.Pt());
    vars.FillVar("Evt_Eta_PrimaryLepton", primLepVec.Eta());
    vars.FillVar("Evt_Phi_PrimaryLepton", primLepVec.Phi());
  }

  // Fill CSV Variables
  // All Jets
  std::vector<double> csvJets;
  for (std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet)
  {
    csvJets.push_back(CSVHelper::GetJetCSV(*itJet, btagger));
  }
  std::vector<double> csvJetsSorted = csvJets;
  std::sort(csvJetsSorted.begin(), csvJetsSorted.end(), std::greater<double>());


  // Tagged Jets
  vector<float> csvTaggedJets;
  for (std::vector<pat::Jet>::iterator itTaggedJet = selectedTaggedJets.begin(); itTaggedJet != selectedTaggedJets.end(); ++itTaggedJet)
  {
    csvTaggedJets.push_back(CSVHelper::GetJetCSV(*itTaggedJet, btagger));
  }
  sort(csvTaggedJets.begin(), csvTaggedJets.end(), std::greater<float>());

  // Fill Variables for closest ak4 Jets
  // All Jets
  if (input.selectedJets.size() > 1)
  {
    int idClosestJet1 = -1;
    int idClosestJet2 = -1;
    float minDrJets = BoostedUtils::GetClosestJetIDs(idClosestJet1, idClosestJet2, input.selectedJets);
    math::XYZTLorentzVector closestJetVec1 = input.selectedJets[idClosestJet1].p4();
    math::XYZTLorentzVector closestJetVec2 = input.selectedJets[idClosestJet2].p4();
    vars.FillVar("Evt_M_MinDeltaRJets", (closestJetVec1 + closestJetVec2).M());
    vars.FillVar("Evt_Dr_MinDeltaRJets", minDrJets);
    vars.FillVar("Evt_Pt_MinDeltaRJets", (closestJetVec1 + closestJetVec2).Pt());
  }
  // Tagged Jets
  if (selectedTaggedJets.size() > 1)
  {
    int idClosestTaggedJet1 = -1;
    int idClosestTaggedJet2 = -1;
    float minDrTaggedJets = BoostedUtils::GetClosestJetIDs(idClosestTaggedJet1, idClosestTaggedJet2, selectedTaggedJets);
    math::XYZTLorentzVector closestTaggedJetVec1 = selectedTaggedJets[idClosestTaggedJet1].p4();
    math::XYZTLorentzVector closestTaggedJetVec2 = selectedTaggedJets[idClosestTaggedJet2].p4();
    vars.FillVar("Evt_M_MinDeltaRTaggedJets", (closestTaggedJetVec1 + closestTaggedJetVec2).M());
    vars.FillVar("Evt_Dr_MinDeltaRTaggedJets", minDrTaggedJets);
    vars.FillVar("Evt_Pt_MinDeltaRTaggedJets", (closestTaggedJetVec1 + closestTaggedJetVec2).Pt());
  }
  // Untagged Jets
  if (selectedUntaggedJets.size() > 1)
  {
    int idClosestUntaggedJet1 = -1;
    int idClosestUntaggedJet2 = -1;
    float minDrUntaggedJets = BoostedUtils::GetClosestJetIDs(idClosestUntaggedJet1, idClosestUntaggedJet2, selectedUntaggedJets);
    math::XYZTLorentzVector closestUntaggedJetVec1 = selectedUntaggedJets[idClosestUntaggedJet1].p4();
    math::XYZTLorentzVector closestUntaggedJetVec2 = selectedUntaggedJets[idClosestUntaggedJet2].p4();
    vars.FillVar("Evt_M_MinDeltaRUntaggedJets", (closestUntaggedJetVec1 + closestUntaggedJetVec2).M());
    vars.FillVar("Evt_Dr_MinDeltaRUntaggedJets", minDrUntaggedJets);
    vars.FillVar("Evt_Pt_MinDeltaRUntaggedJets", (closestUntaggedJetVec1 + closestUntaggedJetVec2).Pt());
  }
  // Jet and Lepton
  if (input.selectedJets.size() > 1 && (input.selectedElectrons.size() > 0 || input.selectedMuons.size() > 0))
  {
    int idClosestJet = -1;
    float minDrLepJet = BoostedUtils::GetClosestLepJetID(idClosestJet, primLepVec, input.selectedJets);
    math::XYZTLorentzVector closestJetVec = input.selectedJets[idClosestJet].p4();
    vars.FillVar("Evt_M_MinDeltaRLeptonJet", (primLepVec + closestJetVec).M());
    vars.FillVar("Evt_Dr_MinDeltaRLeptonJet", minDrLepJet);
  }

  // Tagged Jet and Lepton
  if (selectedTaggedJets.size() > 1 && (input.selectedElectrons.size() > 0 || input.selectedMuons.size() > 0))
  {
    int idClosestTaggedJet = -1;
    float minDrLepTaggedJet = BoostedUtils::GetClosestLepJetID(idClosestTaggedJet, primLepVec, selectedTaggedJets);
    math::XYZTLorentzVector closestTaggedJetVec = selectedTaggedJets[idClosestTaggedJet].p4();
    vars.FillVar("Evt_M_MinDeltaRLeptonTaggedJet", (primLepVec + closestTaggedJetVec).M());
    vars.FillVar("Evt_Dr_MinDeltaRLeptonTaggedJet", minDrLepTaggedJet);
  }

  // JetRelation Variables
  // All Jets
  float mJetsAverage = 0;
  float eJetsAverage = 0;
  float ptJetsAverage = 0;
  float etaJetsAverage = 0;
  float m2JetsAverage = 0;
  float detaJetsAverage = 0;
  float drJetsAverage = 0;
  int nPairsJets = 0;

  std::vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);

  for (std::vector<math::XYZTLorentzVector>::iterator itJetVec1 = jetvecs.begin(); itJetVec1 != jetvecs.end(); ++itJetVec1)
  {
    mJetsAverage += itJetVec1->M();
    eJetsAverage += itJetVec1->E();
    ptJetsAverage += itJetVec1->Pt();
    etaJetsAverage += itJetVec1->Eta();

    for (std::vector<math::XYZTLorentzVector>::iterator itJetVec2 = itJetVec1 + 1; itJetVec2 != jetvecs.end(); ++itJetVec2)
    {
      m2JetsAverage += (*itJetVec1 + *itJetVec2).M();
      detaJetsAverage += fabs(itJetVec1->Eta() - itJetVec2->Eta());
      drJetsAverage += BoostedUtils::DeltaR(*itJetVec1, *itJetVec2);
      nPairsJets++;
    }
  }
  if (jetvecs.size() > 0)
  {
    mJetsAverage /= (float)jetvecs.size();
    etaJetsAverage /= (float)jetvecs.size();
  }
  if (nPairsJets > 0)
  {
    m2JetsAverage /= (float)nPairsJets;
    detaJetsAverage /= (float)nPairsJets;
    drJetsAverage /= (float)nPairsJets;
  }
  vars.FillVar("Evt_M_JetsAverage", mJetsAverage);
  vars.FillVar("Evt_Eta_JetsAverage", etaJetsAverage);
  vars.FillVar("Evt_M2_JetsAverage", m2JetsAverage);
  vars.FillVar("Evt_Deta_JetsAverage", detaJetsAverage);
  vars.FillVar("Evt_Dr_JetsAverage", drJetsAverage);
  vars.FillVar("Evt_JetPtOverJetE", ptJetsAverage / eJetsAverage);

  // Tagged Jets
  float mTaggedJetsAverage = 0;
  float etaTaggedJetsAverage = 0;
  float m2TaggedJetsAverage = 0;
  vector<float> m2TaggedJets;
  float m2TaggedJetsClosestTo125 = -999;
  float detaTaggedJetsAverage = 0;
  float drTaggedJetsAverage = 0;

  int nPairsTaggedJets = 0;
  for (std::vector<pat::Jet>::iterator itTaggedJet1 = selectedTaggedJets.begin(); itTaggedJet1 != selectedTaggedJets.end(); ++itTaggedJet1)
  {
    math::XYZTLorentzVector taggedJetVec1 = itTaggedJet1->p4();

    mTaggedJetsAverage += taggedJetVec1.M();
    etaTaggedJetsAverage += taggedJetVec1.Eta();

    for (std::vector<pat::Jet>::iterator itTaggedJet2 = itTaggedJet1 + 1; itTaggedJet2 != selectedTaggedJets.end(); ++itTaggedJet2)
    {
      math::XYZTLorentzVector taggedJetVec2 = itTaggedJet2->p4();

      m2TaggedJets.push_back((taggedJetVec1 + taggedJetVec2).M());
      m2TaggedJetsAverage += m2TaggedJets.back();
      if (fabs(m2TaggedJets.back() - 125) < fabs(m2TaggedJetsClosestTo125 - 125))
        m2TaggedJetsClosestTo125 = m2TaggedJets.back();
      detaTaggedJetsAverage += fabs(taggedJetVec1.Eta() - taggedJetVec2.Eta());
      drTaggedJetsAverage += BoostedUtils::DeltaR(taggedJetVec1, taggedJetVec2);
      nPairsTaggedJets++;
    }
  }
  if (selectedTaggedJets.size() > 0)
  {
    mTaggedJetsAverage /= (float)selectedTaggedJets.size();
    etaTaggedJetsAverage /= (float)selectedTaggedJets.size();
  }
  if (nPairsTaggedJets > 0)
  {
    m2TaggedJetsAverage /= (float)nPairsTaggedJets;
    detaTaggedJetsAverage /= (float)nPairsTaggedJets;
    drTaggedJetsAverage /= (float)nPairsTaggedJets;
  }
  sort(m2TaggedJets.begin(), m2TaggedJets.end(), std::greater<float>());

  vars.FillVar("Evt_M_TaggedJetsAverage", mTaggedJetsAverage);
  vars.FillVar("Evt_Eta_TaggedJetsAverage", etaTaggedJetsAverage);
  vars.FillVar("Evt_M2_TaggedJetsAverage", m2TaggedJetsAverage);
  if (m2TaggedJets.size() > 0)
    vars.FillVar("Evt_M_MedianTaggedJets", m2TaggedJets.at(m2TaggedJets.size() / 2));
  vars.FillVar("Evt_M_TaggedJetsClosestTo125", m2TaggedJetsClosestTo125);
  vars.FillVar("Evt_Deta_TaggedJetsAverage", detaTaggedJetsAverage);
  vars.FillVar("Evt_Dr_TaggedJetsAverage", drTaggedJetsAverage);

  // Untagged Jets
  float mUntaggedJetsAverage = 0;
  float etaUntaggedJetsAverage = 0;
  float m2UntaggedJetsAverage = 0;
  float detaUntaggedJetsAverage = 0;
  float drUntaggedJetsAverage = 0;
  int nPairsUntaggedJets = 0;
  for (std::vector<pat::Jet>::iterator itUntaggedJet1 = selectedUntaggedJets.begin(); itUntaggedJet1 != selectedUntaggedJets.end(); ++itUntaggedJet1)
  {
    math::XYZTLorentzVector untaggedJetVec1 = itUntaggedJet1->p4();

    mUntaggedJetsAverage += untaggedJetVec1.M();
    etaUntaggedJetsAverage += untaggedJetVec1.Eta();

    for (std::vector<pat::Jet>::iterator itUntaggedJet2 = itUntaggedJet1 + 1; itUntaggedJet2 != selectedUntaggedJets.end(); ++itUntaggedJet2)
    {
      math::XYZTLorentzVector untaggedJetVec2 = itUntaggedJet2->p4();
      m2UntaggedJetsAverage += (untaggedJetVec1 + untaggedJetVec2).M();
      detaUntaggedJetsAverage += fabs(untaggedJetVec1.Eta() - untaggedJetVec2.Eta());
      drUntaggedJetsAverage += BoostedUtils::DeltaR(untaggedJetVec1, untaggedJetVec2);
      //       dktUntaggedJetsAverage += BoostedUtils::DeltaKt(untaggedJetVec1,untaggedJetVec2);
      nPairsUntaggedJets++;
    }
  }
  if (selectedUntaggedJets.size() > 0)
  {
    mUntaggedJetsAverage /= (float)selectedUntaggedJets.size();
    etaUntaggedJetsAverage /= (float)selectedUntaggedJets.size();
  }
  if (nPairsUntaggedJets > 0)
  {
    m2UntaggedJetsAverage /= nPairsUntaggedJets;
    detaUntaggedJetsAverage /= nPairsUntaggedJets;
    drUntaggedJetsAverage /= nPairsUntaggedJets;
    //     dktUntaggedJetsAverage /= nPairsUntaggedJets;
  }
  vars.FillVar("Evt_M_UntaggedJetsAverage", mUntaggedJetsAverage);
  vars.FillVar("Evt_Eta_UntaggedJetsAverage", etaUntaggedJetsAverage);
  vars.FillVar("Evt_M2_UntaggedJetsAverage", m2UntaggedJetsAverage);
  vars.FillVar("Evt_Deta_UntaggedJetsAverage", detaUntaggedJetsAverage);
  vars.FillVar("Evt_Dr_UntaggedJetsAverage", drUntaggedJetsAverage);

  // DeltaEta of Jets
  vars.FillVar("Evt_Jet_MaxDeta_Jets", BoostedUtils::GetJetAverageJetEtaMax(input.selectedJets, input.selectedJets));
  vars.FillVar("Evt_TaggedJet_MaxDeta_Jets", BoostedUtils::GetJetAverageJetEtaMax(input.selectedJets, selectedTaggedJets));
  vars.FillVar("Evt_TaggedJet_MaxDeta_TaggedJets", BoostedUtils::GetJetAverageJetEtaMax(selectedTaggedJets, selectedTaggedJets));

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
    vars.FillVar("MVA_" + it->first, it->second);
  }
}
