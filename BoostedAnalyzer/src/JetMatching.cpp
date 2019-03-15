#include "BoostedTTH/BoostedAnalyzer/interface/JetMatching.hpp"

using namespace std;

std::vector<pat::Jet> JetMatching::GetFilterjets(const boosted::BoostedJetCollection &boostedJets, const float& ptcut, const float& etacut){
  std::vector<pat::Jet> filterjets;
  
  for(size_t j=0; j< boostedJets.size(); j++){
    if(boostedJets[j].nonW.pt()>ptcut && boostedJets[j].nonW.eta()<etacut) filterjets.push_back(boostedJets[j].nonW);
    if(boostedJets[j].W1.pt()>ptcut && boostedJets[j].W1.eta()<etacut) filterjets.push_back(boostedJets[j].W1);
    if(boostedJets[j].W2.pt()>ptcut && boostedJets[j].W2.eta()<etacut) filterjets.push_back(boostedJets[j].W2);
    
    for(size_t k=0; k< boostedJets[j].filterjets.size(); k++){
      if(boostedJets[j].filterjets[k].pt()>=ptcut && boostedJets[j].filterjets[k].eta()<etacut) filterjets.push_back(boostedJets[j].filterjets[k]);
    }
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
      DCSV_Matchedfilterjets.push_back(CSVHelper::GetJetCSV(*itJet,"DeepCSV")-CSVHelper::GetJetCSV(*itmJet,"DeepCSV"));
      Dr_Matchedfilterjets.push_back(drmin);
//       fjets.erase(itmJet);
    }
  }

  return matchjetdiff;
}
