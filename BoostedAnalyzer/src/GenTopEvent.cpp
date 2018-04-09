#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

GenTopEventProducer::GenTopEventProducer(edm::ConsumesCollector&& iC)
{
  customGenJetsToken = iC.consumes<std::vector<reco::GenJet>>(
    edm::InputTag("ak4GenJetsCustom", "", ""));
  genBHadJetIndexToken = iC.consumes<std::vector<int>>(
    edm::InputTag("matchGenBHadron", "genBHadJetIndex", ""));
  genBHadFlavourToken = iC.consumes<std::vector<int>>(
    edm::InputTag("matchGenBHadron", "genBHadFlavour", ""));
  genBHadFromTopWeakDecayToken = iC.consumes<std::vector<int>>(
    edm::InputTag("matchGenBHadron", "genBHadFromTopWeakDecay", ""));
  genBHadPlusMothersToken = iC.consumes<std::vector<reco::GenParticle>>(
    edm::InputTag("matchGenBHadron", "genBHadPlusMothers", ""));
  genBHadPlusMothersIndicesToken = iC.consumes<std::vector<std::vector<int>>>(
    edm::InputTag("matchGenBHadron", "genBHadPlusMothersIndices", ""));
  genBHadIndexToken = iC.consumes<std::vector<int>>(
    edm::InputTag("matchGenBHadron", "genBHadIndex"));
  genBHadLeptonHadronIndexToken = iC.consumes<std::vector<int>>(
    edm::InputTag("matchGenBHadron", "genBHadLeptonHadronIndex", ""));
  genBHadLeptonViaTauToken = iC.consumes<std::vector<int>>(
    edm::InputTag("matchGenBHadron", "genBHadLeptonViaTau", ""));
  genCHadJetIndexToken = iC.consumes<std::vector<int>>(
    edm::InputTag("matchGenCHadron", "genCHadJetIndex", ""));
  genCHadFlavourToken = iC.consumes<std::vector<int>>(
    edm::InputTag("matchGenCHadron", "genCHadFlavour", ""));
  genCHadFromTopWeakDecayToken = iC.consumes<std::vector<int>>(
    edm::InputTag("matchGenCHadron", "genCHadFromTopWeakDecay", ""));
  genCHadBHadronIdToken = iC.consumes<std::vector<int>>(
    edm::InputTag("matchGenCHadron", "genCHadBHadronId", ""));
  genCHadIndexToken = iC.consumes<std::vector<int>>(
    edm::InputTag("matchGenCHadron", "genCHadIndex"));
  genCHadPlusMothersToken = iC.consumes<std::vector<reco::GenParticle>>(
    edm::InputTag("matchGenCHadron", "genCHadPlusMothers", ""));
  genTtbarIdToken =
    iC.consumes<int>(edm::InputTag("categorizeGenTtbar", "genTtbarId", ""));
  prunedGenParticlesToken = iC.consumes<std::vector<reco::GenParticle>>(
    edm::InputTag("prunedGenParticles", "", ""));
}
GenTopEventProducer::~GenTopEventProducer()
{
}

GenTopEvent
GenTopEventProducer::Produce(const edm::Event& iEvent,
                             bool doGenHadronMatch,
                             bool returnDummy)
{
  GenTopEvent genTopEvt;
  if (returnDummy)
    return genTopEvt;
  edm::Handle<std::vector<reco::GenJet>> h_customgenjets;
  iEvent.getByToken(customGenJetsToken, h_customgenjets);
  edm::Handle<std::vector<int>> genBHadFlavour;
  edm::Handle<std::vector<int>> genBHadJetIndex;
  edm::Handle<std::vector<int>> genBHadFromTopWeakDecay;
  edm::Handle<std::vector<reco::GenParticle>> genBHadPlusMothers;
  edm::Handle<std::vector<std::vector<int>>> genBHadPlusMothersIndices;
  edm::Handle<std::vector<reco::GenParticle>> genCHadPlusMothers;
  edm::Handle<std::vector<int>> genBHadIndex;
  edm::Handle<std::vector<int>> genBHadLeptonHadronIndex;
  edm::Handle<std::vector<int>> genBHadLeptonViaTau;
  edm::Handle<std::vector<int>> genCHadIndex;
  edm::Handle<std::vector<int>> genCHadFlavour;
  edm::Handle<std::vector<int>> genCHadJetIndex;
  edm::Handle<std::vector<int>> genCHadFromTopWeakDecay;
  edm::Handle<std::vector<int>> genCHadBHadronId;
  edm::Handle<int> genTtbarId;
  edm::Handle<std::vector<reco::GenParticle>> prunedGenParticles;
  iEvent.getByToken(genCHadBHadronIdToken, genCHadBHadronId);
  iEvent.getByToken(genBHadFlavourToken, genBHadFlavour);
  iEvent.getByToken(genBHadJetIndexToken, genBHadJetIndex);
  iEvent.getByToken(genBHadFromTopWeakDecayToken, genBHadFromTopWeakDecay);
  iEvent.getByToken(genBHadPlusMothersToken, genBHadPlusMothers);
  iEvent.getByToken(genBHadPlusMothersIndicesToken, genBHadPlusMothersIndices);
  iEvent.getByToken(genCHadPlusMothersToken, genCHadPlusMothers);
  iEvent.getByToken(genBHadIndexToken, genBHadIndex);
  iEvent.getByToken(genBHadLeptonHadronIndexToken, genBHadLeptonHadronIndex);
  iEvent.getByToken(genBHadLeptonViaTauToken, genBHadLeptonViaTau);
  iEvent.getByToken(genCHadFlavourToken, genCHadFlavour);
  iEvent.getByToken(genCHadJetIndexToken, genCHadJetIndex);
  iEvent.getByToken(genCHadFromTopWeakDecayToken, genCHadFromTopWeakDecay);
  iEvent.getByToken(genCHadIndexToken, genCHadIndex);
  iEvent.getByToken(genTtbarIdToken, genTtbarId);
  iEvent.getByToken(prunedGenParticlesToken, prunedGenParticles);
  int ttid_full = *genTtbarId;
  genTopEvt.FillTTdecay(*prunedGenParticles, ttid_full);
  if (doGenHadronMatch) {
    genTopEvt.FillTTxDetails(*h_customgenjets,
                             *genBHadIndex,
                             *genBHadJetIndex,
                             *genBHadFlavour,
                             *genBHadFromTopWeakDecay,
                             *genBHadPlusMothers,
                             *genCHadIndex,
                             *genCHadJetIndex,
                             *genCHadFlavour,
                             *genCHadFromTopWeakDecay,
                             *genCHadPlusMothers,
                             *genCHadBHadronId);
  }
  return genTopEvt;
}

