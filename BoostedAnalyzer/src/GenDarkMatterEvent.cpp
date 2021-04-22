#include "BoostedTTH/BoostedAnalyzer/interface/GenDarkMatterEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

// constructor
GenDarkMatterEvent::GenDarkMatterEvent(const std::vector< reco::GenParticle >&      prunedGenParticles_,
                                       const std::vector< pat::PackedGenParticle >& packedGenParticles_) :
    prunedGenParticles{prunedGenParticles_},
    packedGenParticles{packedGenParticles_}
{
}

// destructor
GenDarkMatterEvent::~GenDarkMatterEvent() {}

// initialize some flags
void GenDarkMatterEvent::Initialize()
{
    isFilled = false;

    hasDarkMatter = false;

    hasVectorBoson = false;
    WBosonisFilled = false;
    ZBosonisFilled = false;
    PhotonisFilled = false;
}

// return the prunedGenParticles collection
const std::vector< reco::GenParticle >& GenDarkMatterEvent::ReturnPrunedGenParticles() const { return prunedGenParticles; }

// return the packedGenParticles collection
const std::vector< pat::PackedGenParticle >& GenDarkMatterEvent::ReturnPackedGenParticles() const { return packedGenParticles; }

// fill the DarkMatter Event by retrieving all the needed information from the
// genparticle collections
void GenDarkMatterEvent::Fill()
{
    // find the lightest neutralinos in the event, the mediator, neutrinos, leptons in general (for vector boson pt reweighting) and photons from the
    // prunedGenParticles collection
    for (const reco::GenParticle& genparticle : prunedGenParticles) {
        if ((abs(genparticle.pdgId()) == 1000022 or abs(genparticle.pdgId()) == 18) and genparticle.isPromptFinalState()) {
            Neutralinos.push_back(genparticle);
        }
        if ((abs(genparticle.pdgId()) == 23 or abs(genparticle.pdgId()) == 25 or abs(genparticle.pdgId()) == 55) and genparticle.isLastCopy()) {
            Mediator = genparticle;
        }
        if ((abs(genparticle.pdgId()) == 12 or abs(genparticle.pdgId()) == 14 or abs(genparticle.pdgId()) == 16) and genparticle.isPromptFinalState()) {
            Neutrinos.push_back(genparticle);
        }
        if (((abs(genparticle.pdgId()) == 11 or abs(genparticle.pdgId()) == 12 or abs(genparticle.pdgId()) == 13 or abs(genparticle.pdgId()) == 14 or
              abs(genparticle.pdgId()) == 16) and
             genparticle.isPromptFinalState()) or
            (abs(genparticle.pdgId()) == 15 and genparticle.isPromptDecayed())) {
            Leptons.push_back(genparticle);
        }
        if (abs(genparticle.pdgId()) == 22 and genparticle.isPromptFinalState()) { Photons.push_back(genparticle); }
        if (abs(genparticle.pdgId()) == 24 and genparticle.statusFlags().fromHardProcess() and genparticle.statusFlags().isLastCopy()) {
            GenWBosons.push_back(genparticle);
        }
        if (abs(genparticle.pdgId()) == 23 and genparticle.statusFlags().fromHardProcess() and genparticle.statusFlags().isLastCopy()) {
            GenZBosons.push_back(genparticle);
        }

        // fill containers for fatjet gen matching regarding in-site DeepAK15 calibration
        // light flavor quarks with W+ as mother
        if (abs(genparticle.pdgId()) < 4 and genparticle.statusFlags().fromHardProcess() and genparticle.statusFlags().isFirstCopy() and
            genparticle.mother(0)->pdgId() == 24) {
            LightQuarksFromWPlus.push_back(genparticle);
        }
        // light flavor quarks with W- as mother
        if (abs(genparticle.pdgId()) < 4 and genparticle.statusFlags().fromHardProcess() and genparticle.statusFlags().isFirstCopy() and
            genparticle.mother(0)->pdgId() == -24) {
            LightQuarksFromWMinus.push_back(genparticle);
        }
        // c flavor quarks with W+ as mother
        if (abs(genparticle.pdgId()) == 4 and genparticle.statusFlags().fromHardProcess() and genparticle.statusFlags().isFirstCopy() and
            genparticle.mother(0)->pdgId() == 24) {
            CQuarksFromWPlus.push_back(genparticle);
        }
        // light flavor quarks with W- as mother
        if (abs(genparticle.pdgId()) == 4 and genparticle.statusFlags().fromHardProcess() and genparticle.statusFlags().isFirstCopy() and
            genparticle.mother(0)->pdgId() == -24) {
            CQuarksFromWMinus.push_back(genparticle);
        }
        // b quarks with top quark as mother
        if (abs(genparticle.pdgId()) == 5 and genparticle.statusFlags().fromHardProcess() and genparticle.statusFlags().isFirstCopy() and
            genparticle.mother(0)->pdgId() == 6) {
            BQuarksFromTop.push_back(genparticle);
        }
        // b quarks with top antiquark as mother
        if (abs(genparticle.pdgId()) == 5 and genparticle.statusFlags().fromHardProcess() and genparticle.statusFlags().isFirstCopy() and
            genparticle.mother(0)->pdgId() == -6) {
            BQuarksFromAntiTop.push_back(genparticle);
        }
        // b quarks in general
        if (abs(genparticle.pdgId()) == 5 and genparticle.statusFlags().isLastCopy()) { BQuarks.push_back(genparticle); }
        // c quarks in general
        if (abs(genparticle.pdgId()) == 4 and genparticle.statusFlags().isLastCopy()) { CQuarks.push_back(genparticle); }
        // top quarks
        if (abs(genparticle.pdgId()) == 6 and genparticle.statusFlags().fromHardProcess() and genparticle.statusFlags().isLastCopy()) {
            TQuarks.push_back(genparticle);
        }
    }
    // find all final state hadrons in the event from the the packedGenParticles collection
    for (const pat::PackedGenParticle& genparticle : packedGenParticles) {
        if (genparticle.status() == 1 and (not(abs(genparticle.pdgId()) == 22 or (abs(genparticle.pdgId()) >= 11 and abs(genparticle.pdgId()) <= 16)))) {
            Hadrons.push_back(genparticle);
        }
    }

    isFilled = true;

    if (Neutralinos.size() > 0) hasDarkMatter = true;
    if (Leptons.size() >= 2 or Photons.size() > 0) hasVectorBoson = true;
    //     for (const auto& hadron : Hadrons) {
    //         std::cout << "Hadron: " << hadron.pdgId() << " " << hadron.status() << " " << hadron.pt() << " " << hadron.eta() << std::endl;
    //     }
    if (GenWBosons.size() > 0) {
        std::sort(GenWBosons.begin(), GenWBosons.end(), [](auto& a, auto& b) { return a.p4().pt() > b.p4().pt(); });
    }
    if (GenZBosons.size() > 0) {
        std::sort(GenZBosons.begin(), GenZBosons.end(), [](auto& a, auto& b) { return a.p4().pt() > b.p4().pt(); });
    }
}

