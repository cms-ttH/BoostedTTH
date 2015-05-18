#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

using namespace std;


std::string BoostedUtils::GetAnalyzerPath(){
  char* cpath;
  cpath = getenv("CMSSW_BASE");
  std::string path = cpath;
  
  if (path.size() == 0){
    cerr << "could not find path of exe" << endl;
    return path;
  }
  else
    return path+"/src/BoostedTTH/BoostedAnalyzer";
}


TLorentzVector BoostedUtils::GetTLorentzVector(const math::XYZTLorentzVector& vec){
  
  TLorentzVector result(vec.Px(),vec.Py(),vec.Pz(),vec.E());
  
  return result;
  
}

vector<TLorentzVector> BoostedUtils::GetTLorentzVectors(const std::vector<math::XYZTLorentzVector>& vecs){
  vector<TLorentzVector> results;
  for(auto vec=vecs.begin();vec!=vecs.end();vec++){
    TLorentzVector result(vec->Px(),vec->Py(),vec->Pz(),vec->E());
    results.push_back(result);
  }
  return results;
  
}

math::XYZTLorentzVector BoostedUtils::GetXYZTLorentzVector(const TLorentzVector& vec){
  
  math::XYZTLorentzVector result(vec.Px(),vec.Py(),vec.Pz(),vec.E());
  
  return result;  
}

bool BoostedUtils::FirstIsHarder(math::XYZTLorentzVector vec1,math::XYZTLorentzVector vec2){
  return vec1.Pt()>vec2.Pt();
}

bool BoostedUtils::FirstJetIsHarder(pat::Jet jet1, pat::Jet jet2){
  return jet1.pt()>jet2.pt();
}

bool BoostedUtils::FirstHasHigherCSV(pat::Jet jet1,pat::Jet jet2){
  return jet1.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags") > jet2.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
}


bool BoostedUtils::FirstHasHigherCSVold(pat::Jet jet1,pat::Jet jet2){
  return jet1.bDiscriminator("combinedSecondaryVertexBJetTags") > jet2.bDiscriminator("combinedSecondaryVertexBJetTags");
}


float BoostedUtils::DeltaEta(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2){
  if(vec1.Pt()<0.001||vec2.Pt()<0.001) return -2;
  
  float deta = fabs(vec1.Eta()-vec2.Eta());
  
  return deta;
}


float BoostedUtils::DeltaEta(const pat::Jet& jet1,const pat::Jet& jet2){
  if(jet1.pt()<0.001||jet2.pt()<0.001) return -2;
  
  math::XYZTLorentzVector vec1 = jet1.p4();
  math::XYZTLorentzVector vec2 = jet2.p4();
  
  float deta = fabs(vec1.Eta()-vec2.Eta());
  
  return deta;
}


float BoostedUtils::DeltaPhi(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2){
  if(vec1.Pt()<0.001||vec2.Pt()<0.001) return -2;
  
  float dphi = ROOT::Math::VectorUtil::DeltaPhi(vec1,vec2);
  
  return fabs(dphi);
}


float BoostedUtils::DeltaPhi(const pat::Jet& jet1,const pat::Jet& jet2){
  if(jet1.pt()<0.001||jet2.pt()<0.001) return -2;
  
  math::XYZTLorentzVector vec1 = jet1.p4();
  math::XYZTLorentzVector vec2 = jet2.p4();
  
  float dphi = ROOT::Math::VectorUtil::DeltaPhi(vec1,vec2);
  
  return fabs(dphi);
}


float BoostedUtils::DeltaR(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2){
  if(vec1.Pt()<0.001||vec2.Pt()<0.001){
    //throw std::invalid_argument( "BoostedUtils::DeltaR: vector with zero pt" );
    std::cerr << "BoostedUtils::DeltaR: vector with zero pt" << std::endl;
    return -2;
  }
  
  float dr = ROOT::Math::VectorUtil::DeltaR(vec1,vec2);
  
  return dr;
}


float BoostedUtils::DeltaR(const pat::Jet& jet1,const pat::Jet& jet2){
  
  math::XYZTLorentzVector vec1 = jet1.p4();
  math::XYZTLorentzVector vec2 = jet2.p4();
  
  float dr = BoostedUtils::DeltaR(vec1,vec2);
  
  return dr;
}