GenTopEvent::GenTopEvent()
{
  isFilled = false;
  ttxIsFilled = false;
  ttXid = -1;
}

GenTopEvent::~GenTopEvent()
{
}

bool
GenTopEvent::IsFilled() const
{
  return isFilled;
}
bool
GenTopEvent::TTxIsFilled() const
{
  return ttxIsFilled;
}

void
GenTopEvent::FillTTxDetails(
  const std::vector<reco::GenJet>& customGenJets,
  const std::vector<int>& genBHadIndex,
  const std::vector<int>& genBHadJetIndex,
  const std::vector<int>& genBHadFlavour,
  const std::vector<int>& genBHadFromTopWeakDecay,
  const std::vector<reco::GenParticle>& genBHadPlusMothers,
  const std::vector<int>& genCHadIndex,
  const std::vector<int>& genCHadJetIndex,
  const std::vector<int>& genCHadFlavour,
  const std::vector<int>& genCHadFromTopWeakDecay,
  const std::vector<reco::GenParticle>& genCHadPlusMothers,
  const std::vector<int>& genCHadBHadronId)
{

  std::vector<int> nb_per_genjet(customGenJets.size(), 0);
  std::vector<int> mother_of_genjet_b(customGenJets.size(), 0);
  std::vector<int> nb_aftertop_per_genjet(customGenJets.size(), 0);
  std::vector<int> b_aftertoptype_of_genjet(customGenJets.size(), 3);
  std::vector<const reco::GenParticle*> genjet_leading_bhadron(
    customGenJets.size(), 0);
  std::vector<const reco::GenParticle*> genjet_subleading_bhadron(
    customGenJets.size(), 0);
  std::vector<const reco::GenParticle*> genjet_leading_bhadron_from_tth(
    customGenJets.size(), 0);

  std::vector<int> additionalnc_per_genjet(customGenJets.size(), 0);
  std::vector<int> mother_of_genjet_c(customGenJets.size(), 0);
  std::vector<int> additionalnc_aftertop_per_genjet(customGenJets.size(), 0);
  std::vector<int> c_aftertoptype_of_genjet(customGenJets.size(), 3);
  std::vector<const reco::GenParticle*> genjet_leading_chadron(
    customGenJets.size(), 0);
  std::vector<const reco::GenParticle*> genjet_subleading_chadron(
    customGenJets.size(), 0);

  if (!isFilled) {
    std::cerr << "fill top info before filling addtional info" << std::endl;
  }
  auto tt_decay_leptons = GetAllLeptonVecs();
  auto tt_decay_quarks = GetAllWQuarkVecs();

  // loop over all bhadrons
  for (uint i = 0; i < genBHadIndex.size(); i++) {
    const reco::GenParticle* bhadron =
      genBHadIndex[i] >= 0 && genBHadIndex[i] < int(genBHadPlusMothers.size())
        ? &(genBHadPlusMothers[genBHadIndex[i]])
        : 0;
    int genjetidx = genBHadJetIndex[i];
    int motherflav = genBHadFlavour[i];
    bool from_tth = (abs(motherflav) == 6 || abs(motherflav) == 25);
    int aftertop = genBHadFromTopWeakDecay[i];

    // associate bhadrons with ttH decay products
    if (bhadron != 0 && motherflav == 25) {
      higgs_b_hadron = *bhadron;
    } else if (bhadron != 0 && motherflav == -25) {
      higgs_bbar_hadron = *bhadron;
    } else if (bhadron != 0 && motherflav == 6) {
      top_b_hadron = *bhadron;
    } else if (bhadron != 0 && motherflav == -6) {
      topbar_bbar_hadron = *bhadron;
    } else if (bhadron != 0 && abs(motherflav) != 24) {
      additional_b_hadrons.push_back(*bhadron);
      additional_b_hadron_aftertop.push_back(aftertop);
      additional_b_hadron_mother.push_back(motherflav);
    }

    // count hadrons in genjets
    if (genjetidx >= 0 && genjetidx < int(customGenJets.size())) {
      nb_per_genjet[genjetidx]++;
      b_aftertoptype_of_genjet[genjetidx] =
        std::min(b_aftertoptype_of_genjet[genjetidx], aftertop);
      if (aftertop == 1) {
        nb_aftertop_per_genjet[genjetidx]++;
      }

      // find leading hadron of genjets
      if (genjet_leading_bhadron[genjetidx] == 0) {
        genjet_leading_bhadron[genjetidx] = bhadron;
      } else if (genjet_leading_bhadron[genjetidx]->pt() < bhadron->pt()) {
        genjet_subleading_bhadron[genjetidx] =
          genjet_leading_bhadron[genjetidx];
        genjet_leading_bhadron[genjetidx] = bhadron;
      } else if (genjet_subleading_bhadron[genjetidx] == 0 ||
                 genjet_subleading_bhadron[genjetidx]->pt() < bhadron->pt()) {
        genjet_subleading_bhadron[genjetidx] = bhadron;
      }

      // leading ttH-hadron determines "mother of genjet"
      if (from_tth && (genjet_leading_bhadron_from_tth[genjetidx] == 0 ||
                       (genjet_leading_bhadron_from_tth[genjetidx] != 0 &&
                        genjet_leading_bhadron_from_tth[genjetidx]->pt() <
                          bhadron->pt()))) {
        mother_of_genjet_b[genjetidx] = motherflav;
        genjet_leading_bhadron_from_tth[genjetidx] = bhadron;
      }
    }
  };

  // loop over all chadrons
  for (uint i = 0; i < genCHadIndex.size(); i++) {
    const reco::GenParticle* chadron =
      genCHadIndex[i] >= 0 && genCHadIndex[i] < int(genCHadPlusMothers.size())
        ? &(genCHadPlusMothers[genCHadIndex[i]])
        : 0;
    int genjetidx = genCHadJetIndex[i];
    int aftertop = genCHadFromTopWeakDecay[i];
    int motherflav = genCHadFlavour[i];
    if (abs(motherflav) == 24) {
      w_c_hadron = *chadron;
    }
    // consider only hadrons not from B decays
    else if (genCHadBHadronId[i] < 0) {
      additional_c_hadrons.push_back(chadron != 0 ? *chadron
                                                  : reco::GenParticle());
      additional_c_hadron_aftertop.push_back(aftertop);
      additional_c_hadron_mother.push_back(motherflav);
      // count hadrons in genjets
      if (genjetidx >= 0 && genjetidx < int(customGenJets.size())) {
        additionalnc_per_genjet[genjetidx]++;
        c_aftertoptype_of_genjet[genjetidx] =
          std::min(c_aftertoptype_of_genjet[genjetidx], aftertop);
        if (aftertop == 1) {
          additionalnc_aftertop_per_genjet[genjetidx]++;
        }
        // find leading hadron of genjets
        if (genjet_leading_chadron[genjetidx] == 0) {
          genjet_leading_chadron[genjetidx] = chadron;
        } else if (genjet_leading_chadron[genjetidx]->pt() < chadron->pt()) {
          genjet_subleading_chadron[genjetidx] =
            genjet_leading_chadron[genjetidx];
          genjet_leading_chadron[genjetidx] = chadron;
        } else if (genjet_subleading_chadron[genjetidx] == 0 ||
                   genjet_subleading_chadron[genjetidx]->pt() < chadron->pt()) {
          genjet_subleading_chadron[genjetidx] = chadron;
        }
      }
    }
  }

  // loop over all genjets
  for (uint i = 0; i < customGenJets.size(); i++) {
    // skip jets that aren't selected
    if (customGenJets[i].pt() < ttxptcut ||
        fabs(customGenJets[i].eta()) > ttxetacut) {
      continue;
    }
    // skip light jets
    if (nb_per_genjet[i] > 0) {
      // associate genjet with tth decay products
      if (mother_of_genjet_b[i] == 25) {
        higgs_b_genjet = customGenJets[i];
      } else if (mother_of_genjet_b[i] == -25) {
        higgs_bbar_genjet = customGenJets[i];
      } else if (mother_of_genjet_b[i] == -6) {
        topbar_bbar_genjet = customGenJets[i];
      } else if (mother_of_genjet_b[i] == 6) {
        top_b_genjet = customGenJets[i];
      }
      // remaining genjets are additional
      else {
        additional_b_genjets.push_back(customGenJets[i]);
        additional_b_genjet_nb.push_back(nb_per_genjet[i]);
        additional_b_genjet_nb_aftertop.push_back(nb_aftertop_per_genjet[i]);
        additional_b_genjet_aftertoptype.push_back(b_aftertoptype_of_genjet[i]);
        additional_b_genjet_hadron.push_back(genjet_leading_bhadron[i] != 0
                                               ? *(genjet_leading_bhadron[i])
                                               : reco::GenParticle());
        additional_b_genjet_hadron2.push_back(
          genjet_subleading_bhadron[i] != 0 ? *(genjet_subleading_bhadron[i])
                                            : reco::GenParticle());
      }
    } else if (additionalnc_per_genjet[i] > 0) {
      additional_c_genjets.push_back(customGenJets[i]);
      additional_c_genjet_nc.push_back(additionalnc_per_genjet[i]);
      additional_c_genjet_nc_aftertop.push_back(
        additionalnc_aftertop_per_genjet[i]);
      additional_c_genjet_aftertoptype.push_back(c_aftertoptype_of_genjet[i]);
      additional_c_genjet_hadron.push_back(genjet_leading_chadron[i] != 0
                                             ? *(genjet_leading_chadron[i])
                                             : reco::GenParticle());
      additional_c_genjet_hadron2.push_back(genjet_subleading_chadron[i] != 0
                                              ? *(genjet_subleading_chadron[i])
                                              : reco::GenParticle());
    }
    // no b and no c hadron in jet
    else {
      bool match = false;
      for (auto const& v : tt_decay_leptons) {
        if (v.Pt() > 0.1 &&
            BoostedUtils::DeltaR(v, customGenJets[i].p4()) < wMatchR) {
          match = true;
          break;
        }
      }
      if (!match) {
        for (auto const& v : tt_decay_quarks) {
          if (v.Pt() > 0.1 &&
              BoostedUtils::DeltaR(v, customGenJets[i].p4()) < wMatchR) {
            match = true;
            break;
          }
        }
      }
      if (match) {
        w_genjets.push_back(customGenJets[i]);
      } else {
        additional_light_genjets.push_back(customGenJets[i]);
      }
    }
  }
  ttxIsFilled = true;
}
std::vector<reco::GenJet>
GenTopEvent::GetAllTopHadBGenJets() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  std::vector<reco::GenJet> tophdabs;
  if (ttxIsFilled && topIsHadronic)
    tophdabs.push_back(top_b_genjet);
  if (ttxIsFilled && topbarIsHadronic)
    tophdabs.push_back(topbar_bbar_genjet);
  return tophdabs;
}
std::vector<reco::GenJet>
GenTopEvent::GetAllTopLepBGenJets() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  std::vector<reco::GenJet> toplepbs;
  if (ttxIsFilled && !topIsHadronic)
    toplepbs.push_back(top_b_genjet);
  if (ttxIsFilled && !topbarIsHadronic)
    toplepbs.push_back(topbar_bbar_genjet);
  return toplepbs;
}
reco::GenJet
GenTopEvent::GetTopBarBBarGenJet() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return topbar_bbar_genjet;
}
reco::GenJet
GenTopEvent::GetTopBGenJet() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return top_b_genjet;
}
reco::GenJet
GenTopEvent::GetHiggsBGenJet() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return higgs_b_genjet;
}
reco::GenJet
GenTopEvent::GetHiggsBBarGenJet() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return higgs_bbar_genjet;
}
std::vector<reco::GenJet>
GenTopEvent::GetAdditionalBGenJets() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return additional_b_genjets;
}
std::vector<int>
GenTopEvent::GetAdditionalBGenJetsFromTopType() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return additional_b_genjet_aftertoptype;
}
std::vector<int>
GenTopEvent::GetAdditionalCGenJetsFromTopType() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return additional_c_genjet_aftertoptype;
}
std::vector<int>
GenTopEvent::GetAdditionalBGenJetsNHadrons() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return additional_b_genjet_nb;
}
std::vector<int>
GenTopEvent::GetAdditionalCGenJetsNHadrons() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return additional_c_genjet_nc;
}
std::vector<reco::GenJet>
GenTopEvent::GetAdditionalLightGenJets() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return additional_light_genjets;
}
std::vector<reco::GenJet>
GenTopEvent::GetWGenJets() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return w_genjets;
}
std::vector<reco::GenJet>
GenTopEvent::GetAdditionalCGenJets() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return additional_c_genjets;
}
std::vector<reco::GenParticle>
GenTopEvent::GetAllTopHadBHadrons() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  std::vector<reco::GenParticle> tophdabs;
  if (ttxIsFilled && topIsHadronic)
    tophdabs.push_back(top_b_hadron);
  if (ttxIsFilled && topbarIsHadronic)
    tophdabs.push_back(topbar_bbar_hadron);
  return tophdabs;
}
std::vector<reco::GenParticle>
GenTopEvent::GetAllTopLepBHadrons() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  std::vector<reco::GenParticle> toplepbs;
  if (ttxIsFilled && !topIsHadronic)
    toplepbs.push_back(top_b_hadron);
  if (ttxIsFilled && !topbarIsHadronic)
    toplepbs.push_back(topbar_bbar_hadron);
  return toplepbs;
}
reco::GenParticle
GenTopEvent::GetTopBarBBarHadron() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return topbar_bbar_hadron;
}
reco::GenParticle
GenTopEvent::GetTopBHadron() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return top_b_hadron;
}
reco::GenParticle
GenTopEvent::GetHiggsBHadron() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return higgs_b_hadron;
}
reco::GenParticle
GenTopEvent::GetHiggsBBarHadron() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return higgs_bbar_hadron;
}
reco::GenParticle
GenTopEvent::GetWCHadron() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return w_c_hadron;
}

