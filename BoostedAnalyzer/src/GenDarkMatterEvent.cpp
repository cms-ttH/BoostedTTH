#include "BoostedTTH/BoostedAnalyzer/interface/GenDarkMatterEvent.hpp"

// constructor
GenDarkMatterEvent::GenDarkMatterEvent() {}

// desturctor
GenDarkMatterEvent::~GenDarkMatterEvent() {}

// take the given genparticle collections and save a copy of them as member variables
void GenDarkMatterEvent::Initialize(std::vector<reco::GenParticle> prunedGenParticles_, std::vector<pat::PackedGenParticle> packedGenParticles_)
{
    prunedGenParticles = prunedGenParticles_;
    packedGenParticles = packedGenParticles_;
    
    hasDarkMatter = false;
    
    for(size_t i=0;i<prunedGenParticles.size();i++){
        if(prunedGenParticles[i].pdgId()==1000022){
            hasDarkMatter = true;
            break;
        }
    }
}

// return the prunedGenParticles collection
std::vector<reco::GenParticle> GenDarkMatterEvent::ReturnPrunedGenParticles()
{
    return prunedGenParticles;
}

// return the packedGenParticles collection
std::vector<pat::PackedGenParticle> GenDarkMatterEvent::ReturnPackedGenParticles()
{
    return packedGenParticles;
}

// fill the DarkMatter Event by retrieving all the needed information from the genparticle collections
void GenDarkMatterEvent::Fill() 
{
    if(not hasDarkMatter) {
        std::cout << "The Generator Event does not have a Dark Matter particle with PDGID 1000022 (lightest neutralino)." << std::endl;
        std::cout << "Therefore, the GenDarkMatterEvent cannot be filled." << std::endl;
        return;
    }
    
    // find the lightest neutralinos in the event and the mediator
    for(size_t i=0;i<prunedGenParticles.size();i++){
        reco::GenParticle genparticle = prunedGenParticles[i];
        if(genparticle.pdgId()==1000022 and genparticle.isLastCopy()){
            Neutralinos.push_back(genparticle);
        }
        if(genparticle.pdgId()==23 and genparticle.isLastCopy()) {
            Mediator = genparticle;
        }
    }
}