float BoostedUtils::DeltaKt(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2){
  
  float dr = BoostedUtils::DeltaR(vec1,vec2);
  float ptmin=min(vec1.Pt(),vec2.Pt());
  
  return sqrt(dr*dr*ptmin*ptmin);
}


float BoostedUtils::DeltaKt(const pat::Jet& jet1,const pat::Jet& jet2){
  if(jet1.pt()<0.001||jet2.pt()<0.001) return -2;
  
  math::XYZTLorentzVector vec1 = jet1.p4();
  math::XYZTLorentzVector vec2 = jet2.p4();
  
  return BoostedUtils::DeltaKt(vec1,vec2);
}


float BoostedUtils::CosThetaStar(const math::XYZTLorentzVector& vec1, const math::XYZTLorentzVector& vec2){
  if(vec1.Pt()<0.001||vec2.Pt()<0.001) return -2;
  
  TLorentzVector sumVec = BoostedUtils::GetTLorentzVector(vec1+vec2);
  TVector3 cmboost = -sumVec.BoostVector();
  
  TLorentzVector boostedvec1 = GetTLorentzVector(vec1);
  boostedvec1.Boost(cmboost);
  
  return cos( sumVec.Angle(boostedvec1.Vect()) );
}


float BoostedUtils::CosThetaCM(const math::XYZTLorentzVector& vec,const math::XYZTLorentzVector& boostVec){
  if(vec.Pt()<0.001||boostVec.Pt()<0.001) return -2;
  
  TLorentzVector vec_ = GetTLorentzVector(vec);
  TLorentzVector boostVec_ = GetTLorentzVector(boostVec);
  
  TVector3 zBoost = TVector3(0,0,-boostVec_.BoostVector().Pz());
  TLorentzVector boostedVec = vec_;
  boostedVec.Boost(zBoost);
  float theta = boostedVec.Theta();
  return TMath::Cos(theta);
}


std::vector<math::XYZTLorentzVector> BoostedUtils::GetLepVecs(const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon> selectedMuons){
  
  std::vector<math::XYZTLorentzVector> leptonVecs;
  
  for(std::vector<pat::Electron>::const_iterator itEle = selectedElectrons.begin(); itEle != selectedElectrons.end(); ++itEle){
    leptonVecs.push_back(itEle->p4());
  }
  for(std::vector<pat::Muon>::const_iterator itMu = selectedMuons.begin(); itMu != selectedMuons.end(); ++itMu){
    leptonVecs.push_back(itMu->p4());
  }
  
  std::sort(leptonVecs.begin(), leptonVecs.end(),BoostedUtils::FirstIsHarder);
  
  return leptonVecs;
  
} 


math::XYZTLorentzVector BoostedUtils::GetPrimLepVec(const std::vector<pat::Electron>& selectedElectrons,const std::vector<pat::Muon> selectedMuons){
  
  std::vector<math::XYZTLorentzVector> leptonVecs = GetLepVecs(selectedElectrons,selectedMuons);
  
  if(leptonVecs.size()==0){
    std::cerr<< "No PrimLep Found!" << std::endl;
    return math::XYZTLorentzVector();
  }
  
  return leptonVecs[0];
}


void BoostedUtils::GetNuVecs(const math::XYZTLorentzVector& lepvec, const TVector2& metvec, math::XYZTLorentzVector& nu1, math::XYZTLorentzVector& nu2){
  
  double mu = (80.4*80.4)/2 + metvec.Px()*lepvec.Px() + metvec.Py()*lepvec.Py();
  double a = (mu*lepvec.Pz())/(lepvec.E()*lepvec.E() - lepvec.Pz()*lepvec.Pz());
  double a2 = TMath::Power(a, 2);
  double b = (TMath::Power(lepvec.E(), 2.)*metvec.Mod() - TMath::Power(mu, 2.)) / (TMath::Power(lepvec.E(), 2)- TMath::Power(lepvec.Pz(), 2));
  float pz1,pz2;
  
  if (a2-b < 0) { 
    pz1 = a;
    pz2 = a;
  } else {
    double root = sqrt(a2-b);
    pz1 = a + root;
    pz2 = a - root;
  }
  
  nu1.SetPxPyPzE(metvec.Px(),metvec.Py(),pz1,sqrt(metvec.Mod2()+pz1*pz1));
  nu2.SetPxPyPzE(metvec.Px(),metvec.Py(),pz2,sqrt(metvec.Mod2()+pz2*pz2));
}