std::vector<reco::GenParticle>
GenTopEvent::GetAdditionalBGenJetsHadron() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return additional_b_genjet_hadron;
}
std::vector<reco::GenParticle>
GenTopEvent::GetAdditionalCGenJetsHadron() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return additional_c_genjet_hadron;
}
std::vector<reco::GenParticle>
GenTopEvent::GetAdditionalBGenJetsHadron2() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return additional_b_genjet_hadron2;
}
std::vector<reco::GenParticle>
GenTopEvent::GetAdditionalCGenJetsHadron2() const
{
  if (!ttxIsFilled)
    std::cerr << "Trying to access GenTopEvent ttX info but it is not filled"
              << std::endl;
  return additional_c_genjet_hadron2;
}

std::vector<reco::GenParticle>
GenTopEvent::GetAdditionalBHadrons() const
{
  return additional_b_hadrons;
}
std::vector<int>
GenTopEvent::GetAdditionalBHadronMothers() const
{
  return additional_b_hadron_mother;
}
std::vector<int>
GenTopEvent::GetAdditionalBHadronAfterTopType() const
{
  return additional_b_hadron_aftertop;
}
std::vector<reco::GenParticle>
GenTopEvent::GetAdditionalCHadrons() const
{
  return additional_c_hadrons;
}
std::vector<int>
GenTopEvent::GetAdditionalCHadronMothers() const
{
  return additional_c_hadron_mother;
}
std::vector<int>
GenTopEvent::GetAdditionalCHadronAfterTopType() const
{
  return additional_c_hadron_aftertop;
}

