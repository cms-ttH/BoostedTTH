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
    
    hasVectorBoson = false;
    WBosonisFilled = false;
    ZBosonisFilled = false;
    
    int n_decay_prods = 0;
    
    for(size_t i=0;i<prunedGenParticles.size();i++){
        if(prunedGenParticles[i].pdgId()==1000022 or abs(prunedGenParticles[i].pdgId())==18){
            hasDarkMatter = true;
            //break;
        }
        if((abs(prunedGenParticles[i].pdgId()) == 11 or abs(prunedGenParticles[i].pdgId()) == 12 or abs(prunedGenParticles[i].pdgId()) == 13 or abs(prunedGenParticles[i].pdgId()) == 14 or abs(prunedGenParticles[i].pdgId()) == 15 or abs(prunedGenParticles[i].pdgId()) == 16) and prunedGenParticles[i].isPromptFinalState()){
            n_decay_prods+=1;
        }
    }
    if(n_decay_prods>=2) hasVectorBoson = true;
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
        //std::cout << "The Generator Event does not have a Dark Matter particle with PDGID 1000022 (lightest neutralino)." << std::endl;
        //std::cout << "Therefore, the GenDarkMatterEvent cannot be filled." << std::endl;
        return;
    }
    
    // find the lightest neutralinos in the event, the mediator, and neutrinos
    for(size_t i=0;i<prunedGenParticles.size();i++){
        reco::GenParticle genparticle = prunedGenParticles[i];
        if((genparticle.pdgId()==1000022 or abs(genparticle.pdgId())==18) and genparticle.status()==1){
            Neutralinos.push_back(genparticle);
        }
        if((genparticle.pdgId()==23 || genparticle.pdgId()==25 || genparticle.pdgId()==55) and genparticle.isLastCopy()) {
            Mediator = genparticle;
        }
        if((abs(genparticle.pdgId())==12 or abs(genparticle.pdgId())==14 or abs(genparticle.pdgId())==16) and genparticle.status()==1){
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

// for MC reweighting of Z/W boson + jets events: save the pt of the generator v boson

void GenDarkMatterEvent::FillBoson()
{
    if (not hasVectorBoson) {
        //std::cout << "The Generator Event does not have a VectorBoson with PDGID 23 or 24 (Z/W)." << std::endl;
        //std::cout << "Therefore, the Boson cannot be filled." << std::endl;
        return;
    }
    std::vector<reco::GenParticle> decay_prodW;
    std::vector<reco::GenParticle> decay_prodZ;
    std::vector<reco::GenParticle> radiated_photons;
    //std::cout << "doing Boson stuff" << std::endl;
    //std::cout << "looping over " << prunedGenParticles.size() << " genParticles" << std::endl;
    for (size_t i = 0; i < prunedGenParticles.size(); i++) {
        const reco::GenParticle & genparticle = prunedGenParticles[i];
        
        //Z Bosons
        if ((abs(genparticle.pdgId()) == 12 or abs(genparticle.pdgId()) == 14 or abs(genparticle.pdgId()) == 16) and genparticle.isPromptFinalState())  {
            decay_prodZ.push_back(genparticle);
        }
        

        //W Bosons
        if ((abs(genparticle.pdgId()) == 11 or abs(genparticle.pdgId()) == 12 or abs(genparticle.pdgId()) == 13 or abs(genparticle.pdgId()) == 14) and genparticle.isPromptFinalState()) {//or abs(daughter->pdgId()) == 15 or abs(daughter->pdgId()) == 16
            decay_prodW.push_back(genparticle);
        }
        
        if(abs(genparticle.pdgId())==22 and genparticle.status()==1 and !genparticle.statusFlags().isPrompt()) {
            radiated_photons.push_back(genparticle);
        }
                
  
    }
    if (decay_prodW.size() == 2){
        //std::cout << "filling W Boson" << std::endl;
        if((decay_prodW.at(0).pdgId())*(decay_prodW.at(1).pdgId())<0 and abs(abs(decay_prodW.at(0).pdgId())-abs(decay_prodW.at(1).pdgId()))==1){
            for(size_t k=0;k<decay_prodW.size();k++){
                if(abs(decay_prodW.at(k).pdgId())==11 or abs(decay_prodW.at(k).pdgId())==13){
                    for(size_t l=0;l<radiated_photons.size();l++){
                        if(reco::deltaR(radiated_photons.at(l).p4(),decay_prodW.at(k).p4())<0.1){
                            decay_prodW.at(k).setP4(decay_prodW.at(k).p4()+radiated_photons.at(l).p4());
                        }
                    }
                }
            }
            WBoson = decay_prodW.at(0).p4() + decay_prodW.at(1).p4();
            WBosonisFilled = true;
        }
    }
    if (decay_prodZ.size() == 2){
        //std::cout << "filling Z Boson" << std::endl;
        if((decay_prodZ.at(0).pdgId())+(decay_prodZ.at(1).pdgId())==0){
            ZBoson = decay_prodZ.at(0).p4() + decay_prodZ.at(1).p4();
            ZBosonisFilled = true;
        }
    }
}

// return if the WBoson has been filled
bool GenDarkMatterEvent::WBosonIsFilled() const
{
    return WBosonisFilled;
}

// return if the ZBoson has been filled
bool GenDarkMatterEvent::ZBosonIsFilled() const
{
    return ZBosonisFilled;
}

math::XYZTLorentzVector GenDarkMatterEvent::ReturnWBoson() const
{
    if (not WBosonisFilled) {
        std::cerr << "Attention: WBoson is not filled!";
    }
    return WBoson;
}

math::XYZTLorentzVector GenDarkMatterEvent::ReturnZBoson() const
{
    if (not ZBosonisFilled) {
        std::cerr << "Attention: ZBoson is not filled!";
    }
    return ZBoson;
}
