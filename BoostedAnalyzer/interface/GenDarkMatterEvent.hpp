#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GENDARKMATTEREVENT_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GENDARKMATTEREVENT_HPP
#include <vector>
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include <TLorentzVector.h>

class GenDarkMatterEvent {
   public:
    // constructor
    GenDarkMatterEvent();
    // destructor
    ~GenDarkMatterEvent();
    void Initialize(std::vector< reco::GenParticle > prunedGenParticles_, std::vector< pat::PackedGenParticle > packedGenParticles_);
    void Fill();

    std::vector< reco::GenParticle >      ReturnPrunedGenParticles() const;
    std::vector< pat::PackedGenParticle > ReturnPackedGenParticles() const;

    reco::GenParticle                ReturnMediator() const;
    std::vector< reco::GenParticle > ReturnNeutralinos() const;
    std::vector< reco::GenParticle > ReturnNeutrinos() const;

    bool HasDarkMatter() const;
    bool IsFilled() const;

    double                        ReturnMediatorMass() const;
    TLorentzVector                ReturnMediator4Vector() const;
    std::vector< double >         ReturnNeutralinoMasses() const;
    std::vector< TLorentzVector > ReturnNeutralino4Vectors() const;
    std::vector< TLorentzVector > ReturnNeutrino4Vectors() const;

    double         ReturnNaiveMET() const;
    TLorentzVector ReturnNaiveMET4Vector() const;

    // for MC reweighting of Z/W boson + jets events
    void                    FillBoson();
    bool                    ZBosonIsFilled() const;
    bool                    WBosonIsFilled() const;
    bool                    IsZnunu() const;
    math::XYZTLorentzVector ReturnZBoson() const;
    math::XYZTLorentzVector ReturnWBoson() const;

   private:
    bool hasDarkMatter = false;
    bool isFilled      = false;

    std::vector< reco::GenParticle >      prunedGenParticles;
    std::vector< pat::PackedGenParticle > packedGenParticles;
    std::vector< reco::GenParticle >      Neutralinos;
    reco::GenParticle                     Mediator;
    std::vector< reco::GenParticle >      Neutrinos;

    // for MC reweighting of Z/W boson + jets events
    bool                    hasVectorBoson = false;
    bool                    ZBosonisFilled = false;
    bool                    WBosonisFilled = false;
    bool                    isZnunu        = false;
    math::XYZTLorentzVector ZBoson;
    math::XYZTLorentzVector WBoson;
};

#endif