void
GenTopEvent::FillTTdecay(
  const std::vector<reco::GenParticle>& prunedGenParticles,
  int ttXid_)
{
  bool foundT = false;
  bool foundTbar = false;
  bool foundH = false;
  ttXid = ttXid_;
  for (auto p = prunedGenParticles.begin(); p != prunedGenParticles.end();
       p++) {
    if (abs(p->pdgId()) == 6) {
      if (p->pdgId() == 6)
        foundT = true;
      if (p->pdgId() == -6)
        foundTbar = true;
      if (p->pdgId() == 6 && p->isHardProcess())
        hard_top = *p;
      if (p->pdgId() == -6 && p->isHardProcess())
        hard_topbar = *p;
      bool lastTop = true;
      for (uint i = 0; i < p->numberOfDaughters(); i++) {
        if (abs(p->daughter(i)->pdgId()) == 6)
          lastTop = false;
      }
      if (lastTop) {
        if (p->pdgId() == 6)
          top = *p;
        if (p->pdgId() == -6)
          topbar = *p;
        bool setTDecay = false;
        bool setTBarDecay = false;
        for (uint i = 0; i < p->numberOfDaughters(); i++) {
          if (p->pdgId() == 6 && abs(p->daughter(i)->pdgId()) < 6) {
            if (setTDecay)
              std::cerr << "GenTopEvent: error 1" << std::endl;
            top_decay_quark = *(reco::GenParticle*)p->daughter(i);
            setTDecay = true;
          }
          if (p->pdgId() == -6 && abs(p->daughter(i)->pdgId()) < 6) {
            if (setTBarDecay)
              std::cerr << "GenTopEvent: error 1" << std::endl;
            topbar_decay_quark = *(reco::GenParticle*)p->daughter(i);
            setTBarDecay = true;
          }
        }
      }
    }

    if (abs(p->pdgId()) == 24) {
      bool lastW = true;
      for (uint i = 0; i < p->numberOfDaughters(); i++) {
        if (abs(p->daughter(i)->pdgId()) == 24)
          lastW = false;
      }
      bool fromT = false;
      const reco::Candidate* mother = &(*p);
      while (mother != 0 && abs(mother->pdgId()) == 24) {
        if (abs(mother->mother()->pdgId()) == 6) {
          fromT = true;
          break;
        } else
          mother = mother->mother();
      }
      if (lastW && fromT) {
        if (p->pdgId() == 24)
          wplus = *p;
        if (p->pdgId() == -24)
          wminus = *p;
        for (uint i = 0; i < p->numberOfDaughters(); i++) {
          if (p->pdgId() == 24 && abs(p->daughter(i)->pdgId()) <= 16) {
            wplus_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
          }
          if (p->pdgId() == -24 && abs(p->daughter(i)->pdgId()) <= 16) {
            wminus_decay_products.push_back(
              *(reco::GenParticle*)p->daughter(i));
          }
        }
      }
    }

    if (abs(p->pdgId()) == 25) {
      bool lastH = true;
      foundH = true;
      for (uint i = 0; i < p->numberOfDaughters(); i++) {
        if (abs(p->daughter(i)->pdgId()) == 25)
          lastH = false;
      }
      if (lastH) {
        higgs = *p;
        for (uint i = 0; i < p->numberOfDaughters(); i++) {
          if (p->pdgId() == 25 && abs(p->daughter(i)->pdgId()) != 25) {
            higgs_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
          }
        }
      }
    }
  }
  if (wminus_decay_products.size() != 2 || wplus_decay_products.size() != 2) {
    std::cerr << "GenTopEvent: error 2" << std::endl;
    while (wminus_decay_products.size() < 2) {
      wminus_decay_products.push_back(reco::GenParticle());
    }
  }
  if (top.energy() < 1 || topbar.energy() < 1 || wplus.energy() < 1 ||
      wminus.energy() < 1 || top_decay_quark.energy() < 1 ||
      topbar_decay_quark.energy() < 1)
    std::cerr << "GenTopEvent: error 4" << std::endl;

  int nquarks_from_wplus = 0;
  for (auto p = wplus_decay_products.begin(); p != wplus_decay_products.end();
       p++) {
    if (abs(p->pdgId()) < 6)
      nquarks_from_wplus++;
  }
  int nquarks_from_wminus = 0;
  for (auto p = wminus_decay_products.begin(); p != wminus_decay_products.end();
       p++) {
    if (abs(p->pdgId()) < 6)
      nquarks_from_wminus++;
  }
  topIsHadronic = nquarks_from_wplus == 2;
  topbarIsHadronic = nquarks_from_wminus == 2;
  isTTbar = foundT && foundTbar;
  isTTH = foundT && foundTbar && foundH;
  isFilled = true;
}

