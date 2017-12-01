#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GENDARKMATTEREVENT_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GENDARKMATTEREVENT_HPP
#include <vector>
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include <TLorentzVector.h>

class GenDarkMatterEvent{
  
    public:
        // constructor
        GenDarkMatterEvent();
        // destructor
        ~GenDarkMatterEvent();
        void Initialize(std::vector<reco::GenParticle> prunedGenParticles_, std::vector<pat::PackedGenParticle> packedGenParticles_);
        void Fill();
        
        std::vector<reco::GenParticle> ReturnPrunedGenParticles();
        std::vector<pat::PackedGenParticle> ReturnPackedGenParticles();
        
        reco::GenParticle ReturnMediator();
        std::vector<reco::GenParticle> ReturnNeutralinos();
        
        bool HasDarkMatter();
        bool IsFilled();
        
        double ReturnMediatorMass();
        TLorentzVector ReturnMediator4Vector();
        std::vector<double> ReturnNeutralinoMasses();
        std::vector<TLorentzVector> ReturnNeutralino4Vectors();
        
        double ReturnNaiveMET();
  
    private:
        bool hasDarkMatter = false;
        bool isFilled = false;
        std::vector<reco::GenParticle> prunedGenParticles;
        std::vector<pat::PackedGenParticle> packedGenParticles;
        std::vector<reco::GenParticle> Neutralinos;
        reco::GenParticle Mediator;
        std::vector<reco::GenParticle> Neutrinos;
};


#endif