// return the lightest neutralinos in a vector
std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnNeutralinos() const
{
    if (not isFilled) { std::cerr << "Attention: Neutralinos are not filled!"; }
    return Neutralinos;
}

// return the mediator particle
reco::GenParticle GenDarkMatterEvent::ReturnMediator() const
{
    if (not isFilled) { std::cerr << "Attention: Mediator is not filled!"; }
    return Mediator;
}

// return the neutrinos in a vector
std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnNeutrinos() const
{
    if (not isFilled) { std::cerr << "Attention: Neutrinos are not filled!"; }
    return Neutrinos;
}

// return if the GenDarkMatterEvent has been filled
bool GenDarkMatterEvent::IsFilled() const { return isFilled; }

// return if the event has at least one lightest neutralino (PDGID 1000022)
bool GenDarkMatterEvent::HasDarkMatter() const { return hasDarkMatter; }

// return if the event has at least one vector boson
bool GenDarkMatterEvent::HasVectorBoson() const { return hasVectorBoson; }

// return the mass of the mediator particle
double GenDarkMatterEvent::ReturnMediatorMass() const { return Mediator.mass(); }

// return the masses of the neutralinos in a vector
std::vector< double > GenDarkMatterEvent::ReturnNeutralinoMasses() const
{
    std::vector< double > masses;
    for (size_t i = 0; i < Neutralinos.size(); i++) { masses.push_back(Neutralinos[i].mass()); }
    return masses;
}

// return the 4-vector of the mediator particle
TLorentzVector GenDarkMatterEvent::ReturnMediator4Vector() const
{
    math::XYZTLorentzVector vec4 = Mediator.p4();
    return BoostedUtils::GetTLorentzVector(vec4);
}

// return the 4-vectors of the neutralinos in a vector
std::vector< TLorentzVector > GenDarkMatterEvent::ReturnNeutralino4Vectors() const
{
    std::vector< math::XYZTLorentzVector > vecs4;
    for (size_t i = 0; i < Neutralinos.size(); i++) { vecs4.push_back(Neutralinos[i].p4()); }
    return BoostedUtils::GetTLorentzVectors(vecs4);
}

