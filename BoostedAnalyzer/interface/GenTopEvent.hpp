#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GENTOPEVENT_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GENTOPEVENT_HPP
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include <vector>

class GenTopEvent {

public:
    GenTopEvent();
    ~GenTopEvent();

    reco::GenParticle GetHiggs() const;
    reco::GenParticle GetZ() const;
    std::vector<reco::GenParticle> GetHiggsDecayProducts() const;
    std::vector<reco::GenParticle> GetZDecayProducts() const;
    bool IsFilled() const;
    bool TTxIsFilled() const;
    reco::GenParticle GetTop() const;
    reco::GenParticle GetTopBar() const;
    reco::GenParticle GetHardTop() const;
    reco::GenParticle GetHardTopBar() const;
    reco::GenParticle GetTopDecayQuark() const;
    reco::GenParticle GetTopBarDecayQuark() const;

    reco::GenParticle GetWplus() const;
    reco::GenParticle GetWminus() const;
    std::vector<reco::GenParticle> GetWplusDecayProducts() const;
    std::vector<reco::GenParticle> GetWminusDecayProducts() const;

    reco::GenParticle GetTopHad() const;
    reco::GenParticle GetTopLep() const;
    reco::GenParticle GetTopHadDecayQuark() const;
    reco::GenParticle GetTopLepDecayQuark() const;
    reco::GenParticle GetWhad() const;
    reco::GenParticle GetWlep() const;
    std::vector<reco::GenParticle> GetWLeptons() const;
    reco::GenParticle GetLepton() const;
    reco::GenParticle GetNeutrino() const;
    std::vector<reco::GenParticle> GetWQuarks() const;

    std::vector<reco::GenParticle> GetAllTopHads() const;
    std::vector<reco::GenParticle> GetAllTopLeps() const;
    std::vector<reco::GenParticle> GetAllTopHadDecayQuarks() const;
    std::vector<reco::GenParticle> GetAllTopLepDecayQuarks() const;
    std::vector<reco::GenParticle> GetAllWhads() const;
    std::vector<reco::GenParticle> GetAllWleps() const;
    std::vector<reco::GenParticle> GetAllLeptons() const;
    std::vector<reco::GenParticle> GetAllNeutrinos() const;
    std::vector<reco::GenParticle> GetAllWQuarks() const;
    std::vector<reco::GenParticle> GetAllWAntiQuarks() const;
    
    // for THW
    reco::GenParticle GetWNotFromTop() const;
    std::vector<reco::GenParticle> GetWNotFromTopDecayProducts() const;
    
    // for THQ
    reco::GenParticle GetForwardQuark() const;

    std::vector<reco::GenParticle> GetQuarks() const;

    math::XYZTLorentzVector GetHiggsVec() const;
    math::XYZTLorentzVector GetTopVec() const;
    math::XYZTLorentzVector GetTopBarVec() const;
    math::XYZTLorentzVector GetTopHadVec() const;
    math::XYZTLorentzVector GetTopLepVec() const;
    math::XYZTLorentzVector GetWplusVec() const;
    math::XYZTLorentzVector GetWminusVec() const;
    math::XYZTLorentzVector GetWhadVec() const;
    math::XYZTLorentzVector GetWlepVec() const;
    math::XYZTLorentzVector GetLeptonVec() const;
    math::XYZTLorentzVector GetNeutrinoVec() const;
    std::vector<math::XYZTLorentzVector> GetQuarkVecs() const;
    std::vector<math::XYZTLorentzVector> GetHiggsDecayProductVecs() const;
    math::XYZTLorentzVector GetTopDecayQuarkVec() const;
    math::XYZTLorentzVector GetTopBarDecayQuarkVec() const;
    math::XYZTLorentzVector GetTopHadDecayQuarkVec() const;
    math::XYZTLorentzVector GetTopLepDecayQuarkVec() const;
    std::vector<math::XYZTLorentzVector> GetWLeptonsVecs() const;
    std::vector<math::XYZTLorentzVector> GetWQuarksVecs() const;
    std::vector<math::XYZTLorentzVector> GetWplusDecayProductsVecs() const;
    std::vector<math::XYZTLorentzVector> GetWminusDecayProductsVecs() const;