vector<math::XYZTLorentzVector> BoostedUtils::GetJetVecs(const std::vector<pat::Jet>& jets){
  std::vector<math::XYZTLorentzVector> jetVecs;
  
  for(std::vector<pat::Jet>::const_iterator itJet=jets.begin();itJet!=jets.end();++itJet){
    jetVecs.push_back(itJet->p4());
  }
  
  return jetVecs;
}


boosted::SubFilterJetCollection BoostedUtils::GetSortedByPt(boosted::SubFilterJetCollection const &subfilterjets){
  boosted::SubFilterJetCollection result = subfilterjets;
  std::sort(result.begin(), result.end(),BoostedUtils::FirstFatJetIsHarder<boosted::SubFilterJet>);
  return result;
}


boosted::HEPTopJetCollection BoostedUtils::GetSortedByPt(boosted::HEPTopJetCollection const &heptopjets){
  boosted::HEPTopJetCollection result = heptopjets;
  std::sort(result.begin(), result.end(),BoostedUtils::FirstFatJetIsHarder<boosted::HEPTopJet>);
  return result;
}


bool BoostedUtils::PassesCSV(const pat::Jet& jet, const char workingPoint){
  
  float CSVLv2wp = 0.423;
  float CSVMv2wp = 0.814;
  float CSVTv2wp = 0.941;
  
  float csvValue = jet.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  
  switch(workingPoint){
    case 'L': if(csvValue > CSVLv2wp){ return true; } break;
    case 'M': if(csvValue > CSVMv2wp){ return true; } break;
    case 'T': if(csvValue > CSVTv2wp){ return true; } break;
    case '-': return true; break;
  }
  
  return false;
}


float BoostedUtils::GetClosestJetIDs(int& idJet1, int& idJet2, const std::vector<pat::Jet>& jets){
  
  float minDr = 9.;
  for(std::vector<pat::Jet>::const_iterator itJet1 = jets.begin();itJet1 != jets.end();++itJet1){
    for(std::vector<pat::Jet>::const_iterator itJet2 = itJet1+1;itJet2 != jets.end();++itJet2){
      math::XYZTLorentzVector jetVec1 = itJet1->p4();
      math::XYZTLorentzVector jetVec2 = itJet2->p4();
      
      if(BoostedUtils::DeltaR(jetVec1,jetVec2)<minDr){
	      idJet1 = itJet1 - jets.begin();
	      idJet2 = itJet2 - jets.begin();
	      minDr = BoostedUtils::DeltaR(jetVec1,jetVec2);
      }
    }
  }
  
  return minDr;
}


float BoostedUtils::GetClosestLepJetID(int& idJet, const math::XYZTLorentzVector& lepVec, const std::vector<pat::Jet>& jets){
  
  float minDr = 9.;
  for(std::vector<pat::Jet>::const_iterator itJet = jets.begin(); itJet != jets.end(); ++itJet){
    math::XYZTLorentzVector jetVec = itJet->p4();
    if(DeltaR(lepVec,jetVec)<minDr){
	    idJet = itJet - jets.begin();
	    minDr = DeltaR(lepVec,jetVec);
    }
  }

  return minDr;
}


float BoostedUtils::GetJetAverageJetEtaMax(const std::vector<pat::Jet>& jets1, const std::vector<pat::Jet>& jets2){
  int count=0;
  float avgval=0.;
  for(std::vector<pat::Jet>::const_iterator itJet1 = jets1.begin(); itJet1 != jets1.end(); ++itJet1){
    for(std::vector<pat::Jet>::const_iterator itJet2 = itJet1+1; itJet2 != jets1.end(); ++itJet2){
      avgval += itJet1->eta()-itJet2->eta();
      count++;
    }
  }
  avgval /= count;
  
  float imax = 0.;
  float etamax=0.;
  for(std::vector<pat::Jet>::const_iterator itJet = jets2.begin(); itJet != jets2.end(); ++itJet){
    imax = abs(itJet->eta()-avgval);
    if(imax>etamax) {
      etamax = imax;
    }
  }
  return etamax;
}



