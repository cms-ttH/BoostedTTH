#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMETSelection.hpp"

using namespace std;

DiLeptonMETSelection::DiLeptonMETSelection(const edm::ParameterSet& iConfig)
    : DiLeptonMETSelection(iConfig.getParameter<double>("minMET"),
                           iConfig.getParameter<double>("maxMET")) {}
DiLeptonMETSelection::DiLeptonMETSelection(float minMET_, float maxMET_)
    : minMET(minMET_), maxMET(maxMET_) {}
DiLeptonMETSelection::~DiLeptonMETSelection() {}

void DiLeptonMETSelection::InitCutflow(Cutflow& cutflow) {
  selectionName = "MET > ";
  selectionName += std::to_string(minMET);
  selectionName += " and MET < ";
  selectionName += std::to_string(maxMET);
  cutflow.AddStep(selectionName);

  initialized = true;
}

bool DiLeptonMETSelection::IsSelected(const InputCollections& input,
                                      Cutflow& cutflow) {
  if (!initialized) cerr << "METSelection not initialized" << endl;

  int nleadelectrons_p = 0;
  int nleadelectrons_n = 0;

  for (auto e = input.selectedElectronsDL.begin();
       e != input.selectedElectronsDL.end(); e++) {
    if (e->charge() > 0)
      nleadelectrons_p++;
    else
      nleadelectrons_n++;
  }

  int nleadelectrons = nleadelectrons_p + nleadelectrons_n;

  int nsubleadelectrons_p = 0;
  int nsubleadelectrons_n = 0;

  for (auto e = input.selectedElectronsLoose.begin();
       e != input.selectedElectronsLoose.end(); e++) {
    bool leadID = false;

    for (auto le = input.selectedElectronsDL.begin();
         le != input.selectedElectronsDL.end(); le++) {
      if (BoostedUtils::DeltaR(le->p4(), e->p4()) < 0.001) {
        leadID = true;
        break;
      }
    }

    if (leadID) continue;

    if (e->charge() > 0)
      nsubleadelectrons_p++;
    else
      nsubleadelectrons_n++;
  }

  int nelectrons_p = nleadelectrons_p + nsubleadelectrons_p;
  int nelectrons_n = nleadelectrons_n + nsubleadelectrons_n;

  int nleadmuons_p = 0;
  int nleadmuons_n = 0;

  for (auto e = input.selectedMuonsDL.begin(); e != input.selectedMuonsDL.end();
       e++) {
    if (e->charge() > 0)
      nleadmuons_p++;
    else
      nleadmuons_n++;
  }

  int nleadmuons = nleadmuons_p + nleadmuons_n;

  int nsubleadmuons_p = 0;
  int nsubleadmuons_n = 0;

  for (auto mu = input.selectedMuonsLoose.begin();
       mu != input.selectedMuonsLoose.end(); mu++) {
    bool leadID = false;

    for (auto lmu = input.selectedMuonsDL.begin();
         lmu != input.selectedMuonsDL.end(); lmu++) {
      if (BoostedUtils::DeltaR(lmu->p4(), mu->p4()) < 0.001) {
        leadID = true;
        break;
      }
    }

    if (leadID) continue;

    if (mu->charge() > 0)
      nsubleadmuons_p++;
    else
      nsubleadmuons_n++;
  }

  int nmuons_p = nleadmuons_p + nsubleadmuons_p;
  int nmuons_n = nleadmuons_n + nsubleadmuons_n;

  int nleadleptons = nleadelectrons + nleadmuons;

  if (nleadleptons >= 1 && ((nelectrons_p == 1 && nmuons_n == 1 &&
                             nelectrons_n == 0 && nmuons_p == 0) ||
                            (nelectrons_n == 1 && nmuons_p == 1 &&
                             nelectrons_p == 0 && nmuons_n == 0))) {
    cutflow.EventSurvivedStep(selectionName, input.weights.at("Weight"));
    return true;
  }

  double met = input.correctedMET.corPt(pat::MET::Type1XY);
  if (met > minMET && met < maxMET) {
    cutflow.EventSurvivedStep(selectionName, input.weights.at("Weight"));
    return true;
  }

  return false;
}
