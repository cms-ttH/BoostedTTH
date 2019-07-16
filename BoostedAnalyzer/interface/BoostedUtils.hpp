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
#include "MiniAOD/BoostedObjects/interface/BoostedJet.h"
#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

namespace BoostedJetDisc {
enum Mode { None };
}

class BoostedUtils {
   public:
    static std::string GetAnalyzerPath();

    static TLorentzVector                GetTLorentzVector(const math::XYZTLorentzVector& vec);
    static std::vector< TLorentzVector > GetTLorentzVectors(const std::vector< math::XYZTLorentzVector >& vec);
    static math::XYZTLorentzVector       GetXYZTLorentzVector(const TLorentzVector& vec);
    static bool                          FirstIsHarder(math::XYZTLorentzVector vec1, math::XYZTLorentzVector vec2);
    static bool                          FirstHasHigherCSV(pat::Jet jet1, pat::Jet jet2);
    static bool                          FirstHasHigherCSVold(pat::Jet jet1, pat::Jet jet2);
    static bool                          FirstJetIsHarder(pat::Jet jet1, pat::Jet jet2);
    static bool                          FirstBoostedJetIsHarder(boosted::BoostedJet jet1, boosted::BoostedJet jet2);

    static float DeltaEta(const math::XYZTLorentzVector& vec1, const math::XYZTLorentzVector& vec2);
    static float DeltaEta(const pat::Jet& jet1, const pat::Jet& jet2);
    static float DeltaPhi(const math::XYZTLorentzVector& vec1, const math::XYZTLorentzVector& vec2);
    static float DeltaPhi(const pat::Jet& jet1, const pat::Jet& jet2);
    static float DeltaR(const math::XYZTLorentzVector& vec1, const math::XYZTLorentzVector& vec2);
    static float DeltaR(const pat::Jet& jet1, const pat::Jet& jet2);
    static float DeltaKt(const math::XYZTLorentzVector& vec1, const math::XYZTLorentzVector& vec2);
    static float DeltaKt(const pat::Jet& jet1, const pat::Jet& jet2);

    static float GetJetCSV(const pat::Jet& jet, const std::string& taggername = "DeepJet");

    static float CosThetaStar(const math::XYZTLorentzVector& vec1, const math::XYZTLorentzVector& vec2);
    static float CosThetaCM(const math::XYZTLorentzVector& vec, const math::XYZTLorentzVector& boostVec);

    static std::vector< math::XYZTLorentzVector > GetLepVecs(const std::vector< pat::Electron >& selectedElectrons,
                                                             const std::vector< pat::Muon >      selectedMuons);
    static math::XYZTLorentzVector GetPrimLepVec(const std::vector< pat::Electron >& selectedElectrons, const std::vector< pat::Muon > selectedMuons);

    static void GetNuVecs(const math::XYZTLorentzVector& lepvec, const TVector2& metvec, math::XYZTLorentzVector& nu1, math::XYZTLorentzVector& nu2);

    static std::vector< math::XYZTLorentzVector > GetJetVecs(const std::vector< pat::Jet >& jets);

    static boosted::BoostedJetCollection GetSortedByPt(boosted::BoostedJetCollection const& boostedjets);

    static bool PassesCSV(const pat::Jet& jet, const char workingPoint = 'M');

    static float GetClosestJetIDs(int& idJet1, int& idJet2, const std::vector< pat::Jet >& jets);
    static float GetClosestLepJetID(int& idJet, const math::XYZTLorentzVector& lepVec, const std::vector< pat::Jet >& jets);

    static float GetJetAverageJetEtaMax(const std::vector< pat::Jet >& jets1, const std::vector< pat::Jet >& jets2);

    static void GetFoxWolframMoments(std::vector< math::XYZTLorentzVector > jetVecs, float& h0, float& h1, float& h2, float& h3, float& h4);
    static void GetAplanaritySphericity(math::XYZTLorentzVector leptonVec, math::XYZTLorentzVector metVec, std::vector< math::XYZTLorentzVector > jetVecs,
                                        float& aplanarity, float& sphericity);

    static boosted::JetType GetBoostedJetType(const boosted::BoostedJet boostedJet, const BoostedJetDisc::Mode mode);

    static void TopSubjetCSVDef(std::vector< pat::Jet >& subjets);

    static std::vector< pat::Jet > GetHiggsFilterJets(const boosted::BoostedJet& boostedJet, const int& nCSVJets = 2, const int& nPtJets = 3);
    static std::vector< pat::Jet > GetHiggsFilterJets(const std::vector< pat::Jet >& higgsDecayJets, const int& nCSVJets = 2, const int& nPtJets = 3);
    static float                   GetHiggsMass(const boosted::BoostedJet& boostedJet, const int& nJets = 2, const int& nCSVJets = 2, const int& nPtJets = 3);

    static std::vector< pat::Jet > GetSingleTopJets(const std::vector< pat::Jet >& centralJets, const std::vector< pat::Jet >& forwardJets, float etacut = 2.4);

    static float GetMuonRelIso(const pat::Muon& iMuon);

    static std::vector< pat::MET > GetCorrectedMET(const std::vector< pat::Jet >& cleanIdJetsForMET, const std::vector< pat::Jet >& correctedJets,
                                                   const std::vector< pat::MET >& correctedMETs);

   private:
};

#endif