bool BoostedUtils::GetTopTag(const boosted::HEPTopJet& topJet,const double& fW, const double& mTopMin, const bool& altConf){
  std::vector<pat::Jet> subjets;
  subjets.push_back(topJet.nonW);
  subjets.push_back(topJet.W1);
  subjets.push_back(topJet.W2);
  
  if(subjets.size()!=3) return false;
  
  if(!altConf)  std::sort(subjets.begin(), subjets.end(),FirstJetIsHarder);
  else          TopSubjetCSVDef(subjets);
  
  std::vector<math::XYZTLorentzVector> subjetVecs = GetJetVecs(subjets);
    
  float m12=-999;
  float m23=-999;
  float m13=-999;
  float m123=-999;
  
  m12=(subjetVecs[0]+subjetVecs[1]).M();
  m13=(subjetVecs[0]+subjetVecs[2]).M();
  m23=(subjetVecs[1]+subjetVecs[2]).M();
  m123=(subjetVecs[0]+subjetVecs[1]+subjetVecs[2]).M();

  if(m123<mTopMin) return false;
  
  float mT = 172.3;
  float mW = 80.4;
  
  float Rmin = (1-fW)*mW/mT;
  float Rmax = (1+fW)*mW/mT;
  
  if(!altConf){
    float y1 = 1+pow(m13/m12,2);
    float y2 = 1+pow(m12/m13,2);
    float x = 1-pow(m23/m123,2);  
  
    if(((0.2<atan(m23/m123)) && (atan(m23/m123)<1.3)) && ((Rmin<m23/m123) && (m23/m123<Rmax))) return true;
    if(((x>pow(Rmin,2)*y1) && (x<pow(Rmax,2)*y1)) && (m23/m123>0.35)) return true;
    if(((x>pow(Rmin,2)*y2) && (x<pow(Rmax,2)*y2)) && (m23/m123>0.35)) return true;
  }
  else{
    if(Rmin<m23/m123 && m23/m123<Rmax && 0.2<m12/m13 && 0.2<m13/m12 ) return true;
  }
  
  return false;
}


void BoostedUtils::TopSubjetCSVDef(std::vector<pat::Jet> &subjets){
  std::sort(subjets.begin(), subjets.end(),BoostedUtils::FirstHasHigherCSV);
  
  pat::Jet Bsubjet = subjets[0];
  pat::Jet W1subjet, W2subjet;
  
  if(subjets[1].pt()>subjets[2].pt()){
    W1subjet = subjets[1];
    W2subjet = subjets[2];
  }
  else{
    W1subjet = subjets[2];
    W2subjet = subjets[1];
  }
  
  subjets.clear();
  subjets.push_back(Bsubjet);
  subjets.push_back(W1subjet);
  subjets.push_back(W2subjet);
}


std::vector<pat::Jet> BoostedUtils::GetHiggsFilterJets(const boosted::SubFilterJet& higgsJet, const int& nCSVJets){

  std::vector<pat::Jet> subJets = higgsJet.filterjets;
  
  return GetHiggsFilterJets(subJets,nCSVJets);
}


std::vector<pat::Jet> BoostedUtils::GetHiggsFilterJets(const std::vector<pat::Jet>& higgsDecayJets, const int& nCSVJets){

  std::vector<pat::Jet> subJets = higgsDecayJets;
  
  std::sort(subJets.begin(), subJets.end(),BoostedUtils::FirstHasHigherCSV);
  
  std::vector<pat::Jet> HighCSVSubJets;
  
  for(std::vector<pat::Jet>::iterator itSubJet = subJets.begin(); itSubJet != subJets.end(); ){
    
    bool csvDistance = true;
    for(std::vector<pat::Jet>::iterator itCSVJet = HighCSVSubJets.begin(); itCSVJet != HighCSVSubJets.end(); ++itCSVJet){
      if(BoostedUtils::DeltaR(*itCSVJet,*itSubJet)<.4){
        csvDistance = false;
        break;
      }
    }
    
    if(csvDistance){
      HighCSVSubJets.push_back(*itSubJet);
      subJets.erase(itSubJet);
    }
    else{
      ++itSubJet;
    }
    
    if((int) HighCSVSubJets.size()>=nCSVJets) break;
  }
  
  
  if(subJets.size()==0) return HighCSVSubJets;
  else{
    std::sort(subJets.begin(), subJets.end(),BoostedUtils::FirstJetIsHarder);

    subJets.insert(subJets.begin(),HighCSVSubJets.begin(),HighCSVSubJets.end());
  }
  
  return subJets;
}