void
GenTopEvent::Print() const
{
  std::cout << "top" << std::endl;
  PrintParticle(GetTop());
  std::cout << "top decay quark" << std::endl;
  PrintParticle(GetTopDecayQuark());
  std::cout << "higgs" << std::endl;
  PrintParticle(GetHiggs());
  std::cout << "higgs decay products" << std::endl;
  PrintParticles(GetHiggsDecayProducts());
  std::cout << "topbar" << std::endl;
  PrintParticle(GetTopBar());
  std::cout << "topbar decay quark" << std::endl;
  PrintParticle(GetTopBarDecayQuark());
  std::cout << "wplus" << std::endl;
  PrintParticle(GetWplus());
  std::cout << "wplus decay products" << std::endl;
  PrintParticles(GetWplusDecayProducts());
  std::cout << "wminus" << std::endl;
  PrintParticle(GetWminus());
  std::cout << "wminus decay products" << std::endl;
  PrintParticles(GetWminusDecayProducts());
  std::cout << "all top hads" << std::endl;
  PrintParticles(GetAllTopHads());
  std::cout << "all W hads" << std::endl;
  PrintParticles(GetAllWhads());
  std::cout << "all tophad bs" << std::endl;
  PrintParticles(GetAllTopHadDecayQuarks());
  std::cout << "all tophad W quarks" << std::endl;
  PrintParticles(GetAllWQuarks());
  std::cout << "all tophad W anti quarks" << std::endl;
  PrintParticles(GetAllWAntiQuarks());
  std::cout << "all top leps" << std::endl;
  PrintParticles(GetAllTopLeps());
  std::cout << "all w leps" << std::endl;
  PrintParticles(GetAllWleps());
  std::cout << "all top lep bs" << std::endl;
  PrintParticles(GetAllTopLepDecayQuarks());
  std::cout << "all leptons" << std::endl;
  PrintParticles(GetAllLeptons());
  std::cout << "all neutrinos" << std::endl;
  PrintParticles(GetAllNeutrinos());
  std::cout << "============================" << std::endl;
}
void
GenTopEvent::PrintTTX() const
{
  std::cout << "----------------------------" << std::endl;
  std::cout << "additional_b_genjets.size()" << std::endl;
  std::cout << additional_b_genjets.size() << std::endl;
  for (uint i = 0; i < additional_b_genjets.size(); i++) {
    std::cout << "  additional_b_genjets[i].pt() .eta() .phi()" << std::endl;
    std::cout << additional_b_genjets[i].pt() << " "
              << additional_b_genjets[i].eta() << " "
              << additional_b_genjets[i].phi() << std::endl;
    std::cout << "  additional_b_genjet_nb[i]" << std::endl;
    std::cout << additional_b_genjet_nb[i] << std::endl;
    std::cout << "  additional_b_genjet_nb_aftertop[i]" << std::endl;
    std::cout << additional_b_genjet_nb_aftertop[i] << std::endl;
    std::cout << "  additional_b_genjet_hadron[i].pt()" << std::endl;
    std::cout << additional_b_genjet_hadron[i].pt() << std::endl;
    std::cout << "............................" << std::endl;
  }
  std::cout << "----------------------------" << std::endl;
  std::cout << "additional_c_genjets.size()" << std::endl;
  std::cout << additional_c_genjets.size() << std::endl;
  for (uint i = 0; i < additional_c_genjets.size(); i++) {
    std::cout << "  additional_c_genjets[i].pt() .eta() .phi()" << std::endl;
    std::cout << additional_c_genjets[i].pt() << " "
              << additional_c_genjets[i].eta() << " "
              << additional_c_genjets[i].phi() << std::endl;
    std::cout << "  additional_c_genjet_nc[i]" << std::endl;
    std::cout << additional_c_genjet_nc[i] << std::endl;
    std::cout << "  additional_c_genjet_nc_aftertop[i]" << std::endl;
    std::cout << additional_c_genjet_nc_aftertop[i] << std::endl;
    std::cout << "  additional_c_genjet_hadron[i].pt()" << std::endl;
    std::cout << additional_c_genjet_hadron[i].pt() << std::endl;
    std::cout << "............................" << std::endl;
  }
  std::cout << "----------------------------" << std::endl;
  std::cout << "tt+x id" << std::endl;
  std::cout << GetTTxId() << std::endl;
  std::cout << "tt+x id miniaodhelper" << std::endl;
  std::cout << GetTTxIdFromProducer() << std::endl;
  assert(GetTTxId(true) == GetTTxIdFromProducer());

  std::cout << "============================" << std::endl;
}
void
GenTopEvent::PrintParticle(reco::GenParticle p) const
{
  std::cout << "pdgId: " << p.pdgId() << ", pt: " << p.pt()
            << ", eta: " << p.eta() << ", phi: " << p.phi() << std::endl;
}
void
GenTopEvent::PrintParticles(std::vector<reco::GenParticle> ps) const
{
  for (auto p = ps.begin(); p != ps.end(); p++) {
    PrintParticle(*p);
  }
}
reco::GenParticle
GenTopEvent::GetHiggs() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  return higgs;
}
reco::GenParticle
GenTopEvent::GetTop() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  return top;
}
reco::GenParticle
GenTopEvent::GetTopBar() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  return topbar;
}
reco::GenParticle
GenTopEvent::GetHardTop() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  return hard_top;
}
reco::GenParticle
GenTopEvent::GetHardTopBar() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  return hard_topbar;
}
reco::GenParticle
GenTopEvent::GetTopHad() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  if (topIsHadronic && !topbarIsHadronic)
    return top;
  else if (!topIsHadronic && topbarIsHadronic)
    return topbar;
  else {
    std::cerr << "hadronic/leptonic function called in GenTopEvent, but not a "
                 "semileptonic event"
              << std::endl;
    return reco::GenParticle();
  }
}
reco::GenParticle
GenTopEvent::GetTopLep() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  if (topIsHadronic && !topbarIsHadronic)
    return topbar;
  else if (!topIsHadronic && topbarIsHadronic)
    return top;
  else {
    std::cerr << "hadronic/leptonic function called in GenTopEvent, but not a "
                 "semileptonic event"
              << std::endl;
    return reco::GenParticle();
  }
}
reco::GenParticle
GenTopEvent::GetWplus() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  return wplus;
}
reco::GenParticle
GenTopEvent::GetWminus() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  return wminus;
}
reco::GenParticle
GenTopEvent::GetWhad() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  if (topIsHadronic && !topbarIsHadronic)
    return wplus;
  else if (!topIsHadronic && topbarIsHadronic)
    return wminus;
  else {
    std::cerr << "hadronic/leptonic function called in GenTopEvent, but not a "
                 "semileptonic event"
              << std::endl;
    return reco::GenParticle();
  }
}
reco::GenParticle
GenTopEvent::GetWlep() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  if (topIsHadronic && !topbarIsHadronic)
    return wminus;
  else if (!topIsHadronic && topbarIsHadronic)
    return wplus;
  else {
    std::cerr << "hadronic/leptonic function called in GenTopEvent, but not a "
                 "semileptonic event"
              << std::endl;
    return reco::GenParticle();
  }
}
std::vector<reco::GenParticle>
GenTopEvent::GetWLeptons() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  if (topIsHadronic && !topbarIsHadronic)
    return wminus_decay_products;
  else if (!topIsHadronic && topbarIsHadronic)
    return wplus_decay_products;
  else {
    std::cerr << "hadronic/leptonic function called in GenTopEvent, but not a "
                 "semileptonic event"
              << std::endl;
    return std::vector<reco::GenParticle>();
  }
}
reco::GenParticle
GenTopEvent::GetLepton() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  if (topIsHadronic && !topbarIsHadronic) {
    for (auto p = wminus_decay_products.begin();
         p != wminus_decay_products.end();
         p++) {
      if (p->pdgId() == 11 || p->pdgId() == 13 || p->pdgId() == 15)
        return *p;
    }
    std::cerr << "no lepton found" << std::endl;
    return reco::GenParticle();
  } else if (!topIsHadronic && topbarIsHadronic) {
    for (auto p = wplus_decay_products.begin(); p != wplus_decay_products.end();
         p++) {
      if (p->pdgId() == -11 || p->pdgId() == -13 || p->pdgId() == -15)
        return *p;
    }
    std::cerr << "no lepton found" << std::endl;
    return reco::GenParticle();
  }
  std::cerr << "hadronic/leptonic function called in GenTopEvent, but not a "
               "semileptonic event"
            << std::endl;
  return reco::GenParticle();
}

