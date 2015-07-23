#ifndef BOOSTEDTTH_BOOSTEDANALYZER_JETMATCHING_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_JETMATCHING_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

#include <vector>
#include <stdexcept>
#include "TMath.h"
#include "TVector.h"
#include "TLorentzVector.h"

#include "Math/VectorUtil.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "BoostedTTH/BoostedObjects/interface/SubFilterJet.h"
#include "BoostedTTH/BoostedObjects/interface/HTTTopJet.h"


class JetMatching{
  
  public:

    static std::vector<pat::Jet> GetFilterjets(const boosted::SubFilterJetCollection& subfilterJets, const float& ptcut = 0., const float& etacut = 10.);
    static std::vector<pat::Jet> GetFilterjets(const boosted::HTTTopJetCollection& htttopjets, const float& ptcut = 0., const float& etacut = 10.);
    static std::vector<TLorentzVector> GetMatchedVecs(const std::vector<pat::Jet>& filterJets, const std::vector<pat::Jet>& jets, std::vector<float>& DCSV_Matchedfilterjets, std::vector<float>& Dr_Matchedfilterjets);
  
  private:
  
};

#endif