float BoostedUtils::GetHiggsMass(const boosted::SubFilterJet& higgsJet, const int& nFilterJets, const int& nBTags, const float& csvWP){
  
  if(nFilterJets<2 || nBTags>nFilterJets) return -1.;
  if(((int)higgsJet.filterjets.size())<nFilterJets || ((int)higgsJet.filterjets.size())<nBTags) return -1.;
  
  std::vector<pat::Jet> filterJets = GetHiggsFilterJets(higgsJet,nBTags);
  
  if(nBTags>0){
    if(filterJets[nBTags-1].bDiscriminator("combinedSecondaryVertexBJetTags")<csvWP) return -1.;
  }
  
  std::vector<math::XYZTLorentzVector> filterJetVecs = GetJetVecs(filterJets);
  math::XYZTLorentzVector sumVec = filterJetVecs[0];
  
  for(std::vector<math::XYZTLorentzVector>::const_iterator itFiltJet = filterJetVecs.begin()+1; itFiltJet-filterJetVecs.begin() < nFilterJets; ++itFiltJet){
    sumVec += *itFiltJet;
  }
  
  return sumVec.M();
}


// BNjetCollection BEANUtils::GetCSVJets(const BNtoptagjetCollection& toptagJets, const BNsubfilterjetCollection& subfilterJets, const BNjetCollection& selectedJets, BNjetCollection& matchedak5jets, BNjetCollection& matchedsubjets, int cutflow[], const float& ptcut, const float& etacut){
//   BNjetCollection subJets;
//   for(size_t j=0; j< subfilterJets.size(); j++){
//     for(size_t k=0; k< subfilterJets[j].filterjets.size(); k++){
//       if(subfilterJets[j].filterjets[k].pt>=ptcut && subfilterJets[j].filterjets[k].eta<etacut) subJets.push_back(subfilterJets[j].filterjets[k]);
//     }
//   }
// 
//   for(size_t j=0; j< toptagJets.size(); j++){
//     if(toptagJets[j].nonW.pt>=ptcut && toptagJets[j].nonW.eta<etacut) subJets.push_back(toptagJets[j].nonW);
//     if(toptagJets[j].W1.pt>=ptcut && toptagJets[j].W1.eta<etacut) subJets.push_back(toptagJets[j].W1);
//     if(toptagJets[j].W2.pt>=ptcut && toptagJets[j].W2.eta<etacut) subJets.push_back(toptagJets[j].W2);
//   }
// 
//   BNjetCollection unmatchedJets;
// 
//   if(subJets.size() == 0) return unmatchedJets;
// 
//   BNjetCollection subJets_sorted = BEANUtils::GetSortedByPt(subJets);
//   std::reverse(subJets_sorted.begin(), subJets_sorted.end());
// 
//   cutflow[0] = subJets_sorted.size();
// 
//   for(size_t i=0; i< subJets_sorted.size(); i++){
//     bool isalone = true;
//     for(size_t j=i+1; j< subJets_sorted.size(); j++) if(BEANUtils::DeltaR(subJets_sorted[i], subJets_sorted[j])<0.4) isalone = false;
//     if(isalone == true) unmatchedJets.push_back(subJets_sorted[i]);
//   }
// 
//   return unmatchedJets;
// 
//   cutflow[1] = unmatchedJets.size();
// 
//   for(size_t i=0; i< selectedJets.size(); i++){
//     float drmin = 0.4;
//     int indx = -1;
//     for(size_t j=0; j< unmatchedJets.size(); j++){
//       float DeltaR = BEANUtils::DeltaR(selectedJets[i], unmatchedJets[j]);
//       if(DeltaR<drmin){
//         drmin = DeltaR;
//         indx = j;
//       }
//     }
//     if(indx>0){
//       matchedak5jets.push_back(selectedJets[i]);
//       matchedsubjets.push_back(unmatchedJets[indx]);
//       unmatchedJets.erase(unmatchedJets.begin()+indx);
//     }
//   }
// 
//   cutflow[2] = unmatchedJets.size();
// 
//   for(size_t i=0; i< selectedJets.size(); i++){
//     for(size_t j=0; j< unmatchedJets.size();){
//       if(BEANUtils::DeltaR(selectedJets[i], unmatchedJets[j])<0.4) unmatchedJets.erase(unmatchedJets.begin()+j);
//       else j++;
//     }
//   }
// 
// 
//   return unmatchedJets;
// }