    std::vector<math::XYZTLorentzVector> GetAllTopHadVecs() const;
    std::vector<math::XYZTLorentzVector> GetAllTopLepVecs() const;
    std::vector<math::XYZTLorentzVector> GetAllTopHadDecayQuarkVecs() const;
    std::vector<math::XYZTLorentzVector> GetAllTopLepDecayQuarkVecs() const;
    std::vector<math::XYZTLorentzVector> GetAllWhadVecs() const;
    std::vector<math::XYZTLorentzVector> GetAllWlepVecs() const;
    std::vector<math::XYZTLorentzVector> GetAllLeptonVecs() const;
    std::vector<math::XYZTLorentzVector> GetAllNeutrinoVecs() const;
    std::vector<math::XYZTLorentzVector> GetAllWQuarkVecs() const;
    std::vector<math::XYZTLorentzVector> GetAllWAntiQuarkVecs() const;

    std::vector<reco::GenJet> GetAllTopHadBGenJets() const;
    std::vector<reco::GenJet> GetAllTopLepBGenJets() const;
    reco::GenJet GetTopBarBBarGenJet() const;
    reco::GenJet GetTopBGenJet() const;
    reco::GenJet GetHiggsBGenJet() const;
    reco::GenJet GetHiggsBBarGenJet() const;

    std::vector<reco::GenJet> GetAdditionalBGenJets() const;
    std::vector<reco::GenJet> GetAdditionalCGenJets() const;
    std::vector<reco::GenJet> GetAdditionalLightGenJets() const;
    std::vector<reco::GenJet> GetWGenJets() const;
    std::vector<reco::GenParticle> GetAdditionalBGenJetsHadron() const;
    std::vector<reco::GenParticle> GetAdditionalCGenJetsHadron() const;
    std::vector<reco::GenParticle> GetAdditionalBGenJetsHadron2() const;
    std::vector<reco::GenParticle> GetAdditionalCGenJetsHadron2() const;

    std::vector<int> GetAdditionalCGenJetsFromTopType() const;
    std::vector<int> GetAdditionalBGenJetsFromTopType() const;
    std::vector<int> GetAdditionalCGenJetsNHadrons() const;
    std::vector<int> GetAdditionalBGenJetsNHadrons() const;

    std::vector<reco::GenParticle> GetAllTopHadBHadrons() const;
    std::vector<reco::GenParticle> GetAllTopLepBHadrons() const;
    reco::GenParticle GetTopBarBBarHadron() const;
    reco::GenParticle GetTopBHadron() const;
    reco::GenParticle GetHiggsBHadron() const;
    reco::GenParticle GetHiggsBBarHadron() const;
    reco::GenParticle GetWCHadron() const;

    std::vector<reco::GenParticle> GetAdditionalBHadrons() const;
    std::vector<int> GetAdditionalBHadronMothers() const;
    std::vector<int> GetAdditionalBHadronAfterTopType() const;
    std::vector<reco::GenParticle> GetAdditionalCHadrons() const;
    std::vector<int> GetAdditionalCHadronMothers() const;
    std::vector<int> GetAdditionalCHadronAfterTopType() const;

    int GetTTxId(bool countAdditionalAfterTop = true) const;
    int GetTTxIdFromProducer() const;
    int GetTTxIdFromProducerLong() const;

    bool IsZbb() const;
    bool IsZnonbb() const;
    bool IsTTbar() const;
    bool IsTTH() const;
    bool IsAllHadron() const;
    bool IsDiLepton() const;
    bool IsSemiLepton() const;

    void Print() const;
    void PrintTTX() const;

    void FillTTxDetails(const std::vector<reco::GenJet>& customGenJets,
        const std::vector<int>& genBHadIndex, const std::vector<int>& genBHadJetIndex,
        const std::vector<int>& genBHadFlavour, const std::vector<int>& genBHadFromTopWeakDecay,
        const std::vector<reco::GenParticle>& genBHadPlusMothers,
        const std::vector<int>& genCHadIndex, const std::vector<int>& genCHadJetIndex,
        const std::vector<int>& genCHadFlavour, const std::vector<int>& genCHadFromTopWeakDecay,
        const std::vector<reco::GenParticle>& genCHadPlusMothers,
        const std::vector<int>& genCHadBHadronId);
    void FillTTdecay(const std::vector<reco::GenParticle>& prunedGenParticles, int ttXid_);

private:
    math::XYZTLorentzVector GetLV(const reco::GenParticle& p) const;
    std::vector<math::XYZTLorentzVector> GetLVs(const std::vector<reco::GenParticle>& ps) const;
    void PrintParticle(reco::GenParticle) const;
    void PrintParticles(std::vector<reco::GenParticle>) const;

    reco::GenParticle higgs;
    reco::GenParticle top;
    reco::GenParticle hard_top;
    reco::GenParticle topbar;
    reco::GenParticle hard_topbar;
    reco::GenParticle wplus;
    reco::GenParticle wminus;
    reco::GenParticle top_decay_quark;
    reco::GenParticle topbar_decay_quark;
    std::vector<reco::GenParticle> wplus_decay_products;
    std::vector<reco::GenParticle> wminus_decay_products;
    std::vector<reco::GenParticle> higgs_decay_products;

