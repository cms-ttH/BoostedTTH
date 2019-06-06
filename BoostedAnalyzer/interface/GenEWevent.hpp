#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GenEWevent_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GenEWevent_HPP
#include <vector>
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include <TLorentzVector.h>

class GenEWevent{
  
    public:
        // constructor
        GenEWevent();
        // destructor
        ~GenEWevent();
        void Initialize(std::vector<reco::GenParticle> prunedGenParticles_, std::vector<pat::PackedGenParticle> packedGenParticles_);
        void Fill();

        std::vector<reco::GenParticle> ReturnPrunedGenParticles() const;
        std::vector<pat::PackedGenParticle> ReturnPackedGenParticles() const;


        bool IsFilled() const;

        // for MC reweighting of Z/W boson + jets events
        void FillBoson();
        bool ZBosonIsFilled() const;
        bool WBosonIsFilled() const;
        bool IsZnunu() const;
        // bool IsZll() const;
        math::XYZTLorentzVector ReturnZBoson() const;
        math::XYZTLorentzVector ReturnWBoson() const;
  
    private:
        bool isFilled = false;
        
        std::vector<reco::GenParticle> prunedGenParticles;
        std::vector<pat::PackedGenParticle> packedGenParticles;
        
        // for MC reweighting of Z/W boson + jets events
        bool hasVectorBoson = false;
        bool ZBosonisFilled = false;
        bool WBosonisFilled = false;
        bool isZnunu = false;
        // bool isZll = false;
        math::XYZTLorentzVector ZBoson;
        math::XYZTLorentzVector WBoson;
};


#endif