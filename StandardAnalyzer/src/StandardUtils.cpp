#include "BoostedTTH/StandardAnalyzer/interface/StandardUtils.hpp"

using namespace std;

float StandardUtils::GetMuonRelIso(const pat::Muon& iMuon){
  float result = 9999; 

  double pfIsoCharged = iMuon.pfIsolationR04().sumChargedHadronPt;
  double pfIsoNeutral = iMuon.pfIsolationR04().sumNeutralHadronEt + iMuon.pfIsolationR04().sumPhotonEt;

  double pfIsoPUSubtracted = std::max( 0.0, pfIsoNeutral - 0.5*iMuon.pfIsolationR04().sumPUPt );

  result = (pfIsoCharged + pfIsoPUSubtracted)/iMuon.pt();
  
  return result;
}


float StandardUtils::GetElectronRelIso(const pat::Electron& iElectron){
  float result = 9999; 

  double pfIsoCharged = iElectron.pfIsolationVariables().sumChargedHadronPt;
  double pfIsoNeutral = iElectron.pfIsolationVariables().sumNeutralHadronEt + iElectron.pfIsolationVariables().sumPhotonEt;

  double pfIsoPUSubtracted = std::max( 0.0, pfIsoNeutral - 0.5*iElectron.pfIsolationVariables().sumPUPt );

  result = (pfIsoCharged + pfIsoPUSubtracted)/iElectron.pt();
  
  return result;
}

