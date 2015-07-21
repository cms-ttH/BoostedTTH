#include "BoostedTTH/BoostedAnalyzer/interface/JetMatching.hpp"

using namespace std;

std::vector<pat::Jet> JetMatching::GetFilterjets(const boosted::SubFilterJetCollection &subfilterJets, const float& ptcut, const float& etacut){
  std::vector<pat::Jet> filterjets;
  for(size_t j=0; j< subfilterJets.size(); j++){
    for(size_t k=0; k< subfilterJets[j].filterjets.size(); k++){
      if(subfilterJets[j].filterjets[k].pt()>=ptcut && subfilterJets[j].filterjets[k].eta()<etacut) filterjets.push_back(subfilterJets[j].filterjets[k]);
    }
  }
  return filterjets;
}

std::vector<pat::Jet> JetMatching::GetFilterjets(const boosted::HTTTopJetCollection &htttopjets, const float& ptcut, const float& etacut){
  std::vector<pat::Jet> filterjets;
  for(size_t j=0; j< htttopjets.size(); j++){
    if(htttopjets[j].nonW.pt()>ptcut && htttopjets[j].nonW.eta()<etacut) filterjets.push_back(htttopjets[j].nonW);
    if(htttopjets[j].W1.pt()>ptcut && htttopjets[j].W1.eta()<etacut) filterjets.push_back(htttopjets[j].W1);
    if(htttopjets[j].W2.pt()>ptcut && htttopjets[j].W2.eta()<etacut) filterjets.push_back(htttopjets[j].W2);
  }
  return filterjets;
}

std::vector<TLorentzVector> JetMatching::GetMatchedVecs(const std::vector<pat::Jet>& filterJets, const std::vector<pat::Jet>& jets, std::vector<float>& DCSV_Matchedfilterjets, std::vector<float>& Dr_Matchedfilterjets){
  std::vector<pat::Jet> fjets = filterJets;
  std::vector<TLorentzVector> matchjetdiff;
  for(std::vector<pat::Jet>::const_iterator itJet=jets.begin();itJet!=jets.end();++itJet){
    std::vector<pat::Jet>::const_iterator itmJet;
    float drmin = 0.4;
    for(std::vector<pat::Jet>::const_iterator itfJet=fjets.begin();itfJet!=fjets.end();++itfJet){
      float DeltaR = BoostedUtils::DeltaR(itJet->p4(), itfJet->p4());
      if(DeltaR<drmin){
        drmin = DeltaR;
        itmJet = itfJet;
      }
    }
    if(drmin < 0.4){
      TLorentzVector mjet;
      mjet.SetPtEtaPhiE(itmJet->pt()/itJet->pt(), itJet->eta()-itmJet->eta(), itJet->phi()-itmJet->phi(), itmJet->energy()/itJet->energy());
      matchjetdiff.push_back(mjet);
      DCSV_Matchedfilterjets.push_back(itJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")-itmJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
      Dr_Matchedfilterjets.push_back(drmin);
//       fjets.erase(itmJet);
    }
  }

  return matchjetdiff;
}