    // for ttZ
    reco::GenParticle Z;
    std::vector<reco::GenParticle> Z_decay_products;
    
    // for THW
    reco::GenParticle w_not_from_top;
    std::vector<reco::GenParticle> w_not_from_top_decay_products;
    
    // for THQ
    reco::GenParticle forward_quark;

    reco::GenJet higgs_b_genjet;
    reco::GenJet higgs_bbar_genjet;
    reco::GenJet top_b_genjet;
    reco::GenJet topbar_bbar_genjet;

    std::vector<reco::GenJet> additional_b_genjets;
    std::vector<int> additional_b_genjet_nb;
    std::vector<int> additional_b_genjet_nb_aftertop;
    std::vector<int> additional_b_genjet_aftertoptype;
    std::vector<reco::GenParticle> additional_b_genjet_hadron;
    std::vector<reco::GenParticle> additional_b_genjet_hadron2;

    reco::GenParticle higgs_b_hadron;
    reco::GenParticle higgs_bbar_hadron;
    reco::GenParticle top_b_hadron;
    reco::GenParticle topbar_bbar_hadron;

    std::vector<reco::GenParticle> additional_b_hadrons;
    std::vector<int> additional_b_hadron_aftertop;
    std::vector<int> additional_b_hadron_mother;

    std::vector<reco::GenJet> additional_c_genjets;
    std::vector<int> additional_c_genjet_nc;
    std::vector<int> additional_c_genjet_nc_aftertop;
    std::vector<int> additional_c_genjet_aftertoptype;
    std::vector<reco::GenParticle> additional_c_genjet_hadron;
    std::vector<reco::GenParticle> additional_c_genjet_hadron2;

    std::vector<reco::GenParticle> additional_c_hadrons;
    std::vector<int> additional_c_hadron_aftertop;
    std::vector<int> additional_c_hadron_mother;

    reco::GenParticle w_c_hadron;

    std::vector<reco::GenJet> w_genjets;
    std::vector<reco::GenJet> additional_light_genjets;
    const float wMatchR = 0.4;
    const float ttxptcut = 20;
    const float ttxetacut = 2.4;
    bool isTTbar = false;
    bool isTTH = false;
    bool foundT = false;
    bool foundTbar = false;
    bool foundH = false;
    bool foundZ = false;
    bool isZbb = false;
    bool isZnonbb = false;
    bool topIsHadronic;
    bool topbarIsHadronic;
    bool isFilled;
    bool ttxIsFilled;
    int ttXid;
};

class GenTopEventProducer {
public:
    GenTopEventProducer(edm::ConsumesCollector&& iC);
    GenTopEvent Produce(const edm::Event& iEvent, bool doGenHadronMatch, bool returnDummy);
    ~GenTopEventProducer();

private:
    edm::EDGetTokenT<std::vector<reco::GenJet>> customGenJetsToken;
    edm::EDGetTokenT<std::vector<int>> genBHadJetIndexToken;
    edm::EDGetTokenT<std::vector<int>> genBHadFlavourToken;
    edm::EDGetTokenT<std::vector<int>> genBHadFromTopWeakDecayToken;
    edm::EDGetTokenT<std::vector<reco::GenParticle>> genBHadPlusMothersToken;
    edm::EDGetTokenT<std::vector<std::vector<int>>> genBHadPlusMothersIndicesToken;
    edm::EDGetTokenT<std::vector<int>> genBHadIndexToken;
    edm::EDGetTokenT<std::vector<int>> genBHadLeptonHadronIndexToken;
    edm::EDGetTokenT<std::vector<int>> genBHadLeptonViaTauToken;
    edm::EDGetTokenT<std::vector<int>> genCHadJetIndexToken;
    edm::EDGetTokenT<std::vector<int>> genCHadFlavourToken;
    edm::EDGetTokenT<std::vector<int>> genCHadFromTopWeakDecayToken;
    edm::EDGetTokenT<std::vector<int>> genCHadBHadronIdToken;
    edm::EDGetTokenT<std::vector<int>> genCHadIndexToken;
    edm::EDGetTokenT<std::vector<reco::GenParticle>> genCHadPlusMothersToken;
    edm::EDGetTokenT<int> genTtbarIdToken;
    edm::EDGetTokenT<std::vector<reco::GenParticle>> prunedGenParticlesToken;
};

#endif
