#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GENDARKMATTEREVENT_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GENDARKMATTEREVENT_HPP
#include <vector>
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

class GenDarkMatterEvent{
  
    public:
        // constructor
        GenDarkMatterEvent();
        // destructor
        ~GenDarkMatterEvent();
        void Initialize(std::vector<reco::GenParticle> prunedGenParticles_, std::vector<pat::PackedGenParticle> packedGenParticles_);
        std::vector<reco::GenParticle> ReturnPrunedGenParticles();
        std::vector<pat::PackedGenParticle> ReturnPackedGenParticles();
        void Fill();
  
    private:
        bool hasDarkMatter = false;
        std::vector<reco::GenParticle> prunedGenParticles;
        std::vector<pat::PackedGenParticle> packedGenParticles;
        std::vector<reco::GenParticle> Neutralinos;
        reco::GenParticle Mediator;
};


#endif