reco::GenParticle
GenTopEvent::GetNeutrino() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  if (topIsHadronic && !topbarIsHadronic) {
    for (auto p = wminus_decay_products.begin();
         p != wminus_decay_products.end();
         p++) {
      if (abs(p->pdgId()) == 12 || abs(p->pdgId()) == 14 ||
          abs(p->pdgId()) == 16)
        return *p;
    }
    std::cerr << "no lepton found" << std::endl;
    return reco::GenParticle();
  } else if (!topIsHadronic && topbarIsHadronic) {
    for (auto p = wplus_decay_products.begin(); p != wplus_decay_products.end();
         p++) {
      if (abs(p->pdgId()) == 12 || abs(p->pdgId()) == 14 ||
          abs(p->pdgId()) == 16)
        return *p;
    }
    std::cerr << "no lepton found" << std::endl;
    return reco::GenParticle();
  }
  std::cerr << "hadronic/leptonic function called in GenTopEvent, but not a "
               "semileptonic event"
            << std::endl;
  return reco::GenParticle();
}

std::vector<reco::GenParticle>
GenTopEvent::GetWQuarks() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  if (topIsHadronic && !topbarIsHadronic)
    return wplus_decay_products;
  else if (!topIsHadronic && topbarIsHadronic)
    return wminus_decay_products;
  else {
    std::cerr << "hadronic/leptonic function called in GenTopEvent, but not a "
                 "semileptonic event"
              << std::endl;
    return std::vector<reco::GenParticle>();
  }
}
std::vector<reco::GenParticle>
GenTopEvent::GetHiggsDecayProducts() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  return higgs_decay_products;
}
reco::GenParticle
GenTopEvent::GetTopDecayQuark() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  return top_decay_quark;
}
reco::GenParticle
GenTopEvent::GetTopBarDecayQuark() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  return topbar_decay_quark;
}
reco::GenParticle
GenTopEvent::GetTopHadDecayQuark() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  if (topIsHadronic && !topbarIsHadronic)
    return top_decay_quark;
  else if (!topIsHadronic && topbarIsHadronic)
    return topbar_decay_quark;
  else {
    std::cerr << "hadronic/leptonic function called in GenTopEvent, but not a "
                 "semileptonic event"
              << std::endl;
    return reco::GenParticle();
  }
}
reco::GenParticle
GenTopEvent::GetTopLepDecayQuark() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  if (topIsHadronic && !topbarIsHadronic)
    return topbar_decay_quark;
  else if (!topIsHadronic && topbarIsHadronic)
    return top_decay_quark;
  else {
    std::cerr << "hadronic/leptonic function called in GenTopEvent, but not a "
                 "semileptonic event"
              << std::endl;
    return reco::GenParticle();
  }
}
std::vector<reco::GenParticle>
GenTopEvent::GetQuarks() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  std::vector<reco::GenParticle> quarks;
  quarks.push_back(top_decay_quark);
  quarks.push_back(topbar_decay_quark);
  for (auto p = wplus_decay_products.begin(); p != wplus_decay_products.end();
       p++) {
    quarks.push_back(*p);
  }
  for (auto p = wminus_decay_products.begin(); p != wminus_decay_products.end();
       p++) {
    quarks.push_back(*p);
  }
  for (auto p = higgs_decay_products.begin(); p != higgs_decay_products.end();
       p++) {
    quarks.push_back(*p);
  }
  return quarks;
}
std::vector<reco::GenParticle>
GenTopEvent::GetWplusDecayProducts() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  return wplus_decay_products;
}
std::vector<reco::GenParticle>
GenTopEvent::GetWminusDecayProducts() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  return wminus_decay_products;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle>
GenTopEvent::GetAllTopHads() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  std::vector<reco::GenParticle> tophads;
  assert(isFilled);
  if (isFilled && topIsHadronic)
    tophads.push_back(top);
  if (isFilled && topbarIsHadronic)
    tophads.push_back(topbar);
  return tophads;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle>
GenTopEvent::GetAllTopLeps() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  std::vector<reco::GenParticle> topleps;
  assert(isFilled);
  if (isFilled && !topIsHadronic)
    topleps.push_back(top);
  if (isFilled && !topbarIsHadronic)
    topleps.push_back(topbar);
  return topleps;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle>
GenTopEvent::GetAllTopHadDecayQuarks() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  std::vector<reco::GenParticle> quarks;
  assert(isFilled);
  if (isFilled && topIsHadronic)
    quarks.push_back(top_decay_quark);
  if (isFilled && topbarIsHadronic)
    quarks.push_back(topbar_decay_quark);
  return quarks;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle>
GenTopEvent::GetAllTopLepDecayQuarks() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  std::vector<reco::GenParticle> quarks;
  assert(isFilled);
  if (isFilled && !topIsHadronic)
    quarks.push_back(top_decay_quark);
  if (isFilled && !topbarIsHadronic)
    quarks.push_back(topbar_decay_quark);
  return quarks;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle>
