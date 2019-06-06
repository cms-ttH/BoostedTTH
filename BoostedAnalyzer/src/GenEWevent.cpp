#include "BoostedTTH/BoostedAnalyzer/interface/GenEWevent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

// constructor
GenEWevent::GenEWevent() {}

// destructor
GenEWevent::~GenEWevent() {}

// take the given genparticle collections and save a copy of them as member variables
void GenEWevent::Initialize(std::vector<reco::GenParticle> prunedGenParticles_, std::vector<pat::PackedGenParticle> packedGenParticles_)
{
    prunedGenParticles = prunedGenParticles_;
    packedGenParticles = packedGenParticles_;
    
    isFilled = false;
    
    hasVectorBoson = false;
    WBosonisFilled = false;
    ZBosonisFilled = false;
    
    int n_decay_prods = 0;
    
    for(size_t i=0;i<prunedGenParticles.size();i++){
        if((abs(prunedGenParticles[i].pdgId()) == 11 or abs(prunedGenParticles[i].pdgId()) == 12 or 
            abs(prunedGenParticles[i].pdgId()) == 13 or abs(prunedGenParticles[i].pdgId()) == 14 or 
            abs(prunedGenParticles[i].pdgId()) == 15 or abs(prunedGenParticles[i].pdgId()) == 16) 
            and prunedGenParticles[i].isPromptFinalState()){
            n_decay_prods+=1;
        }
    }
    if(n_decay_prods>=2) hasVectorBoson = true;
}

// return the prunedGenParticles collection
std::vector<reco::GenParticle> GenEWevent::ReturnPrunedGenParticles() const
{
    return prunedGenParticles;
}

// return the packedGenParticles collection
std::vector<pat::PackedGenParticle> GenEWevent::ReturnPackedGenParticles() const
{
    return packedGenParticles;
}

// for MC reweighting of Z/W boson + jets events: save the pt of the generator v boson
void GenEWevent::FillBoson()
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
        if ((abs(genparticle.pdgId()) == 12 or abs(genparticle.pdgId()) == 14 or abs(genparticle.pdgId()) == 16 or abs(genparticle.pdgId()) == 11 or abs(genparticle.pdgId()) == 13) and genparticle.isPromptFinalState())  {
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
        // std::cout << "filling W Boson" << std::endl;
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
            // std::cout << WBoson.Pt() << std::endl;
        }
    }
    if (decay_prodZ.size() == 2){
        //std::cout << "filling Z Boson" << std::endl;
        if((decay_prodZ.at(0).pdgId())+(decay_prodZ.at(1).pdgId())==0){
	    for(size_t k=0;k<decay_prodZ.size();k++){
                if(abs(decay_prodZ.at(k).pdgId())==11 or abs(decay_prodZ.at(k).pdgId())==13){
                    for(size_t l=0;l<radiated_photons.size();l++){
                        if(reco::deltaR(radiated_photons.at(l).p4(),decay_prodZ.at(k).p4())<0.1){
                            decay_prodZ.at(k).setP4(decay_prodZ.at(k).p4()+radiated_photons.at(l).p4());
                        }
                    }
                }
            }
            ZBoson = decay_prodZ.at(0).p4() + decay_prodZ.at(1).p4();
            ZBosonisFilled = true;
            if(abs(decay_prodZ.at(0).pdgId()) == 12 or abs(decay_prodZ.at(0).pdgId()) == 14 or abs(decay_prodZ.at(0).pdgId()) == 16 ){
                isZnunu = true;
            }
            else isZnunu = false;
        }
    }
}

// return if the WBoson has been filled
bool GenEWevent::WBosonIsFilled() const
{
    return WBosonisFilled;
}

// return if the ZBoson has been filled
bool GenEWevent::ZBosonIsFilled() const
{
    return ZBosonisFilled;
}

// return if the ZBoson decayed to Neutrinos
bool GenEWevent::IsZnunu() const
{
    return isZnunu;
}

// return if the ZBoson decayed to Leptons
// bool GenEWevent::IsZll() const
// {
//     return isZll;
// }

math::XYZTLorentzVector GenEWevent::ReturnWBoson() const
{
    if (not WBosonisFilled) {
        std::cerr << "Attention: WBoson is not filled!";
    }
    return WBoson;
}

math::XYZTLorentzVector GenEWevent::ReturnZBoson() const
{
    if (not ZBosonisFilled) {
        std::cerr << "Attention: ZBoson is not filled!";
    }
    return ZBoson;
}