// return the 4-vectors of the neutrinos in a vector
std::vector< TLorentzVector > GenDarkMatterEvent::ReturnNeutrino4Vectors() const
{
    std::vector< math::XYZTLorentzVector > vecs4;
    for (size_t i = 0; i < Neutrinos.size(); i++) { vecs4.push_back(Neutrinos[i].p4()); }
    return BoostedUtils::GetTLorentzVectors(vecs4);
}

// returns a naively calculated MET
// naively MET should be the pt of the sum of neutralinos and neutrinos
// 4-vectors
double GenDarkMatterEvent::ReturnNaiveMET() const
{
    math::XYZTLorentzVector vec4_invisibles;
    for (size_t i = 0; i < Neutralinos.size(); i++) { vec4_invisibles += Neutralinos[i].p4(); }
    for (size_t i = 0; i < Neutrinos.size(); i++) { vec4_invisibles += Neutrinos[i].p4(); }
    return vec4_invisibles.pt();
}

TLorentzVector GenDarkMatterEvent::ReturnNaiveMET4Vector() const
{
    math::XYZTLorentzVector vec4_invisibles;
    for (size_t i = 0; i < Neutralinos.size(); i++) { vec4_invisibles += Neutralinos[i].p4(); }
    for (size_t i = 0; i < Neutrinos.size(); i++) { vec4_invisibles += Neutrinos[i].p4(); }
    return BoostedUtils::GetTLorentzVector(vec4_invisibles);
}

// for MC reweighting of Z/W/Gamma boson + jets events: save the pt of the generator v
// boson

void GenDarkMatterEvent::FillBoson()
{
    if (not hasVectorBoson) { return; }

    std::vector< reco::GenParticle > decay_prodW;
    std::vector< reco::GenParticle > decay_prodZ;
    std::vector< reco::GenParticle > isolated_photons;

    // find all possible leptonic decay product of the Z and W boson
    for (const reco::GenParticle& lepton : Leptons) {
        if (((abs(lepton.pdgId()) == 11 or abs(lepton.pdgId()) == 12 or abs(lepton.pdgId()) == 13 or abs(lepton.pdgId()) == 14 or abs(lepton.pdgId()) == 16) and
             lepton.isPromptFinalState()) or
            (abs(lepton.pdgId()) == 15 and lepton.isPromptDecayed())) {
            // Z Boson decay products
            decay_prodZ.push_back(lepton);
            // W Boson  decay products
            decay_prodW.push_back(lepton);
        }
    }

    // find all isolated photons using a dynamic Frixione isolation criterium
    for (const reco::GenParticle& photon : Photons) {
        //         std::cout << "Photon Pt: " << photon.pt() << std::endl;
        bool                 isolated = true;
        float                R_dyn    = 91.1876 / (photon.pt() * sqrt(epsilon_0_dyn));
        float                R_0_dyn  = std::min(float(1.0), R_dyn);
        std::vector< float > radii;
        for (int j = 1; j <= iterations; j++) { radii.push_back(R_0_dyn / iterations * j); }
        for (const float& R : radii) {
            //             std::cout << "R: " << R << std::endl;
            float isolation = 0.0;
            for (const auto& hadron : Hadrons) {
                if (reco::deltaR(photon.p4(), hadron.p4()) <= R) { isolation += hadron.pt(); }
            }
            //             std::cout << "Dynamic frixione isolation: " << isolation << std::endl;
            float isolation_cut = epsilon_0_dyn * photon.pt() * pow((1 - cos(R)) / (1 - cos(R_0_dyn)), n_dyn);
            //             std::cout << "Dynamic frixione isolation cut: " << isolation_cut << std::endl;
            if (isolation > isolation_cut) {
                isolated = false;
                break;
            }
        }
        if (isolated) isolated_photons.push_back(photon);
    }

    // try to reconstruct the W boson from its decay products
    if (decay_prodW.size() >= 2) {
        std::sort(decay_prodW.begin(), decay_prodW.end(), [](auto& a, auto& b) { return a.pt() > b.pt(); });
        // std::cout << "filling W Boson" << std::endl;
        if ((decay_prodW.at(0).pdgId()) * (decay_prodW.at(1).pdgId()) < 0 and abs(abs(decay_prodW.at(0).pdgId()) - abs(decay_prodW.at(1).pdgId())) == 1) {
            for (size_t k = 0; k < decay_prodW.size(); k++) {
                if (abs(decay_prodW.at(k).pdgId()) == 11 or abs(decay_prodW.at(k).pdgId()) == 13 or abs(decay_prodW.at(k).pdgId()) == 15) {
                    for (size_t l = 0; l < Photons.size(); l++) {
                        if (reco::deltaR(Photons.at(l).p4(), decay_prodW.at(k).p4()) < 0.1) {
                            decay_prodW.at(k).setP4(decay_prodW.at(k).p4() + Photons.at(l).p4());
                        }
                    }
                }
            }
            WBoson         = decay_prodW.at(0).p4() + decay_prodW.at(1).p4();
            WBosonisFilled = true;
        }
    }

    // try to reconstruct the Z boson from its decay products
    if (decay_prodZ.size() >= 2) {
        std::sort(decay_prodZ.begin(), decay_prodZ.end(), [](auto& a, auto& b) { return a.pt() > b.pt(); });
        // std::cout << "filling Z Boson" << std::endl;
        if ((decay_prodZ.at(0).pdgId()) + (decay_prodZ.at(1).pdgId()) == 0) {
            for (size_t k = 0; k < decay_prodZ.size(); k++) {
                if (abs(decay_prodZ.at(k).pdgId()) == 11 or abs(decay_prodZ.at(k).pdgId()) == 13 or abs(decay_prodZ.at(k).pdgId()) == 15) {
                    for (size_t l = 0; l < Photons.size(); l++) {
                        if (reco::deltaR(Photons.at(l).p4(), decay_prodZ.at(k).p4()) < 0.1) {
                            decay_prodZ.at(k).setP4(decay_prodZ.at(k).p4() + Photons.at(l).p4());
                        }
                    }
                }
            }
            ZBoson         = decay_prodZ.at(0).p4() + decay_prodZ.at(1).p4();
            ZBosonisFilled = true;
            if (abs(decay_prodZ.at(0).pdgId()) == 12 or abs(decay_prodZ.at(0).pdgId()) == 14 or abs(decay_prodZ.at(0).pdgId()) == 16) { isZnunu = true; }
            else
                isZnunu = false;
        }
    }

    // fill the hardest isolated photon
    if (isolated_photons.size() > 0) {
        std::sort(isolated_photons.begin(), isolated_photons.end(), [](auto& a, auto& b) { return a.pt() > b.pt(); });
        Photon         = isolated_photons.at(0).p4();
        PhotonisFilled = true;
    }
}