std::vector<TLorentzVector> BoostedUtils::GetCAMatchDiff(const boosted::SubFilterJetCollection &subfilterJets, const std::vector<pat::Jet>& jets, std::vector<float>& DCSV_Matchedfilterjets, std::vector<float>& Dr_Matchedfilterjets, const float& ptcut, const float& etacut){
  std::vector<pat::Jet> filterjets;
  for(size_t j=0; j< subfilterJets.size(); j++){
    for(size_t k=0; k< subfilterJets[j].filterjets.size(); k++){
      if(subfilterJets[j].filterjets[k].pt()>=ptcut && subfilterJets[j].filterjets[k].eta()<etacut) filterjets.push_back(subfilterJets[j].filterjets[k]);
    }
  }
  std::vector<TLorentzVector> matchjetdiff;
  for(std::vector<pat::Jet>::const_iterator itJet=jets.begin();itJet!=jets.end();++itJet){
    std::vector<pat::Jet>::const_iterator itmJet;
    float drmin = 0.3;
    for(std::vector<pat::Jet>::const_iterator itfJet=filterjets.begin();itfJet!=filterjets.end();++itfJet){
      float DeltaR = BoostedUtils::DeltaR(itJet->p4(), itfJet->p4());
      if(DeltaR<drmin){
        drmin = DeltaR;
        itmJet = itfJet;
      }
    }
    if(drmin < 0.3){
      TLorentzVector mjet;
      mjet.SetPtEtaPhiE(itmJet->pt()/itJet->pt(), itJet->eta()-itmJet->eta(), itJet->phi()-itmJet->phi(), itmJet->energy()/itJet->energy());
      matchjetdiff.push_back(mjet);
      DCSV_Matchedfilterjets.push_back(itJet->bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags")-itmJet->bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"));
      Dr_Matchedfilterjets.push_back(drmin);
//       filterjets.erase(filterjets.itmJet);
    }
  }

  return matchjetdiff;
}

std::vector<TLorentzVector> BoostedUtils::GetCAMatchDiff(const boosted::HEPTopJetCollection &heptopjets, const std::vector<pat::Jet>& jets, std::vector<float>& DCSV_Matchedfilterjets, std::vector<float>& Dr_Matchedfilterjets, const float& ptcut, const float& etacut){
  std::vector<pat::Jet> filterjets;
  for(size_t j=0; j< heptopjets.size(); j++){
    if(heptopjets[j].nonW.pt()>=ptcut && heptopjets[j].nonW.eta()<etacut) filterjets.push_back(heptopjets[j].nonW);
    if(heptopjets[j].W1.pt()>=ptcut && heptopjets[j].W1.eta()<etacut) filterjets.push_back(heptopjets[j].W1);
    if(heptopjets[j].W2.pt()>=ptcut && heptopjets[j].W2.eta()<etacut) filterjets.push_back(heptopjets[j].W2);
  }
  std::vector<TLorentzVector> matchjetdiff;
  for(std::vector<pat::Jet>::const_iterator itJet=jets.begin();itJet!=jets.end();++itJet){
    std::vector<pat::Jet>::const_iterator itmJet;
    float drmin = 0.3;
    for(std::vector<pat::Jet>::const_iterator itfJet=filterjets.begin();itfJet!=filterjets.end();++itfJet){
      float DeltaR = BoostedUtils::DeltaR(itJet->p4(), itfJet->p4());
      if(DeltaR<drmin){
        drmin = DeltaR;
        itmJet = itfJet;
      }
    }
    if(drmin < 0.3){
      TLorentzVector mjet;
      mjet.SetPtEtaPhiE(itmJet->pt()/itJet->pt(), itJet->eta()-itmJet->eta(), itJet->phi()-itmJet->phi(), itmJet->energy()/itJet->energy());
      matchjetdiff.push_back(mjet);
      DCSV_Matchedfilterjets.push_back(itJet->bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags")-itmJet->bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"));
      Dr_Matchedfilterjets.push_back(drmin);
//       filterjets.erase(filterjets.itmJet);
    }
  }

  return matchjetdiff;
}