GenTopEvent::GetAllWhads() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  std::vector<reco::GenParticle> ws;
  assert(isFilled);
  if (isFilled && topIsHadronic)
    ws.push_back(wplus);
  if (isFilled && topbarIsHadronic)
    ws.push_back(wminus);
  return ws;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle>
GenTopEvent::GetAllWleps() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent but it is not filled"
              << std::endl;
  std::vector<reco::GenParticle> ws;
  assert(isFilled);
  if (isFilled && !topIsHadronic)
    ws.push_back(wplus);
  if (isFilled && !topbarIsHadronic)
    ws.push_back(wminus);
  return ws;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle>
GenTopEvent::GetAllLeptons() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent Leptons but it is not filled"
              << std::endl;
  std::vector<reco::GenParticle> leptons;
  assert(isFilled);
  for (auto p = wplus_decay_products.begin();
       isFilled && p != wplus_decay_products.end();
       p++) {
    if (abs(p->pdgId()) == 11 || abs(p->pdgId()) == 13 || abs(p->pdgId()) == 15)
      leptons.push_back(*p);
  }
  assert(isFilled);
  for (auto p = wminus_decay_products.begin();
       isFilled && p != wminus_decay_products.end();
       p++) {
    if (abs(p->pdgId()) == 11 || abs(p->pdgId()) == 13 || abs(p->pdgId()) == 15)
      leptons.push_back(*p);
  }
  for (int i = 0;
       i + (isFilled && !topIsHadronic) + (isFilled && !topbarIsHadronic) < 2;
       i++) {
    leptons.push_back(reco::GenParticle());
  }

  return leptons;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle>
