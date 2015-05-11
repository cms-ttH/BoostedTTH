#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDUTILS_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDUTILS_HPP

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
#include "BoostedTTH/BoostedObjects/interface/HEPTopJet.h"


class BoostedUtils{
  
  public:
    
    static std::string GetAnalyzerPath();
    
    static TLorentzVector GetTLorentzVector(const math::XYZTLorentzVector& vec);
    static std::vector<TLorentzVector> GetTLorentzVectors(const std::vector<math::XYZTLorentzVector>& vec);
    static math::XYZTLorentzVector GetXYZTLorentzVector(const TLorentzVector& vec);   
    static bool FirstIsHarder(math::XYZTLorentzVector vec1,math::XYZTLorentzVector vec2);
    static bool FirstHasHigherCSV(pat::Jet jet1,pat::Jet jet2);
    static bool FirstHasHigherCSVold(pat::Jet jet1,pat::Jet jet2);
    static bool FirstJetIsHarder(pat::Jet jet1, pat::Jet jet2);
    template<typename boostedJetType>
    static bool FirstFatJetIsHarder(boostedJetType jet1, boostedJetType jet2){
      return BoostedUtils::FirstJetIsHarder(jet1.fatjet,jet2.fatjet);
    }
    
    static float DeltaEta(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2);
    static float DeltaEta(const pat::Jet& jet1,const pat::Jet& jet2);
    static float DeltaPhi(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2);
    static float DeltaPhi(const pat::Jet& jet1,const pat::Jet& jet2);
    static float DeltaR(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2);
    static float DeltaR(const pat::Jet& jet1,const pat::Jet& jet2);
    static float DeltaKt(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2);
    static float DeltaKt(const pat::Jet& jet1,const pat::Jet& jet2);
    
    static float CosThetaStar(const math::XYZTLorentzVector& vec1, const math::XYZTLorentzVector& vec2);
    static float CosThetaCM(const math::XYZTLorentzVector& vec,const math::XYZTLorentzVector& boostVec);
    
    static std::vector<math::XYZTLorentzVector> GetLepVecs(const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon> selectedMuons);
    static math::XYZTLorentzVector GetPrimLepVec(const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon> selectedMuons);
    
    static void GetNuVecs(const math::XYZTLorentzVector& lepvec, const TVector2& metvec, math::XYZTLorentzVector& nu1, math::XYZTLorentzVector& nu2);
    
    static std::vector<math::XYZTLorentzVector> GetJetVecs(const std::vector<pat::Jet>& jets);
    
    static boosted::SubFilterJetCollection GetSortedByPt(boosted::SubFilterJetCollection const &subfilterjets);
    static boosted::HEPTopJetCollection GetSortedByPt(boosted::HEPTopJetCollection const &heptopjets);
    
    static bool PassesCSV(const pat::Jet& jet, const char workingPoint='M');
    
    static float GetClosestJetIDs(int& idJet1, int& idJet2, const std::vector<pat::Jet>& jets);
    static float GetClosestLepJetID(int& idJet, const math::XYZTLorentzVector& lepVec, const std::vector<pat::Jet>& jets);
    
    static float GetJetAverageJetEtaMax(const std::vector<pat::Jet>& jets1, const std::vector<pat::Jet>& jets2);
        
    static bool GetTopTag(const boosted::HEPTopJet& topJet,const double& fW = 0.15, const double& mTopMin = 120, const bool& altConf = false);
    static void TopSubjetCSVDef(std::vector<pat::Jet> &subjets);
    
    static std::vector<pat::Jet> GetHiggsFilterJets(const boosted::SubFilterJet& higgsJet, const int& nCSVJets = 2);
    static std::vector<pat::Jet> GetHiggsFilterJets(const std::vector<pat::Jet>& higgsDecayJets, const int& nCSVJets = 2);
    static float GetHiggsMass(const boosted::SubFilterJet& higgsJet, const int& nFilterJets = 2, const int& nBTags = 2, const float& csvWP = 0.679);
  
  private:
  
};

#endif
