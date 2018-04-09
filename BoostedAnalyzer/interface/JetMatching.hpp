#ifndef BOOSTEDTTH_BOOSTEDANALYZER_JETMATCHING_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_JETMATCHING_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

#include "TLorentzVector.h"
#include "TMath.h"
#include "TVector.h"
#include <stdexcept>
#include <vector>

#include "Math/VectorUtil.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "MiniAOD/BoostedObjects/interface/BoostedJet.h"

class JetMatching
{

public:
  static std::vector<pat::Jet> GetFilterjets(
    const boosted::BoostedJetCollection& BoostedJets,
    const float& ptcut = 0.,
    const float& etacut = 10.);
  static std::vector<TLorentzVector> GetMatchedVecs(
    const std::vector<pat::Jet>& filterJets,
    const std::vector<pat::Jet>& jets,
    std::vector<float>& DCSV_Matchedfilterjets,
    std::vector<float>& Dr_Matchedfilterjets);

private:
};

#endif
