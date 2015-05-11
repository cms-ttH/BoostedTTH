#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GENTOPEVENT_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GENTOPEVENT_HPP
#include <vector>
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

class GenTopEvent{
  
public:
  GenTopEvent();
  ~GenTopEvent();
  void Fill(const std::vector<reco::GenParticle>& prunedGenParticles, int ttXid);
  reco::GenParticle GetHiggs() const;
  std::vector<reco::GenParticle> GetHiggsDecayProducts() const;
  bool IsFilled() const;
  reco::GenParticle GetTop() const;
  reco::GenParticle GetTopBar() const;
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

  int GetTTxId() const;

  bool IsAllHadron() const;
  bool IsDiLepton() const;
  bool IsSemiLepton() const;
  
  void Print() const;

private:
  math::XYZTLorentzVector GetLV(const reco::GenParticle& p) const;
  std::vector<math::XYZTLorentzVector> GetLVs(const std::vector<reco::GenParticle>& ps) const;
  void PrintParticle(reco::GenParticle) const;
  void PrintParticles(std::vector<reco::GenParticle>) const;

  reco::GenParticle higgs;
  reco::GenParticle top;
  reco::GenParticle topbar;
  reco::GenParticle wplus;
  reco::GenParticle wminus;
  reco::GenParticle top_decay_quark;
  reco::GenParticle topbar_decay_quark;
  std::vector<reco::GenParticle> wplus_decay_products;
  std::vector<reco::GenParticle> wminus_decay_products;
  std::vector<reco::GenParticle> higgs_decay_products;
  bool topIsHadronic;
  bool topbarIsHadronic;
  bool isFilled;
  int ttXid;
};

#endif