GenTopEvent::GetAllNeutrinos() const
{
  std::vector<reco::GenParticle> neutrinos;
  assert(isFilled);
  for (auto p = wplus_decay_products.begin();
       isFilled && p != wplus_decay_products.end();
       p++) {
    if (abs(p->pdgId()) == 12 || abs(p->pdgId()) == 14 || abs(p->pdgId()) == 16)
      neutrinos.push_back(*p);
  }
  assert(isFilled);
  for (auto p = wminus_decay_products.begin();
       isFilled && p != wminus_decay_products.end();
       p++) {
    if (abs(p->pdgId()) == 12 || abs(p->pdgId()) == 14 || abs(p->pdgId()) == 16)
      neutrinos.push_back(*p);
  }
  for (int i = 0;
       i + (isFilled && !topIsHadronic) + (isFilled && !topbarIsHadronic) < 2;
       i++) {
    neutrinos.push_back(reco::GenParticle());
  }
  return neutrinos;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle>
GenTopEvent::GetAllWQuarks() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent Quarks but it is not filled"
              << std::endl;
  std::vector<reco::GenParticle> quarks;
  assert(isFilled);
  for (auto p = wplus_decay_products.begin();
       isFilled && p != wplus_decay_products.end();
       p++) {
    if (p->pdgId() > 0 && p->pdgId() < 6)
      quarks.push_back(*p);
  }
  assert(isFilled);
  for (auto p = wminus_decay_products.begin();
       isFilled && p != wminus_decay_products.end();
       p++) {
    if (p->pdgId() > 0 && p->pdgId() < 6)
      quarks.push_back(*p);
  }
  for (int i = 0;
       i + (isFilled && !topIsHadronic) + (isFilled && !topbarIsHadronic) < 2;
       i++) {
    quarks.push_back(reco::GenParticle());
  }
  return quarks;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle>
GenTopEvent::GetAllWAntiQuarks() const
{
  assert(isFilled);
  if (!isFilled)
    std::cerr << "Trying to access GenTopEvent AntiQuarks but it is not filled"
              << std::endl;
  std::vector<reco::GenParticle> quarks;
  assert(isFilled);
  for (auto p = wplus_decay_products.begin();
       isFilled && p != wplus_decay_products.end();
       p++) {
    if (p->pdgId() < 0 && p->pdgId() > -6)
      quarks.push_back(*p);
  }
  assert(isFilled);
  for (auto p = wminus_decay_products.begin();
       isFilled && p != wminus_decay_products.end();
       p++) {
    if (p->pdgId() < 0 && p->pdgId() > -6)
      quarks.push_back(*p);
  }
  for (int i = 0;
       i + (isFilled && !topIsHadronic) + (isFilled && !topbarIsHadronic) < 2;
       i++) {
    quarks.push_back(reco::GenParticle());
  }
  return quarks;
}

std::vector<math::XYZTLorentzVector>
GenTopEvent::GetAllTopHadVecs() const
{
  return GetLVs(GetAllTopHads());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetAllTopLepVecs() const
{
  return GetLVs(GetAllTopLeps());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetAllTopHadDecayQuarkVecs() const
{
  return GetLVs(GetAllTopHadDecayQuarks());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetAllTopLepDecayQuarkVecs() const
{
  return GetLVs(GetAllTopLepDecayQuarks());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetAllWhadVecs() const
{
  return GetLVs(GetAllWhads());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetAllWlepVecs() const
{
  return GetLVs(GetAllWleps());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetAllLeptonVecs() const
{
  return GetLVs(GetAllLeptons());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetAllNeutrinoVecs() const
{
  return GetLVs(GetAllNeutrinos());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetAllWQuarkVecs() const
{
  return GetLVs(GetAllWQuarks());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetAllWAntiQuarkVecs() const
{
  return GetLVs(GetAllWAntiQuarks());
}

math::XYZTLorentzVector
GenTopEvent::GetHiggsVec() const
{
  return GetLV(GetHiggs());
}
math::XYZTLorentzVector
GenTopEvent::GetTopVec() const
{
  return GetLV(GetTop());
}
math::XYZTLorentzVector
GenTopEvent::GetTopBarVec() const
{
  return GetLV(GetTopBar());
}
math::XYZTLorentzVector
GenTopEvent::GetTopHadVec() const
{
  return GetLV(GetTopHad());
}
math::XYZTLorentzVector
GenTopEvent::GetTopLepVec() const
{
  return GetLV(GetTopLep());
}
math::XYZTLorentzVector
GenTopEvent::GetWplusVec() const
{
  return GetLV(GetWplus());
}
math::XYZTLorentzVector
GenTopEvent::GetWminusVec() const
{
  return GetLV(GetWminus());
}
math::XYZTLorentzVector
GenTopEvent::GetWhadVec() const
{
  return GetLV(GetWhad());
}
math::XYZTLorentzVector
GenTopEvent::GetWlepVec() const
{
  return GetLV(GetWlep());
}
math::XYZTLorentzVector
GenTopEvent::GetLeptonVec() const
{
  return GetLV(GetLepton());
}
math::XYZTLorentzVector
GenTopEvent::GetNeutrinoVec() const
{
  return GetLV(GetNeutrino());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetQuarkVecs() const
{
  return GetLVs(GetQuarks());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetHiggsDecayProductVecs() const
{
  return GetLVs(GetHiggsDecayProducts());
}
math::XYZTLorentzVector
GenTopEvent::GetTopDecayQuarkVec() const
{
  return GetLV(GetTopDecayQuark());
}
math::XYZTLorentzVector
GenTopEvent::GetTopBarDecayQuarkVec() const
{
  return GetLV(GetTopBarDecayQuark());
}
math::XYZTLorentzVector
GenTopEvent::GetTopHadDecayQuarkVec() const
{
  return GetLV(GetTopHadDecayQuark());
}
math::XYZTLorentzVector
GenTopEvent::GetTopLepDecayQuarkVec() const
{
  return GetLV(GetTopLepDecayQuark());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetWLeptonsVecs() const
{
  return GetLVs(GetWLeptons());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetWQuarksVecs() const
{
  return GetLVs(GetWQuarks());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetWplusDecayProductsVecs() const
{
  return GetLVs(GetWplusDecayProducts());
}
std::vector<math::XYZTLorentzVector>
GenTopEvent::GetWminusDecayProductsVecs() const
{
  return GetLVs(GetWminusDecayProducts());
}

bool
GenTopEvent::IsTTbar() const
{
  return isTTbar;
}
bool
GenTopEvent::IsTTH() const
{
  return isTTH;
}
bool
GenTopEvent::IsAllHadron() const
{
  return topIsHadronic && topbarIsHadronic;
}
bool
GenTopEvent::IsDiLepton() const
{
  return !topIsHadronic && !topbarIsHadronic;
}
bool
GenTopEvent::IsSemiLepton() const
{
  return (topIsHadronic && !topbarIsHadronic) ||
         (!topIsHadronic && topbarIsHadronic);
}
math::XYZTLorentzVector
GenTopEvent::GetLV(const reco::GenParticle& p) const
{
  return math::XYZTLorentzVector(p.px(), p.py(), p.pz(), p.energy());
}

std::vector<math::XYZTLorentzVector>
GenTopEvent::GetLVs(const std::vector<reco::GenParticle>& ps) const
{
  std::vector<math::XYZTLorentzVector> vecs;
  for (auto p = ps.begin(); p != ps.end(); p++) {
    vecs.push_back(GetLV(*p));
  }
  return vecs;
}

int
GenTopEvent::GetTTxIdFromProducer() const
{
  return ttXid % 100;
}

int
GenTopEvent::GetTTxIdFromProducerLong() const
{
  return ttXid;
}

int
GenTopEvent::GetTTxId(bool countPseudoAdditional) const
{
  int n_cjets_single = 0;
  int n_bjets_single = 0;
  int n_pseudobjets_single = 0;
  int n_pseudocjets_single = 0;
  int n_cjets_double = 0;
  int n_bjets_double = 0;
  int n_pseudobjets_double = 0;
  int n_pseudocjets_double = 0;
  // consider only the two leading gen jets
  for (int i = 0; i < std::min(2, int(additional_c_genjets.size())); i++) {
    if (countPseudoAdditional) {
      if (additional_c_genjet_nc[i] == 1)
        n_cjets_single++;
      else if (additional_c_genjet_nc[i] > 1)
        n_cjets_double++;
    } else {
      if (additional_c_genjet_nc[i] - additional_c_genjet_nc_aftertop[i] == 1)
        n_cjets_single++;
      else if (additional_c_genjet_nc[i] - additional_c_genjet_nc_aftertop[i] >
               1)
        n_cjets_double++;
      else if (additional_c_genjet_nc_aftertop[i] == 1)
        n_pseudocjets_single++;
      else if (additional_c_genjet_nc_aftertop[i] > 1)
        n_pseudocjets_double++;
    }
  }
  // consider only the two leading hf jets
  for (int i = 0; i < std::min(2, int(additional_b_genjets.size())); i++) {
    if (countPseudoAdditional) {
      if (additional_b_genjet_nb[i] == 1)
        n_bjets_single++;
      else if (additional_b_genjet_nb[i] > 1)
        n_bjets_double++;
    } else {
      if (additional_b_genjet_nb[i] - additional_b_genjet_nb_aftertop[i] == 1)
        n_bjets_single++;
      else if (additional_b_genjet_nb[i] - additional_b_genjet_nb_aftertop[i] >
               1)
        n_bjets_double++;
      else if (additional_b_genjet_nb_aftertop[i] == 1)
        n_pseudobjets_single++;
      else if (additional_b_genjet_nb_aftertop[i] > 1)
        n_pseudobjets_double++;
    }
  }

  // tt + 1 additional b jet from 1 additional b hadron == 51
  if (n_bjets_single == 1 && n_bjets_double == 0)
    return 51;
  // tt + 1 additional b jet from >=2 additional b hadrons == 52
  if (n_bjets_single == 0 && n_bjets_double == 1)
    return 52;
  // tt + 2 additional b jets each from 1 additional b hadron == 53
  if (n_bjets_single >= 2 && n_bjets_double == 0)
    return 53;
  // tt + 2 additional b jets one of which from >=2 overlapping additional b
  // hadrons == 54
  if (n_bjets_single >= 1 && n_bjets_double == 1)
    return 54;
  // tt + 2 additional b jets each from >=2 additional b hadrons == 55
  if (n_bjets_double >= 2)
    return 55;
  // tt + >=1 pseudo-additional b jet with b hadrons after top quark decay == 56
  if (n_pseudobjets_single + n_pseudobjets_double > 0)
    return 56;

  // tt + 1 additional c jet from 1 additional b hadron == 41
  if (n_cjets_single == 1 && n_cjets_double == 0)
    return 41;
  // tt + 1 additional c jet from >=2 additional c hadrons == 42
  if (n_cjets_single == 0 && n_cjets_double == 1)
    return 42;
  // tt + 2 additional c jets each from 1 additional c hadron == 43
  if (n_cjets_single >= 2 && n_cjets_double == 0)
    return 43;
  // tt + 2 additional c jets one of which from >=2 overlapping additional c
  // hadrons == 44
  if (n_cjets_single >= 1 && n_cjets_double == 1)
    return 44;
  // tt + 2 additional c jets each from >=2 additional c hadrons == 44
  if (n_cjets_double >= 2)
    return 45;
  // tt + >=1 pseudo-additional c jet with c hadrons after top quark decay == 46
  if (n_pseudocjets_single + n_pseudocjets_double > 0)
    return 46;

  return 0;
}
