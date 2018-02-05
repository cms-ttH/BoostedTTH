#include "BoostedTTH/BoostedAnalyzer/interface/GenDarkMatterEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

// constructor
GenDarkMatterEvent::GenDarkMatterEvent() {}

// destructor
GenDarkMatterEvent::~GenDarkMatterEvent() {}

// take the given genparticle collections and save a copy of them as member variables
void GenDarkMatterEvent::Initialize(std::vector<reco::GenParticle> prunedGenParticles_, std::vector<pat::PackedGenParticle> packedGenParticles_)
{
    prunedGenParticles = prunedGenParticles_;
    packedGenParticles = packedGenParticles_;
    
    hasDarkMatter = false;
    isFilled = false;
    
    for(size_t i=0;i<prunedGenParticles.size();i++){
        if(prunedGenParticles[i].pdgId()==1000022){
            hasDarkMatter = true;
            break;
        }
    }
}

// return the prunedGenParticles collection
std::vector<reco::GenParticle> GenDarkMatterEvent::ReturnPrunedGenParticles() const
{
    return prunedGenParticles;
}

// return the packedGenParticles collection
std::vector<pat::PackedGenParticle> GenDarkMatterEvent::ReturnPackedGenParticles() const
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
    
    // find the lightest neutralinos in the event, the mediator, and neutrinos
    for(size_t i=0;i<prunedGenParticles.size();i++){
        reco::GenParticle genparticle = prunedGenParticles[i];
        if(genparticle.pdgId()==1000022 and genparticle.isLastCopy() and genparticle.status()==1){
            Neutralinos.push_back(genparticle);
        }
        if((genparticle.pdgId()==23 || genparticle.pdgId()==25) and genparticle.isLastCopy()) {
            Mediator = genparticle;
        }
        if((abs(genparticle.pdgId())==12 or abs(genparticle.pdgId())==14 or abs(genparticle.pdgId())==16) and genparticle.isLastCopy() and genparticle.status()==1){
            Neutrinos.push_back(genparticle);
        }
    }
    isFilled = true;
}

// return the lightest neutralinos in a vector
std::vector<reco::GenParticle> GenDarkMatterEvent::ReturnNeutralinos() const
{
    if(not isFilled){
        std::cerr << "Attention: Neutralinos are not filled!";
    }
    return Neutralinos;
}

// return the mediator particle
reco::GenParticle GenDarkMatterEvent::ReturnMediator() const
{
    if(not isFilled){
        std::cerr << "Attention: Mediator is not filled!";
    }
    return Mediator;
}

// return the neutrinos in a vector
std::vector<reco::GenParticle> GenDarkMatterEvent::ReturnNeutrinos() const
{
    if(not isFilled){
        std::cerr << "Attention: Neutrinos are not filled!";
    }
    return Neutrinos;
}

// return if the GenDarkMatterEvent has been filled
bool GenDarkMatterEvent::IsFilled() const
{
    return isFilled;
}

// return if the event has at least one lightest neutralino (PDGID 1000022)
bool GenDarkMatterEvent::HasDarkMatter() const
{
    return hasDarkMatter;
}

//return the mass of the mediator particle
double GenDarkMatterEvent::ReturnMediatorMass() const
{
    return Mediator.mass();
}

// return the masses of the neutralinos in a vector
std::vector<double> GenDarkMatterEvent::ReturnNeutralinoMasses() const
{
    std::vector<double> masses;
    for(size_t i=0;i<Neutralinos.size();i++){
        masses.push_back(Neutralinos[i].mass());
    }
    return masses;
}

// return the 4-vector of the mediator particle
TLorentzVector GenDarkMatterEvent::ReturnMediator4Vector() const
{
    math::XYZTLorentzVector vec4 = Mediator.p4();
    return BoostedUtils::GetTLorentzVector(vec4);
}

// return the 4-vectors of the neutralinos in a vector
std::vector<TLorentzVector> GenDarkMatterEvent::ReturnNeutralino4Vectors() const
{
    std::vector<math::XYZTLorentzVector> vecs4;
    for(size_t i=0;i<Neutralinos.size();i++){
        vecs4.push_back(Neutralinos[i].p4());
    }
    return BoostedUtils::GetTLorentzVectors(vecs4);
}

// return the 4-vectors of the neutrinos in a vector
std::vector<TLorentzVector> GenDarkMatterEvent::ReturnNeutrino4Vectors() const
{
    std::vector<math::XYZTLorentzVector> vecs4;
    for(size_t i=0;i<Neutrinos.size();i++){
        vecs4.push_back(Neutrinos[i].p4());
    }
    return BoostedUtils::GetTLorentzVectors(vecs4);
}

// returns a naively calculated MET
// naively MET should be the pt of the sum of neutralinos and neutrinos 4-vectors
double GenDarkMatterEvent::ReturnNaiveMET() const
{
    math::XYZTLorentzVector vec4_invisibles;
    for(size_t i=0;i<Neutralinos.size();i++){
        vec4_invisibles+=Neutralinos[i].p4();
    }
    for(size_t i=0;i<Neutrinos.size();i++){
        vec4_invisibles+=Neutrinos[i].p4();
    }
    return vec4_invisibles.pt();
}
