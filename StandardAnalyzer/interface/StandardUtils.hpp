#ifndef BOOSTEDTTH_STANDARDANALYZER_STANDARDUTILS_HPP
#define BOOSTEDTTH_STANDARDANALYZER_STANDARDUTILS_HPP

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

class StandardUtils{
  
  public:
  
    static float GetMuonRelIso(const pat::Muon& iMuon);
    static float GetElectronRelIso(const pat::Electron& iElectron);
  
  private:
  
};

#endif