// return if the WBoson has been filled
bool GenDarkMatterEvent::WBosonIsFilled() const { return WBosonisFilled; }

// return if the ZBoson has been filled
bool GenDarkMatterEvent::ZBosonIsFilled() const { return ZBosonisFilled; }

// return if the Photon has been filled
bool GenDarkMatterEvent::PhotonIsFilled() const { return PhotonisFilled; }

// return if the ZBoson decayed to Neutrinos
bool GenDarkMatterEvent::IsZnunu() const { return isZnunu; }

math::XYZTLorentzVector GenDarkMatterEvent::ReturnWBoson() const
{
    if (not WBosonisFilled) { std::cerr << "Attention: WBoson is not filled!"; }
    return WBoson;
}

math::XYZTLorentzVector GenDarkMatterEvent::ReturnZBoson() const
{
    if (not ZBosonisFilled) { std::cerr << "Attention: ZBoson is not filled!"; }
    return ZBoson;
}

math::XYZTLorentzVector GenDarkMatterEvent::ReturnPhoton() const
{
    if (not PhotonisFilled) { std::cerr << "Attention: Photon is not filled!"; }
    return Photon;
}

std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnGenWBosons() const { return GenWBosons; }

std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnGenZBosons() const { return GenZBosons; }

std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnGenPhotons() const { return Photons; }

std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnBQuarksFromTop() const { return BQuarksFromTop; }
std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnLightQuarksFromWPlus() const { return LightQuarksFromWPlus; }
std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnCQuarksFromWPlus() const { return CQuarksFromWPlus; }
std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnBQuarksFromAntiTop() const { return BQuarksFromAntiTop; }
std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnLightQuarksFromWMinus() const { return LightQuarksFromWMinus; }
std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnCQuarksFromWMinus() const { return CQuarksFromWMinus; }
std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnBQuarks() const { return BQuarks; }
std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnCQuarks() const { return CQuarks; }
std::vector< reco::GenParticle > GenDarkMatterEvent::ReturnTQuarks() const { return TQuarks; }