/*










vector<BNjet> BEANUtils::GetJetsByDr(TLorentzVector vec,const std::vector<BNjet>& jets){
  closerToVec closer;
  closer.vec=vec;
  std::vector<BNjet> sorted_jets = jets;
  std::sort(sorted_jets.begin(),sorted_jets.end(),closer);
  return sorted_jets;
}




void BEANUtils::GetHiggsJetCSVVarsDr(const BNsubfilterjet& jet, BNjet& csvec1_fjet_,BNjet& csvec2_fjet_){
  float csvec1 = -.1;
  float csvec2 = -.1;
  
  int fjindex1 = -1;
  int fjindex2 = -1;
  
  for(size_t i=0;i<jet.filterjets.size();i++){
    if(jet.filterjets[i].pt>20&&jet.filterjets[i].btagCombinedSecVertex>csvec1){
      csvec1 = fmax(jet.filterjets[i].btagCombinedSecVertex,-.1);
      fjindex1 = i;
    }
  }
  for(size_t i=0;i<jet.filterjets.size();i++){
    if(jet.filterjets[i].pt>20&&jet.filterjets[i].btagCombinedSecVertex>csvec2&&i!=fjindex1&&DeltaR(jet.filterjets[i],jet.filterjets[fjindex1])>0.4){
      csvec2 = fmax(jet.filterjets[i].btagCombinedSecVertex,-.1);
      fjindex2 = i;
    }
  }
  
  if(fjindex1>=0) csvec1_fjet_ = jet.filterjets[fjindex1];
  if(fjindex2>=0) csvec2_fjet_ = jet.filterjets[fjindex2];
}


void BEANUtils::GetHiggsJetCSVVarsDr(const BNjetCollection& filterjets,BNjet& b1_fjet_,BNjet& b2_fjet_,BNjet& g_fjet_){
  float csvec1 = -.1;
  float csvec2 = -.1;
 
  int fjindex1 = -1;
  int fjindex2 = -1;
  int fjindex3 = -1;
 
  for(size_t i=0;i<filterjets.size();i++){
    if(filterjets[i].pt<20) continue;
    if(filterjets[i].btagCombinedSecVertex>csvec1){
      csvec1 = fmax(filterjets[i].btagCombinedSecVertex,-.1);
      fjindex1 = i;
    }
  }
  for(size_t i=0;i<filterjets.size();i++){
    if(filterjets[i].pt<20) continue;
    if(i==fjindex1) continue;
    if(DeltaR(filterjets[i],filterjets[fjindex1])<0.4) continue;
    if(filterjets[i].btagCombinedSecVertex>csvec2){
      csvec2 = fmax(filterjets[i].btagCombinedSecVertex,-.1);
      fjindex2 = i;
    }
  }
  for(size_t i=0;i<filterjets.size();i++){
    if(filterjets[i].pt<20) continue;
    if(i==fjindex1) continue;
    if(i==fjindex2) continue;
   
    fjindex3 = i;
  }
 
  if(fjindex1>=0) b1_fjet_ = filterjets[fjindex1];
  if(fjindex2>=0) b2_fjet_ = filterjets[fjindex2];
  if(fjindex3>=0) g_fjet_ = filterjets[fjindex3];
}




float BEANUtils::GetHiggsMass(const BNsubfilterjet& higgs_jet, const int n_filterjets, const bool hardest_jets, const int n_btags, const float csv_wp){
  
  TLorentzVector vec;
  
  int n_filterjets_found = 0;
  int n_btags_found = 0;
  
  for(size_t i=0;i<higgs_jet.filterjets.size() && n_filterjets_found<n_filterjets;i++){
  	if(higgs_jet.filterjets[i].btagCombinedSecVertex<csv_wp)
	  if(n_filterjets_found-n_btags_found < n_filterjets-n_btags) continue;
	else
	  n_btags_found ++;
	
    vec = vec +BEANUtils::GetJetVec(higgs_jet.filterjets[i]);
	n_filterjets_found++;
  }
  
  if(hardest_jets && n_filterjets_found!=n_filterjets) return -1;
  return vec.M();
}



BNjet BEANUtils::GetTopLepBjet(const BNsubfilterjet& sfjet,const BNtoptagjet& topjet, const std::vector<BNjet>& ak5jets){
  std::vector<BNjet> sortedJets=ak5jets;
  std::sort(sortedJets.begin(), sortedJets.end(),BEANUtils::FirstHasHigherCSV);  
  bool clean = false;
  BNjet bjet;
  for(size_t i=0; i<sortedJets.size()&&!clean;i++){    
    clean=true;
    if(DeltaR(sortedJets[i],topjet.W1)<0.2) clean=false;
    if(DeltaR(sortedJets[i],topjet.W2)<0.2) clean=false;
    if(DeltaR(sortedJets[i],topjet.nonW)<0.2) clean=false;
    for(size_t j=0; j<sfjet.filterjets.size()&&j<3;j++){    
      if(DeltaR(sortedJets[i],sfjet.filterjets[j])<0.2) clean=false;
    }
    if(clean) bjet=sortedJets[i];
  }
  return bjet;
}
  


bool BEANUtils::GetSelected_HiggsJets(const BNsubfilterjetCollection& subfilterjets, BNsubfilterjetCollection& selected_higgsjets, BNtoptagjet& topHadCand, BNsubfilterjet& higgsCand, bool check_subjet_overlap=true){
  
  bool foundHiggsJet=false;
  for(size_t i=0; i<subfilterjets.size();i++){
    BNjet csvec1_fjet;
    BNjet csvec2_fjet;
    BEANUtils::GetHiggsJetCSVVarsDr(subfilterjets[i],csvec1_fjet,csvec2_fjet);    
    if(csvec2_fjet.btagCombinedSecVertex>0.814&&subfilterjets[i].fatjet.pt>200 and BEANUtils::DeltaR(topHadCand.fatjet,subfilterjets[i].fatjet)>1.5 and fabs(subfilterjets[i].fatjet.eta)<=2.0) {
      //std::cout<<"test"<<std::endl;
           
      if(check_subjet_overlap){
        bool clean = true;
        for(size_t j=0; j<subfilterjets[i].filterjets.size();j++){
          if(BEANUtils::DeltaR(topHadCand.W1,subfilterjets[i].filterjets[j])<0.2) clean=false;
          if(BEANUtils::DeltaR(topHadCand.W2,subfilterjets[i].filterjets[j])<0.2) clean=false;
          if(BEANUtils::DeltaR(topHadCand.nonW,subfilterjets[i].filterjets[j])<0.2) clean=false;
          }
         if(!clean) continue;
        }//0.814 or 0.244
        
      selected_higgsjets.push_back(subfilterjets[i]);
      foundHiggsJet=true;
    }
  }
  
  if(foundHiggsJet){
    size_t maxHiggsTag=-1.0;
    for(size_t i=0; i<selected_higgsjets.size();i++){
      BNjet csvec1_fjet;
      BNjet csvec2_fjet;
      BEANUtils::GetHiggsJetCSVVarsDr(selected_higgsjets[i],csvec1_fjet,csvec2_fjet);
      if(csvec2_fjet.btagCombinedSecVertex>maxHiggsTag){
        maxHiggsTag=csvec2_fjet.btagCombinedSecVertex;
        higgsCand=selected_higgsjets[i];
      }
      
    }
  }
  
  return foundHiggsJet;
}

bool BEANUtils::MCContainsTTbar(const BNmcparticleCollection& mcparticlesStatus3){
  bool foundT=false;
  bool foundTbar=false;
  for(size_t i=0; i<mcparticlesStatus3.size();i++){
    if(mcparticlesStatus3[i].id==6) foundT=true;
    if(mcparticlesStatus3[i].id==-6) foundTbar=true;
  }
  return foundT&&foundTbar;
}
bool BEANUtils::MCContainsHiggs(const BNmcparticleCollection& mcparticlesStatus3){
  for(size_t i=0; i<mcparticlesStatus3.size();i++){
    if(mcparticlesStatus3[i].id==25) return true;
  }
  return false;
}





// parses input file names
vector<string> BEANUtils:: ParseFileNames(string fnames){
    std::vector<string> filenames;
    while(fnames.size() > 0 && *fnames.rbegin()==' '){
        fnames.erase(fnames.begin() + (fnames.size() - 1));
    }
    
    while(true){
        //erase spaces at the beginning:
        while(fnames.size() > 0 && fnames[0]==' ') fnames.erase(0, 1);
        if(fnames.size()==0) break;
        size_t spacepos = fnames.find(' ');
        if(spacepos==string::npos){
            //take the whole rest and go out of here:
            filenames.push_back(fnames);
            break;
        }
        else{
            //take all up to (excluding) the space:
            filenames.push_back(fnames.substr(0, spacepos));
            fnames.erase(0, spacepos);
        }
    }
    return filenames;
}
*/

